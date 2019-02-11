/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2012-2015
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
 *  \file bsp_boardTda2ex.c
 *
 *  \brief File containing the Tda2ex BSP board functions.
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

#ifdef VPS_CAL_BUILD
#include <ti/drv/vps/include/vps_capture.h>
#endif

#include <ti/drv/vps/include/devices/bsp_device.h>
#include <ti/drv/vps/include/boards/bsp_board.h>
#include <bsp_boardPriv.h>
#include <bsp_boardTda2exDefault.h>
#include <bsp_boardTda2exVision.h>
#include <bsp_boardTda2exJamr3.h>
#include <bsp_boardTda2exMultiDes.h>
#include <bsp_boardTda2exCalDev.h>

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined (SOC_TDA2EX)
#include <ti/csl/hw_types.h>
#include <ti/drv/pm/pmhal.h>
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Max of all the devices present in the board including any valid
 * combination of base board and daughter cards */
#define BOARD_MAX_DEVICE                    (26U)

/*  Base board PCF8575 1 (on I2C1) - mappings
 *  P1_5 - CON_LCD_PWR_DN
 */
#define BOARD_PCF8575_LCDCTRL_POWER_MASK    (PCF8575_P1_5_MASK)

/*  Base board PCF8575 2 (on I2C1) - mappings
 *  P0_4 - SEL_ENET_MUX_S0
 */
#define BOARD_PCF8575_SEL_ENET_MUX_S0       (PCF8575_P0_4_MASK)

/*  Base board PCF8575 3 (on I2C5) - mappings
 *  P0_2 - VIN2_S0
 *  P0_6 - VIN2_S2
 *  P0_7 - SEL_VIN4_MUX_S0
 */
#define BOARD_PCF8575_VIN2_S0               (PCF8575_P0_2_MASK)
#define BOARD_PCF8575_VIN2_S2               (PCF8575_P0_6_MASK)
#define BOARD_PCF8575_SEL_VIN4_MUX_S0       (PCF8575_P0_7_MASK)

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

/* Applicable only for REVC */
#define BOARD_PCF8575_EXVIN2_S2             (PCF8575_P1_2_MASK)
#define BOARD_PCF8575_EXVIN2_S0             (PCF8575_P1_1_MASK)

/* Video mux select for vision daughter card */
#define BOARD_GPIO_BASE_MUX_SEL             ((UInt32) SOC_GPIO1_BASE)
#define BOARD_GPIO_PIN_MUX1_SEL0            ((UInt32) 18U)
#define BOARD_GPIO_PIN_MUX1_SEL1            ((UInt32) 19U)
#define BOARD_GPIO_PIN_MUX2_SEL0            ((UInt32) 20U)
#define BOARD_GPIO_PIN_MUX2_SEL1            ((UInt32) 21U)
#define BOARD_GPIO_BASE_DEMUX_FPD_A         ((UInt32) SOC_GPIO2_BASE)
#define BOARD_GPIO_BASE_DEMUX_FPD_B         ((UInt32) SOC_GPIO1_BASE)
#define BOARD_GPIO_BASE_DEMUX_FPD_C         ((UInt32) SOC_GPIO6_BASE)
#define BOARD_GPIO_PIN_DEMUX_FPD_A          ((UInt32) 29U)
#define BOARD_GPIO_PIN_DEMUX_FPD_B          ((UInt32) 4U)
#define BOARD_GPIO_PIN_DEMUX_FPD_C          ((UInt32) 7U)
#define BOARD_GPIO_BASE_POWER_DWN           ((UInt32) SOC_GPIO6_BASE)
#define BOARD_GPIO_PIN_OV_PWDN              ((UInt32) 17U)

#if defined (BOARD_TYPE_TDA2EX_ETH_SRV)
#define BOARD_GPIO_BASE_ETHCAM_POWER_DWN           ((uint32_t) SOC_GPIO7_BASE)
#define BOARD_GPIO_PIN_ETHCAM_PWDN              ((uint32_t) 1U)
#endif
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
    UInt32 emif1Size;
    UInt32 emif2Size;
    Char   reserved[20U];
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

static Int32 Bsp_boardPowerOnDeviceTda2ex(UInt32 devDrvId,
                                          UInt32 instId,
                                          UInt32 powerOn);
static Int32 Bsp_boardSelectDeviceTda2ex(UInt32 devDrvId, UInt32 instId);
static Int32 Bsp_boardSelectDeviceTda2exVision(UInt32 devDrvId, UInt32 instId);
static Int32 Bsp_boardSelectDeviceTda2exJamr3(UInt32 devDrvId, UInt32 instId);
static Int32 Bsp_boardSelectDeviceTda2exMultiDes(UInt32 devDrvId,
                                                 UInt32 instId);
static Int32 Bsp_boardTda2xxEnableMmc1(void);
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined (SOC_TDA2EX)
static Int32 Bsp_boardTda2xxMmcsdLdoPwr(void);
#endif
#if defined (BOARD_TYPE_TDA2EX_ETH_SRV)
static Int32 Bsp_boardTDA2exEthSrvPinMuxInit();
#endif

#ifdef __cplusplus
}
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static Bsp_BoardI2cInstData gBoardTda2exI2cInstData[] =
{
#ifndef BSP_DISABLE_I2C0
    {
        BSP_DEVICE_I2C_INST_ID_0,           /* instId */
        SOC_I2C1_BASE,                      /* baseAddr */
        CSL_INTC_EVENTID_I2CINT1,           /* intNum */
        400U                                /* busClkKHz */
    },
#endif
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined (SOC_TDA2EX)
#if defined (BOARD_TYPE_TDA2EX_ETH_SRV)
#ifndef BSP_DISABLE_I2C2
    {
        BSP_DEVICE_I2C_INST_ID_2,           /* instId */
        SOC_I2C3_BASE,                      /* baseAddr */
        CSL_INTC_EVENTID_I2CINT3,           /* intNum */
        400U                                /* busClkKHz */
    },
#endif
#endif
#ifndef BSP_DISABLE_I2C3
    {
        BSP_DEVICE_I2C_INST_ID_3,           /* instId */
        SOC_I2C4_BASE,                      /* baseAddr */
        CSL_INTC_EVENTID_I2CINT4,           /* intNum */
        400U                                /* busClkKHz */
    },
#endif  /* #ifndef BSP_DISABLE_I2C3 */
    {
        BSP_DEVICE_I2C_INST_ID_4,           /* instId */
        SOC_I2C5_BASE,                      /* baseAddr */
        CSL_INTC_EVENTID_I2CINT5,           /* intNum */
        400U                                /* busClkKHz */
    }
#endif
};

static Bsp_BoardI2cData     gBoardTda2exI2cData =
{
    /* numI2c */
    (sizeof (gBoardTda2exI2cInstData) / sizeof (Bsp_BoardI2cInstData)),
    /* i2cData */
    gBoardTda2exI2cInstData,
    /* probeInstId */
    BSP_DEVICE_I2C_INST_ID_4,
};

static Bsp_BoardDeviceData  gBoardTda2exDevData[BOARD_MAX_DEVICE];

static Bsp_BoardData        gBoardTda2exData =
{
    /* numDev */
    0U,
    /* devData */
    &gBoardTda2exDevData[0U],
};

static Bsp_BoardData        gBoardTda2exCustomData =
{
    0U,                                     /* numDev */
    NULL,                                   /* devData */
};

static Bsp_BoardDeviceData  gBoardTda2exDefaultDevData[] =
    BSP_BOARD_TDA2EX_DEFAULT_DEVDATA;

static Bsp_BoardDeviceData  gBoardTda2exVisionDevData[] =
    BSP_BOARD_TDA2EX_VISION_DEVDATA;

static Bsp_BoardDeviceData  gBoardTda2exJamr3DevData[] =
    BSP_BOARD_TDA2EX_JAMR3_DEVDATA;

static Bsp_BoardDeviceData  gBoardTda2exMultiDesDevDataRevA[] =
    BSP_BOARD_TDA2EX_MULTIDES_DEVDATA_REVA;

static Bsp_BoardDeviceData  gBoardTda2exMultiDesDevDataRevC[] =
    BSP_BOARD_TDA2EX_MULTIDES_DEVDATA_REVC;

static Bsp_BoardDeviceData  gBoardTda2exCalDevData[] =
    BSP_BOARD_TDA2EX_CAL_UB960_OV10635_DEVDATA;

static Bsp_BoardData        gBoardTda2exDefaultData =
{
    /* numDev */
    (sizeof (gBoardTda2exDefaultDevData) / sizeof (Bsp_BoardDeviceData)),
    /* devData */
    gBoardTda2exDefaultDevData,
};

static Bsp_BoardData        gBoardTda2exVisionData =
{
    /* numDev */
    (sizeof (gBoardTda2exVisionDevData) / sizeof (Bsp_BoardDeviceData)),
    /* devData */
    gBoardTda2exVisionDevData,
};

