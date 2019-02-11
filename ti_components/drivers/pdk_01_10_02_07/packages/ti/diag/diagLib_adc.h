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
 *  \defgroup DIAG_ADC ADC Diag Lib
 *
 *  @{
 */
/**
 *  \file     diagLib_adc.h
 *
 *  \brief    This file contains the prototypes of the APIs present in the
 *            software test library file of ADC.
 *            This also contains some related macros.
 *
 * ==================================================================== */

#ifndef DIAGLIB_ADC_H_
#define DIAGLIB_ADC_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <ti/csl/csl_adc.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/**
 * \brief   Base address of ADC module
 */
#define DIAGLIB_ADC_MODULE_0          (SOC_TSC_ADC_BASE)
/**
 * \brief   Deafult divider value for ADC clock
 */
#define DIAGLIB_ADC_DIV_DEFAULT             (1000U)
/**
 * \brief   Default Reference voltage for ADC - given in mV
 */
#define DIAGLIB_ADC_REF_VOLTAGE_DEFAULT     (1800U)
/**
 * \brief   Total number steps in ADC module
 */
#define DIAGLIB_ADC_RESLN           (ADC_RESLN_MAX)
/**
 * \brief  Macro defines maximum number of channels tested for ADC conversion
 */
#define DIAGLIB_ADC_MAX_NUM_CH     (ADC_MAX_NUM_CHN)
/**
 * \brief  Deafult number of loops is set to 1.
 */
#define DIAGLIB_ADC_NUMLOOP_DEFAULT     (0x01U)
/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */
/**
 * \brief  Enum to represent the test type.
 */
typedef enum DiagLib_AdcTestType
{
    DIAGLIB_ADC_TEST_CONV = 1U,
    /**< Analog-to-Digital Conversion test */
    DIAGLIB_ADC_TEST_OVERRUN,
    /**< ADC overrun test */
    DIAGLIB_ADC_TEST_MAX,
    /**< This is the maximum testType value.
     * There should not be any testType beyond this.
     */
}DiagLib_AdcTestType_t;
/**
 * \brief  Enum to select the mode of transfer of ADC ouptput.
 */
typedef enum DiagLib_AdcTransferMode
{
    DIAGLIB_ADC_INTERRUPT_MODE = 0,
    /**< Select interrupt mode for ADC data transfer */
    DIAGLIB_ADC_POLLED_MODE,
    /**< Select polled mode for ADC data transfer */
}DiagLib_AdcTransferMode_t;

/**
 * \brief  Enum to represent the current state of the test.
 */
typedef enum DiagLib_AdcTestStates
{
    DIAGLIB_ADC_TEST_TIMEOUT = -((int32_t) 4),
    /**< The test has timedout */
    DIAGLIB_ADC_TEST_INVALID_PARAMS = -((int32_t) 3),
    /**< The test has failed due to invalid parameters*/
    DIAGLIB_ADC_TEST_BADARGS = -((int32_t) 2),
    /**< The test has failed due to bad arguments */
    DIAGLIB_ADC_TEST_FAIL = -((int32_t) 1),
    /**< The test has failed in atleast one iteration */
    DIAGLIB_ADC_TEST_PASS = 0,
    /**< The test has passed in all iterations till now */
    DIAGLIB_ADC_TEST_PENDING = 1,
    /**< The test is still running an iteration */
}DiagLib_AdcTestStates_t;

/**
 * \brief  Structure containing input parameters for ADC software test.
 */
typedef struct DiagLib_AdcStartupParams
{
    uint32_t baseAddr;
    /**< Base address of the ADC module
     */
    uint32_t clkDiv;
    /**< Clock divider value for the ADC module
     */
}DiagLib_AdcStartupParams_t;
/**
 * \brief  Structure containing input parameters for ADC software test.
 */
typedef struct DiagLib_AdcChannelConfig
{
    uint32_t channel;
    /**< Channel number from which input is given.
     *  Refer enum adcChannel_t.
     */
    uint32_t openDelay;
    /**< Delay between driving the inputs and the time
     *  to send the start of conversion signal.
     *  It is number of clock cycles of ADC clock and can take values from 0 to
     *  ADC_OPENDELAY_MAX.
     */
    uint32_t sampleDelay;
    /**< Sampling time/width of the start of conversion signal.
     *  It is number of clock cycles of ADC clock and can take values from 1 to
     *  ADC_SAMPLEDELAY_MAX.
     */
    uint32_t rangeCheckEnable;
    /**< Option to enable range check.
     *   Enabled if it is TRUE
     *   Disabled if it is FALSE.
     */
    uint32_t averaging;
    /**< Option for averaging the sampled data.
     *  Refer enum adcAveraging_t.
     */
    uint32_t expVltg;
    /**< Expected Voltage after conversion.
     *  To be given in milliVolts.
     */
}DiagLib_AdcChannelConfig_t;

/**
 * \brief  Structure containing input parameters for ADC software test.
 */
typedef struct DiagLib_AdcTestParams
{
    uint32_t baseAddr;
    /**< Base address of the ADC module
     */
    uint32_t testType;
    /**< Type of test to perform.
     * Refer enum #DiagLib_AdcTestType_t.
     */
    uint32_t mode;
    /**< Mode of Operation.
     *  Refer enum adcOperationMode_t.
     */
    uint32_t numCh;
    /**< Number of input channels activated.
     */
    DiagLib_AdcChannelConfig_t chCfg[DIAGLIB_ADC_MAX_NUM_CH];
    /**< Channel number from which input is given.
     *  Refer struct adcChannelConfig_t.
     */
    uint32_t fifoNum;
    /**< FIFO to be used to store the data.
     *  Refer enum adcFIFONum_t.
     */
    uint32_t refVltg;
    /**< Reference Voltage required for conversion.
     *  To be given in milliVolts.
     */
    uint32_t vltgDev;
    /**< Accepted Voltage deviation after conversion.
     *  Output voltage can be deviated by +/- vltgDev.
     *  To be given in milliVolts.
     *  By default this is set to 0mV.
     */
    uint32_t lowRange;
    /**< Minimum value expected after conversion.
     */
    uint32_t highRange;
    /**< Maximum value expected after conversion.
     */
    uint32_t numLoop;
    /**< Number of times to perform conversion
     *  before disabling the steps.
     *  Set this value to 1 in case of single shot.
     */
    uint32_t transferMode;
    /**< To choose between interrupt method or polled method.
     *  Refer enum #DiagLib_AdcTransferMode_t.
     */
    uint32_t timeout;
    /**< Choose the timeout value within which polling has to be completed
     * failing which test API returns with a failure.
     * Value to be given in milli seconds.
     */
    uint32_t verifyEnable;
    /**< Set this parameter to TRUE to verify the ADC output with
     *  the expected volatge. If set to FALSE, any failure
     *  in the converted output comparision will not be
     *  reflected in the return.
     */
}DiagLib_AdcTestParams_t;

/**
 * \brief   Structure containing output parameters for ADC software test.
 *          User has to allocate an array of this structure with array length
 *          of number of channels used i.e. numCh.
 */
typedef struct DiagLib_AdcTestResultParams
{
    uint32_t channel;
    /**< Corresponding channel for the output .
     */
    uint32_t outVltg;
    /**< Output Voltage after conversion.
     *  To be given in milliVolts.
     */
    uint32_t verifyFailCnt;
    /**< Number of failures occured in conversion for the corresponding channel.
     */
}DiagLib_AdcTestResultParams_t;

/**
 * \brief   Structure containing intermediate parameters and final test result.
 *          This is purely readonly for the user.
 *          User should declare this structure and give it to
 *          the lib. User should not modify this.
 */
typedef struct DiagLib_AdcObj
{
    uint32_t curLoop;
    /**<Currently running loop number.
     */
    int32_t testState;
    /**<Intermediate result used to update final test result.
     * Refer enum #DiagLib_AdcTestStates_t.
     */
}DiagLib_AdcObj_t;
/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 * \brief   This API is used for initializing ADC startup params to default.
 *          This API has to be called from app before calling DiagLib_adcStartup.
 *
 * \param   startupParams   Pointer to structure #DiagLib_AdcStartupParams_t.
 *                          Populated with the default values required for
 *                          the startup of ADC module.
 *
 * \return  None.
 */
void DiagLibAdcStartupParams_init(DiagLib_AdcStartupParams_t *startupParams);
/**
 * \brief   This API is used for initializing ADC test params to default.
 *          This API has to be called from app before starting the test.
 *
 * \param   testParams      Pointer to structure #DiagLib_AdcTestParams_t.
 *                          Populated with all the default values required for
 *                          testing of ADC module.
 *
 * \return  None.
 */
void DiagLibAdcTestParams_init(DiagLib_AdcTestParams_t *testParams);
/**
 * \brief   This API is used for initializing ADC.
 *          This API has to be called from app before starting the test.
 *
 * \param   startupParams   Pointer to structure #DiagLib_AdcStartupParams_t.
 *                          Populated with baseAddr of ADC module, clk divider.
 *
 * \return  status          Configuration status.
 */
int32_t DiagLib_adcStartup(const DiagLib_AdcStartupParams_t *startupParams);
/**
 * \brief   This API is used for ADC software test.
 *          It sets all parameters issued by the app and start ADC conversion.
 *
 * \param   testParams      Pointer to structure #DiagLib_AdcTestParams_t.
 *                          Populated with channel configuration parameters
 *                          like mode, stepId, channel number, opendelay,
 *                          sampledelay, rangecheck and averaging.
 * \param   outParams       Pointer to structure #DiagLib_AdcTestResultParams_t.
 *                          Output parameters for ADC test.
 * \param   adcObj          Pointer to structure #DiagLib_AdcObj_t.
 *                          Structure containing intermediate parameters and
 *                          final test result.
 *
 * \return  status          Configuration status.
 */
int32_t DiagLib_adcStartTest(const DiagLib_AdcTestParams_t *testParams,
                              DiagLib_AdcTestResultParams_t* outParams,
                              DiagLib_AdcObj_t *adcObj);

/**
 * \brief   This API has to be called from application's interruot handler.
 *          To read the data from ADC after conversion depending
 *          upon the interrupt recieved.
 *
 * \param   testParams      Pointer to structure #DiagLib_AdcTestParams_t.
 *                          Populated with channel configuration parameters
 *                          like mode, stepId, channel number, opendelay,
 *                          sampledelay, rangecheck and averaging.
 * \param   outParams       Pointer to structure #DiagLib_AdcTestResultParams_t.
 *                          Output parameters for ADC test.
 * \param   adcObj          Pointer to structure #DiagLib_AdcObj_t.
 *                          Structure containing intermediate parameters and
 *                          final test result.
 *
 * \return  status          Test result status.
 */
int32_t DiagLib_adcProcISR(const DiagLib_AdcTestParams_t *testParams,
                            DiagLib_AdcTestResultParams_t* outParams,
                            DiagLib_AdcObj_t *adcObj);
/**
 * \brief   This API is used for powering down ADC.
 *          This API has to be called from app after the test is complete.
 *
 * \param   testParams      Pointer to structure #DiagLib_AdcTestParams_t.
 *
 * \return  status          Configuration status.
 */
void DiagLib_adcShutdown(const DiagLib_AdcTestParams_t *testParams);
#ifdef __cplusplus
}

