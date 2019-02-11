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
 *  \file stw_boardTda3xx.c
 *
 *  \brief File containing the Tda3xx STW board functions.
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
#include <ti/csl/soc.h>
#include <ti/drv/stw_lld/i2clld/lld_hsi2c.h>
#include <ti/drv/stw_lld/devices/stw_device.h>
#include <ti/drv/stw_lld/boards/stw_board.h>
#include <ti/drv/stw_lld/boards/src/stw_boardPriv.h>
#include <stw_boardTda3xxDefault.h>
#include <ti/drv/stw_lld/devices/stw_deviceIoexp.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Max of all the devices present in the board including any valid
 * combination of base board and daughter cards */
#define BOARD_MAX_DEVICE                    (20U)

#define BOARD_IO_EXP_TCA6416_1_I2C_ADDR     (BOARD_IO_EXP_I2C_ADDR_0)
#define BOARD_IO_EXP_TCA6424_1_I2C_ADDR     (BOARD_IO_EXP_I2C_ADDR_3)
#define BOARD_IO_EXP_TCA6424_2_I2C_ADDR     (BOARD_IO_EXP_I2C_ADDR_2)

#define BOARD_IO_EXP_TCA6416_1_I2C_ID       (HSI2C_INST_0)
#define BOARD_IO_EXP_TCA6424_1_I2C_ID       (HSI2C_INST_0)
#define BOARD_IO_EXP_TCA6424_2_I2C_ID       (HSI2C_INST_0)

/*  Base board TCA6416 1 (on I2C1) - mappings */
#define BOARD_TCA6416_SEL_9127N_MASK        (TCA64_P0_0_MASK)
#define BOARD_TCA6416_APT_TRIGGER_MASK      (TCA64_P0_1_MASK)
#define BOARD_TCA6416_LI_DUAL_TRIGGER_MASK  (TCA64_P0_2_MASK)
#define BOARD_TCA6416_HDMI_CEC_D_MASK       (TCA64_P0_3_MASK)
#define BOARD_TCA6416_HDMI_LS_OE_MASK       (TCA64_P0_4_MASK)
#define BOARD_TCA6416_HDMI_CT_HPD_MASK      (TCA64_P0_5_MASK)
#define BOARD_TCA6416_IOEXP1_P06_MASK       (TCA64_P0_6_MASK)
#define BOARD_TCA6416_FPD_LINK_DB_DET_MASK  (TCA64_P0_7_MASK)
#define BOARD_TCA6416_HDMI_SCDT_MASK        (TCA64_P1_0_MASK)
#define BOARD_TCA6416_HDMI_INT_MASK         (TCA64_P1_1_MASK)
#define BOARD_TCA6416_HDMI_EVNODD_MASK      (TCA64_P1_2_MASK)
#define BOARD_TCA6416_CON_LCD_PWR_DN_MASK   (TCA64_P1_3_MASK)
#define BOARD_TCA6416_TS_LCD_GPIO4_MASK     (TCA64_P1_4_MASK)
#define BOARD_TCA6416_TS_LCD_GPIO3_MASK     (TCA64_P1_5_MASK)
#define BOARD_TCA6416_TS_LCD_GPIO2_MASK     (TCA64_P1_6_MASK)
#define BOARD_TCA6416_TS_LCD_GPIO1_MASK     (TCA64_P1_7_MASK)

/*  Base board TCA6424 1 (on I2C1) - mappings */
#define BOARD_TCA6424_MUX_CNTL0_MASK        (TCA64_P0_0_MASK)
#define BOARD_TCA6424_MUX_CNTL1_MASK        (TCA64_P0_1_MASK)
#define BOARD_TCA6424_MUX_CNTL2_MASK        (TCA64_P0_2_MASK)
#define BOARD_TCA6424_MUX_CNTL3_MASK        (TCA64_P0_3_MASK)
#define BOARD_TCA6424_MUX_CNTL4_MASK        (TCA64_P0_4_MASK)
#define BOARD_TCA6424_MUX_CNTL5_MASK        (TCA64_P0_5_MASK)
#define BOARD_TCA6424_MUX_CNTL6_MASK        (TCA64_P0_6_MASK)
#define BOARD_TCA6424_MUX_CNTL7_MASK        (TCA64_P0_7_MASK)
#define BOARD_TCA6424_MUX_CNTL8_MASK        (TCA64_P1_0_MASK)
#define BOARD_TCA6424_MUX_CNTL9_MASK        (TCA64_P1_1_MASK)
#define BOARD_TCA6424_MUX_CNTL10_MASK       (TCA64_P1_2_MASK)
#define BOARD_TCA6424_MUX_CNTL11_MASK       (TCA64_P1_3_MASK)
#define BOARD_TCA6424_MUX_CNTL12_MASK       (TCA64_P1_4_MASK)
#define BOARD_TCA6424_VOUT_MAP0_MASK        (TCA64_P1_5_MASK)
#define BOARD_TCA6424_VOUT_MAP1_MASK        (TCA64_P1_6_MASK)
#define BOARD_TCA6424_VOUT_MAP2_MASK        (TCA64_P1_7_MASK)
#define BOARD_TCA6424_VIN_MAP0_MASK         (TCA64_P2_0_MASK)
#define BOARD_TCA6424_VIN_MAP1_MASK         (TCA64_P2_1_MASK)
#define BOARD_TCA6424_VIN_MAP2_MASK         (TCA64_P2_2_MASK)
#define BOARD_TCA6424_VIN_MAP3_MASK         (TCA64_P2_3_MASK)
#define BOARD_TCA6424_VIN_MAP4_MASK         (TCA64_P2_4_MASK)
#define BOARD_TCA6424_VIN_MAP5_MASK         (TCA64_P2_5_MASK)
#define BOARD_TCA6424_VIN_MAP6_MASK         (TCA64_P2_6_MASK)
#define BOARD_TCA6424_VIN_MAP7_MASK         (TCA64_P2_7_MASK)

