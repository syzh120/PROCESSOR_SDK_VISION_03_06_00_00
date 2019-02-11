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
 *  \file stw_boardTda2ex.c
 *
 *  \brief File containing the Tda2ex STW board functions.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <stddef.h>
#include <ti/csl/csl_types.h>
#include <ti/drv/stw_lld/uartconsole/uartStdio.h>
#include <ti/drv/vps/include/osal/bsp_osal.h>
#include <ti/csl/csl_gpio.h>
#include <ti/drv/stw_lld/platform/stw_platform.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/csl/soc.h>
#include <ti/drv/stw_lld/i2clld/lld_hsi2c.h>
#include <ti/drv/stw_lld/devices/stw_device.h>
#include <ti/drv/stw_lld/boards/stw_board.h>
#include <ti/drv/stw_lld/boards/src/stw_boardPriv.h>
#include <stw_boardTda2exDefault.h>
#include <stw_boardTda2exVision.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Max of all the devices present in the board including any valid
 * combination of base board and daughter cards */
#define BOARD_MAX_DEVICE                    (20U)

/*  Base board PCF8575 1 (on I2C1) - mappings
 *  P1_5 - CON_LCD_PWR_DN
 */
#define BOARD_PCF8575_LCDCTRL_POWER_MASK    (PCF8575_P1_5_MASK)

/*  Base board PCF8575 3 (on I2C5) - mappings
 *  P0_2 - VIN2_S0
 *  P0_6 - VIN2_S2
 *  P0_7 - SEL_VIN4_MUX_S0
 *  P1_2 - MMC2_SEL
 */
#define BOARD_PCF8575_VIN2_S0               (PCF8575_P0_2_MASK)
#define BOARD_PCF8575_VIN2_S2               (PCF8575_P0_6_MASK)
#define BOARD_PCF8575_MMC2_SEL              (PCF8575_P1_2_MASK)

/* Video mux select for vision daughter card */
#define BOARD_GPIO_BASE_MUX_SEL             ((uint32_t) SOC_GPIO4_BASE)
#define BOARD_GPIO_PIN_MUX1_SEL0            ((uint32_t) 13U)
#define BOARD_GPIO_PIN_MUX1_SEL1            ((uint32_t) 14U)
#define BOARD_GPIO_PIN_MUX2_SEL0            ((uint32_t) 15U)
#define BOARD_GPIO_PIN_MUX2_SEL1            ((uint32_t) 16U)
#define BOARD_GPIO_BASE_DEMUX_FPD_A         ((uint32_t) SOC_GPIO2_BASE)
#define BOARD_GPIO_BASE_DEMUX_FPD_B         ((uint32_t) SOC_GPIO1_BASE)
#define BOARD_GPIO_BASE_DEMUX_FPD_C         ((uint32_t) SOC_GPIO6_BASE)
#define BOARD_GPIO_PIN_DEMUX_FPD_A          ((uint32_t) 29U)
#define BOARD_GPIO_PIN_DEMUX_FPD_B          ((uint32_t) 4U)
#define BOARD_GPIO_PIN_DEMUX_FPD_C          ((uint32_t) 7U)
#define BOARD_GPIO_BASE_POWER_DWN           ((uint32_t) SOC_GPIO6_BASE)
#define BOARD_GPIO_PIN_OV_PWDN              ((uint32_t) 17U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/** \brief EEPROM ID structure. */
typedef struct boardEepromId
{
    uint32_t header;
    char     boardName[16U];
    uint16_t versionMajor;
    uint16_t versionMinor;
    uint32_t configOption;
    uint32_t emif1Size;
    uint32_t emif2Size;
    char     reserved[20U];
} boardEepromId_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  Below ifdef __cplusplus is added so that C++ build passes without
 *  typecasting. This is because the prototype is build as C type
 *  whereas this file is build as CPP file. Hence we get C++ build error.
 *  Also if tyecasting is used, then we get MisraC error Rule 11.1.
 */
