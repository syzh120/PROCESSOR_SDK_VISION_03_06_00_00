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
 *  \file Loopback_main.c
 *
 *  \brief Capture->Display loopback sample application main file.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <Loopback_priv.h>

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

static void LpbkApp_createTsk(void);
static void LpbkApp_tskReset(UArg arg0, UArg arg1);
static void LpbkApp_tskMain(UArg arg0, UArg arg1);

static void LpbkApp_init(LpbkApp_Obj *appObj);
static void LpbkApp_deInit(LpbkApp_Obj *appObj);

static Int32 LpbkApp_getTestId(LpbkApp_Obj *appObj);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Align stack memory to integer boundary. */
#if defined (__GNUC__) && !defined (__ti__)
DATA_ALIGN(32) DATA_SECTION(".bss:taskStackSection")
#else
#pragma DATA_ALIGN(gLpbkAppTskStackMain, 32)
/* Place the stack in stack section. */
#pragma DATA_SECTION(gLpbkAppTskStackMain, ".bss:taskStackSection")
#endif
/* Test application stack */
static UInt8 gLpbkAppTskStackMain[LPBK_APP_TSK_STACK_MAIN];

#if defined (__GNUC__) && !defined (__ti__)
DATA_ALIGN(32) DATA_SECTION(".bss:taskStackSection")
#else
/* Align stack memory to integer boundary. */
#pragma DATA_ALIGN(gLpbkAppTskStackReset, 32)
/* Place the stack in stack section. */
#pragma DATA_SECTION(gLpbkAppTskStackReset, ".bss:taskStackSection")
#endif
/* Test application stack */
static UInt8 gLpbkAppTskStackReset[LPBK_APP_TSK_STACK_MAIN];

/* Test application object */
static LpbkApp_Obj        gLpbkAppObj;

/* Task struct Object for static allocation */
static Task_Struct        gResetTskStruct;
static Task_Struct        gTskStruct;

static volatile UInt32    gExitApp;

static LpbkApp_TestParams gLpbkAppTestPrms[] =
{
    {
#if defined (SOC_TDA2EX) || defined (SOC_AM571x)
        "OV1063x            -> VIP1_S1_PORTA (1280x720@30FPS)  -> BGR888      -> DSS Video1 -> DPI1 LCD (DPI3 LCD for TDA2Ex_17x17)",
#else
        "OV1063x            -> VIP1_S0_PORTA (1280x720@30FPS)  -> BGR888      -> DSS Video1 -> DPI1 LCD",
#endif
        1U,                                         /* numCaptHandles */
        1U,                                         /* numDispHandles */
        /* captInstId[] */
        {
#if defined (SOC_TDA2EX) || defined (SOC_AM571x)
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
#else
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
#endif
        },
        /* dispInstId[] */
        {
            VPS_DISP_INST_DSS_VID1
        },

        /* decDrvId[] */
        {
            FVID2_VID_SENSOR_OV1063X_DRV,
        },
        /* encDrvId[] */
        {
            FVID2_LCD_CTRL_DRV,
        },
        /* vencId */
        {
            VPS_DCTRL_DSS_VENC_LCD1
        },
        FALSE,                                      /* isSdVenc */
        /* captStandard */
        FVID2_STD_720P_60,
        /* dispStandard */
        {
            FVID2_STD_CUSTOM,
        },

        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,           /* captVideoIfMode */
        FVID2_VIFW_8BIT,                         /* captVideoIfWidth */
        FVID2_SF_PROGRESSIVE,                    /* captScanFormat */
        FVID2_DF_YUV422P,                        /* captInDataFmt */
        FVID2_DF_BGR24_888,                      /* captOutDataFmt */

        LPBK_APP_SC_DISABLE_ALL,                 /* captScEnable */
        1280U,                                   /* captInWidth */
        720U,                                    /* captInHeight */
        1280U,                                   /* captOutWidth */
        720U,                                    /* captOutHeight */

        1280U,                                   /* dispInWidth */
        720U,                                    /* dispInHeight */
        LPBK_APP_USE_LCD_WIDTH,                  /* Target width */
        LPBK_APP_USE_LCD_HEIGHT,                 /* Target Height */

        LPBK_APP_RUN_COUNT,                      /* runCount */
        BSP_BOARD_MODE_VIDEO_8BIT,               /* captBoardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,              /* dispBoardMode */
        /* boardId */
        (BSP_BOARD_UNKNOWN | BSP_BOARD_BASE_TDA2XX | BSP_BOARD_BASE_TDA2PX | BSP_BOARD_VISION |
         BSP_BOARD_JAMR3 | BSP_BOARD_MULTIDES | BSP_BOARD_BASE_TDA3XX |
         BSP_BOARD_BASE_TDA2EX)
    },
    {
#if defined (SOC_TDA2EX) || defined (SOC_AM571x)
        "OV1063x            -> VIP1_S1_PORTA (1280x720@30FPS)  -> ARGB32_8888 -> DSS Video1 -> DPI1 LCD (DPI3 LCD for TDA2Ex_17x17)",
#else
        "OV1063x            -> VIP1_S0_PORTA (1280x720@30FPS)  -> ARGB32_8888 -> DSS Video1 -> DPI1 LCD",
#endif
        1U,                                         /* numCaptHandles */
        1U,                                         /* numDispHandles */
        /* captInstId[] */
        {
#if defined (SOC_TDA2EX) || defined (SOC_AM571x)
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
#else
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
#endif
        },
        /* dispInstId[] */
        {
            VPS_DISP_INST_DSS_VID1
        },

        /* decDrvId[] */
        {
            FVID2_VID_SENSOR_OV1063X_DRV,
        },
        /* encDrvId[] */
        {
            FVID2_LCD_CTRL_DRV,
        },
        /* vencId */
        {
            VPS_DCTRL_DSS_VENC_LCD1
        },
        FALSE,                                      /* isSdVenc */
        /* captStandard */
        FVID2_STD_720P_60,
        /* dispStandard */
        {
            FVID2_STD_CUSTOM,
        },

        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,             /* captVideoIfMode */
        FVID2_VIFW_8BIT,                           /* captVideoIfWidth */
        FVID2_SF_PROGRESSIVE,                      /* captScanFormat */
        FVID2_DF_YUV422P,                          /* captInDataFmt */
        FVID2_DF_ARGB32_8888,                      /* captOutDataFmt */

        LPBK_APP_SC_DISABLE_ALL,                   /* captScEnable */
        1280U,                                     /* captInWidth */
        720U,                                      /* captInHeight */
        1280U,                                     /* captOutWidth */
        720U,                                      /* captOutHeight */

        1280U,                                     /* dispInWidth */
        720U,                                      /* dispInHeight */
        LPBK_APP_USE_LCD_WIDTH,                    /* Target width */
        LPBK_APP_USE_LCD_HEIGHT,                   /* Target Height */

        LPBK_APP_RUN_COUNT,                        /* runCount */
        BSP_BOARD_MODE_VIDEO_8BIT,                 /* captBoardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,                /* dispBoardMode */
        /* boardId */
        (BSP_BOARD_UNKNOWN | BSP_BOARD_BASE_TDA2XX | BSP_BOARD_BASE_TDA2PX | BSP_BOARD_VISION |
         BSP_BOARD_JAMR3 | BSP_BOARD_MULTIDES | BSP_BOARD_BASE_TDA3XX |
         BSP_BOARD_BASE_TDA2EX)
    },
    {
#if defined (SOC_TDA2EX) || defined (SOC_AM571x)
        "OV1063x            -> VIP1_S1_PORTA (1280x720@30FPS)  -> YUV420SP    -> DSS Video1 -> DPI1 LCD (DPI3 LCD for TDA2Ex_17x17)",
#else
        "OV1063x            -> VIP1_S0_PORTA (1280x720@30FPS)  -> YUV420SP    -> DSS Video1 -> DPI1 LCD",
#endif
        1U,                                         /* numCaptHandles */
        1U,                                         /* numDispHandles */
        /* captInstId[] */
        {
#if defined (SOC_TDA2EX) || defined (SOC_AM571x)
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
#else
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
#endif
        },
        /* dispInstId[] */
        {
            VPS_DISP_INST_DSS_VID1
        },

        /* decDrvId[] */
        {
            FVID2_VID_SENSOR_OV1063X_DRV,
        },
        /* encDrvId[] */
        {
            FVID2_LCD_CTRL_DRV,
        },
        /* vencId */
        {
            VPS_DCTRL_DSS_VENC_LCD1
        },
        FALSE,                                      /* isSdVenc */
        /* captStandard */
        FVID2_STD_720P_60,
        /* dispStandard */
        {
            FVID2_STD_CUSTOM,
        },

        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,             /* captVideoIfMode */
        FVID2_VIFW_8BIT,                           /* captVideoIfWidth */
        FVID2_SF_PROGRESSIVE,                      /* captScanFormat */
        FVID2_DF_YUV422P,                          /* captInDataFmt */
        FVID2_DF_YUV420SP_UV,                      /* captOutDataFmt */

        LPBK_APP_SC_DISABLE_ALL,                   /* captScEnable */
        1280U,                                     /* captInWidth */
        720U,                                      /* captInHeight */
        1280U,                                     /* captOutWidth */
        720U,                                      /* captOutHeight */

        1280U,                                     /* dispInWidth */
        720U,                                      /* dispInHeight */
        LPBK_APP_USE_LCD_WIDTH,                    /* Target width */
        LPBK_APP_USE_LCD_HEIGHT,                   /* Target Height */

        LPBK_APP_RUN_COUNT,                        /* runCount */
        BSP_BOARD_MODE_VIDEO_8BIT,                 /* captBoardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,                /* dispBoardMode */
        /* boardId */
        (BSP_BOARD_UNKNOWN | BSP_BOARD_BASE_TDA2XX | BSP_BOARD_BASE_TDA2PX | BSP_BOARD_VISION |
         BSP_BOARD_JAMR3 | BSP_BOARD_MULTIDES | BSP_BOARD_BASE_TDA3XX |
         BSP_BOARD_BASE_TDA2EX)
    },
    {
#if defined (SOC_TDA2EX) || defined (SOC_AM571x)
        "OV1063x            -> VIP1_S1_PORTA (1280x720@30FPS)  -> DSS Video1 -> DPI1 LCD (DPI3 LCD for TDA2Ex_17x17)",
#else
        "OV1063x            -> VIP1_S0_PORTA (1280x720@30FPS)  -> DSS Video1 -> DPI1 LCD",
#endif
        1U,                                         /* numCaptHandles */
        1U,                                         /* numDispHandles */
        /* captInstId[] */
        {
#if defined (SOC_TDA2EX) || defined (SOC_AM571x)
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
#else
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
#endif
        },
        /* dispInstId[] */
        {
            VPS_DISP_INST_DSS_VID1
        },

        /* decDrvId[] */
        {
            FVID2_VID_SENSOR_OV1063X_DRV,
        },
        /* encDrvId[] */
        {
            FVID2_LCD_CTRL_DRV,
        },
        /* vencId */
        {
            VPS_DCTRL_DSS_VENC_LCD1
        },
        FALSE,                                      /* isSdVenc */
        /* captStandard */
        FVID2_STD_720P_60,
        /* dispStandard */
        {
            FVID2_STD_CUSTOM,
        },

        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,              /* captVideoIfMode */
        FVID2_VIFW_8BIT,                            /* captVideoIfWidth */
        FVID2_SF_PROGRESSIVE,                       /* captScanFormat */
        FVID2_DF_YUV422P,                           /* captInDataFmt */
        FVID2_DF_YUV422I_YUYV,                      /* captOutDataFmt */

        LPBK_APP_SC_DISABLE_ALL,                    /* captScEnable */
        1280U,                                      /* captInWidth */
        720U,                                       /* captInHeight */
        1280U,                                      /* captOutWidth */
        720U,                                       /* captOutHeight */

        1280U,                                      /* dispInWidth */
        720U,                                       /* dispInHeight */
        LPBK_APP_USE_LCD_WIDTH,                     /* Target width */
        LPBK_APP_USE_LCD_HEIGHT,                    /* Target Height */

        LPBK_APP_RUN_COUNT,                         /* runCount */
        BSP_BOARD_MODE_VIDEO_8BIT,                  /* captBoardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,                 /* dispBoardMode */
        /* boardId */
        (BSP_BOARD_VISION | BSP_BOARD_MULTIDES | BSP_BOARD_BASE_TDA3XX)
    },
#if defined (SOC_TDA3XX)
    {
        "OV1063x            -> VIP1_S0_PORTA (1280x720@30FPS)  -> DSS Video1 -> DPI -> SDVENC (NTSC)",
        1U,                                         /* numCaptHandles */
        1U,                                         /* numDispHandles */
        /* captInstId[] */
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
        },
        /* dispInstId[] */
        {
            VPS_DISP_INST_DSS_VID1
        },

        /* decDrvId[] */
        {
            FVID2_VID_SENSOR_OV1063X_DRV,
        },
        /* encDrvId[] */
        {
            0,
        },
        /* vencId */
        {
            VPS_DCTRL_DSS_VENC_LCD1
        },
        TRUE,                                       /* isSdVenc */
        /* captStandard */
        FVID2_STD_720P_60,
        /* dispStandard */
        {
            FVID2_STD_NTSC,
        },

        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,              /* captVideoIfMode */
        FVID2_VIFW_8BIT,                            /* captVideoIfWidth */
        FVID2_SF_PROGRESSIVE,                       /* captScanFormat */
        FVID2_DF_YUV422P,                           /* captInDataFmt */
        FVID2_DF_YUV422I_YUYV,                      /* captOutDataFmt */

        LPBK_APP_SC_DISABLE_ALL,                    /* captScEnable */
        1280U,                                      /* captInWidth */
        720U,                                       /* captInHeight */
        1280U,                                      /* captOutWidth */
        720U,                                       /* captOutHeight */

        1280U,                                      /* dispInWidth */
        720U,                                       /* dispInHeight */
        720U,                                       /* Target width */
        480U,                                       /* Target Height */

        LPBK_APP_RUN_COUNT,                         /* runCount */
        BSP_BOARD_MODE_VIDEO_8BIT,                  /* captBoardMode */
        BSP_BOARD_MODE_DEFAULT,                     /* dispBoardMode */
        /* boardId */
        (BSP_BOARD_BASE_TDA3XX | BSP_BOARD_MULTIDES)
    },
    {
        "OV1063x            -> VIP1_S0_PORTA (1280x720@30FPS)  -> DSS Video1 -> DPI1 ->SIL9022A HDMI @720P60",
        1U,                                         /* numCaptHandles */
        1U,                                         /* numDispHandles */

        /* captInstId[] */
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
        },
        /* dispInstId[] */
        {
            VPS_DISP_INST_DSS_VID1
        },

        /* decDrvId[] */
        {
            FVID2_VID_SENSOR_OV1063X_DRV,
        },
        /* encDrvId[] */
        {
            FVID2_VID_ENC_SII9022A_DRV,
        },
        /* vencId */
        {
            VPS_DCTRL_DSS_VENC_LCD1
        },
        FALSE,                                      /* isSdVenc */
        /* captStandard */
        FVID2_STD_720P_60,
        /* dispStandard */
        {
            FVID2_STD_720P_60,
        },

        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,              /* captVideoIfMode */
        FVID2_VIFW_8BIT,                            /* captVideoIfWidth */
        FVID2_SF_PROGRESSIVE,                       /* captScanFormat */
        FVID2_DF_YUV422P,                           /* captInDataFmt */
        FVID2_DF_YUV422I_YUYV,                      /* captOutDataFmt */

        LPBK_APP_SC_DISABLE_ALL,                    /* captScEnable */
        1280U,                                      /* captInWidth */
        720U,                                       /* captInHeight */
        1280U,                                      /* captOutWidth */
        720U,                                       /* captOutHeight */

        1280U,                                      /* dispInWidth */
        720U,                                       /* dispInHeight */
        1280U,                                      /* Target width */
        720U,                                       /* Target Height */

        LPBK_APP_RUN_COUNT,                         /* runCount */
        BSP_BOARD_MODE_VIDEO_8BIT,                  /* captBoardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,                 /* dispBoardMode */
        /* boardId */
        (BSP_BOARD_BASE_TDA3XX | BSP_BOARD_MULTIDES)
    },
