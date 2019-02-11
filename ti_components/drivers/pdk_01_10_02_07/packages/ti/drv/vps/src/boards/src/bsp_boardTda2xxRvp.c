/*
 *  Copyright (c) Texas Instruments Incorporated 2018
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
 */

/**
 *  \file bsp_boardTda2xx.c
 *
 *  \brief File containing the Tda2xx BSP board functions.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/csl/tistdtypes.h>
#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/osal/bsp_osal.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/bsp_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/csl/csl_gpio.h>
#include <ti/csl/soc.h>
#include <ti/drv/vps/include/platforms/bsp_platform.h>
#ifdef VPS_VIP_BUILD
#include <ti/drv/vps/include/vps_capture.h>
#endif
#ifdef VPS_DSS_BUILD
#include <ti/drv/vps/include/vps_displayCtrl.h>
#endif
#include <ti/drv/vps/include/devices/bsp_device.h>
#include <ti/drv/vps/include/boards/bsp_board.h>
#include <bsp_boardPriv.h>
#include <bsp_boardTda2xxRvp.h>
#include <ti/drv/pm/pmhal.h>

#if defined (SOC_TDA2PX)
#include <bsp_boardTda2pxCalDev.h>
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Max of all the devices present in the board including any valid
 * combination of base board and daughter cards */
#define BOARD_MAX_DEVICE                    (36U)

/*  Base board PCF8575 3 (on I2C2) - mappings
 *  P0_0 - SEL_HDMI_I2C2
 *  P0_1 - VIN6_SEL
 *  P0_2 - VIN2_S0
 *  P0_3 - CAM_FPD_MUX_S0
 */
#define BOARD_PCF8575_SEL_HDMI_I2C2_MASK    (PCF8575_P0_0_MASK)
#define BOARD_PCF8575_VIN6_SEL              (PCF8575_P0_1_MASK)
#define BOARD_PCF8575_VIN2_S0               (PCF8575_P0_2_MASK)
#define BOARD_PCF8575_CAM_FPD_MUX_S0        (PCF8575_P0_3_MASK)

/*  Base board PCF8575 1 (on I2C1) - mappings
 *  P1_5 - CON_LCD_PWR_DN
 */
#define BOARD_PCF8575_LCDCTRL_POWER_MASK    (PCF8575_P1_5_MASK)

/*  Base board PCF8575 2 (on I2C1) - mappings
 *  P0_4 - SEL_ENET_MUX_S0
 */
#define BOARD_PCF8575_SEL_ENET_MUX_S0       (PCF8575_P0_4_MASK)

/*  Base board PCF8575 2 (on I2C1) - mappings
 *  P1_4 - UART_SEL1_3
 *  P1_6 - SEL_UART3_SPI2
 */
#define BOARD_PCF8575_UART_SEL1_3           (PCF8575_P1_4_MASK)
#define BOARD_PCF8575_SEL_UART3_SPI2        (PCF8575_P1_6_MASK)

/*  Base board PCF8575 2 (on I2C1) - mappings
 *  P1_2 - SEL_MMC2
 */
#define BOARD_PCF8575_MMC2                  (PCF8575_P1_2_MASK)

/* Video mux select for vision daughter card */
#define BOARD_GPIO_BASE_MUX_SEL             ((UInt32) SOC_GPIO4_BASE)
#define BOARD_GPIO_PIN_MUX1_SEL0            ((UInt32) 13U)
#define BOARD_GPIO_PIN_MUX1_SEL1            ((UInt32) 14U)
#define BOARD_GPIO_PIN_MUX2_SEL0            ((UInt32) 15U)
#define BOARD_GPIO_PIN_MUX2_SEL1            ((UInt32) 16U)
#define BOARD_GPIO_BASE_DEMUX_FPD_A         ((UInt32) SOC_GPIO2_BASE)
#define BOARD_GPIO_BASE_DEMUX_FPD_B         ((UInt32) SOC_GPIO1_BASE)
#define BOARD_GPIO_BASE_DEMUX_FPD_C         ((UInt32) SOC_GPIO6_BASE)
#define BOARD_GPIO_PIN_DEMUX_FPD_A          ((UInt32) 29U)
#define BOARD_GPIO_PIN_DEMUX_FPD_B          ((UInt32) 4U)
#define BOARD_GPIO_PIN_DEMUX_FPD_C          ((UInt32) 7U)
#define BOARD_GPIO_BASE_POWER_DWN           ((UInt32) SOC_GPIO6_BASE)
#define BOARD_GPIO_PIN_OV_PWDN              ((UInt32) 17U)
#define BOARD_GPIO_PIN_AR0132RC             ((UInt32) 11U)
#define BOARD_GPIO_PIN_AR0132RC_INST0_S0    ((UInt32) 11U)
#define BOARD_GPIO_PIN_AR0132RC_INST0_S1    ((UInt32) 4U)
#define BOARD_GPIO_PIN_AR0132RC_INST1_S0    ((UInt32) 6U)
#define BOARD_GPIO_PIN_AR0132RC_INST1_S1    ((UInt32) 9U)
#define BOARD_GPIO_PIN_OV1063X_MAIN_IMAGER  ((UInt32) 0U)
#define BOARD_GPIO_PIN_OV1063X_PWRON        ((UInt32) 7U)

/* GPIO Expander Registers */
#define BOARD_TCA9539_INPUT0_REG                  0x00
#define BOARD_TCA9539_INPUT1_REG                  0x01
#define BOARD_TCA9539_OUTPUT0_REG                 0x02
#define BOARD_TCA9539_OUTPUT1_REG                 0x03
#define BOARD_TCA9539_POLINV0_REG                 0x04
#define BOARD_TCA9539_POLINV1_REG                 0x05
#define BOARD_TCA9539_CONFIG0_REG                 0x06
#define BOARD_TCA9539_CONFIG1_REG                 0x07

/* Available FPD Voltages */
#define BOARD_FPD_VOLTAGE_5V5                     0x00
#define BOARD_FPD_VOLTAGE_12V                     0x01


/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/** \brief EEPROM ID structure. */
typedef struct
{
    UInt32 header;
    Char   boardName[16U];
    UInt16 versionMajor;
    UInt16 versionMinor;
    UInt32 configOption;
    Char   reserved[28U];
} Bsp_BoardEepromId;

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

static Int32 Bsp_boardConfigureGPIOExpanders();
static void Bsp_boardSetBitsInGPIOExpander(Uint32 i2cBus, Uint32 i2cAddr,
  Uint8 regAddr, Uint8 bitMask);
static Int32 Bsp_boardEnableFpdInputs(UInt32 voltage);
static void Bsp_boardSetPinMuxTda2xxRVP();

static Int32 Bsp_boardPowerOnDeviceTda2xxRVP(UInt32 devDrvId,
                                          UInt32 instId,
                                          UInt32 powerOn);
static Int32 Bsp_boardSelectDeviceTda2xxRVP(UInt32 devDrvId, UInt32 instId);

