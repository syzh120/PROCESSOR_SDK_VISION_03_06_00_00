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
/*
 * \file   uartConsole.c
 *
 * \brief  This file contains the UART Console APIs.
 */

#include <stdint.h>
#include <stdarg.h>
#include <ti/csl/soc.h>
#include <ti/drv/stw_lld/uartconsole/uartConsole.h>

uint32_t uart_base_address;

uint32_t UART_Init(UART_INST_t num)
{
    return UARTConsoleConfigInit(num,
                                 (uint32_t) BAUD_RATE,
                                 (uint32_t) OPER_MODE,
                                 (uint32_t) UART_PARITY_NONE,
                                 (uint32_t) UART_FRAME_WORD_LENGTH_8,
                                 (uint32_t) UART_FRAME_NUM_STB_1
                                 );
}

uint32_t UARTConsoleConfigInit(UART_INST_t num,
                               uint32_t    baudRate,
                               uint32_t    operMode,
                               uint32_t    parity,
                               uint32_t    wordLen,
                               uint32_t    stopBit)

{
    uint32_t divisorValue = 0, fifoConfig = 0;
    Bool     retVal       = TRUE;

    switch (num)
    {
        case UART1_INST:
            uart_base_address = SOC_UART1_BASE;
            break;
        case UART2_INST:
            uart_base_address = SOC_UART2_BASE;
            break;
        case UART3_INST:
            uart_base_address = SOC_UART3_BASE;
            break;
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (TI814X_BUILD)
        case UART4_INST:
            uart_base_address = SOC_UART4_BASE;
            break;
        case UART5_INST:
            uart_base_address = SOC_UART5_BASE;
            break;
        case UART6_INST:
            uart_base_address = SOC_UART6_BASE;
            break;
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
        case UART7_INST:
            uart_base_address = SOC_UART7_BASE;
            break;
        case UART8_INST:
            uart_base_address = SOC_UART8_BASE;
            break;
        case UART9_INST:
            uart_base_address = SOC_UART9_BASE;
            break;
        case UART10_INST:
            uart_base_address = SOC_UART10_BASE;
            break;
#endif
#endif
        default:
            retVal = FALSE;
            break;
    }
    if (retVal != FALSE)
    {
        /* Performing a module reset. */
        UARTModuleReset(uart_base_address);

        /* Performing FIFO configurations. */
        /*
        ** - Transmit Trigger Level Granularity is 4
        ** - Receiver Trigger Level Granularity is 1
        ** - Transmit FIFO Space Setting is 56. Hence TX Trigger level
        **   is 8 (64 - 56). The TX FIFO size is 64 bytes.
        ** - The Receiver Trigger Level is 1.
        ** - Clear the Transmit FIFO.
        ** - Clear the Receiver FIFO.
        ** - DMA Mode enabling shall happen through SCR register.
        ** - DMA Mode 0 is enabled. DMA Mode 0 corresponds to No
        **   DMA Mode. Effectively DMA Mode is disabled.
        */
        fifoConfig = UART_FIFO_CONFIG(UART_TRIG_LVL_GRANULARITY_4,
                                      UART_TRIG_LVL_GRANULARITY_1,
                                      UART_FCR_TX_TRIG_LVL_56,
                                      1U,
                                      1U,
                                      1U,
                                      UART_DMA_EN_PATH_SCR,
                                      UART_DMA_MODE_0_ENABLE);

        /* Configuring the FIFO settings. */
        UARTFIFOConfig(uart_base_address, fifoConfig);

        /* Performing Baud Rate settings. */
        /* Computing the Divisor Value. */
        divisorValue = UARTDivisorValCompute(UART_MODULE_INPUT_CLK,
                                             baudRate,
                                             operMode,
                                             UART_MIR_OVERSAMPLING_RATE_42);
        /* Programming the Divisor Latches. */
        UARTDivisorLatchWrite(uart_base_address, divisorValue);

        /* Switching to Configuration Mode B. */
        UARTRegConfigModeEnable(uart_base_address, UART_REG_CONFIG_MODE_B);

        /* Programming the Line Characteristics. */
        UARTLineCharacConfig(uart_base_address,
                             (wordLen | stopBit),
                             parity);

        /* Disabling write access to Divisor Latches. */
        UARTDivisorLatchDisable(uart_base_address);

        /* Disabling Break Control. */
        UARTBreakCtl(uart_base_address, UART_BREAK_COND_DISABLE);

        /* Uart enable */
        UARTOperatingModeSelect(uart_base_address, operMode);

        /* Debug */
        UARTOperatingModeSelect(uart_base_address, operMode);
    }
    return ((uint32_t) retVal);
}

/*
** A wrapper function for putting data on Uart Console.
*/
void UARTConsolePutc(uint8_t data)
{
    UARTCharPut(uart_base_address, data);
}

/*
** A wrapper function for getting data from Uart Console.
*/
uint8_t UARTConsoleGetc(void)
{
    return (uint8_t) UARTCharGet(uart_base_address);
}

/*
** A wrapper function performing UART console init operations.
*/
void UARTConsoleInit(UART_INST_t num)
{
    UART_Init(num);
}

/*
** A wrapper function performing UART wait operation.
*/
void UARTConsoleWaitUntilTransmitComplete(void)
{
    /*
    ** Waits indefinitely until the THR and Transmitter Shift Registers are
    ** empty.
    */
    while ((uint32_t) (TRUE) != UARTIsTransmitterEmpty(uart_base_address))
    {
        /* Do nothing - Busy wait */
    }
}

/**
 *  \brief   This function reads a byte entered on the Uart console in a
 *           non-blocking way.
 *
 *  \return  Returns -1 if no char read else character if a char is read.
 */
int8_t UARTConsoleGetcNonBlocking(void)
{
    return UARTCharGetNonBlocking(uart_base_address);
}