#ifdef __cplusplus
extern "C" {
#endif

static int32_t BOARDSelectDeviceTda2ex(uint32_t devDrvId, uint32_t instId);
static int32_t BOARDPowerOnDeviceTda2ex(uint32_t devDrvId,
                                        uint32_t instId,
                                        uint32_t powerOn);
static int32_t BOARDSelectDeviceTda2exVision(uint32_t devDrvId, uint32_t instId);
#ifdef __cplusplus
}
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
#if defined (SOC_TDA2EX)
extern boardPinmuxBoardCfg_t gBoardTda2exPinMuxData[
    NUM_OF_TDA2EXBOARD_PINMUX_CONFIGUARATIONS];
#endif
static boardI2cInstData_t    gBoardTda2exI2cInstData[] =
{
#ifndef STW_DISABLE_I2C0
    {
        HSI2C_INST_0,                       /* instId */
        SOC_I2C1_BASE,                      /* baseAddr */
        CSL_INTC_EVENTID_I2CINT1,           /* intNum */
        I2C_NORMAL                          /* busClkKHz */
    },
#endif
#if defined (SOC_TDA2EX)
    {
        HSI2C_INST_4,                       /* instId */
        SOC_I2C5_BASE,                      /* baseAddr */
        CSL_INTC_EVENTID_I2CINT5,           /* intNum */
        I2C_NORMAL                          /* busClkKHz */
    }
#endif
};

static boardI2cData_t        gBoardTda2exI2cData =
{
    /* numI2c */
    (sizeof (gBoardTda2exI2cInstData) / sizeof (boardI2cInstData_t)),
    /* i2cData */
    gBoardTda2exI2cInstData,
    /* probeInstId */
#if defined (SOC_TDA2EX)
    HSI2C_INST_4,
#else
    /* To avoid build warning for other platforms */
    HSI2C_INST_0,
#endif
};

static boardDeviceData_t     gBoardTda2exDevData[BOARD_MAX_DEVICE];

static boardData_t           gBoardTda2exData =
{
    /* numDev */
    0U,
    /* devData */
    &gBoardTda2exDevData[0U],
    /* pinMuxData */
#if defined (SOC_TDA2EX)
    &gBoardTda2exPinMuxData[0U],
#else
    NULL,
#endif
};

static boardDeviceData_t     gBoardTda2exDefaultDevData[] =
    BOARD_TDA2EX_DEFAULT_DEVDATA;
static boardDeviceData_t     gBoardTda2exVisionDevData[] =
    BOARD_TDA2EX_VISION_DEVDATA;
static boardData_t           gBoardTda2exDefaultData =
{
    /* numDev */
    (sizeof (gBoardTda2exDefaultDevData) / sizeof (boardDeviceData_t)),
    /* devData */
    gBoardTda2exDefaultDevData,
    /* pinMuxdata */
    NULL
};
static boardData_t           gBoardTda2exVisionData =
{
    /* numDev */
    (sizeof (gBoardTda2exVisionDevData) / sizeof (boardDeviceData_t)),
    /* devData */
    gBoardTda2exVisionDevData,
    /* pinMuxdata */
    NULL
};
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t BOARDTda2exInit(const boardInitParams_t *pInitPrms)
{
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
    /* Enable GPIO required for video mux as output */
    GPIOModuleEnable(BOARD_GPIO_BASE_MUX_SEL);
    GPIOModuleEnable(BOARD_GPIO_BASE_POWER_DWN);
    GPIOModuleEnable(BOARD_GPIO_BASE_DEMUX_FPD_A);
    GPIOModuleEnable(BOARD_GPIO_BASE_DEMUX_FPD_B);
    GPIOModuleEnable(BOARD_GPIO_BASE_DEMUX_FPD_C);
    GPIODirModeSet(
        BOARD_GPIO_BASE_MUX_SEL,
        BOARD_GPIO_PIN_MUX1_SEL0,
        GPIO_DIR_OUTPUT);
    GPIODirModeSet(
        BOARD_GPIO_BASE_MUX_SEL,
        BOARD_GPIO_PIN_MUX1_SEL1,
        GPIO_DIR_OUTPUT);
    GPIODirModeSet(
        BOARD_GPIO_BASE_MUX_SEL,
        BOARD_GPIO_PIN_MUX2_SEL0,
        GPIO_DIR_OUTPUT);
    GPIODirModeSet(
        BOARD_GPIO_BASE_MUX_SEL,
        BOARD_GPIO_PIN_MUX2_SEL1,
        GPIO_DIR_OUTPUT);
    GPIODirModeSet(
        BOARD_GPIO_BASE_POWER_DWN,
        BOARD_GPIO_PIN_OV_PWDN,
        GPIO_DIR_OUTPUT);
    GPIODirModeSet(
        BOARD_GPIO_BASE_DEMUX_FPD_A,
        BOARD_GPIO_PIN_DEMUX_FPD_A,
        GPIO_DIR_OUTPUT);
    GPIODirModeSet(
        BOARD_GPIO_BASE_DEMUX_FPD_B,
        BOARD_GPIO_PIN_DEMUX_FPD_B,
        GPIO_DIR_OUTPUT);
    GPIODirModeSet(
        BOARD_GPIO_BASE_DEMUX_FPD_C,
        BOARD_GPIO_PIN_DEMUX_FPD_C,
        GPIO_DIR_OUTPUT);
#endif

    return (STW_SOK);
}

