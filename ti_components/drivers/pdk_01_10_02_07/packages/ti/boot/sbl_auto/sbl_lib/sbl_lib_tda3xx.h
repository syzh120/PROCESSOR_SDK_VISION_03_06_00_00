/*
 *  Copyright (C) 2016 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \defgroup SBL_TDA3XX_LIB SBL TDA3xx Lib
 *
 *  @{
 */
/**
 *  \file     sbl_lib_tda3xx.h
 *
 *  \brief    This file contains the interfaces present in the
 *            Secondary Bootloader(SBL) Library valid only for TDA3xx platform.
 *            This also contains some related macros, structures and enums.
 */

#ifndef SBL_LIB_TDA3XX_H_
#define SBL_LIB_TDA3XX_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/csl/csl_tesoc.h>
#include <ti/csl/csl_crc.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 * \brief  This macro contains the maximum number of MPU cores where each
 *         dual core MPU subsystem is counted as two cores.
 */
#define SBLLIB_MAX_MPU_CORES                            ((uint32_t) 0U)

/**
 * \brief  This macro contains the maximum number of M4 cores in the system.
 */
#define SBLLIB_MAX_IPU_CORES                            ((uint32_t) 2U)

/**
 * \brief  This macro contains the maximum number of DSP cores.
 */
#define SBLLIB_MAX_DSP_CORES                            ((uint32_t) 2U)

/**
 * \brief  This macro contains the maximum number of EVE cores.
 */
#define SBLLIB_MAX_EVE_CORES                            ((uint32_t) 1U)

/**
 * \brief  This macro contains the IPU1 Core1's boot address when there is no
 *         App Image for IPU1 Core1.
 */
#define SBLLIB_IPU1_CORE1_BOOT_ADDRESS_NO_IMAGE        ((uint32_t) 0x80000201U)

/**
 * \brief  This macro contains the Address where IPU1 Core1 Entry Point is
 *         written and read.
 */
#define SBLLIB_IPU1_CORE_1_ENTRY_POINT_ADDRESS         ((uint32_t) 0x00300180U)

/**
 * \brief  This macro contains the IPU1's internal RAM base address as accessed
 *         from IPU.
 */
#define SBLLIB_SOC_IPU_RAM_BASE                        ((uint32_t) 0x00000000U)

/**
 * \brief  This typedef contains the prototype of SBL function used for
 *         calculating CRC.
 *
 * \param   srcAddr      Source address of data for which CRC is calculated
 * \param   crcDataSize  Size of the CRC Data
 * \param   crcSignVal   Value of CRC Signature
 *
 * \return  status       Whether CRC is calculated successfully
 *                       STW_SOK   : Success
 *                       STW_EFAIL : Failure
 */
typedef int32_t (*SBLLibCalculateCRCFxn)(const void     *srcAddr,
                                         uint32_t        crcDataSize,
                                         crcSignature_t *crcSignVal);

/**
 * \brief  This typedef contains the prototype of SBL function used for
 *         authenticating RPRC images.
 *
 * \param   rprcAddr      Source address of data RPRC image
 * \param   rprcDataSize  Size of the RPRC image
 *
 * \return  status        Whether RPRC is authenticated
 *                        STW_SOK   : Success
 *                        STW_EFAIL : Failure
 */
typedef int32_t (*SBLLibAuthenticateRPRCFxn)(uint32_t rprcAddr,
                                             uint32_t rprcDataSize);

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 * \brief  Enum to select the Core Id. Each dual core CPU is considered as two
 *         separate cores to get number of individual cores. Dual core CPU is
 *         added as one core in the end.
 */
