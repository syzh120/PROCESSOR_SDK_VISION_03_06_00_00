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
 *  \file st_eccParser.c
 *
 *  \brief User interface for ECC modules testing.
 *
 *  This file takes the input from the user specified test file and
 *  then initiates the tests on ECC accordingly.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <st_ecc.h>
#include <st_eccTestCases.h>
#include <ti/drv/stw_lld/uartconsole/uartStdio.h>
#include <ti/drv/stw_lld/examples/utility/stwutils_app.h>
#include <ti/drv/stw_lld/platform/platform.h>

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
 * \brief   Parse the testcase data
 *
 * \param   None.
 *
 * \return  None
 */
int32_t eccParser(void);

/**
 * \brief   Get the index of the testcase to run from st_eccTestcases.h.
 *
 * \param   testcaseId        Testcase Id to run.
 *
 * \return  None
 */
int32_t eccGetTestcaseIdx(uint32_t testcaseId);

/**
 * \brief   Print main menu.
 *
 * \param   None.
 *
 * \return  None
 */
void st_eccShowMainMenu(void);

/**
 * \brief   Print ECC system setings.
 *
 * \param   tcIdx Testcase index for which setting is to be print.
 *
 * \return  None
 */
void st_eccPrintSettings(uint32_t tcIdx);

/**
 * \brief   Print ECC testcases.
 *
 * \return  None
 */
void st_eccPrintTCs(void);

/**
 * \brief   Print ECC testcase details.
 *
 * \return  None
 */
void st_eccPrintTCDetails(uint32_t testId);

/**
 * \brief   Initialize ECC testcase details.
 *
 * \return  None
 */
void st_eccTCResultInit(void);

/**
 * \brief   Prints ECC Test Case Results.
 *
 * \return  None
 */
void st_eccPrintTCResults(void);

/**
 * \brief   Print messages on UART console.
 *
 * \param   None.
 *
 * \return  None
 */
void st_eccUARTConfig(void);

