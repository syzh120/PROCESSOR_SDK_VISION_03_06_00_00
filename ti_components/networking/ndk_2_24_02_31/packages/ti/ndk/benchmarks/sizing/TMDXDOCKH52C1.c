/*
 *  Copyright 2015 by Texas Instruments Incorporated.
 *
 */

/*
 * Copyright (c) 2015, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== TMDXDOCKH52C1.c ========
 *  This file is responsible for setting up the board specific items for the
 *  TMDXDOCKH52C1 board.
 */

#include <inc/hw_memmap.h>
#include <inc/hw_types.h>
#include <inc/hw_ints.h>
#include <inc/hw_gpio.h>
#include <inc/hw_sysctl.h>

#include <driverlib/gpio.h>
#include <driverlib/sysctl.h>
#include <driverlib/i2c.h>
#include <driverlib/ssi.h>
#include <driverlib/uart.h>
#include <driverlib/udma.h>

#include <xdc/std.h>
#include <xdc/cfg/global.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/family/arm/m3/Hwi.h>

#include "TMDXDOCKH52C1.h"

#include <stdbool.h>

/*
 *  =============================== DMA ===============================
 */
#pragma DATA_SECTION(dmaControlTable, ".dma");
#pragma DATA_ALIGN(dmaControlTable, 1024)
static tDMAControlTable dmaControlTable[32];
static bool dmaInitialized = false;

/* Hwi_Struct used in the initDMA Hwi_construct call */
static Hwi_Struct hwiStruct;
/*
 *  ======== dmaErrorHwi ========
 */
static Void dmaErrorHwi(UArg arg)
{
    System_printf("DMA error code: %d\n", uDMAErrorStatusGet());
    uDMAErrorStatusClear();
    System_abort("DMA error!!");
}

/*
 *  ======== TMDXDOCKH52C1_initDMA ========
 */
void TMDXDOCKH52C1_initDMA(void)
{
    Error_Block eb;
    Hwi_Params  hwiParams;

    if(!dmaInitialized){

        Error_init(&eb);

        Hwi_Params_init(&hwiParams);
        Hwi_construct(&(hwiStruct), INT_UDMAERR, dmaErrorHwi, &hwiParams, &eb);
        if (Error_check(&eb)) {
            System_abort("Couldn't create DMA error hwi");
        }

        SysCtlPeripheralEnable(SYSCTL_PERIPH_UDMA);
        uDMAEnable();
        uDMAControlBaseSet(dmaControlTable);

        dmaInitialized = true;
    }
}

/*
 *  =============================== EMAC ===============================
 */
/* Place into subsections to allow the TI linker to remove items properly */
#pragma DATA_SECTION(EMAC_config, ".const:EMAC_config")
#pragma DATA_SECTION(emacHWAttrs, ".const:emacHWAttrs")
#pragma DATA_SECTION(NIMUDeviceTable, ".data:NIMUDeviceTable")

#include <ti/drivers/EMAC.h>
#include <ti/drivers/emac/EMACTiva.h>

/* EMAC objects */
EMACTiva_Object emacObjects[TMDXDOCKH52C1_EMACCOUNT];

/*
 *  EMAC configuration structure
 *  Set user/company specific MAC octates. The following sets the address
 *  to ff-ff-ff-ff-ff-ff. Users need to change this to match the label on
 *  their boards.
 */
