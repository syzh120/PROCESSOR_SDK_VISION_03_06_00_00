/*
 *  Copyright (C) 2013-2017 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \brief This file demonstrates I2C dal by writing data to blink
 *         LED on and off.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <stdio.h>
#include <ti/csl/csl_i2c.h>
#include <ti/csl/soc.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
/* I2C address of TCA6424 expander - 2. */
#define HSI2C_SLAVE_ADDR            ((uint8_t) 0x22U)
#elif defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
/* I2C address of TPIC2810  */
#define HSI2C_SLAVE_ADDR            ((uint8_t) 0x60U)
#else
/* I2C address of PCF8575 expander. */
#define HSI2C_SLAVE_ADDR            ((uint8_t) 0x20U)
#endif

/* Turn on the LEDs. */
#define HSI2C_EXP_PORT0_LED_ON      ((uint8_t) 0x00U)

/* Turn off the LEDs. */
#define HSI2C_EXP_PORT0_LED_OFF     ((uint8_t) 0xFU)

/* Number of times led toggles. */
#define HSI2C_LED_TOGGLE_NO         (10U)

/* Led toggle check value*/
#define HSI2C_LED_TOGGLE_END        (0U)

/* Transfer Size */
#define HSI2C_TRANSFER_SIZE         (5U)

#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
#define TCA6424_CMD_AUTO_INC            ((uint8_t) 0x80U)

/* Output register to change state of output BIT set to 1, output set HIGH */
#define TCA6424_REG_OUTPUT0             ((uint8_t) 0x04U)
#define TCA6424_REG_OUTPUT1             ((uint8_t) 0x05U)
#define TCA6424_REG_OUTPUT2             ((uint8_t) 0x06U)

/* Configuration register. BIT = '1' sets port to input, BIT = '0' sets
 * port to output */
#define TCA6424_REG_CONFIG0             ((uint8_t) 0x0CU)
#define TCA6424_REG_CONFIG1             ((uint8_t) 0x0DU)
#define TCA6424_REG_CONFIG2             ((uint8_t) 0x0EU)

#endif

/* ===========================================================================*/
/*                          Global Variables                                  */
/* ===========================================================================*/
uint8_t dataToSlave[HSI2C_TRANSFER_SIZE];

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
void SetupI2C(void);
void sampleDelay(int32_t delay);
void SetupI2CTransmit(uint8_t *data, uint32_t numBytes);
static void ioexpDataWrite(uint8_t *data);
static void initialize_ioexp(void);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
int main()
{
    volatile uint8_t done = 1;
    uint8_t          data;
    /*
    ** Configures I2C to Master mode to generate start codition
    ** on I2C bus and to transmit data at a bus speed of  100khz
    */

    uint32_t         num;

    SetupI2C();

    initialize_ioexp();

    for (num = HSI2C_LED_TOGGLE_NO; num != HSI2C_LED_TOGGLE_END; num--)
    {
        data = HSI2C_EXP_PORT0_LED_ON;
        /*
         * **Transmits command byte and data to I/0 expander
         * **through I2C bus
         */
        ioexpDataWrite(&data);
        sampleDelay(0xFFFF);

        data = HSI2C_EXP_PORT0_LED_OFF; /*data to OFF LED*/
        ioexpDataWrite(&data);
        sampleDelay(0xFFFF);
    }

    while (done) ;

    return 0;
}

static void initialize_ioexp(void)
{
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
    /* TCA6424 ioexpander pins should be configure as output
     * In config register write 1 for input, 0 for output */
    dataToSlave[0] = TCA6424_REG_CONFIG0 | TCA6424_CMD_AUTO_INC;
    dataToSlave[1] = 0x0U;
    SetupI2CTransmit(&dataToSlave[0], 2);
#endif
}

#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
/* On tda3xx leds are connected on TCA6424 ioexpander - 2
 * LEDs are connected on port 0 first 4 bits, and ioexpander has 3 ports */