void eccRunTestCase(st_ECCTestcaseParams_t *testParams);
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
int32_t eccParser(void)
{
    uint32_t testcaseId;
    int32_t  testIp;
    uint32_t numTCPass, numTCFail, totalTCRun, done = 0U;
    int32_t  testcaseIdx, getCharRetVal /*, dspCore*/;
    char     option;
    st_ECCTestcaseParams_t *testParams;

    StwUtils_appWaitForSbl();

    st_eccUARTConfig();

#ifdef _TMS320C6X
    //UARTprintf("\nEnter 1 for DSP1/2 for DSP2:");
    //scanf("%d", &dspCore);
#endif
    st_eccTCResultInit();
    while (!done)
    {
        st_eccShowMainMenu();

        UARTprintf("\nEnter your choice: ");
        getCharRetVal = StwUtils_appGetCharTimeout(
            (int8_t *) &option,
            ECC_APP_UART_TIMEOUT_MSEC);
        if (STW_EFAIL == getCharRetVal)
        {
            /* Timeout - Enable Auto run Option */
            UARTprintf("\r\nUART read timeout %dms. Enable Auto Run !!",
                       ECC_APP_UART_TIMEOUT_MSEC);
            option = '4';
            done   = 1;
        }

        numTCPass  = 0U;
        numTCFail  = 0U;
        totalTCRun = 0U;
        switch (option)
        {
            case '1':
                UARTprintf("\nEnter testcase ID to run: ");
                getCharRetVal = StwUtils_appGetNumTimeout(
                    (int32_t *) &testIp,
                    ECC_APP_UART_TIMEOUT_MSEC);
                if (STW_EFAIL == getCharRetVal)
                {
                    /* Timeout - Enable Auto run Option */
                    UARTprintf("\r\nUART read timeout %dms. Enable Auto Run !!",
                               ECC_APP_UART_TIMEOUT_MSEC);
                    testcaseIdx = -1;
                }
                else
                {
                    testcaseIdx = eccGetTestcaseIdx(testIp);
                }
                if (testcaseIdx < 0)
                {
                    UARTprintf("Invalid test case Id.");
                }
                else if (TEST_ENABLE ==
                         gECCTestcaseParams[testcaseIdx].enableTest)
                {
                    testParams = &gECCTestcaseParams[testcaseIdx];
                    #ifdef __TI_ARM_V7M4__
                    if (IPU == testParams->cpuID)
                    {
                        totalTCRun++;
                        eccRunTestCase(testParams);
                        if (STW_SOK == testParams->testResult)
                        {
                            numTCPass++;
                        }
                        else
                        {
                            numTCFail++;
                        }
                    }
                    #elif defined (_TMS320C6X)
                    if ((DSP1 == testParams->cpuID) &&
                        (dspCore == 1U))
                    {
                        totalTCRun++;
                        eccRunTestCase(testParams);
                        if (STW_SOK == testParams->testResult)
                        {
                            numTCPass++;
                        }
                        else
                        {
                            numTCFail++;
                        }
                    }
                    if ((DSP2 == testParams->cpuID) &&
                        (dspCore == 2U))
                    {
                        totalTCRun++;
                        eccRunTestCase(testParams);
                        if (STW_SOK == testParams->testResult)
                        {
                            numTCPass++;
                        }
                        else
                        {
                            numTCFail++;
                        }
                    }
                #endif
                }
                UARTprintf("\nTotal Testcases run:%u/%u\n", totalTCRun,
                       ECC_NUM_TESTCASES);
                UARTprintf("Number of Testcases Passed:%u\n", numTCPass);
                UARTprintf("Number of Testcases Failed:%u\n", numTCFail);
                break;
            case '2':
                for (testcaseId = 1;
                     testcaseId <= ECC_NUM_TESTCASES;
                     testcaseId++)
                {
                    testcaseIdx = eccGetTestcaseIdx(testcaseId);
                    if (testcaseIdx < 0)
                    {
                        UARTprintf("Invalid test case Id.");
                    }
                    else if (TEST_ENABLE ==
                             gECCTestcaseParams[testcaseIdx].enableTest)
                    {
                        testParams = &gECCTestcaseParams[testcaseIdx];
                        if (ST_TT_SANITY ==
                            (testParams->testType & ST_TT_SANITY))
                        {
                            #ifdef __TI_ARM_V7M4__
                            if (IPU == testParams->cpuID)
                            {
                                totalTCRun++;
                                eccRunTestCase(testParams);
                                if (STW_SOK == testParams->testResult)
                                {
                                    numTCPass++;
                                }
                                else
                                {
                                    numTCFail++;
                                }
                            }
                            #elif defined (_TMS320C6X)
                            if ((DSP1 == testParams->cpuID) &&
                                (dspCore == 1U))
                            {
                                totalTCRun++;
                                eccRunTestCase(testParams);
                                if (STW_SOK == testParams->testResult)
                                {
                                    numTCPass++;
                                }
                                else
                                {
                                    numTCFail++;
                                }
                            }
                            if ((DSP2 == testParams->cpuID) &&
                                (dspCore == 2U))
                            {
                                totalTCRun++;
                                eccRunTestCase(testParams);
                                if (STW_SOK == testParams->testResult)
                                {
                                    numTCPass++;
                                }
                                else
                                {
                                    numTCFail++;
                                }
                            }
                            #endif
                        }
                    }
                }
                UARTprintf("\nTotal Testcases run:%u/%u\n", totalTCRun,
                       ECC_NUM_TESTCASES);
                UARTprintf("Number of Testcases Passed:%u\n", numTCPass);
                UARTprintf("Number of Testcases Failed:%u\n", numTCFail);
                break;
            case '3':
                for (testcaseId = 1;
                     testcaseId <= ECC_NUM_TESTCASES;
                     testcaseId++)
                {
                    testcaseIdx = eccGetTestcaseIdx(testcaseId);
                    if (testcaseIdx < 0)
                    {
                        UARTprintf("Invalid test case Id.\n");
                    }
                    else if (TEST_ENABLE ==
                             gECCTestcaseParams[testcaseIdx].enableTest)
                    {
                        testParams = &gECCTestcaseParams[testcaseIdx];
                        if (ST_TT_REGRESSION ==
                            (testParams->testType & ST_TT_REGRESSION))
                        {
                            totalTCRun++;
                            eccRunTestCase(testParams);
                            if (STW_SOK == testParams->testResult)
                            {
                                numTCPass++;
                            }
                            else
                            {
                                numTCFail--;
                            }
                        }
                    }
                }
                UARTprintf("\nTotal Testcases run:%d/%d\n", totalTCRun,
                       ECC_NUM_TESTCASES);
                UARTprintf("Number of Testcases Passed:%d\n", numTCPass);
                UARTprintf("Number of Testcases Failed:%d\n", numTCFail);
                break;
            case '4':
                for (testcaseId = 1;
                     testcaseId <= ECC_NUM_TESTCASES;
                     testcaseId++)
                {
                    testcaseIdx = eccGetTestcaseIdx(testcaseId);
                    if (testcaseIdx < 0)
                    {
                        UARTprintf("Invalid test case Id.\n");
                    }
                    else if (TEST_ENABLE ==
                             gECCTestcaseParams[testcaseIdx].enableTest)
                    {
                        testParams = &gECCTestcaseParams[testcaseIdx];
                        if (ST_TT_FULL ==
                            (testParams->testType & ST_TT_FULL))
                        {
                            totalTCRun++;
                            eccRunTestCase(testParams);
                            if (STW_SOK == testParams->testResult)
                            {
                                numTCPass++;
                            }
                            else
                            {
                                numTCFail--;
                            }
                        }
                    }
                }
                UARTprintf("\nTotal Testcases run:%d/%d\n", totalTCRun,
                       ECC_NUM_TESTCASES);
                UARTprintf("Number of Testcases Passed:%d\n", numTCPass);
                UARTprintf("Number of Testcases Failed:%d\n", numTCFail);
                st_eccPrintTCResults();
                break;
            case 'd':
                st_eccPrintTCs();
                break;
            case 't':
                UARTprintf("\nEnter testcase ID: ");
                getCharRetVal = StwUtils_appGetNumTimeout(
                    (int32_t *) &testIp,
                    ECC_APP_UART_TIMEOUT_MSEC);
                if (STW_EFAIL == getCharRetVal)
                {
                    /* Timeout - Enable Auto run Option */
                    UARTprintf("\r\nUART read timeout %dms. Enable Auto Run !!",
                               ECC_APP_UART_TIMEOUT_MSEC);
                    testIp = -1;
                }
                testcaseIdx = eccGetTestcaseIdx(testIp);
                if (testcaseIdx < 0)
                {
                    UARTprintf("Invalid test case Id.");
                }
                else
                {
                    st_eccPrintTCDetails(testcaseIdx);
                }
                break;
            case 'g':
                st_eccPrintTCResults();
                break;
            case 'q':
                UARTprintf("Exiting ECC UT.\n");
                done = 1;
                break;
        }
    }

    if(0U == numTCFail)
    {
        UARTprintf("\nAll Test-cases have PASSED.\n");
        StwUtils_appLogTestResult(STWUTILS_APP_TST_STATUS_PASS);
    }
    else
    {
        UARTprintf("\nSome of the Test-cases have FAILED.\n");
        StwUtils_appLogTestResult(STWUTILS_APP_TST_STATUS_FAIL);
    }

    return 0;
}

