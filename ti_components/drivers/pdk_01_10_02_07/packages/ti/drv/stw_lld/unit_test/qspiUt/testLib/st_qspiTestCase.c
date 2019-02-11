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
 *  \file st_qspiTestCase.c
 *
 *  \brief This file contains QSPI test cases
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <st_qspiCommon.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
uint32_t gStQspiNumWCInt = 0U;
uint32_t gStQspiNumFCInt = 0U;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void st_qspiTest_quickFlash(st_QSPITestcaseParams_t *testPrms)
{
    int32_t  retVal = STW_SOK;
    st_QspiTestCfgPrms  testCfg = testPrms->testCfg;
    int32_t loopCnt;

    for(loopCnt = 0U; loopCnt < testPrms->loopCnt; loopCnt++)
    {
        if ((testPrms->testType & ST_TT_STRESS) == ST_TT_STRESS)
        {
            printf("\r\n QSPI Flash Stress Test - %d \r\n", loopCnt);
        }

        retVal = st_qspiTest_initFlash(testCfg, testCfg.flashType);

        if(retVal != STW_SOK)
        {
            printf("QSPI Flash Init fails \r\n");
        }
        else
        {
            printf("QSPI Flash Init Complete \r\n");
        }

        if(loopCnt == 0)
        {
            if(retVal == STW_SOK)
            {
                retVal = st_qspiTest_eraseFlash(testCfg.eraseType,
                                                testCfg.eraseBlockNo,
                                                testCfg.eraseSectorNo);
                if(retVal != STW_SOK)
                {
                    printf("QSPI Flash Erase fails \r\n");
                }
            }

            if(retVal == STW_SOK)
            {
                retVal = st_qspiTest_writeRandomTestPattern();

                if(retVal != STW_SOK)
                {
                    printf("QSPI Flash Write Test Pattern fails \r\n");
                }
            }

            if(retVal == STW_SOK)
            {
                retVal = st_qspiTest_writeFlash(testCfg.flashSize,
                                                testCfg.dataWidth,
                                                testCfg.offsetAddr);

                if(retVal != STW_SOK)
                {
                    printf("QSPI Flash Write fails \r\n");
                }
                else
                {
                    printf("QSPI Write to Flash Complete \r\n");
                }
            }
        }

        if(retVal == STW_SOK)
        {
            retVal = st_qspiTest_readFlash(testCfg.flashSize,
                                           testCfg.dataWidth,
                                           testCfg.enableReadMemMapMode,
                                           testCfg.offsetAddr,
                                           testCfg.dataTransferMode);

            if(retVal != STW_SOK)
            {
                printf("QSPI Flash Read fails \r\n");
            }
            else
            {
                printf("QSPI Read from Flash Complete \r\n");
            }
        }


        if(retVal == STW_SOK)
        {
            retVal = st_qspiTest_verifyFlashData(testCfg.flashSize,
                                                 testCfg.enableReadMemMapMode);

            if(retVal != STW_SOK)
            {
                printf("QSPI Flash Data Mismatch \r\n");
            }
        }

        if(retVal == STW_SOK)
        {
            retVal = st_qspiTest_deInitFlash();

            if(retVal != STW_SOK)
            {
                printf("QSPI Flash DeInit Fails \r\n");
            }
            else
            {
                printf("QSPI Flash DeInit Complete \r\n");
            }
        }
    }

    if(retVal == STW_SOK)
    {
        printf("QSPI Quick Flash Test Pass\r\n");
        testPrms->testResult = STW_SOK;
    }
    else
    {
        printf("QSPI Quick Flash Test Fail\r\n");
        testPrms->testResult = STW_EFAIL;
    }

}

