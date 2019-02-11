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
 *  \file st_crcParser.c
 *
 *  \brief User interface for CRCs driver testing.
 *
 *  This file takes the input from the user specified test file and
 *  then initiates the tests on CRC driver accordingly.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <string.h>
#include <st_crc.h>
#include <st_crcTestCases.h>
#include <ti/csl/soc.h>
#include <ti/csl/soc.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/drv/stw_lld/uartconsole/uartStdio.h>
#include <ti/drv/stw_lld/examples/utility/stwutils_app.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define DEBUG_FLAG        (0U)

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
int32_t crcParser(void);

/**
 * \brief   Get the index of the testcase to run from st_crcTestcases.h.
 *
 * \param   testcaseId        Testcase Id to run.
 *
 * \return  None
 */
int32_t crcGetTestcaseIdx(uint32_t testcaseId);

/**
 * \brief   Fetch testcase data and run the testcase. Present in st_crcSemiCPU.c
 *
 * \param   testParams        structure to details of testcase to run.
 *
 * \return  None
 */
extern void st_crcSemiCPU_main(st_CRCTestcaseParams_t *testParams);

/**
 * \brief   Fetch testcase data and run the testcase. Present in st_crcFullCPU.c
 *
 * \param   testParams        structure to details of testcase to run.
 *
 * \return  None
 */
extern void st_crcFullCPU_main(st_CRCTestcaseParams_t *testParams);

/**
 * \brief   Print main menu.
 *
 * \param   None.
 *
 * \return  None
 */
void st_crcShowMainMenu(void);

/**
 * \brief   Print CRC testcases.
 *
 * \return  None
 */
void st_crcPrintTCs(void);

/**
 * \brief   Print CRC testcase details.
 *
 * \return  None
 */
void st_crcPrintTCDetails(uint32_t testId);

/**
 * \brief   Initialize  CRC testcase details.
 *
 * \return  None
 */
void st_crcTCResultInit(void);

/**
 * \brief   Prints CRC Test Case Statistics.
 *
 * \return  None
 */
void st_crcPrintTCStats(void);

/**
 * \brief   Prints CRC Test Case Results.
 *
 * \return  None
 */
void st_crcPrintTCResults(void);

/**
 * \brief   Print CRC system setings.
 *
 * \param   tcIdx Testcase index for which setting is to be print.
 *
 * \return  None
 */
void st_crcPrintSettings(uint32_t tcIdx);

/**
 * \brief   Print messages on UART console.
 *
 * \param   None.
 *
 * \return  None
 */
void st_crcUARTConfig(void);

#ifdef __TI_ARM_V7M4__
/**
 * \brief   AMMU config - needed for AVVREGRESSION.
 *
 * \param   None.
 *
 * \return  None
 */
