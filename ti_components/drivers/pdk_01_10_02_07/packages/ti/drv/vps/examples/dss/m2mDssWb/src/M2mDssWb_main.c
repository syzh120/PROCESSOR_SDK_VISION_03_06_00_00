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
 *  \file M2mDssWb_main.c
 *
 *  \brief DSS M2M sample application.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <M2mDssWb_main.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define M2MWB_BANDWIDTH_CONTROL_NONE {0U, 0U}

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void M2mDssApp_createTsk(void);
static void M2mDssApp_tskMain(UArg arg0, UArg arg1);

static void M2mDssApp_init(M2mDssApp_Obj *appObj);
static void M2mDssApp_deInit(M2mDssApp_Obj *appObj);

static Int32 M2mDssApp_runTest(M2mDssApp_Obj              *appObj,
                               const M2mDssApp_TestParams *testPrms);

static Int32 M2mDssApp_create(M2mDssApp_Obj *appObj);
static Int32 M2mDssApp_delete(M2mDssApp_Obj *appObj);

static Int32 M2mDssApp_cbFxn(Fvid2_Handle handle, Ptr appData, Ptr reserved);
static void M2mDssApp_updateFrameList(M2mDssApp_Obj     *appObj,
                                      Fvid2_FrameList   *inFrmList,
                                      Fvid2_FrameList   *outFrmList);

static void M2mDssApp_initParams(M2mDssApp_Obj *appObj);
static Int32 M2mDssApp_getTestId(M2mDssApp_Obj *appObj);
static Int32 M2mDssApp_getTestIndex(Int32 testId);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Align stack memory to integer boundary. */
/* Place the stack in stack section. */
#if defined(__GNUC__) && !defined(__ti__)
DATA_ALIGN(32) DATA_SECTION(".bss:taskStackSection")
#else
#pragma DATA_ALIGN(gM2mDssAppTskStackMain, 32)
#pragma DATA_SECTION(gM2mDssAppTskStackMain, ".bss:taskStackSection")
#endif
/* Test application stack */
static UInt8             gM2mDssAppTskStackMain[M2MDSS_APP_TSK_STACK_MAIN];

/* Test application object */
static M2mDssApp_Obj     gM2mDssAppObj;

/* Current Test cases index */
static Int32 gTestIdx = 0;

