/*
 *  Copyright (c) Texas Instruments Incorporated 2012
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
 *  \file st_uartTestCases.h
 *
 *  \brief This file defines the test cases for UART UT.
 */

#ifndef ST_UART_TEST_CASES_H_
#define ST_UART_TEST_CASES_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <testLib/st_uart.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define ST_UART_NUM_TESTCASES        ((sizeof (gStUartTestCasePrms)) / \
                                     (sizeof (st_UartTestCaseParams)))

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief Defines the various UART test cases. */
static st_UartTestCaseParams gStUartTestCasePrms[] =
{
    /* enableTest, testCaseId, testCaseType,
     * *reqId,
     * *testCaseName,
     * *userInfo,
     * *disableReason
     * numHandles, devId[], devName[], handleCfgId[],
     * txNumCh[], txChCfgId[],
     * rxNumCh[], rxChCfgId[],
     * printEnable,
     * testType,
     */

    /**************************************************************************
     * UART1 TX Test cases
     *************************************************************************/
    /*
     * UART1 TX Test cases - Polled
     */
    {
        TEST_ENABLE, 1U, ST_UART_TCT_TX,
        ":PDK-216:PDK-217:PDK-218:PDK-1050:PDK-746:PDK-1036:PDK-1051:PDK-1039:PDK-1043:PDK-222:PDK-1064:PDK-1076:PDK-1085:PDK-219:PDK-1089:PDK-1090:PDK-1091:",
        "UART1_TX_Default",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 101U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1064:PDK-1067:PDK-1073:",
        "UART1_TX_Polled_115200Baudrate_Default",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_POLLED_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 102U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1064:PDK-1067:PDK-1073:",
        "UART1_TX_Polled_115200Baudrate_Performance_Test",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_POLLED_PERFORMANCE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL | ST_TT_PERFORMANCE),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 103U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1064:PDK-1067:PDK-1073:",
        "UART1_TX_Polled_115200Baudrate_Rampup_Test",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_POLLED_PERFORMANCE
        },
        {
            1U
        },
        {
            ST_UART_CCID_RAMP_UP
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_REGRESSION | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 104U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1064:PDK-1067:PDK-1073:",
        "UART1_TX_Polled_115200Baudrate_Rampdown_Test",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_POLLED_PERFORMANCE
        },
        {
            1U
        },
        {
            ST_UART_CCID_RAMP_DOWN
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_REGRESSION | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 121U, ST_UART_TCT_TX,
        ":System:OMAPS00308504:",
        "UART1_TX_Polled_OpenClose_Test",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_POLLED_OPEN_CLOSE
        },
        {
            1U
        },
        {
            ST_UART_CCID_TX_OPEN_CLOSE
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_DISABLE,
        (ST_TT_FULL | ST_TT_STRESS),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 131U, ST_UART_TCT_TX,
        ":PDK-1040:OMAPS00308349:",
        "UART1_TX_Polled_FIFO_Enable",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_POLLED_FIFO_ENABLE
        },
        {
            1U
        },
        {
            ST_UART_CCID_RAMP_UP
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL | ST_TT_PERFORMANCE),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 132U, ST_UART_TCT_TX,
        ":PDK-1040:",
        "UART1_TX_Polled_FIFO_Disable",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_POLLED_FIFO_DISABLE
        },
        {
            1U
        },
        {
            ST_UART_CCID_RAMP_UP
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL | ST_TT_PERFORMANCE),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 151U, ST_UART_TCT_TX,
        ":System:",
        "UART1_TX_Polled_RandomTx",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_POLLED_RANDOMLOOPCNT_ENABLE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 161U, ST_UART_TCT_TX,
        ":PDK-1049:",
        "UART1_TX_Polled_ChunkSize_1",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_POLLED_CHUNKSIZE_1
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 162U, ST_UART_TCT_TX,
        ":PDK-1049:",
        "UART1_TX_Polled_ChunkSize_32",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_POLLED_CHUNKSIZE_32
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_REGRESSION | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 163U, ST_UART_TCT_TX,
        ":PDK-1049:",
        "UART1_TX_Polled_ChunkSize_64",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_POLLED_CHUNKSIZE_64
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_REGRESSION | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 164U, ST_UART_TCT_TX,
        ":OMAPS00309190:",
        "UART1_TX_Polled_ChunkSize_Invalid(100 bytes)",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_POLLED_CHUNKSIZE_INVALID
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL | ST_TT_NEGATIVE),
        DEF_SOC_ID,
    },

    /*
     * UART1 TX Test cases - Interrupt
     */
    {
        TEST_ENABLE, 201U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1065:PDK-220:PDK-1067:PDK-1073:",
        "UART1_TX_Interrupt_115200Baudrate_Default",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_INTERRUPT_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 202U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1065:PDK-220:OMAPS00306882:OMAPS00307780:",
        "UART1_TX_Interrupt_115200Baudrate_Performance_Test",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_INTERRUPT_PERFORMANCE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL | ST_TT_PERFORMANCE),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 203U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1065:PDK-220:",
        "UART1_TX_Interrupt_115200Baudrate_Rampup_Test",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_INTERRUPT_PERFORMANCE
        },
        {
            1U
        },
        {
            ST_UART_CCID_RAMP_UP
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_REGRESSION | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 204U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1065:PDK-220:",
        "UART1_TX_Interrupt_115200Baudrate_Rampdown_Test",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_INTERRUPT_PERFORMANCE
        },
        {
            1U
        },
        {
            ST_UART_CCID_RAMP_DOWN
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_REGRESSION | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 221U, ST_UART_TCT_TX,
        ":System:OMAPS00308504:",
        "UART1_TX_Interrupt_OpenClose_Test",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_INTERRUPT_OPEN_CLOSE
        },
        {
            1U
        },
        {
            ST_UART_CCID_TX_OPEN_CLOSE
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_DISABLE,
        (ST_TT_FULL | ST_TT_STRESS),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 231U, ST_UART_TCT_TX,
        ":PDK-1040:OMAPS00308349:",
        "UART1_TX_Interrupt_FIFO_Enable",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_INTERRUPT_FIFO_ENABLE
        },
        {
            1U
        },
        {
            ST_UART_CCID_RAMP_UP
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL | ST_TT_PERFORMANCE),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 232U, ST_UART_TCT_TX,
        ":PDK-1040:",
        "UART1_TX_Interrupt_FIFO_Disable",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_INTERRUPT_FIFO_DISABLE
        },
        {
            1U
        },
        {
            ST_UART_CCID_RAMP_UP
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL | ST_TT_PERFORMANCE),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 241U, ST_UART_TCT_TX,
        ":PDK-1052:PDK-1058:PDK-1059:",
        "UART1_TX_Interrupt_FIFO_Trigger_Level_8",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_INTERRUPT_TXTRIGLVL_8
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL | ST_TT_PERFORMANCE),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 242U, ST_UART_TCT_TX,
        ":PDK-1052:PDK-1058:PDK-1060:",
        "UART1_TX_Interrupt_FIFO_Trigger_Level_16",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_INTERRUPT_TXTRIGLVL_16
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL | ST_TT_PERFORMANCE),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 243U, ST_UART_TCT_TX,
        ":PDK-1052:PDK-1058:PDK-1061:",
        "UART1_TX_Interrupt_FIFO_Trigger_Level_32",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_INTERRUPT_TXTRIGLVL_32
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL | ST_TT_PERFORMANCE),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 244U, ST_UART_TCT_TX,
        ":PDK-1052:PDK-1058:PDK-1062:",
        "UART1_TX_Interrupt_FIFO_Trigger_Level_56",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_INTERRUPT_TXTRIGLVL_56
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL | ST_TT_PERFORMANCE),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 251U, ST_UART_TCT_TX,
        ":System:",
        "UART1_TX_Interrupt_RandomTx",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_INTERRUPT_RANDOMLOOPCNT_ENABLE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 261U, ST_UART_TCT_TX,
        ":PDK-1049:",
        "UART1_TX_Interrupt_ChunkSize_1",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_INTERRUPT_CHUNKSIZE_1
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 262U, ST_UART_TCT_TX,
        ":PDK-1049:",
        "UART1_TX_Interrupt_ChunkSize_32",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_INTERRUPT_CHUNKSIZE_32
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_REGRESSION | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 263U, ST_UART_TCT_TX,
        ":PDK-1049:",
        "UART1_TX_Interrupt_ChunkSize_64",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_INTERRUPT_CHUNKSIZE_64
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_REGRESSION | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 264U, ST_UART_TCT_TX,
        ":OMAPS00309190:",
        "UART1_TX_Interrupt_ChunkSize_Invalid(100 bytes)",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_INTERRUPT_CHUNKSIZE_INVALID
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL | ST_TT_NEGATIVE),
        DEF_SOC_ID,
    },

    /*
     * UART1 TX Test cases - DMA
     */
    {
        TEST_ENABLE, 301U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1043:PDK-222:PDK-1066:PDK-221:OMAPS00308273:OMAPS00294713:",
        "UART1_TX_DMA_115200Baudrate_Default",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_DMA_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 302U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1043:PDK-222:PDK-1066:PDK-221:",
        "UART1_TX_DMA_115200Baudrate_Performance_Test",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_DMA_PERFORMANCE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL | ST_TT_PERFORMANCE),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 321U, ST_UART_TCT_TX,
        ":System:OMAPS00308504:",
        "UART1_TX_DMA_OpenClose_Test",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_DMA_OPEN_CLOSE
        },
        {
            1U
        },
        {
            ST_UART_CCID_TX_OPEN_CLOSE
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_DISABLE,
        (ST_TT_FULL | ST_TT_STRESS),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 331U, ST_UART_TCT_TX,
        ":PDK-1040:",
        "UART1_TX_DMA_FIFO_Enable",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_DMA_FIFO_ENABLE_PERFORMANCE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL | ST_TT_PERFORMANCE),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 332U, ST_UART_TCT_TX,
        ":PDK-1040:OMAPS00308425:",
        "UART1_TX_DMA_FIFO_Disable",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_DMA_FIFO_DISABLE_PERFORMANCE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL | ST_TT_PERFORMANCE),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 341U, ST_UART_TCT_TX,
        ":PDK-1052:PDK-1058:PDK-1059:OMAPS00304966:",
        "UART1_TX_DMA_FIFO_Trigger_Level_8",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_DMA_TXTRIGLVL_8
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL | ST_TT_PERFORMANCE),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 342U, ST_UART_TCT_TX,
        ":PDK-1052:PDK-1058:PDK-1060:OMAPS00304966:",
        "UART1_TX_DMA_FIFO_Trigger_Level_16",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_DMA_TXTRIGLVL_16
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL | ST_TT_PERFORMANCE),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 343U, ST_UART_TCT_TX,
        ":PDK-1052:PDK-1058:PDK-1061:OMAPS00304966:",
        "UART1_TX_DMA_FIFO_Trigger_Level_32",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_DMA_TXTRIGLVL_32
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL | ST_TT_PERFORMANCE),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 344U, ST_UART_TCT_TX,
        ":PDK-1052:PDK-1058:PDK-1062:",
        "UART1_TX_DMA_FIFO_Trigger_Level_56",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_DMA_TXTRIGLVL_56
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL | ST_TT_PERFORMANCE),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 351U, ST_UART_TCT_TX,
        ":System:",
        "UART1_TX_DMA_RandomTx",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_DMA_RANDOMLOOPCNT_ENABLE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 361U, ST_UART_TCT_TX,
        ":PDK-1049:",
        "UART1_TX_DMA_ChunkSize_1",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_DMA_CHUNKSIZE_1
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 362U, ST_UART_TCT_TX,
        ":PDK-1049:",
        "UART1_TX_DMA_ChunkSize_32",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_DMA_CHUNKSIZE_32
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_REGRESSION | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 363U, ST_UART_TCT_TX,
        ":PDK-1049:",
        "UART1_TX_DMA_ChunkSize_64",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_DMA_CHUNKSIZE_64
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_REGRESSION | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 364U, ST_UART_TCT_TX,
        ":OMAPS00309190:",
        "UART1_TX_DMA_ChunkSize_Invalid(100 bytes)",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_DMA_CHUNKSIZE_INVALID
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL | ST_TT_NEGATIVE),
        DEF_SOC_ID,
    },

    /**************************************************************************
     * UART1 RX Test cases
     *************************************************************************/
    /*
     * UART1 RX Test cases - Polled
     */
    {
        TEST_ENABLE, 501U, ST_UART_TCT_RX,
        ":PDK-1039:PDK-1043:PDK-222:PDK-1064:PDK-1096:PDK-1097:",
        "UART1_RX_Default",
        "Send 1000 bytes through UART console!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 601U, ST_UART_TCT_RX,
        ":PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1064:",
        "UART1_RX_Polled_115200Baudrate_Default",
        "Send 1000 bytes through UART console!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_POLLED_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 651U, ST_UART_TCT_RX,
        ":PDK-1048:PDK-1064:OMAPS00305590:OMAPS00308417:",
        "UART1_RX_Polled_115200Baudrate_Timeout(Every 2 seconds)",
        "You should get timeout every 2 seconds!! After this send 1000 bytes through UART console!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_POLLED_TIMEOUT_2SEC
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 652U, ST_UART_TCT_RX,
        ":PDK-1048:PDK-1064:OMAPS00305590:OMAPS00308417:OMAPS00308406:",
        "UART1_RX_Polled_115200Baudrate_Timeout(Every 10 seconds)",
        "You should get timeout every 10 seconds!! After this send 1000 bytes through UART console!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_POLLED_TIMEOUT_10SEC
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 621U, ST_UART_TCT_RX,
        ":System:",
        "UART1_RX_Polled_OpenClose_Test (1 Bytes per open/close)",
        "Send 1 byte through UART console per open/close!! Keep pressing a key continuously!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_POLLED_OPEN_CLOSE
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        {
            1U
        },
        {
            ST_UART_CCID_RX_OPEN_CLOSE
        },
        PRINT_DISABLE,
        (ST_TT_FULL | ST_TT_STRESS),
        DEF_SOC_ID,
    },

    /*
     * UART1 RX Test cases - Interrupt
     */
    {
        TEST_ENABLE, 701U, ST_UART_TCT_RX,
        ":PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1065:PDK-220:",
        "UART1_RX_Interrupt_115200Baudrate_Default",
        "Send 1000 bytes through UART console!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_INTERRUPT_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 721U, ST_UART_TCT_RX,
        ":System:",
        "UART1_RX_Interrupt_OpenClose_Test (1 Bytes per open/close)",
        "Send 1 byte through UART console per open/close!! Keep pressing a key continuously!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_INTERRUPT_OPEN_CLOSE
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        {
            1U
        },
        {
            ST_UART_CCID_RX_OPEN_CLOSE
        },
        PRINT_DISABLE,
        (ST_TT_FULL | ST_TT_STRESS),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 741U, ST_UART_TCT_RX,
        ":PDK-1052:PDK-1053:PDK-1054:",
        "UART1_RX_Interrupt_FIFO_Trigger_Level_8",
        "Send 1000 bytes through UART console!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_INTERRUPT_RXTRIGLVL_8
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 742U, ST_UART_TCT_RX,
        ":PDK-1052:PDK-1053:PDK-1055:",
        "UART1_RX_Interrupt_FIFO_Trigger_Level_16",
        "Send 1000 bytes through UART console!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_INTERRUPT_RXTRIGLVL_16
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 743U, ST_UART_TCT_RX,
        ":PDK-1052:PDK-1053:PDK-1056:",
        "UART1_RX_Interrupt_FIFO_Trigger_Level_56",
        "Send 1000 bytes through UART console!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_INTERRUPT_RXTRIGLVL_56
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 744U, ST_UART_TCT_RX,
        ":PDK-1052:PDK-1053:PDK-1057:",
        "UART1_RX_Interrupt_FIFO_Trigger_Level_60",
        "Send 1000 bytes through UART console!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_INTERRUPT_RXTRIGLVL_60
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },

    /*
     * UART1 RX Test cases - DMA
     */
    {
        TEST_ENABLE, 801U, ST_UART_TCT_RX,
        ":PDK-1039:PDK-1043:PDK-222:PDK-1066:PDK-221:OMAPS00294713:",
        "UART1_RX_DMA_115200Baudrate_Default",
        "Send 1000 bytes through UART console!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_DMA_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 821U, ST_UART_TCT_RX,
        ":System:",
        "UART1_RX_DMA_OpenClose_Test (8 Bytes per open/close)",
        "Send 8 byte through UART console per open/close!! Keep pressing a key continuously!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_DMA_OPEN_CLOSE
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        {
            1U
        },
        {
            ST_UART_CCID_RX_OPEN_CLOSE
        },
        PRINT_DISABLE,
        (ST_TT_FULL | ST_TT_STRESS),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 831U, ST_UART_TCT_RX,
        ":PDK-1040:",
        "UART1_RX_DMA_FIFO_Enable",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_DMA_FIFO_ENABLE
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 832U, ST_UART_TCT_RX,
        ":PDK-1040:OMAPS00308425:",
        "UART1_RX_DMA_FIFO_Disable",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_DMA_FIFO_DISABLE
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 841U, ST_UART_TCT_RX,
        ":PDK-1052:PDK-1053:PDK-1054:",
        "UART1_RX_DMA_FIFO_Trigger_Level_8",
        "Send 1000 bytes through UART console!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_DMA_RXTRIGLVL_8
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 842U, ST_UART_TCT_RX,
        ":PDK-1052:PDK-1053:PDK-1055:",
        "UART1_RX_DMA_FIFO_Trigger_Level_16",
        "Send 1000 bytes through UART console!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_DMA_RXTRIGLVL_16
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 843U, ST_UART_TCT_RX,
        ":PDK-1052:PDK-1053:PDK-1056:",
        "UART1_RX_DMA_FIFO_Trigger_Level_56",
        "Send 1000 bytes through UART console!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_DMA_RXTRIGLVL_56
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 844U, ST_UART_TCT_RX,
        ":PDK-1052:PDK-1053:PDK-1057:",
        "UART1_RX_DMA_FIFO_Trigger_Level_60",
        "Send 1000 bytes through UART console!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_DMA_RXTRIGLVL_60
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },

    /**************************************************************************
     * UART1 RX to TX Test cases
     *************************************************************************/
    /*
     * UART1 RX to TX Test cases - Polled
     */
    {
        TEST_ENABLE, 1001U, ST_UART_TCT_RX_TO_TX,
        ":PDK-1038:PDK-1039:PDK-1043:PDK-222:PDK-1064:",
        "UART1_RX_TO_TX_Default",
        "Send 1000 bytes through UART console and see the same echoed back in console!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 1101U, ST_UART_TCT_RX_TO_TX,
        ":PDK-1038:PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1064:",
        "UART1_RX_TO_TX_Polled_115200Baudrate_Default",
        "Send 1000 bytes through UART console and see the same echoed back in console!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_POLLED_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_REGRESSION | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },

    /*
     * UART1 RX to TX Test cases - Interrupt
     */
    {
        TEST_ENABLE, 1201U, ST_UART_TCT_RX_TO_TX,
        ":PDK-1038:PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1065:PDK-220:",
        "UART1_RX_TO_TX_Interrupt_115200Baudrate_Default",
        "Send 1000 bytes through UART console and see the same echoed back in console!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_INTERRUPT_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_REGRESSION | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },

    /*
     * UART1 RX to TX Test cases - DMA
     */
    {
        TEST_ENABLE, 1301U, ST_UART_TCT_RX_TO_TX,
        ":PDK-1038:PDK-1039:PDK-1043:PDK-222:PDK-1066:PDK-221:",
        "UART1_RX_TO_TX_DMA_115200Baudrate_Default",
        "Send 1000 bytes through UART console and see the same echoed back in console!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_DMA_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_REGRESSION | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },

    /**************************************************************************
     * UART1 RX and TX (independent) Test cases
     *************************************************************************/
    /*
     * UART1 RX-TX Test cases - Polled
     */
    {
        TEST_ENABLE, 1501U, ST_UART_TCT_RX_TX,
        ":PDK-1038:PDK-1039:PDK-1043:PDK-222:PDK-1044:PDK-1064:",
        "UART1_RX_TX_Default(Simultaneous RX+TX)",
        "Send 1000 bytes through UART console and see the same echoed back in CCS!! Meanwhile TX keeps happening!!", NULL,
        2U,
        {
            ST_INSTANCE_ID_UART1,
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1,
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_DEFAULT,
            ST_UART_HCID_DEFAULT
        },
        {
            1U,
            0U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U,
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 1601U, ST_UART_TCT_RX_TX,
        ":PDK-1038:PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1044:PDK-1064:",
        "UART1_RX_TX_Polled_115200Baudrate_Default(Simultaneous RX+TX)",
        "Send 1000 bytes through UART console and see the same echoed back in CCS!! Meanwhile TX keeps happening!!", NULL,
        2U,
        {
            ST_INSTANCE_ID_UART1,
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1,
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_POLLED_DEFAULT,
            ST_UART_HCID_POLLED_DEFAULT
        },
        {
            1U,
            0U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U,
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },

    /*
     * UART1 RX-TX Test cases - Interrupt
     */
    {
        TEST_ENABLE, 1701U, ST_UART_TCT_RX_TX,
        ":PDK-1038:PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1044:PDK-1065:PDK-220:",
        "UART1_RX_TX_Interrupt_115200Baudrate_Default(Simultaneous RX+TX)",
        "Send 1000 bytes through UART console and see the same echoed back in CCS!! Meanwhile TX keeps happening!!", NULL,
        2U,
        {
            ST_INSTANCE_ID_UART1,
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1,
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_INTERRUPT_DEFAULT,
            ST_UART_HCID_INTERRUPT_DEFAULT
        },
        {
            1U,
            0U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U,
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },

    /*
     * UART1 RX-TX Test cases - DMA
     */
    {
        TEST_ENABLE, 1801U, ST_UART_TCT_RX_TX,
        ":PDK-1038:PDK-1039:PDK-1043:PDK-222:PDK-1066:PDK-221:PDK-1044:",
        "UART1_RX_TX_DMA_115200Baudrate_Default(Simultaneous RX+TX)",
        "Send 1000 bytes through UART console and see the same echoed back in CCS!! Meanwhile TX keeps happening!!", NULL,
        2U,
        {
            ST_INSTANCE_ID_UART1,
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1,
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_DMA_DEFAULT,
            ST_UART_HCID_DMA_DEFAULT
        },
        {
            1U,
            0U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U,
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },

    /**************************************************************************
     * UART2 TX Test cases
     *************************************************************************/
    /*
     * UART2 TX Test cases - Polled
     */
    {
        TEST_ENABLE, 2001U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1043:PDK-222:PDK-1064:",
        "UART2_TX_Default",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART2
        },
        {
            ST_INSTANCE_NAME_UART2
        },
        {
            ST_UART_HCID_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 2101U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1064:",
        "UART2_TX_Polled_115200Baudrate_Default",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART2
        },
        {
            ST_INSTANCE_NAME_UART2
        },
        {
            ST_UART_HCID_POLLED_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 2102U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1064:",
        "UART2_TX_Polled_115200Baudrate_Performance_Test",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART2
        },
        {
            ST_INSTANCE_NAME_UART2
        },
        {
            ST_UART_HCID_POLLED_PERFORMANCE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL | ST_TT_PERFORMANCE),
        DEF_SOC_ID,
    },

    /*
     * UART2 TX Test cases - Interrupt
     */
    {
        TEST_ENABLE, 2201U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1065:PDK-220:",
        "UART2_TX_Interrupt_115200Baudrate_Default",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART2
        },
        {
            ST_INSTANCE_NAME_UART2
        },
        {
            ST_UART_HCID_INTERRUPT_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 2202U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1065:PDK-220:",
        "UART2_TX_Interrupt_115200Baudrate_Performance_Test",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART2
        },
        {
            ST_INSTANCE_NAME_UART2
        },
        {
            ST_UART_HCID_INTERRUPT_PERFORMANCE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL | ST_TT_PERFORMANCE),
        DEF_SOC_ID,
    },

    /*
     * UART2 TX Test cases - DMA
     */
    {
        TEST_ENABLE, 2301U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1043:PDK-222:PDK-1066:PDK-221:",
        "UART2_TX_DMA_115200Baudrate_Default",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART2
        },
        {
            ST_INSTANCE_NAME_UART2
        },
        {
            ST_UART_HCID_DMA_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 2302U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1043:PDK-222:PDK-1066:PDK-221:",
        "UART2_TX_DMA_115200Baudrate_Performance_Test",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART2
        },
        {
            ST_INSTANCE_NAME_UART2
        },
        {
            ST_UART_HCID_DMA_PERFORMANCE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL | ST_TT_PERFORMANCE),
        DEF_SOC_ID,
    },

    /**************************************************************************
     * UART3 TX Test cases
     *************************************************************************/
    /*
     * UART3 TX Test cases - Polled
     */
    {
        TEST_ENABLE, 4001U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1043:PDK-222:PDK-1064:",
        "UART3_TX_Default",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART3
        },
        {
            ST_INSTANCE_NAME_UART3
        },
        {
            ST_UART_HCID_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 4101U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1064:",
        "UART3_TX_Polled_115200Baudrate_Default",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART3
        },
        {
            ST_INSTANCE_NAME_UART3
        },
        {
            ST_UART_HCID_POLLED_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 4102U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1064:",
        "UART3_TX_Polled_115200Baudrate_Performance_Test",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART3
        },
        {
            ST_INSTANCE_NAME_UART3
        },
        {
            ST_UART_HCID_POLLED_PERFORMANCE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL | ST_TT_PERFORMANCE),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 4103U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1064:",
        "UART3_TX_Polled_115200Baudrate_Rampup_Test",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART3
        },
        {
            ST_INSTANCE_NAME_UART3
        },
        {
            ST_UART_HCID_POLLED_PERFORMANCE
        },
        {
            1U
        },
        {
            ST_UART_CCID_RAMP_UP
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_REGRESSION | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 4104U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1064:",
        "UART3_TX_Polled_115200Baudrate_Rampdown_Test",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART3
        },
        {
            ST_INSTANCE_NAME_UART3
        },
        {
            ST_UART_HCID_POLLED_PERFORMANCE
        },
        {
            1U
        },
        {
            ST_UART_CCID_RAMP_DOWN
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_REGRESSION | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },

    /*
     * UART3 TX Test cases - Interrupt
     */
    {
        TEST_ENABLE, 4201U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1065:PDK-220:",
        "UART3_TX_Interrupt_115200Baudrate_Default",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART3
        },
        {
            ST_INSTANCE_NAME_UART3
        },
        {
            ST_UART_HCID_INTERRUPT_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 4202U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1065:PDK-220:",
        "UART3_TX_Interrupt_115200Baudrate_Performance_Test",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART3
        },
        {
            ST_INSTANCE_NAME_UART3
        },
        {
            ST_UART_HCID_INTERRUPT_PERFORMANCE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL | ST_TT_PERFORMANCE),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 4203U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1065:PDK-220:",
        "UART3_TX_Interrupt_115200Baudrate_Rampup_Test",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART3
        },
        {
            ST_INSTANCE_NAME_UART3
        },
        {
            ST_UART_HCID_INTERRUPT_PERFORMANCE
        },
        {
            1U
        },
        {
            ST_UART_CCID_RAMP_UP
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_REGRESSION | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 4204U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1065:PDK-220:",
        "UART3_TX_Interrupt_115200Baudrate_Rampdown_Test",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART3
        },
        {
            ST_INSTANCE_NAME_UART3
        },
        {
            ST_UART_HCID_INTERRUPT_PERFORMANCE
        },
        {
            1U
        },
        {
            ST_UART_CCID_RAMP_DOWN
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_REGRESSION | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },

    /*
     * UART3 TX Test cases - DMA
     */
    {
        TEST_ENABLE, 4301U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1043:PDK-222:PDK-1066:PDK-221:",
        "UART3_TX_DMA_115200Baudrate_Default",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART3
        },
        {
            ST_INSTANCE_NAME_UART3
        },
        {
            ST_UART_HCID_DMA_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 4302U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1043:PDK-222:PDK-1066:PDK-221:",
        "UART3_TX_DMA_115200Baudrate_Performance_Test",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART3
        },
        {
            ST_INSTANCE_NAME_UART3
        },
        {
            ST_UART_HCID_DMA_PERFORMANCE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL | ST_TT_PERFORMANCE),
        DEF_SOC_ID,
    },

    /**************************************************************************
     * UART3 RX Test cases
     *************************************************************************/
    /*
     * UART3 RX Test cases - Polled
     */
    {
        TEST_ENABLE, 4501U, ST_UART_TCT_RX,
        ":PDK-1039:PDK-1043:PDK-222:PDK-1064:",
        "UART3_RX_Default",
        "Send 1000 bytes through UART console!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART3
        },
        {
            ST_INSTANCE_NAME_UART3
        },
        {
            ST_UART_HCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        ST_UART_SOC_ID_TDA2XX,
    },
    {
        TEST_ENABLE, 4601U, ST_UART_TCT_RX,
        ":PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1064:",
        "UART3_RX_Polled_115200Baudrate_Default",
        "Send 1000 bytes through UART console!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART3
        },
        {
            ST_INSTANCE_NAME_UART3
        },
        {
            ST_UART_HCID_POLLED_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        ST_UART_SOC_ID_TDA2XX,
    },

    /*
     * UART3 RX Test cases - Interrupt
     */
    {
        TEST_ENABLE, 4701U, ST_UART_TCT_RX,
        ":PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1065:PDK-220:",
        "UART3_RX_Interrupt_115200Baudrate_Default",
        "Send 1000 bytes through UART console!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART3
        },
        {
            ST_INSTANCE_NAME_UART3
        },
        {
            ST_UART_HCID_INTERRUPT_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        ST_UART_SOC_ID_TDA2XX,
    },

    /*
     * UART3 RX Test cases - DMA
     */
    {
        TEST_ENABLE, 4801U, ST_UART_TCT_RX,
        ":PDK-1039:PDK-1043:PDK-222:PDK-1066:PDK-221:",
        "UART3_RX_DMA_115200Baudrate_Default",
        "Send 1000 bytes through UART console!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART3
        },
        {
            ST_INSTANCE_NAME_UART3
        },
        {
            ST_UART_HCID_DMA_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        ST_UART_SOC_ID_TDA2XX,
    },

    /**************************************************************************
     * UART3 RX to TX Test cases
     *************************************************************************/
    /*
     * UART3 RX to TX Test cases - Polled
     */
    {
        TEST_ENABLE, 5001U, ST_UART_TCT_RX_TO_TX,
        ":PDK-1038:PDK-1039:PDK-1043:PDK-222:PDK-1064:",
        "UART3_RX_TO_TX_Default",
        "Send 1000 bytes through UART console and see the same echoed back in console!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART3
        },
        {
            ST_INSTANCE_NAME_UART3
        },
        {
            ST_UART_HCID_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        ST_UART_SOC_ID_TDA2XX,
    },
    {
        TEST_ENABLE, 5101U, ST_UART_TCT_RX_TO_TX,
        ":PDK-1038:PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1064:",
        "UART3_RX_TO_TX_Polled_115200Baudrate_Default",
        "Send 1000 bytes through UART console and see the same echoed back in console!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART3
        },
        {
            ST_INSTANCE_NAME_UART3
        },
        {
            ST_UART_HCID_POLLED_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        ST_UART_SOC_ID_TDA2XX,
    },

    /*
     * UART3 RX to TX Test cases - Interrupt
     */
    {
        TEST_ENABLE, 5201U, ST_UART_TCT_RX_TO_TX,
        ":PDK-1038:PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1065:PDK-220:",
        "UART3_RX_TO_TX_Interrupt_115200Baudrate_Default",
        "Send 1000 bytes through UART console and see the same echoed back in console!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART3
        },
        {
            ST_INSTANCE_NAME_UART3
        },
        {
            ST_UART_HCID_INTERRUPT_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        ST_UART_SOC_ID_TDA2XX,
    },

    /*
     * UART3 RX to TX Test cases - DMA
     */
    {
        TEST_ENABLE, 5301U, ST_UART_TCT_RX_TO_TX,
        ":PDK-1038:PDK-1039:PDK-1043:PDK-222:PDK-1066:PDK-221:",
        "UART3_RX_TO_TX_DMA_115200Baudrate_Default",
        "Send 1000 bytes through UART console and see the same echoed back in console!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART3
        },
        {
            ST_INSTANCE_NAME_UART3
        },
        {
            ST_UART_HCID_DMA_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        ST_UART_SOC_ID_TDA2XX,
    },

    /**************************************************************************
     * UART4 TX Test cases
     *************************************************************************/
    /*
     * UART4 TX Test cases - Polled
     */
    {
        TEST_ENABLE, 6001U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1043:PDK-222:PDK-1064:",
        "UART4_TX_Default",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART4
        },
        {
            ST_INSTANCE_NAME_UART4
        },
        {
            ST_UART_HCID_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        ST_UART_SOC_ID_TDA2XX_2PX_2EX_TI814X,
    },
    {
        TEST_ENABLE, 6101U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1064:",
        "UART4_TX_Polled_115200Baudrate_Default",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART4
        },
        {
            ST_INSTANCE_NAME_UART4
        },
        {
            ST_UART_HCID_POLLED_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        ST_UART_SOC_ID_TDA2XX_2PX_2EX_TI814X,
    },
    {
        TEST_ENABLE, 6102U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1064:",
        "UART4_TX_Polled_115200Baudrate_Performance_Test",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART4
        },
        {
            ST_INSTANCE_NAME_UART4
        },
        {
            ST_UART_HCID_POLLED_PERFORMANCE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL | ST_TT_PERFORMANCE),
        ST_UART_SOC_ID_TDA2XX_2PX_2EX_TI814X,
    },

    /*
     * UART4 TX Test cases - Interrupt
     */
    {
        TEST_ENABLE, 6201U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1065:PDK-220:OMAPS00308304:",
        "UART4_TX_Interrupt_115200Baudrate_Default",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART4
        },
        {
            ST_INSTANCE_NAME_UART4
        },
        {
            ST_UART_HCID_INTERRUPT_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        ST_UART_SOC_ID_TDA2XX_2PX_2EX_TI814X,
    },
    {
        TEST_ENABLE, 6202U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1065:PDK-220:",
        "UART4_TX_Interrupt_115200Baudrate_Performance_Test",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART4
        },
        {
            ST_INSTANCE_NAME_UART4
        },
        {
            ST_UART_HCID_INTERRUPT_PERFORMANCE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL | ST_TT_PERFORMANCE),
        ST_UART_SOC_ID_TDA2XX_2PX_2EX_TI814X,
    },

    /*
     * UART4 TX Test cases - DMA
     */
    {
        TEST_ENABLE, 6301U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1043:PDK-222:PDK-1066:PDK-221:",
        "UART4_TX_DMA_115200Baudrate_Default",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART4
        },
        {
            ST_INSTANCE_NAME_UART4
        },
        {
            ST_UART_HCID_DMA_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        ST_UART_SOC_ID_TDA2XX_2PX_2EX_TI814X,
    },
    {
        TEST_ENABLE, 6302U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1043:PDK-222:PDK-1066:PDK-221:",
        "UART4_TX_DMA_115200Baudrate_Performance_Test",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART4
        },
        {
            ST_INSTANCE_NAME_UART4
        },
        {
            ST_UART_HCID_DMA_PERFORMANCE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL | ST_TT_PERFORMANCE),
        ST_UART_SOC_ID_TDA2XX_2PX_2EX_TI814X,
    },

    /**************************************************************************
     * UART5 TX Test cases
     *************************************************************************/
    /*
     * UART5 TX Test cases - Polled
     */
    {
        TEST_ENABLE, 8001U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1043:PDK-222:PDK-1064:",
        "UART5_TX_Default",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART5
        },
        {
            ST_INSTANCE_NAME_UART5
        },
        {
            ST_UART_HCID_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        ST_UART_SOC_ID_TDA2XX_2PX_2EX_TI814X,
    },
    {
        TEST_ENABLE, 8101U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1064:",
        "UART5_TX_Polled_115200Baudrate_Default",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART5
        },
        {
            ST_INSTANCE_NAME_UART5
        },
        {
            ST_UART_HCID_POLLED_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        ST_UART_SOC_ID_TDA2XX_2PX_2EX_TI814X,
    },
    {
        TEST_ENABLE, 8102U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1064:",
        "UART5_TX_Polled_115200Baudrate_Performance_Test",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART5
        },
        {
            ST_INSTANCE_NAME_UART5
        },
        {
            ST_UART_HCID_POLLED_PERFORMANCE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL | ST_TT_PERFORMANCE),
        ST_UART_SOC_ID_TDA2XX_2PX_2EX_TI814X,
    },

    /*
     * UART5 TX Test cases - Interrupt
     */
    {
        TEST_ENABLE, 8201U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1065:PDK-220:OMAPS00308304:",
        "UART5_TX_Interrupt_115200Baudrate_Default",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART5
        },
        {
            ST_INSTANCE_NAME_UART5
        },
        {
            ST_UART_HCID_INTERRUPT_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        ST_UART_SOC_ID_TDA2XX_2PX_2EX_TI814X,
    },
    {
        TEST_ENABLE, 8202U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1065:PDK-220:",
        "UART5_TX_Interrupt_115200Baudrate_Performance_Test",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART5
        },
        {
            ST_INSTANCE_NAME_UART5
        },
        {
            ST_UART_HCID_INTERRUPT_PERFORMANCE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL | ST_TT_PERFORMANCE),
        ST_UART_SOC_ID_TDA2XX_2PX_2EX_TI814X,
    },

    /*
     * UART5 TX Test cases - DMA
     */
    {
        TEST_ENABLE, 8301U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1043:PDK-222:PDK-1066:PDK-221:",
        "UART5_TX_DMA_115200Baudrate_Default",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART5
        },
        {
            ST_INSTANCE_NAME_UART5
        },
        {
            ST_UART_HCID_DMA_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        ST_UART_SOC_ID_TDA2XX_2PX_2EX_TI814X,
    },
    {
        TEST_ENABLE, 8302U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1043:PDK-222:PDK-1066:PDK-221:",
        "UART5_TX_DMA_115200Baudrate_Performance_Test",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART5
        },
        {
            ST_INSTANCE_NAME_UART5
        },
        {
            ST_UART_HCID_DMA_PERFORMANCE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL | ST_TT_PERFORMANCE),
        ST_UART_SOC_ID_TDA2XX_2PX_2EX_TI814X,
    },

    /**************************************************************************
     * UART6 TX Test cases
     *************************************************************************/
    /*
     * UART6 TX Test cases - Polled
     */
    {
        TEST_ENABLE, 10001U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1043:PDK-222:PDK-1064:",
        "UART6_TX_Default",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART6
        },
        {
            ST_INSTANCE_NAME_UART6
        },
        {
            ST_UART_HCID_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        ST_UART_SOC_ID_TDA2XX_2PX_2EX_TI814X,
    },
    {
        TEST_ENABLE, 10101U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1064:",
        "UART6_TX_Polled_115200Baudrate_Default",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART6
        },
        {
            ST_INSTANCE_NAME_UART6
        },
        {
            ST_UART_HCID_POLLED_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        ST_UART_SOC_ID_TDA2XX_2PX_2EX_TI814X,
    },
    {
        TEST_ENABLE, 10102U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1064:",
        "UART6_TX_Polled_115200Baudrate_Performance_Test",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART6
        },
        {
            ST_INSTANCE_NAME_UART6
        },
        {
            ST_UART_HCID_POLLED_PERFORMANCE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL | ST_TT_PERFORMANCE),
        ST_UART_SOC_ID_TDA2XX_2PX_2EX_TI814X,
    },

    /*
     * UART6 TX Test cases - Interrupt
     */
    {
        TEST_ENABLE, 10201U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1065:PDK-220:OMAPS00308304:",
        "UART6_TX_Interrupt_115200Baudrate_Default",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART6
        },
        {
            ST_INSTANCE_NAME_UART6
        },
        {
            ST_UART_HCID_INTERRUPT_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        ST_UART_SOC_ID_TDA2XX_2PX_2EX_TI814X,
    },
    {
        TEST_ENABLE, 10202U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1065:PDK-220:",
        "UART6_TX_Interrupt_115200Baudrate_Performance_Test",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART6
        },
        {
            ST_INSTANCE_NAME_UART6
        },
        {
            ST_UART_HCID_INTERRUPT_PERFORMANCE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL | ST_TT_PERFORMANCE),
        ST_UART_SOC_ID_TDA2XX_2PX_2EX_TI814X,
    },

    /*
     * UART6 TX Test cases - DMA
     */
    {
        TEST_ENABLE, 10301U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1043:PDK-222:PDK-1066:PDK-221:",
        "UART6_TX_DMA_115200Baudrate_Default",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART6
        },
        {
            ST_INSTANCE_NAME_UART6
        },
        {
            ST_UART_HCID_DMA_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        ST_UART_SOC_ID_TDA2XX_2PX_2EX_TI814X,
    },
    {
        TEST_ENABLE, 10302U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1043:PDK-222:PDK-1066:PDK-221:",
        "UART6_TX_DMA_115200Baudrate_Performance_Test",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART6
        },
        {
            ST_INSTANCE_NAME_UART6
        },
        {
            ST_UART_HCID_DMA_PERFORMANCE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL | ST_TT_PERFORMANCE),
        ST_UART_SOC_ID_TDA2XX_2PX_2EX_TI814X,
    },

    /**************************************************************************
     * UART7 TX Test cases
     *************************************************************************/
    /*
     * UART7 TX Test cases - Polled
     */
    {
        TEST_ENABLE, 12001U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1043:PDK-222:PDK-1064:",
        "UART7_TX_Default",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART7
        },
        {
            ST_INSTANCE_NAME_UART7
        },
        {
            ST_UART_HCID_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        ST_UART_SOC_ID_TDA2XX_2PX_2EX,
    },
    {
        TEST_ENABLE, 12101U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1064:",
        "UART7_TX_Polled_115200Baudrate_Default",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART7
        },
        {
            ST_INSTANCE_NAME_UART7
        },
        {
            ST_UART_HCID_POLLED_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        ST_UART_SOC_ID_TDA2XX_2PX_2EX,
    },
    {
        TEST_ENABLE, 12102U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1064:",
        "UART7_TX_Polled_115200Baudrate_Performance_Test",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART7
        },
        {
            ST_INSTANCE_NAME_UART7
        },
        {
            ST_UART_HCID_POLLED_PERFORMANCE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL | ST_TT_PERFORMANCE),
        ST_UART_SOC_ID_TDA2XX_2PX_2EX,
    },

    /*
     * UART7 TX Test cases - Interrupt
     */
    {
        TEST_ENABLE, 12201U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1065:PDK-220:OMAPS00308304:",
        "UART7_TX_Interrupt_115200Baudrate_Default",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART7
        },
        {
            ST_INSTANCE_NAME_UART7
        },
        {
            ST_UART_HCID_INTERRUPT_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        ST_UART_SOC_ID_TDA2XX_2PX_2EX,
    },
    {
        TEST_ENABLE, 12202U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1065:PDK-220:",
        "UART7_TX_Interrupt_115200Baudrate_Performance_Test",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART7
        },
        {
            ST_INSTANCE_NAME_UART7
        },
        {
            ST_UART_HCID_INTERRUPT_PERFORMANCE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL | ST_TT_PERFORMANCE),
        ST_UART_SOC_ID_TDA2XX_2PX_2EX,
    },

    /*
     * UART7 TX Test cases - DMA
     */
    {
        TEST_ENABLE, 12301U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1043:PDK-222:PDK-1066:PDK-221:",
        "UART7_TX_DMA_115200Baudrate_Default",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART7
        },
        {
            ST_INSTANCE_NAME_UART7
        },
        {
            ST_UART_HCID_DMA_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        ST_UART_SOC_ID_TDA2XX_2PX_2EX,
    },
    {
        TEST_ENABLE, 12302U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1043:PDK-222:PDK-1066:PDK-221:",
        "UART7_TX_DMA_115200Baudrate_Performance_Test",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART7
        },
        {
            ST_INSTANCE_NAME_UART7
        },
        {
            ST_UART_HCID_DMA_PERFORMANCE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL | ST_TT_PERFORMANCE),
        ST_UART_SOC_ID_TDA2XX_2PX_2EX,
    },

    /**************************************************************************
     * UART8 TX Test cases
     *************************************************************************/
    /*
     * UART8 TX Test cases - Polled
     */
    {
        TEST_ENABLE, 14001U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1043:PDK-222:PDK-1064:",
        "UART8_TX_Default",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART8
        },
        {
            ST_INSTANCE_NAME_UART8
        },
        {
            ST_UART_HCID_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        ST_UART_SOC_ID_TDA2XX_2PX_2EX,
    },
    {
        TEST_ENABLE, 14101U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1064:",
        "UART8_TX_Polled_115200Baudrate_Default",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART8
        },
        {
            ST_INSTANCE_NAME_UART8
        },
        {
            ST_UART_HCID_POLLED_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        ST_UART_SOC_ID_TDA2XX_2PX_2EX,
    },
    {
        TEST_ENABLE, 14102U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1064:",
        "UART8_TX_Polled_115200Baudrate_Performance_Test",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART8
        },
        {
            ST_INSTANCE_NAME_UART8
        },
        {
            ST_UART_HCID_POLLED_PERFORMANCE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL | ST_TT_PERFORMANCE),
        ST_UART_SOC_ID_TDA2XX_2PX_2EX,
    },

    /*
     * UART8 TX Test cases - Interrupt
     */
    {
        TEST_ENABLE, 14201U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1065:PDK-220:OMAPS00308304:",
        "UART8_TX_Interrupt_115200Baudrate_Default",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART8
        },
        {
            ST_INSTANCE_NAME_UART8
        },
        {
            ST_UART_HCID_INTERRUPT_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        ST_UART_SOC_ID_TDA2XX_2PX_2EX,
    },
    {
        TEST_ENABLE, 14202U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1065:PDK-220:",
        "UART8_TX_Interrupt_115200Baudrate_Performance_Test",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART8
        },
        {
            ST_INSTANCE_NAME_UART8
        },
        {
            ST_UART_HCID_INTERRUPT_PERFORMANCE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL | ST_TT_PERFORMANCE),
        ST_UART_SOC_ID_TDA2XX_2PX_2EX,
    },

    /*
     * UART8 TX Test cases - DMA
     */
    {
        TEST_ENABLE, 14301U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1043:PDK-222:PDK-1066:PDK-221:",
        "UART8_TX_DMA_115200Baudrate_Default",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART8
        },
        {
            ST_INSTANCE_NAME_UART8
        },
        {
            ST_UART_HCID_DMA_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        ST_UART_SOC_ID_TDA2XX_2PX_2EX,
    },
    {
        TEST_ENABLE, 14302U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1043:PDK-222:PDK-1066:PDK-221:",
        "UART8_TX_DMA_115200Baudrate_Performance_Test",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART8
        },
        {
            ST_INSTANCE_NAME_UART8
        },
        {
            ST_UART_HCID_DMA_PERFORMANCE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL | ST_TT_PERFORMANCE),
        ST_UART_SOC_ID_TDA2XX_2PX_2EX,
    },

    /**************************************************************************
     * UART9 TX Test cases
     *************************************************************************/
    /*
     * UART9 TX Test cases - Polled
     */
    {
        TEST_ENABLE, 16001U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1043:PDK-222:PDK-1064:",
        "UART9_TX_Default",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART9
        },
        {
            ST_INSTANCE_NAME_UART9
        },
        {
            ST_UART_HCID_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        ST_UART_SOC_ID_TDA2XX_2PX_2EX,
    },
    {
        TEST_ENABLE, 16101U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1064:",
        "UART9_TX_Polled_115200Baudrate_Default",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART9
        },
        {
            ST_INSTANCE_NAME_UART9
        },
        {
            ST_UART_HCID_POLLED_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        ST_UART_SOC_ID_TDA2XX_2PX_2EX,
    },
    {
        TEST_ENABLE, 16102U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1064:",
        "UART9_TX_Polled_115200Baudrate_Performance_Test",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART9
        },
        {
            ST_INSTANCE_NAME_UART9
        },
        {
            ST_UART_HCID_POLLED_PERFORMANCE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL | ST_TT_PERFORMANCE),
        ST_UART_SOC_ID_TDA2XX_2PX_2EX,
    },

    /*
     * UART9 TX Test cases - Interrupt
     */
    {
        TEST_ENABLE, 16201U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1065:PDK-220:OMAPS00308304:",
        "UART9_TX_Interrupt_115200Baudrate_Default",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART9
        },
        {
            ST_INSTANCE_NAME_UART9
        },
        {
            ST_UART_HCID_INTERRUPT_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        ST_UART_SOC_ID_TDA2XX_2PX_2EX,
    },
    {
        TEST_ENABLE, 16202U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1065:PDK-220:",
        "UART9_TX_Interrupt_115200Baudrate_Performance_Test",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART9
        },
        {
            ST_INSTANCE_NAME_UART9
        },
        {
            ST_UART_HCID_INTERRUPT_PERFORMANCE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL | ST_TT_PERFORMANCE),
        ST_UART_SOC_ID_TDA2XX_2PX_2EX,
    },

    /*
     * UART9 TX Test cases - DMA
     */
    {
        TEST_ENABLE, 16301U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1043:PDK-222:PDK-1066:PDK-221:",
        "UART9_TX_DMA_115200Baudrate_Default",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART9
        },
        {
            ST_INSTANCE_NAME_UART9
        },
        {
            ST_UART_HCID_DMA_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        ST_UART_SOC_ID_TDA2XX_2PX_2EX,
    },
    {
        TEST_ENABLE, 16302U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1043:PDK-222:PDK-1066:PDK-221:",
        "UART9_TX_DMA_115200Baudrate_Performance_Test",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART9
        },
        {
            ST_INSTANCE_NAME_UART9
        },
        {
            ST_UART_HCID_DMA_PERFORMANCE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL | ST_TT_PERFORMANCE),
        ST_UART_SOC_ID_TDA2XX_2PX_2EX,
    },

    /**************************************************************************
     * UART10 TX Test cases
     *************************************************************************/
    /*
     * UART10 TX Test cases - Polled
     */
    {
        TEST_ENABLE, 18001U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1043:PDK-222:PDK-1064:",
        "UART10_TX_Default",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART10
        },
        {
            ST_INSTANCE_NAME_UART10
        },
        {
            ST_UART_HCID_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        ST_UART_SOC_ID_TDA2XX_2PX_2EX,
    },
    {
        TEST_ENABLE, 18101U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1064:",
        "UART10_TX_Polled_115200Baudrate_Default",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART10
        },
        {
            ST_INSTANCE_NAME_UART10
        },
        {
            ST_UART_HCID_POLLED_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        ST_UART_SOC_ID_TDA2XX_2PX_2EX,
    },
    {
        TEST_ENABLE, 18102U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1064:",
        "UART10_TX_Polled_115200Baudrate_Performance_Test",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART10
        },
        {
            ST_INSTANCE_NAME_UART10
        },
        {
            ST_UART_HCID_POLLED_PERFORMANCE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL | ST_TT_PERFORMANCE),
        ST_UART_SOC_ID_TDA2XX_2PX_2EX,
    },

    /*
     * UART10 TX Test cases - Interrupt
     */
    {
        TEST_ENABLE, 18201U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1065:PDK-220:OMAPS00308304:",
        "UART10_TX_Interrupt_115200Baudrate_Default",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART10
        },
        {
            ST_INSTANCE_NAME_UART10
        },
        {
            ST_UART_HCID_INTERRUPT_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        ST_UART_SOC_ID_TDA2XX_2PX_2EX,
    },
    {
        TEST_ENABLE, 18202U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1065:PDK-220:",
        "UART10_TX_Interrupt_115200Baudrate_Performance_Test",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART10
        },
        {
            ST_INSTANCE_NAME_UART10
        },
        {
            ST_UART_HCID_INTERRUPT_PERFORMANCE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL | ST_TT_PERFORMANCE),
        ST_UART_SOC_ID_TDA2XX_2PX_2EX,
    },

    /*
     * UART10 TX Test cases - DMA
     */
    {
        TEST_ENABLE, 18301U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1043:PDK-222:PDK-1066:PDK-221:",
        "UART10_TX_DMA_115200Baudrate_Default",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART10
        },
        {
            ST_INSTANCE_NAME_UART10
        },
        {
            ST_UART_HCID_DMA_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        ST_UART_SOC_ID_TDA2XX_2PX_2EX,
    },
    {
        TEST_ENABLE, 18302U, ST_UART_TCT_TX,
        ":PDK-1039:PDK-1043:PDK-222:PDK-1066:PDK-221:",
        "UART10_TX_DMA_115200Baudrate_Performance_Test",
        NULL, NULL,
        1U,
        {
            ST_INSTANCE_ID_UART10
        },
        {
            ST_INSTANCE_NAME_UART10
        },
        {
            ST_UART_HCID_DMA_PERFORMANCE
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL | ST_TT_PERFORMANCE),
        ST_UART_SOC_ID_TDA2XX_2PX_2EX,
    },

    /**************************************************************************
     * Multi instance testing
     *************************************************************************/
    /*
     * UART1 TX + UART3 TX Test cases
     */
    {
        TEST_ENABLE, 20001U, ST_UART_TCT_TX,
        ":PDK-1037:PDK-1064:",
        "UART1_TX_UART3_TX_Polled_115200Baudrate_Multi_Instance_Test",
        NULL, NULL,
        2U,
        {
            ST_INSTANCE_ID_UART1,
            ST_INSTANCE_ID_UART3
        },
        {
            ST_INSTANCE_NAME_UART1,
            ST_INSTANCE_NAME_UART3
        },
        {
            ST_UART_HCID_POLLED_PERFORMANCE,
            ST_UART_HCID_POLLED_PERFORMANCE
        },
        {
            1U,
            1U
        },
        {
            ST_UART_CCID_DEFAULT,
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 20002U, ST_UART_TCT_TX,
        ":PDK-1037:PDK-1064:",
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
        "UART1-10_TX_Polled_115200Baudrate_All_Instance_Test",
        NULL, NULL,
        10U,
#else
        "UART1-3_TX_Polled_115200Baudrate_All_Instance_Test",
        NULL, NULL,
        3U,
#endif  /* Tda2xx */
        {
            ST_INSTANCE_ID_UART1,
            ST_INSTANCE_ID_UART2,
            ST_INSTANCE_ID_UART3,
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
            ST_INSTANCE_ID_UART4,
            ST_INSTANCE_ID_UART5,
            ST_INSTANCE_ID_UART6,
            ST_INSTANCE_ID_UART7,
            ST_INSTANCE_ID_UART8,
            ST_INSTANCE_ID_UART9,
            ST_INSTANCE_ID_UART10
#endif  /* Tda2xx */
        },
        {
            ST_INSTANCE_NAME_UART1,
            ST_INSTANCE_NAME_UART2,
            ST_INSTANCE_NAME_UART3,
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
            ST_INSTANCE_NAME_UART4,
            ST_INSTANCE_NAME_UART5,
            ST_INSTANCE_NAME_UART6,
            ST_INSTANCE_NAME_UART7,
            ST_INSTANCE_NAME_UART8,
            ST_INSTANCE_NAME_UART9,
            ST_INSTANCE_NAME_UART10
#endif  /* Tda2xx */
        },
        {
            ST_UART_HCID_POLLED_PERFORMANCE,
            ST_UART_HCID_POLLED_PERFORMANCE,
            ST_UART_HCID_POLLED_PERFORMANCE,
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
            ST_UART_HCID_POLLED_PERFORMANCE,
            ST_UART_HCID_POLLED_PERFORMANCE,
            ST_UART_HCID_POLLED_PERFORMANCE,
            ST_UART_HCID_POLLED_PERFORMANCE,
            ST_UART_HCID_POLLED_PERFORMANCE,
            ST_UART_HCID_POLLED_PERFORMANCE,
            ST_UART_HCID_POLLED_PERFORMANCE
#endif  /* Tda2xx */
        },
        {
            1U,
            1U,
            1U,
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
            1U,
            1U,
            1U,
            1U,
            1U,
            1U,
            1U
#endif  /* Tda2xx */
        },
        {
            ST_UART_CCID_DEFAULT,
            ST_UART_CCID_DEFAULT,
            ST_UART_CCID_DEFAULT,
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
            ST_UART_CCID_DEFAULT,
            ST_UART_CCID_DEFAULT,
            ST_UART_CCID_DEFAULT,
            ST_UART_CCID_DEFAULT,
            ST_UART_CCID_DEFAULT,
            ST_UART_CCID_DEFAULT,
            ST_UART_CCID_DEFAULT
#endif  /* Tda2xx */
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 20011U, ST_UART_TCT_TX,
        ":PDK-1037:PDK-1065:PDK-220:",
        "UART1_TX_UART3_TX_Interrupt_115200Baudrate_Multi_Instance_Test",
        NULL, NULL,
        2U,
        {
            ST_INSTANCE_ID_UART1,
            ST_INSTANCE_ID_UART3
        },
        {
            ST_INSTANCE_NAME_UART1,
            ST_INSTANCE_NAME_UART3
        },
        {
            ST_UART_HCID_INTERRUPT_PERFORMANCE,
            ST_UART_HCID_INTERRUPT_PERFORMANCE
        },
        {
            1U,
            1U
        },
        {
            ST_UART_CCID_DEFAULT,
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 20012U, ST_UART_TCT_TX,
        ":PDK-1037:PDK-1065:PDK-220:",
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
        "UART1-10_TX_Interrupt_115200Baudrate_All_Instance_Test",
        NULL, NULL,
        10U,
#else
        "UART1-3_TX_Interrupt_115200Baudrate_All_Instance_Test",
        NULL, NULL,
        3U,
#endif  /* Tda2xx */
        {
            ST_INSTANCE_ID_UART1,
            ST_INSTANCE_ID_UART2,
            ST_INSTANCE_ID_UART3,
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
            ST_INSTANCE_ID_UART4,
            ST_INSTANCE_ID_UART5,
            ST_INSTANCE_ID_UART6,
            ST_INSTANCE_ID_UART7,
            ST_INSTANCE_ID_UART8,
            ST_INSTANCE_ID_UART9,
            ST_INSTANCE_ID_UART10
#endif  /* Tda2xx */
        },
        {
            ST_INSTANCE_NAME_UART1,
            ST_INSTANCE_NAME_UART2,
            ST_INSTANCE_NAME_UART3,
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
            ST_INSTANCE_NAME_UART4,
            ST_INSTANCE_NAME_UART5,
            ST_INSTANCE_NAME_UART6,
            ST_INSTANCE_NAME_UART7,
            ST_INSTANCE_NAME_UART8,
            ST_INSTANCE_NAME_UART9,
            ST_INSTANCE_NAME_UART10
#endif  /* Tda2xx */
        },
        {
            ST_UART_HCID_INTERRUPT_PERFORMANCE,
            ST_UART_HCID_INTERRUPT_PERFORMANCE,
            ST_UART_HCID_INTERRUPT_PERFORMANCE,
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
            ST_UART_HCID_INTERRUPT_PERFORMANCE,
            ST_UART_HCID_INTERRUPT_PERFORMANCE,
            ST_UART_HCID_INTERRUPT_PERFORMANCE,
            ST_UART_HCID_INTERRUPT_PERFORMANCE,
            ST_UART_HCID_INTERRUPT_PERFORMANCE,
            ST_UART_HCID_INTERRUPT_PERFORMANCE,
            ST_UART_HCID_INTERRUPT_PERFORMANCE
#endif  /* Tda2xx */
        },
        {
            1U,
            1U,
            1U,
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
            1U,
            1U,
            1U,
            1U,
            1U,
            1U,
            1U,
            1U,
            1U
#endif  /* Tda2xx */
        },
        {
            ST_UART_CCID_DEFAULT,
            ST_UART_CCID_DEFAULT,
            ST_UART_CCID_DEFAULT,
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
            ST_UART_CCID_DEFAULT,
            ST_UART_CCID_DEFAULT,
            ST_UART_CCID_DEFAULT,
            ST_UART_CCID_DEFAULT,
            ST_UART_CCID_DEFAULT,
            ST_UART_CCID_DEFAULT,
            ST_UART_CCID_DEFAULT
#endif  /* Tda2xx */
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 20021U, ST_UART_TCT_TX,
        ":PDK-1037:PDK-1066:PDK-221:OMAPS00304966:",
        "UART1_TX_UART3_TX_DMA_115200Baudrate_Multi_Instance_Test",
        NULL, NULL,
        2U,
        {
            ST_INSTANCE_ID_UART1,
            ST_INSTANCE_ID_UART3
        },
        {
            ST_INSTANCE_NAME_UART1,
            ST_INSTANCE_NAME_UART3
        },
        {
            ST_UART_HCID_DMA_PERFORMANCE,
            ST_UART_HCID_DMA_PERFORMANCE
        },
        {
            1U,
            1U
        },
        {
            ST_UART_CCID_DEFAULT,
            ST_UART_CCID_DEFAULT
        },
        {
            0U
        },
        {
            ST_UART_CCID_NONE
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },

    /*
     * UART1 TX + UART3 RX-TX Test cases
     */
    {
        TEST_ENABLE, 20101U, ST_UART_TCT_RX_TO_TX,
        ":PDK-1037:PDK-1038:PDK-1065:PDK-220:",
        "UART1_TX_UART3_RX_TO_TX_Interrupt_115200Baudrate_Multi_Instance_Test",
        NULL, NULL,
        2U,
        {
            ST_INSTANCE_ID_UART1,
            ST_INSTANCE_ID_UART3
        },
        {
            ST_INSTANCE_NAME_UART1,
            ST_INSTANCE_NAME_UART3
        },
        {
            ST_UART_HCID_INTERRUPT_PERFORMANCE,
            ST_UART_HCID_INTERRUPT_DEFAULT
        },
        {
            1U,
            1U
        },
        {
            ST_UART_CCID_DEFAULT,
            ST_UART_CCID_DEFAULT
        },
        {
            0U,
            1U,
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        ST_UART_SOC_ID_TDA2XX,
    },
    {
        TEST_ENABLE, 0U, ST_UART_TCT_HALT,
        NULL,
        " Set UART3 baud rate to 38400 and all other parameter to default!!\r\n"
        " Press any alpha numeric key to continue: ",
        NULL, NULL, 0U, {0U}, {NULL}, {ST_UART_HCID_NONE}, {0U},
        {ST_UART_CCID_NONE}, {0U}, {ST_UART_CCID_NONE},
        PRINT_ENABLE, ST_TT_MISC, DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 20102U, ST_UART_TCT_RX_TO_TX,
        ":PDK-1037:PDK-1038:",
        "UART1_TX_UART3_RX_TO_TX_Interrupt_AlphineUsecase_UART1-115200Baudrate_UART3-38400Baudrate",
        NULL, NULL,
        2U,
        {
            ST_INSTANCE_ID_UART1,
            ST_INSTANCE_ID_UART3
        },
        {
            ST_INSTANCE_NAME_UART1,
            ST_INSTANCE_NAME_UART3
        },
        {
            ST_UART_HCID_INTERRUPT_PERFORMANCE,
            ST_UART_HCID_INTERRUPT_BAUDRATE_38400
        },
        {
            1U,
            1U
        },
        {
            ST_UART_CCID_DEFAULT,
            ST_UART_CCID_DEFAULT
        },
        {
            0U,
            1U,
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        ST_UART_SOC_ID_TDA2XX,
    },

    /*
     * 2400 baud rate UART1 RX to TX Test cases
     */
    {
        TEST_ENABLE, 0U, ST_UART_TCT_HALT,
        NULL,
        " Set UART1 baud rate to 2400 and all other parameter to default!!\r\n"
        " Press any alpha numeric key to continue: ",
        NULL, NULL, 0U, {0U}, {NULL}, {ST_UART_HCID_NONE}, {0U},
        {ST_UART_CCID_NONE}, {0U}, {ST_UART_CCID_NONE},
        PRINT_ENABLE, ST_TT_MISC, DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 22001U, ST_UART_TCT_RX_TO_TX,
        ":PDK-1038:PDK-1039:PDK-1043:PDK-222:PDK-1064:PDK-1067:PDK-1068:",
        "UART1_RX_TO_TX_Polled_2400Baudrate",
        "Send 1000 bytes through UART console and see the same echoed back in console!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_POLLED_BAUDRATE_2400
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 22002U, ST_UART_TCT_RX_TO_TX,
        ":PDK-1038:PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1065:PDK-220:PDK-1067:PDK-1068:",
        "UART1_RX_TO_TX_Interrupt_2400Baudrate",
        "Send 1000 bytes through UART console and see the same echoed back in console!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_INTERRUPT_BAUDRATE_2400
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 22003U, ST_UART_TCT_RX_TO_TX,
        ":PDK-1038:PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1066:PDK-221:PDK-1067:PDK-1068:",
        "UART1_RX_TO_TX_DMA_2400Baudrate",
        "Send 1000 bytes through UART console and see the same echoed back in console!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_DMA_BAUDRATE_2400
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },

    /*
     * 4800 baud rate UART1 RX to TX Test cases
     */
    {
        TEST_ENABLE, 0U, ST_UART_TCT_HALT,
        NULL,
        " Set UART1 baud rate to 4800 and all other parameter to default!!\r\n"
        " Press any alpha numeric key to continue: ",
        NULL, NULL, 0U, {0U}, {NULL}, {ST_UART_HCID_NONE}, {0U},
        {ST_UART_CCID_NONE}, {0U}, {ST_UART_CCID_NONE},
        PRINT_ENABLE, ST_TT_MISC, DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 22011U, ST_UART_TCT_RX_TO_TX,
        ":PDK-1038:PDK-1039:PDK-1043:PDK-222:PDK-1064:PDK-1067:",
        "UART1_RX_TO_TX_Polled_4800Baudrate",
        "Send 1000 bytes through UART console and see the same echoed back in console!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_POLLED_BAUDRATE_4800
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 22012U, ST_UART_TCT_RX_TO_TX,
        ":PDK-1038:PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1065:PDK-220:PDK-1067:",
        "UART1_RX_TO_TX_Interrupt_4800Baudrate",
        "Send 1000 bytes through UART console and see the same echoed back in console!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_INTERRUPT_BAUDRATE_4800
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 22013U, ST_UART_TCT_RX_TO_TX,
        ":PDK-1038:PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1066:PDK-221:PDK-1067:",
        "UART1_RX_TO_TX_DMA_4800Baudrate",
        "Send 1000 bytes through UART console and see the same echoed back in console!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_DMA_BAUDRATE_4800
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },

    /*
     * 9600 baud rate UART1 RX to TX Test cases
     */
    {
        TEST_ENABLE, 0U, ST_UART_TCT_HALT,
        NULL,
        " Set UART1 baud rate to 9600 and all other parameter to default!!\r\n"
        " Press any alpha numeric key to continue: ",
        NULL, NULL, 0U, {0U}, {NULL}, {ST_UART_HCID_NONE}, {0U},
        {ST_UART_CCID_NONE}, {0U}, {ST_UART_CCID_NONE},
        PRINT_ENABLE, ST_TT_MISC, DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 22021U, ST_UART_TCT_RX_TO_TX,
        ":PDK-1038:PDK-1039:PDK-1043:PDK-222:PDK-1064:PDK-1067:PDK-1069:",
        "UART1_RX_TO_TX_Polled_9600Baudrate",
        "Send 1000 bytes through UART console and see the same echoed back in console!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_POLLED_BAUDRATE_9600
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 22022U, ST_UART_TCT_RX_TO_TX,
        ":PDK-1038:PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1065:PDK-220:PDK-1067:PDK-1069:",
        "UART1_RX_TO_TX_Interrupt_9600Baudrate",
        "Send 1000 bytes through UART console and see the same echoed back in console!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_INTERRUPT_BAUDRATE_9600
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 22023U, ST_UART_TCT_RX_TO_TX,
        ":PDK-1038:PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1066:PDK-221:PDK-1067:PDK-1069:",
        "UART1_RX_TO_TX_DMA_9600Baudrate",
        "Send 1000 bytes through UART console and see the same echoed back in console!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_DMA_BAUDRATE_9600
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },

    /*
     * 19200 baud rate UART1 RX to TX Test cases
     */
    {
        TEST_ENABLE, 0U, ST_UART_TCT_HALT,
        NULL,
        " Set UART1 baud rate to 19200 and all other parameter to default!!\r\n"
        " Press any alpha numeric key to continue: ",
        NULL, NULL, 0U, {0U}, {NULL}, {ST_UART_HCID_NONE}, {0U},
        {ST_UART_CCID_NONE}, {0U}, {ST_UART_CCID_NONE},
        PRINT_ENABLE, ST_TT_MISC, DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 22031U, ST_UART_TCT_RX_TO_TX,
        ":PDK-1038:PDK-1039:PDK-1043:PDK-222:PDK-1064:PDK-1067:PDK-1070:",
        "UART1_RX_TO_TX_Polled_19200Baudrate",
        "Send 1000 bytes through UART console and see the same echoed back in console!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_POLLED_BAUDRATE_19200
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 22032U, ST_UART_TCT_RX_TO_TX,
        ":PDK-1038:PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1065:PDK-220:PDK-1067:PDK-1070:",
        "UART1_RX_TO_TX_Interrupt_19200Baudrate",
        "Send 1000 bytes through UART console and see the same echoed back in console!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_INTERRUPT_BAUDRATE_19200
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 22033U, ST_UART_TCT_RX_TO_TX,
        ":PDK-1038:PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1066:PDK-221:PDK-1067:PDK-1070:",
        "UART1_RX_TO_TX_DMA_19200Baudrate",
        "Send 1000 bytes through UART console and see the same echoed back in console!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_DMA_BAUDRATE_19200
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },

    /*
     * 38400 baud rate UART1 RX to TX Test cases
     */
    {
        TEST_ENABLE, 0U, ST_UART_TCT_HALT,
        NULL,
        " Set UART1 baud rate to 38400 and all other parameter to default!!\r\n"
        " Press any alpha numeric key to continue: ",
        NULL, NULL, 0U, {0U}, {NULL}, {ST_UART_HCID_NONE}, {0U},
        {ST_UART_CCID_NONE}, {0U}, {ST_UART_CCID_NONE},
        PRINT_ENABLE, ST_TT_MISC, DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 22041U, ST_UART_TCT_RX_TO_TX,
        ":PDK-1038:PDK-1039:PDK-1043:PDK-222:PDK-1064:PDK-1067:PDK-1071:",
        "UART1_RX_TO_TX_Polled_38400Baudrate",
        "Send 1000 bytes through UART console and see the same echoed back in console!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_POLLED_BAUDRATE_38400
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 22042U, ST_UART_TCT_RX_TO_TX,
        ":PDK-1038:PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1065:PDK-220:PDK-1067:PDK-1071:",
        "UART1_RX_TO_TX_Interrupt_38400Baudrate",
        "Send 1000 bytes through UART console and see the same echoed back in console!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_INTERRUPT_BAUDRATE_38400
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 22043U, ST_UART_TCT_RX_TO_TX,
        ":PDK-1038:PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1066:PDK-221:PDK-1067:PDK-1071:",
        "UART1_RX_TO_TX_DMA_38400Baudrate",
        "Send 1000 bytes through UART console and see the same echoed back in console!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_DMA_BAUDRATE_38400
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },

    /*
     * 57600 baud rate UART1 RX to TX Test cases
     */
    {
        TEST_ENABLE, 0U, ST_UART_TCT_HALT,
        NULL,
        " Set UART1 baud rate to 57600 and all other parameter to default!!\r\n"
        " Press any alpha numeric key to continue: ",
        NULL, NULL, 0U, {0U}, {NULL}, {ST_UART_HCID_NONE}, {0U},
        {ST_UART_CCID_NONE}, {0U}, {ST_UART_CCID_NONE},
        PRINT_ENABLE, ST_TT_MISC, DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 22051U, ST_UART_TCT_RX_TO_TX,
        ":PDK-1038:PDK-1039:PDK-1043:PDK-222:PDK-1064:PDK-1067:PDK-1072:",
        "UART1_RX_TO_TX_Polled_57600Baudrate",
        "Send 1000 bytes through UART console and see the same echoed back in console!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_POLLED_BAUDRATE_57600
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 22052U, ST_UART_TCT_RX_TO_TX,
        ":PDK-1038:PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1065:PDK-220:PDK-1067:PDK-1072:",
        "UART1_RX_TO_TX_Interrupt_57600Baudrate",
        "Send 1000 bytes through UART console and see the same echoed back in console!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_INTERRUPT_BAUDRATE_57600
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 22053U, ST_UART_TCT_RX_TO_TX,
        ":PDK-1038:PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1066:PDK-221:PDK-1067:PDK-1072:",
        "UART1_RX_TO_TX_DMA_57600Baudrate",
        "Send 1000 bytes through UART console and see the same echoed back in console!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_DMA_BAUDRATE_57600
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },

    /*
     * Different stop bits 1 length UART1 RX to TX Test cases
     */
    {
        TEST_ENABLE, 0U, ST_UART_TCT_HALT,
        NULL,
        " Set UART1 stop bits to 1 and all other parameter to default!!\r\n"
        " Press any alpha numeric key to continue: ",
        NULL, NULL, 0U, {0U}, {NULL}, {ST_UART_HCID_NONE}, {0U},
        {ST_UART_CCID_NONE}, {0U}, {ST_UART_CCID_NONE},
        PRINT_ENABLE, ST_TT_MISC, DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 22101U, ST_UART_TCT_RX_TO_TX,
        ":PDK-1038:PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1064:PDK-1081:PDK-219:PDK-1082:",
        "UART1_RX_TO_TX_Polled_Stopbits_1",
        "Send 1000 bytes through UART console and see the same echoed back in console!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_POLLED_STOPBITS_1
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 22102U, ST_UART_TCT_RX_TO_TX,
        ":PDK-1038:PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1065:PDK-220:PDK-1081:PDK-219:PDK-1082:",
        "UART1_RX_TO_TX_Interrupt_Stopbits_1",
        "Send 1000 bytes through UART console and see the same echoed back in console!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_INTERRUPT_STOPBITS_1
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },

    /*
     * Different stop bits 2 length UART1 RX to TX Test cases
     */
    {
        TEST_ENABLE, 0U, ST_UART_TCT_HALT,
        NULL,
        " Set UART1 stop bits to 2 and all other parameter to default!!\r\n"
        " Press any alpha numeric key to continue: ",
        NULL, NULL, 0U, {0U}, {NULL}, {ST_UART_HCID_NONE}, {0U},
        {ST_UART_CCID_NONE}, {0U}, {ST_UART_CCID_NONE},
        PRINT_ENABLE, ST_TT_MISC, DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 22121U, ST_UART_TCT_RX_TO_TX,
        ":PDK-1038:PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1064:PDK-1081:PDK-219:PDK-1084:",
        "UART1_RX_TO_TX_Polled_Stopbits_2",
        "Send 1000 bytes through UART console and see the same echoed back in console!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_POLLED_STOPBITS_2
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 22122U, ST_UART_TCT_RX_TO_TX,
        ":PDK-1038:PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1065:PDK-220:PDK-1081:PDK-219:PDK-1084:",
        "UART1_RX_TO_TX_Interrupt_Stopbits_2",
        "Send 1000 bytes through UART console and see the same echoed back in console!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_INTERRUPT_STOPBITS_2
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },

    /*
     * Different Parity Even UART1 RX to TX Test cases
     */
    {
        TEST_ENABLE, 0U, ST_UART_TCT_HALT,
        NULL,
        " Set UART1 parity to Even and all other parameter to default!!\r\n"
        " Press any alpha numeric key to continue: ",
        NULL, NULL, 0U, {0U}, {NULL}, {ST_UART_HCID_NONE}, {0U},
        {ST_UART_CCID_NONE}, {0U}, {ST_UART_CCID_NONE},
        PRINT_ENABLE, ST_TT_MISC, DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 22211U, ST_UART_TCT_RX_TO_TX,
        ":PDK-1038:PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1064:PDK-1075:PDK-219:PDK-1078:",
        "UART1_RX_TO_TX_Polled_Parity_Even",
        "Send 1000 bytes through UART console and see the same echoed back in console!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_POLLED_PARITY_EVEN
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 22212U, ST_UART_TCT_RX_TO_TX,
        ":PDK-1038:PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1065:PDK-220:PDK-1075:PDK-219:PDK-1078:",
        "UART1_RX_TO_TX_Interrupt_Parity_Even",
        "Send 1000 bytes through UART console and see the same echoed back in console!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_INTERRUPT_PARITY_EVEN
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },

    /*
     * Different Parity Odd UART1 RX to TX Test cases
     */
    {
        TEST_ENABLE, 0U, ST_UART_TCT_HALT,
        NULL,
        " Set UART1 parity to Odd and all other parameter to default!!\r\n"
        " Press any alpha numeric key to continue: ",
        NULL, NULL, 0U, {0U}, {NULL}, {ST_UART_HCID_NONE}, {0U},
        {ST_UART_CCID_NONE}, {0U}, {ST_UART_CCID_NONE},
        PRINT_ENABLE, ST_TT_MISC, DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 22221U, ST_UART_TCT_RX_TO_TX,
        ":PDK-1038:PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1064:PDK-1075:PDK-219:PDK-1077:",
        "UART1_RX_TO_TX_Polled_Parity_Odd",
        "Send 1000 bytes through UART console and see the same echoed back in console!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_POLLED_PARITY_ODD
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 22222U, ST_UART_TCT_RX_TO_TX,
        ":PDK-1038:PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1065:PDK-220:PDK-1075:PDK-219:PDK-1077:",
        "UART1_RX_TO_TX_Interrupt_Parity_Odd",
        "Send 1000 bytes through UART console and see the same echoed back in console!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_INTERRUPT_PARITY_ODD
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },

    /*
     * Different Character Length 7 UART1 RX to TX Test cases
     */
    {
        TEST_ENABLE, 0U, ST_UART_TCT_HALT,
        NULL,
        " Set UART1 Character Length to 7 and all other parameter to default!!\r\n"
        " Press any alpha numeric key to continue: ",
        NULL, NULL, 0U, {0U}, {NULL}, {ST_UART_HCID_NONE}, {0U},
        {ST_UART_CCID_NONE}, {0U}, {ST_UART_CCID_NONE},
        PRINT_ENABLE, ST_TT_MISC, DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 22321U, ST_UART_TCT_RX_TO_TX,
        ":PDK-1038:PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1064:PDK-1085:PDK-219:PDK-1088:",
        "UART1_RX_TO_TX_Polled_CharLen_7",
        "Send 1000 bytes through UART console and see the same echoed back in console!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_POLLED_CHARLEN_7
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_FULL | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 22322U, ST_UART_TCT_RX_TO_TX,
        ":PDK-1038:PDK-1039:PDK-1063:PDK-1043:PDK-222:PDK-1065:PDK-220:PDK-1085:PDK-219:PDK-1088:",
        "UART1_RX_TO_TX_Interrupt_CharLen_7",
        "Send 1000 bytes through UART console and see the same echoed back in console!!", NULL,
        1U,
        {
            ST_INSTANCE_ID_UART1
        },
        {
            ST_INSTANCE_NAME_UART1
        },
        {
            ST_UART_HCID_INTERRUPT_CHARLEN_7
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        {
            1U
        },
        {
            ST_UART_CCID_DEFAULT
        },
        PRINT_ENABLE,
        (ST_TT_SANITY | ST_TT_FUNCTIONAL),
        DEF_SOC_ID,
    },
    {
        TEST_ENABLE, 0U, ST_UART_TCT_HALT,
        NULL,
        " Set UART1 baud rate back to 115200 and parameters as default!!\r\n"
        " Press any alpha numeric key to continue: ",
        NULL, NULL, 0U, {0U}, {NULL}, {ST_UART_HCID_NONE}, {0U},
        {ST_UART_CCID_NONE}, {0U}, {ST_UART_CCID_NONE},
        PRINT_ENABLE, ST_TT_MISC, DEF_SOC_ID,
    },
};

#endif /* #ifndef ST_UART_TEST_CASES_H_ */