/*  Base board TCA6424 2 (on I2C1) - mappings */
#define BOARD_TCA6424_USR_LED1_MASK         (TCA64_P0_0_MASK)
#define BOARD_TCA6424_USR_LED2_MASK         (TCA64_P0_1_MASK)
#define BOARD_TCA6424_USR_LED3_MASK         (TCA64_P0_2_MASK)
#define BOARD_TCA6424_USR_LED4_MASK         (TCA64_P0_3_MASK)
#define BOARD_TCA6424_VIP_RSTN_MASK         (TCA64_P0_4_MASK)
#define BOARD_TCA6424_VOUT_RSTN_MASK        (TCA64_P0_5_MASK)
#define BOARD_TCA6424_IOEXP2_P06_MASK       (TCA64_P0_6_MASK)
#define BOARD_TCA6424_IOEXP2_P07_MASK       (TCA64_P0_7_MASK)
#define BOARD_TCA6424_IOEXP2_P10_MASK       (TCA64_P1_0_MASK)
#define BOARD_TCA6424_TMP102_ALERT_MASK     (TCA64_P1_1_MASK)
#define BOARD_TCA6424_ETH0_RSTN_MASK        (TCA64_P1_2_MASK)
#define BOARD_TCA6424_ETH1_EXP_RSTN_MASK    (TCA64_P1_3_MASK)
#define BOARD_TCA6424_ETH0_EXP_RSTN_MASK    (TCA64_P1_4_MASK)
#define BOARD_TCA6424_SD_CARD_DETECTN_MASK  (TCA64_P1_5_MASK)
#define BOARD_TCA6424_IOEXP2_P16_MASK       (TCA64_P1_6_MASK)
#define BOARD_TCA6424_IOEXP2_P17_MASK       (TCA64_P1_7_MASK)
#define BOARD_TCA6424_USR_SW1_MASK          (TCA64_P2_0_MASK)
#define BOARD_TCA6424_USR_SW2_MASK          (TCA64_P2_1_MASK)
#define BOARD_TCA6424_USR_SW3_MASK          (TCA64_P2_2_MASK)
#define BOARD_TCA6424_USR_SW4_MASK          (TCA64_P2_3_MASK)
#define BOARD_TCA6424_USR_SW5_MASK          (TCA64_P2_4_MASK)
#define BOARD_TCA6424_IOEXP2_P25_MASK       (TCA64_P2_5_MASK)
#define BOARD_TCA6424_IOEXP2_P26_MASK       (TCA64_P2_6_MASK)
#define BOARD_TCA6424_IOEXP2_P27_MASK       (TCA64_P2_7_MASK)

/*
 *  Mux selection for VOUT
 *  ----------------------
 *
 *                   VOUT_MAP0     VOUT_MAP1   VOUT_MAP2
 *                   -----------------------------------
 *  FPD Link             0             0           0
 *  FPD Link TDM         1             0           0
 *  HDMI                 0             1           0
 *  HDMI TDM             1             1           0
 *  HDMI BT656           0             0           1
 *  HDMI BT1120          1             0           1
 *  Expander/LCD Panel   0             1           1
 *  Expander TDM         1             1           1
 *
 *  Mux Select for Imager Selection
 *  -------------------------------
 *
 *                   VIN_MAP0      VIN_MAP1    VIN_MAP2
 *                   ----------------------------------
 *  LI Straight          0             0           0
 *  LI 8-bit             1             0           0
 *  Aptina Straight      0             1           0
 *  Aptina 8-bit         1             1           0
 *  OV Straight          0             0           1
 *  OV 8-bit             1             0           1
 *
 *  Mux Select for VIN1 Selection
 *  -----------------------------
 *
 *                   VIN_MAP3      VIN_MAP4    VIN_MAP5
 *                   ----------------------------------
 *  Imager               0             0           0
 *  FPD Link             1             0           0
 *  HDMI                 0             1           0
 *  Expansion Cam1       1             1           0
 *  Expansion Cam2       0             0           1
 *  Expansion Cam2:1     1             0           1
 *
 *  Mux Select for VIN2 Selection
 *  -----------------------------
 *
 *                   VIN_MAP6      VIN_MAP7
 *                   ----------------------
 *  Imager               0             0
 *  HDMI                 1             0
 *  Expansion Cam2       0             1
 *  Expansion Cam2:1     1             1
 */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/** \brief EEPROM ID structure. */
