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
 *  \ingroup STWUTILS_API
 *  \defgroup STWUTILS_APP_API Application helper APIs
 *  @{
 */

/**
 *  \file stwutils_app.h
 *
 *  \brief Header file to use application level helper functions.
 */

#ifndef STWUTILS_APP_H_
#define STWUTILS_APP_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* UART read timeout in msec. */
#define STWUTILS_APP_UART_TIMEOUT_MSEC    (10000U)

/* Magic String for STW App Test Status : Started */
#define STWUTILS_APP_TST_STATUS_INIT      (0x494E4954U)

/* Magic String for STW App Test Status : AppImage not found*/
#define STWUTILS_APP_TST_STATUS_AINF      (0x41494E46U)

#if !(defined (AVV_TEST_AUTO_BUILD))

/* Magic String for STW App Test Status : PASS */
#define STWUTILS_APP_TST_STATUS_PASS      (0x50415353U)

/* Magic String for STW App Test Status : FAIL */
#define STWUTILS_APP_TST_STATUS_FAIL      (0x46417376U)

/* OCMC Address used to store STW App Test Status */
#define STWUTILS_APP_TST_ADDR             (0x4033B100U)

#else

/* Magic String for STW App Test Status : PASS */
#define STWUTILS_APP_TST_STATUS_PASS      (0x50415353U)

/* Magic String for STW App Test Status : FAIL */
#define STWUTILS_APP_TST_STATUS_FAIL      (0x4641494cU)

/* OCMC Address used to store STW App Test Status */
#define STWUTILS_APP_TST_ADDR             (0x4033FC00U)

#endif
/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Starterware Application initialization parameters.
 */
typedef struct stwAppInitParams
{
    uint32_t isI2cInitReq;
    /**< I2c Initialisation is required or not */
    uint32_t isUartInitReq;
    /**< uart Initialisation is required or not */
    uint32_t enablePrintEvmInfo;
    /**< Flag to enable /disable to print EVM details */
} stwAppInitParams_t;

/**
 *  \brief Starterware Application initialization parameters.
 */
typedef struct stwAppDeInitParams
{
    uint32_t isI2cDeInitReq;
    /**< I2c Initialisation is required or not */
} stwAppDeInitParams_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief STW application utils init function.
 *
 *  Init function which initializes global objects.
 *
 *  This function should be called only once after doing all other module
 *  initialization device init and platform init.
 *
 *  \return STW_SOK on success else appropiate error code on failure.
 */
int32_t StwUtils_appInit(void);

/**
 *  \brief STW application utils deinit function.
 *
 *  De-init function
 *
 *  \return STW_SOK on success else appropriate error code on failure.
 */
int32_t StwUtils_appDeInit(void);

/**
 *  \brief STW application utils function to call all the default init
 *  functions.
 *
 *  Note that this function calls the StwUtils_appInit() as well
 *  and hence the application should not call StwUtils_appInit() separately.
 *
 *  \return STW_SOK on success else appropriate error code on failure.
 */
int32_t StwUtils_appDefaultInit(stwAppInitParams_t stwAppInitPrms);

/**
 *  \brief STW application utils function to call all the default de-init
 *  functions.
 *
 *  Note that this function calls the StwUtils_appDeInit() as well
 *  and hence the application should not call StwUtils_appDeInit() separately.
 *
 *  \return STW_SOK on success else appropriate error code on failure.
 */
int32_t StwUtils_appDefaultDeInit(stwAppDeInitParams_t stwAppDeInitPrms);

/**
 *  \brief STW application utils function to print platform and Board Info
 *
 */
void StwUtils_appPrintInfo(void);

/**
 *  \brief STW application utils function for UART Console Intialisation
 *
 * \retval STW_SOK       Success
 * \retval STW_EFAIL     Fail
 */
int32_t StwUtils_appUartModuleInit(uint32_t uartInitReq);

/**
 *  \brief STW application utils function which waits for input for the defined
 *         time
 *
 * \retval STW_SOK       Success
 * \retval STW_EFAIL     Fail
 */
int32_t StwUtils_appGetCharTimeout(int8_t *ch, uint32_t msec);

/**
 *  \brief STW application utils function which waits for input for the defined
 *         time
 *
 * \retval STW_SOK       Success
 * \retval STW_EFAIL     Fail
 */
int32_t StwUtils_appGetNumTimeout(int32_t *num, uint32_t msec);

/**
 * \brief STW application utils function which returns 32K Timer Value
 *
 * \param  Value      Pointer to variable to return count value.
 *
 * \retval STW_SOK       Counter read is successful.
 * \retval STW_EFAIL     Counter read failed.
 */
int32_t StwUtils_appGet32KCounterValue(uint32_t *value);

/**
 * \brief STW application utils function which returns current count value of
 *        32K Timer
 *
 * \param  Value           Current count value is compared to get elapsed count.
 * \param  ElapsedValue    Pointer to variable to return elapsed count value.
 *
 * \retval STW_SOK       Success
 * \retval STW_EFAIL     Fail
 */
int32_t StwUtils_appGetElapsedValue(uint32_t  value,
                                    uint32_t *elapsedValue);

#if defined (__TI_ARM_V7M4__) && (defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX))
/**
 * \brief   This function does the IPU1's default AMMU Configuration for Tda2xx
 *
 */
void StwUtils_appConfigIPU1DefaultAMMU(void);
#endif

/**
 * \brief   This function used to log the test result of Starterware Examples
 *
 * \param  testResult       Status of testResult
 *
 */
void StwUtils_appLogTestResult(uint32_t testResult);

/**
 * \brief   This function makes sure when A15 is halt, 32K Counter is not halted
 *
 */
void StwUtils_appConfig32KCounterSuspendState(void);

/**
 * \brief   This function used to check the test result of Starterware Examples
 *
 * \return    Returns the status of testResult
 */
uint32_t StwUtils_appCheckTestResult(void);

/**
 * \brief   This function used to add a delay of 100mSec
 *
 */
void StwUtils_appWaitForSbl(void);

/**
 *  \brief stwAppInitParams structure init function.
 *
 *  \param initPrms     [IN] Pointer to #stwAppInitParams_t structure.
 *
 */
static inline void StwUtils_appInitParams_init(stwAppInitParams_t *initPrms);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static inline void StwUtils_appInitParams_init(stwAppInitParams_t *initPrms)
{
    if (NULL != initPrms)
    {
        initPrms->isI2cInitReq       = (uint32_t) TRUE;
        initPrms->isUartInitReq      = (uint32_t) TRUE;
        initPrms->enablePrintEvmInfo = (uint32_t) TRUE;
    }

    return;
}

#ifdef __cplusplus
}
#endif

#endif  /* #define STWUTILS_APP_H_ */

/* @} */