static uint16_t Bsp_boardTda2xxRvpGetId(UInt8 address);

#ifdef __cplusplus
}
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static Bool gFPDInputsEnabled = FALSE;


static Bsp_BoardI2cInstData gBoardTda2xxI2cInstData[] =
{
#ifndef BSP_DISABLE_I2C0
    {
        BSP_DEVICE_I2C_INST_ID_0,           /* instId */
        SOC_I2C1_BASE,                      /* baseAddr */
        CSL_INTC_EVENTID_I2CINT1,           /* intNum */
        400U                                /* busClkKHz */
    },
#endif  /* #ifndef BSP_DISABLE_I2C0 */
#ifndef BSP_DISABLE_I2C1
    {
        BSP_DEVICE_I2C_INST_ID_1,           /* instId */
        SOC_I2C2_BASE,                      /* baseAddr */
        CSL_INTC_EVENTID_I2CINT2,           /* intNum */
        400U                                /* busClkKHz */
    },
#endif  /* #ifndef BSP_DISABLE_I2C1 */
#ifndef BSP_DISABLE_I2C2
    {
        BSP_DEVICE_I2C_INST_ID_2,           /* instId */
        SOC_I2C3_BASE,                      /* baseAddr */
        CSL_INTC_EVENTID_I2CINT3,           /* intNum */
        400U                                /* busClkKHz */
    },
#endif  /* #ifndef BSP_DISABLE_I2C2 */
#ifndef BSP_DISABLE_I2C3
    {
        BSP_DEVICE_I2C_INST_ID_3,           /* instId */
        SOC_I2C4_BASE,                      /* baseAddr */
#if defined (VPS_USE_LINUX_INTC_NUMBERS)
        44U,                                /* intNum */
#else
        CSL_INTC_EVENTID_I2CINT4,           /* intNum */
#endif
        400U                                /* busClkKHz */
    },
#endif  /* #ifndef BSP_DISABLE_I2C3 */
#ifndef BSP_DISABLE_I2C4
    {
        BSP_DEVICE_I2C_INST_ID_4,           /* instId */
        SOC_I2C5_BASE,                      /* baseAddr */
        49U,                                /* intNum */
        400U                                /* busClkKHz */
    }
#endif
};

static Bsp_BoardI2cData     gBoardTda2xxI2cData =
{
    /* numI2c */
    (sizeof (gBoardTda2xxI2cInstData) / sizeof (Bsp_BoardI2cInstData)),
    /* i2cData */
    gBoardTda2xxI2cInstData,
    /* probeInstId */
#if defined (SOC_TDA2PX)
    BSP_DEVICE_I2C_INST_ID_4,
#else
    BSP_DEVICE_I2C_INST_ID_1,
#endif
};

static Bsp_BoardDeviceData  gBoardTda2xxDevData[BOARD_MAX_DEVICE];

static Bsp_BoardData        gBoardTda2xxData =
{
    /* numDev */
    0U,
    /* devData */
    &gBoardTda2xxDevData[0U],
};

static Bsp_BoardDeviceData  gBoardTda2xxRvpDevData[] =
    BSP_BOARD_TDA2XX_RVP_DEVDATA;

static Bsp_BoardData        gBoardTda2xxRvpData =
{
    /* numDev */
    (sizeof (gBoardTda2xxRvpDevData) / sizeof (Bsp_BoardDeviceData)),
    /* devData */
    gBoardTda2xxRvpDevData,
};


/* Tda2xx interposer */
extern Bsp_BoardData        gBoardTda3xxDefaultData;

#if defined (BSP_DISABLE_I2C0)
/* Cached board IDs sent from linux */
UInt8 bsp_boardTda2xxRvpSomId = (UInt8) KID_FAIL;
UInt8 bsp_boardTda2xxRvpBaseboardId = (UInt8) KID_FAIL;
#endif

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

Int32 Bsp_boardTda2xxInit(void)
{
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
    GPIODirModeSet(
        SOC_GPIO6_BASE,
        BOARD_GPIO_PIN_AR0132RC_INST0_S0,
        GPIO_DIR_OUTPUT);
    GPIODirModeSet(
        SOC_GPIO1_BASE,
        BOARD_GPIO_PIN_AR0132RC_INST0_S1,
        GPIO_DIR_OUTPUT);
    GPIODirModeSet(
        SOC_GPIO5_BASE,
        BOARD_GPIO_PIN_AR0132RC_INST1_S0,
        GPIO_DIR_OUTPUT);
    GPIODirModeSet(
        SOC_GPIO5_BASE,
        BOARD_GPIO_PIN_AR0132RC_INST1_S1,
        GPIO_DIR_OUTPUT);

    Bsp_boardSetPinMuxTda2xxRVP();

    return (BSP_SOK);
}

Int32 Bsp_boardTda2xxLateInit(void)
{
    Int32 retVal = BSP_SOK;
    retVal = Bsp_boardConfigureGPIOExpanders();
    return retVal;
}

Bsp_BoardId Bsp_boardGetIdTda2xx(void)
{
    Int32 baseBoardId;
    Bsp_BoardId rvpBoardId;

    baseBoardId = Bsp_boardTda2xxRvpGetId(KTCA9539_I2CADDR_SOM);
    switch(baseBoardId)
    {
        case 0x00:
            rvpBoardId = BSP_BOARD_TDA2ECO_RVP_1;
            break;

        case 0x02:
            rvpBoardId = BSP_BOARD_TDA2ECO_RVP_AM571X_1;
            break;

        case 0x03:
            rvpBoardId = BSP_BOARD_TDA2ECO_RVP_AM572X_1;
            break;
        case 0x04:
            rvpBoardId = BSP_BOARD_TDA2ECO_RVP_TDA2X_1;
            break;

        case 0x01:
        case 0x06:
        case 0x09:
        case 0x0D:
        default:
            rvpBoardId = BSP_BOARD_TDA2XDE_RVP_X;
            break;
    }

    return (rvpBoardId);
}

Bsp_BoardRev Bsp_boardGetBaseBoardRevTda2xx(void)
{
    Int32 baseBoardRev;
    Bsp_BoardRev rvpBoardRev;

    baseBoardRev = Bsp_boardTda2xxRvpGetId(KTCA9539_I2CADDR_BASEBOARD);
    if(baseBoardRev == KID_FAIL) {
        /*
         * Rev 1 8 channel baseboards had non-standard board id i2c addresses.
         * If the read of the correct address fails, try the old, incorrect
         * address.
         */
        baseBoardRev = Bsp_boardTda2xxRvpGetId(KTCA9539_I2CADDR_BASEBOARD_REV1);
    }

    switch(baseBoardRev)
    {
        case 0x00:
            rvpBoardRev = BSP_BOARD_REV_1_4CH;
            break;

        case 0x05:
            rvpBoardRev = BSP_BOARD_REV_1_8CH;
            break;

        case 0x07:
            rvpBoardRev = BSP_BOARD_REV_2_8CH;
            break;

        default:
        case KID_FAIL:
            rvpBoardRev = BSP_BOARD_REV_UNKNOWN;
            break;
    }

    return (rvpBoardRev);
}

