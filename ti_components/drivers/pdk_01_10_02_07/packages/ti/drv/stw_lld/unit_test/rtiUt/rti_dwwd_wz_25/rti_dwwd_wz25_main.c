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
 *  \file     rti_dwwd_wz25_main.c
 *
 *  \brief    This file contains RTI DWWD test code for window size 100%.
 *
 *  \details  DWWD window size is set to 100%. Test runs in three stages:
 *                  stage 1: DWWD is serviced and should not generate Reset
 *                  stage 2: DWWD will be serviced within closed window to
 *                           generate System RESET.
 *                  stage 3: DWWD will expire and generate Reset to
 *                           System.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <string.h>
#include <ti/csl/csl_rti.h>
#include <ti/csl/soc.h>
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
    RTI_DWWD_WINDOWSIZE_25_PERCENT;
static uint32_t rtiPreload_value = 0x00EAU;
static uint32_t rtiModule        = SOC_RTI2_BASE;
static uint32_t rtiTimeoutValue;
/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
/**
 * \brief   This API return the status of the last system Reset.
 *
 * \param   none.
 *
 * \retval  status          Last device reset status.
 *                          values given by enum #deviceLastResetStaus_t
 */
uint32_t start_window_violation_time(void);

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
    uint32_t WDT_violation_service_time;

    StwUtils_appWaitForSbl();

    PlatformUartConsoleSetPinMux();
    UARTStdioInit();

    RTISetClockSource(rtiModule, RTI_CLOCK_SOURCE_32KHZ);
    reset_status = DeviceGetLastResetStatus();
    switch (reset_status) {
        case DEVICE_LAST_RESET_STATUS_NOT_WDT_GENERATED:
            RTIDwwdClearStatus(rtiModule, RTI_DWWD_STATUS_KEY_SEQ_VIOLATION |
                               RTI_DWWD_STATUS_TIME_WINDOW_VIOLATION |
                               RTI_DWWD_STATUS_ENDTIME_WINDOW_VIOLATION |
                               RTI_DWWD_STATUS_STARTTIME_WINDOW_VIOLATION |
                               RTI_DWWD_STATUS_LAST_RESET);
            config_status = RTIDwwdWindowConfig(
                rtiModule,
                RTI_DWWD_REACTION_GENERATE_RESET,
                rtiPreload_value,
                rtiWindow_size);
            if (config_status == STW_EFAIL)
            {
                UARTprintf(" Error during Window configuration.\n");
            }
            else
            {
                UARTprintf("DWWD is configured for 60sec time-out.\n");
                RTIDwwdCounterEnable(rtiModule);
                /*      Service DWWD in Open Window      */
                while (RTIDwwdIsClosedWindow(rtiModule)) {}
                RTIDwwdService(rtiModule);
                UARTprintf("DWWD serviced.\n");
                /*      let DWWD expire here  */
                UARTprintf("Wait for RESET to be generated by DWWD.\n");
                UARTWaitUntilTransmitComplete();
                for (;; ) ;
            }
            break;
        case DEVICE_LAST_RESET_STATUS_WDT_GENERATED:
            if ((RTI_DWWD_RESET_STATUS_GENERATED ==
                 RTIDwwdGetLastResetStatus(rtiModule)) &&
                (1U != HW_RD_FIELD32(rtiModule + RTI_RTIWDSTATUS,
                                     RTI_RTIWDSTATUS_START_TIME_VIOL)))
            {
                UARTprintf("Last reset was generated by DWWD.\n");
                UARTprintf("Recovered from RESET generated by DWWD.\n");
                config_status = RTIDwwdWindowConfig(
                    rtiModule,
                    RTI_DWWD_REACTION_GENERATE_RESET,
                    rtiPreload_value,
                    rtiWindow_size);
                if (config_status == STW_EFAIL)
                {
                    UARTprintf(" Error during Window configuration.\n");
                }
                else
                {
                    UARTprintf("DWWD is configured for 60sec time-out.\n");
                    rtiTimeoutValue = RTIDwwdGetCurrentDownCounter(rtiModule);
                    WDT_violation_service_time = start_window_violation_time();
                    RTIDwwdCounterEnable(rtiModule);
                    /*      Service DWWD in closed window       */
                    UARTprintf("Servicing DWWD in closed Window.\n\n");
                    while (RTIDwwdGetCurrentDownCounter(rtiModule) >
                           WDT_violation_service_time)
                    {}
                    RTIDwwdService(rtiModule);
                    /*      DWWD will generate Violation/RESET here      */
                    UARTWaitUntilTransmitComplete();
                    for (;; ) ;
                }
            }
            else
            {
                if (0x1U == HW_RD_FIELD32(rtiModule + RTI_RTIWDSTATUS,
                                          RTI_RTIWDSTATUS_START_TIME_VIOL))
                {
                    UARTprintf("Testcase (ID = STW_RTI_TC00003) PASSED.\n");
                    StwUtils_appLogTestResult(STWUTILS_APP_TST_STATUS_PASS);
                }
                else
                {
                    UARTprintf("Last RESET was not generated by DWWD.\n");
                    UARTprintf("Testcase (ID = STW_RTI_TC00003) FAILED.\n");
                    UARTprintf("Please try to run application again.\n");
                    StwUtils_appLogTestResult(STWUTILS_APP_TST_STATUS_FAIL);
                }
                UARTWaitUntilTransmitComplete();
            }
            break;
        default:
        {}
    }
    return 0;
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */
uint32_t start_window_violation_time(void)
{
    uint32_t time;
    switch (rtiWindow_size) {
        case RTI_DWWD_WINDOWSIZE_100_PERCENT:
            time = 0;
            break;
        case RTI_DWWD_WINDOWSIZE_50_PERCENT:
            time = (rtiTimeoutValue / 4) + (rtiTimeoutValue / 2);
            break;
        case RTI_DWWD_WINDOWSIZE_25_PERCENT:
            time = (rtiTimeoutValue / 8) + (rtiTimeoutValue / 4);
            break;
        case RTI_DWWD_WINDOWSIZE_12_5_PERCENT:
            time = (rtiTimeoutValue / 16) + (rtiTimeoutValue / 8);
            break;
        case RTI_DWWD_WINDOWSIZE_6_25_PERCENT:
            time = (rtiTimeoutValue / 32) + (rtiTimeoutValue / 16);
            break;
        case RTI_DWWD_WINDOWSIZE_3_125_PERCENT:
            time = (rtiTimeoutValue / 64) + (rtiTimeoutValue / 32);
            break;
    }
    return time;
}

