/*
 *   Copyright (c) Texas Instruments Incorporated 2012-2017
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
#include <bsp_boardTda2xxDefault.h>
#include <bsp_boardTda2pxDefault.h>
#include <bsp_boardTda2xxVision.h>
#include <bsp_boardTda2xxJamr3.h>
#include <bsp_boardTda2xxMultiDes.h>
#include <bsp_boardTda2xxMonsterCam.h>
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined (SOC_TDA2EX)
#include <ti/drv/pm/pmhal.h>
#endif
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

#define BOARD_PCF8575_EXVIN2_S0             (PCF8575_P1_1_MASK)
#define BOARD_PCF8575_EXVIN2_S2             (PCF8575_P1_2_MASK)

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

/* Base board LCD power select */
#define BOARD_GPIO_BASE_LCD_PWDN            ((UInt32) SOC_GPIO3_BASE)
#define BOARD_GPIO_PIN_LCD_PWDN             ((UInt32) 1U)

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

/*  JAMR3 board PCF8575 1 (on I2C1/I2C4) - mappings
 *  P0_0 - BOARD_PCF8575_MMC_CD
 *  P0_1 - BOARD_PCF8575_MMC_WP
 *  P0_2 - HI_ISOL_4
 *  P0_3 - EN_DAB3_4
 *  P0_4 - EN_DABL_4
 *  P0_5 - HI_ISOL_3
 *  P0_6 - EN_DAB3_3
 *  P0_7 - EN_DABL_3
 *  P1_0 - SEL_TVP_FPD
 *  P1_2 - HI_ISOL_2
 *  P1_3 - EN_DAB3_2
 *  P1_4 - EN_DABL_2
 *  P1_5 - HI_ISOL_1
 *  P1_6 - EN_DAB3_1
 *  P1_7 - EN_DABL_1
 */
#define BOARD_PCF8575_MMC_CD                (PCF8575_P0_0_MASK)
#define BOARD_PCF8575_MMC_WP                (PCF8575_P0_1_MASK)
#define BOARD_PCF8575_HI_ISOL_4             (PCF8575_P0_2_MASK)
#define BOARD_PCF8575_EN_DAB3_4             (PCF8575_P0_3_MASK)
#define BOARD_PCF8575_EN_DABL_4             (PCF8575_P0_4_MASK)
#define BOARD_PCF8575_HI_ISOL_3             (PCF8575_P0_5_MASK)
#define BOARD_PCF8575_EN_DAB3_3             (PCF8575_P0_6_MASK)
#define BOARD_PCF8575_EN_DABL_3             (PCF8575_P0_7_MASK)
#define BOARD_PCF8575_SEL_TVP_FPD           (PCF8575_P1_0_MASK)
#define BOARD_PCF8575_HI_ISOL_2             (PCF8575_P1_2_MASK)
#define BOARD_PCF8575_EN_DAB3_2             (PCF8575_P1_3_MASK)
#define BOARD_PCF8575_EN_DABL_2             (PCF8575_P1_4_MASK)
#define BOARD_PCF8575_HI_ISOL_1             (PCF8575_P1_5_MASK)
#define BOARD_PCF8575_EN_DAB3_1             (PCF8575_P1_6_MASK)
#define BOARD_PCF8575_EN_DABL_1             (PCF8575_P1_7_MASK)

/* MonsterCam Board specific */
#define BOARD_GPIO_BASE_MUX_SEL_RESET             ((UInt32) SOC_GPIO8_BASE)
#define BOARD_GPIO_BASE_MUX_SEL1_RESET            ((UInt32) SOC_GPIO1_BASE)
#define BOARD_GPIO_PIN_MUX1_SEL0_RESET            ((UInt32) 0U)
#define BOARD_GPIO_PIN_MUX1_SEL1_RESET            ((UInt32) 1U)
#define BOARD_GPIO_PIN_MUX1_SEL4_RESET            ((UInt32) 4U)
#define BOARD_GPIO_PIN_MUX1_SEL7_RESET            ((UInt32) 7U)
#define BOARD_GPIO_PIN_MUX1_SEL5_RESET            ((UInt32) 5U)
#define BOARD_GPIO_PIN_GPIO2_27                   ((UInt32) 27U)

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

static Int32 Bsp_boardPowerOnDeviceTda2xx(UInt32 devDrvId,
                                          UInt32 instId,
                                          UInt32 powerOn);
static Int32 Bsp_boardSelectDeviceTda2xx(UInt32 devDrvId, UInt32 instId);
static Int32 Bsp_boardSelectDeviceTda2xxVision(UInt32 devDrvId, UInt32 instId);
static Int32 Bsp_boardSelectDeviceTda2xxMonsterCam(UInt32 devDrvId,
                                                   UInt32 instId);
static Int32 Bsp_boardSelectDeviceTda2xxJamr3(UInt32 devDrvId, UInt32 instId);
static Int32 Bsp_boardSelectDeviceTda2xxMultiDes(UInt32 devDrvId,
                                                 UInt32 instId);
static Int32 Bsp_boardTda2xxEnableMmc1(void);
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined (SOC_TDA2EX)
static Int32 Bsp_boardTda2xxMmcsdLdoPwr(void);
#endif

#if defined (TDA2XX_MC_BUILD)
static void Bsp_boardSetPinMuxTda2xxMC(void);
#endif

#if defined (BOARD_TYPE_TDA2XX_CASCADE_RADAR)
/* Output register to change state of output BIT set to 1, output set HIGH */
#define BSP_BOARD_TCA9539_REG_OUTPUT0   (0x02U)
#define BSP_BOARD_TCA9539_REG_OUTPUT1   (0x03U)

/* Configuration register. BIT = '1' sets port to input, BIT = '0' sets
 * port to output */
#define BSP_BOARD_TCA9539_REG_CONFIG0   (0x06U)
#define BSP_BOARD_TCA9539_REG_CONFIG1   (0x07U)

/* I2C address of TCA9539-Q1 expander -. */
#define BSP_BOARD_TCA9539_I2C_SLAVE_ADDR (0x76U)

static void Bsp_boardTda2xxCascadeEnableSdAndEth(void);
static void Bsp_boardTda2xxCascadeAwr12xxPadConfig(void);
static void Bsp_boardTda2xxCascadeVipPadConfig(void);
#endif

#ifdef __cplusplus
}
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

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
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined (SOC_TDA2EX)
#ifndef BSP_DISABLE_I2C2
    {
        BSP_DEVICE_I2C_INST_ID_2,           /* instId */
        SOC_I2C3_BASE,                      /* baseAddr */
        CSL_INTC_EVENTID_I2CINT3,           /* intNum */
        400U                                /* busClkKHz */
    },
#endif  /* #ifndef BSP_DISABLE_I2C2 */
#if defined (TDA2XX_MC_BUILD)
    {
        BSP_DEVICE_I2C_INST_ID_4,           /* instId */
        SOC_I2C5_BASE,                      /* baseAddr */
        CSL_INTC_EVENTID_I2CINT4,           /* intNum */
        400U                                /* busClkKHz */
    },
#else
#ifndef BSP_DISABLE_I2C3
    {
        BSP_DEVICE_I2C_INST_ID_3,           /* instId */
        SOC_I2C4_BASE,                      /* baseAddr */
        CSL_INTC_EVENTID_I2CINT4,           /* intNum */
        400U                                /* busClkKHz */
    },
#endif  /* #ifndef BSP_DISABLE_I2C3 */
#endif
#endif

#if defined (SOC_TDA2PX)
#ifndef BSP_DISABLE_I2C4
    {
        BSP_DEVICE_I2C_INST_ID_4,           /* instId */
        SOC_I2C5_BASE,                      /* baseAddr */
        CSL_INTC_EVENTID_I2CINT5,           /* intNum */
        400U                                /* busClkKHz */
    }
#endif
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

static Bsp_BoardData        gBoardTda2xxCustomData =
{
    0U,                                     /* numDev */
    NULL,                                   /* devData */
};

#if defined (SOC_TDA2PX)
static Bsp_BoardDeviceData  gBoardTda2xxDefaultDevData[] =
    BSP_BOARD_TDA2PX_DEFAULT_DEVDATA;
#else
static Bsp_BoardDeviceData  gBoardTda2xxDefaultDevData[] =
    BSP_BOARD_TDA2XX_DEFAULT_DEVDATA;
#endif

static Bsp_BoardDeviceData  gBoardTda2xxMCDevData[] =
    BSP_BOARD_TDA2XX_MONSTERCAM_DEVDATA;

static Bsp_BoardDeviceData  gBoardTda2xxVisionDevData[] =
    BSP_BOARD_TDA2XX_VISION_DEVDATA;

static Bsp_BoardDeviceData  gBoardTda2xxJamr3DevData[] =
    BSP_BOARD_TDA2XX_JAMR3_DEVDATA;

static Bsp_BoardDeviceData  gBoardTda2xxMultiDesDevData[] =
    BSP_BOARD_TDA2XX_MULTIDES_DEVDATA;

#if defined (SOC_TDA2PX)
static Bsp_BoardDeviceData  gBoardTda2pxCalDevData[] =
    BSP_BOARD_TDA2PX_CAL_UB960_OV10635_DEVDATA;
#endif

static Bsp_BoardData        gBoardTda2xxDefaultData =
{
    /* numDev */
    (sizeof (gBoardTda2xxDefaultDevData) / sizeof (Bsp_BoardDeviceData)),
    /* devData */
    gBoardTda2xxDefaultDevData,
};

static Bsp_BoardData        gBoardTda2xxMCData =
{
    /* numDev */
    (sizeof (gBoardTda2xxMCDevData) / sizeof (Bsp_BoardDeviceData)),
    /* devData */
    gBoardTda2xxMCDevData,
};

/* This is not static as TI814x interposer board need this */
Bsp_BoardData gBoardTda2xxVisionData =
{
    /* numDev */
    (sizeof (gBoardTda2xxVisionDevData) / sizeof (Bsp_BoardDeviceData)),
    /* devData */
    gBoardTda2xxVisionDevData,
};

static Bsp_BoardData        gBoardTda2xxJamr3Data =
{
    /* numDev */
    (sizeof (gBoardTda2xxJamr3DevData) / sizeof (Bsp_BoardDeviceData)),
    /* devData */
    gBoardTda2xxJamr3DevData,
};

static Bsp_BoardData        gBoardTda2xxMultiDesData =
{
    /* numDev */
    (sizeof (gBoardTda2xxMultiDesDevData) / sizeof (Bsp_BoardDeviceData)),
    /* devData */
    gBoardTda2xxMultiDesDevData,
};

#if defined (SOC_TDA2PX)
static Bsp_BoardData        gBoardTda2pxCalDevicesData =
{
    /* numDev */
    (sizeof (gBoardTda2pxCalDevData) / sizeof (Bsp_BoardDeviceData)),
    /* devData */
    gBoardTda2pxCalDevData,
};
#endif

/* Tda2xx interposer */
extern Bsp_BoardData        gBoardTda3xxDefaultData;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

Int32 Bsp_boardTda2xxLateInit(void)
{

#if defined (BOARD_TYPE_TDA2XX_CASCADE_RADAR)
    Bsp_boardTda2xxCascadeAwr12xxPadConfig();
    Bsp_boardTda2xxCascadeEnableSdAndEth();
#endif
    return (BSP_SOK);

}
Int32 Bsp_boardTda2xxInit(void)
{
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined (SOC_TDA2EX)
#if defined (BOARD_TYPE_TDA2XX_CASCADE_RADAR)
    Bsp_boardTda2xxCascadeVipPadConfig();
#else
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
#if defined (TDA2XX_MC_BUILD)
    Bsp_boardSetPinMuxTda2xxMC();
#endif
#endif
#endif

    return (BSP_SOK);
}

Bsp_BoardId Bsp_boardGetIdTda2xx(void)
{
    Bsp_BoardId boardId = BSP_BOARD_UNKNOWN;
#if defined (BOARD_TYPE_TDA2XX_CASCADE_RADAR)
    boardId = BSP_BOARD_TDA2XX_CASCADE_RADAR;
#else
#if defined (PLATFORM_ZEBU) || defined (PLATFORM_VIRTIO)
    boardId = BSP_BOARD_VISION;
#else
    Int32       retVal = FVID2_EFAIL;
    const Bsp_BoardI2cData *i2cData;

    i2cData = Bsp_boardGetI2cData();
    GT_assert(BspBoardTrace, (i2cData != NULL));

    /*
     * Detect board ID
     */

#if defined (TDA2XX_MC_BUILD)
    /*
     * Probe for AUDIO CODEC Chip in MonsterCam board @ 0x18 address to
     * detect MONSTER CAMERA BASE board
     */
    retVal = Bsp_deviceI2cProbeDevice(
        BSP_DEVICE_I2C_INST_ID_0,
        BOARD_TLV320AIC3106_I2C_ADDR_0);
    if (FVID2_SOK == retVal)
    {
        boardId = BSP_BOARD_MONSTERCAM;
    }
#else /* #if defined (TDA2XX_MC_BUILD) */
    if (FVID2_SOK != retVal)
    {
        /*
         * Probe for IO Expander 1 in MULTI DES @ 0x25 address to detect
         * MULTI DESERIALISER daughter card.
         */
        retVal = Bsp_deviceI2cProbeDevice(
            i2cData->probeInstId,
            BOARD_MULTIDES_IO_EXP_I2C_ADDR_0);
        if (FVID2_SOK == retVal)
        {
            boardId = BSP_BOARD_MULTIDES;
        }

        if (FVID2_SOK != retVal)
        {
            /*
             * Probe for SII9127 @ 0x31 address to detect
             * Vision daughter card.
             */
            retVal = Bsp_deviceI2cProbeDevice(
                i2cData->probeInstId,
                BOARD_SII9127_I2C_ADDR_1);
            if (FVID2_SOK == retVal)
            {
                boardId = BSP_BOARD_VISION;

#ifndef BSP_DISABLE_I2C0
                /*
                 * Probe for EEPROM @ 0x51 address to detect
                 * Tda3xx base board. This is required as both Tda2xx and
                 * Tda3xx has SII9127 @ 0x31 address
                 */
                retVal = Bsp_deviceI2cProbeDevice(
                    BSP_DEVICE_I2C_INST_ID_0,
                    BOARD_EEPROM_I2C_ADDR_1);
                if (FVID2_SOK == retVal)
                {
                    boardId = BSP_BOARD_BASE_TDA3XX;
                }
                else
                {
                    /*
                     * if EEPROM is not detected then it is TDA2xx Vision
                     * Board
                     */
                    retVal = FVID2_SOK;
                }
#endif              /* #ifndef BSP_DISABLE_I2C0 */
            }
        }
    }

    if (FVID2_SOK != retVal)
    {
        /*
         * Probe for TVP5158 @ 0x58 address to detect
         * JAMR3 daughter card.
         */
        retVal = Bsp_deviceI2cProbeDevice(
            i2cData->probeInstId,
            BOARD_TVP5158_I2C_ADDR_0);
        if (FVID2_SOK == retVal)
        {
            boardId = BSP_BOARD_JAMR3;
        }
    }

#ifndef BSP_DISABLE_I2C0
    if (FVID2_SOK != retVal)
    {
        /*
         * Probe for EEPROM @ 0x51 address to detect
         * TDA3XX base board.
         * Note: This should be the last check as base board is
         * present by default even when daughter card is present.
         */
        retVal = Bsp_deviceI2cProbeDevice(
            BSP_DEVICE_I2C_INST_ID_0,
            BOARD_EEPROM_I2C_ADDR_1);
        if (FVID2_SOK == retVal)
        {
            boardId = BSP_BOARD_BASE_TDA3XX;
        }
    }

    if (FVID2_SOK != retVal)
    {
        /*
         * Probe for EEPROM @ 0x50 address to detect
         * TDA2XX base board.
         * Note: This should be the last check as base board is
         * present by default even when daughter card is present.
         */
        retVal = Bsp_deviceI2cProbeDevice(
            BSP_DEVICE_I2C_INST_ID_0,
            BOARD_EEPROM_I2C_ADDR_0);
        if (FVID2_SOK == retVal)
        {
            /* Default to vision board when base board is detected.
             * This is required because in some of the vision
             * boards, SII9127 HDMI is not populated. And hence even if
             * vision board is connected, we detect as base board */
            boardId = BSP_BOARD_VISION;
        }
    }
#else
    /* Default to vision board when I2C is disabled as we can't
     * detect base board. */
    if (FVID2_SOK != retVal)
    {
        boardId = BSP_BOARD_VISION;
        retVal  = FVID2_SOK;
    }
#endif /* #ifndef BSP_DISABLE_I2C0 */
#endif /* #if defined (TDA2XX_MC_BUILD) */
#endif /* #if defined (PLATFORM_ZEBU) || defined (PLATFORM_VIRTIO) */
#endif /* #if defined (BOARD_TYPE_TDA2XX_CASCADE_RADAR) */
    return (boardId);
}

