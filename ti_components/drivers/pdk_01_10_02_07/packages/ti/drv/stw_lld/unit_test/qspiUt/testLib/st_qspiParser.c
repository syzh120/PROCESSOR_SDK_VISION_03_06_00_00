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
 *  \file st_qspiParser.c
 *
 *  \brief User interface for QSPI modules testing.
 *
 *  This file takes the input from the user specified test file and
 *  then initiates the tests on QSPI accordingly.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <st_qspiTestCases.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/* None */

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
int32_t st_qspiParser(void);

/**
 * \brief   Get the index of the testcase to run from st_qspiTestcases.h.
 *
 * \param   testcaseId        Testcase Id to run.
 *
 * \return  None
 */
int32_t st_qspiGetTestcaseIdx(uint32_t testcaseId);

/**
 * \brief   Print main menu.
 *
 * \param   None.
 *
 * \return  None
 */
void st_qspiShowMainMenu(void);

/**
 * \brief   Print QSPI testcases.
 *
 * \return  None
 */
void st_qspiPrintTCs(void);

/**
 * \brief   Print QSPI testcase details.
 *
 * \return  None
 */
void st_qspiPrintTCDetails(uint32_t testId);

/**
 * \brief   Initialize QSPI testcase details.
 *
 * \return  None
 */
void st_qspiTCResultInit(void);

/**
 * \brief   Prints QSPI Test Case Results.
 *
 * \return  None
 */
void st_qspiPrintTCResults(void);