int32_t eccGetTestcaseIdx(uint32_t testcaseId)
{
    int32_t  testcaseIdx = -1;
    uint32_t testCnt;
    const st_ECCTestcaseParams_t *testParams;

    testParams = &gECCTestcaseParams[0u];
    for (testCnt = 0; testCnt < ECC_NUM_TESTCASES; testCnt++)
    {
        if (testParams[testCnt].testcaseId == testcaseId)
        {
            testcaseIdx = testCnt;
            break;
        }
    }
    return testcaseIdx;
}

void eccRunTestCase(st_ECCTestcaseParams_t *testParams)
{
    UARTprintf("\n|TEST START|:: %u ::\n", testParams->testcaseId);
    UARTprintf("|TEST PARAM|:: %s ::\n", testParams->testCaseName);
    UARTprintf("|SR|:: %s ::\n", testParams->reqId);

    UARTprintf("Testcase Settings:\n");
    UARTprintf("--------------------------------------------------------------\n");
    UARTprintf("Module                                              :ECC\n");

    if (TRUE != DiagLibEccTest_skipTest(testParams))
    {
        testParams->isRun = STW_SOK;
        testParams->testCaseFxnPtr(testParams);

        if (testParams->testResult == 0U)
            UARTprintf("|TEST RESULT|PASS|%u|\n", testParams->testcaseId);
        else
            UARTprintf("|TEST RESULT|FAIL|%u|\n", testParams->testcaseId);

        UARTprintf("|TEST INFO|:: %s ::\n", testParams->testCaseName);
        UARTprintf("|TEST END|:: %u ::\n", testParams->testcaseId);
    }
    else
    {
        testParams->isRun = STW_EFAIL;
        testParams->testResult = STW_SOK;
    }
}

