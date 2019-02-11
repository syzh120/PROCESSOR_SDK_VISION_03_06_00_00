/*
 *  Copyright (c) Texas Instruments Incorporated 2012-2017
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *
 *  Redistributions in binary form must reproduce the above copyright
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the
 *  distribution.
 *
 *  Neither the name of Texas Instruments Incorporated nor the names of
 *  its contributors may be used to endorse or promote products derived
 *  from this software without specific prior written permission.
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
 */

/*
 * main.c
 */

#include <stdint.h>
#include <stdio.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/csl_uart.h>
#include <ti/csl/soc.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/example/utils/uart_console/inc/uartConfig.h>

/******************************************************************************
**              INTERNAL MACRO DEFINITIONS
******************************************************************************/
#define XBAR_CPU                        (CSL_XBAR_IRQ_CPU_ID_IPU1)
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
#define UART_INT_ID                     (44U)
#define XBAR_INST                       (CSL_XBAR_INST_IPU1_IRQ_44)
#define XBAR_INTR_SOURCE                (CSL_XBAR_UART1_IRQ)
#elif defined (SOC_TDA3XX)
#define UART_INT_ID                     (45U)
#define XBAR_INST                       (CSL_XBAR_INST_IPU1_IRQ_45)
#define XBAR_INTR_SOURCE                (CSL_XBAR_UART3_IRQ)
#endif

/******************************************************************************
**              INTERNAL FUNCTION PROTOTYPES
******************************************************************************/
static void UartInterruptEnable(void);
static void UartINTCConfigure(void);
static void UartFIFOConfigure(void);
static void UartBaudRateSet(void);
static void UARTIsr(void *handle);
static void padConfig_prcmEnable(void);
/******************************************************************************
**              GLOBAL VARIABLE DEFINITIONS
******************************************************************************/
unsigned char txArray[] = "PDK UART Interrupt application\n\r";
uint32_t      uartBaseAddr;

/******************************************************************************
**              FUNCTION DEFINITIONS
******************************************************************************/
static void padConfig_prcmEnable()
{
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
    /*Pad configurations */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_UART1_RXD,
        0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_UART1_TXD,
        0x00000000);
#endif
#if defined (SOC_TDA3XX)
    /*Pad configurations */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_SCLK,
        0x00040001);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_CS0,
        0x00000001);
#endif
}


int main()
{
    int32_t  retVal = STW_SOK;
    volatile uint32_t loopVar = 1U;

    uartBaseAddr = SOC_UART1_BASE;

#if defined (SOC_TDA3XX)
    uartBaseAddr = SOC_UART3_BASE;
#endif

    /*Pad configuration and PRCM enable*/
    padConfig_prcmEnable();

    /* Performing a module reset. */
    UARTModuleReset(uartBaseAddr);

    /* Performing FIFO configurations. */
    UartFIFOConfigure();

    /* Performing Baud Rate settings. */
    UartBaudRateSet();

    /* Switching to Configuration Mode B. */
    UARTRegConfigModeEnable(uartBaseAddr, UART_REG_CONFIG_MODE_B);

    /* Programming the Line Characteristics. */
    UARTLineCharacConfig(uartBaseAddr,
                         (UART_FRAME_WORD_LENGTH_8 | UART_FRAME_NUM_STB_1),
                         UART_PARITY_NONE);

    /* Disabling write access to Divisor Latches. */
    UARTDivisorLatchDisable(uartBaseAddr);

    /* Disabling Break Control. */
    UARTBreakCtl(uartBaseAddr, UART_BREAK_COND_DISABLE);

    /* Switching to UART16x operating mode. */
    UARTOperatingModeSelect(uartBaseAddr, UART16x_OPER_MODE);

    /* Performing Interrupt configurations. */
    UartInterruptEnable();

    while(loopVar == 1U);
    return retVal;
}

/*
** A wrapper function performing FIFO configurations.
*/

static void UartFIFOConfigure(void)
{
    uint32_t fifoConfig = 0;

    /* Setting the TX and RX FIFO Trigger levels as 1. No DMA enabled. */
    fifoConfig = UART_FIFO_CONFIG(UART_TRIG_LVL_GRANULARITY_1,
                                  UART_TRIG_LVL_GRANULARITY_1,
                                  1,
                                  1,
                                  1,
                                  1,
                                  UART_DMA_EN_PATH_SCR,
                                  UART_DMA_MODE_0_ENABLE);

    /* Configuring the FIFO settings. */
    UARTFIFOConfig(uartBaseAddr, fifoConfig);
}

/*
** A wrapper function performing Baud Rate settings.
*/

static void UartBaudRateSet(void)
{
    uint32_t divisorValue = 0;

    /* Computing the Divisor Value. */
    divisorValue = UARTDivisorValCompute(UART_MODULE_INPUT_CLK,
                                         BAUD_RATE_115200,
                                         UART16x_OPER_MODE,
                                         UART_MIR_OVERSAMPLING_RATE_42);

    /* Programming the Divisor Latches. */
    UARTDivisorLatchWrite(uartBaseAddr, divisorValue);
}

/*
** A wrapper function performing Interrupt configurations.
*/

static void UartInterruptEnable(void)
{
    /* Configuring INTC to receive UART interrupts. */
    UartINTCConfigure();

    /* Enabling the specified UART interrupts. */
    UARTIntEnable(uartBaseAddr, (UART_INT_LINE_STAT | UART_INT_THR |
                                 UART_INT_RHR_CTI));
}

/*
** Interrupt Service Routine for UART.
*/

static void UARTIsr(void *handle)
{
    static uint32_t txStrLength = sizeof (txArray);
    static uint32_t count       = 0;
    unsigned char   rxByte      = 0;
    uint32_t        intId       = 0;

    /* Checking ths source of UART interrupt. */
    intId = UARTIntIdentityGet(uartBaseAddr);

    switch (intId)
    {
        case UART_INTID_TX_THRES_REACH:

            if (0 != txStrLength)
            {
                UARTCharPut(uartBaseAddr, txArray[count]);
                txStrLength--;
                count++;
            }
            else
            {
                /* Disabling the THR interrupt. */
                UARTIntDisable(uartBaseAddr, UART_INT_THR);
            }

            break;

        case UART_INTID_RX_THRES_REACH:
            rxByte = UARTCharGetNonBlocking(uartBaseAddr);
            UARTCharPutNonBlocking(uartBaseAddr, rxByte);
            break;

        case UART_INTID_RX_LINE_STAT_ERROR:
        case UART_INTID_CHAR_TIMEOUT:
            UARTCharGetNonBlocking(uartBaseAddr);
            break;

        default:
            break;
    }
}

/*
** This function configures the INTC to receive UART interrupts.
*/
static void UartINTCConfigure(void)
{
    /* Crossbar registers are already unlocked, so connect directly */
    CSL_xbarIrqConfigure(XBAR_CPU,XBAR_INST,XBAR_INTR_SOURCE);

    /* Initializing the Interrupt Controller. */
    Intc_Init();

    /* Enable the interrupt */
    Intc_IntEnable(0);

    /* Registering the Interrupt Service Routine(ISR). */
    Intc_IntRegister(UART_INT_ID, (IntrFuncPtr) UARTIsr, NULL);

    /* Setting the priority for the UART interrupt in INTC. */
    Intc_IntPrioritySet(UART_INT_ID, 1, 0);

    /* Enabling the UART interrupt in INTC. */
    Intc_SystemEnable(UART_INT_ID);
}

/******************************* End of file *********************************/
