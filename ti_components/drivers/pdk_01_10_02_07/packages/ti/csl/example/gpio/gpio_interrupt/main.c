/*
 *  Copyright (C) 2013-2017 Texas Instruments Incorporated
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
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <string.h>
#include <ti/csl/csl_gpio.h>
#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
#include <ti/board/board.h>
#endif
#include <ti/csl/example/utils/uart_console/inc/uartConfig.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/soc.h>
#include <ti/csl/hw_types.h>

/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
char     uartOutput[100];

/*To use UARTConfigPuts(uartBaseAddr, function for prints*/
/*To use UARTConfigPuts function for prints*/
#if defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x)
uint32_t uartBaseAddr = SOC_UART1_BASE;
#endif
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
uint32_t uartBaseAddr = SOC_UART3_BASE;
#endif

#if defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x)
uint32_t gpio_base_address = SOC_GPIO1_BASE;
uint32_t gpio_pin          = 14;
uint32_t interrupt_num     = 29;
uint32_t xbar_cfg_required = 0;
#endif
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
uint32_t gpio_base_address = SOC_GPIO4_BASE;
uint32_t gpio_pin          = 10;
uint32_t interrupt_num     = 51;
#define IRQ_XBAR_CFG_REQUIRED 1
#define IRQ_XBAR_CPU_ID       CSL_XBAR_IRQ_CPU_ID_IPU1
#define IRQ_XBAR_INST_NO      CSL_XBAR_INST_IPU1_IRQ_51
#define IRQ_XBAR_INDEX        CSL_XBAR_GPIO4_IRQ_1
#endif

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void padconfig_PrcmEnable()
{
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_DRA75x)
    /*Pad configurations */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_UART1_RXD,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_UART1_TXD,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_DCAN1_TX,0x0006000E);
    /*Enable GPIO clock*/
    HW_WR_REG32(SOC_L4PER_CM_CORE_BASE+CM_L4PER_GPIO2_CLKCTRL,0x101);
    while ((HW_RD_REG32(SOC_L4PER_CM_CORE_BASE+CM_L4PER_GPIO2_CLKCTRL) & (0x00030000U)) != 0x0)
        {
            ;
        }
    HW_WR_REG32(SOC_L4PER_CM_CORE_BASE+CM_L4PER_GPIO3_CLKCTRL,0x101);
    while ((HW_RD_REG32(SOC_L4PER_CM_CORE_BASE+CM_L4PER_GPIO3_CLKCTRL) & (0x00030000U)) != 0x0)
        {
            ;
        }
    HW_WR_REG32(SOC_L4PER_CM_CORE_BASE+CM_L4PER_GPIO4_CLKCTRL,0x101);
    while ((HW_RD_REG32(SOC_L4PER_CM_CORE_BASE+CM_L4PER_GPIO4_CLKCTRL) & (0x00030000U)) != 0x0)
        {
            ;
        }
    /* Set the UART Parameters */
    UARTConfigInit(uartBaseAddr, BAUD_RATE_115200, UART_WORD_LENGTH_8, UART_STOP_BIT_1, UART_NO_PARITY,
                   UART_16x_MODE);
#endif
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_SCLK,0x00040001);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_CS0,0x00000001);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_DCAN1_RX,0x0006000E);
    /* Set the access to the GPMC registers - Enable GPMC Clock */
    HW_WR_REG32(SOC_L4PER_CM_CORE_BASE + CM_L4PER_GPIO2_CLKCTRL, 0x102);
    while ((HW_RD_REG32(SOC_L4PER_CM_CORE_BASE +
                    CM_L4PER_GPIO2_CLKCTRL) & (0x00030000U)) != 0x0)
       {
            ;
       }
   HW_WR_REG32(SOC_L4PER_CM_CORE_BASE + CM_L4PER_GPIO3_CLKCTRL, 0x102);
   while ((HW_RD_REG32(SOC_L4PER_CM_CORE_BASE +
                    CM_L4PER_GPIO2_CLKCTRL) & (0x00030000U)) != 0x0)
       {
            ;
       }
   HW_WR_REG32(SOC_L4PER_CM_CORE_BASE + CM_L4PER_GPIO4_CLKCTRL, 0x102);
   while ((HW_RD_REG32(SOC_L4PER_CM_CORE_BASE +
                    CM_L4PER_GPIO2_CLKCTRL) & (0x00030000U)) != 0x0)
       {
            ;
       }
    /* Set the UART Parameters */
    UARTConfigInit(uartBaseAddr, BAUD_RATE_115200, UART_WORD_LENGTH_8, UART_STOP_BIT_1, UART_NO_PARITY,
                   UART_16x_MODE);
#endif
}

void gpioIsr(void *arg)
{
    volatile uint32_t gpio_pin_value = 0;

    /*Disable interrupt*/
    GPIOPinIntDisable(gpio_base_address, GPIO_INT_LINE_1, gpio_pin);

    /*Read pin*/
    gpio_pin_value = GPIOPinRead(gpio_base_address, gpio_pin);

    UARTConfigPuts(uartBaseAddr, uartOutput, -1);
    UARTConfigPutHexNum(uartBaseAddr, (gpio_pin_value & (0x1U << gpio_pin)) >> gpio_pin);

    GPIOPinIntClear(gpio_base_address, GPIO_INT_LINE_1, gpio_pin);

    /*Enable interrupt interrupt*/
    GPIOPinIntEnable(gpio_base_address, GPIO_INT_LINE_1, gpio_pin);
}