/* Read Data based on block size for full flash size*/
void st_qspiTest_fullFlash(st_QSPITestcaseParams_t *testPrms)
{
    int32_t  retVal = STW_SOK;
    uint32_t  flashSize, bufSize, k=0, loopCnt;
    st_QspiTestCfgPrms  testCfg = testPrms->testCfg;

    for(loopCnt = 0U; loopCnt < testPrms->loopCnt; loopCnt++)
    {
        if ((testPrms->testType & ST_TT_STRESS) == ST_TT_STRESS)
        {
            printf("QSPI Flash Stress Test - %d \r\n", loopCnt);
        }

        retVal = st_qspiTest_initFlash(testCfg, testCfg.flashType);

        if(retVal != STW_SOK)
        {
            printf("QSPI Flash Init fails \r\n");
        }
        else
        {
            printf("QSPI Flash Init Complete \r\n");
        }

        if(loopCnt == 0)
        {
            if(retVal == STW_SOK)
            {
                retVal = st_qspiTest_eraseFlash(testCfg.eraseType,
                                                testCfg.eraseBlockNo,
                                                testCfg.eraseSectorNo);
                if(retVal != STW_SOK)
                {
                    printf("QSPI Flash Erase fails \r\n");
                }
            }

            if(retVal == STW_SOK)
            {
                retVal = st_qspiTest_writeRandomTestPattern();

                if(retVal != STW_SOK)
                {
                    printf("QSPI Flash Write Test Pattern fails \r\n");
                }
            }
        }

        flashSize = ST_QSPI_FLASH_SIZE;
        bufSize = ST_QSPI_FLASH_BLOCK_SIZE;
        testCfg.flashSize = ST_QSPI_FLASH_BLOCK_SIZE;
        testCfg.offsetAddr = 0U;

        while(flashSize != 0)
        {
            if(loopCnt == 0)
            {
                if(retVal == STW_SOK)
                {
                    retVal = st_qspiTest_writeFlash(testCfg.flashSize,
                                                    testCfg.dataWidth,
                                                    testCfg.offsetAddr);

                    if(retVal != STW_SOK)
                    {
                        printf("QSPI Flash Write fails \r\n");
                    }
                }
            }

            if(retVal == STW_SOK)
            {
                retVal = st_qspiTest_readFlash(testCfg.flashSize,
                                               testCfg.dataWidth,
                                               testCfg.enableReadMemMapMode,
                                               testCfg.offsetAddr,
                                               testCfg.dataTransferMode);

                if(retVal != STW_SOK)
                {
                    printf("QSPI Flash Read fails \r\n");
                }
            }


            if(retVal == STW_SOK)
            {
                retVal = st_qspiTest_verifyFlashData(testCfg.flashSize,
                                                     testCfg.enableReadMemMapMode);

                if(retVal != STW_SOK)
                {
                    printf("QSPI Flash Data Mismatch \r\n");
                }
            }

            if(retVal != STW_SOK)
            {
                break;
            }
            else
            {
                 if ((k % 20U) == 0)
                {
                    /* Print Success Msg only once in 20 times not to clutter console,
                     * still letting user know test is in progress */
                    printf("Testing Completed till block no: %d\r\n", k);
                }

                k++;
                testCfg.offsetAddr += bufSize;
                flashSize  -= bufSize;
            }
        }

        if(retVal == STW_SOK)
        {
            retVal = st_qspiTest_deInitFlash();

            if(retVal != STW_SOK)
            {
                printf("QSPI Flash DeInit Fails \r\n");
            }
            else
            {
                printf("QSPI Flash DeInit Complete \r\n");
            }
        }
    }

    if(retVal == STW_SOK)
    {
        printf("QSPI Full Flash Test Pass\r\n");
        testPrms->testResult = STW_SOK;
    }
    else
    {
        printf("QSPI Full Flash Test Fail\r\n");
        testPrms->testResult = STW_EFAIL;
    }
}