unsigned char macAddress[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

const EMACTiva_HWAttrs emacHWAttrs[TMDXDOCKH52C1_EMACCOUNT] = {
    {INT_ETH, ~0 /* Interrupt priority */, macAddress}
};

const EMAC_Config EMAC_config[] = {
    {&EMACTiva_fxnTable, emacObjects, emacHWAttrs},
    {NULL, NULL, NULL}
};

/*
 *  Required by the Networking Stack (NDK). This array must be NULL terminated.
 *  This can be removed if NDK is not used.
 *  Double curly braces are needed to avoid GCC bug #944572
 *  https://bugs.launchpad.net/gcc-linaro/+bug/944572
 */
NIMU_DEVICE_TABLE_ENTRY  NIMUDeviceTable[2] = {{EMACTiva_NIMUInit}, {NULL}};

/*
 *  ======== TMDXDOCKH52C1_initEMAC ========
 */
void TMDXDOCKH52C1_initEMAC(void)
{
    /*
     *  Set up the pins that are used for Ethernet
     *  MII_TXD3
     */
    GPIODirModeSet(GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_DIR_MODE_HW);
    GPIOPadConfigSet(GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_PIN_TYPE_STD);
    GPIOPinConfigure(GPIO_PC4_MIITXD3);

    /* MII_MDIO */
    GPIODirModeSet(GPIO_PORTE_BASE, GPIO_PIN_6, GPIO_DIR_MODE_HW);
    GPIOPadConfigSet(GPIO_PORTE_BASE, GPIO_PIN_6, GPIO_PIN_TYPE_STD);
    GPIOPinConfigure(GPIO_PE6_MIIMDIO);

    /* MII_RXD3 */
    GPIODirModeSet(GPIO_PORTF_BASE, GPIO_PIN_5, GPIO_DIR_MODE_HW);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_5, GPIO_PIN_TYPE_STD);
    GPIOPinConfigure(GPIO_PF5_MIIRXD3);

    /* MII_TXER , MII_RXDV , MII_RXD1 , MII_RXD2 */
    GPIODirModeSet(GPIO_PORTG_BASE, GPIO_PIN_7|GPIO_PIN_3|GPIO_PIN_1|GPIO_PIN_0,
                   GPIO_DIR_MODE_HW);
    GPIOPadConfigSet(GPIO_PORTG_BASE, GPIO_PIN_7|GPIO_PIN_3|GPIO_PIN_1|
                     GPIO_PIN_0,
                     GPIO_PIN_TYPE_STD);
    GPIOPinConfigure(GPIO_PG0_MIIRXD2);
    GPIOPinConfigure(GPIO_PG1_MIIRXD1);
    GPIOPinConfigure(GPIO_PG3_MIIRXDV);
    GPIOPinConfigure(GPIO_PG7_MIITXER);

    /* MII_TXCK , MII_TXEN , MII_TXD0 , MII_TXD1 , MII_TXD2 , MII_RXD0 */
    GPIODirModeSet(
        GPIO_PORTH_BASE, GPIO_PIN_7|GPIO_PIN_6|GPIO_PIN_5|GPIO_PIN_4|
        GPIO_PIN_3|
        GPIO_PIN_1, GPIO_DIR_MODE_HW);
    GPIOPadConfigSet(
        GPIO_PORTH_BASE, GPIO_PIN_7|GPIO_PIN_6|GPIO_PIN_5|GPIO_PIN_4|
        GPIO_PIN_3|
        GPIO_PIN_1, GPIO_PIN_TYPE_STD);
    GPIOPinConfigure(GPIO_PH1_MIIRXD0);
    GPIOPinConfigure(GPIO_PH3_MIITXD2);
    GPIOPinConfigure(GPIO_PH4_MIITXD1);
    GPIOPinConfigure(GPIO_PH5_MIITXD0);
    GPIOPinConfigure(GPIO_PH6_MIITXEN);
    GPIOPinConfigure(GPIO_PH7_MIITXCK);

    /*
     *  MII_PHYRSTn , MII_PHYINTRn , MII_CRS , MII_COL , MII_MDC , MII_RXCK ,
     *  MII_RXER
     */
    GPIODirModeSet(
        GPIO_PORTJ_BASE, GPIO_PIN_7|GPIO_PIN_6|GPIO_PIN_5|GPIO_PIN_4|
        GPIO_PIN_3|
        GPIO_PIN_2|GPIO_PIN_0, GPIO_DIR_MODE_HW);
    GPIOPadConfigSet(
        GPIO_PORTJ_BASE, GPIO_PIN_7|GPIO_PIN_6|GPIO_PIN_5|GPIO_PIN_4|
        GPIO_PIN_3|
        GPIO_PIN_2|GPIO_PIN_0, GPIO_PIN_TYPE_STD);
    GPIOPinConfigure(GPIO_PJ0_MIIRXER);
    GPIOPinConfigure(GPIO_PJ2_MIIRXCK);
    GPIOPinConfigure(GPIO_PJ3_MIIMDC);
    GPIOPinConfigure(GPIO_PJ4_MIICOL);
    GPIOPinConfigure(GPIO_PJ5_MIICRS);
    GPIOPinConfigure(GPIO_PJ6_MIIPHYINTRn);
    GPIOPinConfigure(GPIO_PJ7_MIIPHYRSTn);

    /* Enable and Reset the Ethernet Controller. */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ETH);
    SysCtlPeripheralReset(SYSCTL_PERIPH_ETH);

    if (macAddress[0] == 0xff && macAddress[1] == 0xff &&
        macAddress[2] == 0xff && macAddress[3] == 0xff &&
        macAddress[4] == 0xff && macAddress[5] == 0xff) {
        System_abort("Change the macAddress variable to match your board's MAC sticker");
    }

    /* Once EMAC_init is called, EMAC_config cannot be changed */
    EMAC_init();
}

