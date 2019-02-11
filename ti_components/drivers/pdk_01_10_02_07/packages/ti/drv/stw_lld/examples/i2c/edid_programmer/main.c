/*
 *  Copyright (C) 2013 Texas Instruments Incorporated
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
 *  \file     edid_programmer_main.c
 *
 *  \brief    This file contains EDID programmer.
 *
 *  \details  This file contains EDID programmer.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include <ti/csl/tistdtypes.h>
#include <ti/csl/csl_types.h>
#include <ti/drv/stw_lld/uartconsole/uartStdio.h>
#include <ti/drv/stw_lld/examples/utility/stwutils_app.h>
#include <ti/csl/soc.h>

#include <ti/drv/stw_lld/i2clld/lld_hsi2c.h>
#include <ti/drv/stw_lld/i2clld/src/lld_hsi2c_edma.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/csl/arch/csl_arch.h>

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */
#define EEPROM_I2C_ADDR             (0x50U)

#ifdef __ARM_ARCH_7A__
#if defined (SOC_TDA2EX) || defined (SOC_TDA2PX)
#define I2C5_INT_NUM                (61U)
#else
#define I2C2_INT_NUM                (56U)
#endif
#endif

#ifdef __TI_ARM_V7M4__
#define I2C2_INT_NUM                (41U)
#endif

#define POLLED_MODE                 (1)
#define PAGE_SIZE                   (8)

#define PRGRM                       ('1')
#define VERIFY                      ('2')
#define EXIT(opt)                   (('x' == opt) || ('X' == opt))

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static uint8_t       gPageData[PAGE_SIZE + 2];
static uint8_t       gEepromReadData[256] = {0};

static const uint8_t gEdid1080p60[] =
{
    0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x4D, 0x29, 0x09, 0x05,
    0x0A, 0x00, 0x00, 0x00, 0x1A, 0x14, 0x01, 0x03, 0x80, 0x52, 0x2E, 0x78,
    0x2A, 0x1B, 0xBE, 0xA2, 0x55, 0x34, 0xB3, 0x26, 0x14, 0x4A, 0x52, 0xAF,
    0xCE, 0x00, 0x81, 0x80, 0x90, 0x40, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x3A, 0x80, 0x18, 0x71, 0x38,
    0x2D, 0x40, 0x58, 0x2C, 0x45, 0x00, 0x34, 0xCD, 0x31, 0x00, 0x00, 0x1E,
    0x66, 0x21, 0x50, 0xB0, 0x51, 0x00, 0x1B, 0x30, 0x40, 0x70, 0x36, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x48,
    0x44, 0x4D, 0x49, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A,
    0x00, 0x00, 0x00, 0xFD, 0x00, 0x37, 0x4C, 0x0F, 0x44, 0x0A, 0x0F, 0x00,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x01, 0x6E, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF
};
int32_t gTestStatus = STW_SOK;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static int32_t programEdid(hsI2cHandle i2cHandle);
static int32_t verifyEdid(hsI2cHandle i2cHandle);

