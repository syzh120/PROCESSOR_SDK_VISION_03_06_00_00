/*
 *  Copyright (C) 2016 Texas Instruments Incorporated
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
 *  \file stw_mcspiTestcases.h
 *
 *  \brief This file defines the test cases for McSPI UT.
 */

#ifndef STW_MCSPI_TEST_CASES_H_
#define STW_MCSPI_TEST_CASES_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <ti/csl/soc.h>
#include <ti/csl/cslr_mcspi.h>
#include <ti/csl/soc.h>
#include <ti/csl/csl_mcspi.h>
#include <st_mcspi.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define MCSPI_NUM_TESTCASES   (sizeof (gMCSPITestcaseParams) / \
                               sizeof (st_MCSPITestcaseParams_t))

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief Defines the various McSPI test cases. */
static st_MCSPITestcaseParams_t gMCSPITestcaseParams[] =
{
    /* enableTest, testCaseId,
     * testCaseFxnPtr,
     * *reqId,
     * *testCaseName,
     * *userInfo, *disableReason, *passFailCriteria
     * cpuID,
     * diagLibTestParams
     * printEnable,
     * testType,
     */
    {
        TEST_DISABLE, 0U,
        &DiagLibMcspiTest_main,
        "None",
        "McSPI 1 internal loopback test",
        "McSPI internal loopback test for channel 0 mode 0 32bit in polled mode at 48MHz ",
        "Hangs",
        NULL,
        IPU,
        {
            DEF_MCSPI_MODULE,
            DEF_MCSPI_CHANNEL,
            48000000U,
            MCSPI_CLK_MODE_0,
            32U,
            DIAGLIB_MCSPI_POLLED_MODE,
            32U, 0U, 0U,
            100U,
            0U, 0U, 0U, 1U, 1U,
        },
        PRINT_ENABLE,
        ST_TT_SANITY | ST_TT_FULL,
    },
    {
        TEST_ENABLE, 1U,
        &DiagLibMcspiTest_main,
        ":PDK-1595:PDK-1556:PDK-1571:PDK-1695:PDK-1645:PDK-1703:",
        "McSPI 1 internal loopback test",
        "McSPI internal loopback test for channel 0 mode 0 32bit in polled mode at 48MHz ",
        "None",
        "McSPI Tx and Rx registers should be able to transmit and recieve data before timeout. The Tx and Rx data should match",
        IPU,
        {
            DEF_MCSPI_MODULE,
            DEF_MCSPI_CHANNEL,
            48000000U,
            MCSPI_CLK_MODE_0,
            32U,
            DIAGLIB_MCSPI_POLLED_MODE,
            32U, 0U, 0U,
            100U,
            0U, 0U, 0U, 0U, 1U,
        },
        PRINT_ENABLE,
        ST_TT_SANITY | ST_TT_FULL,
    },
    {
        TEST_ENABLE, 2U,
        &DiagLibMcspiTest_main,
        ":PDK-1595:PDK-1556:PDK-1571:PDK-1695:PDK-1703:",
        "McSPI 2 internal loopback test",
        "McSPI internal loopback test for channel 1 mode 1 16bit in dma mode at 1MHz ",
        "None",
        "McSPI Tx and Rx registers should be able to transmit and recieve data via DMA. EDMA interrupt should occur. The Tx and Rx data should match",
        IPU,
        {
            SOC_MCSPI2_BASE,
            1U,
            1000000U,
            MCSPI_CLK_MODE_1,
            16U,
            DIAGLIB_MCSPI_DMA_MODE,
            32U, 0U, 0U,
            0U,
            CSL_EDMA3_CHA1_MCSPI1_TX, CSL_EDMA3_CHA1_MCSPI1_RX, 0U, 0U, 1U,
        },
        PRINT_ENABLE,
        ST_TT_SANITY | ST_TT_FULL,
    },
    {
        TEST_ENABLE, 3U,
        &DiagLibMcspiTest_main,
        ":PDK-1595:PDK-1556:PDK-1571:PDK-1695:PDK-1703:",
        "McSPI 4 internal loopback test",
        "McSPI internal loopback test for channel 0 mode 2 8bit in dma mode at 1MHz ",
        "None",
        "McSPI Tx and Rx registers should be able to transmit and recieve data via DMA for any channel. EDMA interrupt should occur. The Tx and Rx data should match",
        IPU,
        {
            SOC_MCSPI4_BASE,
            DEF_MCSPI_CHANNEL,
            1500000U,
            MCSPI_CLK_MODE_2,
            8U,
            DIAGLIB_MCSPI_DMA_MODE,
            64U, 0U, 0U,
            0U,
            CSL_EDMA3_CHA0_MCSPI3_TX, CSL_EDMA3_CHA0_MCSPI3_RX, 0U, 1U, 1U,
        },
        PRINT_ENABLE,
        ST_TT_SANITY | ST_TT_FULL,
    },
    {
        TEST_ENABLE, 4U,
        &DiagLibMcspiTest_main,
        ":PDK-1595:PDK-1556:PDK-1571:PDK-1695:PDK-1645:PDK-1703:",
        "McSPI 1 internal loopback test",
        "McSPI internal loopback test for channel 3 mode 3 8bit in polled mode at 24MHz ",
        "None",
        "McSPI Tx and Rx registers should be able to transmit and recieve data before timeout for any channel. The Tx and Rx data should match",
        IPU,
        {
            DEF_MCSPI_MODULE,
            3U,
            24000000U,
            MCSPI_CLK_MODE_3,
            8U,
            DIAGLIB_MCSPI_POLLED_MODE,
            64U, 0U, 0U,
            300U,
            0U, 0U, 0U, 1U, 1U,
        },
        PRINT_ENABLE,
        ST_TT_SANITY | ST_TT_FULL,
    },
    {
        TEST_ENABLE, 5U,
        &DiagLibMcspiTest_main,
        ":PDK-1595:PDK-1556:PDK-1571:PDK-1695:PDK-1703:",
        "McSPI 1 internal loopback test",
        "McSPI internal loopback test for channel 2 mode 3 16bit in dma mode at 12MHz ",
        "None",
        "McSPI Tx and Rx registers should be able to transmit and recieve data via DMA for any output clock. EDMA interrupt should occur. The Tx and Rx data should match",
        IPU,
        {
            DEF_MCSPI_MODULE,
            2U,
            12000000U,
            MCSPI_CLK_MODE_3,
            16U,
            DIAGLIB_MCSPI_DMA_MODE,
            128U, 0U, 0U,
            0U,
            CSL_EDMA3_CHA2_MCSPI0_TX, CSL_EDMA3_CHA2_MCSPI0_RX, 0U, 1U, 1U,
        },
        PRINT_ENABLE,
        ST_TT_SANITY | ST_TT_FULL,
    },
    {
        TEST_DISABLE, 6U,
        &DiagLibMcspiTest_main,
        ":PDK-1595:PDK-1556:PDK-1571:PDK-1695:PDK-1703:",
        "McSPI 3 internal loopback test",
        "McSPI internal loopback test for channel 0 mode 0 32 in dma mode at 6MHz ",
        ":PDK-1752:",
        "McSPI Tx and Rx registers should be able to transmit and recieve data via DMA in any mode. EDMA interrupt should occur. The Tx and Rx data should match",
        IPU,
        {
            SOC_MCSPI3_BASE,
            DEF_MCSPI_CHANNEL,
            6000000U,
            MCSPI_CLK_MODE_0,
            32U,
            DIAGLIB_MCSPI_DMA_MODE,
            32U, 0U, 0U,
            0U,
            CSL_EDMA3_CHA0_MCSPI2_TX, CSL_EDMA3_CHA0_MCSPI2_RX, 0U, 1U, 1U,
        },
        PRINT_ENABLE,
        ST_TT_SANITY | ST_TT_FULL,
    },
};

#endif /* #ifndef ST_UART_TEST_CASES_H_ */