/*
 *  =============================== General ===============================
 */
/*
 *  ======== TMDXDOCKH52C1_initGeneral ========
 */
void TMDXDOCKH52C1_initGeneral(void)
{
    /* Disable Protection */
    HWREG(SYSCTL_MWRALLOW) =  0xA5A5A5A5;

    /* Enable clock supply for the following peripherals */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOH);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);

    /* Disable clock supply for the watchdog modules */
    SysCtlPeripheralDisable(SYSCTL_PERIPH_WDOG1);
    SysCtlPeripheralDisable(SYSCTL_PERIPH_WDOG0);
}

/*
 *  =============================== GPIO ===============================
 */
/* Place into subsections to allow the TI linker to remove items properly */
#pragma DATA_SECTION(GPIOTiva_config, ".const:GPIOTiva_config")

#include <ti/drivers/GPIO.h>
#include <ti/drivers/gpio/GPIOTiva.h>

/*
 * Array of Pin configurations
 * NOTE: The order of the pin configurations must coincide with what was
 *       defined in TMDXDOCKH52C1.h
 * NOTE: Pins not used for interrupts should be placed at the end of the
 *       array.  Callback entries can be omitted from callbacks array to
 *       reduce memory usage.
 */
GPIO_PinConfig gpioPinConfigs[] = {
    /* Input pins */
    /* TMDXDOCKH52C1_BUTTON */
    GPIOTiva_PB_4 | GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_RISING,

    /* Output pins */
    /* TMDXDOCKH52C1_LD2 */
    GPIOTiva_PC_6 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_HIGH | GPIO_CFG_OUT_LOW,
    /* TMDXDOCKH52C1_LD3 */
    GPIOTiva_PC_7 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_HIGH | GPIO_CFG_OUT_LOW,
};

/*
 * Array of callback function pointers
 * NOTE: The order of the pin configurations must coincide with what was
 *       defined in TMDXDOCKH52C1.h
 * NOTE: Pins not used for interrupts can be omitted from callbacks array to
 *       reduce memory usage (if placed at end of gpioPinConfigs array).
 */
GPIO_CallbackFxn gpioCallbackFunctions[] = {
    NULL   /* TMDXDOCKH52C1_BUTTON */
};

/* The device-specific GPIO_config structure */
const GPIOTiva_Config GPIOTiva_config = {
    .pinConfigs = (GPIO_PinConfig *) gpioPinConfigs,
    .callbacks = (GPIO_CallbackFxn *) gpioCallbackFunctions,
    .numberOfPinConfigs = sizeof(gpioPinConfigs) / sizeof(GPIO_PinConfig),
    .numberOfCallbacks = sizeof(gpioCallbackFunctions)/sizeof(GPIO_CallbackFxn),
    .intPriority = (~0)
};

/*
 *  ======== TMDXDOCKH52C1_initGPIO ========
 */
void TMDXDOCKH52C1_initGPIO(void)
{
    /* Initialize peripheral and pins */
    GPIO_init();

    GPIO_write(TMDXDOCKH52C1_LD2, TMDXDOCKH52C1_LED_OFF);
    GPIO_write(TMDXDOCKH52C1_LD3, TMDXDOCKH52C1_LED_OFF);
}

