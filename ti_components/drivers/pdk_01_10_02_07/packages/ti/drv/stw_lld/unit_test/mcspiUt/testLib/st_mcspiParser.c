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
 *  \file st_mcspiParser.c
 *
 *  \brief User interface for McSPI modules testing.
 *
 *  This file takes the input from the user specified test file and
 *  then initiates the tests on McSPI accordingly.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <st_mcspi.h>
#include <st_mcspiTestCases.h>

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
int32_t mcspiParser(void);

/**
 * \brief   Get the index of the testcase to run from st_mcspiTestcases.h.
 *
 * \param   testcaseId        Testcase Id to run.
 *
 * \return  None
 */
int32_t mcspiGetTestcaseIdx(uint32_t testcaseId);

/**
 * \brief   Print main menu.
 *
 * \param   None.
 *
 * \return  None
 */
void st_mcspiShowMainMenu(void);

/**
 * \brief   Print McSPI system setings.
 *
 * \param   tcIdx Testcase index for which setting is to be print.
 *
 * \return  None
 */
void st_mcspiPrintSettings(uint32_t tcIdx);

/**
 * \brief   Print McSPI testcases.
 *
 * \return  None
 */
void st_mcspiPrintTCs(void);

/**
 * \brief   Print McSPI testcase details.
 *
 * \return  None
 */
void st_mcspiPrintTCDetails(uint32_t testId);

/**
 * \brief   Initialize McSPI testcase details.
 *
 * \return  None
 */
void st_mcspiTCResultInit(void);

/**
 * \brief   Prints McSPI Test Case Results.
 *
 * \return  None
 */
void st_mcspiPrintTCResults(void);