#endif
    {
#if defined (SOC_TDA2EX) || defined (SOC_AM571x)
        "LI OV1063x         -> VIP1_S1_PORTA (1280x720@30FPS)  -> DSS Video1 -> DPI1 LCD (DPI3 LCD for TDA2Ex_17x17)",
#else
        "LI OV1063x         -> VIP1_S0_PORTA (1280x720@30FPS)  -> DSS Video1 -> DPI1 LCD",
#endif
        1U,                                         /* numCaptHandles */
        1U,                                         /* numDispHandles */

        /* captInstId[] */
        {
#if defined (SOC_TDA2EX) || defined (SOC_AM571x)
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
#else
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
#endif
        },
        /* dispInstId[] */
        {
            VPS_DISP_INST_DSS_VID1
        },

        /* decDrvId[] */
        {
            FVID2_VID_SENSOR_LI_OV1063X_DRV,
        },
        /* encDrvId[] */
        {
            FVID2_LCD_CTRL_DRV,
        },
        /* vencId */
        {
            VPS_DCTRL_DSS_VENC_LCD1
        },
        FALSE,                                      /* isSdVenc */
        /* captStandard */
        FVID2_STD_720P_60,
        /* dispStandard */
        {
            FVID2_STD_CUSTOM,
        },

        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,              /* captVideoIfMode */
        FVID2_VIFW_8BIT,                            /* captVideoIfWidth */
        FVID2_SF_PROGRESSIVE,                       /* captScanFormat */
        FVID2_DF_YUV422P,                           /* captInDataFmt */
        FVID2_DF_YUV422I_YUYV,                      /* captOutDataFmt */

        LPBK_APP_SC_DISABLE_ALL,                    /* captScEnable */
        1280U,                                      /* captInWidth */
        720U,                                       /* captInHeight */
        1280U,                                      /* captOutWidth */
        720U,                                       /* captOutHeight */

        1280U,                                      /* dispInWidth */
        720U,                                       /* dispInHeight */
        LPBK_APP_USE_LCD_WIDTH,                     /* Target width */
        LPBK_APP_USE_LCD_HEIGHT,                    /* Target Height */

        LPBK_APP_RUN_COUNT,                         /* runCount */
        BSP_BOARD_MODE_VIDEO_8BIT,                  /* captBoardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,                 /* dispBoardMode */
        /* boardId */
        (BSP_BOARD_BASE_TDA2XX | BSP_BOARD_BASE_TDA2PX | BSP_BOARD_VISION | BSP_BOARD_JAMR3 |
         BSP_BOARD_MULTIDES | BSP_BOARD_BASE_TDA3XX | BSP_BOARD_BASE_TDA2EX)
    },
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x)
    {
#if defined (SOC_TDA2EX) || defined (SOC_AM571x)
        "SII9127            -> VIP1_S1_PORTA (1280x720@30FPS)  -> DSS Video1 -> DPI1 LCD (DPI3 LCD for TDA2Ex_17x17)",
#else
        "SII9127            -> VIP1_S0_PORTA (1280x720@30FPS)  -> DSS Video1 -> DPI1 LCD",
#endif
        1U,                                         /* numCaptHandles */
        1U,                                         /* numDispHandles */

        /* captInstId[] */
        {
#if defined (SOC_TDA2EX) || defined (SOC_AM571x)
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
#else
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
#endif
        },
        /* dispInstId[] */
        {
            VPS_DISP_INST_DSS_VID1
        },

        /* decDrvId[] */
        {
            FVID2_VID_DEC_SII9127_DRV,
        },
        /* encDrvId[] */
        {
            FVID2_LCD_CTRL_DRV,
        },
        /* vencId */
        {
            VPS_DCTRL_DSS_VENC_LCD1
        },
        FALSE,                                      /* isSdVenc */
        /* captStandard */
        FVID2_STD_CUSTOM,
        /* dispStandard */
        {
            FVID2_STD_CUSTOM,
        },

        FVID2_VIFM_SCH_DS_AVID_VSYNC,               /* captVideoIfMode */
        FVID2_VIFW_16BIT,                           /* captVideoIfWidth */
        FVID2_SF_PROGRESSIVE,                       /* captScanFormat */
        FVID2_DF_YUV422P,                           /* captInDataFmt */
        FVID2_DF_YUV422I_YUYV,                      /* captOutDataFmt */

        LPBK_APP_SC_DISABLE_ALL,                    /* captScEnable */
        1280U,                                      /* captInWidth */
        720U,                                       /* captInHeight */
        1280U,                                      /* captOutWidth */
        720U,                                       /* captOutHeight */

        1280U,                                      /* dispInWidth */
        720U,                                       /* dispInHeight */
        LPBK_APP_USE_LCD_WIDTH,                     /* Target width */
        LPBK_APP_USE_LCD_HEIGHT,                    /* Target Height */

        LPBK_APP_RUN_COUNT,                         /* runCount */
        BSP_BOARD_MODE_VIDEO_16BIT,                 /* captBoardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,                 /* dispBoardMode */
        /* Note: Can't run in muldes board because of I2C conflict */
        (BSP_BOARD_VISION)
    },
    {
#if defined (SOC_TDA2EX) || defined (SOC_AM571x)
        "SII9127            -> VIP1_S1_PORTA (1920x1080@60FPS) -> DSS Video1 -> DPI1 LCD (DPI3 LCD for TDA2Ex_17x17)",
#else
        "SII9127            -> VIP1_S0_PORTA (1920x1080@60FPS) -> DSS Video1 -> DPI1 LCD",
#endif
        1U,                                         /* numCaptHandles */
        1U,                                         /* numDispHandles */

        /* captInstId[] */
        {
#if defined (SOC_TDA2EX) || defined (SOC_AM571x)
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
#else
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
#endif
        },
        /* dispInstId[] */
        {
            VPS_DISP_INST_DSS_VID1
        },

        /* decDrvId[] */
        {
            FVID2_VID_DEC_SII9127_DRV,
        },
        /* encDrvId[] */
        {
            FVID2_LCD_CTRL_DRV,
        },
        /* vencId */
        {
            VPS_DCTRL_DSS_VENC_LCD1
        },
        FALSE,                                      /* isSdVenc */
        /* captStandard */
        FVID2_STD_CUSTOM,
        /* dispStandard */
        {
            FVID2_STD_CUSTOM,
        },

        FVID2_VIFM_SCH_DS_AVID_VSYNC,               /* captVideoIfMode */
        FVID2_VIFW_16BIT,                           /* captVideoIfWidth */
        FVID2_SF_PROGRESSIVE,                       /* captScanFormat */
        FVID2_DF_YUV422P,                           /* captInDataFmt */
        FVID2_DF_YUV422I_YUYV,                      /* captOutDataFmt */

        LPBK_APP_SC_DISABLE_ALL,                    /* captScEnable */
        1920U,                                      /* captInWidth */
        1080U,                                      /* captInHeight */
        1920U,                                      /* captOutWidth */
        1080U,                                      /* captOutHeight */

        1920,                                       /* dispInWidth */
        1080,                                       /* dispInHeight */
        LPBK_APP_USE_LCD_WIDTH,                     /* Target width */
        LPBK_APP_USE_LCD_HEIGHT,                    /* Target Height */

        LPBK_APP_RUN_COUNT,                         /* runCount */
        BSP_BOARD_MODE_VIDEO_16BIT,                 /* captBoardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,                 /* dispBoardMode */
        /* Note: Can't run in muldes board because of I2C conflict */
        (BSP_BOARD_VISION)
    },
