/*
 *  Copyright (C) 2014 Texas Instruments Incorporated
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

/**
 *  \file stw_crcTestcases.h
 *
 *  \brief This file defines the test cases for CRC UT.
 */

#ifndef STW_CRC_TEST_CASES_H_
#define STW_CRC_TEST_CASES_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include<string.h>
#include <st_crc.h>
#include <ti/csl/csl_crc.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define CRC_NUM_TESTCASES   (sizeof (gCRCTestcaseParams) / sizeof (st_CRCTestcaseParams_t))

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief Defines the various CRC test cases. */
st_CRCTestcaseParams_t gCRCTestcaseParams[] =
{
    /* enableTest, testCaseId,
     * testCaseFxnPtr,
     * *reqId,
     * *testCaseName,
     * *userInfo, *disableReason
     * *passFailCriteria,
     * cpuID, dataSize, sourceMemory,
     * crcConfigParams,
     * diagLibTestParams
     * printEnable,
     * testType,
     */
    {
        TEST_ENABLE, 0U,
        &crcRunTestcase,
        NULL,
        "User defined test",
        NULL, NULL,
        NULL,
        IPU, 1024U, 0x80000000U,
        {
            DEF_CRC_CHANNEL,
            DEF_CRC_MODE,
            DEF_CRC_PATTERN_SIZE,
            DEF_CRC_PATTERN_COUNT,
            DEF_CRC_SECTOR_COUNT,
            DEF_CRC_WATCHDOG_PRELOAD,
            DEF_CRC_BLOCK_PRELOAD,
            0x0U,
            0x0U,
        },
        NULL,
        PRINT_ENABLE,
        0U,
    },
    {
        TEST_ENABLE, 1U,
        &crcRunTestcase,
        ":PDK-67:PDK-330:PDK-314:PDK-315:PDK-316:PDK-317:PDK-318:PDK-319:PDK-320:PDK-321:PDK-322:PDK-323:PDK-334:PDK-337:PDK-324:PDK-325:",
        "crc_ch1_semi_cpu_ipu_ddr",
        NULL, NULL,
        "EDMA interrupt should occur. CRC signature verification should be successful. Performance should be met with expected values",
        IPU, 4147200U, 0x80000000U,
        {
            (uint32_t) CRC_CHANNEL_1,
            (uint32_t) CRC_OPERATION_MODE_SEMICPU,
            DEF_CRC_PATTERN_SIZE,
            DEF_CRC_PATTERN_COUNT,
            DEF_CRC_SECTOR_COUNT,
            DEF_CRC_WATCHDOG_PRELOAD,
            DEF_CRC_BLOCK_PRELOAD,
            0x76474dc5U,
            0x449b086fU,
        },
        {
            0U, 0U, 0U, 0U, 0U, 0U,
            0U, 0U, 0U, 0U, 0U, 0U,
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_PERFORMANCE),
    },
    {
        TEST_ENABLE, 2U,
        &crcRunTestcase,
        ":PDK-67:PDK-330:PDK-314:PDK-315:PDK-316:PDK-317:PDK-318:PDK-319:PDK-320:PDK-321:PDK-322:PDK-323:PDK-334:PDK-337:",
        "crc_ch2_semi_cpu_ipu_control_module",
        NULL, NULL,
        "EDMA interrupt should occur. CRC signature verification should be successful.",
        IPU, 100U, 0x4a002100U,
        {
            (uint32_t) CRC_CHANNEL_2,
            (uint32_t) CRC_OPERATION_MODE_SEMICPU,
            4U,
            DEF_CRC_PATTERN_COUNT,
            DEF_CRC_SECTOR_COUNT,
            DEF_CRC_WATCHDOG_PRELOAD,
            DEF_CRC_BLOCK_PRELOAD,
            0x0U,
            0x0U,
        },
        {
            0U, 0U, 0U, 0U, 0U, 0U,
            0U, 0U, 0U, 0U, 0U, 0U,
        },
        PRINT_ENABLE,
        ST_TT_SANITY,
    },
    {
        TEST_ENABLE, 3U,
        &crcRunTestcase,
        ":PDK-67:PDK-330:PDK-314:PDK-315:PDK-316:PDK-317:PDK-318:PDK-319:PDK-320:PDK-321:PDK-322:PDK-323:PDK-335:PDK-337:PDK-324:",
        "crc_ch3_semi_cpu_dsp1_ddr",
        NULL, NULL,
        "EDMA interrupt should occur. CRC signature verification should be successful. Performance should be met with expected values",
        DSP1, 4147200U, 0x80000000U,
        {
            (uint32_t) CRC_CHANNEL_3,
            (uint32_t) CRC_OPERATION_MODE_SEMICPU,
            8U,
            DEF_CRC_PATTERN_COUNT,
            DEF_CRC_SECTOR_COUNT,
            DEF_CRC_WATCHDOG_PRELOAD,
            DEF_CRC_BLOCK_PRELOAD,
            0x76474dc5U,
            0x449b086fU,
        },
        {
            0U, 0U, 0U, 0U, 0U, 0U,
            0U, 0U, 0U, 0U, 0U, 0U,
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_PERFORMANCE),
    },
    {
        TEST_ENABLE, 4U,
        &crcRunTestcase,
        ":PDK-67:PDK-330:PDK-314:PDK-315:PDK-316:PDK-317:PDK-318:PDK-319:PDK-320:PDK-321:PDK-322:PDK-323:PDK-335:PDK-337:",
        "crc_ch4_semi_cpu_dsp1_control_module",
        NULL, NULL,
        "EDMA interrupt should occur. CRC signature verification should be successful.",
        DSP1, 100U, 0x4a002100U,
        {
            (uint32_t) CRC_CHANNEL_4,
            (uint32_t) CRC_OPERATION_MODE_SEMICPU,
            DEF_CRC_PATTERN_SIZE,
            DEF_CRC_PATTERN_COUNT,
            DEF_CRC_SECTOR_COUNT,
            DEF_CRC_WATCHDOG_PRELOAD,
            DEF_CRC_BLOCK_PRELOAD,
            0x0U,
            0x0U,
        },
        {
            0U, 0U, 0U, 0U, 0U, 0U,
            0U, 0U, 0U, 0U, 0U, 0U,
        },
        PRINT_ENABLE,
        ST_TT_SANITY,
    },
    {
        TEST_ENABLE, 5U,
        &crcRunTestcase,
        ":PDK-67:PDK-330:PDK-314:PDK-315:PDK-316:PDK-317:PDK-318:PDK-319:PDK-320:PDK-321:PDK-322:PDK-323:PDK-336:PDK-337:",
        "crc_ch1_semi_cpu_dsp2_l2ram",
        NULL, NULL,
        "EDMA interrupt should occur. CRC signature verification should be successful.",
        DSP2, 32768U, 0x41000000U,
        {
            (uint32_t) CRC_CHANNEL_1,
            (uint32_t) CRC_OPERATION_MODE_SEMICPU,
            4U,
            DEF_CRC_PATTERN_COUNT,
            DEF_CRC_SECTOR_COUNT,
            DEF_CRC_WATCHDOG_PRELOAD,
            DEF_CRC_BLOCK_PRELOAD,
            0x0U,
            0x0U,
        },
        {
            0U, 0U, 0U, 0U, 0U, 0U,
            0U, 0U, 0U, 0U, 0U, 0U,
        },
        PRINT_ENABLE,
        ST_TT_SANITY,
    },
    {
        TEST_ENABLE, 6U,
        &crcRunTestcase,
        ":PDK-67:PDK-330:PDK-314:PDK-315:PDK-316:PDK-317:PDK-318:PDK-319:PDK-320:PDK-321:PDK-322:PDK-323:PDK-336:PDK-337:",
        "crc_ch1_semi_cpu_dsp2_control_module",
        NULL, NULL,
        "EDMA interrupt should occur. CRC signature verification should be successful.",
        DSP2, 100U, 0x4a002100U,
        {
            (uint32_t) CRC_CHANNEL_1,
            (uint32_t) CRC_OPERATION_MODE_SEMICPU,
            8U,
            DEF_CRC_PATTERN_COUNT,
            DEF_CRC_SECTOR_COUNT,
            DEF_CRC_WATCHDOG_PRELOAD,
            DEF_CRC_BLOCK_PRELOAD,
            0x0U,
            0x0U,
        },
        {
            0U, 0U, 0U, 0U, 0U, 0U,
            0U, 0U, 0U, 0U, 0U, 0U,
        },
        PRINT_ENABLE,
        ST_TT_SANITY,
    },
    {
        TEST_ENABLE, 7U,
        &crcRunTestcase,
        ":PDK-67:PDK-330:PDK-314:PDK-315:PDK-316:PDK-317:PDK-318:PDK-319:PDK-320:PDK-321:PDK-322:PDK-323:PDK-331:PDK-337:PDK-327:",
        "crc_ch1_full_cpu_ipu_ddr",
        NULL, NULL,
        "CRC signature verification should be successful. Performance should be met with expected values",
        IPU, 1843200U, 0x80000000U,
        {
            (uint32_t) CRC_CHANNEL_1,
            (uint32_t) CRC_OPERATION_MODE_FULLCPU,
            4U,
            DEF_CRC_PATTERN_COUNT,
            DEF_CRC_SECTOR_COUNT,
            DEF_CRC_WATCHDOG_PRELOAD,
            DEF_CRC_BLOCK_PRELOAD,
            0xf2c2e9eeU,
            0xebeb19c1U,
        },
        {
            0U, 0U, 0U, 0U, 0U, 0U,
            0U, 0U, 0U, 0U, 0U, 0U,
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_PERFORMANCE),
    },
    {
        TEST_ENABLE, 8U,
        &crcRunTestcase,
        ":PDK-67:PDK-330:PDK-314:PDK-315:PDK-316:PDK-317:PDK-318:PDK-319:PDK-320:PDK-321:PDK-322:PDK-323:PDK-331:PDK-337:",
        "crc_ch2_full_cpu_ipu_control_module",
        NULL, NULL,
        "CRC signature calculation and verification from any channel should be successful.",
        IPU, 100U, 0x4a002100U,
        {
            (uint32_t) CRC_CHANNEL_2,
            (uint32_t) CRC_OPERATION_MODE_FULLCPU,
            4U,
            DEF_CRC_PATTERN_COUNT,
            DEF_CRC_SECTOR_COUNT,
            DEF_CRC_WATCHDOG_PRELOAD,
            DEF_CRC_BLOCK_PRELOAD,
            0x0U,
            0x0U,
        },
        {
            0U, 0U, 0U, 0U, 0U, 0U,
            0U, 0U, 0U, 0U, 0U, 0U,
        },
        PRINT_ENABLE,
        ST_TT_SANITY,
    },
    {
        TEST_ENABLE, 9U,
        &crcRunTestcase,
        ":PDK-67:PDK-330:PDK-314:PDK-315:PDK-316:PDK-317:PDK-318:PDK-319:PDK-320:PDK-321:PDK-322:PDK-323:PDK-332:PDK-337:",
        "crc_ch3_full_cpu_dsp1_ddr",
        NULL, NULL,
        "CRC signature verification should be successful. Performance should be met with expected values",
        DSP1, 1843200U, 0x80000000U,
        {
            (uint32_t) CRC_CHANNEL_3,
            (uint32_t) CRC_OPERATION_MODE_FULLCPU,
            4U,
            DEF_CRC_PATTERN_COUNT,
            DEF_CRC_SECTOR_COUNT,
            DEF_CRC_WATCHDOG_PRELOAD,
            DEF_CRC_BLOCK_PRELOAD,
            0xf2c2e9eeU,
            0xebeb19c1U,
        },
        {
            0U, 0U, 0U, 0U, 0U, 0U,
            0U, 0U, 0U, 0U, 0U, 0U,
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_PERFORMANCE),
    },
    {
        TEST_ENABLE, 10U,
        &crcRunTestcase,
        ":PDK-67:PDK-330:PDK-314:PDK-315:PDK-316:PDK-317:PDK-318:PDK-319:PDK-320:PDK-321:PDK-322:PDK-323:PDK-332:PDK-337:",
        "crc_ch4_full_cpu_dsp1_control_module",
        NULL, NULL,
        "CRC signature calculation and verification from any channel should be successful.",
        DSP1, 100U, 0x4a002100U,
        {
            (uint32_t) CRC_CHANNEL_4,
            (uint32_t) CRC_OPERATION_MODE_FULLCPU,
            4U,
            DEF_CRC_PATTERN_COUNT,
            DEF_CRC_SECTOR_COUNT,
            DEF_CRC_WATCHDOG_PRELOAD,
            DEF_CRC_BLOCK_PRELOAD,
            0x0U,
            0x0U,
        },
        {
            0U, 0U, 0U, 0U, 0U, 0U,
            0U, 0U, 0U, 0U, 0U, 0U,
        },
        PRINT_ENABLE,
        ST_TT_SANITY,
    },
    {
        TEST_ENABLE, 11U,
        &crcRunTestcase,
        ":PDK-67:PDK-330:PDK-314:PDK-315:PDK-316:PDK-317:PDK-318:PDK-319:PDK-320:PDK-321:PDK-322:PDK-323:PDK-333:PDK-337:",
        "crc_ch1_full_cpu_dsp2_ddr",
        NULL, NULL,
        "CRC signature calculation and verification from any channel should be successful.",
        DSP2, 1843200U, 0x80000000U,
        {
            (uint32_t) CRC_CHANNEL_1,
            (uint32_t) CRC_OPERATION_MODE_FULLCPU,
            4U,
            DEF_CRC_PATTERN_COUNT,
            DEF_CRC_SECTOR_COUNT,
            DEF_CRC_WATCHDOG_PRELOAD,
            DEF_CRC_BLOCK_PRELOAD,
            0x0U,
            0x0U,
        },
        {
            0U, 0U, 0U, 0U, 0U, 0U,
            0U, 0U, 0U, 0U, 0U, 0U,
        },
        PRINT_ENABLE,
        ST_TT_SANITY,
    },
    {
        TEST_ENABLE, 12U,
        &crcRunTestcase,
        ":PDK-67:PDK-330:PDK-314:PDK-315:PDK-316:PDK-317:PDK-318:PDK-319:PDK-320:PDK-321:PDK-322:PDK-323:PDK-333:PDK-337:",
        "crc_ch1_full_cpu_dsp2_control_module",
        NULL, NULL,
        "CRC signature calculation and verification from any channel should be successful.",
        DSP2, 100U, 0x4a002100U,
        {
            (uint32_t) CRC_CHANNEL_1,
            (uint32_t) CRC_OPERATION_MODE_FULLCPU,
            4U,
            DEF_CRC_PATTERN_COUNT,
            DEF_CRC_SECTOR_COUNT,
            DEF_CRC_WATCHDOG_PRELOAD,
            DEF_CRC_BLOCK_PRELOAD,
            0x0U,
            0x0U,
        },
        {
            0U, 0U, 0U, 0U, 0U, 0U,
            0U, 0U, 0U, 0U, 0U, 0U,
        },
        PRINT_ENABLE,
        ST_TT_SANITY,
    },
    {
        TEST_ENABLE, 13U,
        &crcRunTestcase,
        ":PDK-67:",
        "CRC_FULLCPU_IPU_DDR",
        NULL, NULL,
        "CRC signature calculation and verification from any channel should be successful.",
        IPU, 1843200U, 0x80000000U,
        {
            (uint32_t) CRC_CHANNEL_1,
            (uint32_t) CRC_OPERATION_MODE_FULLCPU,
            4U,
            DEF_CRC_PATTERN_COUNT,
            DEF_CRC_SECTOR_COUNT,
            DEF_CRC_WATCHDOG_PRELOAD,
            DEF_CRC_BLOCK_PRELOAD,
            0x0U,
            0x0U,
        },
        {
            0U, 0U, 0U, 0U, 0U, 0U,
            0U, 0U, 0U, 0U, 0U, 0U,
        },
        PRINT_ENABLE,
        ST_TT_SANITY,
    },
#if !(defined (AVV_TEST_AUTO_BUILD))
#ifdef __TI_ARM_V7M4__
    {
        TEST_ENABLE, 14U,
        &DiagLibCrcTest_main,
        ":PDK-1577:PDK-1574:",
        "DiagLib CRC Test Inbuilt",
        NULL, NULL,
        "CRC signature for inbuilt data should be verified with golden CRC",
        IPU, 0U, 0U,
        {
            0U, 0U, 0U, 0U, 0U,
            0U, 0U, 0U, 0U,
        },
        {
            SOC_CRC_BASE,
            CRC_OPERATION_MODE_FULLCPU,
            CRC_CHANNEL_1,
            0U,
            NULL,
            DIAGLIB_CRC_TEST_INBUILT,
            DIAGLIB_CRC_BIT_32,
            DIAGLIB_CRC_POLLED_MODE,
            200U,
            0U, 0U, 0U
        },
        PRINT_ENABLE,
        ST_TT_SANITY,
    },
    {
        TEST_ENABLE, 15U,
        &DiagLibCrcTest_main,
        ":PDK-1675:",
        "DiagLib CRC Test Inbuilt",
        NULL, NULL,
        "EDMA interrupt should occur. CRC signature for inbuilt data should be verified with golden CRC",
        IPU, 0U, 0U,
        {
            0U, 0U, 0U, 0U, 0U,
            0U, 0U, 0U, 0U,
        },
        {
            SOC_CRC_BASE,
            CRC_OPERATION_MODE_SEMICPU,
            CRC_CHANNEL_1,
            0U,
            NULL,
            DIAGLIB_CRC_TEST_INBUILT,
            DIAGLIB_CRC_BIT_32,
            DIAGLIB_CRC_INTERRUPT_MODE,
            0U,
            0U, 0U, 0U
        },
        PRINT_ENABLE,
        ST_TT_SANITY,
    },
    {
        TEST_ENABLE, 16U,
        &DiagLibCrcTest_main,
        ":PDK-1641:",
        "DiagLib CRC Test User",
        NULL, NULL,
        "EDMA interrupt should occur. CRC signature for user data should be verified with SW CRC",
        IPU, 0U, 0U,
        {
            0U, 0U, 0U, 0U, 0U,
            0U, 0U, 0U, 0U,
        },
        {
            SOC_CRC_BASE,
            CRC_OPERATION_MODE_SEMICPU,
            CRC_CHANNEL_2,
            0x400U,
            NULL,
            DIAGLIB_CRC_TEST_USER,
            DIAGLIB_CRC_BIT_32,
            DIAGLIB_CRC_INTERRUPT_MODE,
            0U,
            0U, 0U, 0U
        },
        PRINT_ENABLE,
        ST_TT_SANITY,
    },
    {
        TEST_ENABLE, 17U,
        &DiagLibCrcTest_main,
        ":PDK-1614:PDK-1623:",
        "DiagLib CRC Test Get HW CRC Value",
        NULL, NULL,
        "EDMA interrupt should occur. CRC signature should be calculated for given data",
        IPU, 0U, 0U,
        {
            0U, 0U, 0U, 0U, 0U,
            0U, 0U, 0U, 0U,
        },
        {
            SOC_CRC_BASE,
            CRC_OPERATION_MODE_SEMICPU,
            CRC_CHANNEL_2,
            0x1000U,
            NULL,
            DIAGLIB_CRC_TEST_GET_CRC,
            DIAGLIB_CRC_BIT_64,
            DIAGLIB_CRC_INTERRUPT_MODE,
            0U,
            1U, 0U, 1U
        },
        PRINT_ENABLE,
        ST_TT_SANITY,
    },
    {
        TEST_ENABLE, 18U,
        &DiagLibCrcTest_main,
        ":PDK-1654:PDK-1545:",
        "DiagLib CRC Test Get HW CRC Value",
        NULL, NULL,
        "CRC signature should be calculated for given data",
        IPU, 0U, 0U,
        {
            0U, 0U, 0U, 0U, 0U,
            0U, 0U, 0U, 0U,
        },
        {
            SOC_CRC_BASE,
            CRC_OPERATION_MODE_FULLCPU,
            CRC_CHANNEL_3,
            0x900U,
            NULL,
            DIAGLIB_CRC_TEST_GET_CRC,
            DIAGLIB_CRC_BIT_32,
            DIAGLIB_CRC_INTERRUPT_MODE,
            0U,
            0U, 0U, 0U
        },
        PRINT_ENABLE,
        ST_TT_SANITY,
    },
    {
        TEST_ENABLE, 19U,
        &DiagLibCrcTest_main,
        ":PDK-1574:",
        "DiagLib CRC Get HW CRC value",
        NULL, NULL,
        "EDMA interrupt should occur. CRC signature for given data should be calculated",
        IPU, 0U, 0U,
        {
            0U, 0U, 0U, 0U, 0U,
            0U, 0U, 0U, 0U,
        },
        {
            SOC_CRC_BASE,
            CRC_OPERATION_MODE_SEMICPU,
            CRC_CHANNEL_2,
            64U,
            NULL,
            DIAGLIB_CRC_TEST_GET_CRC,
            DIAGLIB_CRC_BIT_32,
            DIAGLIB_CRC_INTERRUPT_MODE,
            0U,
            0U, 0U, 0U
        },
        PRINT_ENABLE,
        ST_TT_SANITY,
    },
    {
        TEST_ENABLE, 20U,
        &DiagLibCrcTest_main,
        ":PDK-1549:",
        "DiagLib CRC Test Get HW CRC Value",
        NULL, NULL,
        "CRC interrupt status to be set before timeout. CRC signature should be calculated for given data",
        IPU, 0U, 0U,
        {
            0U, 0U, 0U, 0U, 0U,
            0U, 0U, 0U, 0U,
        },
        {
            SOC_CRC_BASE,
            CRC_OPERATION_MODE_SEMICPU,
            CRC_CHANNEL_3,
            0x100U,
            NULL,
            DIAGLIB_CRC_TEST_GET_CRC,
            DIAGLIB_CRC_BIT_64,
            DIAGLIB_CRC_POLLED_MODE,
            100U,
            1U, 0U, 1U
        },
        PRINT_ENABLE,
        ST_TT_SANITY,
    },
    {
        TEST_ENABLE, 21U,
        &DiagLibCrcTest_main,
        ":PDK-1670:",
        "DiagLib CRC Full CPU User Test 32 bit",
        NULL, NULL,
        "CRC signature should be calculated for given data and should match with the SW CRC for the same data",
        IPU, 0U, 0U,
        {
            0U, 0U, 0U, 0U, 0U,
            0U, 0U, 0U, 0U,
        },
        {
            SOC_CRC_BASE,
            CRC_OPERATION_MODE_FULLCPU,
            CRC_CHANNEL_4,
            0x100U,
            NULL,
            DIAGLIB_CRC_TEST_USER,
            DIAGLIB_CRC_BIT_32,
            DIAGLIB_CRC_INTERRUPT_MODE,
            0U,
            0U, 0U, 0U
        },
        PRINT_ENABLE,
        ST_TT_SANITY,
    },
    {
        TEST_ENABLE, 22U,
        &DiagLibCrcTest_main,
        ":PDK-1690:",
        "DiagLib CRC Test User",
        NULL, NULL,
        "CRC interrupt should occur. CRC signature for user data should be verified with SW CRC",
        IPU, 0U, 0U,
        {
            0U, 0U, 0U, 0U, 0U,
            0U, 0U, 0U, 0U,
        },
        {
            SOC_CRC_BASE,
            CRC_OPERATION_MODE_SEMICPU,
            CRC_CHANNEL_1,
            0x80U,
            NULL,
            DIAGLIB_CRC_TEST_USER,
            DIAGLIB_CRC_BIT_64,
            DIAGLIB_CRC_INTERRUPT_MODE,
            0U,
            0U, 0U, 0U
        },
        PRINT_ENABLE,
        ST_TT_SANITY,
    },
    {
        TEST_ENABLE, 23U,
        &DiagLibCrcTest_main,
        ":PDK-1699:",
        "DiagLib CRC Test User",
        NULL, NULL,
        "CRC interrupt status bit should be set before timeout. CRC signature for user data should be verified with SW CRC",
        IPU, 0U, 0U,
        {
            0U, 0U, 0U, 0U, 0U,
            0U, 0U, 0U, 0U,
        },
        {
            SOC_CRC_BASE,
            CRC_OPERATION_MODE_SEMICPU,
            CRC_CHANNEL_1,
            0x80U,
            NULL,
            DIAGLIB_CRC_TEST_USER,
            DIAGLIB_CRC_BIT_64,
            DIAGLIB_CRC_POLLED_MODE,
            60U,
            0U, 0U, 0U
        },
        PRINT_ENABLE,
        ST_TT_SANITY,
    },
    {
        TEST_ENABLE, 24U,
        &DiagLibCrcTest_main,
        ":PDK-1617:",
        "DiagLib CRC Test User",
        NULL, NULL,
        "CRC interrupt status bit should be set before timeout. CRC signature for user data should be verified with SW CRC",
        IPU, 0U, 0U,
        {
            0U, 0U, 0U, 0U, 0U,
            0U, 0U, 0U, 0U,
        },
        {
            SOC_CRC_BASE,
            CRC_OPERATION_MODE_SEMICPU,
            CRC_CHANNEL_2,
            0x80U,
            NULL,
            DIAGLIB_CRC_TEST_USER,
            DIAGLIB_CRC_BIT_32,
            DIAGLIB_CRC_POLLED_MODE,
            60U,
            0U, 0U, 0U
        },
        PRINT_ENABLE,
        ST_TT_SANITY,
    },
    {
        TEST_ENABLE, 25U,
        &DiagLibCrcTest_main,
        ":PDK-1668:",
        "DIAGLIB CRC: Semi CPU 32Bit Inbuilt Test Polled Mode",
        NULL, NULL,
        "CRC signature for inbuilt data should be verified with golden CRC.",
        IPU, 0U, 0U,
        {
            0U, 0U, 0U, 0U, 0U,
            0U, 0U, 0U, 0U,
        },
        {
            SOC_CRC_BASE,
            CRC_OPERATION_MODE_SEMICPU,
            CRC_CHANNEL_2,
            0x80U,
            NULL,
            DIAGLIB_CRC_TEST_INBUILT,
            DIAGLIB_CRC_BIT_32,
            DIAGLIB_CRC_POLLED_MODE,
            60U,
            0U, 0U, 0U
        },
        PRINT_ENABLE,
        ST_TT_SANITY,
    },
    {
        TEST_ENABLE, 26U,
        &DiagLibCrcTest_main,
        ":PDK-1567:",
        "DIAGLIB CRC: Semi CPU 64Bit Inbuilt Test Interrupt Mode",
        NULL, NULL,
        "CRC interrupt status bit should be set before timeout. CRC signature for inbuilt data should be verified with SW CRC",
        IPU, 0U, 0U,
        {
            0U, 0U, 0U, 0U, 0U,
            0U, 0U, 0U, 0U,
        },
        {
            SOC_CRC_BASE,
            CRC_OPERATION_MODE_SEMICPU,
            CRC_CHANNEL_2,
            0x80U,
            NULL,
            DIAGLIB_CRC_TEST_INBUILT,
            DIAGLIB_CRC_BIT_64,
            DIAGLIB_CRC_INTERRUPT_MODE,
            60U,
            0U, 0U, 0U
        },
        PRINT_ENABLE,
        ST_TT_SANITY,
    },
    {
        TEST_ENABLE, 27U,
        &DiagLibCrcTest_main,
        ":PDK-1584:",
        "DIAGLIB CRC: Semi CPU 64Bit Inbuilt Test Polled Mode",
        NULL, NULL,
        "CRC signature for inbuilt data should be verified with SW CRC",
        IPU, 0U, 0U,
        {
            0U, 0U, 0U, 0U, 0U,
            0U, 0U, 0U, 0U,
        },
        {
            SOC_CRC_BASE,
            CRC_OPERATION_MODE_SEMICPU,
            CRC_CHANNEL_2,
            0x80U,
            NULL,
            DIAGLIB_CRC_TEST_INBUILT,
            DIAGLIB_CRC_BIT_64,
            DIAGLIB_CRC_POLLED_MODE,
            60U,
            0U, 0U, 0U
        },
        PRINT_ENABLE,
        ST_TT_SANITY,
    },
    {
        TEST_ENABLE, 28U,
        &DiagLibCrcTest_main,
        ":PDK-1657:",
        "DIAGLIB CRC: Semi CPU 32Bit HW CRC Polled Mode",
        NULL, NULL,
        "CRC signature should be calculated for given data.",
        IPU, 0U, 0U,
        {
            0U, 0U, 0U, 0U, 0U,
            0U, 0U, 0U, 0U,
        },
        {
            SOC_CRC_BASE,
            CRC_OPERATION_MODE_SEMICPU,
            CRC_CHANNEL_2,
            0x80U,
            NULL,
            DIAGLIB_CRC_TEST_GET_CRC,
            DIAGLIB_CRC_BIT_32,
            DIAGLIB_CRC_POLLED_MODE,
            60U,
            0U, 0U, 0U
        },
        PRINT_ENABLE,
        ST_TT_SANITY,
    },
    {
        TEST_ENABLE, 29U,
        &DiagLibCrcTest_main,
        ":PDK-1669:",
        "DIAGLIB CRC: Semi CPU 32Bit HW CRC Interrupt Mode",
        NULL, NULL,
        "CRC interrupt status bit should be set before timeout.CRC signature should be calculated for given data.",
        IPU, 0U, 0U,
        {
            0U, 0U, 0U, 0U, 0U,
            0U, 0U, 0U, 0U,
        },
        {
            SOC_CRC_BASE,
            CRC_OPERATION_MODE_SEMICPU,
            CRC_CHANNEL_2,
            0x80U,
            NULL,
            DIAGLIB_CRC_TEST_GET_CRC,
            DIAGLIB_CRC_BIT_32,
            DIAGLIB_CRC_INTERRUPT_MODE,
            60U,
            0U, 0U, 0U
        },
        PRINT_ENABLE,
        ST_TT_SANITY,
    },
#endif
#endif
};

#endif /* #ifndef ST_UART_TEST_CASES_H_ */

