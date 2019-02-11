/*
 *   Copyright (c) Texas Instruments Incorporated 2015
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
 *  \file     tesoc.c
 *
 *  \brief    This file contains the implementation of the APIs present in the
 *            device abstraction layer file of TESOC.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/cslr_tesoc.h>
#include <ti/csl/soc.h>
#include <ti/csl/csl_tesoc.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   This function clears TESOC Misc. register.
 *
 * \param   baseAddr        Base Address of the TESOC Registers.
 *
 * \return  None
 */
static void TesocClearMiscRegister(uint32_t baseAddr);

/**
 * \brief   This function clears TESOC slice config of previous run for
 *          selected domain. This isdone so no unintended slices are run by
 *            TESOC.
 *
 * \param   baseAddr        Base Address of the TESOC Registers.
 *
 * \return  None
 */
static void TesocClearSliceConfig(uint32_t baseAddr);

/**
 * \brief   This function clears TESOC slice status of previous run for
 *            selected domain.
 *
 * \param   baseAddr        Base Address of the TESOC Registers.
 *
 * \return  None
 */
static void TesocClearSliceStatus(uint32_t baseAddr);

/**
 * \brief   This function clears TESOC slice result of previous run for
 *            selected domain.
 *
 * \param   baseAddr        Base Address of the TESOC Registers.
 *
 * \return  None
 */
static void TesocClearSliceResult(uint32_t baseAddr);

/**
 * \brief   This function clears TESOC diagnostic log registers.
 *
 * \param   baseAddr        Base Address of the TESOC Registers.
 *
 * \return  None
 */
static void TesocClearDiagnosticLog(uint32_t baseAddr);

/**
 * \brief   This function is used to enable TESOC test on selected domain by
 *          writing enable pattern to TESOC domain enable register for that
 *            domain.
 *
 * \param   baseAddr        Base Address of the TESOC Registers.
 * \param   domainLabel     Domain on which test is run.
 *                          Refer enum #tesocDomainLabel_t for details.
 *
 * \return  status          Whether TESOC test start on domain succeeded.
 *                          STW_SOK         : Success
 *                          STW_EFAIL       : Failure
 */
static int32_t TesocDomainStart(uint32_t baseAddr, uint32_t domainLabel);

/**
 * \brief   This function is used to read TESOC slice status register
 *          for domain on which test was run. Slice status can be
 *          completed, not completed(or not run) depending on slice
 *          configuration for test.
 *
 * \param   baseAddr        Base Address of the TESOC Registers.
 * \param   domainLabel     Domain on which test is run.
 *                          Refer enum #tesocDomainLabel_t for details.
 * \param   testSliceStatus Pointer to array of size NUM_SLICE_BLOCKS
 *                          for storing slice status.
 *
 * \return  status          Whether slice status info is fetched correctly.
 *                          STW_SOK         : Success.
 *                          STW_EFAIL       : Failure.
 */
static int32_t TesocGetTestSliceStatus(uint32_t  baseAddr,
                                       uint32_t  domainLabel,
                                       uint32_t *testSliceStatus);

/**
 * \brief   This function is used to read TESOC slice result register
 *          for domain on which test was run. Slice result can be
 *          fail, pass(or not run) depending on slice configuration
 *          for test.
 *
 * \param   baseAddr        Base Address of the TESOC Registers.
 * \param   domainLabel     Domain on which test is run.
 *                          Refer enum #tesocDomainLabel_t for details.
 * \param   testSliceResult Pointer to array of size NUM_SLICE_BLOCKS
 *                          for storing slice result.
 *
 * \return  status          Whether slice result info is fetched correctly.
 *                          STW_SOK         : Success.
 *                          STW_EFAIL       : Failure.
 */
static int32_t TesocGetTestSliceResult(uint32_t  baseAddr,
                                       uint32_t  domainLabel,
                                       uint32_t *testSliceResult);

/**
 * \brief   This function will return diagnostic slice number for domain.
 *
 * \param   baseAddr        Base Address of the TESOC Registers.
 * \param   testId          TESOC Test ID.
 *
 * \return  diagSliceNumber Whether diagnostic slice number for domain
 *                          fetched correctly.
 *                          (+ve value)         : diagnostic slice number.
 *                          (-1)               : No diagnostic slice for
 *                                                this domain.
 */