#endif
    {
#if defined (SOC_TDA2EX) || defined (SOC_AM571x)
        "ADV7611            -> VIP1_S1_PORTA (1920x1080@60FPS) -> DSS Video1 -> DPI1 LCD (DPI3 LCD for TDA2Ex_17x17)",
#else
        "ADV7611            -> VIP1_S0_PORTA (1920x1080@60FPS) -> DSS Video1 -> DPI1 LCD",
#endif
        1U,                                         /* numCaptHandles */
        1U,                                         /* numDispHandles */

        /* captInstId[] */
        {
#if defined (SOC_TDA2EX) || defined (SOC_AM571x)
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
#else
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
#endif
        },
        /* dispInstId[] */
        {
            VPS_DISP_INST_DSS_VID1
        },

        /* decDrvId[] */
        {
            FVID2_VID_DEC_ADV7611_DRV,
        },
        /* encDrvId[] */
        {
            FVID2_LCD_CTRL_DRV,
        },
        /* vencId */
        {
            VPS_DCTRL_DSS_VENC_LCD1
        },
        FALSE,                                      /* isSdVenc */
        /* captStandard */
        FVID2_STD_CUSTOM,
        /* dispStandard */
        {
            FVID2_STD_CUSTOM,
        },

        FVID2_VIFM_SCH_DS_AVID_VSYNC,               /* captVideoIfMode */
        FVID2_VIFW_16BIT,                           /* captVideoIfWidth */
        FVID2_SF_PROGRESSIVE,                       /* captScanFormat */
        FVID2_DF_YUV422P,                           /* captInDataFmt */
        FVID2_DF_YUV422I_YUYV,                      /* captOutDataFmt */

        LPBK_APP_SC_DISABLE_ALL,                    /* captScEnable */
        1920U,                                      /* captInWidth */
        1080U,                                      /* captInHeight */
        1920U,                                      /* captOutWidth */
        1080U,                                      /* captOutHeight */

        1920,                                       /* dispInWidth */
        1080,                                       /* dispInHeight */
        LPBK_APP_USE_LCD_WIDTH,                     /* Target width */
        LPBK_APP_USE_LCD_HEIGHT,                    /* Target Height */

        LPBK_APP_RUN_COUNT,                         /* runCount */
        BSP_BOARD_MODE_VIDEO_16BIT,                 /* captBoardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,                 /* dispBoardMode */
        /* Note: Can't run in muldes board because of I2C conflict */
        (BSP_BOARD_VISION | BSP_BOARD_BASE_TDA3XX | BSP_BOARD_MULTIDES)
    },
    {
#if defined (SOC_TDA2EX) || defined (SOC_AM571x)
        "MULDESCAM1_OV1063x -> VIP1_S1_PORTA (1280x720@30FPS)  -> DSS Video1 -> DPI1 LCD (on-chip HDMI for TDA2Ex_17x17)",
#else
        "MULDESCAM1_OV1063x -> VIP1_S0_PORTA (1280x720@30FPS)  -> DSS Video1 -> DPI1 LCD",
#endif  /* #if defined (SOC_TDA2EX) || defined (SOC_AM571x) */
        1U,                                         /* numCaptHandles */
        1U,                                         /* numDispHandles */

        /* captInstId[] */
        {
#if defined (SOC_TDA2EX) || defined (SOC_AM571x)
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
#else
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
#endif      /* #if defined (SOC_TDA2EX) || defined (SOC_AM571x) */
        },
        /* dispInstId[] */
        {
            VPS_DISP_INST_DSS_VID1
        },

        /* decDrvId[] */
        {
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
        },
        /* encDrvId[] */
        {
            FVID2_LCD_CTRL_DRV,
        },
        /* vencId */
        {
            VPS_DCTRL_DSS_VENC_LCD1
        },
        FALSE,                                      /* isSdVenc */
        /* captStandard */
        FVID2_STD_720P_60,
        /* dispStandard */
        {
            FVID2_STD_CUSTOM,
        },

        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,              /* captVideoIfMode */
        FVID2_VIFW_8BIT,                            /* captVideoIfWidth */
        FVID2_SF_PROGRESSIVE,                       /* captScanFormat */
        FVID2_DF_YUV422P,                           /* captInDataFmt */
        FVID2_DF_YUV422I_YUYV,                      /* captOutDataFmt */

        LPBK_APP_SC_DISABLE_ALL,                    /* captScEnable */
        1280U,                                      /* captInWidth */
        720U,                                       /* captInHeight */
        1280U,                                      /* captOutWidth */
        720U,                                       /* captOutHeight */

        1280U,                                      /* dispInWidth */
        720U,                                       /* dispInHeight */
        LPBK_APP_USE_LCD_WIDTH,                     /* Target width */
        LPBK_APP_USE_LCD_HEIGHT,                    /* Target Height */

        LPBK_APP_RUN_COUNT,                         /* runCount */
        BSP_BOARD_MODE_VIDEO_8BIT,                  /* captBoardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,                 /* dispBoardMode */
        /* boardId */
        (BSP_BOARD_MULTIDES)
    },
    {
#if defined (SOC_TDA3XX)
        "MULDESCAM2_OV1063x -> VIP1_S0_PORTB (1280x720@30FPS)  -> DSS Video1 -> DPI1 LCD",
#elif defined (SOC_TDA2EX) || defined (SOC_AM571x)
        "MULDESCAM2_OV1063x -> VIP1_S0_PORTA (1280x720@30FPS)  -> DSS Video1 -> DPI1 LCD (on-chip HDMI for TDA2Ex_17x17)",
#else
        "MULDESCAM2_OV1063x -> VIP1_S1_PORTA (1280x720@30FPS)  -> DSS Video1 -> DPI1 LCD",
#endif
        1U,                                         /* numCaptHandles */
        1U,                                         /* numDispHandles */

        /* captInstId[] */
        {
#if defined (SOC_TDA3XX)
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTB),
#elif defined (SOC_TDA2EX) || defined (SOC_AM571x)
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
#else
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
#endif
        },
        /* dispInstId[] */
        {
            VPS_DISP_INST_DSS_VID1
        },

        /* decDrvId[] */
        {
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
        },
        /* encDrvId[] */
        {
            FVID2_LCD_CTRL_DRV,
        },
        /* vencId */
        {
            VPS_DCTRL_DSS_VENC_LCD1
        },
        FALSE,                                      /* isSdVenc */
        /* captStandard */
        FVID2_STD_720P_60,
        /* dispStandard */
        {
            FVID2_STD_CUSTOM,
        },

        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,              /* captVideoIfMode */
        FVID2_VIFW_8BIT,                            /* captVideoIfWidth */
        FVID2_SF_PROGRESSIVE,                       /* captScanFormat */
        FVID2_DF_YUV422P,                           /* captInDataFmt */
        FVID2_DF_YUV422I_YUYV,                      /* captOutDataFmt */

        LPBK_APP_SC_DISABLE_ALL,                    /* captScEnable */
        1280U,                                      /* captInWidth */
        720U,                                       /* captInHeight */
        1280U,                                      /* captOutWidth */
        720U,                                       /* captOutHeight */

        1280U,                                      /* dispInWidth */
        720U,                                       /* dispInHeight */
        LPBK_APP_USE_LCD_WIDTH,                     /* Target width */
        LPBK_APP_USE_LCD_HEIGHT,                    /* Target Height */

        LPBK_APP_RUN_COUNT,                         /* runCount */
        BSP_BOARD_MODE_VIDEO_8BIT,                  /* captBoardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,                 /* dispBoardMode */
        /* boardId */
        (BSP_BOARD_MULTIDES)
    },
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x)
    {
#if defined (SOC_TDA2EX) || defined (SOC_AM571x)
        "MULDES_OV1063x(RevA/B:CAM3 Else:CAM4) -> VIP1_S1_PORTB (1280x720@30FPS)  -> DSS Video1 -> DPI1 LCD (on-chip HDMI for TDA2Ex_17x17)",
#else
        "MULDESCAM3_OV1063x -> VIP2_S0_PORTA (1280x720@30FPS)  -> DSS Video1 -> DPI1 LCD",
#endif  /* #if defined (SOC_TDA2EX) || defined (SOC_AM571x) */
        1U,                                         /* numCaptHandles */
        1U,                                         /* numDispHandles */

        /* captInstId[] */
        {
#if defined (SOC_TDA2EX) || defined (SOC_AM571x)
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTB),
#else
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S0, VPS_VIP_PORTA),
#endif      /* #if defined (SOC_TDA2EX) || defined (SOC_AM571x) */
        },
        /* dispInstId[] */
        {
            VPS_DISP_INST_DSS_VID1
        },

        /* decDrvId[] */
        {
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
        },
        /* encDrvId[] */
        {
            FVID2_LCD_CTRL_DRV,
        },
        /* vencId */
        {
            VPS_DCTRL_DSS_VENC_LCD1
        },
        FALSE,                                      /* isSdVenc */
        /* captStandard */
        FVID2_STD_720P_60,
        /* dispStandard */
        {
            FVID2_STD_CUSTOM,
        },

        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,              /* captVideoIfMode */
        FVID2_VIFW_8BIT,                            /* captVideoIfWidth */
        FVID2_SF_PROGRESSIVE,                       /* captScanFormat */
        FVID2_DF_YUV422P,                           /* captInDataFmt */
        FVID2_DF_YUV422I_YUYV,                      /* captOutDataFmt */

        LPBK_APP_SC_DISABLE_ALL,                    /* captScEnable */
        1280U,                                      /* captInWidth */
        720U,                                       /* captInHeight */
        1280U,                                      /* captOutWidth */
        720U,                                       /* captOutHeight */

        1280U,                                      /* dispInWidth */
        720U,                                       /* dispInHeight */
        LPBK_APP_USE_LCD_WIDTH,                     /* Target width */
        LPBK_APP_USE_LCD_HEIGHT,                    /* Target Height */

        LPBK_APP_RUN_COUNT,                         /* runCount */
        BSP_BOARD_MODE_VIDEO_8BIT,                  /* captBoardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,                 /* dispBoardMode */
        /* boardId */
        (BSP_BOARD_MULTIDES)
    },
    {
#if defined (SOC_TDA2EX) || defined (SOC_AM571x)
        "MULDES_OV1063x(RevA/B:CAM4 Else:CAM5) -> VIP1_S0_PORTB (1280x720@30FPS)  -> DSS Video1 -> DPI1 LCD (on-chip HDMI for TDA2Ex_17x17)",
#elif defined (SOC_TDA2PX) || defined (SOC_AM574x)
        "MULDESCAM4_OV1063x -> VIP1_S1_PORTB (1280x720@30FPS)  -> DSS Video1 -> DPI1 LCD",
#else
        "MULDESCAM4_OV1063x -> VIP3_S0_PORTA (1280x720@30FPS)  -> DSS Video1 -> DPI1 LCD",
#endif  /* #if defined (SOC_TDA2EX) || defined (SOC_AM571x) */
        1U,                                         /* numCaptHandles */
        1U,                                         /* numDispHandles */

        /* captInstId[] */
        {
#if defined (SOC_TDA2EX) || defined (SOC_AM571x)
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTB),
#elif defined (SOC_TDA2PX) || defined (SOC_AM574x)
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTB),
#else
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP3, VPS_VIP_S0, VPS_VIP_PORTA),
#endif      /* #if defined (SOC_TDA2EX) || defined (SOC_AM571x) */
        },
        /* dispInstId[] */
        {
            VPS_DISP_INST_DSS_VID1
        },

        /* decDrvId[] */
        {
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
        },
        /* encDrvId[] */
        {
            FVID2_LCD_CTRL_DRV,
        },
        /* vencId */
        {
            VPS_DCTRL_DSS_VENC_LCD1
        },
        FALSE,                                      /* isSdVenc */
        /* captStandard */
        FVID2_STD_720P_60,
        /* dispStandard */
        {
            FVID2_STD_CUSTOM,
        },

        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,              /* captVideoIfMode */
        FVID2_VIFW_8BIT,                            /* captVideoIfWidth */
        FVID2_SF_PROGRESSIVE,                       /* captScanFormat */
        FVID2_DF_YUV422P,                           /* captInDataFmt */
        FVID2_DF_YUV422I_YUYV,                      /* captOutDataFmt */

        LPBK_APP_SC_DISABLE_ALL,                    /* captScEnable */
        1280U,                                      /* captInWidth */
        720U,                                       /* captInHeight */
        1280U,                                      /* captOutWidth */
        720U,                                       /* captOutHeight */

        1280U,                                      /* dispInWidth */
        720U,                                       /* dispInHeight */
        LPBK_APP_USE_LCD_WIDTH,                     /* Target width */
        LPBK_APP_USE_LCD_HEIGHT,                    /* Target Height */

        LPBK_APP_RUN_COUNT,                         /* runCount */
        BSP_BOARD_MODE_VIDEO_8BIT,                  /* captBoardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,                 /* dispBoardMode */
        /* boardId */
        (BSP_BOARD_MULTIDES)
    },