/* Test cases */
static const M2mDssApp_TestParams gM2mDssAppTestPrms[] =
{
    {
        /* Test case id. */
        0U,
        "VID1 BGR888 720P                       -> WB YUV422I_YUYV 480P",
        VPS_DSS_DISPC_WB_IN_NODE_VID1,      /* wbInNode */
        1U,                                 /* numInPipeLines */
        {
            VPS_DSS_DISPC_PIPE_VID1,        /* inPipeLines */
        },
        {
            FVID2_DF_BGR24_888,             /* inDataFmt */
        },
        {
            1280U,                          /* inWidth */
        },
        {
            720U,                           /* inHeight */
        },
        {
            1280U,                          /* inTarWidth */
        },
        {
            720U,                           /* inTarHeight */
        },
        FVID2_DF_YUV422I_YUYV,              /* outDataFmt */
        720U,                               /* outWidth */
        480U,                               /* outHeight */
        0U,                                 /* ovlyWidth - NA */
        0U,                                 /* ovlyHeight - NA */
        FALSE,                              /* cropEnable */
        {
            0                               /* cropCfg - NA */
        },
        M2MWB_BANDWIDTH_CONTROL_NONE,       /* bandwidth control */
        M2MDSS_APP_TOTAL_LOOP_COUNT,        /* runCount */
#if defined (SOC_TDA3XX)
        0x1C3742D2U,                        /* crcValue */
#else
        0xA923C506U,                        /* crcValue */
#endif
    },
    {
        /* Test case id. */
        1U,
        "VID2 BGR565 720P                       -> WB YUV422I_UYVY 720P",
        VPS_DSS_DISPC_WB_IN_NODE_VID2,      /* wbInNode */
        1U,                                 /* numInPipeLines */
        {
            VPS_DSS_DISPC_PIPE_VID2,        /* inPipeLines */
        },
        {
            FVID2_DF_BGR16_565,             /* inDataFmt */
        },
        {
            1280U,                          /* inWidth */
        },
        {
            720U,                           /* inHeight */
        },
        {
            1280U,                          /* inTarWidth */
        },
        {
            720U,                           /* inTarHeight */
        },
        FVID2_DF_YUV422I_UYVY,              /* outDataFmt */
        1280U,                              /* outWidth */
        720U,                               /* outHeight */
        0U,                                 /* ovlyWidth - NA */
        0U,                                 /* ovlyHeight - NA */
        FALSE,                              /* cropEnable */
        {
            0                               /* cropCfg - NA */
        },
        M2MWB_BANDWIDTH_CONTROL_NONE,       /* bandwidth control */
        M2MDSS_APP_TOTAL_LOOP_COUNT,        /* runCount */
#if defined (SOC_TDA3XX)
        0xD762C362U,                        /* crcValue */
#else
        0x78EC8B29U,                        /* crcValue */
#endif
    },
    {
        /* Test case id. */
        2U,
        "VID1 YUV422_YUYV 720P                  -> WB BGR888 1080P",
        VPS_DSS_DISPC_WB_IN_NODE_VID1,      /* wbInNode */
        1U,                                 /* numInPipeLines */
        {
            VPS_DSS_DISPC_PIPE_VID1,        /* inPipeLines */
        },
        {
            FVID2_DF_YUV422I_YUYV,          /* inDataFmt */
        },
        {
            1280U,                          /* inWidth */
        },
        {
            720U,                           /* inHeight */
        },
        {
            1280U,                          /* inTarWidth */
        },
        {
            720U,                           /* inTarHeight */
        },
        FVID2_DF_BGR24_888,                 /* outDataFmt */
        1920U,                              /* outWidth */
        1080U,                              /* outHeight */
        0U,                                 /* ovlyWidth - NA */
        0U,                                 /* ovlyHeight - NA */
        FALSE,                              /* cropEnable */
        {
            0                               /* cropCfg - NA */
        },
        M2MWB_BANDWIDTH_CONTROL_NONE,       /* bandwidth control */
        M2MDSS_APP_TOTAL_LOOP_COUNT,        /* runCount */
#if defined (SOC_TDA3XX)
        0xE716D39EU,                        /* crcValue */
#else
        0xD46C7FA4U,                        /* crcValue */
#endif
    },
    {
        /* Test case id. */
        3U,
        "VID1 YUV422_YUYV 1080P                  -> WB YUV422I_UYVY 1080P",
        VPS_DSS_DISPC_WB_IN_NODE_VID1,      /* wbInNode */
        1U,                                 /* numInPipeLines */
        {
            VPS_DSS_DISPC_PIPE_VID1,        /* inPipeLines */
        },
        {
            FVID2_DF_YUV422I_YUYV,          /* inDataFmt */
        },
        {
            1920U,                          /* inWidth */
        },
        {
            1080U,                           /* inHeight */
        },
        {
            1920U,                          /* inTarWidth */
        },
        {
            1080U,                           /* inTarHeight */
        },
        FVID2_DF_YUV422I_UYVY,                 /* outDataFmt */
        1920U,                              /* outWidth */
        1080U,                              /* outHeight */
        0U,                                 /* ovlyWidth - NA */
        0U,                                 /* ovlyHeight - NA */
        FALSE,                              /* cropEnable */
        {
            0                               /* cropCfg - NA */
        },
        M2MWB_BANDWIDTH_CONTROL_NONE,       /* bandwidth control */
        M2MDSS_APP_TOTAL_LOOP_COUNT,        /* runCount */
#if defined (SOC_TDA3XX)
        0x279F8C47U,                        /* crcValue */
#else
        0xED51381EU,                        /* crcValue */
#endif
    },
    {
        /* Test case id. */
        4U,
        "VID1 YUV422_UYVY 1080P                  -> WB YUV422I_YUYV 1080P",
        VPS_DSS_DISPC_WB_IN_NODE_VID1,      /* wbInNode */
        1U,                                 /* numInPipeLines */
        {
            VPS_DSS_DISPC_PIPE_VID1,        /* inPipeLines */
        },
        {
            FVID2_DF_YUV422I_UYVY,          /* inDataFmt */
        },
        {
            1920U,                          /* inWidth */
        },
        {
            1080U,                           /* inHeight */
        },
        {
            1920U,                          /* inTarWidth */
        },
        {
            1080U,                           /* inTarHeight */
        },
        FVID2_DF_YUV422I_YUYV,                 /* outDataFmt */
        1920U,                              /* outWidth */
        1080U,                              /* outHeight */
        0U,                                 /* ovlyWidth - NA */
        0U,                                 /* ovlyHeight - NA */
        FALSE,                              /* cropEnable */
        {
            0                               /* cropCfg - NA */
        },
        M2MWB_BANDWIDTH_CONTROL_NONE,       /* bandwidth control */
        M2MDSS_APP_TOTAL_LOOP_COUNT,        /* runCount */
#if defined (SOC_TDA3XX)
        0xE71F3DB2U,                        /* crcValue */
#else
        0xC7BF8562U,                        /* crcValue */
#endif
    },
/* PDP-1402: GFX WB not working on TDA2xx */
#if defined (SOC_TDA3XX)
    {
        /* Test case id. */
        5U,
        "GPX1 BGR888 720P                       -> WB YUV422I_YUYV 720P",
        VPS_DSS_DISPC_WB_IN_NODE_GFX,       /* wbInNode */
        1U,                                 /* numInPipeLines */
        {
            VPS_DSS_DISPC_PIPE_GFX1,        /* inPipeLines */
        },
        {
            FVID2_DF_BGR24_888,             /* inDataFmt */
        },
        {
            1280U,                          /* inWidth */
        },
        {
            720U,                           /* inHeight */
        },
        {
            1280U,                          /* inTarWidth */
        },
        {
            720U,                           /* inTarHeight */
        },
        FVID2_DF_YUV422I_YUYV,              /* outDataFmt */
        1280U,                              /* outWidth */
        720U,                               /* outHeight */
        0U,                                 /* ovlyWidth - NA */
        0U,                                 /* ovlyHeight - NA */
        FALSE,                              /* cropEnable */
        {
            0                               /* cropCfg - NA */
        },
        M2MWB_BANDWIDTH_CONTROL_NONE,       /* bandwidth control */
        M2MDSS_APP_TOTAL_LOOP_COUNT,        /* runCount */
#if defined (SOC_TDA3XX)
        0x936968b2U,                        /* crcValue */
#else
        0xB673E7A6U,                        /* crcValue */
#endif
    },
#endif
    {
        /* Test case id. */
        6U,
        "VID1 YUV422_YUYV 1080P                 -> WB BGR565 1080P",
        VPS_DSS_DISPC_WB_IN_NODE_VID1,      /* wbInNode */
        1U,                                 /* numInPipeLines */
        {
            VPS_DSS_DISPC_PIPE_VID1,        /* inPipeLines */
        },
        {
            FVID2_DF_YUV422I_YUYV,          /* inDataFmt */
        },
        {
            1920U,                          /* inWidth */
        },
        {
            1080U,                          /* inHeight */
        },
        {
            1920U,                          /* inTarWidth */
        },
        {
            1080U,                          /* inTarHeight */
        },
        FVID2_DF_BGR16_565,                 /* outDataFmt */
        1920U,                              /* outWidth */
        1080U,                              /* outHeight */
        0U,                                 /* ovlyWidth - NA */
        0U,                                 /* ovlyHeight - NA */
        FALSE,                              /* cropEnable */
        {
            0                               /* cropCfg - NA */
        },
        M2MWB_BANDWIDTH_CONTROL_NONE,       /* bandwidth control */
        M2MDSS_APP_TOTAL_LOOP_COUNT,        /* runCount */
#if defined (SOC_TDA3XX)
        0x658612D9U,                        /* crcValue */
#else
        0x6250FB88U,                        /* crcValue */
#endif
    },
    {
        /* Test case id. */
        7U,
        "VID1 YUV420SP 1080P                    -> WB YUV422_YUYV 720P",
        VPS_DSS_DISPC_WB_IN_NODE_VID1,      /* wbInNode */
        1U,                                 /* numInPipeLines */
        {
            VPS_DSS_DISPC_PIPE_VID1,        /* inPipeLines */
        },
        {
            FVID2_DF_YUV420SP_UV,           /* inDataFmt */
        },
        {
            1920U,                          /* inWidth */
        },
        {
            1080U,                          /* inHeight */
        },
        {
            1920U,                          /* inTarWidth */
        },
        {
            1080U,                          /* inTarHeight */
        },
        FVID2_DF_YUV422I_YUYV,              /* outDataFmt */
        1280U,                              /* outWidth */
        720U,                               /* outHeight */
        0U,                                 /* ovlyWidth - NA */
        0U,                                 /* ovlyHeight - NA */
        FALSE,                              /* cropEnable */
        {
            0                               /* cropCfg - NA */
        },
        M2MWB_BANDWIDTH_CONTROL_NONE,       /* bandwidth control */
        M2MDSS_APP_TOTAL_LOOP_COUNT,        /* runCount */
#if defined (SOC_TDA3XX)
        0x799ED4B4U,                        /* crcValue */
#else
        0xEA35CF20U,                        /* crcValue */
#endif
    },
    {
        /* Test case id. */
        8U,
        "VID1 YUV422_YUYV 1080P                 -> WB YUV420SP 720P",
        VPS_DSS_DISPC_WB_IN_NODE_VID1,      /* wbInNode */
        1U,                                 /* numInPipeLines */
        {
            VPS_DSS_DISPC_PIPE_VID1,        /* inPipeLines */
        },
        {
            FVID2_DF_YUV422I_YUYV,          /* inDataFmt */
        },
        {
            1920U,                          /* inWidth */
        },
        {
            1080U,                          /* inHeight */
        },
        {
            1280U,                          /* inTarWidth */
        },
        {
            720U,                           /* inTarHeight */
        },
        FVID2_DF_YUV420SP_UV,               /* outDataFmt */
        1280U,                              /* outWidth */
        720U,                               /* outHeight */
        0U,                                 /* ovlyWidth - NA */
        0U,                                 /* ovlyHeight - NA */
        FALSE,                              /* cropEnable */
        {
            0                               /* cropCfg - NA */
        },
        M2MWB_BANDWIDTH_CONTROL_NONE,       /* bandwidth control */
        M2MDSS_APP_TOTAL_LOOP_COUNT,        /* runCount */
#if defined (SOC_TDA3XX)
        0x8A26FA58U,                        /* crcValue */
#else
        0x89AA093BU,                        /* crcValue */
#endif
    },
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_TDA2EX) || defined (SOC_AM571x)
    {
        /* Test case id. */
        9U,
        "VID3 BGR888 1080P                      -> WB YUV422_YUYV 1080P",
        VPS_DSS_DISPC_WB_IN_NODE_VID3,      /* wbInNode */
        1U,                                 /* numInPipeLines */
        {
            VPS_DSS_DISPC_PIPE_VID3,        /* inPipeLines */
        },
        {
            FVID2_DF_BGR24_888,             /* inDataFmt */
        },
        {
            1920U,                          /* inWidth */
        },
        {
            1080U,                          /* inHeight */
        },
        {
            1920U,                          /* inTarWidth */
        },
        {
            1080U,                          /* inTarHeight */
        },
        FVID2_DF_YUV422I_YUYV,              /* outDataFmt */
        1920U,                              /* outWidth */
        1080U,                              /* outHeight */
        0U,                                 /* ovlyWidth - NA */
        0U,                                 /* ovlyHeight - NA */
        FALSE,                              /* cropEnable */
        {
            0                               /* cropCfg - NA */
        },
        M2MWB_BANDWIDTH_CONTROL_NONE,       /* bandwidth control */
        M2MDSS_APP_TOTAL_LOOP_COUNT,        /* runCount */
        0x1B4A7E01U,                        /* crcValue */
    },
