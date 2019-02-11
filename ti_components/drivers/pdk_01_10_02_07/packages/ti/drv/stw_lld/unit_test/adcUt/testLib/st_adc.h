/*
 *  Copyright (C) 2014 Texas Instruments Incorporated
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
 *  \file st_adc.h
 *
 *  \brief This file contains all the structures, macros, enums
 *  used by the ADC UT applications.
 */

#ifndef STW_ADC_H_
#define STW_ADC_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <stdio.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/tistdtypes.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/cslr_adc.h>
#include <ti/csl/csl_adc.h>
#include <ti/csl/csl_edma.h>
#include <ti/diag/diagLib_adc.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */
/* Application name string used in print statements. */
#define APP_NAME                        "STW_ADC"
#define TEST_ENABLE                     (TRUE)
#define TEST_DISABLE                    (FALSE)
#define PRINT_ENABLE                    (TRUE)
#define PRINT_DISABLE                   (FALSE)

/*      Default values      */
#define DEF_ADC_MODULE                  ((uint32_t) SOC_TSC_ADC_BASE)
#define DEF_ADC_MODE                    ((uint32_t) \
                                         ADC_OPERATION_MODE_SINGLE_SHOT)

#define MAX_ARG_LEN                     (30)

/* ADC reference volatege in mV */
#define ADC_REFERENCE_VOLTAGE_MV            ((uint32_t) 1800)

/** Volatage Levels given to ADC module
 *  These levels will be used to compare against converted values for PASS/FAIL
 *  Criteria
 */
#define ADC_CHANNEL_1_VOLTAGE_MV            (0U)
#define ADC_CHANNEL_2_VOLTAGE_MV            (0U)
#define ADC_CHANNEL_3_VOLTAGE_MV            (680U)
#define ADC_CHANNEL_4_VOLTAGE_MV            (605U)
#define ADC_CHANNEL_5_VOLTAGE_MV            (534U)
#define ADC_CHANNEL_6_VOLTAGE_MV            (424U)
#define ADC_CHANNEL_7_VOLTAGE_MV            (350U)
#define ADC_CHANNEL_8_VOLTAGE_MV            (0U)

/* ADC error offset in mV */
#define ADC_VOLTAGE_ERR_OFFSET_MV      (50U)

/* Time-out value for AutoRun */
#define ADC_APP_UART_TIMEOUT_MSEC              (5000U)
/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */
typedef enum
{
    IPU = 0,
    /**< Select IPU core0/core1 for execution */
    DSP1 = 1,
    /**< Select DSP 1 for execution */
    DSP2 = 2,
    /**< Select DSP 2 for execution */
    EVE = 3
          /**< Select EVE for execution */
}cpuID_t;

/**
 *  \brief Test types.
 */
typedef enum
{
    ST_TT_SANITY      = 0x01,
    ST_TT_REGRESSION  = 0x02,
    ST_TT_FULL        = 0x04,
    ST_TT_FUNCTIONAL  = 0x08,
    ST_TT_STRESS      = 0x10,
    ST_TT_NEGATIVE    = 0x20,
    ST_TT_PERFORMANCE = 0x40,
    ST_TT_MISC        = 0x80,
    ST_TT_API         = 0x100
} st_TestType;

/**
 *  \brief ADC indication path interrupt/adc_error pin.
 */
typedef enum
{
    ADC_OUT_ERROR_LOW_INTR  = 0x1U,
    ADC_OUT_ERROR_HIGH_INTR = 0x2U,
    ADC_OUT_ERROR_ERR_PIN   = 0x4U
} st_ADCOutError;

/* Forward Declarations */
typedef struct st_ADCTestcaseParams st_ADCTestcaseParams_t;

/**
 * \brief Typedef for test case type function pointer.
 */
typedef void (*adcTestCaseFxnPtr)(st_ADCTestcaseParams_t *testPrms);
/**
 *  \brief ADC configuration parameter structure.
 */
typedef struct
{
    uint32_t adcModule;
    /**< ADC module instance. */
    uint32_t adcMode;
    /**< ADC operational mode. */
    uint32_t intrEnable;
    /**< Interrupts to enable.*/
    uint32_t adcSteps[17][8];
    /**< Step to configure.
     *   First element indicates number of steps to be enabled for conversion.
     *   adcSteps[ID][i/p
     ****Channel][FIFO][Avg][mode][RangeChk][OpenDelay][SampleDelay]
     */
    uint32_t fifo[2][3];
    /**< FIFO configuration.
     *   fifo[Enable/disable][CPU threshold][DMA req threshold]
     */
    uint32_t highRange;
    /**< Upper limit for conversion. */
    uint32_t lowRange;
    /**< Lower limit for conversion. */
    uint32_t stepIdTagEnable;
    /**< Enable/disable step ID tagging. */
} stw_ADCConfigParams_t;

/**
 *  \brief Test case parameter structure.
 */
struct st_ADCTestcaseParams
{
    Bool                       enableTest;
    /**< Whether test case should be executed or not. */
    uint32_t                   testcaseId;
    /**< Test case ID. */
    adcTestCaseFxnPtr          testCaseFxnPtr;
    /**< Type of test case to run. */
    char                      *reqId;
    /**< Requirements covered by this test case. */
    char                      *testCaseName;
    /**< Test case name. */
    char                      *userInfo;
    /**< Test case user Info. */
    char                      *disableReason;
    /**< Reason string for disabling a test case. */
    char                      *passFailCriteria;
    /**< Test case pass/fail criteria. */
    cpuID_t                    cpuID;
    /**< Specify core on which test case is running. */
    stw_ADCConfigParams_t      adcConfigParams;
    /**< ADC configuration parameters Refer struct #stw_ADCConfigParams_t. */
    DiagLib_AdcStartupParams_t diagLibStartupParams;
    /**< Diaglib ADC startup parameters structure */
    DiagLib_AdcTestParams_t    diagLibTestParams;
    /**< Diaglib ADC test parameters structure */
    Bool                       printEnable;
    /**< Enable/disable print statements, used for stress testing. */
    uint32_t                   testType;
    /**< Type of test  - like BFT, stress etc... */

    /*
     * Below variables are initialized in code and not in table!!
     */
    int32_t                    isRun;
    /**< Flag to indicate whether the test case is run or not. */
    Int32                      testResult;
    /**< Test result. */
};
/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 * ADC Test Case Functions
 */
/**
 * \brief   Fetch testcase data and run the testcase.
 *
 * \param   testParams        structure to details of testcase to run.
 *
 * \return  None
 */
void DiagLibAdcTest_main(st_ADCTestcaseParams_t *testPrms);
/**
 * \brief   Fetch testcase data and run the testcase.
 *
 * \param   testParams        structure to details of testcase to run.
 *
 * \return  None
 */
void adcRunTestcase(st_ADCTestcaseParams_t *testParams);

/**
 * \brief   This API will return extected voltage in mV for given channel.
 *
 * \param   channelId       Channel ID for ADC module.
 *
 * \retval  voltLvl         Expected voltage level in mV.
 */
uint32_t ADCGetExpectedVol(uint32_t channelId);

#ifdef __cplusplus
}

#endif /*extern "C" */

#endif