void configurGpioInterrupt()
{
#if IRQ_XBAR_CFG_REQUIRED
    /* XBar configuration */
    CSL_xbarIrqConfigure(IRQ_XBAR_CPU_ID,IRQ_XBAR_INST_NO,IRQ_XBAR_INDEX);
#endif
    Intc_Init();
    Intc_IntEnable(interrupt_num);

    Intc_IntRegister(interrupt_num, (IntrFuncPtr) gpioIsr, (void *) 0);
    Intc_IntPrioritySet(interrupt_num, 1, 0);
    Intc_SystemEnable(interrupt_num);
}

int main(void)
{
    volatile uint32_t waitForGpioInput = 1;
    char testType = 0;

    padconfig_PrcmEnable();
	
    UARTConfigPuts(uartBaseAddr, "\r\nGPIO Input interrupt App", -1);
    UARTConfigPuts(uartBaseAddr, "\r\nGenerate interrupt based on input value on GPIO pin", -1);
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_DRA75x)
    UARTConfigPuts(uartBaseAddr, "\r\nUse GPIO1 pin 14 on JP2 connector - pin 1 on EVM.", -1);
#endif
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
    UARTConfigPuts(uartBaseAddr, "\r\nUse GPIO4 pin 10 on J6108 connector - pin 2 on EVM", -1);
#endif
    UARTConfigPuts(uartBaseAddr, "\r\nTo Drive the value on pin to LOW connect to ground", -1);
    UARTConfigPuts(uartBaseAddr, "\r\nDefault value on the pin is High", -1);

    /* User Interface*/
    UARTConfigPuts(uartBaseAddr, "\r\nEnter type of test", -1);
    UARTConfigPuts(uartBaseAddr, "\r\n1. GPIO_INT_TYPE_LEVEL_LOW", -1);
    UARTConfigPuts(uartBaseAddr, "\r\n2. GPIO_INT_TYPE_LEVEL_HIGH ", -1);
    UARTConfigPuts(uartBaseAddr, "\r\n3. GPIO_INT_TYPE_FALL_EDGE", -1);
    UARTConfigPuts(uartBaseAddr, "\r\n4. GPIO_INT_TYPE_RISE_EDGE ", -1);
    UARTConfigPuts(uartBaseAddr, "\r\nEnter value(1, 2, 3 or 4) : ", -1);
    UARTConfigGets(uartBaseAddr, &testType, 1);

    /*Configure interrupt controller*/
    configurGpioInterrupt();

    /*Reset GPIO*/
    GPIOModuleReset(gpio_base_address);

    /*Enable GPIO*/
    GPIOModuleEnable(gpio_base_address);

    /*Configure and enable debouncing feature*/
    GPIODebounceTimeConfig(gpio_base_address, 0xFF);

    GPIODebounceFuncControl(gpio_base_address, gpio_pin,
                            GPIO_DEBOUNCE_FUNC_ENABLE);

    if ('1' == testType)
    {
        GPIOIntTypeSet(gpio_base_address, gpio_pin,
                       GPIO_INT_TYPE_LEVEL_LOW);
        strcpy(uartOutput, "\r\nGPIO: Low  Level detected. Pin value = ");
    }
    else if ('2' == testType)
    {
        GPIOIntTypeSet(gpio_base_address, gpio_pin,
                       GPIO_INT_TYPE_LEVEL_HIGH);
        strcpy(uartOutput, "\r\nGPIO: Default High Level detected. Pin value = ");
    }
    else if ('3' == testType)
    {
        GPIOIntTypeSet(gpio_base_address, gpio_pin,
                       GPIO_INT_TYPE_FALL_EDGE);
        strcpy(uartOutput, "\r\nGPIO: Falling edge detected. Pin value = ");
    }
    else
    {
        GPIOIntTypeSet(gpio_base_address, gpio_pin,
                       GPIO_INT_TYPE_RISE_EDGE);
        strcpy(uartOutput, "\r\nGPIO: Rising edge detected. Pin value = ");
    }

    /* Set pin direction as input*/
    GPIODirModeSet(gpio_base_address, gpio_pin, GPIO_DIR_INPUT);

    /*Clear interrupt*/
    GPIOPinIntDisable(gpio_base_address, GPIO_INT_LINE_1, gpio_pin);
    GPIOPinIntClear(gpio_base_address, GPIO_INT_LINE_1, gpio_pin);

    /*Enable interrupt*/
    GPIOPinIntEnable(gpio_base_address, GPIO_INT_LINE_1, gpio_pin);

    while (waitForGpioInput)
    {
        /*Keep while busy*/
        waitForGpioInput++;
        waitForGpioInput--;
    }
    return 0;
}