void st_qspiRunTestCase(st_QSPITestcaseParams_t *testParams);
static void st_qspiInitFlashCmd(st_QSPITestcaseParams_t *testParams);
static int32_t st_qspiGetFlashCmdCfgIdx(uint32_t cmdCfgId);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
int32_t st_qspiParser(void)
{
    uint32_t testcaseId, testIp;
    uint32_t numTCPass, numTCFail, totalTCRun, done = 0U;
    int32_t  testcaseIdx ;
    char     scnStr[MAX_ARG_LEN], option;
    st_QSPITestcaseParams_t *testParams;

    st_qspiTCResultInit();
    while (!done)
    {
        st_qspiShowMainMenu();
        printf("Enter your choice: \r\n");
        scanf("%s", scnStr);
        option     = scnStr[0];
        numTCPass  = 0U;
        numTCFail  = 0U;
        totalTCRun = 0U;
        switch (option)
        {
            case '1':
                printf("Enter testcase ID to run: \r\n");
                scanf("%d", &testIp);
                testcaseIdx = st_qspiGetTestcaseIdx(testIp);
                if (testcaseIdx < 0)
                {
                    printf("Invalid test case Id \r\n");
                }
                else if (TEST_ENABLE ==
                         gQSPITestcaseParams[testcaseIdx].enableTest)
                {
                    testParams = &gQSPITestcaseParams[testcaseIdx];
                    totalTCRun++;
                    st_qspiRunTestCase(testParams);
                    if (STW_SOK == testParams->testResult)
                    {
                        numTCPass++;
                    }
                    else
                    {
                        numTCFail++;
                    }
                }
                printf("Total Testcases run:%u/%u\r\n", totalTCRun,
                       QSPI_NUM_TESTCASES);
                printf("Number of Testcases Passed:%u\r\n", numTCPass);
                printf("Number of Testcases Failed:%u\r\n", numTCFail);
                break;
            case '2':
                for (testcaseId = 0;
                     testcaseId <= QSPI_NUM_TESTCASES;
                     testcaseId++)
                {
                    testcaseIdx = st_qspiGetTestcaseIdx(testcaseId);
                    if (testcaseIdx < 0)
                    {
                        printf("Invalid test case Id \r\n");
                    }
                    else if (TEST_ENABLE ==
                             gQSPITestcaseParams[testcaseIdx].enableTest)
                    {
                        testParams = &gQSPITestcaseParams[testcaseIdx];
                        if (ST_TT_SANITY ==
                            (testParams->testType & ST_TT_SANITY))
                        {
                            totalTCRun++;
                            st_qspiRunTestCase(testParams);
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
                printf("Total Testcases run:%u/%u \r\n", totalTCRun,
                       QSPI_NUM_TESTCASES);
                printf("Number of Testcases Passed:%u \r\n", numTCPass);
                printf("Number of Testcases Failed:%u \r\n", numTCFail);
                break;
            case '3':
                for (testcaseId = 0;
                     testcaseId <= QSPI_NUM_TESTCASES;
                     testcaseId++)
                {
                    testcaseIdx = st_qspiGetTestcaseIdx(testcaseId);
                    if (testcaseIdx < 0)
                    {
                        printf("Invalid test case Id \r\n");
                    }
                    else if (TEST_ENABLE ==
                             gQSPITestcaseParams[testcaseIdx].enableTest)
                    {
                        testParams = &gQSPITestcaseParams[testcaseIdx];
                        if (ST_TT_REGRESSION ==
                            (testParams->testType & ST_TT_REGRESSION))
                        {
                            totalTCRun++;
                            st_qspiRunTestCase(testParams);
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
                printf("Total Testcases run:%d/%d \r\n", totalTCRun,
                       QSPI_NUM_TESTCASES);
                printf("Number of Testcases Passed:%d \r\n", numTCPass);
                printf("Number of Testcases Failed:%d \r\n", numTCFail);
                break;
            case '4':
                for (testcaseId = 0;
                     testcaseId <= QSPI_NUM_TESTCASES;
                     testcaseId++)
                {
                    testcaseIdx = st_qspiGetTestcaseIdx(testcaseId);
                    if (testcaseIdx < 0)
                    {
                        printf("Invalid test case Id \r\n");
                    }
                    else if (TEST_ENABLE ==
                             gQSPITestcaseParams[testcaseIdx].enableTest)
                    {
                        testParams = &gQSPITestcaseParams[testcaseIdx];
                        if ((ST_TT_SANITY == (testParams->testType & ST_TT_SANITY)) ||
                            (ST_TT_REGRESSION == (testParams->testType & ST_TT_REGRESSION))||
                            (ST_TT_FULL == (testParams->testType & ST_TT_FULL)))
                        {
                            totalTCRun++;
                            st_qspiRunTestCase(testParams);
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
                printf("Total Testcases run:%d/%d \r\n", totalTCRun,
                       QSPI_NUM_TESTCASES);
                printf("Number of Testcases Passed:%d \r\n", numTCPass);
                printf("Number of Testcases Failed:%d \r\n", numTCFail);
                break;
            case 'd':
                st_qspiPrintTCs();
                break;
            case 't':
                printf("Enter testcase ID: \r\n");
                scanf("%d", &testIp);
                testcaseIdx = st_qspiGetTestcaseIdx(testIp);
                if (testcaseIdx < 0)
                {
                    printf("Invalid test case Id \r\n");
                }
                else
                {
                    st_qspiPrintTCDetails(testcaseIdx);
                }
                break;
            case 'g':
                st_qspiPrintTCResults();
                break;
            case 'q':
                printf("Exiting QSPI UT \r\n");
                done = 1;
                break;
        }
    }
    return 0;
}

int32_t st_qspiGetTestcaseIdx(uint32_t testcaseId)
{
    int32_t  testcaseIdx = -1;
    uint32_t testCnt;
    const st_QSPITestcaseParams_t *testParams;

    testParams = &gQSPITestcaseParams[0u];
    for (testCnt = 0; testCnt < QSPI_NUM_TESTCASES; testCnt++)
    {
        if (testParams[testCnt].testcaseId == testcaseId)
        {
            testcaseIdx = testCnt;
            break;
        }
    }
    return testcaseIdx;
}

void st_qspiRunTestCase(st_QSPITestcaseParams_t *testParams)
{
    printf("|TEST START|:: %u ::\r\n", testParams->testcaseId);
    printf("|TEST PARAM|:: %s ::\r\n", testParams->testCaseName);
    printf("|SR|:: %s ::\r\n", testParams->reqId);

    printf("Testcase Settings:\r\n");
    printf("--------------------------------------------------------------\r\n");
    testParams->isRun = STW_SOK;

    st_qspiInitFlashCmd(testParams);

    testParams->testCaseFxnPtr(testParams);

    if (testParams->testResult == 0U)
        printf("|TEST RESULT|PASS|%u|\r\n", testParams->testcaseId);
    else
        printf("|TEST RESULT|FAIL|%u|\r\n", testParams->testcaseId);

    printf("|TEST INFO|:: %s ::\r\n", testParams->testCaseName);
    printf("|TEST END|:: %u ::\r\n", testParams->testcaseId);
    printf("\r\n");
}

void st_qspiShowMainMenu(void)
{
    printf("=============\r\n");
    printf("QSPI UT Select\r\n");
    printf("=============\r\n");
    printf("QSPI UT main menu:\r\n");
    printf("1: Manual testing (select specific test case to run)\r\n");
    printf("2. Sanity testing \r\n");
    printf("3: Regression testing \r\n");
    printf("4: Full testing \r\n");
    printf("5: Performance testing \r\n");
    printf("d: Display test cases \r\n");
    printf("t: Display test case Details \r\n");
    printf("g: Generate test report \r\n");
    printf("s: System Settings \r\n");
    printf("q: Quit \r\n");
}

void st_qspiPrintTCs(void)
{
    uint32_t loopCnt;
    int32_t  testcaseIdx;
    const st_QSPITestcaseParams_t *testParams;

    printf("QSPI Testcase:\r\n");
    printf("--------------------------------------------------------------\r\n");
    printf("TC Id\tTC name\r\n");
    printf("--------------------------------------------------------------\r\n");
    for (loopCnt = 0; loopCnt <= QSPI_NUM_TESTCASES; loopCnt++)
    {
        testcaseIdx = st_qspiGetTestcaseIdx(loopCnt);
        if (0 > testcaseIdx)
        {
            printf("Invalid test case Id\r\n");
        }
        else
        {
            testParams = &gQSPITestcaseParams[testcaseIdx];
            printf("%d\t%s \r\n", testParams->testcaseId, testParams->testCaseName);
        }
    }
    printf("--------------------------------------------------------------\r\n");
}

void st_qspiPrintTCDetails(uint32_t testId)
{
    const st_QSPITestcaseParams_t *testParams;

    testParams = &gQSPITestcaseParams[testId];
    printf("Testcase Id : %d\r\n", testParams->testcaseId);
    printf("Testcase Name : %s", testParams->testCaseName);
    printf("Testcase Enabled(0-Disabled/1-Enabled) : %d",
           testParams->enableTest);
    printf("Testcase Req. Id : %s", testParams->reqId);
    printf("Testcase User Info. : %s", testParams->userInfo);
    printf("Testcase Disable Reason : %s", testParams->disableReason);
    printf("Testcase Type : %d", testParams->testType);
    printf("Testcase Print Enable(0-Disabled/1-Enabled) : %d\r\n",
           testParams->printEnable);
}

void st_qspiTCResultInit(void)
{
    uint32_t loopCnt;
    int32_t  testcaseIdx;
    st_QSPITestcaseParams_t *testParams;

    for (loopCnt = 0; loopCnt <= QSPI_NUM_TESTCASES; loopCnt++)
    {
        testcaseIdx = st_qspiGetTestcaseIdx(loopCnt);
        if (testcaseIdx < 0)
        {
            /* Invalid test case Id */
        }
        else
        {
            testParams             = &gQSPITestcaseParams[testcaseIdx];
            testParams->isRun      = STW_EFAIL;
            testParams->testResult = STW_EFAIL;
        }
    }
}

void st_qspiPrintTCResults(void)
{
    uint32_t loopCnt;
    int32_t  testcaseIdx;
    st_QSPITestcaseParams_t *testParams;
    char    *testResult, *testEnable, *testType, *adequacy, *passFailCriteria;
    char    *disableReason;

    printf(
        "Sr No.\t        ID\t         Description\t\t                         Status\t    Auto Run\r\n");
    printf(
        "-----------------------------------------------------------------------------------------------------------\r\n");
    for (loopCnt = 0; loopCnt <= QSPI_NUM_TESTCASES; loopCnt++)
    {
        testcaseIdx = st_qspiGetTestcaseIdx(loopCnt);
        if (testcaseIdx < 0)
        {
            printf("Invalid test case Id \r\n");
        }
        else
        {
            testParams = &gQSPITestcaseParams[testcaseIdx];
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
    for (loopCnt = 0; loopCnt <= QSPI_NUM_TESTCASES; loopCnt++)
    {
        testcaseIdx = st_qspiGetTestcaseIdx(loopCnt);
        if (testcaseIdx < 0)
        {
            printf("Invalid test case Id \r\n");
        }
        else
        {
            testParams = &gQSPITestcaseParams[testcaseIdx];
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

            printf("%d;STW_QSPI_TC%05d;%s;%s;%s;%s;%s;%s;%s;\r\n", loopCnt,
                   testcaseIdx, testParams->reqId, testParams->testCaseName,
                   passFailCriteria, disableReason, testType, adequacy,
                   testResult);
        }
    }
}

static void st_qspiInitFlashCmd(st_QSPITestcaseParams_t *testParams)
{
    uint32_t cmdCfgId;
    int32_t  cfgIdx;

    cmdCfgId = testParams->testCfg.idCmdCfg.cfgId;

    cfgIdx = st_qspiGetFlashCmdCfgIdx(cmdCfgId);
    if(cfgIdx < 0)
    {
        printf("Invalid command config ID \r\n");
    }
    else
    {
        memcpy(&testParams->testCfg.idCmdCfg.cmd,
               &gStQSPIFlashCmdCfg[cfgIdx].cmd,
               sizeof (QSPI_FlashCmd_t));
    }

    cmdCfgId = testParams->testCfg.rdCmdCfg.cfgId;

    cfgIdx = st_qspiGetFlashCmdCfgIdx(cmdCfgId);
    if(cfgIdx < 0)
    {
        printf("Invalid command config ID \r\n");
    }
    else
    {
        memcpy(&testParams->testCfg.rdCmdCfg.cmd,
               &gStQSPIFlashCmdCfg[cfgIdx].cmd,
               sizeof (QSPI_FlashCmd_t));
    }

    cmdCfgId = testParams->testCfg.wrCmdCfg.cfgId;

    cfgIdx = st_qspiGetFlashCmdCfgIdx(cmdCfgId);
    if(cfgIdx < 0)
    {
        printf("Invalid command config ID \r\n");
    }
    else
    {
        memcpy(&testParams->testCfg.wrCmdCfg.cmd,
               &gStQSPIFlashCmdCfg[cfgIdx].cmd,
               sizeof (QSPI_FlashCmd_t));
    }

    cmdCfgId = testParams->testCfg.sectEraseCmdCfg.cfgId;

    cfgIdx = st_qspiGetFlashCmdCfgIdx(cmdCfgId);
    if(cfgIdx < 0)
    {
        printf("Invalid command config ID \r\n");
    }
    else
    {
        memcpy(&testParams->testCfg.sectEraseCmdCfg.cmd,
               &gStQSPIFlashCmdCfg[cfgIdx].cmd,
               sizeof (QSPI_FlashCmd_t));
    }

    cmdCfgId = testParams->testCfg.subSectEraseCmdCfg.cfgId;

    cfgIdx = st_qspiGetFlashCmdCfgIdx(cmdCfgId);
    if(cfgIdx < 0)
    {
        printf("Invalid command config ID \r\n");
    }
    else
    {
        memcpy(&testParams->testCfg.subSectEraseCmdCfg.cmd,
               &gStQSPIFlashCmdCfg[cfgIdx].cmd,
               sizeof (QSPI_FlashCmd_t));
    }

    cmdCfgId = testParams->testCfg.fullEraseCmdCfg.cfgId;

    cfgIdx = st_qspiGetFlashCmdCfgIdx(cmdCfgId);
    if(cfgIdx < 0)
    {
        printf("Invalid command config ID \r\n");
    }
    else
    {
        memcpy(&testParams->testCfg.fullEraseCmdCfg.cmd,
               &gStQSPIFlashCmdCfg[cfgIdx].cmd,
               sizeof (QSPI_FlashCmd_t));
    }

    cmdCfgId = testParams->testCfg.statCmdCfg.cfgId;

    cfgIdx = st_qspiGetFlashCmdCfgIdx(cmdCfgId);
    if(cfgIdx < 0)
    {
        printf("Invalid command config ID \r\n");
    }
    else
    {
        memcpy(&testParams->testCfg.statCmdCfg.cmd,
               &gStQSPIFlashCmdCfg[cfgIdx].cmd,
               sizeof (QSPI_FlashCmd_t));
    }

    cmdCfgId = testParams->testCfg.wrEnCmdCfg.cfgId;

    cfgIdx = st_qspiGetFlashCmdCfgIdx(cmdCfgId);
    if(cfgIdx < 0)
    {
        printf("Invalid command config ID \r\n");
    }
    else
    {
        memcpy(&testParams->testCfg.wrEnCmdCfg.cmd,
               &gStQSPIFlashCmdCfg[cfgIdx].cmd,
               sizeof (QSPI_FlashCmd_t));
    }
}

static int32_t st_qspiGetFlashCmdCfgIdx(uint32_t cmdCfgId)
{
    int32_t  cfgIdx = -1;
    uint32_t testCnt;
    const st_QSPIFlashCmdCfg *testCmdCfg;

    testCmdCfg = &gStQSPIFlashCmdCfg[0u];
    for (testCnt = 0; testCnt < QSPI_NUM_FLASHCMD_CFG; testCnt++)
    {
        if (testCmdCfg[testCnt].cfgId == cmdCfgId)
        {
            cfgIdx = testCnt;
            break;
        }
    }
    return cfgIdx;
}
