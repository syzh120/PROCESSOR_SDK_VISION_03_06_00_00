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
 *  \file st_vpeTestCases.h
 *
 *  \brief This file defines the test cases for VPE UT.
 */

#ifndef _ST_VPE_TEST_CASES_H_
#define _ST_VPE_TEST_CASES_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <testLib/st_vpe.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define ST_VPE_NUM_TESTCASES        ((sizeof (gStVpeTestCasePrms)) / \
                                     (sizeof (st_VpeTestCaseParams)))

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief Defines the various VPE test cases. */
static st_VpeTestCaseParams gStVpeTestCasePrms[] =
{
    /* enableTest, testCaseId, testCaseType,
     * *reqId,
     * *testCaseName,
     * *disableReason
     * numHandles, handleCfgId[],
     * numCh[],
     * chCfgId[],
     * *loadBufCfg, lazyLoadingEnable, printEnable,
     * testType,
     * crcCheckEnable,
     * crcValue[]
     */
    /**************************************************************************/
    /*                         Load buffer Test Cases                         */
    /**************************************************************************/
    {
        TEST_ENABLE, 0u, ST_VPE_TCT_LOAD_BUFFER, NULL,
        "Load Buffer", NULL,
        0u,{VPS_M2M_INST_VPE1        }, {ST_VPE_HCID_NONE},
        {0u                       }, {ST_VPE_CCID_NONE},
        &gVpeUtLoadBufCfg[0u], LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_MISC),
        CRCCHECK_DISABLE,
        {
            0u
        }
    },
    {
        TEST_ENABLE, 0u, ST_VPE_TCT_LOAD_BUFFER, NULL,
        "Load Buffer", NULL,
        0u, {VPS_M2M_INST_VPE1}, {ST_VPE_HCID_NONE},
        {0u}, {ST_VPE_CCID_NONE},
        &gVpeUtLoadBufCfg[1u], LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_MISC),
        CRCCHECK_DISABLE,
        {
            0u
        }
    },
    {
        TEST_ENABLE, 0u, ST_VPE_TCT_LOAD_BUFFER, NULL,
        "Load Buffer", NULL,
        0u, {VPS_M2M_INST_VPE1}, {ST_VPE_HCID_NONE},
        {0u}, {ST_VPE_CCID_NONE},
        &gVpeUtLoadBufCfg[2u], LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_MISC),
        CRCCHECK_DISABLE,
        {
            0u
        }
    },
    {
        TEST_ENABLE, 0u, ST_VPE_TCT_LOAD_BUFFER, NULL,
        "Load Buffer", NULL,
        0u, {VPS_M2M_INST_VPE1}, {ST_VPE_HCID_NONE},
        {0u}, {ST_VPE_CCID_NONE},
        &gVpeUtLoadBufCfg[3u], LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_MISC),
        CRCCHECK_DISABLE,
        {
            0u
        }
    },
    {
        TEST_ENABLE, 0u, ST_VPE_TCT_LOAD_BUFFER, NULL,
        "Load Buffer", NULL,
        0u, {VPS_M2M_INST_VPE1}, {ST_VPE_HCID_NONE},
        {0u}, {ST_VPE_CCID_NONE},
        &gVpeUtLoadBufCfg[4u], LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_MISC),
        CRCCHECK_DISABLE,
        {
            0u
        }
    },
    {
        TEST_ENABLE, 0u, ST_VPE_TCT_LOAD_BUFFER, NULL,
        "Load Buffer", NULL,
        0u, {VPS_M2M_INST_VPE1}, {ST_VPE_HCID_NONE},
        {0u}, {ST_VPE_CCID_NONE},
        &gVpeUtLoadBufCfg[5u], LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_MISC),
        CRCCHECK_DISABLE,
        {
            0u
        }
    },

    /**************************************************************************/
    /*                     YUYV422I to YUYV422I Test Cases                    */
    /**************************************************************************/
    /*
     * Single handle, Single channel, different sizes with DEI OFF
     */
    {
        TEST_ENABLE, 1u, ST_VPE_TCT_MAIN,
        ":PDK-1144:PDK-1145:PDK-1146:PDK-1147:PDK-1148:PDK-1149:PDK-1150:PDK-1152:PDK-1161:PDK-1167:PDK-1168:PDK-1169:PDK-1173:PDK-1175:PDK-1186:PDK-1188:PDK-1189:PDK-1199:PDK-1200:PDK-1203:PDK-1204:",
        "VPE1_1H_1CH_D1_YUYV422I_CIF_YUYV422I_DEIOFF_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUYV422I_TO_CIF_YUYV422I_P_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_PERFORMANCE),
        CRCCHECK_ENABLE,
        {
            0x7A62A986u
        }
    },
    {
        TEST_ENABLE, 2u, ST_VPE_TCT_MAIN,
        ":PDK-1200:PDK-1204:PDK-1200:PDK-1204:",
        "VPE1_1H_1CH_D1_YUYV422I_D1_YUYV422I_DEIOFF_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUYV422I_TO_D1_YUYV422I_P_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0x827F22FBu
        }
    },
    {
        TEST_ENABLE, 3u, ST_VPE_TCT_MAIN,
        ":PDK-1200:PDK-1204:PDK-1183:PDK-1184:PDK-1185:PDK-1187:PDK-1200:PDK-1204:",
        "VPE1_1H_1CH_D1_YUYV422I_720P_YUYV422I_DEIOFF_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUYV422I_TO_720P_YUYV422I_P_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0x353A4AE4u
        }
    },
    {
        TEST_ENABLE, 4u, ST_VPE_TCT_MAIN,
        ":PDK-1200:PDK-1204:PDK-1161:PDK-1185:PDK-1200:PDK-1204:",
        "VPE1_1H_1CH_D1_YUYV422I_1080P_YUYV422I_DEIOFF_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUYV422I_TO_1080P_YUYV422I_P_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_PERFORMANCE),
        CRCCHECK_ENABLE,
        {
            0x157ABECDu
        }
    },
    {
        TEST_ENABLE, 5u, ST_VPE_TCT_MAIN,
        ":PDK-1200:PDK-1204:PDK-1200:PDK-1204:",
        "VPE1_1H_1CH_WXGA_YUYV422I_1080P_YUYV422I_DEIOFF_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_WXGA_YUYV422I_TO_1080P_YUYV422I_P_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0x0B879231u
        }
    },
    {
        TEST_ENABLE, 6u, ST_VPE_TCT_MAIN,
        ":PDK-1200:PDK-1204:PDK-1200:PDK-1204:",
        "VPE1_1H_1CH_CIF_YUYV422I_D1_YUYV422I_DEIOFF_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_CIF_YUYV422I_TO_D1_YUYV422I_P_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0x7916D4FEu
        }
    },
    {
        TEST_ENABLE, 7u, ST_VPE_TCT_MAIN,
        ":PDK-1160:PDK-1200:PDK-1204:",
        "VPE1_1H_1CH_1080P_YUYV422I_1080P_YUYV422I_DEIOFF_4SubFrame",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_1080P_YUYV422I_TO_1080P_YUYV422I_P_TO_P_4SUBFRM
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_PERFORMANCE),
        CRCCHECK_ENABLE,
        {
            0xAB689CBBu
        }
    },
    /*
     * Single handle, Single channel, different sizes with DEI ON
     */
    {
        TEST_ENABLE, 21u, ST_VPE_TCT_MAIN,
        ":PDK-1200:PDK-1204:PDK-1151:PDK-1161:PDK-1172:PDK-1173:PDK-1174:PDK-1179:PDK-1180:PDK-1181:PDK-1182:PDK-1200:PDK-1204:",
        "VPE1_1H_1CH_D1_YUYV422I_CIF_YUYV422I_DEION_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUYV422I_TO_CIF_YUYV422I_I_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_PERFORMANCE),
        CRCCHECK_ENABLE,
        {
            0xFA81D521u
        }
    },
    {
        TEST_ENABLE, 22u, ST_VPE_TCT_MAIN,
        ":PDK-1200:PDK-1204:PDK-1200:PDK-1204:",
        "VPE1_1H_1CH_D1_YUYV422I_D1_YUYV422I_DEION_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUYV422I_TO_D1_YUYV422I_I_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_REGRESSION | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0xD9BA4E21u
        }
    },
    {
        TEST_ENABLE, 23u, ST_VPE_TCT_MAIN,
        ":PDK-1200:PDK-1204:PDK-1200:PDK-1204:",
        "VPE1_1H_1CH_D1_YUYV422I_720P_YUYV422I_DEION_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUYV422I_TO_720P_YUYV422I_I_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0x5848F6F2u
        }
    },
    {
        TEST_ENABLE, 24u, ST_VPE_TCT_MAIN,
        ":PDK-1200:PDK-1204:PDK-1200:PDK-1204:",
        "VPE1_1H_1CH_D1_YUYV422I_1080P_YUYV422I_DEION_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUYV422I_TO_1080P_YUYV422I_I_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_REGRESSION | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0x9D11E1B7u
        }
    },

    /**************************************************************************/
    /*                     YUV420SPUV to YUYV422I Test Cases                  */
    /**************************************************************************/
    /*
     * Single handle, Single channel, different sizes with DEI OFF
     */
    {
        TEST_ENABLE, 201u, ST_VPE_TCT_MAIN,
        ":PDK-1202:PDK-1204:PDK-1171:PDK-1176:PDK-1177:PDK-1197:PDK-1198:PDK-1202:PDK-1204:",
        "VPE1_1H_1CH_D1_YUV420SPUV_CIF_YUYV422I_DEIOFF_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUV420SPUV_TO_CIF_YUYV422I_P_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_REGRESSION | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0x2CF31A2Cu
        }
    },
    {
        TEST_ENABLE, 202u, ST_VPE_TCT_MAIN,
        ":PDK-1202:PDK-1204:PDK-1202:PDK-1204:",
        "VPE1_1H_1CH_D1_YUV420SPUV_D1_YUYV422I_DEIOFF_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUV420SPUV_TO_D1_YUYV422I_P_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0xC60D82E9u
        }
    },
    {
        TEST_ENABLE, 203u, ST_VPE_TCT_MAIN,
        ":PDK-1202:PDK-1204:PDK-1202:PDK-1204:",
        "VPE1_1H_1CH_D1_YUV420SPUV_720P_YUYV422I_DEIOFF_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUV420SPUV_TO_720P_YUYV422I_P_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0x0C395504u
        }
    },
    {
        TEST_ENABLE, 204u, ST_VPE_TCT_MAIN,
        ":PDK-1202:PDK-1204:PDK-1202:PDK-1204:",
        "VPE1_1H_1CH_D1_YUV420SPUV_D1_YUYV422I_DEIOFF_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUV420SPUV_TO_D1_YUYV422I_P_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0xC60D82E9u
        }
    },
    {
        TEST_ENABLE, 205u, ST_VPE_TCT_MAIN,
        ":PDK-1202:PDK-1204:PDK-1202:PDK-1204:",
        "VPE1_1H_1CH_WXGA_YUV420SPUV_1080P_YUYV422I_DEIOFF_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_WXGA_YUV420SPUV_TO_1080P_YUYV422I_P_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0xF44863C3u
        }
    },
    {
        TEST_ENABLE, 206u, ST_VPE_TCT_MAIN,
        ":PDK-1202:PDK-1204:PDK-1202:PDK-1204:",
        "VPE1_1H_1CH_CIF_YUV420SPUV_D1_YUYV422I_DEIOFF_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_CIF_YUV420SPUV_TO_D1_YUYV422I_P_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0xE82207D6u
        }
    },
    /*
     * Single handle, Single channel, different sizes with DEI ON
     */
    {
        TEST_ENABLE, 221u, ST_VPE_TCT_MAIN,
        ":PDK-1202:PDK-1204:PDK-1178:PDK-1202:PDK-1204:",
        "VPE1_1H_1CH_D1_YUV420SPUV_CIF_YUYV422I_DEION_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUV420SPUV_TO_CIF_YUYV422I_I_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0x7281C3B3u
        }
    },
    {
        TEST_ENABLE, 222u, ST_VPE_TCT_MAIN,
        ":PDK-1202:PDK-1204:PDK-1202:PDK-1204:",
        "VPE1_1H_1CH_D1_YUV420SPUV_D1_YUYV422I_DEION_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUV420SPUV_TO_D1_YUYV422I_I_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0x7E1BC127u
        }
    },
    {
        TEST_ENABLE, 223u, ST_VPE_TCT_MAIN,
        ":PDK-1202:PDK-1204:PDK-1202:PDK-1204:",
        "VPE1_1H_1CH_D1_YUV420SPUV_720P_YUYV422I_DEION_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUV420SPUV_TO_720P_YUYV422I_I_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0x23C618CAu
        }
    },
    {
        TEST_ENABLE, 224u, ST_VPE_TCT_MAIN,
        ":PDK-1202:PDK-1204:PDK-1202:PDK-1204:",
        "VPE1_1H_1CH_D1_YUV420SPUV_1080P_YUYV422I_DEION_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUV420SPUV_TO_1080P_YUYV422I_I_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0x38CE1952u
        }
    },

    /**************************************************************************/
    /*                     YUV422SPUV to YUYV422I Test Cases                  */
    /**************************************************************************/
    /*
     * Single handle, Single channel, different sizes with DEI OFF
     */
    {
        TEST_ENABLE, 401u, ST_VPE_TCT_MAIN,
        ":PDK-1201:PDK-1204:PDK-1201:PDK-1204:",
        "VPE1_1H_1CH_D1_YUV422SPUV_CIF_YUYV422I_DEIOFF_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUV422SPUV_TO_CIF_YUYV422I_P_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_REGRESSION | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0x7A62A986u
        }
    },
    {
        TEST_ENABLE, 402u, ST_VPE_TCT_MAIN,
        ":PDK-1201:PDK-1204:PDK-1201:PDK-1204:",
        "VPE1_1H_1CH_D1_YUV422SPUV_D1_YUYV422I_DEIOFF_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUV422SPUV_TO_D1_YUYV422I_P_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0x827F22FBu
        }
    },
    {
        TEST_ENABLE, 403u, ST_VPE_TCT_MAIN,
        ":PDK-1201:PDK-1204:PDK-1201:PDK-1204:",
        "VPE1_1H_1CH_D1_YUV422SPUV_720P_YUYV422I_DEIOFF_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUV422SPUV_TO_720P_YUYV422I_P_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0x353A4AE4u
        }
    },
    {
        TEST_ENABLE, 404u, ST_VPE_TCT_MAIN,
        ":PDK-1201:PDK-1204:PDK-1201:PDK-1204:",
        "VPE1_1H_1CH_D1_YUV422SPUV_D1_YUYV422I_DEIOFF_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUV422SPUV_TO_D1_YUYV422I_P_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0x827F22FBu
        }
    },
    {
        TEST_ENABLE, 405u, ST_VPE_TCT_MAIN,
        ":PDK-1201:PDK-1204:PDK-1201:PDK-1204:",
        "VPE1_1H_1CH_WXGA_YUV422SPUV_1080P_YUYV422I_DEIOFF_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_WXGA_YUV422SPUV_TO_1080P_YUYV422I_P_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0x0B879231u
        }
    },
    {
        TEST_ENABLE, 406u, ST_VPE_TCT_MAIN,
        ":PDK-1201:PDK-1204:PDK-1201:PDK-1204:",
        "VPE1_1H_1CH_CIF_YUV422SPUV_D1_YUYV422I_DEIOFF_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_CIF_YUV422SPUV_TO_D1_YUYV422I_P_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0x7916D4FEu
        }
    },
    /*
     * Single handle, Single channel, different sizes with DEI ON
     */
    {
        TEST_ENABLE, 421u, ST_VPE_TCT_MAIN,
        ":PDK-1201:PDK-1204:PDK-1201:PDK-1204:",
        "VPE1_1H_1CH_D1_YUV422SPUV_CIF_YUYV422I_DEION_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUV422SPUV_TO_CIF_YUYV422I_I_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_REGRESSION | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0xFA81D521u
        }
    },
    {
        TEST_ENABLE, 422u, ST_VPE_TCT_MAIN,
        ":PDK-1201:PDK-1204:PDK-1201:PDK-1204:",
        "VPE1_1H_1CH_D1_YUV422SPUV_D1_YUYV422I_DEION_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUV422SPUV_TO_D1_YUYV422I_I_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0xD9BA4E21u
        }
    },
    {
        TEST_ENABLE, 423u, ST_VPE_TCT_MAIN,
        ":PDK-1201:PDK-1204:PDK-1201:PDK-1204:",
        "VPE1_1H_1CH_D1_YUV422SPUV_720P_YUYV422I_DEION_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUV422SPUV_TO_720P_YUYV422I_I_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0x5848F6F2u
        }
    },
    {
        TEST_ENABLE, 424u, ST_VPE_TCT_MAIN,
        ":PDK-1201:PDK-1204:PDK-1201:PDK-1204:",
        "VPE1_1H_1CH_D1_YUV422SPUV_1080P_YUYV422I_DEION_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUV422SPUV_TO_1080P_YUYV422I_I_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0x9D11E1B7u
        }
    },

    /**************************************************************************/
    /*                     YUYV422I to YUV420SPUV Test Cases                  */
    /**************************************************************************/
    /*
     * Single handle, Single channel, different sizes with DEI OFF
     */
    {
        TEST_ENABLE, 601u, ST_VPE_TCT_MAIN,
        ":PDK-1200:PDK-1206:",
        "VPE1_1H_1CH_D1_YUYV422I_CIF_YUV420SPUV_DEIOFF_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUYV422I_TO_CIF_YUV420SPUV_P_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_REGRESSION | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0x9D1B47B2u
        }
    },
    {
        TEST_ENABLE, 602u, ST_VPE_TCT_MAIN,
        ":PDK-1200:PDK-1206:",
        "VPE1_1H_1CH_D1_YUYV422I_D1_YUV420SPUV_DEIOFF_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUYV422I_TO_D1_YUV420SPUV_P_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0x6D7CB5D7u
        }
    },
    {
        TEST_ENABLE, 603u, ST_VPE_TCT_MAIN,
        ":PDK-1200:PDK-1206:",
        "VPE1_1H_1CH_D1_YUYV422I_1080P_YUV420SPUV_DEIOFF_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUYV422I_TO_1080P_YUV420SPUV_P_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0xFAEBCA85u
        }
    },
    /*
     * Single handle, Single channel, different sizes with DEI ON
     */
    {
        TEST_ENABLE, 621u, ST_VPE_TCT_MAIN,
        ":PDK-1200:PDK-1206:",
        "VPE1_1H_1CH_D1_YUYV422I_CIF_YUV420SPUV_DEION_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUYV422I_TO_CIF_YUV420SPUV_I_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_REGRESSION | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0x1A942CCAu
        }
    },
    {
        TEST_ENABLE, 622u, ST_VPE_TCT_MAIN,
        ":PDK-1200:PDK-1206:",
        "VPE1_1H_1CH_D1_YUYV422I_D1_YUV420SPUV_DEION_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUYV422I_TO_D1_YUV420SPUV_I_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0xC8A19865u
        }
    },
    {
        TEST_ENABLE, 623u, ST_VPE_TCT_MAIN,
        ":PDK-1200:PDK-1206:",
        "VPE1_1H_1CH_D1_YUYV422I_1080P_YUV420SPUV_DEION_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUYV422I_TO_1080P_YUV420SPUV_I_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0xF78311E2u
        }
    },

    /**************************************************************************/
    /*                     YUYV422I to YUV422SPUV Test Cases                  */
    /**************************************************************************/
    /*
     * Single handle, Single channel, different sizes with DEI OFF
     */
    {
        TEST_ENABLE, 801u, ST_VPE_TCT_MAIN,
        ":PDK-1200:PDK-1205:",
        "VPE1_1H_1CH_D1_YUYV422I_CIF_YUV422SPUV_DEIOFF_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUYV422I_TO_CIF_YUV422SPUV_P_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_REGRESSION | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0xF7A8121Au
        }
    },
    {
        TEST_ENABLE, 802u, ST_VPE_TCT_MAIN,
        ":PDK-1200:PDK-1205:",
        "VPE1_1H_1CH_D1_YUYV422I_D1_YUV422SPUV_DEIOFF_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUYV422I_TO_D1_YUV422SPUV_P_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0x386B59A7u
        }
    },
    {
        TEST_ENABLE, 803u, ST_VPE_TCT_MAIN,
        ":PDK-1200:PDK-1205:",
        "VPE1_1H_1CH_D1_YUYV422I_1080P_YUV422SPUV_DEIOFF_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUYV422I_TO_1080P_YUV422SPUV_P_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0x539A9396u
        }
    },
    /*
     * Single handle, Single channel, different sizes with DEI ON
     */
    {
        TEST_ENABLE, 821u, ST_VPE_TCT_MAIN,
        ":PDK-1200:PDK-1205:",
        "VPE1_1H_1CH_D1_YUYV422I_CIF_YUV422SPUV_DEION_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUYV422I_TO_CIF_YUV422SPUV_I_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_REGRESSION | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0x6F9069E6u
        }
    },
    {
        TEST_ENABLE, 822u, ST_VPE_TCT_MAIN,
        ":PDK-1200:PDK-1205:",
        "VPE1_1H_1CH_D1_YUYV422I_D1_YUV422SPUV_DEION_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUYV422I_TO_D1_YUV422SPUV_I_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0xAC86E5A2u
        }
    },
    {
        TEST_ENABLE, 823u, ST_VPE_TCT_MAIN,
        ":PDK-1200:PDK-1205:",
        "VPE1_1H_1CH_D1_YUYV422I_1080P_YUV422SPUV_DEION_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUYV422I_TO_1080P_YUV422SPUV_I_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0xFD914F52u
        }
    },

    /**************************************************************************/
    /*                     YUYV422I to RGB888 Test Cases                      */
    /**************************************************************************/
    /*
     * Single handle, Single channel, different sizes with DEI OFF
     */
    {
        TEST_ENABLE, 1001u, ST_VPE_TCT_MAIN,
        ":PDK-1200:PDK-1208:PDK-1194:PDK-1195:PDK-1196:PDK-1208:",
        "VPE1_1H_1CH_D1_YUYV422I_CIF_RGB888_DEIOFF_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUYV422I_TO_CIF_RGB888_P_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_REGRESSION | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0x3D17755Fu
        }
    },
    {
        TEST_ENABLE, 1002u, ST_VPE_TCT_MAIN,
        ":PDK-1200:PDK-1208:",
        "VPE1_1H_1CH_D1_YUYV422I_D1_RGB888_DEIOFF_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUYV422I_TO_D1_RGB888_P_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0x4AF742FBu
        }
    },
    {
        TEST_ENABLE, 1003u, ST_VPE_TCT_MAIN,
        ":PDK-1200:PDK-1208:",
        "VPE1_1H_1CH_D1_YUYV422I_1080P_RGB888_DEIOFF_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUYV422I_TO_1080P_RGB888_P_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0x34F065AFu
        }
    },
    {
        TEST_ENABLE, 1004u, ST_VPE_TCT_MAIN,
        ":PDK-1200:PDK-1208:PDK-1170:PDK-1208:",
        "VPE1_1H_1CH_1080P_YUYV422I_1080P_RGB888_DEIOFF_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_1080P_YUYV422I_TO_1080P_RGB888_P_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0xC533B4BEu
        }
    },
    /*
     * Single handle, Single channel, different sizes with DEI ON
     */
    {
        TEST_ENABLE, 1021u, ST_VPE_TCT_MAIN,
        ":PDK-1200:PDK-1208:",
        "VPE1_1H_1CH_D1_YUYV422I_CIF_RGB888_DEION_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUYV422I_TO_CIF_RGB888_I_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_REGRESSION | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0x69B5ACF8u
        }
    },
    {
        TEST_ENABLE, 1022u, ST_VPE_TCT_MAIN,
        ":PDK-1200:PDK-1208:",
        "VPE1_1H_1CH_D1_YUYV422I_D1_RGB888_DEION_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUYV422I_TO_D1_RGB888_I_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0x8B2B18BEu
        }
    },
    {
        TEST_ENABLE, 1023u, ST_VPE_TCT_MAIN,
        ":PDK-1200:PDK-1208:",
        "VPE1_1H_1CH_D1_YUYV422I_1080P_RGB888_DEION_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUYV422I_TO_1080P_RGB888_I_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0xEBA6334Bu
        }
    },

    /**************************************************************************/
    /*                     YUYV422I to YUV444I Test Cases                     */
    /**************************************************************************/
    /*
     * Single handle, Single channel, different sizes with DEI OFF
     */
    {
        TEST_ENABLE, 1101u, ST_VPE_TCT_MAIN,
        ":PDK-1200:PDK-1207:",
        "VPE1_1H_1CH_D1_YUYV422I_CIF_YUV444I_DEIOFF_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUYV422I_TO_CIF_YUV444I_P_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_REGRESSION | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0x16AA3A8Eu
        }
    },
    {
        TEST_ENABLE, 1102u, ST_VPE_TCT_MAIN,
        ":PDK-1200:PDK-1207:",
        "VPE1_1H_1CH_D1_YUYV422I_D1_YUV444I_DEIOFF_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUYV422I_TO_D1_YUV444I_P_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0xC2B052B5u
        }
    },
    {
        TEST_ENABLE, 1103u, ST_VPE_TCT_MAIN,
        ":PDK-1200:PDK-1207:",
        "VPE1_1H_1CH_D1_YUYV422I_1080P_YUV444I_DEIOFF_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUYV422I_TO_1080P_YUV444I_P_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0x9E1C0469u
        }
    },
    {
        TEST_ENABLE, 1104u, ST_VPE_TCT_MAIN,
        ":PDK-1200:PDK-1207:",
        "VPE1_1H_1CH_1080P_YUYV422I_1080P_YUV444I_DEIOFF_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_1080P_YUYV422I_TO_1080P_YUV444I_P_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0x4D91E2DCu
        }
    },
    /*
     * Single handle, Single channel, different sizes with DEI ON
     */
    {
        TEST_ENABLE, 1121u, ST_VPE_TCT_MAIN,
        ":PDK-1200:PDK-1207:",
        "VPE1_1H_1CH_D1_YUYV422I_CIF_YUV444I_DEION_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUYV422I_TO_CIF_YUV444I_I_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_REGRESSION | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0x8E6D24CFu
        }
    },
    {
        TEST_ENABLE, 1122u, ST_VPE_TCT_MAIN,
        ":PDK-1200:PDK-1207:",
        "VPE1_1H_1CH_D1_YUYV422I_D1_YUV444I_DEION_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUYV422I_TO_D1_YUV444I_I_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0xEF8BFC92u
        }
    },
    {
        TEST_ENABLE, 1123u, ST_VPE_TCT_MAIN,
        ":PDK-1200:PDK-1207:",
        "VPE1_1H_1CH_D1_YUYV422I_1080P_YUV444I_DEION_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUYV422I_TO_1080P_YUV444I_I_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0xE7486EEDu
        }
    },

    /**************************************************************************/
    /*                     YUV420SPUV to YUV420SPUV Test Cases                */
    /**************************************************************************/
    /*
     * Single handle, Single channel, different sizes with DEI OFF
     */
    {
        TEST_ENABLE, 1201u, ST_VPE_TCT_MAIN,
        ":PDK-1202:PDK-1206:",
        "VPE1_1H_1CH_D1_YUV420SPUV_1080P_YUV420SPUV_DEIOFF_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUV420SPUV_TO_1080P_YUV420SPUV_P_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0x8C95A9CAu
        }
    },

    /**************************************************************************/
    /*                     YUV420SPUV to YUV422SPUV Test Cases                */
    /**************************************************************************/
    /*
     * Single handle, Single channel, different sizes with DEI OFF
     */
    {
        TEST_ENABLE, 1301u, ST_VPE_TCT_MAIN,
        ":PDK-1202:PDK-1205:",
        "VPE1_1H_1CH_D1_YUV420SPUV_1080P_YUV422SPUV_DEIOFF_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUV420SPUV_TO_1080P_YUV422SPUV_P_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0x7B4DAD0Fu
        }
    },

    /**************************************************************************/
    /*                     YUV420SPUV to RGB888 Test Cases                    */
    /**************************************************************************/
    /*
     * Single handle, Single channel, different sizes with DEI OFF
     */
    {
        TEST_ENABLE, 1401u, ST_VPE_TCT_MAIN,
        ":PDK-1202:PDK-1208:",
        "VPE1_1H_1CH_D1_YUV420SPUV_1080P_RGB888_DEIOFF_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUV420SPUV_TO_1080P_RGB888_P_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0x28F9B29Du
        }
    },

    /**************************************************************************/
    /*                     YUV420SPUV to YUV444I Test Cases                   */
    /**************************************************************************/
    /*
     * Single handle, Single channel, different sizes with DEI OFF
     */
    {
        TEST_ENABLE, 1501u, ST_VPE_TCT_MAIN,
        ":PDK-1202:PDK-1207:",
        "VPE1_1H_1CH_D1_YUV420SPUV_1080P_YUV444I_DEIOFF_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUV420SPUV_TO_1080P_YUV444I_P_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0xA499E42Au
        }
    },

    /**************************************************************************/
    /*                     YUV422SPUV to YUV420SPUV Test Cases                */
    /**************************************************************************/
    /*
     * Single handle, Single channel, different sizes with DEI OFF
     */
    {
        TEST_ENABLE, 1601u, ST_VPE_TCT_MAIN,
        ":PDK-1201:PDK-1206:",
        "VPE1_1H_1CH_D1_YUV422SPUV_1080P_YUV420SPUV_DEIOFF_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUV422SPUV_TO_1080P_YUV420SPUV_P_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0x7B4DAD0Fu
        }
    },

    /**************************************************************************/
    /*                     YUV420SPUV to YUV422SPUV Test Cases                */
    /**************************************************************************/
    /*
     * Single handle, Single channel, different sizes with DEI OFF
     */
    {
        TEST_ENABLE, 1701u, ST_VPE_TCT_MAIN,
        ":PDK-1201:PDK-1205:",
        "VPE1_1H_1CH_D1_YUV420SPUV_1080P_YUV422SPUV_DEIOFF_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUV420SPUV_TO_1080P_YUV422SPUV_P_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0x7B4DAD0Fu
        }
    },

    /**************************************************************************/
    /*                     YUV420SPUV to RGB888 Test Cases                    */
    /**************************************************************************/
    /*
     * Single handle, Single channel, different sizes with DEI OFF
     */
    {
        TEST_ENABLE, 1801u, ST_VPE_TCT_MAIN,
        ":PDK-1201:PDK-1208:",
        "VPE1_1H_1CH_D1_YUV420SPUV_1080P_RGB888_DEIOFF_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUV420SPUV_TO_1080P_RGB888_P_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0x28F9B29Du
        }
    },

    /**************************************************************************/
    /*                     YUV420SPUV to YUV444I Test Cases                   */
    /**************************************************************************/
    /*
     * Single handle, Single channel, different sizes with DEI OFF
     */
    {
        TEST_ENABLE, 1901u, ST_VPE_TCT_MAIN,
        ":PDK-1201:PDK-1207:",
        "VPE1_1H_1CH_D1_YUV420SPUV_1080P_YUV444I_DEIOFF_Default",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUV420SPUV_TO_1080P_YUV444I_P_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0xA499E42Au
        }
    },

    /**************************************************************************/
    /*               Single handle, Multi-channel Test Cases                  */
    /**************************************************************************/
    {
        TEST_ENABLE, 2001u, ST_VPE_TCT_MAIN,
        ":PDK-1155:PDK-1161:",
        "VPE1_1H_4CH_D1_YUYV422I_CIF_YUYV422I_DEIOFF",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {4u},
        {
            ST_VPE_CCID_D1_YUYV422I_TO_CIF_YUYV422I_P_TO_P,
            ST_VPE_CCID_D1_YUYV422I_TO_CIF_YUYV422I_P_TO_P,
            ST_VPE_CCID_D1_YUYV422I_TO_CIF_YUYV422I_P_TO_P,
            ST_VPE_CCID_D1_YUYV422I_TO_CIF_YUYV422I_P_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_PERFORMANCE),
        CRCCHECK_ENABLE,
        {
            0x7A62A986u,
            0x7A62A986u,
            0x7A62A986u,
            0x7A62A986u
        }
    },
    {
        TEST_ENABLE, 2002u, ST_VPE_TCT_MAIN,
        ":PDK-1155:PDK-1161:",
        "VPE1_1H_8CH_D1_YUYV422I_D1_YUYV422I_DEIOFF",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {8u},
        {
            ST_VPE_CCID_D1_YUYV422I_TO_D1_YUYV422I_P_TO_P,
            ST_VPE_CCID_D1_YUYV422I_TO_D1_YUYV422I_P_TO_P,
            ST_VPE_CCID_D1_YUYV422I_TO_D1_YUYV422I_P_TO_P,
            ST_VPE_CCID_D1_YUYV422I_TO_D1_YUYV422I_P_TO_P,
            ST_VPE_CCID_D1_YUYV422I_TO_D1_YUYV422I_P_TO_P,
            ST_VPE_CCID_D1_YUYV422I_TO_D1_YUYV422I_P_TO_P,
            ST_VPE_CCID_D1_YUYV422I_TO_D1_YUYV422I_P_TO_P,
            ST_VPE_CCID_D1_YUYV422I_TO_D1_YUYV422I_P_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_PERFORMANCE),
        CRCCHECK_ENABLE,
        {
            0x827F22FBu,
            0x827F22FBu,
            0x827F22FBu,
            0x827F22FBu,
            0x827F22FBu,
            0x827F22FBu,
            0x827F22FBu,
            0x827F22FBu
        }
    },
    {
        TEST_ENABLE, 2003u, ST_VPE_TCT_MAIN,
        ":PDK-1155:",
        "VPE1_1H_12CH_D1_YUYV422I_CIF_YUYV422I_DEIOFF",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {12u},
        {
            ST_VPE_CCID_D1_YUYV422I_TO_CIF_YUYV422I_P_TO_P,
            ST_VPE_CCID_D1_YUYV422I_TO_CIF_YUYV422I_P_TO_P,
            ST_VPE_CCID_D1_YUYV422I_TO_CIF_YUYV422I_P_TO_P,
            ST_VPE_CCID_D1_YUYV422I_TO_CIF_YUYV422I_P_TO_P,
            ST_VPE_CCID_D1_YUYV422I_TO_CIF_YUYV422I_P_TO_P,
            ST_VPE_CCID_D1_YUYV422I_TO_CIF_YUYV422I_P_TO_P,
            ST_VPE_CCID_D1_YUYV422I_TO_CIF_YUYV422I_P_TO_P,
            ST_VPE_CCID_D1_YUYV422I_TO_CIF_YUYV422I_P_TO_P,
            ST_VPE_CCID_D1_YUYV422I_TO_CIF_YUYV422I_P_TO_P,
            ST_VPE_CCID_D1_YUYV422I_TO_CIF_YUYV422I_P_TO_P,
            ST_VPE_CCID_D1_YUYV422I_TO_CIF_YUYV422I_P_TO_P,
            ST_VPE_CCID_D1_YUYV422I_TO_CIF_YUYV422I_P_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_REGRESSION | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0x7A62A986u,
            0x7A62A986u,
            0x7A62A986u,
            0x7A62A986u,
            0x7A62A986u,
            0x7A62A986u,
            0x7A62A986u,
            0x7A62A986u,
            0x7A62A986u,
            0x7A62A986u,
            0x7A62A986u,
            0x7A62A986u
        }
    },
    {
        TEST_ENABLE, 2004u, ST_VPE_TCT_MAIN,
        ":PDK-1155:PDK-1157:",
        "VPE1_1H_4CH_DifferentSizes_DEIOFF",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {4u},
        {
            ST_VPE_CCID_D1_YUYV422I_TO_CIF_YUYV422I_P_TO_P,
            ST_VPE_CCID_D1_YUYV422I_TO_D1_YUYV422I_P_TO_P,
            ST_VPE_CCID_D1_YUYV422I_TO_1080P_YUYV422I_P_TO_P,
            ST_VPE_CCID_CIF_YUYV422I_TO_D1_YUYV422I_P_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_REGRESSION | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0x7A62A986u,
            0x827F22FBu,
            0x157ABECDu,
            0x7916D4FEu
        }
    },
    {
        TEST_ENABLE, 2005u, ST_VPE_TCT_MAIN,
        ":PDK-1155:PDK-1157:PDK-1161:",
        "VPE1_1H_2CH_DifferentSizes_DEION",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {2u},
        {
            ST_VPE_CCID_D1_YUYV422I_TO_CIF_YUYV422I_I_TO_P,
            ST_VPE_CCID_D1_YUYV422I_TO_D1_YUYV422I_I_TO_P,
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_PERFORMANCE),
        CRCCHECK_ENABLE,
        {
            0xFA81D521u,
            0xD9BA4E21u
        }
    },
    {
        TEST_ENABLE, 2006u, ST_VPE_TCT_MAIN,
        ":PDK-1155:PDK-1157:",
        "VPE1_1H_4CH_DifferentSizes_DEION/OFF",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {4u},
        {
            ST_VPE_CCID_D1_YUYV422I_TO_CIF_YUYV422I_I_TO_P,
            ST_VPE_CCID_D1_YUYV422I_TO_D1_YUYV422I_I_TO_P,
            ST_VPE_CCID_D1_YUYV422I_TO_CIF_YUYV422I_P_TO_P,
            ST_VPE_CCID_D1_YUYV422I_TO_D1_YUYV422I_P_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0xFA81D521u,
            0xD9BA4E21u,
            0x7A62A986u,
            0x827F22FBu
        }
    },
    {
        TEST_ENABLE, 2007u, ST_VPE_TCT_MAIN,
        ":PDK-1155:PDK-1161:",
        "VPE1_1H_4CH_WXGA_YUV420SPUV_640x400_YUYV422I_AVB_MCV_2DESV_SDK_Usecases",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {4u},
        {
            ST_VPE_CCID_WXGA_YUV420SPUV_TO_640x400_YUYV422I_P_TO_P,
            ST_VPE_CCID_WXGA_YUV420SPUV_TO_640x400_YUYV422I_P_TO_P,
            ST_VPE_CCID_WXGA_YUV420SPUV_TO_640x400_YUYV422I_P_TO_P,
            ST_VPE_CCID_WXGA_YUV420SPUV_TO_640x400_YUYV422I_P_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_PERFORMANCE),
        CRCCHECK_ENABLE,
        {
            0x54A43F08u,
            0x54A43F08u,
            0x54A43F08u,
            0x54A43F08u
        }
    },
    {
        TEST_ENABLE, 2008u, ST_VPE_TCT_MAIN,
        ":PDK-1155:PDK-1161:",
        "VPE1_1H_4CH_WXGA_YUYV422I_640x400_YUYV422I_LVDS_MCV_SDK_Usecase",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {6u},
        {
            ST_VPE_CCID_WXGA_YUYV422I_TO_640x400_YUYV422I_P_TO_P,
            ST_VPE_CCID_WXGA_YUYV422I_TO_640x400_YUYV422I_P_TO_P,
            ST_VPE_CCID_WXGA_YUYV422I_TO_640x400_YUYV422I_P_TO_P,
            ST_VPE_CCID_WXGA_YUYV422I_TO_640x400_YUYV422I_P_TO_P,
            ST_VPE_CCID_WXGA_YUYV422I_TO_640x400_YUYV422I_P_TO_P,
            ST_VPE_CCID_WXGA_YUYV422I_TO_640x400_YUYV422I_P_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_PERFORMANCE),
        CRCCHECK_ENABLE,
        {
            0x31B746D8u,
            0x31B746D8u,
            0x31B746D8u,
            0x31B746D8u,
            0x31B746D8u,
            0x31B746D8u
        }
    },

    /**************************************************************************/
    /*                       Multi handle Test Cases                          */
    /**************************************************************************/
    {
        TEST_ENABLE, 2101u, ST_VPE_TCT_MAIN,
        ":PDK-1153:PDK-1156:",
        "VPE1_2H_4CH_DifferentSizes_DEIOFF",
        NULL,
        2u,
        {
            VPS_M2M_INST_VPE1,
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT,
            ST_VPE_HCID_DEFAULT
        },
        {2u, 2u},
        {
            ST_VPE_CCID_D1_YUYV422I_TO_CIF_YUYV422I_P_TO_P,
            ST_VPE_CCID_D1_YUYV422I_TO_CIF_YUYV422I_P_TO_P,
            ST_VPE_CCID_D1_YUYV422I_TO_D1_YUYV422I_P_TO_P,
            ST_VPE_CCID_D1_YUYV422I_TO_D1_YUYV422I_P_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0x7A62A986u,
            0x7A62A986u,
            0x827F22FBu,
            0x827F22FBu
        }
    },
    {
        TEST_ENABLE, 2102u, ST_VPE_TCT_MAIN,
        ":PDK-1153:PDK-1156:",
        "VPE1_4H_4CH_DifferentSizes_DEIOFF/ON",
        NULL,
        4u,
        {
            VPS_M2M_INST_VPE1,
            VPS_M2M_INST_VPE1,
            VPS_M2M_INST_VPE1,
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT,
            ST_VPE_HCID_DEFAULT,
            ST_VPE_HCID_DEFAULT,
            ST_VPE_HCID_DEFAULT
        },
        {1u, 1u, 1u, 1u},
        {
            ST_VPE_CCID_D1_YUYV422I_TO_CIF_YUYV422I_P_TO_P,
            ST_VPE_CCID_D1_YUYV422I_TO_CIF_YUYV422I_I_TO_P,
            ST_VPE_CCID_D1_YUYV422I_TO_D1_YUYV422I_P_TO_P,
            ST_VPE_CCID_D1_YUYV422I_TO_D1_YUYV422I_I_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0x7A62A986u,
            0xFA81D521u,
            0x827F22FBu,
            0xD9BA4E21u
        }
    },

    /**************************************************************************/
    /*                     Start/stop Test Cases                              */
    /**************************************************************************/
    {
        TEST_ENABLE, 3001u, ST_VPE_TCT_MAIN,
        ":System:",
        "VPE1_1H_1CH_D1_YUV420SPUV_CIF_YUYV422I_DEIOFF_Start/Stop",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_START_STOP
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUV420SPUV_TO_CIF_YUYV422I_P_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_DISABLE,
        (ST_TT_FULL | ST_TT_STRESS),
        CRCCHECK_DISABLE,
        {
            0u
        }
    },
    {
        TEST_ENABLE, 3002u, ST_VPE_TCT_MAIN,
        ":System:",
        "VPE1_1H_1CH_D1_YUV420SPUV_CIF_YUYV422I_DEION_Start/Stop",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_START_STOP
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUV420SPUV_TO_CIF_YUYV422I_I_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_DISABLE,
        (ST_TT_FULL | ST_TT_STRESS),
        CRCCHECK_DISABLE,
        {
            0u
        }
    },

    /**************************************************************************/
    /*                     Open/close Test Cases                              */
    /**************************************************************************/
    {
        TEST_ENABLE, 3101u, ST_VPE_TCT_MAIN,
        ":System:",
        "VPE1_1H_1CH_D1_YUV420SPUV_CIF_YUYV422I_DEIOFF_Open/Close_Start/Stop",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_OPEN_CLOSE
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUV420SPUV_TO_CIF_YUYV422I_P_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_DISABLE,
        (ST_TT_FULL | ST_TT_STRESS),
        CRCCHECK_DISABLE,
        {
            0u
        }
    },
    {
        TEST_ENABLE, 3102u, ST_VPE_TCT_MAIN,
        ":System:",
        "VPE1_1H_1CH_D1_YUV420SPUV_CIF_YUYV422I_DEION_Open/Close_Start/Stop",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_OPEN_CLOSE
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUV420SPUV_TO_CIF_YUYV422I_I_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_DISABLE,
        (ST_TT_FULL | ST_TT_STRESS),
        CRCCHECK_DISABLE,
        {
            0u
        }
    },

    /**************************************************************************/
    /*                         Misc Test Cases                                */
    /**************************************************************************/