Bsp_BoardRev Bsp_boardGetDcRevTda2xx(void)
{
    Bsp_BoardRev boardRev = BSP_BOARD_REV_A;

    return (boardRev);
}

const Bsp_BoardI2cData *Bsp_boardGetI2cDataTda2xx(void)
{
    return (&gBoardTda2xxI2cData);
}

const Bsp_BoardData *Bsp_boardGetDataTda2xx(void)
{
    UInt32               numDev;
    Bsp_BoardId          boardId;
    Bsp_BoardData       *boardData;
    Bsp_BoardDeviceData *tempDevData;

    boardId   = Bsp_boardGetId();
    boardData = &gBoardTda2xxData;

    /* Copy only for the first time */
    if (0U == boardData->numDev)
    {
        /* Copy the individual board data to global board data as per
         * hierarchy */
        numDev      = 0U;
        tempDevData = &gBoardTda2xxDevData[0U];
        switch (boardId)
        {
            case BSP_BOARD_TDA2ECO_RVP_1:
            case BSP_BOARD_TDA2ECO_RVP_AM571X_1:
            case BSP_BOARD_TDA2ECO_RVP_AM572X_1:
            case BSP_BOARD_TDA2ECO_RVP_TDA2X_1:
            case BSP_BOARD_TDA2XDE_RVP_X:
                numDev += gBoardTda2xxRvpData.numDev;
                /* Array bound check */
                GT_assert(BspBoardTrace, numDev < BOARD_MAX_DEVICE);
                BspUtils_memcpy(
                    tempDevData,
                    gBoardTda2xxRvpData.devData,
                    (sizeof (Bsp_BoardDeviceData) *
                     gBoardTda2xxRvpData.numDev));
                tempDevData += gBoardTda2xxRvpData.numDev;
                break;

            case BSP_BOARD_UNKNOWN:
            default:
                /* Do nothing as numDev will automatically become 0 in
                 * below code */
                break;
        }

        /* Set the total number of device */
        boardData->numDev = numDev;
    }

    return (boardData);
}

static Int32 Bsp_boardSelectDeviceTda2xxRVP(UInt32 devDrvId,
                                            UInt32 instId)
{
    Int32  retVal = BSP_SOK;

    return retVal;
}

static Int32 Bsp_boardPowerOnDeviceTda2xxRVP(UInt32 devDrvId,
                                          UInt32 instId,
                                          UInt32 powerOn)
{
    Int32  retVal = BSP_SOK;

    if (retVal == BSP_SOK && powerOn && !gFPDInputsEnabled) {
      retVal = Bsp_boardEnableFpdInputs(BOARD_FPD_VOLTAGE_12V);
      gFPDInputsEnabled = TRUE;
    }


    return retVal;
}

static Int32 Bsp_boardEnableFpdInputs(UInt32 voltage)
{
    Uint32 retVal = BSP_SOK;

    /* Set PDB bits high for all FPD Link channels */
    Bsp_boardSetBitsInGPIOExpander(KTCA9539_U32_I2CBUS, KTCA9539_U32_I2CADDR,
                                   BOARD_TCA9539_OUTPUT0_REG, 0x22);

    Bsp_boardSetBitsInGPIOExpander(KTCA9539_U32_I2CBUS, KTCA9539_U32_I2CADDR,
                                   BOARD_TCA9539_OUTPUT1_REG, 0x22);

    Bsp_boardSetBitsInGPIOExpander(KTCA9539_U34_I2CBUS, KTCA9539_U34_I2CADDR,
                                   BOARD_TCA9539_OUTPUT0_REG, 0x22);

    Bsp_boardSetBitsInGPIOExpander(KTCA9539_U34_I2CBUS, KTCA9539_U34_I2CADDR,
                                   BOARD_TCA9539_OUTPUT1_REG, 0x22);

    /* Select voltage */
    if (voltage == BOARD_FPD_VOLTAGE_12V)
    {
        Bsp_boardSetBitsInGPIOExpander(KTCA9539_U33_I2CBUS, KTCA9539_U33_I2CADDR,
                                       BOARD_TCA9539_OUTPUT0_REG, 0x11);
    }

    /* Enable VDD_FPD */
    Bsp_boardSetBitsInGPIOExpander(KTCA9539_U33_I2CBUS, KTCA9539_U33_I2CADDR,
                                   BOARD_TCA9539_OUTPUT0_REG, 0x22);

    /* Enable output power */
    Bsp_boardSetBitsInGPIOExpander(KTCA9539_U33_I2CBUS, KTCA9539_U33_I2CADDR,
                                   BOARD_TCA9539_OUTPUT0_REG, 0x44);

    /* Bring 925 out of reset */
    Bsp_boardSetBitsInGPIOExpander(KTCA9539_U33_I2CBUS, KTCA9539_U33_I2CADDR,
                                   BOARD_TCA9539_OUTPUT1_REG, 0x02);

    /* Set OE bits high for all FPD Link channels */
    Bsp_boardSetBitsInGPIOExpander(KTCA9539_U32_I2CBUS, KTCA9539_U32_I2CADDR,
                                   BOARD_TCA9539_OUTPUT0_REG, 0x11);

    Bsp_boardSetBitsInGPIOExpander(KTCA9539_U32_I2CBUS, KTCA9539_U32_I2CADDR,
                                   BOARD_TCA9539_OUTPUT1_REG, 0x11);

    Bsp_boardSetBitsInGPIOExpander(KTCA9539_U34_I2CBUS, KTCA9539_U34_I2CADDR,
                                   BOARD_TCA9539_OUTPUT0_REG, 0x11);

    Bsp_boardSetBitsInGPIOExpander(KTCA9539_U34_I2CBUS, KTCA9539_U34_I2CADDR,
                                   BOARD_TCA9539_OUTPUT1_REG, 0x11);

    return (retVal);
}

static void Bsp_boardSetBitsInGPIOExpander(Uint32 i2cBus, Uint32 i2cAddr,
                                            Uint8 regAddr, Uint8 bitMask)
{
    Uint8 tempData;
    Int32 retVal;
    retVal = Bsp_deviceRead8(i2cBus,
                             i2cAddr,
                             &regAddr,
                             &tempData,
                             (UInt32) 1U);
    GT_assert(BspBoardTrace, (retVal == BSP_SOK));

    tempData |= bitMask;
    retVal = Bsp_deviceWrite8(i2cBus,
                              i2cAddr,
                              &regAddr,
                              &tempData,
                              (UInt32) 1U);
    GT_assert(BspBoardTrace, (retVal == BSP_SOK));
}

Int32 Bsp_boardSetPinMuxTda2xx(
    UInt32        drvId,
    UInt32        instId,
    Bsp_BoardMode boardMode)
{
    /* RVP pin muxing is performed statically at startup in Bsp_boardTda2xxInit */
    return (FVID2_SOK);
}