#endif
    {
        /* Test case id. */
        10U,
        "VID1 BGR565 720P + VID2 YUV422 720P    -> LCD1 WB YUV420SP 720P",
        VPS_DSS_DISPC_WB_IN_NODE_LCD1,      /* wbInNode */
        2U,                                 /* numInPipeLines */
        {
            VPS_DSS_DISPC_PIPE_VID1,        /* inPipeLines */
            VPS_DSS_DISPC_PIPE_VID2,        /* inPipeLines */
        },
        {
            FVID2_DF_BGR16_565,             /* inDataFmt */
            FVID2_DF_YUV422I_YUYV,          /* inDataFmt */
        },
        {
            1280U,                          /* inWidth */
            1280U,                          /* inWidth */
        },
        {
            720U,                           /* inHeight */
            720U,                           /* inHeight */
        },
        {
            640U,                           /* inTarWidth */
            640U,                           /* inTarWidth */
        },
        {
            480U,                           /* inTarHeight */
            480U,                           /* inTarHeight */
        },
        FVID2_DF_YUV420SP_UV,               /* outDataFmt */
        1280U,                              /* outWidth */
        720U,                               /* outHeight */
        1280U,                              /* ovlyWidth */
        720U,                               /* ovlyHeight */
        FALSE,                              /* cropEnable */
        {
            0                               /* cropCfg - NA */
        },
        M2MWB_BANDWIDTH_CONTROL_NONE,       /* bandwidth control */
        M2MDSS_APP_TOTAL_LOOP_COUNT,        /* runCount */
#if defined (SOC_TDA3XX)
        0x9ECB876CU,                        /* crcValue */
#else
        0xCC0ACFB8U,                        /* crcValue */
#endif
    },
    {
        /* Test case id. */
        11U,
        "VID1 BGR565 720P + VID2 YUV422 720P    -> LCD2 WB YUV422_YUYV 720P",
        VPS_DSS_DISPC_WB_IN_NODE_LCD2,      /* wbInNode */
        2U,                                 /* numInPipeLines */
        {
            VPS_DSS_DISPC_PIPE_VID1,        /* inPipeLines */
            VPS_DSS_DISPC_PIPE_VID2,        /* inPipeLines */
        },
        {
            FVID2_DF_BGR16_565,             /* inDataFmt */
            FVID2_DF_YUV422I_YUYV,          /* inDataFmt */
        },
        {
            1280U,                          /* inWidth */
            1280U,                          /* inWidth */
        },
        {
            720U,                           /* inHeight */
            720U,                           /* inHeight */
        },
        {
            640U,                           /* inTarWidth */
            640U,                           /* inTarWidth */
        },
        {
            480U,                           /* inTarHeight */
            480U,                           /* inTarHeight */
        },
        FVID2_DF_YUV422I_YUYV,              /* outDataFmt */
        1280U,                              /* outWidth */
        720U,                               /* outHeight */
        1280U,                              /* ovlyWidth */
        720U,                               /* ovlyHeight */
        FALSE,                              /* cropEnable */
        {
            0                               /* cropCfg - NA */
        },
        M2MWB_BANDWIDTH_CONTROL_NONE,       /* bandwidth control */
        M2MDSS_APP_TOTAL_LOOP_COUNT,        /* runCount */
#if defined (SOC_TDA3XX)
        0xC5A56880U,                        /* crcValue */
#else
        0x7319A3C8U,                        /* crcValue */
#endif
    },
/* PDP-1402: GFX WB not working on TDA2xx */
#if defined (SOC_TDA3XX)
    {
        /* Test case id. */
        12U,
        "VID1 YUV422+VID2 BGR565+GPX1 RGB888    -> LCD1 WB YUV422_YUYV 720P",
        VPS_DSS_DISPC_WB_IN_NODE_LCD1,      /* wbInNode */
        3U,                                 /* numInPipeLines */
        {
            VPS_DSS_DISPC_PIPE_VID1,        /* inPipeLines */
            VPS_DSS_DISPC_PIPE_VID2,        /* inPipeLines */
            VPS_DSS_DISPC_PIPE_GFX1,        /* inPipeLines */
        },
        {
            FVID2_DF_YUV422I_YUYV,          /* inDataFmt */
            FVID2_DF_BGR16_565,             /* inDataFmt */
            FVID2_DF_BGR24_888,             /* inDataFmt */
        },
        {
            1280U,                          /* inWidth */
            1280U,                          /* inWidth */
            1280U,                          /* inWidth */
        },
        {
            720U,                           /* inHeight */
            720U,                           /* inHeight */
            720U,                           /* inHeight */
        },
        {
            640U,                           /* inTarWidth */
            640U,                           /* inTarWidth */
            1280U,                          /* inWidth */
        },
        {
            480U,                           /* inTarHeight */
            480U,                           /* inTarHeight */
            720U,                           /* inHeight */
        },
        FVID2_DF_YUV422I_YUYV,              /* outDataFmt */
        1280U,                              /* outWidth */
        720U,                               /* outHeight */
        1280U,                              /* ovlyWidth */
        720U,                               /* ovlyHeight */
        FALSE,                              /* cropEnable */
        {
            0                               /* cropCfg - NA */
        },
        M2MWB_BANDWIDTH_CONTROL_NONE,       /* bandwidth control */
        M2MDSS_APP_TOTAL_LOOP_COUNT,        /* runCount */
#if defined (SOC_TDA3XX)
        0X556E0BB0U,                        /* crcValue */
#else
        0x12D30794U,                        /* crcValue */
#endif
    },
