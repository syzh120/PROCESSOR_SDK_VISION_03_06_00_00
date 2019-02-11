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
 *  \defgroup DIAG_CRC CRC Diag Lib
 *
 *  @{
 */
/**
 *  \file     diagLib_crc.h
 *
 *  \brief    This file contains the prototypes of the APIs present in the
 *            software test library file of CRC.
 *            This also contains some related macros.
 *
 * ==================================================================== */

#ifndef DIAGLIB_CRC_H_
#define DIAGLIB_CRC_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <ti/csl/csl_crc.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/* ========================================================================== */
/*                         Global Variables Declarations                      */
/* ========================================================================== */
/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */
/**
 * \brief  Enum to select the mode to check CRC compression.
 */
typedef enum DiagLib_CrcCheckMode
{
    DIAGLIB_CRC_INTERRUPT_MODE = 0,
    /**< Select interrupt mode for CRC */
    DIAGLIB_CRC_POLLED_MODE
    /**< Select polled mode for CRC */
}DiagLib_CrcCheckMode_t;

/**
 * \brief  Enum to select the type CRC comparision.
 */
typedef enum DiagLib_CrcTestType
{
    DIAGLIB_CRC_TEST_INBUILT = 0,
    /**< Select inbuit CRC test to compare the crc value with golden crc
     * User need not provide any input test data */
    DIAGLIB_CRC_TEST_USER,
    /**< Select user CRC test for comparision of c-mode value and hw crc
     * vlaue for the given user input */
    DIAGLIB_CRC_TEST_GET_CRC
    /**< Select CRC test none for only getting the CRC values from HW or
     * c-model without any comparision */
}DiagLib_CrcTestType_t;

/**
 * \brief  Enum to represent the state of the test.
 */
typedef enum DiagLib_CrcTestStates
{
    DIAGLIB_CRC_TEST_TIMEOUT = -((int32_t) 4),
    /**< The test has timedout */
    DIAGLIB_CRC_TEST_INVALID_PARAMS = -((int32_t) 3),
    /**< The test has failed due to invalid parameters*/
    DIAGLIB_CRC_TEST_BADARGS = -((int32_t) 2),
    /**< The test has failed due to bad arguments */
    DIAGLIB_CRC_TEST_FAIL = -((int32_t) 1),
    /**< The test has failed in atleast one iteration */
    DIAGLIB_CRC_TEST_PASS = 0,
    /**< The test has passed in all iterations till now */
    DIAGLIB_CRC_TEST_PENDING = 1
    /**< The test is still running an iteration */
}DiagLib_CrcTestStates_t;

/**
 * \brief  Enum to select the bit width
 */
typedef enum DiagLib_CrcBitSize
{
    DIAGLIB_CRC_BIT_64 = 0,
    /**< Select 64 bit mode for CRC */
    DIAGLIB_CRC_BIT_32
    /**< Select 32 bit mode for CRC */
}DiagLib_CrcBitSize_t;

/**
 * \brief  Structure containing input parameters for CRC software test.
 */
typedef struct DiagLib_CrcTestParams
{
    uint32_t  baseAddr;
    /**< Base address of the CRC module
     */
    uint32_t  mode;
    /**< Mode of operation of CRC.
     * Refer crcOperationMode_t
     */
    uint32_t  chNumber;
    /**< CRC Channel number used for testing.
     *  Refer enum crcChannel_t.
     */
    uint32_t  dataSize;
    /**< Size of the data in bytes for which CRC has to be calculated.
     * Datasize should be multiple of 64-bits for SemiCPU mode
     * i.e. divisible by DIAGLIB_CRC_PATTERN_SIZE_64_BIT.
     */
    uint32_t *testData;
    /**< Pointer to the data to be tested in #DIAGLIB_CRC_TEST_USER.
     * The address should be 32bit aligned.
     * This value need not be populated for inbuilt test.
     */
    uint32_t  testType;
    /**< Number of iterations of CRC compression.
     *  Refer enum #DiagLib_CrcTestType_t.
     */
    uint32_t  bitSize;
    /**< Input Data width can be 32-bit or 64-bit.
     *  Refer enum #DiagLib_CrcBitSize_t.
     */
    uint32_t  crcCheckMode;
    /**< Interrupt or Polled mode to check CRC compression complete
     *  Refer enum #DiagLib_CrcCheckMode_t.
     */
    uint32_t  timeout;
    /**< Choose the timeout value within which polling has to be completed
     * failing which test API returns with a failure.
     * Value to be given in milli seconds.
     */
    /**
     * EDMA params are required for writing 64 bits of data at once.
     * This is because CRC is calculated for 64 bit data.
     * Otherwise CRC value would change if 32bits are written.
     * EDMA is not used in Full CPU mode or 32 bit data size.
     */
    uint32_t crcEdmaChNum;
    /**< Channel number for EDMA transfer.
     */
    uint32_t crcEdmaEvtqNum;
    /**< Event queue number for EDMA transfer.
     */
    uint32_t crcEdmaTccNum;
    /**< Channel number on which EDMA transfer completion interrupt is generated
     */
}DiagLib_CrcTestParams_t;

/**
 * \brief  Structure containing output parameters for CRC software test.
 */
typedef struct DiagLib_CrcOutParams
{
    crcSignature_t crcData;
    /**< Structure containing the C-model CRC value.
     */
}DiagLib_CrcOutParams_t;

/**
 * \brief   Structure containing intermediate parameters and final test result.
 *          This is purely readonly for the user.
 *          User should declare this structure and give it to
 *          the lib. User should not modify this.
 */
typedef struct DiagLib_CrcObj
{
    uint32_t        remDataSize;
    /**< Excess Datasize left out after edma transfer.
     */
    const uint32_t *curSrcAddr;
    /**< Current source address from where the data transfer has to start.
     */
    int32_t         testState;
    /**< Intermediate result used to update final test result.
     * Refer enum #DiagLib_CrcTestStates_t.
     */
    uint32_t        crcSW_l;
    /**< CRC RegL value from C-model
     */
    uint32_t        crcSW_h;
    /**< CRC RegH value from C-model
     */
}DiagLib_CrcObj_t;
/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 * \brief   This API is used for initializing CRC test params to default.
 *          This API has to be called from app before starting the test.
 *
 * \param   testParams      Pointer to structure #DiagLib_CrcTestParams_t.
 *                          Populated with all the default values required for
 *                          testing of CRC functionality.
 *
 * \return  None.
 */
void DiagLibCrcTestParams_init(DiagLib_CrcTestParams_t *testParams);
/**
 * \brief   This API is used for software CRC calculation using C-model.
 *
 * \param   testParams      Pointer to structure #DiagLib_CrcTestParams_t.
 * \param   outParams       Pointer to structure #DiagLib_CrcOutParams_t.
 * \param   crcObj          Pointer to structure #DiagLib_CrcObj_t.
 *
 * \return  status          Run status.
 */
int32_t DiagLib_crcCalculateSW(const DiagLib_CrcTestParams_t *testParams,
                               DiagLib_CrcOutParams_t        *outParams,
                               DiagLib_CrcObj_t              *crcObj);
/**
 * \brief   This API is used for CRC calculation using hardware CRC IP.
 *
 * \param   testParams      Pointer to structure #DiagLib_CrcTestParams_t.
 * \param   outParams       Pointer to structure #DiagLib_CrcOutParams_t.
 * \param   crcObj          Pointer to structure #DiagLib_CrcObj_t.
 *
 * \return  status          Run status.
 */
int32_t DiagLib_crcCalculateHW(const DiagLib_CrcTestParams_t *testParams,
                               DiagLib_CrcOutParams_t        *outParams,
                               DiagLib_CrcObj_t              *crcObj);
/**
 * \brief   This API is used for CRC software test.
 *          It sets all parameters issued by the app and start CRC compression.
 *
 * \param   testParams      Pointer to structure #DiagLib_CrcTestParams_t.
 * \param   outParams       Pointer to structure #DiagLib_CrcOutParams_t.
 * \param   crcObj          Pointer to structure #DiagLib_CrcObj_t.
 *
 * \return  status          Test status.
 */
int32_t DiagLib_crcStartTest(const DiagLib_CrcTestParams_t *testParams,
                             DiagLib_CrcOutParams_t        *outParams,
                             DiagLib_CrcObj_t              *crcObj);
/**
 * \brief   This API is used for CRC software test for handling ISR.
 *          It sets all parameters issued by the app and start CRC compression.
 *
 * \param   testParams      Pointer to structure #DiagLib_CrcTestParams_t.
 * \param   outParams       Pointer to structure #DiagLib_CrcOutParams_t.
 * \param   crcObj          Pointer to structure #DiagLib_CrcObj_t.
 *
 * \return  status          ISR check status.
 */
int32_t DiagLib_crcISR(const DiagLib_CrcTestParams_t *testParams,
                       DiagLib_CrcOutParams_t        *outParams,
                       DiagLib_CrcObj_t              *crcObj);

#ifdef __cplusplus
}

#endif /*extern "C" */

#endif
/* @} */