static int32_t TesocGetDiagSliceNumber(uint32_t baseAddr,
                                       uint32_t testId);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/**
 * \brief   Default slice configurations for each of TESOC domain in the SOC.
 *          Refer struct #tesocTestCfg_t for details.
 */
static const tesocTestCfg_t
    gTesocDefaultSliceCfg[TESOC_NUM_TESTS] = TESOC_DEFAULT_SLICE_CFG;

/**
 * \brief   Diagnostic slice configurations for each of TESOC domain in the SOC.
 */
static const tesocDiagnosticSliceCfg_t
    gTesocDiagnosticSliceCfg[TESOC_NUM_TESTS] =
    TESOC_DIAGNOSTIC_SLICE_CFG;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t TESOCGetDefaultSliceInfo(uint32_t        baseAddr,
                                 tesocTestCfg_t *testCfg)
{
    int32_t  retVal = STW_SOK;
    uint32_t sliceBlock;

    if ((TESOC_NUM_TESTS - 1U) < (testCfg->testId))
    {
        /* Invalid test Id */
        retVal = STW_EFAIL;
    }
    else
    {
        testCfg->domainLabel =
            gTesocDefaultSliceCfg[testCfg->testId].domainLabel;
        testCfg->completionIntrEnable =
            gTesocDefaultSliceCfg[testCfg->testId].completionIntrEnable;
        for (sliceBlock = 0; sliceBlock < TESOC_NUM_SLICE_BLOCKS; sliceBlock++)
        {
            testCfg->sliceTestBlock[sliceBlock] =
                gTesocDefaultSliceCfg[testCfg->testId].sliceTestBlock[
                    sliceBlock];
        }
    }
    return retVal;
}

int32_t TESOCClearPrevState(uint32_t baseAddr, uint32_t domainLabel)
{
    int32_t retVal  = STW_SOK;
    int32_t intMask = TESOC_INTR_FLAG_TEST_COMPLETION;

    if ((TESOC_NUM_DOMAINS - 1U) < domainLabel)
    {
        /* Invalid domain label */
        retVal = STW_EFAIL;
    }
    else
    {
        TESOCClearAbort(baseAddr);
        TesocClearMiscRegister(baseAddr);
        TESOCIntrClear(baseAddr, (uint32_t) intMask);
        TesocClearDiagnosticLog(baseAddr);
        TesocClearSliceConfig(baseAddr);
        TesocClearSliceStatus(baseAddr);
        TesocClearSliceResult(baseAddr);
    }
    return retVal;
}

int32_t TESOCConfigAndStart(uint32_t              baseAddr,
                            const tesocTestCfg_t *testCfg)
{
    int32_t  retVal = STW_SOK;
    uint32_t tesocDomainConfigAddr, tesocDomainConfigOffset;
    uint32_t i, sliceBlock;
    uint32_t domainLabel = testCfg->domainLabel;

    if ((TESOC_NUM_DOMAINS - 1U) < domainLabel)
    {
        /* Invalid domain label */
        retVal = STW_EFAIL;
    }
    else
    {
        TESOCUnlockMMR(baseAddr);
        /* Get slice config register address for domain */
        tesocDomainConfigOffset = (TESOC_SLICE_CONFIG_DOM0(0) +
                                   ((TESOC_NUM_SLICES /
                                     TESOC_NUM_SLICE_BLOCKS) * domainLabel));
        tesocDomainConfigAddr = (baseAddr + tesocDomainConfigOffset);

        /* Configure slices to be run in TESOC slice config register */
        for (i = 0; i < TESOC_NUM_SLICE_BLOCKS; i++)
        {
            sliceBlock = tesocDomainConfigAddr + (i * 0x4U);
            if (0U !=
                testCfg->sliceTestBlock[i])
            {
                /* write config to TESOC config register */
                HW_WR_REG32(sliceBlock, testCfg->sliceTestBlock[i]);
            }
        }

        /* Start test by writing start pattern to TESOC domain
         * start register */
        retVal = TesocDomainStart(baseAddr, domainLabel);
        /* TESOC execution won't start until TESOC Configuration registers
         * are locked after slice configuration.*/
        TESOCLockMMR(baseAddr);
    }
    return retVal;
}