#endif
/* PDP-1425: writeback in YUV420 with scaling in WB pipe not working on TDA3xx */
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_TDA2EX) || defined (SOC_AM571x)
    {
        /* Test case id. */
        13U,
        "VID1 YUV422_YUYV 1080P                 -> WB YUV420SP 720P (Scaling in WB pipe)",
        VPS_DSS_DISPC_WB_IN_NODE_VID1,      /* wbInNode */
        1U,                                 /* numInPipeLines */
        {
            VPS_DSS_DISPC_PIPE_VID1,        /* inPipeLines */
        },
        {
            FVID2_DF_YUV422I_YUYV,          /* inDataFmt */
        },
        {
            1920U,                          /* inWidth */
        },
        {
            1080U,                          /* inHeight */
        },
        {
            1920U,                          /* inTarWidth */
        },
        {
            1080U,                          /* inTarHeight */
        },
        FVID2_DF_YUV420SP_UV,               /* outDataFmt */
        1280U,                              /* outWidth */
        720U,                               /* outHeight */
        0U,                                 /* ovlyWidth - NA */
        0U,                                 /* ovlyHeight - NA */
        FALSE,                              /* cropEnable */
        {
            0                               /* cropCfg - NA */
        },
        M2MWB_BANDWIDTH_CONTROL_NONE,       /* bandwidth control */
        M2MDSS_APP_TOTAL_LOOP_COUNT,        /* runCount */
        #if defined (SOC_TDA3XX)
        0x754CABABU,                        /* crcValue */
        #else
        0x38EF8E02U,                        /* crcValue */
        #endif
    },
#endif
#if 0
    /* PDP-2075 Disabled the Crop Testcases. */
#if defined (SOC_TDA3XX)
    /* Crop Testcases, Applicable only for tda3xx. */
    {
        /* Test case id. */
        14U,
        "VID1 BGR888 720P                       -> WB YUV422I_YUYV 480P RB CROP",
        VPS_DSS_DISPC_WB_IN_NODE_LCD1,      /* wbInNode */
        1U,                                 /* numInPipeLines */
        {
            VPS_DSS_DISPC_PIPE_VID1,        /* inPipeLines */
        },
        {
            FVID2_DF_BGR24_888,             /* inDataFmt */
        },
        {
            1280U,                          /* inWidth */
        },
        {
            720U,                           /* inHeight */
        },
        {
            1280U,                          /* inTarWidth */
        },
        {
            720U,                           /* inTarHeight */
        },
        FVID2_DF_YUV422I_YUYV,              /* outDataFmt */
        720U,                               /* outWidth */
        480U,                               /* outHeight */
        1280U,                              /* ovlyWidth */
        720U,                               /* ovlyHeight */
        TRUE,                               /* cropEnable */
        {                                   /* cropCfg */
            0U,                             /* cropStartX */
            0U,                             /* cropStartY */
            720U,                           /* cropWidth */
            480U,                           /* cropHeight */
        },
        M2MWB_BANDWIDTH_CONTROL_NONE,       /* bandwidth control */
        M2MDSS_APP_TOTAL_LOOP_COUNT,        /* runCount */
        0xA923C506U,                        /* crcValue */
    },
#endif
#endif
    {
        /* Test case id. */
        15U,
        "VID1 YUV422_YUYV 720P                  -> WB BGR888 1080P (BW Ctrld: 120 idle cycle)",
        VPS_DSS_DISPC_WB_IN_NODE_VID1,      /* wbInNode */
        1U,                                 /* numInPipeLines */
        {
            VPS_DSS_DISPC_PIPE_VID1,        /* inPipeLines */
        },
        {
            FVID2_DF_YUV422I_YUYV,          /* inDataFmt */
        },
        {
            1280U,                          /* inWidth */
        },
        {
            720U,                           /* inHeight */
        },
        {
            1280U,                          /* inTarWidth */
        },
        {
            720U,                           /* inTarHeight */
        },
        FVID2_DF_BGR24_888,                 /* outDataFmt */
        1920U,                              /* outWidth */
        1080U,                              /* outHeight */
        0U,                                 /* ovlyWidth - NA */
        0U,                                 /* ovlyHeight - NA */
        FALSE,                              /* cropEnable */
        {
            0                               /* cropCfg - NA */
        },
        {
            15U,
            1U
        },       /* bandwidth control */
        M2MDSS_APP_TOTAL_LOOP_COUNT,        /* runCount */
#if defined (SOC_TDA3XX)
        0xE716D39EU,                        /* crcValue */
#else
        0xD46C7FA4U,                        /* crcValue */
#endif
    },
    {
        /* Test case id. */
        16U,
        "VID1 YUV422_YUYV 720P                  -> WB BGR888 1080P (BW Ctrld: 80 idle cycle)",
        VPS_DSS_DISPC_WB_IN_NODE_VID1,      /* wbInNode */
        1U,                                 /* numInPipeLines */
        {
            VPS_DSS_DISPC_PIPE_VID1,        /* inPipeLines */
        },
        {
            FVID2_DF_YUV422I_YUYV,          /* inDataFmt */
        },
        {
            1280U,                          /* inWidth */
        },
        {
            720U,                           /* inHeight */
        },
        {
            1280U,                          /* inTarWidth */
        },
        {
            720U,                           /* inTarHeight */
        },
        FVID2_DF_BGR24_888,                 /* outDataFmt */
        1920U,                              /* outWidth */
        1080U,                              /* outHeight */
        0U,                                 /* ovlyWidth - NA */
        0U,                                 /* ovlyHeight - NA */
        FALSE,                              /* cropEnable */
        {
            0                               /* cropCfg - NA */
        },
        {
            10U,
            1U
        },       /* bandwidth control */
        M2MDSS_APP_TOTAL_LOOP_COUNT,        /* runCount */
#if defined (SOC_TDA3XX)
        0xE716D39EU,                        /* crcValue */
#else
        0xD46C7FA4U,                        /* crcValue */
#endif
    },
    {
        /* Test case id. */
        17U,
        "VID1 YUV422_YUYV 720P                  -> WB BGR888 1080P (BW Ctrld: 40 idle cycle)",
        VPS_DSS_DISPC_WB_IN_NODE_VID1,      /* wbInNode */
        1U,                                 /* numInPipeLines */
        {
            VPS_DSS_DISPC_PIPE_VID1,        /* inPipeLines */
        },
        {
            FVID2_DF_YUV422I_YUYV,          /* inDataFmt */
        },
        {
            1280U,                          /* inWidth */
        },
        {
            720U,                           /* inHeight */
        },
        {
            1280U,                          /* inTarWidth */
        },
        {
            720U,                           /* inTarHeight */
        },
        FVID2_DF_BGR24_888,                 /* outDataFmt */
        1920U,                              /* outWidth */
        1080U,                              /* outHeight */
        0U,                                 /* ovlyWidth - NA */
        0U,                                 /* ovlyHeight - NA */
        FALSE,                              /* cropEnable */
        {
            0                               /* cropCfg - NA */
        },
        {
            5U,
            1U
        },       /* bandwidth control */
        M2MDSS_APP_TOTAL_LOOP_COUNT,        /* runCount */
#if defined (SOC_TDA3XX)
        0xE716D39EU,                        /* crcValue */
#else
        0xD46C7FA4U,                        /* crcValue */
#endif
    },
};

#define M2MDSS_APP_NUM_TESTS            (sizeof (gM2mDssAppTestPrms) / \
                                            sizeof (gM2mDssAppTestPrms[0U]))
#define M2MDSS_APP_AUTORUN_OPT          (50U)
#define M2MDSS_APP_EXIT_OPT             (100U)

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/*
 * Application main
 */
int main(void)
{
    static Char stdin_buf[BUFSIZ];

    /* Provide buffer so that STDIO library will use this memory instead of
     * allocating from system heap, which might lead to false system leak
     * warning */
    setvbuf(stdin, stdin_buf, _IOLBF, BUFSIZ);

    /* Create test task */
    M2mDssApp_createTsk();

    /* Start BIOS */
    BIOS_start();

    return (0);
}

/*
 * Create test task
 */