Bsp_BoardRev Bsp_boardGetBaseBoardRevTda2xx(void)
{
    Bsp_BoardRev      boardRev = BSP_BOARD_REV_A;
#ifndef BSP_DISABLE_I2C0
    Int32             retVal;
    UInt8             regValue[2];
    UInt32            i2cInst, eepromAddr, page, pageSize, delay, numRegs;
    Bsp_BoardEepromId eepromVal;
    Bsp_BoardId       boardId;

    boardId    = Bsp_boardGetId();
    i2cInst    = BSP_DEVICE_I2C_INST_ID_0;
    eepromAddr = (UInt32) BOARD_EEPROM_I2C_ADDR_0;
    if (BSP_BOARD_BASE_TDA3XX == boardId)
    {
        eepromAddr = (UInt32) BOARD_EEPROM_I2C_ADDR_1;
    }

    /* Send 16-bit page address */
    page        = 0U;
    pageSize    = 48U;
    regValue[0] = (UInt8) (page >> 8U);         /* HIGH address */
    regValue[1] = (UInt8) (page & 0xFFU);       /* LOW address */
    numRegs     = 2U;
    retVal      = Bsp_deviceRawWrite8(i2cInst, eepromAddr, regValue, numRegs);

    /* Eeprom write cycle time is 5ms - so wait for 5ms after
     * write before reading */
    delay = 5U;
    BspOsal_sleep(delay);

    /* Read 0th page */
    retVal += Bsp_deviceRawRead8(
        i2cInst,
        eepromAddr,
        (UInt8 *) &eepromVal,
        pageSize);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspBoardTrace, GT_ERR, "EEPROM read failed!!\r\n");
    }

    if (FVID2_SOK == retVal)
    {
        if (eepromVal.header == 0xAA5533EEU)
        {
            GT_1trace(BspBoardTrace, GT_INFO,
                      " EEPROM Base Board Name: [%s]\r\n", eepromVal.boardName);
            switch (eepromVal.versionMajor)
            {
                case 0x01U:
                    boardRev = BSP_BOARD_REV_A;
                    break;

                case 0x02U:
                    boardRev = BSP_BOARD_REV_B;
                    break;

                case 0x03U:
                    boardRev = BSP_BOARD_REV_C;
                    break;

                case 0x04U:
                    boardRev = BSP_BOARD_REV_D;
                    break;

                case 0x05U:
                    boardRev = BSP_BOARD_REV_E;
                    break;

                default:
                    boardRev = BSP_BOARD_REV_E;
                    break;
            }
        }
        else
        {
            GT_0trace(BspBoardTrace, GT_INFO,
                      " EEPROM Board Info Header Mismatch!!\r\n");
            if (BSP_BOARD_TDA2XX_CASCADE_RADAR == boardId)
            {
                boardRev = BSP_BOARD_REV_E;
            }
        }
    }
#elif defined (BOARD_TYPE_TDA2XX_CASCADE_RADAR)
    boardRev = BSP_BOARD_REV_E;
#endif /* #ifndef BSP_DISABLE_I2C0 */

    return (boardRev);
}

Bsp_BoardRev Bsp_boardGetDcRevTda2xx(void)
{
    Int32        retVal;
    Bsp_BoardId  boardId;
    Bsp_BoardRev boardRev = BSP_BOARD_REV_A;
    const Bsp_BoardI2cData *i2cData;

    boardId = Bsp_boardGetId();
    i2cData = Bsp_boardGetI2cData();
    GT_assert(BspBoardTrace, (i2cData != NULL));

    if ((BSP_BOARD_VISION == boardId) || (BSP_BOARD_MULTIDES == boardId))
    {
        /*
         * REV D boards doesn't have SII9127 and instead have ADV7611.
         * Probe for SII9127 @ 0x31 address to detect < REV D boards.
         */
        retVal = Bsp_deviceI2cProbeDevice(
            i2cData->probeInstId,
            BOARD_SII9127_I2C_ADDR_1);
        if (FVID2_SOK != retVal)
        {
            /* No SII9127 detected, so REV D boards */
            boardRev = BSP_BOARD_REV_D;
        }
    }

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
            case BSP_BOARD_BASE_TDA2XX:
            case BSP_BOARD_BASE_TDA2PX:
                numDev += gBoardTda2xxDefaultData.numDev;
                /* Array bound check */
                GT_assert(BspBoardTrace, numDev < BOARD_MAX_DEVICE);
                BspUtils_memcpy(
                    tempDevData,
                    gBoardTda2xxDefaultData.devData,
                    (sizeof (Bsp_BoardDeviceData) *
                     gBoardTda2xxDefaultData.numDev));
                tempDevData += gBoardTda2xxDefaultData.numDev;
                break;

            case BSP_BOARD_BASE_TDA3XX:
                numDev += gBoardTda3xxDefaultData.numDev;
                /* Array bound check */
                GT_assert(BspBoardTrace, numDev < BOARD_MAX_DEVICE);
                BspUtils_memcpy(
                    tempDevData,
                    gBoardTda3xxDefaultData.devData,
                    (sizeof (Bsp_BoardDeviceData) *
                     gBoardTda3xxDefaultData.numDev));
                tempDevData += gBoardTda3xxDefaultData.numDev;
                break;

            case BSP_BOARD_VISION:
                numDev += gBoardTda2xxDefaultData.numDev;
                numDev += gBoardTda2xxVisionData.numDev;
#if defined (SOC_TDA2PX)
                numDev += gBoardTda2pxCalDevicesData.numDev;
#endif

                /* Array bound check */
                GT_assert(BspBoardTrace, numDev < BOARD_MAX_DEVICE);
                BspUtils_memcpy(
                    tempDevData,
                    gBoardTda2xxDefaultData.devData,
                    (sizeof (Bsp_BoardDeviceData) *
                     gBoardTda2xxDefaultData.numDev));
                tempDevData += gBoardTda2xxDefaultData.numDev;
                BspUtils_memcpy(
                    tempDevData,
                    gBoardTda2xxVisionData.devData,
                    (sizeof (Bsp_BoardDeviceData) *
                     gBoardTda2xxVisionData.numDev));
                tempDevData += gBoardTda2xxVisionData.numDev;

#if defined (SOC_TDA2PX)
                BspUtils_memcpy(
                    tempDevData,
                    gBoardTda2pxCalDevicesData.devData,
                    (sizeof (Bsp_BoardDeviceData) *
                     gBoardTda2pxCalDevicesData.numDev));
                tempDevData += gBoardTda2pxCalDevicesData.numDev;
#endif
                break;

            case BSP_BOARD_MONSTERCAM:
                numDev += gBoardTda2xxMCData.numDev;
                /* Array bound check */
                GT_assert(BspBoardTrace, numDev < BOARD_MAX_DEVICE);
                BspUtils_memcpy(
                    tempDevData,
                    gBoardTda2xxMCData.devData,
                    (sizeof (Bsp_BoardDeviceData) *
                     gBoardTda2xxMCData.numDev));
                tempDevData += gBoardTda2xxMCData.numDev;
                break;

            case BSP_BOARD_JAMR3:
                numDev += gBoardTda2xxDefaultData.numDev;
                numDev += gBoardTda2xxJamr3Data.numDev;
                /* Array bound check */
                GT_assert(BspBoardTrace, numDev < BOARD_MAX_DEVICE);
                BspUtils_memcpy(
                    tempDevData,
                    gBoardTda2xxDefaultData.devData,
                    (sizeof (Bsp_BoardDeviceData) *
                     gBoardTda2xxDefaultData.numDev));
                tempDevData += gBoardTda2xxDefaultData.numDev;
                BspUtils_memcpy(
                    tempDevData,
                    gBoardTda2xxJamr3Data.devData,
                    (sizeof (Bsp_BoardDeviceData) *
                     gBoardTda2xxJamr3Data.numDev));
                tempDevData += gBoardTda2xxJamr3Data.numDev;
                break;

            case BSP_BOARD_MULTIDES:
                numDev += gBoardTda2xxDefaultData.numDev;
                numDev += gBoardTda2xxVisionData.numDev;
                numDev += gBoardTda2xxMultiDesData.numDev;
#if defined (SOC_TDA2PX)
                numDev += gBoardTda2pxCalDevicesData.numDev;
#endif

                /* Array bound check */
                GT_assert(BspBoardTrace, numDev < BOARD_MAX_DEVICE);
                BspUtils_memcpy(
                    tempDevData,
                    gBoardTda2xxDefaultData.devData,
                    (sizeof (Bsp_BoardDeviceData) *
                     gBoardTda2xxDefaultData.numDev));
                tempDevData += gBoardTda2xxDefaultData.numDev;
                BspUtils_memcpy(
                    tempDevData,
                    gBoardTda2xxVisionData.devData,
                    (sizeof (Bsp_BoardDeviceData) *
                     gBoardTda2xxVisionData.numDev));
                tempDevData += gBoardTda2xxVisionData.numDev;
                BspUtils_memcpy(
                    tempDevData,
                    gBoardTda2xxMultiDesData.devData,
                    (sizeof (Bsp_BoardDeviceData) *
                     gBoardTda2xxMultiDesData.numDev));
                tempDevData += gBoardTda2xxMultiDesData.numDev;

#if defined (SOC_TDA2PX)
                BspUtils_memcpy(
                    tempDevData,
                    gBoardTda2pxCalDevicesData.devData,
                    (sizeof (Bsp_BoardDeviceData) *
                     gBoardTda2pxCalDevicesData.numDev));
                tempDevData += gBoardTda2pxCalDevicesData.numDev;
#endif
                break;

            case BSP_BOARD_CUSTOM:
                numDev += gBoardTda2xxCustomData.numDev;
                /* Array bound check */
                GT_assert(BspBoardTrace, numDev < BOARD_MAX_DEVICE);
                BspUtils_memcpy(
                    tempDevData,
                    gBoardTda2xxCustomData.devData,
                    (sizeof (Bsp_BoardDeviceData) *
                     gBoardTda2xxCustomData.numDev));
                tempDevData += gBoardTda2xxDefaultData.numDev;
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

/* Base EVM mux select */
static Int32 Bsp_boardSelectDeviceTda2xx(UInt32 devDrvId, UInt32 instId)
{
    Int32  retVal = BSP_SOK;
    UInt8  regValue[2];
    UInt32 i2cInst, ioExpAddr, numRegs;
    const Bsp_BoardI2cData *i2cData;
    UInt32 regValueTemp;
    UInt32 i2cInstValid;

    i2cData = Bsp_boardGetI2cData();
    GT_assert(BspBoardTrace, (i2cData != NULL));

    /*
     * Select base EVM leapord imaging sensor or daughter card input for
     * VIN1 signals.
     *
     * CAM_FPD_MUX_S0 = 0 for base EVM input from leapord imaging sensor.
     * CAM_FPD_MUX_S0 = 1 for daughter card input.
     */
    if ((FVID2_VID_SENSOR_OV1063X_DRV == devDrvId) ||
        (FVID2_VID_SENSOR_LI_OV1063X_DRV == devDrvId) ||
        (FVID2_VID_SENSOR_MULDES_OV1063X_DRV == devDrvId) ||
        (FVID2_VID_SENSOR_GW4200_IMX290_DRV == devDrvId) ||
        (FVID2_VID_SENSOR_APT_AR0132_DRV == devDrvId) ||
        (FVID2_VID_DEC_SII9127_DRV == devDrvId) ||
        (FVID2_VID_DEC_ADV7611_DRV == devDrvId) ||
        (FVID2_VID_DEC_TVP5158_DRV == devDrvId) ||
        (BSP_DRV_ID_UART == devDrvId) ||
        (BSP_DRV_ID_MCSPI == devDrvId) ||
        (BSP_DRV_ID_MMC == devDrvId))
    {
        if ((BSP_DRV_ID_UART != devDrvId) &&
            (BSP_DRV_ID_MCSPI != devDrvId) &&
            (BSP_DRV_ID_MMC != devDrvId))
        {
        #if defined(SOC_TDA2PX)
            i2cInst   = BSP_DEVICE_I2C_INST_ID_0;
#if !defined (BSP_DISABLE_I2C0)
            i2cInstValid = (UInt32) TRUE;
#else
            i2cInstValid = (UInt32) FALSE;
#endif
        #else
            i2cInst   = BSP_DEVICE_I2C_INST_ID_1;
#if !defined (BSP_DISABLE_I2C1)
            i2cInstValid = (UInt32) TRUE;
#else
            i2cInstValid = (UInt32) FALSE;
#endif
        #endif
            if(i2cInstValid == (UInt32) TRUE)
            {
                ioExpAddr = BOARD_IO_EXP_I2C_ADDR_6;
                numRegs   = 2U;
                retVal    = Bsp_deviceRawRead8(i2cInst, ioExpAddr, regValue,
                                            numRegs);
                if (FVID2_SOK != retVal)
                {
                    GT_0trace(BspBoardTrace, GT_ERR, "I2C read failed!!\r\n");
                }
                else
                {
                    /* Configure muxes */
                    if ((FVID2_VID_SENSOR_LI_OV1063X_DRV == devDrvId) &&
                        (BSP_DEVICE_LI_OV1063X_INST_ID_0 == instId))
                    {
                        regValueTemp =
                            ((UInt32) regValue[0U] &
                            ((UInt32) (~BOARD_PCF8575_CAM_FPD_MUX_S0)));
                        regValue[0U] = (UInt8) regValueTemp;
                    }
                    else
                    {
                        regValueTemp = ((UInt32) regValue[0U] |
                                        (BOARD_PCF8575_CAM_FPD_MUX_S0));
                        regValue[0U] = (UInt8) regValueTemp;
                    }
                    /* Configure muxes */
                    if (((FVID2_VID_SENSOR_MULDES_OV1063X_DRV == devDrvId) &&
                        (BSP_DEVICE_MULDES_OV1063X_INST_ID_2 == instId)) ||
                        ((FVID2_VID_SENSOR_GW4200_IMX290_DRV == devDrvId) &&
                        (BSP_DEVICE_MULDES_IMX290_INST_ID_2 == instId)))
                    {
                        regValueTemp =
                            ((UInt32) regValue[0U] &
                            ((UInt32) (~BOARD_PCF8575_VIN2_S0)));
                        regValue[0U] = (UInt8) regValueTemp;
                        regValueTemp =
                            ((UInt32) regValue[0U] |
                            (BOARD_PCF8575_CAM_FPD_MUX_S0));
                        regValue[0U] = (UInt8) regValueTemp;
                    }

#if defined (SOC_TDA2PX)
                    /* Configure muxes */
                    /* Required for multides cam3 and also for the video config
                    * software control. So configuring for all instances in this
                    * condition.
                    */
                    regValueTemp =
                        ((UInt32) regValue[1U] &
                        ((UInt32) (~BOARD_PCF8575_EXVIN2_S0)));
                    regValue[1U] = (UInt8) regValueTemp;
                    regValueTemp =
                        ((UInt32) regValue[1U] |
                        (BOARD_PCF8575_EXVIN2_S2));
                    regValue[1U] = (UInt8) regValueTemp;
#endif

                    /* Configure muxes */
                    if (((FVID2_VID_SENSOR_MULDES_OV1063X_DRV == devDrvId) &&
                        (BSP_DEVICE_MULDES_OV1063X_INST_ID_5 == instId)) ||
                        ((FVID2_VID_SENSOR_GW4200_IMX290_DRV == devDrvId) &&
                        (BSP_DEVICE_MULDES_IMX290_INST_ID_5 == instId)))
                    {
                        /* Set VIN6_SEL_S0 & CAM_FPD_MUX_S0 to 1 */
                        regValueTemp = ((UInt32) regValue[0U] |
                                        (BOARD_PCF8575_VIN6_SEL));
                        regValue[0U] = (UInt8) regValueTemp;
                        regValueTemp =
                            ((UInt32) regValue[0U] |
                            (BOARD_PCF8575_CAM_FPD_MUX_S0));
                        regValue[0U] = (UInt8) regValueTemp;
                    }

                    /* The GPIO4_13 to 16 which is controlling the video mux
                    * on vision board is muxed in the base board. This should be
                    * selected as well
                    */
                    regValueTemp =
                        ((UInt32) regValue[0U] &
                        ((UInt32) (~BOARD_PCF8575_VIN2_S0)));
                    regValue[0U] = (UInt8) regValueTemp;

                    retVal += Bsp_deviceRawWrite8(i2cInst, ioExpAddr,
                                                regValue, numRegs);
                    if (FVID2_SOK != retVal)
                    {
                        GT_0trace(BspBoardTrace, GT_ERR, "I2C write failed!!\r\n");
                    }
                }
            }
        }

        /* Configuring U57 IO Expander for VIN4B / UART1 / UART3 / SPI2 Input*/
        if (((FVID2_VID_SENSOR_MULDES_OV1063X_DRV == devDrvId) &&
             (BSP_DEVICE_MULDES_OV1063X_INST_ID_5 == instId)) ||
            ((FVID2_VID_SENSOR_GW4200_IMX290_DRV == devDrvId) &&
             (BSP_DEVICE_MULDES_IMX290_INST_ID_5 == instId)) ||
            (BSP_DRV_ID_UART == devDrvId) ||
            (BSP_DRV_ID_MCSPI == devDrvId) ||
            (BSP_DRV_ID_MMC == devDrvId))
        {
            i2cInst   = BSP_DEVICE_I2C_INST_ID_0;
#if !defined (BSP_DISABLE_I2C0)
            i2cInstValid = (UInt32) TRUE;
#else
            i2cInstValid = (UInt32) FALSE;
#endif
            if(i2cInstValid == (UInt32) TRUE)
            {
                ioExpAddr = BOARD_IO_EXP_I2C_ADDR_1;
                numRegs   = 2U;
                retVal    =
                    Bsp_deviceRawRead8(i2cInst, ioExpAddr, regValue, numRegs);
                if (FVID2_SOK != retVal)
                {
                    GT_0trace(BspBoardTrace, GT_ERR, "I2C read failed!!\r\n");
                }
                else
                {
                    if (((FVID2_VID_SENSOR_MULDES_OV1063X_DRV == devDrvId) &&
                        (BSP_DEVICE_MULDES_OV1063X_INST_ID_5 == instId)) ||
                        ((FVID2_VID_SENSOR_GW4200_IMX290_DRV == devDrvId) &&
                        (BSP_DEVICE_MULDES_IMX290_INST_ID_5 == instId)))
                    {
                        /*
                        * This selects VIN4B signals over RGMII0
                        * SEL_ENET_MUX_S0 to 0
                        */
                        regValueTemp =
                            ((UInt32) regValue[0U] &
                            ((UInt32) (~(BOARD_PCF8575_SEL_ENET_MUX_S0))));
                        regValue[0U] = (UInt8) regValueTemp;
                    }

                    if ((BSP_DRV_ID_UART == devDrvId) &&
                        (BSP_DEVICE_UART_INST_ID_0 == instId))
                    {
                        /*
                        * This selects UART1 signals over UART1
                        * UART_SEL1_3 to 0
                        */
                        regValueTemp =
                            ((UInt32) regValue[1U] &
                            ((UInt32) (~BOARD_PCF8575_UART_SEL1_3)));
                        regValue[1U] = (UInt8) regValueTemp;
                    }
                    if ((BSP_DRV_ID_UART == devDrvId) &&
                        (BSP_DEVICE_UART_INST_ID_2 == instId))
                    {
                        /*
                        * This selects UART3 signals over SPI2 and UART1
                        * SEL_UART3_SPI2 to 0
                        * UART_SEL1_3 to 1
                        */
                        regValueTemp =
                            ((UInt32) regValue[1U] &
                            ((UInt32) (~BOARD_PCF8575_SEL_UART3_SPI2)));
                        regValue[1U] = (UInt8) regValueTemp;
                        regValueTemp =
                            ((UInt32) regValue[1U] | (BOARD_PCF8575_UART_SEL1_3));
                        regValue[1U] = (UInt8) regValueTemp;
                    }
                    if ((BSP_DRV_ID_MCSPI == devDrvId) &&
                        (BSP_DEVICE_MCSPI_INST_ID_1 == instId))
                    {
                        /*
                        * This selects SPI2 signals over SPI2 and UART1
                        * SEL_UART3_SPI2 to 1
                        */
                        regValueTemp =
                            ((UInt32) regValue[1U] | (BOARD_PCF8575_SEL_UART3_SPI2));
                        regValue[1U] = (UInt8) regValueTemp;
                    }
                    if ((BSP_DRV_ID_MMC == devDrvId) &&
                        (BSP_DEVICE_MMC_INST_ID_2 == instId))
                    {
                        /*
                        * This selects SPI2 signals over SPI2 and UART1
                        * SEL_MMC2 to 0
                        */
                        regValueTemp =
                            ((UInt32) regValue[1U] & (~BOARD_PCF8575_MMC2));
                        regValue[1U] = (UInt8) regValueTemp;
                    }

                    retVal +=
                        Bsp_deviceRawWrite8(i2cInst, ioExpAddr, regValue, numRegs);
                    if (FVID2_SOK != retVal)
                    {
                        GT_0trace(BspBoardTrace, GT_ERR, "I2C write failed!!\r\n");
                    }
                }
            }
        }
    }

    return (retVal);
}

static Int32 Bsp_boardPowerOnDeviceTda2xx(UInt32 devDrvId,
                                          UInt32 instId,
                                          UInt32 powerOn)
{
    Int32  retVal = BSP_SOK;
    UInt8  regValue[2];
    UInt32 i2cInst, ioExpAddr, numRegs;
    const Bsp_BoardI2cData *i2cData;
    UInt32 regValueTemp;

    i2cData = Bsp_boardGetI2cData();
    GT_assert(BspBoardTrace, (i2cData != NULL));

    if (FVID2_LCD_CTRL_DRV == devDrvId)
    {
        if (0U == instId)
        {
            i2cInst   = BSP_DEVICE_I2C_INST_ID_0;
            ioExpAddr = BOARD_IO_EXP_I2C_ADDR_0;
            numRegs   = 2U;
            retVal    = Bsp_deviceRawRead8(i2cInst, ioExpAddr, regValue,
                                           numRegs);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(BspBoardTrace, GT_ERR, "I2C read failed!!\r\n");
            }
            else
            {
                /* Configure muxes to power on LCD */
                regValueTemp =
                    ((UInt32) regValue[1U] &
                     ((UInt32) ~(BOARD_PCF8575_LCDCTRL_POWER_MASK)));
                regValue[1U] = (UInt8) regValueTemp;

                retVal += Bsp_deviceRawWrite8(i2cInst, ioExpAddr, regValue,
                                              numRegs);
                if (FVID2_SOK != retVal)
                {
                    GT_0trace(BspBoardTrace, GT_ERR, "I2C write failed!!\r\n");
                }
            }
        }
#if defined (SOC_TDA2PX)
            GPIODirModeSet(
                BOARD_GPIO_BASE_LCD_PWDN,
                BOARD_GPIO_PIN_LCD_PWDN,
                GPIO_DIR_OUTPUT);
            GPIOPinWrite(
                BOARD_GPIO_BASE_LCD_PWDN,
                BOARD_GPIO_PIN_LCD_PWDN,
                GPIO_PIN_LOW);
            BspOsal_sleep((UInt32) 100U);
#endif
    }

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined (SOC_TDA2EX)
    if ((FVID2_VID_SENSOR_MULDES_OV1063X_DRV == devDrvId) ||
        (FVID2_VID_SENSOR_GW4200_IMX290_DRV == devDrvId) ||
        (FVID2_VID_SENSOR_OV1063X_DRV == devDrvId))
    {
        if (BSP_BOARD_MONSTERCAM == Bsp_boardGetId())
        {
            GPIODirModeSet(
                (UInt32) SOC_GPIO8_BASE,
                BOARD_GPIO_PIN_OV1063X_PWRON,
                GPIO_DIR_OUTPUT);
            GPIOPinWrite(
                SOC_GPIO8_BASE,
                BOARD_GPIO_PIN_OV1063X_PWRON,
                GPIO_PIN_HIGH);

            BspOsal_sleep((UInt32) 100U);
        }
    }
    if (FVID2_VID_SENSOR_OV1063X_DRV == devDrvId)
    {
        if (BSP_BOARD_MONSTERCAM != Bsp_boardGetId())
        {
            /*
             * OV_PWDN is controlled by GP6[17]. 0 is ON, 1 is OFF
             */
            if (powerOn == (UInt32) TRUE)
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
        }
    }
#endif

    if (FVID2_VID_SENSOR_APT_AR0132RCCC_DRV == devDrvId)
    {
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined (SOC_TDA2EX)
        /*
         * OV_PWDN is controlled by GP6[11]. 0 is OFF, 1 is ON
         */
        if (powerOn == (UInt32) TRUE)
        {
            GPIOPinWrite(
                BOARD_GPIO_BASE_POWER_DWN,
                BOARD_GPIO_PIN_AR0132RC,
                GPIO_PIN_HIGH);
        }
        else
        {
            GPIOPinWrite(
                BOARD_GPIO_BASE_POWER_DWN,
                BOARD_GPIO_PIN_AR0132RC,
                GPIO_PIN_LOW);
        }
#endif
    }

    if ((BSP_DRV_ID_MMC == devDrvId) && (BSP_DEVICE_MCSPI_INST_ID_1 == instId))
    {
        Bsp_boardTda2xxEnableMmc1();
    }
    return (retVal);
}