typedef enum sbllibCoreId
{
    SBLLIB_CORE_ID_MPU_CPU0,
    /**< Core: Cortex A15 CPU0 */
    SBLLIB_CORE_ID_MPU_CPU1,
    /**< Core: Cortex A15 CPU1 */
    SBLLIB_CORE_ID_IPU1_CPU0,
    /**< Core: Cortex M4 (IPU1) CPU0 */
    SBLLIB_CORE_ID_IPU1_CPU1,
    /**< Core: Cortex M4 (IPU1) CPU1 */
    SBLLIB_CORE_ID_IPU2_CPU0,
    /**< Core: Cortex M4 (IPU2) CPU0 */
    SBLLIB_CORE_ID_IPU2_CPU1,
    /**< Core: Cortex M4 (IPU2) CPU1 */
    SBLLIB_CORE_ID_DSP1,
    /**< Core: C66x DSP1 */
    SBLLIB_CORE_ID_DSP2,
    /**< Core: C66x DSP2 */
    SBLLIB_CORE_ID_EVE1,
    /**< Core: EVE1 */
    SBLLIB_CORE_ID_EVE2,
    /**< Core: EVE2 */
    SBLLIB_CORE_ID_EVE3,
    /**< Core: EVE3 */
    SBLLIB_CORE_ID_EVE4,
    /**< Core: EVE4 */
    SBLLIB_CORE_INDIVIDUAL_MAX,
    /**< Enum value for maximum number individual cores */
    SBLLIB_CORE_ID_MPU,
    /**< Core: Dual Cortex A15 */
    SBLLIB_CORE_ID_IPU1,
    /**< Core: Dual Cortex M4 (IPU1) */
    SBLLIB_CORE_ID_IPU2
    /**< Core: Dual Cortex M4 (IPU2) */
} sbllibCoreId_t;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   This function runs the TESOC test for the selected test ID. It
 *          powers down the test module's clock domain and starts the TESOC
 *          test.
 *
 * \param   testId          Test ID for which TESOC test should be run.
 *                          Refer enum tesocTestId_t for values.
 * \param   tesocTestConfig TESOC test configuration.
 *
 * \return  status          Whether TESOC test is configured and started
 *                          correctly.
 *                          STW_SOK         : Success
 *                          STW_EFAIL       : Failure
 *
 * \note    The application should configure TESOC's clock, dividers, etc.
 *          appropriately so that TESOC test runs correctly.
 */
int32_t SBLLibRunTesocTest(uint32_t              testId,
                           const tesocTestCfg_t *tesocTestConfig);

/**
 * \brief   This API checks the result of last run TESOC test. It reads TESOC
 *          registers to get the result value and there is only one set of
 *          registers in TESOC IP. Thus this API is dependent on last run TESOC
 *          test.
 *
 * \param   tesocTestConfig TESOC test configuration.
 *
 * \return  result          TESOC test result.
 *                          STW_SOK         : Test Passed.
 *                          STW_EFAIL       : Test Failed.
 *
 * \note    The test configuration should be exactly same as the one used for
 *          running TESOC test.
 */
int32_t SBLLibCheckTesocTestResult(const tesocTestCfg_t *tesocTestConfig);

/**
 * \brief   This function registers the CRC calculation callback function which
 *          is used for checking integrity of multi-core App image.
 *
 * \param   calculateCRCFxn Function for calculating CRC
 *
 * \return  status       Whether call back function is assigned correctly
 *                       STW_SOK   : Success
 *                       STW_EFAIL : Failure
 */
int32_t SBLLibRegisterCRCCallback(SBLLibCalculateCRCFxn calculateCRCFxn);

/**
 * \brief   This function registers the RPRC authentication callback function
 *          which is used for checking integrity of multi-core App image.
 *
 * \param   authenticateRPRCFxn Function for authenticating(/decrypting) RPRC
 *
 * \return  status       Whether call back function is assigned correctly
 *                       STW_SOK   : Success
 *                       STW_EFAIL : Failure
 */
int32_t SBLLibRegisterAuthenticateRPRCCallback(
    SBLLibAuthenticateRPRCFxn authenticateRPRCFxn);

#ifdef __cplusplus
}

#endif

#endif
/* @} */
