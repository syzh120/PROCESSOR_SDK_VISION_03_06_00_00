/*
 *  Copyright (C) 2010-2017 Texas Instruments Incorporated
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
 *  \file   i2csample_io.c
 *
 *  \brief  This file contains sample code to demonstrate the I2C driver
 *          implemented for SYS/BIOS
 *
 *   This file performs tests on the following:
 *
 *      1. Blink the LEDS connected to the user LEDs on TCA6416
 *
 *
 *   Note
 *      1. The sample application is written for TI814X EVM.
 *      2. The only available i2c instance for sample application use is I2c0
 *      3. This instance of I2c is connected to TCA6416 expander on the EVM and
 *         hence application uses this device for demonstration of I2c driver
 *         usage.
 *
 */

/* ========================================================================== */
/*                          INCLUDE FILES                                     */
/* ========================================================================== */

#include <stdio.h>
#include <xdc/std.h>
#include <string.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/knl/Task.h>

#include <ti/sysbios/io/GIO.h>
#include <ti/sysbios/io/IOM.h>
#include <ti/drv/stw_lld/i2clld/lld_hsi2c.h>

/* ========================================================================== */
/*                            MACRO DEFINTIONS                                */
/* ========================================================================== */

#define I2C_TRANSFER_SIZE         (5U)

/* Refer to PCF8575PWR I2C expander PCF8575PWR for mode details               */
#if defined (SOC_TDA3XX)
#define I2C_SLAVE_ADDR            (0x22U) /* i2c address of TCA6424           */
#else
#define I2C_SLAVE_ADDR            (0x20U) /* i2c address of PCF8575PWR        */
#endif

#define I2C_EXP_PORT0_LED_ON      (0xF0U) /* This will turn on the LEDs       */
#define I2C_EXP_PORT0_LED_OFF     (0x00U) /* This will turn off the LEDs      */
#define BLINKLEDNUM  (0x10U)
#define BLINKLEDNUMCORRTN (0xFU)

#if defined (SOC_TDA3XX)
#define TCA6424_CMD_AUTO_INC            ((UInt8) 0x80U)

/* Output register to change state of output BIT set to 1, output set HIGH */
#define TCA6424_REG_OUTPUT0             ((UInt8) 0x04U)
#define TCA6424_REG_OUTPUT1             ((UInt8) 0x05U)
#define TCA6424_REG_OUTPUT2             ((UInt8) 0x06U)

/* Configuration register. BIT = '1' sets port to input, BIT = '0' sets
 * port to output */
#define TCA6424_REG_CONFIG0             ((UInt8) 0x0CU)
#define TCA6424_REG_CONFIG1             ((UInt8) 0x0DU)
#define TCA6424_REG_CONFIG2             ((UInt8) 0x0EU)

#endif

/* ========================================================================== */
/*                            GLOBAL VARIABLES                                */
/* ========================================================================== */

/* buffer aligned to cache line is required when working in DMA Mode          */
#pragma DATA_ALIGN(wBuffer, 128);
UInt8      wBuffer[I2C_TRANSFER_SIZE];

#pragma DATA_ALIGN(rBuffer, 128);
UInt8      rBuffer[I2C_TRANSFER_SIZE];

GIO_Handle i2c_outHandle;                         /* Handle to the TX channel */
GIO_Handle i2c_inHandle;                          /* Handle to the RX channel */

/* Global function prototypes */
void user_i2c_init(void);

/* ========================================================================== */
/*                          LOCAL FUNCTION PROTOTYPE                          */
/* ========================================================================== */

static void readExpanderPort(Error_Block *eb);
static void ledBlink(Error_Block *eb);
static void i2cExpander_WritePort(const Uint8 *data, Error_Block *eb);
static void initialize_ioexp(Error_Block *eb);
static void i2c_Write_port(Uint8       *data,
                           UInt32       numBytes,
                           UInt32       slaveAddr,
                           Error_Block *eb);

/* ========================================================================== */
/*                           FUNCTION DEFINITIONS                             */
/* ========================================================================== */