static void sampleDelay(int32_t delay);
static void mainMenu();

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int main(void)
{
    hsI2cHandle           i2cHandle;
    lld_hsi2c_initParam_t initPar;
    hsI2cObjHandle        i2cObjHandle;
    int32_t retVal = LLD_HSI2C_SUCCESS;
    char mainMenuOption;
    LLD_Hsi2cInstId_t     i2cInstId;
    uint32_t enableAutorun = 0, testID;
    int32_t  getCharRetVal;
    uint32_t testFlag = 0;

    PlatformUartConsoleSetPinMux();
    UARTStdioInit();
    UARTPuts("\r\nI2C EDID Programmer Test Application ", -1);

#if defined (SOC_TDA2XX)
    PlatformI2C2SetPinMux();
#elif defined (SOC_TDA2EX) || defined (SOC_TDA2PX)
    PlatformI2C5SetPinMux();
#endif

#if defined (SOC_TDA2EX) || defined (SOC_TDA2PX)
    initPar.i2cIntNum = I2C5_INT_NUM;
    i2cInstId         = HSI2C_INST_4;
#else
    initPar.i2cIntNum = I2C2_INT_NUM;
    i2cInstId         = HSI2C_INST_1;
#endif

    initPar.i2cBusFreq = I2C_NORMAL;
    initPar.opMode     = HSI2C_OPMODE_INTERRUPT;
#if POLLED_MODE
    initPar.opMode = HSI2C_OPMODE_POLLED;
#endif
    initPar.i2cOwnAddr   = 0xFE;
    initPar.is10BitAddr  = 0;
    initPar.isMasterMode = 1;

    lld_i2c_init(&i2cObjHandle, i2cInstId, &initPar);
    i2cHandle = lld_i2c_open(i2cInstId, NULL, NULL);
    if (NULL == i2cHandle)
    {
        UARTPuts("\r\nI2C open failed!!", -1);
        StwUtils_appLogTestResult(STWUTILS_APP_TST_STATUS_FAIL);
        UARTPuts("\r\nI2C EDID Programmer Test Fail ", -1);
        return (-1);
    }

    do
    {
        /* Probe for EEPROM */
        retVal = lld_i2c_probe(i2cHandle, EEPROM_I2C_ADDR);
        if (retVal != LLD_HSI2C_SUCCESS)
        {
            UARTPuts("\r\nI2c Probe failed!!", -1);
            StwUtils_appLogTestResult(STWUTILS_APP_TST_STATUS_FAIL);
            UARTPuts("\r\nI2C EDID Programmer Test Fail ", -1);

#if defined (SOC_TDA2XX) || defined (SOC_TDA2EX) || defined (SOC_TDA2PX)
            UARTPuts("\r\nPlease ensure vision app board is connected and "
                     "both SW1-1 and SW1-2 on Vision app board is ON!!", -1);
#elif defined (SOC_TDA3XX)
            UARTPuts("\r\nPlease ensure SW80000-1 & SW80000-2 on board is ON!!",
                     -1);
#endif
            sampleDelay(10000);
        }
    } while (retVal != LLD_HSI2C_SUCCESS);

    mainMenu();

    getCharRetVal = StwUtils_appGetCharTimeout(
        (int8_t *) &mainMenuOption,
        STWUTILS_APP_UART_TIMEOUT_MSEC);
    if (STW_EFAIL == getCharRetVal)
    {
        /* Timeout - Enable Auto run Option */
        UARTPuts("\r\nUART read timeout (10 sec). Enable Auto Run !!", -1);
        enableAutorun = 1;
        testID        = 0;
    }
    else
    {
        enableAutorun = 0;
    }

    while (1)
    {
        if (enableAutorun == 0)
        {
            if (testFlag == 1)
            {
                mainMenu();
                UARTGets((char *) &mainMenuOption, 1);
            }
            else
            {
                testFlag = 1;
            }
            while (1)
            {
                if ((PRGRM == mainMenuOption) ||
                    (VERIFY == mainMenuOption) ||
                    EXIT(mainMenuOption))
                {
                    break;
                }
                else
                {
                    UARTPuts("\r\nEnter Valid option\r\n", -1);
                    /* Get option */
                    UARTGets(&mainMenuOption, 1);
                }
            }
        }
        else
        {
            if (testID == 0)
            {
                mainMenuOption = PRGRM;
                UARTPuts("\r\nProgram EDID for 1080p", -1);
            }
            else if (testID == 1)
            {
                UARTPuts("\r\nVerify EDID for 1080p", -1);
                mainMenuOption = VERIFY;
            }
            else if (testID == 2)
            {
                mainMenuOption = 'x';
            }
            testID++;
        }
        if (PRGRM == mainMenuOption)
        {
            UARTPuts("\r\nProcessing wait...", -1);
            retVal = programEdid(i2cHandle);
            if (retVal == LLD_HSI2C_SUCCESS)
            {
                UARTPuts("\r\nEDID programming successful!!", -1);
            }
            else
            {
                UARTPuts("\r\nEDID programming failed!!", -1);
                gTestStatus = STW_EFAIL;
            }
        }
        else if (VERIFY == mainMenuOption)
        {
            UARTPuts("\r\nProcessing wait...", -1);
            retVal = verifyEdid(i2cHandle);
            if (retVal == LLD_HSI2C_SUCCESS)
            {
                UARTPuts("\r\nEDID verification successful!!", -1);
            }
            else
            {
                UARTPuts("\r\nEDID verification failed!!", -1);
                gTestStatus = STW_EFAIL;
            }
        }
        else
        {
            UARTPuts("\r\nEDID board diagnostic test exiting...", -1);
            break;
        }
    }

    lld_i2c_close(&i2cHandle);
    lld_i2c_deinit(i2cInstId);

    if (gTestStatus == STW_SOK)
    {
        StwUtils_appLogTestResult(STWUTILS_APP_TST_STATUS_PASS);
        UARTPuts("\r\nI2C EDID Programmer Test Pass ", -1);
    }
    else
    {
        StwUtils_appLogTestResult(STWUTILS_APP_TST_STATUS_FAIL);
        UARTPuts("\r\nI2C EDID Programmer Test Fail ", -1);
    }

    return (0);
}

