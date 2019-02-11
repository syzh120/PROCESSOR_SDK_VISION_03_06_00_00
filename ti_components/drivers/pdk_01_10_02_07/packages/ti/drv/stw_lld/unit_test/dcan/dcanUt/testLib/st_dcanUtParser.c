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
 *  \file st_dcanUtParser.c
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
#include <st_dcanUt.h>
#include <st_dcanUtTestCases.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
uint32_t gTestCaseType;
extern uint32_t        gtraceMask;
/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 * \brief   Get the index of the testcase to run from st_dcanTestcases.h.
 *
 * \param   testcaseId        Testcase Id to run.
 *
 * \return  None
 */
int32_t dcanGetTestcaseIdx(uint32_t testcaseId);

/**
 * \brief   Fetch testcase data and run the testcase.
 *
 * \param   testParams        structure to details of testcase to run.
 *
 * \return  None
 */
void dcanRunTestcase(st_DCANTestcaseParams_t *testParams);

/**
 * \brief   Print main menu.
 *
 * \param   None.
 *
 * \return  None
 */
void st_dcanShowMainMenu(void);
void st_dcanShowSubMainMenu(void);
static void st_dcanDisplayTestInfo();
static void st_dcanSetDefaultCfg(void);
static void st_dcanGenerateTestReports(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/*NONE*/

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
int32_t st_dcanParser(void)
{
    uint32_t                 testcaseId, retVal = STW_SOK;
    uint32_t                 numTCPass, numTCFail, totalTCRun, done = 0U;
    int32_t                  testcaseIdx, startTcIdx = 0, numTests = 0;
    char                     option, subOption;
    st_DCANTestcaseParams_t *testParams = NULL;
    platformInitParams_t     platInitPrms;
    platformSocId_t          platformSocId;
#if defined (SOC_TDA2XX)
    uint32_t                 siliconRev;
#endif

    PlatformUartConsoleSetPinMux();
    UARTStdioInit();

#if defined (SOC_TDA2XX)
    siliconRev = PlatformGetSiliconRev();
    if (0U == siliconRev)
    {
        UARTPuts(
            "\nDCAN Ut is not supported for Tda2xx PG1.0 Silicon", -1);
        return 0;
    }
#endif

    PLATFORMInitParams_init(&platInitPrms);
    retVal = PLATFORMInit(&platInitPrms);
    if (STW_SOK != retVal)
    {
        UARTprintf("\nError: Platform Init failed!!");
    }

#if defined (SOC_TDA2PX)
    PlatformDCAN1PadConfig();
#endif

    st_dcanSetDefaultCfg();

    platformSocId = PLATFORMGetSocId();

    while (!done)
    {
        st_dcanShowMainMenu();
        UARTprintf("\nEnter your choice: ");
        UARTGets(&option, 1);
        if ((option != 'q') && (option != 'g') && (option != 'd'))
        {
            st_dcanShowSubMainMenu();
            UARTprintf("\nEnter your choice: ");
            UARTGets(&subOption, 1);
            switch (subOption)
            {
                case '1':
                    gTestCaseType = ST_TCT_DCAN_TX;
                    startTcIdx    = 1U;
                    numTests      = DCAN_NUM_TX_TESTCASES;
                    break;
                case '2':
                    gTestCaseType = ST_TCT_DCAN_RX;
                    startTcIdx    = 100U;
                    numTests      = DCAN_NUM_RX_TESTCASES;
                    break;
                case '3':
                    gTestCaseType = ST_TCT_DCAN_TEST_MODE;
                    startTcIdx    = 200U;
                    numTests      = DCAN_NUM_TEST_MODE_TESTCASES;
                    break;
                case '4':
                    gTestCaseType = ST_TCT_DCAN_ERR;
                    startTcIdx    = 300U;
                    numTests      = DCAN_NUM_ERR_TESTCASES;
                    break;
                case '5':
                    gTestCaseType = ST_TCT_DCAN_PERF_TX;
                    startTcIdx    = 1U;
                    numTests      = 1;
                    break;
            }
        }
        numTCPass  = 0U;
        numTCFail  = 0U;
        totalTCRun = 0U;
        switch (option)
        {
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
                for (testcaseId = startTcIdx;
                     testcaseId < (startTcIdx + numTests);
                     testcaseId++)
                {
                    testcaseIdx = dcanGetTestcaseIdx(testcaseId);
                    if (testcaseIdx < 0)
                    {
                        UARTprintf("Invalid test case Id.");
                    }
                    else
                    {
                        if (gTestCaseType == ST_TCT_DCAN_TX)
                        {
                            testParams = &gDCANTxTestcaseParams[testcaseIdx];
                        }
                        if (gTestCaseType == ST_TCT_DCAN_RX)
                        {
                            testParams = &gDCANRxTestcaseParams[testcaseIdx];
                        }
                        if (gTestCaseType == ST_TCT_DCAN_TEST_MODE)
                        {
                            testParams =
                                &gDCANTestModeTestcaseParams[testcaseIdx];
                        }
                        if (gTestCaseType == ST_TCT_DCAN_ERR)
                        {
                            testParams =
                                &gDCANErrTestcaseParams[testcaseIdx];
                        }
                        if (gTestCaseType == ST_TCT_DCAN_PERF_TX)
                        {
                            testParams =
                                &gDCANTxTestcaseParams[testcaseIdx];
                        }

                        GT_assert(gtraceMask, (testParams != NULL));
                        if ((((ST_TT_SANITY ==
                               (testParams->testType & ST_TT_SANITY))
                              && ('1' == option)) ||
                             ((ST_TT_REGRESSION ==
                               (testParams->testType & ST_TT_REGRESSION)) &&
                              ('2' == option)) ||
                             ((ST_TT_FULL == (testParams->testType & ST_TT_FULL))
                              && ('3' == option)) ||
                             ((ST_TT_FULL == (testParams->testType & ST_TT_FULL))
                              && ('4' == option))) &&
                            (testParams->platformSocId & platformSocId))
                        {
                            totalTCRun++;
                            dcanRunTestcase(testParams);
                            if (STW_SOK == testParams->testResult)
                            {
                                numTCPass++;
                            }
                            else
                            {
                                numTCFail++;
                            }
                        }
                    }
                }
                if (gTestCaseType == ST_TCT_DCAN_TX)
                {
                    UARTprintf("\nTotal Testcases run:%u/%u\n",
                               totalTCRun, DCAN_NUM_TX_TESTCASES);
                }
                if (gTestCaseType == ST_TCT_DCAN_RX)
                {
                    UARTprintf("\nTotal Testcases run:%u/%u\n",
                               totalTCRun, DCAN_NUM_RX_TESTCASES);
                }
                if (gTestCaseType == ST_TCT_DCAN_TEST_MODE)
                {
                    UARTprintf("\nTotal Testcases run:%u/%u\n",
                               totalTCRun, DCAN_NUM_TEST_MODE_TESTCASES);
                }
                if (gTestCaseType == ST_TCT_DCAN_ERR)
                {
                    UARTprintf("\nTotal Testcases run:%u/%u\n",
                               totalTCRun, DCAN_NUM_ERR_TESTCASES);
                }
                if (gTestCaseType == ST_TCT_DCAN_PERF_TX)
                {
                    UARTprintf("\nTotal Testcases run:%u/%u\n",
                               totalTCRun, 1U);
                }
                UARTprintf("Number of Testcases Passed:%u\n", numTCPass);
                UARTprintf("Number of Testcases Failed:%u\n", numTCFail);
                break;

            case 'd':
                /* Display test info */
                st_dcanDisplayTestInfo();
                break;

            case 'g':
                /* Generate test report */
                st_dcanGenerateTestReports();
                break;

            case 'q':
                UARTprintf("\nExiting DCAN UT.\n");
                done = 1;
                break;
        }
    }

    retVal = PLATFORMDeInit(NULL);
    if (STW_SOK != retVal)
    {
        UARTprintf("\nError: STW Platform De-Init failed!!");
    }

    return 0;
}

int32_t dcanGetTestcaseIdx(uint32_t testcaseId)
{
    int32_t  testcaseIdx = -1;
    uint32_t testCnt;
    uint32_t numOfTestCases = 0;
    const st_DCANTestcaseParams_t *testParams;

    if (gTestCaseType == ST_TCT_DCAN_TX)
    {
        testParams = &gDCANTxTestcaseParams[0u];
        numOfTestCases = DCAN_NUM_TX_TESTCASES;
    }
    if (gTestCaseType == ST_TCT_DCAN_RX)
    {
        testParams = &gDCANRxTestcaseParams[0u];
        numOfTestCases = DCAN_NUM_RX_TESTCASES;
    }
    if (gTestCaseType == ST_TCT_DCAN_TEST_MODE)
    {
        testParams = &gDCANTestModeTestcaseParams[0u];
        numOfTestCases = DCAN_NUM_TEST_MODE_TESTCASES;
    }
    if (gTestCaseType == ST_TCT_DCAN_ERR)
    {
        testParams = &gDCANErrTestcaseParams[0u];
        numOfTestCases = DCAN_NUM_ERR_TESTCASES;
    }
    if (gTestCaseType == ST_TCT_DCAN_PERF_TX)
    {
        testParams = &gDCANTxTestcaseParams[0u];
        numOfTestCases = DCAN_NUM_TX_TESTCASES;
    }

    GT_assert(gtraceMask, (testParams != NULL));
    for (testCnt = 0; testCnt < numOfTestCases; testCnt++)
    {
        if (testParams[testCnt].testcaseId == testcaseId)
        {
            testcaseIdx = testCnt;
            break;
        }
    }
    return testcaseIdx;
}

void dcanRunTestcase(st_DCANTestcaseParams_t *testParams)
{
    int32_t retVal = STW_SOK;
    UARTprintf("\n|TEST START|:: %u ::\n", testParams->testcaseId);
    UARTprintf("|TEST PARAM|:: %s ::\n", testParams->testCaseName);
    UARTprintf("|SR|:: %s ::\n", testParams->reqId);
    UARTprintf("======================RUNNING===========================\n");
    if ((gTestCaseType == ST_TCT_DCAN_TX) ||
        (gTestCaseType == ST_TCT_DCAN_PERF_TX))
    {
        if (gTestCaseType == ST_TCT_DCAN_PERF_TX)
        {
            testParams->isPerfTest = TRUE;
            testParams->numMsg     = 10000;
        }
        else
        {
            testParams->isPerfTest = FALSE;
        }
        retVal = st_dcanTxTest_main(testParams);
        sampleDelay(700);
    }
    if (gTestCaseType == ST_TCT_DCAN_RX)
    {
        retVal = st_dcanRxTest_main(testParams);
    }
    if (gTestCaseType == ST_TCT_DCAN_TEST_MODE)
    {
        retVal = st_dcanTestModeTest_main(testParams);
    }
    if (gTestCaseType == ST_TCT_DCAN_ERR)
    {
        retVal = st_dcanErrTest_main(testParams);
    }

    UARTprintf("\n======================FINISHED==========================\n");

    if (retVal == STW_SOK)
    {
        if (testParams->testResult == 0U)
            UARTprintf("|TEST RESULT|PASS|%u|\n", testParams->testcaseId);
        else
            UARTprintf("|TEST RESULT|FAIL|%u|\n", testParams->testcaseId);
    }
    else
    {
        UARTprintf("|TEST RESULT|FAIL|%u|\n", testParams->testcaseId);
    }
    UARTprintf("|TEST INFO|:: %s ::\n", testParams->testCaseName);
    UARTprintf("|TEST END|:: %u ::\n", testParams->testcaseId);
}

void st_dcanShowMainMenu(void)
{
    UARTprintf("\n=============\n");
    UARTprintf("DCAN UT Select\n");
    UARTprintf("=============\n");
    UARTprintf("\nDCAN UT main menu:\n");
    UARTprintf("1. Sanity testing.\n");
    UARTprintf("2: Regression testing.\n");
    UARTprintf("3: Full testing.\n");
    UARTprintf("d: Display test cases.\n");
    UARTprintf("g: Generate test report.\n");
    UARTprintf("q: Quit.\n");
}

void st_dcanShowSubMainMenu(void)
{
    UARTprintf("\n=============\n");
    UARTprintf("DCAN UT TCT Select\n");
    UARTprintf("=============\n");
    UARTprintf("\nDCAN UT TCT main menu:\n");
    UARTprintf("1: TX Test\n");
    UARTprintf("2. RX Test\n");
    UARTprintf("3. Test Mode\n");
    UARTprintf("4. Error Test\n");
    UARTprintf("5: Performance for TX Test\n");
}

/**
 *  st_dcanGenerateTestReports
 */
static void st_dcanGenerateTestReports(void)
{
    UInt32                   sCnt, testCnt, testCaseTypeCnt = 4, numTests;
    char                    *runStatus, *category, *adequacy;
    st_DCANTestcaseParams_t *testPrms;
    platformSocId_t          platformSocId;

    platformSocId = PLATFORMGetSocId();

    sCnt = 1;

    UARTprintf(" \r\n");
    UARTprintf(
        "S.No;ID;Requirement Mapping;Description;IR;Category;Test Adequacy;Test Result;\r\n");
    UARTprintf(
        "-------------------------------------------------------------------------------\r\n");
    while (testCaseTypeCnt--)
    {
        if (testCaseTypeCnt == 0)
        {
            numTests = DCAN_NUM_ERR_TESTCASES;
        }
        else if (testCaseTypeCnt == 1)
        {
            numTests = DCAN_NUM_TEST_MODE_TESTCASES;
        }
        else if (testCaseTypeCnt == 2)
        {
            numTests = DCAN_NUM_RX_TESTCASES;
        }
        else
        {
            numTests = DCAN_NUM_TX_TESTCASES;
        }
        for (testCnt = 0; testCnt < numTests; testCnt++)
        {
            if (testCaseTypeCnt == 3)
            {
                testPrms = &gDCANTxTestcaseParams[testCnt];
            }
            else if (testCaseTypeCnt == 2)
            {
                testPrms = &gDCANRxTestcaseParams[testCnt];
            }
            else if (testCaseTypeCnt == 1)
            {
                testPrms = &gDCANTestModeTestcaseParams[testCnt];
            }
            else
            {
                testPrms = &gDCANErrTestcaseParams[testCnt];
            }
            runStatus = "NRY";
            if (FALSE == testPrms->isRun)
            {
                if (!(platformSocId & testPrms->platformSocId))
                {
                    runStatus = "NA";
                }
                else if (FALSE == testPrms->enableTest)
                {
                    runStatus = "BLK";
                }
            }
            else
            {
                if (STW_SOK == testPrms->testResult)
                {
                    runStatus = "PASS";
                }
                else
                {
                    runStatus = "FAIL";
                }
            }

            if (testPrms->testType & ST_TT_SANITY)
            {
                category = "Sanity";
            }
            else if (testPrms->testType & ST_TT_REGRESSION)
            {
                category = "Regression";
            }
            else
            {
                category = "Full";
            }

            if (testPrms->testType & ST_TT_STRESS)
            {
                adequacy = "Stress";
            }
            else if (testPrms->testType & ST_TT_NEGATIVE)
            {
                adequacy = "Negative";
            }
            else if (testPrms->testType & ST_TT_PERFORMANCE)
            {
                adequacy = "Performance";
            }
            else if (testPrms->testType & ST_TT_MISC)
            {
                adequacy = "Misc";
            }
            else
            {
                adequacy = "Functional";
            }

            UARTprintf("%d;ST_DCAN_TC%d;%s;%s;%s;%s;%s;%s",
                       sCnt,
                       testPrms->testcaseId,
                       testPrms->reqId,
                       testPrms->testCaseName,
                       testPrms->disableReason,
                       category,
                       adequacy,
                       runStatus);
            UARTprintf("\r\n");
            sCnt++;
        }
    }
    return;
}

static void st_dcanSetDefaultCfg(void)
{
    UInt32 testCnt, testCaseTypeCnt = 4, numTests;
    st_DCANTestcaseParams_t *testPrms;

    /* Mark all test cases as not run and set result to PASS */
    while (testCaseTypeCnt--)
    {
        if (testCaseTypeCnt == 0)
        {
            numTests = DCAN_NUM_ERR_TESTCASES;
        }
        else if (testCaseTypeCnt == 1)
        {
            numTests = DCAN_NUM_TEST_MODE_TESTCASES;
        }
        else if (testCaseTypeCnt == 2)
        {
            numTests = DCAN_NUM_RX_TESTCASES;
        }
        else
        {
            numTests = DCAN_NUM_TX_TESTCASES;
        }
        for (testCnt = 0; testCnt < numTests; testCnt++)
        {
            if (testCaseTypeCnt == 3)
            {
                testPrms = &gDCANTxTestcaseParams[testCnt];
            }
            else if (testCaseTypeCnt == 2)
            {
                testPrms = &gDCANRxTestcaseParams[testCnt];
            }
            else if (testCaseTypeCnt == 1)
            {
                testPrms = &gDCANTestModeTestcaseParams[testCnt];
            }
            else
            {
                testPrms = &gDCANErrTestcaseParams[testCnt];
            }
            testPrms->isRun      = FALSE;
            testPrms->testResult = STW_SOK;
        }
    }
    return;
}

/**
 *  st_dcanDisplayTestInfo
 */
static void st_dcanDisplayTestInfo()
{
    UInt32                   sCnt, testCnt, testCaseTypeCnt = 4, numTests;
    char                    *runStatus;
    st_DCANTestcaseParams_t *testPrms;
    static char             *enableDisableName[] = {"Disabled", "Enabled"};
    platformSocId_t          platformSocId;

    platformSocId = PLATFORMGetSocId();

    /* Display test info */
    sCnt = 1;
    UARTprintf("\r\n");
    UARTprintf(
        "S.No    ID              Description                                                    Status    Auto Run\r\n");
    UARTprintf(
        "----------------------------------------------------------------------------------------------------------\r\n");

    while (testCaseTypeCnt--)
    {
        if (testCaseTypeCnt == 0)
        {
            numTests = DCAN_NUM_ERR_TESTCASES;
        }
        else if (testCaseTypeCnt == 1)
        {
            numTests = DCAN_NUM_TEST_MODE_TESTCASES;
        }
        else if (testCaseTypeCnt == 2)
        {
            numTests = DCAN_NUM_RX_TESTCASES;
        }
        else
        {
            numTests = DCAN_NUM_TX_TESTCASES;
        }
        for (testCnt = 0; testCnt < numTests; testCnt++)
        {
            if (testCaseTypeCnt == 3)
            {
                testPrms = &gDCANTxTestcaseParams[testCnt];
            }
            else if (testCaseTypeCnt == 2)
            {
                testPrms = &gDCANRxTestcaseParams[testCnt];
            }
            else if (testCaseTypeCnt == 1)
            {
                testPrms = &gDCANTestModeTestcaseParams[testCnt];
            }
            else
            {
                testPrms = &gDCANErrTestcaseParams[testCnt];
            }
            runStatus = "NRY";

            if (FALSE == testPrms->isRun)
            {
                if (!(platformSocId & testPrms->platformSocId))
                {
                    runStatus = "NA";
                }
                else if (FALSE == testPrms->enableTest)
                {
                    runStatus = "BLK";
                }
            }
            else
            {
                if (STW_SOK == testPrms->testResult)
                {
                    runStatus = "PASS";
                }
                else
                {
                    runStatus = "FAIL";
                }
            }

            UARTprintf(" %d  ST_DCAN_TC%d  %s  %s  %s",
                       sCnt,
                       testPrms->testcaseId,
                       testPrms->testCaseName,
                       runStatus,
                       enableDisableName[testPrms->enableTest]);
            UARTprintf("\r\n");
            sCnt++;
        }
    }
    return;
}