static uint16_t Bsp_boardTda2xxRvpGetId(UInt8 address)
{
    UInt8 id = KID_FAIL;
#if defined (BSP_DISABLE_I2C0)
    if(address == KTCA9539_I2CADDR_SOM) {
        id = bsp_boardTda2xxRvpSomId;
    } else if(address == KTCA9539_I2CADDR_BASEBOARD ||
              address == KTCA9539_I2CADDR_BASEBOARD_REV1) {
        id = bsp_boardTda2xxRvpBaseboardId;
    }
#else
    Int32 retval = 0;
    UInt8 regs[1];
    UInt8 vals[1] = {0};

    regs[0] = (address == KTCA9539_I2CADDR_SOM ? 0x00 : 0x01);

    retval = Bsp_deviceRead8(
                    BSP_DEVICE_I2C_INST_ID_0,
                    address,
                    regs,
                    vals,
                    1U);

    if(BSP_SOK == retval)
    {
        id = vals[0];
    }
#endif
    /* will return 0xFF if timeout */
    return id;
}

static Int32 Bsp_boardConfigureGPIOExpanders() {
    Int32 retVal = BSP_SOK;
    UInt8 tempAddr;
    UInt8 tempData;

    /* -------------------------------------------------------------------------
     * Setup GPIO expander U32
     * ---------------------------------------------------------------------- */

    /* Set all outputs low */
    tempAddr = BOARD_TCA9539_OUTPUT0_REG;
    tempData = 0x00;
    retVal = Bsp_deviceWrite8(KTCA9539_U32_I2CBUS,
                              KTCA9539_U32_I2CADDR,
                              &tempAddr,
                              &tempData,
                              (UInt32) 1U);
    GT_assert(BspBoardTrace, (retVal == BSP_SOK));

    tempAddr = BOARD_TCA9539_OUTPUT1_REG;
    tempData = 0x00;
    retVal = Bsp_deviceWrite8(KTCA9539_U32_I2CBUS,
                              KTCA9539_U32_I2CADDR,
                              &tempAddr,
                              &tempData,
                              (UInt32) 1U);
    GT_assert(BspBoardTrace, (retVal == BSP_SOK));

    /* Configure the following pins as outputs:
     *   fpd1_oen, fpd1_pdb, fpd2_oen, fpd2_pdb
     */
    tempAddr = BOARD_TCA9539_CONFIG0_REG; /*Pin direction of bank 0 pins*/
    tempData = 0xCC; /*[7:0] IIOO IIOO*/
    retVal = Bsp_deviceWrite8(KTCA9539_U32_I2CBUS,
                              KTCA9539_U32_I2CADDR,
                              &tempAddr,
                              &tempData,
                              (UInt32) 1U);
    GT_assert(BspBoardTrace, (retVal == BSP_SOK));

    /* Configure the following pins as outputs:
     *   fpd3_oen, fpd3_pdb, fpd3_oen, fpd3_pdb
     */
    tempAddr = BOARD_TCA9539_CONFIG1_REG; /*Pin direction of bank 0 pins*/
    tempData = 0xCC; /*[7:0] IIOO IIOO*/
    retVal = Bsp_deviceWrite8(KTCA9539_U32_I2CBUS,
                              KTCA9539_U32_I2CADDR,
                              &tempAddr,
                              &tempData,
                              (UInt32) 1U);
    GT_assert(BspBoardTrace, (retVal == BSP_SOK));

    /* -------------------------------------------------------------------------
     * Setup GPIO expander U34
     * ---------------------------------------------------------------------- */

    /* Set all outputs low */
    tempAddr = BOARD_TCA9539_OUTPUT0_REG;
    tempData = 0x00;
    retVal = Bsp_deviceWrite8(KTCA9539_U34_I2CBUS,
                              KTCA9539_U34_I2CADDR,
                              &tempAddr,
                              &tempData,
                              (UInt32) 1U);
    GT_assert(BspBoardTrace, (retVal == BSP_SOK));

    tempAddr = BOARD_TCA9539_OUTPUT1_REG;
    tempData = 0x00;
    retVal = Bsp_deviceWrite8(KTCA9539_U34_I2CBUS,
                              KTCA9539_U34_I2CADDR,
                              &tempAddr,
                              &tempData,
                              (UInt32) 1U);
    GT_assert(BspBoardTrace, (retVal == BSP_SOK));

    /* Configure the following pins as outputs:
     *   fpd5_oen, fpd5_pdb, fpd6_oen, fpd6_pdb, bus_ctl_vin5
     */
    tempAddr = BOARD_TCA9539_CONFIG0_REG; /*Pin direction of bank 0 pins*/
    tempData = 0xC4; /*[7:0] IIOO OIOO*/
    retVal = Bsp_deviceWrite8(KTCA9539_U34_I2CBUS,
                              KTCA9539_U34_I2CADDR,
                              &tempAddr,
                              &tempData,
                              (UInt32) 1U);
    GT_assert(BspBoardTrace, (retVal == BSP_SOK));

    /* Configure the following pins as outputs:
     *   fpd7_oen, fpd7_pdb, fpd8_oen, fpd8_pdb
     */
    tempAddr = BOARD_TCA9539_CONFIG1_REG; /*Pin direction of bank 0 pins*/
    tempData = 0xCC; /*[7:0] IIOO IIOO*/
    retVal = Bsp_deviceWrite8(KTCA9539_U34_I2CBUS,
                              KTCA9539_U34_I2CADDR,
                              &tempAddr,
                              &tempData,
                              (UInt32) 1U);
    GT_assert(BspBoardTrace, (retVal == BSP_SOK));


    /* -------------------------------------------------------------------------
     * Setup GPIO expander U33
     * ---------------------------------------------------------------------- */

    /* Set all outputs low */
    tempAddr = BOARD_TCA9539_OUTPUT0_REG;
    tempData = 0x00;
    retVal = Bsp_deviceWrite8(KTCA9539_U33_I2CBUS,
                              KTCA9539_U33_I2CADDR,
                              &tempAddr,
                              &tempData,
                              (UInt32) 1U);
    GT_assert(BspBoardTrace, (retVal == BSP_SOK));

    tempAddr = BOARD_TCA9539_OUTPUT1_REG;
    tempData = 0x00; /*[7:0] xxxx xx00*/
    retVal = Bsp_deviceWrite8(KTCA9539_U33_I2CBUS,
                              KTCA9539_U33_I2CADDR,
                              &tempAddr,
                              &tempData,
                              (UInt32) 1U);
    GT_assert(BspBoardTrace, (retVal == BSP_SOK));

    /* Configure the following pins as outputs:
     *   sepic_a_12v_sel, sepic_a_en, sepic_a_sw_en, sepic_b_12v_sel,
     *   sepic_b_en, sepic_b_sw_en
     */
    tempAddr = BOARD_TCA9539_CONFIG0_REG; /*Pin direction of bank 0 pins*/
    tempData = 0x88; /*[7:0] IOOO IOOO*/
    retVal = Bsp_deviceWrite8(KTCA9539_U33_I2CBUS,
                              KTCA9539_U33_I2CADDR,
                              &tempAddr,
                              &tempData,
                              (UInt32) 1U);
    GT_assert(BspBoardTrace, (retVal == BSP_SOK));


    /* Configure the following pins as outputs:
     *  bus_ctl_vin3a, fpd_925_pdb
     */
    tempAddr = BOARD_TCA9539_CONFIG1_REG;
    tempData = 0xFC; /*[7:0] IIII IIOO*/
    retVal = Bsp_deviceWrite8(KTCA9539_U33_I2CBUS,
                              KTCA9539_U33_I2CADDR,
                              &tempAddr,
                              &tempData,
                              (UInt32) 1U);
    GT_assert(BspBoardTrace, (retVal == BSP_SOK));
    return retVal;
}