/* \fn      start_i2c_sample
 *
 * \brief   Function to illustrate usage of I2C driver.
 *
 *  This function will illustrate the usage of I2C driver by writing to the I2c
 *  expander to blink the user LEDs connected to the TCA6416 expander
 * \param   None
 * \return  None
 */

void start_i2c_sample(void)
{
    Error_Block eb;
    lld_hsi2c_datatfr_params_t i2cXferParams;
    GIO_Params  ioParams;

    Error_init(&eb);

    /*
     * Initialize channel attributes.
     */
    GIO_Params_init(&ioParams);

    ioParams.chanParams = (void *) &i2cXferParams;

    System_printf("\r\nI2C  :Start of I2C sample application\r\n");

    /* Create the I2C Channels for the TX and RX communication                */
    i2c_outHandle = GIO_create("i2c0", GIO_OUTPUT, &ioParams, &eb);
    i2c_inHandle  = GIO_create("i2c0", GIO_INPUT, &ioParams, &eb);

    if ((NULL == i2c_outHandle) || (NULL == i2c_inHandle))
    {
        System_printf("\r\nI2C : I2C Handle Create Failed.......! \r\n");
    }
    else
    {
        /* Call function for the I2c read write test                          */
        ledBlink(&eb);
    }
    System_printf("\r\nI2C  :End of I2C sample application\r\n");
}

/* \fn      ledBlink
 *
 * \brief   Function to read and write the I2C expander TCA6416.
 *
 *  This function will illustrate the usage of I2C driver by writing data to the
 *  I2C expander which will in turn blink the User LEDs connected to it.
 *
 * \param   None
 * \return  None
 */
static void ledBlink(Error_Block *eb)
{
    volatile Int8 ledBlinkCount = 20;
    Uint8         value;
    Uint8         bitval;
    Uint8         counter = 0;

    System_printf("I2C expander/LEDs write/read test started\r\n");

    initialize_ioexp(eb);

    while (0 != ledBlinkCount)
    {
        /* Modify the P0 values to switch ON the LED                          */
        value = I2C_EXP_PORT0_LED_ON;
        i2cExpander_WritePort(&value, eb);

        readExpanderPort(eb);

        Task_sleep(500);

        value = I2C_EXP_PORT0_LED_OFF;
        i2cExpander_WritePort(&value, eb);

        readExpanderPort(eb);

        value = I2C_EXP_PORT0_LED_ON;
        Task_sleep(500);
        while (1)
        {
            value = value << 1U;
            i2cExpander_WritePort(&value, eb);
            Task_sleep(500);
            if (value == 0U)
            {
                break;
            }
        }
        System_printf(
            "\r\nI2C expander/LEDs write/read test "
            "\r\nNow Each LED Blinks Independently...\r\n");
        bitval = BLINKLEDNUM;
        while (counter < 8)
        {
            value = (UInt8) ~bitval | BLINKLEDNUMCORRTN;
            i2cExpander_WritePort(&value, eb);
            Task_sleep(500);
            bitval = bitval << 1U;
            counter++;
            if (bitval == 0U)
            {
                break;
            }
        }
        counter = 0;

        Task_sleep(500);

        ledBlinkCount--;

        System_printf("LED Blinking Down Counter: %d\r\n", ledBlinkCount);
    }
}

/* Perform write operation on port0                                           */
static void i2c_Write_port(Uint8       *data,
                           UInt32       numBytes,
                           UInt32       slaveAddr,
                           Error_Block *eb)
{
    lld_hsi2c_datatfr_params_t i2cXferParams;
    Int32 status = 0;

    /* Prepare the data to be written to the port                             */
    i2cXferParams.slaveAddr = slaveAddr;
    i2cXferParams.buffer    = &data[0];
    i2cXferParams.bufLen    = numBytes;
    i2cXferParams.flags     = LLD_HSI2C_WRITE | LLD_HSI2C_MASTER |
                              LLD_HSI2C_START | LLD_HSI2C_STOP;
    i2cXferParams.timeout = 4000;

    /* Write the data to I2c expander                                         */
    status = GIO_submit(i2c_outHandle,
                        IOM_WRITE,
                        &i2cXferParams,
                        &i2cXferParams.bufLen,
                        NULL);
    if (status != 0)
    {
        System_printf("I2C Write Failed, error status %d\r\n", status);
    }
}

