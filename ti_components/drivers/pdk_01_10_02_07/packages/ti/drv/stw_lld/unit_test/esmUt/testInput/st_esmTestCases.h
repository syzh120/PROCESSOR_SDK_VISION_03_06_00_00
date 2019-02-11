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
 *  \file stw_esmTestcases.h
 *
 *  \brief This file defines the test cases for ESM UT.
 */

#ifndef STW_ESM_TEST_CASES_H_
#define STW_ESM_TEST_CASES_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <ti/csl/soc.h>
#include <ti/csl/cslr_esm.h>
#include <ti/csl/soc.h>
#include <ti/csl/csl_esm.h>
#include <st_esm.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define ESM_NUM_TESTCASES               (sizeof (gESMTestcaseParams) / sizeof (st_ESMTestcaseParams_t))

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief Defines the various ESM test cases. */
st_ESMTestcaseParams_t gESMTestcaseParams[] =
{
    /* enableTest, testCaseId,
     * *reqId,
     * *testCaseName,
     * *userInfo, *disableReason
     * cpuID, dataSize, sourceMemory,
     * esmConfigParams,
     * printEnable,
     * testType,
     */
    {
        TEST_ENABLE, 0U,
        "None",
        "User defined test",
        "None", "None",
        "None",
        IPU,
        {
            DEF_ESM_MODULE,
            DEF_ESM_MODE,
            DEF_ESM_LTCPR,
            {
                0
            },
        },
        PRINT_ENABLE,
        0U,
    },
    {
        TEST_ENABLE, 1U,
        ":PDK-369:PDK-370:PDK-355:PDK-371:PDK-375:PDK-376:PDK-361:PDK-362:PDK-363:PDK-364:PDK-365:PDK-366:",
        "esm_highlvlintr_everst",
        "Set an interrupt in group 1 to high level and trigger the error condition.",
        "None",
        "ESM should generate high level interrupt on error detection",
        IPU,
        {
            DEF_ESM_MODULE,
            DEF_ESM_MODE,
            DEF_ESM_LTCPR,
            {
                1U, 0U,
                ESM_GROUP1_INTR_SRC_EVE_CPU_RST, ESM_OUT_ERROR_HIGH_INTR,
            },
            1U,
        },
        PRINT_ENABLE,
        ST_TT_SANITY,
    },
    {
        TEST_ENABLE, 2U,
        ":PDK-369:PDK-370:PDK-355:PDK-371:PDK-374:PDK-376:PDK-361:PDK-362:PDK-363:PDK-364:PDK-365:PDK-366:PDK-368:",
        "esm_lowlvlintr_everst",
        "Set an interrupt in group 1 to low level and trigger the error condition.",
        "None",
        "ESM should generate low level interrupt on error detection",
        IPU,
        {
            DEF_ESM_MODULE,
            DEF_ESM_MODE,
            DEF_ESM_LTCPR,
            {
                1U, 0U,
                ESM_GROUP1_INTR_SRC_EVE_CPU_RST, ESM_OUT_ERROR_LOW_INTR,
            },
            1U,
        },
        PRINT_ENABLE,
        ST_TT_SANITY,
    },
    {
        TEST_ENABLE, 3U,
        ":PDK-369:PDK-370:PDK-355:PDK-373:PDK-359:PDK-360:",
        "esm_efm",
        "Verify the Error forcing mode.", "None",
        "ESM should enter in Error Force Mode and assert esm_error pin",
        IPU,
        {
            DEF_ESM_MODULE,
            ESM_OPERATION_MODE_ERROR_FORCE,
            DEF_ESM_LTCPR,
            {
                1U, 0U,
                ESM_GROUP1_INTR_SRC_EVE_CPU_RST, ESM_OUT_ERROR_LOW_INTR,
            },
            1U,
        },
        PRINT_ENABLE,
        ST_TT_SANITY,
    },
    {
        TEST_ENABLE, 4U,
        ":PDK-369:PDK-370:PDK-355:PDK-372:PDK-356:PDK-357:PDK-358:PDK-359:PDK-360:",
        "esm_esmerr_everst",
        "Check influence of Group 1 interrupt on nERROR pin.",\
        "None",
        "ESM should assert esm_error pin on error detection",
        IPU,
        {
            DEF_ESM_MODULE,
            DEF_ESM_MODE,
            0xFFFF,
            {
                1U, 0U,
                ESM_GROUP1_INTR_SRC_EVE_CPU_RST,
                (ESM_OUT_ERROR_ERR_PIN),
            },
            1U,
        },
        PRINT_ENABLE,
        ST_TT_SANITY,
    },
    {
        TEST_ENABLE, 5U,
        ":PDK-369:PDK-370:PDK-355:PDK-372:PDK-356:PDK-357:PDK-358:PDK-359:PDK-360:",
        "esm_err_handling",
        "Check error signal handling.",
        "None",
        "ESM should assert esm_error pin for configured time peroid on error detection",
        IPU,
        {
            DEF_ESM_MODULE,
            DEF_ESM_MODE,
            DEF_ESM_LTCPR,
            {
                1U, 0U,
                ESM_GROUP1_INTR_SRC_EVE_CPU_RST, ESM_OUT_ERROR_ERR_PIN,
            },
            1U,
        },
        PRINT_ENABLE,
        ST_TT_SANITY,
    },
    {
        TEST_ENABLE, 6U,
        ":PDK-369:PDK-370:PDK-355:PDK-371:PDK-375:PDK-376:PDK-361:PDK-362:PDK-363:PDK-364:PDK-365:PDK-366:PDK-367:",
        "esm_highlvlgrp",
        "Set multiple interrupts from Group 1 to high level and check for the offset in ESMIOFFHR register.",
        "None",
        "ESM should generate high level interrupt on error detection",
        IPU,
        {
            DEF_ESM_MODULE,
            DEF_ESM_MODE,
            DEF_ESM_LTCPR,
            {
                3U, 0U,
                ESM_GROUP1_INTR_SRC_EVE_CPU_RST, ESM_OUT_ERROR_HIGH_INTR,
                ESM_GROUP1_INTR_SRC_DCC4_IRQ_ERROR, ESM_OUT_ERROR_HIGH_INTR,
                ESM_GROUP1_INTR_SRC_DCC5_IRQ_ERROR, ESM_OUT_ERROR_HIGH_INTR,
            },
            1U,
        },
        PRINT_ENABLE,
        ST_TT_SANITY,
    },
    {
        TEST_ENABLE, 7U,
        ":PDK-369:PDK-370:PDK-355:PDK-371:PDK-374:PDK-376:PDK-361:PDK-362:PDK-363:PDK-364:PDK-365:PDK-366:",
        "esm_lowlvlintrgrp",
        "Set multiple interrupts from Group 1 to low level and check for the offset in ESMIOFFLR register.",
        "None",
        "ESM should generate low level interrupt on error detection",
        IPU,
        {
            DEF_ESM_MODULE,
            DEF_ESM_MODE,
            DEF_ESM_LTCPR,
            {
                3U, 0U,
                ESM_GROUP1_INTR_SRC_EVE_CPU_RST, ESM_OUT_ERROR_LOW_INTR,
                ESM_GROUP1_INTR_SRC_DCC4_IRQ_ERROR, ESM_OUT_ERROR_LOW_INTR,
                ESM_GROUP1_INTR_SRC_DCC5_IRQ_ERROR, ESM_OUT_ERROR_LOW_INTR,
            },
            1U,
        },
        PRINT_ENABLE,
        ST_TT_SANITY,
    },
};

#endif /* #ifndef ST_UART_TEST_CASES_H_ */