/* Read Data using EDMA for full flash size : But this test fails at end*/
void st_qspiTest_fullFlash_Test(st_QSPITestcaseParams_t *testPrms)
{
    int32_t  retVal = STW_SOK;
    uint32_t  flashSize, bufSize, k=0;
    st_QspiTestCfgPrms  testCfg = testPrms->testCfg;

    retVal = st_qspiTest_initFlash(testCfg, testCfg.flashType);

    if(retVal != STW_SOK)
    {
        printf("QSPI Flash Init fails \r\n");
    }

    if(retVal == STW_SOK)
    {
        retVal = st_qspiTest_eraseFlash(testCfg.eraseType,
                                        testCfg.eraseBlockNo,
                                        testCfg.eraseSectorNo);
        if(retVal != STW_SOK)
        {
            printf("QSPI Flash Erase fails \r\n");
        }
    }

    if(retVal == STW_SOK)
    {
        st_qspiTest_writeRandomTestPattern();

        if(retVal != STW_SOK)
        {
            printf("QSPI Flash Write Test Pattern fails \r\n");
        }
    }

    flashSize = ST_QSPI_FLASH_SIZE;
    bufSize = ST_QSPI_FLASH_BLOCK_SIZE;
    testCfg.flashSize = ST_QSPI_FLASH_BLOCK_SIZE;
    testCfg.offsetAddr = 0U;

    while(flashSize != 0)
    {
        if(retVal == STW_SOK)
        {
            retVal = st_qspiTest_writeFlash(testCfg.flashSize,
                                            testCfg.dataWidth,
                                            testCfg.offsetAddr);

            if(retVal != STW_SOK)
            {
                printf("QSPI Flash Write fails \r\n");
            }
        }

        if ((k % 20U) == 0)
        {
            /* Print Success write Msg only once in 20 times not to clutter console,
             * still letting user know test is in progress */
            printf("Write data Completed till block no: %d\r\n", k);
        }

        k++;
        testCfg.offsetAddr += bufSize;
        flashSize  -= bufSize;
    }

    testCfg.flashSize = ST_QSPI_FLASH_SIZE;
    testCfg.offsetAddr = 0U;

    if(retVal == STW_SOK)
    {
        retVal = st_qspiTest_readFlash(testCfg.flashSize,
                                       testCfg.dataWidth,
                                       testCfg.enableReadMemMapMode,
                                       testCfg.offsetAddr,
                                       testCfg.dataTransferMode);

        if(retVal != STW_SOK)
        {
            printf("QSPI Flash Read fails \r\n");
        }
    }


    if(retVal == STW_SOK)
    {
        retVal = st_qspiTest_verifyFlashData(testCfg.flashSize,
                                             testCfg.enableReadMemMapMode);

        if(retVal != STW_SOK)
        {
            printf("QSPI Flash Data Mismatch \r\n");
        }
    }

    if(retVal == STW_SOK)
    {
        retVal = st_qspiTest_deInitFlash();

        if(retVal != STW_SOK)
        {
            printf("QSPI Flash DeInit Fails \r\n");
        }
    }

    if(retVal == STW_SOK)
    {
        printf("QSPI Full Flash Test Pass\r\n");
        testPrms->testResult = STW_SOK;
    }
    else
    {
        printf("QSPI Full Flash Test Fail\r\n");
        testPrms->testResult = STW_EFAIL;
    }
}

void st_qspiTest_GetMemMapCfg(st_QSPITestcaseParams_t *testPrms)
{
    int32_t  retVal = STW_SOK;
    uint32_t memSetupInfo = 0U, rdCmd;
    st_QspiTestCfgPrms  testCfg = testPrms->testCfg;
    QSPI_FlashCmd_t  *testRdcmd;

    testRdcmd = &testCfg.rdCmdCfg.cmd;

    retVal = st_qspiTest_initFlash(testCfg, testCfg.flashType);

    if(retVal != STW_SOK)
    {
        printf("QSPI Flash Init fails \r\n");
    }

    memSetupInfo = QSPIgetMemoryMapSetup(DEF_QSPI_MODULE, DEF_CHIP_SELECT);

    rdCmd = memSetupInfo & QSPI_SPI_SETUP0_REG_RCMD_MASK;

    if(rdCmd != testRdcmd->cmd)
    {
      retVal =  STW_EFAIL;
    }

    if(retVal == STW_SOK)
    {
        retVal = st_qspiTest_deInitFlash();

        if(retVal != STW_SOK)
        {
            printf("QSPI Flash DeInit Fails \r\n");
        }
    }

    if(retVal == STW_SOK)
    {
        printf("QSPI Flash: Get Memory Map Setup Configuration Test Pass\r\n");
        testPrms->testResult = STW_SOK;
    }
    else
    {
        printf("QSPI Flash: Get Memory Map Setup Configuration Test Fail\r\n");
        testPrms->testResult = STW_EFAIL;
    }

}