static Int32 Bsp_boardSelectDeviceTda2xxMultiDes(UInt32 devDrvId,
                                                 UInt32 instId)
{
    Int32 retVal = BSP_SOK;

    /* Select mux at Vision App Board level */
    retVal += Bsp_boardSelectDeviceTda2xxVision(devDrvId, instId);

    return retVal;
}

/* Vision card mux select */
static Int32 Bsp_boardSelectDeviceTda2xxVision(UInt32 devDrvId, UInt32 instId)
{
    Int32  retVal = BSP_SOK;
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || \
    defined (SOC_TDA2EX) || defined (SOC_TDA3XX)
    UInt32 delay;
#endif

    /* Select mux at base EVM level */
    retVal = Bsp_boardSelectDeviceTda2xx(devDrvId, instId);

    if (BSP_SOK == retVal)
    {
        if ((FVID2_VID_SENSOR_OV1063X_DRV == devDrvId) ||
            (FVID2_VID_SENSOR_LI_OV1063X_DRV == devDrvId) ||
            (FVID2_VID_SENSOR_MULDES_OV1063X_DRV == devDrvId) ||
            (FVID2_VID_SENSOR_GW4200_IMX290_DRV == devDrvId) ||
            (FVID2_VID_SENSOR_APT_AR0132_DRV == devDrvId) ||
            (FVID2_VID_DEC_SII9127_DRV == devDrvId) ||
            (FVID2_VID_DEC_ADV7611_DRV == devDrvId))
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
            /* Above is valid for TDA2xx EVM only, for TI81xx interposer board
             * this is controlled thorugh different set of pins */
#if defined (TI814X_BUILD) || defined (TI8149_BUILD) || defined (TI811X_BUILD)
            {
                /* TODO */
            }
#else
            {
/* GPIO6 is not defined for TI81xx, hence putting under #ifdef to avoid compile
 * error */
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined (SOC_TDA2EX)
                /* By default set to 8-bit mode for all ports by setting
                 * Demux_FPD_A,B,C to (1,0,1) except Aptina sensor.
                 * We use 12-bit mode for Aptina: Demux_FPD_A,B,C to (1,1,1) */
                GPIOPinWrite(
                    BOARD_GPIO_BASE_DEMUX_FPD_A,
                    BOARD_GPIO_PIN_DEMUX_FPD_A,
                    GPIO_PIN_HIGH);
                if (FVID2_VID_SENSOR_APT_AR0132_DRV == devDrvId)
                {
                    GPIOPinWrite(
                        BOARD_GPIO_BASE_DEMUX_FPD_B,
                        BOARD_GPIO_PIN_DEMUX_FPD_B,
                        GPIO_PIN_HIGH);
                }
                else
                {
                    GPIOPinWrite(
                        BOARD_GPIO_BASE_DEMUX_FPD_B,
                        BOARD_GPIO_PIN_DEMUX_FPD_B,
                        GPIO_PIN_LOW);
                }
                GPIOPinWrite(
                    BOARD_GPIO_BASE_DEMUX_FPD_C,
                    BOARD_GPIO_PIN_DEMUX_FPD_C,
                    GPIO_PIN_HIGH);
#endif

                /* For CAM1/3 FPD Linx */
                if ((FVID2_VID_SENSOR_MULDES_OV1063X_DRV == devDrvId) ||
                    (FVID2_VID_SENSOR_GW4200_IMX290_DRV == devDrvId))
                {
                    GPIOPinWrite(
                        BOARD_GPIO_BASE_MUX_SEL,
                        BOARD_GPIO_PIN_MUX1_SEL0,
                        GPIO_PIN_LOW);
                    GPIOPinWrite(
                        BOARD_GPIO_BASE_MUX_SEL,
                        BOARD_GPIO_PIN_MUX1_SEL1,
                        GPIO_PIN_LOW);
                    GPIOPinWrite(
                        BOARD_GPIO_BASE_MUX_SEL,
                        BOARD_GPIO_PIN_MUX2_SEL0,
                        GPIO_PIN_LOW);
                    GPIOPinWrite(
                        BOARD_GPIO_BASE_MUX_SEL,
                        BOARD_GPIO_PIN_MUX2_SEL1,
                        GPIO_PIN_HIGH);
                }
                else if (FVID2_VID_SENSOR_OV1063X_DRV == devDrvId)
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
                else if ((FVID2_VID_DEC_SII9127_DRV == devDrvId) ||
                         (FVID2_VID_DEC_ADV7611_DRV == devDrvId))
                {
                    GPIOPinWrite(
                        BOARD_GPIO_BASE_MUX_SEL,
                        BOARD_GPIO_PIN_MUX1_SEL0,
                        GPIO_PIN_LOW);
                    GPIOPinWrite(
                        BOARD_GPIO_BASE_MUX_SEL,
                        BOARD_GPIO_PIN_MUX1_SEL1,
                        GPIO_PIN_LOW);
                    GPIOPinWrite(
                        BOARD_GPIO_BASE_MUX_SEL,
                        BOARD_GPIO_PIN_MUX2_SEL0,
                        GPIO_PIN_LOW);
                    GPIOPinWrite(
                        BOARD_GPIO_BASE_MUX_SEL,
                        BOARD_GPIO_PIN_MUX2_SEL1,
                        GPIO_PIN_LOW);
                }
                else if (FVID2_VID_SENSOR_LI_OV1063X_DRV == devDrvId)
                {
                    GPIOPinWrite(
                        BOARD_GPIO_BASE_MUX_SEL,
                        BOARD_GPIO_PIN_MUX1_SEL0,
                        GPIO_PIN_LOW);
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
                else if (FVID2_VID_SENSOR_APT_AR0132_DRV == devDrvId)
                {
                    /* Assert reset - CPLD will assert reset when already
                     * selected Aptina sensor is deselected - we select HDMI
                     * temporarily!! */
                    GPIOPinWrite(
                        BOARD_GPIO_BASE_MUX_SEL,
                        BOARD_GPIO_PIN_MUX1_SEL0,
                        GPIO_PIN_LOW);
                    GPIOPinWrite(
                        BOARD_GPIO_BASE_MUX_SEL,
                        BOARD_GPIO_PIN_MUX1_SEL1,
                        GPIO_PIN_LOW);
                    GPIOPinWrite(
                        BOARD_GPIO_BASE_MUX_SEL,
                        BOARD_GPIO_PIN_MUX2_SEL0,
                        GPIO_PIN_LOW);
                    GPIOPinWrite(
                        BOARD_GPIO_BASE_MUX_SEL,
                        BOARD_GPIO_PIN_MUX2_SEL1,
                        GPIO_PIN_LOW);
                    /* As per spec this is 1ms */
                    delay = 5U;
                    BspOsal_sleep(delay);

                    /* Select Aptina */
                    GPIOPinWrite(
                        BOARD_GPIO_BASE_MUX_SEL,
                        BOARD_GPIO_PIN_MUX1_SEL0,
                        GPIO_PIN_LOW);
                    GPIOPinWrite(
                        BOARD_GPIO_BASE_MUX_SEL,
                        BOARD_GPIO_PIN_MUX1_SEL1,
                        GPIO_PIN_HIGH);
                    GPIOPinWrite(
                        BOARD_GPIO_BASE_MUX_SEL,
                        BOARD_GPIO_PIN_MUX2_SEL0,
                        GPIO_PIN_HIGH);
                    GPIOPinWrite(
                        BOARD_GPIO_BASE_MUX_SEL,
                        BOARD_GPIO_PIN_MUX2_SEL1,
                        GPIO_PIN_LOW);

                    /* This also brings the sensor out of reset.
                     * Need below delay for reset to complete.
                     * As per spec this is 35ms + 1 ms */
                    delay = 50U;
                    BspOsal_sleep(delay);
                }
                else
                {
                    /* Do Nothing */
                }
            }
#endif
        }
    }

    return (retVal);
}

static Int32 Bsp_boardSelectDeviceTda2xxMonsterCam(UInt32 devDrvId,
                                                   UInt32 instId)
{
    Int32  retVal = BSP_SOK;
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined (SOC_TDA2EX)
    UInt32 delay;

    GPIOPinWrite(
        SOC_GPIO5_BASE,
        BOARD_GPIO_PIN_AR0132RC_INST1_S1,
        GPIO_PIN_HIGH);
    GPIOPinWrite(
        SOC_GPIO1_BASE,
        BOARD_GPIO_PIN_AR0132RC_INST0_S1,
        GPIO_PIN_HIGH);
    GPIOPinWrite(
        SOC_GPIO6_BASE,
        BOARD_GPIO_PIN_AR0132RC_INST0_S0,
        GPIO_PIN_HIGH);
    GPIOPinWrite(
        SOC_GPIO5_BASE,
        BOARD_GPIO_PIN_AR0132RC_INST1_S0,
        GPIO_PIN_HIGH);

    /* This also brings the sensor out of reset.
     * Need below delay for reset to complete.
     * As per spec this is 35ms + 1 ms */
    delay = 50U;
    BspOsal_sleep(delay);

    if (FVID2_VID_SENSOR_OV1063X_DRV == devDrvId)
    {
        GPIODirModeSet(
            (UInt32) SOC_GPIO8_BASE,
            BOARD_GPIO_PIN_OV1063X_MAIN_IMAGER,
            GPIO_DIR_OUTPUT);
        GPIOPinWrite(
            SOC_GPIO8_BASE,
            BOARD_GPIO_PIN_OV1063X_MAIN_IMAGER,
            GPIO_PIN_HIGH);
    }
    else if ((FVID2_VID_SENSOR_MULDES_OV1063X_DRV == devDrvId) ||
             (FVID2_VID_SENSOR_GW4200_IMX290_DRV == devDrvId))
    {
        GPIODirModeSet(
            (UInt32) SOC_GPIO8_BASE,
            BOARD_GPIO_PIN_OV1063X_MAIN_IMAGER,
            GPIO_DIR_OUTPUT);
        GPIOPinWrite(
            SOC_GPIO8_BASE,
            BOARD_GPIO_PIN_OV1063X_MAIN_IMAGER,
            GPIO_PIN_LOW);
    }
    else /* Need additional else-if condition when FPD camera is added */
    {
        GPIODirModeSet(
            (UInt32) SOC_GPIO8_BASE,
            BOARD_GPIO_PIN_OV1063X_MAIN_IMAGER,
            GPIO_DIR_INPUT);
    }
#endif

    return (retVal);
}

