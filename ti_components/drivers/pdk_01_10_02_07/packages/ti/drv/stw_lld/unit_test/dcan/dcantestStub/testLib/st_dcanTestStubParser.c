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
 *  \file st_dcanTestStubParser.c
 *
 *  \brief User interface for DCAN driver testing.
 *
 *  This file takes the input from the user specified test file and
 *  then initiates the tests on DCAN driver accordingly.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdio.h>
#include <st_dcanTestStub.h>
#include <st_dcanTestStubTestCases.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   Fetch testcase data and run the testcase.
 *
 * \return  None
 */
void st_dcanTestStubRunTestcase();

/**
 * \brief   Fetch testcase data and run the testcase. Present in st_dcanTxTest.c
 *
 * \param   testParams        structure to details of testcase to run.
 *
 * \return  None
 */
extern int32_t st_dcanTestStubTxTest_main(st_DCANTestcaseParams_t *testParams);

/**
 * \brief   Fetch testcase data and run the testcase. Present in st_dcanRxTest.c
 *
 * \param   testParams        structure to details of testcase to run.
 *
 * \return  None
 */
extern int32_t st_dcanTestStubRxTest_main(st_DCANTestcaseParams_t *testParams);

/**
 * \brief   Print main menu.
 *
 * \param   None.
 *
 * \return  None
 */
void st_dcanTestStubShowMainMenu(void);
void st_dcanTestStubShowSubMainMenu(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
uint32_t gTestType;
uint32_t gTestCaseType;
uint32_t gNumTests;
uint32_t gPerfTest = 0;
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
int32_t st_dcanTestStubParser(void)
{
    char     option, subOption;
    uint32_t done = 0U;
#if defined (SOC_TDA2XX)
    uint32_t siliconRev;
#endif

    PlatformUartConsoleSetPinMux();
    UARTStdioInit();

#if defined (SOC_TDA2XX)
    siliconRev = PlatformGetSiliconRev();
    if (0U == siliconRev)
    {
        UARTPuts(
            "\nDCAN TestStub is not supported for Tda2xx PG1.0 Silicon", -1);
        return 0;
    }
#endif

#if defined (SOC_TDA2PX)
    PlatformDCAN1PadConfig();
#endif

    while (!done)
    {
        st_dcanTestStubShowMainMenu();
        UARTprintf("\nEnter your choice: ");
        UARTGets(&option, 1);
        switch (option)
        {
            case '1':
                gTestType = ST_TT_SANITY;
                break;
            case '2':
                gTestType = ST_TT_REGRESSION;
                break;
            case '3':
                gTestType = ST_TT_FULL;
                break;
            case 'q':
                UARTprintf("\nExiting DCAN TestStub.\n");
                done = 1;
                break;
        }
        if (done == 1)
            continue;

        st_dcanTestStubShowSubMainMenu();
        UARTprintf("\nEnter your choice: ");
        UARTGets(&subOption, 1);
        switch (subOption)
        {
            case '1':
                gTestCaseType = ST_TCT_DCAN_TX;
                gNumTests     = DCAN_NUM_TESTCASES;
                gPerfTest     = 0;
                break;
            case '2':
                gTestCaseType = ST_TCT_DCAN_RX;
                gNumTests     = DCAN_NUM_TESTCASES;
                gPerfTest     = 0;
                break;
            case '3':
                gTestCaseType = ST_TCT_DCAN_RX;
                gNumTests     = 1;
                break;
        }

        st_dcanTestStubRunTestcase();
    }
    return 0;
}

void st_dcanTestStubRunTestcase()
{
    int32_t retVal      = STW_SOK;
    int32_t testcaseIdx = 0;
    st_DCANTestcaseParams_t *testParams;

    if (gTestCaseType == ST_TCT_DCAN_TX)
    {
        for (testcaseIdx = 0; testcaseIdx < gNumTests; testcaseIdx++)
        {
            UARTprintf(
                "\n======================RUNNING===========================\n");
            testParams = &gDCANTxTestcaseParams[testcaseIdx];
            if (testParams->testType & gTestType)
            {
                retVal = st_dcanTestStubTxTest_main(testParams);
                sampleDelay(700);
            }
            if (retVal == STW_SOK)
            {
                UARTprintf("|TEST RESULT|PASS|%u|\n", testParams->testcaseId);
            }
            else
            {
                UARTprintf("|TEST RESULT|FAIL|%u|\n", testParams->testcaseId);
            }

            UARTprintf(
                "\n======================FINISHED==========================\n");
        }
    }
    if (gTestCaseType == ST_TCT_DCAN_RX)
    {
        for (testcaseIdx = 0; testcaseIdx < gNumTests; testcaseIdx++)
        {
            UARTprintf(
                "\n======================RUNNING===========================\n");
            testParams = &gDCANRxTestcaseParams[testcaseIdx];
            if (gPerfTest == 1)
            {
                testParams->numMsg = 10000;
            }
            if (testParams->testType & gTestType)
            {
                retVal = st_dcanTestStubRxTest_main(testParams);
            }
            if (retVal == STW_SOK)
            {
                UARTprintf("|TEST RESULT|PASS|%u|\n", testParams->testcaseId);
            }
            else
            {
                UARTprintf("|TEST RESULT|FAIL|%u|\n", testParams->testcaseId);
            }

            UARTprintf(
                "\n======================FINISHED==========================\n");
        }
    }
}

void st_dcanTestStubShowMainMenu(void)
{
    UARTprintf("\n====================\n");
    UARTprintf("DCAN Test Stub Select\n");
    UARTprintf("=======================\n");
    UARTprintf("\nDCAN Test Stub menu:\n");
    UARTprintf("1. Sanity testing.\n");
    UARTprintf("2: Regression testing.\n");
    UARTprintf("3: Full testing.\n");
    UARTprintf("q: Quit.\n");
}

void st_dcanTestStubShowSubMainMenu(void)
{
    UARTprintf("\n====================\n");
    UARTprintf("DCAN Test Stub TCT Select\n");
    UARTprintf("=======================\n");
    UARTprintf("\nDCAN Test Stub menu:\n");
    UARTprintf("1. TX Test.\n");
    UARTprintf("2: RX Test.\n");
    UARTprintf("3. Performance Test.\n");
}