boardId_t BOARDGetIdTda2ex(void)
{
    int32_t               retVal  = LLD_HSI2C_FAIL;
    boardId_t             boardId = BOARD_UNKNOWN;
    const boardI2cData_t *i2cData;
    platformId_t          platfrmId;

    i2cData = BOARDGetI2cData();
    if (i2cData != NULL)
    {
        platfrmId = PLATFORMGetId();
        if ((PLATFORM_ID_ZEBU == platfrmId) ||
            (PLATFORM_ID_VIRTIO == platfrmId))
        {
            boardId = BOARD_VISION;
        }
        else
        {
            /*
             * Detect board ID
             */
            /*
             * Probe for SII9127 @ 0x31 address to detect
             * Vision daughter card.
             */
            retVal = DEVICEI2cProbeDevice(
                i2cData->probeInstId,
                BOARD_SII9127_I2C_ADDR_1);
            if (LLD_HSI2C_SUCCESS == retVal)
            {
                boardId = BOARD_VISION;
            }

#ifndef STW_DISABLE_I2C0
            if (LLD_HSI2C_SUCCESS != retVal)
            {
                /*
                 * Probe for EEPROM @ 0x51 address to detect
                 * TDA2XX base board (REV A/B).
                 * Note: This should be the last check as base board is
                 * present by default even when daughter card is present.
                 */
                retVal = DEVICEI2cProbeDevice(
                    HSI2C_INST_0,
                    BOARD_EEPROM_I2C_ADDR_1);
                if (LLD_HSI2C_SUCCESS == retVal)
                {
                    boardId = BOARD_VISION;
                }
            }
            if (LLD_HSI2C_SUCCESS != retVal)
            {
                /*
                 * Probe for EEPROM @ 0x50 address to detect
                 * TDA2XX base board (REV C or above).
                 * Note: This should be the last check as base board is
                 * present by default even when daughter card is present.
                 */
                retVal = DEVICEI2cProbeDevice(
                    HSI2C_INST_0,
                    BOARD_EEPROM_I2C_ADDR_0);
                if (LLD_HSI2C_SUCCESS == retVal)
                {
                    boardId = BOARD_VISION;
                }
            }
#endif
        }
    }
    else
    {
        UARTPuts(" \r\nNULL Pointer Detected i2cData : ", (-((int32_t) 1)));
    }
    return (boardId);
}

