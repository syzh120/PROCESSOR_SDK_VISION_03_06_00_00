/*
 *  Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
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
 * \file     diagLib_eccEmif.c
 * \brief    This file contains internal functions ECC EMIF tests.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <stdlib.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/cslr_cache.h>
#include <diagLib_eccEmif.h>
#include <diagLib_utils.h>

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */
/**
 * \brief   Base address of EMIF module
 */
#define DIAGLIB_EMIF_INST_0                 (SOC_EMIF1_CONF_REGS_BASE)
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void emifEccConfig(uint32_t testType, DiagLib_EccObj_t *eccObj)
{
    uint32_t i;

#if defined (__TI_ARM_V7M4__)
    /* Disable cache to ensure writes are completed */
    HW_WR_FIELD32(SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE + IPU_UNICACHE_CONFIG,
                  IPU_UNICACHE_CONFIG_BYPASS,
                  IPU_UNICACHE_CONFIG_BYPASS_BYPASS);
#endif

    if ((testType == DIAGLIB_ECC_TEST_EMIF_SEC) ||
            (testType == DIAGLIB_ECC_TEST_EMIF_DED))
    {
        for (i = 0; i < EMIF_ECC_FIFO_BUF_SIZE; i++)
        {
            eccObj->errInfo.errAddr[i] = 0U;
        }
        eccObj->errInfo.numValidErrAddr = 0U;
        eccObj->errInfo.errBitLoc       = 0U;
    }

    /* Clear older EMIF interrupts */
    EMIFClearIntrStatus(DIAGLIB_EMIF_INST_0, EMIF_INTR_ALL);
    EMIFConfigECCEnableEcc(DIAGLIB_EMIF_INST_0);

}

#if defined (SOC_TDA2PX)
int32_t emifEccSubQuantaWriteTest
                (const DiagLib_EccEmifTestParams_t *testParams,
                 DiagLib_EccObj_t *eccObj, uint32_t errChkMode, uint32_t timeout)
{
    int32_t status = STW_SOK;
    uint8_t volatile testVal;
    uint32_t volatile testVal32[4];
    uint8_t *test_Addr = NULL;
    uint32_t *test_Addr32 = NULL;
    uint32_t timeStart, elapsedTime = 0U;
    uint32_t tempAddr;
    volatile uint32_t irqStatus;
    uint32_t i;

    eccObj->testState = DIAGLIB_ECC_TEST_PENDING;

    /*  Initialize the uint8 ptr to Ecc Emif Err Addr. */
    tempAddr = (uint32_t) testParams->eccEmifErrAddr;
    test_Addr = (uint8_t *) tempAddr;
    test_Addr32 = (uint32_t *) tempAddr;

    /* Disable ECC and read data from the addr */
    EMIFConfigECCDisableEcc(DIAGLIB_EMIF_INST_0);
    for (i = 0U; i < 4U; i++)
    {
        testVal32[i] = test_Addr32[i];
    }
    testVal = *test_Addr;

    /* Enable ECC and initialize the addr with data for ECC generation.
     * Minimum initialization size is 16 bytes */
    EMIFConfigECCEnableEcc(DIAGLIB_EMIF_INST_0);
    for (i = 0U; i < 4U; i++)
    {
        test_Addr32[i] = testVal32[i];
    }

    EMIFConfigECCClrAllEccErrInfo(DIAGLIB_EMIF_INST_0);
    /* Set RMW bit and then check write sub quanta address. */
    HW_WR_FIELD32(DIAGLIB_EMIF_INST_0 + EMIF_ECC_CTRL_REG,
                  EMIF_ECC_CTRL_REG_REG_RMW_EN, 1U);

    /* Enable ECC and write back the read data */
    EMIFConfigECCEnableEcc(DIAGLIB_EMIF_INST_0);
    *test_Addr = testVal;

    irqStatus = EMIFGetIntrRawStatus(DIAGLIB_EMIF_INST_0);
    /* This should not result in Error as the RMW bit is set. */
    if ((irqStatus & EMIF_SYSTEM_OCP_INTERRUPT_RAW_STATUS_WR_ECC_ERR_SYS_MASK) !=
         0x0)
    {
        status += STW_EINVALID_PARAMS;
    }

    /* read sub quanta. */
    testVal = *test_Addr;
    irqStatus = EMIFGetIntrRawStatus(DIAGLIB_EMIF_INST_0);
    EMIFClearIntrStatus(DIAGLIB_EMIF_INST_0, EMIF_INTR_ALL);
    /* This should not result in Error as the RMW bit is set. */
    if ((irqStatus & EMIF_SYSTEM_OCP_INTERRUPT_RAW_STATUS_WR_ECC_ERR_SYS_MASK) !=
         0x0)
    {
        status += STW_EINVALID_PARAMS;
    }

    /* Clear RMW bit and then check write sub quanta address.
       This will result in error. */
    HW_WR_FIELD32(DIAGLIB_EMIF_INST_0 + EMIF_ECC_CTRL_REG,
                  EMIF_ECC_CTRL_REG_REG_RMW_EN, 0U);

    if (errChkMode == DIAGLIB_ECC_INTERRUPT_MODE)
    {
        EMIFEnableIntr(DIAGLIB_EMIF_INST_0,
                   EMIF_SYSTEM_OCP_INTERRUPT_STATUS_WR_ECC_ERR_SYS_MASK);
    }

    /* Enable ECC and write back the read data */
    EMIFConfigECCEnableEcc(DIAGLIB_EMIF_INST_0);
    *test_Addr = testVal;
    irqStatus = EMIFGetIntrRawStatus(DIAGLIB_EMIF_INST_0);
    EMIFClearIntrStatus(DIAGLIB_EMIF_INST_0, EMIF_INTR_ALL);

    if (errChkMode == DIAGLIB_ECC_INTERRUPT_MODE)
    {
        status += eccObj->testState;
    }
    else if (errChkMode == DIAGLIB_ECC_POLLED_MODE)
    {
        timeStart = DiagLibUtils_getCurTimeInMsec();
        /* Wait for the raw interrupt status to be set */
        do
        {
            /* Get the time elapsed from the start of polling */
            elapsedTime = DiagLibUtils_getElapsedTimeInMsec(timeStart);
            if (EMIFGetIntrRawStatus(DIAGLIB_EMIF_INST_0) != 0U)
            {
                break;
            }

        }
        while(elapsedTime <= timeout);

        if(elapsedTime <= timeout)
        {
            emifNonEccQuantaAddrISR(testParams, eccObj);
        }
        else
        {
            eccObj->testState = DIAGLIB_ECC_TEST_TIMEOUT;
        }
    }
    else
    {
        eccObj->testState = DIAGLIB_ECC_TEST_INVALID_PARAMS;
        status += STW_EINVALID_PARAMS;
    }
    return status;
}
#endif

