/*
 *  Copyright (C) 2015-2017 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \file   main.c
 *
 *  \brief This file demonstrates WD TIMER dal.
 *
**/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "stdint.h"
#include <ti/csl/csl_wd_timer.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/example/utils/uart_console/inc/uartConfig.h>
#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
#include <ti/board/board.h>
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define INITIAL_COUNT_VALUE          (0xFFFE0000U)
#define RELOAD_COUNT_VALUE           (0xFFFE0000U)

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_DRA75x)
#define SOC_WD_TIMER_BASE  SOC_WD_TIMER2_BASE
#endif

#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
#define SOC_WD_TIMER_BASE CSL_MPU_WD_TIMER2_REGS
#endif

#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
uint32_t uartBaseAddr = CSL_MPU_UART3_REGS;
#endif
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_DRA75x)
uint32_t uartBaseAddr = SOC_UART1_BASE;
#endif

/* ========================================================================== */
/*                   Internal Function Declarations                           */
/* ========================================================================== */
static void WDTimerSetUp(void);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void padConfig_prcmEnable()
{
#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
    /*Pad configurations */
    Board_initCfg boardCfg;
    boardCfg = BOARD_INIT_UNLOCK_MMR | BOARD_INIT_UART_STDIO | 
               BOARD_INIT_MODULE_CLOCK | BOARD_INIT_PINMUX_CONFIG;
    Board_init(boardCfg);
#endif
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_DRA75x)
    /*Pad configurations */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_UART1_RXD,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_UART1_TXD,0x00000000);
    /* Initialize the UART Instance */
    UARTConfigInit(uartBaseAddr, BAUD_RATE_115200, UART_WORD_LENGTH_8, UART_STOP_BIT_1, UART_NO_PARITY,
                   UART_16x_MODE);
#endif
}

int main(void)
{
    uint32_t triggerValue = 0;

    padConfig_prcmEnable();

    UARTConfigPuts(uartBaseAddr,"\nWD Timer Application Running on A15", -1);

    /* Reset the Watchdog Timer */
    WDTIMERReset(SOC_WD_TIMER_BASE);

    /* Disable the Watchdog timer */
    WDTIMERDisable(SOC_WD_TIMER_BASE);

    /* Perform the initial settings for the Watchdog Timer */
    WDTimerSetUp();

    /* Send the message to UART console */
    UARTConfigPuts(uartBaseAddr,"\nProgram Reset!", -1);
    UARTConfigPuts(uartBaseAddr,
        "\nInput any key at least once in every 4 seconds to avoid a further reset.\n\r",
        -1);

    /* Enable the Watchdog Timer */
    WDTIMEREnable(SOC_WD_TIMER_BASE);

    while (1)
    {
        /* Wait for an input through UART. If no input is given,
        ** the WD Timer will timeout and reset will occur.
        */
        if (UARTCharGet(uartBaseAddr))
        {
            triggerValue += 1;

            /* Write into the trigger register. This will load the value from
            * the
            ** load register into the counter register and hence timer will
            ** start
            ** from the initial count.
            */
            WDTIMERTriggerSet(SOC_WD_TIMER_BASE, triggerValue);
        }
    }
}

/**
 * \brief   This function will perform the necessary initialization for
 *          the Watchdog Timer.
**/
static void WDTimerSetUp(void)
{
    /* Configure and enable the pre-scaler clock */
    WDTIMERPreScalerClkEnable(SOC_WD_TIMER_BASE, WD_TIMER_PRESCALER_CLK_DIV_1);

    /* Set the count value into the counter register */
    WDTIMERCounterSet(SOC_WD_TIMER_BASE, INITIAL_COUNT_VALUE);

    /* Set the reload value into the load register */
    WDTIMERReloadSet(SOC_WD_TIMER_BASE, RELOAD_COUNT_VALUE);
}
/********************************* End of file ******************************/