boardRev_t BOARDGetBaseBoardRevTda2ex(void)
{
    boardRev_t            boardRev = BOARD_REV_A;
#ifndef STW_DISABLE_I2C0
    int32_t               retVal;
    uint8_t               regValue[2];
    uint32_t              i2cInst, eepromAddr, page, pageSize, delay, numRegs;
    boardEepromId_t       eepromVal;
    void                 *pEepromVal = &eepromVal;
    const boardI2cData_t *i2cData;

    i2cInst    = HSI2C_INST_0;
    eepromAddr = BOARD_EEPROM_I2C_ADDR_0;

    i2cData = BOARDGetI2cData();

    if (NULL != i2cData)
    {
        retVal = DEVICEI2cProbeDevice(
            i2cInst,
            BOARD_EEPROM_I2C_ADDR_0);

        if (LLD_HSI2C_SUCCESS != retVal)
        {
            /* No slave detected at 0x51, baord is REV A or REV B */
            eepromAddr = BOARD_EEPROM_I2C_ADDR_1;
        }

        /* Send 16-bit page address */
        page        = 0U;
        pageSize    = 48U;
        regValue[0] = (uint8_t) (page >> 8U);         /* HIGH address */
        regValue[1] = (uint8_t) (page & 0xFFU);       /* LOW address */
        numRegs     = 2U;
        retVal      = DEVICEI2cRawWrite8(i2cInst, eepromAddr, regValue, numRegs);

        /* Eeprom write cycle time is 5ms - so wait for 5ms after
         * write before reading */
        delay = 5U;
        BspOsal_sleep(delay);

        /* Read 0th page */
        retVal += DEVICEI2cRawRead8(
            i2cInst,
            eepromAddr,
            (UInt8 *) pEepromVal,
            pageSize);
        if ((LLD_HSI2C_SUCCESS == retVal) &&
            (eepromVal.header == 0xAA5533EEU))
        {
            UARTPuts("\r\nEEPROM Base Board Name       : ", (-((int32_t) 1)));
            UARTPuts(eepromVal.boardName, (-((int32_t) 1)));

            switch (eepromVal.versionMajor)
            {
                case 0x01U:
                    boardRev = BOARD_REV_A;
                    break;

                case 0x02U:
                    boardRev = BOARD_REV_B;
                    break;

                case 0x03U:
                    boardRev = BOARD_REV_C;
                    break;

                default:
                    boardRev = BOARD_REV_B;
                    break;
            }
        #if defined (SOC_TDA2EX)
            if((PlatformGetSiliconPackageType() ==
                    PLATFORM_SILICON_PACKAGE_TYPE_17X17) &&
                (boardRev < BOARD_REV_C))
            {
                /* This is J6Eco 17X17 Evm. The initial version of this board is
                 * Rev A only, but it is compatible with REV C EVM of J6Eco.
                 * So software will return REV C for REV A/B of TDA2Ex 17X17.
                 */
                boardRev = BOARD_REV_C;
            }
        #endif
            if (BOARD_REV_C <= boardRev)
            {
                uint32_t tempSize;
                UARTPuts("\r\nEEPROM Base Board EMIF1 Size : ", (-((int32_t) 1)));
                tempSize = eepromVal.emif1Size / (1024U * 1024U);
                UARTPutNum((int32_t) tempSize);
                UARTPuts("MB", (-((int32_t) 1)));

                UARTPuts("\r\nEEPROM Base Board EMIF2 Size : ", (-((int32_t) 1)));
                tempSize = eepromVal.emif2Size / (1024U * 1024U);
                UARTPutNum((int32_t) tempSize);
                UARTPuts("MB", (-((int32_t) 1)));
            }
        }
        else
        {
            UARTPuts("\r\nEEPROM read failed!!", (-((int32_t) 1)));
        }
    }
    else
    {
        UARTPuts(" \r\nNULL Pointer Detected i2cData : ", (-((int32_t) 1)));
    }
#endif

    return (boardRev);
}

boardRev_t BOARDGetDcRevTda2ex(void)
{
    /* Only one revision of board till date */
    return (BOARD_REV_A);
}

const boardI2cData_t *BOARDGetI2cDataTda2ex(void)
{
    return (&gBoardTda2exI2cData);
}