void mcspiRunTestCase(st_MCSPITestcaseParams_t *testParams);
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
int32_t mcspiParser(void)
{
    uint32_t testcaseId, testIp;
    uint32_t numTCPass, numTCFail, totalTCRun, done = 0U;
    int32_t  testcaseIdx /*, dspCore*/;
    char     scnStr[MAX_ARG_LEN], option;
    st_MCSPITestcaseParams_t *testParams;

    #ifdef _TMS320C6X
    printf("\nEnter 1 for DSP1/2 for DSP2:");
    scanf("%d", &dspCore);
    #endif
    st_mcspiTCResultInit();
    while (!done)
    {
        st_mcspiShowMainMenu();
        printf("\nEnter your choice: ");
        scanf("%s", scnStr);
        option     = scnStr[0];
        numTCPass  = 0U;
        numTCFail  = 0U;
        totalTCRun = 0U;
        switch (option)
        {
            case '1':
                printf("\nEnter testcase ID to run: ");
                scanf("%d", &testIp);
                testcaseIdx = mcspiGetTestcaseIdx(testIp);
                if (testcaseIdx < 0)
                {
                    printf("Invalid test case Id.");
                }
                else if (TEST_ENABLE ==
                         gMCSPITestcaseParams[testcaseIdx].enableTest)
                {
                    testParams = &gMCSPITestcaseParams[testcaseIdx];
                    #ifdef __TI_ARM_V7M4__
                    if (IPU == testParams->cpuID)
                    {
                        totalTCRun++;
                        mcspiRunTestCase(testParams);
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
                        mcspiRunTestCase(testParams);
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
                        mcspiRunTestCase(testParams);
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
                printf("\nTotal Testcases run:%u/%u\n", totalTCRun,
                       MCSPI_NUM_TESTCASES);
                printf("Number of Testcases Passed:%u\n", numTCPass);
                printf("Number of Testcases Failed:%u\n", numTCFail);
                break;
            case '2':
                for (testcaseId = 0;
                     testcaseId <= MCSPI_NUM_TESTCASES;
                     testcaseId++)
                {
                    testcaseIdx = mcspiGetTestcaseIdx(testcaseId);
                    if (testcaseIdx < 0)
                    {
                        printf("Invalid test case Id.");
                    }
                    else if (TEST_ENABLE ==
                             gMCSPITestcaseParams[testcaseIdx].enableTest)
                    {
                        testParams = &gMCSPITestcaseParams[testcaseIdx];
                        if (ST_TT_SANITY ==
                            (testParams->testType & ST_TT_SANITY))
                        {
                            #ifdef __TI_ARM_V7M4__
                            if (IPU == testParams->cpuID)
                            {
                                totalTCRun++;
                                mcspiRunTestCase(testParams);
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
                                mcspiRunTestCase(testParams);
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
                                mcspiRunTestCase(testParams);
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
                printf("\nTotal Testcases run:%u/%u\n", totalTCRun,
                       MCSPI_NUM_TESTCASES);
                printf("Number of Testcases Passed:%u\n", numTCPass);
                printf("Number of Testcases Failed:%u\n", numTCFail);
                break;
            case '3':
                for (testcaseId = 0;
                     testcaseId <= MCSPI_NUM_TESTCASES;
                     testcaseId++)
                {
                    testcaseIdx = mcspiGetTestcaseIdx(testcaseId);
                    if (testcaseIdx < 0)
                    {
                        printf("Invalid test case Id.\n");
                    }
                    else if (TEST_ENABLE ==
                             gMCSPITestcaseParams[testcaseIdx].enableTest)
                    {
                        testParams = &gMCSPITestcaseParams[testcaseIdx];
                        if (ST_TT_REGRESSION ==
                            (testParams->testType & ST_TT_REGRESSION))
                        {
                            totalTCRun++;
                            mcspiRunTestCase(testParams);
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
                printf("\nTotal Testcases run:%d/%d\n", totalTCRun,
                       MCSPI_NUM_TESTCASES);
                printf("Number of Testcases Passed:%d\n", numTCPass);
                printf("Number of Testcases Failed:%d\n", numTCFail);
                break;
            case '4':
                for (testcaseId = 0;
                     testcaseId <= MCSPI_NUM_TESTCASES;
                     testcaseId++)
                {
                    testcaseIdx = mcspiGetTestcaseIdx(testcaseId);
                    if (testcaseIdx < 0)
                    {
                        printf("Invalid test case Id.\n");
                    }
                    else if (TEST_ENABLE ==
                             gMCSPITestcaseParams[testcaseIdx].enableTest)
                    {
                        testParams = &gMCSPITestcaseParams[testcaseIdx];
                        if (ST_TT_FULL ==
                            (testParams->testType & ST_TT_FULL))
                        {
                            totalTCRun++;
                            mcspiRunTestCase(testParams);
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
                printf("\nTotal Testcases run:%d/%d\n", totalTCRun,
                       MCSPI_NUM_TESTCASES);
                printf("Number of Testcases Passed:%d\n", numTCPass);
                printf("Number of Testcases Failed:%d\n", numTCFail);
                break;
            case 'd':
                st_mcspiPrintTCs();
                break;
            case 't':
                printf("\nEnter testcase ID: ");
                scanf("%d", &testIp);
                testcaseIdx = mcspiGetTestcaseIdx(testIp);
                if (testcaseIdx < 0)
                {
                    printf("Invalid test case Id.");
                }
                else
                {
                    st_mcspiPrintTCDetails(testcaseIdx);
                }
                break;
            case 'g':
                st_mcspiPrintTCResults();
                break;
            case 'q':
                printf("Exiting McSPI UT.\n");
                done = 1;
                break;
        }
    }
    return 0;
}

int32_t mcspiGetTestcaseIdx(uint32_t testcaseId)
{
    int32_t  testcaseIdx = -1;
    uint32_t testCnt;
    const st_MCSPITestcaseParams_t *testParams;

    testParams = &gMCSPITestcaseParams[0u];
    for (testCnt = 0; testCnt < MCSPI_NUM_TESTCASES; testCnt++)
    {
        if (testParams[testCnt].testcaseId == testcaseId)
        {
            testcaseIdx = testCnt;
            break;
        }
    }
    return testcaseIdx;
}

void mcspiRunTestCase(st_MCSPITestcaseParams_t *testParams)
{
    printf("\n|TEST START|:: %u ::\n", testParams->testcaseId);
    printf("|TEST PARAM|:: %s ::\n", testParams->testCaseName);
    printf("|SR|:: %s ::\n", testParams->reqId);

    printf("Testcase Settings:\n");
    printf("--------------------------------------------------------------\n");
    printf("Module                                              :0x%x\n",
           testParams->diagLibTestParams.baseAddr);

    testParams->isRun = STW_SOK;
    testParams->testCaseFxnPtr(testParams);

    if (testParams->testResult == 0U)
        printf("|TEST RESULT|PASS|%u|\n", testParams->testcaseId);
    else
        printf("|TEST RESULT|FAIL|%u|\n", testParams->testcaseId);

    printf("|TEST INFO|:: %s ::\n", testParams->testCaseName);
    printf("|TEST END|:: %u ::\n", testParams->testcaseId);
}

void st_mcspiShowMainMenu(void)
{
    printf("\n=============\n");
    printf("McSPI UT Select\n");
    printf("=============\n");
    st_mcspiPrintSettings(0);
    printf("\nMCSPI UT main menu:\n");
    printf("1: Manual testing (select specific test case to run)\n");
    printf("2. Sanity testing.\n");
    printf("3: Regression testing.\n");
    printf("4: Full testing.\n");
    printf("5: Performance testing.\n");
    printf("d: Display test cases.\n");
    printf("t: Display test case Details.\n");
    printf("g: Generate test report.\n");
    printf("s: System Settings.\n");
    printf("q: Quit.\n");
}

void st_mcspiPrintSettings(uint32_t tcIdx)
{
    st_MCSPITestcaseParams_t *testParams;

    testParams = &gMCSPITestcaseParams[tcIdx];
    if (tcIdx == 0U)
    {
        printf("Current System Settings:\n");
    }
    else
    {
        printf("Testcase Settings:\n");
    }
    printf("--------------------------------------------------------------\n");
    printf("Module                                              :0x%x\n",
           testParams->diagLibTestParams.baseAddr);
    printf("Channel Number (0/1/2/3.)    :0x%x\n",
           testParams->diagLibTestParams.chNumber);
}

void st_mcspiPrintTCs(void)
{
    uint32_t loopCnt;
    int32_t  testcaseIdx;
    const st_MCSPITestcaseParams_t *testParams;

    printf("McSPI Testcase:\n");
    printf("--------------------------------------------------------------\n");
    printf("TC Id\tTC name\n");
    printf("--------------------------------------------------------------\n");
    for (loopCnt = 0; loopCnt <= MCSPI_NUM_TESTCASES; loopCnt++)
    {
        testcaseIdx = mcspiGetTestcaseIdx(loopCnt);
        if (0 > testcaseIdx)
        {
            printf("Invalid test case Id.");
        }
        else
        {
            testParams = &gMCSPITestcaseParams[testcaseIdx];
            printf("%d\t%s\n", testParams->testcaseId, testParams->testCaseName);
        }
    }
    printf("--------------------------------------------------------------\n");
}

void st_mcspiPrintTCDetails(uint32_t testId)
{
    const st_MCSPITestcaseParams_t *testParams;

    testParams = &gMCSPITestcaseParams[testId];
    printf("Testcase Id : %d\n", testParams->testcaseId);
    printf("Testcase Name : %s", testParams->testCaseName);
    printf("\nTestcase Enabled(0-Disabled/1-Enabled) : %d",
           testParams->enableTest);
    printf("\nTestcase Req. Id : %s", testParams->reqId);
    printf("\nTestcase User Info. : %s", testParams->userInfo);
    printf("\nTestcase Disable Reason : %s", testParams->disableReason);
    printf("\nTestcase CPU ID : %d", testParams->cpuID);
    printf("\nTestcase Type : %d", testParams->testType);
    printf("\nTestcase Print Enable(0-Disabled/1-Enabled) : %d\n",
           testParams->printEnable);
}

void st_mcspiTCResultInit(void)
{
    uint32_t loopCnt;
    int32_t  testcaseIdx;
    st_MCSPITestcaseParams_t *testParams;

    for (loopCnt = 0; loopCnt <= MCSPI_NUM_TESTCASES; loopCnt++)
    {
        testcaseIdx = mcspiGetTestcaseIdx(loopCnt);
        if (testcaseIdx < 0)
        {
            /* Invalid test case Id */
        }
        else
        {
            testParams             = &gMCSPITestcaseParams[testcaseIdx];
            testParams->isRun      = STW_EFAIL;
            testParams->testResult = STW_EFAIL;
        }
    }
}

void st_mcspiPrintTCResults(void)
{
    uint32_t loopCnt;
    int32_t  testcaseIdx;
    st_MCSPITestcaseParams_t *testParams;
    char    *testResult, *testEnable, *testType, *adequacy, *passFailCriteria;
    char    *disableReason;

    printf(
        "Sr No.\t        ID\t         Description\t\t                         Status\t    Auto Run\r\n");
    printf(
        "-----------------------------------------------------------------------------------------------------------\r\n");
    for (loopCnt = 0; loopCnt <= MCSPI_NUM_TESTCASES; loopCnt++)
    {
        testcaseIdx = mcspiGetTestcaseIdx(loopCnt);
        if (testcaseIdx < 0)
        {
            // printf("Invalid test case Id.");
        }
        else
        {
            testParams = &gMCSPITestcaseParams[testcaseIdx];
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
            printf(
                "%d\t        %d\t         %s\t                         %s\t    %s\r\n",
                loopCnt,
                testcaseIdx, testParams->testCaseName, testResult,
                testEnable);
        }
    }

    printf(
        "S.No;ID;Requirement Mapping;Description;Pass Fail Criteria;IR;Category;Test Adequacy;Test Result;\r\n");
    printf(
        "------------------------------------------------------------------\r\n");
    for (loopCnt = 0; loopCnt <= MCSPI_NUM_TESTCASES; loopCnt++)
    {
        testcaseIdx = mcspiGetTestcaseIdx(loopCnt);
        if (testcaseIdx < 0)
        {
            // printf("Invalid test case Id.");
        }
        else
        {
            testParams = &gMCSPITestcaseParams[testcaseIdx];
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
            else if (testParams->testType & ST_TT_API)
            {
                testType = "API";
                adequacy = "API";
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

            printf("%d;STW_McSPI_TC%05d;%s;%s;%s;%s;%s;%s;%s;\r\n", loopCnt,
                   testcaseIdx, testParams->reqId, testParams->testCaseName,
                   passFailCriteria, disableReason, testType, adequacy,
                   testResult);
        }
    }
}

