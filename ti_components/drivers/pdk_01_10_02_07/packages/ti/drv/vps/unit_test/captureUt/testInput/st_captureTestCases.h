/*
 *  Copyright (c) Texas Instruments Incorporated 2012-2017
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
 *  \file st_captureTestCases.h
 *
 *  \brief This file defines the test cases for CAPTURE UT.
 */

#ifndef ST_CAPTURE_TEST_CASES_H_
#define ST_CAPTURE_TEST_CASES_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <testLib/st_capture.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define ST_CAPT_NUM_TESTCASES        ((sizeof (gStCaptTestCasePrms)) / \
                                      (sizeof (st_CaptApp_TestParams)))

#if SOC_TDA2EX
#define BOARD_MAKE_VIP_INST_ID      VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA)
#define BOARD_VID_SENSOR_DRV_ID    (FVID2_VID_SENSOR_OV1063X_DRV)
#define BOARD_SOC_ID               (BSP_PLATFORM_SOC_ID_TDA2XX)
#elif defined (SOC_AM572x) || defined (SOC_AM574x)
#define BOARD_MAKE_VIP_INST_ID     VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S1, VPS_VIP_PORTB)
#define BOARD_VID_SENSOR_DRV_ID    (FVID2_VID_SENSOR_OV2659_DRV)
#define BOARD_SOC_ID               (BSP_PLATFORM_SOC_ID_AM572X)
#elif defined (SOC_AM571x)
#define BOARD_MAKE_VIP_INST_ID     VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTB)
#define BOARD_VID_SENSOR_DRV_ID    (FVID2_VID_SENSOR_OV2659_DRV)
#define BOARD_SOC_ID               (BSP_PLATFORM_SOC_ID_AM571X)
#else
#define BOARD_MAKE_VIP_INST_ID     VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA)
#define BOARD_VID_SENSOR_DRV_ID    (FVID2_VID_SENSOR_OV1063X_DRV)
#define BOARD_SOC_ID               (BSP_PLATFORM_SOC_ID_TDA2XX)
#endif