void st_eccShowMainMenu(void)
{
    UARTprintf("\n=============\n");
    UARTprintf("ECC UT Select\n");
    UARTprintf("=============\n");
    st_eccPrintSettings(0);
    UARTprintf("\nECC UT main menu:\n");
    UARTprintf("1: Manual testing (select specific test case to run)\n");
    UARTprintf("2. Sanity testing.\n");
    UARTprintf("3: Regression testing.\n");
    UARTprintf("4: Full testing.\n");
    UARTprintf("5: Performance testing.\n");
    UARTprintf("d: Display test cases.\n");
    UARTprintf("t: Display test case Details.\n");
    UARTprintf("g: Generate test report.\n");
    UARTprintf("s: System Settings.\n");
    UARTprintf("q: Quit.\n");
}

void st_eccPrintSettings(uint32_t tcIdx)
{
    st_ECCTestcaseParams_t *testParams;

    testParams = &gECCTestcaseParams[tcIdx];
    if (tcIdx == 0U)
    {
        UARTprintf("Current System Settings:\n");
    }
    else
    {
        UARTprintf("Testcase Settings:\n");
    }
    UARTprintf("--------------------------------------------------------------\n");
    UARTprintf("Module                                              : ECC\n");
    UARTprintf("TestType                                            : %d\n",
           testParams->testType);
}

void st_eccPrintTCs(void)
{
    uint32_t loopCnt;
    int32_t  testcaseIdx;
    const st_ECCTestcaseParams_t *testParams;

    UARTprintf("ECC Testcase:\n");
    UARTprintf("--------------------------------------------------------------\n");
    UARTprintf("TC Id\tTC name\n");
    UARTprintf("--------------------------------------------------------------\n");
    for (loopCnt = 1; loopCnt <= ECC_NUM_TESTCASES; loopCnt++)
    {
        testcaseIdx = eccGetTestcaseIdx(loopCnt);
        if (0 > testcaseIdx)
        {
            UARTprintf("Invalid test case Id.");
        }
        else
        {
            testParams = &gECCTestcaseParams[testcaseIdx];
            UARTprintf("%d\t%s\n", testParams->testcaseId, testParams->testCaseName);
        }
    }
    UARTprintf("--------------------------------------------------------------\n");
}

void st_eccPrintTCDetails(uint32_t testId)
{
    const st_ECCTestcaseParams_t *testParams;

    testParams = &gECCTestcaseParams[testId];
    UARTprintf("Testcase Id : %d\n", testParams->testcaseId);
    UARTprintf("Testcase Name : %s", testParams->testCaseName);
    UARTprintf("\nTestcase Enabled(0-Disabled/1-Enabled) : %d",
           testParams->enableTest);
    UARTprintf("\nTestcase Req. Id : %s", testParams->reqId);
    UARTprintf("\nTestcase User Info. : %s", testParams->userInfo);
    UARTprintf("\nTestcase Disable Reason : %s", testParams->disableReason);
    UARTprintf("\nTestcase CPU ID : %d", testParams->cpuID);
    UARTprintf("\nTestcase Type : %d", testParams->testType);
    UARTprintf("\nTestcase Print Enable(0-Disabled/1-Enabled) : %d\n",
           testParams->printEnable);
}

void st_eccTCResultInit(void)
{
    uint32_t loopCnt;
    int32_t  testcaseIdx;
    st_ECCTestcaseParams_t *testParams;

    for (loopCnt = 1; loopCnt <= ECC_NUM_TESTCASES; loopCnt++)
    {
        testcaseIdx = eccGetTestcaseIdx(loopCnt);
        if (testcaseIdx < 0)
        {
            /* Invalid test case Id */
        }
        else
        {
            testParams             = &gECCTestcaseParams[testcaseIdx];
            testParams->isRun      = STW_EFAIL;
            testParams->testResult = STW_EFAIL;
        }
    }
}