/* JAMR3 card mux select */
static Int32 Bsp_boardSelectDeviceTda2xxJamr3(UInt32 devDrvId, UInt32 instId)
{
    Int32  retVal = BSP_SOK;
    UInt8  regValue[2];
    UInt32 i2cInst, ioExpAddr, numRegs;
    UInt32 regValueTemp;

    /* Select mux at base EVM level */
    retVal = Bsp_boardSelectDeviceTda2xx(devDrvId, instId);

    if (BSP_SOK == retVal)
    {
        if (FVID2_VID_DEC_TVP5158_DRV == devDrvId)
        {
            i2cInst   = BSP_DEVICE_I2C_INST_ID_3;
            ioExpAddr = BOARD_IO_EXP_I2C_ADDR_1;
            numRegs   = 2U;
            retVal    = Bsp_deviceRawRead8(i2cInst, ioExpAddr, regValue,
                                           numRegs);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(BspBoardTrace, GT_ERR, "I2C read failed!!\r\n");
            }
            else
            {
                /* Configure muxes */
                regValueTemp =
                    ((UInt32) regValue[1U] &
                     ((UInt32) (~BOARD_PCF8575_SEL_TVP_FPD)));
                regValue[1U] = (UInt8) regValueTemp;
                retVal      +=
                    Bsp_deviceRawWrite8(i2cInst, ioExpAddr, regValue, numRegs);
                if (FVID2_SOK != retVal)
                {
                    GT_0trace(BspBoardTrace, GT_ERR, "I2C write failed!!\r\n");
                }
            }
        }
    }

    return (retVal);
}