static Bsp_BoardData        gBoardTda2exJamr3Data =
{
    /* numDev */
    (sizeof (gBoardTda2exJamr3DevData) / sizeof (Bsp_BoardDeviceData)),
    /* devData */
    gBoardTda2exJamr3DevData,
};

static Bsp_BoardData        gBoardTda2exMultiDesDataRevA =
{
    /* numDev */
    (sizeof (gBoardTda2exMultiDesDevDataRevA) / sizeof (Bsp_BoardDeviceData)),
    /* devData */
    gBoardTda2exMultiDesDevDataRevA,
};

static Bsp_BoardData        gBoardTda2exMultiDesDataRevC =
{
    /* numDev */
    (sizeof (gBoardTda2exMultiDesDevDataRevC) / sizeof (Bsp_BoardDeviceData)),
    /* devData */
    gBoardTda2exMultiDesDevDataRevC,
};

static Bsp_BoardData        gBoardTda2exCalDevicesData =
{
    /* numDev */
    (sizeof (gBoardTda2exCalDevData) / sizeof (Bsp_BoardDeviceData)),
    /* devData */
    gBoardTda2exCalDevData,
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

Int32 Bsp_boardTda2exInit(void)
{
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined (SOC_TDA2EX)
    /* Enable GPIO required for video mux as output */
    GPIOModuleEnable(BOARD_GPIO_BASE_POWER_DWN);
    GPIODirModeSet(
        BOARD_GPIO_BASE_POWER_DWN,
        BOARD_GPIO_PIN_OV_PWDN,
        GPIO_DIR_OUTPUT);
    /* In case of TDA2Ex REV A and REV B boards and TDA2Ex 17X17 Evm the
     * software control of the video mux selection is not availbale.
     * To detect the board revision the I2C should be enabled. I2C is enabled
     * only in Bsp_platformInit(), which is called after this function.
     * At this point board rev cant be detected.
     * The below code enabled the internal GPIO modules. It doesnot effect
     * the signals going outside SOC, as the corresponding pin muixes are not
     * done. This is specific to TI EVMs and this code would be modified for
     * customer board accordingly.
     */
    GPIOModuleEnable(BOARD_GPIO_BASE_MUX_SEL);
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

#if defined (BOARD_TYPE_TDA2EX_ETH_SRV)
    GPIOModuleEnable(BOARD_GPIO_BASE_ETHCAM_POWER_DWN);
    Bsp_boardTDA2exEthSrvPinMuxInit();
#endif

#endif

    return (BSP_SOK);
}

#if defined (BOARD_TYPE_TDA2EX_ETH_SRV)
static Int32 Bsp_boardTDA2exEthSrvPinMuxInit()
{
    /* TDA2Ex AVB BB
    * GPIO_2_0, PWDN Ethernet Phy U21
    */
    Bsp_platformSetPinmuxRegs(
        (UInt32) 14U,
        (UInt32) CTRL_CORE_PAD_GPMC_A10,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);

    GPIODirModeSet(SOC_GPIO2_BASE,0,GPIO_DIR_OUTPUT);
    GPIOPinWrite(SOC_GPIO2_BASE,0,1);

    /* GPIO_5_19, RESETn for Ethernet Phy U21 */
    Bsp_platformSetPinmuxRegs(
        (UInt32) 14U,
        (UInt32) CTRL_CORE_PAD_UART3_TXD,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    /* Toggle reset on Ethernet PHY */
    GPIODirModeSet(SOC_GPIO5_BASE,19,GPIO_DIR_OUTPUT);
    GPIOPinWrite(SOC_GPIO5_BASE,19,1);
    BspOsal_sleep(100);
    GPIOPinWrite(SOC_GPIO5_BASE,19,0);
    BspOsal_sleep(100);
    GPIOPinWrite(SOC_GPIO5_BASE,19,1);

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

    /* GPIO_6_10, RESETn for MV_RESETn */
    Bsp_platformSetPinmuxRegs(
           (UInt32) 0U,
           (UInt32) CTRL_CORE_PAD_GPIO6_10,
           BSP_PLATFORM_IOPAD_CFG_DEFAULT);

    GPIODirModeSet(SOC_GPIO6_BASE,10,GPIO_DIR_OUTPUT);
    GPIOPinWrite(SOC_GPIO6_BASE,10,0);
    BspOsal_sleep(10);
    GPIOPinWrite(SOC_GPIO6_BASE,10,1);

    /* Hot Plug Detect with internal pullup so it is always on */
    Bsp_platformSetPinmuxRegs(
           (UInt32) 0x6,
           (UInt32) CTRL_CORE_PAD_SPI1_CS2,
           BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_UP);

    /* Swaps HDMI output polarity */
    UInt32* HDMI_PHY_PAD_CONFIG_CONTROL = (UInt32*) 0x5804030C;
    *HDMI_PHY_PAD_CONFIG_CONTROL |= 0x78000000;

    /* GPIO7_27 for LED D1 */
    Bsp_platformSetPinmuxRegs(
           (UInt32) 14U,
           (UInt32) CTRL_CORE_PAD_UART2_TXD,
           BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    GPIODirModeSet(SOC_GPIO7_BASE,27,GPIO_DIR_OUTPUT);
    GPIOPinWrite(SOC_GPIO7_BASE,27,1);  /* initial state high witch is OFF */

    /* GPIO6_11 for Camera Power Enable */
    Bsp_platformSetPinmuxRegs(
           (UInt32) 0U,
           (UInt32) CTRL_CORE_PAD_GPIO6_11,
           BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    GPIODirModeSet(SOC_GPIO6_BASE,11,GPIO_DIR_OUTPUT);
    GPIOPinWrite(SOC_GPIO6_BASE,11,1);  /* initial state high witch is ON */

    /* GPIO7_1 Camera Power High side switches - pin 57 on J1, ball AC9 */
    Bsp_platformSetPinmuxRegs(
           (UInt32) 14U,
           (UInt32) CTRL_CORE_PAD_MMC3_DAT2,
           BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    GPIODirModeSet(SOC_GPIO7_BASE,1,GPIO_DIR_OUTPUT);
    GPIOPinWrite(SOC_GPIO7_BASE,1,1);  /* initial state high witch is ON */
    /* GPIO1_22 Cam 1 Low side switch - pin 55, ball AC8 */
    Bsp_platformSetPinmuxRegs(
           (UInt32) 14U,
           (UInt32) CTRL_CORE_PAD_MMC3_DAT4,
           BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    GPIODirModeSet(SOC_GPIO1_BASE,22,GPIO_DIR_OUTPUT);
    GPIOPinWrite(SOC_GPIO1_BASE,22,1);  /* initial state high witch is ON */
    /* GPIO1_23 Cam 2 Low side switch - pin 56, ball AD6 */
    Bsp_platformSetPinmuxRegs(
           (UInt32) 14U,
           (UInt32) CTRL_CORE_PAD_MMC3_DAT5,
           BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    GPIODirModeSet(SOC_GPIO1_BASE,23,GPIO_DIR_OUTPUT);
    GPIOPinWrite(SOC_GPIO1_BASE,23,1);  /* initial state high witch is ON */
    /* GPIO1_24 Cam 3 Low side switch - pin 72, ball AB8 */
    Bsp_platformSetPinmuxRegs(
           (UInt32) 14U,
           (UInt32) CTRL_CORE_PAD_MMC3_DAT6,
           BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    GPIODirModeSet(SOC_GPIO1_BASE,24,GPIO_DIR_OUTPUT);
    GPIOPinWrite(SOC_GPIO1_BASE,24,1);  /* initial state high witch is ON */
    /* GPIO1_25 Cam 4 Low side switch - pin 71, ball AB5 */
    Bsp_platformSetPinmuxRegs(
           (UInt32) 14U,
           (UInt32) CTRL_CORE_PAD_MMC3_DAT7,
           BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    GPIODirModeSet(SOC_GPIO1_BASE,25,GPIO_DIR_OUTPUT);
    GPIOPinWrite(SOC_GPIO1_BASE,25,1);  /* initial state high witch is ON */
    /* GPIO7_2 CAM_HS_DIAG - pin 58, ball AC3 */
    /* pull down input */
    Bsp_platformSetPinmuxRegs(
           (UInt32) 14U,
           (UInt32) CTRL_CORE_PAD_MMC3_DAT3,
            (BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_ENABLE |
             BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN));
    GPIODirModeSet(SOC_GPIO7_BASE,2,GPIO_DIR_INPUT);
    /* I2C2 pinmux */
    Bsp_platformSetPinmuxRegs(
        (UInt32) 10,
        (UInt32) CTRL_CORE_PAD_MCASP1_ACLKX,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    Bsp_platformSetPinmuxRegs(
        (UInt32) 10,
        (UInt32) CTRL_CORE_PAD_MCASP1_FSX,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);

    return (0);
}
#endif

Bsp_BoardId Bsp_boardGetIdTda2ex(void)
{
    Bsp_BoardId boardId = BSP_BOARD_UNKNOWN;
#if defined (BOARD_TYPE_TDA2EX_ETH_SRV)
    boardId = BSP_BOARD_BASE_TDA2EX;
#else
#if defined (PLATFORM_ZEBU) || defined (PLATFORM_VIRTIO)
    boardId = BSP_BOARD_VISION;
#else
    Int32       retVal;
    const Bsp_BoardI2cData *i2cData;

    i2cData = Bsp_boardGetI2cData();
    GT_assert(BspBoardTrace, (i2cData != NULL));

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
         * TDA2EX base board (REV A/B).
         * Note: This should be the last check as base board is
         * present by default even when daughter card is present.
         */
        retVal = Bsp_deviceI2cProbeDevice(
            BSP_DEVICE_I2C_INST_ID_0,
            BOARD_EEPROM_I2C_ADDR_1);
        if (FVID2_SOK == retVal)
        {
            /* Default to vision board when base board is detected.
             * This is required because in some of the vision
             * boards, SII9127 HDMI is not populated. And hence even if
             * vision board is connected, we detect as base board */
            boardId = BSP_BOARD_VISION;
        }
    }

    if (FVID2_SOK != retVal)
    {
        /*
         * Probe for EEPROM @ 0x50 address to detect
         * TDA2EX base board (REV C and above).
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
#endif  /* #ifndef BSP_DISABLE_I2C0 */
#endif  /* #if defined (PLATFORM_ZEBU) || defined (PLATFORM_VIRTIO) */
#endif  /* #if defined (BOARD_TYPE_TDA2EX_ETH_SRV) */

    return (boardId);
}

Bsp_BoardRev Bsp_boardGetBaseBoardRevTda2ex(void)
{
    Bsp_BoardRev      boardRev = BSP_BOARD_REV_C;

#if defined (BOARD_TYPE_TDA2EX_ETH_SRV)
    boardRev = BSP_BOARD_REV_A;
#else
#ifndef BSP_DISABLE_I2C0
    Int32             retVal;
    UInt8             regValue[2];
    UInt32            i2cInst, eepromAddr, page, pageSize, delay, numRegs;
    Bsp_BoardEepromId eepromVal;
    void             *pEepromVal = &eepromVal;

    i2cInst    = BSP_DEVICE_I2C_INST_ID_0;
    eepromAddr = (UInt32) BOARD_EEPROM_I2C_ADDR_0;

    retVal = Bsp_deviceI2cProbeDevice(
        i2cInst,
        BOARD_EEPROM_I2C_ADDR_0);
    if (FVID2_SOK != retVal)
    {
        /* No slave detected at 0x51, baord is REV A or REV B */
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
        (UInt8 *) pEepromVal,
        pageSize);
    if ((FVID2_SOK == retVal) &&
        (eepromVal.header == 0xAA5533EEU))
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
        /* For J6 Entry board the intial board revision is A. But the board is
         * compitable with the J6Eco Rev C Evm. So software will initialize
         * J6 Entry board revision to C and used everywhere in this file.
         */
        if ((Bsp_platformGetPackageType() == BSP_PLATFORM_PACKAGE_TYPE_17x17) &&
            (boardRev < BSP_BOARD_REV_C))
        {
            boardRev = BSP_BOARD_REV_C;
        }

        if (BSP_BOARD_REV_C <= boardRev)
        {
            GT_1trace(BspBoardTrace, GT_INFO,
                      " EEPROM Base Board EMIF1 Size: %u MB\r\n",
                      eepromVal.emif1Size / (1024U * 1024U));
            GT_1trace(BspBoardTrace, GT_INFO,
                      " EEPROM Base Board EMIF2 Size: %u MB\r\n",
                      eepromVal.emif2Size / (1024U * 1024U));
        }
    }
    else
    {
        GT_0trace(BspBoardTrace, GT_ERR, "EEPROM read failed!!\r\n");
    }
#endif
#endif

    return (boardRev);
}

Bsp_BoardRev Bsp_boardGetDcRevTda2ex(void)
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

const Bsp_BoardI2cData *Bsp_boardGetI2cDataTda2ex(void)
{
    return (&gBoardTda2exI2cData);
}

const Bsp_BoardData *Bsp_boardGetDataTda2ex(void)
{
    UInt32               numDev;
    Bsp_BoardId          boardId;
    Bsp_BoardData       *boardData;
    Bsp_BoardDeviceData *tempDevData;
    Bsp_BoardRev         boardRev;

    boardRev  = Bsp_boardGetBaseBoardRev();
    boardId   = Bsp_boardGetId();
    boardData = &gBoardTda2exData;

    /* Copy only for the first time */
    if (0U == boardData->numDev)
    {
        /* Copy the individual board data to global board data as per
         * hierarchy */
        numDev      = 0U;
        tempDevData = &gBoardTda2exDevData[0U];
        switch (boardId)
        {
            case BSP_BOARD_BASE_TDA2EX:
                numDev += gBoardTda2exDefaultData.numDev;
                numDev += gBoardTda2exCalDevicesData.numDev;
                /* Array bound check */
                GT_assert(BspBoardTrace, numDev < BOARD_MAX_DEVICE);
                BspUtils_memcpy(
                    tempDevData,
                    gBoardTda2exDefaultData.devData,
                    (sizeof (Bsp_BoardDeviceData) *
                     gBoardTda2exDefaultData.numDev));
                tempDevData += gBoardTda2exDefaultData.numDev;

                BspUtils_memcpy(
                    tempDevData,
                    gBoardTda2exCalDevicesData.devData,
                    (sizeof (Bsp_BoardDeviceData) *
                     gBoardTda2exCalDevicesData.numDev));
                tempDevData += gBoardTda2exCalDevicesData.numDev;
                break;

            case BSP_BOARD_VISION:
                numDev += gBoardTda2exDefaultData.numDev;
                numDev += gBoardTda2exVisionData.numDev;
                numDev += gBoardTda2exCalDevicesData.numDev;
                /* Array bound check */
                GT_assert(BspBoardTrace, numDev < BOARD_MAX_DEVICE);
                BspUtils_memcpy(
                    tempDevData,
                    gBoardTda2exDefaultData.devData,
                    (sizeof (Bsp_BoardDeviceData) *
                     gBoardTda2exDefaultData.numDev));
                tempDevData += gBoardTda2exDefaultData.numDev;
                BspUtils_memcpy(
                    tempDevData,
                    gBoardTda2exVisionData.devData,
                    (sizeof (Bsp_BoardDeviceData) *
                     gBoardTda2exVisionData.numDev));
                tempDevData += gBoardTda2exVisionData.numDev;
                BspUtils_memcpy(
                    tempDevData,
                    gBoardTda2exCalDevicesData.devData,
                    (sizeof (Bsp_BoardDeviceData) *
                     gBoardTda2exCalDevicesData.numDev));
                tempDevData += gBoardTda2exCalDevicesData.numDev;
                break;

            case BSP_BOARD_JAMR3:
                numDev += gBoardTda2exDefaultData.numDev;
                numDev += gBoardTda2exJamr3Data.numDev;
                numDev += gBoardTda2exCalDevicesData.numDev;
                /* Array bound check */
                GT_assert(BspBoardTrace, numDev < BOARD_MAX_DEVICE);
                BspUtils_memcpy(
                    tempDevData,
                    gBoardTda2exDefaultData.devData,
                    (sizeof (Bsp_BoardDeviceData) *
                     gBoardTda2exDefaultData.numDev));
                tempDevData += gBoardTda2exDefaultData.numDev;
                BspUtils_memcpy(
                    tempDevData,
                    gBoardTda2exJamr3Data.devData,
                    (sizeof (Bsp_BoardDeviceData) *
                     gBoardTda2exJamr3Data.numDev));
                tempDevData += gBoardTda2exJamr3Data.numDev;
                BspUtils_memcpy(
                    tempDevData,
                    gBoardTda2exCalDevicesData.devData,
                    (sizeof (Bsp_BoardDeviceData) *
                     gBoardTda2exCalDevicesData.numDev));
                tempDevData += gBoardTda2exCalDevicesData.numDev;
                break;

            case BSP_BOARD_MULTIDES:
                numDev += gBoardTda2exDefaultData.numDev;
                numDev += gBoardTda2exVisionData.numDev;
                numDev += gBoardTda2exCalDevicesData.numDev;
                if ((BSP_BOARD_REV_A == boardRev) ||
                    (BSP_BOARD_REV_B == boardRev))
                {
                    numDev += gBoardTda2exMultiDesDataRevA.numDev;
                }
                else
                {
                    numDev += gBoardTda2exMultiDesDataRevC.numDev;
                }
                /* Array bound check */
                GT_assert(BspBoardTrace, numDev < BOARD_MAX_DEVICE);
                BspUtils_memcpy(
                    tempDevData,
                    gBoardTda2exDefaultData.devData,
                    (sizeof (Bsp_BoardDeviceData) *
                     gBoardTda2exDefaultData.numDev));
                tempDevData += gBoardTda2exDefaultData.numDev;
                BspUtils_memcpy(
                    tempDevData,
                    gBoardTda2exVisionData.devData,
                    (sizeof (Bsp_BoardDeviceData) *
                     gBoardTda2exVisionData.numDev));
                tempDevData += gBoardTda2exVisionData.numDev;
                if ((BSP_BOARD_REV_A == boardRev) ||
                    (BSP_BOARD_REV_B == boardRev))
                {
                    BspUtils_memcpy(
                        tempDevData,
                        gBoardTda2exMultiDesDataRevA.devData,
                        (sizeof (Bsp_BoardDeviceData) *
                         gBoardTda2exMultiDesDataRevA.numDev));
                    tempDevData += gBoardTda2exMultiDesDataRevA.numDev;
                }
                else
                {
                    BspUtils_memcpy(
                        tempDevData,
                        gBoardTda2exMultiDesDataRevC.devData,
                        (sizeof (Bsp_BoardDeviceData) *
                         gBoardTda2exMultiDesDataRevC.numDev));
                    tempDevData += gBoardTda2exMultiDesDataRevC.numDev;
                }
                BspUtils_memcpy(
                    tempDevData,
                    gBoardTda2exCalDevicesData.devData,
                    (sizeof (Bsp_BoardDeviceData) *
                     gBoardTda2exCalDevicesData.numDev));
                tempDevData += gBoardTda2exCalDevicesData.numDev;
                break;

            case BSP_BOARD_CUSTOM:
                numDev += gBoardTda2exCustomData.numDev;
                /* Array bound check */
                GT_assert(BspBoardTrace, numDev < BOARD_MAX_DEVICE);
                BspUtils_memcpy(
                    tempDevData,
                    gBoardTda2exCustomData.devData,
                    (sizeof (Bsp_BoardDeviceData) *
                     gBoardTda2exCustomData.numDev));
                tempDevData += gBoardTda2exDefaultData.numDev;
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
static Int32 Bsp_boardSelectDeviceTda2ex(UInt32 devDrvId, UInt32 instId)
{
    Int32        retVal = BSP_SOK;

#if !defined (BOARD_TYPE_TDA2EX_ETH_SRV)
    UInt8        regValue[2], regValue1[2];
    UInt32       i2cInst, i2cInst1, ioExpAddr, ioExpAddr1, numRegs, numRegs1;
    const Bsp_BoardI2cData *i2cData;
    UInt32       regValueTemp, regValueTemp1;
    Bsp_BoardRev boardRev;


    boardRev = Bsp_boardGetBaseBoardRev();
    i2cData  = Bsp_boardGetI2cData();
    GT_assert(BspBoardTrace, (i2cData != NULL));

    /*
     * Select base EVM leapord imaging sensor or daughter card input for
     * VIN2 signals.
     *
     * VIN2_S0,VIN2_S2 = 10 for base EVM input from leapord imaging sensor.
     * VIN2_S0,VIN2_S2 = 01 for input from daughter card.
     */
    if ((FVID2_VID_SENSOR_OV1063X_DRV == devDrvId) ||
        (FVID2_VID_SENSOR_LI_OV1063X_DRV == devDrvId) ||
        (FVID2_VID_SENSOR_MULDES_OV1063X_DRV == devDrvId) ||
        (FVID2_VID_SENSOR_APT_AR0132_DRV == devDrvId) ||
        (FVID2_VID_DEC_SII9127_DRV == devDrvId) ||
        (FVID2_VID_DEC_ADV7611_DRV == devDrvId) ||
        (FVID2_VID_DEC_TVP5158_DRV == devDrvId) ||
        (BSP_DRV_ID_ENET_PHY_DP83865 == devDrvId))
    {
        i2cInst   = BSP_DEVICE_I2C_INST_ID_4;
        ioExpAddr = BOARD_IO_EXP_I2C_ADDR_6;
        numRegs   = 2U;
        retVal    = Bsp_deviceRawRead8(i2cInst, ioExpAddr, regValue, numRegs);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspBoardTrace, GT_ERR, "I2C read failed!!\r\n");
        }
        else
        {
            /* Configure muxes */
            if (BSP_DRV_ID_ENET_PHY_DP83865 == devDrvId)
            {
                i2cInst1   = BSP_DEVICE_I2C_INST_ID_0;
                ioExpAddr1 = BOARD_IO_EXP_I2C_ADDR_1;
                numRegs1   = 2U;
                retVal     = Bsp_deviceRawRead8(
                    i2cInst1,
                    ioExpAddr1,
                    regValue1,
                    numRegs1);
                if (FVID2_SOK != retVal)
                {
                    GT_0trace(BspBoardTrace, GT_ERR, "I2C read failed!!\r\n");
                }
                else
                {
                    if (BSP_DEVICE_ENET_PHY_DP83865_INST_ID_1 == instId)
                    {
                        if ((BSP_BOARD_REV_A == boardRev) ||
                            (BSP_BOARD_REV_B == boardRev))
                        {
                            /* ENET: VIN2_S2=1,VIN2_S0=1 */
                            regValueTemp =
                                ((UInt32) regValue[0U] | BOARD_PCF8575_VIN2_S0);
                            regValue[0U] = (UInt8) regValueTemp;
                            regValueTemp =
                                ((UInt32) regValue[0U] | BOARD_PCF8575_VIN2_S2);
                            regValue[0U] = (UInt8) regValueTemp;

                            /* ENET: SEL_ENET_MUX_S0=1 */
                            regValueTemp1 = ((UInt32) regValue1[0U] |
                                             BOARD_PCF8575_SEL_ENET_MUX_S0);
                            regValue1[0U] = (UInt8) regValueTemp1;
                        }
                        else
                        {
                            /* ENET: EXVIN2_S2=1,EXVIN2_S0=1 */
                            regValueTemp =
                                ((UInt32) regValue[1U] &
                                 ((UInt32) (~BOARD_PCF8575_EXVIN2_S0)) &
                                 ((UInt32) (~BOARD_PCF8575_EXVIN2_S2)));
                            regValue[1U] = (UInt8) regValueTemp;
                            regValueTemp = ((UInt32) (regValue[1U] |
                                                      BOARD_PCF8575_EXVIN2_S2 |
                                                      BOARD_PCF8575_EXVIN2_S0));
                            regValue[1U] = (UInt8) regValueTemp;
                        }
                    }
                    else
                    {
                        if ((BSP_BOARD_REV_A == boardRev) ||
                            (BSP_BOARD_REV_B == boardRev))
                        {
                            /* When user want to use port 0, we are
                             * routing EMAC[1] signal coming from the ENET
                             * phy to EMAC[0] pads using the SEL_ENET_MUX_S0
                             * signal. In this case the video muxes are not
                             * used and hence not changed */
                            /* ENET: SEL_ENET_MUX_S0=0 */
                            regValueTemp1 =
                                ((UInt32) regValue1[0U] &
                                 ((UInt32) (~BOARD_PCF8575_SEL_ENET_MUX_S0)));
                            regValue1[0U] = (UInt8) regValueTemp1;
                        }
                        else
                        {
                            /* ENET: SEL_ENET_MUX_S0=1 */
                            regValueTemp1 =
                                ((UInt32) regValue1[0U] &
                                 ((UInt32) (~BOARD_PCF8575_SEL_ENET_MUX_S0)));
                            regValueTemp1 = ((UInt32) regValueTemp1 |
                                             BOARD_PCF8575_SEL_ENET_MUX_S0);
                            regValue1[0U] = (UInt8) regValueTemp1;
                        }
                    }

                    retVal += Bsp_deviceRawWrite8(
                        i2cInst1,
                        ioExpAddr1,
                        regValue1,
                        numRegs1);
                    if (FVID2_SOK != retVal)
                    {
                        GT_0trace(BspBoardTrace, GT_ERR,
                                  "I2C write failed!!\r\n");
                    }
                }
            }
            else
            {
                if ((FVID2_VID_SENSOR_LI_OV1063X_DRV == devDrvId) &&
                    (BSP_DEVICE_LI_OV1063X_INST_ID_0 == instId))
                {
                    /* CAM: VIN2_S2=0,VIN2_S0=1 */
                    regValueTemp =
                        ((UInt32) regValue[0U] &
                         ((UInt32) (~BOARD_PCF8575_VIN2_S2)));
                    regValue[0U] = (UInt8) regValueTemp;
                    regValueTemp = ((UInt32) regValue[0U] |
                                    BOARD_PCF8575_VIN2_S0);
                    regValue[0U] = (UInt8) regValueTemp;
                }
                else
                {
                    /* VIN2: VIN2_S2=1,VIN2_S0=0 */
                    regValueTemp = ((UInt32) regValue[0U] |
                                    BOARD_PCF8575_VIN2_S2);
                    regValue[0U] = (UInt8) regValueTemp;
                    regValueTemp =
                        ((UInt32) regValue[0U] &
                         ((UInt32) (~BOARD_PCF8575_VIN2_S0)));
                    regValue[0U] = (UInt8) regValueTemp;
                    if ((boardRev >= BSP_BOARD_REV_C) &&
                        ((FVID2_VID_DEC_SII9127_DRV == devDrvId) ||
                         (FVID2_VID_DEC_ADV7611_DRV == devDrvId)))
                    {
                        /* VIN2: EXVIN2_S2=1,EXVIN2_S0=0 */
                        regValueTemp =
                            ((UInt32) regValue[1U] &
                             ((UInt32) (~BOARD_PCF8575_EXVIN2_S0)) &
                             ((UInt32) (~BOARD_PCF8575_EXVIN2_S2)));
                        regValue[1U] = (UInt8) regValueTemp;
                        regValueTemp =
                            ((UInt32) (regValue[1U] | BOARD_PCF8575_EXVIN2_S2));
                        regValue[1U] = (UInt8) regValueTemp;
                    }
                }

                if (((FVID2_VID_SENSOR_MULDES_OV1063X_DRV == devDrvId) ||
                     (FVID2_VID_DEC_SII9127_DRV == devDrvId) ||
                     (FVID2_VID_DEC_ADV7611_DRV == devDrvId))
                    && (BSP_BOARD_REV_C <= boardRev))
                {
#ifndef BSP_DISABLE_I2C0
                    /* Select VIN1; this also selects GIP control signals */
                    i2cInst1   = BSP_DEVICE_I2C_INST_ID_0;
                    ioExpAddr1 = BOARD_IO_EXP_I2C_ADDR_1;
                    numRegs1   = 2U;
                    retVal     = Bsp_deviceRawRead8(
                        i2cInst1,
                        ioExpAddr1,
                        regValue1,
                        numRegs1);
                    if (FVID2_SOK != retVal)
                    {
                        GT_0trace(BspBoardTrace, GT_ERR,
                                  "I2C read failed!!\r\n");
                    }

                    /* Bits P0 and P7 should be set to '1' and '0' */
                    regValueTemp1 =
                        ((UInt32) regValue1[0U] &
                         ((UInt32) (~PCF8575_P0_0_MASK)) &
                         ((UInt32) (~PCF8575_P0_7_MASK)));
                    regValue1[0U] = (UInt8) regValueTemp1;
                    regValueTemp1 =
                        ((UInt32) (regValue1[0U] | PCF8575_P0_0_MASK));
                    regValue1[0U] = (UInt8) regValueTemp1;
                    if (FVID2_VID_SENSOR_MULDES_OV1063X_DRV == devDrvId)
                    {
                        if ((BSP_DEVICE_MULDES_OV1063X_INST_ID_5 == instId) ||
                            (BSP_DEVICE_MULDES_OV1063X_INST_ID_2 == instId))
                        {
                            if (BSP_DEVICE_MULDES_OV1063X_INST_ID_2 == instId)
                            {
                                /* This automatically gets selected above */
                            }
                            else
                            {
                                /* Set P4 bit to '0' */
                                regValueTemp1 =
                                    ((UInt32) regValue1[0U] &
                                     ((UInt32) (~PCF8575_P0_4_MASK)));
                                regValue1[0U] = (UInt8) regValueTemp1;
                            }
                        }

                        if (BSP_DEVICE_MULDES_OV1063X_INST_ID_1 == instId)
                        {
                            /* Bits P2 and P6 should be set to '0' and '1' */
                            regValueTemp =
                                ((UInt32) regValue[0U] &
                                 ((UInt32) (~PCF8575_P0_2_MASK)) &
                                 ((UInt32) (~PCF8575_P0_6_MASK)));
                            regValue[0U] = (UInt8) regValueTemp;
                            regValueTemp =
                                ((UInt32) regValue[0U] | PCF8575_P0_6_MASK);
                            regValue[0U] = (UInt8) regValueTemp;
                        }

                        if (BSP_DEVICE_MULDES_OV1063X_INST_ID_4 == instId)
                        {
                            /* Set P13 bit to '0' */
                            regValueTemp =
                                ((UInt32) regValue[1U] &
                                 ((UInt32) (~PCF8575_P1_3_MASK)));
                            regValue[1U] = (UInt8) regValueTemp;
                        }
                    }
                    retVal += Bsp_deviceRawWrite8(
                        i2cInst1,
                        ioExpAddr1,
                        regValue1,
                        numRegs1);
                    if (FVID2_SOK != retVal)
                    {
                        GT_0trace(BspBoardTrace, GT_ERR,
                                  "I2C write failed!!\r\n");
                    }
#endif
                }
            }
        }

        if (BSP_DRV_ID_ENET_PHY_DP83865 == devDrvId)
        {
            /* SEL_VIN4_MUX_S0 should be 1 for ENET MDIO signals */
            regValueTemp =
                ((UInt32) regValue[0U] | BOARD_PCF8575_SEL_VIN4_MUX_S0);
            regValue[0U] = (UInt8) regValueTemp;
        }
        else
        {
            if ((FVID2_VID_SENSOR_MULDES_OV1063X_DRV == devDrvId) &&
                (BSP_DEVICE_MULDES_OV1063X_INST_ID_4 == instId))
            {
                /* SEL_VIN4_MUX_S0 should be 0 for VIN1B */
                regValueTemp =
                    ((UInt32) regValue[0U] &
                     ((UInt32) (~BOARD_PCF8575_SEL_VIN4_MUX_S0)));
                regValue[0U] = (UInt8) regValueTemp;
            }
        }

        retVal += Bsp_deviceRawWrite8(i2cInst, ioExpAddr, regValue, numRegs);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspBoardTrace, GT_ERR, "I2C write failed!!\r\n");
        }
    }
    if (FVID2_LCD_CTRL_DRV == devDrvId)
    {
        if (instId == (UInt32)0x01U)
        {
            i2cInst   = BSP_DEVICE_I2C_INST_ID_0;
            ioExpAddr = BOARD_IO_EXP_I2C_ADDR_1;
            numRegs   = 2U;
            retVal    = Bsp_deviceRawRead8(i2cInst, ioExpAddr, regValue,
                                           numRegs);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(BspBoardTrace, GT_ERR, "I2C read failed!!\r\n");
            }
            /* io expander 2 (0x21) P0 set to '0' and P7 set to '1' */
            regValueTemp = ((UInt32) (regValue[0U] & (~PCF8575_P0_0_MASK)));
            regValueTemp = ((UInt32) (regValueTemp | PCF8575_P0_7_MASK));
            regValue[0U] = (UInt8) regValueTemp;
            retVal      += Bsp_deviceRawWrite8(i2cInst, ioExpAddr, regValue,
                                               numRegs);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(BspBoardTrace, GT_ERR, "I2C write failed!!\r\n");
            }
        }
    }
#endif /* !defined (BOARD_TYPE_TDA2EX_ETH_SRV) */

    return (retVal);
}

/* Base EVM power on */
static Int32 Bsp_boardPowerOnDeviceTda2ex(UInt32 devDrvId,
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
        if ((0U == instId) || (1U == instId))
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
    }

    if (FVID2_VID_SENSOR_OV1063X_DRV == devDrvId)
    {
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined (SOC_TDA2EX)
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
#endif
    }

    if ((BSP_DRV_ID_MMC == devDrvId) && (BSP_DEVICE_MCSPI_INST_ID_1 == instId))
    {
        Bsp_boardTda2xxEnableMmc1();
    }

#if defined (BOARD_TYPE_TDA2EX_ETH_SRV)
    if ( FVID2_VID_ETHSRV_CAM_DRV == devDrvId)
    {
        /*
         * Not using camera instance id as all camera modules are controlled
         * through same switch.
         */
        if (powerOn == (UInt32) TRUE)
        {
            GPIOPinWrite(
                BOARD_GPIO_BASE_ETHCAM_POWER_DWN,
                BOARD_GPIO_PIN_ETHCAM_PWDN,
                GPIO_PIN_HIGH);
        }
        else
        {
            GPIOPinWrite(
                BOARD_GPIO_BASE_ETHCAM_POWER_DWN,
                BOARD_GPIO_PIN_ETHCAM_PWDN,
                GPIO_PIN_LOW);
        }
    }
#endif

    return (retVal);
}

static Int32 Bsp_boardSelectDeviceTda2exMultiDes(UInt32 devDrvId,
                                                 UInt32 instId)
{
    Int32 retVal = BSP_SOK;

    /* Select mux at Vision App Board level */
    retVal += Bsp_boardSelectDeviceTda2exVision(devDrvId, instId);

    return retVal;
}

/* Vision card mux select */
static Int32 Bsp_boardSelectDeviceTda2exVision(UInt32 devDrvId, UInt32 instId)
{
    Int32        retVal = BSP_SOK;
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined (SOC_TDA2EX)
    UInt32       delay;
#endif
    Bsp_BoardRev boardRev;

    /* Get board revision ID */
    boardRev = Bsp_boardGetBaseBoardRev();

    /* Select mux at base EVM level */
    retVal = Bsp_boardSelectDeviceTda2ex(devDrvId, instId);

    if (BSP_SOK == retVal)
    {
        if ((FVID2_VID_SENSOR_OV1063X_DRV == devDrvId) ||
            (FVID2_VID_SENSOR_LI_OV1063X_DRV == devDrvId) ||
            (FVID2_VID_SENSOR_MULDES_OV1063X_DRV == devDrvId) ||
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

            /*
             * Note: The GPIO's are not routed to the VISION card in case of
             * TDA2Ex EVM Rev A and Rev B. Hence the mux control is done through
             * the SW3 of the Vision card (Set SW3-8 to ON). In case of EVM
             * with higher revision this control is done by GPIO programming.
             * This comment is given just for reference so that the same could
             * be set in SW3. Note a 1 here means switch is OFF and viceversa.
             * In case of TDA2Ex 17X17 EVM the LCD is connected to DPI3 and the
             * pins used conflict with the GPIOs used for autodetect. Hence the
             * mux control is done through the SW3 of the Vision card.
             */

            if ((BSP_BOARD_REV_C <= boardRev) &&
                (Bsp_platformGetPackageType() != BSP_PLATFORM_PACKAGE_TYPE_17x17))
            {
/* GPIO6 is not defined for TI81xx, hence putting under #ifdef to avoid compile
 * error */
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined (SOC_TDA2EX)
                /* By default set to 8-bit mode for all ports by setting
                 * Demux_FPD_A,B,C to (1,0,1) */
                GPIOPinWrite(
                    BOARD_GPIO_BASE_DEMUX_FPD_A,
                    BOARD_GPIO_PIN_DEMUX_FPD_A,
                    GPIO_PIN_HIGH);
                GPIOPinWrite(
                    BOARD_GPIO_BASE_DEMUX_FPD_B,
                    BOARD_GPIO_PIN_DEMUX_FPD_B,
                    GPIO_PIN_LOW);
                GPIOPinWrite(
                    BOARD_GPIO_BASE_DEMUX_FPD_C,
                    BOARD_GPIO_PIN_DEMUX_FPD_C,
                    GPIO_PIN_HIGH);

                /* Set pin mux for GPIO pads */
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 14U,
                    (UInt32) CTRL_CORE_PAD_MCASP2_AXR4,
                    (BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE
                     |
                     BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN |
                     BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_OUT));
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 14U,
                    (UInt32) CTRL_CORE_PAD_MCASP2_AXR5,
                    (BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE
                     |
                     BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN |
                     BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_OUT));
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 14U,
                    (UInt32) CTRL_CORE_PAD_MCASP2_AXR6,
                    (BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE
                     |
                     BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN |
                     BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_OUT));
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 14U,
                    (UInt32) CTRL_CORE_PAD_GPMC_AD12,
                    (BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE
                     |
                     BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN |
                     BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_OUT));
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 14U,
                    (UInt32) CTRL_CORE_PAD_GPMC_AD13,
                    (BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE
                     |
                     BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN |
                     BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_OUT));
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 14U,
                    (UInt32) CTRL_CORE_PAD_GPMC_AD14,
                    (BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE
                     |
                     BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN |
                     BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_OUT));
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 14U,
                    (UInt32) CTRL_CORE_PAD_GPMC_AD15,
                    (BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE
                     |
                     BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN |
                     BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_OUT));

                /* For CAM1/3 FPD Linx */
                if (FVID2_VID_SENSOR_MULDES_OV1063X_DRV == devDrvId)
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
#endif
            }
        }
    }

    return (retVal);
}