static void M2mDssApp_createTsk(void)
{
    Task_Params tskPrms;

    /* Create test task */
    Task_Params_init(&tskPrms);
    tskPrms.priority      = M2MDSS_APP_TSK_PRI_MAIN;
    tskPrms.stack         = gM2mDssAppTskStackMain;
    tskPrms.stackSize     = sizeof (gM2mDssAppTskStackMain);
    tskPrms.arg0          = (UArg) & gM2mDssAppObj;
    gM2mDssAppObj.tskHandle = Task_create(M2mDssApp_tskMain, &tskPrms, NULL);
    GT_assert(BspAppTrace, (gM2mDssAppObj.tskHandle != NULL));

    /* Register the task to the load module for calculating the load */
    BspUtils_prfLoadRegister(gM2mDssAppObj.tskHandle, APP_NAME);

    return;
}

/*
 * Test task main
 */
static void M2mDssApp_tskMain(UArg arg0, UArg arg1)
{
    Int32                       testId;
    M2mDssApp_Obj              *appObj = (M2mDssApp_Obj *) arg0;
    const M2mDssApp_TestParams *testPrms;
    BspUtils_MemHeapStatus      startHeapStat, startHeapStat1;

    GT_0trace(BspAppTrace, GT_INFO,
              APP_NAME ": Sample Application - STARTS !!!\r\n");
    BspUtils_memGetHeapStat(&startHeapStat);
    M2mDssApp_init(appObj);

    appObj->enableAutoRun = (UInt32) FALSE;
    while (1U)
    {
        /* Get the TestId */
        testId = M2mDssApp_getTestId(appObj);
        if ((testId >= 0) && (testId < M2MDSS_APP_NUM_TESTS))
        {
            testPrms = &gM2mDssAppTestPrms[testId];
            BspUtils_memGetHeapStat(&startHeapStat1);

            BspUtils_appServiceWatchdog();
            M2mDssApp_runTest(appObj, testPrms);

            BspUtils_memCheckHeapStat(&startHeapStat1);
        }
        else
        {
            /* Exit */
            break;
        }
    }

    M2mDssApp_deInit(appObj);

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

static void M2mDssApp_init(M2mDssApp_Obj *appObj)
{
    Int32  retVal = FVID2_SOK;
    UInt32 isI2cInitReq;

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
        retVal = M2mDssApp_allocInBuf();
    }

    if (FVID2_SOK == retVal)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": M2mDssApp_init() - DONE !!!\r\n");
    }

    return;
}

static void M2mDssApp_deInit(M2mDssApp_Obj *appObj)
{
    Int32  retVal = FVID2_SOK;
    UInt32 isI2cInitReq;

    retVal = M2mDssApp_freeInBuf();
    if (FVID2_SOK == retVal)
    {
        /* System de-init */
        isI2cInitReq = TRUE;
        retVal       = BspUtils_appDefaultDeInit(isI2cInitReq);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": System De-Init Failed!!!\r\n");
        }
    }

    if (FVID2_SOK == retVal)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": M2mDssApp_deInit() - DONE !!!\r\n");
    }

    return;
}

/**
 *  M2mDssApp_runTest
 *  M2M DSS test function.
 */
static Int32 M2mDssApp_runTest(M2mDssApp_Obj              *appObj,
                               const M2mDssApp_TestParams *testPrms)
{
    Int32               retVal = FVID2_SOK;
    UInt32              frmId;
    BspUtils_PrfTsHndl *prfTsHandle;
    Fvid2_FrameList     inFrmList, outFrmList;

    BspUtils_memcpy(&appObj->testPrms, testPrms, sizeof (appObj->testPrms));

    /* Start the TimeStamp Calculation */
    prfTsHandle = BspUtils_prfTsCreate(APP_NAME ":");

    /* Create driver */
    retVal = M2mDssApp_create(appObj);

    if (FVID2_SOK == retVal)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Starting M2M DSS Test... !!!\r\n");

        /* Start the load calculation */
        BspUtils_prfLoadCalcStart();
        BspUtils_prfTsBegin(prfTsHandle);

        /* Prime all available buffers - this tests the driver queuing model */
        for (frmId = 0U; frmId < M2MDSS_APP_NUM_OUT_BUFFERS; frmId++)
        {
            /* Update the buffer address */
            M2mDssApp_updateFrameList(appObj, &inFrmList, &outFrmList);
            retVal = Fvid2_processRequest(
                        appObj->drvHandle, &inFrmList, &outFrmList);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          APP_NAME ": Queue Failed!!!\r\n");
                break;
            }
            appObj->completedLoopCnt++;
        }

        while (appObj->completedLoopCnt < M2MDSS_APP_TOTAL_LOOP_COUNT)
        {
            /* Wait till frames get processed */
            Semaphore_pend(appObj->reqCompleteSem, BIOS_WAIT_FOREVER);

            retVal = Fvid2_getProcessedRequest(
                         appObj->drvHandle,
                         &inFrmList,
                         &outFrmList,
                         FVID2_TIMEOUT_NONE);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          APP_NAME ": Dequeue Failed!!!\r\n");
            }

            if (FVID2_SOK == retVal)
            {
                /* Update the buffer address */
                M2mDssApp_updateFrameList(appObj, &inFrmList, &outFrmList);
                retVal = Fvid2_processRequest(
                            appObj->drvHandle, &inFrmList, &outFrmList);
                if (FVID2_SOK != retVal)
                {
                    GT_0trace(BspAppTrace, GT_ERR,
                              APP_NAME ": Queue Failed!!!\r\n");
                }
            }

            if (FVID2_SOK != retVal)
            {
                break;
            }

            appObj->completedLoopCnt++;
        }

        /* Wait till all primed frames get processed */
        for (frmId = 0U; frmId < M2MDSS_APP_NUM_OUT_BUFFERS; frmId++)
        {
            Semaphore_pend(appObj->reqCompleteSem, BIOS_WAIT_FOREVER);

            retVal = Fvid2_getProcessedRequest(
                         appObj->drvHandle,
                         &inFrmList,
                         &outFrmList,
                         FVID2_TIMEOUT_NONE);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          APP_NAME ": Dequeue Failed!!!\r\n");
            }
        }

        /* Stop the load calculation */
        /* End of timestamp addition */
        BspUtils_prfTsEnd(prfTsHandle, M2MDSS_APP_TOTAL_LOOP_COUNT);
        BspUtils_prfLoadCalcStop();

        /* Print the load */
        BspUtils_prfLoadPrintAll(TRUE);
        /* print the fps based on TimeStamp */
        BspUtils_prfTsPrint(prfTsHandle, TRUE);
        /* Reset the load */
        BspUtils_prfLoadCalcReset();
        /* Delete the timestamp instance */
        BspUtils_prfTsDelete(prfTsHandle);
    }

    if (FVID2_SOK == retVal)
    {
        /* Delete driver */
        retVal = M2mDssApp_delete(appObj);
    }

    /* Print the load */
    BspUtils_prfLoadPrintAll(TRUE);
    /* Reset the load */
    BspUtils_prfLoadCalcReset();

    GT_0trace(BspAppTrace, GT_INFO,
              APP_NAME ": M2M DSS Test Completed!!!\r\n");

    return (retVal);
}