int32_t emifNonEccQuantaAlignAddrTest
                (const DiagLib_EccEmifTestParams_t *testParams,
                 DiagLib_EccObj_t *eccObj, uint32_t errChkMode, uint32_t timeout)
{
    int32_t status = STW_SOK;
    uint32_t volatile testVal;
    uint32_t *test_Addr = NULL;
    uint32_t timeStart, elapsedTime = 0U;
    uint32_t tempAddr;

    eccObj->testState = DIAGLIB_ECC_TEST_PENDING;

    /* Add an offset to make the address non-quanta aligned */
    tempAddr = (uint32_t) testParams->eccEmifErrAddr + 0x3U;
    test_Addr = (uint32_t *) tempAddr;

    if (errChkMode == DIAGLIB_ECC_INTERRUPT_MODE)
    {
        EMIFEnableIntr(DIAGLIB_EMIF_INST_0,
                   EMIF_SYSTEM_OCP_INTERRUPT_STATUS_WR_ECC_ERR_SYS_MASK);
    }
    EMIFConfigECCClrAllEccErrInfo(DIAGLIB_EMIF_INST_0);

    /* Disable ECC and read data from the addr */
    EMIFConfigECCDisableEcc(DIAGLIB_EMIF_INST_0);
    testVal = *test_Addr;

    /* Enable ECC and write back the read data */
    EMIFConfigECCEnableEcc(DIAGLIB_EMIF_INST_0);
    *test_Addr = testVal;

    if (errChkMode == DIAGLIB_ECC_INTERRUPT_MODE)
    {
        status = eccObj->testState;
    }
    else if (errChkMode == DIAGLIB_ECC_POLLED_MODE)
    {
        timeStart = DiagLibUtils_getCurTimeInMsec();
        /* Wait for the raw interrupt status to be set */
        do
        {
            /* Get the time elapsed from the start of polling */
            elapsedTime = DiagLibUtils_getElapsedTimeInMsec(timeStart);
            if (EMIFGetIntrRawStatus(DIAGLIB_EMIF_INST_0) != 0U)
            {
                break;
            }

        }
        while(elapsedTime <= timeout);

        if(elapsedTime <= timeout)
        {
            emifNonEccQuantaAddrISR(testParams, eccObj);
        }
        else
        {
            eccObj->testState = DIAGLIB_ECC_TEST_TIMEOUT;
        }
    }
    else
    {
        eccObj->testState = DIAGLIB_ECC_TEST_INVALID_PARAMS;
        status = STW_EINVALID_PARAMS;
    }
    return status;
}