/* JAMR3 card mux select */
static Int32 Bsp_boardSelectDeviceTda2exJamr3(UInt32 devDrvId, UInt32 instId)
{
    Int32  retVal = BSP_SOK;
    UInt8  regValue[2];
    UInt32 i2cInst, ioExpAddr, numRegs;
    UInt32 regValueTemp;

    /* Select mux at base EVM level */
    retVal = Bsp_boardSelectDeviceTda2ex(devDrvId, instId);

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

Int32 Bsp_boardSetPinMuxTda2ex(
    UInt32        drvId,
    UInt32        instId,
    Bsp_BoardMode boardMode)
{
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined (SOC_TDA2EX)
    #ifdef VPS_VIP_BUILD
    Bsp_BoardId  boardId;
    Bsp_BoardRev boardRev;

    boardId  = Bsp_boardGetId();
    boardRev = Bsp_boardGetBaseBoardRev();
    #endif

    if (BSP_DRV_ID_UART == drvId)
    {
        if (BSP_DEVICE_UART_INST_ID_0 == instId)
        {
            /* boardMode is ignored as of now */
            /* UART1 mux */
            Bsp_platformSetPinmuxRegs(
                (UInt32) 0U,
                (UInt32) CTRL_CORE_PAD_UART1_RXD,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 0U,
                (UInt32) CTRL_CORE_PAD_UART1_TXD,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 0U,
                (UInt32) CTRL_CORE_PAD_UART1_CTSN,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 0U,
                (UInt32) CTRL_CORE_PAD_UART1_RTSN,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        }
        else if (BSP_DEVICE_UART_INST_ID_2 == instId)
        {
            /* boardMode is ignored as of now */
            Bsp_platformSetPinmuxRegs(
                (UInt32) 1,
                (UInt32) CTRL_CORE_PAD_SPI2_SCLK,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 1,
                (UInt32) CTRL_CORE_PAD_SPI2_D1,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        }
        else if (BSP_DEVICE_UART_INST_ID_9 == instId)
        {
            /* boardMode is ignored as of now */
            /* UART10 mux
             * PAD=gpio6_14, PIN=uart10_rxd
             * PAD=gpio6_15, PIN=uart10_txd */
            Bsp_platformSetPinmuxRegs(
                (UInt32) 3,
                (UInt32) CTRL_CORE_PAD_GPIO6_14,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 3,
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
            Bsp_platformSetPinmuxRegs(
                (UInt32) 0U,
                (UInt32) CTRL_CORE_PAD_I2C1_SDA,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 0U,
                (UInt32) CTRL_CORE_PAD_I2C1_SCL,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        }
        else if (BSP_DEVICE_I2C_INST_ID_1 == instId)
        {
            /* boardMode is ignored as of now */
            /* I2C2 mux */
            Bsp_platformSetPinmuxRegs(
                (UInt32) 0U,
                (UInt32) CTRL_CORE_PAD_I2C2_SDA,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 0U,
                (UInt32) CTRL_CORE_PAD_I2C2_SCL,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        }
#if defined (BOARD_TYPE_TDA2EX_ETH_SRV)
        else if (BSP_DEVICE_I2C_INST_ID_2 == instId)
        {
            /* boardMode is ignored as of now */
            /* I2C3 mux */
            Bsp_platformSetPinmuxRegs(
                (UInt32) 10,
                (UInt32) CTRL_CORE_PAD_MCASP1_ACLKX,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 10,
                (UInt32) CTRL_CORE_PAD_MCASP1_FSX,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        }
#endif
        else if (BSP_DEVICE_I2C_INST_ID_3 == instId)
        {
            /* boardMode is ignored as of now */
            /* I2C4 mux */
            Bsp_platformSetPinmuxRegs(
                (UInt32) 4,
                (UInt32) CTRL_CORE_PAD_MCASP4_ACLKX,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 4,
                (UInt32) CTRL_CORE_PAD_MCASP4_FSX,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        }
        else if (BSP_DEVICE_I2C_INST_ID_4 == instId)
        {
            /* boardMode is ignored as of now */
            /* I2C5 mux */
            Bsp_platformSetPinmuxRegs(
                (UInt32) 10,
                (UInt32) CTRL_CORE_PAD_MCASP1_AXR0,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 10,
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
            Bsp_platformSetPinmuxRegs(
                (UInt32) 0U,
                (UInt32) CTRL_CORE_PAD_SPI1_SCLK,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 0U,
                (UInt32) CTRL_CORE_PAD_SPI1_D1,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 0U,
                (UInt32) CTRL_CORE_PAD_SPI1_D0,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 0U,
                (UInt32) CTRL_CORE_PAD_SPI1_CS0,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        }
        else if (BSP_DEVICE_MCSPI_INST_ID_1 == instId)
        {
            /* boardMode is ignored as of now */
            /* SPI2 mux */
            Bsp_platformSetPinmuxRegs(
                (UInt32) 0U,
                (UInt32) CTRL_CORE_PAD_SPI2_SCLK,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 0U,
                (UInt32) CTRL_CORE_PAD_SPI2_D1,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 0U,
                (UInt32) CTRL_CORE_PAD_SPI2_D0,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 0U,
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
            Bsp_platformSetPinmuxRegs(
                (UInt32) 7,
                (UInt32) CTRL_CORE_PAD_UART3_RXD,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 7,
                (UInt32) CTRL_CORE_PAD_UART3_TXD,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 7,
                (UInt32) CTRL_CORE_PAD_RGMII0_TXC,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 7,
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
            Bsp_platformSetPinmuxRegs(
                (UInt32) 8,
                (UInt32) CTRL_CORE_PAD_GPMC_A8,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 8,
                (UInt32) CTRL_CORE_PAD_GPMC_A9,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 8,
                (UInt32) CTRL_CORE_PAD_GPMC_A10,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 8,
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
            Bsp_platformSetPinmuxRegs(
                (UInt32) 3,
                (UInt32) CTRL_CORE_PAD_XREF_CLK2,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 0U,
                (UInt32) CTRL_CORE_PAD_MCASP3_ACLKX,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 0U,
                (UInt32) CTRL_CORE_PAD_MCASP3_FSX,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 0U,
                (UInt32) CTRL_CORE_PAD_MCASP3_AXR0,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 0U,
                (UInt32) CTRL_CORE_PAD_MCASP3_AXR1,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
        }
        else if (BSP_DEVICE_MCASP_INST_ID_5 == instId)
        {
            /* boardMode is ignored as of now */
            /* McASP6 mux (JAMR3) */
            /* PAD = mcasp1_axr[8], PIN = MCASP6_AXR0 */
            Bsp_platformSetPinmuxRegs(
                (UInt32) 1,
                (UInt32) CTRL_CORE_PAD_MCASP1_AXR8,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            /* PAD = mcasp1_axr[9], PIN = MCASP6_AXR1 */
            Bsp_platformSetPinmuxRegs(
                (UInt32) 1,
                (UInt32) CTRL_CORE_PAD_MCASP1_AXR9,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            /* PAD = mcasp1_axr[10], PIN = MCASP6_ACLKX */
            Bsp_platformSetPinmuxRegs(
                (UInt32) 1,
                (UInt32) CTRL_CORE_PAD_MCASP1_AXR10,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            /* PAD = mcasp1_axr[11], PIN = MCASP6_AFSX */
            Bsp_platformSetPinmuxRegs(
                (UInt32) 1,
                (UInt32) CTRL_CORE_PAD_MCASP1_AXR11,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            /* PAD = XREF_CLK1, PIN = MCASP6_AHCLKX */
            Bsp_platformSetPinmuxRegs(
                (UInt32) 4,
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
    if ((FVID2_VPS_DCTRL_DRV == drvId) && (VPS_DSS_DISPC_OVLY_DPI3 == instId))
    {
        Bsp_platformSetPinmuxRegs((UInt32) 3, (UInt32) CTRL_CORE_PAD_GPMC_AD0,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 3, (UInt32) CTRL_CORE_PAD_GPMC_AD1,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 3, (UInt32) CTRL_CORE_PAD_GPMC_AD2,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 3, (UInt32) CTRL_CORE_PAD_GPMC_AD3,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 3, (UInt32) CTRL_CORE_PAD_GPMC_AD4,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 3, (UInt32) CTRL_CORE_PAD_GPMC_AD5,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 3, (UInt32) CTRL_CORE_PAD_GPMC_AD6,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 3, (UInt32) CTRL_CORE_PAD_GPMC_AD7,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 3, (UInt32) CTRL_CORE_PAD_GPMC_AD8,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 3, (UInt32) CTRL_CORE_PAD_GPMC_AD9,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 3, (UInt32) CTRL_CORE_PAD_GPMC_AD10,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 3, (UInt32) CTRL_CORE_PAD_GPMC_AD11,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 3, (UInt32) CTRL_CORE_PAD_GPMC_AD12,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 3, (UInt32) CTRL_CORE_PAD_GPMC_AD13,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 3, (UInt32) CTRL_CORE_PAD_GPMC_AD14,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 3, (UInt32) CTRL_CORE_PAD_GPMC_AD15,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 3, (UInt32) CTRL_CORE_PAD_GPMC_A0,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 3, (UInt32) CTRL_CORE_PAD_GPMC_A1,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 3, (UInt32) CTRL_CORE_PAD_GPMC_A2,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 3, (UInt32) CTRL_CORE_PAD_GPMC_A3,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 3, (UInt32) CTRL_CORE_PAD_GPMC_A4,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 3, (UInt32) CTRL_CORE_PAD_GPMC_A5,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 3, (UInt32) CTRL_CORE_PAD_GPMC_A6,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 3, (UInt32) CTRL_CORE_PAD_GPMC_A7,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 3, (UInt32) CTRL_CORE_PAD_GPMC_A8,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 3, (UInt32) CTRL_CORE_PAD_GPMC_A9,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 3, (UInt32) CTRL_CORE_PAD_GPMC_A10,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 3, (UInt32) CTRL_CORE_PAD_GPMC_CS3,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    }
#endif

#ifdef VPS_VIP_BUILD
    /*
     *   In Multi des board the connections are as shown below
     *   CAM2 ---> VIN1A (VIN5A Pads)
     *   CAM4 ---> VIN1B (VIN4B Pads)
     *   CAM1 ---> VIN2A (VIN2A Pads)
     *   CAM3 ---> VIN2B (VIN2B Pads)
     */
    if (FVID2_VPS_CAPT_VID_DRV == drvId)
    {
        if ((VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA) ==
             instId))
        {
#if defined (SOC_TDA2EX)
            /* Set the VIN mux at control module level */
            if ((BSP_BOARD_REV_A == boardRev) || (BSP_BOARD_REV_B == boardRev))
            {
                HW_WR_FIELD32(
                    (SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                     CTRL_CORE_VIP_MUX_SELECT),
                    CTRL_CORE_VIP_MUX_SELECT_VIP_SEL_1A,
                    CTRL_CORE_VIP_MUX_SELECT_VIP_SEL_1A_GROUP5A);
            }
            else
            {
                HW_WR_FIELD32(
                    (SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                     CTRL_CORE_VIP_MUX_SELECT),
                    CTRL_CORE_VIP_MUX_SELECT_VIP_SEL_1A,
                    CTRL_CORE_VIP_MUX_SELECT_VIP_SEL_1A_GROUP3A);
            }
#endif

            if ((BSP_BOARD_REV_A == boardRev) || (BSP_BOARD_REV_B == boardRev))
            {
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 9U,
                    (UInt32) CTRL_CORE_PAD_GPIO6_10,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 9U,
                    (UInt32) CTRL_CORE_PAD_MMC3_DAT6,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 9U,
                    (UInt32) CTRL_CORE_PAD_MMC3_DAT7,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);

                Bsp_platformSetPinmuxRegs(
                    (UInt32) 9U,
                    (UInt32) CTRL_CORE_PAD_MMC3_DAT5,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 9U,
                    (UInt32) CTRL_CORE_PAD_MMC3_DAT4,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 9U,
                    (UInt32) CTRL_CORE_PAD_MMC3_DAT3,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 9U,
                    (UInt32) CTRL_CORE_PAD_MMC3_DAT2,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 9U,
                    (UInt32) CTRL_CORE_PAD_MMC3_DAT1,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 9U,
                    (UInt32) CTRL_CORE_PAD_MMC3_DAT0,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 9U,
                    (UInt32) CTRL_CORE_PAD_MMC3_CMD,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 9U,
                    (UInt32) CTRL_CORE_PAD_MMC3_CLK,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            }
            else
            {
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 2U,
                    (UInt32) CTRL_CORE_PAD_GPMC_CS3,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 2U,
                    (UInt32) CTRL_CORE_PAD_GPMC_A8,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 2U,
                    (UInt32) CTRL_CORE_PAD_GPMC_A9,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);

                Bsp_platformSetPinmuxRegs(
                    (UInt32) 2U,
                    (UInt32) CTRL_CORE_PAD_GPMC_AD7,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 2U,
                    (UInt32) CTRL_CORE_PAD_GPMC_AD6,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 2U,
                    (UInt32) CTRL_CORE_PAD_GPMC_AD5,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 2U,
                    (UInt32) CTRL_CORE_PAD_GPMC_AD4,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 2U,
                    (UInt32) CTRL_CORE_PAD_GPMC_AD3,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 2U,
                    (UInt32) CTRL_CORE_PAD_GPMC_AD2,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 2U,
                    (UInt32) CTRL_CORE_PAD_GPMC_AD1,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 2U,
                    (UInt32) CTRL_CORE_PAD_GPMC_AD0,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            }
        }
        else if ((VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0,
                                            VPS_VIP_PORTB) == instId))
        {
#if defined (SOC_TDA2EX)
            /* Set the VIN mux at control module level */
            HW_WR_FIELD32(
                (SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                 CTRL_CORE_VIP_MUX_SELECT),
                CTRL_CORE_VIP_MUX_SELECT_VIP_SEL_1B,
                CTRL_CORE_VIP_MUX_SELECT_VIP_SEL_1B_GROUP4B);
#endif

            if ((BSP_BOARD_REV_A == boardRev) || (BSP_BOARD_REV_B == boardRev))
            {
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 5U,
                    (UInt32) CTRL_CORE_PAD_MDIO_MCLK,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 6U,
                    (UInt32) CTRL_CORE_PAD_GPMC_A8,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 5U,
                    (UInt32) CTRL_CORE_PAD_RGMII0_TXD1,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);

                Bsp_platformSetPinmuxRegs(
                    (UInt32) 5U,
                    (UInt32) CTRL_CORE_PAD_MDIO_D,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 5U,
                    (UInt32) CTRL_CORE_PAD_UART3_RXD,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 5U,
                    (UInt32) CTRL_CORE_PAD_UART3_TXD,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 5U,
                    (UInt32) CTRL_CORE_PAD_RGMII0_TXC,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 5U,
                    (UInt32) CTRL_CORE_PAD_RGMII0_TXCTL,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 5U,
                    (UInt32) CTRL_CORE_PAD_RGMII0_RXC,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 5U,
                    (UInt32) CTRL_CORE_PAD_RGMII0_RXCTL,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 5U,
                    (UInt32) CTRL_CORE_PAD_RGMII0_RXD3,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            }
            else
            {
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 5U,
                    (UInt32) CTRL_CORE_PAD_MDIO_MCLK,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 5U,
                    (UInt32) CTRL_CORE_PAD_RGMII0_TXD2,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 5U,
                    (UInt32) CTRL_CORE_PAD_RGMII0_TXD1,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 5U,
                    (UInt32) CTRL_CORE_PAD_RGMII0_RXD3,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 5U,
                    (UInt32) CTRL_CORE_PAD_RGMII0_RXCTL,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 5U,
                    (UInt32) CTRL_CORE_PAD_RGMII0_RXC,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 5U,
                    (UInt32) CTRL_CORE_PAD_RGMII0_TXCTL,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 5U,
                    (UInt32) CTRL_CORE_PAD_RGMII0_TXC,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 5U,
                    (UInt32) CTRL_CORE_PAD_UART3_TXD,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 5U,
                    (UInt32) CTRL_CORE_PAD_UART3_RXD,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 5U,
                    (UInt32) CTRL_CORE_PAD_MDIO_D,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);

                /* Since we are overwriting the default MDIO pinmux to
                 * VIN1B CLK and VIN1B D0 in above, we will need to change the
                 * pads for MDIO to VIN2A D10/D11 pins.
                 * Note: At time the ethernet stack should be idle
                 * (No comuunication to phy should happen. */
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 3U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D10,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 3U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D11,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            }
        }
        else if ((VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1,
                                            VPS_VIP_PORTA) == instId))
        {
#if defined (SOC_TDA2EX)
            /* Set the VIN mux at control module level */
            HW_WR_FIELD32(
                (SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                 CTRL_CORE_VIP_MUX_SELECT),
                CTRL_CORE_VIP_MUX_SELECT_VIP_SEL_2A,
                CTRL_CORE_VIP_MUX_SELECT_VIP_SEL_2A_GROUP2A);
#endif

            Bsp_platformSetPinmuxRegs(
                (UInt32) 0U,
                (UInt32) CTRL_CORE_PAD_VIN2A_CLK0,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            if (BSP_BOARD_MULTIDES == boardId)
            {
                if ((BSP_BOARD_REV_A == boardRev) ||
                    (BSP_BOARD_REV_B == boardRev))
                {
                    Bsp_platformSetPinmuxRegs(
                        (UInt32) 4U,
                        (UInt32) CTRL_CORE_PAD_RGMII0_TXD2,
                        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                }
                else
                {
                    Bsp_platformSetPinmuxRegs(
                        (UInt32) 0U,
                        (UInt32) CTRL_CORE_PAD_VIN2A_HSYNC0,
                        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                }
            }
            else
            {
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 0U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_HSYNC0,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            }
            Bsp_platformSetPinmuxRegs(
                (UInt32) 0U,
                (UInt32) CTRL_CORE_PAD_VIN2A_VSYNC0,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 0U,
                (UInt32) CTRL_CORE_PAD_VIN2A_DE0,
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
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 0U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D0,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 0U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D1,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 0U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D2,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 0U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D3,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 0U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D4,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 0U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D5,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 0U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D6,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 0U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D7,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            }

            if ((BSP_BOARD_MODE_VIDEO_BT1120 == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_10BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_12BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_14BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_16BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_24BIT == boardMode))
            {
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 0U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D8,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 0U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D9,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            }
            if ((BSP_BOARD_MODE_VIDEO_BT1120 == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_12BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_14BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_16BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_24BIT == boardMode))
            {
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 0U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D10,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 0U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D11,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            }
            if ((BSP_BOARD_MODE_VIDEO_BT1120 == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_14BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_16BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_24BIT == boardMode))
            {
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 0U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D12,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 0U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D13,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            }
            if ((BSP_BOARD_MODE_VIDEO_BT1120 == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_16BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_24BIT == boardMode))
            {
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 0U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D14,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 0U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D15,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            }
            if (BSP_BOARD_MODE_VIDEO_24BIT == boardMode)
            {
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 0U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D16,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 0U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D17,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 0U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D18,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 0U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D19,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 0U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D20,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 0U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D21,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 0U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D22,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 0U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D23,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            }
        }
        else if ((VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1,
                                            VPS_VIP_PORTB) == instId))
        {
#if defined (SOC_TDA2EX)
            /* Set the VIN mux at control module level */
            HW_WR_FIELD32(
                (SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                 CTRL_CORE_VIP_MUX_SELECT),
                CTRL_CORE_VIP_MUX_SELECT_VIP_SEL_2B,
                CTRL_CORE_VIP_MUX_SELECT_VIP_SEL_2B_GROUP2B);
#endif

            if ((BSP_BOARD_REV_A == boardRev) || (BSP_BOARD_REV_B == boardRev))
            {
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 2U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_FLD0,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            }
            else
            {
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 4U,
                    (UInt32) CTRL_CORE_PAD_MMC3_DAT7,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            }

            if (BSP_BOARD_MULTIDES == boardId)
            {
                if ((BSP_BOARD_REV_A == boardRev) ||
                    (BSP_BOARD_REV_B == boardRev))
                {
                    Bsp_platformSetPinmuxRegs(
                        (UInt32) 3U,
                        (UInt32) CTRL_CORE_PAD_VIN2A_HSYNC0,
                        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                }
                else
                {
                    Bsp_platformSetPinmuxRegs(
                        (UInt32) 4U,
                        (UInt32) CTRL_CORE_PAD_GPIO6_10,
                        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                }
            }
            else
            {
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 4U,
                    (UInt32) CTRL_CORE_PAD_GPIO6_10,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            }
            Bsp_platformSetPinmuxRegs(
                (UInt32) 4U,
                (UInt32) CTRL_CORE_PAD_GPIO6_11,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);

            if ((BSP_BOARD_REV_A == boardRev) || (BSP_BOARD_REV_B == boardRev))
            {
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 2U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D23,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 2U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D22,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 2U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D21,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 2U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D20,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 2U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D19,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 2U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D18,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 2U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D17,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 2U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D16,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            }
            else
            {
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 4U,
                    (UInt32) CTRL_CORE_PAD_MMC3_CLK,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 4U,
                    (UInt32) CTRL_CORE_PAD_MMC3_CMD,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 4U,
                    (UInt32) CTRL_CORE_PAD_MMC3_DAT0,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 4U,
                    (UInt32) CTRL_CORE_PAD_MMC3_DAT1,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 4U,
                    (UInt32) CTRL_CORE_PAD_MMC3_DAT2,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 4U,
                    (UInt32) CTRL_CORE_PAD_MMC3_DAT3,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 4U,
                    (UInt32) CTRL_CORE_PAD_MMC3_DAT4,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 4U,
                    (UInt32) CTRL_CORE_PAD_MMC3_DAT5,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            }
        }
        else
        {
            /* Dummy else */
        }
    }
#endif
#endif

    return (FVID2_SOK);
}

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