#if defined(__GNUC__) && !defined(__ti__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-braces"
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief Defines the various CAPTURE test cases. */
static st_CaptApp_TestParams gStCaptTestCasePrms[] =
{
    {
        /* testEnable */
        TEST_ENABLE,
        /* bufCaptModeTestEnable */
        BUF_CAPT_MODE_TEST_DISABLE,
        /* printEnable */
        PRINT_ENABLE,
        /* Software Requirement Id  */
        ":PDK-936:PDK-937:PDK-939:PDK-940:PDK-942:PDK-947:PDK-953:PDK-955:PDK-958:PDK-961:PDK-1215:PDK-941:",
        /* testCaseId */
        10000u,
        /* testType */
        ST_TT_SANITY,
        /* runCount */
        ST_CAPT_RUN_COUNT,
        /* testDescStr */
#ifdef SOC_TDA2EX
        "OV1063x->VIP1_S1_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), YUYV422I out",
#else
        "OV1063x->VIP1_S0_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), YUYV422I out",
#endif
        /* testCaseType */
        ST_CAPT_TCT_MAIN,
        /* numHandles */
        1u,
        NULL,
        NULL,
        /* platformId */
        BSP_PLATFORM_ID_EVM,
        /* socId */
        BOARD_SOC_ID,
        /* boardId */
        (BSP_BOARD_GP_AM572X | BSP_BOARD_IDK_AM57XX | BSP_BOARD_VISION | BSP_BOARD_BASE_TDA3XX),
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_8BIT,
        /* startstpCnt */
        1,
        /* maxSizeRegs[VPS_VIP_MAX] */
        {
            /* VPS_VIP1 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX) || defined(SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_AM574x)
            /* VPS_VIP2 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX)
            /* VPS_VIP3 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            }
#endif
#endif
        },

        /* testInstPrms[VPS_CAPT_INST_MAX] */
        {
            /*instId */
            BOARD_MAKE_VIP_INST_ID,
            /* decDrvId[] */
            BOARD_VID_SENSOR_DRV_ID,
            /* standard */
            FVID2_STD_720P_60,
            /* videoIfMode */
            FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
            /* videoIfWidth */
            FVID2_VIFW_8BIT,
            /* bufCaptMode */
            VPS_CAPT_BCM_LAST_FRM_REPEAT,
            /* numCh */
            1u,
            /* numStream */
            1u,
            /* inWidth */
            1280u,
            /* inHeight */
            720u,
            /* inDataFmt */
            FVID2_DF_YUV422P,
            /* inScanFormat */
            FVID2_SF_PROGRESSIVE,
            /* inBPP */
            FVID2_BPP_BITS16,
            /* cropStartX */
            0u,
            /* cropStartY */
            0u,
            /* cropWidth */
            1280u,
            /* cropHeight */
            720u,
            /* nonLinear */
            SC_NONLINEAR_DISABLE,
            /* stripSize */
            0u,
            /* enableScAdvCfg */
            SC_ADVCFG_DISABLE,
            /* advCfg */
            NULL,
            /* cscCoeff */
            NULL,
            /* outStrmParams[VPS_CAPT_STREAM_ID_MAX] */
            {
                /* Stream #0 */
                {
                    /* outWidth */
                    1280u,
                    /* outHeight */
                    720u,
                    /* outDataFmt */
                    FVID2_DF_YUV422I_YUYV,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_DISABLE_ALL,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                }
            }
        }
    },
    {
        /* testEnable */
        TEST_ENABLE,
        /* bufCaptModeTestEnable */
        BUF_CAPT_MODE_TEST_DISABLE,
        /* printEnable */
        PRINT_ENABLE,
        /* Software Requirement Id  */
        "SR775:PDK-877:PDK-878:PDK-879:PDK-880:PDK-881:PDK-884:PDK-885:PDK-891:PDK-899:PDK-900:PDK-904:PDK-959:",
        /* testCaseId */
        10001u,
        /* testType */
        ST_TT_SANITY,
        /* runCount */
        ST_CAPT_RUN_COUNT,
        /* testDescStr */
#ifdef SOC_TDA2EX
        "OV1063x->VIP1_S1_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), YUV420SP out",
#else
        "OV1063x->VIP1_S0_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), YUV420SP out",
#endif
        /* testCaseType */
        ST_CAPT_TCT_MAIN,
        /* numHandles */
        1u,
        NULL,
        NULL,
        /* platformId */
        BSP_PLATFORM_ID_EVM,
        /* socId */
        BOARD_SOC_ID,
        /* boardId */
        (BSP_BOARD_GP_AM572X | BSP_BOARD_IDK_AM57XX | BSP_BOARD_VISION | BSP_BOARD_BASE_TDA3XX),
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_8BIT,
        /* startstpCnt */
        1,
        /* maxSizeRegs[VPS_VIP_MAX] */
        {
            /* VPS_VIP1 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX) || defined(SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_AM574x)
            /* VPS_VIP2 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX)
            /* VPS_VIP3 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            }
#endif
#endif
        },

        /* testInstPrms[VPS_CAPT_INST_MAX] */
        {
            /*instId */
            BOARD_MAKE_VIP_INST_ID,
            /* decDrvId[] */
            BOARD_VID_SENSOR_DRV_ID,
            /* standard */
            FVID2_STD_720P_60,
            /* videoIfMode */
            FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
            /* videoIfWidth */
            FVID2_VIFW_8BIT,
            /* bufCaptMode */
            VPS_CAPT_BCM_LAST_FRM_REPEAT,
            /* numCh */
            1u,
            /* numStream */
            1u,
            /* inWidth */
            1280u,
            /* inHeight */
            720u,
            /* inDataFmt */
            FVID2_DF_YUV422P,
            /* inScanFormat */
            FVID2_SF_PROGRESSIVE,
            /* inBPP */
            FVID2_BPP_BITS16,
            /* cropStartX */
            0u,
            /* cropStartY */
            0u,
            /* cropWidth */
            1280u,
            /* cropHeight */
            720u,
            /* nonLinear */
            SC_NONLINEAR_DISABLE,
            /* stripSize */
            0u,
            /* enableScAdvCfg */
            SC_ADVCFG_DISABLE,
            /* advCfg */
            NULL,
            /* cscCoeff */
            NULL,
            /* outStrmParams[VPS_CAPT_STREAM_ID_MAX] */
            {
                /* Stream #0 */
                {
                    /* outWidth */
                    1280u,
                    /* outHeight */
                    720u,
                    /* outDataFmt */
                    FVID2_DF_YUV420SP_UV,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_DISABLE_ALL,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                }
            }
        }
    },
    {
        /* testEnable */
        TEST_ENABLE,
        /* bufCaptModeTestEnable */
        BUF_CAPT_MODE_TEST_DISABLE,
        /* printEnable */
        PRINT_ENABLE,
        /* Software Requirement Id  */
        ":PDK-912:PDK-934:PDK-713:PDK-754:PDK-869:PDK-870:PDK-871:PDK-872:PDK-873:PDK-874:PDK-875:PDK-960:",
        /* testCaseId */
        10002u,
        /* testType */
        ST_TT_SANITY,
        /* runCount */
        ST_CAPT_RUN_COUNT,
        /* testDescStr */
#ifdef SOC_TDA2EX
        "OV1063x->VIP1_S1_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), YUV422SP_UV out",
#else
        "OV1063x->VIP1_S0_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), YUV422SP_UV out",
#endif
        /* testCaseType */
        ST_CAPT_TCT_MAIN,
        /* numHandles */
        1u,
        NULL,
        NULL,
        /* platformId */
        BSP_PLATFORM_ID_EVM,
        /* socId */
        BOARD_SOC_ID,
        /* boardId */
        (BSP_BOARD_GP_AM572X | BSP_BOARD_IDK_AM57XX | BSP_BOARD_VISION | BSP_BOARD_BASE_TDA3XX),
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_8BIT,
        /* startstpCnt */
        1,
        /* maxSizeRegs[VPS_VIP_MAX] */
        {
            /* VPS_VIP1 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX) || defined(SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_AM574x)
            /* VPS_VIP2 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX)
            /* VPS_VIP3 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            }
#endif
#endif
        },

        /* testInstPrms[VPS_CAPT_INST_MAX] */
        {
            /*instId */
            BOARD_MAKE_VIP_INST_ID,
            /* decDrvId[] */
            BOARD_VID_SENSOR_DRV_ID,
            /* standard */
            FVID2_STD_720P_60,
            /* videoIfMode */
            FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
            /* videoIfWidth */
            FVID2_VIFW_8BIT,
            /* bufCaptMode */
            VPS_CAPT_BCM_LAST_FRM_REPEAT,
            /* numCh */
            1u,
            /* numStream */
            1u,
            /* inWidth */
            1280u,
            /* inHeight */
            720u,
            /* inDataFmt */
            FVID2_DF_YUV422P,
            /* inScanFormat */
            FVID2_SF_PROGRESSIVE,
            /* inBPP */
            FVID2_BPP_BITS16,
            /* cropStartX */
            0u,
            /* cropStartY */
            0u,
            /* cropWidth */
            1280u,
            /* cropHeight */
            720u,
            /* nonLinear */
            SC_NONLINEAR_DISABLE,
            /* stripSize */
            0u,
            /* enableScAdvCfg */
            SC_ADVCFG_DISABLE,
            /* advCfg */
            NULL,
            /* cscCoeff */
            NULL,
            /* outStrmParams[VPS_CAPT_STREAM_ID_MAX] */
            {
                /* Stream #0 */
                {
                    /* outWidth */
                    1280u,
                    /* outHeight */
                    720u,
                    /* outDataFmt */
                    FVID2_DF_YUV422SP_UV,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_DISABLE_ALL,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                }
            }
        }
    },
    {
        /* testEnable */
        TEST_ENABLE,
        /* bufCaptModeTestEnable */
        BUF_CAPT_MODE_TEST_DISABLE,
        /* printEnable */
        PRINT_ENABLE,
        /* Software Requirement Id  */
        ":PDK-906:PDK-907:PDK-908:PDK-909:PDK-910:PDK-916:PDK-917:PDK-918:PDK-919:PDK-920:PDK-921:PDK-927:",
        /* testCaseId */
        10003u,
        /* testType */
        ST_TT_SANITY,
        /* runCount */
        ST_CAPT_RUN_COUNT,
        /* testDescStr */
#ifdef SOC_TDA2EX
        "OV1063x->VIP1_S1_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), YUYV422I 800x480 Scaled out",
#else
        "OV1063x->VIP1_S0_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), YUYV422I 800x480 Scaled out",
#endif
        /* testCaseType */
        ST_CAPT_TCT_MAIN,
        /* numHandles */
        1u,
        NULL,
        NULL,
        /* platformId */
        BSP_PLATFORM_ID_EVM,
        /* socId */
        BOARD_SOC_ID,
        /* boardId */
        (BSP_BOARD_GP_AM572X | BSP_BOARD_IDK_AM57XX | BSP_BOARD_VISION | BSP_BOARD_BASE_TDA3XX),
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_8BIT,
        /* startstpCnt */
        1,
        /* maxSizeRegs[VPS_VIP_MAX] */
        {
            /* VPS_VIP1 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX) || defined(SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_AM574x)
            /* VPS_VIP2 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX)
            /* VPS_VIP3 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            }
#endif
#endif
        },

        /* testInstPrms[VPS_CAPT_INST_MAX] */
        {
            /*instId */
            BOARD_MAKE_VIP_INST_ID,
            /* decDrvId[] */
            BOARD_VID_SENSOR_DRV_ID,
            /* standard */
            FVID2_STD_720P_60,
            /* videoIfMode */
            FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
            /* videoIfWidth */
            FVID2_VIFW_8BIT,
            /* bufCaptMode */
            VPS_CAPT_BCM_LAST_FRM_REPEAT,
            /* numCh */
            1u,
            /* numStream */
            1u,
            /* inWidth */
            1280u,
            /* inHeight */
            720u,
            /* inDataFmt */
            FVID2_DF_YUV422P,
            /* inScanFormat */
            FVID2_SF_PROGRESSIVE,
            /* inBPP */
            FVID2_BPP_BITS16,
            /* cropStartX */
            0u,
            /* cropStartY */
            0u,
            /* cropWidth */
            1280u,
            /* cropHeight */
            720u,
            /* nonLinear */
            SC_NONLINEAR_DISABLE,
            /* stripSize */
            0u,
            /* enableScAdvCfg */
            SC_ADVCFG_DISABLE,
            /* advCfg */
            NULL,
            /* cscCoeff */
            NULL,
            /* outStrmParams[VPS_CAPT_STREAM_ID_MAX] */
            {
                /* Stream #0 */
                {
                    /* outWidth */
                    800u,
                    /* outHeight */
                    480u,
                    /* outDataFmt */
                    FVID2_DF_YUV422I_YUYV,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_ENABLE_0,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                }
            }
        }
    },
    {
        /* testEnable */
        TEST_ENABLE,
        /* bufCaptModeTestEnable */
        BUF_CAPT_MODE_TEST_DISABLE,
        /* printEnable */
        PRINT_ENABLE,
        /* Software Requirement Id  */
        ":PDK-985:",
        /* testCaseId */
        10004u,
        /* testType */
        ST_TT_SANITY,
        /* runCount */
        ST_CAPT_RUN_COUNT,
        /* testDescStr */
#ifdef SOC_TDA2EX
        "OV1063x->VIP1_S1_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), Dual out - YUYV422I, YUYV422I 800x480 Scaled out",
#else
        "OV1063x->VIP1_S0_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), Dual out - YUYV422I, YUYV422I 800x480 Scaled out",
#endif
        /* testCaseType */
        ST_CAPT_TCT_MAIN,
        /* numHandles */
        1u,
        NULL,
        NULL,
        /* platformId */
        BSP_PLATFORM_ID_EVM,
        /* socId */
        BOARD_SOC_ID,
        /* boardId */
        (BSP_BOARD_GP_AM572X | BSP_BOARD_IDK_AM57XX | BSP_BOARD_VISION | BSP_BOARD_BASE_TDA3XX),
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_8BIT,
        /* startstpCnt */
        1,
        /* maxSizeRegs[VPS_VIP_MAX] */
        {
            /* VPS_VIP1 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX) || defined(SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_AM574x)
            /* VPS_VIP2 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX)
            /* VPS_VIP3 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            }
#endif
#endif
        },

        /* testInstPrms[VPS_CAPT_INST_MAX] */
        {
            /*instId */
            BOARD_MAKE_VIP_INST_ID,
            /* decDrvId[] */
            BOARD_VID_SENSOR_DRV_ID,
            /* standard */
            FVID2_STD_720P_60,
            /* videoIfMode */
            FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
            /* videoIfWidth */
            FVID2_VIFW_8BIT,
            /* bufCaptMode */
            VPS_CAPT_BCM_LAST_FRM_REPEAT,
            /* numCh */
            1u,
            /* numStream */
            2u,
            /* inWidth */
            1280u,
            /* inHeight */
            720u,
            /* inDataFmt */
            FVID2_DF_YUV422P,
            /* inScanFormat */
            FVID2_SF_PROGRESSIVE,
            /* inBPP */
            FVID2_BPP_BITS16,
            /* cropStartX */
            0u,
            /* cropStartY */
            0u,
            /* cropWidth */
            1280u,
            /* cropHeight */
            720u,
            /* nonLinear */
            SC_NONLINEAR_DISABLE,
            /* stripSize */
            0u,
            /* enableScAdvCfg */
            SC_ADVCFG_DISABLE,
            /* advCfg */
            NULL,
            /* cscCoeff */
            NULL,
            /* outStrmParams[VPS_CAPT_STREAM_ID_MAX] */
            {
                /* Stream #0 */
                {
                    /* outWidth */
                    1280u,
                    /* outHeight */
                    720u,
                    /* outDataFmt */
                    FVID2_DF_YUV422I_YUYV,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_DISABLE_ALL,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                },
                /* Stream #1 */
                {
                    /* outWidth */
                    800u,
                    /* outHeight */
                    480u,
                    /* outDataFmt */
                    FVID2_DF_YUV422I_YUYV,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_ENABLE_1,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                }
            }
        }
    },
    {
        /* testEnable */
        TEST_ENABLE,
        /* bufCaptModeTestEnable */
        BUF_CAPT_MODE_TEST_DISABLE,
        /* printEnable */
        PRINT_ENABLE,
        /* Software Requirement Id  */
        ":PDK-754:",
        /* testCaseId */
        10005u,
        /* testType */
        ST_TT_SANITY,
        /* runCount */
        ST_CAPT_RUN_COUNT,
        /* testDescStr */
#ifdef SOC_TDA2EX
        "OV1063x->VIP1_S1_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), UYVY422I out",
#else
        "OV1063x->VIP1_S0_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), UYVY422I out",
#endif
        /* testCaseType */
        ST_CAPT_TCT_MAIN,
        /* numHandles */
        1u,
        NULL,
        NULL,
        /* platformId */
        BSP_PLATFORM_ID_EVM,
        /* socId */
        BOARD_SOC_ID,
        /* boardId */
        (BSP_BOARD_GP_AM572X | BSP_BOARD_IDK_AM57XX | BSP_BOARD_VISION | BSP_BOARD_BASE_TDA3XX),
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_8BIT,
        /* startstpCnt */
        1,
        /* maxSizeRegs[VPS_VIP_MAX] */
        {
            /* VPS_VIP1 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX) || defined(SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_AM574x)
            /* VPS_VIP2 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX)
            /* VPS_VIP3 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            }
#endif
#endif
        },

        /* testInstPrms[VPS_CAPT_INST_MAX] */
        {
            /* instId[] */
            BOARD_MAKE_VIP_INST_ID,
            /* decDrvId[] */
            BOARD_VID_SENSOR_DRV_ID,
            /* standard */
            FVID2_STD_720P_60,
            /* videoIfMode */
            FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
            /* videoIfWidth */
            FVID2_VIFW_8BIT,
            /* bufCaptMode */
            VPS_CAPT_BCM_LAST_FRM_REPEAT,
            /* numCh */
            1u,
            /* numStream */
            1u,
            /* inWidth */
            1280u,
            /* inHeight */
            720u,
            /* inDataFmt */
            FVID2_DF_YUV422P,
            /* inScanFormat */
            FVID2_SF_PROGRESSIVE,
            /* inBPP */
            FVID2_BPP_BITS16,
            /* cropStartX */
            0u,
            /* cropStartY */
            0u,
            /* cropWidth */
            1280u,
            /* cropHeight */
            720u,
            /* nonLinear */
            SC_NONLINEAR_DISABLE,
            /* stripSize */
            0u,
            /* enableScAdvCfg */
            SC_ADVCFG_DISABLE,
            /* advCfg */
            NULL,
            /* cscCoeff */
            NULL,
            /* outStrmParams[VPS_CAPT_STREAM_ID_MAX] */
            {
                /* Stream #0 */
                {
                    /* outWidth */
                    1280u,
                    /* outHeight */
                    720u,
                    /* outDataFmt */
                    FVID2_DF_YUV422I_UYVY,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_DISABLE_ALL,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                }
            }
        }
    },
    {
        /* testEnable */
        TEST_ENABLE,
        /* bufCaptModeTestEnable */
        BUF_CAPT_MODE_TEST_DISABLE,
        /* printEnable */
        PRINT_ENABLE,
        /* Software Requirement Id  */
        ":PDK-963:",
        /* testCaseId */
        10006u,
        /* testType */
        ST_TT_SANITY,
        /* runCount */
        ST_CAPT_RUN_COUNT,
        /* testDescStr */
#ifdef SOC_TDA2EX
        "OV1063x->VIP1_S1_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), 8 Bit Raw data out",
#else
        "OV1063x->VIP1_S0_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), 8 Bit Raw data out",
#endif
        /* testCaseType */
        ST_CAPT_TCT_MAIN,
        /* numHandles */
        1u,
        NULL,
        NULL,
        /* platformId */
        BSP_PLATFORM_ID_EVM,
        /* socId */
        BOARD_SOC_ID,
        /* boardId */
        (BSP_BOARD_GP_AM572X | BSP_BOARD_IDK_AM57XX | BSP_BOARD_VISION | BSP_BOARD_BASE_TDA3XX),
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_8BIT,
        /* startstpCnt */
        1,
        /* maxSizeRegs[VPS_VIP_MAX] */
        {
            /* VPS_VIP1 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX) || defined(SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_AM574x)
            /* VPS_VIP2 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX)
            /* VPS_VIP3 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            }
#endif
#endif
        },

        /* testInstPrms[VPS_CAPT_INST_MAX] */
        {
            /* instId[] */
            BOARD_MAKE_VIP_INST_ID,
            /* decDrvId[] */
            BOARD_VID_SENSOR_DRV_ID,
            /* standard */
            FVID2_STD_720P_60,
            /* videoIfMode */
            FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
            /* videoIfWidth */
            FVID2_VIFW_8BIT,
            /* bufCaptMode */
            VPS_CAPT_BCM_LAST_FRM_REPEAT,
            /* numCh */
            1u,
            /* numStream */
            1u,
            /* inWidth */
            1280u,
            /* inHeight */
            720u,
            /* inDataFmt */
            FVID2_DF_YUV422P,
            /* inScanFormat */
            FVID2_SF_PROGRESSIVE,
            /* inBPP */
            FVID2_BPP_BITS16,
            /* cropStartX */
            0u,
            /* cropStartY */
            0u,
            /* cropWidth */
            1280u,
            /* cropHeight */
            720u,
            /* nonLinear */
            SC_NONLINEAR_DISABLE,
            /* stripSize */
            0u,
            /* enableScAdvCfg */
            SC_ADVCFG_DISABLE,
            /* advCfg */
            NULL,
            /* cscCoeff */
            NULL,
            /* outStrmParams[VPS_CAPT_STREAM_ID_MAX] */
            {
                /* Stream #0 */
                {
                    /* outWidth */
                    1280u,
                    /* outHeight */
                    720u,
                    /* outDataFmt */
                    FVID2_DF_RAW08,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_DISABLE_ALL,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                }
            }
        }
    },
    {
        /* testEnable */
        TEST_ENABLE,
        /* bufCaptModeTestEnable */
        BUF_CAPT_MODE_TEST_DISABLE,
        /* printEnable */
        PRINT_ENABLE,
        /* Software Requirement Id  */
        ":PDK-965:",
        /* testCaseId */
        10007u,
        /* testType */
        ST_TT_SANITY,
        /* runCount */
        ST_CAPT_RUN_COUNT,
        /* testDescStr */
#ifdef SOC_TDA2EX
        "OV1063x->VIP1_S1_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), 24 bit Raw data out",
#else
        "OV1063x->VIP1_S0_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), 24 bit Raw data out",
#endif
        /* testCaseType */
        ST_CAPT_TCT_MAIN,
        /* numHandles */
        1u,
        NULL,
        NULL,
        /* platformId */
        BSP_PLATFORM_ID_EVM,
        /* socId */
        BOARD_SOC_ID,
        /* boardId */
        (BSP_BOARD_GP_AM572X | BSP_BOARD_IDK_AM57XX | BSP_BOARD_VISION | BSP_BOARD_BASE_TDA3XX),
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_8BIT,
        /* startstpCnt */
        1,
        /* maxSizeRegs[VPS_VIP_MAX] */
        {
            /* VPS_VIP1 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX) || defined(SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_AM574x)
            /* VPS_VIP2 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX)
            /* VPS_VIP3 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            }
#endif
#endif
        },

        /* testInstPrms[VPS_CAPT_INST_MAX] */
        {
            /* instId[] */
            BOARD_MAKE_VIP_INST_ID,
            /* decDrvId[] */
            BOARD_VID_SENSOR_DRV_ID,
            /* standard */
            FVID2_STD_720P_60,
            /* videoIfMode */
            FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
            /* videoIfWidth */
            FVID2_VIFW_8BIT,
            /* bufCaptMode */
            VPS_CAPT_BCM_LAST_FRM_REPEAT,
            /* numCh */
            1u,
            /* numStream */
            1u,
            /* inWidth */
            1280u,
            /* inHeight */
            720u,
            /* inDataFmt */
            FVID2_DF_YUV422P,
            /* inScanFormat */
            FVID2_SF_PROGRESSIVE,
            /* inBPP */
            FVID2_BPP_BITS16,
            /* cropStartX */
            0u,
            /* cropStartY */
            0u,
            /* cropWidth */
            1280u,
            /* cropHeight */
            720u,
            /* nonLinear */
            SC_NONLINEAR_DISABLE,
            /* stripSize */
            0u,
            /* enableScAdvCfg */
            SC_ADVCFG_DISABLE,
            /* advCfg */
            NULL,
            /* cscCoeff */
            NULL,
            /* outStrmParams[VPS_CAPT_STREAM_ID_MAX] */
            {
                /* Stream #0 */
                {
                    /* outWidth */
                    1280u,
                    /* outHeight */
                    720u,
                    /* outDataFmt */
                    FVID2_DF_RAW24,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_DISABLE_ALL,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                }
            }
        }
    },
    {
        /* testEnable */
        TEST_ENABLE,
        /* bufCaptModeTestEnable */
        BUF_CAPT_MODE_TEST_DISABLE,
        /* printEnable */
        PRINT_ENABLE,
        /* Software Requirement Id  */
        ":PDK-967:",
        /* testCaseId */
        10008u,
        /* testType */
        ST_TT_SANITY,
        /* runCount */
        ST_CAPT_RUN_COUNT,
        /* testDescStr */
#ifdef SOC_TDA2EX
        "OV1063x->VIP1_S1_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), Dual out - YUYV422I, YUYV422I",
#else
        "OV1063x->VIP1_S0_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), Dual out - YUYV422I, YUYV422I",
#endif
        /* testCaseType */
        ST_CAPT_TCT_MAIN,
        /* numHandles */
        1u,
        NULL,
        NULL,
        /* platformId */
        BSP_PLATFORM_ID_EVM,
        /* socId */
        BOARD_SOC_ID,
        /* boardId */
        (BSP_BOARD_GP_AM572X | BSP_BOARD_IDK_AM57XX | BSP_BOARD_VISION | BSP_BOARD_BASE_TDA3XX),
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_8BIT,
        /* startstpCnt */
        1,
        /* maxSizeRegs[VPS_VIP_MAX] */
        {
            /* VPS_VIP1 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX) || defined(SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_AM574x)
            /* VPS_VIP2 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX)
            /* VPS_VIP3 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            }
#endif
#endif
        },

        /* testInstPrms[VPS_CAPT_INST_MAX] */
        {
            /* instId[] */
            BOARD_MAKE_VIP_INST_ID,
            /* decDrvId[] */
            BOARD_VID_SENSOR_DRV_ID,
            /* standard */
            FVID2_STD_720P_60,
            /* videoIfMode */
            FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
            /* videoIfWidth */
            FVID2_VIFW_8BIT,
            /* bufCaptMode */
            VPS_CAPT_BCM_LAST_FRM_REPEAT,
            /* numCh */
            1u,
            /* numStream */
            2u,
            /* inWidth */
            1280u,
            /* inHeight */
            720u,
            /* inDataFmt */
            FVID2_DF_YUV422P,
            /* inScanFormat */
            FVID2_SF_PROGRESSIVE,
            /* inBPP */
            FVID2_BPP_BITS16,
            /* cropStartX */
            0u,
            /* cropStartY */
            0u,
            /* cropWidth */
            1280u,
            /* cropHeight */
            720u,
            /* nonLinear */
            SC_NONLINEAR_DISABLE,
            /* stripSize */
            0u,
            /* enableScAdvCfg */
            SC_ADVCFG_DISABLE,
            /* advCfg */
            NULL,
            /* cscCoeff */
            NULL,
            /* outStrmParams[VPS_CAPT_STREAM_ID_MAX] */
            {
                /* Stream #0 */
                {
                    /* outWidth */
                    1280u,
                    /* outHeight */
                    720u,
                    /* outDataFmt */
                    FVID2_DF_YUV422I_YUYV,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_DISABLE_ALL,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                },
                /* Stream #1 */
                {
                    /* outWidth */
                    1280u,
                    /* outHeight */
                    720u,
                    /* outDataFmt */
                    FVID2_DF_YUV422I_YUYV,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_DISABLE_ALL,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                }
            }
        }
    },
    {
        /* testEnable */
        TEST_ENABLE,
        /* bufCaptModeTestEnable */
        BUF_CAPT_MODE_TEST_DISABLE,
        /* printEnable */
        PRINT_ENABLE,
        /* Software Requirement Id  */
        ":PDK-968:",
        /* testCaseId */
        10009u,
        /* testType */
        ST_TT_SANITY,
        /* runCount */
        ST_CAPT_RUN_COUNT,
        /* testDescStr */
#ifdef SOC_TDA2EX
        "OV1063x->VIP1_S1_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), Dual out - YUYV422I, YUV420SP",
#else
        "OV1063x->VIP1_S0_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), Dual out - YUYV422I, YUV420SP",
#endif
        /* testCaseType */
        ST_CAPT_TCT_MAIN,
        /* numHandles */
        1u,
        NULL,
        NULL,
        /* platformId */
        BSP_PLATFORM_ID_EVM,
        /* socId */
        BOARD_SOC_ID,
        /* boardId */
        (BSP_BOARD_GP_AM572X | BSP_BOARD_IDK_AM57XX | BSP_BOARD_VISION | BSP_BOARD_BASE_TDA3XX),
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_8BIT,
        /* startstpCnt */
        1,
        /* maxSizeRegs[VPS_VIP_MAX] */
        {
            /* VPS_VIP1 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX) || defined(SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_AM574x)
            /* VPS_VIP2 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX)
            /* VPS_VIP3 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            }
#endif
#endif
        },

        /* testInstPrms[VPS_CAPT_INST_MAX] */
        {
            /* instId[] */
            BOARD_MAKE_VIP_INST_ID,
            /* decDrvId[] */
            BOARD_VID_SENSOR_DRV_ID,
            /* standard */
            FVID2_STD_720P_60,
            /* videoIfMode */
            FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
            /* videoIfWidth */
            FVID2_VIFW_8BIT,
            /* bufCaptMode */
            VPS_CAPT_BCM_LAST_FRM_REPEAT,
            /* numCh */
            1u,
            /* numStream */
            2u,
            /* inWidth */
            1280u,
            /* inHeight */
            720u,
            /* inDataFmt */
            FVID2_DF_YUV422P,
            /* inScanFormat */
            FVID2_SF_PROGRESSIVE,
            /* inBPP */
            FVID2_BPP_BITS16,
            /* cropStartX */
            0u,
            /* cropStartY */
            0u,
            /* cropWidth */
            1280u,
            /* cropHeight */
            720u,
            /* nonLinear */
            SC_NONLINEAR_DISABLE,
            /* stripSize */
            0u,
            /* enableScAdvCfg */
            SC_ADVCFG_DISABLE,
            /* advCfg */
            NULL,
            /* cscCoeff */
            NULL,
            /* outStrmParams[VPS_CAPT_STREAM_ID_MAX] */
            {
                /* Stream #0 */
                {
                    /* outWidth */
                    1280u,
                    /* outHeight */
                    720u,
                    /* outDataFmt */
                    FVID2_DF_YUV422I_YUYV,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_DISABLE_ALL,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                },
                /* Stream #1 */
                {
                    /* outWidth */
                    1280u,
                    /* outHeight */
                    720u,
                    /* outDataFmt */
                    FVID2_DF_YUV420SP_UV,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_DISABLE_ALL,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                }
            }
        }
    },
    {
        /* testEnable */
        TEST_ENABLE,
        /* bufCaptModeTestEnable */
        BUF_CAPT_MODE_TEST_DISABLE,
        /* printEnable */
        PRINT_ENABLE,
        /* Software Requirement Id  */
        ":PDK-969:",
        /* testCaseId */
        10010u,
        /* testType */
        ST_TT_SANITY,
        /* runCount */
        ST_CAPT_RUN_COUNT,
        /* testDescStr */
#ifdef SOC_TDA2EX
        "OV1063x->VIP1_S1_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), Dual out - YUYV422I, RGB888",
#else
        "OV1063x->VIP1_S0_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), Dual out - YUYV422I, RGB888",
#endif
        /* testCaseType */
        ST_CAPT_TCT_MAIN,
        /* numHandles */
        1u,
        NULL,
        NULL,
        /* platformId */
        BSP_PLATFORM_ID_EVM,
        /* socId */
        BOARD_SOC_ID,
        /* boardId */
        (BSP_BOARD_GP_AM572X | BSP_BOARD_IDK_AM57XX | BSP_BOARD_VISION | BSP_BOARD_BASE_TDA3XX),
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_8BIT,
        /* startstpCnt */
        1,
        /* maxSizeRegs[VPS_VIP_MAX] */
        {
            /* VPS_VIP1 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX) || defined(SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_AM574x)
            /* VPS_VIP2 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX)
            /* VPS_VIP3 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            }
#endif
#endif
        },

        /* testInstPrms[VPS_CAPT_INST_MAX] */
        {
            /* instId[] */
            BOARD_MAKE_VIP_INST_ID,
            /* decDrvId[] */
            BOARD_VID_SENSOR_DRV_ID,
            /* standard */
            FVID2_STD_720P_60,
            /* videoIfMode */
            FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
            /* videoIfWidth */
            FVID2_VIFW_8BIT,
            /* bufCaptMode */
            VPS_CAPT_BCM_LAST_FRM_REPEAT,
            /* numCh */
            1u,
            /* numStream */
            2u,
            /* inWidth */
            1280u,
            /* inHeight */
            720u,
            /* inDataFmt */
            FVID2_DF_YUV422P,
            /* inScanFormat */
            FVID2_SF_PROGRESSIVE,
            /* inBPP */
            FVID2_BPP_BITS16,
            /* cropStartX */
            0u,
            /* cropStartY */
            0u,
            /* cropWidth */
            1280u,
            /* cropHeight */
            720u,
            /* nonLinear */
            SC_NONLINEAR_DISABLE,
            /* stripSize */
            0u,
            /* enableScAdvCfg */
            SC_ADVCFG_DISABLE,
            /* advCfg */
            NULL,
            /* cscCoeff */
            NULL,
            /* outStrmParams[VPS_CAPT_STREAM_ID_MAX] */
            {
                /* Stream #0 */
                {
                    /* outWidth */
                    1280u,
                    /* outHeight */
                    720u,
                    /* outDataFmt */
                    FVID2_DF_YUV422I_YUYV,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_DISABLE_ALL,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                },
                /* Stream #1 */
                {
                    /* outWidth */
                    1280u,
                    /* outHeight */
                    720u,
                    /* outDataFmt */
                    FVID2_DF_RGB24_888,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_DISABLE_ALL,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                }
            }
        }
    },
    {
        /* testEnable */
        TEST_ENABLE,
        /* bufCaptModeTestEnable */
        BUF_CAPT_MODE_TEST_DISABLE,
        /* printEnable */
        PRINT_ENABLE,
        /* Software Requirement Id  */
        ":PDK-970:",
        /* testCaseId */
        10011u,
        /* testType */
        ST_TT_SANITY,
        /* runCount */
        ST_CAPT_RUN_COUNT,
        /* testDescStr */
#ifdef SOC_TDA2EX
        "OV1063x->VIP1_S1_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), Dual out - YUV420SP, YUYV422I",
#else
        "OV1063x->VIP1_S0_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), Dual out - YUV420SP, YUYV422I",
#endif
        /* testCaseType */
        ST_CAPT_TCT_MAIN,
        /* numHandles */
        1u,
        NULL,
        NULL,
        /* platformId */
        BSP_PLATFORM_ID_EVM,
        /* socId */
        BOARD_SOC_ID,
        /* boardId */
        (BSP_BOARD_GP_AM572X | BSP_BOARD_IDK_AM57XX | BSP_BOARD_VISION | BSP_BOARD_BASE_TDA3XX),
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_8BIT,
        /* startstpCnt */
        1,
        /* maxSizeRegs[VPS_VIP_MAX] */
        {
            /* VPS_VIP1 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX) || defined(SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_AM574x)
            /* VPS_VIP2 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX)
            /* VPS_VIP3 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            }
#endif
#endif
        },

        /* testInstPrms[VPS_CAPT_INST_MAX] */
        {
            /* instId[] */
            BOARD_MAKE_VIP_INST_ID,
            /* decDrvId[] */
            BOARD_VID_SENSOR_DRV_ID,
            /* standard */
            FVID2_STD_720P_60,
            /* videoIfMode */
            FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
            /* videoIfWidth */
            FVID2_VIFW_8BIT,
            /* bufCaptMode */
            VPS_CAPT_BCM_LAST_FRM_REPEAT,
            /* numCh */
            1u,
            /* numStream */
            2u,
            /* inWidth */
            1280u,
            /* inHeight */
            720u,
            /* inDataFmt */
            FVID2_DF_YUV422P,
            /* inScanFormat */
            FVID2_SF_PROGRESSIVE,
            /* inBPP */
            FVID2_BPP_BITS16,
            /* cropStartX */
            0u,
            /* cropStartY */
            0u,
            /* cropWidth */
            1280u,
            /* cropHeight */
            720u,
            /* nonLinear */
            SC_NONLINEAR_DISABLE,
            /* stripSize */
            0u,
            /* enableScAdvCfg */
            SC_ADVCFG_DISABLE,
            /* advCfg */
            NULL,
            /* cscCoeff */
            NULL,
            /* outStrmParams[VPS_CAPT_STREAM_ID_MAX] */
            {
                /* Stream #0 */
                {
                    /* outWidth */
                    1280u,
                    /* outHeight */
                    720u,
                    /* outDataFmt */
                    FVID2_DF_YUV420SP_UV,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_DISABLE_ALL,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                },
                /* Stream #1 */
                {
                    /* outWidth */
                    1280u,
                    /* outHeight */
                    720u,
                    /* outDataFmt */
                    FVID2_DF_YUV422I_YUYV,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_DISABLE_ALL,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                }
            }
        }
    },
    {
        /* testEnable */
        TEST_ENABLE,
        /* bufCaptModeTestEnable */
        BUF_CAPT_MODE_TEST_DISABLE,
        /* printEnable */
        PRINT_ENABLE,
        /* Software Requirement Id  */
        ":PDK-971:",
        /* testCaseId */
        10012u,
        /* testType */
        ST_TT_SANITY,
        /* runCount */
        ST_CAPT_RUN_COUNT,
        /* testDescStr */
#ifdef SOC_TDA2EX
        "OV1063x->VIP1_S1_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), Dual out - YUV420SP, YUV420SP",
#else
        "OV1063x->VIP1_S0_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), Dual out - YUV420SP, YUV420SP",
#endif
        /* testCaseType */
        ST_CAPT_TCT_MAIN,
        /* numHandles */
        1u,
        NULL,
        NULL,
        /* platformId */
        BSP_PLATFORM_ID_EVM,
        /* socId */
        BOARD_SOC_ID,
        /* boardId */
        (BSP_BOARD_GP_AM572X | BSP_BOARD_IDK_AM57XX | BSP_BOARD_VISION | BSP_BOARD_BASE_TDA3XX),
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_8BIT,
        /* startstpCnt */
        1,
        /* maxSizeRegs[VPS_VIP_MAX] */
        {
            /* VPS_VIP1 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX) || defined(SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_AM574x)
            /* VPS_VIP2 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX)
            /* VPS_VIP3 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            }
#endif
#endif
        },

        /* testInstPrms[VPS_CAPT_INST_MAX] */
        {
            /* instId[] */
            BOARD_MAKE_VIP_INST_ID,
            /* decDrvId[] */
            BOARD_VID_SENSOR_DRV_ID,
            /* standard */
            FVID2_STD_720P_60,
            /* videoIfMode */
            FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
            /* videoIfWidth */
            FVID2_VIFW_8BIT,
            /* bufCaptMode */
            VPS_CAPT_BCM_LAST_FRM_REPEAT,
            /* numCh */
            1u,
            /* numStream */
            2u,
            /* inWidth */
            1280u,
            /* inHeight */
            720u,
            /* inDataFmt */
            FVID2_DF_YUV422P,
            /* inScanFormat */
            FVID2_SF_PROGRESSIVE,
            /* inBPP */
            FVID2_BPP_BITS16,
            /* cropStartX */
            0u,
            /* cropStartY */
            0u,
            /* cropWidth */
            1280u,
            /* cropHeight */
            720u,
            /* nonLinear */
            SC_NONLINEAR_DISABLE,
            /* stripSize */
            0u,
            /* enableScAdvCfg */
            SC_ADVCFG_DISABLE,
            /* advCfg */
            NULL,
            /* cscCoeff */
            NULL,
            /* outStrmParams[VPS_CAPT_STREAM_ID_MAX] */
            {
                /* Stream #0 */
                {
                    /* outWidth */
                    1280u,
                    /* outHeight */
                    720u,
                    /* outDataFmt */
                    FVID2_DF_YUV420SP_UV,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_DISABLE_ALL,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                },
                /* Stream #1 */
                {
                    /* outWidth */
                    1280u,
                    /* outHeight */
                    720u,
                    /* outDataFmt */
                    FVID2_DF_YUV420SP_UV,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_DISABLE_ALL,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                }
            }
        }
    },
    {
        /* testEnable */
        TEST_ENABLE,
        /* bufCaptModeTestEnable */
        BUF_CAPT_MODE_TEST_DISABLE,
        /* printEnable */
        PRINT_ENABLE,
        /* Software Requirement Id  */
        ":PDK-972:",
        /* testCaseId */
        10013u,
        /* testType */
        ST_TT_SANITY,
        /* runCount */
        ST_CAPT_RUN_COUNT,
        /* testDescStr */
#ifdef SOC_TDA2EX
        "OV1063x->VIP1_S1_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), Dual out - YUV420SP, RGB888",
#else
        "OV1063x->VIP1_S0_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), Dual out - YUV420SP, RGB888",
#endif
        /* testCaseType */
        ST_CAPT_TCT_MAIN,
        /* numHandles */
        1u,
        NULL,
        NULL,
        /* platformId */
        BSP_PLATFORM_ID_EVM,
        /* socId */
        BOARD_SOC_ID,
        /* boardId */
        (BSP_BOARD_GP_AM572X | BSP_BOARD_IDK_AM57XX | BSP_BOARD_VISION | BSP_BOARD_BASE_TDA3XX),
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_8BIT,
        /* startstpCnt */
        1,
        /* maxSizeRegs[VPS_VIP_MAX] */
        {
            /* VPS_VIP1 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX) || defined(SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_AM574x)
            /* VPS_VIP2 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX)
            /* VPS_VIP3 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            }
#endif
#endif
        },

        /* testInstPrms[VPS_CAPT_INST_MAX] */
        {
            /* instId[] */
            BOARD_MAKE_VIP_INST_ID,
            /* decDrvId[] */
            BOARD_VID_SENSOR_DRV_ID,
            /* standard */
            FVID2_STD_720P_60,
            /* videoIfMode */
            FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
            /* videoIfWidth */
            FVID2_VIFW_8BIT,
            /* bufCaptMode */
            VPS_CAPT_BCM_LAST_FRM_REPEAT,
            /* numCh */
            1u,
            /* numStream */
            2u,
            /* inWidth */
            1280u,
            /* inHeight */
            720u,
            /* inDataFmt */
            FVID2_DF_YUV422P,
            /* inScanFormat */
            FVID2_SF_PROGRESSIVE,
            /* inBPP */
            FVID2_BPP_BITS16,
            /* cropStartX */
            0u,
            /* cropStartY */
            0u,
            /* cropWidth */
            1280u,
            /* cropHeight */
            720u,
            /* nonLinear */
            SC_NONLINEAR_DISABLE,
            /* stripSize */
            0u,
            /* enableScAdvCfg */
            SC_ADVCFG_DISABLE,
            /* advCfg */
            NULL,
            /* cscCoeff */
            NULL,
            /* outStrmParams[VPS_CAPT_STREAM_ID_MAX] */
            {
                /* Stream #0 */
                {
                    /* outWidth */
                    1280u,
                    /* outHeight */
                    720u,
                    /* outDataFmt */
                    FVID2_DF_YUV420SP_UV,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_DISABLE_ALL,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                },
                /* Stream #1 */
                {
                    /* outWidth */
                    1280u,
                    /* outHeight */
                    720u,
                    /* outDataFmt */
                    FVID2_DF_RGB24_888,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_DISABLE_ALL,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                }
            }
        }
    },
    {
        /* testEnable */
        TEST_ENABLE,
        /* bufCaptModeTestEnable */
        BUF_CAPT_MODE_TEST_DISABLE,
        /* printEnable */
        PRINT_ENABLE,
        /* Software Requirement Id  */
        ":PDK-973:",
        /* testCaseId */
        10014u,
        /* testType */
        ST_TT_SANITY,
        /* runCount */
        ST_CAPT_RUN_COUNT,
        /* testDescStr */
#ifdef SOC_TDA2EX
        "OV1063x->VIP1_S1_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), Dual out - YUV422SP, YUYV422I",
#else
        "OV1063x->VIP1_S0_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), Dual out - YUV422SP, YUYV422I",
#endif
        /* testCaseType */
        ST_CAPT_TCT_MAIN,
        /* numHandles */
        1u,
        NULL,
        NULL,
        /* platformId */
        BSP_PLATFORM_ID_EVM,
        /* socId */
        BOARD_SOC_ID,
        /* boardId */
        (BSP_BOARD_GP_AM572X | BSP_BOARD_IDK_AM57XX | BSP_BOARD_VISION | BSP_BOARD_BASE_TDA3XX),
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_8BIT,
        /* startstpCnt */
        1,
        /* maxSizeRegs[VPS_VIP_MAX] */
        {
            /* VPS_VIP1 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX) || defined(SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_AM574x)
            /* VPS_VIP2 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX)
            /* VPS_VIP3 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            }
#endif
#endif
        },

        /* testInstPrms[VPS_CAPT_INST_MAX] */
        {
            /* instId[] */
            BOARD_MAKE_VIP_INST_ID,
            /* decDrvId[] */
            BOARD_VID_SENSOR_DRV_ID,
            /* standard */
            FVID2_STD_720P_60,
            /* videoIfMode */
            FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
            /* videoIfWidth */
            FVID2_VIFW_8BIT,
            /* bufCaptMode */
            VPS_CAPT_BCM_LAST_FRM_REPEAT,
            /* numCh */
            1u,
            /* numStream */
            2u,
            /* inWidth */
            1280u,
            /* inHeight */
            720u,
            /* inDataFmt */
            FVID2_DF_YUV422P,
            /* inScanFormat */
            FVID2_SF_PROGRESSIVE,
            /* inBPP */
            FVID2_BPP_BITS16,
            /* cropStartX */
            0u,
            /* cropStartY */
            0u,
            /* cropWidth */
            1280u,
            /* cropHeight */
            720u,
            /* nonLinear */
            SC_NONLINEAR_DISABLE,
            /* stripSize */
            0u,
            /* enableScAdvCfg */
            SC_ADVCFG_DISABLE,
            /* advCfg */
            NULL,
            /* cscCoeff */
            NULL,
            /* outStrmParams[VPS_CAPT_STREAM_ID_MAX] */
            {
                /* Stream #0 */
                {
                    /* outWidth */
                    1280u,
                    /* outHeight */
                    720u,
                    /* outDataFmt */
                    FVID2_DF_YUV422SP_UV,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_DISABLE_ALL,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                },
                /* Stream #1 */
                {
                    /* outWidth */
                    1280u,
                    /* outHeight */
                    720u,
                    /* outDataFmt */
                    FVID2_DF_YUV422I_YUYV,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_DISABLE_ALL,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                }
            }
        }
    },
    {
        /* testEnable */
        TEST_ENABLE,
        /* bufCaptModeTestEnable */
        BUF_CAPT_MODE_TEST_DISABLE,
        /* printEnable */
        PRINT_ENABLE,
        /* Software Requirement Id  */
        ":PDK-974:",
        /* testCaseId */
        10015u,
        /* testType */
        ST_TT_SANITY,
        /* runCount */
        ST_CAPT_RUN_COUNT,
        /* testDescStr */
#ifdef SOC_TDA2EX
        "OV1063x->VIP1_S1_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), Dual out - RGB888, YUYV422I",
#else
        "OV1063x->VIP1_S0_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), Dual out - RGB888, YUYV422I",
#endif
        /* testCaseType */
        ST_CAPT_TCT_MAIN,
        /* numHandles */
        1u,
        NULL,
        NULL,
        /* platformId */
        BSP_PLATFORM_ID_EVM,
        /* socId */
        BOARD_SOC_ID,
        /* boardId */
        (BSP_BOARD_GP_AM572X | BSP_BOARD_IDK_AM57XX | BSP_BOARD_VISION | BSP_BOARD_BASE_TDA3XX),
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_8BIT,
        /* startstpCnt */
        1,
        /* maxSizeRegs[VPS_VIP_MAX] */
        {
            /* VPS_VIP1 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX) || defined(SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_AM574x)
            /* VPS_VIP2 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX)
            /* VPS_VIP3 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            }
#endif
#endif
        },

        /* testInstPrms[VPS_CAPT_INST_MAX] */
        {
            /* instId[] */
            BOARD_MAKE_VIP_INST_ID,
            /* decDrvId[] */
            BOARD_VID_SENSOR_DRV_ID,
            /* standard */
            FVID2_STD_720P_60,
            /* videoIfMode */
            FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
            /* videoIfWidth */
            FVID2_VIFW_8BIT,
            /* bufCaptMode */
            VPS_CAPT_BCM_LAST_FRM_REPEAT,
            /* numCh */
            1u,
            /* numStream */
            2u,
            /* inWidth */
            1280u,
            /* inHeight */
            720u,
            /* inDataFmt */
            FVID2_DF_YUV422P,
            /* inScanFormat */
            FVID2_SF_PROGRESSIVE,
            /* inBPP */
            FVID2_BPP_BITS16,
            /* cropStartX */
            0u,
            /* cropStartY */
            0u,
            /* cropWidth */
            1280u,
            /* cropHeight */
            720u,
            /* nonLinear */
            SC_NONLINEAR_DISABLE,
            /* stripSize */
            0u,
            /* enableScAdvCfg */
            SC_ADVCFG_DISABLE,
            /* advCfg */
            NULL,
            /* cscCoeff */
            NULL,
            /* outStrmParams[VPS_CAPT_STREAM_ID_MAX] */
            {
                /* Stream #0 */
                {
                    /* outWidth */
                    1280u,
                    /* outHeight */
                    720u,
                    /* outDataFmt */
                    FVID2_DF_RGB24_888,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_DISABLE_ALL,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                },
                /* Stream #1 */
                {
                    /* outWidth */
                    1280u,
                    /* outHeight */
                    720u,
                    /* outDataFmt */
                    FVID2_DF_YUV422I_YUYV,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_DISABLE_ALL,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                }
            }
        }
    },
    {
        /* testEnable */
        TEST_ENABLE,
        /* bufCaptModeTestEnable */
        BUF_CAPT_MODE_TEST_DISABLE,
        /* printEnable */
        PRINT_ENABLE,
        /* Software Requirement Id  */
        ":PDK-976:",
        /* testCaseId */
        10016u,
        /* testType */
        ST_TT_SANITY,
        /* runCount */
        ST_CAPT_RUN_COUNT,
        /* testDescStr */
#ifdef SOC_TDA2EX
        "OV1063x->VIP1_S1_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), Dual out - RGB888, RGB888",
#else
        "OV1063x->VIP1_S0_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), Dual out - RGB888, RGB888",
#endif
        /* testCaseType */
        ST_CAPT_TCT_MAIN,
        /* numHandles */
        1u,
        NULL,
        NULL,
        /* platformId */
        BSP_PLATFORM_ID_EVM,
        /* socId */
        BOARD_SOC_ID,
        /* boardId */
        (BSP_BOARD_GP_AM572X | BSP_BOARD_IDK_AM57XX | BSP_BOARD_VISION | BSP_BOARD_BASE_TDA3XX),
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_8BIT,
        /* startstpCnt */
        1,
        /* maxSizeRegs[VPS_VIP_MAX] */
        {
            /* VPS_VIP1 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX) || defined(SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_AM574x)
            /* VPS_VIP2 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX)
            /* VPS_VIP3 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            }
#endif
#endif
        },

        /* testInstPrms[VPS_CAPT_INST_MAX] */
        {
            /* instId[] */
            BOARD_MAKE_VIP_INST_ID,
            /* decDrvId[] */
            BOARD_VID_SENSOR_DRV_ID,
            /* standard */
            FVID2_STD_720P_60,
            /* videoIfMode */
            FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
            /* videoIfWidth */
            FVID2_VIFW_8BIT,
            /* bufCaptMode */
            VPS_CAPT_BCM_LAST_FRM_REPEAT,
            /* numCh */
            1u,
            /* numStream */
            2u,
            /* inWidth */
            1280u,
            /* inHeight */
            720u,
            /* inDataFmt */
            FVID2_DF_YUV422P,
            /* inScanFormat */
            FVID2_SF_PROGRESSIVE,
            /* inBPP */
            FVID2_BPP_BITS16,
            /* cropStartX */
            0u,
            /* cropStartY */
            0u,
            /* cropWidth */
            1280u,
            /* cropHeight */
            720u,
            /* nonLinear */
            SC_NONLINEAR_DISABLE,
            /* stripSize */
            0u,
            /* enableScAdvCfg */
            SC_ADVCFG_DISABLE,
            /* advCfg */
            NULL,
            /* cscCoeff */
            NULL,
            /* outStrmParams[VPS_CAPT_STREAM_ID_MAX] */
            {
                /* Stream #0 */
                {
                    /* outWidth */
                    1280u,
                    /* outHeight */
                    720u,
                    /* outDataFmt */
                    FVID2_DF_RGB24_888,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_DISABLE_ALL,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                },
                /* Stream #1 */
                {
                    /* outWidth */
                    1280u,
                    /* outHeight */
                    720u,
                    /* outDataFmt */
                    FVID2_DF_RGB24_888,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_DISABLE_ALL,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                }
            }
        }
    },
    {
        /* testEnable */
        TEST_ENABLE,
        /* bufCaptModeTestEnable */
        BUF_CAPT_MODE_TEST_DISABLE,
        /* printEnable */
        PRINT_ENABLE,
        /* Software Requirement Id  */
        ":PDK-977:",
        /* testCaseId */
        10017u,
        /* testType */
        ST_TT_SANITY,
        /* runCount */
        ST_CAPT_RUN_COUNT,
        /* testDescStr */
#ifdef SOC_TDA2EX
        "OV1063x->VIP1_S1_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), Dual out - YUYV422I 800x480 Scaled out, YUYV422I",
#else
        "OV1063x->VIP1_S0_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), Dual out - YUYV422I 800x480 Scaled out, YUYV422I",
#endif
        /* testCaseType */
        ST_CAPT_TCT_MAIN,
        /* numHandles */
        1u,
        NULL,
        NULL,
        /* platformId */
        BSP_PLATFORM_ID_EVM,
        /* socId */
        BOARD_SOC_ID,
        /* boardId */
        (BSP_BOARD_GP_AM572X | BSP_BOARD_IDK_AM57XX | BSP_BOARD_VISION | BSP_BOARD_BASE_TDA3XX),
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_8BIT,
        /* startstpCnt */
        1,
        /* maxSizeRegs[VPS_VIP_MAX] */
        {
            /* VPS_VIP1 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX) || defined(SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_AM574x)
            /* VPS_VIP2 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX)
            /* VPS_VIP3 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            }
#endif
#endif
        },

        /* testInstPrms[VPS_CAPT_INST_MAX] */
        {
            /* instId[] */
            BOARD_MAKE_VIP_INST_ID,
            /* decDrvId[] */
            BOARD_VID_SENSOR_DRV_ID,
            /* standard */
            FVID2_STD_720P_60,
            /* videoIfMode */
            FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
            /* videoIfWidth */
            FVID2_VIFW_8BIT,
            /* bufCaptMode */
            VPS_CAPT_BCM_LAST_FRM_REPEAT,
            /* numCh */
            1u,
            /* numStream */
            2u,
            /* inWidth */
            1280u,
            /* inHeight */
            720u,
            /* inDataFmt */
            FVID2_DF_YUV422P,
            /* inScanFormat */
            FVID2_SF_PROGRESSIVE,
            /* inBPP */
            FVID2_BPP_BITS16,
            /* cropStartX */
            0u,
            /* cropStartY */
            0u,
            /* cropWidth */
            1280u,
            /* cropHeight */
            720u,
            /* nonLinear */
            SC_NONLINEAR_DISABLE,
            /* stripSize */
            0u,
            /* enableScAdvCfg */
            SC_ADVCFG_DISABLE,
            /* advCfg */
            NULL,
            /* cscCoeff */
            NULL,
            /* outStrmParams[VPS_CAPT_STREAM_ID_MAX] */
            {
                /* Stream #0 */
                {
                    /* outWidth */
                    800u,
                    /* outHeight */
                    480u,
                    /* outDataFmt */
                    FVID2_DF_YUV422I_YUYV,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_ENABLE_0,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                },
                /* Stream #1 */
                {
                    /* outWidth */
                    1280u,
                    /* outHeight */
                    720u,
                    /* outDataFmt */
                    FVID2_DF_YUV422I_YUYV,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_DISABLE_ALL,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                }
            }
        }
    },
    {
        /* testEnable */
        TEST_ENABLE,
        /* bufCaptModeTestEnable */
        BUF_CAPT_MODE_TEST_DISABLE,
        /* printEnable */
        PRINT_ENABLE,
        /* Software Requirement Id  */
        ":PDK-978:",
        /* testCaseId */
        10018u,
        /* testType */
        ST_TT_SANITY,
        /* runCount */
        ST_CAPT_RUN_COUNT,
        /* testDescStr */
#ifdef SOC_TDA2EX
        "OV1063x->VIP1_S1_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), Dual out - YUYV422I 640x360 Scaled out, YUV420SP",
#else
        "OV1063x->VIP1_S0_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), Dual out - YUYV422I 640x360 Scaled out, YUV420SP",
#endif
        /* testCaseType */
        ST_CAPT_TCT_MAIN,
        /* numHandles */
        1u,
        NULL,
        NULL,
        /* platformId */
        BSP_PLATFORM_ID_EVM,
        /* socId */
        BOARD_SOC_ID,
        /* boardId */
        (BSP_BOARD_GP_AM572X | BSP_BOARD_IDK_AM57XX | BSP_BOARD_VISION | BSP_BOARD_BASE_TDA3XX),
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_8BIT,
        /* startstpCnt */
        1,
        /* maxSizeRegs[VPS_VIP_MAX] */
        {
            /* VPS_VIP1 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX) || defined(SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_AM574x)
            /* VPS_VIP2 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX)
            /* VPS_VIP3 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            }
#endif
#endif
        },

        /* testInstPrms[VPS_CAPT_INST_MAX] */
        {
            /* instId[] */
            BOARD_MAKE_VIP_INST_ID,
            /* decDrvId[] */
            BOARD_VID_SENSOR_DRV_ID,
            /* standard */
            FVID2_STD_720P_60,
            /* videoIfMode */
            FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
            /* videoIfWidth */
            FVID2_VIFW_8BIT,
            /* bufCaptMode */
            VPS_CAPT_BCM_LAST_FRM_REPEAT,
            /* numCh */
            1u,
            /* numStream */
            2u,
            /* inWidth */
            1280u,
            /* inHeight */
            720u,
            /* inDataFmt */
            FVID2_DF_YUV422P,
            /* inScanFormat */
            FVID2_SF_PROGRESSIVE,
            /* inBPP */
            FVID2_BPP_BITS16,
            /* cropStartX */
            0u,
            /* cropStartY */
            0u,
            /* cropWidth */
            1280u,
            /* cropHeight */
            720u,
            /* nonLinear */
            SC_NONLINEAR_DISABLE,
            /* stripSize */
            0u,
            /* enableScAdvCfg */
            SC_ADVCFG_DISABLE,
            /* advCfg */
            NULL,
            /* cscCoeff */
            NULL,
            /* outStrmParams[VPS_CAPT_STREAM_ID_MAX] */
            {
                /* Stream #0 */
                {
                    /* outWidth */
                    640u,
                    /* outHeight */
                    360u,
                    /* outDataFmt */
                    FVID2_DF_YUV422I_YUYV,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_ENABLE_0,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                },
                /* Stream #1 */
                {
                    /* outWidth */
                    1280u,
                    /* outHeight */
                    720u,
                    /* outDataFmt */
                    FVID2_DF_YUV420SP_UV,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_DISABLE_ALL,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                }
            }
        }
    },
    {
        /* testEnable */
        TEST_ENABLE,
        /* bufCaptModeTestEnable */
        BUF_CAPT_MODE_TEST_DISABLE,
        /* printEnable */
        PRINT_ENABLE,
        /* Software Requirement Id  */
        ":PDK-980:",
        /* testCaseId */
        10020u,
        /* testType */
        ST_TT_SANITY,
        /* runCount */
        ST_CAPT_RUN_COUNT,
        /* testDescStr */
#ifdef SOC_TDA2EX
        "OV1063x->VIP1_S1_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), Dual out - YUYV422I 720x240 Scaled out, RGB888",
#else
        "OV1063x->VIP1_S0_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), Dual out - YUYV422I 720x240 Scaled out, RGB888",
#endif
        /* testCaseType */
        ST_CAPT_TCT_MAIN,
        /* numHandles */
        1u,
        NULL,
        NULL,
        /* platformId */
        BSP_PLATFORM_ID_EVM,
        /* socId */
        BOARD_SOC_ID,
        /* boardId */
        (BSP_BOARD_GP_AM572X | BSP_BOARD_IDK_AM57XX | BSP_BOARD_VISION | BSP_BOARD_BASE_TDA3XX),
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_8BIT,
        /* startstpCnt */
        1,
        /* maxSizeRegs[VPS_VIP_MAX] */
        {
            /* VPS_VIP1 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX) || defined(SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_AM574x)
            /* VPS_VIP2 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX)
            /* VPS_VIP3 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            }
#endif
#endif
        },

        /* testInstPrms[VPS_CAPT_INST_MAX] */
        {
            /* instId[] */
            BOARD_MAKE_VIP_INST_ID,
            /* decDrvId[] */
            BOARD_VID_SENSOR_DRV_ID,
            /* standard */
            FVID2_STD_720P_60,
            /* videoIfMode */
            FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
            /* videoIfWidth */
            FVID2_VIFW_8BIT,
            /* bufCaptMode */
            VPS_CAPT_BCM_LAST_FRM_REPEAT,
            /* numCh */
            1u,
            /* numStream */
            2u,
            /* inWidth */
            1280u,
            /* inHeight */
            720u,
            /* inDataFmt */
            FVID2_DF_YUV422P,
            /* inScanFormat */
            FVID2_SF_PROGRESSIVE,
            /* inBPP */
            FVID2_BPP_BITS16,
            /* cropStartX */
            0u,
            /* cropStartY */
            0u,
            /* cropWidth */
            1280u,
            /* cropHeight */
            720u,
            /* nonLinear */
            SC_NONLINEAR_DISABLE,
            /* stripSize */
            0u,
            /* enableScAdvCfg */
            SC_ADVCFG_DISABLE,
            /* advCfg */
            NULL,
            /* cscCoeff */
            NULL,
            /* outStrmParams[VPS_CAPT_STREAM_ID_MAX] */
            {
                /* Stream #0 */
                {
                    /* outWidth */
                    720u,
                    /* outHeight */
                    240u,
                    /* outDataFmt */
                    FVID2_DF_YUV422I_YUYV,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_ENABLE_0,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                },
                /* Stream #1 */
                {
                    /* outWidth */
                    1280u,
                    /* outHeight */
                    720u,
                    /* outDataFmt */
                    FVID2_DF_RGB24_888,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_DISABLE_ALL,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                }
            }
        }
    },
    {
        /* testEnable */
        TEST_ENABLE,
        /* bufCaptModeTestEnable */
        BUF_CAPT_MODE_TEST_DISABLE,
        /* printEnable */
        PRINT_ENABLE,
        /* Software Requirement Id  */
        ":PDK-981:",
        /* testCaseId */
        10021u,
        /* testType */
        ST_TT_SANITY,
        /* runCount */
        ST_CAPT_RUN_COUNT,
        /* testDescStr */
#ifdef SOC_TDA2EX
        "OV1063x->VIP1_S1_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), Dual out - YUV420SP 800x480 Scaled out, YUV422I",
#else
        "OV1063x->VIP1_S0_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), Dual out - YUV420SP 800x480 Scaled out, YUV422I",
#endif
        /* testCaseType */
        ST_CAPT_TCT_MAIN,
        /* numHandles */
        1u,
        NULL,
        NULL,
        /* platformId */
        BSP_PLATFORM_ID_EVM,
        /* socId */
        BOARD_SOC_ID,
        /* boardId */
        (BSP_BOARD_GP_AM572X | BSP_BOARD_IDK_AM57XX | BSP_BOARD_VISION | BSP_BOARD_BASE_TDA3XX),
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_8BIT,
        /* startstpCnt */
        1,
        /* maxSizeRegs[VPS_VIP_MAX] */
        {
            /* VPS_VIP1 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX) || defined(SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_AM574x)
            /* VPS_VIP2 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX)
            /* VPS_VIP3 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            }
#endif
#endif
        },

        /* testInstPrms[VPS_CAPT_INST_MAX] */
        {
            /* instId[] */
            BOARD_MAKE_VIP_INST_ID,
            /* decDrvId[] */
            BOARD_VID_SENSOR_DRV_ID,
            /* standard */
            FVID2_STD_720P_60,
            /* videoIfMode */
            FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
            /* videoIfWidth */
            FVID2_VIFW_8BIT,
            /* bufCaptMode */
            VPS_CAPT_BCM_LAST_FRM_REPEAT,
            /* numCh */
            1u,
            /* numStream */
            2u,
            /* inWidth */
            1280u,
            /* inHeight */
            720u,
            /* inDataFmt */
            FVID2_DF_YUV422P,
            /* inScanFormat */
            FVID2_SF_PROGRESSIVE,
            /* inBPP */
            FVID2_BPP_BITS16,
            /* cropStartX */
            0u,
            /* cropStartY */
            0u,
            /* cropWidth */
            1280u,
            /* cropHeight */
            720u,
            /* nonLinear */
            SC_NONLINEAR_DISABLE,
            /* stripSize */
            0u,
            /* enableScAdvCfg */
            SC_ADVCFG_DISABLE,
            /* advCfg */
            NULL,
            /* cscCoeff */
            NULL,
            /* outStrmParams[VPS_CAPT_STREAM_ID_MAX] */
            {
                /* Stream #0 */
                {
                    /* outWidth */
                    800u,
                    /* outHeight */
                    480u,
                    /* outDataFmt */
                    FVID2_DF_YUV420SP_UV,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_ENABLE_0,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                },
                /* Stream #1 */
                {
                    /* outWidth */
                    1280u,
                    /* outHeight */
                    720u,
                    /* outDataFmt */
                    FVID2_DF_YUV422I_YUYV,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_DISABLE_ALL,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                }
            }
        }
    },
    {
        /* testEnable */
        TEST_ENABLE,
        /* bufCaptModeTestEnable */
        BUF_CAPT_MODE_TEST_DISABLE,
        /* printEnable */
        PRINT_ENABLE,
        /* Software Requirement Id  */
        ":PDK-982:",
        /* testCaseId */
        10022u,
        /* testType */
        ST_TT_SANITY,
        /* runCount */
        ST_CAPT_RUN_COUNT,
        /* testDescStr */
#ifdef SOC_TDA2EX
        "OV1063x->VIP1_S1_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), Dual out - YUV420SP 640x360 Scaled out, YUV420SP",
#else
        "OV1063x->VIP1_S0_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), Dual out - YUV420SP 640x360 Scaled out, YUV420SP",
#endif
        /* testCaseType */
        ST_CAPT_TCT_MAIN,
        /* numHandles */
        1u,
        NULL,
        NULL,
        /* platformId */
        BSP_PLATFORM_ID_EVM,
        /* socId */
        BOARD_SOC_ID,
        /* boardId */
        (BSP_BOARD_GP_AM572X | BSP_BOARD_IDK_AM57XX | BSP_BOARD_VISION | BSP_BOARD_BASE_TDA3XX),
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_8BIT,
        /* startstpCnt */
        1,
        /* maxSizeRegs[VPS_VIP_MAX] */
        {
            /* VPS_VIP1 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX) || defined(SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_AM574x)
            /* VPS_VIP2 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX)
            /* VPS_VIP3 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            }
#endif
#endif
        },

        /* testInstPrms[VPS_CAPT_INST_MAX] */
        {
            /* instId[] */
            BOARD_MAKE_VIP_INST_ID,
            /* decDrvId[] */
            BOARD_VID_SENSOR_DRV_ID,
            /* standard */
            FVID2_STD_720P_60,
            /* videoIfMode */
            FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
            /* videoIfWidth */
            FVID2_VIFW_8BIT,
            /* bufCaptMode */
            VPS_CAPT_BCM_LAST_FRM_REPEAT,
            /* numCh */
            1u,
            /* numStream */
            2u,
            /* inWidth */
            1280u,
            /* inHeight */
            720u,
            /* inDataFmt */
            FVID2_DF_YUV422P,
            /* inScanFormat */
            FVID2_SF_PROGRESSIVE,
            /* inBPP */
            FVID2_BPP_BITS16,
            /* cropStartX */
            0u,
            /* cropStartY */
            0u,
            /* cropWidth */
            1280u,
            /* cropHeight */
            720u,
            /* nonLinear */
            SC_NONLINEAR_DISABLE,
            /* stripSize */
            0u,
            /* enableScAdvCfg */
            SC_ADVCFG_DISABLE,
            /* advCfg */
            NULL,
            /* cscCoeff */
            NULL,
            /* outStrmParams[VPS_CAPT_STREAM_ID_MAX] */
            {
                /* Stream #0 */
                {
                    /* outWidth */
                    640u,
                    /* outHeight */
                    360u,
                    /* outDataFmt */
                    FVID2_DF_YUV420SP_UV,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_ENABLE_0,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                },
                /* Stream #1 */
                {
                    /* outWidth */
                    1280u,
                    /* outHeight */
                    720u,
                    /* outDataFmt */
                    FVID2_DF_YUV420SP_UV,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_DISABLE_ALL,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                }
            }
        }
    },
    {
        /* testEnable */
        TEST_ENABLE,
        /* bufCaptModeTestEnable */
        BUF_CAPT_MODE_TEST_DISABLE,
        /* printEnable */
        PRINT_ENABLE,
        /* Software Requirement Id  */
        ":PDK-983:",
        /* testCaseId */
        10023u,
        /* testType */
        ST_TT_SANITY,
        /* runCount */
        ST_CAPT_RUN_COUNT,
        /* testDescStr */
#ifdef SOC_TDA2EX
        "OV1063x->VIP1_S1_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), Dual out - YUV420SP 320x180 Scaled out, RGB888",
#else
        "OV1063x->VIP1_S0_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), Dual out - YUV420SP 320x180 Scaled out, RGB888",
#endif
        /* testCaseType */
        ST_CAPT_TCT_MAIN,
        /* numHandles */
        1u,
        NULL,
        NULL,
        /* platformId */
        BSP_PLATFORM_ID_EVM,
        /* socId */
        BOARD_SOC_ID,
        /* boardId */
        (BSP_BOARD_GP_AM572X | BSP_BOARD_IDK_AM57XX | BSP_BOARD_VISION | BSP_BOARD_BASE_TDA3XX),
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_8BIT,
        /* startstpCnt */
        1,
        /* maxSizeRegs[VPS_VIP_MAX] */
        {
            /* VPS_VIP1 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX) || defined(SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_AM574x)
            /* VPS_VIP2 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX)
            /* VPS_VIP3 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            }
#endif
#endif
        },

        /* testInstPrms[VPS_CAPT_INST_MAX] */
        {
            /* instId[] */
            BOARD_MAKE_VIP_INST_ID,
            /* decDrvId[] */
            BOARD_VID_SENSOR_DRV_ID,
            /* standard */
            FVID2_STD_720P_60,
            /* videoIfMode */
            FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
            /* videoIfWidth */
            FVID2_VIFW_8BIT,
            /* bufCaptMode */
            VPS_CAPT_BCM_LAST_FRM_REPEAT,
            /* numCh */
            1u,
            /* numStream */
            2u,
            /* inWidth */
            1280u,
            /* inHeight */
            720u,
            /* inDataFmt */
            FVID2_DF_YUV422P,
            /* inScanFormat */
            FVID2_SF_PROGRESSIVE,
            /* inBPP */
            FVID2_BPP_BITS16,
            /* cropStartX */
            0u,
            /* cropStartY */
            0u,
            /* cropWidth */
            1280u,
            /* cropHeight */
            720u,
            /* nonLinear */
            SC_NONLINEAR_DISABLE,
            /* stripSize */
            0u,
            /* enableScAdvCfg */
            SC_ADVCFG_DISABLE,
            /* advCfg */
            NULL,
            /* cscCoeff */
            NULL,
            /* outStrmParams[VPS_CAPT_STREAM_ID_MAX] */
            {
                /* Stream #0 */
                {
                    /* outWidth */
                    320u,
                    /* outHeight */
                    180u,
                    /* outDataFmt */
                    FVID2_DF_YUV420SP_UV,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_ENABLE_0,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                },
                /* Stream #1 */
                {
                    /* outWidth */
                    1280u,
                    /* outHeight */
                    720u,
                    /* outDataFmt */
                    FVID2_DF_RGB24_888,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_DISABLE_ALL,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                }
            }
        }
    },
    {
        /* testEnable */
        TEST_ENABLE,
        /* bufCaptModeTestEnable */
        BUF_CAPT_MODE_TEST_DISABLE,
        /* printEnable */
        PRINT_ENABLE,
        /* Software Requirement Id  */
        ":PDK-984:",
        /* testCaseId */
        10024u,
        /* testType */
        ST_TT_SANITY,
        /* runCount */
        ST_CAPT_RUN_COUNT,
        /* testDescStr */
#ifdef SOC_TDA2EX
        "OV1063x->VIP1_S1_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), Dual out - YUV422SP 800x480 Scaled out, YUV422I",
#else
        "OV1063x->VIP1_S0_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), Dual out - YUV422SP 800x480 Scaled out, YUV422I",
#endif
        /* testCaseType */
        ST_CAPT_TCT_MAIN,
        /* numHandles */
        1u,
        NULL,
        NULL,
        /* platformId */
        BSP_PLATFORM_ID_EVM,
        /* socId */
        BOARD_SOC_ID,
        /* boardId */
        (BSP_BOARD_GP_AM572X | BSP_BOARD_IDK_AM57XX | BSP_BOARD_VISION | BSP_BOARD_BASE_TDA3XX),
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_8BIT,
        /* startstpCnt */
        1,
        /* maxSizeRegs[VPS_VIP_MAX] */
        {
            /* VPS_VIP1 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX) || defined(SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_AM574x)
            /* VPS_VIP2 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX)
            /* VPS_VIP3 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            }
#endif
#endif
        },

        /* testInstPrms[VPS_CAPT_INST_MAX] */
        {
            /* instId[] */
            BOARD_MAKE_VIP_INST_ID,
            /* decDrvId[] */
            BOARD_VID_SENSOR_DRV_ID,
            /* standard */
            FVID2_STD_720P_60,
            /* videoIfMode */
            FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
            /* videoIfWidth */
            FVID2_VIFW_8BIT,
            /* bufCaptMode */
            VPS_CAPT_BCM_LAST_FRM_REPEAT,
            /* numCh */
            1u,
            /* numStream */
            2u,
            /* inWidth */
            1280u,
            /* inHeight */
            720u,
            /* inDataFmt */
            FVID2_DF_YUV422P,
            /* inScanFormat */
            FVID2_SF_PROGRESSIVE,
            /* inBPP */
            FVID2_BPP_BITS16,
            /* cropStartX */
            0u,
            /* cropStartY */
            0u,
            /* cropWidth */
            1280u,
            /* cropHeight */
            720u,
            /* nonLinear */
            SC_NONLINEAR_DISABLE,
            /* stripSize */
            0u,
            /* enableScAdvCfg */
            SC_ADVCFG_DISABLE,
            /* advCfg */
            NULL,
            /* cscCoeff */
            NULL,
            /* outStrmParams[VPS_CAPT_STREAM_ID_MAX] */
            {
                /* Stream #0 */
                {
                    /* outWidth */
                    800u,
                    /* outHeight */
                    480u,
                    /* outDataFmt */
                    FVID2_DF_YUV422SP_UV,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_ENABLE_0,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                },
                /* Stream #1 */
                {
                    /* outWidth */
                    1280u,
                    /* outHeight */
                    720u,
                    /* outDataFmt */
                    FVID2_DF_YUV422I_YUYV,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_DISABLE_ALL,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                }
            }
        }
    },
    {
        /* testEnable */
        TEST_ENABLE,
        /* bufCaptModeTestEnable */
        BUF_CAPT_MODE_TEST_DISABLE,
        /* printEnable */
        PRINT_ENABLE,
        /* Software Requirement Id  */
        ":PDK-986:",
        /* testCaseId */
        10025u,
        /* testType */
        ST_TT_SANITY,
        /* runCount */
        ST_CAPT_RUN_COUNT,
        /* testDescStr */
#ifdef SOC_TDA2EX
        "OV1063x->VIP1_S1_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), Dual out - YUYV422I, YUV420SP 800x480 Scaled out",
#else
        "OV1063x->VIP1_S0_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), Dual out - YUYV422I, YUV420SP 800x480 Scaled out",
#endif
        /* testCaseType */
        ST_CAPT_TCT_MAIN,
        /* numHandles */
        1u,
        NULL,
        NULL,
        /* platformId */
        BSP_PLATFORM_ID_EVM,
        /* socId */
        BOARD_SOC_ID,
        /* boardId */
        (BSP_BOARD_GP_AM572X | BSP_BOARD_IDK_AM57XX | BSP_BOARD_VISION | BSP_BOARD_BASE_TDA3XX),
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_8BIT,
        /* startstpCnt */
        1,
        /* maxSizeRegs[VPS_VIP_MAX] */
        {
            /* VPS_VIP1 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX) || defined(SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_AM574x)
            /* VPS_VIP2 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX)
            /* VPS_VIP3 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            }
#endif
#endif
        },

        /* testInstPrms[VPS_CAPT_INST_MAX] */
        {
            /* instId[] */
            BOARD_MAKE_VIP_INST_ID,
            /* decDrvId[] */
            BOARD_VID_SENSOR_DRV_ID,
            /* standard */
            FVID2_STD_720P_60,
            /* videoIfMode */
            FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
            /* videoIfWidth */
            FVID2_VIFW_8BIT,
            /* bufCaptMode */
            VPS_CAPT_BCM_LAST_FRM_REPEAT,
            /* numCh */
            1u,
            /* numStream */
            2u,
            /* inWidth */
            1280u,
            /* inHeight */
            720u,
            /* inDataFmt */
            FVID2_DF_YUV422P,
            /* inScanFormat */
            FVID2_SF_PROGRESSIVE,
            /* inBPP */
            FVID2_BPP_BITS16,
            /* cropStartX */
            0u,
            /* cropStartY */
            0u,
            /* cropWidth */
            1280u,
            /* cropHeight */
            720u,
            /* nonLinear */
            SC_NONLINEAR_DISABLE,
            /* stripSize */
            0u,
            /* enableScAdvCfg */
            SC_ADVCFG_DISABLE,
            /* advCfg */
            NULL,
            /* cscCoeff */
            NULL,
            /* outStrmParams[VPS_CAPT_STREAM_ID_MAX] */
            {
                /* Stream #0 */
                {
                    /* outWidth */
                    1280u,
                    /* outHeight */
                    720u,
                    /* outDataFmt */
                    FVID2_DF_YUV422I_YUYV,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_DISABLE_ALL,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                },
                /* Stream #1 */
                {
                    /* outWidth */
                    800u,
                    /* outHeight */
                    480u,
                    /* outDataFmt */
                    FVID2_DF_YUV420SP_UV,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_ENABLE_1,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                }
            }
        }
    },
    {
        /* testEnable */
        TEST_ENABLE,
        /* bufCaptModeTestEnable */
        BUF_CAPT_MODE_TEST_DISABLE,
        /* printEnable */
        PRINT_ENABLE,
        /* Software Requirement Id  */
        ":PDK-987:",
        /* testCaseId */
        10026u,
        /* testType */
        ST_TT_SANITY,
        /* runCount */
        ST_CAPT_RUN_COUNT,
        /* testDescStr */
#ifdef SOC_TDA2EX
        "OV1063x->VIP1_S1_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), Dual out -  YUV420SP, YUV420SP 640x360 Scaled out",
#else
        "OV1063x->VIP1_S0_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), Dual out -  YUV420SP, YUV420SP 640x360 Scaled out",
#endif
        /* testCaseType */
        ST_CAPT_TCT_MAIN,
        /* numHandles */
        1u,
        NULL,
        NULL,
        /* platformId */
        BSP_PLATFORM_ID_EVM,
        /* socId */
        BOARD_SOC_ID,
        /* boardId */
        (BSP_BOARD_GP_AM572X | BSP_BOARD_IDK_AM57XX | BSP_BOARD_VISION | BSP_BOARD_BASE_TDA3XX),
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_8BIT,
        /* startstpCnt */
        1,
        /* maxSizeRegs[VPS_VIP_MAX] */
        {
            /* VPS_VIP1 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX) || defined(SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_AM574x)
            /* VPS_VIP2 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX)
            /* VPS_VIP3 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            }
#endif
#endif
        },

        /* testInstPrms[VPS_CAPT_INST_MAX] */
        {
            /* instId[] */
            BOARD_MAKE_VIP_INST_ID,
            /* decDrvId[] */
            BOARD_VID_SENSOR_DRV_ID,
            /* standard */
            FVID2_STD_720P_60,
            /* videoIfMode */
            FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
            /* videoIfWidth */
            FVID2_VIFW_8BIT,
            /* bufCaptMode */
            VPS_CAPT_BCM_LAST_FRM_REPEAT,
            /* numCh */
            1u,
            /* numStream */
            2u,
            /* inWidth */
            1280u,
            /* inHeight */
            720u,
            /* inDataFmt */
            FVID2_DF_YUV422P,
            /* inScanFormat */
            FVID2_SF_PROGRESSIVE,
            /* inBPP */
            FVID2_BPP_BITS16,
            /* cropStartX */
            0u,
            /* cropStartY */
            0u,
            /* cropWidth */
            1280u,
            /* cropHeight */
            720u,
            /* nonLinear */
            SC_NONLINEAR_DISABLE,
            /* stripSize */
            0u,
            /* enableScAdvCfg */
            SC_ADVCFG_DISABLE,
            /* advCfg */
            NULL,
            /* cscCoeff */
            NULL,
            /* outStrmParams[VPS_CAPT_STREAM_ID_MAX] */
            {
                /* Stream #0 */
                {
                    /* outWidth */
                    1280u,
                    /* outHeight */
                    720u,
                    /* outDataFmt */
                    FVID2_DF_YUV420SP_UV,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_DISABLE_ALL,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                },
                /* Stream #1 */
                {
                    /* outWidth */
                    640u,
                    /* outHeight */
                    360u,
                    /* outDataFmt */
                    FVID2_DF_YUV420SP_UV,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_ENABLE_1,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                }
            }
        }
    },
    {
        /* testEnable */
        TEST_ENABLE,
        /* bufCaptModeTestEnable */
        BUF_CAPT_MODE_TEST_DISABLE,
        /* printEnable */
        PRINT_ENABLE,
        /* Software Requirement Id  */
        ":PDK-988:",
        /* testCaseId */
        10027u,
        /* testType */
        ST_TT_SANITY,
        /* runCount */
        ST_CAPT_RUN_COUNT,
        /* testDescStr */
#ifdef SOC_TDA2EX
        "OV1063x->VIP1_S1_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), Dual out -  YUV422SP, YUV422I 320x180 Scaled out",
#else
        "OV1063x->VIP1_S0_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), Dual out -  YUV422SP, YUV422I 320x180 Scaled out",
#endif
        /* testCaseType */
        ST_CAPT_TCT_MAIN,
        /* numHandles */
        1u,
        NULL,
        NULL,
        /* platformId */
        BSP_PLATFORM_ID_EVM,
        /* socId */
        BOARD_SOC_ID,
        /* boardId */
        (BSP_BOARD_GP_AM572X | BSP_BOARD_IDK_AM57XX | BSP_BOARD_VISION | BSP_BOARD_BASE_TDA3XX),
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_8BIT,
        /* startstpCnt */
        1,
        /* maxSizeRegs[VPS_VIP_MAX] */
        {
            /* VPS_VIP1 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX) || defined(SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_AM574x)
            /* VPS_VIP2 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX)
            /* VPS_VIP3 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            }
#endif
#endif
        },

        /* testInstPrms[VPS_CAPT_INST_MAX] */
        {
            /* instId[] */
            BOARD_MAKE_VIP_INST_ID,
            /* decDrvId[] */
            BOARD_VID_SENSOR_DRV_ID,
            /* standard */
            FVID2_STD_720P_60,
            /* videoIfMode */
            FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
            /* videoIfWidth */
            FVID2_VIFW_8BIT,
            /* bufCaptMode */
            VPS_CAPT_BCM_LAST_FRM_REPEAT,
            /* numCh */
            1u,
            /* numStream */
            2u,
            /* inWidth */
            1280u,
            /* inHeight */
            720u,
            /* inDataFmt */
            FVID2_DF_YUV422P,
            /* inScanFormat */
            FVID2_SF_PROGRESSIVE,
            /* inBPP */
            FVID2_BPP_BITS16,
            /* cropStartX */
            0u,
            /* cropStartY */
            0u,
            /* cropWidth */
            1280u,
            /* cropHeight */
            720u,
            /* nonLinear */
            SC_NONLINEAR_DISABLE,
            /* stripSize */
            0u,
            /* enableScAdvCfg */
            SC_ADVCFG_DISABLE,
            /* advCfg */
            NULL,
            /* cscCoeff */
            NULL,
            /* outStrmParams[VPS_CAPT_STREAM_ID_MAX] */
            {
                /* Stream #0 */
                {
                    /* outWidth */
                    1280u,
                    /* outHeight */
                    720u,
                    /* outDataFmt */
                    FVID2_DF_YUV422SP_UV,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_DISABLE_ALL,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                },
                /* Stream #1 */
                {
                    /* outWidth */
                    320u,
                    /* outHeight */
                    180u,
                    /* outDataFmt */
                    FVID2_DF_YUV422I_YUYV,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_ENABLE_1,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                }
            }
        }
    },
    {
        /* testEnable */
        TEST_ENABLE,
        /* bufCaptModeTestEnable */
        BUF_CAPT_MODE_TEST_DISABLE,
        /* printEnable */
        PRINT_ENABLE,
        /* Software Requirement Id  */
        ":PDK-989:",
        /* testCaseId */
        10028u,
        /* testType */
        ST_TT_SANITY,
        /* runCount */
        ST_CAPT_RUN_COUNT,
        /* testDescStr */
#ifdef SOC_TDA2EX
        "OV1063x->VIP1_S1_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), Dual out -  RGB888, YUV422I 720x240 Scaled out",
#else
        "OV1063x->VIP1_S0_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), Dual out -  RGB888, YUV422I 720x240 Scaled out",
#endif
        /* testCaseType */
        ST_CAPT_TCT_MAIN,
        /* numHandles */
        1u,
        NULL,
        NULL,
        /* platformId */
        BSP_PLATFORM_ID_EVM,
        /* socId */
        BOARD_SOC_ID,
        /* boardId */
        (BSP_BOARD_GP_AM572X | BSP_BOARD_IDK_AM57XX | BSP_BOARD_VISION | BSP_BOARD_BASE_TDA3XX),
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_8BIT,
        /* startstpCnt */
        1,
        /* maxSizeRegs[VPS_VIP_MAX] */
        {
            /* VPS_VIP1 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX) || defined(SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_AM574x)
            /* VPS_VIP2 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX)
            /* VPS_VIP3 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            }
#endif
#endif
        },

        /* testInstPrms[VPS_CAPT_INST_MAX] */
        {
            /* instId[] */
            BOARD_MAKE_VIP_INST_ID,
            /* decDrvId[] */
            BOARD_VID_SENSOR_DRV_ID,
            /* standard */
            FVID2_STD_720P_60,
            /* videoIfMode */
            FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
            /* videoIfWidth */
            FVID2_VIFW_8BIT,
            /* bufCaptMode */
            VPS_CAPT_BCM_LAST_FRM_REPEAT,
            /* numCh */
            1u,
            /* numStream */
            2u,
            /* inWidth */
            1280u,
            /* inHeight */
            720u,
            /* inDataFmt */
            FVID2_DF_YUV422P,
            /* inScanFormat */
            FVID2_SF_PROGRESSIVE,
            /* inBPP */
            FVID2_BPP_BITS16,
            /* cropStartX */
            0u,
            /* cropStartY */
            0u,
            /* cropWidth */
            1280u,
            /* cropHeight */
            720u,
            /* nonLinear */
            SC_NONLINEAR_DISABLE,
            /* stripSize */
            0u,
            /* enableScAdvCfg */
            SC_ADVCFG_DISABLE,
            /* advCfg */
            NULL,
            /* cscCoeff */
            NULL,
            /* outStrmParams[VPS_CAPT_STREAM_ID_MAX] */
            {
                /* Stream #0 */
                {
                    /* outWidth */
                    1280u,
                    /* outHeight */
                    720u,
                    /* outDataFmt */
                    FVID2_DF_RGB24_888,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_DISABLE_ALL,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                },
                /* Stream #1 */
                {
                    /* outWidth */
                    720u,
                    /* outHeight */
                    240u,
                    /* outDataFmt */
                    FVID2_DF_YUV422I_YUYV,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_ENABLE_1,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                }
            }
        }
    },
    {
        /* testEnable */
        TEST_ENABLE,
        /* bufCaptModeTestEnable */
        BUF_CAPT_MODE_TEST_DISABLE,
        /* printEnable */
        PRINT_ENABLE,
        /* Software Requirement Id  */
        ":PDK-966:PDK-990:",
        /* testCaseId */
        10029u,
        /* testType */
        ST_TT_SANITY,
        /* runCount */
        ST_CAPT_RUN_COUNT,
        /* testDescStr */
#ifdef SOC_TDA2EX
        "OV1063x->VIP1_S1_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), Dual out -  RGB888, YUV420SP 800x480 Scaled out",
#else
        "OV1063x->VIP1_S0_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), Dual out -  RGB888, YUV420SP 800x480 Scaled out",
#endif
        /* testCaseType */
        ST_CAPT_TCT_MAIN,
        /* numHandles */
        1u,
        NULL,
        NULL,
        /* platformId */
        BSP_PLATFORM_ID_EVM,
        /* socId */
        BOARD_SOC_ID,
        /* boardId */
        (BSP_BOARD_GP_AM572X | BSP_BOARD_IDK_AM57XX | BSP_BOARD_VISION | BSP_BOARD_BASE_TDA3XX),
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_8BIT,
        /* startstpCnt */
        1,
        /* maxSizeRegs[VPS_VIP_MAX] */
        {
            /* VPS_VIP1 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX) || defined(SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_AM574x)
            /* VPS_VIP2 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX)
            /* VPS_VIP3 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            }
#endif
#endif
        },

        /* testInstPrms[VPS_CAPT_INST_MAX] */
        {
            /* instId[] */
            BOARD_MAKE_VIP_INST_ID,
            /* decDrvId[] */
            BOARD_VID_SENSOR_DRV_ID,
            /* standard */
            FVID2_STD_720P_60,
            /* videoIfMode */
            FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
            /* videoIfWidth */
            FVID2_VIFW_8BIT,
            /* bufCaptMode */
            VPS_CAPT_BCM_LAST_FRM_REPEAT,
            /* numCh */
            1u,
            /* numStream */
            2u,
            /* inWidth */
            1280u,
            /* inHeight */
            720u,
            /* inDataFmt */
            FVID2_DF_YUV422P,
            /* inScanFormat */
            FVID2_SF_PROGRESSIVE,
            /* inBPP */
            FVID2_BPP_BITS16,
            /* cropStartX */
            0u,
            /* cropStartY */
            0u,
            /* cropWidth */
            1280u,
            /* cropHeight */
            720u,
            /* nonLinear */
            SC_NONLINEAR_DISABLE,
            /* stripSize */
            0u,
            /* enableScAdvCfg */
            SC_ADVCFG_DISABLE,
            /* advCfg */
            NULL,
            /* cscCoeff */
            NULL,
            /* outStrmParams[VPS_CAPT_STREAM_ID_MAX] */
            {
                /* Stream #0 */
                {
                    /* outWidth */
                    1280u,
                    /* outHeight */
                    720u,
                    /* outDataFmt */
                    FVID2_DF_RGB24_888,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_DISABLE_ALL,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                },
                /* Stream #1 */
                {
                    /* outWidth */
                    800u,
                    /* outHeight */
                    480u,
                    /* outDataFmt */
                    FVID2_DF_YUV420SP_UV,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_ENABLE_1,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                }
            }
        }
    },
    {
        /* testEnable */
        TEST_ENABLE,
        /* bufCaptModeTestEnable */
        BUF_CAPT_MODE_TEST_DISABLE,
        /* printEnable */
        PRINT_ENABLE,
        /* Software Requirement Id  */
        ":PDK-922:PDK-923:",
        /* testCaseId */
        10030u,
        /* testType */
        ST_TT_SANITY,
        /* runCount */
        ST_CAPT_RUN_COUNT,
        /* testDescStr */
#ifdef SOC_TDA2EX
        "OV1063x->VIP1_S1_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), YUYV422I out, with PosXY(400,200), Crop(800W,480H)",
#else
        "OV1063x->VIP1_S0_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), YUYV422I out, with PosXY(400,200), Crop(800W,480H)",
#endif
        /* testCaseType */
        ST_CAPT_TCT_MAIN,
        /* numHandles */
        1u,
        NULL,
        NULL,
        /* platformId */
        BSP_PLATFORM_ID_EVM,
        /* socId */
        BOARD_SOC_ID,
        /* boardId */
        (BSP_BOARD_GP_AM572X | BSP_BOARD_IDK_AM57XX | BSP_BOARD_VISION | BSP_BOARD_BASE_TDA3XX),
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_8BIT,
        /* startstpCnt */
        1,
        /* maxSizeRegs[VPS_VIP_MAX] */
        {
            /* VPS_VIP1 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX) || defined(SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_AM574x)
            /* VPS_VIP2 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX)
            /* VPS_VIP3 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            }
#endif
#endif
        },

        /* testInstPrms[VPS_CAPT_INST_MAX] */
        {
            /* instId[] */
            BOARD_MAKE_VIP_INST_ID,
            /* decDrvId[] */
            BOARD_VID_SENSOR_DRV_ID,
            /* standard */
            FVID2_STD_720P_60,
            /* videoIfMode */
            FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
            /* videoIfWidth */
            FVID2_VIFW_8BIT,
            /* bufCaptMode */
            VPS_CAPT_BCM_LAST_FRM_REPEAT,
            /* numCh */
            1u,
            /* numStream */
            1u,
            /* inWidth */
            1280u,
            /* inHeight */
            720u,
            /* inDataFmt */
            FVID2_DF_YUV422P,
            /* inScanFormat */
            FVID2_SF_PROGRESSIVE,
            /* inBPP */
            FVID2_BPP_BITS16,
            /* cropStartX */
            400u,
            /* cropStartY */
            200u,
            /* cropWidth */
            800u,
            /* cropHeight */
            480u,
            /* nonLinear */
            SC_NONLINEAR_DISABLE,
            /* stripSize */
            0u,
            /* enableScAdvCfg */
            SC_ADVCFG_DISABLE,
            /* advCfg */
            NULL,
            /* cscCoeff */
            NULL,
            /* outStrmParams[VPS_CAPT_STREAM_ID_MAX] */
            {
                /* Stream #0 */
                {
                    /* outWidth */
                    800u,
                    /* outHeight */
                    480u,
                    /* outDataFmt */
                    FVID2_DF_YUV422I_YUYV,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_ENABLE_0,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                }
            }
        }
    },
    {
        /* testEnable */
        TEST_ENABLE,
        /* bufCaptModeTestEnable */
        BUF_CAPT_MODE_TEST_DISABLE,
        /* printEnable */
        PRINT_ENABLE,
        /* Software Requirement Id  */
        ":PDK-924:",
        /* testCaseId */
        10031u,
        /* testType */
        ST_TT_SANITY,
        /* runCount */
        ST_CAPT_RUN_COUNT,
        /* testDescStr */
#ifdef SOC_TDA2EX
        "OV1063x->VIP1_S1_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), YUYV422I 160x180 Scaled out",
#else
        "OV1063x->VIP1_S0_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), YUYV422I 160x180 Scaled out",
#endif
        /* testCaseType */
        ST_CAPT_TCT_MAIN,
        /* numHandles */
        1u,
        NULL,
        NULL,
        /* platformId */
        BSP_PLATFORM_ID_EVM,
        /* socId */
        BOARD_SOC_ID,
        /* boardId */
        (BSP_BOARD_GP_AM572X | BSP_BOARD_IDK_AM57XX | BSP_BOARD_VISION | BSP_BOARD_BASE_TDA3XX),
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_8BIT,
        /* startstpCnt */
        1,
        /* maxSizeRegs[VPS_VIP_MAX] */
        {
            /* VPS_VIP1 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX) || defined(SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_AM574x)
            /* VPS_VIP2 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX)
            /* VPS_VIP3 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            }
#endif
#endif
        },

        /* testInstPrms[VPS_CAPT_INST_MAX] */
        {
            /* instId[] */
            BOARD_MAKE_VIP_INST_ID,
            /* decDrvId[] */
            BOARD_VID_SENSOR_DRV_ID,
            /* standard */
            FVID2_STD_720P_60,
            /* videoIfMode */
            FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
            /* videoIfWidth */
            FVID2_VIFW_8BIT,
            /* bufCaptMode */
            VPS_CAPT_BCM_LAST_FRM_REPEAT,
            /* numCh */
            1u,
            /* numStream */
            1u,
            /* inWidth */
            1280u,
            /* inHeight */
            720u,
            /* inDataFmt */
            FVID2_DF_YUV422P,
            /* inScanFormat */
            FVID2_SF_PROGRESSIVE,
            /* inBPP */
            FVID2_BPP_BITS16,
            /* cropStartX */
            0u,
            /* cropStartY */
            0u,
            /* cropWidth */
            1280u,
            /* cropHeight */
            720u,
            /* nonLinear */
            SC_NONLINEAR_DISABLE,
            /* stripSize */
            0u,
            /* enableScAdvCfg */
            SC_ADVCFG_DISABLE,
            /* advCfg */
            NULL,
            /* cscCoeff */
            NULL,
            /* outStrmParams[VPS_CAPT_STREAM_ID_MAX] */
            {
                /* Stream #0 */
                {
                    /* outWidth */
                    160u,
                    /* outHeight */
                    180u,
                    /* outDataFmt */
                    FVID2_DF_YUV422I_YUYV,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_ENABLE_0,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                }
            }
        }
    },
    {
        /* testEnable */
        TEST_ENABLE,
        /* bufCaptModeTestEnable */
        BUF_CAPT_MODE_TEST_DISABLE,
        /* printEnable */
        PRINT_ENABLE,
        /* Software Requirement Id  */
        ":PDK-925:",
        /* testCaseId */
        10032u,
        /* testType */
        ST_TT_SANITY,
        /* runCount */
        ST_CAPT_RUN_COUNT,
        /* testDescStr */
#ifdef SOC_TDA2EX
        "OV1063x->VIP1_S1_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), YUYV422I 1920x1080 Scaled out",
#else
        "OV1063x->VIP1_S0_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), YUYV422I 1920x1080 Scaled out",
#endif
        /* testCaseType */
        ST_CAPT_TCT_MAIN,
        /* numHandles */
        1u,
        NULL,
        NULL,
        /* platformId */
        BSP_PLATFORM_ID_EVM,
        /* socId */
        BOARD_SOC_ID,
        /* boardId */
        (BSP_BOARD_GP_AM572X | BSP_BOARD_IDK_AM57XX | BSP_BOARD_VISION | BSP_BOARD_BASE_TDA3XX),
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_8BIT,
        /* startstpCnt */
        1,
        /* maxSizeRegs[VPS_VIP_MAX] */
        {
            /* VPS_VIP1 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX) || defined(SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_AM574x)
            /* VPS_VIP2 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX)
            /* VPS_VIP3 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            }
#endif
#endif
        },

        /* testInstPrms[VPS_CAPT_INST_MAX] */
        {
            /* instId[] */
            BOARD_MAKE_VIP_INST_ID,
            /* decDrvId[] */
            BOARD_VID_SENSOR_DRV_ID,
            /* standard */
            FVID2_STD_720P_60,
            /* videoIfMode */
            FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
            /* videoIfWidth */
            FVID2_VIFW_8BIT,
            /* bufCaptMode */
            VPS_CAPT_BCM_LAST_FRM_REPEAT,
            /* numCh */
            1u,
            /* numStream */
            1u,
            /* inWidth */
            1280u,
            /* inHeight */
            720u,
            /* inDataFmt */
            FVID2_DF_YUV422P,
            /* inScanFormat */
            FVID2_SF_PROGRESSIVE,
            /* inBPP */
            FVID2_BPP_BITS16,
            /* cropStartX */
            0u,
            /* cropStartY */
            0u,
            /* cropWidth */
            1280u,
            /* cropHeight */
            720u,
            /* nonLinear */
            SC_NONLINEAR_DISABLE,
            /* stripSize */
            0u,
            /* enableScAdvCfg */
            SC_ADVCFG_DISABLE,
            /* advCfg */
            NULL,
            /* cscCoeff */
            NULL,
            /* outStrmParams[VPS_CAPT_STREAM_ID_MAX] */
            {
                /* Stream #0 */
                {
                    /* outWidth */
                    1920u,
                    /* outHeight */
                    1080u,
                    /* outDataFmt */
                    FVID2_DF_YUV422I_YUYV,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_ENABLE_0,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                }
            }
        }
    },
    {
        /* testEnable */
        TEST_ENABLE,
        /* bufCaptModeTestEnable */
        BUF_CAPT_MODE_TEST_DISABLE,
        /* printEnable */
        PRINT_ENABLE,
        /* Software Requirement Id  */
        ":PDK-754:",
        /* testCaseId */
        10033u,
        /* testType */
        ST_TT_SANITY,
        /* runCount */
        ST_CAPT_RUN_COUNT,
        /* testDescStr */
#ifdef SOC_TDA2EX
        "OV1063x->VIP1_S1_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), YUV444I out",
#else
        "OV1063x->VIP1_S0_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), YUV444I out",
#endif
        /* testCaseType */
        ST_CAPT_TCT_MAIN,
        /* numHandles */
        1u,
        NULL,
        NULL,
        /* platformId */
        BSP_PLATFORM_ID_EVM,
        /* socId */
        BOARD_SOC_ID,
        /* boardId */
        (BSP_BOARD_GP_AM572X | BSP_BOARD_IDK_AM57XX | BSP_BOARD_VISION | BSP_BOARD_BASE_TDA3XX),
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_8BIT,
        /* startstpCnt */
        1,
        /* maxSizeRegs[VPS_VIP_MAX] */
        {
            /* VPS_VIP1 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX) || defined(SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_AM574x)
            /* VPS_VIP2 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX)
            /* VPS_VIP3 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            }
#endif
#endif
        },

        /* testInstPrms[VPS_CAPT_INST_MAX] */
        {
            /* instId[] */
            BOARD_MAKE_VIP_INST_ID,
            /* decDrvId[] */
            BOARD_VID_SENSOR_DRV_ID,
            /* standard */
            FVID2_STD_720P_60,
            /* videoIfMode */
            FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
            /* videoIfWidth */
            FVID2_VIFW_8BIT,
            /* bufCaptMode */
            VPS_CAPT_BCM_LAST_FRM_REPEAT,
            /* numCh */
            1u,
            /* numStream */
            1u,
            /* inWidth */
            1280u,
            /* inHeight */
            720u,
            /* inDataFmt */
            FVID2_DF_YUV422P,
            /* inScanFormat */
            FVID2_SF_PROGRESSIVE,
            /* inBPP */
            FVID2_BPP_BITS16,
            /* cropStartX */
            0u,
            /* cropStartY */
            0u,
            /* cropWidth */
            1280u,
            /* cropHeight */
            720u,
            /* nonLinear */
            SC_NONLINEAR_DISABLE,
            /* stripSize */
            0u,
            /* enableScAdvCfg */
            SC_ADVCFG_DISABLE,
            /* advCfg */
            NULL,
            /* cscCoeff */
            NULL,
            /* outStrmParams[VPS_CAPT_STREAM_ID_MAX] */
            {
                /* Stream #0 */
                {
                    /* outWidth */
                    1280u,
                    /* outHeight */
                    720u,
                    /* outDataFmt */
                    FVID2_DF_YUV444I,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_DISABLE_ALL,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                }
            }
        }
    },
    {
        /* testEnable */
        TEST_ENABLE,
        /* bufCaptModeTestEnable */
        BUF_CAPT_MODE_TEST_DISABLE,
        /* printEnable */
        PRINT_ENABLE,
        /* Software Requirement Id  */
        ":PDK-922:PDK-923:",
        /* testCaseId */
        10034u,
        /* testType */
        ST_TT_SANITY,
        /* runCount */
        ST_CAPT_RUN_COUNT,
        /* testDescStr */
#ifdef SOC_TDA2EX
        "OV1063x->VIP1_S1_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), YUYV422I out, with PosXY(200,100), Crop(800W,480H)",
#else
        "OV1063x->VIP1_S0_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), YUYV422I out, with PosXY(200,100), Crop(800W,480H)",
#endif
        /* testCaseType */
        ST_CAPT_TCT_MAIN,
        /* numHandles */
        1u,
        NULL,
        NULL,
        /* platformId */
        BSP_PLATFORM_ID_EVM,
        /* socId */
        BOARD_SOC_ID,
        /* boardId */
        (BSP_BOARD_GP_AM572X | BSP_BOARD_IDK_AM57XX | BSP_BOARD_VISION | BSP_BOARD_BASE_TDA3XX),
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_8BIT,
        /* startstpCnt */
        1,
        /* maxSizeRegs[VPS_VIP_MAX] */
        {
            /* VPS_VIP1 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX) || defined(SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_AM574x)
            /* VPS_VIP2 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX)
            /* VPS_VIP3 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            }
#endif
#endif
        },

        /* testInstPrms[VPS_CAPT_INST_MAX] */
        {
            /* instId[] */
            BOARD_MAKE_VIP_INST_ID,
            /* decDrvId[] */
            BOARD_VID_SENSOR_DRV_ID,
            /* standard */
            FVID2_STD_720P_60,
            /* videoIfMode */
            FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
            /* videoIfWidth */
            FVID2_VIFW_8BIT,
            /* bufCaptMode */
            VPS_CAPT_BCM_LAST_FRM_REPEAT,
            /* numCh */
            1u,
            /* numStream */
            1u,
            /* inWidth */
            1280u,
            /* inHeight */
            720u,
            /* inDataFmt */
            FVID2_DF_YUV422P,
            /* inScanFormat */
            FVID2_SF_PROGRESSIVE,
            /* inBPP */
            FVID2_BPP_BITS16,
            /* cropStartX */
            200u,
            /* cropStartY */
            100u,
            /* cropWidth */
            800u,
            /* cropHeight */
            480u,
            /* nonLinear */
            SC_NONLINEAR_DISABLE,
            /* stripSize */
            0u,
            /* enableScAdvCfg */
            SC_ADVCFG_DISABLE,
            /* advCfg */
            NULL,
            /* cscCoeff */
            NULL,
            /* outStrmParams[VPS_CAPT_STREAM_ID_MAX] */
            {
                /* Stream #0 */
                {
                    /* outWidth */
                    800u,
                    /* outHeight */
                    480u,
                    /* outDataFmt */
                    FVID2_DF_YUV422I_YUYV,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_ENABLE_0,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                }
            }
        }
    },
    {
        /* testEnable */
        TEST_ENABLE,
        /* bufCaptModeTestEnable */
        BUF_CAPT_MODE_TEST_DISABLE,
        /* printEnable */
        PRINT_ENABLE,
        /* Software Requirement Id  */
        ":PDK-926:",
        /* testCaseId */
        10035u,
        /* testType */
        ST_TT_SANITY,
        /* runCount */
        ST_CAPT_RUN_COUNT,
        /* testDescStr */
#ifdef SOC_TDA2EX
        "OV1063x->VIP1_S1_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), YUYV422I 320x180 Scaled out",
#else
        "OV1063x->VIP1_S0_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), YUYV422I 320x180 Scaled out",
#endif
        /* testCaseType */
        ST_CAPT_TCT_MAIN,
        /* numHandles */
        1u,
        NULL,
        NULL,
        /* platformId */
        BSP_PLATFORM_ID_EVM,
        /* socId */
        BOARD_SOC_ID,
        /* boardId */
        (BSP_BOARD_GP_AM572X | BSP_BOARD_IDK_AM57XX | BSP_BOARD_VISION | BSP_BOARD_BASE_TDA3XX),
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_8BIT,
        /* startstpCnt */
        1,
        /* maxSizeRegs[VPS_VIP_MAX] */
        {
            /* VPS_VIP1 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX) || defined(SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_AM574x)
            /* VPS_VIP2 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX)
            /* VPS_VIP3 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            }
#endif
#endif
        },

        /* testInstPrms[VPS_CAPT_INST_MAX] */
        {
            /* instId[] */
            BOARD_MAKE_VIP_INST_ID,
            /* decDrvId[] */
            BOARD_VID_SENSOR_DRV_ID,
            /* standard */
            FVID2_STD_720P_60,
            /* videoIfMode */
            FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
            /* videoIfWidth */
            FVID2_VIFW_8BIT,
            /* bufCaptMode */
            VPS_CAPT_BCM_LAST_FRM_REPEAT,
            /* numCh */
            1u,
            /* numStream */
            1u,
            /* inWidth */
            1280u,
            /* inHeight */
            720u,
            /* inDataFmt */
            FVID2_DF_YUV422P,
            /* inScanFormat */
            FVID2_SF_PROGRESSIVE,
            /* inBPP */
            FVID2_BPP_BITS16,
            /* cropStartX */
            0u,
            /* cropStartY */
            0u,
            /* cropWidth */
            1280u,
            /* cropHeight */
            720u,
            /* nonLinear */
            SC_NONLINEAR_DISABLE,
            /* stripSize */
            0u,
            /* enableScAdvCfg */
            SC_ADVCFG_DISABLE,
            /* advCfg */
            NULL,
            /* cscCoeff */
            NULL,
            /* outStrmParams[VPS_CAPT_STREAM_ID_MAX] */
            {
                /* Stream #0 */
                {
                    /* outWidth */
                    320u,
                    /* outHeight */
                    180u,
                    /* outDataFmt */
                    FVID2_DF_YUV422I_YUYV,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_ENABLE_ALL,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                }
            }
        }
    },
    {
        /* testEnable */
        TEST_ENABLE,
        /* bufCaptModeTestEnable */
        BUF_CAPT_MODE_TEST_DISABLE,
        /* printEnable */
        PRINT_ENABLE,
        /* Software Requirement Id  */
        ":PDK-926:",
        /* testCaseId */
        10036u,
        /* testType */
        ST_TT_SANITY,
        /* runCount */
        ST_CAPT_RUN_COUNT,
        /* testDescStr */
#ifdef SOC_TDA2EX
        "OV1063x->VIP1_S1_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), YUYV422I 640x360 Scaled out",
#else
        "OV1063x->VIP1_S0_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), YUYV422I 640x360 Scaled out",
#endif
        /* testCaseType */
        ST_CAPT_TCT_MAIN,
        /* numHandles */
        1u,
        NULL,
        NULL,
        /* platformId */
        BSP_PLATFORM_ID_EVM,
        /* socId */
        BOARD_SOC_ID,
        /* boardId */
        (BSP_BOARD_GP_AM572X | BSP_BOARD_IDK_AM57XX | BSP_BOARD_VISION | BSP_BOARD_BASE_TDA3XX),
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_8BIT,
        /* startstpCnt */
        1,
        /* maxSizeRegs[VPS_VIP_MAX] */
        {
            /* VPS_VIP1 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX) || defined(SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_AM574x)
            /* VPS_VIP2 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX)
            /* VPS_VIP3 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            }
#endif
#endif
        },

        /* testInstPrms[VPS_CAPT_INST_MAX] */
        {
            /* instId[] */
            BOARD_MAKE_VIP_INST_ID,
            /* decDrvId[] */
            BOARD_VID_SENSOR_DRV_ID,
            /* standard */
            FVID2_STD_720P_60,
            /* videoIfMode */
            FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
            /* videoIfWidth */
            FVID2_VIFW_8BIT,
            /* bufCaptMode */
            VPS_CAPT_BCM_LAST_FRM_REPEAT,
            /* numCh */
            1u,
            /* numStream */
            1u,
            /* inWidth */
            1280u,
            /* inHeight */
            720u,
            /* inDataFmt */
            FVID2_DF_YUV422P,
            /* inScanFormat */
            FVID2_SF_PROGRESSIVE,
            /* inBPP */
            FVID2_BPP_BITS16,
            /* cropStartX */
            0u,
            /* cropStartY */
            0u,
            /* cropWidth */
            1280u,
            /* cropHeight */
            720u,
            /* nonLinear */
            SC_NONLINEAR_DISABLE,
            /* stripSize */
            0u,
            /* enableScAdvCfg */
            SC_ADVCFG_DISABLE,
            /* advCfg */
            NULL,
            /* cscCoeff */
            NULL,
            /* outStrmParams[VPS_CAPT_STREAM_ID_MAX] */
            {
                /* Stream #0 */
                {
                    /* outWidth */
                    640u,
                    /* outHeight */
                    360u,
                    /* outDataFmt */
                    FVID2_DF_YUV422I_YUYV,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_ENABLE_ALL,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                }
            }
        }
    },
    {
        /* testEnable */
        TEST_ENABLE,
        /* bufCaptModeTestEnable */
        BUF_CAPT_MODE_TEST_DISABLE,
        /* printEnable */
        PRINT_ENABLE,
        /* Software Requirement Id  */
        ":PDK-926:",
        /* testCaseId */
        10037u,
        /* testType */
        ST_TT_SANITY,
        /* runCount */
        ST_CAPT_RUN_COUNT,
        /* testDescStr */
#ifdef SOC_TDA2EX
        "OV1063x->VIP1_S1_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), YUYV422I 1280x720 Scaled out",
#else
        "OV1063x->VIP1_S0_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), YUYV422I 1280x720 Scaled out",
#endif
        /* testCaseType */
        ST_CAPT_TCT_MAIN,
        /* numHandles */
        1u,
        NULL,
        NULL,
        /* platformId */
        BSP_PLATFORM_ID_EVM,
        /* socId */
        BOARD_SOC_ID,
        /* boardId */
        (BSP_BOARD_GP_AM572X | BSP_BOARD_IDK_AM57XX | BSP_BOARD_VISION | BSP_BOARD_BASE_TDA3XX),
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_8BIT,
        /* startstpCnt */
        1,
        /* maxSizeRegs[VPS_VIP_MAX] */
        {
            /* VPS_VIP1 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX) || defined(SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_AM574x)
            /* VPS_VIP2 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX)
            /* VPS_VIP3 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            }
#endif
#endif
        },

        /* testInstPrms[VPS_CAPT_INST_MAX] */
        {
            /* instId[] */
            BOARD_MAKE_VIP_INST_ID,
            /* decDrvId[] */
            BOARD_VID_SENSOR_DRV_ID,
            /* standard */
            FVID2_STD_720P_60,
            /* videoIfMode */
            FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
            /* videoIfWidth */
            FVID2_VIFW_8BIT,
            /* bufCaptMode */
            VPS_CAPT_BCM_LAST_FRM_REPEAT,
            /* numCh */
            1u,
            /* numStream */
            1u,
            /* inWidth */
            1280u,
            /* inHeight */
            720u,
            /* inDataFmt */
            FVID2_DF_YUV422P,
            /* inScanFormat */
            FVID2_SF_PROGRESSIVE,
            /* inBPP */
            FVID2_BPP_BITS16,
            /* cropStartX */
            0u,
            /* cropStartY */
            0u,
            /* cropWidth */
            1280u,
            /* cropHeight */
            720u,
            /* nonLinear */
            SC_NONLINEAR_DISABLE,
            /* stripSize */
            0u,
            /* enableScAdvCfg */
            SC_ADVCFG_DISABLE,
            /* advCfg */
            NULL,
            /* cscCoeff */
            NULL,
            /* outStrmParams[VPS_CAPT_STREAM_ID_MAX] */
            {
                /* Stream #0 */
                {
                    /* outWidth */
                    1280u,
                    /* outHeight */
                    720u,
                    /* outDataFmt */
                    FVID2_DF_YUV422I_YUYV,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_ENABLE_ALL,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                }
            }
        }
    },
    {
        /* testEnable */
        TEST_ENABLE,
        /* bufCaptModeTestEnable */
        BUF_CAPT_MODE_TEST_DISABLE,
        /* printEnable */
        PRINT_ENABLE,
        /* Software Requirement Id  */
        ":None:",
        /* testCaseId */
        10038u,
        /* testType */
        ST_TT_SANITY,
        /* runCount */
        ST_CAPT_RUN_COUNT,
        /* testDescStr */
#ifdef SOC_TDA2EX
        "OV1063x->VIP1_S1_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), YUYV422I out - Buffer Capture Mode:Last frame repeat mode ",
#else
        "OV1063x->VIP1_S0_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), YUYV422I out - Buffer Capture Mode:Last frame repeat mode ",
#endif
        /* testCaseType */
        ST_CAPT_TCT_MAIN,
        /* numHandles */
        1u,
        NULL,
        NULL,
        /* platformId */
        BSP_PLATFORM_ID_EVM,
        /* socId */
        BOARD_SOC_ID,
        /* boardId */
        (BSP_BOARD_GP_AM572X | BSP_BOARD_IDK_AM57XX | BSP_BOARD_VISION | BSP_BOARD_BASE_TDA3XX),
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_8BIT,
        /* startstpCnt */
        1,
        /* maxSizeRegs[VPS_VIP_MAX] */
        {
            /* VPS_VIP1 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX) || defined(SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_AM574x)
            /* VPS_VIP2 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX)
            /* VPS_VIP3 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            }
#endif
#endif
        },

        /* testInstPrms[VPS_CAPT_INST_MAX] */
        {
            /* instId[] */
            BOARD_MAKE_VIP_INST_ID,
            /* decDrvId[] */
            BOARD_VID_SENSOR_DRV_ID,
            /* standard */
            FVID2_STD_720P_60,
            /* videoIfMode */
            FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
            /* videoIfWidth */
            FVID2_VIFW_8BIT,
            /* bufCaptMode */
            VPS_CAPT_BCM_LAST_FRM_REPEAT,
            /* numCh */
            1u,
            /* numStream */
            1u,
            /* inWidth */
            1280u,
            /* inHeight */
            720u,
            /* inDataFmt */
            FVID2_DF_YUV422P,
            /* inScanFormat */
            FVID2_SF_PROGRESSIVE,
            /* inBPP */
            FVID2_BPP_BITS16,
            /* cropStartX */
            0u,
            /* cropStartY */
            0u,
            /* cropWidth */
            1280u,
            /* cropHeight */
            720u,
            /* nonLinear */
            SC_NONLINEAR_DISABLE,
            /* stripSize */
            0u,
            /* enableScAdvCfg */
            SC_ADVCFG_DISABLE,
            /* advCfg */
            NULL,
            /* cscCoeff */
            NULL,
            /* outStrmParams[VPS_CAPT_STREAM_ID_MAX] */
            {
                /* Stream #0 */
                {
                    /* outWidth */
                    1280u,
                    /* outHeight */
                    720u,
                    /* outDataFmt */
                    FVID2_DF_YUV422I_YUYV,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_DISABLE_ALL,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                }
            }
        }
    },
    {
        /* testEnable */
        TEST_ENABLE,
        /* bufCaptModeTestEnable */
        BUF_CAPT_MODE_TEST_DISABLE,
        /* printEnable */
        PRINT_ENABLE,
        /* Software Requirement Id  */
        ":None:",
        /* testCaseId */
        10039u,
        /* testType */
        ST_TT_SANITY,
        /* runCount */
        ST_CAPT_RUN_COUNT,
        /* testDescStr */
#ifdef SOC_TDA2EX
        "OV1063x->VIP1_S1_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), YUYV422I out - Buffer Capture Mode:Circular frame repeat mode",
#else
        "OV1063x->VIP1_S0_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), YUYV422I out - Buffer Capture Mode:Circular frame repeat mode",
#endif
        /* testCaseType */
        ST_CAPT_TCT_MAIN,
        /* numHandles */
        1u,
        NULL,
        NULL,
        /* platformId */
        BSP_PLATFORM_ID_EVM,
        /* socId */
        BOARD_SOC_ID,
        /* boardId */
        (BSP_BOARD_GP_AM572X | BSP_BOARD_IDK_AM57XX | BSP_BOARD_VISION | BSP_BOARD_BASE_TDA3XX),
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_8BIT,
        /* startstpCnt */
        1,
        /* maxSizeRegs[VPS_VIP_MAX] */
        {
            /* VPS_VIP1 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX) || defined(SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_AM574x)
            /* VPS_VIP2 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX)
            /* VPS_VIP3 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            }
#endif
#endif
        },

        /* testInstPrms[VPS_CAPT_INST_MAX] */
        {
            /* instId[] */
            BOARD_MAKE_VIP_INST_ID,
            /* decDrvId[] */
            BOARD_VID_SENSOR_DRV_ID,
            /* standard */
            FVID2_STD_720P_60,
            /* videoIfMode */
            FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
            /* videoIfWidth */
            FVID2_VIFW_8BIT,
            /* bufCaptMode */
            VPS_CAPT_BCM_CIRCULAR_FRM_REPEAT,
            /* numCh */
            1u,
            /* numStream */
            1u,
            /* inWidth */
            1280u,
            /* inHeight */
            720u,
            /* inDataFmt */
            FVID2_DF_YUV422P,
            /* inScanFormat */
            FVID2_SF_PROGRESSIVE,
            /* inBPP */
            FVID2_BPP_BITS16,
            /* cropStartX */
            0u,
            /* cropStartY */
            0u,
            /* cropWidth */
            1280u,
            /* cropHeight */
            720u,
            /* nonLinear */
            SC_NONLINEAR_DISABLE,
            /* stripSize */
            0u,
            /* enableScAdvCfg */
            SC_ADVCFG_DISABLE,
            /* advCfg */
            NULL,
            /* cscCoeff */
            NULL,
            /* outStrmParams[VPS_CAPT_STREAM_ID_MAX] */
            {
                /* Stream #0 */
                {
                    /* outWidth */
                    1280u,
                    /* outHeight */
                    720u,
                    /* outDataFmt */
                    FVID2_DF_YUV422I_YUYV,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_DISABLE_ALL,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                }
            }
        }
    },
    {
        /* testEnable */
        TEST_ENABLE,
        /* bufCaptModeTestEnable */
        BUF_CAPT_MODE_TEST_DISABLE,
        /* printEnable */
        PRINT_ENABLE,
        /* Software Requirement Id  */
        ":PDK-897:",
        /* testCaseId */
        10040u,
        /* testType */
        ST_TT_SANITY,
        /* runCount */
        ST_CAPT_RUN_COUNT,
        /* testDescStr */
#ifdef SOC_TDA2EX
        "OV1063x->VIP1_S1_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), YUYV422I out - Buffer Capture Mode: Frame drop mode",
#else
        "OV1063x->VIP1_S0_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), YUYV422I out - Buffer Capture Mode: Frame drop mode",
#endif
        /* testCaseType */
        ST_CAPT_TCT_MAIN,
        /* numHandles */
        1u,
        NULL,
        NULL,
        /* platformId */
        BSP_PLATFORM_ID_EVM,
        /* socId */
        BOARD_SOC_ID,
        /* boardId */
        (BSP_BOARD_GP_AM572X | BSP_BOARD_IDK_AM57XX | BSP_BOARD_VISION | BSP_BOARD_BASE_TDA3XX),
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_8BIT,
        /* startstpCnt */
        1,
        /* maxSizeRegs[VPS_VIP_MAX] */
        {
            /* VPS_VIP1 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX) || defined(SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_AM574x)
            /* VPS_VIP2 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX)
            /* VPS_VIP3 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            }
#endif
#endif
        },

        /* testInstPrms[VPS_CAPT_INST_MAX] */
        {
            /* instId[] */
            BOARD_MAKE_VIP_INST_ID,
            /* decDrvId[] */
            BOARD_VID_SENSOR_DRV_ID,
            /* standard */
            FVID2_STD_720P_60,
            /* videoIfMode */
            FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
            /* videoIfWidth */
            FVID2_VIFW_8BIT,
            /* bufCaptMode */
            VPS_CAPT_BCM_FRM_DROP,
            /* numCh */
            1u,
            /* numStream */
            1u,
            /* inWidth */
            1280u,
            /* inHeight */
            720u,
            /* inDataFmt */
            FVID2_DF_YUV422P,
            /* inScanFormat */
            FVID2_SF_PROGRESSIVE,
            /* inBPP */
            FVID2_BPP_BITS16,
            /* cropStartX */
            0u,
            /* cropStartY */
            0u,
            /* cropWidth */
            1280u,
            /* cropHeight */
            720u,
            /* nonLinear */
            SC_NONLINEAR_DISABLE,
            /* stripSize */
            0u,
            /* enableScAdvCfg */
            SC_ADVCFG_DISABLE,
            /* advCfg */
            NULL,
            /* cscCoeff */
            NULL,
            /* outStrmParams[VPS_CAPT_STREAM_ID_MAX] */
            {
                /* Stream #0 */
                {
                    /* outWidth */
                    1280u,
                    /* outHeight */
                    720u,
                    /* outDataFmt */
                    FVID2_DF_YUV422I_YUYV,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_DISABLE_ALL,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x2AAAAAAA, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                }
            }
        }
    },
/* Disable TVP5158 testcases as they are already tested in example and is a
 * problem for test automation */
#if 0
#if (defined SOC_TDA2XX) || (defined SOC_DRA75x) || (defined SOC_TDA2EX)
    {
        /* testEnable */
        TEST_ENABLE,
        /* bufCaptModeTestEnable */
        BUF_CAPT_MODE_TEST_DISABLE,
        /* printEnable */
        PRINT_ENABLE,
        /* Software Requirement Id  */
        ":PDK-894:PDK-935:PDK-938:PDK-943:PDK-1216:",
        /* testCaseId */
        10041u,
        /* testType */
        ST_TT_SANITY,
        /* runCount */
        ST_CAPT_RUN_COUNT,
        /* testDescStr */
#ifdef SOC_TDA2EX
        "TVP5158->VIP1_S1_PORTA SCH D1 8-bit Embedded Sync, YUYV422I out",
#else
        "TVP5158->VIP1_S0_PORTA SCH D1 8-bit Embedded Sync, YUYV422I out",
#endif
        /* testCaseType */
        ST_CAPT_TCT_MAIN,
        /* numHandles */
        1u,
        NULL,
        NULL,
        /* platformId */
        BSP_PLATFORM_ID_EVM,
        /* socId */
        BOARD_SOC_ID,
        /* boardId */
        (BSP_BOARD_JAMR3),
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_BT656,
        /* startstpCnt */
        1,
        /* maxSizeRegs[VPS_VIP_MAX] */
        {
            /* VPS_VIP1 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX) || defined(SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_AM574x)
            /* VPS_VIP2 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX)
            /* VPS_VIP3 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            }
#endif
#endif
        },

        /* testInstPrms[VPS_CAPT_INST_MAX] */
        {
            /*instId */
            BOARD_MAKE_VIP_INST_ID,
            /* decDrvId[] */
            FVID2_VID_DEC_TVP5158_DRV,
            /* standard */
            FVID2_STD_D1,
            /* videoIfMode */
            FVID2_VIFM_SCH_ES,
            /* videoIfWidth */
            FVID2_VIFW_8BIT,
            /* bufCaptMode */
            VPS_CAPT_BCM_LAST_FRM_REPEAT,
            /* numCh */
            1u,
            /* numStream */
            1u,
            /* inWidth */
            720u,
            /* inHeight */
            240u,
            /* inDataFmt */
            FVID2_DF_YUV422P,
            /* inScanFormat */
            FVID2_SF_INTERLACED,
            /* inBPP */
            FVID2_BPP_BITS16,
            /* cropStartX */
            0u,
            /* cropStartY */
            0u,
            /* cropWidth */
            720u,
            /* cropHeight */
            240u,
            /* nonLinear */
            SC_NONLINEAR_DISABLE,
            /* stripSize */
            0u,
            /* enableScAdvCfg */
            SC_ADVCFG_DISABLE,
            /* advCfg */
            NULL,
            /* cscCoeff */
            NULL,
            /* outStrmParams[VPS_CAPT_STREAM_ID_MAX] */
            {
                /* Stream #0 */
                {
                    /* outWidth */
                    720u,
                    /* outHeight */
                    240u,
                    /* outDataFmt */
                    FVID2_DF_YUV422I_YUYV,
                    /* outScanFormat */
                    FVID2_SF_INTERLACED,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_768_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_768_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_768_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_576_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_576_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_576_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_DISABLE_ALL,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                }
            }
        }
    },
    {
        /* testEnable */
        TEST_ENABLE,
        /* bufCaptModeTestEnable */
        BUF_CAPT_MODE_TEST_DISABLE,
        /* printEnable */
        PRINT_ENABLE,
        /* Software Requirement Id  */
        ":PDK-945:",
        /* testCaseId */
        10042u,
        /* testType */
        ST_TT_SANITY,
        /* runCount */
        ST_CAPT_RUN_COUNT,
        /* testDescStr */
#ifdef SOC_TDA2EX
        "TVP5158->VIP1_S1_PORTA 4-CH D1 8-bit Pixel Multiplexed Embedded Sync, YUYV422I out",
#else
        "TVP5158->VIP1_S0_PORTA 4-CH D1 8-bit Pixel Multiplexed Embedded Sync, YUYV422I out",
#endif
        /* testCaseType */
        ST_CAPT_TCT_MAIN,
        /* numHandles */
        1u,
        NULL,
        NULL,
        /* platformId */
        BSP_PLATFORM_ID_EVM,
        /* socId */
        BOARD_SOC_ID,
        /* boardId */
        (BSP_BOARD_JAMR3),
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_BT656,
        /* startstpCnt */
        1,
        /* maxSizeRegs[VPS_VIP_MAX] */
        {
            /* VPS_VIP1 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX) || defined(SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_AM574x)
            /* VPS_VIP2 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX)
            /* VPS_VIP3 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            }
#endif
#endif
        },

        /* testInstPrms[VPS_CAPT_INST_MAX] */
        {
            /*instId */
            BOARD_MAKE_VIP_INST_ID,
            /* decDrvId[] */
            FVID2_VID_DEC_TVP5158_DRV,
            /* standard */
            FVID2_STD_MUX_4CH_D1,
            /* videoIfMode */
            FVID2_VIFM_MCH_PIXEL_MUX_ES,
            /* videoIfWidth */
            FVID2_VIFW_8BIT,
            /* bufCaptMode */
            VPS_CAPT_BCM_LAST_FRM_REPEAT,
            /* numCh */
            4u,
            /* numStream */
            1u,
            /* inWidth */
            720u,
            /* inHeight */
            240u,
            /* inDataFmt */
            FVID2_DF_YUV422P,
            /* inScanFormat */
            FVID2_SF_INTERLACED,
            /* inBPP */
            FVID2_BPP_BITS16,
            /* cropStartX */
            0u,
            /* cropStartY */
            0u,
            /* cropWidth */
            720u,
            /* cropHeight */
            240u,
            /* nonLinear */
            SC_NONLINEAR_DISABLE,
            /* stripSize */
            0u,
            /* enableScAdvCfg */
            SC_ADVCFG_DISABLE,
            /* advCfg */
            NULL,
            /* cscCoeff */
            NULL,
            /* outStrmParams[VPS_CAPT_STREAM_ID_MAX] */
            {
                /* Stream #0 */
                {
                    /* outWidth */
                    720u,
                    /* outHeight */
                    240u,
                    /* outDataFmt */
                    FVID2_DF_YUV422I_YUYV,
                    /* outScanFormat */
                    FVID2_SF_INTERLACED,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_768_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_768_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_768_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_576_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_576_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_576_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_DISABLE_ALL,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                }
            }
        }
    },
    {
        /* testEnable */
        TEST_ENABLE,
        /* bufCaptModeTestEnable */
        BUF_CAPT_MODE_TEST_DISABLE,
        /* printEnable */
        PRINT_ENABLE,
        /* Software Requirement Id  */
        ":PDK-946:",
        /* testCaseId */
        10043u,
        /* testType */
        ST_TT_SANITY,
        /* runCount */
        ST_CAPT_RUN_COUNT,
        /* testDescStr */
#ifdef SOC_TDA2EX
        "TVP5158->VIP1_S1_PORTA 4-CH D1 8-bit Line Multiplexed Embedded Sync, YUYV422I out",
#else
        "TVP5158->VIP1_S0_PORTA 4-CH D1 8-bit Line Multiplexed Embedded Sync, YUYV422I out",
#endif
        /* testCaseType */
        ST_CAPT_TCT_MAIN,
        /* numHandles */
        1u,
        NULL,
        NULL,
        /* platformId */
        BSP_PLATFORM_ID_EVM,
        /* socId */
        BOARD_SOC_ID,
        /* boardId */
        (BSP_BOARD_JAMR3),
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_BT656,
        /* startstpCnt */
        1,
        /* maxSizeRegs[VPS_VIP_MAX] */
        {
            /* VPS_VIP1 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX) || defined(SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_AM574x)
            /* VPS_VIP2 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX)
            /* VPS_VIP3 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            }
#endif
#endif
        },

        /* testInstPrms[VPS_CAPT_INST_MAX] */
        {
            /*instId */
            BOARD_MAKE_VIP_INST_ID,
            /* decDrvId[] */
            FVID2_VID_DEC_TVP5158_DRV,
            /* standard */
            FVID2_STD_MUX_4CH_D1,
            /* videoIfMode */
            FVID2_VIFM_MCH_LINE_MUX_ES,
            /* videoIfWidth */
            FVID2_VIFW_8BIT,
            /* bufCaptMode */
            VPS_CAPT_BCM_LAST_FRM_REPEAT,
            /* numCh */
            4u,
            /* numStream */
            1u,
            /* inWidth */
            720u,
            /* inHeight */
            240u,
            /* inDataFmt */
            FVID2_DF_YUV422P,
            /* inScanFormat */
            FVID2_SF_INTERLACED,
            /* inBPP */
            FVID2_BPP_BITS16,
            /* cropStartX */
            0u,
            /* cropStartY */
            0u,
            /* cropWidth */
            720u,
            /* cropHeight */
            240u,
            /* nonLinear */
            SC_NONLINEAR_DISABLE,
            /* stripSize */
            0u,
            /* enableScAdvCfg */
            SC_ADVCFG_DISABLE,
            /* advCfg */
            NULL,
            /* cscCoeff */
            NULL,
            /* outStrmParams[VPS_CAPT_STREAM_ID_MAX] */
            {
                /* Stream #0 */
                {
                    /* outWidth */
                    720u,
                    /* outHeight */
                    240u,
                    /* outDataFmt */
                    FVID2_DF_YUV422I_YUYV,
                    /* outScanFormat */
                    FVID2_SF_INTERLACED,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_768_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_768_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_768_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_576_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_576_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_576_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_DISABLE_ALL,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                }
            }
        }
    },
#endif
#endif
    {
        /* testEnable */
        TEST_ENABLE,
        /* bufCaptModeTestEnable */
        BUF_CAPT_MODE_TEST_DISABLE,
        /* printEnable */
        PRINT_ENABLE,
        /* Software Requirement Id  */
        ":PDK-975:",
        /* testCaseId */
        10044u,
        /* testType */
        ST_TT_SANITY,
        /* runCount */
        ST_CAPT_RUN_COUNT,
        /* testDescStr */
#ifdef SOC_TDA2EX
        "OV1063x->VIP1_S1_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), Dual out - RGB888, YUV420SP",
#else
        "OV1063x->VIP1_S0_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), Dual out - RGB888, YUV420SP",
#endif
        /* testCaseType */
        ST_CAPT_TCT_MAIN,
        /* numHandles */
        1u,
        NULL,
        NULL,
        /* platformId */
        BSP_PLATFORM_ID_EVM,
        /* socId */
        BOARD_SOC_ID,
        /* boardId */
        (BSP_BOARD_GP_AM572X | BSP_BOARD_IDK_AM57XX | BSP_BOARD_VISION | BSP_BOARD_BASE_TDA3XX),
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_8BIT,
        /* startstpCnt */
        1,
        /* maxSizeRegs[VPS_VIP_MAX] */
        {
            /* VPS_VIP1 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX) || defined(SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_AM574x)
            /* VPS_VIP2 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX)
            /* VPS_VIP3 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            }
#endif
#endif
        },

        /* testInstPrms[VPS_CAPT_INST_MAX] */
        {
            /* instId[] */
            BOARD_MAKE_VIP_INST_ID,
            /* decDrvId[] */
            BOARD_VID_SENSOR_DRV_ID,
            /* standard */
            FVID2_STD_720P_60,
            /* videoIfMode */
            FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
            /* videoIfWidth */
            FVID2_VIFW_8BIT,
            /* bufCaptMode */
            VPS_CAPT_BCM_LAST_FRM_REPEAT,
            /* numCh */
            1u,
            /* numStream */
            2u,
            /* inWidth */
            1280u,
            /* inHeight */
            720u,
            /* inDataFmt */
            FVID2_DF_YUV422P,
            /* inScanFormat */
            FVID2_SF_PROGRESSIVE,
            /* inBPP */
            FVID2_BPP_BITS16,
            /* cropStartX */
            0u,
            /* cropStartY */
            0u,
            /* cropWidth */
            1280u,
            /* cropHeight */
            720u,
            /* nonLinear */
            SC_NONLINEAR_DISABLE,
            /* stripSize */
            0u,
            /* enableScAdvCfg */
            SC_ADVCFG_DISABLE,
            /* advCfg */
            NULL,
            /* cscCoeff */
            NULL,
            /* outStrmParams[VPS_CAPT_STREAM_ID_MAX] */
            {
                /* Stream #0 */
                {
                    /* outWidth */
                    1280u,
                    /* outHeight */
                    720u,
                    /* outDataFmt */
                    FVID2_DF_RGB24_888,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_DISABLE_ALL,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                },
                /* Stream #1 */
                {
                    /* outWidth */
                    1280u,
                    /* outHeight */
                    720u,
                    /* outDataFmt */
                    FVID2_DF_YUV420SP_UV,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_DISABLE_ALL,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                }
            }
        }
    },
    {
        /* testEnable */
        TEST_ENABLE,
        /* bufCaptModeTestEnable */
        BUF_CAPT_MODE_TEST_DISABLE,
        /* printEnable */
        PRINT_ENABLE,
        /* Software Requirement Id  */
        ":PDK-979:",
        /* testCaseId */
        10045u,
        /* testType */
        ST_TT_SANITY,
        /* runCount */
        ST_CAPT_RUN_COUNT,
        /* testDescStr */
#ifdef SOC_TDA2EX
        "OV1063x->VIP1_S1_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), Dual out - YUYV422I 800x480 Scaled out, YUV422SP",
#else
        "OV1063x->VIP1_S0_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), Dual out - YUYV422I 800x480 Scaled out, YUV422SP",
#endif
        /* testCaseType */
        ST_CAPT_TCT_MAIN,
        /* numHandles */
        1u,
        NULL,
        NULL,
        /* platformId */
        BSP_PLATFORM_ID_EVM,
        /* socId */
        BOARD_SOC_ID,
        /* boardId */
        (BSP_BOARD_GP_AM572X | BSP_BOARD_IDK_AM57XX | BSP_BOARD_VISION | BSP_BOARD_BASE_TDA3XX),
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_8BIT,
        /* startstpCnt */
        1,
        /* maxSizeRegs[VPS_VIP_MAX] */
        {
            /* VPS_VIP1 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX) || defined(SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_AM574x)
            /* VPS_VIP2 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX)
            /* VPS_VIP3 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            }
#endif
#endif
        },

        /* testInstPrms[VPS_CAPT_INST_MAX] */
        {
            /* instId[] */
            BOARD_MAKE_VIP_INST_ID,
            /* decDrvId[] */
            BOARD_VID_SENSOR_DRV_ID,
            /* standard */
            FVID2_STD_720P_60,
            /* videoIfMode */
            FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
            /* videoIfWidth */
            FVID2_VIFW_8BIT,
            /* bufCaptMode */
            VPS_CAPT_BCM_LAST_FRM_REPEAT,
            /* numCh */
            1u,
            /* numStream */
            2u,
            /* inWidth */
            1280u,
            /* inHeight */
            720u,
            /* inDataFmt */
            FVID2_DF_YUV422P,
            /* inScanFormat */
            FVID2_SF_PROGRESSIVE,
            /* inBPP */
            FVID2_BPP_BITS16,
            /* cropStartX */
            0u,
            /* cropStartY */
            0u,
            /* cropWidth */
            1280u,
            /* cropHeight */
            720u,
            /* nonLinear */
            SC_NONLINEAR_DISABLE,
            /* stripSize */
            0u,
            /* enableScAdvCfg */
            SC_ADVCFG_DISABLE,
            /* advCfg */
            NULL,
            /* cscCoeff */
            NULL,
            /* outStrmParams[VPS_CAPT_STREAM_ID_MAX] */
            {
                /* Stream #0 */
                {
                    /* outWidth */
                    800u,
                    /* outHeight */
                    480u,
                    /* outDataFmt */
                    FVID2_DF_YUV422I_YUYV,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_ENABLE_0,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                },
                /* Stream #1 */
                {
                    /* outWidth */
                    1280u,
                    /* outHeight */
                    720u,
                    /* outDataFmt */
                    FVID2_DF_YUV422SP_UV,
                    /* outScanFormat */
                    FVID2_SF_PROGRESSIVE,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_DISABLE_ALL,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                }
            }
        }
    },
    {
        /* testEnable */
        TEST_ENABLE,
        /* bufCaptModeTestEnable */
        BUF_CAPT_MODE_TEST_DISABLE,
        /* printEnable */
        PRINT_ENABLE,
        /* Software Requirement Id  */
        ":PDK-2217:",
        /* testCaseId */
        10046u,
        /* testType */
        ST_TT_SANITY,
        /* runCount */
        0U,
        /* testDescStr */
        "5-CH Driver Open Close use case",
        /* testCaseType */
        ST_CAPT_TCT_MAIN,
        /* numHandles */
        1u,
        NULL,
        NULL,
        /* platformId */
        BSP_PLATFORM_ID_EVM,
        /* socId */
        BOARD_SOC_ID,
        /* boardId */
        (BSP_BOARD_VISION | BSP_BOARD_BASE_TDA3XX),
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_BT656,
        /* startstpCnt */
        1,
        /* maxSizeRegs[VPS_VIP_MAX] */
        {
            /* VPS_VIP1 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX) || defined(SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_AM574x)
            /* VPS_VIP2 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX)
            /* VPS_VIP3 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            }
#endif
#endif
        },

        /* testInstPrms[VPS_CAPT_INST_MAX] */
        {
            /*instId */
            BOARD_MAKE_VIP_INST_ID,
            /* decDrvId[] */
            0U,
            /* standard */
            FVID2_STD_MUX_4CH_D1,
            /* videoIfMode */
            FVID2_VIFM_MCH_LINE_MUX_ES,
            /* videoIfWidth */
            FVID2_VIFW_8BIT,
            /* bufCaptMode */
            VPS_CAPT_BCM_LAST_FRM_REPEAT,
            /* numCh */
            5u,
            /* numStream */
            1u,
            /* inWidth */
            720u,
            /* inHeight */
            240u,
            /* inDataFmt */
            FVID2_DF_YUV422P,
            /* inScanFormat */
            FVID2_SF_INTERLACED,
            /* inBPP */
            FVID2_BPP_BITS16,
            /* cropStartX */
            0u,
            /* cropStartY */
            0u,
            /* cropWidth */
            720u,
            /* cropHeight */
            240u,
            /* nonLinear */
            SC_NONLINEAR_DISABLE,
            /* stripSize */
            0u,
            /* enableScAdvCfg */
            SC_ADVCFG_DISABLE,
            /* advCfg */
            NULL,
            /* cscCoeff */
            NULL,
            /* outStrmParams[VPS_CAPT_STREAM_ID_MAX] */
            {
                /* Stream #0 */
                {
                    /* outWidth */
                    720u,
                    /* outHeight */
                    240u,
                    /* outDataFmt */
                    FVID2_DF_YUV422I_YUYV,
                    /* outScanFormat */
                    FVID2_SF_INTERLACED,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_768_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_768_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_768_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_576_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_576_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_576_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_DISABLE_ALL,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                }
            }
        }
    },
    {
        /* testEnable */
        TEST_ENABLE,
        /* bufCaptModeTestEnable */
        BUF_CAPT_MODE_TEST_DISABLE,
        /* printEnable */
        PRINT_ENABLE,
        /* Software Requirement Id  */
        ":PDK-2217:",
        /* testCaseId */
        10046u,
        /* testType */
        ST_TT_SANITY,
        /* runCount */
        0U,
        /* testDescStr */
        "5-CH Driver Open Close use case",
        /* testCaseType */
        ST_CAPT_TCT_MAIN,
        /* numHandles */
        1u,
        NULL,
        NULL,
        /* platformId */
        BSP_PLATFORM_ID_EVM,
        /* socId */
        BOARD_SOC_ID,
        /* boardId */
        (BSP_BOARD_VISION | BSP_BOARD_BASE_TDA3XX),
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_BT656,
        /* startstpCnt */
        1,
        /* maxSizeRegs[VPS_VIP_MAX] */
        {
            /* VPS_VIP1 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX) || defined(SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_AM574x)
            /* VPS_VIP2 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            },
#if defined(SOC_TDA2XX)
            /* VPS_VIP3 */
            {
                /* maxSizeRegWidth[3] */
                {
                    1920u,
                    1920u,
                    1280u
                },
                /* maxSizeRegHeight[3] */
                {
                    1080u,
                    540u,
                    800u
                }
            }
#endif
#endif
        },

        /* testInstPrms[VPS_CAPT_INST_MAX] */
        {
            /*instId */
            BOARD_MAKE_VIP_INST_ID,
            /* decDrvId[] */
            0U,
            /* standard */
            FVID2_STD_MUX_4CH_D1,
            /* videoIfMode */
            FVID2_VIFM_MCH_LINE_MUX_ES,
            /* videoIfWidth */
            FVID2_VIFW_8BIT,
            /* bufCaptMode */
            VPS_CAPT_BCM_LAST_FRM_REPEAT,
            /* numCh */
            5u,
            /* numStream */
            1u,
            /* inWidth */
            720u,
            /* inHeight */
            240u,
            /* inDataFmt */
            FVID2_DF_YUV422P,
            /* inScanFormat */
            FVID2_SF_INTERLACED,
            /* inBPP */
            FVID2_BPP_BITS16,
            /* cropStartX */
            0u,
            /* cropStartY */
            0u,
            /* cropWidth */
            720u,
            /* cropHeight */
            240u,
            /* nonLinear */
            SC_NONLINEAR_DISABLE,
            /* stripSize */
            0u,
            /* enableScAdvCfg */
            SC_ADVCFG_DISABLE,
            /* advCfg */
            NULL,
            /* cscCoeff */
            NULL,
            /* outStrmParams[VPS_CAPT_STREAM_ID_MAX] */
            {
                /* Stream #0 */
                {
                    /* outWidth */
                    720u,
                    /* outHeight */
                    240u,
                    /* outDataFmt */
                    FVID2_DF_YUV422I_YUYV,
                    /* outScanFormat */
                    FVID2_SF_INTERLACED,
                    /* outBPP */
                    FVID2_BPP_BITS16,
                    /* bufFmt */
                    FVID2_BUF_FMT_FRAME,
                    /* memType */
                    VPS_VPDMA_MT_NONTILEDMEM,
                    /* maxOutWidth */
                    {
                        VPS_VPDMA_MAX_OUT_WIDTH_768_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_768_PIXELS,
                        VPS_VPDMA_MAX_OUT_WIDTH_768_PIXELS
                    },
                    /* maxOutHeight */
                    {
                        VPS_VPDMA_MAX_OUT_HEIGHT_576_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_576_LINES,
                        VPS_VPDMA_MAX_OUT_HEIGHT_576_LINES
                    },
                    /* scEnable */
                    ST_CAPT_SC_DISABLE_ALL,
                    /* subFrameEnable */
                    SUBFRM_DISABLE,
                    /* numSlicesPerFrame */
                    8,
                    /* frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX] */
                    {
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                        0x0, 0x0, 0x0, 0x0,
                    }
                }
            }
        }
    },
};

#if defined(__GNUC__) && !defined(__ti__)
#pragma GCC diagnostic pop
#endif

#endif /* #ifndef ST_CAPTURE_TEST_CASES_H_ */
