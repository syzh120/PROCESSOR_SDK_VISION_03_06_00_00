/*
 *  Copyright (C) 2016 Texas Instruments Incorporated
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
 *  \file st_adcDiagLibTests.c
 *
 *  \brief Common across test-cases with DiagLib.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <ti/csl/tistdtypes.h>
#include <ti/csl/soc.h>
#include <ti/csl/soc.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/drv/stw_lld/platform/irq_xbar.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/csl/hw_types.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <st_adc.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define APP_ADC_INT                     (34U)
#define XBAR_CPU                        (CPU_IPU1)
#define XBAR_INST                       (XBAR_INST_IPU1_IRQ_34)
#define XBAR_INTR_SOURCE                (TSC_ADC_IRQ_GENINT)
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
static DiagLib_AdcTestParams_t      *gAdcTestParams;
static DiagLib_AdcTestResultParams_t gAdcOutParams[DIAGLIB_ADC_MAX_NUM_CH];
static DiagLib_AdcObj_t gAdcObj;
static volatile int32_t gTestStatus;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 * \brief   This Interrupt Service Routine for ADC interrupt.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void AdcISR(void *handle);
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void DiagLibAdcTest_main(st_ADCTestcaseParams_t *testPrms)
{
    int32_t  configStatus;
    uint32_t i, expectedVolmV, voltLvl, failCount = 0U;

    /* Enable ADC module */
    configStatus = PMHALModuleModeSet(PMHAL_PRCM_MOD_ADC,
                                      PMHAL_PRCM_MODULE_MODE_ENABLED,
                                      PM_TIMEOUT_INFINITE);
    if (PM_SUCCESS != configStatus)
    {
        printf("Error in ADC module enable.\n");
    }
    if (STW_SOK == configStatus)
    {
        configStatus = DiagLib_adcStartup(&testPrms->diagLibStartupParams);
        if (STW_SOK != configStatus)
        {
            printf("Error in ADC divider configuration.\n");
        }
        else
        {
            gAdcTestParams = &testPrms->diagLibTestParams;
        }
    }

    /* XBar configuration */
    if (gAdcTestParams->transferMode == DIAGLIB_ADC_INTERRUPT_MODE)
    {
        if (irq_xbar_success ==
            IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                           XBAR_CPU, XBAR_INST,
                           XBAR_INTR_SOURCE))
        {
            /* Enable Error interrupt for ADC */
            Intc_Init();
            Intc_IntEnable(0);
            /* Register ISR */
            Intc_IntRegister(APP_ADC_INT,
                             (IntrFuncPtr) AdcISR, 0);
            Intc_IntPrioritySet(APP_ADC_INT, (uint16_t) 1, (uint8_t) 0);
            Intc_SystemEnable(APP_ADC_INT);
        }
        else
        {
            printf("Error in configuring CrossBar.\n");
        }
    }

    if (STW_SOK == configStatus)
    {
        gTestStatus = DiagLib_adcStartTest(gAdcTestParams, gAdcOutParams,
                                           (DiagLib_AdcObj_t *) &gAdcObj);

        while (DIAGLIB_ADC_TEST_PENDING == gTestStatus)
        {}

        if (gAdcTestParams->testType == DIAGLIB_ADC_TEST_CONV)
        {
            printf("The ADC values converted into mV are :\n");
            for (i = 0; i < gAdcTestParams->numCh; i++)
            {
                printf("Channel %d \t Data:%dmV\n",
                       gAdcOutParams[i].channel, gAdcOutParams[i].outVltg);
                expectedVolmV = ADCGetExpectedVol(gAdcOutParams[i].channel);
                voltLvl       = gAdcOutParams[i].outVltg;
                if ((voltLvl <= (expectedVolmV + ADC_VOLTAGE_ERR_OFFSET_MV)) &&
                    (voltLvl >= (expectedVolmV - ADC_VOLTAGE_ERR_OFFSET_MV)))
                {
                    testPrms->testResult = STW_SOK;
                }
                else
                {
                    failCount++;
                }
            }
            if (failCount > 0U)
            {
                testPrms->testResult = STW_EFAIL;
            }
            else
            {
                testPrms->testResult = STW_SOK;
            }
        }

        if (gAdcTestParams->testType == DIAGLIB_ADC_TEST_OVERRUN)
        {
            if (DIAGLIB_ADC_TEST_PASS == gTestStatus)
            {
                testPrms->testResult = STW_SOK;
            }
            else
            {
                testPrms->testResult = STW_EFAIL;
            }
        }
    }
    else
    {
        testPrms->testResult = STW_EFAIL;
    }

    configStatus = PMHALModuleModeSet(PMHAL_PRCM_MOD_ADC,
                                      PMHAL_PRCM_MODULE_MODE_DISABLED,
                                      PM_TIMEOUT_INFINITE);
    if (PM_SUCCESS != configStatus)
    {
        printf("Error in ADC module disable.\n");
    }

    /* Disable the interrupt */
    Intc_SystemDisable(APP_ADC_INT);

    /* Unregister the interrupt */
    Intc_IntUnregister(APP_ADC_INT);

    Intc_IntDisable();

    testPrms->isRun = STW_SOK;
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */
static void AdcISR(void *handle)
{
    gTestStatus = DiagLib_adcProcISR(gAdcTestParams, gAdcOutParams, &gAdcObj);
}