const boardData_t *BOARDGetDataTda2ex(void)
{
    uint32_t           numDev;
    boardId_t          boardId;
    boardData_t       *boardDat;
    boardDeviceData_t *tempDevData;

    boardId  = BOARDGetId();
    boardDat = &gBoardTda2exData;

    /* Copy only for the first time */
    if (0U == boardDat->numDev)
    {
        /* Copy the individual board data to global board data as per
         * hierarchy */
        numDev      = 0U;
        tempDevData = &gBoardTda2exDevData[0U];
        switch (boardId)
        {
            case BOARD_BASE_TDA2XX:
                numDev += gBoardTda2exDefaultData.numDev;
                /* Array bound check */
                if (numDev < BOARD_MAX_DEVICE)
                {
                    memcpy(
                        tempDevData,
                        gBoardTda2exDefaultData.pDevData,
                        (sizeof (boardDeviceData_t) *
                         gBoardTda2exDefaultData.numDev));
                    tempDevData += gBoardTda2exDefaultData.numDev;
                }
                break;
            case BOARD_VISION:
                numDev += gBoardTda2exDefaultData.numDev;
                numDev += gBoardTda2exVisionData.numDev;
                /* Array bound check */
                if (numDev < BOARD_MAX_DEVICE)
                {
                    memcpy(
                        tempDevData,
                        gBoardTda2exDefaultData.pDevData,
                        (sizeof (boardDeviceData_t) *
                         gBoardTda2exDefaultData.numDev));
                    tempDevData += gBoardTda2exDefaultData.numDev;
                    memcpy(
                        tempDevData,
                        gBoardTda2exVisionData.pDevData,
                        (sizeof (boardDeviceData_t) *
                         gBoardTda2exVisionData.numDev));
                    tempDevData += gBoardTda2exVisionData.numDev;
                }
                break;
            case BOARD_UNKNOWN:
            default:
                /* Do nothing as numDev will automatically become 0 in
                 * below code */
                break;
        }

        /* Set the total number of device */
        if (numDev < BOARD_MAX_DEVICE)
        {
            boardDat->numDev = numDev;
        }
        else
        {
            UARTPuts("\r\nInvalid num of devices !!", (-((int32_t) 1)));
        }
    }
    return (boardDat);
}