static int32_t programEdid(hsI2cHandle i2cHandle)
{
    volatile int32_t           retVal = LLD_HSI2C_SUCCESS;
    volatile uint32_t          count;
    volatile uint32_t          gArrayIdx = 0;
    lld_hsi2c_datatfr_params_t i2cXferParams;
    volatile uint32_t          j = 0;

    /* Write data to eeprom */
    i2cXferParams.bufLen    = (PAGE_SIZE + 1);
    i2cXferParams.buffer    = &gPageData[0];
    i2cXferParams.slaveAddr = (uint8_t) EEPROM_I2C_ADDR;
    i2cXferParams.timeout   = 4000;
    i2cXferParams.flags     = LLD_HSI2C_WRITE | LLD_HSI2C_MASTER |
                              LLD_HSI2C_START | LLD_HSI2C_STOP;

    for (j = 0; j < 256; j += 8)
    {
        gPageData[0] = j;        /* page address */
        for (count = 1; count < (PAGE_SIZE + 1); count++)
        {
            gPageData[count] = gEdid1080p60[gArrayIdx++];
        }
        retVal += lld_i2c_transfer(i2cHandle, &i2cXferParams);
        /* Wait for EEPROM to complete write */
        sampleDelay(1000);
    }

    if (retVal == LLD_HSI2C_SUCCESS)
    {
        retVal = verifyEdid(i2cHandle);
        if (retVal != LLD_HSI2C_SUCCESS)
        {
#if defined (SOC_TDA2XX) || defined (SOC_TDA2EX) || defined (SOC_TDA2PX)
            UARTPuts("\r\nPlease check SW1-2 of vision board for "
                     "WP pin position is ON!!", -1);
#elif defined (SOC_TDA3XX)
            UARTPuts("\r\nPlease check SW80000-2 on board for "
                     "WP pin position is ON!!", -1);
#endif
        }
    }

    return (retVal);
}

static int32_t verifyEdid(hsI2cHandle i2cHandle)
{
    volatile int32_t           retVal   = LLD_HSI2C_SUCCESS;
    volatile uint32_t          j        = 0;
    uint32_t                   mismatch = 0;
    lld_hsi2c_datatfr_params_t i2cXferParams;

    for (j = 0; j < 256; j += 8)
    {
        /* Write page address */
        gPageData[0]            = j;
        i2cXferParams.bufLen    = 1;
        i2cXferParams.buffer    = &gPageData[0];
        i2cXferParams.slaveAddr = (uint8_t) EEPROM_I2C_ADDR;
        i2cXferParams.timeout   = 4000;
        i2cXferParams.flags     = LLD_HSI2C_WRITE | LLD_HSI2C_MASTER |
                                  LLD_HSI2C_START | LLD_HSI2C_STOP;
        retVal = lld_i2c_transfer(i2cHandle, &i2cXferParams);
        sampleDelay(1000);

        /* Read page */
        i2cXferParams.bufLen = PAGE_SIZE;
        i2cXferParams.buffer = &gEepromReadData[j];
        i2cXferParams.flags  = LLD_HSI2C_READ | LLD_HSI2C_MASTER |
                               LLD_HSI2C_START | LLD_HSI2C_STOP;
        retVal = lld_i2c_transfer(i2cHandle, &i2cXferParams);
        sampleDelay(1000);
    }

    for (j = 0; j < 256; j++)
    {
        if (gEepromReadData[j] != gEdid1080p60[j])
        {
            mismatch = 1;
            break;
        }
    }

    if (mismatch)
    {
        retVal = LLD_HSI2C_FAIL;
    }
    else
    {
        retVal = LLD_HSI2C_SUCCESS;
    }

    return (retVal);
}

static void mainMenu()
{
    UARTPuts("\r\n\r\n**** EDID PROGRAMMING ****", -1);
    UARTPuts("\r\nMenu:", -1);
    UARTPuts("\r\n1. Program EDID for 1080p", -1);
    UARTPuts("\r\n2. Verify EDID for 1080p", -1);
    UARTPuts("\r\nx. Exit", -1);
    UARTPuts("\r\nSelect option : ", -1);

    return;
}

static void sampleDelay(int32_t delay)
{
    volatile int32_t i, j;

    for (i = 0; i < delay; i++)
    {
        for (j = 0; j < 100; j++)
        {}
    }

    return;
}