#endif
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x)
    {
        "MULDESCAM5_OV1063x -> VIP2_S1_PORTB (1280x720@30FPS)  -> DSS Video1 -> DPI1 LCD",
        1U,                                         /* numCaptHandles */
        1U,                                         /* numDispHandles */

        /* captInstId[] */
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S1, VPS_VIP_PORTB),
        },
        /* dispInstId[] */
        {
            VPS_DISP_INST_DSS_VID1
        },

        /* decDrvId[] */
        {
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
        },
        /* encDrvId[] */
        {
            FVID2_LCD_CTRL_DRV,
        },
        /* vencId */
        {
            VPS_DCTRL_DSS_VENC_LCD1
        },
        FALSE,                                      /* isSdVenc */
        /* captStandard */
        FVID2_STD_720P_60,
        /* dispStandard */
        {
            FVID2_STD_CUSTOM,
        },

        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,              /* captVideoIfMode */
        FVID2_VIFW_8BIT,                            /* captVideoIfWidth */
        FVID2_SF_PROGRESSIVE,                       /* captScanFormat */
        FVID2_DF_YUV422P,                           /* captInDataFmt */
        FVID2_DF_YUV422I_YUYV,                      /* captOutDataFmt */

        LPBK_APP_SC_DISABLE_ALL,                    /* captScEnable */
        1280U,                                      /* captInWidth */
        720U,                                       /* captInHeight */
        1280U,                                      /* captOutWidth */
        720U,                                       /* captOutHeight */

        1280U,                                      /* dispInWidth */
        720U,                                       /* dispInHeight */
        LPBK_APP_USE_LCD_WIDTH,                     /* Target width */
        LPBK_APP_USE_LCD_HEIGHT,                    /* Target Height */

        LPBK_APP_RUN_COUNT,                         /* runCount */
        BSP_BOARD_MODE_VIDEO_8BIT,                  /* captBoardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,                 /* dispBoardMode */
        /* boardId */
        (BSP_BOARD_MULTIDES)
    },
#endif
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
    {
        "MULDESCAM6_OV1063x -> VIP3_S1_PORTA (1280x720@30FPS)  -> DSS Video1 -> DPI1 LCD",
        1U,                                         /* numCaptHandles */
        1U,                                         /* numDispHandles */

        /* captInstId[] */
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP3, VPS_VIP_S1, VPS_VIP_PORTA),
        },
        /* dispInstId[] */
        {
            VPS_DISP_INST_DSS_VID1
        },

        /* decDrvId[] */
        {
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
        },
        /* encDrvId[] */
        {
            FVID2_LCD_CTRL_DRV,
        },
        /* vencId */
        {
            VPS_DCTRL_DSS_VENC_LCD1
        },
        FALSE,                                      /* isSdVenc */
        /* captStandard */
        FVID2_STD_720P_60,
        /* dispStandard */
        {
            FVID2_STD_CUSTOM,
        },

        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,              /* captVideoIfMode */
        FVID2_VIFW_8BIT,                            /* captVideoIfWidth */
        FVID2_SF_PROGRESSIVE,                       /* captScanFormat */
        FVID2_DF_YUV422P,                           /* captInDataFmt */
        FVID2_DF_YUV422I_YUYV,                      /* captOutDataFmt */

        LPBK_APP_SC_DISABLE_ALL,                    /* captScEnable */
        1280U,                                      /* captInWidth */
        720U,                                       /* captInHeight */
        1280U,                                      /* captOutWidth */
        720U,                                       /* captOutHeight */

        1280U,                                      /* dispInWidth */
        720U,                                       /* dispInHeight */
        LPBK_APP_USE_LCD_WIDTH,                     /* Target width */
        LPBK_APP_USE_LCD_HEIGHT,                    /* Target Height */

        LPBK_APP_RUN_COUNT,                         /* runCount */
        BSP_BOARD_MODE_VIDEO_8BIT,                  /* captBoardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,                 /* dispBoardMode */
        /* boardId */
        (BSP_BOARD_MULTIDES)
    },