int32_t emifByteCntWRAccessNotMultEccQuantaTest
                (const DiagLib_EccEmifTestParams_t *testParams,
                 DiagLib_EccObj_t *eccObj, uint32_t errChkMode, uint32_t timeout)
{
    int32_t status = STW_SOK;
    uint8_t volatile testVal;
    uint8_t *test_Addr = NULL;
    uint32_t timeStart, elapsedTime = 0U;

    eccObj->testState = DIAGLIB_ECC_TEST_PENDING;
    test_Addr = (uint8_t *) testParams->eccEmifErrAddr;

    if (errChkMode == DIAGLIB_ECC_INTERRUPT_MODE)
    {
        EMIFEnableIntr(DIAGLIB_EMIF_INST_0,
                   EMIF_SYSTEM_OCP_INTERRUPT_STATUS_WR_ECC_ERR_SYS_MASK);
    }

    EMIFConfigECCClrAllEccErrInfo(DIAGLIB_EMIF_INST_0);

    /* Disable ECC and read data from the addr */
    EMIFConfigECCDisableEcc(DIAGLIB_EMIF_INST_0);
    eccObj->eccTestVal = *test_Addr;
    testVal = (uint8_t) eccObj->eccTestVal;

    /* Enable ECC and write back the non multiple quanta data */
    EMIFConfigECCEnableEcc(DIAGLIB_EMIF_INST_0);
    *test_Addr = testVal;

    if (errChkMode == DIAGLIB_ECC_INTERRUPT_MODE)
    {
        status = eccObj->testState;
    }
    else if (errChkMode == DIAGLIB_ECC_POLLED_MODE)
    {
        timeStart = DiagLibUtils_getCurTimeInMsec();
        /* Wait for the raw interrupt status to be set */
        do
        {
            /* Get the time elapsed from the start of polling */
            elapsedTime = DiagLibUtils_getElapsedTimeInMsec(timeStart);

            if(EMIFGetIntrRawStatus(DIAGLIB_EMIF_INST_0) != 0U)
            {
                break;
            }
        }
        while(elapsedTime <= timeout);

        if(elapsedTime <= timeout)
        {
            emifNonEccQuantaAddrISR(testParams, eccObj);
        }
        else
        {
            eccObj->testState = DIAGLIB_ECC_TEST_TIMEOUT;
        }
    }
    else
    {
        eccObj->testState = DIAGLIB_ECC_TEST_INVALID_PARAMS;
        status = STW_EINVALID_PARAMS;
    }
    return status;
}

int32_t emifSecErrTest(const DiagLib_EccEmifTestParams_t *testParams,
                        DiagLib_EccObj_t *eccObj, uint32_t errChkMode, uint32_t timeout)
{
    int32_t status = STW_SOK;
    uint32_t volatile testVal[4];
    uint32_t *test_Addr = NULL;
    uint32_t i, j = 0U;
    uint32_t timeStart, elapsedTime = 0U;
    uint32_t tempAddr;

    eccObj->testState = DIAGLIB_ECC_TEST_PENDING;
    test_Addr = (uint32_t *)testParams->eccEmifErrAddr;
    tempAddr = (uint32_t)testParams->eccEmifErrAddr;

    /* Disable ECC and read data from the addr */
    EMIFConfigECCDisableEcc(DIAGLIB_EMIF_INST_0);
    for (i = tempAddr; i < (tempAddr + 0x10U); i += 4U)
    {
        testVal[j] = test_Addr[j];
        j++;
    }

    /* Enable ECC and initialize the addr with data for ECC generation.
     * Minimum initialization size is 16 bytes */
    j = 0;
    EMIFConfigECCEnableEcc(DIAGLIB_EMIF_INST_0);
    for (i = tempAddr; i < (tempAddr + 0x10U); i += 4U)
    {
        test_Addr[j] = testVal[j];
        j++;
    }

    if (errChkMode == DIAGLIB_ECC_INTERRUPT_MODE)
    {
        EMIFEnableIntr(DIAGLIB_EMIF_INST_0,
                   EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_SET_ONEBIT_ECC_ERR_SYS_MASK);
    }

    EMIFConfigECCClrAllEccErrInfo(DIAGLIB_EMIF_INST_0);

    /* Disable ECC, read the data from the address.
     * Toggle a single bit and write it back */
    EMIFConfigECCDisableEcc(DIAGLIB_EMIF_INST_0);

    testVal[0]      = test_Addr[0];
    testVal[0]      = testVal[0] ^ 0x00010000U;
    test_Addr[0] = testVal[0];

    /* Enable ECC and read back from the address */
    EMIFConfigECCEnableEcc(DIAGLIB_EMIF_INST_0);
    testVal[0] = test_Addr[0];

    if (errChkMode == DIAGLIB_ECC_INTERRUPT_MODE)
    {
        status = eccObj->testState;
    }
    else if (errChkMode == DIAGLIB_ECC_POLLED_MODE)
    {
        timeStart = DiagLibUtils_getCurTimeInMsec();
        /* Wait for the raw interrupt status to be set */
        do
        {
            /* Get the time elapsed from the start of polling */
            elapsedTime = DiagLibUtils_getElapsedTimeInMsec(timeStart);

            if (EMIFGetIntrRawStatus(DIAGLIB_EMIF_INST_0) != 0U)
            {
                break;
            }
        }
        while (elapsedTime <= timeout);

        if(elapsedTime <= timeout)
        {
            emifSecISR(testParams, eccObj);
        }
        else
        {
            eccObj->testState = DIAGLIB_ECC_TEST_TIMEOUT;
        }
    }
    else
    {
        eccObj->testState = DIAGLIB_ECC_TEST_INVALID_PARAMS;
        status = STW_EINVALID_PARAMS;
    }
    return status;
}