static Int32 M2mDssApp_create(M2mDssApp_Obj *appObj)
{
    Int32               retVal = FVID2_SOK;
    Semaphore_Params    semPrms;

    Semaphore_Params_init(&semPrms);
    appObj->reqCompleteSem = Semaphore_create(0, &semPrms, NULL);
    if (NULL == appObj->reqCompleteSem)
    {
        GT_1trace(BspAppTrace, GT_ERR, "%s: Sem alloc failed\r\n", APP_NAME);
        retVal = FVID2_EALLOC;
    }

    if (FVID2_SOK == retVal)
    {
        M2mDssApp_initParams(appObj);

        appObj->drvHandle = Fvid2_create(
            FVID2_VPS_DSS_M2M_DRV,
            VPS_M2M_DSS_INST_WB1,
            &appObj->createPrms,
            &appObj->createStatus,
            &appObj->cbPrms);
        if ((NULL == appObj->drvHandle) ||
            (appObj->createStatus.retVal != FVID2_SOK))
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Create Failed!!!\r\n");
            retVal = appObj->createStatus.retVal;
        }
    }

    if (FVID2_SOK == retVal)
    {
        retVal = Fvid2_control(
            appObj->drvHandle,
            IOCTL_VPS_M2M_DSS_SET_PARAMS,
            &appObj->dssPrms,
            NULL);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": DSS Set Params IOCTL Failed!!!\r\n");
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Allocate output buffers */
        retVal = M2mDssApp_allocOutBuf(appObj);
        if (FVID2_SOK != retVal)
        {
            GT_3trace(BspAppTrace, GT_ERR,
                      "%s: Error %d @ line %d\r\n", __FUNCTION__, retVal, __LINE__);
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Init buffers */
        M2mDssApp_initFrames(appObj);

        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Create complete!!\r\n");
    }

    return (retVal);
}

static Int32 M2mDssApp_delete(M2mDssApp_Obj *appObj)
{
    char           userInput;
    Int32          retVal;
    char           fileNameString[100];
    char           fileStr[30];
    UInt32         bytesWritten, crcValue;

    retVal = Fvid2_delete(appObj->drvHandle, NULL);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Delete Failed!!!\r\n");
    }
    Semaphore_delete(&appObj->reqCompleteSem);

    /* Wait for user to save the output buffers */
    if ((FVID2_SOK == retVal) && (NULL != appObj->outSaveBuf))
    {
        BspOsal_cacheInv(appObj->outSaveBuf,
                (appObj->outBufSize * M2MDSS_APP_NUM_OUT_BUFFERS),
                BSP_OSAL_CT_ALL,
                BSP_OSAL_WAIT_FOREVER);

        /* Check CRC */
        crcValue = BspUtils_appGetCrc(
                       appObj->outSaveBuf,
                       (appObj->outBufSize * M2MDSS_APP_NUM_OUT_BUFFERS));
        GT_2trace(BspAppTrace, GT_INFO,
                  "%s: Writeback Buffer CRC32 value: 0x%0.8x!!\r\n",
                  APP_NAME, crcValue);
        if (crcValue != appObj->testPrms.crcValue)
        {
            GT_3trace(
                BspAppTrace, GT_INFO,
                "%s: Warning: CRC32 value 0x%0.8x doesn't match "
                "with expected CRC32 of 0x%0.8x!!\r\n",
                APP_NAME, crcValue, appObj->testPrms.crcValue);
        }

        /* Save output buffer to memory */
        GT_1trace(BspAppTrace, GT_INFO,
                  "%s: Saving output buffers to file in SD card...\r\n", APP_NAME);
        snprintf(fileStr, sizeof(fileStr), "dssWbOpt%d", appObj->testPrms.testId);
        BspUtils_appGetFileName(
            fileNameString,
            sizeof(fileNameString),
            fileStr,
            appObj->dssPrms.outPipePrms.outFmt.dataFormat,
            appObj->dssPrms.outPipePrms.outFmt.width,
            appObj->dssPrms.outPipePrms.outFmt.height);
        BspUtils_appPrintSaveRawCmd(
            fileStr,
            appObj->outSaveBuf,
            appObj->dssPrms.outPipePrms.outFmt.dataFormat,
            appObj->dssPrms.outPipePrms.outFmt.width,
            appObj->dssPrms.outPipePrms.outFmt.height,
            (appObj->outBufSize * M2MDSS_APP_NUM_OUT_BUFFERS));
        if (BSP_SOK != BspUtils_appSaveFileToSd(
                fileNameString,
                "/dssm2mwb_output_files",
                appObj->outSaveBuf,
                (appObj->outBufSize * M2MDSS_APP_NUM_OUT_BUFFERS),
                &bytesWritten))
        {
            GT_0trace(BspAppTrace, GT_INFO,
                "Couldnot save buffer to SD card. \r\n"
                "Waiting for 2 min to save buffer from scripting console"
                "Press any key (in UART console) after saving buffer.\r\n");
            BspUtils_uartGetChar(&userInput, 120);
        }
    }

    /* Free the allocated output buffer memory */
    retVal += M2mDssApp_freeOutBuf(appObj);
    if (FVID2_SOK != retVal)
    {
        GT_3trace(BspAppTrace, GT_ERR,
                  "%s: Error %d @ line %d\r\n", __FUNCTION__, retVal,
                  __LINE__);
    }

    if (FVID2_SOK == retVal)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Delete complete!!\r\n");
    }

    return (retVal);
}

/**
 *  M2mDssApp_cbFxn
 *  \brief Driver callback function.
 */
static Int32 M2mDssApp_cbFxn(Fvid2_Handle handle, Ptr appData, Ptr reserved)
{
    Int32           retVal  = FVID2_SOK;
    M2mDssApp_Obj  *appObj = (M2mDssApp_Obj *) appData;

    /* Transfer complete. Signal it */
    Semaphore_post(appObj->reqCompleteSem);

    return (retVal);
}

/**
 *  M2mDssApp_updateFrameList
 *  Updates the frame list with the next request buffer information.
 */
static void M2mDssApp_updateFrameList(M2mDssApp_Obj     *appObj,
                                      Fvid2_FrameList   *inFrmList,
                                      Fvid2_FrameList   *outFrmList)
{
    UInt32 pipeId;

    /* Use the same input buffer for all channels */
    if (M2MDSS_APP_NUM_IN_BUFFERS == appObj->inBufIdx)
    {
        appObj->inBufIdx = 0U;
    }
    if (M2MDSS_APP_NUM_OUT_BUFFERS == appObj->outBufIdx)
    {
        appObj->outBufIdx = 0U;
    }

    Fvid2FrameList_init(inFrmList);
    Fvid2FrameList_init(outFrmList);
    for (pipeId = 0U; pipeId < appObj->testPrms.numInPipeLines; pipeId++)
    {
        inFrmList->frames[pipeId] =
            &appObj->inFrames[pipeId][appObj->outBufIdx];
    }
    inFrmList->numFrames = appObj->testPrms.numInPipeLines;
    appObj->inBufIdx++;

    outFrmList->frames[0U] = &appObj->outFrames[appObj->outBufIdx];
    outFrmList->numFrames = 1U;
    appObj->outBufIdx++;

    return;
}

/**
 *  M2mDssApp_initParams
 *  Initialize the global variables and frame pointers.
 */
