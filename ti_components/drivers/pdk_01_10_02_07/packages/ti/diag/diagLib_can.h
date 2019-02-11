/*
 *  Copyright (C) 2016 Texas Instruments Incorporated - www.ti.com/
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
 *  \defgroup DIAG_CAN CAN Diag Lib
 *
 *  @{
 */
/**
 *  \file     diagLib_can.h
 *
 *  \brief    This file contains the prototypes of the APIs present in the
 *            software test library file of CAN.
 *            This also contains some related macros.
 *
 * ==================================================================== */

#ifndef DIAGLIB_CAN_H_
#define DIAGLIB_CAN_H_

/*==========================================================================*/
/*                            Include Files                                 */
/*==========================================================================*/

#include <ti/csl/csl_types.h>
#include <ti/csl/csl_dcan.h>

#ifdef __cplusplus
extern "C" {
#endif

/*==========================================================================*/
/*                          Macros & Typedefs                               */
/*==========================================================================*/

/**
 * \brief Default CAN clock frequency
 */
#define  DIAGLIB_CAN_DEFAULT_CLK_FREQ            (20000000U)
/**
 * \brief Default CAN bit rate
 */
#define  DIAGLIB_CAN_DEFAULT_BIT_RATE            (1000000U)
/**
 * \brief Default CAN Propagation Delay
 */
#define DIAGLIB_CAN_DEFAULT_PROP_DELAY           (700U)
/**
 * \brief Default CAN Sampling Point (%)
 */
#define DIAGLIB_CAN_DEFAULT_SAMP_PT              (70U)

/*==========================================================================*/
/*                        Global Variables Declarations                     */
/*==========================================================================*/

/* None */

/*==========================================================================*/
/*                        Structures and Enums                              */
/*==========================================================================*/

/**
 * \brief  Enum to represent return types for CAN diaglib.
 */
typedef enum DiagLib_CanReturnTypes
{
    DIAGLIB_CAN_DATA_MISMATCH = -((int32_t) 16),
    /**< Data mismatch error */
    DIAGLIB_CAN_TEST_TIMEOUT = STW_ETIMEOUT,
    /**< The test has timedout */
    DIAGLIB_CAN_TEST_INVALID_PARAMS = STW_EINVALID_PARAMS,
    /**< The test has failed due to invalid parameters*/
    DIAGLIB_CAN_TEST_BADARGS = STW_EBADARGS,
    /**< The test has failed due to bad arguments */
    DIAGLIB_CAN_TEST_FAIL = STW_EFAIL,
    /**< The test has failed in atleast one iteration */
    DIAGLIB_CAN_TEST_OK = STW_SOK,
    /**< The test has passed in all iterations till now */
    DIAGLIB_CAN_TEST_PENDING = 1,
    /**< The test is still running an iteration */
    DIAGLIB_CAN_PARITY_DBE_ISR_RECEIVED = 0x10,
    /**< Double bit parity error event received */
    DIAGLIB_CAN_PARITY_SBE_ISR_RECEIVED = 0x20,
    /**< Single bit parity error event received */
    DIAGLIB_CAN_LOOPBACK_VERIFIED = 0x40,
    /**< Loopback test verified event received */
}DiagLib_CanReturnTypes_t;

/**
 * \brief  Enum to select type of test for CAN.
 */
typedef enum DiagLib_CanTestTypes
{
    DIAGLIB_CAN_TEST_INT_LOOPBACK,
    /**< The test type internal loop-back */
    DIAGLIB_CAN_TEST_EXT_LOOPBACK,
    /**< The test type external loop-back */
    DIAGLIB_CAN_PARITY_ECC_TEST,
    /**< The test type Parity */
}DiagLib_CanTestType_t;

/**
 * \brief  Structure containing configuration parameters for DCAN module.
 */
typedef struct DiagLib_DcanTestParams
{
    dcanCfgParams_t       canCfgPrm;
    /**< structure for CAN generic configuration parameters.
     */
    dcanMsgObjCfgParams_t canTxCfgPrms;
    /**< structure for CAN TX configuration parameters.
     */
    dcanMsgObjCfgParams_t canRxCfgPrms;
    /**< structure for can RX configuration parameters.
     */
    dcanTxParams_t        canTxPrms;
    /**< Structure holding TX transfer parameters of DCAN module.
     */
    dcanRxParams_t        canRxPrms[2];
    /**< Structure holding RX transfer parameters of DCAN module
     * used for the parity test.
     */
}DiagLib_DcanParams_t;

/**
 * \brief  Structure containing input parameters for CAN test.
 */
typedef struct DiagLib_CanTestParam
{
    uint32_t             canModule;
    /**< Module to be tested DiagLib_CanTestModule_t.
     */
    uint32_t             testType;
    /**< Test type for CAN module #DiagLib_CanTestType_t.
     */
    uint32_t             canBase;
    /**< Can base used for the testing
     *  This value will be initialized based on the test type.
     */
    uint32_t             clkFrequency;
    /**< CAN module input clock frequency
     */
    uint32_t             bitRate;
    /**< CAN module output bit rate
     */
    uint32_t             propDelay;
    /**< CAN propagation delay
     */
    uint32_t             samplingPt;
    /**< CAN sampling point
     */
    uint32_t             timeout;
    /**< Choose the time out value within which polling has to be completed
     * failing which test API returns with a failure.
     * Value to be given in milli seconds.
     */
    DiagLib_DcanParams_t dcanPrm;
    /**< Test parameter configuration for the CAN module used.
     */

    /* New structure for MCAN can be added here */
}DiagLib_CanTestParam_t;

/*==========================================================================*/
/*                         Function Declarations                            */
/*==========================================================================*/
/**
 * \brief   This API is used for initializing Can test parameters to default.
 *          This API has to be called from application before starting the
 *          test.
 *
 * \param   testPrm         Pointer to structure #DiagLib_CanTestParam_t.
 *
 * \return  None.
 *
 * \note    parameters 'canModule' and 'testType' of structure
 *          #DiagLib_CanTestParam_t must be initialized before calling this API.
 */
int32_t DiagLib_canTestParamsInit(DiagLib_CanTestParam_t *testPrm);

/**
 * \brief   This API is used for CAN internal loop-back/parity test.
 *
 * \param   testPrm         Pointer to structure #DiagLib_CanTestParam_t.
 *
 * \return status           Test run status.
 *
 * \note   For parity test a single bit error is introduced and
 *         corrected data is verified.
 */
int32_t DiagLib_canStartTest(DiagLib_CanTestParam_t *testPrm);

/**
 * \brief   This API has to be called from application's interrupt handler.
 *
 * \param   testPrm         Pointer to structure #DiagLib_CanTestParam_t.
 *
 * \return status           ISR check status.
 */
int32_t DiagLib_canISR(const DiagLib_CanTestParam_t *testPrm);

/**
 * \brief   This API is used to verify the received data for the parity test
 *          used only for tda3xx.
 *
 * \param   testPrm         Pointer to structure #DiagLib_CanTestParam_t.
 *
 * \return status           Data check status.
 */
int32_t DiagLib_canParityVerifyData(const DiagLib_CanTestParam_t *testPrm);
#ifdef __cplusplus
}

#endif /*extern "C" */

#endif
/* @} */
