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
 *  \file main.c
 *
 *  \brief TDA2xx Junction Temperature Sensor Application
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/csl_types.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/drv/pm/examples/utils/uartStdio.h>
#include <ti/drv/pm/include/pm_utils.h>
#include <ti/drv/pm/include/pm_types.h>
#include <ti/drv/pm/include/prcm/pmhal_bgap.h>
#include <ti/drv/pm/include/prcm/pmhal_prcm.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define MPU_IRQ_126                      (126U)
/**< \brief MPU IRQ number for Temperature Sensor Interrupt */

#define TIMEOUT_VAL                      (10000U)
/**< \brief Timeout value to wait for event */

#define HOT_EVT_TEMP_THRESH              (10000)
/**< \brief HOT temperature event triggered at 10 degrees Celcius */

#define MAX_HOT_EVT_TEMP_THRESH          (125000)
/**< \brief HOT temperature event triggered at 125 degrees Celcius */

#define COLD_EVT_TEMP_THRESH             (100000)
/**< \brief HOT temperature event triggered at 100 degrees Celcius */

#define MIN_COLD_EVT_TEMP_THRESH         (0)
/**< \brief HOT temperature event triggered at 0 degrees Celcius */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/** \brief  Configure the Temperature Sensor Interrupt.
 */
static void SensorIntcInit(void);

/** \brief  Sensor interrupt service routine. This will disable the Temperature
 *          sensor interrupt.
 */
static void TemperatureSensorIsr(void *handle);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

const char              *voltageDomain_t_names[] =
{
    "PMHAL_PRCM_VD_MPU",
    "PMHAL_PRCM_VD_CORE",
    "PMHAL_PRCM_VD_IVAHD",
    "PMHAL_PRCM_VD_DSPEVE",
    "PMHAL_PRCM_VD_GPU",
};

pmhalPrcmVdId_t          gVoltId         = PMHAL_PRCM_VD_MPU;
static volatile uint8_t  tempEvtOccurred = 0U;

