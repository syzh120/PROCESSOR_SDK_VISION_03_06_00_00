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
 *  \file     rti_dwwd_suspend_eve_main.c
 *
 *  \brief    This file contains RTI DWWD test code for suspend functionality\
 *        with IPU core 0.
 *
 *  \details  DWWD window size is set to 100%. Test runs in three stages:
 *          stage 1: DWWD is serviced and should not generate Reset
 *          stage 2: DWWD will be serviced within closed window to
 *               generate System RESET.
 *          stage 3: DWWD will expire and generate Reset to
 *               System.
 */

/* ========================================================================== */
/*                 Include Files                  */
/* ========================================================================== */
#include <stdint.h>
#include <ti/csl/csl_rti.h>
#include <ti/csl/tistdtypes.h>
#include <ti/csl/soc.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/soc.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/drv/stw_lld/uartconsole/uartStdio.h>
#include <ti/drv/stw_lld/examples/utility/stwutils_app.h>
#include <st_rti.h>

/* ========================================================================== */
/*                Macros                      */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*             Structures and Enums                   */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                Global Variables                */
/* ========================================================================== */
static uint32_t rtiWindow_size =
    RTI_DWWD_WINDOWSIZE_3_125_PERCENT;
static uint32_t rtiPreload_value = 0x00EAU;
static uint32_t rtiModule        = SOC_RTI4_BASE;

/* ========================================================================== */
/*         Internal Function Declarations                 */
/* ========================================================================== */
/**
 * \brief   This API return the status of the last system Reset.
 *
 * \param   none.
 *
 * \retval  status      Last device reset status.
 *              values given by enum #deviceLastResetStaus_t
 */
uint32_t start_window_violation_time(void);

extern deviceLastResetStaus_t DeviceGetLastResetStatus(void);
extern void RTISetClockSource(uint32_t rtiModule, uint32_t rtiClockSource);
extern void RTISetSuspendLine(uint32_t             rtiModule,
                              rtiSuspendLineCore_t deviceCore);
extern void AMMU_config(void);

/* ========================================================================== */
/*              Function Definitions                  */
/* ========================================================================== */
int main()
{
    int32_t config_status;

    StwUtils_appWaitForSbl();

    PlatformUartConsoleSetPinMux();
    UARTStdioInit();

    RTISetClockSource(rtiModule, RTI_CLOCK_SOURCE_32KHZ);
    RTISetSuspendLine(rtiModule, RTI_SUSPEND_LINE_CORE_EVE);
    config_status = RTIDwwdWindowConfig(rtiModule,
                                        RTI_DWWD_REACTION_GENERATE_RESET,
                                        rtiPreload_value,
                                        rtiWindow_size);
    if (config_status == STW_EFAIL)
    {
        UARTprintf("\n Error during Window configuration.");
    }
    else
    {
        UARTprintf("\nDWWD is configured for ..sec time-out.");
        RTIDwwdCounterEnable(rtiModule);
        UARTprintf("\nPause the execution and check for DWWD down counter.");
        while (1)
        {
            /*      Service DWWD in Open Window      */
            while (RTIDwwdIsClosedWindow(rtiModule)) {}
            RTIDwwdService(rtiModule);
            UARTprintf("\nDWWD serviced.");
        }
    }
    return 0;
}

/* ========================================================================== */
/*         Internal Function Definitions                  */
/* ========================================================================== */
/* None */