int32_t emifDedErrTest(const DiagLib_EccEmifTestParams_t *testParams,
                        DiagLib_EccObj_t *eccObj, uint32_t errChkMode)
{
    int32_t status = STW_SOK;
    uint32_t *test_Addr = NULL;
    uint32_t volatile testVal[4];
    uint32_t i, j = 0U;
    uint32_t tempAddr;

    eccObj->testState = DIAGLIB_ECC_TEST_PENDING;
    test_Addr =  (uint32_t *)testParams->eccEmifErrAddr;
    tempAddr =  (uint32_t)testParams->eccEmifErrAddr;

    /* Disable ECC and read data from the addr */
    EMIFConfigECCDisableEcc(DIAGLIB_EMIF_INST_0);
    for (i = tempAddr; i < (tempAddr + 0x10U); i += 4U)
    {
        testVal[j] = test_Addr[j];
        j++;
    }

    /* Enable ECC and initialize the addr with data for ECC generation.
     * Minimum initialization size is 16 bytes */
    j = 0;
    EMIFConfigECCEnableEcc(DIAGLIB_EMIF_INST_0);
    for (i = tempAddr; i < (tempAddr + 0x10U); i += 4U)
    {
        test_Addr[j] = testVal[j];
        j++;
    }
    EMIFEnableIntr(DIAGLIB_EMIF_INST_0,
                   EMIF_SYSTEM_OCP_INTERRUPT_STATUS_TWOBIT_ECC_ERR_SYS_MASK);
    EMIFConfigECCClrAllEccErrInfo(DIAGLIB_EMIF_INST_0);

    /* Disable ECC, read the data from the address.
     * Toggle 2 bits and write it back */
    EMIFConfigECCDisableEcc(DIAGLIB_EMIF_INST_0);

    testVal[0]      = test_Addr[0];
    eccObj->eccTestVal = test_Addr[0];
    testVal[0]      = testVal[0] ^ 0x00030000U;
    test_Addr[0] = testVal[0];

    /* Enable ECC and read back from the address */
    EMIFConfigECCEnableEcc(DIAGLIB_EMIF_INST_0);

    testVal[0] = test_Addr[0];

    status = eccObj->testState;
    return status;
}

void emifNonEccQuantaAddrISR(const DiagLib_EccEmifTestParams_t *testParams,
                                            DiagLib_EccObj_t *eccObj)
{

    uint32_t errStatus;

    /* Get the interrupt status, clear the same & verify if the interrupt
     * is generated by the configured source */
    errStatus = EMIFGetIntrRawStatus(DIAGLIB_EMIF_INST_0);

    EMIFClearIntrStatus(DIAGLIB_EMIF_INST_0,
            EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_SET_WR_ECC_ERR_SYS_MASK |
                EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_SET_EN_ERR_SYS_MASK);

    errStatus = (errStatus &
                    EMIF_SYSTEM_OCP_INTERRUPT_STATUS_WR_ECC_ERR_SYS_MASK) >>
                    EMIF_SYSTEM_OCP_INTERRUPT_STATUS_WR_ECC_ERR_SYS_SHIFT;
    if (errStatus == 1U)
    {
        eccObj->testState = DIAGLIB_ECC_TEST_PASS;
    }
    else
    {
        eccObj->testState = DIAGLIB_ECC_TEST_FAIL;
    }

}