uint32_t TESOCGetTestExecutionStatus(uint32_t baseAddr)
{
    uint32_t retVal;
    uint32_t regVal, busyStatus;

    regVal     = HW_RD_REG32(baseAddr + TESOC_BUSY);
    busyStatus = HW_GET_FIELD(regVal, TESOC_BUSY);
    if (TESOC_BUSY_BUSY != busyStatus)
    {
        retVal = 0U;
    }
    else
    {
        retVal = 1U;
    }
    return retVal;
}

int32_t TESOCWaitUntilBusy(uint32_t baseAddr, uint32_t timeOut)
{
    int32_t           retVal           = STW_SOK;
    volatile uint32_t timeOutTesocTest = timeOut;
    volatile uint32_t regVal, busyStatus;
    Bool timeOutTesocTestTmp;

    if (TESOC_TIMEOUT_INFINITE != timeOut)
    {
        do
        {
            regVal     = HW_RD_REG32(baseAddr + TESOC_BUSY);
            busyStatus = HW_GET_FIELD(regVal, TESOC_BUSY);
            timeOutTesocTest--;
            timeOutTesocTestTmp = (Bool) (timeOutTesocTest != 0);
        }
        while ((TESOC_BUSY_BUSY != busyStatus) && (timeOutTesocTestTmp != FALSE));
        if (0U == timeOutTesocTest)
        {
            retVal = STW_EFAIL;
        }
    }
    else
    {
        do
        {
            regVal     = HW_RD_REG32(baseAddr + TESOC_BUSY);
            busyStatus = HW_GET_FIELD(regVal, TESOC_BUSY);
        } while (TESOC_BUSY_BUSY == busyStatus);
    }
    return retVal;
}

int32_t TESOCWaitUntilNotBusy(uint32_t baseAddr, uint32_t timeOut)
{
    int32_t           retVal           = STW_SOK;
    volatile uint32_t timeOutTesocTest = timeOut;
    volatile uint32_t regVal, busyStatus;
    Bool timeOutTesocTestTmp;

    if (TESOC_TIMEOUT_INFINITE != timeOut)
    {
        do
        {
            regVal     = HW_RD_REG32(baseAddr + TESOC_BUSY);
            busyStatus = HW_GET_FIELD(regVal, TESOC_BUSY);
            timeOutTesocTest--;
            timeOutTesocTestTmp = (Bool) (timeOutTesocTest != 0);
        }
        while ((TESOC_BUSY_BUSY == busyStatus) && (timeOutTesocTestTmp != FALSE));
        if (0U == timeOutTesocTest)
        {
            retVal = STW_EFAIL;
        }
    }
    else
    {
        do
        {
            regVal     = HW_RD_REG32(baseAddr + TESOC_BUSY);
            busyStatus = HW_GET_FIELD(regVal, TESOC_ABORT);
        } while (TESOC_BUSY_BUSY == busyStatus);
    }
    return retVal;
}

int32_t TESOCCheckTestResult(uint32_t              baseAddr,
                             const tesocTestCfg_t *testCfg)
{
    int32_t retVal;
    tesocAdvanceResult_t testResult;

    if (testCfg->domainLabel > (TESOC_NUM_DOMAINS - 1U))
    {
        /* Invalid domain label */
        retVal = STW_EFAIL;
    }
    else
    {
        /* Ignore advance result structure as not needed for simple
         * pass/fail status
         */
        retVal = TESOCGetAdvanceResult(baseAddr, testCfg,
                                       &testResult);
    }
    return retVal;
}

int32_t TESOCAbortTest(uint32_t baseAddr)
{
    int32_t status = STW_SOK;

    HW_WR_FIELD32(baseAddr + TESOC_ABORT,
                  TESOC_ABORT, TESOC_ABORT_ABORT);
    return status;
}

void TESOCClearAbort(uint32_t baseAddr)
{
    HW_WR_FIELD32(baseAddr + TESOC_ABORT,
                  TESOC_ABORT, 0x0);
}