#endif
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x)
    {
#if defined (SOC_TDA2EX)
        "MULDES (RevA/B:CAM1,2,3,4 Else:CAM1,2,4,5) -> VIP -> DSS Video1 -> DPI1 LCD (on-chip HDMI for TDA2Ex_17x17)",
#else
        "MULDESCAM1to4 -> VIP -> DSS Video1 -> DPI1 LCD",
#endif
        4U,                                         /* numCaptHandles */
        1U,                                         /* numDispHandles */

        /* captInstId[] */
        {
#if defined (SOC_TDA2EX) || defined (SOC_AM571x)
            /*
             * CAM1->VIP1_S1_PORTA, CAM2->VIP1_S0_PORTA,
             * CAM3->VIP1_S1_PORTB, CAM4->VIP1_S0_PORTB
             */
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTB),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTB),
#else
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S0, VPS_VIP_PORTA),
#if defined (SOC_TDA2PX) || defined (SOC_AM574x)
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTB),
#else
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP3, VPS_VIP_S0, VPS_VIP_PORTA),
#endif
#endif      /* #if defined (SOC_TDA2EX) || defined (SOC_AM571x) */
        },
        /* dispInstId[] */
        {
            VPS_DISP_INST_DSS_VID1
        },

        /* decDrvId[] */
        {
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
        },
        /* encDrvId[] */
        {
            FVID2_LCD_CTRL_DRV,
        },
        /* vencId */
        {
            VPS_DCTRL_DSS_VENC_LCD1
        },
        FALSE,                                      /* isSdVenc */
        /* captStandard */
        FVID2_STD_720P_60,
        /* dispStandard */
        {
            FVID2_STD_CUSTOM,
        },

        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,              /* captVideoIfMode */
        FVID2_VIFW_8BIT,                            /* captVideoIfWidth */
        FVID2_SF_PROGRESSIVE,                       /* captScanFormat */
        FVID2_DF_YUV422P,                           /* captInDataFmt */
        FVID2_DF_YUV422I_YUYV,                      /* captOutDataFmt */

        LPBK_APP_SC_DISABLE_ALL,                    /* captScEnable */
        1280U,                                      /* captInWidth */
        720U,                                       /* captInHeight */
        1280U,                                      /* captOutWidth */
        720U,                                       /* captOutHeight */

        1280U,                                      /* dispInWidth */
        720U,                                       /* dispInHeight */
        LPBK_APP_USE_LCD_WIDTH,                     /* Target width */
        LPBK_APP_USE_LCD_HEIGHT,                    /* Target Height */

        LPBK_APP_RUN_COUNT,                         /* runCount */
        BSP_BOARD_MODE_VIDEO_8BIT,                  /* captBoardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,                 /* dispBoardMode */
        /* boardId */
        (BSP_BOARD_MULTIDES)
    },
#endif
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
    {
        "MULDESCAM1to6      -> VIP                             -> DSS Video1 -> DPI1 LCD",
        6U,                                         /* numCaptHandles */
        1U,                                         /* numDispHandles */

        /* captInstId[] */
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S0, VPS_VIP_PORTA),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP3, VPS_VIP_S0, VPS_VIP_PORTA),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S1, VPS_VIP_PORTB),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP3, VPS_VIP_S1, VPS_VIP_PORTA),
        },
        /* dispInstId[] */
        {
            VPS_DISP_INST_DSS_VID1
        },

        /* decDrvId[] */
        {
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
        },
        /* encDrvId[] */
        {
            FVID2_LCD_CTRL_DRV,
        },
        /* vencId */
        {
            VPS_DCTRL_DSS_VENC_LCD1
        },
        FALSE,                                      /* isSdVenc */
        /* captStandard */
        FVID2_STD_720P_60,
        /* dispStandard */
        {
            FVID2_STD_CUSTOM,
        },

        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,              /* captVideoIfMode */
        FVID2_VIFW_8BIT,                            /* captVideoIfWidth */
        FVID2_SF_PROGRESSIVE,                       /* captScanFormat */
        FVID2_DF_YUV422P,                           /* captInDataFmt */
        FVID2_DF_YUV422I_YUYV,                      /* captOutDataFmt */

        LPBK_APP_SC_DISABLE_ALL,                    /* captScEnable */
        1280U,                                      /* captInWidth */
        720U,                                       /* captInHeight */
        1280U,                                      /* captOutWidth */
        720U,                                       /* captOutHeight */

        1280U,                                      /* dispInWidth */
        720U,                                       /* dispInHeight */
        LPBK_APP_USE_LCD_WIDTH,                     /* Target width */
        LPBK_APP_USE_LCD_HEIGHT,                    /* Target Height */

        LPBK_APP_RUN_COUNT,                         /* runCount */
        BSP_BOARD_MODE_VIDEO_8BIT,                  /* captBoardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,                 /* dispBoardMode */
        /* boardId */
        (BSP_BOARD_MULTIDES)
    },
#endif
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x)
    {
        "MULDESCAM1to4      -> VIP                             -> DSS Video1 -> DPI1 HDMI 1920x1080@60FPS",
        4U,                                         /* numCaptHandles */
        1U,                                         /* numDispHandles */

        /* captInstId[] */
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S0, VPS_VIP_PORTA),
#if defined (SOC_TDA2PX) || defined (SOC_AM574x)
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTB),
#else
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP3, VPS_VIP_S0, VPS_VIP_PORTA),
#endif
        },
        /* dispInstId[] */
        {
            VPS_DISP_INST_DSS_VID1
        },

        /* decDrvId[] */
        {
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
        },
        /* encDrvId[] */
        {
            0,
        },
        /* vencId */
        {
            VPS_DCTRL_DSS_VENC_HDMI
        },
        FALSE,                                      /* isSdVenc */
        /* captStandard */
        FVID2_STD_720P_60,
        /* dispStandard */
        {
            FVID2_STD_1080P_60,
        },

        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,              /* captVideoIfMode */
        FVID2_VIFW_8BIT,                            /* captVideoIfWidth */
        FVID2_SF_PROGRESSIVE,                       /* captScanFormat */
        FVID2_DF_YUV422P,                           /* captInDataFmt */
        FVID2_DF_YUV422I_YUYV,                      /* captOutDataFmt */

        LPBK_APP_SC_DISABLE_ALL,                    /* captScEnable */
        1280U,                                      /* captInWidth */
        720U,                                       /* captInHeight */
        1280U,                                      /* captOutWidth */
        720U,                                       /* captOutHeight */

        1280U,                                      /* dispInWidth */
        720U,                                       /* dispInHeight */
        1920U,                                      /* Target width */
        1080U,                                      /* Target Height */

        LPBK_APP_RUN_COUNT,                         /* runCount */
        BSP_BOARD_MODE_VIDEO_8BIT,                  /* captBoardMode */
        BSP_BOARD_MODE_DEFAULT,                     /* dispBoardMode */
        /* boardId */
        (BSP_BOARD_MULTIDES)
    },
#endif
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x)
    {
        "MULDESCAM1(GW4200_IMX290@24FPS)      -> VIP           -> DSS Video1 -> DPI1 HDMI 1920x1080@60FPS",
        1U,                                         /* numCaptHandles */
        1U,                                         /* numDispHandles */

        /* captInstId[] */
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA)
        },
        /* dispInstId[] */
        {
            VPS_DISP_INST_DSS_VID1
        },

        /* decDrvId[] */
        {
            FVID2_VID_SENSOR_GW4200_IMX290_DRV
        },
        /* encDrvId[] */
        {
            0,
        },
        /* vencId */
        {
            VPS_DCTRL_DSS_VENC_HDMI
        },
        FALSE,                                      /* isSdVenc */
        /* captStandard */
        FVID2_STD_720P_60,
        /* dispStandard */
        {
            FVID2_STD_1080P_60,
        },

        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,              /* captVideoIfMode */
        FVID2_VIFW_8BIT,                            /* captVideoIfWidth */
        FVID2_SF_PROGRESSIVE,                       /* captScanFormat */
        FVID2_DF_YUV422P,                           /* captInDataFmt */
        FVID2_DF_YUV422I_YUYV,                      /* captOutDataFmt */

        LPBK_APP_SC_DISABLE_ALL,                    /* captScEnable */
        1920U,                                      /* captInWidth */
        960U,                                       /* captInHeight */
        1920U,                                      /* captOutWidth */
        960U,                                       /* captOutHeight */

        1920U,                                      /* dispInWidth */
        960U,                                       /* dispInHeight */
        1920U,                                      /* Target width */
        1080U,                                      /* Target Height */

        LPBK_APP_RUN_COUNT,                         /* runCount */
        BSP_BOARD_MODE_VIDEO_8BIT,                  /* captBoardMode */
        BSP_BOARD_MODE_DEFAULT,                     /* dispBoardMode */
        /* boardId */
        (BSP_BOARD_MULTIDES)
    },
#endif
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
    {
        "MULDESCAM1to6      -> VIP                             -> DSS Video1 -> DPI1 HDMI 1920x1080@60FPS",
        6U,                                         /* numCaptHandles */
        1U,                                         /* numDispHandles */

        /* captInstId[] */
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S0, VPS_VIP_PORTA),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP3, VPS_VIP_S0, VPS_VIP_PORTA),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S1, VPS_VIP_PORTB),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP3, VPS_VIP_S1, VPS_VIP_PORTA),
        },
        /* dispInstId[] */
        {
            VPS_DISP_INST_DSS_VID1
        },

        /* decDrvId[] */
        {
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
        },
        /* encDrvId[] */
        {
            0,
        },
        /* vencId */
        {
            VPS_DCTRL_DSS_VENC_HDMI
        },
        FALSE,                                      /* isSdVenc */
        /* captStandard */
        FVID2_STD_720P_60,
        /* dispStandard */
        {
            FVID2_STD_1080P_60,
        },

        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,              /* captVideoIfMode */
        FVID2_VIFW_8BIT,                            /* captVideoIfWidth */
        FVID2_SF_PROGRESSIVE,                       /* captScanFormat */
        FVID2_DF_YUV422P,                           /* captInDataFmt */
        FVID2_DF_YUV422I_YUYV,                      /* captOutDataFmt */

        LPBK_APP_SC_DISABLE_ALL,                    /* captScEnable */
        1280U,                                      /* captInWidth */
        720U,                                       /* captInHeight */
        1280U,                                      /* captOutWidth */
        720U,                                       /* captOutHeight */

        1280U,                                      /* dispInWidth */
        720U,                                       /* dispInHeight */
        1920U,                                      /* Target width */
        1080U,                                      /* Target Height */

        LPBK_APP_RUN_COUNT,                         /* runCount */
        BSP_BOARD_MODE_VIDEO_8BIT,                  /* captBoardMode */
        BSP_BOARD_MODE_DEFAULT,                     /* dispBoardMode */
        /* boardId */
        (BSP_BOARD_MULTIDES)
    },