static void Bsp_boardSetPinMuxTda2xxRVP()
{

    /* GPIO_2_0, PWDN Ethernet Phy */
    Bsp_platformSetPinmuxRegs(
            (UInt32) 14U,
            (UInt32) CTRL_CORE_PAD_GPMC_A10,
            BSP_PLATFORM_IOPAD_CFG_DEFAULT);

    GPIODirModeSet(SOC_GPIO2_BASE,0,GPIO_DIR_OUTPUT);
    GPIOPinWrite(SOC_GPIO2_BASE,0,1);


    Bsp_platformSetPinmuxRegs(
            (UInt32) 0xE,
            (UInt32) CTRL_CORE_PAD_GPMC_AD14,
            BSP_PLATFORM_IOPAD_CFG_DEFAULT);

    GPIODirModeSet(SOC_GPIO1_BASE,19,GPIO_DIR_OUTPUT);
    GPIOPinWrite(SOC_GPIO1_BASE,19,1);


    /* Hot Plug Detect with internal pullup so it is always on */
    Bsp_platformSetPinmuxRegs(
           (UInt32) 0x6,
           (UInt32) CTRL_CORE_PAD_SPI1_CS2,
           BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_UP);

    /* Swaps HDMI output polarity */
    UInt32* HDMI_PHY_PAD_CONFIG_CONTROL = (UInt32*) 0x5804030C;
    *HDMI_PHY_PAD_CONFIG_CONTROL |= 0x78000000;


    /* RGMII1 Pinmuxing*/


    /*Disable Unused MDIO pins to avoid mux conflict*/
    Bsp_platformSetPinmuxRegs(
            (UInt32) 15U,
            (UInt32) CTRL_CORE_PAD_MDIO_MCLK,
            BSP_PLATFORM_IOPAD_CFG_DEFAULT);

    /*Disable Unused MDIO pins to avoid mux conflict*/
    Bsp_platformSetPinmuxRegs(
            (UInt32) 15U,
            (UInt32) CTRL_CORE_PAD_MDIO_D,
            BSP_PLATFORM_IOPAD_CFG_DEFAULT);

    /*MDIO CLK*/
    Bsp_platformSetPinmuxRegs(
            (UInt32) 0x3U,
            (UInt32) CTRL_CORE_PAD_VIN2A_D10,
            BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_UP);

    /*MDIO DATA*/
    Bsp_platformSetPinmuxRegs(
            (UInt32) 3U,
            (UInt32) CTRL_CORE_PAD_VIN2A_D11,
            BSP_PLATFORM_IOPAD_CFG_DEFAULT);

    /*RGMII1_TXC*/
    Bsp_platformSetPinmuxRegs(
           (UInt32) 0x3,
           (UInt32) CTRL_CORE_PAD_VIN2A_D12,
           BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    /*RGMII1_TXCTL*/
    Bsp_platformSetPinmuxRegs(
           (UInt32) 0x3,
           (UInt32) CTRL_CORE_PAD_VIN2A_D13,
           BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    /*RGMII1_TXD3*/
    Bsp_platformSetPinmuxRegs(
           (UInt32) 0x3,
           (UInt32) CTRL_CORE_PAD_VIN2A_D14,
           BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    /*RGMII1_TXD2*/
    Bsp_platformSetPinmuxRegs(
           (UInt32) 0x3,
           (UInt32) CTRL_CORE_PAD_VIN2A_D15,
           BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    /*RGMII1_TXD1*/
    Bsp_platformSetPinmuxRegs(
           (UInt32) 0x3,
           (UInt32) CTRL_CORE_PAD_VIN2A_D16,
           BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    /*RGMII1_TXD0*/
    Bsp_platformSetPinmuxRegs(
           (UInt32) 0x3,
           (UInt32) CTRL_CORE_PAD_VIN2A_D17,
           BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    /*RGMII1_RXC*/
    Bsp_platformSetPinmuxRegs(
           (UInt32) 0x3,
           (UInt32) CTRL_CORE_PAD_VIN2A_D18,
           BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    /*RGMII1_RXCTL*/
    Bsp_platformSetPinmuxRegs(
           (UInt32) 0x3,
           (UInt32) CTRL_CORE_PAD_VIN2A_D19,
           BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    /*RGMII1_RXD3*/
    Bsp_platformSetPinmuxRegs(
           (UInt32) 0x3,
           (UInt32) CTRL_CORE_PAD_VIN2A_D20,
           BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    /*RGMII1_RXD2*/
    Bsp_platformSetPinmuxRegs(
           (UInt32) 0x3,
           (UInt32) CTRL_CORE_PAD_VIN2A_D21,
           BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    /*RGMII1_RXD1*/
    Bsp_platformSetPinmuxRegs(
           (UInt32) 0x3,
           (UInt32) CTRL_CORE_PAD_VIN2A_D22,
           BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    /*RGMII1_RXD0*/
    Bsp_platformSetPinmuxRegs(
           (UInt32) 0x3,
           (UInt32) CTRL_CORE_PAD_VIN2A_D23,
           BSP_PLATFORM_IOPAD_CFG_DEFAULT);


    /*UART3_RX*/
    Bsp_platformSetPinmuxRegs(
           (UInt32) 0x2,
           (UInt32) CTRL_CORE_PAD_UART2_CTSN,
           BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    /*UART3_TX*/
    Bsp_platformSetPinmuxRegs(
           (UInt32) 0x1,
           (UInt32) CTRL_CORE_PAD_UART2_RTSN,
           BSP_PLATFORM_IOPAD_CFG_DEFAULT);



    /* I2C4 sda */
    Bsp_platformSetPinmuxRegs((UInt32) 7,
                              (UInt32) CTRL_CORE_PAD_GPMC_A1,
                              BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    /* I2C4 sda */
    Bsp_platformSetPinmuxRegs((UInt32) 7,
                              (UInt32) CTRL_CORE_PAD_GPMC_A0,
                              BSP_PLATFORM_IOPAD_CFG_DEFAULT);

    /* I2C5 scl */
    Bsp_platformSetPinmuxRegs((UInt32) 7,
                              (UInt32) CTRL_CORE_PAD_GPMC_A4,
                              BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    /* I2C5 sda */
    Bsp_platformSetPinmuxRegs((UInt32) 7,
                              (UInt32) CTRL_CORE_PAD_GPMC_A5,
                              BSP_PLATFORM_IOPAD_CFG_DEFAULT);

    /* DCAN1 RX */
    Bsp_platformSetPinmuxRegs((UInt32) 1,
                              (UInt32) CTRL_CORE_PAD_WAKEUP0,
                              BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    /* DCAN1 TX */
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_DCAN1_TX,
                              BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    /* DCAN2 RX */
    Bsp_platformSetPinmuxRegs((UInt32) 1,
                              (UInt32) CTRL_CORE_PAD_WAKEUP1,
                              BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    /* DCAN2 TX */
    Bsp_platformSetPinmuxRegs((UInt32) 4,
                              (UInt32) CTRL_CORE_PAD_SPI1_CS2,
                              BSP_PLATFORM_IOPAD_CFG_DEFAULT);

    /*
     *   TDA2x_RVP 8CH inputs
     *   CAM1 ---> VIN3A
     *   CAM2 ---> VIN4A
     *   CAM3 ---> VIN6A
     *   CAM4 ---> VIN5A
     *   CAM5 ---> VIN2A
     *   CAM6 ---> VIN1A
     *   CAM7 ---> VIN1B
     *   CAM8 ---> VIN4B
     */
    /* VIN1-A pin mux */
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN1A_HSYNC0,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN1A_VSYNC0,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN1A_CLK0,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN1A_D0,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN1A_D1,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN1A_D2,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN1A_D3,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN1A_D4,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN1A_D5,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN1A_D6,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN1A_D7,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN1A_D8,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN1A_D9,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN1A_D10,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN1A_D11,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);

    /* VIN2-A pin mux */
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN2A_HSYNC0,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN2A_VSYNC0,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN2A_CLK0,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN2A_D0,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN2A_D1,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN2A_D2,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN2A_D3,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN2A_D4,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN2A_D5,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN2A_D6,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN2A_D7,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN2A_D8,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN2A_D9,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);

    /* VIN3-A pin mux */
    Bsp_platformSetPinmuxRegs((UInt32) 2U,
                              (UInt32) CTRL_CORE_PAD_GPMC_A8,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=GPMC_A8,  PIN=VIN3A_HSYNC0 */
    Bsp_platformSetPinmuxRegs((UInt32) 2U,
                              (UInt32) CTRL_CORE_PAD_GPMC_A9,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=GPMC_A9,  PIN=VIN3A_VSYNC0 */
    Bsp_platformSetPinmuxRegs((UInt32) 2U,
                              (UInt32) CTRL_CORE_PAD_GPMC_CS3,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=GPMC_CS3, PIN=VIN3A_CLK0 */
    Bsp_platformSetPinmuxRegs((UInt32) 2U,
                              (UInt32) CTRL_CORE_PAD_GPMC_AD0,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=GPMC_AD0,  PIN=VIN3A_D0 */
    Bsp_platformSetPinmuxRegs((UInt32) 2U,
                              (UInt32) CTRL_CORE_PAD_GPMC_AD1,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=GPMC_AD1,  PIN=VIN3A_D1 */
    Bsp_platformSetPinmuxRegs((UInt32) 2U,
                              (UInt32) CTRL_CORE_PAD_GPMC_AD2,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=GPMC_AD2,  PIN=VIN3A_D2 */
    Bsp_platformSetPinmuxRegs((UInt32) 2U,
                              (UInt32) CTRL_CORE_PAD_GPMC_AD3,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=GPMC_AD3,  PIN=VIN3A_D3 */
    Bsp_platformSetPinmuxRegs((UInt32) 2U,
                              (UInt32) CTRL_CORE_PAD_GPMC_AD4,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=GPMC_AD4,  PIN=VIN3A_D4 */
    Bsp_platformSetPinmuxRegs((UInt32) 2U,
                              (UInt32) CTRL_CORE_PAD_GPMC_AD5,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=GPMC_AD5,  PIN=VIN3A_D5 */
    Bsp_platformSetPinmuxRegs((UInt32) 2U,
                              (UInt32) CTRL_CORE_PAD_GPMC_AD6,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=GPMC_AD6,  PIN=VIN3A_D6 */
    Bsp_platformSetPinmuxRegs((UInt32) 2U,
                              (UInt32) CTRL_CORE_PAD_GPMC_AD7,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=GPMC_AD7,  PIN=VIN3A_D7 */
    Bsp_platformSetPinmuxRegs((UInt32) 2U,
                              (UInt32) CTRL_CORE_PAD_GPMC_AD8,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=GPMC_AD8,  PIN=VIN3A_D8 */
    Bsp_platformSetPinmuxRegs((UInt32) 2U,
                              (UInt32) CTRL_CORE_PAD_GPMC_AD9,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=GPMC_AD9,  PIN=VIN3A_D9 */
    Bsp_platformSetPinmuxRegs((UInt32) 2U,
                              (UInt32) CTRL_CORE_PAD_GPMC_AD10,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=GPMC_AD10,  PIN=VIN3A_D10 */
    Bsp_platformSetPinmuxRegs((UInt32) 2U,
                              (UInt32) CTRL_CORE_PAD_GPMC_AD11,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=GPMC_AD11,  PIN=VIN3A_D11 */

    /* VIN4-A pin mux */
    Bsp_platformSetPinmuxRegs((UInt32) 8U,
                              (UInt32) CTRL_CORE_PAD_GPIO6_14,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=GPIO6_14,    PIN=VIN4A_HSYNC0   */
    Bsp_platformSetPinmuxRegs((UInt32) 8U,
                              (UInt32) CTRL_CORE_PAD_GPIO6_15,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=GPIO6_15,    PIN=VIN4A_VSYNC0   */
    Bsp_platformSetPinmuxRegs((UInt32) 8U,
                              (UInt32) CTRL_CORE_PAD_XREF_CLK2,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=XREF_CLK2,    PIN=VIN4A_CLK0   */
    Bsp_platformSetPinmuxRegs((UInt32) 8U,
                              (UInt32) CTRL_CORE_PAD_MCASP1_ACLKR,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=MCASP1_ACLKR,    PIN=VIN4A_D0   */
    Bsp_platformSetPinmuxRegs((UInt32) 8U,
                              (UInt32) CTRL_CORE_PAD_MCASP1_FSR,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=MCASP1_FSR,    PIN=VIN4A_D1   */
    Bsp_platformSetPinmuxRegs((UInt32) 8U,
                              (UInt32) CTRL_CORE_PAD_MCASP1_AXR2,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=MCASP1_AXR2,    PIN=VIN4A_D2   */
    Bsp_platformSetPinmuxRegs((UInt32) 8U,
                              (UInt32) CTRL_CORE_PAD_MCASP1_AXR3,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=MCASP1_AXR3,    PIN=VIN4A_D3   */
    Bsp_platformSetPinmuxRegs((UInt32) 8U,
                              (UInt32) CTRL_CORE_PAD_MCASP1_AXR4,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=MCASP1_AXR4,    PIN=VIN4A_D4   */
    Bsp_platformSetPinmuxRegs((UInt32) 8U,
                              (UInt32) CTRL_CORE_PAD_MCASP1_AXR5,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=MCASP1_AXR5,    PIN=VIN4A_D5   */
    Bsp_platformSetPinmuxRegs((UInt32) 8U,
                              (UInt32) CTRL_CORE_PAD_MCASP1_AXR6,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=MCASP1_AXR6,    PIN=VIN4A_D6   */
    Bsp_platformSetPinmuxRegs((UInt32) 8U,
                              (UInt32) CTRL_CORE_PAD_MCASP1_AXR7,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=MCASP1_AXR7,    PIN=VIN4A_D7   */
    Bsp_platformSetPinmuxRegs((UInt32) 8U,
                              (UInt32) CTRL_CORE_PAD_MCASP2_ACLKR,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=MCASP2_ACLKR,    PIN=VIN4A_D8   */
    Bsp_platformSetPinmuxRegs((UInt32) 8U,
                              (UInt32) CTRL_CORE_PAD_MCASP2_FSR,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=MCASP2_FSR,    PIN=VIN4A_D9   */
    Bsp_platformSetPinmuxRegs((UInt32) 8U,
                              (UInt32) CTRL_CORE_PAD_MCASP2_AXR0,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=MCASP2_AXR0,    PIN=VIN4A_D10  */
    Bsp_platformSetPinmuxRegs((UInt32) 8U,
                              (UInt32) CTRL_CORE_PAD_MCASP2_AXR1,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=MCASP2_AXR1,    PIN=VIN4A_D11  */

    /* VIN5-A pin mux */
    Bsp_platformSetPinmuxRegs((UInt32) 9U,
                              (UInt32) CTRL_CORE_PAD_MMC3_DAT6,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=MMC3_DAT6, PIN=VIN5A_HSYNC0 */
    Bsp_platformSetPinmuxRegs((UInt32) 9U,
                              (UInt32) CTRL_CORE_PAD_MMC3_DAT7,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=MMC3_DAT7, PIN=VIN5A_VSYNC0 */
    Bsp_platformSetPinmuxRegs((UInt32) 9U,
                              (UInt32) CTRL_CORE_PAD_GPIO6_10,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=GPIO6_10,  PIN=VIN5A_CLK0 */
    Bsp_platformSetPinmuxRegs((UInt32) 9U,
                              (UInt32) CTRL_CORE_PAD_GPIO6_11,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=GPIO6_11, PIN=VIN5A_DE0 */
    Bsp_platformSetPinmuxRegs((UInt32) 9U,
                              (UInt32) CTRL_CORE_PAD_MCASP3_AXR1,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=MCASP3_AXR1, PIN=VIN5A_FLD0 */
    Bsp_platformSetPinmuxRegs((UInt32) 9U,
                              (UInt32) CTRL_CORE_PAD_MMC3_DAT5,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=MMC3_DAT5,  PIN=VIN5A_D0 */
    Bsp_platformSetPinmuxRegs((UInt32) 9U,
                              (UInt32) CTRL_CORE_PAD_MMC3_DAT4,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=MMC3_DAT4,  PIN=VIN5A_D1 */
    Bsp_platformSetPinmuxRegs((UInt32) 9U,
                              (UInt32) CTRL_CORE_PAD_MMC3_DAT3,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=MMC3_DAT3,  PIN=VIN5A_D2 */
    Bsp_platformSetPinmuxRegs((UInt32) 9U,
                              (UInt32) CTRL_CORE_PAD_MMC3_DAT2,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=MMC3_DAT2,  PIN=VIN5A_D3 */
    Bsp_platformSetPinmuxRegs((UInt32) 9U,
                              (UInt32) CTRL_CORE_PAD_MMC3_DAT1,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=MMC3_DAT1,  PIN=VIN5A_D4 */
    Bsp_platformSetPinmuxRegs((UInt32) 9U,
                              (UInt32) CTRL_CORE_PAD_MMC3_DAT0,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=MMC3_DAT0,  PIN=VIN5A_D5 */
    Bsp_platformSetPinmuxRegs((UInt32) 9U,
                              (UInt32) CTRL_CORE_PAD_MMC3_CMD,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=MMC3_CMD,   PIN=VIN5A_D6 */
    Bsp_platformSetPinmuxRegs((UInt32) 9U,
                              (UInt32) CTRL_CORE_PAD_MMC3_CLK,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=MMC3_CLK,   PIN=VIN5A_D7 */
    Bsp_platformSetPinmuxRegs((UInt32) 9U,
                              (UInt32) CTRL_CORE_PAD_MCASP5_AXR1,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=MCASP5_AXR1,  PIN=VIN3A_D8 */
    Bsp_platformSetPinmuxRegs((UInt32) 9U,
                              (UInt32) CTRL_CORE_PAD_MCASP5_AXR0,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=MCASP5_AXR0,  PIN=VIN3A_D9 */
    Bsp_platformSetPinmuxRegs((UInt32) 9U,
                              (UInt32) CTRL_CORE_PAD_MCASP5_FSX,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=MCASP5_FSX,  PIN=VIN3A_D10 */
    Bsp_platformSetPinmuxRegs((UInt32) 9U,
                              (UInt32) CTRL_CORE_PAD_MCASP5_ACLKX,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=MCASP5_ACLKX,  PIN=VIN3A_D11 */

    /* VIN6-A pin mux */
    Bsp_platformSetPinmuxRegs((UInt32) 7U,
                              (UInt32) CTRL_CORE_PAD_MCASP1_AXR1,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=MCASP1_AXR1,  PIN=VIN6A_HSYNC0   */
    Bsp_platformSetPinmuxRegs((UInt32) 7U,
                              (UInt32) CTRL_CORE_PAD_MCASP1_AXR0,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=MCASP1_AXR0,  PIN=VIN6A_VSYNC0   */
    Bsp_platformSetPinmuxRegs((UInt32) 7U,
                              (UInt32) CTRL_CORE_PAD_XREF_CLK1,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=XREF_CLK1,    PIN=VIN6A_CLK0   */
    Bsp_platformSetPinmuxRegs((UInt32) 7U,
                              (UInt32) CTRL_CORE_PAD_XREF_CLK0,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=XREF_CLK0,  PIN=VIN6A_D0   */
    Bsp_platformSetPinmuxRegs((UInt32) 7U,
                              (UInt32) CTRL_CORE_PAD_MCASP3_AXR0,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=MCASP3_AXR0,  PIN=VIN6A_D1   */
    Bsp_platformSetPinmuxRegs((UInt32) 7U,
                              (UInt32) CTRL_CORE_PAD_MCASP3_FSX,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=MCASP3_FSX,   PIN=VIN6A_D2   */
    Bsp_platformSetPinmuxRegs((UInt32) 7U,
                              (UInt32) CTRL_CORE_PAD_MCASP3_ACLKX,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=MCASP3_ACLKX, PIN=VIN6A_D3   */
    Bsp_platformSetPinmuxRegs((UInt32) 7U,
                              (UInt32) CTRL_CORE_PAD_MCASP2_AXR3,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=MCASP2_AXR3,  PIN=VIN6A_D4   */
    Bsp_platformSetPinmuxRegs((UInt32) 7U,
                              (UInt32) CTRL_CORE_PAD_MCASP2_AXR2,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=MCASP2_AXR2,  PIN=VIN6A_D5   */
    Bsp_platformSetPinmuxRegs((UInt32) 7U,
                              (UInt32) CTRL_CORE_PAD_MCASP2_FSX,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=MCASP2_FSX,   PIN=VIN6A_D6   */
    Bsp_platformSetPinmuxRegs((UInt32) 7U,
                              (UInt32) CTRL_CORE_PAD_MCASP2_ACLKX,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=MCASP2_ACLKX, PIN=VIN6A_D7   */
    Bsp_platformSetPinmuxRegs((UInt32) 7U,
                              (UInt32) CTRL_CORE_PAD_MCASP1_AXR15,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=MCASP1_AXR15,  PIN=VIN6A_D8 */
    Bsp_platformSetPinmuxRegs((UInt32) 7U,
                              (UInt32) CTRL_CORE_PAD_MCASP1_AXR14,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=MCASP1_AXR14,  PIN=VIN6A_D9 */
    Bsp_platformSetPinmuxRegs((UInt32) 7U,
                              (UInt32) CTRL_CORE_PAD_MCASP1_AXR13,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=MCASP1_AXR13,  PIN=VIN6A_D10 */
    Bsp_platformSetPinmuxRegs((UInt32) 7U,
                              (UInt32) CTRL_CORE_PAD_MCASP1_AXR12,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=MCASP1_AXR12,  PIN=VIN6A_D11 */

    /* VIN1-B pin mux */
    Bsp_platformSetPinmuxRegs((UInt32) 1U,
                              (UInt32) CTRL_CORE_PAD_VIN1A_DE0,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=VIN1A_DE0,  PIN=VIN1B_HSYNC1   */
    Bsp_platformSetPinmuxRegs((UInt32) 1U,
                              (UInt32) CTRL_CORE_PAD_VIN1A_FLD0,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=VIN1A_FLD0,  PIN=VIN1B_VSYNC1   */
    Bsp_platformSetPinmuxRegs((UInt32) 0U,
                              (UInt32) CTRL_CORE_PAD_VIN1B_CLK1,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=VIN1B_CLK1,    PIN=VIN1B_CLK1   */
    Bsp_platformSetPinmuxRegs((UInt32) 1U,
                              (UInt32) CTRL_CORE_PAD_VIN1A_D23,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=VIN1A_D23,  PIN=VIN1B_D0   */
    Bsp_platformSetPinmuxRegs((UInt32) 1U,
                              (UInt32) CTRL_CORE_PAD_VIN1A_D22,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=VIN1A_D22,  PIN=VIN1B_D1   */
    Bsp_platformSetPinmuxRegs((UInt32) 1U,
                              (UInt32) CTRL_CORE_PAD_VIN1A_D21,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=VIN1A_D21,   PIN=VIN1B_D2   */
    Bsp_platformSetPinmuxRegs((UInt32) 1U,
                              (UInt32) CTRL_CORE_PAD_VIN1A_D20,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=VIN1A_D20, PIN=VIN1B_D3   */
    Bsp_platformSetPinmuxRegs((UInt32) 1U,
                              (UInt32) CTRL_CORE_PAD_VIN1A_D19,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=VIN1A_D19,  PIN=VIN1B_D4   */
    Bsp_platformSetPinmuxRegs((UInt32) 1U,
                              (UInt32) CTRL_CORE_PAD_VIN1A_D18,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=VIN1A_D18,  PIN=VIN1B_D5   */
    Bsp_platformSetPinmuxRegs((UInt32) 1U,
                              (UInt32) CTRL_CORE_PAD_VIN1A_D17,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=VIN1A_D17,   PIN=VIN1B_D6   */
    Bsp_platformSetPinmuxRegs((UInt32) 1U,
                              (UInt32) CTRL_CORE_PAD_VIN1A_D16,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=VIN1A_D16, PIN=VIN1B_D7   */

    /* VIN4-B pin mux */
    Bsp_platformSetPinmuxRegs((UInt32) 5U,
                              (UInt32) CTRL_CORE_PAD_RGMII0_TXD2,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=RGMII0_TXD2,  PIN=VIN4B_HSYNC1   */
    Bsp_platformSetPinmuxRegs((UInt32) 5U,
                              (UInt32) CTRL_CORE_PAD_RGMII0_TXD1,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=RGMII0_TXD1,  PIN=VIN4B_VSYNC1   */
    Bsp_platformSetPinmuxRegs((UInt32) 5U,
                              (UInt32) CTRL_CORE_PAD_MDIO_MCLK,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=MDIO_MCLK,    PIN=VIN4B_CLK1   */
    Bsp_platformSetPinmuxRegs((UInt32) 5U,
                              (UInt32) CTRL_CORE_PAD_MDIO_D,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=MDIO_D,  PIN=VIN4B_D0   */
    Bsp_platformSetPinmuxRegs((UInt32) 5U,
                              (UInt32) CTRL_CORE_PAD_UART3_RXD,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=UART3_RXD,  PIN=VIN4B_D1   */
    Bsp_platformSetPinmuxRegs((UInt32) 5U,
                              (UInt32) CTRL_CORE_PAD_UART3_TXD,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=UART3_TXD,   PIN=VIN4B_D2   */
    Bsp_platformSetPinmuxRegs((UInt32) 5U,
                              (UInt32) CTRL_CORE_PAD_RGMII0_TXC,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=RGMII0_TXC, PIN=VIN4B_D3   */
    Bsp_platformSetPinmuxRegs((UInt32) 5U,
                              (UInt32) CTRL_CORE_PAD_RGMII0_TXCTL,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=RGMII0_TXCTL,  PIN=VIN4B_D4   */
    Bsp_platformSetPinmuxRegs((UInt32) 5U,
                              (UInt32) CTRL_CORE_PAD_RGMII0_RXC,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=RGMII0_RXC,  PIN=VIN4B_D5   */
    Bsp_platformSetPinmuxRegs((UInt32) 5U,
                              (UInt32) CTRL_CORE_PAD_RGMII0_RXCTL,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=RGMII0_RXCTL,   PIN=VIN4B_D6   */
    Bsp_platformSetPinmuxRegs((UInt32) 5U,
                              (UInt32) CTRL_CORE_PAD_RGMII0_RXD3,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI | BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    /* PAD=RGMII0_RXD3, PIN=VIN4B_D7   */
}
