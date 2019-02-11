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
 *  \file     rti_dwwd_reset_status_main.c
 *
 *  \brief    This file contains RTI DWWD test code for getting Reset status
 *            when it is generated from more than one RTI.
 *
 *  \details  Three RTIs are configured with two of them at close
 *            time-out value and another with larger time-out value than
 *            first two RTIs.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <ti/csl/csl_rti.h>
#include <ti/csl/tistdtypes.h>
#include <ti/csl/soc.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/hw_types.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/drv/stw_lld/uartconsole/uartStdio.h>
#include <ti/drv/stw_lld/examples/utility/stwutils_app.h>
#include <st_rti.h>

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
static uint32_t rtiWindow_size =
    RTI_DWWD_WINDOWSIZE_100_PERCENT;
static uint32_t rtiPreload_value = 0x00EAU;
static uint32_t rtiModule1       = SOC_RTI1_BASE;
static uint32_t rtiModule3       = SOC_RTI3_BASE;
static uint32_t rtiModule2       = SOC_RTI2_BASE;
static uint32_t rtiModule4       = SOC_RTI4_BASE;
static uint32_t rtiModule5       = SOC_RTI5_BASE;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
extern deviceLastResetStaus_t DeviceGetLastResetStatus(void);
extern void RTISetClockSource(uint32_t rtiModule, uint32_t rtiClockSource);
extern void RTISetSuspendLine(uint32_t             rtiModule,
                              rtiSuspendLineCore_t deviceCore);
extern void AMMU_config(void);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
int main()
{
    deviceLastResetStaus_t reset_status;
    int32_t  config_status;
    uint32_t configError = 0, temp = 0;

    StwUtils_appWaitForSbl();

    PlatformUartConsoleSetPinMux();
    UARTStdioInit();

    RTISetClockSource(rtiModule4, RTI_CLOCK_SOURCE_32KHZ);
    RTISetClockSource(rtiModule2, RTI_CLOCK_SOURCE_32KHZ);
    RTISetClockSource(rtiModule3, RTI_CLOCK_SOURCE_32KHZ);
    reset_status = DeviceGetLastResetStatus();
    switch (reset_status) {
        case DEVICE_LAST_RESET_STATUS_NOT_WDT_GENERATED:
            /*      Clear status register for RTI modules       */
            RTIDwwdClearStatus(rtiModule4, RTI_DWWD_STATUS_KEY_SEQ_VIOLATION |
                               RTI_DWWD_STATUS_TIME_WINDOW_VIOLATION |
                               RTI_DWWD_STATUS_ENDTIME_WINDOW_VIOLATION |
                               RTI_DWWD_STATUS_STARTTIME_WINDOW_VIOLATION |
                               RTI_DWWD_STATUS_LAST_RESET);
            RTIDwwdClearStatus(rtiModule2, RTI_DWWD_STATUS_KEY_SEQ_VIOLATION |
                               RTI_DWWD_STATUS_TIME_WINDOW_VIOLATION |
                               RTI_DWWD_STATUS_ENDTIME_WINDOW_VIOLATION |
                               RTI_DWWD_STATUS_STARTTIME_WINDOW_VIOLATION |
                               RTI_DWWD_STATUS_LAST_RESET);
            RTIDwwdClearStatus(rtiModule3, RTI_DWWD_STATUS_KEY_SEQ_VIOLATION |
                               RTI_DWWD_STATUS_TIME_WINDOW_VIOLATION |
                               RTI_DWWD_STATUS_ENDTIME_WINDOW_VIOLATION |
                               RTI_DWWD_STATUS_STARTTIME_WINDOW_VIOLATION |
                               RTI_DWWD_STATUS_LAST_RESET);
            /*      Configure RTI modules       */
            config_status = RTIDwwdWindowConfig(
                rtiModule4,
                RTI_DWWD_REACTION_GENERATE_RESET,
                rtiPreload_value,
                rtiWindow_size);
            if (config_status == STW_EFAIL)
            {
                UARTprintf(" Error during Window configuration.\n");
                configError++;
            }
            config_status = RTIDwwdWindowConfig(
                rtiModule2,
                RTI_DWWD_REACTION_GENERATE_RESET,
                rtiPreload_value,
                rtiWindow_size);
            if (config_status == STW_EFAIL)
            {
                UARTprintf(" Error during Window configuration.\n");
                configError++;
            }
            config_status = RTIDwwdWindowConfig(
                rtiModule3,
                RTI_DWWD_REACTION_GENERATE_RESET,
                rtiPreload_value,
                rtiWindow_size);
            if (config_status == STW_EFAIL)
            {
                UARTprintf(" Error during Window configuration.\n");
                configError++;
            }
            if (configError != 0U)
            {
                UARTprintf("Error occurred during configuration of RTI.\n");
                UARTprintf("Try to run application again.\n");
            }
            else
            {
                UARTprintf(
                    "Two RTI modules are configured for 60sec time-out.\n");
                UARTprintf(
                    "One RTI module is configured for 9375sec time-out.\n");
                /*      Enable RTI/DWWD modules      */
                RTIDwwdCounterEnable(rtiModule4);
                RTIDwwdCounterEnable(rtiModule2);
                RTIDwwdCounterEnable(rtiModule3);
                /*      let DWWD expire here  */
                UARTprintf("Wait for RESET to be generated by DWWD.\n");
                for (;; ) ;
            }
            break;
        case DEVICE_LAST_RESET_STATUS_WDT_GENERATED:
            if (RTI_DWWD_RESET_STATUS_GENERATED ==
                RTIDwwdGetLastResetStatus(rtiModule1))
            {
                UARTprintf("Last RESET is generated by RTI Module 1.\n");
            }
            if (RTI_DWWD_RESET_STATUS_GENERATED ==
                RTIDwwdGetLastResetStatus(rtiModule2))
            {
                UARTprintf("Last RESET is generated by RTI Module 2.\n");
                temp++;
            }
            if (RTI_DWWD_RESET_STATUS_GENERATED ==
                RTIDwwdGetLastResetStatus(rtiModule3))
            {
                UARTprintf("Last RESET is generated by RTI Module 3.\n");
            }
            if (RTI_DWWD_RESET_STATUS_GENERATED ==
                RTIDwwdGetLastResetStatus(rtiModule4))
            {
                UARTprintf("Last RESET is generated by RTI Module 4.\n");
                temp++;
            }
            if (RTI_DWWD_RESET_STATUS_GENERATED ==
                RTIDwwdGetLastResetStatus(rtiModule5))
            {
                UARTprintf("Last RESET is generated by RTI Module 5.\n");
            }
            break;
        default:
        {}
    }
    if (temp == 2U)
    {
        UARTprintf("Testcase (ID = STW_RTI_TC00012) PASSED.\n");
        StwUtils_appLogTestResult(STWUTILS_APP_TST_STATUS_PASS);
    }
    else
    {
        UARTprintf("Testcase (ID = STW_RTI_TC00012) FAILED.\n");
        StwUtils_appLogTestResult(STWUTILS_APP_TST_STATUS_FAIL);
    }
    return 0;
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */
/* None */