void emifSecISR(const DiagLib_EccEmifTestParams_t *testParams,
                                    DiagLib_EccObj_t *eccObj)
{

    uint32_t errStatus;
    int32_t retVal;
    uint32_t test_Addr = NULL;

    test_Addr = (uint32_t)testParams->eccEmifErrAddr;

    /* Get the interrupt status, clear the same & verify if the interrupt
     * is generated by the configured source */
    errStatus = EMIFGetIntrRawStatus(DIAGLIB_EMIF_INST_0);
    errStatus = (errStatus &
                    EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_SET_ONEBIT_ECC_ERR_SYS_MASK) >>
                    EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_SET_ONEBIT_ECC_ERR_SYS_SHIFT;

    if (errStatus == 1U)
    {
        /* Get the error info of the SEC Error */
        retVal    = EMIFConfigECCGetEccErrInfo(DIAGLIB_EMIF_INST_0,
                    EMIF_ERR_ECC_ONEBIT, &(eccObj->errInfo));
    }
    else
    {
        retVal = STW_EFAIL;
    }

    if (retVal == STW_SOK)
    {
            EMIFClearIntrStatus(DIAGLIB_EMIF_INST_0,
                EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_SET_ONEBIT_ECC_ERR_SYS_MASK);
    }

    if (retVal == STW_SOK)
    {
        if (eccObj->errInfo.numValidErrAddr == 1U)
        {
            /* Compare the error address with the test address */
            if(test_Addr == (eccObj->errInfo.errAddr[0] +
                                    DIAGLIB_EMIF_START_ADDR))
            {
                eccObj->testState = DIAGLIB_ECC_TEST_PASS;
            }
            else
            {
                eccObj->testState = DIAGLIB_ECC_TEST_FAIL;
            }
        }
        else
        {
            eccObj->testState = DIAGLIB_ECC_TEST_FAIL;
        }
    }
    else
    {
        eccObj->testState = DIAGLIB_ECC_TEST_FAIL;
    }
}

void emifDedISR(const DiagLib_EccEmifTestParams_t *testParams,
                                    DiagLib_EccObj_t *eccObj)
{

    uint32_t errStatus;
    int32_t retVal;
    uint32_t *test_Addr = NULL;
    uint32_t tempAddr;

    test_Addr = (uint32_t *)testParams->eccEmifErrAddr;

    /* Get the interrupt status, clear the same & verify if the interrupt
     * is generated by the configured source */
    errStatus = EMIFGetIntrStatus(DIAGLIB_EMIF_INST_0);
    errStatus = (errStatus &
                    EMIF_SYSTEM_OCP_INTERRUPT_STATUS_TWOBIT_ECC_ERR_SYS_MASK) >>
                    EMIF_SYSTEM_OCP_INTERRUPT_STATUS_TWOBIT_ECC_ERR_SYS_SHIFT;
    if (errStatus == 1U)
    {
        /* Get the error info of the DED Error */
        retVal    = EMIFConfigECCGetEccErrInfo(DIAGLIB_EMIF_INST_0,
                        EMIF_ERR_ECC_TWOBIT, &(eccObj->errInfo));
    }
    else
    {
        retVal = STW_EFAIL;
    }

    if (retVal == STW_SOK)
    {
            EMIFClearIntrStatus(DIAGLIB_EMIF_INST_0,
                EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_SET_TWOBIT_ECC_ERR_SYS_MASK);
    }

    if (retVal == STW_SOK)
    {
        /* Compare the error address with the test address
         * And write back the original value before intorducing DED err
         * since DED error is not self-corrected */
        tempAddr = eccObj->errInfo.errAddr[0] + DIAGLIB_EMIF_START_ADDR;
        if((uint32_t)testParams->eccEmifErrAddr == tempAddr)
        {
            EMIFConfigECCDisableEcc(DIAGLIB_EMIF_INST_0);
            test_Addr[0] = eccObj->eccTestVal;
            EMIFConfigECCEnableEcc(DIAGLIB_EMIF_INST_0);
            eccObj->testState = DIAGLIB_ECC_TEST_PASS;
        }
    }
    else
    {
        eccObj->testState = DIAGLIB_ECC_TEST_FAIL;
    }
}