int32_t TESOCSetSliceSrc(uint32_t baseAddr, uint32_t testSliceSrc)
{
    int32_t retVal = STW_SOK;

    /* Unlock TESOC MMR */
    TESOCUnlockMMR(baseAddr);
    switch (testSliceSrc)
    {
        case TESOC_SLICE_SRC_ROM:
            HW_WR_FIELD32(baseAddr + TESOC_MISC_CONFIG,
                          TESOC_MISC_CONFIG_SOURCE_CONTROL,
                          TESOC_MISC_CONFIG_SOURCE_CONTROL_SLICE_SOURCE_ROM);
            break;
        case TESOC_SLICE_SRC_RAM:
            HW_WR_FIELD32(baseAddr + TESOC_MISC_CONFIG,
                          TESOC_MISC_CONFIG_SOURCE_CONTROL,
                          TESOC_MISC_CONFIG_SOURCE_CONTROL_SLICE_SOURCE_RAM);
            break;
        default:
            retVal = STW_EFAIL;
            break;
    }
    TESOCLockMMR(baseAddr);
    return retVal;
}

int32_t TESOCRunTesoCDiagnostic(uint32_t baseAddr,
                                uint32_t testId)
{
    int32_t        retVal = STW_SOK;
    int32_t        status;
    uint32_t       block;
    tesocTestCfg_t diagTestCfg;

    if ((TESOC_NUM_TESTS - 1U) < testId)
    {
        retVal = STW_EFAIL;
    }
    else
    {
        diagTestCfg.domainLabel = gTesocDiagnosticSliceCfg[testId].domainLabel;
        for (block = 0; block < TESOC_NUM_SLICE_BLOCKS; block++)
        {
            diagTestCfg.sliceTestBlock[block] =
                gTesocDiagnosticSliceCfg[testId].diagSliceCfg[block];
        }
        TESOCClearPrevState(baseAddr, diagTestCfg.domainLabel);
        status = TESOCConfigAndStart(baseAddr, &diagTestCfg);
        if (STW_SOK == status)
        {
            status = TESOCCheckTestResult(baseAddr, &diagTestCfg);
            /* TESOCCheckTestResult takes care of checking if failed slice
             * is diagnostic slice and if yes returns STW_SOK of diagnostic
             * slice failure */
            if (STW_EFAIL == status)
            {
                retVal = status;
            }
        }
        else
        {
            retVal = status;
        }
    }
    return retVal;
}

int32_t TESOCGetAdvanceResult(uint32_t              baseAddr,
                              const tesocTestCfg_t *testCfg,
                              tesocAdvanceResult_t *advanceResult)
{
    int32_t  retVal = STW_SOK;
    uint32_t currentSlice;
    uint32_t slice, block, sliceStatusFlag = 1U, sliceResultFlag = 1U;
    int32_t  diagSliceNumber;
    uint32_t sliceBlockStatus, sliceBlockResult;
    uint32_t currentSliceTmp;

    if ((TESOC_NUM_DOMAINS - 1U) < testCfg->domainLabel)
    {
        /* Invalid domain label */
        retVal = STW_EFAIL;
    }
    else
    {
        advanceResult->domainLabel = testCfg->domainLabel;
        /*Get result of  all slices configured for TESOC execution */
        TesocGetTestSliceResult(baseAddr, testCfg->domainLabel,
                                advanceResult->sliceResult);
        /*Get status of all slices configured for TESOC execution */
        TesocGetTestSliceStatus(baseAddr, testCfg->domainLabel,
                                advanceResult->sliceStatus);
        for (block = 0; block < TESOC_NUM_SLICE_BLOCKS; block++)
        {
            /*Check if all slices configured for TESOC execution are
             * completed and passed*/
            sliceBlockStatus = testCfg->sliceTestBlock[block] &
                               advanceResult->sliceStatus[block];
            sliceBlockResult = testCfg->sliceTestBlock[block] &
                               advanceResult->sliceResult[block];
            if ((sliceBlockStatus == testCfg->sliceTestBlock[block])
                &&
                (sliceBlockResult == testCfg->sliceTestBlock[block]))
            {
                /* All slices completed execution */
                sliceResultFlag = 1U;
                sliceStatusFlag = 1U;
                advanceResult->failedSliceNumber = -((int32_t) 1);
                advanceResult->abortFlag         = 0;
            }
            else
            {
                /* Not all slices configured completed execution */
                for (slice = 0;
                     slice < (TESOC_NUM_SLICES / TESOC_NUM_SLICE_BLOCKS);
                     slice++)
                {
                    currentSlice = (block * 32U) + slice;
                    /* Check if current slice was configured for execution*/
                    if (testCfg->sliceTestBlock[block] & ((uint32_t) 1 << slice))
                    {
                        /* Check if current slice completed its execution */
                        if ((advanceResult->sliceStatus[block] &
                             ((uint32_t) 1 << slice)))
                        {
                            /* Check if current slice passed after execution */
                            currentSliceTmp =
                                (advanceResult->sliceResult[block] &
                                 ((uint32_t) 1 << slice));
                            if (currentSliceTmp == 0)
                            {
                                /* Break slices loop as TESOC stops execution
                                 * once
                                 * detects failure */
                                sliceResultFlag = 0U;
                                sliceStatusFlag = 0U;
                                advanceResult->failedSliceNumber = currentSlice;
                                advanceResult->abortFlag         = 0;
                                retVal = STW_EFAIL;
                                break;
                            }
                        }
                        else
                        {
                            sliceStatusFlag = 0U;
                        }
                    }
                }
                /* Break slice block loop as TESOC stop execution once detects
                 *  failure */
                break;
            }
        }
        if (0U == sliceResultFlag)
        {
            /* Check if failed slice is TESOC diagnostic slice for domain */
            diagSliceNumber = TesocGetDiagSliceNumber(baseAddr,
                                                      testCfg->testId);

            /* check if domain doesn't have diagnostic slice */
            if ((-((int32_t) 1)) == diagSliceNumber)
            {
                /* As domain does not have diagnostic slice some other
                 * valid slice failed*/
                retVal = STW_EFAIL;
            }
            else
            {
                if ((uint32_t) diagSliceNumber == currentSlice)
                {
                    /* As only diagnostic slice failed(which is valid failure)
                     * return
                     * test pass*/
                    retVal = STW_SOK;
                    /* As diagnostic slice fails for normal operation,
                     * removing it as failed slice*/
                    advanceResult->failedSliceNumber = -((int32_t) 1);
                }
                else
                {
                    /* As slice other that diagnostic slice failed return test
                     *fail*/
                    retVal = STW_EFAIL;
                }
            }
        }
        /* Check if Test was aborted and TESOC aborted gracefully */
        if ((1U == sliceResultFlag)
            &&
            (0U == sliceStatusFlag))
        {
            advanceResult->abortFlag = 1U;
        }
    }
    return retVal;
}