/**
 * \brief     Function to read the data from the IO expander using the I2c
 *            driver.
 *
 * \param     eb   [OUT]   pointer to Error block
 *
 * \return    None
 */
static void i2c_Read_port(Uint8       *data,
                          UInt32       numBytes,
                          UInt32       slaveAddr,
                          Error_Block *eb)
{
    lld_hsi2c_datatfr_params_t i2cXferParams;
    UInt32 size = 0;

    /* Prepare the data to be written to the expander                         */
    i2cXferParams.slaveAddr = slaveAddr;
    i2cXferParams.buffer    = &data[0];
    i2cXferParams.bufLen    = numBytes;
    i2cXferParams.flags     = LLD_HSI2C_READ | LLD_HSI2C_MASTER |
                              LLD_HSI2C_START | LLD_HSI2C_STOP;
    i2cXferParams.timeout = 4000;
    /* Send the data on the i2c bus                                           */
    GIO_submit(i2c_outHandle,
               IOM_WRITE,
               &i2cXferParams,
               &i2cXferParams.bufLen,
               NULL);

    if ((TRUE == Error_check(eb)) && (i2cXferParams.bufLen != size))
    {
        System_printf("\r\nI2C Expander read port failed!");
    }
}

static void initialize_ioexp(Error_Block *eb)
{
#if defined (SOC_TDA3XX)
    /* Configure every pin as output */
    /* TCA6424 2 IO expander 1 is input, 0 is output */
    wBuffer[0] = TCA6424_REG_CONFIG0 | TCA6424_CMD_AUTO_INC;
    wBuffer[1] = 0x0U;
    i2c_Write_port(&wBuffer[0], 2U, I2C_SLAVE_ADDR, eb);
#endif
}

#if defined (SOC_TDA3XX)
static void i2cExpander_WritePort(const Uint8 *data, Error_Block *eb)
{
    rBuffer[0] = 0;
    readExpanderPort(eb);
    /* Clear the last 4 bits of rBuffer[0] */
    rBuffer[0] &= 0xF0U;
    wBuffer[0]  = TCA6424_REG_OUTPUT0 | (UInt32) TCA6424_CMD_AUTO_INC;
    /* Modify only last 4 bits which are connected to LEDs */
    wBuffer[1] = rBuffer[0] | (((*data) >> 4U) & 0x0FU);
    wBuffer[2] = rBuffer[0];
    i2c_Write_port(&wBuffer[0], 3U, I2C_SLAVE_ADDR, eb);
}

static void readExpanderPort(Error_Block *eb)
{
    UInt8  tempRegVal;
    UInt32 i;
    memset(rBuffer, 0x00, I2C_TRANSFER_SIZE);

    for (i = 0U; i < 3U; i++)
    {
        tempRegVal = TCA6424_REG_OUTPUT0 + i;
        i2c_Write_port(&tempRegVal, 1U, I2C_SLAVE_ADDR, eb);
        i2c_Read_port(&rBuffer[i], 1U, I2C_SLAVE_ADDR, eb);
    }
}
#else
static void i2cExpander_WritePort(const Uint8 *data, Error_Block *eb)
{
    /* Assign data into output buffer                                         */
    /* First command word and then the data                                   */

    wBuffer[0] = *data;
    wBuffer[1] = rBuffer[0];
    i2c_Write_port(&wBuffer[0], 2U, I2C_SLAVE_ADDR, eb);
}

static void readExpanderPort(Error_Block *eb)
{
    memset(rBuffer, 0x00, I2C_TRANSFER_SIZE);

    i2c_Read_port(&rBuffer[0], 1U, I2C_SLAVE_ADDR, eb);
}
#endif