#endif
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x)
    {
#if defined (SOC_TDA2EX) || defined (SOC_AM571x)
        "TVP5158            -> VIP1_S1_PORTA (PAL)             -> DSS Video1 -> DPI1 LCD (DPI3 LCD for TDA2Ex_17x17)",
#else
        "TVP5158            -> VIP1_S0_PORTA (PAL)             -> DSS Video1 -> DPI1 LCD",
#endif
        1U,                                         /* numCaptHandles */
        1U,                                         /* numDispHandles */
        {
#if defined (SOC_TDA2EX) || defined (SOC_AM571x)
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
#else
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
#endif
        },
        {
            VPS_DISP_INST_DSS_VID1
        },
        {
            FVID2_VID_DEC_TVP5158_DRV,
        },
        {
            FVID2_LCD_CTRL_DRV,
        },
        {
            VPS_DCTRL_DSS_VENC_LCD1
        },
        FALSE,                                      /* isSdVenc */
        FVID2_STD_D1,                               /* captStandard */
        {
            FVID2_STD_CUSTOM,                       /* dispStandard */
        },

        FVID2_VIFM_SCH_ES,                          /* captVideoIfMode */
        FVID2_VIFW_8BIT,                            /* captVideoIfWidth */
        FVID2_SF_INTERLACED,                        /* captScanFormat */
        FVID2_DF_YUV422P,                           /* captInDataFmt */
        FVID2_DF_YUV422I_YUYV,                      /* captOutDataFmt */

        LPBK_APP_SC_DISABLE_ALL,                    /* captScEnable */
        720U,                                       /* captInWidth */
        288U,                                       /* captInHeight */
        720U,                                       /* captOutWidth */
        288U,                                       /* captOutHeight */

        720U,                                       /* dispInWidth */
        576U,                                       /* dispInHeight */
        LPBK_APP_USE_LCD_WIDTH,                     /* Target width */
        LPBK_APP_USE_LCD_HEIGHT,                    /* Target Height */

        LPBK_APP_RUN_COUNT,                         /* runCount */
        BSP_BOARD_MODE_VIDEO_BT656,                 /* captBoardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,                 /* dispBoardMode */
        /* boardId */
        (BSP_BOARD_JAMR3)
    },
#endif
#if defined (SOC_TDA3XX)
    {
        "MULDESCAM1to4      -> VIP                             -> DSS Video1 -> DPI -> SDVENC (NTSC)",
        4U,                                         /* numCaptHandles */
        1U,                                         /* numDispHandles */

        /* captInstId[] */
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTB),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTB),
        },
        /* dispInstId[] */
        {
            VPS_DISP_INST_DSS_VID1
        },

        /* decDrvId[] */
        {
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
        },
        /* encDrvId[] */
        {
            0,
        },
        /* vencId */
        {
            VPS_DCTRL_DSS_VENC_LCD1
        },
        TRUE,                                       /* isSdVenc */
        /* captStandard */
        FVID2_STD_720P_60,
        /* dispStandard */
        {
            FVID2_STD_NTSC,
        },

        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,              /* captVideoIfMode */
        FVID2_VIFW_8BIT,                            /* captVideoIfWidth */
        FVID2_SF_PROGRESSIVE,                       /* captScanFormat */
        FVID2_DF_YUV422P,                           /* captInDataFmt */
        FVID2_DF_YUV422I_YUYV,                      /* captOutDataFmt */

        LPBK_APP_SC_DISABLE_ALL,                    /* captScEnable */
        1280U,                                      /* captInWidth */
        720U,                                       /* captInHeight */
        1280U,                                      /* captOutWidth */
        720U,                                       /* captOutHeight */

        1280U,                                      /* dispInWidth */
        720U,                                       /* dispInHeight */
        720U,                                       /* Target width */
        480U,                                       /* Target Height */

        LPBK_APP_RUN_COUNT,                         /* runCount */
        BSP_BOARD_MODE_VIDEO_8BIT,                  /* captBoardMode */
        BSP_BOARD_MODE_DEFAULT,                     /* dispBoardMode */
        /* boardId */
        (BSP_BOARD_MULTIDES)
    },
#endif
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x)
    {
#if defined (SOC_TDA2EX) || defined (SOC_AM571x)
        "OV1063x            -> VIP1_S1_PORTA (1280x720@30FPS)  -> DSS Video1 -> DPI1 HDMI 1920x1080@60FPS",
#else
        "OV1063x            -> VIP1_S0_PORTA (1280x720@30FPS)  -> DSS Video1 -> DPI1 HDMI 1920x1080@60FPS",
#endif
        1U,                                         /* numCaptHandles */
        1U,                                         /* numDispHandles */

        /* captInstId[] */
        {
#if defined (SOC_TDA2EX) || defined (SOC_AM571x)
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
#else
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
#endif
        },
        /* dispInstId[] */
        {
            VPS_DISP_INST_DSS_VID1
        },

        /* decDrvId[] */
        {
            FVID2_VID_SENSOR_OV1063X_DRV,
        },
        /* encDrvId[] */
        {
            0,
        },
        /* vencId */
        {
            VPS_DCTRL_DSS_VENC_HDMI
        },
        FALSE,                                      /* isSdVenc */
        /* captStandard */
        FVID2_STD_720P_60,
        /* dispStandard */
        {
            FVID2_STD_1080P_60,
        },

        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,              /* captVideoIfMode */
        FVID2_VIFW_8BIT,                            /* captVideoIfWidth */
        FVID2_SF_PROGRESSIVE,                       /* captScanFormat */
        FVID2_DF_YUV422P,                           /* captInDataFmt */
        FVID2_DF_YUV422I_YUYV,                      /* captOutDataFmt */

        LPBK_APP_SC_DISABLE_ALL,                    /* captScEnable */
        1280U,                                      /* captInWidth */
        720U,                                       /* captInHeight */
        1280U,                                      /* captOutWidth */
        720U,                                       /* captOutHeight */

        1280U,                                      /* dispInWidth */
        720U,                                       /* dispInHeight */
        1920U,                                      /* Target width */
        1080U,                                      /* Target Height */

        LPBK_APP_RUN_COUNT,                         /* runCount */
        BSP_BOARD_MODE_VIDEO_8BIT,                  /* captBoardMode */
        BSP_BOARD_MODE_DEFAULT,                     /* dispBoardMode */
        /* boardId */
        (BSP_BOARD_VISION | BSP_BOARD_MULTIDES | BSP_BOARD_BASE_TDA3XX)
    },
#endif
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x)
    {
        "Virtio:               VIP1_S0_PORTA                   -> DSS Video1 -> DPI1 @ D1 (720x480), YUYV422I",
        1U,                                         /* numCaptHandles */
        1U,                                         /* numDispHandles */

        /* captInstId[] */
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
        },
        /* dispInstId[] */
        {
            VPS_DISP_INST_DSS_VID1
        },
        /* decDrvId[] */
        {
            0U,
        },
        /* encDrvId[] */
        {
            0U,
        },
        /* vencId */
        {
            VPS_DCTRL_DSS_VENC_LCD1
        },
        FALSE,                                      /* isSdVenc */
        /* captStandard */
        FVID2_STD_D1,
        /* dispStandard */
        {
            FVID2_STD_CUSTOM,
        },

        FVID2_VIFM_SCH_ES,                          /* captVideoIfMode */
        FVID2_VIFW_8BIT,                            /* captVideoIfWidth */
        FVID2_SF_PROGRESSIVE,                       /* captScanFormat */
        FVID2_DF_YUV422P,                           /* captInDataFmt */
        FVID2_DF_YUV422I_YUYV,                      /* captOutDataFmt */

        LPBK_APP_SC_DISABLE_ALL,                    /* captScEnable */
        720U,                                       /* captInWidth */
        480U,                                       /* captInHeight */
        720U,                                       /* captOutWidth */
        480U,                                       /* captOutHeight */

        720U,                                       /* dispInWidth */
        480U,                                       /* dispInHeight */
        720U,                                       /* Target width */
        480U,                                       /* Target Height */

        LPBK_APP_RUN_COUNT,                         /* runCount */
        BSP_BOARD_MODE_DEFAULT,                     /* captBoardMode */
        BSP_BOARD_MODE_DEFAULT,                     /* dispBoardMode */
        /* boardId */
        (BSP_BOARD_UNKNOWN)
    },
#endif
#if defined (SOC_AM571x) || defined (SOC_AM572x) || defined (SOC_AM574x) || defined (SOC_AM574x)
    {
#if defined (SOC_AM571x)
        "OV2659            -> VIP1_S0_PORTB (1280x720@30FPS)  -> YUYV422      -> DSS Video1 -> DPI1 LCD",
#else
        "OV2659            -> VIP2_S1_PORTB (1280x720@30FPS)  -> YUYV422      -> DSS Video1 -> DPI1 LCD",
#endif
        1U,                                         /* numCaptHandles */
        1U,                                         /* numDispHandles */
        /* captInstId[] */
        {
#if defined (SOC_AM571x)
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTB),
#else
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S1, VPS_VIP_PORTB),
#endif
        },
        /* dispInstId[] */
        {
            VPS_DISP_INST_DSS_VID1
        },

        /* decDrvId[] */
        {
            FVID2_VID_SENSOR_OV2659_DRV,
        },
        /* encDrvId[] */
        {
            FVID2_LCD_CTRL_DRV,
        },
        /* vencId */
        {
            VPS_DCTRL_DSS_VENC_LCD1
        },
        FALSE,                                      /* isSdVenc */
        /* captStandard */
        FVID2_STD_720P_60,
        /* dispStandard */
        {
            FVID2_STD_CUSTOM,
        },

        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,           /* captVideoIfMode */
        FVID2_VIFW_8BIT,                         /* captVideoIfWidth */
        FVID2_SF_PROGRESSIVE,                    /* captScanFormat */
        FVID2_DF_YUV422P,                        /* captInDataFmt */
        FVID2_DF_YUV422I_UYVY,                   /* captOutDataFmt */

        LPBK_APP_SC_DISABLE_ALL,                 /* captScEnable */
        1280U,                                   /* captInWidth */
        720U,                                    /* captInHeight */
        1280U,                                   /* captOutWidth */
        720U,                                    /* captOutHeight */

        1280U,                                   /* dispInWidth */
        720U,                                    /* dispInHeight */
        LPBK_APP_USE_LCD_WIDTH,                  /* Target width */
        LPBK_APP_USE_LCD_HEIGHT,                 /* Target Height */

        LPBK_APP_RUN_COUNT,                      /* runCount */
        BSP_BOARD_MODE_VIDEO_8BIT,               /* captBoardMode */
        BSP_BOARD_MODE_DEFAULT,                  /* dispBoardMode */
        /* boardId */
        (BSP_BOARD_UNKNOWN | BSP_BOARD_IDK_AM57XX)
    },
