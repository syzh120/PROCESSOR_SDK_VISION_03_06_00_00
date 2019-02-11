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
 *  \defgroup DIAG_MCSPI MCSPI Diag Lib
 *
 *  @{
 */
/**
 *  \file     diagLib_mcspi.h
 *
 *  \brief    This file contains the prototypes of the APIs present in the
 *            software test library file of MCSPI.
 *            This also contains some related macros.
 *
 * ==================================================================== */

#ifndef DIAGLIB_MCSPI_H_
#define DIAGLIB_MCSPI_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <ti/csl/csl_mcspi.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/**
 * \brief  Default MCSPI Out clock in Hz
 */
#define DIAGLIB_MCSPI_DEFAULT_CLK_OUT       (48000000U)
/* ========================================================================== */
/*                         Global Variables Declarations                      */
/* ========================================================================== */
/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */
/**
 * \brief  Enum to select the mode of data transfer in SPI.
 */
typedef enum DiagLib_McspiTransferMode
{
    DIAGLIB_MCSPI_DMA_MODE = 0,
    /**< Select interrupt mode for McSPI */
    DIAGLIB_MCSPI_POLLED_MODE,
    /**< Select polled mode for McSPI */
}DiagLib_McspiTransferMode_t;

/**
 * \brief  Enum to represent the state of the test.
 */
typedef enum DiagLib_McspiTestStates
{
    DIAGLIB_MCSPI_TEST_TIMEOUT = -((int32_t) 4),
    /**< The test has timedout */
    DIAGLIB_MCSPI_TEST_INVALID_PARAMS = -((int32_t) 3),
    /**< The test has failed due to invalid parameters*/
    DIAGLIB_MCSPI_TEST_BADARGS = -((int32_t) 2),
    /**< The test has failed due to bad arguments */
    DIAGLIB_MCSPI_TEST_FAIL = -((int32_t) 1),
    /**< The test has failed in atleast one iteration */
    DIAGLIB_MCSPI_TEST_PASS = 0,
    /**< The test has passed in all iterations till now */
    DIAGLIB_MCSPI_TEST_PENDING = 1,
    /**< The test is still running an iteration */
}DiagLib_McspiTestStates_t;


/**
 * \brief  Structure containing input parameters for MCSPI software test.
 */
typedef struct DiagLib_McspiTestParams
{
    uint32_t baseAddr;
    /**< Base address of the MCSPI module.
     */
    uint32_t chNumber;
    /**< Select the MCSPI channel number.
     */
    uint32_t spiOutClk;
    /**< Select the output clock frequency for MCSPI channel.
     * Value to be given in Hertz.
     */
    uint32_t spiClkMode;
    /**< Select the clock mode for MCSPI channel.
     */
    uint16_t wordLen;
    /**< Select Word length for data transfer.
     * The values supported for MCSPI internal loopback test are
     * 8, 16 & 32 bit only.
     */
    uint32_t transferMode;
    /**< Mode of transfer of data
     *  Refer enum #DiagLib_McspiTransferMode_t.
     */
    uint16_t dataCount;
    /**< Amount of data to be tested in bytes.
     * In case of using DMA transfer mode, dataCount should be multiple of
     * 32bytes.
     */
    uint32_t *txBuffer;
    /**< Transmit buffer pointer.
     * User should allocate reqd memory for transmit buffer and assign here.
     */
    uint32_t *rxBuffer;
    /**< Receive buffer pointer.
     * User should allocate reqd memory for transmit buffer and assign here.
     */
    uint32_t timeout;
    /**< Choose the timeout value within which polling has to be completed
     * failing which test API returns with a failure.
     * Value to be given in milli seconds.
     */
    /**
     * EDMA params are required for data transfer if DMA mode id chosen.
     */
    uint32_t mcspiTxEdmaChNum;
    /**< MCSPI TX Channel number for EDMA transfer.
     */
    uint32_t mcspiRxEdmaChNum;
    /**< MCSPI RX Channel number for EDMA transfer.
     */
    uint32_t mcspiEdmaEvtqNum;
    /**< Event queue number for EDMA transfer.
     */
    uint32_t performCacheOps;
    /**< Set this value to TRUE if the cache is used for SPI transmission.
     * Otherwise, set it to FALSE.
     */
    uint32_t internalLpbk;
    /**< Set this value to TRUE if testing internal loopback.
     * By default, it is set to TRUE by #DiagLibMcspiTestParams_init function.
     */
}DiagLib_McspiTestParams_t;

/**
 * \brief   Structure containing intermediate parameters and final test result.
 *          This is purely readonly for the user.
 *          User should declare this structure and give it to
 *          the lib. User should not modify this.
 */
typedef struct DiagLib_McspiObj
{
    int32_t testState;
    /**< Intermediate result used to update final test result.
     * Refer enum #DiagLib_McspiTestStates_t.
     */
    const uint32_t *txBuffer;
    /**< Transmit buffer, size of the buffer is fixed to 64.
     */
    uint32_t *rxBuffer;
    /**< Receive buffer, size of the buffer is fixed to 64.
     */
}DiagLib_McspiObj_t;
/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 * \brief   This API is used for initializing MCSPI test params to default.
 *          This API has to be called from app before starting the test.
 *
 * \param   testParams      Pointer to structure #DiagLib_McspiTestParams_t.
 *                          Populated with all the default values required for
 *                          testing of MCSPI configuration.
 *
 * \return  None.
 */
void DiagLibMcspiTestParams_init(DiagLib_McspiTestParams_t *testParams);
/**
 * \brief   This API is used for MCSPI internal loopback test.
 *
 * \param   testParams      Pointer to structure #DiagLib_McspiTestParams_t.
 * \param   mcspiObj        Pointer to structure #DiagLib_McspiObj_t.
 *
 * \return status           Test status.
 */
int32_t DiagLib_mcspiStartTest(const DiagLib_McspiTestParams_t *testParams,
                               DiagLib_McspiObj_t *mcspiObj);
/**
 * \brief   This API has to be called from application's interrupt handler.
 *
 * \param   testParams      Pointer to structure #DiagLib_McspiTestParams_t.
 * \param   mcspiObj        Pointer to structure #DiagLib_McspiObj_t.
 *
 * \return status           ISR check status.
 */
int32_t DiagLib_mcspiISR(const DiagLib_McspiTestParams_t *testParams,
                         DiagLib_McspiObj_t *mcspiObj);


#ifdef __cplusplus
}

#endif /*extern "C" */

#endif
/* @} */