/* Base EVM mux select */
static int32_t BOARDSelectDeviceTda2ex(uint32_t devDrvId, uint32_t instId)
{
    int32_t  retVal = STW_SOK;
#if defined (SOC_TDA2EX)
    uint8_t  regValue[2];
    uint32_t i2cInst, ioExpAddr, numRegs;
    uint32_t regValueTemp;

    /*
     * Select base EVM leapord imaging sensor or daughter card input for
     * VIN2 signals.
     *
     * VIN2_S0,VIN2_S2 = 10 for base EVM input from leapord imaging sensor.
     * VIN2_S0,VIN2_S2 = 01 for input from daughter card.
     */
    if (DEVICE_ID_OV1063X == devDrvId)
    {
        i2cInst   = HSI2C_INST_4;
        ioExpAddr = BOARD_IO_EXP_I2C_ADDR_6;
        numRegs   = 2U;
        retVal    = DEVICEI2cRawRead8(i2cInst, ioExpAddr, regValue, numRegs);
        if (LLD_HSI2C_SUCCESS != retVal)
        {
            UARTPuts("\r\nI2C read failed!!", (-((int32_t) 1)));
        }
        /* Configure muxes */
        regValueTemp = ((UInt32) regValue[0U] | (BOARD_PCF8575_VIN2_S2));
        regValue[0U] = (UInt8) regValueTemp;
        regValueTemp =
            ((UInt32) regValue[0U] &
             ((UInt32) (~((uint32_t) BOARD_PCF8575_VIN2_S0))));
        regValue[0U] = (UInt8) regValueTemp;

        retVal += DEVICEI2cRawWrite8(i2cInst, ioExpAddr, regValue, numRegs);
        if (LLD_HSI2C_SUCCESS != retVal)
        {
            UARTPuts("\r\nI2C write failed!!", (-((int32_t) 1)));
        }
    }
    if ((DEVICE_ID_MMC == devDrvId) &&
        (DEVICE_MMC_INST_ID_2 == instId))
    {
        i2cInst   = HSI2C_INST_0;
        ioExpAddr = BOARD_IO_EXP_I2C_ADDR_1;
        numRegs   = 2U;
        retVal    = DEVICEI2cRawRead8(i2cInst, ioExpAddr, regValue, numRegs);
        if (LLD_HSI2C_SUCCESS != retVal)
        {
            UARTPuts("\r\nI2C read failed!!", (-((int32_t) 1)));
        }
        /* Configure muxes */
        regValueTemp =
            ((UInt32) regValue[1U] &
             ((UInt32) (~((uint32_t) BOARD_PCF8575_MMC2_SEL))));
        regValue[1U] = (UInt8) regValueTemp;

        retVal += DEVICEI2cRawWrite8(i2cInst, ioExpAddr, regValue, numRegs);
        if (LLD_HSI2C_SUCCESS != retVal)
        {
            UARTPuts("\r\nI2C write failed!!", (-((int32_t) 1)));
        }
    }
    if ((DEVICE_ID_LCD == devDrvId) &&
        (DEVICE_LCD_INST_ID_1 == instId))
    {
        i2cInst   = HSI2C_INST_0;
        ioExpAddr = BOARD_IO_EXP_I2C_ADDR_1;
        numRegs   = 2U;
        retVal    = DEVICEI2cRawRead8(i2cInst, ioExpAddr, regValue, numRegs);
        if (LLD_HSI2C_SUCCESS != retVal)
        {
            UARTPuts("\r\nI2C read failed!!", (-((int32_t) 1)));
        }
        /* io expander 2 (0x21) P0 set to '0' and P7 set to '1' */
        regValueTemp =
            ((UInt32) regValue[0U] &
             ((UInt32) (~((uint32_t) PCF8575_P0_0_MASK))));
        regValueTemp = (regValueTemp | (PCF8575_P0_7_MASK));
        regValue[0U] = (UInt8) regValueTemp;
        retVal += DEVICEI2cRawWrite8(i2cInst, ioExpAddr, regValue, numRegs);
        if (LLD_HSI2C_SUCCESS != retVal)
        {
            UARTPuts("\r\nI2C write failed!!", (-((int32_t) 1)));
        }
    }
#endif
    return (retVal);
}

static int32_t BOARDPowerOnDeviceTda2ex(uint32_t devDrvId,
                                        uint32_t instId,
                                        uint32_t powerOn)
{
    int32_t  retVal = STW_SOK;
    uint8_t  regValue[2];
    uint32_t i2cInst, ioExpAddr, numRegs;

    if (DEVICE_ID_LCD == devDrvId)
    {
        if ((DEVICE_LCD_INST_ID_0 == instId) || (DEVICE_LCD_INST_ID_1 == instId))
        {
            i2cInst   = HSI2C_INST_0;
            ioExpAddr = BOARD_IO_EXP_I2C_ADDR_0;
            numRegs   = 2U;
            retVal    = DEVICEI2cRawRead8(i2cInst, ioExpAddr, regValue,
                                          numRegs);
            if (LLD_HSI2C_SUCCESS != retVal)
            {
                UARTPuts("\r\nI2C read failed!!", (-((int32_t) 1)));
            }

            /* Configure muxes to power on LCD */
            regValue[1U] &= (uint8_t) ~(BOARD_PCF8575_LCDCTRL_POWER_MASK);

            retVal += DEVICEI2cRawWrite8(i2cInst, ioExpAddr, regValue,
                                         numRegs);
            if (LLD_HSI2C_SUCCESS != retVal)
            {
                UARTPuts("\r\nI2C write failed!!", (-((int32_t) 1)));
            }
        }
    }

    if (DEVICE_ID_OV1063X == devDrvId)
    {
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
        /*
         * OV_PWDN is controlled by GP6[17]. 0 is ON, 1 is OFF
         */
        if (powerOn == (uint32_t) TRUE)
        {
            GPIOPinWrite(
                BOARD_GPIO_BASE_POWER_DWN,
                BOARD_GPIO_PIN_OV_PWDN,
                GPIO_PIN_LOW);
        }
        else
        {
            GPIOPinWrite(
                BOARD_GPIO_BASE_POWER_DWN,
                BOARD_GPIO_PIN_OV_PWDN,
                GPIO_PIN_HIGH);
        }
#endif
    }

    return (retVal);
}

