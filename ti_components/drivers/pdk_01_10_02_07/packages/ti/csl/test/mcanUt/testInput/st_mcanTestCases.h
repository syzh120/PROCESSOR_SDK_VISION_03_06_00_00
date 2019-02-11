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
 *  \file stw_mcanTestcases.h
 *
 *  \brief This file defines the test cases for mcan UT.
 */

#ifndef ST_MCAN_TEST_CASES_H_
#define ST_MCAN_TEST_CASES_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <ti/csl/soc.h>
#include <ti/csl/cslr_mcan.h>
#include <ti/csl/soc.h>
#include <ti/csl/csl_mcan.h>
#include <st_mcan.h>
#include <st_mcanTestCasesConfig.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define MCAN_NUM_TESTCASES               (sizeof (gmcanTestcaseParams) / sizeof (st_mcanTestcaseParams_t))

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief Defines the various mcan test cases. */
st_mcanTestcaseParams_t gmcanTestcaseParams[] =
{
    /* enableTest, testCaseId,
     * *reqId,
     * *testCaseName,
     * *userInfo, *disableReason
     * cpuID,
     * mcanConfigParams,
     * printEnable,
     * testType,
     */
    {
        TEST_DISABLE, 0U,
        "None",
        "User defined test",
        "None", "None",
        "None",
        IPU,
        {
            (MCAN_TEST_TYPE_B2B | MCAN_TEST_TYPE_INTERNAL_LOOBACK), /* testType */
            1U, /* iteration count for tx */
            DEF_MCAN_MODULE, /* mcan module base address */
            NULL, /* mcan module bit timing parameters */
            NULL, /* mcan module initialization parameters */
            NULL, /* mcan module configuration parameters */
            NULL, /* mcan module MSG RAM configuration parameters */
            NULL, /* mcan module ECC configuration parameters */
            NULL, /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            1U, /* standard ID message filter number */
            1U, /* extended ID message filter number */
            NULL, /* tx Buffer elements/Tx message */
            NULL, /* standard message ID filters */
            NULL,  /* extended message ID filters */
            0U,  /* Interrupt Enable/Disable Mask */
            0U,  /* Interrupt Line Select Mask */
            0U  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 1U,
        "None",
        "MCAN: CAN FD Mode with Bit Rate Switching ON",
        "None", "None",
        "1.Sent message shall match with received message. 2.Tx Event message marker shall match with sent message. 3. Time Stamp shall be captured.",
        IPU,
        {
            (MCAN_TEST_TYPE_B2B | MCAN_TEST_TYPE_INTERNAL_LOOBACK), /* testType */
            2U, /* iteration count for tx */
            DEF_MCAN_MODULE, /* mcan module base address */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[1U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[2U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 2U,
        "None",
        "MCAN: Classic CAN Mode",
        "None", "None",
        "Sent message shall match with received message.",
        IPU,
        {
            (MCAN_TEST_TYPE_B2B | MCAN_TEST_TYPE_INTERNAL_LOOBACK), /* testType */
            1U, /* iteration count for tx */
            DEF_MCAN_MODULE, /* mcan module base address */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[0U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            2U, /* tx message number */
            1U, /* standard ID message filter number */
            1U, /* extended ID message filter number */
            &canTxMSG[3U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[2U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 3U,
        "None",
        "MCAN: CAN FD Mode with Bit Rate Switching OFF",
        "None", "None",
        "Sent message shall match with received message.",
        IPU,
        {
            (MCAN_TEST_TYPE_B2B | MCAN_TEST_TYPE_INTERNAL_LOOBACK), /* testType */
            1U, /* iteration count for tx */
            DEF_MCAN_MODULE, /* mcan module base address */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[0U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            3U, /* tx message number */
            1U, /* standard ID message filter number */
            1U, /* extended ID message filter number */
            &canTxMSG[5U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[3U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 4U,
        "None",
        "MCAN: External Time-Stamp",
        "None", "None",
        "1.Sent message shall match with received message.2.Tx Event message marker shall match with sent message.3. Time Stamp shall be captured.",
        IPU,
        {
            (MCAN_TEST_TYPE_B2B | MCAN_TEST_TYPE_INTERNAL_LOOBACK), /* testType */
            1U, /* iteration count for tx */
            DEF_MCAN_MODULE, /* mcan module base address */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[3U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            1U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[2U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 5U,
        "None",
        "MCAN: High Priority Messages",
        "None", "None",
        "Sent message shall match with received message with High Priority.",
        IPU,
        {
            (MCAN_TEST_TYPE_B2B | MCAN_TEST_TYPE_INTERNAL_LOOBACK), /* testType */
            1U, /* iteration count for tx */
            DEF_MCAN_MODULE, /* mcan module base address */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[2U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[7U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[5U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 6U,
        "None",
        "MCAN: Internal Loopback",
        "None", "None",
        "Sent message shall match with received message with High Priority.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOBACK), /* testType */
            1U, /* iteration count for tx */
            DEF_MCAN_MODULE, /* mcan module base address */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[2U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[7U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[5U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 7U,
        "None",
        "MCAN: Tx Mixed Config. With Buffer and FIFO",
        "None", "None",
        "Sent messages shall match with received message.",
        IPU,
        {
            (MCAN_TEST_TYPE_B2B | MCAN_TEST_TYPE_INTERNAL_LOOBACK), /* testType */
            1U, /* iteration count for tx */
            DEF_MCAN_MODULE, /* mcan module base address */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[2U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            2U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[8U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 8U,
        "None",
        "MCAN: Tx Mixed Config. With Buffer and Queue",
        "None", "None",
        "Sent messages shall match with received message.",
        IPU,
        {
            (MCAN_TEST_TYPE_B2B | MCAN_TEST_TYPE_INTERNAL_LOOBACK), /* testType */
            1U, /* iteration count for tx */
            DEF_MCAN_MODULE, /* mcan module base address */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[2U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[1U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            2U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[8U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 9U,
        "None",
        "MCAN: Throughput",
        "None", "None",
        "Sent messages shall match with received message and measured frames per seconds should be 85% of the theoretical.",
        IPU,
        {
            (MCAN_TEST_TYPE_B2B), /* testType */
            10000U, /* iteration count for tx */
            DEF_MCAN_MODULE, /* mcan module base address */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[2U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[8U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_PERFORMANCE),
    },
    {
        TEST_ENABLE, 10U,
        "None",
        "MCAN: ECC Test",
        "None", "None",
        "In case single bit error corrected data should be transmitted and in case of double bit error message should not go out.",
        IPU,
        {
            (MCAN_TEST_TYPE_B2B | MCAN_TEST_TYPE_INTERNAL_LOOBACK), /* testType */
            1U, /* iteration count for tx */
            DEF_MCAN_MODULE, /* mcan module base address */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[2U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[10U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND & ~MCAN_INTR_SRC_BIT_ERR_UNCORRECTED & ~MCAN_INTR_SRC_BIT_ERR_CORRECTED),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 11U,
        "None",
        "MCAN: ECC Self Test => SEC Test",
        "None", "None",
        "In case single bit error corrected data should be transmitted and in case of double bit error message should not go out.",
        IPU,
        {
            (MCAN_TEST_TYPE_B2B | MCAN_TEST_TYPE_INTERNAL_LOOBACK), /* testType */
            1U, /* iteration count for tx */
            DEF_MCAN_MODULE, /* mcan module base address */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[2U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[10U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND & ~MCAN_INTR_SRC_BIT_ERR_UNCORRECTED & ~MCAN_INTR_SRC_BIT_ERR_CORRECTED),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 12U,
        "None",
        "MCAN: ECC Self Test => DED Test",
        "None", "None",
        "In case single bit error corrected data should be transmitted and in case of double bit error message should not go out.",
        IPU,
        {
            (MCAN_TEST_TYPE_B2B | MCAN_TEST_TYPE_INTERNAL_LOOBACK), /* testType */
            1U, /* iteration count for tx */
            DEF_MCAN_MODULE, /* mcan module base address */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[2U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[1U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[10U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND & ~MCAN_INTR_SRC_BIT_ERR_UNCORRECTED & ~MCAN_INTR_SRC_BIT_ERR_CORRECTED),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 13U,
        "None",
        "MCAN: DMA Events",
        "None", "None",
        "Sent messages shall match with received message. ",
        IPU,
        {
            (MCAN_TEST_TYPE_B2B), /* testType */
            100U, /* iteration count for tx */
            DEF_MCAN_MODULE, /* mcan module base address */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[2U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[0U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND & ~MCAN_INTR_SRC_BIT_ERR_UNCORRECTED & ~MCAN_INTR_SRC_BIT_ERR_CORRECTED),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 14U,
        "None",
        "MCAN: Programmable Bit rate",
        "None", "None",
        "Sent messages shall match with received message.",
        IPU,
        {
            (MCAN_TEST_TYPE_B2B | MCAN_TEST_TYPE_INTERNAL_LOOBACK), /* testType */
            1U, /* iteration count for tx */
            DEF_MCAN_MODULE, /* mcan module base address */
            &canFDBitTimings[1U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[2U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[8U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 15U,
        "None",
        "MCAN: Node State Transitions",
        "None", "None",
        "MCAN shall transition its states properly(as mentioned in description in Test plan).",
        IPU,
        {
            (MCAN_TEST_TYPE_B2B), /* testType */
            1U, /* iteration count for tx */
            DEF_MCAN_MODULE, /* mcan module base address */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[2U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[0U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 16U,
        "None",
        "MCAN: External Time-Stamp Overflow Interrupt",
        "None", "None",
        "Core shall receive external time stamp interrupt.",
        IPU,
        {
            (MCAN_TEST_TYPE_B2B), /* testType */
            1U, /* iteration count for tx */
            DEF_MCAN_MODULE, /* mcan module base address */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[2U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[2U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 17U,
        "None",
        "MCAN: Pin State",
        "None", "None",
        "Configured PAD values shall match with read values.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOBACK), /* testType */
            1U, /* iteration count for tx */
            DEF_MCAN_MODULE, /* mcan module base address */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[2U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[2U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 18U,
        "None",
        "MCAN: Clock Stop Request",
        "None", "None",
        "MCAN shall ack back the clock stop request.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOBACK), /* testType */
            1U, /* iteration count for tx */
            DEF_MCAN_MODULE, /* mcan module base address */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[2U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[2U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 19U,
        "None",
        "MCAN: Time Stamp Counter Reset",
        "None", "None",
        "Time Stamp Counter shall get reset after calling TS Reset API.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOBACK), /* testType */
            1U, /* iteration count for tx */
            DEF_MCAN_MODULE, /* mcan module base address */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[1U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[2U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 20U,
        "None",
        "MCAN: Bus Monitoring Mode",
        "None", "None",
        "MCAN shall be able to receiver messages.",
        IPU,
        {
            (MCAN_TEST_TYPE_B2B), /* testType */
            1U, /* iteration count for tx */
            DEF_MCAN_MODULE, /* mcan module base address */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[4U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[2U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (~MCAN_INTR_MASK_ALL | MCAN_INTR_SRC_RX_FIFO0_NEW_MSG | MCAN_INTR_SRC_RX_FIFO1_NEW_MSG | MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
#if 0
    {
        TEST_DISABLE, 99U,
        "None",
        "User defined test",
        "None", "None",
        "None",
        IPU,
        {
            (MCAN_TEST_TYPE_B2B), /* testType */
            2U, /* iteration count for tx */
            DEF_MCAN_MODULE, /* mcan module base address */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[0U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[0U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_DISABLE, 100U,
        "None",
        "User defined test",
        "None", "None",
        "None",
        IPU,
        {
            (MCAN_TEST_TYPE_B2B | MCAN_TEST_TYPE_INTERNAL_LOOBACK), /* testType */
            2U, /* iteration count for tx */
            DEF_MCAN_MODULE, /* mcan module base address */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[0U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            2U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[0U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 1000U,
        "None",
        "MCAN: CAN FD Mode with Bit Rate Switching ON",
        "None", "None",
        "1.Sent message shall match with received message. 2.Tx Event message marker shall match with sent message. 3. Time Stamp shall be captured.",
        IPU,
        {
            (MCAN_TEST_TYPE_B2B | MCAN_TEST_TYPE_INTERNAL_LOOBACK), /* testType */
            2U, /* iteration count for tx */
            DEF_MCAN_MODULE, /* mcan module base address */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[1U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[2U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 1001U,
        "None",
        "MCAN: Classic CAN Mode",
        "None", "None",
        "Sent message shall match with received message.",
        IPU,
        {
            (MCAN_TEST_TYPE_B2B | MCAN_TEST_TYPE_INTERNAL_LOOBACK), /* testType */
            1U, /* iteration count for tx */
            DEF_MCAN_MODULE, /* mcan module base address */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[0U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            2U, /* tx message number */
            1U, /* standard ID message filter number */
            1U, /* extended ID message filter number */
            &canTxMSG[3U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[2U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 1002U,
        "None",
        "MCAN: CAN FD Mode with Bit Rate Switching OFF",
        "None", "None",
        "Sent message shall match with received message.",
        IPU,
        {
            (MCAN_TEST_TYPE_B2B | MCAN_TEST_TYPE_INTERNAL_LOOBACK), /* testType */
            1U, /* iteration count for tx */
            DEF_MCAN_MODULE, /* mcan module base address */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[0U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            3U, /* tx message number */
            1U, /* standard ID message filter number */
            1U, /* extended ID message filter number */
            &canTxMSG[5U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[3U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 1003U,
        "None",
        "MCAN: External Time-Stamp",
        "None", "None",
        "1.Sent message shall match with received message.2.Tx Event message marker shall match with sent message.3. Time Stamp shall be captured.",
        IPU,
        {
            (MCAN_TEST_TYPE_B2B | MCAN_TEST_TYPE_INTERNAL_LOOBACK), /* testType */
            1U, /* iteration count for tx */
            DEF_MCAN_MODULE, /* mcan module base address */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[3U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            1U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[2U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 1004U,
        "None",
        "MCAN: High Priority Messages",
        "None", "None",
        "Sent message shall match with received message with High Priority.",
        IPU,
        {
            (MCAN_TEST_TYPE_B2B | MCAN_TEST_TYPE_INTERNAL_LOOBACK), /* testType */
            1U, /* iteration count for tx */
            DEF_MCAN_MODULE, /* mcan module base address */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[2U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[7U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[5U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 1005U,
        "None",
        "MCAN: Internal Loopback",
        "None", "None",
        "Sent message shall match with received message with High Priority.",
        IPU,
        {
            (MCAN_TEST_TYPE_INTERNAL_LOOBACK), /* testType */
            1U, /* iteration count for tx */
            DEF_MCAN_MODULE, /* mcan module base address */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[2U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[0U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            1U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[7U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[5U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
    {
        TEST_ENABLE, 1006U,
        "None",
        "MCAN: Tx Mixed Config. With Buffer and FIFO",
        "None", "None",
        "Sent messages shall match with received message.",
        IPU,
        {
            (MCAN_TEST_TYPE_B2B | MCAN_TEST_TYPE_INTERNAL_LOOBACK), /* testType */
            1U, /* iteration count for tx */
            DEF_MCAN_MODULE, /* mcan module base address */
            &canFDBitTimings[0U], /* mcan module bit timing parameters */
            &canFDInitParams[0U], /* mcan module initialization parameters */
            &canFDConfigParams[2U], /* mcan module configuration parameters */
            &canFDRAMConfigParams[1U], /* mcan module MSG RAM configuration parameters */
            &canFDECCConfigParams[0U], /* mcan module ECC configuration parameters */
            &canFDECCErrForceConfigParams[0U], /* mcan module ECC Error Force parameters */
            2U, /* tx message number */
            2U, /* standard ID message filter number */
            2U, /* extended ID message filter number */
            &canTxMSG[8U], /* tx Buffer elements/Tx message */
            &canSTDIDFilter[0U], /* standard message ID filters */
            &canEXTIDFilter[0U],  /* extended message ID filters */
            (MCAN_INTR_MASK_ALL & ~MCAN_INTR_SRC_RES_ADDR_ACCESS & ~MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND),  /* Interrupt Enable/Disable Mask */
            (MCAN_INTR_MASK_ALL),  /* Interrupt Line Select Mask */
            (MCAN_INTR_LINE_NUM_0)  /* Interrupt Line Select */
        },
        PRINT_ENABLE,
        (ST_TT_SANITY),
    },
#endif
};

uint32_t bitTimingsListSize = (sizeof(canFDBitTimings) / sizeof(MCAN_BitTimingParams));

#endif /* #ifndef ST_MCAN_TEST_CASES_H_ */