int32_t TESOCReadDiagnosticLog(uint32_t         baseAddr,
                               uint32_t *const *diagnosticLog)
{
    int32_t    status = STW_SOK;
    uint32_t   i, j;
    uint32_t **pDiagLog;
    uint32_t   tmpOffset;

    tmpOffset = baseAddr + TESOC_DIAG_INFO_0(0);
    pDiagLog  = (uint32_t **) tmpOffset;
    for (i = 0; i < TESOC_DIAG_LOG_CYCLES; i++)
    {
        for (j = 0; j < (TESOC_DIAG_LOG_DATA_SIZE); j++)
        {
            diagnosticLog[i][j] = pDiagLog[i][j];
        }
    }
    return status;
}

void TESOCIntrEnable(uint32_t baseAddr, uint32_t intrMask)
{
    TESOCUnlockMMR(baseAddr);
    HW_WR_REG32(baseAddr + TESOC_INTR_ENABLE_SET, intrMask);
    TESOCLockMMR(baseAddr);
}

void TESOCIntrDisable(uint32_t baseAddr, uint32_t intrMask)
{
    TESOCUnlockMMR(baseAddr);
    HW_WR_REG32(baseAddr + TESOC_INTR_ENABLE_CLEAR, intrMask);
    TESOCLockMMR(baseAddr);
}

uint32_t TESOCGetIntrEnable(uint32_t baseAddr)
{
    return HW_RD_REG32(baseAddr + TESOC_INTR_ENABLE_SET);
}

uint32_t TESOCGetIntrStatus(uint32_t baseAddr)
{
    return HW_RD_REG32(baseAddr + TESOC_INTR_STATUS_RAW_SET);
}

void TESOCIntrClear(uint32_t baseAddr, uint32_t intrMask)
{
    TESOCUnlockMMR(baseAddr);
    HW_WR_REG32(
        baseAddr + TESOC_INTR_STATUS_ENABLED_CLEAR,
        intrMask);
    TESOCLockMMR(baseAddr);
}

uint32_t TESOCGetIntrRawStatus(uint32_t baseAddr)
{
    return HW_RD_REG32(baseAddr + TESOC_INTR_STATUS_RAW_SET);
}