void st_eccPrintTCResults(void)
{
    uint32_t loopCnt;
    int32_t  testcaseIdx;
    st_ECCTestcaseParams_t *testParams;
    char    *testResult, *testEnable, *testType, *adequacy, *passFailCriteria;
    char    *disableReason;

    UARTprintf(
        "Sr No.\t        ID\t         Description\t\t                         Status\t    Auto Run\r\n");
    UARTprintf(
        "-----------------------------------------------------------------------------------------------------------\r\n");
    for (loopCnt = 1; loopCnt <= ECC_NUM_TESTCASES; loopCnt++)
    {
        testcaseIdx = eccGetTestcaseIdx(loopCnt);
        if (testcaseIdx < 0)
        {
            // UARTprintf("Invalid test case Id.");
        }
        else
        {
            testParams = &gECCTestcaseParams[testcaseIdx];
            if (STW_SOK == testParams->testResult)
            {
                testResult = "PASS";
            }
            else if (STW_SOK == testParams->isRun)
            {
                testResult = "FAIL";
            }
            else
            {
                testResult = "NRQ";
            }
            if (TEST_DISABLE == testParams->enableTest)
            {
                testEnable = "Disabled";
            }
            else
            {
                testEnable = "Enabled";
            }
            UARTprintf(
                "%d\t        %d\t         %s\t                         %s\t    %s\r\n",
                loopCnt,
                testcaseIdx, testParams->testCaseName, testResult,
                testEnable);
        }
    }

    UARTprintf(
        "S.No;ID;Requirement Mapping;Description;Pass Fail Criteria;IR;Category;Test Adequacy;Test Result;\r\n");
    UARTprintf(
        "---------------------------------------------------------------------------\r\n");
    for (loopCnt = 1; loopCnt <= ECC_NUM_TESTCASES; loopCnt++)
    {
        testcaseIdx = eccGetTestcaseIdx(loopCnt);
        if (testcaseIdx < 0)
        {
            // UARTprintf("Invalid test case Id.");
        }
        else
        {
            testParams = &gECCTestcaseParams[testcaseIdx];
            if (STW_SOK == testParams->testResult)
            {
                testResult = "PASS";
            }
            else if (STW_SOK == testParams->isRun)
            {
                testResult = "FAIL";
            }
            else
            {
                testResult = "NRQ";
            }
            if (TEST_DISABLE == testParams->enableTest)
            {
                testEnable = "Disabled";
                testResult = "BLK";
            }
            else
            {
                testEnable = "Enabled";
            }
            if (testParams->testType & ST_TT_SANITY)
            {
                testType = "Sanity";
                adequacy = "Functional";
            }
            else if (testParams->testType & ST_TT_REGRESSION)
            {
                testType = "Regression";
                adequacy = "Functional";
            }
            else if (testParams->testType & ST_TT_STRESS)
            {
                testType = "Stress";
                adequacy = "Stress";
            }
            else if (testParams->testType & ST_TT_NEGATIVE)
            {
                testType = "Negative";
                adequacy = "Negative";
            }
            else if (testParams->testType & ST_TT_PERFORMANCE)
            {
                testType = "Performance";
                adequacy = "Performance";
            }
            else if (testParams->testType & ST_TT_MISC)
            {
                testType = "Misc";
                adequacy = "Misc";
            }
            else
            {
                testType = "";
                adequacy = "";
            }

            passFailCriteria = testParams->passFailCriteria;
            if (NULL == passFailCriteria)
            {
                passFailCriteria = "";
            }

            disableReason = testParams->disableReason;
            if (NULL == disableReason)
            {
                disableReason = "";
            }

            UARTprintf("%d;STW_ECC_TC%05d;%s;%s;%s;%s;%s;%s;%s;\r\n", loopCnt,
                   testcaseIdx, testParams->reqId, testParams->testCaseName,
                   passFailCriteria, disableReason, testType, adequacy,
                   testResult);
        }
    }
}

void st_eccUARTConfig(void)
{
    PlatformUartConsoleSetPinMux();
    UARTStdioInit();
}