#endif
#if defined (SOC_AM572x)
    {
        "OV1063x            -> VIP2_S0_PORTA (1280x720@30FPS)  -> YUYV422      -> DSS Video1 -> DPI1 LCD",
        1U,                                         /* numCaptHandles */
        1U,                                         /* numDispHandles */
        /* captInstId[] */
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S0, VPS_VIP_PORTA),
        },
        /* dispInstId[] */
        {
            VPS_DISP_INST_DSS_VID1
        },

        /* decDrvId[] */
        {
            FVID2_VID_SENSOR_OV1063X_DRV,
        },
        /* encDrvId[] */
        {
            FVID2_LCD_CTRL_DRV,
        },
        /* vencId */
        {
            VPS_DCTRL_DSS_VENC_LCD1
        },
        FALSE,                                      /* isSdVenc */
        /* captStandard */
        FVID2_STD_720P_60,
        /* dispStandard */
        {
            FVID2_STD_CUSTOM,
        },

         FVID2_VIFM_SCH_DS_HSYNC_VSYNC,           /* captVideoIfMode */
         FVID2_VIFW_8BIT,                         /* captVideoIfWidth */
         FVID2_SF_PROGRESSIVE,                    /* captScanFormat */
         FVID2_DF_YUV422P,                        /* captInDataFmt */
         FVID2_DF_BGR24_888,                      /* captOutDataFmt */

         LPBK_APP_SC_DISABLE_ALL,                 /* captScEnable */
         1280U,                                   /* captInWidth */
         720U,                                    /* captInHeight */
         1280U,                                   /* captOutWidth */
         720U,                                    /* captOutHeight */

         1280U,                                   /* dispInWidth */
         720U,                                    /* dispInHeight */
         LPBK_APP_USE_LCD_WIDTH,                  /* Target width */
         LPBK_APP_USE_LCD_HEIGHT,                 /* Target Height */

         LPBK_APP_RUN_COUNT,                      /* runCount */
         BSP_BOARD_MODE_VIDEO_8BIT,               /* captBoardMode */
         BSP_BOARD_MODE_VIDEO_24BIT,              /* dispBoardMode */

        /* boardId */
        (BSP_BOARD_UNKNOWN | BSP_BOARD_GP_AM572X)
    },
#endif

#ifdef PLATFORM_ZEBU
    {
        "Zebu:                 VIP1_S0_PORTA (16-bit DiscSync) -> DSS Video1 -> DPI1 @ D1 (720x480), YUYV422I",
        1U,                                         /* numCaptHandles */
        1U,                                         /* numDispHandles */

        /* captInstId[] */
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
        },
        /* dispInstId[] */
        {
            VPS_DISP_INST_DSS_VID1
        },

        /* decDrvId[] */
        {
            0U,
        },
        /* encDrvId[] */
        {
            0U,
        },
        /* vencId */
        {
            VPS_DCTRL_DSS_VENC_LCD1
        },
        FALSE,                                      /* isSdVenc */
        /* captStandard */
        FVID2_STD_D1,
        /* dispStandard */
        {
            FVID2_STD_CUSTOM,
        },

        FVID2_VIFM_SCH_DS_AVID_VSYNC,               /* captVideoIfMode */
        FVID2_VIFW_16BIT,                           /* captVideoIfWidth */
        FVID2_SF_PROGRESSIVE,                       /* captScanFormat */
        FVID2_DF_YUV422I_YUYV,                      /* captInDataFmt */
        FVID2_DF_YUV422I_YUYV,                      /* captOutDataFmt */

        LPBK_APP_SC_DISABLE_ALL,                    /* captScEnable */
        720U,                                       /* captInWidth */
        480U,                                       /* captInHeight */
        720U,                                       /* captOutWidth */
        480U,                                       /* captOutHeight */

        720U,                                       /* dispInWidth */
        480U,                                       /* dispInHeight */
        720U,                                       /* Target width */
        480U,                                       /* Target Height */

        LPBK_APP_RUN_COUNT,                         /* runCount */
        BSP_BOARD_MODE_DEFAULT,                     /* captBoardMode */
        BSP_BOARD_MODE_DEFAULT,                     /* dispBoardMode */
        /* boardId */
        (BSP_BOARD_UNKNOWN)
    }
#endif
};

#define LPBK_APP_NUM_TESTS              (sizeof (gLpbkAppTestPrms) / \
                                         sizeof (gLpbkAppTestPrms[0U]))

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
#define PDK_RAW_BOOT
static Board_STATUS CapApp_boardInit(void)
{
    Board_STATUS ret;
    Board_initCfg boardCfg;

#ifdef PDK_RAW_BOOT
    boardCfg = BOARD_INIT_PINMUX_CONFIG | BOARD_INIT_MODULE_CLOCK;
#endif

    boardCfg |= BOARD_INIT_UART_STDIO;
    ret = Board_init(boardCfg);
    return (ret);
}
#endif
/*
 * Application main
 */
int main(void)
{
    static Char stdin_buf[BUFSIZ];
#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
    UInt32                  tempFuncPtr;
    BspOsal_InitParams_t    bspOsalInitPrms = {0};

    CapApp_boardInit();
    /* Initialize the UART prints */
    BspUtils_uartInit();
    tempFuncPtr = (UInt32) & BspUtils_uartPrint;
    bspOsalInitPrms.printFxn = (BspOsal_PrintFxn) (tempFuncPtr);
    BspOsal_Init(&bspOsalInitPrms);
#endif
    /* Provide buffer so that STDIO library will use this memory instead of
     * allocating from system heap, which might lead to false system leak
     * warning */
    setvbuf(stdin, stdin_buf, _IOLBF, BUFSIZ);

    /* Create test task */
    LpbkApp_createTsk();

    /* Start BIOS */
    BIOS_start();

    return (0);
}

/*
 * Create test task
 */
static void LpbkApp_createTsk(void)
{
    Task_Params tskPrms;

    /* Create task to wait for overflow to occur.
     * When it occurs, this task will just reset VIP */
    gExitApp = FALSE;
    Task_Params_init(&tskPrms);
    tskPrms.priority  = LPBK_APP_TSK_PRI_MAIN;
    tskPrms.stack     = gLpbkAppTskStackReset;
    tskPrms.stackSize = sizeof (gLpbkAppTskStackReset);
    tskPrms.arg0      = (UArg) & gLpbkAppObj;
    Task_construct(&gResetTskStruct, LpbkApp_tskReset, &tskPrms, NULL);
    gLpbkAppObj.resetTskHandle = Task_handle(&gResetTskStruct);
    GT_assert(BspAppTrace, (gLpbkAppObj.resetTskHandle != NULL));

    /* Create test task */
    Task_Params_init(&tskPrms);
    tskPrms.priority  = LPBK_APP_TSK_PRI_MAIN;
    tskPrms.stack     = gLpbkAppTskStackMain;
    tskPrms.stackSize = sizeof (gLpbkAppTskStackMain);
    tskPrms.arg0      = (UArg) & gLpbkAppObj;
    Task_construct(&gTskStruct, LpbkApp_tskMain, &tskPrms, NULL);
    gLpbkAppObj.tskHandle = Task_handle(&gTskStruct);
    GT_assert(BspAppTrace, (gLpbkAppObj.tskHandle != NULL));

    /* Register the task to the load module for calculating the load */
    BspUtils_prfLoadRegister(gLpbkAppObj.tskHandle, APP_NAME);

    return;
}

/*
 *  Reset task
 * When overflow occurs, this task will run.
 * It will stop the driver, reset it and again start it.
 */

static void LpbkApp_tskReset(UArg arg0, UArg arg1)
{
    LpbkApp_Obj     *appObj = (LpbkApp_Obj *) arg0;
    LpbkApp_InstObj *instObj;
    UInt32           captInstCnt = 0;
    Int32 retVal;
    overflowSem = BspOsal_semCreate(0, FALSE);

    GT_assert(BspAppTrace, (NULL != appObj));
    GT_assert(BspAppTrace, (NULL != overflowSem));

    while (1U)
    {
        BspOsal_semWait(overflowSem, BSP_OSAL_WAIT_FOREVER);
        if ((UInt32) TRUE == gExitApp)
        {
            BspOsal_semDelete(&overflowSem);
            break;
        }
        for (captInstCnt = 0; captInstCnt < appObj->testPrms.numCaptHandles;
             captInstCnt++)
        {
            Vps_CaptOverflowCheckParams overflowCheckParams;
            instObj = &appObj->instObj[captInstCnt];
            instObj->overflowCount = 0;
            retVal = Fvid2_control(
                instObj->captDrvHandle,
                IOCTL_VPS_CAPT_CHECK_OVERFLOW,
                &overflowCheckParams,
                NULL);
            if (TRUE == overflowCheckParams.isOverflowOccured)
            {
                /*Stop the driver*/
                retVal = Fvid2_stop(instObj->captDrvHandle, NULL);
                if (retVal != FVID2_SOK)
                {
                    GT_0trace(BspAppTrace, GT_ERR,
                              APP_NAME ": Capture Stop Failed!!!\r\n");
                }

                if (FVID2_SOK == retVal)
                {
                    /* Reset the VIP */
                    retVal = Fvid2_control(
                        instObj->captDrvHandle,
                        IOCTL_VPS_CAPT_RESET_VIP,
                        NULL,
                        NULL);

                    if (retVal != FVID2_SOK)
                    {
                        GT_0trace(BspAppTrace, GT_ERR,
                                  APP_NAME ": VIP Port Reset Failed!!!\r\n");
                    }
                }

                if (FVID2_SOK == retVal)
                {
                    /* Restart the driver */
                    retVal = Fvid2_start(instObj->captDrvHandle, NULL);
                    if (retVal != FVID2_SOK)
                    {
                        GT_0trace(BspAppTrace, GT_ERR,
                                  APP_NAME ": Capture Start Failed!!!\r\n");
                    }
                }
                if (FVID2_SOK != retVal)
                {
                    break;
                }
            }
        }
    }

    return;
}