/*
 *  =============================== I2C ===============================
 */
/* Place into subsections to allow the TI linker to remove items properly */
#pragma DATA_SECTION(I2C_config, ".const:I2C_config")
#pragma DATA_SECTION(i2cTivaHWAttrs, ".const:i2cTivaHWAttrs")

#include <ti/drivers/I2C.h>
#include <ti/drivers/i2c/I2CTiva.h>

/* I2C objects */
I2CTiva_Object i2cTivaObjects[TMDXDOCKH52C1_I2CCOUNT];

/* I2C configuration structure, describing which pins are to be used */
const I2CTiva_HWAttrs i2cTivaHWAttrs[TMDXDOCKH52C1_I2CCOUNT] = {
    {I2C0_MASTER_BASE, INT_I2C0, ~0 /* Interrupt priority */},
    {I2C1_MASTER_BASE, INT_I2C1, ~0 /* Interrupt priority */}
};

const I2C_Config I2C_config[] = {
    {&I2CTiva_fxnTable, &i2cTivaObjects[0], &i2cTivaHWAttrs[0]},
    {&I2CTiva_fxnTable, &i2cTivaObjects[1], &i2cTivaHWAttrs[1]},
    {NULL, NULL, NULL}
};

/*
 *  ======== TMDXDOCKH52C1_initI2C ========
 */
void TMDXDOCKH52C1_initI2C(void)
{
    /* I2C0 Init */
    /* Enable the peripheral */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);

    /* Configure the appropriate pins to be I2C instead of GPIO. */
    GPIOPinUnlock(GPIO_PORTB_BASE, GPIO_PIN_7);
    GPIOPinConfigure(GPIO_PB7_I2C0SCL); /* GPIO15 on Concerto base board */
    GPIOPinConfigure(GPIO_PB6_I2C0SDA); /* GPIO14 on Concerto base board */
    GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_6 | GPIO_PIN_7);

    /* I2C1 Init */
    /* Enable the peripheral */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C1);

    /* Configure the appropriate pins to be I2C instead of GPIO. */
    GPIOPinConfigure(GPIO_PA0_I2C1SCL); /* GPIO00 on Concerto base board */
    GPIOPinConfigure(GPIO_PA1_I2C1SDA); /* GPIO01 on Concerto base board */
    GPIOPinTypeI2C(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    I2C_init();
}

/*
 *  =============================== SDSPI ===============================
 */
/* Place into subsections to allow the TI linker to remove items properly */
#pragma DATA_SECTION(SDSPI_config, ".const:SDSPI_config")
#pragma DATA_SECTION(sdspiTivaHWattrs, ".const:sdspiTivaHWattrs")

#include <ti/drivers/SDSPI.h>
#include <ti/drivers/sdspi/SDSPITiva.h>

/* SDSPI objects */
SDSPITiva_Object sdspiTivaObjects[TMDXDOCKH52C1_SDSPICOUNT];

/* SDSPI configuration structure, describing which pins are to be used */
const SDSPITiva_HWAttrs sdspiTivaHWattrs[TMDXDOCKH52C1_SDSPICOUNT] = {
    {
        SSI0_BASE,          /* SPI base address */

        GPIO_PORTD_BASE,    /* SPI SCK PORT */
        GPIO_PIN_2,         /* SCK PIN */
        GPIO_PORTD_BASE,    /* SPI MISO PORT*/
        GPIO_PIN_1,         /* MISO PIN */
        GPIO_PORTD_BASE,    /* SPI MOSI PORT */
        GPIO_PIN_0,         /* MOSI PIN */
        GPIO_PORTD_BASE,    /* GPIO CS PORT */
        GPIO_PIN_3,         /* CS PIN */
    }
};

const SDSPI_Config SDSPI_config[] = {
    {&SDSPITiva_fxnTable, &sdspiTivaObjects[0], &sdspiTivaHWattrs[0]},
    {NULL, NULL, NULL}
};

/*
 *  ======== TMDXDOCKH52C1_initSDSPI ========
 */