static void M2mDssApp_initParams(M2mDssApp_Obj *appObj)
{
    UInt32              pipeId;
    Vps_M2mDssParams   *dssPrms;
    Fvid2_Format       *inFmt, *outFmt;
    Fvid2_CropConfig   *pipeCropCfg;

    /* Init other globals used in buffer exchange */
    appObj->inBufIdx         = 0U;
    appObj->outBufIdx        = 0U;
    appObj->completedLoopCnt = 0U;

    appObj->drvHandle                   = NULL;
    Fvid2CbParams_init(&appObj->cbPrms);
    appObj->cbPrms.cbFxn                = &M2mDssApp_cbFxn;
    appObj->cbPrms.appData              = appObj;

    /* Init create params */
    VpsM2mDssCreateParams_init(&appObj->createPrms);
    appObj->createPrms.wbInNode         = appObj->testPrms.wbInNode;
    appObj->createPrms.numInPipeLines   = appObj->testPrms.numInPipeLines;

    /* Init DSS params */
    dssPrms = &appObj->dssPrms;
    VpsM2mDssParams_init(dssPrms);
    dssPrms->ovlyWidth                  = appObj->testPrms.ovlyWidth;
    dssPrms->ovlyHeight                 = appObj->testPrms.ovlyHeight;

    /* Init DSS out params */
    Fvid2CropConfig_init(&dssPrms->outPipePrms.cropCfg);
    dssPrms->outPipePrms.memType            = VPS_VPDMA_MT_NONTILEDMEM;
    dssPrms->outPipePrms.scEnable           = FALSE;
    if (TRUE == VpsDss_isWbInNodeFromOvly(appObj->testPrms.wbInNode))
    {
        if ((appObj->testPrms.ovlyWidth != appObj->testPrms.outWidth) ||
            (appObj->testPrms.ovlyHeight != appObj->testPrms.outHeight))
        {
            dssPrms->outPipePrms.scEnable   = TRUE;
        }
    }
    else
    {
        if ((appObj->testPrms.inWidth[0U] != appObj->testPrms.outWidth) ||
            (appObj->testPrms.inHeight[0U] != appObj->testPrms.outHeight))
        {
            dssPrms->outPipePrms.scEnable   = TRUE;
        }
    }
    dssPrms->outPipePrms.cscFullRngEnable   = TRUE;
    dssPrms->outPipePrms.cropEnable         = appObj->testPrms.cropEnable;
    if (TRUE == appObj->testPrms.cropEnable)
    {
        pipeCropCfg = &dssPrms->outPipePrms.cropCfg;
        pipeCropCfg->cropStartX = appObj->testPrms.cropCfg.cropStartX;
        pipeCropCfg->cropStartY = appObj->testPrms.cropCfg.cropStartY;
        pipeCropCfg->cropWidth  = appObj->testPrms.cropCfg.cropWidth;
        pipeCropCfg->cropHeight = appObj->testPrms.cropCfg.cropHeight;
    }
    VpsDssDispcAdvWbDmaConfig_init(&appObj->advDmaCfg);
    appObj->advDmaCfg.idleNumber = appObj->testPrms.bwCfg.idleNumber;
    appObj->advDmaCfg.idleSize   = appObj->testPrms.bwCfg.idleSize;
    dssPrms->outPipePrms.advDmaCfg          = &appObj->advDmaCfg;
    outFmt                                  = &dssPrms->outPipePrms.outFmt;
    outFmt->dataFormat                      = appObj->testPrms.outDataFmt;
    outFmt->width                           = appObj->testPrms.outWidth;
    outFmt->height                          = appObj->testPrms.outHeight;
    if (Fvid2_isDataFmtSemiPlanar(outFmt->dataFormat))
    {
        outFmt->pitch[FVID2_YUV_SP_Y_ADDR_IDX] =
            VpsUtils_align(appObj->testPrms.outWidth, VPS_BUFFER_ALIGNMENT);
        outFmt->pitch[FVID2_YUV_SP_CBCR_ADDR_IDX] =
            outFmt->pitch[FVID2_YUV_SP_Y_ADDR_IDX];
    }
    else if (Fvid2_isDataFmtYuv422I(outFmt->dataFormat))
    {
        outFmt->pitch[FVID2_YUV_INT_ADDR_IDX] =
            VpsUtils_align(appObj->testPrms.outWidth * 2U, VPS_BUFFER_ALIGNMENT);
    }
    else if (Fvid2_isDataFmtRgb16bit(outFmt->dataFormat))
    {
        outFmt->pitch[FVID2_YUV_INT_ADDR_IDX] =
            VpsUtils_align(appObj->testPrms.outWidth * 2U, VPS_BUFFER_ALIGNMENT);
    }
    else if (Fvid2_isDataFmtRgb24bit(outFmt->dataFormat))
    {
        /* Align the pitch to BPP boundary as well since the pitch
         * aligined to VPS_BUFFER_ALIGNMENT may not be multiple of 3
         * bytes (1 pixel) */
        outFmt->pitch[FVID2_RGB_ADDR_IDX] =
            VpsUtils_align(appObj->testPrms.outWidth * 3U,
                           (VPS_BUFFER_ALIGNMENT * 3U));
    }
    else if (Fvid2_isDataFmtRgb32bit(outFmt->dataFormat))
    {
        /* Align the pitch to BPP boundary as well since the pitch
         * aligined to VPS_BUFFER_ALIGNMENT may not be multiple of 3
         * bytes (1 pixel) */
        outFmt->pitch[FVID2_RGB_ADDR_IDX] =
            VpsUtils_align(appObj->testPrms.outWidth * 4U, VPS_BUFFER_ALIGNMENT);
    }

    /* Init DSS in params */
    for (pipeId = 0U; pipeId < appObj->testPrms.numInPipeLines; pipeId++)
    {
        appObj->createPrms.inPipeLines[pipeId]  =
            appObj->testPrms.inPipeLines[pipeId];
        dssPrms->inPipePrms[pipeId].inPipeId    =
            appObj->testPrms.inPipeLines[pipeId];
        inFmt               = &dssPrms->inPipePrms[pipeId].inFmt;
        inFmt->width        = appObj->testPrms.inWidth[pipeId];
        inFmt->height       = appObj->testPrms.inHeight[pipeId];
        inFmt->dataFormat   = appObj->testPrms.inDataFmt[pipeId];
        dssPrms->inPipePrms[pipeId].tarWidth  =
            appObj->testPrms.inTarWidth[pipeId];
        dssPrms->inPipePrms[pipeId].tarHeight =
            appObj->testPrms.inTarHeight[pipeId];
        dssPrms->inPipePrms[pipeId].posX    = 0U;
        dssPrms->inPipePrms[pipeId].posY    = 0U;
        if (TRUE == VpsDss_isWbInNodeFromOvly(appObj->testPrms.wbInNode))
        {
            /* position the pipeline frames side-by-side vertically centered
             * in the overlay */
            dssPrms->inPipePrms[pipeId].posX =
                pipeId * (appObj->testPrms.ovlyWidth -
                            appObj->testPrms.inTarWidth[pipeId]);
            dssPrms->inPipePrms[pipeId].posY =
                (appObj->testPrms.ovlyHeight -
                    appObj->testPrms.inTarHeight[pipeId]) / 2U;
        }
        dssPrms->inPipePrms[pipeId].memType = VPS_VPDMA_MT_NONTILEDMEM;
        if (Fvid2_isDataFmtSemiPlanar(inFmt->dataFormat))
        {
            inFmt->pitch[FVID2_YUV_SP_Y_ADDR_IDX] =
                VpsUtils_align(M2MDSS_APP_BUF_WIDTH, VPS_BUFFER_ALIGNMENT);
            inFmt->pitch[FVID2_YUV_SP_CBCR_ADDR_IDX] =
                inFmt->pitch[FVID2_YUV_SP_Y_ADDR_IDX];
        }
        else if (Fvid2_isDataFmtYuv422I(inFmt->dataFormat))
        {
            inFmt->pitch[FVID2_YUV_INT_ADDR_IDX] =
                VpsUtils_align(M2MDSS_APP_BUF_WIDTH * 2U, VPS_BUFFER_ALIGNMENT);
        }
        else if (Fvid2_isDataFmtRgb16bit(inFmt->dataFormat))
        {
            inFmt->pitch[FVID2_YUV_INT_ADDR_IDX] =
                VpsUtils_align(M2MDSS_APP_BUF_WIDTH * 2U, VPS_BUFFER_ALIGNMENT);
        }
        else if (Fvid2_isDataFmtRgb24bit(inFmt->dataFormat))
        {
            /* Align the pitch to BPP boundary as well since the pitch
             * aligined to VPS_BUFFER_ALIGNMENT may not be multiple of 3
             * bytes (1 pixel) */
            inFmt->pitch[FVID2_RGB_ADDR_IDX] =
                VpsUtils_align(M2MDSS_APP_BUF_WIDTH * 3U,
                               (VPS_BUFFER_ALIGNMENT * 3U));
        }
        else if (Fvid2_isDataFmtRgb32bit(inFmt->dataFormat))
        {
            /* Align the pitch to BPP boundary as well since the pitch
             * aligined to VPS_BUFFER_ALIGNMENT may not be multiple of 3
             * bytes (1 pixel) */
            inFmt->pitch[FVID2_RGB_ADDR_IDX] =
                VpsUtils_align(M2MDSS_APP_BUF_WIDTH * 4U, VPS_BUFFER_ALIGNMENT);
        }

        /* Enable/disable scaling based on target size in overlay */
        dssPrms->inPipePrms[pipeId].vidCfg.pipeCfg.scEnable = FALSE;
        if ((appObj->testPrms.inWidth[pipeId] !=
                appObj->testPrms.inTarWidth[pipeId]) ||
            (appObj->testPrms.inHeight[pipeId] !=
                appObj->testPrms.inTarHeight[pipeId]))
        {
            dssPrms->inPipePrms[pipeId].vidCfg.pipeCfg.scEnable = TRUE;
        }

        dssPrms->inPipePrms[pipeId].ovlyPipeCfg.pipeLine        =
            appObj->testPrms.inPipeLines[pipeId];
        /* Each pipe should have different Z-order */
        dssPrms->inPipePrms[pipeId].ovlyPipeCfg.zorder          = pipeId;
        dssPrms->inPipePrms[pipeId].ovlyPipeCfg.zorderEnable    = TRUE;
        dssPrms->inPipePrms[pipeId].ovlyPipeCfg.globalAlpha     = 0xFFU;
        if ((TRUE == VpsDss_isWbInNodeFromOvly(appObj->testPrms.wbInNode)) &&
            (dssPrms->inPipePrms[pipeId].inPipeId == VPS_DSS_DISPC_PIPE_GFX1))
        {
            /* Use 50% transparency for GRPX pipeline going to overlay */
            dssPrms->inPipePrms[pipeId].ovlyPipeCfg.globalAlpha = 0x7FU;

            /* Enable color keying */
            dssPrms->ovlyCfg.colorKeyEnable     = TRUE;
            dssPrms->ovlyCfg.colorKeySel        =
                VPS_DSS_DISPC_TRANS_COLOR_KEY_SRC;
            dssPrms->ovlyCfg.transColorKey      = 0x00000000U;
            dssPrms->ovlyCfg.backGroundColor    = 0x00000000U;
            dssPrms->ovlyCfg.alphaBlenderEnable = FALSE;
        }
    }

    return;
}