static void ioexpDataWrite(uint8_t *data)
{
    dataToSlave[0] = TCA6424_REG_OUTPUT0 | (uint32_t) TCA6424_CMD_AUTO_INC;
    dataToSlave[1] = ((*data) & 0x0FU);
    dataToSlave[2] = 0U;
    dataToSlave[3] = 0U;
    SetupI2CTransmit(&dataToSlave[0], 4);
}
#elif defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
/* On idkam572x leds are connected on TPCI2810 need to write a subaddress */
static void ioexpDataWrite(uint8_t *data)
{
    dataToSlave[0] = 0x11U;
    dataToSlave[1] = *data;
    SetupI2CTransmit(&dataToSlave[0], 2);
    dataToSlave[0] = 0x22U;
    SetupI2CTransmit(&dataToSlave[0], 1);
}
#else
/* On tda2xx and ti814x leds are connected on PCF8575 ioexpander
 * LEDs are connected on port 0 last 4 bits, and ioexpander has 2 ports */
static void ioexpDataWrite(uint8_t *data)
{
    dataToSlave[0] = (((*data) << 4U) & 0xF0U);
    dataToSlave[1] = 0U;
    SetupI2CTransmit(&dataToSlave[0], 2);
}

#endif

void SetupI2C(void)
{
    /* Do a software reset */
    I2CSoftReset(SOC_I2C1_BASE);

    /* Enable i2c module */
    I2CMasterEnable(SOC_I2C1_BASE);

    while (!I2CSystemStatusGet(SOC_I2C1_BASE)) ;

    /* Put i2c in reset/disabled state */
    I2CMasterDisable(SOC_I2C1_BASE);

    /* Configure i2c bus speed to 100khz */
#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
    I2CMasterInitExpClk(SOC_I2C1_BASE, 96000000,
                        4000000U, 100000);
#else
    I2CMasterInitExpClk(SOC_I2C1_BASE, 24000000,
                        8000000, 100000);
#endif

    I2COwnAddressSet(SOC_I2C1_BASE, 0,
                     I2C_OWN_ADDR_0);

    I2CSyscInit(SOC_I2C1_BASE, 0x08);

    /*Set Rx and Tx FIFO threshold value and reset the fifo*/
    I2CFIFOThresholdConfig(SOC_I2C1_BASE, 0, I2C_TX_MODE);

    I2CFIFOThresholdConfig(SOC_I2C1_BASE, 0, I2C_RX_MODE);

    /* Set i2c slave address */
    I2CMasterSlaveAddrSet(SOC_I2C1_BASE, HSI2C_SLAVE_ADDR);
    
    /* Bring i2c out of reset */
    I2CMasterEnable(SOC_I2C1_BASE);

    /* Enable free run mode */
    I2CMasterEnableFreeRun(SOC_I2C1_BASE);
}

void SetupI2CTransmit(uint8_t *data, uint32_t numBytes)
{
    uint32_t i;
    
    I2CFIFOClear(SOC_I2C1_BASE, I2C_TX_MODE);
    I2CFIFOClear(SOC_I2C1_BASE, I2C_RX_MODE);

    /*Clear all interrupt status*/
    I2CMasterIntClearEx(SOC_I2C1_BASE, I2C_INT_ALL);
    
    /* Set data count */
    I2CSetDataCount(SOC_I2C1_BASE, numBytes);

    /*
    ** Configure i2c as master-transmitter and to generate stop condition
    */
    I2CMasterControl(SOC_I2C1_BASE, I2C_CFG_MST_TX);
    
    /* generate start */
    I2CMasterStart(SOC_I2C1_BASE);

    /* wait for bus busy */
    while(I2CMasterBusBusy(SOC_I2C1_BASE)==0)
    {
    }

    for (i = 0; i < numBytes; i++)
    {
        /*Wait for transmit interrupt to occur*/
        while (I2CMasterIntRawStatusEx(SOC_I2C1_BASE,
                                       I2C_INT_TRANSMIT_READY) != 0x10) ;

        /* Send the data */
        I2CMasterDataPut(SOC_I2C1_BASE, data[i]);

        /*Disable transmit ready and stop condition interrupt*/
        I2CMasterIntClearEx(SOC_I2C1_BASE, I2C_INT_TRANSMIT_READY);
    }
    
    /* generate stop when requested */
    I2CMasterStop(SOC_I2C1_BASE);

    sampleDelay(5000);

    /*Clear data buffer length*/
    I2CSetDataCount(SOC_I2C1_BASE, 0);
}

void sampleDelay(int32_t delay)
{
    volatile int32_t i, j;

    for (i = 0; i < delay; i++)
    {
        for (j = 0; j < 100; j++) ;
    }
}
/********************************* End of file ******************************/