void TESOCUnlockMMR(uint32_t baseAddr)
{
    /* Unlock the access to TESOC registers */
    HW_WR_FIELD32(baseAddr + TESOC_LOCK,
                  TESOC_LOCK, TESOC_LOCK_TO_UNLOCK);
}

void TESOCLockMMR(uint32_t baseAddr)
{
    /* Lock the access to TESOC registers */
    HW_WR_FIELD32(baseAddr + TESOC_LOCK,
                  TESOC_LOCK, TESOC_LOCK_TO_LOCK);
}

/* ========================================================================== */
/*                Internal  Function Definitions                              */
/* ========================================================================== */

static void TesocClearMiscRegister(uint32_t baseAddr)
{
    TESOCUnlockMMR(baseAddr);
    HW_WR_REG32(baseAddr + TESOC_MISC_CONFIG, 0x0);
    TESOCLockMMR(baseAddr);
}

static void TesocClearSliceConfig(uint32_t baseAddr)
{
    uint32_t tesocDomainConfigOffset;
    uint32_t tesocDomainConfigAddr;
    uint32_t sliceBlockAddr;
    uint32_t domain, sliceBlock;

    TESOCUnlockMMR(baseAddr);

    for (domain = 0; domain < TESOC_NUM_DOMAINS; domain++)
    {
        /* Get slice config register address for domain */
        tesocDomainConfigOffset = (TESOC_SLICE_CONFIG_DOM0(0) +
                                   ((TESOC_NUM_SLICES /
                                     TESOC_NUM_SLICE_BLOCKS) * domain));
        tesocDomainConfigAddr = (baseAddr + tesocDomainConfigOffset);

        for (sliceBlock = 0; sliceBlock < TESOC_NUM_SLICE_BLOCKS; sliceBlock++)
        {
            sliceBlockAddr = tesocDomainConfigAddr + (sliceBlock * 0x4U);
            HW_WR_REG32(sliceBlockAddr, 0x0);
        }
    }
    TESOCLockMMR(baseAddr);
}

static void TesocClearSliceStatus(uint32_t baseAddr)
{
    uint32_t tesocDomainStatusOffset;
    uint32_t tesocDomainStatusAddr;
    uint32_t sliceBlockAddr;
    uint32_t domain, sliceBlock;

    TESOCUnlockMMR(baseAddr);
    for (domain = 0; domain < TESOC_NUM_DOMAINS; domain++)
    {
        /* Get slice status register address for domain */
        tesocDomainStatusOffset = (TESOC_SLICE_STATUS_DOM0(0) +
                                   ((TESOC_NUM_SLICES /
                                     TESOC_NUM_SLICE_BLOCKS) * domain));
        tesocDomainStatusAddr = (baseAddr + tesocDomainStatusOffset);
        for (sliceBlock = 0; sliceBlock < TESOC_NUM_SLICE_BLOCKS; sliceBlock++)
        {
            sliceBlockAddr = tesocDomainStatusAddr + (sliceBlock * 0x4U);
            HW_WR_REG32(sliceBlockAddr, 0x0);
        }
    }
    TESOCLockMMR(baseAddr);
}

static void TesocClearSliceResult(uint32_t baseAddr)
{
    uint32_t tesocDomainResultOffset;
    uint32_t tesocDomainResultAddr;
    uint32_t sliceBlockAddr;
    uint32_t domain, sliceBlock;

    TESOCUnlockMMR(baseAddr);
    for (domain = 0; domain < TESOC_NUM_DOMAINS; domain++)
    {
        /* Get slice result register address for domain */
        tesocDomainResultOffset = (TESOC_SLICE_RESULT_DOM0(0) +
                                   ((TESOC_NUM_SLICES /
                                     TESOC_NUM_SLICE_BLOCKS) * domain));
        tesocDomainResultAddr = (baseAddr + tesocDomainResultOffset);
        for (sliceBlock = 0; sliceBlock < TESOC_NUM_SLICE_BLOCKS; sliceBlock++)
        {
            sliceBlockAddr = tesocDomainResultAddr + (sliceBlock * 0x4U);
            HW_WR_REG32(sliceBlockAddr, 0xFFFFFFFFU);
        }
    }
    TESOCLockMMR(baseAddr);
}