void TMDXDOCKH52C1_initSDSPI(void)
{
    /* Enable the peripherals used by the SD Card */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);

    /* Configure SSI Peripheral pin muxing */
    GPIOPinConfigure(GPIO_PD2_SSI0CLK);
    GPIOPinConfigure(GPIO_PD0_SSI0TX);
    GPIOPinConfigure(GPIO_PD1_SSI0RX);

    /* Configure pad settings */
    GPIOPadConfigSet(GPIO_PORTD_BASE,
            GPIO_PIN_2 | GPIO_PIN_1 | GPIO_PIN_0,
            GPIO_PIN_TYPE_STD_WPU);

    GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_3, GPIO_PIN_TYPE_STD_WPU);

    SDSPI_init();
}

/*
 *  =============================== SPI ===============================
 */
/* Place into subsections to allow the TI linker to remove items properly */
#pragma DATA_SECTION(SPI_config, ".const:SPI_config")
#pragma DATA_SECTION(spiTivaDMAHWAttrs, ".const:spiTivaDMAHWAttrs")

#include <ti/drivers/SPI.h>
#include <ti/drivers/spi/SPITivaDMA.h>

/* SPI objects */
SPITivaDMA_Object spiTivaDMAObjects[TMDXDOCKH52C1_SPICOUNT];
#pragma DATA_SECTION(spiTivaDMAscratchBuf, ".dma");
#pragma DATA_ALIGN(spiTivaDMAscratchBuf, 32)
uint32_t spiTivaDMAscratchBuf[TMDXDOCKH52C1_SPICOUNT];

/* SPI configuration structure */
const SPITivaDMA_HWAttrs spiTivaDMAHWAttrs[TMDXDOCKH52C1_SPICOUNT] = {
    {
        SSI0_BASE,
        INT_SSI0,
                ~0,     /* Interrupt priority */
        &spiTivaDMAscratchBuf[0],
        0,
        UDMA_CHANNEL_SSI0RX,
        UDMA_CHANNEL_SSI0TX,
        uDMAChannel8_15SelectDefault,
        UDMA_CHAN10_DEF_SSI0RX_M,
        UDMA_CHAN11_DEF_SSI0TX_M
    },
    {
        SSI1_BASE,
        INT_SSI1,
                ~0,     /* Interrupt priority */
        &spiTivaDMAscratchBuf[1],
        0,
        UDMA_CHANNEL_SSI1RX,
        UDMA_CHANNEL_SSI1TX,
        uDMAChannel24_31SelectDefault,
        UDMA_CHAN24_DEF_SSI1RX_M,
        UDMA_CHAN25_DEF_SSI1TX_M
    },
    {
        SSI2_BASE,
        INT_SSI2,
                ~0,     /* Interrupt priority */
        &spiTivaDMAscratchBuf[2],
        0,
        UDMA_THRD_CHANNEL_SSI2RX,
        UDMA_THRD_CHANNEL_SSI2TX,
        uDMAChannel8_15SelectAltMapping,
        UDMA_CHAN12_THRD_SSI2RX,
        UDMA_CHAN13_THRD_SSI2TX
    },
    {
        SSI3_BASE,
        INT_SSI3,
                ~0,     /* Interrupt priority */
        &spiTivaDMAscratchBuf[3],
        0,
        UDMA_THRD_CHANNEL_SSI3RX,
        UDMA_THRD_CHANNEL_SSI3TX,
        uDMAChannel8_15SelectAltMapping,
        UDMA_CHAN14_THRD_SSI3RX,
        UDMA_CHAN15_THRD_SSI3TX
    }
};

const SPI_Config SPI_config[] = {
    {&SPITivaDMA_fxnTable, &spiTivaDMAObjects[0], &spiTivaDMAHWAttrs[0]},
    {&SPITivaDMA_fxnTable, &spiTivaDMAObjects[1], &spiTivaDMAHWAttrs[1]},
    {&SPITivaDMA_fxnTable, &spiTivaDMAObjects[2], &spiTivaDMAHWAttrs[2]},
    {&SPITivaDMA_fxnTable, &spiTivaDMAObjects[3], &spiTivaDMAHWAttrs[3]},
    {NULL, NULL, NULL},
};