Int32 Bsp_boardSetPinMuxTda2xx(
    UInt32        drvId,
    UInt32        instId,
    Bsp_BoardMode boardMode)
{
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined (SOC_TDA2EX)
    if (BSP_DRV_ID_UART == drvId)
    {
        if (BSP_DEVICE_UART_INST_ID_0 == instId)
        {
            /* boardMode is ignored as of now */
            /* UART1 mux */
            Bsp_platformSetPinmuxRegs((UInt32) 0,
                                      (UInt32) CTRL_CORE_PAD_UART1_RXD,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0,
                                      (UInt32) CTRL_CORE_PAD_UART1_TXD,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0,
                                      (UInt32) CTRL_CORE_PAD_UART1_CTSN,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0,
                                      (UInt32) CTRL_CORE_PAD_UART1_RTSN,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        }
        else if (BSP_DEVICE_UART_INST_ID_2 == instId)
        {
            /* boardMode is ignored as of now */
            Bsp_platformSetPinmuxRegs((UInt32) 1,
                                      (UInt32) CTRL_CORE_PAD_SPI2_SCLK,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 1,
                                      (UInt32) CTRL_CORE_PAD_SPI2_D1,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        }
        else if (BSP_DEVICE_UART_INST_ID_9 == instId)
        {
            /* boardMode is ignored as of now */
            /* UART10 mux
             * PAD=gpio6_14, PIN=uart10_rxd
             * PAD=gpio6_15, PIN=uart10_txd */
            Bsp_platformSetPinmuxRegs((UInt32) 3,
                                      (UInt32) CTRL_CORE_PAD_GPIO6_14,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 3,
                                      (UInt32) CTRL_CORE_PAD_GPIO6_15,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        }
        else
        {
            /* Dummy else */
        }
    }

    if (BSP_DRV_ID_I2C == drvId)
    {
        if (BSP_DEVICE_I2C_INST_ID_0 == instId)
        {
            /* boardMode is ignored as of now */
            /* I2C mux */
            Bsp_platformSetPinmuxRegs((UInt32) 0,
                                      (UInt32) CTRL_CORE_PAD_I2C1_SDA,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0,
                                      (UInt32) CTRL_CORE_PAD_I2C1_SCL,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        }
        else if (BSP_DEVICE_I2C_INST_ID_1 == instId)
        {
            /* boardMode is ignored as of now */
            /* I2C2 mux */
            Bsp_platformSetPinmuxRegs((UInt32) 0,
                                      (UInt32) CTRL_CORE_PAD_I2C2_SDA,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0,
                                      (UInt32) CTRL_CORE_PAD_I2C2_SCL,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        }
        else if (BSP_DEVICE_I2C_INST_ID_3 == instId)
        {
            /* boardMode is ignored as of now */
            /* I2C4 mux */
            Bsp_platformSetPinmuxRegs((UInt32) 4,
                                      (UInt32) CTRL_CORE_PAD_MCASP4_ACLKX,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 4,
                                      (UInt32) CTRL_CORE_PAD_MCASP4_FSX,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        }
        else if (BSP_DEVICE_I2C_INST_ID_4 == instId)
        {
            /* boardMode is ignored as of now */
            /* I2C5 mux */
            Bsp_platformSetPinmuxRegs((UInt32) 10,
                                      (UInt32) CTRL_CORE_PAD_MCASP1_AXR0,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 10,
                                      (UInt32) CTRL_CORE_PAD_MCASP1_AXR1,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        }
        else
        {
            /* Dummy else */
        }
    }

    if (BSP_DRV_ID_MCSPI == drvId)
    {
        if (BSP_DEVICE_MCSPI_INST_ID_0 == instId)
        {
            /* boardMode is ignored as of now */
            /* SPI1 mux */
            Bsp_platformSetPinmuxRegs((UInt32) 0,
                                      (UInt32) CTRL_CORE_PAD_SPI1_SCLK,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0,
                                      (UInt32) CTRL_CORE_PAD_SPI1_D1,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0,
                                      (UInt32) CTRL_CORE_PAD_SPI1_D0,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0,
                                      (UInt32) CTRL_CORE_PAD_SPI1_CS0,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0,
                                      (UInt32) CTRL_CORE_PAD_SPI1_CS1,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        }
        else if (BSP_DEVICE_MCSPI_INST_ID_1 == instId)
        {
            /* boardMode is ignored as of now */
            /* SPI2 mux */
            Bsp_platformSetPinmuxRegs((UInt32) 0,
                                      (UInt32) CTRL_CORE_PAD_SPI2_SCLK,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0,
                                      (UInt32) CTRL_CORE_PAD_SPI2_D1,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0,
                                      (UInt32) CTRL_CORE_PAD_SPI2_D0,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0,
                                      (UInt32) CTRL_CORE_PAD_SPI2_CS0,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        }
        else if (BSP_DEVICE_MCSPI_INST_ID_2 == instId)
        {
            /* boardMode is ignored as of now */
            /* SPI3 mux
             * PAD=uart3_rxd, PIN=spi3_clk
             * PAD=uart3_txd, PIN=spi3_d(1)
             * PAD=rgmii0_txc, PIN=spi3_d(0)
             * PAD=rgmii0_txctl, PIN=spi3_cs(0) */
            Bsp_platformSetPinmuxRegs((UInt32) 7,
                                      (UInt32) CTRL_CORE_PAD_UART3_RXD,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 7,
                                      (UInt32) CTRL_CORE_PAD_UART3_TXD,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 7,
                                      (UInt32) CTRL_CORE_PAD_RGMII0_TXC,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 7,
                                      (UInt32) CTRL_CORE_PAD_RGMII0_TXCTL,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        }
        else if (BSP_DEVICE_MCSPI_INST_ID_3 == instId)
        {
            /* boardMode is ignored as of now */
            /* SPI4 mux
             * PAD=gpmc_a[8], PIN=spi4_clk
             * PAD=gpmc_a[9], PIN=spi4_d(1)
             * PAD=gpmc_a[10], PIN=spi4_d(0)
             * PAD=gpmc_a[11], PIN=spi4_cs(0) */
            Bsp_platformSetPinmuxRegs((UInt32) 8,
                                      (UInt32) CTRL_CORE_PAD_GPMC_A8,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 8,
                                      (UInt32) CTRL_CORE_PAD_GPMC_A9,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 8,
                                      (UInt32) CTRL_CORE_PAD_GPMC_A10,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 8,
                                      (UInt32) CTRL_CORE_PAD_GPMC_A11,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        }
        else
        {
            /* Dummy else */
        }
    }

    if (BSP_DRV_ID_MCASP == drvId)
    {
        if (BSP_DEVICE_MCASP_INST_ID_2 == instId)
        {
            /* boardMode is ignored as of now */
            /* McASP3 mux */
            /* PAD=xref_clk2,PIN=mcasp3_ahclkx */
            Bsp_platformSetPinmuxRegs((UInt32) 3,
                                      (UInt32) CTRL_CORE_PAD_XREF_CLK2,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            Bsp_platformSetPinmuxRegs((UInt32) 0,
                                      (UInt32) CTRL_CORE_PAD_MCASP3_ACLKX,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            Bsp_platformSetPinmuxRegs((UInt32) 0,
                                      (UInt32) CTRL_CORE_PAD_MCASP3_FSX,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            Bsp_platformSetPinmuxRegs((UInt32) 0,
                                      (UInt32) CTRL_CORE_PAD_MCASP3_AXR0,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            Bsp_platformSetPinmuxRegs((UInt32) 0,
                                      (UInt32) CTRL_CORE_PAD_MCASP3_AXR1,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
        }
        else if (BSP_DEVICE_MCASP_INST_ID_5 == instId)
        {
            /* boardMode is ignored as of now */
            /* McASP6 mux (JAMR3) */
            /* PAD = mcasp1_axr[8], PIN = MCASP6_AXR0 */
            Bsp_platformSetPinmuxRegs((UInt32) 1,
                                      (UInt32) CTRL_CORE_PAD_MCASP1_AXR8,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            /* PAD = mcasp1_axr[9], PIN = MCASP6_AXR1 */
            Bsp_platformSetPinmuxRegs((UInt32) 1,
                                      (UInt32) CTRL_CORE_PAD_MCASP1_AXR9,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            /* PAD = mcasp1_axr[10], PIN = MCASP6_ACLKX */
            Bsp_platformSetPinmuxRegs((UInt32) 1,
                                      (UInt32) CTRL_CORE_PAD_MCASP1_AXR10,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            /* PAD = mcasp1_axr[11], PIN = MCASP6_AFSX */
            Bsp_platformSetPinmuxRegs((UInt32) 1,
                                      (UInt32) CTRL_CORE_PAD_MCASP1_AXR11,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            /* PAD = XREF_CLK1, PIN = MCASP6_AHCLKX */
            Bsp_platformSetPinmuxRegs((UInt32) 4,
                                      (UInt32) CTRL_CORE_PAD_XREF_CLK1,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
        }
        else
        {
            /* Dummy else */
        }
    }
    if (BSP_DRV_ID_MMC == drvId)
    {
        if (BSP_DEVICE_MMC_INST_ID_1 == instId)
        {
            Bsp_platformSetPinmuxRegs((UInt32) 0,
                                      (UInt32) CTRL_CORE_PAD_MMC1_CLK,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0,
                                      (UInt32) CTRL_CORE_PAD_MMC1_CMD,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0,
                                      (UInt32) CTRL_CORE_PAD_MMC1_DAT0,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0,
                                      (UInt32) CTRL_CORE_PAD_MMC1_DAT1,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0,
                                      (UInt32) CTRL_CORE_PAD_MMC1_DAT2,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0,
                                      (UInt32) CTRL_CORE_PAD_MMC1_DAT3,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        }
    }
#ifdef VPS_DSS_BUILD
    if ((FVID2_VPS_DCTRL_DRV == drvId) && (VPS_DSS_DISPC_OVLY_DPI1 == instId))
    {
        Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_VOUT1_CLK,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_VOUT1_DE,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_VOUT1_FLD,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0,
                                  (UInt32) CTRL_CORE_PAD_VOUT1_HSYNC,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0,
                                  (UInt32) CTRL_CORE_PAD_VOUT1_VSYNC,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_VOUT1_D0,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_VOUT1_D1,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_VOUT1_D2,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_VOUT1_D3,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_VOUT1_D4,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_VOUT1_D5,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_VOUT1_D6,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_VOUT1_D7,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_VOUT1_D8,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_VOUT1_D9,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_VOUT1_D10,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_VOUT1_D11,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_VOUT1_D12,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_VOUT1_D13,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_VOUT1_D14,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_VOUT1_D15,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_VOUT1_D16,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_VOUT1_D17,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_VOUT1_D18,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_VOUT1_D19,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_VOUT1_D20,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_VOUT1_D21,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_VOUT1_D22,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_VOUT1_D23,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    }
#endif

#ifdef VPS_VIP_BUILD
    /*
     *   In Multi des board the connections are as shown below
     *   CAM1 ---> VIN1A
     *   CAM2 ---> VIN2A
     *   CAM3 ---> VIN3A
     *   CAM4 ---> VIN5A
     *   CAM5 ---> VIN4B
     *   CAM6 ---> VIN6A
     */
    if (FVID2_VPS_CAPT_VID_DRV == drvId)
    {
        if ((VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA) ==
             instId))
        {
            Bsp_platformSetPinmuxRegs((UInt32) 0,
                                      (UInt32) CTRL_CORE_PAD_VIN1A_CLK0,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0,
                                      (UInt32) CTRL_CORE_PAD_VIN1A_DE0,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
#if defined (SOC_TDA2PX)
            /* Donot do pin mux for FLD0 for J6 Plus. As this is used as GPIO
             * Pin to control the LCD power on/off.
             */
#else
            Bsp_platformSetPinmuxRegs((UInt32) 0,
                                      (UInt32) CTRL_CORE_PAD_VIN1A_FLD0,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
#endif
            Bsp_platformSetPinmuxRegs((UInt32) 0,
                                      (UInt32) CTRL_CORE_PAD_VIN1A_HSYNC0,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0,
                                      (UInt32) CTRL_CORE_PAD_VIN1A_VSYNC0,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);

            if ((BSP_BOARD_MODE_VIDEO_BT1120 == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_BT656 == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_8BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_10BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_12BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_14BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_16BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_24BIT == boardMode))
            {
                Bsp_platformSetPinmuxRegs((UInt32) 0,
                                          (UInt32) CTRL_CORE_PAD_VIN1A_D0,
                                          BSP_PLATFORM_IOPAD_CFG_DEFAULT);
                Bsp_platformSetPinmuxRegs((UInt32) 0,
                                          (UInt32) CTRL_CORE_PAD_VIN1A_D1,
                                          BSP_PLATFORM_IOPAD_CFG_DEFAULT);
                Bsp_platformSetPinmuxRegs((UInt32) 0,
                                          (UInt32) CTRL_CORE_PAD_VIN1A_D2,
                                          BSP_PLATFORM_IOPAD_CFG_DEFAULT);
                Bsp_platformSetPinmuxRegs((UInt32) 0,
                                          (UInt32) CTRL_CORE_PAD_VIN1A_D3,
                                          BSP_PLATFORM_IOPAD_CFG_DEFAULT);
                Bsp_platformSetPinmuxRegs((UInt32) 0,
                                          (UInt32) CTRL_CORE_PAD_VIN1A_D4,
                                          BSP_PLATFORM_IOPAD_CFG_DEFAULT);
                Bsp_platformSetPinmuxRegs((UInt32) 0,
                                          (UInt32) CTRL_CORE_PAD_VIN1A_D5,
                                          BSP_PLATFORM_IOPAD_CFG_DEFAULT);
                Bsp_platformSetPinmuxRegs((UInt32) 0,
                                          (UInt32) CTRL_CORE_PAD_VIN1A_D6,
                                          BSP_PLATFORM_IOPAD_CFG_DEFAULT);
                Bsp_platformSetPinmuxRegs((UInt32) 0,
                                          (UInt32) CTRL_CORE_PAD_VIN1A_D7,
                                          BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            }

            if ((BSP_BOARD_MODE_VIDEO_BT1120 == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_10BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_12BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_14BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_16BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_24BIT == boardMode))
            {
                Bsp_platformSetPinmuxRegs((UInt32) 0,
                                          (UInt32) CTRL_CORE_PAD_VIN1A_D8,
                                          BSP_PLATFORM_IOPAD_CFG_DEFAULT);
                Bsp_platformSetPinmuxRegs((UInt32) 0,
                                          (UInt32) CTRL_CORE_PAD_VIN1A_D9,
                                          BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            }
            if ((BSP_BOARD_MODE_VIDEO_BT1120 == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_12BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_14BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_16BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_24BIT == boardMode))
            {
                Bsp_platformSetPinmuxRegs((UInt32) 0,
                                          (UInt32) CTRL_CORE_PAD_VIN1A_D10,
                                          BSP_PLATFORM_IOPAD_CFG_DEFAULT);
                Bsp_platformSetPinmuxRegs((UInt32) 0,
                                          (UInt32) CTRL_CORE_PAD_VIN1A_D11,
                                          BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            }
            if ((BSP_BOARD_MODE_VIDEO_BT1120 == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_14BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_16BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_24BIT == boardMode))
            {
                Bsp_platformSetPinmuxRegs((UInt32) 0,
                                          (UInt32) CTRL_CORE_PAD_VIN1A_D12,
                                          BSP_PLATFORM_IOPAD_CFG_DEFAULT);
                Bsp_platformSetPinmuxRegs((UInt32) 0,
                                          (UInt32) CTRL_CORE_PAD_VIN1A_D13,
                                          BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            }
            if ((BSP_BOARD_MODE_VIDEO_BT1120 == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_16BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_24BIT == boardMode))
            {
                Bsp_platformSetPinmuxRegs((UInt32) 0,
                                          (UInt32) CTRL_CORE_PAD_VIN1A_D14,
                                          BSP_PLATFORM_IOPAD_CFG_DEFAULT);
                Bsp_platformSetPinmuxRegs((UInt32) 0,
                                          (UInt32) CTRL_CORE_PAD_VIN1A_D15,
                                          BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            }
            if (BSP_BOARD_MODE_VIDEO_24BIT == boardMode)
            {
                Bsp_platformSetPinmuxRegs((UInt32) 0,
                                          (UInt32) CTRL_CORE_PAD_VIN1A_D16,
                                          BSP_PLATFORM_IOPAD_CFG_DEFAULT);
                Bsp_platformSetPinmuxRegs((UInt32) 0,
                                          (UInt32) CTRL_CORE_PAD_VIN1A_D17,
                                          BSP_PLATFORM_IOPAD_CFG_DEFAULT);
                Bsp_platformSetPinmuxRegs((UInt32) 0,
                                          (UInt32) CTRL_CORE_PAD_VIN1A_D18,
                                          BSP_PLATFORM_IOPAD_CFG_DEFAULT);
                Bsp_platformSetPinmuxRegs((UInt32) 0,
                                          (UInt32) CTRL_CORE_PAD_VIN1A_D19,
                                          BSP_PLATFORM_IOPAD_CFG_DEFAULT);
                Bsp_platformSetPinmuxRegs((UInt32) 0,
                                          (UInt32) CTRL_CORE_PAD_VIN1A_D20,
                                          BSP_PLATFORM_IOPAD_CFG_DEFAULT);
                Bsp_platformSetPinmuxRegs((UInt32) 0,
                                          (UInt32) CTRL_CORE_PAD_VIN1A_D21,
                                          BSP_PLATFORM_IOPAD_CFG_DEFAULT);
                Bsp_platformSetPinmuxRegs((UInt32) 0,
                                          (UInt32) CTRL_CORE_PAD_VIN1A_D22,
                                          BSP_PLATFORM_IOPAD_CFG_DEFAULT);
                Bsp_platformSetPinmuxRegs((UInt32) 0,
                                          (UInt32) CTRL_CORE_PAD_VIN1A_D23,
                                          BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            }
        }
        else if ((VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1,
                                            VPS_VIP_PORTA) == instId))
        {
            Bsp_platformSetPinmuxRegs((UInt32) 0,
                                      (UInt32) CTRL_CORE_PAD_VIN2A_CLK0,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0,
                                      (UInt32) CTRL_CORE_PAD_VIN2A_DE0,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0,
                                      (UInt32) CTRL_CORE_PAD_VIN2A_FLD0,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0,
                                      (UInt32) CTRL_CORE_PAD_VIN2A_HSYNC0,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0,
                                      (UInt32) CTRL_CORE_PAD_VIN2A_VSYNC0,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            if ((BSP_BOARD_MODE_VIDEO_BT1120 == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_BT656 == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_8BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_10BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_12BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_14BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_16BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_24BIT == boardMode))
            {
                Bsp_platformSetPinmuxRegs((UInt32) 0,
                                          (UInt32) CTRL_CORE_PAD_VIN2A_D0,
                                          BSP_PLATFORM_IOPAD_CFG_DEFAULT);
                Bsp_platformSetPinmuxRegs((UInt32) 0,
                                          (UInt32) CTRL_CORE_PAD_VIN2A_D1,
                                          BSP_PLATFORM_IOPAD_CFG_DEFAULT);
                Bsp_platformSetPinmuxRegs((UInt32) 0,
                                          (UInt32) CTRL_CORE_PAD_VIN2A_D2,
                                          BSP_PLATFORM_IOPAD_CFG_DEFAULT);
                Bsp_platformSetPinmuxRegs((UInt32) 0,
                                          (UInt32) CTRL_CORE_PAD_VIN2A_D3,
                                          BSP_PLATFORM_IOPAD_CFG_DEFAULT);
                Bsp_platformSetPinmuxRegs((UInt32) 0,
                                          (UInt32) CTRL_CORE_PAD_VIN2A_D4,
                                          BSP_PLATFORM_IOPAD_CFG_DEFAULT);
                Bsp_platformSetPinmuxRegs((UInt32) 0,
                                          (UInt32) CTRL_CORE_PAD_VIN2A_D5,
                                          BSP_PLATFORM_IOPAD_CFG_DEFAULT);
                Bsp_platformSetPinmuxRegs((UInt32) 0,
                                          (UInt32) CTRL_CORE_PAD_VIN2A_D6,
                                          BSP_PLATFORM_IOPAD_CFG_DEFAULT);
                Bsp_platformSetPinmuxRegs((UInt32) 0,
                                          (UInt32) CTRL_CORE_PAD_VIN2A_D7,
                                          BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            }

            if ((BSP_BOARD_MODE_VIDEO_BT1120 == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_10BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_12BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_14BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_16BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_24BIT == boardMode))
            {
                Bsp_platformSetPinmuxRegs((UInt32) 0,
                                          (UInt32) CTRL_CORE_PAD_VIN2A_D8,
                                          BSP_PLATFORM_IOPAD_CFG_DEFAULT);
                Bsp_platformSetPinmuxRegs((UInt32) 0,
                                          (UInt32) CTRL_CORE_PAD_VIN2A_D9,
                                          BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            }
            if ((BSP_BOARD_MODE_VIDEO_BT1120 == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_12BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_14BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_16BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_24BIT == boardMode))
            {
                Bsp_platformSetPinmuxRegs((UInt32) 0,
                                          (UInt32) CTRL_CORE_PAD_VIN2A_D10,
                                          BSP_PLATFORM_IOPAD_CFG_DEFAULT);
                Bsp_platformSetPinmuxRegs((UInt32) 0,
                                          (UInt32) CTRL_CORE_PAD_VIN2A_D11,
                                          BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            }
            if ((BSP_BOARD_MODE_VIDEO_BT1120 == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_14BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_16BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_24BIT == boardMode))
            {
                Bsp_platformSetPinmuxRegs((UInt32) 0,
                                          (UInt32) CTRL_CORE_PAD_VIN2A_D12,
                                          BSP_PLATFORM_IOPAD_CFG_DEFAULT);
                Bsp_platformSetPinmuxRegs((UInt32) 0,
                                          (UInt32) CTRL_CORE_PAD_VIN2A_D13,
                                          BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            }
            if ((BSP_BOARD_MODE_VIDEO_BT1120 == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_16BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_24BIT == boardMode))
            {
                Bsp_platformSetPinmuxRegs((UInt32) 0,
                                          (UInt32) CTRL_CORE_PAD_VIN2A_D14,
                                          BSP_PLATFORM_IOPAD_CFG_DEFAULT);
                Bsp_platformSetPinmuxRegs((UInt32) 0,
                                          (UInt32) CTRL_CORE_PAD_VIN2A_D15,
                                          BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            }
            if (BSP_BOARD_MODE_VIDEO_24BIT == boardMode)
            {
                Bsp_platformSetPinmuxRegs((UInt32) 0,
                                          (UInt32) CTRL_CORE_PAD_VIN2A_D16,
                                          BSP_PLATFORM_IOPAD_CFG_DEFAULT);
                Bsp_platformSetPinmuxRegs((UInt32) 0,
                                          (UInt32) CTRL_CORE_PAD_VIN2A_D17,
                                          BSP_PLATFORM_IOPAD_CFG_DEFAULT);
                Bsp_platformSetPinmuxRegs((UInt32) 0,
                                          (UInt32) CTRL_CORE_PAD_VIN2A_D18,
                                          BSP_PLATFORM_IOPAD_CFG_DEFAULT);
                Bsp_platformSetPinmuxRegs((UInt32) 0,
                                          (UInt32) CTRL_CORE_PAD_VIN2A_D19,
                                          BSP_PLATFORM_IOPAD_CFG_DEFAULT);
                Bsp_platformSetPinmuxRegs((UInt32) 0,
                                          (UInt32) CTRL_CORE_PAD_VIN2A_D20,
                                          BSP_PLATFORM_IOPAD_CFG_DEFAULT);
                Bsp_platformSetPinmuxRegs((UInt32) 0,
                                          (UInt32) CTRL_CORE_PAD_VIN2A_D21,
                                          BSP_PLATFORM_IOPAD_CFG_DEFAULT);
                Bsp_platformSetPinmuxRegs((UInt32) 0,
                                          (UInt32) CTRL_CORE_PAD_VIN2A_D22,
                                          BSP_PLATFORM_IOPAD_CFG_DEFAULT);
                Bsp_platformSetPinmuxRegs((UInt32) 0,
                                          (UInt32) CTRL_CORE_PAD_VIN2A_D23,
                                          BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            }
        }
#if defined (SOC_TDA2PX)
        else if ((VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1,
                                            VPS_VIP_PORTB) == instId))
        {
            /* VIN2-B pin mux */
            Bsp_platformSetPinmuxRegs((UInt32) 4U,
                                      (UInt32) CTRL_CORE_PAD_MMC3_DAT7,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=MMC3_DAT7_0,  PIN=VIN2B_CLK1_4 */
            Bsp_platformSetPinmuxRegs((UInt32) 4U,
                                      (UInt32) CTRL_CORE_PAD_GPIO6_10,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=GPIO6_10_0, PIN=VIN2B_HSYNC1_4 */
            Bsp_platformSetPinmuxRegs((UInt32) 4U,
                                      (UInt32) CTRL_CORE_PAD_GPIO6_11,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=GPIO6_11_0, PIN=VIN5A_VSYNC1_4 */
            Bsp_platformSetPinmuxRegs((UInt32) 4U,
                                      (UInt32) CTRL_CORE_PAD_MMC3_DAT0,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=MMC3_DAT0_0,  PIN=VIN2B_D5_4 */
            Bsp_platformSetPinmuxRegs((UInt32) 4U,
                                      (UInt32) CTRL_CORE_PAD_MMC3_DAT1,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=MMC3_DAT1_0,  PIN=VIN2B_D4_4 */
            Bsp_platformSetPinmuxRegs((UInt32) 4U,
                                      (UInt32) CTRL_CORE_PAD_MMC3_DAT2,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=MMC3_DAT2_0,  PIN=VIN2B_D3_4 */
            Bsp_platformSetPinmuxRegs((UInt32) 4U,
                                      (UInt32) CTRL_CORE_PAD_MMC3_DAT3,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=MMC3_DAT3_0,  PIN=VIN2B_D2_4 */
            Bsp_platformSetPinmuxRegs((UInt32) 4U,
                                      (UInt32) CTRL_CORE_PAD_MMC3_DAT4,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=MMC3_DAT4_0,  PIN=VIN2B_D1_4 */
            Bsp_platformSetPinmuxRegs((UInt32) 4U,
                                      (UInt32) CTRL_CORE_PAD_MMC3_DAT5,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=MMC3_DAT5_0,  PIN=VIN2B_D0_4 */
            Bsp_platformSetPinmuxRegs((UInt32) 4U,
                                      (UInt32) CTRL_CORE_PAD_MMC3_CMD,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=MMC3_CMD_0,   PIN=VIN2B_D6_4 */
            Bsp_platformSetPinmuxRegs((UInt32) 4U,
                                      (UInt32) CTRL_CORE_PAD_MMC3_CLK,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=MMC3_CLK_0,   PIN=VIN2B_D7_4 */
        }
#endif
        else if ((VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S0,
                                            VPS_VIP_PORTA) ==
                  instId))
        {
            /* VIN3-A pin mux */
            Bsp_platformSetPinmuxRegs((UInt32) 6U,
                                      (UInt32) CTRL_CORE_PAD_VIN1B_CLK1,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            /* PAD=VIN1B_CLK1_0, PIN=VIN3A_CLK0_6 */
            Bsp_platformSetPinmuxRegs((UInt32) 5U,
                                      (UInt32) CTRL_CORE_PAD_VIN2A_D22,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            /* PAD=VIN2A_D22_0,  PIN=VIN3A_HSYNC0_5 */
            Bsp_platformSetPinmuxRegs((UInt32) 5U,
                                      (UInt32) CTRL_CORE_PAD_VIN2A_D23,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            /* PAD=VIN2A_D23_0,  PIN=VIN3A_VSYNC0_5 */
            Bsp_platformSetPinmuxRegs((UInt32) 6U,
                                      (UInt32) CTRL_CORE_PAD_VIN1A_D16,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            /* PAD=VIN1A_D16_0,  PIN=VIN3A_D0_6 */
            Bsp_platformSetPinmuxRegs((UInt32) 6U,
                                      (UInt32) CTRL_CORE_PAD_VIN1A_D17,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            /* PAD=VIN1A_D17_0,  PIN=VIN3A_D1_6 */
            Bsp_platformSetPinmuxRegs((UInt32) 6U,
                                      (UInt32) CTRL_CORE_PAD_VIN1A_D18,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            /* PAD=VIN1A_D18_0,  PIN=VIN3A_D2_6 */
            Bsp_platformSetPinmuxRegs((UInt32) 6U,
                                      (UInt32) CTRL_CORE_PAD_VIN1A_D19,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            /* PAD=VIN1A_D19_0,  PIN=VIN3A_D3_6 */
            Bsp_platformSetPinmuxRegs((UInt32) 6U,
                                      (UInt32) CTRL_CORE_PAD_VIN1A_D20,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            /* PAD=VIN1A_D20_0,  PIN=VIN3A_D4_6 */
            Bsp_platformSetPinmuxRegs((UInt32) 6U,
                                      (UInt32) CTRL_CORE_PAD_VIN1A_D21,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            /* PAD=VIN1A_D21_0,  PIN=VIN3A_D5_6 */
            Bsp_platformSetPinmuxRegs((UInt32) 6U,
                                      (UInt32) CTRL_CORE_PAD_VIN1A_D22,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            /* PAD=VIN1A_D22_0,  PIN=VIN3A_D6_6 */
            Bsp_platformSetPinmuxRegs((UInt32) 6U,
                                      (UInt32) CTRL_CORE_PAD_VIN1A_D23,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            /* PAD=VIN1A_D23_0,  PIN=VIN3A_D7_6 */
        }
        else if ((VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S1,
                                            VPS_VIP_PORTB)) ==
                 instId)
        {
            /* VIN4-B pin mux */
            Bsp_platformSetPinmuxRegs((UInt32) 5U,
                                      (UInt32) CTRL_CORE_PAD_MDIO_MCLK,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            /* PAD=MDIO_MCLK_0,    PIN=VIN4B_CLK1_5   */
            Bsp_platformSetPinmuxRegs((UInt32) 5U,
                                      (UInt32) CTRL_CORE_PAD_RGMII0_TXD2,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            /* PAD=RGMII0_TXD2_0,  PIN=VIN4B_HSYNC1_5 */
            Bsp_platformSetPinmuxRegs((UInt32) 5U,
                                      (UInt32) CTRL_CORE_PAD_RGMII0_TXD1,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            /* PAD=RGMII0_TXD1_0,  PIN=VIN4B_VSYNC1_5 */
            Bsp_platformSetPinmuxRegs((UInt32) 5U,
                                      (UInt32) CTRL_CORE_PAD_RGMII0_RXC,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            /* PAD=RGMII0_RXC_0,   PIN=VIN4B_D5_5 */
            Bsp_platformSetPinmuxRegs((UInt32) 5U,
                                      (UInt32) CTRL_CORE_PAD_RGMII0_RXCTL,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            /* PAD=RGMII0_RXCTL_0, PIN=VIN4B_D6_5 */
            Bsp_platformSetPinmuxRegs((UInt32) 5U,
                                      (UInt32) CTRL_CORE_PAD_RGMII0_RXD3,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            /* PAD=RGMII0_RXD3_0,  PIN=VIN4B_D7_5 */
            Bsp_platformSetPinmuxRegs((UInt32) 5U,
                                      (UInt32) CTRL_CORE_PAD_MDIO_D,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            /* PAD=MDIO_D_0,       PIN=VIN4B_D0_5 */
            Bsp_platformSetPinmuxRegs((UInt32) 5U,
                                      (UInt32) CTRL_CORE_PAD_UART3_RXD,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            /* PAD=UART3_RXD_0,    PIN=VIN4B_D1_5 */
            Bsp_platformSetPinmuxRegs((UInt32) 5U,
                                      (UInt32) CTRL_CORE_PAD_UART3_TXD,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            /* PAD=UART3_TXD_0,    PIN=VIN4B_D2_5 */
            Bsp_platformSetPinmuxRegs((UInt32) 5U,
                                      (UInt32) CTRL_CORE_PAD_RGMII0_TXC,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            /* PAD=RGMII0_TXC_0,   PIN=VIN4B_D3_5 */
            Bsp_platformSetPinmuxRegs((UInt32) 5U,
                                      (UInt32) CTRL_CORE_PAD_RGMII0_TXCTL,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            /* PAD=RGMII0_TXCTL_0, PIN=VIN4B_D4_5 */
        }
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_AM574x) || defined (SOC_DRA75x)
        else if ((VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP3, VPS_VIP_S0,
                                            VPS_VIP_PORTA)) ==
                 instId)
        {
            /* VIN5-A pin mux */
            Bsp_platformSetPinmuxRegs((UInt32) 9U,
                                      (UInt32) CTRL_CORE_PAD_GPIO6_10,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=GPIO6_10_0,  PIN=VIN5A_CLK0_9 */
            Bsp_platformSetPinmuxRegs((UInt32) 9U,
                                      (UInt32) CTRL_CORE_PAD_MMC3_DAT6,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=MMC3_DAT6_0, PIN=VIN5A_HSYNC0_9 */
            Bsp_platformSetPinmuxRegs((UInt32) 9U,
                                      (UInt32) CTRL_CORE_PAD_MMC3_DAT7,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=MMC3_DAT7_0, PIN=VIN5A_VSYNC0_9 */
            Bsp_platformSetPinmuxRegs((UInt32) 9U,
                                      (UInt32) CTRL_CORE_PAD_MMC3_DAT0,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=MMC3_DAT0_0,  PIN=VIN5A_D5_9 */
            Bsp_platformSetPinmuxRegs((UInt32) 9U,
                                      (UInt32) CTRL_CORE_PAD_MMC3_DAT1,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=MMC3_DAT1_0,  PIN=VIN5A_D4_9 */
            Bsp_platformSetPinmuxRegs((UInt32) 9U,
                                      (UInt32) CTRL_CORE_PAD_MMC3_DAT2,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=MMC3_DAT2_0,  PIN=VIN5A_D3_9 */
            Bsp_platformSetPinmuxRegs((UInt32) 9U,
                                      (UInt32) CTRL_CORE_PAD_MMC3_DAT3,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=MMC3_DAT3_0,  PIN=VIN5A_D2_9 */
            Bsp_platformSetPinmuxRegs((UInt32) 9U,
                                      (UInt32) CTRL_CORE_PAD_MMC3_DAT4,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=MMC3_DAT4_0,  PIN=VIN5A_D1_9 */
            Bsp_platformSetPinmuxRegs((UInt32) 9U,
                                      (UInt32) CTRL_CORE_PAD_MMC3_DAT5,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=MMC3_DAT5_0,  PIN=VIN5A_D0_9 */
            Bsp_platformSetPinmuxRegs((UInt32) 9U,
                                      (UInt32) CTRL_CORE_PAD_MMC3_CMD,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=MMC3_CMD_0,   PIN=VIN5A_D6_9 */
            Bsp_platformSetPinmuxRegs((UInt32) 9U,
                                      (UInt32) CTRL_CORE_PAD_MMC3_CLK,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=MMC3_CLK_0,   PIN=VIN5A_D7_9 */
        }
        else if ((VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP3, VPS_VIP_S1,
                                            VPS_VIP_PORTA)) == instId)
        {
            /* VIN6-A pin mux */
            Bsp_platformSetPinmuxRegs((UInt32) 7U,
                                      (UInt32) CTRL_CORE_PAD_XREF_CLK1,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            /* PAD=XREF_CLK1_0,    PIN=VIN6A_CLK0_7   */
            Bsp_platformSetPinmuxRegs((UInt32) 7U,
                                      (UInt32) CTRL_CORE_PAD_MCASP1_AXR1,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            /* PAD=MCASP1_AXR1_0,  PIN=VIN6A_HSYNC0_7   */
            Bsp_platformSetPinmuxRegs((UInt32) 7U,
                                      (UInt32) CTRL_CORE_PAD_MCASP1_AXR0,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            /* PAD=MCASP1_AXR0_0,  PIN=VIN6A_VSYNC0_7   */
            Bsp_platformSetPinmuxRegs((UInt32) 7U,
                                      (UInt32) CTRL_CORE_PAD_MCASP3_AXR1,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            /* PAD=MCASP3_AXR1_0,  PIN=VIN6A_D0_7   */
            Bsp_platformSetPinmuxRegs((UInt32) 7U,
                                      (UInt32) CTRL_CORE_PAD_MCASP3_AXR0,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            /* PAD=MCASP3_AXR0_0,  PIN=VIN6A_D1_7   */
            Bsp_platformSetPinmuxRegs((UInt32) 7U,
                                      (UInt32) CTRL_CORE_PAD_MCASP3_FSX,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            /* PAD=MCASP3_FSX_0,   PIN=VIN6A_D2_7   */
            Bsp_platformSetPinmuxRegs((UInt32) 7U,
                                      (UInt32) CTRL_CORE_PAD_MCASP3_ACLKX,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            /* PAD=MCASP3_ACLKX_0, PIN=VIN6A_D3_7   */
            Bsp_platformSetPinmuxRegs((UInt32) 7U,
                                      (UInt32) CTRL_CORE_PAD_MCASP2_AXR3,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            /* PAD=MCASP2_AXR3_0,  PIN=VIN6A_D4_7   */
            Bsp_platformSetPinmuxRegs((UInt32) 7U,
                                      (UInt32) CTRL_CORE_PAD_MCASP2_AXR2,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            /* PAD=MCASP2_AXR2_0,  PIN=VIN6A_D5_7   */
            Bsp_platformSetPinmuxRegs((UInt32) 7U,
                                      (UInt32) CTRL_CORE_PAD_MCASP2_FSX,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            /* PAD=MCASP2_FSX_0,   PIN=VIN6A_D6_7   */
            Bsp_platformSetPinmuxRegs((UInt32) 7U,
                                      (UInt32) CTRL_CORE_PAD_MCASP2_ACLKX,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            /* PAD=MCASP2_ACLKX_0, PIN=VIN6A_D7_7   */

            if (BSP_BOARD_MODE_VIDEO_16BIT == boardMode)
            {
                /* PIN=VIN6A_D[8:15] */
                Bsp_platformSetPinmuxRegs((UInt32) 7U,
                                          (UInt32) CTRL_CORE_PAD_MCASP1_AXR15,
                                          BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs((UInt32) 7U,
                                          (UInt32) CTRL_CORE_PAD_MCASP1_AXR14,
                                          BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs((UInt32) 7U,
                                          (UInt32) CTRL_CORE_PAD_MCASP1_AXR13,
                                          BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs((UInt32) 7U,
                                          (UInt32) CTRL_CORE_PAD_MCASP1_AXR12,
                                          BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs((UInt32) 7U,
                                          (UInt32) CTRL_CORE_PAD_MCASP1_AXR11,
                                          BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs((UInt32) 7U,
                                          (UInt32) CTRL_CORE_PAD_MCASP1_AXR10,
                                          BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs((UInt32) 7U,
                                          (UInt32) CTRL_CORE_PAD_MCASP1_AXR9,
                                          BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs((UInt32) 7U,
                                          (UInt32) CTRL_CORE_PAD_MCASP1_AXR8,
                                          BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            }
        }
#endif
        else
        {
            /* Dummy else */
        }
    }
#endif
#endif

    return (FVID2_SOK);
}

#if defined (TDA2XX_MC_BUILD)
static void Bsp_boardSetPinMuxTda2xxMC(void)
{
    /*TOF*/
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_GPMC_A11_GPMC_A11_MUXMODE_SPI4_CS0_8,
        (UInt32) CTRL_CORE_PAD_GPMC_A11,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_GPMC_A8_GPMC_A8_MUXMODE_SPI4_SCLK_8,
        (UInt32) CTRL_CORE_PAD_GPMC_A8,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_GPMC_A10_GPMC_A10_MUXMODE_SPI4_D0_8,
        (UInt32) CTRL_CORE_PAD_GPMC_A10,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_GPMC_A3_GPMC_A3_MUXMODE_GPIO7_6_14,
        (UInt32) CTRL_CORE_PAD_GPMC_A3,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_GPMC_A6_GPMC_A6_MUXMODE_GPIO1_28_14,
        (UInt32) CTRL_CORE_PAD_GPMC_A6,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_GPMC_A7_GPMC_A7_MUXMODE_GPIO1_29_14,
        (UInt32) CTRL_CORE_PAD_GPMC_A7,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_GPMC_A1_GPMC_A1_MUXMODE_GPIO7_4_14,
        (UInt32) CTRL_CORE_PAD_GPMC_A1,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_GPMC_A2_GPMC_A2_MUXMODE_GPIO7_5_14,
        (UInt32) CTRL_CORE_PAD_GPMC_A2,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VOUT1_D2_VOUT1_D2_MUXMODE_GPIO8_2_14,
        (UInt32) CTRL_CORE_PAD_VOUT1_D2,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VOUT1_D3_VOUT1_D3_MUXMODE_GPIO8_3_14,
        (UInt32) CTRL_CORE_PAD_VOUT1_D3,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_GPMC_A27_GPMC_A27_MUXMODE_VIN3B_HSYNC1_6,
        (UInt32) CTRL_CORE_PAD_GPMC_A27,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_GPMC_CS1_GPMC_CS1_MUXMODE_VIN3B_VSYNC1_6,
        (UInt32) CTRL_CORE_PAD_GPMC_CS1,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_GPMC_A26_GPMC_A26_MUXMODE_VIN3B_D7_6,
        (UInt32) CTRL_CORE_PAD_GPMC_A26,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_GPMC_A25_GPMC_A25_MUXMODE_VIN3B_D6_6,
        (UInt32) CTRL_CORE_PAD_GPMC_A25,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_GPMC_A24_GPMC_A24_MUXMODE_VIN3B_D5_6,
        (UInt32) CTRL_CORE_PAD_GPMC_A24,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_GPMC_A23_GPMC_A23_MUXMODE_VIN3B_D4_6,
        (UInt32) CTRL_CORE_PAD_GPMC_A23,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_GPMC_A22_GPMC_A22_MUXMODE_VIN3B_D3_6,
        (UInt32) CTRL_CORE_PAD_GPMC_A22,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_GPMC_A21_GPMC_A21_MUXMODE_VIN3B_D2_6,
        (UInt32) CTRL_CORE_PAD_GPMC_A21,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_GPMC_A20_GPMC_A20_MUXMODE_VIN3B_D1_6,
        (UInt32) CTRL_CORE_PAD_GPMC_A20,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_GPMC_A19_GPMC_A19_MUXMODE_VIN3B_D0_6,
        (UInt32) CTRL_CORE_PAD_GPMC_A19,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);

    /*AUDIO*/
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_MCASP1_AXR2_MCASP1_AXR2_MUXMODE_MCASP1_AXR2_0,
        (UInt32) CTRL_CORE_PAD_MCASP1_AXR2,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_MCASP1_AXR3_MCASP1_AXR3_MUXMODE_MCASP1_AXR3_0,
        (UInt32) CTRL_CORE_PAD_MCASP1_AXR3,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_MCASP1_ACLKX_MCASP1_ACLKX_MUXMODE_MCASP1_ACLKX_0,
        (UInt32) CTRL_CORE_PAD_MCASP1_ACLKX,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_MCASP1_FSX_MCASP1_FSX_MUXMODE_MCASP1_FSX_0,
        (UInt32) CTRL_CORE_PAD_MCASP1_FSX,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);

    /*SPI 1 & 2*/
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_SPI1_CS0_SPI1_CS0_MUXMODE_SPI1_CS0_0,
        (UInt32) CTRL_CORE_PAD_SPI1_CS0,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_SPI1_SCLK_SPI1_SCLK_MUXMODE_SPI1_SCLK_0,
        (UInt32) CTRL_CORE_PAD_SPI1_SCLK,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_SPI1_D0_SPI1_D0_MUXMODE_SPI1_D0_0,
        (UInt32) CTRL_CORE_PAD_SPI1_D0,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_SPI1_D1_SPI1_D1_MUXMODE_SPI1_D1_0,
        (UInt32) CTRL_CORE_PAD_SPI1_D1,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);

    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_SPI2_CS0_SPI2_CS0_MUXMODE_SPI2_CS0_0,
        (UInt32) CTRL_CORE_PAD_SPI2_CS0,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_SPI2_SCLK_SPI2_SCLK_MUXMODE_SPI2_SCLK_0,
        (UInt32) CTRL_CORE_PAD_SPI2_SCLK,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_SPI2_D0_SPI2_D0_MUXMODE_SPI2_D0_0,
        (UInt32) CTRL_CORE_PAD_SPI2_D0,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_SPI2_D1_SPI2_D1_MUXMODE_SPI2_D1_0,
        (UInt32) CTRL_CORE_PAD_SPI2_D1,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);

    /*USB*/
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_USB1_DRVVBUS_USB1_DRVVBUS_MUXMODE_USB1_DRVVBUS_0,
        (UInt32) CTRL_CORE_PAD_USB1_DRVVBUS,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_USB2_DRVVBUS_USB2_DRVVBUS_MUXMODE_USB2_DRVVBUS_0,
        (UInt32) CTRL_CORE_PAD_USB2_DRVVBUS,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);

    /*CAN port*/
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_DCAN1_RX_DCAN1_RX_MUXMODE_DCAN1_RX_0,
        (UInt32) CTRL_CORE_PAD_DCAN1_RX,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_DCAN1_TX_DCAN1_TX_MUXMODE_DCAN1_TX_0,
        (UInt32) CTRL_CORE_PAD_DCAN1_TX,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_GPMC_BEN1_GPMC_BEN1_MUXMODE_GPIO2_27_14,
        (UInt32) CTRL_CORE_PAD_GPMC_BEN1,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);

    /* Driving CAN transceiver's STB pin low */
    GPIOModuleEnable((UInt32) SOC_GPIO2_BASE);
    GPIODirModeSet(
        (UInt32) SOC_GPIO2_BASE,
        BOARD_GPIO_PIN_GPIO2_27,
        GPIO_DIR_OUTPUT);
    GPIOPinWrite(
        (UInt32) SOC_GPIO2_BASE,
        BOARD_GPIO_PIN_GPIO2_27,
        GPIO_PIN_LOW);

    /*LIN port*/
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_UART1_RXD_UART1_RXD_MUXMODE_UART1_RXD_0,
        (UInt32) CTRL_CORE_PAD_UART1_RXD,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_UART1_TXD_UART1_TXD_MUXMODE_UART1_TXD_0,
        (UInt32) CTRL_CORE_PAD_UART1_TXD,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_GPMC_CS3_GPMC_CS3_MUXMODE_GPIO2_21_14,
        (UInt32) CTRL_CORE_PAD_GPMC_CS3,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_GPMC_WEN_GPMC_WEN_MUXMODE_GPIO2_25_14,
        (UInt32) CTRL_CORE_PAD_GPMC_WEN,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);

    /*RS485 port*/
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_UART2_RXD_UART2_RXD_MUXMODE_UART2_RXD_0,
        (UInt32) CTRL_CORE_PAD_UART2_RXD,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_UART2_TXD_UART2_TXD_MUXMODE_UART2_TXD_0,
        (UInt32) CTRL_CORE_PAD_UART2_TXD,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_GPMC_A0_GPMC_A0_MUXMODE_GPIO7_3_14,
        (UInt32) CTRL_CORE_PAD_GPMC_A0,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_GPIO6_16_GPIO6_16_MUXMODE_GPIO6_16_14,
        (UInt32) CTRL_CORE_PAD_GPIO6_16,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);

    /*Board to Board connector*/
    /*DM388_GPIO_0*/
    GPIOModuleEnable((UInt32) SOC_GPIO8_BASE);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VOUT1_D0_VOUT1_D0_MUXMODE_GPIO8_0_14,
        (UInt32) CTRL_CORE_PAD_VOUT1_D0,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    /*DM388_GPIO_1*/
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_MCASP2_AXR7_MCASP2_AXR7_MUXMODE_GPIO1_5_14,
        (UInt32) CTRL_CORE_PAD_MCASP2_AXR7,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    /*DM388_GPIO_2*/
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VOUT1_D1_VOUT1_D1_MUXMODE_GPIO8_1_14,
        (UInt32) CTRL_CORE_PAD_VOUT1_D1,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    /*DM388_GPIO_3*/
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VOUT1_D4_VOUT1_D4_MUXMODE_GPIO8_4_14,
        (UInt32) CTRL_CORE_PAD_VOUT1_D4,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    /*DM388_GPIO_4*/
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VOUT1_D7_VOUT1_D7_MUXMODE_GPIO8_7_14,
        (UInt32) CTRL_CORE_PAD_VOUT1_D7,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);

    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN2A_D0_VIN2A_D0_MUXMODE_VIN2A_D0_0,
        (UInt32) CTRL_CORE_PAD_VIN2A_D0,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN2A_D1_VIN2A_D1_MUXMODE_VIN2A_D1_0,
        (UInt32) CTRL_CORE_PAD_VIN2A_D1,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN2A_D2_VIN2A_D2_MUXMODE_VIN2A_D2_0,
        (UInt32) CTRL_CORE_PAD_VIN2A_D2,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN2A_D3_VIN2A_D3_MUXMODE_VIN2A_D3_0,
        (UInt32) CTRL_CORE_PAD_VIN2A_D3,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN2A_D4_VIN2A_D4_MUXMODE_VIN2A_D4_0,
        (UInt32) CTRL_CORE_PAD_VIN2A_D4,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN2A_D5_VIN2A_D5_MUXMODE_VIN2A_D5_0,
        (UInt32) CTRL_CORE_PAD_VIN2A_D5,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN2A_D6_VIN2A_D6_MUXMODE_VIN2A_D6_0,
        (UInt32) CTRL_CORE_PAD_VIN2A_D6,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN2A_D7_VIN2A_D7_MUXMODE_VIN2A_D7_0,
        (UInt32) CTRL_CORE_PAD_VIN2A_D7,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN2A_D8_VIN2A_D8_MUXMODE_VIN2A_D8_0,
        (UInt32) CTRL_CORE_PAD_VIN2A_D8,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN2A_D9_VIN2A_D9_MUXMODE_VIN2A_D9_0,
        (UInt32) CTRL_CORE_PAD_VIN2A_D9,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN2A_D10_VIN2A_D10_MUXMODE_VIN2A_D10_0,
        (UInt32) CTRL_CORE_PAD_VIN2A_D10,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN2A_D11_VIN2A_D11_MUXMODE_VIN2A_D11_0,
        (UInt32) CTRL_CORE_PAD_VIN2A_D11,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN2A_D12_VIN2A_D12_MUXMODE_VIN2A_D12_0,
        (UInt32) CTRL_CORE_PAD_VIN2A_D12,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN2A_D13_VIN2A_D13_MUXMODE_VIN2A_D13_0,
        (UInt32) CTRL_CORE_PAD_VIN2A_D13,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN2A_D14_VIN2A_D14_MUXMODE_VIN2A_D14_0,
        (UInt32) CTRL_CORE_PAD_VIN2A_D14,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN2A_D15_VIN2A_D15_MUXMODE_VIN2A_D15_0,
        (UInt32) CTRL_CORE_PAD_VIN2A_D15,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN2A_D16_VIN2A_D16_MUXMODE_VIN2A_D16_0,
        (UInt32) CTRL_CORE_PAD_VIN2A_D16,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN2A_D17_VIN2A_D17_MUXMODE_VIN2A_D17_0,
        (UInt32) CTRL_CORE_PAD_VIN2A_D17,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN2A_D18_VIN2A_D18_MUXMODE_VIN2A_D18_0,
        (UInt32) CTRL_CORE_PAD_VIN2A_D18,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN2A_D19_VIN2A_D19_MUXMODE_VIN2A_D19_0,
        (UInt32) CTRL_CORE_PAD_VIN2A_D19,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN2A_D20_VIN2A_D20_MUXMODE_VIN2A_D20_0,
        (UInt32) CTRL_CORE_PAD_VIN2A_D20,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN2A_D21_VIN2A_D21_MUXMODE_VIN2A_D21_0,
        (UInt32) CTRL_CORE_PAD_VIN2A_D21,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN2A_D22_VIN2A_D22_MUXMODE_VIN2A_D22_0,
        (UInt32) CTRL_CORE_PAD_VIN2A_D22,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN2A_D23_VIN2A_D23_MUXMODE_VIN2A_D23_0,
        (UInt32) CTRL_CORE_PAD_VIN2A_D23,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN2A_HSYNC0_VIN2A_HSYNC0_MUXMODE_VIN2A_HSYNC0_0,
        (UInt32) CTRL_CORE_PAD_VIN2A_HSYNC0,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN2A_VSYNC0_VIN2A_VSYNC0_MUXMODE_VIN2A_VSYNC0_0,
        (UInt32) CTRL_CORE_PAD_VIN2A_VSYNC0,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN2A_DE0_VIN2A_DE0_MUXMODE_VIN2A_DE0_0,
        (UInt32) CTRL_CORE_PAD_VIN2A_DE0,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN2A_FLD0_VIN2A_FLD0_MUXMODE_VIN2A_FLD0_0,
        (UInt32) CTRL_CORE_PAD_VIN2A_FLD0,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN2A_CLK0_VIN2A_CLK0_MUXMODE_VIN2A_CLK0_0,
        (UInt32) CTRL_CORE_PAD_VIN2A_CLK0,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);

    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN1A_D0_VIN1A_D0_MUXMODE_VIN1A_D0_0,
        (UInt32) CTRL_CORE_PAD_VIN1A_D0,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN1A_D1_VIN1A_D1_MUXMODE_VIN1A_D1_0,
        (UInt32) CTRL_CORE_PAD_VIN1A_D1,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN1A_D2_VIN1A_D2_MUXMODE_VIN1A_D2_0,
        (UInt32) CTRL_CORE_PAD_VIN1A_D2,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN1A_D3_VIN1A_D3_MUXMODE_VIN1A_D3_0,
        (UInt32) CTRL_CORE_PAD_VIN1A_D3,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN1A_D4_VIN1A_D4_MUXMODE_VIN1A_D4_0,
        (UInt32) CTRL_CORE_PAD_VIN1A_D4,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN1A_D5_VIN1A_D5_MUXMODE_VIN1A_D5_0,
        (UInt32) CTRL_CORE_PAD_VIN1A_D5,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN1A_D6_VIN1A_D6_MUXMODE_VIN1A_D6_0,
        (UInt32) CTRL_CORE_PAD_VIN1A_D6,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN1A_D7_VIN1A_D7_MUXMODE_VIN1A_D7_0,
        (UInt32) CTRL_CORE_PAD_VIN1A_D7,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN1A_D8_VIN1A_D8_MUXMODE_VIN1A_D8_0,
        (UInt32) CTRL_CORE_PAD_VIN1A_D8,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN1A_D9_VIN1A_D9_MUXMODE_VIN1A_D9_0,
        (UInt32) CTRL_CORE_PAD_VIN1A_D9,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN1A_D10_VIN1A_D10_MUXMODE_VIN1A_D10_0,
        (UInt32) CTRL_CORE_PAD_VIN1A_D10,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN1A_D11_VIN1A_D11_MUXMODE_VIN1A_D11_0,
        (UInt32) CTRL_CORE_PAD_VIN1A_D11,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN1A_D12_VIN1A_D12_MUXMODE_VIN1A_D12_0,
        (UInt32) CTRL_CORE_PAD_VIN1A_D12,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN1A_D13_VIN1A_D13_MUXMODE_VIN1A_D13_0,
        (UInt32) CTRL_CORE_PAD_VIN1A_D13,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN1A_D14_VIN1A_D14_MUXMODE_VIN1A_D14_0,
        (UInt32) CTRL_CORE_PAD_VIN1A_D14,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN1A_D15_VIN1A_D15_MUXMODE_VIN1A_D15_0,
        (UInt32) CTRL_CORE_PAD_VIN1A_D15,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN1A_D16_VIN1A_D16_MUXMODE_VIN1A_D16_0,
        (UInt32) CTRL_CORE_PAD_VIN1A_D16,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN1A_D17_VIN1A_D17_MUXMODE_VIN1A_D17_0,
        (UInt32) CTRL_CORE_PAD_VIN1A_D17,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN1A_D18_VIN1A_D18_MUXMODE_VIN1A_D18_0,
        (UInt32) CTRL_CORE_PAD_VIN1A_D18,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN1A_D19_VIN1A_D19_MUXMODE_VIN1A_D19_0,
        (UInt32) CTRL_CORE_PAD_VIN1A_D19,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN1A_D20_VIN1A_D20_MUXMODE_VIN1A_D20_0,
        (UInt32) CTRL_CORE_PAD_VIN1A_D20,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN1A_D21_VIN1A_D21_MUXMODE_VIN1A_D21_0,
        (UInt32) CTRL_CORE_PAD_VIN1A_D21,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN1A_D22_VIN1A_D22_MUXMODE_VIN1A_D22_0,
        (UInt32) CTRL_CORE_PAD_VIN1A_D22,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN1A_D23_VIN1A_D23_MUXMODE_VIN1A_D23_0,
        (UInt32) CTRL_CORE_PAD_VIN1A_D23,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN1A_HSYNC0_VIN1A_HSYNC0_MUXMODE_VIN1A_HSYNC0_0,
        (UInt32) CTRL_CORE_PAD_VIN1A_HSYNC0,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN1A_VSYNC0_VIN1A_VSYNC0_MUXMODE_VIN1A_VSYNC0_0,
        (UInt32) CTRL_CORE_PAD_VIN1A_VSYNC0,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN1A_DE0_VIN1A_DE0_MUXMODE_VIN1A_DE0_0,
        (UInt32) CTRL_CORE_PAD_VIN1A_DE0,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN1A_FLD0_VIN1A_FLD0_MUXMODE_VIN1A_FLD0_0,
        (UInt32) CTRL_CORE_PAD_VIN1A_FLD0,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN1A_CLK0_VIN1A_CLK0_MUXMODE_VIN1A_CLK0_0,
        (UInt32) CTRL_CORE_PAD_VIN1A_CLK0,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);

    /*Main Image Sensor*/
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VOUT1_D16_VOUT1_D16_MUXMODE_VIN3A_D0_4,
        (UInt32) CTRL_CORE_PAD_VOUT1_D16,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VOUT1_D17_VOUT1_D17_MUXMODE_VIN3A_D1_4,
        (UInt32) CTRL_CORE_PAD_VOUT1_D17,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VOUT1_D18_VOUT1_D18_MUXMODE_VIN3A_D2_4,
        (UInt32) CTRL_CORE_PAD_VOUT1_D18,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VOUT1_D19_VOUT1_D19_MUXMODE_VIN3A_D3_4,
        (UInt32) CTRL_CORE_PAD_VOUT1_D19,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VOUT1_D20_VOUT1_D20_MUXMODE_VIN3A_D4_4,
        (UInt32) CTRL_CORE_PAD_VOUT1_D20,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VOUT1_D21_VOUT1_D21_MUXMODE_VIN3A_D5_4,
        (UInt32) CTRL_CORE_PAD_VOUT1_D21,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VOUT1_D22_VOUT1_D22_MUXMODE_VIN3A_D6_4,
        (UInt32) CTRL_CORE_PAD_VOUT1_D22,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VOUT1_D23_VOUT1_D23_MUXMODE_VIN3A_D7_4,
        (UInt32) CTRL_CORE_PAD_VOUT1_D23,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);

    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VOUT1_D8_VOUT1_D8_MUXMODE_VIN3A_D8_4,
        (UInt32) CTRL_CORE_PAD_VOUT1_D8,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VOUT1_D9_VOUT1_D9_MUXMODE_VIN3A_D9_4,
        (UInt32) CTRL_CORE_PAD_VOUT1_D9,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VOUT1_D10_VOUT1_D10_MUXMODE_VIN3A_D10_4,
        (UInt32) CTRL_CORE_PAD_VOUT1_D10,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VOUT1_D11_VOUT1_D11_MUXMODE_VIN3A_D11_4,
        (UInt32) CTRL_CORE_PAD_VOUT1_D11,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VOUT1_D12_VOUT1_D12_MUXMODE_VIN3A_D12_4,
        (UInt32) CTRL_CORE_PAD_VOUT1_D12,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VOUT1_D13_VOUT1_D13_MUXMODE_VIN3A_D13_4,
        (UInt32) CTRL_CORE_PAD_VOUT1_D13,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VOUT1_D14_VOUT1_D14_MUXMODE_VIN3A_D14_4,
        (UInt32) CTRL_CORE_PAD_VOUT1_D14,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VOUT1_D15_VOUT1_D15_MUXMODE_VIN3A_D15_4,
        (UInt32) CTRL_CORE_PAD_VOUT1_D15,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);

    /*CAM_RESET*/
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VOUT1_DE_VOUT1_DE_MUXMODE_GPIO4_20_14,
        (UInt32) CTRL_CORE_PAD_VOUT1_DE,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VOUT1_FLD_VOUT1_FLD_MUXMODE_VIN3A_CLK0_4,
        (UInt32) CTRL_CORE_PAD_VOUT1_FLD,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VOUT1_HSYNC_VOUT1_HSYNC_MUXMODE_VIN3A_HSYNC0_4,
        (UInt32) CTRL_CORE_PAD_VOUT1_HSYNC,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VOUT1_VSYNC_VOUT1_VSYNC_MUXMODE_VIN3A_VSYNC0_4,
        (UInt32) CTRL_CORE_PAD_VOUT1_VSYNC,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    /*CAM_GPIO_0*/
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_MCASP2_AXR5_MCASP2_AXR5_MUXMODE_GPIO6_7_14,
        (UInt32) CTRL_CORE_PAD_MCASP2_AXR5,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    /*CAM_GPIO_1*/
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_UART2_CTSN_UART2_CTSN_MUXMODE_GPIO1_16_14,
        (UInt32) CTRL_CORE_PAD_UART2_CTSN,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    /*CAM_GPIO_2*/
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_UART2_RTSN_UART2_RTSN_MUXMODE_GPIO1_17_14,
        (UInt32) CTRL_CORE_PAD_UART2_RTSN,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);

    /*PWM*/
    /*PWM_VIDEO*/
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_GPMC_BEN0_GPMC_BEN0_MUXMODE_TIMER2_7,
        (UInt32) CTRL_CORE_PAD_GPMC_BEN0,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    /*PWM_DC*/
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_GPMC_ADVN_ALE_GPMC_ADVN_ALE_MUXMODE_TIMER3_7,
        (UInt32) CTRL_CORE_PAD_GPMC_ADVN_ALE,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);

    /*GPIO's*/
    /*ALARM_RESET*/
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_GPMC_A9_GPMC_A9_MUXMODE_GPIO1_31_14,
        (UInt32) CTRL_CORE_PAD_GPMC_A9,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    /*ALARM_IN*/
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_GPMC_A12_GPMC_A12_MUXMODE_GPIO2_2_14,
        (UInt32) CTRL_CORE_PAD_GPMC_A12,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    /*ETH_INT#*/
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_GPMC_CS0_GPMC_CS0_MUXMODE_GPIO2_19_14,
        (UInt32) CTRL_CORE_PAD_GPMC_CS0,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    /*LED_GPIO_B*/
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_GPMC_OEN_REN_GPMC_OEN_REN_MUXMODE_GPIO2_24_14,
        (UInt32) CTRL_CORE_PAD_GPMC_OEN_REN,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    /*PIR_OUT*/
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_GPMC_WAIT0_GPMC_WAIT0_MUXMODE_GPIO2_28_14,
        (UInt32) CTRL_CORE_PAD_GPMC_WAIT0,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    /*ALARM_OUT*/
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_MCASP2_AXR6_MCASP2_AXR6_MUXMODE_GPIO2_29_14,
        (UInt32) CTRL_CORE_PAD_MCASP2_AXR6,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    /*HDMI_HPD*/
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_SPI1_CS3_SPI1_CS3_MUXMODE_GPIO7_13_14,
        (UInt32) CTRL_CORE_PAD_SPI1_CS3,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    /*HDMI_CEC*/
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_SPI1_CS2_SPI1_CS2_MUXMODE_GPIO7_12_14,
        (UInt32) CTRL_CORE_PAD_SPI1_CS2,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    /*HDMI_CT_HPD*/
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VOUT1_D5_VOUT1_D5_MUXMODE_GPIO8_5_14,
        (UInt32) CTRL_CORE_PAD_VOUT1_D5,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    /*HDMI_LS_OE*/
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VOUT1_D6_VOUT1_D6_MUXMODE_GPIO8_6_14,
        (UInt32) CTRL_CORE_PAD_VOUT1_D6,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    /*LED_GPIO_R*/
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VIN1B_CLK1_VIN1B_CLK1_MUXMODE_GPIO2_31_14,
        (UInt32) CTRL_CORE_PAD_VIN1B_CLK1,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    /*LED_GPIO_G*/
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VOUT1_CLK_VOUT1_CLK_MUXMODE_GPIO4_19_14,
        (UInt32) CTRL_CORE_PAD_VOUT1_CLK,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);

    /* FPD link CAM2 -> VIN3A */
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VOUT1_FLD_VOUT1_FLD_MUXMODE_VIN3A_CLK0_4,
        (UInt32) CTRL_CORE_PAD_VOUT1_FLD,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VOUT1_HSYNC_VOUT1_HSYNC_MUXMODE_VIN3A_HSYNC0_4,
        (UInt32) CTRL_CORE_PAD_VOUT1_HSYNC,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VOUT1_VSYNC_VOUT1_VSYNC_MUXMODE_VIN3A_VSYNC0_4,
        (UInt32) CTRL_CORE_PAD_VOUT1_VSYNC,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VOUT1_D16_VOUT1_D16_MUXMODE_VIN3A_D0_4,
        (UInt32) CTRL_CORE_PAD_VOUT1_D16,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VOUT1_D17_VOUT1_D17_MUXMODE_VIN3A_D1_4,
        (UInt32) CTRL_CORE_PAD_VOUT1_D17,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VOUT1_D18_VOUT1_D18_MUXMODE_VIN3A_D2_4,
        (UInt32) CTRL_CORE_PAD_VOUT1_D18,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VOUT1_D19_VOUT1_D19_MUXMODE_VIN3A_D3_4,
        (UInt32) CTRL_CORE_PAD_VOUT1_D19,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VOUT1_D20_VOUT1_D20_MUXMODE_VIN3A_D4_4,
        (UInt32) CTRL_CORE_PAD_VOUT1_D20,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VOUT1_D21_VOUT1_D21_MUXMODE_VIN3A_D5_4,
        (UInt32) CTRL_CORE_PAD_VOUT1_D21,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VOUT1_D22_VOUT1_D22_MUXMODE_VIN3A_D6_4,
        (UInt32) CTRL_CORE_PAD_VOUT1_D22,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_VOUT1_D23_VOUT1_D23_MUXMODE_VIN3A_D7_4,
        (UInt32) CTRL_CORE_PAD_VOUT1_D23,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);

    /* I2C3 SCl SDA for stereo sensor configuration */
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_GPIO6_14_GPIO6_14_MUXMODE_I2C3_SDA_9,
        (UInt32) CTRL_CORE_PAD_GPIO6_14,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_GPIO6_15_GPIO6_15_MUXMODE_I2C3_SCL_9,
        (UInt32) CTRL_CORE_PAD_GPIO6_15,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);

    /*DM388_GPIO_0*/
    GPIODirModeSet(
        BOARD_GPIO_BASE_MUX_SEL_RESET,
        BOARD_GPIO_PIN_MUX1_SEL0_RESET,
        GPIO_DIR_OUTPUT);

    GPIOPinWrite(
        BOARD_GPIO_BASE_MUX_SEL_RESET,
        BOARD_GPIO_PIN_MUX1_SEL0_RESET,
        GPIO_PIN_HIGH);
    /*DM388_GPIO_1*/
    GPIODirModeSet(
        BOARD_GPIO_BASE_MUX_SEL1_RESET,
        BOARD_GPIO_PIN_MUX1_SEL5_RESET,
        GPIO_DIR_INPUT);

    /*DM388_GPIO_2*/
    GPIODirModeSet(
        BOARD_GPIO_BASE_MUX_SEL_RESET,
        BOARD_GPIO_PIN_MUX1_SEL1_RESET,
        GPIO_DIR_INPUT);

    /*DM388_GPIO_3*/
    GPIODirModeSet(
        BOARD_GPIO_BASE_MUX_SEL_RESET,
        BOARD_GPIO_PIN_MUX1_SEL4_RESET,
        GPIO_DIR_INPUT);

    /*DM388_GPIO_4*/
    GPIODirModeSet(
        BOARD_GPIO_BASE_MUX_SEL_RESET,
        BOARD_GPIO_PIN_MUX1_SEL7_RESET,
        GPIO_DIR_INPUT);
}

#endif

static Int32 Bsp_boardTda2xxEnableMmc1(void)
{
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined (SOC_TDA2EX)
    uint32_t tmpRegVal;

    /*MMC1- CM_L3INIT_MMC1_CLKCTRL */
    tmpRegVal  = HW_RD_REG32(SOC_L3INIT_CM_CORE_BASE + CM_L3INIT_MMC1_CLKCTRL);
    tmpRegVal |= 0x03000000U;
    HW_WR_REG32(SOC_L3INIT_CM_CORE_BASE + CM_L3INIT_MMC1_CLKCTRL, tmpRegVal);

    /*Enable the module - mmc1  */
    PMHALModuleModeSet(PMHAL_PRCM_MOD_MMC1, PMHAL_PRCM_MODULE_MODE_ENABLED,
                       PM_TIMEOUT_INFINITE);

    Bsp_boardTda2xxMmcsdLdoPwr();
#endif
    return (BSP_SOK);
}

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined (SOC_TDA2EX)
static Int32 Bsp_boardTda2xxMmcsdLdoPwr(void)
{
    /*CTRL_CORE_CONTROL_PBIAS*/
    uint32_t reg_val = 0;

    reg_val = HW_RD_REG32(
        SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE + CTRL_CORE_CONTROL_PBIAS);

    reg_val &= ~CTRL_CORE_CONTROL_PBIAS_SDCARD_IO_PWRDNZ_MASK;
    HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                CTRL_CORE_CONTROL_PBIAS, reg_val);
    BspOsal_sleep(1U);

    reg_val &= ~CTRL_CORE_CONTROL_PBIAS_SDCARD_BIAS_PWRDNZ_MASK;
    HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                CTRL_CORE_CONTROL_PBIAS, reg_val);

    /*Enable SDCARD_BIAS_VMODE*/
    reg_val |= CTRL_CORE_CONTROL_PBIAS_SDCARD_BIAS_VMODE_MASK; /* 3v */
    HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                CTRL_CORE_CONTROL_PBIAS, reg_val);

    reg_val = HW_RD_REG32(
        SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE + CTRL_CORE_CONTROL_PBIAS);
    reg_val |= CTRL_CORE_CONTROL_PBIAS_SDCARD_BIAS_PWRDNZ_MASK;
    HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                CTRL_CORE_CONTROL_PBIAS, reg_val);
    BspOsal_sleep(1U);

    reg_val |= CTRL_CORE_CONTROL_PBIAS_SDCARD_IO_PWRDNZ_MASK;
    HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                CTRL_CORE_CONTROL_PBIAS, reg_val);

    BspOsal_sleep(1U);

    return BSP_SOK;
}

#endif

#if defined (BOARD_TYPE_TDA2XX_CASCADE_RADAR)
void Bsp_boardTda2xxCascadeEnableSdAndEth(void)
{
#ifndef BSP_DISABLE_I2C0
    Int32  retVal = BSP_SOK;
    UInt8  regValue[2];
    UInt32 i2cInst, ioExpAddr, numRegs;

    Bsp_boardSetPinMuxTda2xx(BSP_DRV_ID_I2C, BSP_DEVICE_I2C_INST_ID_0, BSP_BOARD_MODE_NONE);
    i2cInst   = BSP_DEVICE_I2C_INST_ID_0;
    ioExpAddr = BSP_BOARD_TCA9539_I2C_SLAVE_ADDR;
    numRegs   = 1U;
    /* Configure muxes */
    regValue[0U] = (UInt8) BSP_BOARD_TCA9539_REG_CONFIG1;
    regValue[1U] = (UInt8) 0xDE; /* configure output Pins EXP_ETH0_RSTn and SD_PWR_EN */
    retVal      +=
        Bsp_deviceWrite8(i2cInst, ioExpAddr, &regValue[0], &regValue[1], numRegs);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspBoardTrace, GT_ERR, "I2C write failed!!\r\n");
    }
    regValue[0U] = (UInt8) BSP_BOARD_TCA9539_REG_OUTPUT1;
    regValue[1U] = (UInt8) 0xFF; /* configure output Pins EXP_ETH0_RSTn and SD_PWR_EN */
    retVal      +=
        Bsp_deviceWrite8(i2cInst, ioExpAddr, &regValue[0], &regValue[1], numRegs);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspBoardTrace, GT_ERR, "I2C write failed!!\r\n");
    }
#endif
}
void Bsp_boardTda2xxCascadeAwr12xxPadConfig(void)
{
    /* GPIO2_2_AWR1_RESETN */
    Bsp_platformSetPinmuxRegs((UInt32) 0xE,
                            (UInt32) CTRL_CORE_PAD_GPMC_A12,     /* gpio2_2 */
                            0x8);
    /* GPIO2_9_AWR2_RESETN */
    Bsp_platformSetPinmuxRegs((UInt32) 0xE,
                            (UInt32) CTRL_CORE_PAD_GPMC_A19,     /* gpio2_9 */
                            0x8);
    /* GPIO2_10_AWR3_RESETN */
    Bsp_platformSetPinmuxRegs((UInt32) 0xE,
                            (UInt32) CTRL_CORE_PAD_GPMC_A20,     /* gpio2_10 */
                            0x8);
    /* GPIO2_11_AWR4_RESETN */
    Bsp_platformSetPinmuxRegs((UInt32) 0xE,
                            (UInt32) CTRL_CORE_PAD_GPMC_A21,    /* gpio2_11 */
                            0x8);
    /* GPIO2_12_AWR_WARM_RST */
    Bsp_platformSetPinmuxRegs((UInt32) 0xE,
                            (UInt32) CTRL_CORE_PAD_GPMC_A22,     /* gpio2_12 */
                            0x8);
    /* GPIO2_13_AWR_SOP2 */
    Bsp_platformSetPinmuxRegs((UInt32) 0xE,
                            (UInt32) CTRL_CORE_PAD_GPMC_A23,     /* 0x18 - gpio2_13 */
                            0x8);
    /* GPIO2_22_AWR_SOP0 */
    Bsp_platformSetPinmuxRegs((UInt32) 0xE,
                            (UInt32) CTRL_CORE_PAD_GPMC_CLK,     /* gpio2_22 */
                            0x8);
    /* GPIO2_25_AWR_SOP1 */
    Bsp_platformSetPinmuxRegs((UInt32) 0xE,
                            (UInt32) CTRL_CORE_PAD_GPMC_WEN,     /* gpio2_25 */
                            0x8);
    /* GPIO7_24_AWR1_SPI_INT */
    Bsp_platformSetPinmuxRegs((UInt32) 0xE,
                            (UInt32) CTRL_CORE_PAD_UART1_CTSN,   /* gpio7_24 */
                            0xC);
    /* GPIO5_10_AWR2_SPI_INT */
    Bsp_platformSetPinmuxRegs((UInt32) 0xE,
                            (UInt32) CTRL_CORE_PAD_MCASP1_AXR8,     /* SPI Int */
                            0xC);
    /* GPIO5_11_AWR3_SPI_INT */
    Bsp_platformSetPinmuxRegs((UInt32) 0xE,
                            (UInt32) CTRL_CORE_PAD_MCASP1_AXR9,     /* SPI Int */
                            0xC);
    /* GPIO7_25_AWR4_SPI_INT */
    Bsp_platformSetPinmuxRegs((UInt32) 0xE,
                            (UInt32) CTRL_CORE_PAD_UART1_RTSN,   /* gpio7_25 */
                            0xC);
    Bsp_platformSetPinmuxRegs((UInt32) 0x1,
                            (UInt32) CTRL_CORE_PAD_MMC3_DAT2,     /* SPI3 */
                            0x6);
    Bsp_platformSetPinmuxRegs((UInt32) 0x1,
                            (UInt32) CTRL_CORE_PAD_MMC3_DAT0,     /* SPI3 */
                            0xC);
    Bsp_platformSetPinmuxRegs((UInt32) 0x1,
                            (UInt32) CTRL_CORE_PAD_MMC3_DAT1,     /* SPI3 */
                            0xC);
    Bsp_platformSetPinmuxRegs((UInt32) 0x1,
                            (UInt32) CTRL_CORE_PAD_MMC3_CMD,     /* SPI3 */
                            0xC);
    Bsp_platformSetPinmuxRegs((UInt32) 0x0,
                            (UInt32) CTRL_CORE_PAD_SPI1_CS0,     /* SPI1 */
                            0x6);
    Bsp_platformSetPinmuxRegs((UInt32) 0x0,
                            (UInt32) CTRL_CORE_PAD_SPI1_CS1,     /* SPI1 */
                            0x6);
    Bsp_platformSetPinmuxRegs((UInt32) 0x0,
                            (UInt32) CTRL_CORE_PAD_SPI1_SCLK,     /* SPI1 */
                            0xC);
    Bsp_platformSetPinmuxRegs((UInt32) 0x0,
                            (UInt32) CTRL_CORE_PAD_SPI1_D0,     /* SPI1 */
                            0xC);
    Bsp_platformSetPinmuxRegs((UInt32) 0x0,
                            (UInt32) CTRL_CORE_PAD_SPI1_D1,     /* SPI1 */
                            0xC);
    Bsp_platformSetPinmuxRegs((UInt32) 0xE,
                            (UInt32) CTRL_CORE_PAD_UART2_CTSN,   /* TDA_GPIO1_16_UART3_SELECTA */
                            0xC);
    Bsp_platformSetPinmuxRegs((UInt32) 0xE,
                            (UInt32) CTRL_CORE_PAD_UART2_RTSN,   /* TDA_GPIO1_17_UART3_SELECTB */
                            0xC);
    Bsp_platformSetPinmuxRegs((UInt32) 0x0,
                            (UInt32) CTRL_CORE_PAD_UART3_RXD,   /* UART3_RXD */
                            0xE);
    Bsp_platformSetPinmuxRegs((UInt32) 0x0,
                            (UInt32) CTRL_CORE_PAD_UART3_TXD,   /* UART3_TXD */
                            0xE);

    if (Bsp_boardGetBaseBoardRev() >= BSP_BOARD_REV_E)
    {
        /* SPI2_AWR2_CS0N */
        Bsp_platformSetPinmuxRegs((UInt32) 0x0,
                                (UInt32) CTRL_CORE_PAD_SPI2_CS0,    /* SPI2 */
                                0x6);
        /* SPI2_AWR2_SCLK */
        Bsp_platformSetPinmuxRegs((UInt32) 0x0,
                                (UInt32) CTRL_CORE_PAD_SPI2_SCLK,   /* SPI2 */
                                0xC);
        /* SPI2_AWR2_MOSI */
        Bsp_platformSetPinmuxRegs((UInt32) 0x0,
                                (UInt32) CTRL_CORE_PAD_SPI2_D0,     /* SPI2 */
                                0xC);
        /* SPI2_AWR2_MISO */
        Bsp_platformSetPinmuxRegs((UInt32) 0x0,
                                (UInt32) CTRL_CORE_PAD_SPI2_D1,     /* SPI2 */
                                0xC);
        /* SPI4_AWR4_CS0N */
        Bsp_platformSetPinmuxRegs((UInt32) 0x1,
                                (UInt32) CTRL_CORE_PAD_MMC3_DAT7,     /* SPI4 */
                                0x6);
        /* SPI4_AWR4_SCLK */
        Bsp_platformSetPinmuxRegs((UInt32) 0x1,
                                (UInt32) CTRL_CORE_PAD_MMC3_DAT4,     /* SPI4 */
                                0xC);
        /* SPI4_AWR4_MOSI */
        Bsp_platformSetPinmuxRegs((UInt32) 0x1,
                                (UInt32) CTRL_CORE_PAD_MMC3_DAT5,     /* SPI4 */
                                0xC);
        /* SPI4_AWR4_MISO */
        Bsp_platformSetPinmuxRegs((UInt32) 0x1,
                                (UInt32) CTRL_CORE_PAD_MMC3_DAT6,     /* SPI4 */
                                0xC);
    }
    else
    {
        Bsp_platformSetPinmuxRegs((UInt32) 0x1,
                                (UInt32) CTRL_CORE_PAD_MMC3_DAT3,     /* SPI3 */
                                0x6);
    }
}

void Bsp_boardTda2xxCascadeVipPadConfig(void)
{
    /* VIN1A */
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN1A_CLK0,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN1A_DE0,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                               (UInt32) CTRL_CORE_PAD_VIN1A_VSYNC0,
                               BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN1A_D0,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN1A_D1,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN1A_D2,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN1A_D3,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN1A_D4,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN1A_D5,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN1A_D6,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN1A_D7,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN1A_D8,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN1A_D9,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN1A_D10,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN1A_D11,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN1A_D12,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN1A_D13,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN1A_D14,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN1A_D15,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    /* VIP2A */
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN2A_CLK0,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN2A_DE0,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN2A_VSYNC0,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN2A_D0,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN2A_D1,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN2A_D2,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN2A_D3,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN2A_D4,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN2A_D5,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN2A_D6,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN2A_D7,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN2A_D8,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN2A_D9,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN2A_D10,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN2A_D11,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN2A_D12,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN2A_D13,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN2A_D14,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 0,
                              (UInt32) CTRL_CORE_PAD_VIN2A_D15,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    /* VIN3A */
    Bsp_platformSetPinmuxRegs((UInt32) 2,
                              (UInt32) CTRL_CORE_PAD_GPMC_CS3,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 2,
                              (UInt32) CTRL_CORE_PAD_GPMC_A10,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 2,
                              (UInt32) CTRL_CORE_PAD_GPMC_A9,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 2,
                              (UInt32) CTRL_CORE_PAD_GPMC_AD0,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 2,
                              (UInt32) CTRL_CORE_PAD_GPMC_AD1,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 2,
                              (UInt32) CTRL_CORE_PAD_GPMC_AD2,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 2,
                              (UInt32) CTRL_CORE_PAD_GPMC_AD3,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 2,
                              (UInt32) CTRL_CORE_PAD_GPMC_AD4,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 2,
                              (UInt32) CTRL_CORE_PAD_GPMC_AD5,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 2,
                              (UInt32) CTRL_CORE_PAD_GPMC_AD6,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 2,
                              (UInt32) CTRL_CORE_PAD_GPMC_AD7,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 2,
                              (UInt32) CTRL_CORE_PAD_GPMC_AD8,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 2,
                              (UInt32) CTRL_CORE_PAD_GPMC_AD9,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 2,
                              (UInt32) CTRL_CORE_PAD_GPMC_AD10,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 2,
                              (UInt32) CTRL_CORE_PAD_GPMC_AD11,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 2,
                              (UInt32) CTRL_CORE_PAD_GPMC_AD12,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 2,
                              (UInt32) CTRL_CORE_PAD_GPMC_AD13,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 2,
                              (UInt32) CTRL_CORE_PAD_GPMC_AD14,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 2,
                              (UInt32) CTRL_CORE_PAD_GPMC_AD15,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    /* VIN4A */
    Bsp_platformSetPinmuxRegs((UInt32) 8,
                              (UInt32) CTRL_CORE_PAD_XREF_CLK2,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 8,
                              (UInt32) CTRL_CORE_PAD_XREF_CLK3,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 8,
                              (UInt32) CTRL_CORE_PAD_GPIO6_15,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 8,
                              (UInt32) CTRL_CORE_PAD_MCASP1_ACLKR,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 8,
                              (UInt32) CTRL_CORE_PAD_MCASP1_FSR,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 8,
                              (UInt32) CTRL_CORE_PAD_MCASP1_AXR2,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 8,
                              (UInt32) CTRL_CORE_PAD_MCASP1_AXR3,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 8,
                              (UInt32) CTRL_CORE_PAD_MCASP1_AXR4,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 8,
                              (UInt32) CTRL_CORE_PAD_MCASP1_AXR5,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 8,
                              (UInt32) CTRL_CORE_PAD_MCASP1_AXR6,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 8,
                              (UInt32) CTRL_CORE_PAD_MCASP1_AXR7,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 8,
                              (UInt32) CTRL_CORE_PAD_MCASP2_ACLKR,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 8,
                              (UInt32) CTRL_CORE_PAD_MCASP2_FSR,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 8,
                              (UInt32) CTRL_CORE_PAD_MCASP2_AXR0,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 8,
                              (UInt32) CTRL_CORE_PAD_MCASP2_AXR1,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 8,
                              (UInt32) CTRL_CORE_PAD_MCASP2_AXR4,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 8,
                              (UInt32) CTRL_CORE_PAD_MCASP2_AXR5,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 8,
                              (UInt32) CTRL_CORE_PAD_MCASP2_AXR6,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs((UInt32) 8,
                              (UInt32) CTRL_CORE_PAD_MCASP2_AXR7,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
}
#endif