typedef struct
{
    uint32_t header;
    char     boardName[16U];
    uint16_t versionMajor;
    uint16_t versionMinor;
    uint32_t configOption;
    char     reserved[28U];
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

static int32_t BOARDPowerOnDeviceTda3xx(uint32_t devDrvId,
                                        uint32_t instId,
                                        uint32_t powerOn);

static int32_t BOARDSelectDeviceTda3xx(uint32_t devDrvId, uint32_t instId);

#ifdef __cplusplus
}
#endif

static int32_t BOARDTda3xxInitIoexp(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
#if defined (SOC_TDA3XX)
extern boardPinmuxBoardCfg_t gBoardTda3xxPinMuxData[
    NUM_OF_TDA3XXBOARD_PINMUX_CONFIGUARATIONS];
#endif

static boardI2cInstData_t    gBoardTda3xxI2cInstData[] =
{
    {
        HSI2C_INST_0,                       /* instId */
        SOC_I2C1_BASE,                      /* baseAddr */
        CSL_INTC_EVENTID_I2CINT1,           /* intNum */
        I2C_NORMAL                          /* busClkKHz */
    },
    {
        HSI2C_INST_1,                       /* instId */
        SOC_I2C2_BASE,                      /* baseAddr */
        CSL_INTC_EVENTID_I2CINT2,           /* intNum */
        I2C_FAST                            /* busClkKHz */
    }
};

static boardI2cData_t        gBoardTda3xxI2cData =
{
    /* numI2c */
    (sizeof (gBoardTda3xxI2cInstData) / sizeof (boardI2cInstData_t)),
    /* i2cData */
    gBoardTda3xxI2cInstData,
    /* probeInstId */
    HSI2C_INST_0,
};

static boardDeviceData_t     gBoardTda3xxDevData[BOARD_MAX_DEVICE];

static boardData_t           gBoardTda3xxData =
{
    /* numDev */
    0U,
    /* devData */
    &gBoardTda3xxDevData[0U],
    /* pinMuxData */
#if defined (SOC_TDA3XX)
    &gBoardTda3xxPinMuxData[0U],
#else
    NULL,
#endif
};

static boardDeviceData_t     gBoardTda3xxDefaultDevData[] =
    BOARD_TDA3XX_DEFAULT_DEVDATA;

static boardData_t           gBoardTda3xxDefaultData =
{
    /* numDev */
    (sizeof (gBoardTda3xxDefaultDevData) / sizeof (boardDeviceData_t)),
    /* devData */
    gBoardTda3xxDefaultDevData,
    /* pinMuxdata */
    NULL
};

/* Falg to inidicate whether IO expander is configured for input/output */
static int32_t gBoardTda3xxIsIoexpInit = (int32_t) FALSE;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t BOARDTda3xxInit(const boardInitParams_t *pInitPrms)
{
    gBoardTda3xxIsIoexpInit = (int32_t) FALSE;

    return (STW_SOK);
}

boardId_t BOARDGetIdTda3xx(void)
{
    int32_t      retVal;
    boardId_t    boardId = BOARD_UNKNOWN;
    platformId_t platfrmId;

    platfrmId = PLATFORMGetId();
    if ((PLATFORM_ID_ZEBU == platfrmId) ||
        (PLATFORM_ID_VIRTIO == platfrmId))
    {
        boardId = BOARD_BASE_TDA3XX;
    }
    else
    {
        /*
         * Detect board ID
         */

        /*
         * Probe for EEPROM @ 0x51 address to detect
         * TDA3XX base board for RevA/ RevB/ RevC/ RevD.
         * Note: This should be the last check as base board is
         * present by default even when daughter card is present.
         */
        retVal = DEVICEI2cProbeDevice(HSI2C_INST_0, BOARD_EEPROM_I2C_ADDR_1);
        if (STW_SOK == retVal)
        {
            boardId = BOARD_BASE_TDA3XX;
        }
        else
        {
            /*
             * Probe for EEPROM @ 0x50 address to detect
             * TDA3XX base board for >=RevE
             * Note: This should be the last check as base board is
             * present by default even when daughter card is present.
             */
            retVal = DEVICEI2cProbeDevice(HSI2C_INST_0, BOARD_EEPROM_I2C_ADDR_0);
            if (STW_SOK == retVal)
            {
                boardId = BOARD_BASE_TDA3XX;
            }
        }
    }

    return (boardId);
}

boardRev_t BOARDGetBaseBoardRevTda3xx(void)
{
    boardRev_t      boardRev = BOARD_REV_A;
    int32_t         retVal;
    uint8_t         regValue[2];
    uint32_t        i2cInst, eepromAddr, page, pageSize, delay, numRegs;
    boardEepromId_t eepromVal;
    void           *pEepromVal = &eepromVal;

    i2cInst    = HSI2C_INST_0;
    eepromAddr = (UInt32) BOARD_EEPROM_I2C_ADDR_0;

    retVal = DEVICEI2cProbeDevice(i2cInst, (uint8_t) eepromAddr);
    if (STW_SOK != retVal)
    {
      /*No slave detected at 0x50, baord is REV A or REV B or REV C or REV D*/
        eepromAddr = (UInt32) BOARD_EEPROM_I2C_ADDR_1;
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
        (uint8_t *) pEepromVal,
        pageSize);
    if ((STW_SOK == retVal) &&
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
                boardRev = BOARD_REV_A;
                break;
        }
    }
    else
    {
        UARTPuts("\r\nEEPROM read failed!!", (-((int32_t) 1)));
    }

    return (boardRev);
}