#if 0
    {
        TEST_DISABLE, 3201u, ST_VPE_TCT_MAIN,
        ":System:",
        "VPE1_1H_1CH_D1_YUV420SPUV_CIF_YUYV422I_DEIOFF_ISR_Context",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_MISC_ISR_CTX
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUV420SPUV_TO_CIF_YUYV422I_P_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0u
        }
    },
    {
        TEST_DISABLE, 3202u, ST_VPE_TCT_MAIN,
        ":System:",
        "VPE1_1H_1CH_D1_YUV420SPUV_CIF_YUYV422I_DEION_ISR_Context",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_MISC_ISR_CTX
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUV420SPUV_TO_CIF_YUYV422I_I_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0u
        }
    },
    {
        TEST_DISABLE, 3251u, ST_VPE_TCT_MAIN,
        ":System:",
        "VPE1_1H_1CH_D1_YUV420SPUV_CIF_YUYV422I_DEIOFF_TimeStampEnabled",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_MISC_TIMESTAMP
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUV420SPUV_TO_CIF_YUYV422I_P_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_REGRESSION | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0u
        }
    },
    {
        TEST_DISABLE, 3252u, ST_VPE_TCT_MAIN,
        ":System:",
        "VPE1_1H_1CH_D1_YUV420SPUV_CIF_YUYV422I_DEION_TimeStampEnabled",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_MISC_TIMESTAMP
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUV420SPUV_TO_CIF_YUYV422I_I_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_REGRESSION | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0u
        }
    },
    {
        TEST_DISABLE, 3301u, ST_VPE_TCT_MAIN,
        ":PDK-1149:PDK-1150:",
        "VPE1_1H_1CH_D1_YUV420SPUV_CIF_YUYV422I_DEIOFF_AsyncQEnabled",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_MISC_ASYNCQ
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUV420SPUV_TO_CIF_YUYV422I_P_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_REGRESSION | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0u
        }
    },
    {
        TEST_DISABLE, 3302u, ST_VPE_TCT_MAIN,
        ":PDK-1149:PDK-1150:",
        "VPE1_1H_1CH_D1_YUV420SPUV_CIF_YUYV422I_DEION_AsyncQEnabled",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_MISC_ASYNCQ
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUV420SPUV_TO_CIF_YUYV422I_I_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_REGRESSION | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0u
        }
    },