void AMMU_config(void);
#endif
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
extern st_CRCTestcaseParams_t gCRCTestcaseParams[];

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
int32_t crcParser(void)
{
    uint32_t                testcaseId;
    uint32_t                numTCPass, numTCFail, totalTCRun, done = 0U;
    int32_t                 testcaseIdx, getCharRetVal, testIp;
    volatile uint32_t       debugFlag = DEBUG_FLAG;
#ifdef _TMS320C6X
    uint32_t                dspCore;
#endif
    char option;
    st_CRCTestcaseParams_t *testParams;

    StwUtils_appWaitForSbl();
#ifdef __TI_ARM_V7M4__
    AMMU_config();
#endif

    st_crcUARTConfig();
    while (debugFlag) ;
#ifdef _TMS320C6X
    /* SOC_DSP_SYSTEM_BASE + DSP_HWINFO FOR DSP1 or DSP2 */
    if (HW_RD_REG32(0x1d00000U + 0x4U) == 0x0)
    {
        dspCore = 1;
    }
    else
    {
        dspCore = 2;
    }
#endif
    st_crcTCResultInit();

    while (!done)
    {
        st_crcShowMainMenu();
        UARTprintf("\nEnter your choice: ");
        getCharRetVal = StwUtils_appGetCharTimeout(
            (int8_t *) &option,
            CRC_APP_UART_TIMEOUT_MSEC);
        if (STW_EFAIL == getCharRetVal)
        {
            /* Timeout - Enable Auto run Option */
            UARTprintf("\r\nUART read timeout %dms. Enable Auto Run !!",
                       CRC_APP_UART_TIMEOUT_MSEC);
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
                    CRC_APP_UART_TIMEOUT_MSEC);
                if (STW_EFAIL == getCharRetVal)
                {
                    /* Timeout - Enable Auto run Option */
                    UARTprintf("\r\nUART read timeout %dms. Enable Auto Run !!",
                               CRC_APP_UART_TIMEOUT_MSEC);
                    testcaseIdx = -1;
                }
                else
                {
                    testcaseIdx = crcGetTestcaseIdx(testIp);
                }
                if (testcaseIdx < 0)
                {
                    UARTprintf("Invalid test case Id.");
                }
                else if (TEST_ENABLE ==
                         gCRCTestcaseParams[testcaseIdx].enableTest)
                {
                    testParams = &gCRCTestcaseParams[testcaseIdx];
                    #ifdef __TI_ARM_V7M4__
                    if (IPU == testParams->cpuID)
                    {
                        totalTCRun++;
                        testParams->testCaseFxnPtr(testParams);
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
                        testParams->testCaseFxnPtr(testParams);
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
                        testParams->testCaseFxnPtr(testParams);
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
                UARTprintf("\nCRC: Total Testcases run:%u/%u\n", totalTCRun,
                           CRC_NUM_TESTCASES);
                UARTprintf("CRC: Number of Testcases Passed:%u\n", numTCPass);
                UARTprintf("CRC: Number of Testcases Failed:%u\n", numTCFail);
                break;
            case '2':
                for (testcaseId = 1;
                     testcaseId <= CRC_NUM_TESTCASES;
                     testcaseId++)
                {
                    testParams = &gCRCTestcaseParams[testcaseId];
                    if ((ST_TT_SANITY ==
                         (testParams->testType & ST_TT_SANITY)) &&
                        (TEST_ENABLE == testParams->enableTest))
                    {
#ifdef __TI_ARM_V7M4__
                        if (IPU == testParams->cpuID)
                        {
                            totalTCRun++;
                            testParams->testCaseFxnPtr(testParams);
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
                            testParams->testCaseFxnPtr(testParams);
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
                            testParams->testCaseFxnPtr(testParams);
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
                UARTprintf("\nCRC: Total Testcases run:%u/%u\n", totalTCRun,
                           (CRC_NUM_TESTCASES - 1));
                UARTprintf("CRC: Number of Testcases Passed:%u\n", numTCPass);
                UARTprintf("CRC: Number of Testcases Failed:%u\n", numTCFail);
                st_crcPrintTCResults();
                break;
            case '3':
                for (testcaseId = 1;
                     testcaseId <= CRC_NUM_TESTCASES;
                     testcaseId++)
                {
                    testcaseIdx = crcGetTestcaseIdx(testcaseId);
                    if (testcaseIdx < 0)
                    {
                        UARTprintf("Invalid test case Id.\n");
                    }
                    else
                    {
                        testParams = &gCRCTestcaseParams[testcaseIdx];
                        if (ST_TT_REGRESSION ==
                            (testParams->testType & ST_TT_REGRESSION))
                        {
                            totalTCRun++;
                            testParams->testCaseFxnPtr(testParams);
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
                UARTprintf("\nCRC: Total Testcases run:%d/%d\n", totalTCRun,
                           CRC_NUM_TESTCASES);
                UARTprintf("CRC: Number of Testcases Passed:%d\n", numTCPass);
                UARTprintf("CRC: Number of Testcases Failed:%d\n", numTCFail);
                break;
            case '4':
                for (testcaseId = 1;
                     testcaseId <= CRC_NUM_TESTCASES;
                     testcaseId++)
                {
                    testParams = &gCRCTestcaseParams[testcaseId];
                    if (TEST_ENABLE == testParams->enableTest)
                    {
#ifdef __TI_ARM_V7M4__
                        if (IPU == testParams->cpuID)
                        {
                            totalTCRun++;
                            testParams->testCaseFxnPtr(testParams);
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
                            testParams->testCaseFxnPtr(testParams);
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
                            testParams->testCaseFxnPtr(testParams);
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
                UARTprintf("\nCRC: Total Testcases run:%u/%u\n", totalTCRun,
                           (CRC_NUM_TESTCASES - 1));
                UARTprintf("CRC: Number of Testcases Passed:%u\n", numTCPass);
                UARTprintf("CRC: Number of Testcases Failed:%u\n", numTCFail);
                st_crcPrintTCResults();
                break;
            case 'd':
                st_crcPrintTCs();
                break;
            case 't':
                UARTprintf("\nEnter testcase ID: ");
                getCharRetVal = StwUtils_appGetNumTimeout(
                    (int32_t *) &testIp,
                    CRC_APP_UART_TIMEOUT_MSEC);
                if (STW_EFAIL == getCharRetVal)
                {
                    /* Timeout - Enable Auto run Option */
                    UARTprintf("\r\nUART read timeout %dms. Enable Auto Run !!",
                               CRC_APP_UART_TIMEOUT_MSEC);
                    testIp = -1;
                }
                testcaseIdx = crcGetTestcaseIdx(testIp);
                if (testcaseIdx < 0)
                {
                    UARTprintf("Invalid test case Id.");
                }
                else
                {
                    st_crcPrintTCDetails(testcaseIdx);
                }
                break;
            case 'g':
                st_crcPrintTCResults();
                break;
            case 'q':
                UARTprintf("Exiting CRC UT.\n");
                done = 1;
                break;
        }
    }

    if (0U == numTCFail)
    {
        UARTprintf("\nAll Test-cases have PASSED.\n");
        StwUtils_appLogTestResult(STWUTILS_APP_TST_STATUS_PASS);
    }
    else
    {
        UARTprintf("\nSome of the Test-cases have FAILED.\n");
        StwUtils_appLogTestResult(STWUTILS_APP_TST_STATUS_FAIL);
    }
    /*for(testcaseId = 1; testcaseId <= CRC_NUM_TESTCASES ; testcaseId++)
     * {
     *  testcaseIdx = crcGetTestcaseIdx(testcaseId);
     *  if(testcaseIdx < 0)
     *  {
     *      UARTprintf("Invalid test case Id.");
     *  }
     *  else
     *  {
     *      testParams = &gCRCTestcaseParams[testcaseIdx];
     *      crcRunTestcase(testParams);
     *  }
     * }*/
    return 0;
}

int32_t crcGetTestcaseIdx(uint32_t testcaseId)
{
    int32_t  testcaseIdx = -1;
    uint32_t testCnt;
    const st_CRCTestcaseParams_t *testParams;

    testParams = &gCRCTestcaseParams[0u];
    for (testCnt = 1; testCnt <= CRC_NUM_TESTCASES; testCnt++)
    {
        if (testParams[testCnt].testcaseId == testcaseId)
        {
            testcaseIdx = testCnt;
            break;
        }
    }
    return testcaseIdx;
}

void crcRunTestcase(st_CRCTestcaseParams_t *testParams)
{
    UARTprintf("\n|TEST START|:: %u ::\n", testParams->testcaseId);
    UARTprintf("|TEST PARAM|:: %s ::\n", testParams->testCaseName);
    UARTprintf("|SR|:: %s ::\n", testParams->reqId);

    UARTprintf("Testcase Settings:\n");
    UARTprintf("--------------------------------\n");
    UARTprintf("Channel                         :%u\n",
               testParams->crcConfigParams.crcChannelNumber);
    UARTprintf("Op Mode(2.SEMI CPU/3.Full CPU)  :%u\n",
               testParams->crcConfigParams.crcMode);
    UARTprintf("Pattern Size(in Bytes)          :%u\n",
               testParams->crcConfigParams.crcPatternSize);
    UARTprintf("Source Memory                   :0x%x\n",
               testParams->sourceMemory);
    UARTprintf("Data Size                       :%u\n",
               testParams->dataSize);
    UARTprintf("======================RUNNING===========================\n");
    switch (testParams->crcConfigParams.crcMode)
    {
        case CRC_OPERATION_MODE_SEMICPU:
            st_crcSemiCPU_main(testParams);
            break;
        case CRC_OPERATION_MODE_FULLCPU:
            st_crcFullCPU_main(testParams);
            break;
        default:
        {}
    }
    testParams->isRun = STW_SOK;
    UARTprintf("\n======================FINISHED==========================\n");
    if (testParams->testResult == 0U)
        UARTprintf("|TEST RESULT|PASS|%u|\n", testParams->testcaseId);
    else
        UARTprintf("|TEST RESULT|FAIL|%u|\n", testParams->testcaseId);

    UARTprintf("|TEST INFO|:: %s ::\n", testParams->testCaseName);
    UARTprintf("|TEST END|:: %u ::\n", testParams->testcaseId);
}

void st_crcShowMainMenu(void)
{
    UARTprintf("\n=============\n");
    UARTprintf("CRC UT Select\n");
    UARTprintf("=============\n");
    st_crcPrintSettings(0);
    UARTprintf("\nCRC UT main menu:\n");
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

void st_crcPrintSettings(uint32_t tcIdx)
{
    st_CRCTestcaseParams_t *testParams;

    testParams = &gCRCTestcaseParams[tcIdx];
    if (tcIdx == 0U)
    {
        UARTprintf("Current System Settings:\n");
    }
    else
    {
        UARTprintf("Testcase Settings:\n");
    }
    UARTprintf("--------------------------------\n");
    UARTprintf("Channel                         :%u\n",
               testParams->crcConfigParams.crcChannelNumber);
    UARTprintf("Op Mode(2.SEMI CPU/3.Full CPU)  :%u\n",
               testParams->crcConfigParams.crcMode);
    UARTprintf("Pattern Size(in Bytes)          :%u\n",
               testParams->crcConfigParams.crcPatternSize);
    UARTprintf("Pattern Count                   :%u\n",
               testParams->crcConfigParams.crcPatternCount);
    UARTprintf("Sector Count                    :%u\n",
               testParams->crcConfigParams.crcSectorCount);
    UARTprintf("Watchdog Preload                :%u\n",
               testParams->crcConfigParams.crcWatchdogPreload);
    UARTprintf("Block Preload                   :%u\n",
               testParams->crcConfigParams.crcBlockPreload);
    UARTprintf("Source Memory                   :0x%x\n",
               testParams->sourceMemory);
    UARTprintf("Data Size                       :%u\n",
               testParams->dataSize);
}

void st_crcPrintTCs(void)
{
    uint32_t loopCnt;
    int32_t  testcaseIdx;
    const st_CRCTestcaseParams_t *testParams;

    UARTprintf("CRC Testcase:\n");
    UARTprintf(
        "--------------------------------------------------------------\n");
    UARTprintf("TC Id\tTC name\n");
    UARTprintf(
        "--------------------------------------------------------------\n");
    for (loopCnt = 1; loopCnt < CRC_NUM_TESTCASES; loopCnt++)
    {
        testcaseIdx = crcGetTestcaseIdx(loopCnt);
        if (0 > testcaseIdx)
        {
            UARTprintf("Invalid test case Id.");
        }
        else
        {
            testParams = &gCRCTestcaseParams[testcaseIdx];
            UARTprintf("%d\t%s\n", testParams->testcaseId,
                       testParams->testCaseName);
        }
    }
    UARTprintf(
        "--------------------------------------------------------------\n");
}

void st_crcPrintTCDetails(uint32_t testId)
{
    const st_CRCTestcaseParams_t *testParams;

    testParams = &gCRCTestcaseParams[testId];
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

void st_crcTCResultInit(void)
{
    uint32_t loopCnt;
    int32_t  testcaseIdx;
    st_CRCTestcaseParams_t *testParams;

    for (loopCnt = 1; loopCnt < CRC_NUM_TESTCASES; loopCnt++)
    {
        testcaseIdx = crcGetTestcaseIdx(loopCnt);
        if (testcaseIdx < 0)
        {
            UARTprintf("Invalid test case Id.");
        }
        else
        {
            testParams             = &gCRCTestcaseParams[testcaseIdx];
            testParams->isRun      = STW_EFAIL;
            testParams->testResult = STW_EFAIL;
        }
    }
}

void st_crcPrintTCStats(void)
{}

void st_crcPrintTCResults(void)
{
    uint32_t loopCnt;
    int32_t  testcaseIdx;
    st_CRCTestcaseParams_t *testParams;
    char    *testResult;
#if !(defined (AVV_TEST_AUTO_BUILD))
    char    *testType, *adequacy, *passFailCriteria;
#endif

    UARTprintf(
        "-----------------------------------------------------------------------------------------------------------\r\n");
    UARTprintf(
        "ID\t         Description\t\t\t                         Status\r\n");
    UARTprintf(
        "-----------------------------------------------------------------------------------------------------------\r\n");
    for (loopCnt = 1; loopCnt < CRC_NUM_TESTCASES; loopCnt++)
    {
        testParams  = &gCRCTestcaseParams[loopCnt];
        testcaseIdx = testParams->testcaseId;
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
        UARTprintf(
            "%d\t         %s\t                         %s\r\n",
            testcaseIdx, testParams->testCaseName, testResult);
    }

    UARTprintf(
        "\n-----------------------------------------------------------------------------------------------------------\r\n");
#if !(defined (AVV_TEST_AUTO_BUILD))
    UARTprintf(
        "S.No;ID;Requirement Mapping;Description;Pass Fail Criteria;IR;Category;Test Adequacy; Test Result;\r\n");
    UARTprintf(
        "------------------------------------------------------------\r\n");
    for (loopCnt = 1; loopCnt < CRC_NUM_TESTCASES; loopCnt++)
    {
        testParams  = &gCRCTestcaseParams[loopCnt];
        testcaseIdx = testParams->testcaseId;
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
            testResult = "NRY";
        }

        switch (testParams->testType)
        {
            case 1:
                testType = "Sanity";
                break;
            case 2:
                testType = "Regression";
                break;
            case 4:
                testType = "Full Testing";
                break;
            case 8:
                testType = "Functional";
                break;
            case 16:
                testType = "Stress";
                break;
            case 32:
                testType = "Negative";
                break;
            case 64:
                testType = "Performance";
                break;
            case 128:
                testType = "Misc.";
                break;
            case 256:
                testType = "API";
                break;
            default:
                testType = "INVALID";
                break;
        }
        if (testParams->testType & ST_TT_STRESS)
        {
            adequacy = "Stress";
        }
        else if (testParams->testType & ST_TT_NEGATIVE)
        {
            adequacy = "Negative";
        }
        else if (testParams->testType & ST_TT_PERFORMANCE)
        {
            adequacy = "Performance";
        }
        else if (testParams->testType & ST_TT_MISC)
        {
            adequacy = "Misc";
        }
        else
        {
            adequacy = "Functional";
        }

        passFailCriteria = testParams->passFailCriteria;
        if (NULL == passFailCriteria)
        {
            passFailCriteria = "";
        }

        UARTprintf("%d;ST_CRC_TC%05d;%s;%s;%s;;%s;%s;%s;\r\n", loopCnt,
                   testcaseIdx, testParams->reqId, testParams->testCaseName,
                   passFailCriteria, testType, adequacy, testResult);
    }
#endif
}

void st_crcUARTConfig(void)
{
    PlatformUartConsoleSetPinMux();
    UARTStdioInit();
}

#ifdef __TI_ARM_V7M4__
void AMMU_config(void)
{
    uint32_t regAddr;

    /*---------------- Setup the UNICACHE MMU -----------------*/
    /*Large Page Translations */
    /* Clear Policy Register- to avoid any conflict */
    regAddr  = SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE;
    regAddr += 0x840;
    HW_WR_REG32(regAddr, 0x0); regAddr += 0x4;
    HW_WR_REG32(regAddr, 0x0); regAddr += 0x4;
    HW_WR_REG32(regAddr, 0x0); regAddr += 0x4;
    HW_WR_REG32(regAddr, 0x0); regAddr += 0x4;

    /* Logical Address */
    regAddr  = SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE;
    regAddr += 0x800;
    HW_WR_REG32(regAddr, 0x40000000); regAddr += 0x4;
    HW_WR_REG32(regAddr, 0x80000000); regAddr += 0x4;
    HW_WR_REG32(regAddr, 0xA0000000); regAddr += 0x4;
    HW_WR_REG32(regAddr, 0x60000000); regAddr += 0x4;

    /* Physical Address */
    regAddr  = SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE;
    regAddr += 0x820;
    HW_WR_REG32(regAddr, 0x40000000); regAddr += 0x4;
    HW_WR_REG32(regAddr, 0x80000000); regAddr += 0x4;
    HW_WR_REG32(regAddr, 0x80000000); regAddr += 0x4;
    HW_WR_REG32(regAddr, 0x40000000); regAddr += 0x4;

    /* Policy Register */
    regAddr  = SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE;
    regAddr += 0x840;
    HW_WR_REG32(regAddr, 0x00000007); regAddr += 0x4;
    HW_WR_REG32(regAddr, 0x000B0007); regAddr += 0x4;
    HW_WR_REG32(regAddr, 0x00000007); regAddr += 0x4;
    HW_WR_REG32(regAddr, 0x00000007); regAddr += 0x4;

    /*Medium Page*/
    /* Clear Policy Register- to avoid any conflict */
    regAddr  = SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE;
    regAddr += 0x8E0;
    HW_WR_REG32(regAddr, 0x0); regAddr += 0x4;
    HW_WR_REG32(regAddr, 0x0); regAddr += 0x4;

    /* Medium page Physical Address */
    regAddr  = SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE;
    regAddr += 0x860;
    HW_WR_REG32(regAddr, 0x00300000); regAddr += 0x4;
    HW_WR_REG32(regAddr, 0x00340000); regAddr += 0x4;

    /* Medium page Virtual Address */
    regAddr  = SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE;
    regAddr += 0x8A0;
    HW_WR_REG32(regAddr, 0x40300000); regAddr += 0x4;
    HW_WR_REG32(regAddr, 0x40340000); regAddr += 0x4;

    /* Policy Register */
    regAddr  = SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE;
    regAddr += 0x8E0;
    HW_WR_REG32(regAddr, 0x00030003); regAddr += 0x4;
    HW_WR_REG32(regAddr, 0x00030003); regAddr += 0x4;

    /*Small Page*/
    /* Clear Policy Register- to avoid any conflict */
    regAddr  = SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE;
    regAddr += 0xA20;
    HW_WR_REG32(regAddr, 0x0); regAddr += 0x4;
    HW_WR_REG32(regAddr, 0x0); regAddr += 0x4;
    HW_WR_REG32(regAddr, 0x0); regAddr += 0x4;
    HW_WR_REG32(regAddr, 0x0); regAddr += 0x4;
    HW_WR_REG32(regAddr, 0x0); regAddr += 0x4;
    HW_WR_REG32(regAddr, 0x0); regAddr += 0x4;
    HW_WR_REG32(regAddr, 0x0); regAddr += 0x4;
    HW_WR_REG32(regAddr, 0x0); regAddr += 0x4;
    HW_WR_REG32(regAddr, 0x0); regAddr += 0x4;
    HW_WR_REG32(regAddr, 0x0); regAddr += 0x4;

    /* Small page Physical Address */
    regAddr  = SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE;
    regAddr += 0x920;
    HW_WR_REG32(regAddr, 0x00000000); regAddr += 0x4;
    HW_WR_REG32(regAddr, 0x40000000); regAddr += 0x4;
    HW_WR_REG32(regAddr, 0x00004000); regAddr += 0x4;
    HW_WR_REG32(regAddr, 0x00008000); regAddr += 0x4;
    HW_WR_REG32(regAddr, 0x0000C000); regAddr += 0x4;
    HW_WR_REG32(regAddr, 0x00000000); regAddr += 0x4;
    HW_WR_REG32(regAddr, 0x00000000); regAddr += 0x4;
    HW_WR_REG32(regAddr, 0x00000000); regAddr += 0x4;
    HW_WR_REG32(regAddr, 0x00000000); regAddr += 0x4;
    HW_WR_REG32(regAddr, 0x00000000); regAddr += 0x4;

    /* Small page Virtual Address */
    regAddr  = SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE;
    regAddr += 0x9A0;
    HW_WR_REG32(regAddr, 0x55020000); regAddr += 0x4;
    HW_WR_REG32(regAddr, 0x55080000); regAddr += 0x4;
    HW_WR_REG32(regAddr, 0x55024000); regAddr += 0x4;
    HW_WR_REG32(regAddr, 0x55028000); regAddr += 0x4;
    HW_WR_REG32(regAddr, 0x5502C000); regAddr += 0x4;
    HW_WR_REG32(regAddr, 0x00000000); regAddr += 0x4;
    HW_WR_REG32(regAddr, 0x00000000); regAddr += 0x4;
    HW_WR_REG32(regAddr, 0x00000000); regAddr += 0x4;
    HW_WR_REG32(regAddr, 0x00000000); regAddr += 0x4;
    HW_WR_REG32(regAddr, 0x00000000); regAddr += 0x4;

    /* Policy Register */
    regAddr  = SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE;
    regAddr += 0xA20;
    HW_WR_REG32(regAddr, 0x0001000B); regAddr += 0x4;
    HW_WR_REG32(regAddr, 0x0000000B); regAddr += 0x4;
    HW_WR_REG32(regAddr, 0x0001000B); regAddr += 0x4;
    HW_WR_REG32(regAddr, 0x00000007); regAddr += 0x4;
    HW_WR_REG32(regAddr, 0x00000007); regAddr += 0x4;
    HW_WR_REG32(regAddr, 0x00000000); regAddr += 0x4;
    HW_WR_REG32(regAddr, 0x00000000); regAddr += 0x4;
    HW_WR_REG32(regAddr, 0x00000000); regAddr += 0x4;
    HW_WR_REG32(regAddr, 0x00000000); regAddr += 0x4;
    HW_WR_REG32(regAddr, 0x00000000); regAddr += 0x4;
}

#endif