/*
 *  ======== TMDXDOCKH52C1_initSPI ========
 */
void TMDXDOCKH52C1_initSPI(void)
{
    /* SSI0 */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);

    GPIOPinConfigure(GPIO_PA2_SSI0CLK);
    GPIOPinConfigure(GPIO_PA3_SSI0FSS);
    GPIOPinConfigure(GPIO_PA4_SSI0RX);
    GPIOPinConfigure(GPIO_PA5_SSI0TX);

    GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_2 | GPIO_PIN_3 |
                                    GPIO_PIN_4 | GPIO_PIN_5);

    /* SSI1 */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI1);

    GPIOPinConfigure(GPIO_PE0_SSI1CLK);
    GPIOPinConfigure(GPIO_PE1_SSI1FSS);
    GPIOPinConfigure(GPIO_PE2_SSI1RX);
    GPIOPinConfigure(GPIO_PE3_SSI1TX);

    GPIOPinTypeSSI(GPIO_PORTE_BASE, GPIO_PIN_0 | GPIO_PIN_1 |
                                    GPIO_PIN_2 | GPIO_PIN_3);
    TMDXDOCKH52C1_initDMA();
    SPI_init();
}

/*
 *  =============================== UART ===============================
 */
/* Place into subsections to allow the TI linker to remove items properly */
#pragma DATA_SECTION(UART_config, ".const:UART_config")
#pragma DATA_SECTION(uartTivaHWAttrs, ".const:uartTivaHWAttrs")

#include <ti/drivers/UART.h>
#include <ti/drivers/uart/UARTTiva.h>

/* UART objects */
UARTTiva_Object uartTivaObjects[TMDXDOCKH52C1_UARTCOUNT];
unsigned char uartTivaRingBuffer[32];

/* UART configuration structure */
const UARTTiva_HWAttrs uartTivaHWAttrs[TMDXDOCKH52C1_UARTCOUNT] = {
    {/* TMDXDOCKH52C1_UART0 */
        .baseAddr = UART0_BASE,
        .intNum = INT_UART0,
        .intPriority = ~0,
        .flowControl = UART_FLOWCONTROL_NONE,
        .ringBufPtr  = uartTivaRingBuffer,
        .ringBufSize = sizeof(uartTivaRingBuffer)
    }
};

const UART_Config UART_config[] = {
    {
        &UARTTiva_fxnTable,
        &uartTivaObjects[0],
        &uartTivaHWAttrs[0]
    },
    {NULL, NULL, NULL}
};

/*
 *  ======== TMDXDOCKH52C1_initUART ========
 */
void TMDXDOCKH52C1_initUART(void)
{
    /* Enable and configure the peripherals used by the uart. */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    GPIOPinTypeUART(GPIO_PORTE_BASE, GPIO_PIN_4 | GPIO_PIN_5);
    GPIOPinConfigure(GPIO_PE4_U0RX);
    GPIOPinConfigure(GPIO_PE5_U0TX);
    GPIOPadConfigSet(GPIO_PORTE_BASE, GPIO_PIN_4 | GPIO_PIN_5, GPIO_PIN_TYPE_STD_WPU);

    /* Initialize the UART driver */
    UART_init();
}

/*
 *  =============================== USB ===============================
 */
/*
 *  ======== TMDXDOCKH52C1_initUSB ========
 *  This function just turns on the USB
 */
