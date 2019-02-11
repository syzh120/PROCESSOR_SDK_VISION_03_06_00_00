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
 *  \ingroup CSL_IP_MODULE
 *  \defgroup CSL_TESOC Tesoc
 *
 *  @{
 */
/**
 *  \file     tesoc.h
 *
 *  \brief    This file contains the prototypes of the APIs present in the
 *            device abstraction layer file of TESOC.
 *            This also contains some related macros.
 */

/**
 *   TESOC module allows functional mode field testing of SoC. It enables
 *   SW initiated field testing during run-time. The field test can be
 *   initiated by any SoC master having access to TESOC registers.
 *   SoC is divided into multiple domains for field test. At any point of
 *   time field test can be enabled on one domain without corrupting/
 *   stalling functionality of the rest of the SoC. The TESOC ROM image
 *   is the encoded version of the test vectors and is already divided into
 *   slices.
 *   For running field test through TESOC, select domain for which test be tun,
 *   slices to be run are configured through tesocTestCfg_t structure.
 *   Default slice configuration of each domain on SoC can be obtained through
 *   TESOCGetDefaultSliceInfo function.
 *
 *   TESOC programming sequence:
 *
 *      1. Configure TESOC external clock for required frequency.
 *      2. Check if module for which TESOC test to be run is powered off.
 *      3. Select configuration for running TESOC through tesocTestCfg_t
 *         structure.
 *      4. Clear TESOC registers before test
 *         (use API TESOCClearPrevState()).
 *      5. Configure TESOC for test, select domain and slices to be run
 *         (use API TESOCConfigAndStart()).
 *      6. Get TESOC test running status(use API TESOCGetTestStatus()).
 *      7. Wait for TESOC test to complete(Interrupt or polling).
 *      8. Check result of test. Use API TESOCCheckTestResult() which returns
 *         fail or pass status of TESOC test.
 */

#ifndef TESOC_H_
#define TESOC_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <ti/csl/cslr_tesoc.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */
/**
 * \brief  Macro containing mask of all the interrupts.
 *         This macro can be passed to interrupt control API's to enable or
 *         disable all the main interrupts at a time.
 */
#define TESOC_IRQSTATUS_RAW_ALL (TESOC_INTR_STATUS_RAW_TEST_COMPLETION_SET_MASK)

/**
 * \brief  Timeout value for TESOC start after test configuration is done.
 */
#define  TESOC_TIMEOUT_TEST_START                            (0xFFFFU)

/**
 * \brief  Timeout value for TESOC test completion after test is started.
 *         This is maximum of test times of all domains.
 */
#define  TESOC_TIMEOUT_TEST_END                              (0xFFFFU)

/**
 * \brief  Infinite timeout for TESOC test.
 *         Use this if you want to wait infinitely for test start or
 *         test completion.
 */
#define  TESOC_TIMEOUT_INFINITE                              (0xFFFFFFFFU)

/**
 * \brief  TESOC test running status: TESOC is running test.
 */
#define  TESOC_TEST_RUNNING                                  (0U)

/**
 * \brief  TESOC test running status: TESOC has completed test.
 */
#define  TESOC_TEST_COMPLETED                                (1U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */
/**
 * \brief  Enum to select the slice source for TESOC Test.
 *         TESOC can run slices from ROM or RAM.
 */
typedef enum tesocSliceSrc
{
    TESOC_SLICE_SRC_ROM = TESOC_MISC_CONFIG_SOURCE_CONTROL_SLICE_SOURCE_ROM,
    /**< Configure slice source as ROM */
    TESOC_SLICE_SRC_RAM = TESOC_MISC_CONFIG_SOURCE_CONTROL_SLICE_SOURCE_RAM
                          /**< Configure slice source as RAM */
}tesocSliceSrc_t;

/**
 * \brief  TESOC interrupt flags.
 */
typedef enum tesocIntrFlag
{
    TESOC_INTR_FLAG_TEST_COMPLETION =
        TESOC_INTR_STATUS_RAW_TEST_COMPLETION_SET_ENABLE,
    /**< TESOC test completion interrupt mask */
    TESOC_INTR_FLAG_ALL = TESOC_IRQSTATUS_RAW_ALL
                          /**< Macro to control all the above interrupt status
                          **/
}tesocIntrFlag_t;

/**
 * \brief  This Structure defines the configuration for running TESOC test.
 *         These parameters are used for configuring domainType and
 *         slice configuration.
 */
typedef struct tesocTestCfg
{
    uint32_t testId;
    /**< Test ID for running TESOC test. Refer
     *   enum #tesocTestId_t for details */
    uint32_t domainLabel;
    /**< Domain label for running TESOC test on. Refer
     *   enum #tesocDomainLabel_t for details */
    uint32_t completionIntrEnable;
    /**< Flag to enable TESOC test completion interrupt */
    uint32_t sliceTestBlock[TESOC_NUM_SLICE_BLOCKS];
    /**< Array containing slice numbers on which test is run */
}tesocTestCfg_t;

/**
 *  \brief This Structure is used for diagnostic slice configuration info for
 *         each domain in current revision of SoC.
 */
typedef struct tesocDiagnosticSliceCfg
{
    uint32_t testId;
    /**< Test ID for running TESOC test. Refer
     *   enum #tesocTestId_t for details */
    uint32_t domainLabel;
    /**< Domain label for running TESOC test on. Refer
     *   enum #tesocDomainLabel_t for details */
    uint32_t diagSliceCfg[TESOC_NUM_SLICE_BLOCKS];
    /**< Diagnostic slice configuration for domain in SoC */
    int32_t  diagSliceNumber;
    /**< Diagnostic slice number for domain in SoC */
}tesocDiagnosticSliceCfg_t;

/**
 * \brief   This Structure is used for storing results of TESOC test.
 *          These parameters are used as place holder for storing result.
 */
typedef struct tesocAdvanceResult
{
    uint32_t domainLabel;
    /**< Domain label for running TESOC test on. Refer
     *   enum #tesocDomainLabel_t for details */
    uint32_t sliceStatus[TESOC_NUM_SLICE_BLOCKS];
    /**< Status of slices configured for TESOC test*/
    uint32_t sliceResult[TESOC_NUM_SLICE_BLOCKS];
    /**< Result of slices configured for TESOC test*/
    int32_t  failedSliceNumber;
    /**< Slice number of failed slice after TESOC execution,
     *      value of (-1) if none failed */
    uint32_t abortFlag;
    /**< Flag for detecting TESOC test Abort */
    uint32_t errorLog[TESOC_DIAG_LOG_CYCLES][TESOC_DIAG_LOG_DATA_SIZE];
    /**< On test failure TESOC dumps TESOC_DIAG_LOG_CYCLES cycles of
     *   data. Each cycle of data is of size TESOC_DIAG_LOG_DATA_SIZE.
     */
}tesocAdvanceResult_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 * \brief   This API gets default slice configuration information for a
 *          particular domain.
 *
 * \param   baseAddr        Base Address of the TESOC registers
 * \param   testCfg         Structure for holding TESOC test default
 *                          configuration. Contains information of default
 *                          slices enabled for the domain in the current
 *                          revision of SoC.
 *                          Refer struct #tesocTestCfg_t for details.
 *
 * \return  status          Whether slice info is fetched correctly.
 *                          STW_SOK         : Success.
 *                          STW_EFAIL       : Failure.
 */
int32_t TESOCGetDefaultSliceInfo(uint32_t        baseAddr,
                                 tesocTestCfg_t *testCfg);

/**
 * \brief   This API clears register state of previous TESOC test run(if any).
 *
 * \param   baseAddr        Base Address of the TESOC Registers.
 * \param   domainLabel     Domain configured for TESOC test. Registers
 *                          associated with this domain will be cleared.
 *                          Refer enum #tesocDomainLabel_t for details.
 * \return  status          Whether TESOC previous run state is cleaned
 *                          correctly.
 *                          STW_SOK         : Success.
 *                          STW_EFAIL       : Failure.
 */
int32_t TESOCClearPrevState(uint32_t baseAddr, uint32_t domainLabel);

/**
 * \brief   This API configures TESOC for test and starts test
 *          on selected domain.
 *
 * \param   baseAddr        Base Address of the TESOC Registers.
 * \param   testCfg         Structure for TESOC test configuration, contains
 *                          details like domain label and slices to be run.
 *                          Refer struct #tesocTestCfg_t for details.
 *
 * \return  status          Whether TESOC configured and started test correctly.
 *                          STW_SOK         : Success
 *                          STW_EFAIL       : Failure
 */
int32_t TESOCConfigAndStart(uint32_t              baseAddr,
                            const tesocTestCfg_t *testCfg);

/**
 * \brief   Get execution state of TESOC(busy/completed).
 *
 * \param   baseAddr        Base Address of the TESOC Registers.
 *
 * \return  status          TESOC running status
 *                          TESOC_TEST_RUNNING  : TESOC test Running
 *                          TESOC_TEST_COMPLETED: TESOC test Completed.
 */
uint32_t TESOCGetTestExecutionStatus(uint32_t baseAddr);

/**
 * \brief   This function is used to wait till TESOC starts test.
 *
 * \param   baseAddr        Base Address of the TESOC Registers.
 * \param   timeOut         Wait time duration can be set to any uint32 or
 *                          TESOC_TIMEOUT_TEST_START
 *                          TESOC_TIMEOUT_INFINITE
 *
 * \return  status          Whether wait for TESOC busy succeeded.
 *                          STW_SOK         : Success
 *                          STW_EFAIL       : wait for busy failed(timeout).
 */
int32_t TESOCWaitUntilBusy(uint32_t baseAddr, uint32_t timeOut);

/**
 * \brief   This function is used to wait till TESOC completes running test.
 *
 * \param   baseAddr        Base Address of the TESOC Registers.
 * \param   timeOut         Wait time duration can be set to any uint32 or
 *                          TESOC_TIMEOUT_TEST_END
 *                          TESOC_TIMEOUT_INFINITE
 *
 * \return  status          Whether wait for TESOC not busy succeeded.
 *                          STW_SOK         : Success
 *                          STW_EFAIL       : wait for not busy
 *                                            failed(timeout).
 */
int32_t TESOCWaitUntilNotBusy(uint32_t baseAddr, uint32_t timeOut);

/**
 * \brief   Check result of TESOC test.
 *
 * \param   baseAddr        Base Address of the TESOC Registers.
 * \param   testCfg         Structure containing TESOC test configuration info
 *                          like domain label and slices configured.
 *                          Refer struct #tesocTestCfg_t for details.
 *
 * \return  status          TESOC test result.
 *                          STW_SOK         : Test Passed.
 *                          STW_EFAIL       : Test Failed.
 */
int32_t TESOCCheckTestResult(uint32_t              baseAddr,
                             const tesocTestCfg_t *testCfg);

/**
 * \brief   This API aborts ongoing TESOC test.
 *
 * \param   baseAddr        Base Address of the TESOC Registers.
 *
 * \return  status          Whether test is aborted correctly.
 *                          STW_SOK   : Success
 *                          STW_EFAIL : Failure
 */
int32_t TESOCAbortTest(uint32_t baseAddr);

/**
 * \brief   This API clears TESOC abort register.
 *
 * \param   baseAddr        Base Address of the TESOC Registers.
 *
 * \return  None
 */
void TESOCClearAbort(uint32_t baseAddr);

/**
 * \brief   This API will set slice source for running TESOC test.
 *
 * \param   baseAddr        Base Address of the TESOC Registers.
 * \param   testSliceSrc    Source of slice for TESOC test.
 *                          Refer enum #tesocSliceSrc_t for details.
 *
 * \return  status          TESOC test result.
 *                          STW_SOK         : Test Passed.
 *                          STW_EFAIL       : Failure
 */
int32_t TESOCSetSliceSrc(uint32_t baseAddr, uint32_t testSliceSrc);

/**
 * \brief   This API will run TESOC diagnostic slice for domain passed.
 *
 * \param   baseAddr        Base Address of the TESOC Registers.
 * \param   testId          Test Id for which TESOC diagnostic slice to be run.
 *                          Refer enum #tesocTestId_t for details.
 *
 * \return  status          Whether TESOC diagnostic test on selected domain
 *                          run correctly.
 *                          STW_SOK      : Success
 *                          STW_EFAIL    : Failure
 *
 * \note    Not all TESOC domains have diagnostic slice.
 *
 */
int32_t TESOCRunTesoCDiagnostic(uint32_t baseAddr,
                                uint32_t testId);

/**
 * \brief   This API reads detailed result of TESOC test.
 *          Result contains details like slices configured for test, slice
 *          status like completed/not run and result(pass/fail)
 *          of each of these slice.
 *
 * \param   baseAddr        Base Address of the TESOC Registers.
 * \param   testCfg         Structure containing TESOC test configuration info
 *                          like domain label and slices configured.
 *                          Refer struct #tesocTestCfg_t for details.
 * \param   advanceResult   Structure for holding detailed TESOC test result,
 *                          contains information for slice configured, slice
 *                          status and slice result after TESOC test.
 *                          Refer struct #tesocAdvanceResult_t for details.
 *
 * \return  status          TESOC test result.
 *                          STW_SOK         : Test Passed.
 *                          STW_EFAIL       : Test Failed.
 */
int32_t TESOCGetAdvanceResult(uint32_t              baseAddr,
                              const tesocTestCfg_t *testCfg,
                              tesocAdvanceResult_t *advanceResult);

/**
 * \brief   This API reads error diagnostic log for TESOC test failure.
 *
 * \param   baseAddr        Base Address of the TESOC Registers.
 * \param   diagnosticLog   Pointer to 2D integer array size 16x4 to store
 *                          TESOC test diagnostic log(as TESOC dumps 16 cycles
 *                          of 128 bit data on test failure).
 *
 * \return  status          Whether TESOC diagnostic log read correctly.
 *                          STW_SOK   : Success
 *                          STW_EFAIL : Failure.
 */
int32_t TESOCReadDiagnosticLog(uint32_t         baseAddr,
                               uint32_t *const *diagnosticLog);

/**
 * \brief   This function enables specified TESOC interrupts
 *
 * \param   baseAddr       Base Address of the TESOC registers.
 * \param   intrMask       Mask value for the interrupts to be enabled.
 *                         Supported values are given by the enum
 *                         TESOCIntrFlag_t.
 *
 * \return  None
 */
void TESOCIntrEnable(uint32_t baseAddr, uint32_t intrMask);

/**
 * \brief   This function disables specified TESOC interrupts
 *
 * \param   baseAddr   Base Address of the TESOC registers.
 * \param   intrMask   Mask value for the interrupts to be disabled.
 *                     Supported values are given by enum
 *                     TESOCIntrFlag_t.
 *
 * \return  None
 */
void TESOCIntrDisable(uint32_t baseAddr, uint32_t intrMask);

/**
 * \brief   This function gets the status of enabled interrupts.
 *          - It returns 32 bit integer with bits specifying whether
 *            an interrupt is enabled or disabled.
 *          - Returned value can be masked with the values in enum
 *            TESOCIntrFlag_t to check the required interrupt status.
 *
 * \param   baseAddr   Base Address of the TESOC registers.
 *
 * \return  status     All the enabled interrupts.
 */
uint32_t TESOCGetIntrEnable(uint32_t baseAddr);

/**
 * \brief   This function returns the status of interrupts.
 *          - It specifies whether an interrupt is active or inactive.
 *          - After an interrupt is serviced, the software must set to 0
 *            the corresponding flag in the interrupt status register.
 *          - Returned value can be masked with the values in enum
 *            TESOCIntrFlag_t to check the required interrupt status.
 *
 * \param   baseAddr   Base Address of the TESOC registers.
 *
 * \return  status     All the active interrupt status.
 */
uint32_t TESOCGetIntrStatus(uint32_t baseAddr);

/**
 * \brief   This Function clears the status of specified interrupts.
 *
 * \param   baseAddr   Base Address of the TESOC registers.
 * \param   intrMask   Mask value for the interrupts to be cleared
 *                     given by enum - TESOCIntrFlag_t.
 *
 * \return  None
 */
void TESOCIntrClear(uint32_t baseAddr, uint32_t intrMask);

/**
 * \brief   This function returns the raw status of interrupts.
 *          Returned value can be masked with the values in enum
 *            TESOCIntrFlag_t to check the required interrupt status.
 *
 * \param   baseAddr   Base Address of the TESOC registers.
 *
 * \return  status     All the raw interrupt status.
 */
uint32_t TESOCGetIntrRawStatus(uint32_t baseAddr);

/**
 * \brief   Unlock access to TESOC registers by writing unlock pattern
 *          to TESOC lock register.
 *
 * \param   baseAddr        Base Address of the TESOC Registers.
 *
 * \return  None
 */
void TESOCUnlockMMR(uint32_t baseAddr);

/**
 * \brief   Lock access to TESOC registers by writing lock pattern
 *          to TESOC lock register.
 *
 * \param   baseAddr        Base Address of the TESOC Registers.
 *
 * \return  None
 */
void TESOCLockMMR(uint32_t baseAddr);

#ifdef __cplusplus
}

#endif /*extern "C" */

#endif
 /** @} */