/* Vision card mux select */
static int32_t BOARDSelectDeviceTda2exVision(uint32_t devDrvId, uint32_t instId)
{
    int32_t retVal = STW_SOK;

    /* Select mux at base EVM level */
    retVal = BOARDSelectDeviceTda2ex(devDrvId, instId);

    if (STW_SOK == retVal)
    {
        if (DEVICE_ID_OV1063X == devDrvId)
        {
            /*
             * Select CPLD mux to select between sensors/decoder in vision
             * daughter card
             *
             * MUX Signal mapping
             * ------------------
             * MUX1_SEL0 - GPIO4_13 (Mux mode 15, muxed with VIN2A_D12)
             * MUX1_SEL1 - GPIO4_14 (Mux mode 15, muxed with VIN2A_D13)
             * MUX2_SEL0 - GPIO4_15 (Mux mode 15, muxed with VIN2A_D14)
             * MUX2_SEL1 - GPIO4_16 (Mux mode 15, muxed with VIN2A_D15)
             *
             *                  MUX1_SEL0     MUX1_SEL1   MUX2_SEL0   MUX2_SEL1
             *                  -----------------------------------------------
             * HDMI Receiver        X             X           0           0
             * LI Imager            0             0           1           0
             * OV Imager            1             0           1           0
             * Aptina Imager        0             1           1           0
             * CAM1/3 FPD Link      X             X           0           1
             *
             */
            /* Above is valid for TDA2xx EVM only */
            if (PLATFORMIsTI814xFamilyBuild())
            {
                /* TODO */
            }
            else
            {
                GPIOPinWrite(
                    BOARD_GPIO_BASE_MUX_SEL,
                    BOARD_GPIO_PIN_MUX1_SEL0,
                    GPIO_PIN_HIGH);
                GPIOPinWrite(
                    BOARD_GPIO_BASE_MUX_SEL,
                    BOARD_GPIO_PIN_MUX1_SEL1,
                    GPIO_PIN_LOW);
                GPIOPinWrite(
                    BOARD_GPIO_BASE_MUX_SEL,
                    BOARD_GPIO_PIN_MUX2_SEL0,
                    GPIO_PIN_HIGH);
                GPIOPinWrite(
                    BOARD_GPIO_BASE_MUX_SEL,
                    BOARD_GPIO_PIN_MUX2_SEL1,
                    GPIO_PIN_LOW);
            }
        }
    }

    return (retVal);
}

/**
 * \brief   Configures IO pins needed by UART console. This API uses the pin mux
 *          data and configures the pinmux of UART console for default mode
 *
 * \param   uartInstId     Instance number of the UART console
 *
 **/
void BOARDTda2exConfigConsolePinMux(uint32_t uartInstId)
{
#if defined (SOC_TDA2EX)
    const boardPinmuxBoardCfg_t *pPinmuxData;
    uint32_t i = 0;

    pPinmuxData = &gBoardTda2exPinMuxData[0U];

    for (i = 0; (DEVICE_ID_INVALID != pPinmuxData[i].moduleId); i++)
    {
        if ((pPinmuxData[i].moduleId == DEVICE_ID_UART) &&
            (pPinmuxData[i].instNum == uartInstId) &&
            (pPinmuxData[i].boardMode == BOARD_MODE_DEFAULT))
        {
            PLATFORMSetPinmuxRegs(pPinmuxData[i].regOffset,
                                  pPinmuxData[i].regVal);
        }
    }
#endif
    return;
}