void TMDXDOCKH52C1_initUSB(TMDXDOCKH52C1_USBMode usbMode)
{
    /*
     * Setup USB clock tree for 60MHz
     * 20MHz * 12 / 4 = 60
     */
    SysCtlUSBPLLConfigSet(
            (SYSCTL_UPLLIMULT_M & 12) | SYSCTL_UPLLCLKSRC_X1 | SYSCTL_UPLLEN);

    /* Setup pins for USB operation */
    GPIOPinTypeUSBAnalog(GPIO_PORTF_BASE, GPIO_PIN_6);
    GPIOPinTypeUSBAnalog(
            GPIO_PORTG_BASE, GPIO_PIN_2 | GPIO_PIN_5 | GPIO_PIN_6);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_USB0);

    /* Additional configurations for Host mode */
    if (usbMode == TMDXDOCKH52C1_USBHOST) {
        /* Configure the pins needed */
        GPIOPinConfigure(GPIO_PC5_USB0EPEN);
        GPIOPinConfigure(GPIO_PJ1_USB0PFLT);
        GPIOPinTypeUSBDigital(GPIO_PORTC_BASE, GPIO_PIN_5);
        GPIOPinTypeUSBDigital(GPIO_PORTJ_BASE, GPIO_PIN_1);
    }
}

/*
 *  =============================== USBMSCHFatFs ===============================
 */
/* Place into subsections to allow the TI linker to remove items properly */
#pragma DATA_SECTION(USBMSCHFatFs_config, ".const:USBMSCHFatFs_config")
#pragma DATA_SECTION(usbmschfatfstivaHWAttrs, ".const:usbmschfatfstivaHWAttrs")

#include <ti/drivers/USBMSCHFatFs.h>
#include <ti/drivers/usbmschfatfs/USBMSCHFatFsTiva.h>

/* USBMSCHFatFs objects */
USBMSCHFatFsTiva_Object usbmschfatfstivaObjects[TMDXDOCKH52C1_USBMSCHFatFsCOUNT];

/* USBMSCHFatFs configuration structure, describing which pins are to be used */
const USBMSCHFatFsTiva_HWAttrs usbmschfatfstivaHWAttrs[TMDXDOCKH52C1_USBMSCHFatFsCOUNT] = {
    {INT_USB0, ~0 /* Interrupt priority */}
};

const USBMSCHFatFs_Config USBMSCHFatFs_config[] = {
    {
        &USBMSCHFatFsTiva_fxnTable,
        &usbmschfatfstivaObjects[0],
        &usbmschfatfstivaHWAttrs[0]
    },
    {NULL, NULL, NULL}
};

/*
 *  ======== TMDXDOCKH52C1_initUSBMSCHFatFs ========
 */
void TMDXDOCKH52C1_initUSBMSCHFatFs(void)
{
    /* Call the USB initialization function for the USB Reference modules */
    TMDXDOCKH52C1_initUSB(TMDXDOCKH52C1_USBHOST);
    USBMSCHFatFs_init();
}

/*
 *  =============================== Watchdog ===============================
 */
/* Place into subsections to allow the TI linker to remove items properly */
#pragma DATA_SECTION(Watchdog_config, ".const:Watchdog_config")
#pragma DATA_SECTION(watchdogTivaHWAttrs, ".const:watchdogTivaHWAttrs")

#include <ti/drivers/Watchdog.h>
#include <ti/drivers/watchdog/WatchdogTiva.h>

/* Watchdog objects */
WatchdogTiva_Object watchdogTivaObjects[TMDXDOCKH52C1_WATCHDOGCOUNT];

/* Watchdog configuration structure */
const WatchdogTiva_HWAttrs watchdogTivaHWAttrs[TMDXDOCKH52C1_WATCHDOGCOUNT] = {
    /* TMDXDOCKH52C1_WATCHDOG0 with 1 sec period at default CPU clock freq */
    {WATCHDOG0_BASE, INT_WATCHDOG, ~0 /* Interrupt priority */, 75000000},
};

const Watchdog_Config Watchdog_config[] = {
    {&WatchdogTiva_fxnTable, &watchdogTivaObjects[0], &watchdogTivaHWAttrs[0]},
    {NULL, NULL, NULL},
};

/*
 *  ======== TMDXDOCKH52C1_initWatchdog ========
 */
void TMDXDOCKH52C1_initWatchdog(void)
{
    /* Enable peripherals used by Watchdog */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_WDOG0);

    /* Initialize the Watchdog driver */
    Watchdog_init();
}
/*
 *  @(#) ti.ndk.benchmarks.sizing; 1,0,0,0; 3-24-2015 15:39:24; /db/vtree/library/trees/ndktest/ndktest-c17/src/ xlibrary

 */