/**
 *  M2mDssApp_getTestId
 *  Return the test ID to run.
 */
static Int32 M2mDssApp_getTestId(M2mDssApp_Obj *appObj)
{
    UInt32       testCnt;
    Int32        retVal = BSP_SOK;
    Int32        testId = 0;
    static UInt32 timeoutVal = BSP_UTILS_UART_RX_DEFAULT_TIMEOUT;

    GT_0trace(BspAppTrace, GT_INFO, " \r\n");
    GT_0trace(BspAppTrace, GT_INFO,
              "--------------------------------------\r\n");
    GT_0trace(BspAppTrace, GT_INFO,
              "Select test to run as per below table:\r\n");
    GT_0trace(BspAppTrace, GT_INFO,
              "--------------------------------------\r\n");
    GT_0trace(BspAppTrace, GT_INFO, " \r\n");
    for (testCnt = 0; testCnt < M2MDSS_APP_NUM_TESTS; testCnt++)
    {
        GT_2trace(BspAppTrace, GT_INFO, "%3d: %s\r\n",
            gM2mDssAppTestPrms[testCnt].testId,
            gM2mDssAppTestPrms[testCnt].testDescStr);
    }
    GT_2trace(BspAppTrace, GT_INFO,
              "%3d: %s\r\n", M2MDSS_APP_AUTORUN_OPT, "Auto Run\r\n");
    GT_1trace(BspAppTrace, GT_INFO, "%3d: EXIT\r\n", 100);
    GT_0trace(BspAppTrace, GT_INFO, " \r\n");
    GT_0trace(BspAppTrace, GT_INFO,
        "Enter Test to Run (in UART console): \r\n");

    if (TRUE == appObj->enableAutoRun)
    {
        gTestIdx++;
        if (gTestIdx < M2MDSS_APP_NUM_TESTS)
        {
            GT_2trace(BspAppTrace, GT_INFO, "%d: %s\r\n",
                gM2mDssAppTestPrms[gTestIdx].testId,
                gM2mDssAppTestPrms[gTestIdx].testDescStr);
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
                gTestIdx = 0;
                GT_2trace(BspAppTrace, GT_INFO, "%d: %s\r\n",
                    gM2mDssAppTestPrms[gTestIdx].testId,
                    gM2mDssAppTestPrms[gTestIdx].testDescStr);
                break;
            }
            else
            {
                timeoutVal = BSP_UTILS_UART_RX_WAIT_FOREVER;
            }
            gTestIdx = M2mDssApp_getTestIndex(testId);

            if ((gTestIdx >= 0) && (gTestIdx < M2MDSS_APP_NUM_TESTS))
            {
                GT_1trace(BspAppTrace, GT_INFO, "%d\r\n", testId);
                break;
            }
            if (M2MDSS_APP_AUTORUN_OPT == testId)
            {
                appObj->enableAutoRun = (UInt32) TRUE;
                gTestIdx = 0;
                GT_2trace(BspAppTrace, GT_INFO, "%d: %s\r\n",
                    gM2mDssAppTestPrms[gTestIdx].testId,
                    gM2mDssAppTestPrms[gTestIdx].testDescStr);
                break;
            }
            else if (M2MDSS_APP_EXIT_OPT == testId)
            {
                gTestIdx = M2MDSS_APP_EXIT_OPT;
                break;
            }
            GT_0trace(BspAppTrace, GT_INFO, "Invalid Test ID. Enter Agian!!\r\n");
        }
    }

    return (gTestIdx);
}

static Int32 M2mDssApp_getTestIndex(Int32 testId)
{
    Int32  testIdx;
    UInt32 testIdFound = FALSE;
    for (testIdx = 0; testIdx < M2MDSS_APP_NUM_TESTS; testIdx++)
    {
        if(testId == gM2mDssAppTestPrms[testIdx].testId)
        {
            testIdFound = TRUE;
            break;
        }
    }
    if(testIdFound == FALSE)
    {
        testIdx = -1;
    }
    return testIdx;
}