boardRev_t BOARDGetDcRevTda3xx(void)
{
    boardRev_t boardRev = BOARD_REV_A;
    /* Only one revision of board till date */
    return (boardRev);
}

const boardI2cData_t *BOARDGetI2cDataTda3xx(void)
{
    return (&gBoardTda3xxI2cData);
}

const boardData_t *BOARDGetDataTda3xx(void)
{
    uint32_t           numDev;
    boardId_t          boardId;
    boardData_t       *boardDat;
    boardDeviceData_t *tempDevData;

    boardId  = BOARDGetId();
    boardDat = &gBoardTda3xxData;

    /* Copy only for the first time */
    if (0U == boardDat->numDev)
    {
        /* Copy the individual board data to global board data as per
         * hierarchy */
        numDev      = 0U;
        tempDevData = &gBoardTda3xxDevData[0U];
        switch (boardId)
        {
            case BOARD_BASE_TDA3XX:
                numDev += gBoardTda3xxDefaultData.numDev;
                /* Array bound check */
                if (numDev < BOARD_MAX_DEVICE)
                {
                    memcpy(
                        tempDevData,
                        gBoardTda3xxDefaultData.pDevData,
                        (sizeof (boardDeviceData_t) *
                         gBoardTda3xxDefaultData.numDev));
                    tempDevData += gBoardTda3xxDefaultData.numDev;
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

/* Mode select function */
int32_t BOARDSelectModeTda3xx(uint32_t    devDrvId,
                              uint32_t    instId,
                              boardMode_t boardMod)
{
    int32_t  retVal = STW_SOK;
    uint8_t  regValue[DEVICE_IOEXP_TCA6424_NUM_PORTS];
    uint32_t i2cInst, ioExpAddr, numRegs, needsUpdate = FALSE;

    if ((int32_t) FALSE == gBoardTda3xxIsIoexpInit)
    {
        BOARDTda3xxInitIoexp();
    }

    i2cInst   = BOARD_IO_EXP_TCA6424_1_I2C_ID;
    ioExpAddr = BOARD_IO_EXP_TCA6424_1_I2C_ADDR;
    numRegs   = DEVICE_IOEXP_TCA6424_NUM_PORTS;
    retVal    = DEVICEIoexpTca6424ReadOutputPort(
        i2cInst,
        ioExpAddr,
        regValue,
        numRegs);
    if (STW_SOK != retVal)
    {
        UARTPuts("\r\nI2C read failed!!", (-((int32_t) 1)));
    }

    if (STW_SOK == retVal)
    {
        if ((DEVICE_ID_LCD == devDrvId) && (0U == instId))
        {
            needsUpdate = (uint32_t) TRUE;

            /* Set MUX_CNTL[2:1] to 01 for VOUT1 data[7:0] and ctrl signals */
            regValue[DEVICE_IOEXP_TCA64XX_PORT0_OFFSET] &=
                (UInt8) ~(BOARD_TCA6424_MUX_CNTL2_MASK);
            regValue[DEVICE_IOEXP_TCA64XX_PORT0_OFFSET] |=
                (UInt8) BOARD_TCA6424_MUX_CNTL1_MASK;

            if (BOARD_MODE_VIDEO_24BIT == boardMod)
            {
                /* Set MUX_CNTL[4:3,0] to 011 for VOUT1 data[8:23] */
                regValue[DEVICE_IOEXP_TCA64XX_PORT0_OFFSET] &=
                    (UInt8) ~(BOARD_TCA6424_MUX_CNTL4_MASK);
                regValue[DEVICE_IOEXP_TCA64XX_PORT0_OFFSET] |=
                    (UInt8) BOARD_TCA6424_MUX_CNTL3_MASK;
                regValue[DEVICE_IOEXP_TCA64XX_PORT0_OFFSET] |=
                    (UInt8) BOARD_TCA6424_MUX_CNTL0_MASK;
            }
        }
        else if (DEVICE_ID_OV1063X == devDrvId)
        {
            needsUpdate = (uint32_t) TRUE;
            if (BOARD_MODE_VIDEO_8BIT == boardMod)
            {
                regValue[DEVICE_IOEXP_TCA64XX_PORT2_OFFSET] |=
                    (UInt8) BOARD_TCA6424_VIN_MAP0_MASK;
            }
            else
            {
                /* Straight */
                regValue[DEVICE_IOEXP_TCA64XX_PORT2_OFFSET] &=
                    (UInt8) ~BOARD_TCA6424_VIN_MAP0_MASK;
            }
        }
        else
        {
            /* Do Nothing */
        }
    }

    if ((STW_SOK == retVal) && (TRUE == needsUpdate))
    {
        retVal += DEVICEIoexpTca6424WriteOutputPort(
            i2cInst,
            ioExpAddr,
            regValue,
            numRegs);
        if (STW_SOK != retVal)
        {
            UARTPuts("\r\nI2C write failed!!", (-((int32_t) 1)));
        }
    }

    return (retVal);
}

/* Base EVM mux select */
static int32_t BOARDSelectDeviceTda3xx(uint32_t devDrvId, uint32_t instId)
{
    int32_t  retVal = STW_SOK;
    uint8_t  regValue[DEVICE_IOEXP_TCA6424_NUM_PORTS];
    uint32_t i2cInst, ioExpAddr, numRegs;

    if ((int32_t) FALSE == gBoardTda3xxIsIoexpInit)
    {
        BOARDTda3xxInitIoexp();
    }

    if (DEVICE_ID_LCD == devDrvId)
    {
        if (0U == instId)
        {
            i2cInst   = BOARD_IO_EXP_TCA6424_1_I2C_ID;
            ioExpAddr = BOARD_IO_EXP_TCA6424_1_I2C_ADDR;
            numRegs   = DEVICE_IOEXP_TCA6424_NUM_PORTS;
            retVal    = DEVICEIoexpTca6424ReadOutputPort(
                i2cInst,
                ioExpAddr,
                regValue,
                numRegs);
            if (STW_SOK != retVal)
            {
                UARTPuts("\r\nI2C read failed!!", (-((int32_t) 1)));
            }

            /* Set VOUT_MAP[2:0] to 110 for LCD panel */
            regValue[DEVICE_IOEXP_TCA64XX_PORT1_OFFSET] &=
                (uint8_t) ~(BOARD_TCA6424_VOUT_MAP0_MASK);
            regValue[DEVICE_IOEXP_TCA64XX_PORT1_OFFSET] |=
                (uint8_t) BOARD_TCA6424_VOUT_MAP1_MASK;
            regValue[DEVICE_IOEXP_TCA64XX_PORT1_OFFSET] |=
                (uint8_t) BOARD_TCA6424_VOUT_MAP2_MASK;

            retVal += DEVICEIoexpTca6424WriteOutputPort(
                i2cInst,
                ioExpAddr,
                regValue,
                numRegs);
            if (STW_SOK != retVal)
            {
                UARTPuts("\r\nI2C write failed!!", (-((int32_t) 1)));
            }
        }
    }
    else if ((DEVICE_ID_OV1063X == devDrvId) ||
             (DEVICE_ID_UART == devDrvId) ||
             (DEVICE_ID_NORFLASH == devDrvId) ||
             (DEVICE_ID_MMC == devDrvId) ||
             (DEVICE_ID_EMAC0PHY == devDrvId) ||
             (DEVICE_ID_MCSPI == devDrvId))
    {
        i2cInst   = BOARD_IO_EXP_TCA6424_1_I2C_ID;
        ioExpAddr = BOARD_IO_EXP_TCA6424_1_I2C_ADDR;
        numRegs   = DEVICE_IOEXP_TCA6424_NUM_PORTS;
        retVal    = DEVICEIoexpTca6424ReadOutputPort(
            i2cInst,
            ioExpAddr,
            regValue,
            numRegs);
        if (STW_SOK != retVal)
        {
            UARTPuts("\r\nI2C read failed!!", (-((int32_t) 1)));
        }

        if ((DEVICE_ID_OV1063X == devDrvId) &&
            (DEVICE_OV1063X_INST_ID_0 == instId))
        {
            /* Set VIN_MAP[3:5] to 000 for Imager to VIN1 - Level 1 */
            regValue[DEVICE_IOEXP_TCA64XX_PORT2_OFFSET] &=
                (uint8_t) ~(BOARD_TCA6424_VIN_MAP3_MASK);
            regValue[DEVICE_IOEXP_TCA64XX_PORT2_OFFSET] &=
                (uint8_t) ~(BOARD_TCA6424_VIN_MAP4_MASK);
            regValue[DEVICE_IOEXP_TCA64XX_PORT2_OFFSET] &=
                (uint8_t) ~(BOARD_TCA6424_VIN_MAP5_MASK);
        }

        if ((DEVICE_ID_OV1063X == devDrvId) &&
            (DEVICE_OV1063X_INST_ID_1 == instId))
        {
            /* Set VIN_MAP[6:7] to 00 for Imager to VIN2 - Level 1 */
            regValue[DEVICE_IOEXP_TCA64XX_PORT2_OFFSET] &=
                (uint8_t) ~(BOARD_TCA6424_VIN_MAP6_MASK);
            regValue[DEVICE_IOEXP_TCA64XX_PORT2_OFFSET] &=
                (uint8_t) ~(BOARD_TCA6424_VIN_MAP7_MASK);
        }
        if (DEVICE_ID_OV1063X == devDrvId)
        {
            /* Set VIN_MAP[0:2] to 101 for OV 8-bit - Level 2 */
            regValue[DEVICE_IOEXP_TCA64XX_PORT2_OFFSET] |=
                (uint8_t) BOARD_TCA6424_VIN_MAP0_MASK;
            regValue[DEVICE_IOEXP_TCA64XX_PORT2_OFFSET] &=
                (uint8_t) ~(BOARD_TCA6424_VIN_MAP1_MASK);
            regValue[DEVICE_IOEXP_TCA64XX_PORT2_OFFSET] |=
                (uint8_t) BOARD_TCA6424_VIN_MAP2_MASK;
        }
        if (((DEVICE_ID_UART == devDrvId) &&
             (DEVICE_UART_INST_ID_1 == instId)) ||
            ((DEVICE_ID_UART == devDrvId) &&
             (DEVICE_UART_INST_ID_2 == instId)))
        {
            /* Set MUX_CNTL[9] & MUX_CNTL[0] to 11 for UART2 */
            /* Set MUX_CNTL[10] , MUX_CNTL[9] & MUX_CNTL[0] to 011 for UART1 */
            regValue[DEVICE_IOEXP_TCA64XX_PORT0_OFFSET] |=
                (uint8_t) BOARD_TCA6424_MUX_CNTL0_MASK;
            regValue[DEVICE_IOEXP_TCA64XX_PORT1_OFFSET] |=
                (uint8_t) BOARD_TCA6424_MUX_CNTL9_MASK;
            if (instId == DEVICE_UART_INST_ID_1)
            {
                regValue[DEVICE_IOEXP_TCA64XX_PORT1_OFFSET] &=
                    (uint8_t) ~(BOARD_TCA6424_MUX_CNTL10_MASK);
            }
        }
        if ((DEVICE_ID_NORFLASH == devDrvId) &&
            (DEVICE_NORFLASH_INST_ID_0 == instId))
        {
            /* Set MUX_CNTL[11], MUX_CNTL[9], MUX_CNTL[5] & MUX_CNTL[4] to 1111
             * MUX_CNTL[3] & MUX_CNTL[0] to 00 for GPMC lines for NOR FLASH */
            regValue[DEVICE_IOEXP_TCA64XX_PORT0_OFFSET] &=
                (uint8_t) ~(BOARD_TCA6424_MUX_CNTL0_MASK);
            regValue[DEVICE_IOEXP_TCA64XX_PORT0_OFFSET] &=
                (uint8_t) ~(BOARD_TCA6424_MUX_CNTL3_MASK);
            regValue[DEVICE_IOEXP_TCA64XX_PORT0_OFFSET] |=
                (uint8_t) BOARD_TCA6424_MUX_CNTL4_MASK;
            regValue[DEVICE_IOEXP_TCA64XX_PORT0_OFFSET] |=
                (uint8_t) BOARD_TCA6424_MUX_CNTL5_MASK;
            regValue[DEVICE_IOEXP_TCA64XX_PORT1_OFFSET] |=
                (uint8_t) BOARD_TCA6424_MUX_CNTL9_MASK;
            regValue[DEVICE_IOEXP_TCA64XX_PORT1_OFFSET] |=
                (uint8_t) BOARD_TCA6424_MUX_CNTL10_MASK;
            regValue[DEVICE_IOEXP_TCA64XX_PORT1_OFFSET] |=
                (uint8_t) BOARD_TCA6424_MUX_CNTL11_MASK;
        }
        if ((DEVICE_ID_MMC == devDrvId) &&
            (DEVICE_MMC_INST_ID_4 == instId))
        {
            /* Set MUX_CNTL[7] & MUX_CNTL[6] to 10 for MMC4 */
            regValue[DEVICE_IOEXP_TCA64XX_PORT0_OFFSET] |=
                (uint8_t) BOARD_TCA6424_MUX_CNTL7_MASK;
            regValue[DEVICE_IOEXP_TCA64XX_PORT0_OFFSET] &=
                (uint8_t) ~(BOARD_TCA6424_MUX_CNTL6_MASK);
        }
        if ((DEVICE_ID_EMAC0PHY == devDrvId) &&
            (DEVICE_EMAC0PHY_INST_ID_0 == instId))
        {
            /* Set MUX_CNTL[7] & MUX_CNTL[6] to 01 for EMAC0PHY */
            regValue[DEVICE_IOEXP_TCA64XX_PORT0_OFFSET] &=
                (uint8_t) ~(BOARD_TCA6424_MUX_CNTL7_MASK);
            regValue[DEVICE_IOEXP_TCA64XX_PORT0_OFFSET] |=
                (uint8_t) BOARD_TCA6424_MUX_CNTL6_MASK;
        }
        if ((DEVICE_ID_MCSPI == devDrvId) &&
            (DEVICE_MCSPI_INST_ID_1 == instId))
        {
            /* Set MUX_CNTL[8] to 1 for SPI1 */
            regValue[DEVICE_IOEXP_TCA64XX_PORT1_OFFSET] |=
                (uint8_t) BOARD_TCA6424_MUX_CNTL8_MASK;
        }
        else
        {
            /* Do Nothing */
        }
        retVal += DEVICEIoexpTca6424WriteOutputPort(
            i2cInst,
            ioExpAddr,
            regValue,
            numRegs);
        if (STW_SOK != retVal)
        {
            UARTPuts("\r\nI2C write failed!!", (-((int32_t) 1)));
        }
    }
    else
    {
        /* Do Nothing */
    }

    return (retVal);
}

static int32_t BOARDPowerOnDeviceTda3xx(uint32_t devDrvId,
                                        uint32_t instId,
                                        uint32_t powerOn)
{
    int32_t  retVal = STW_SOK;
    uint8_t  regValue[DEVICE_IOEXP_TCA6416_NUM_PORTS];
    uint32_t i2cInst, ioExpAddr, numRegs;

    if ((int32_t) FALSE == gBoardTda3xxIsIoexpInit)
    {
        BOARDTda3xxInitIoexp();
    }

    if (DEVICE_ID_LCD == devDrvId)
    {
        if (0U == instId)
        {
            i2cInst   = BOARD_IO_EXP_TCA6416_1_I2C_ID;
            ioExpAddr = BOARD_IO_EXP_TCA6416_1_I2C_ADDR;
            numRegs   = DEVICE_IOEXP_TCA6416_NUM_PORTS;
            retVal    = DEVICEIoexpTca6416ReadOutputPort(
                i2cInst,
                ioExpAddr,
                regValue,
                numRegs);
            if (STW_SOK != retVal)
            {
                UARTPuts("\r\nI2C read failed!!", (-((int32_t) 1)));
            }

            /* Configure muxes to power on LCD */
            regValue[DEVICE_IOEXP_TCA64XX_PORT1_OFFSET] &=
                (uint8_t) ~(BOARD_TCA6416_CON_LCD_PWR_DN_MASK);

            retVal += DEVICEIoexpTca6416WriteOutputPort(
                i2cInst,
                ioExpAddr,
                regValue,
                numRegs);
            if (STW_SOK != retVal)
            {
                UARTPuts("\r\nI2C write failed!!", (-((int32_t) 1)));
            }
        }
    }

    return (retVal);
}

static int32_t BOARDTda3xxInitIoexp(void)
{
    int32_t  retVal = STW_SOK;
    uint8_t  regValue[DEVICE_IOEXP_TCA6424_NUM_PORTS];
    uint32_t i2cInst, ioExpAddr, numRegs;

    /* Configure TCA6416 1 IO expander */
    i2cInst   = BOARD_IO_EXP_TCA6416_1_I2C_ID;
    ioExpAddr = BOARD_IO_EXP_TCA6416_1_I2C_ADDR;
    numRegs   = DEVICE_IOEXP_TCA6416_NUM_PORTS;

    /* Configure the default values for the output port */
    regValue[DEVICE_IOEXP_TCA64XX_PORT0_OFFSET] = 0xB8U;
    regValue[DEVICE_IOEXP_TCA64XX_PORT1_OFFSET] = 0xFFU;
    retVal = DEVICEIoexpTca6416WriteOutputPort(
        i2cInst,
        ioExpAddr,
        regValue,
        numRegs);
    if (STW_SOK != retVal)
    {
        UARTPuts("\r\nI2C write failed!!", (-((int32_t) 1)));
    }

    /* Configure every pin as output except P03 for TCA6416 1 IO expander
     * 1 is input, 0 is output */
    regValue[DEVICE_IOEXP_TCA64XX_PORT0_OFFSET] = BOARD_TCA6416_HDMI_CEC_D_MASK;
    regValue[DEVICE_IOEXP_TCA64XX_PORT1_OFFSET] = 0x00U;

    retVal = DEVICEIoexpTca6416WriteConfig(i2cInst, ioExpAddr, regValue,
                                           numRegs);
    if (STW_SOK != retVal)
    {
        UARTPuts("\r\nI2C write failed!!", (-((int32_t) 1)));
    }

    if (STW_SOK == retVal)
    {
        /* Configure TCA6424 1 IO expander */
        i2cInst   = BOARD_IO_EXP_TCA6424_1_I2C_ID;
        ioExpAddr = BOARD_IO_EXP_TCA6424_1_I2C_ADDR;
        numRegs   = DEVICE_IOEXP_TCA6424_NUM_PORTS;

        /* Configure the default values for the output port */
        regValue[DEVICE_IOEXP_TCA64XX_PORT0_OFFSET] = 0x5BU;
        regValue[DEVICE_IOEXP_TCA64XX_PORT1_OFFSET] = 0xD0U;
        regValue[DEVICE_IOEXP_TCA64XX_PORT2_OFFSET] = 0xFFU;
        retVal = DEVICEIoexpTca6424WriteOutputPort(
            i2cInst,
            ioExpAddr,
            regValue,
            numRegs);
        if (STW_SOK != retVal)
        {
            UARTPuts("\r\nI2C write failed!!", (-((int32_t) 1)));
        }

        /* Configure every pin as output for TCA6424 1 IO expander
         * 1 is input, 0 is output */
        regValue[DEVICE_IOEXP_TCA64XX_PORT0_OFFSET] = 0x00U;
        regValue[DEVICE_IOEXP_TCA64XX_PORT1_OFFSET] = 0x00U;
        regValue[DEVICE_IOEXP_TCA64XX_PORT2_OFFSET] = 0x00U;

        retVal = DEVICEIoexpTca6424WriteConfig(i2cInst, ioExpAddr, regValue,
                                               numRegs);
        if (STW_SOK != retVal)
        {
            UARTPuts("\r\nI2C write failed!!", (-((int32_t) 1)));
        }
    }

    if (STW_SOK == retVal)
    {
        /* Configure TCA6424 2 IO expander */
        i2cInst   = BOARD_IO_EXP_TCA6424_2_I2C_ID;
        ioExpAddr = BOARD_IO_EXP_TCA6424_2_I2C_ADDR;
        numRegs   = DEVICE_IOEXP_TCA6424_NUM_PORTS;

        /* Configure every pin as output except SD detect and USR_SW for
         * TCA6424 2 IO expander
         * 1 is input, 0 is output */
        regValue[DEVICE_IOEXP_TCA64XX_PORT0_OFFSET] = 0x00U;
        regValue[DEVICE_IOEXP_TCA64XX_PORT1_OFFSET] =
            BOARD_TCA6424_SD_CARD_DETECTN_MASK;
        regValue[DEVICE_IOEXP_TCA64XX_PORT2_OFFSET] =
            (BOARD_TCA6424_USR_SW1_MASK | BOARD_TCA6424_USR_SW2_MASK |
             BOARD_TCA6424_USR_SW3_MASK | BOARD_TCA6424_USR_SW4_MASK |
             BOARD_TCA6424_USR_SW5_MASK);

        retVal = DEVICEIoexpTca6424WriteConfig(i2cInst, ioExpAddr, regValue,
                                               numRegs);
        if (STW_SOK != retVal)
        {
            UARTPuts("\r\nI2C write failed!!", (-((int32_t) 1)));
        }
    }

    if (STW_SOK == retVal)
    {
        gBoardTda3xxIsIoexpInit = (int32_t) TRUE;
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
void BOARDTda3xxConfigConsolePinMux(uint32_t uartInstId)
{
#if defined (SOC_TDA3XX)
    const boardPinmuxBoardCfg_t *pPinmuxData;
    uint32_t index = 0;

    pPinmuxData = &gBoardTda3xxPinMuxData[0U];

    for (index = 0;
         (DEVICE_ID_INVALID != pPinmuxData[index].moduleId); index++)
    {
        if ((pPinmuxData[index].moduleId == DEVICE_ID_UART) &&
            (pPinmuxData[index].instNum == uartInstId) &&
            (pPinmuxData[index].boardMode == BOARD_MODE_DEFAULT))
        {
            PLATFORMSetPinmuxRegs(pPinmuxData[index].regOffset,
                                  pPinmuxData[index].regVal);
        }
    }
#endif
    return;
}

