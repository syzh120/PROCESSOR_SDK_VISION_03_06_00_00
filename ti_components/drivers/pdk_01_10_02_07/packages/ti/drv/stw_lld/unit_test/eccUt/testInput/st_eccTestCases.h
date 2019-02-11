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
 *  \file stw_eccTestcases.h
 *
 *  \brief This file defines the test cases for ECC UT.
 */

#ifndef STW_ECC_TEST_CASES_H_
#define STW_ECC_TEST_CASES_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <ti/csl/soc.h>
#include <ti/csl/soc.h>
#include <st_ecc.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define ECC_NUM_TESTCASES   (sizeof (gECCTestcaseParams) / \
                             sizeof (st_ECCTestcaseParams_t))

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief Defines the various McSPI test cases. */
static st_ECCTestcaseParams_t gECCTestcaseParams[] =
{
    /* enableTest, testCaseId,
     * testCaseFxnPtr,
     * *reqId,
     * *testCaseName,
     * *userInfo, *disableReason
     * *passFailCriteria,
     * cpuID,
     * diagLibTestParams
     * printEnable,
     * testType,
     */
    {
        TEST_ENABLE, 1U,
        &DiagLibEccTest_main,
        ":PDK-1587:PDP:965:PDK-1633:",
        "ECC Test for EMIF SEC Test in interrupt mode",
        "None",
        "None",
        "EMIF interrupt should occur. Single bit error should be corrected at correct address",
        IPU,
        {
            DIAGLIB_ECC_TEST_EMIF_SEC,
            DIAGLIB_ECC_INTERRUPT_MODE,
            0U,
            {
                (void *) 0x90000100,
            },
            NULL,
            NULL,
        },
        PRINT_ENABLE,
        ST_TT_SANITY | ST_TT_FULL,
    },
    {
        TEST_ENABLE, 2U,
        &DiagLibEccTest_main,
        ":PDK-1558:PDP:965:PDK-1569:PDK-1665:",
        "ECC Test for OCMC SEC error",
        "None",
        "None",
        "OCMC interrupt should occur. Single bit error should be corrected at correct address",
        IPU,
        {
            DIAGLIB_ECC_TEST_OCMC_SEC,
            DIAGLIB_ECC_INTERRUPT_MODE,
            0U,
            {},
            {
                DIAGLIB_ECC_OCMC_MODE_RAM_FULL,
                0x40311104U,
                1U,
                0U,
                1U,
            },
            NULL,
        },
        PRINT_ENABLE,
        ST_TT_SANITY | ST_TT_FULL,
    },
    {
        TEST_ENABLE, 3U,
        &DiagLibEccTest_main,
        ":PDK-1587:PDP:965:PDK-1552:",
        "ECC Test for EMIF non quanta aligned address error",
        "None",
        "None",
        "EMIF interrupt should occur. Quanta error should be detected at correct address",
        IPU,
        {
            DIAGLIB_ECC_TEST_EMIF_NON_QUANTA_ALIGN_ADDR,
            DIAGLIB_ECC_INTERRUPT_MODE,
            0U,
            {
                (void *) 0x90000100,
            },
            {},
            NULL,
        },
        PRINT_ENABLE,
        ST_TT_SANITY | ST_TT_FULL,
    },
    {
        TEST_ENABLE, 4U,
        &DiagLibEccTest_main,
        ":PDK-1587:PDP:965:PDK-1698:",
        "ECC Test for EMIF non quanta multiple write error in interrupt mode",
        "None",
        "None",
        "EMIF interrupt should occur. Quanta error should be detected at correct address",
        IPU,
        {
            DIAGLIB_ECC_TEST_EMIF_NON_QUANTA_MULTIPLE_BYTE,
            DIAGLIB_ECC_INTERRUPT_MODE,
            0U,
            {
                (void *) 0x90000200,
            },
            {},
            NULL,
        },
        PRINT_ENABLE,
        ST_TT_SANITY | ST_TT_FULL,
    },
    {
        TEST_ENABLE, 5U,
        &DiagLibEccTest_main,
        ":PDK-1587:PDP:965:PDK-1681:",
        "ECC Test for EMIF non quanta multiple write error polled mode",
        "None",
        "None",
        "EMIF quanta error status to be set before timeout. Quanta error should be detected at correct address",
        IPU,
        {
            DIAGLIB_ECC_TEST_EMIF_NON_QUANTA_MULTIPLE_BYTE,
            DIAGLIB_ECC_POLLED_MODE,
            0U,
            {
                (void *) 0x90000300,
            },
            {},
            NULL,
        },
        PRINT_ENABLE,
        ST_TT_SANITY | ST_TT_FULL,
    },
    {
        TEST_ENABLE, 6U,
        &DiagLibEccTest_main,
        ":PDK-1587:PDP:965:PDK-1582:",
        "ECC Test for EMIF non quanta aligned address error polled mode",
        "None",
        "None",
        "EMIF quanta error status to be set before timeout. Quanta error should be detected at correct address",
        IPU,
        {
            DIAGLIB_ECC_TEST_EMIF_NON_QUANTA_ALIGN_ADDR,
            DIAGLIB_ECC_POLLED_MODE,
            0U,
            {
                (void *) 0x90000400,
            },
            {},
            NULL,
        },
        PRINT_ENABLE,
        ST_TT_SANITY | ST_TT_FULL,
    },
    {
        TEST_ENABLE, 7U,
        &DiagLibEccTest_main,
        ":PDK-1587:PDP:965:PDK-1691:",
        "ECC Test for EMIF SEC Test in polled mode",
        "None",
        "None",
        "EMIF SEC error status to be set before timeout. Single bit error should be corrected at correct address",
        IPU,
        {
            DIAGLIB_ECC_TEST_EMIF_SEC,
            DIAGLIB_ECC_POLLED_MODE,
            0U,
            {
                (void *) 0x90000500,
            },
            {},
            NULL,
        },
        PRINT_ENABLE,
        ST_TT_SANITY | ST_TT_FULL,
    },
    {
        TEST_ENABLE, 8U,
        &DiagLibEccTest_main,
        ":PDK-1558:PDP:965:PDK-1701:PDK-1665:",
        "ECC Test for OCMC SEC error",
        "None",
        "None",
        "OCMC SEC error status to be set before timeout. Single bit error should be corrected at correct address",
        IPU,
        {
            DIAGLIB_ECC_TEST_OCMC_SEC,
            DIAGLIB_ECC_POLLED_MODE,
            0U,
            {},
            {
                DIAGLIB_ECC_OCMC_MODE_RAM_BLOCK,
                0x40311104U,
                1U,
                0U,
                1U,
            },
            NULL,
        },
        PRINT_ENABLE,
        ST_TT_SANITY | ST_TT_FULL,
    },
    {
        TEST_ENABLE, 9U,
        &DiagLibEccTest_main,
        ":PDK-1558:PDP:965:PDK-1610:PDK-1665:",
        "ECC Test for OCMC DED error",
        "None",
        "None",
        "OCMC interrupt should occur. Double bit error should be detected at correct address",
        IPU,
        {
            DIAGLIB_ECC_TEST_OCMC_DED,
            DIAGLIB_ECC_INTERRUPT_MODE,
            0U,
            {},
            {
                DIAGLIB_ECC_OCMC_MODE_RAM_BLOCK,
                0x40311118U,
                1U,
                0U,
                1U,
            },
            NULL,
        },
        PRINT_ENABLE,
        ST_TT_SANITY | ST_TT_FULL,
    },
    {
        TEST_ENABLE, 10U,
        &DiagLibEccTest_main,
        ":PDK-1558:PDP:965:PDK-1572:PDK-1665:",
        "ECC Test for OCMC Address error",
        "None",
        "None",
        "OCMC interrupt should occur. Address bit error should be detected at correct address",
        IPU,
        {
            DIAGLIB_ECC_TEST_OCMC_ADDR,
            DIAGLIB_ECC_INTERRUPT_MODE,
            0U,
            {},
            {
                DIAGLIB_ECC_OCMC_MODE_RAM_FULL,
                0x40311110U,
                1U,
                0U,
                1U,
            },
            NULL,
        },
        PRINT_ENABLE,
        ST_TT_SANITY | ST_TT_FULL,
    },
    {
        TEST_ENABLE, 11U,
        &DiagLibEccTest_main,
        ":PDK-1587:PDP:965:PDK-1659:",
        "ECC Test for EMIF DED Test in interrupt mode",
        "None",
        "None",
        "EMIF interrupt should occur. Double bit error should be detected at correct address",
        IPU,
        {
            DIAGLIB_ECC_TEST_EMIF_DED,
            DIAGLIB_ECC_INTERRUPT_MODE,
            0U,
            {
                (void *) 0x90000600,
            },
            {},
            NULL,
        },
        PRINT_ENABLE,
        ST_TT_SANITY | ST_TT_FULL,
    },
};

#endif /* #ifndef ST_UART_TEST_CASES_H_ */
