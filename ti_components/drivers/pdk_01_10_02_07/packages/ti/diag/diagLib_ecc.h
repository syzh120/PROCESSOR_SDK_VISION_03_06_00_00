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
 *  \defgroup DIAG_ECC ECC Diag Lib
 *
 *  @{
 */
/**
 *  \file     diagLib_ecc.h
 *
 *  \brief    This file contains the prototypes of the APIs present in the
 *            software test library file of ECC.
 *            This also contains some related macros.
 *
 * ==================================================================== */

#ifndef DIAGLIB_ECC_H_
#define DIAGLIB_ECC_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <ti/csl/csl_emif.h>
#include <ti/csl/csl_ocmc_ecc.h>
#if defined (SOC_TDA3XX)
#include <ti/csl/arch/csl_arch.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/**
 * \brief  Start address of EMIF memory space. If the start address of EMIF
 *         changes, update here and rebuild.
 */
#define DIAGLIB_EMIF_START_ADDR             (0x80000000U)
/**
 * \brief  Start address of OCMC memory space. If the start address of OCMC
 *         changes, update here and rebuild.
 */
#define DIAGLIB_OCMC_RAM_START_ADDR         (0x40300000U)
/**
 * \brief  Number of 8-bit data to be stored or restored for L2 RAM access.
 */
#define DIAGLIB_ECC_L2RAM_BYTES             (0x08U)
/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */
/**
 * \brief  Enum to select the mode of ECC error check.
 */
typedef enum DiagLib_EccErrCheckMode
{
    DIAGLIB_ECC_INTERRUPT_MODE = 0,
    /**< Select interrupt mode for ECC error notification */
    DIAGLIB_ECC_POLLED_MODE,
    /**< Select polled mode for ECC error notification */
}DiagLib_EccErrCheckMode_t;

/**
 * \brief  Enum to represent the current state of the test.
 */
typedef enum DiagLib_EccTestStates
{
    DIAGLIB_ECC_TEST_TIMEOUT = -((int32_t) 4),
    /**< The test has timed out */
    DIAGLIB_ECC_TEST_INVALID_PARAMS = -((int32_t) 3),
    /**< The test failed due to invalid parameters*/
    DIAGLIB_ECC_TEST_BADARGS = -((int32_t) 2),
    /**< The test failed due to bad arguments */
    DIAGLIB_ECC_TEST_FAIL = -((int32_t) 1),
    /**< The test has failed */
    DIAGLIB_ECC_TEST_PASS = 0,
    /**< The test has passed */
    DIAGLIB_ECC_TEST_PENDING = 1,
    /**< The test is still running */
}DiagLib_EccTestStates_t;
/**
 * \brief  Enum to represent the ECC test type.
 */
typedef enum DiagLib_EccTestType
{
    DIAGLIB_ECC_TEST_EMIF_NON_QUANTA_ALIGN_ADDR = 1U,
    /**< EMIF non-quanta aligned address write error detection test */
    DIAGLIB_ECC_TEST_EMIF_NON_QUANTA_MULTIPLE_BYTE,
    /**< EMIF non-quanta multiple byte write error detection test */
    DIAGLIB_ECC_TEST_EMIF_SEC,
    /**< EMIF single error correction test */
    DIAGLIB_ECC_TEST_EMIF_DED,
    /**< EMIF double error detection test */
    DIAGLIB_ECC_TEST_OCMC_SEC,
    /**< OCMC single error correction test */
    DIAGLIB_ECC_TEST_OCMC_DED,
    /**< OCMC double error detection test */
    DIAGLIB_ECC_TEST_OCMC_ADDR,
    /**< OCMC address error detection test */
    DIAGLIB_ECC_TEST_IPU_L2RAM_SEC,
    /**< IPU L2 ram single bit error correction test */
    DIAGLIB_ECC_TEST_IPU_L2RAM_DED,
    /**< IPU L2 ram double bit error detection test */
    DIAGLIB_ECC_TEST_IPU_L2RAM_CODE,
    /**< IPU L2 ram ECC code error detection test */
    DIAGLIB_ECC_TEST_IPU_L1DATA_SEC,
    /**< IPU L1 unicache single bit error correction test */
    DIAGLIB_ECC_TEST_IPU_L1DATA_DED,
    /**< IPU L1 unicache double bit error detection test */
    DIAGLIB_ECC_TEST_IPU_L1DATA_CODE,
    /**< IPU L1 unicache ECC code error detection test */
    DIAGLIB_ECC_TEST_IPU_L1TAG_SEC,
    /**< IPU L1 Tag single bit error detection test */
    DIAGLIB_ECC_TEST_IPU_L1TAG_DED,
    /**< IPU L1 Tag double bit error detection test */
    DIAGLIB_ECC_TEST_IPU_L1TAG_CODE,
    /**< IPU L1 Tag ECC code error detection test */
    DIAGLIB_ECC_TEST_EMIF_SUB_QUANTA_WRITE,
    /**< EMIF sub quanta address write error detection test */
    DIAGLIB_ECC_TEST_MAX,
    /**< This is the maximum testType value.
     * There should not be any testType beyond this.
     */
}DiagLib_EccTestType_t;
/**
 * \brief  Enum to represent the OCMC controller mode for ecc calculation.
 */
typedef enum DiagLib_EccOcmcModes
{
    DIAGLIB_ECC_OCMC_MODE_RAM_FULL = 0U,
    /**< OCMC Ram full ECC mode */
    DIAGLIB_ECC_OCMC_MODE_RAM_BLOCK,
    /**< OCMC Ram block ECC mode */
}DiagLib_EccOcmcModes_t;

/**
 * \brief  Structure containing input parameters for EMIF ECC software test.
 */
typedef struct DiagLib_EccEmifTestParams
{
    void *eccEmifErrAddr;
    /**< Address of EMIF ECC region where the error can be introduced.
     * Threshold for interrupt to be set to 1.
     */
}DiagLib_EccEmifTestParams_t;

/**
 * \brief  Structure containing input parameters for OCMC ECC software test.
 */
typedef struct DiagLib_EccOcmcTestParams
{
    uint32_t eccOcmcMode;
    /**< OCMC controller mode of operation.
     * Refer enum #DiagLib_EccOcmcModes_t.
     */
    uint32_t eccOcmcRamErrAddr;
    /**< Address of OCMC ECC region where the error can be introduced.
     */
    /**
     * EDMA params are required for writing 128 bits of data at once.
     * This is because ECC is calculated for 128bit data.
     * Otherwise ECC value would change if 32bits are written.
     */
    uint32_t eccOcmcEdmaChNum;
    /**< Channel number for EDMA transfer.
     */
    uint32_t eccOcmcEdmaEvtqNum;
    /**< Event queue number for EDMA transfer.
     */
    uint32_t eccOcmcEdmaTccNum;
    /**< Channel number on which EDMA transfer completion interrupt is generated
     */
}DiagLib_EccOcmcTestParams_t;

/**
 * \brief  Structure containing input parameters for OCMC ECC software test.
 */
typedef struct DiagLib_EccIpuTestParams
{
    uint32_t eccIpuRamErrAddr;
    /**< Address of IPU L1/L2 ECC region where the error can be introduced.
     */
}DiagLib_EccIpuTestParams_t;
/**
 * \brief  Structure containing input parameters for ECC software test.
 */
typedef struct DiagLib_EccTestParams
{
    uint32_t testType;
    /**< Type of ECC to perform.
     * Refer enum #DiagLib_EccTestType_t.
     */
    uint32_t eccErrCheckMode;
    /**< Type of ECC to perform.
     * Refer enum #DiagLib_EccErrCheckMode_t.
     */
    uint32_t timeout;
    /**< Choose the timeout value within which polling has to be completed
     * failing which test API returns with a failure.
     * Value to be given in milli seconds.
     */
    DiagLib_EccEmifTestParams_t emifPrm;
    /**< ECC EMIF test params structure.
     */
    DiagLib_EccOcmcTestParams_t ocmcPrm;
    /**< ECC OCMC test params structure.
     */
    DiagLib_EccIpuTestParams_t ipuPrm;
    /**< ECC IPU L1 & L2 test params structure.
     */
}DiagLib_EccTestParams_t;

/* ========================================================================== */
/*                          Internal Structures                               */
/* ========================================================================== */
/**
 * \brief  Structure containing object parameters updated by the library only.
 */
typedef struct DiagLib_EccObj
{
    emifEccErrInfo_t errInfo;
    /**< Pointer to emif error information of ECC.
     */
    uint32_t eccTestVal;
    /**< Storage for Test Value modified during
     * double errors & code errors tests.
     */
    uint8_t eccL2RamTestVal[DIAGLIB_ECC_L2RAM_BYTES];
    /**< Storage for L2 RAM Test Value modified during double error test.
     */
    int32_t testState;
    /**< Result parameter used to update final test result.
     * Refer enum #DiagLib_EccTestStates_t.
     */
}DiagLib_EccObj_t;
/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 * \brief   This API has to be called from application to initialize ECC
 *          parameters for the ECC ERR check test.
 *
 * \param   initParams      Pointer to structure #DiagLib_EccTestParams_t.
 *
 * \return  None.
 */
void DiagLibEccTestParams_init(DiagLib_EccTestParams_t *initParams);
/**
 * \brief   This API has to be called from application to start
 *          the required ECC test.
 *          Cache is disabled for EMIF ECC error tests to
 *          ensure writes are completed. L1 cache is also
 *          disabled in case of EMIF quanta error tests.
 *
 * \param   testParams      Pointer to structure #DiagLib_EccTestParams_t.
 *                          Populated with the type of test information
 *                          and all the struct pointers required for
 *                          testing of ECC module.
 *
 * \param   eccObj          Pointer to struct #DiagLib_EccObj_t.
 *                          This carries the test result information.
 *
 * \return  status          Test status.
 */
int32_t DiagLib_eccStartTest(const DiagLib_EccTestParams_t *testParams,
                            DiagLib_EccObj_t *eccObj);
/**
 * \brief   This API has to be called from application's interrupt handler.
 *          The interrupt source will be either emif error interrupt
 *          or ocmc error interrupt.
 *          Configuration and enabling of interrupt accordingly has to be done
 *          by the application.
 *
 * \param   testParams      Pointer to structure #DiagLib_EccTestParams_t.
 *                          Populated with the type of test information
 *                          and all the struct pointers required for
 *                          testing of ECC module.
 *
 * \param   eccObj          Pointer to struct #DiagLib_EccObj_t.
 *                          This carries the test result information.
 *
 * \return  status          ISR check status.
 */
int32_t DiagLib_eccISR(const DiagLib_EccTestParams_t *testParams,
                            DiagLib_EccObj_t *eccObj);

#ifdef __cplusplus
}

#endif /*extern "C" */

#endif
/* @} */