/*
 * Test task main
 */
static void LpbkApp_tskMain(UArg arg0, UArg arg1)
{
    Int32       testId;
    Bsp_BoardId boardId;
    LpbkApp_Obj           *appObj = (LpbkApp_Obj *) arg0;
    LpbkApp_TestParams    *testPrms;
    BspUtils_MemHeapStatus startHeapStat, startHeapStat1;

    GT_0trace(BspAppTrace, GT_INFO,
              APP_NAME ": Sample Application - STARTS !!!\r\n");
    BspUtils_memGetHeapStat(&startHeapStat);
    LpbkApp_init(appObj);

    appObj->enableAutoRun = (UInt32) FALSE;
    boardId = Bsp_boardGetId();
    while (1U)
    {
        /* Get the TestId */
        testId = LpbkApp_getTestId(appObj);
        if ((testId >= 0) && (testId < LPBK_APP_NUM_TESTS))
        {
            testPrms = &gLpbkAppTestPrms[testId];
            if (testPrms->boardId & boardId)
            {
                BspUtils_memGetHeapStat(&startHeapStat1);

                testPrms->testId = testId;
                LpbkApp_runTest(appObj, testPrms);

                BspUtils_memCheckHeapStat(&startHeapStat1);
            }
            else
            {
                GT_1trace(BspAppTrace, GT_INFO,
                          APP_NAME ": Skipping test case %d!!!\r\n", testId);
            }
        }
        else
        {
            /* Exit */
            break;
        }
    }

    LpbkApp_deInit(appObj);

    gExitApp = (UInt32) TRUE;
    BspOsal_semPost(overflowSem);
    BspOsal_sleep(500);         /* Wait for reset task to exit */

    BspUtils_memCheckHeapStat(&startHeapStat);
    GT_1trace(BspAppTrace, GT_INFO,
              APP_NAME ": Max stack used for test task: %d bytes\r\n",
              BspOsal_getTaskStackUsage(NULL));
    GT_1trace(BspAppTrace, GT_INFO,
              APP_NAME ": Max system stack used (ISR): %d bytes\r\n",
              BspOsal_getSystemStackUsage());
    BspUtils_appPrintMemStatus();

    GT_0trace(BspAppTrace, GT_INFO,
              APP_NAME ": Sample Application - DONE !!!\r\n");

    return;
}

static void LpbkApp_init(LpbkApp_Obj *appObj)
{
    Int32  retVal;
    UInt32 isI2cInitReq;
    UInt32 defPixelClk;

    /* System init */
    isI2cInitReq = TRUE;
    retVal       = BspUtils_appDefaultInit(isI2cInitReq);
    if (retVal != FVID2_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": System Init Failed!!!\r\n");
    }
    if (FVID2_SOK == retVal)
    {
        /* Create global capture handle, used for common driver configuration */
        appObj->fvidHandleAll = Fvid2_create(
            FVID2_VPS_CAPT_VID_DRV,
            VPS_CAPT_INST_ALL,
            NULL,                       /* NULL for VPS_LPBK_INST_ALL */
            NULL,                       /* NULL for VPS_LPBK_INST_ALL */
            NULL);                      /* NULL for VPS_LPBK_INST_ALL */
        if (NULL == appObj->fvidHandleAll)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Global Handle Create Failed!!!\r\n");
            retVal = FVID2_EBADARGS;
        }
    }
    if (FVID2_SOK == retVal)
    {
        /* Create DCTRL handle, used for common driver configuration */
        appObj->dctrlHandle = Fvid2_create(
            FVID2_VPS_DCTRL_DRV,
            VPS_DCTRL_INST_0,
            NULL,                       /* NULL for VPS_DCTRL_INST_0 */
            NULL,                       /* NULL for VPS_DCTRL_INST_0 */
            NULL);                      /* NULL for VPS_DCTRL_INST_0 */
        if (NULL == appObj->dctrlHandle)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": DCTRL Create Failed!!!\r\n");
            retVal = FVID2_EBADARGS;
        }
    }

    if ((BSP_PLATFORM_ID_EVM == Bsp_platformGetId()) && (FVID2_SOK == retVal))
    {
        /* Set default video PLL clock - This will be changed later based
         * on detected LCD */
        defPixelClk = 29232U * 4U;

        /* No Internal Dividers present in DSS in Tda3xx platform,
         * so default it to 29232 itself. */
        if (TRUE == Bsp_platformIsTda3xxFamilyBuild())
        {
            defPixelClk = 29232U;
        }

        retVal = LpbkApp_configureVideoPllAndClkSrc(appObj, defPixelClk);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Configuring PLL Failed!!!\r\n");
        }

        if (FVID2_SOK == retVal)
        {
            /* Needed onlt for TDA2xx platform. Other platform will do nothing
             * and return OK */
            retVal = Bsp_platformEnableHdmiPll(TRUE);
            if (retVal != FVID2_SOK)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          APP_NAME ": Enabling HDMI PLL Failed!!!\r\n");
            }
        }

        if (FVID2_SOK == retVal)
        {
            if (BSP_BOARD_MULTIDES == Bsp_boardGetId())
            {
                retVal =
                    BspUtils_appInitSerDeSer();
                if (retVal != FVID2_SOK)
                {
                    GT_0trace(BspAppTrace, GT_ERR,
                              APP_NAME ": MultiDes Board Init failed!!!\r\n");
                }
            }
        }
    }

    if (FVID2_SOK == retVal)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": LpbkApp_init() - DONE !!!\r\n");
    }

    return;
}

static void LpbkApp_deInit(LpbkApp_Obj *appObj)
{
    Int32  retVal;
    UInt32 isI2cDeInitReq;

    /* Delete DCTRL handle */
    retVal = Fvid2_delete(appObj->dctrlHandle, NULL);
    if (retVal != FVID2_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": DCTRL handle delete failed!!!\r\n");
    }

    if (FVID2_SOK == retVal)
    {
        /* Delete global VIP capture handle */
        retVal = Fvid2_delete(appObj->fvidHandleAll, NULL);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Global handle delete failed!!!\r\n");
        }
    }

    if (FVID2_SOK == retVal)
    {
        if (BSP_BOARD_MULTIDES == Bsp_boardGetId())
        {
            retVal =
                BspUtils_appDeInitSerDeSer();
            if (retVal != FVID2_SOK)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          APP_NAME ": MultiDes Board DeInit failed!!!\r\n");
            }
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* System de-init */
        isI2cDeInitReq = TRUE;
        retVal         = BspUtils_appDefaultDeInit(isI2cDeInitReq);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": System De-Init Failed!!!\r\n");
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Needed onlt for TDA2xx platform. Other platform will do nothing
         * and return OK */
        retVal = Bsp_platformEnableHdmiPll(FALSE);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Disabling HDMI PLL Failed!!!\r\n");
        }
    }

    if (FVID2_SOK == retVal)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": LpbkApp_deInit() - DONE !!!\r\n");
    }

    return;
}

/**
 *  LpbkApp_getTestId
 *  Return the test ID to run.
 */
static Int32 LpbkApp_getTestId(LpbkApp_Obj *appObj)
{
    UInt32        testCnt;
    static Int32  testId     = 0;
    Int32         retVal     = BSP_SOK;
    static UInt32 timeoutVal = BSP_UTILS_UART_RX_DEFAULT_TIMEOUT;

    GT_0trace(BspAppTrace, GT_INFO, " \r\n");
    GT_0trace(BspAppTrace, GT_INFO,
              "--------------------------------------\r\n");
    GT_0trace(BspAppTrace, GT_INFO,
              "Select test to run as per below table:\r\n");
    GT_0trace(BspAppTrace, GT_INFO,
              "--------------------------------------\r\n");
    GT_0trace(BspAppTrace, GT_INFO, " \r\n");
    for (testCnt = 0; testCnt < LPBK_APP_NUM_TESTS; testCnt++)
    {
        GT_2trace(BspAppTrace, GT_INFO,
                  "%3d: %s\r\n", testCnt, gLpbkAppTestPrms[testCnt].testDescStr);
    }
    GT_2trace(BspAppTrace, GT_INFO,
              "%3d: %s\r\n", LPBK_APP_NUM_TESTS, "Auto Run\r\n");
    GT_1trace(BspAppTrace, GT_INFO, "%3d: EXIT\r\n", 100);
    GT_0trace(BspAppTrace, GT_INFO, " \r\n");
    GT_0trace(BspAppTrace, GT_INFO, "Enter Test to Run (in UART console): \r\n");

    if (TRUE == appObj->enableAutoRun)
    {
        testId++;
        if (testId < LPBK_APP_NUM_TESTS)
        {
            GT_1trace(BspAppTrace, GT_INFO, "%d\r\n", testId);
        }
    }
    else
    {
        while (1U)
        {
            retVal = BspUtils_uartGetNum(&testId, timeoutVal);
            if (retVal == BSP_ETIMEOUT)
            {
                /* No user input within the timeout */
                appObj->enableAutoRun = (UInt32) TRUE;
                testId = 0;
                GT_1trace(BspAppTrace, GT_INFO, "%d\r\n", testId);
                break;
            }
            else
            {
                timeoutVal = BSP_UTILS_UART_RX_WAIT_FOREVER;
            }
            if ((testId >= 0) && (testId < LPBK_APP_NUM_TESTS))
            {
                GT_1trace(BspAppTrace, GT_INFO, "%d\r\n", testId);
                break;
            }
            else if (testId == LPBK_APP_NUM_TESTS)
            {
                appObj->enableAutoRun = (UInt32) TRUE;
                testId = 0;
                GT_1trace(BspAppTrace, GT_INFO, "%d\r\n", testId);
                break;
            }
            else if (100 == testId)
            {
                break;
            }
            GT_0trace(BspAppTrace, GT_INFO,
                      "Invalid Test ID. Enter Agian!!\r\n");
        }
    }

    return (testId);
}