#endif /*extern "C" */

#endif
/* @} */
/**
 * \mainpage  Diagnostics Library
 *
 * \par IMPORTANT NOTE
 *   <b>
 *   The interfaces defined in this package are bound to change.
 *   Release notes/user guide list the additional limitation/restriction
 *   of this module/interfaces.
 *   </b> See also \ref TI_DISCLAIMER.
 *
 *
 * Diagnostics Library(DiagLib) contains APIs for diagnostics of Safety IPs.
 * The DiagLib provides APIs for ADC, CRC, McSPI, DCAN &
 * ECC (EMIF, OCMC & IPU) modules.
 *
 * <b>
 * Also refer to top level user guide for detailed features,
 * limitations and usage description.
 * </b>
 *
 * The DiagLib API can be broadly divided into the following:
 *
 * - <b> Analog to Digital Converter Diagnostics Library(ADC DiagLib)
 * </b> (See \ref DIAG_ADC) <br>
 *  ADC DiagLib provides APIs for ADC test.
 *
 * - <b> Controller Area Network Diagnostics Library(CAN DiagLib)
 * </b> (See \ref DIAG_CAN) <br>
 *  CAN DiagLib provides APIs for DCAN self-test.
 *
 * - <b> Cyclic Redundancy Check Diagnostics Library(CRC DiagLib)
 * </b> (See \ref DIAG_CRC) <br>
 *  CRC DiagLib provides APIs for CRC test.
 *
 * - <b> Error Code Correction Diagnostics Library(ECC DiagLib)
 * </b> (See \ref DIAG_ECC) <br>
 *  ECC DiagLib provides APIs for ECC self-test.
 *
 * - <b> Multichannel Serial Peripheral Interface Diagnostics Library(MCSPI DiagLib)
 * </b> (See \ref DIAG_MCSPI) <br>
 *  ADC DiagLib provides APIs for MCSPI test.
 *
 */

/**
 *  \page  TI_DISCLAIMER  TI Disclaimer
 *
 *  \htmlinclude ti_disclaim.htm
 */