void st_qspiTest_quickFlash_Interrupt(st_QSPITestcaseParams_t *testPrms)
{
    int32_t  retVal = STW_SOK;
    st_QspiTestCfgPrms  testCfg = testPrms->testCfg;
    uint32_t  intStatus, intRawStatus, intFlag = 0U;

    intRawStatus = QSPIintRawStatus(SOC_QSPI_ADDRSP0_BASE);
    QSPIintRawStatusClear(SOC_QSPI_ADDRSP0_BASE, intRawStatus);

    if((testCfg.enableWcInt == TRUE) |
       (testCfg.enableFcInt == TRUE))
    {
        if(testCfg.enableWcInt == TRUE)
        {
            HW_SET_FIELD32(intFlag, QSPI_INTR_ENABLE_SET_REG_WIRQ_ENA_SET, TRUE);
        }

        if(testCfg.enableFcInt == TRUE)
        {
            HW_SET_FIELD32(intFlag, QSPI_INTR_ENABLE_SET_REG_FIRQ_ENA_SET, TRUE);
        }

        Intc_Init();
        Intc_IntEnable(APP_QSPI_INT_M4);
        /* Register ISR */
        Intc_IntRegister(APP_QSPI_INT_M4,
                         (IntrFuncPtr) st_qspiTest_isr_wc_fc, 0);
        Intc_IntPrioritySet(APP_QSPI_INT_M4, 1, 0);
        Intc_SystemEnable(APP_QSPI_INT_M4);

        QSPIintEnable(SOC_QSPI_ADDRSP0_BASE, intFlag);
    }

    retVal = st_qspiTest_initFlash(testCfg, testCfg.flashType);

    if(retVal != STW_SOK)
    {
        printf("QSPI Flash Init fails \r\n");
    }

    printf("Init Flash complete\r\n");

    if(retVal == STW_SOK)
    {
        st_qspiTest_eraseFlash(testCfg.eraseType,
                               testCfg.eraseBlockNo,
                               testCfg.eraseSectorNo);
        if(retVal != STW_SOK)
        {
            printf("QSPI Flash Erase fails \r\n");
        }
    }

    printf("Erase Flash complete\r\n");

    if(retVal == STW_SOK)
    {
        st_qspiTest_writeRandomTestPattern();

        if(retVal != STW_SOK)
        {
            printf("QSPI Flash Write Test Pattern fails \r\n");
        }
    }

    if(retVal == STW_SOK)
    {
        st_qspiTest_writeFlash(testCfg.flashSize,
                               testCfg.dataWidth,
                               testCfg.offsetAddr);

        if(retVal != STW_SOK)
        {
            printf("QSPI Flash Write fails \r\n");
        }
    }

    printf("Write Flash complete\r\n");

    if(retVal == STW_SOK)
    {
        st_qspiTest_readFlash(testCfg.flashSize,
                              testCfg.dataWidth,
                              testCfg.enableReadMemMapMode,
                              testCfg.offsetAddr,
                              testCfg.dataTransferMode);

        if(retVal != STW_SOK)
        {
            printf("QSPI Flash Read fails \r\n");
        }
    }

    printf("Read Flash complete\r\n");

    if((testCfg.enableWcInt == TRUE) |
       (testCfg.enableFcInt == TRUE))
    {
        QSPIintDisable(SOC_QSPI_ADDRSP0_BASE, intFlag);
        intStatus = QSPIgetEnabledIntStatus(SOC_QSPI_ADDRSP0_BASE);

        while(intStatus !=0)
        {
            /*Do Nothing*/
        }
    }
    else
    {
        intRawStatus = QSPIintRawStatus(SOC_QSPI_ADDRSP0_BASE);
        QSPIintRawStatusClear(SOC_QSPI_ADDRSP0_BASE, intRawStatus);
    }

    if(retVal == STW_SOK)
    {
        retVal = st_qspiTest_verifyFlashData(testCfg.flashSize,
                                             testCfg.enableReadMemMapMode);

        if(retVal != STW_SOK)
        {
            printf("QSPI Flash Data Mismatch \r\n");
        }
    }

    if(retVal == STW_SOK)
    {
        st_qspiTest_deInitFlash();

        if(retVal != STW_SOK)
        {
            printf("QSPI Flash DeInit Fails \r\n");
        }
    }

    if(retVal == STW_SOK)
    {
        if((testCfg.enableWcInt == TRUE) |
           (testCfg.enableFcInt == TRUE))
        {
            printf("Number of WC Interuupts %d\r\n", gStQspiNumWCInt);
            printf("Number of FC Interuupts %d\r\n", gStQspiNumFCInt);
        }

        printf("QSPI Quick Flash Interrupt Test Pass\r\n");
        testPrms->testResult = STW_SOK;
    }
    else
    {
        printf("QSPI Quick Flash Interrupt Test Fail\r\n");
        testPrms->testResult = STW_EFAIL;
    }

    if((testCfg.enableWcInt == TRUE) |
       (testCfg.enableFcInt == TRUE))
    {
        Intc_SystemDisable(APP_QSPI_INT_M4);
        Intc_IntUnregister(APP_QSPI_INT_M4);
        Intc_IntDisable();
    }
}