#endif
    {
        TEST_ENABLE, 3401u, ST_VPE_TCT_MAIN,
        ":PDK-1159:PDK-1154:",
        "VPE1_1H_4CH_DifferentSizes_DEIOFF_LazyLoadingEnabled",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {4u},
        {
            ST_VPE_CCID_D1_YUYV422I_TO_CIF_YUYV422I_P_TO_P,
            ST_VPE_CCID_D1_YUYV422I_TO_D1_YUYV422I_P_TO_P,
            ST_VPE_CCID_D1_YUYV422I_TO_1080P_YUYV422I_P_TO_P,
            ST_VPE_CCID_CIF_YUYV422I_TO_D1_YUYV422I_P_TO_P
        },
        NULL, LAZY_LOAD_ENABLE, PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0x543CBD3Eu,
            0x827F22FBu,
            0xD3900D91u,
            0x9D82B553u
        }
    },
    {
        TEST_ENABLE, 3402u, ST_VPE_TCT_MAIN,
        ":PDK-1159:PDK-1154:",
        "VPE1_1H_3CH_DifferentSizes_DEION_LazyLoadingEnabled",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_DEFAULT
        },
        {3u},
        {
            ST_VPE_CCID_D1_YUYV422I_TO_CIF_YUYV422I_I_TO_P,
            ST_VPE_CCID_D1_YUYV422I_TO_D1_YUYV422I_I_TO_P,
            ST_VPE_CCID_D1_YUYV422I_TO_1080P_YUYV422I_I_TO_P
        },
        NULL, LAZY_LOAD_ENABLE, PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0xD91D9363u,
            0xD9BA4E21u,
            0x82DE89C0u
        }
    },
    /*
     * Frame drop test cases with DEI ON
     */
    {
        TEST_ENABLE, 3501u, ST_VPE_TCT_MAIN,
        ":PDK-1158:",
        "VPE1_1H_1CH_D1_YUYV422I_CIF_YUYV422I_DEION_FrameDrop(Alternate)",
        NULL,
        1u,
        {
            VPS_M2M_INST_VPE1
        },
        {
            ST_VPE_HCID_MISC_FRAMEDROP_ALTERNATE
        },
        {1u},
        {
            ST_VPE_CCID_D1_YUYV422I_TO_CIF_YUYV422I_I_TO_P
        },
        NULL, LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        CRCCHECK_ENABLE,
        {
            0x4E72F9BBu
        }
    },

    /**************************************************************************/
    /*                         Free buffer Test Cases                         */
    /**************************************************************************/
    {
        TEST_ENABLE, 0u, ST_VPE_TCT_FREE_BUFFER, NULL,
        "Free Buffer", NULL,
        0u, {VPS_M2M_INST_VPE1}, {ST_VPE_HCID_NONE},
        {0u}, {ST_VPE_CCID_NONE},
        &gVpeUtLoadBufCfg[0u], LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_MISC),
        CRCCHECK_DISABLE,
        {
            0u
        }
    },
    {
        TEST_ENABLE, 0u, ST_VPE_TCT_FREE_BUFFER, NULL,
        "Free Buffer", NULL,
        0u, {VPS_M2M_INST_VPE1}, {ST_VPE_HCID_NONE},
        {0u}, {ST_VPE_CCID_NONE},
        &gVpeUtLoadBufCfg[1u], LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_MISC),
        CRCCHECK_DISABLE,
        {
            0u
        }
    },
    {
        TEST_ENABLE, 0u, ST_VPE_TCT_FREE_BUFFER, NULL,
        "Free Buffer", NULL,
        0u, {VPS_M2M_INST_VPE1}, {ST_VPE_HCID_NONE},
        {0u}, {ST_VPE_CCID_NONE},
        &gVpeUtLoadBufCfg[2u], LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_MISC),
        CRCCHECK_DISABLE,
        {
            0u
        }
    },
    {
        TEST_ENABLE, 0u, ST_VPE_TCT_FREE_BUFFER, NULL,
        "Free Buffer", NULL,
        0u, {VPS_M2M_INST_VPE1}, {ST_VPE_HCID_NONE},
        {0u}, {ST_VPE_CCID_NONE},
        &gVpeUtLoadBufCfg[3u], LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_MISC),
        CRCCHECK_DISABLE,
        {
            0u
        }
    },
    {
        TEST_ENABLE, 0u, ST_VPE_TCT_FREE_BUFFER, NULL,
        "Free Buffer", NULL,
        0u, {VPS_M2M_INST_VPE1}, {ST_VPE_HCID_NONE},
        {0u}, {ST_VPE_CCID_NONE},
        &gVpeUtLoadBufCfg[4u], LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_MISC),
        CRCCHECK_DISABLE,
        {
            0u
        }
    },
    {
        TEST_ENABLE, 0u, ST_VPE_TCT_FREE_BUFFER, NULL,
        "Free Buffer", NULL,
        0u, {VPS_M2M_INST_VPE1}, {ST_VPE_HCID_NONE},
        {0u}, {ST_VPE_CCID_NONE},
        &gVpeUtLoadBufCfg[5u], LAZY_LOAD_DISABLE, PRINT_ENABLE,
        (ST_TT_MISC),
        CRCCHECK_DISABLE,
        {
            0u
        }
    },
};

#endif /* #ifndef _ST_VPE_TEST_CASES_H_ */