static void TesocClearDiagnosticLog(uint32_t baseAddr)
{
    uint32_t  i, j;
    uint32_t *pDiagLog;
    uint32_t  tmpOffset;

    TESOCUnlockMMR(baseAddr);
    for (i = 0; i < TESOC_DIAG_LOG_CYCLES; i++)
    {
        tmpOffset = baseAddr + TESOC_DIAG_INFO_0(i * 4U);
        pDiagLog  = (uint32_t *) tmpOffset;
        for (j = 0; j < (TESOC_DIAG_LOG_DATA_SIZE); j++)
        {
            HW_WR_REG32((pDiagLog + j), 0x0);
        }
    }
    TESOCLockMMR(baseAddr);
}

static int32_t TesocDomainStart(uint32_t baseAddr,
                                uint32_t domainLabel)
{
    int32_t  status = STW_SOK;
    uint32_t tesocDomainEnRegAddr;

    tesocDomainEnRegAddr = baseAddr +
                           TESOC_DOMAIN_EN_DOM(domainLabel);
    HW_WR_FIELD32(tesocDomainEnRegAddr,
                  TESOC_DOMAIN_EN_DOM_START,
                  TESOC_DOMAIN_EN_DOM_START_TO_START);
    return status;
}

static int32_t TesocGetTestSliceStatus(uint32_t  baseAddr,
                                       uint32_t  domainLabel,
                                       uint32_t *testSliceStatus)
{
    int32_t  retVal = STW_SOK;
    uint32_t tesocDomainStatusOffset;
    uint32_t tesocDomainStatusAddr;
    uint32_t sliceBlock, sliceBlockAddress, sliceBlockStatus;

    if ((TESOC_NUM_DOMAINS - 1U) < domainLabel)
    {
        /* Invalid domain label */
        retVal = STW_EFAIL;
    }
    else
    {
        /* Get slice status register address for domain */
        tesocDomainStatusOffset = (TESOC_SLICE_STATUS_DOM0(0) +
                                   ((TESOC_NUM_SLICES /
                                     TESOC_NUM_SLICE_BLOCKS) * domainLabel));
        tesocDomainStatusAddr = (baseAddr + tesocDomainStatusOffset);
        for (sliceBlock = 0; sliceBlock < TESOC_NUM_SLICE_BLOCKS; sliceBlock++)
        {
            sliceBlockAddress = tesocDomainStatusAddr +
                                (sliceBlock * 0x4U);
            sliceBlockStatus = HW_RD_REG32(sliceBlockAddress);
            testSliceStatus[sliceBlock] = sliceBlockStatus;
        }
    }
    return retVal;
}

static int32_t TesocGetTestSliceResult(uint32_t  baseAddr,
                                       uint32_t  domainLabel,
                                       uint32_t *testSliceResult)
{
    int32_t  retVal = STW_SOK;
    uint32_t tesocDomainResultOffset;
    uint32_t tesocDomainResultAddr;
    uint32_t sliceBlock, sliceBlockAddress, sliceBlockResult;

    if ((TESOC_NUM_DOMAINS - 1U) < domainLabel)
    {
        /* Invalid domain label */
        retVal = STW_EFAIL;
    }
    else
    {
        /* Get slice result register address for domain */
        tesocDomainResultOffset = (TESOC_SLICE_RESULT_DOM0(0) +
                                   ((TESOC_NUM_SLICES /
                                     TESOC_NUM_SLICE_BLOCKS) * domainLabel));
        tesocDomainResultAddr = (baseAddr + tesocDomainResultOffset);
        for (sliceBlock = 0; sliceBlock < TESOC_NUM_SLICE_BLOCKS; sliceBlock++)
        {
            sliceBlockAddress = tesocDomainResultAddr +
                                (sliceBlock * 0x4U);
            sliceBlockResult = HW_RD_REG32(sliceBlockAddress);
            testSliceResult[sliceBlock] = sliceBlockResult;
        }
    }
    return retVal;
}

static int32_t TesocGetDiagSliceNumber(uint32_t baseAddr,
                                       uint32_t testId)
{
    int32_t diagSlice;

    diagSlice =
        gTesocDiagnosticSliceCfg[testId].diagSliceNumber;
    if ((-((int32_t) 1)) == diagSlice)
    {
        /* No diagnostic slice for domain */
        diagSlice = (-((int32_t) 1));
    }
    return diagSlice;
}