static volatile uint32_t gXbarInst = 121;
int32_t gTestStatus = STW_SOK;
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int main(void)
{
    pmhalBgapRange_t currTempRange = {0, 0};
    int32_t          retVal        = PM_SUCCESS;
    int32_t          timeout       = TIMEOUT_VAL;

    UART_PAD_CONFIG();
    UARTStdioInit();
    UARTPuts("\r\nPM Junction Temperature Measure Test Application", -1);

    PMHALBgapSetMeasureDelay(PMHAL_BGAP_BAND_GAP_1_MS);
    for (gVoltId = PMHAL_PRCM_VD_MPU; gVoltId <= PMHAL_PRCM_VD_GPU; gVoltId++)
    {
        PMHALBgapClearState(gVoltId);
    }

    UARTPuts("\r\n----------------------------------------", -1);
    UARTPuts("\r\n Measure the Current Temperature of different Voltage Rails",
             -1);
    UARTPuts("\r\n----------------------------------------", -1);
    for (gVoltId = PMHAL_PRCM_VD_MPU; gVoltId <= PMHAL_PRCM_VD_GPU; gVoltId++)
    {
        UARTPuts("\r\nVoltage Domain: ", -1);
        UARTPuts(voltageDomain_t_names[gVoltId], -1);
        retVal = PMHALBgapGetCurrTemperature(gVoltId, &currTempRange);

        if (PM_SUCCESS == retVal)
        {
            UARTPrintf(
                "\r\nCurrent Temperature Range in Degrees C = [%u.%u , %u.%u]",
                currTempRange.minTemp / 1000, (currTempRange.minTemp % 1000),
                currTempRange.maxTemp / 1000, (currTempRange.maxTemp % 1000));
        }
        else
        {
            UARTPuts("\r\nGet Current Temperature Failed!!", -1);
            gTestStatus = STW_EFAIL;
        }
    }

    UARTPuts("\r\n----------------------------------------", -1);
    UARTPuts("\r\n Check for Hot events of different Voltage Rails",
             -1);
    UARTPuts("\r\n----------------------------------------", -1);
    SensorIntcInit();
    for (gVoltId = PMHAL_PRCM_VD_MPU; gVoltId <= PMHAL_PRCM_VD_GPU; gVoltId++)
    {
        UARTPuts("\r\nVoltage Domain: ", -1);
        UARTPuts(voltageDomain_t_names[gVoltId], -1);
        tempEvtOccurred = 0U;
        timeout         = TIMEOUT_VAL;
        retVal          = PMHALBgapSetHotThreshold(gVoltId, HOT_EVT_TEMP_THRESH);
        while ((0U == tempEvtOccurred) && (timeout > 0U))
        {
            timeout--;
        }

        if ((0U == timeout) && (0U == tempEvtOccurred))
        {
            UARTPuts("\r\nHot event not received. Timed Out!!", -1);
            gTestStatus = STW_EFAIL;
        }
    }

    UARTPuts("\r\n----------------------------------------", -1);
    UARTPuts("\r\n Check for Cold events of different Voltage Rails",
             -1);
    UARTPuts("\r\n----------------------------------------", -1);
    for (gVoltId = PMHAL_PRCM_VD_MPU; gVoltId <= PMHAL_PRCM_VD_GPU; gVoltId++)
    {
        UARTPuts("\r\nVoltage Domain: ", -1);
        UARTPuts(voltageDomain_t_names[gVoltId], -1);
        tempEvtOccurred = 0U;
        timeout         = TIMEOUT_VAL;
        retVal          = PMHALBgapSetColdThreshold(gVoltId,
                                                    COLD_EVT_TEMP_THRESH);
        while ((0U == tempEvtOccurred) && (timeout > 0U))
        {
            timeout--;
        }

        if ((0U == timeout) && (0U == tempEvtOccurred))
        {
            UARTPuts("\r\nCold event not received. Timed Out!!", -1);
            gTestStatus = STW_EFAIL;
        }
    }

    if (gTestStatus == STW_SOK)
    {
        UARTPuts("\r\nPM Junction Temperature Measure Test Pass", -1);
    }
    else
    {
        UARTPuts("\r\nPM Junction Temperature Measure Test Fail", -1);
    }

    return 0;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

static void SensorIntcInit(void)
{
    /*Unlock the Crossbar register */
    PlatformUnlockMMR();

    /* Connect the Xbar with interrupt source */
    CSL_xbarIrqConfigure(CSL_XBAR_IRQ_CPU_ID_MPU,gXbarInst,
                         CSL_XBAR_CTRL_MODULE_CORE_IRQ_THERMAL_ALERT);

    /* Initialize the interrupt control */
    Intc_Init();

    /* Enable the interrupt */
    Intc_IntEnable(0);

    /* Registering TimerIsr */
    Intc_IntRegister(MPU_IRQ_126, (IntrFuncPtr) TemperatureSensorIsr, NULL);

    /* Set the priority */
    Intc_IntPrioritySet(MPU_IRQ_126, 1, 0);

    /* Enable the system interrupt */
    Intc_SystemEnable(MPU_IRQ_126);
}

static void TemperatureSensorIsr(void *handle)
{
    int32_t retVal = PM_SUCCESS;

    UARTPuts("\r\nTemperature Event Occurred", -1);
    tempEvtOccurred = 1U;

    /* Follow this sequence to resolve silicon Errata ID: i813 which can
     * cause a spurious interrupt.
     */

    /* Disable the system interrupt */
    Intc_SystemDisable(MPU_IRQ_126);

    retVal  = PMHALBgapSetHotThreshold(gVoltId, MAX_HOT_EVT_TEMP_THRESH);
    retVal |= PMHALBgapSetColdThreshold(gVoltId, MIN_COLD_EVT_TEMP_THRESH);

    PMHALBgapDisableHotEvent(gVoltId);
    PMHALBgapDisableColdEvent(gVoltId);

    IntClearPendingState(MPU_IRQ_126);

    /* Enable the system interrupt */
    Intc_SystemEnable(MPU_IRQ_126);

    if (PM_SUCCESS != retVal)
    {
        UARTPuts("\r\nNot able to change thresholds", -1);
        gTestStatus = STW_EFAIL;
    }
}

