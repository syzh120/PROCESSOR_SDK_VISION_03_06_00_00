/*
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
 *  \file bsp_boardTda3xx.c
 *
 *  \brief File containing the Tda3xx BSP board functions.
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
#include <ti/drv/vps/include/vps.h>
#ifdef VPS_VIP_BUILD
#include <ti/drv/vps/include/vps_capture.h>
#endif
#ifdef VPS_DSS_BUILD
#include <ti/drv/vps/include/vps_displayCtrl.h>
#endif
#ifdef VPS_CAL_BUILD
#include <ti/drv/vps/include/vps_capture.h>
#endif
#if defined (VPS_ISS_BUILD) || defined (VPS_CAL_BUILD)
#include <ti/drv/vps/include/iss/vps_isscommon.h>
#endif

#include <ti/drv/vps/include/devices/bsp_device.h>
#include <ti/drv/vps/include/devices/bsp_ioexp.h>
#include <ti/drv/vps/include/boards/bsp_board.h>
#include <bsp_boardPriv.h>
#include <bsp_boardTda3xxDefault.h>
#include <bsp_boardTda3xxMultiDes.h>

#ifdef BOARD_TYPE_TDA3XX_RVP
#include <bsp_boardTda3xxRvp.h>
#endif

#ifdef BOARD_TYPE_TDA3XX_AR12_ALPS
#include <bsp_boardTda3xxAlps.h>
#endif

#include <ti/csl/hw_types.h>
#if defined (SOC_TDA3XX)
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Max of all the devices present in the board including any valid
 * combination of base board and daughter cards */
#define BOARD_MAX_DEVICE                    (50U)

#define BOARD_IO_EXP_TCA6416_1_I2C_ADDR     (BOARD_IO_EXP_I2C_ADDR_0)
#define BOARD_IO_EXP_TCA6424_1_I2C_ADDR     (BOARD_IO_EXP_I2C_ADDR_3)
#define BOARD_IO_EXP_TCA6424_2_I2C_ADDR     (BOARD_IO_EXP_I2C_ADDR_2)

#define BOARD_IO_EXP_TCA6416_1_I2C_ID       (BSP_DEVICE_I2C_INST_ID_0)
#define BOARD_IO_EXP_TCA6424_1_I2C_ID       (BSP_DEVICE_I2C_INST_ID_0)
#define BOARD_IO_EXP_TCA6424_2_I2C_ID       (BSP_DEVICE_I2C_INST_ID_0)

/*  Base board TCA6416 1 (on I2C1) - mappings */
#define BOARD_TCA6416_SEL_HDMI_INN_MASK     (TCA64_P0_0_MASK)
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
 *
 *  Mux A selection for VOUT1/VIN1A
 *  -------------------------------
 *
 *                          MUX_CNTL1     MUX_CNTL2
 *                          -----------------------
 *  VOUT1[D7:D0]+CTRL           1             0
 *  VIN1A[D23:D16]              1             1
 *  NA                          0             1
 *  ZZ                          0             0
 *
 *  Mux C selection for VOUT1/VIN2A/GPMC/BOOT
 *  -----------------------------------------
 *
 *                                          MUX_CNTL0     MUX_CNTL3    MUX_CNTL4
 *                                          ------------------------------------
 *  VOUT1[D23:D8]                               1             1            0
 *  VIN2A[D15:D0]/(VIN2A[D7:D0]+VIN2B[D7:D0])   1             1            1
 *  GPMC[A7:A0]+[A20:A27]                       0             0            1
 *  ZZ                                          0             0            0
 *
 *  Mux D/E selection for VIN1A/2A/2B/CPI/GPMC
 *  ------------------------------------------
 *
 *                                                  MUX_CNTL0     MUX_CNTL5
 *                                                  ---------------------
 *  VIN1A[D7:D0]+CTRL+(VIN1A[D15:D8]
 *   / VIN1B[D7:D0])+VIN2B CTRL                         1             0
 *  CPI[D15:D0]+CTRL                                    1             1
 *  GPMC[A15:A8]                                        0             1
 *  ZZ                                                  0             0
 *
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
 *  Mux Select for Imager Selection  (MUX-1)
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
 *  Mux Select for VIN1 Selection (MUX - 2 and 3)
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
 *  FPD Radar            0             1           1
 *
 *  Mux Select for VIN2 Selection (Mux - 5)
 *  -----------------------------
 *
 *                   VIN_MAP6      VIN_MAP7
 *                   ----------------------
 *  Imager               0             0
 *  Expansion Cam3       1             0
 *  Expansion Cam4       0             1
 *  Expansion Cam4:3     1             1
 */

/* Reset type - VIN reset or VOUT reset */
#define BOARD_RESET_TYPE_VOUT           (0U)
#define BOARD_RESET_TYPE_VIN            (1U)

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

static Int32 Bsp_boardPowerOnDeviceTda3xx(UInt32 devDrvId,
                                          UInt32 instId,
                                          UInt32 powerOn);
static Int32 Bsp_boardSelectDeviceTda3xx(UInt32 devDrvId, UInt32 instId);

#ifdef __cplusplus
}
#endif

#ifdef BOARD_TYPE_TDA3XX_RVP
static uint16_t Bsp_boardTda3xxRvpGetId(UInt8 address);
static Bsp_BoardId Bsp_boardGetIdTda3xxRvp(void);
static Bsp_BoardRev Bsp_boardGetRevTda3xxRvp(void);
static Int32 Bsp_boardTda3xxRvpInit(void);
static Int32 Bsp_boardTda3xxRvpLateInit(void);
Int32 Bsp_boardD3SK_ResetADV7611(void); /* Needs to be accessible by d3 test suite */
#else
static Int32 Bsp_boardVideoReset(UInt32 resetType, UInt32 doReset);
static Int32 Bsp_boardTda3xxEnableMmc4(void);
#endif
#if defined (BOARD_TYPE_TDA3XX_AR12_VIB_DAB_BOOSTER) || \
    defined (BOARD_TYPE_TDA3XX_AR12_ALPS)
static Int32 Bsp_boardTda3xxAr12xxRadarInit(void);
#endif
static Int32 Bsp_boardTda3xxInitIoexp(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static Bsp_BoardI2cInstData gBoardTda3xxI2cInstData[] =
{
    {
        BSP_DEVICE_I2C_INST_ID_0,           /* instId */
        SOC_I2C1_BASE,                      /* baseAddr */
        CSL_INTC_EVENTID_I2CINT1,           /* intNum */
        400U                                /* busClkKHz */
    },
    {
        BSP_DEVICE_I2C_INST_ID_1,           /* instId */
        SOC_I2C2_BASE,                      /* baseAddr */
        CSL_INTC_EVENTID_I2CINT2,           /* intNum */
        400U                                /* busClkKHz */
    }
};

static Bsp_BoardI2cData     gBoardTda3xxI2cData =
{
    /* numI2c */
    (sizeof (gBoardTda3xxI2cInstData) / sizeof (Bsp_BoardI2cInstData)),
    /* i2cData */
    gBoardTda3xxI2cInstData,
    /* probeInstId */
    BSP_DEVICE_I2C_INST_ID_0,
};

static Bsp_BoardDeviceData  gBoardTda3xxDevData[BOARD_MAX_DEVICE];

static Bsp_BoardData        gBoardTda3xxData =
{
    /* numDev */
    0U,
    /* devData */
    &gBoardTda3xxDevData[0U],
};

static Bsp_BoardData        gBoardTda3xxCustomData =
{
    0U,                                     /* numDev */
    NULL,                                   /* devData */
};

static Bsp_BoardDeviceData  gBoardTda3xxDefaultDevData[] =
    BSP_BOARD_TDA3XX_DEFAULT_DEVDATA;
static Bsp_BoardDeviceData  gBoardTda3xxMultiDesDevData[] =
    BSP_BOARD_TDA3XX_MULTIDES_DEVDATA;

#ifdef BOARD_TYPE_TDA3XX_RVP
static Bsp_BoardDeviceData  gBoardTda3xxRvpDevData[] =
    BSP_BOARD_TDA3XX_RVP_DEVDATA;
static Bsp_BoardDeviceData  gBoardTda3xxSKDevData[] =
    BSP_BOARD_TDA3XX_SK_DEVDATA;
#endif

#ifdef BOARD_TYPE_TDA3XX_AR12_ALPS
static Bsp_BoardDeviceData  gBoardTda3xxAlpsDevData[] =
    BSP_BOARD_TDA3XX_ALPS_DEVDATA;
#endif

/* This is not static as Tda2xx interposer board need this */
Bsp_BoardData gBoardTda3xxDefaultData =
{
    /* numDev */
    (sizeof (gBoardTda3xxDefaultDevData) / sizeof (Bsp_BoardDeviceData)),
    /* devData */
    gBoardTda3xxDefaultDevData,
};

static Bsp_BoardData        gBoardTda3xxMultiDesData =
{
    /* numDev */
    (sizeof (gBoardTda3xxMultiDesDevData) / sizeof (Bsp_BoardDeviceData)),
    /* devData */
    gBoardTda3xxMultiDesDevData,
};

#ifdef  BOARD_TYPE_TDA3XX_RVP
Bsp_BoardData gBoardTda3xxRvpData =
{
    /* numDev */
    (sizeof (gBoardTda3xxRvpDevData) / sizeof (Bsp_BoardDeviceData)),
    /* devData */
    gBoardTda3xxRvpDevData,
};
Bsp_BoardData gBoardTda3xxSKData =
{
    /* numDev */
    (sizeof (gBoardTda3xxSKDevData) / sizeof (Bsp_BoardDeviceData)),
    /* devData */
    gBoardTda3xxSKDevData,
};
#endif

#ifdef  BOARD_TYPE_TDA3XX_AR12_ALPS
Bsp_BoardData gBoardTda3xxAlpsData =
{
    /* numDev */
    (sizeof (gBoardTda3xxAlpsDevData) / sizeof (Bsp_BoardDeviceData)),
    /* devData */
    gBoardTda3xxAlpsDevData,
};
#endif

/* Falg to inidicate whether IO expander is configured for input/output */
static Int32  gBoardTda3xxIsIoexpInit = (Int32) FALSE;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

Int32 Bsp_boardTda3xxInit(void)
{
    gBoardTda3xxIsIoexpInit = (Int32) FALSE;

#ifdef BOARD_TYPE_TDA3XX_RVP
    Bsp_boardTda3xxRvpInit();
#elif defined (BOARD_TYPE_TDA3XX_AR12_VIB_DAB_BOOSTER) \
    || defined (BOARD_TYPE_TDA3XX_AR12_ALPS)
    Bsp_boardTda3xxAr12xxRadarInit();
#else
    /* Do Nothing */
#endif

    return (BSP_SOK);
}

Int32 Bsp_boardTda3xxLateInit(void)
{
    Int32  retVal = BSP_SOK;

#ifdef BOARD_TYPE_TDA3XX_RVP
    retVal = Bsp_boardTda3xxRvpLateInit();
#else
    /* Do Nothing */
#endif

    return (retVal);
}

Bsp_BoardId Bsp_boardGetIdTda3xx(void)
{
    Bsp_BoardId boardId = BSP_BOARD_UNKNOWN;

#if defined (PLATFORM_ZEBU) || defined (PLATFORM_VIRTIO)
    boardId = BSP_BOARD_BASE_TDA3XX;
#elif defined (BOARD_TYPE_TDA3XX_RVP)
    boardId = Bsp_boardGetIdTda3xxRvp();
#elif defined (BOARD_TYPE_TDA3XX_AR12_VIB_DAB_BOOSTER)
    boardId = BSP_BOARD_TDA3XX_AR12XX_RADAR;
#elif defined (BOARD_TYPE_TDA3XX_AR12_ALPS)
    boardId = BSP_BOARD_TDA3XX_AR12XX_ALPS;
#else
    Int32       retVal;
    const Bsp_BoardI2cData *i2cData;

    i2cData = Bsp_boardGetI2cData();
    GT_assert(BspBoardTrace, (i2cData != NULL));

    /*
     * Detect board ID
     */

    /*
     * Probe for IO Expander 1 in MULTI DES @ 0x25 address to detect
     * MULTI DESERIALISER daughter card.
     */
    retVal = Bsp_deviceI2cProbeDevice(
        BSP_DEVICE_I2C_INST_ID_1,
        BOARD_MULTIDES_IO_EXP_I2C_ADDR_0);
    if (FVID2_SOK == retVal)
    {
        boardId = BSP_BOARD_MULTIDES;
    }

    if (FVID2_SOK != retVal)
    {
        /*
         * Probe for EEPROM address @ 0x51 to detect TDA3XX base board (Revision
         * is Rev A/Rev B/ Rev C/ RevD)
         * Note: This should be the last check as base board is
         * present by default even when daughter card is present.
         */
        retVal = Bsp_deviceI2cProbeDevice(BSP_DEVICE_I2C_INST_ID_0,
                                          BOARD_EEPROM_I2C_ADDR_1);
        if (BSP_SOK == retVal)
        {
            boardId = BSP_BOARD_BASE_TDA3XX;
        }
        else
        {
            /*
             * Probe for EEPROM address @ 0x50 to detect TDA3XX base board
             * (Revision is >=Rev E)
             * Note: This should be the last check as base board is
             * present by default even when daughter card is present.
             */
            retVal = Bsp_deviceI2cProbeDevice(BSP_DEVICE_I2C_INST_ID_0,
                                              BOARD_EEPROM_I2C_ADDR_0);
            if (BSP_SOK == retVal)
            {
                boardId = BSP_BOARD_BASE_TDA3XX;
            }
        }
    }
#endif  /* #if defined (PLATFORM_ZEBU) || defined (PLATFORM_VIRTIO) */

    return (boardId);
}

Bsp_BoardRev Bsp_boardGetBaseBoardRevTda3xx(void)
{
#ifdef BOARD_TYPE_TDA3XX_RVP
    return Bsp_boardGetRevTda3xxRvp();
#elif defined (BOARD_TYPE_TDA3XX_AR12_ALPS)
    /* TODO: Find Alps board revision */
    return BSP_BOARD_REV_A;
#else
    Bsp_BoardRev      boardRev = BSP_BOARD_REV_A;
    Int32             retVal;
    UInt8             regValue[2];
    UInt32            i2cInst, eepromAddr, page, pageSize, delay, numRegs;
    Bsp_BoardEepromId eepromVal;

    i2cInst    = BSP_DEVICE_I2C_INST_ID_0;
    eepromAddr = (UInt32) BOARD_EEPROM_I2C_ADDR_0;

    retVal = Bsp_deviceI2cProbeDevice(i2cInst, (uint8_t) eepromAddr);
    if (FVID2_SOK != retVal)
    {
        /*No slave detected at 0x50, baord is REV A or REV B or REV C or REV D*/
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
        }
    }

    return (boardRev);
#endif
}

Bsp_BoardRev Bsp_boardGetDcRevTda3xx(void)
{
    /* Only one revision of board till date */
    return (BSP_BOARD_REV_A);
}

const Bsp_BoardI2cData *Bsp_boardGetI2cDataTda3xx(void)
{
    return (&gBoardTda3xxI2cData);
}

const Bsp_BoardData *Bsp_boardGetDataTda3xx(void)
{
    UInt32               numDev;
    Bsp_BoardId          boardId;
    Bsp_BoardData       *boardData;
    Bsp_BoardDeviceData *tempDevData;

    boardId   = Bsp_boardGetId();
    boardData = &gBoardTda3xxData;

    /* Copy only for the first time */
    if (0U == boardData->numDev)
    {
        /* Copy the individual board data to global board data as per
         * hierarchy */
        numDev      = 0U;
        tempDevData = &gBoardTda3xxDevData[0U];
        switch (boardId)
        {
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

            case BSP_BOARD_MULTIDES:
                numDev += gBoardTda3xxDefaultData.numDev;
                numDev += gBoardTda3xxMultiDesData.numDev;
                /* Array bound check */
                GT_assert(BspBoardTrace, numDev < BOARD_MAX_DEVICE);
                BspUtils_memcpy(
                    tempDevData,
                    gBoardTda3xxDefaultData.devData,
                    (sizeof (Bsp_BoardDeviceData) *
                     gBoardTda3xxDefaultData.numDev));
                tempDevData += gBoardTda3xxDefaultData.numDev;
                BspUtils_memcpy(
                    tempDevData,
                    gBoardTda3xxMultiDesData.devData,
                    (sizeof (Bsp_BoardDeviceData) *
                     gBoardTda3xxMultiDesData.numDev));
                tempDevData += gBoardTda3xxMultiDesData.numDev;
                break;

            case BSP_BOARD_CUSTOM:
                numDev += gBoardTda3xxCustomData.numDev;
                /* Array bound check */
                GT_assert(BspBoardTrace, numDev < BOARD_MAX_DEVICE);
                BspUtils_memcpy(
                    tempDevData,
                    gBoardTda3xxCustomData.devData,
                    (sizeof (Bsp_BoardDeviceData) *
                     gBoardTda3xxCustomData.numDev));
                tempDevData += gBoardTda3xxCustomData.numDev;
                break;

#ifdef BOARD_TYPE_TDA3XX_RVP
            case BSP_BOARD_TDA3XX_RVP_ALPHA:
            case BSP_BOARD_TDA3XX_RVP_BETA:
            case BSP_BOARD_TDA3XX_RVP_A:
                numDev += gBoardTda3xxRvpData.numDev;
                /* Array bound check */
                GT_assert(BspBoardTrace, numDev < BOARD_MAX_DEVICE);
                BspUtils_memcpy(
                    tempDevData,
                    gBoardTda3xxRvpData.devData,
                    (sizeof (Bsp_BoardDeviceData) *
                     gBoardTda3xxRvpData.numDev));
                tempDevData += gBoardTda3xxRvpData.numDev;
                break;
            case BSP_BOARD_TDA3XX_D3_SK:
                numDev += gBoardTda3xxSKData.numDev;
                /* Array bound check */
                GT_assert(BspBoardTrace, numDev < BOARD_MAX_DEVICE);
                BspUtils_memcpy(
                    tempDevData,
                    gBoardTda3xxSKData.devData,
                    (sizeof (Bsp_BoardDeviceData) *
                     gBoardTda3xxSKData.numDev));
                tempDevData += gBoardTda3xxSKData.numDev;
                break;
#endif
#if defined (BOARD_TYPE_TDA3XX_AR12_VIB_DAB_BOOSTER)
            case BSP_BOARD_TDA3XX_AR12XX_RADAR:
                /* Use the default board configuration */
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
#endif
#if defined (BOARD_TYPE_TDA3XX_AR12_ALPS)
            case BSP_BOARD_TDA3XX_AR12XX_ALPS:
                /* Use the default board configuration */
                numDev += gBoardTda3xxAlpsData.numDev;
                /* Array bound check */
                GT_assert(BspBoardTrace, numDev < BOARD_MAX_DEVICE);
                BspUtils_memcpy(
                    tempDevData,
                    gBoardTda3xxAlpsData.devData,
                    (sizeof (Bsp_BoardDeviceData) *
                     gBoardTda3xxAlpsData.numDev));
                tempDevData += gBoardTda3xxAlpsData.numDev;
                break;
#endif
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

/* Mode select function */
Int32 Bsp_boardSelectModeTda3xx(UInt32        devDrvId,
                                UInt32        instId,
                                Bsp_BoardMode boardMode)
{
#ifdef BOARD_TYPE_TDA3XX_RVP
    if ((Int32) FALSE == gBoardTda3xxIsIoexpInit)
    {
        Bsp_boardTda3xxInitIoexp();
    }
    return (BSP_SOK);
#else
    Int32  retVal = BSP_SOK;
    UInt8  regValue[TCA6424_NUM_PORTS];
    UInt32 i2cInst, ioExpAddr, numRegs;
    UInt32 delay;
    const Bsp_BoardI2cData *i2cData;
    UInt32 regValueTemp;

    i2cData = Bsp_boardGetI2cData();
    GT_assert(BspBoardTrace, (i2cData != NULL));

    if ((Int32) FALSE == gBoardTda3xxIsIoexpInit)
    {
        Bsp_boardTda3xxInitIoexp();
    }

    i2cInst   = BOARD_IO_EXP_TCA6424_1_I2C_ID;
    ioExpAddr = BOARD_IO_EXP_TCA6424_1_I2C_ADDR;
    numRegs   = TCA6424_NUM_PORTS;
    retVal    = TCA6424_readOutputPort(
        i2cInst,
        ioExpAddr,
        regValue,
        numRegs);
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspBoardTrace, GT_ERR, "I2C read failed!!\r\n");
    }

    if (BSP_SOK == retVal)
    {
        if (((FVID2_LCD_CTRL_DRV == devDrvId) ||
             (FVID2_VID_ENC_SII9022A_DRV == devDrvId) ||
             (FVID2_VID_ENC_DS90UH925_DRV == devDrvId)) &&
            (0U == instId))
        {
            /* Set MUX_CNTL[2:1] to 01 for VOUT1 data[7:0] and ctrl signals */
            regValueTemp = ((UInt32) regValue[TCA64XX_PORT0_OFFSET] &
                            ((UInt32) ~(BOARD_TCA6424_MUX_CNTL2_MASK)));
            regValue[TCA64XX_PORT0_OFFSET] = (UInt8) regValueTemp;
            regValueTemp = ((UInt32) regValue[TCA64XX_PORT0_OFFSET] |
                            BOARD_TCA6424_MUX_CNTL1_MASK);
            regValue[TCA64XX_PORT0_OFFSET] = (UInt8) regValueTemp;

            /* BT656 output is on D2-D9 so need to configure this mux as well.*/
            if ((BSP_BOARD_MODE_VIDEO_24BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_BT1120 == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_BT656 == boardMode))
            {
                /* Set MUX_CNTL[4:3,0] to 011 for VOUT1 data[8:23] */
                regValueTemp = ((UInt32) regValue[TCA64XX_PORT0_OFFSET] &
                                ((UInt32) ~(BOARD_TCA6424_MUX_CNTL4_MASK)));
                regValue[TCA64XX_PORT0_OFFSET] = (UInt8) regValueTemp;
                regValueTemp = ((UInt32) regValue[TCA64XX_PORT0_OFFSET] |
                                BOARD_TCA6424_MUX_CNTL3_MASK);
                regValue[TCA64XX_PORT0_OFFSET] = (UInt8) regValueTemp;
                regValueTemp = ((UInt32) regValue[TCA64XX_PORT0_OFFSET] |
                                BOARD_TCA6424_MUX_CNTL0_MASK);
                regValue[TCA64XX_PORT0_OFFSET] = (UInt8) regValueTemp;
            }

            if (FVID2_LCD_CTRL_DRV == devDrvId)
            {
                if (BSP_BOARD_MODE_VIDEO_8BIT_TDM == boardMode)
                {
                    /* Set VOUT_MAP[2:0] to 111 for LCD/Expander 8bit TDM Mode*/
                    regValueTemp = ((UInt32) regValue[TCA64XX_PORT1_OFFSET] |
                                    (BOARD_TCA6424_VOUT_MAP0_MASK));
                    regValue[TCA64XX_PORT1_OFFSET] = (UInt8) regValueTemp;
                    regValueTemp = ((UInt32) regValue[TCA64XX_PORT1_OFFSET] |
                                    BOARD_TCA6424_VOUT_MAP1_MASK);
                    regValue[TCA64XX_PORT1_OFFSET] = (UInt8) regValueTemp;
                    regValueTemp = ((UInt32) regValue[TCA64XX_PORT1_OFFSET] |
                                    ((UInt32) (BOARD_TCA6424_VOUT_MAP2_MASK)));
                    regValue[TCA64XX_PORT1_OFFSET] = (UInt8) regValueTemp;
                }
                else if (BSP_BOARD_MODE_VIDEO_24BIT == boardMode)
                {
                    /* Set VOUT_MAP[2:0] to 110 for LCD/Expander 24-bit Mode*/
                    regValueTemp = ((UInt32) regValue[TCA64XX_PORT1_OFFSET] &
                                    ((UInt32) ~(BOARD_TCA6424_VOUT_MAP0_MASK)));
                    regValue[TCA64XX_PORT1_OFFSET] = (UInt8) regValueTemp;
                    regValueTemp = ((UInt32) regValue[TCA64XX_PORT1_OFFSET] |
                                    BOARD_TCA6424_VOUT_MAP1_MASK);
                    regValue[TCA64XX_PORT1_OFFSET] = (UInt8) regValueTemp;
                    regValueTemp = ((UInt32) regValue[TCA64XX_PORT1_OFFSET] |
                                    ((UInt32) (BOARD_TCA6424_VOUT_MAP2_MASK)));
                    regValue[TCA64XX_PORT1_OFFSET] = (UInt8) regValueTemp;
                }
                else
                {
                    retVal = BSP_EINVALID_PARAMS;
                    GT_0trace(
                        BspBoardTrace, GT_ERR,
                        "Invalid Board Mode for \
                        LCD CTRL driver!!\r\n");
                }
            }

            if (FVID2_VID_ENC_SII9022A_DRV == devDrvId)
            {
                if (BSP_BOARD_MODE_VIDEO_24BIT == boardMode)
                {
                    /* Set VOUT_MAP[2:0] to 010 for HDMI 24bit panel */
                    regValueTemp = ((UInt32) regValue[TCA64XX_PORT1_OFFSET] &
                                    ((UInt32) ~(BOARD_TCA6424_VOUT_MAP0_MASK)));
                    regValue[TCA64XX_PORT1_OFFSET] = (UInt8) regValueTemp;
                    regValueTemp = ((UInt32) regValue[TCA64XX_PORT1_OFFSET] |
                                    BOARD_TCA6424_VOUT_MAP1_MASK);
                    regValue[TCA64XX_PORT1_OFFSET] = (UInt8) regValueTemp;
                    regValueTemp = (regValue[TCA64XX_PORT1_OFFSET] &
                                    ((UInt32) ~((UInt32)
                                                BOARD_TCA6424_VOUT_MAP2_MASK)));
                    regValue[TCA64XX_PORT1_OFFSET] = (UInt8) regValueTemp;
                }
                else if (BSP_BOARD_MODE_VIDEO_8BIT_TDM == boardMode)
                {
                    /* Set VOUT_MAP[2:0] to 011 for HDMI 8bit TDM Mode */
                    regValueTemp = ((UInt32) regValue[TCA64XX_PORT1_OFFSET] |
                                    (BOARD_TCA6424_VOUT_MAP0_MASK));
                    regValue[TCA64XX_PORT1_OFFSET] = (UInt8) regValueTemp;
                    regValueTemp = ((UInt32) regValue[TCA64XX_PORT1_OFFSET] |
                                    BOARD_TCA6424_VOUT_MAP1_MASK);
                    regValue[TCA64XX_PORT1_OFFSET] = (UInt8) regValueTemp;
                    regValueTemp = ((UInt32) regValue[TCA64XX_PORT1_OFFSET] &
                                    ((UInt32) ~(BOARD_TCA6424_VOUT_MAP2_MASK)));
                    regValue[TCA64XX_PORT1_OFFSET] = (UInt8) regValueTemp;
                }
                else if (BSP_BOARD_MODE_VIDEO_BT656 == boardMode)
                {
                    /* Set VOUT_MAP[2:0] to 100 for HDMI BT656 Mode */
                    regValueTemp = ((UInt32) regValue[TCA64XX_PORT1_OFFSET] &
                                    ((UInt32) ~(BOARD_TCA6424_VOUT_MAP0_MASK)));
                    regValue[TCA64XX_PORT1_OFFSET] = (UInt8) regValueTemp;
                    regValueTemp = ((UInt32) regValue[TCA64XX_PORT1_OFFSET] &
                                    ((UInt32) ~(BOARD_TCA6424_VOUT_MAP1_MASK)));
                    regValue[TCA64XX_PORT1_OFFSET] = (UInt8) regValueTemp;
                    regValueTemp = ((UInt32) regValue[TCA64XX_PORT1_OFFSET] |
                                    (BOARD_TCA6424_VOUT_MAP2_MASK));
                    regValue[TCA64XX_PORT1_OFFSET] = (UInt8) regValueTemp;
                }
                else if (BSP_BOARD_MODE_VIDEO_BT1120 == boardMode)
                {
                    /* Set VOUT_MAP[2:0] to 101 for HDMI BT1120 Mode */
                    regValueTemp = ((UInt32) regValue[TCA64XX_PORT1_OFFSET] |
                                    (BOARD_TCA6424_VOUT_MAP0_MASK));
                    regValue[TCA64XX_PORT1_OFFSET] = (UInt8) regValueTemp;
                    regValueTemp = ((UInt32) regValue[TCA64XX_PORT1_OFFSET] &
                                    ((UInt32) ~(BOARD_TCA6424_VOUT_MAP1_MASK)));
                    regValue[TCA64XX_PORT1_OFFSET] = (UInt8) regValueTemp;
                    regValueTemp = ((UInt32) regValue[TCA64XX_PORT1_OFFSET] |
                                    (BOARD_TCA6424_VOUT_MAP2_MASK));
                    regValue[TCA64XX_PORT1_OFFSET] = (UInt8) regValueTemp;
                }
                else
                {
                    retVal = BSP_EINVALID_PARAMS;
                    GT_0trace(
                        BspBoardTrace, GT_ERR,
                        "Invalid Board Mode for \
                        SII9022A driver!!\r\n");
                }
            }

            if (FVID2_VID_ENC_DS90UH925_DRV == devDrvId)
            {
                if (BSP_BOARD_MODE_VIDEO_8BIT_TDM == boardMode)
                {
                    /* Set VOUT_MAP[2:0] to 001 for FPD 8bit TDM */
                    regValueTemp = ((UInt32) regValue[TCA64XX_PORT1_OFFSET] |
                                    BOARD_TCA6424_VOUT_MAP0_MASK);
                    regValue[TCA64XX_PORT1_OFFSET] = (UInt8) regValueTemp;
                    regValueTemp = ((UInt32) regValue[TCA64XX_PORT1_OFFSET] &
                                    ((UInt32) ~(BOARD_TCA6424_VOUT_MAP1_MASK)));
                    regValue[TCA64XX_PORT1_OFFSET] = (UInt8) regValueTemp;
                    regValueTemp = (regValue[TCA64XX_PORT1_OFFSET] &
                                    ((UInt32) ~((UInt32)
                                                BOARD_TCA6424_VOUT_MAP2_MASK)));
                    regValue[TCA64XX_PORT1_OFFSET] = (UInt8) regValueTemp;
                }
                else
                {
                    /* Set VOUT_MAP[2:0] to 000 for FPD 24bit */
                    regValueTemp = ((UInt32) regValue[TCA64XX_PORT1_OFFSET] &
                                    ((UInt32) ~(BOARD_TCA6424_VOUT_MAP0_MASK)));
                    regValue[TCA64XX_PORT1_OFFSET] = (UInt8) regValueTemp;
                    regValueTemp = ((UInt32) regValue[TCA64XX_PORT1_OFFSET] &
                                    ((UInt32) ~(BOARD_TCA6424_VOUT_MAP1_MASK)));
                    regValue[TCA64XX_PORT1_OFFSET] = (UInt8) regValueTemp;
                    regValueTemp = (regValue[TCA64XX_PORT1_OFFSET] &
                                    ((UInt32) ~((UInt32)
                                                BOARD_TCA6424_VOUT_MAP2_MASK)));
                    regValue[TCA64XX_PORT1_OFFSET] = (UInt8) regValueTemp;
                }
            }
        }
        else if ((FVID2_VID_SENSOR_OV1063X_DRV == devDrvId) ||
                 (FVID2_VID_SENSOR_MULDES_OV1063X_DRV == devDrvId) ||
                 (FVID2_VID_SENSOR_APT_AR0132_DRV == devDrvId) ||
                 (FVID2_VID_SENSOR_APT_AR0140_DRV == devDrvId))
        {
            if (((FVID2_VID_SENSOR_APT_AR0132_DRV == devDrvId) &&
                 ((BSP_DEVICE_APT_AR0132_INST_ID_2_ISS == instId))) ||
                ((FVID2_VID_SENSOR_APT_AR0140_DRV == devDrvId) &&
                 ((BSP_DEVICE_APT_AR0140_INST_ID_0_ISS == instId))) ||
                ((FVID2_VID_SENSOR_APT_AR0140_DRV == devDrvId) &&
                 ((BSP_DEVICE_APT_AR0140_INST_ID_1_ISS == instId))))
            {
                /* Select the CPI input by setting Mux Control 0 and 5 */
                regValueTemp = ((UInt32) regValue[TCA64XX_PORT0_OFFSET] |
                                (BOARD_TCA6424_MUX_CNTL0_MASK));
                regValue[TCA64XX_PORT0_OFFSET] = (UInt8) regValueTemp;
                regValueTemp = ((UInt32) regValue[TCA64XX_PORT0_OFFSET] |
                                (BOARD_TCA6424_MUX_CNTL5_MASK));
                regValue[TCA64XX_PORT0_OFFSET] = (UInt8) regValueTemp;
            }

            if (BSP_BOARD_MODE_VIDEO_8BIT == boardMode)
            {
                regValueTemp = ((UInt32) regValue[TCA64XX_PORT2_OFFSET] |
                                BOARD_TCA6424_VIN_MAP0_MASK);
                regValue[TCA64XX_PORT2_OFFSET] = (UInt8) regValueTemp;
            }
            else
            {
                /* Straight */
                regValueTemp = ((UInt32) regValue[TCA64XX_PORT2_OFFSET] &
                                ((UInt32) ~BOARD_TCA6424_VIN_MAP0_MASK));
                regValue[TCA64XX_PORT2_OFFSET] = (UInt8) regValueTemp;
            }
        }
        else if (FVID2_VID_SENSOR_LI_OV1063X_DRV == devDrvId)
        {
            /* For LI sensor, always use a straight path as the bit shift is
             * already taken care in the sensor board schematics */
            regValueTemp = ((UInt32) regValue[TCA64XX_PORT2_OFFSET] &
                            ((UInt32) ~BOARD_TCA6424_VIN_MAP0_MASK));
            regValue[TCA64XX_PORT2_OFFSET] = (UInt8) regValueTemp;
        }
        else if ((FVID2_VID_SENSOR_OV10640_CPI_DRV == devDrvId) &&
                 ((BSP_DEVICE_OV10640_INST_ID_0 == instId) ||
                  (BSP_DEVICE_OV10640_INST_ID_1 == instId)))
        {
            /* Select the CPI input by setting Mux Control 0 and 5 */
            regValueTemp = ((UInt32) regValue[TCA64XX_PORT0_OFFSET] |
                            (BOARD_TCA6424_MUX_CNTL0_MASK));
            regValue[TCA64XX_PORT0_OFFSET] = (UInt8) regValueTemp;
            regValueTemp = ((UInt32) regValue[TCA64XX_PORT0_OFFSET] |
                            (BOARD_TCA6424_MUX_CNTL5_MASK));
            regValue[TCA64XX_PORT0_OFFSET] = (UInt8) regValueTemp;

            /* Select OV Sensor input by selecting VIN Map 0 and 2*/
            regValueTemp = ((UInt32) regValue[TCA64XX_PORT2_OFFSET] &
                            ((UInt32) ~(BOARD_TCA6424_VIN_MAP2_MASK)));
            regValue[TCA64XX_PORT2_OFFSET] = (UInt8) regValueTemp;
            regValueTemp = ((UInt32) regValue[TCA64XX_PORT2_OFFSET] &
                            ((UInt32) ~(BOARD_TCA6424_VIN_MAP1_MASK)));
            regValue[TCA64XX_PORT2_OFFSET] = (UInt8) regValueTemp;

            if (BSP_BOARD_MODE_VIDEO_8BIT == boardMode)
            {
                regValueTemp = ((UInt32) regValue[TCA64XX_PORT2_OFFSET] |
                                BOARD_TCA6424_VIN_MAP0_MASK);
                regValue[TCA64XX_PORT2_OFFSET] = (UInt8) regValueTemp;
            }
            else
            {
                /* Straight */
                regValueTemp = ((UInt32) regValue[TCA64XX_PORT2_OFFSET] &
                                ((UInt32) ~BOARD_TCA6424_VIN_MAP0_MASK));
                regValue[TCA64XX_PORT2_OFFSET] = (UInt8) regValueTemp;
            }
        }
        else if ((FVID2_VID_DEC_SII9127_DRV == devDrvId) ||
                 (FVID2_VID_DEC_ADV7611_DRV == devDrvId) ||
                 (FVID2_VID_DEC_DS90UH926_DRV == devDrvId))
        {
            if (BSP_BOARD_MODE_VIDEO_8BIT == boardMode)
            {
                regValueTemp = ((UInt32) regValue[TCA64XX_PORT2_OFFSET] |
                                BOARD_TCA6424_VIN_MAP0_MASK);
                regValue[TCA64XX_PORT2_OFFSET] = (UInt8) regValueTemp;
            }
            else
            {
                /* Straight */
                regValueTemp = ((UInt32) regValue[TCA64XX_PORT2_OFFSET] &
                                ((UInt32) ~BOARD_TCA6424_VIN_MAP0_MASK));
                regValue[TCA64XX_PORT2_OFFSET] = (UInt8) regValueTemp;
            }

            if (BSP_BOARD_MODE_VIDEO_24BIT == boardMode)
            {
                /* Set MUX_CNTL[2:1] to 11 for VIN1 data[16:23] */
                regValueTemp = ((UInt32) regValue[TCA64XX_PORT0_OFFSET] |
                                BOARD_TCA6424_MUX_CNTL2_MASK);
                regValue[TCA64XX_PORT0_OFFSET] = (UInt8) regValueTemp;
                regValueTemp = ((UInt32) regValue[TCA64XX_PORT0_OFFSET] |
                                BOARD_TCA6424_MUX_CNTL1_MASK);
                regValue[TCA64XX_PORT0_OFFSET] = (UInt8) regValueTemp;
            }
        }
        else
        {
            /* Do Nothing */
        }
    }

    if (BSP_SOK == retVal)
    {
        retVal += TCA6424_writeOutputPort(
            i2cInst,
            ioExpAddr,
            regValue,
            numRegs);
        if (BSP_SOK != retVal)
        {
            GT_0trace(BspBoardTrace, GT_ERR, "I2C write failed!!\r\n");
        }
    }

    if ((FVID2_VID_SENSOR_APT_AR0132_DRV == devDrvId) ||
        (FVID2_VID_SENSOR_APT_AR0140_DRV == devDrvId))
    {
        /* This brings the sensor out of reset, need below delay for
         * reset to complete. As per Aptina spec this is 35ms + 1 ms */
        delay = 50U;
        BspOsal_sleep(delay);
    }

    return (retVal);
#endif
}

Int32 Bsp_boardTda3xxReadTCA6424BoardMux(UInt32 numRegs, UInt8 regVal[])
{
    Int32 retVal;

    if ((Int32) FALSE == gBoardTda3xxIsIoexpInit)
    {
        Bsp_boardTda3xxInitIoexp();
    }

    retVal = TCA6424_readOutputPort(
        BOARD_IO_EXP_TCA6424_1_I2C_ID,
        BOARD_IO_EXP_TCA6424_1_I2C_ADDR,
        regVal,
        numRegs);
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspBoardTrace, GT_ERR, "I2C read failed!!\r\n");
    }

    return (retVal);
}

Int32 Bsp_boardTda3xxWriteTCA6424BoardMux(UInt32 numRegs, UInt8 regVal[])
{
    Int32 retVal;

    if ((Int32) FALSE == gBoardTda3xxIsIoexpInit)
    {
        Bsp_boardTda3xxInitIoexp();
    }

    retVal = TCA6424_writeOutputPort(
        BOARD_IO_EXP_TCA6424_1_I2C_ID,
        BOARD_IO_EXP_TCA6424_1_I2C_ADDR,
        regVal,
        numRegs);
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspBoardTrace, GT_ERR, "I2C Write failed!!\r\n");
    }

    return (retVal);
}

Int32 Bsp_boardSetPinMuxTda3xx(
    UInt32        drvId,
    UInt32        instId,
    Bsp_BoardMode boardMode)
{
#if defined (SOC_TDA3XX)
#ifdef VPS_ISS_BUILD
    if ((FVID2_VPS_CAPT_VID_DRV == drvId) &&
        ((VPS_CAPT_INST_ISS_CAL_A_CPI == instId) || /* For VPORT Input */
         (VPS_CAPT_INST_ISS_CAL_A == instId)))      /* For Parallel LVDS input*/
    {
        /* CPI_PCLK */
        Bsp_platformSetPinmuxRegs(1, CTRL_CORE_PAD_IO_VIN1A_CLK0,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        /* CPI HSYNC */
        Bsp_platformSetPinmuxRegs(1, CTRL_CORE_PAD_IO_VIN1A_DE0,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        /* CPI VSYNC */
        Bsp_platformSetPinmuxRegs(1, CTRL_CORE_PAD_IO_VIN1A_FLD0,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        /* CPI WEN */
        Bsp_platformSetPinmuxRegs(1, CTRL_CORE_PAD_IO_VIN1A_D13,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        /* CPI FID */
        Bsp_platformSetPinmuxRegs(1, CTRL_CORE_PAD_IO_VIN1A_D14,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        /* CPI D0 */
        Bsp_platformSetPinmuxRegs(1, CTRL_CORE_PAD_IO_VIN1A_HSYNC0,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        /* CPI D1 */
        Bsp_platformSetPinmuxRegs(1, CTRL_CORE_PAD_IO_VIN1A_VSYNC0,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        /* CPI D2 */
        Bsp_platformSetPinmuxRegs(1, CTRL_CORE_PAD_IO_VIN1A_D0,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        /* CPI D3 */
        Bsp_platformSetPinmuxRegs(1, CTRL_CORE_PAD_IO_VIN1A_D1,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        /* CPI D4 */
        Bsp_platformSetPinmuxRegs(1, CTRL_CORE_PAD_IO_VIN1A_D2,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        /* CPI D5 */
        Bsp_platformSetPinmuxRegs(1, CTRL_CORE_PAD_IO_VIN1A_D3,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        /* CPI D6 */
        Bsp_platformSetPinmuxRegs(1, CTRL_CORE_PAD_IO_VIN1A_D4,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        /* CPI D7 */
        Bsp_platformSetPinmuxRegs(1, CTRL_CORE_PAD_IO_VIN1A_D5,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);

        if (BSP_BOARD_MODE_VIDEO_10BIT == boardMode)
        {
            /* CPI D8 */
            Bsp_platformSetPinmuxRegs(1, CTRL_CORE_PAD_IO_VIN1A_D6,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* CPI D9 */
            Bsp_platformSetPinmuxRegs(1, CTRL_CORE_PAD_IO_VIN1A_D7,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        }
        else if (BSP_BOARD_MODE_VIDEO_12BIT == boardMode)
        {
            /* CPI D8 */
            Bsp_platformSetPinmuxRegs(1, CTRL_CORE_PAD_IO_VIN1A_D6,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* CPI D9 */
            Bsp_platformSetPinmuxRegs(1, CTRL_CORE_PAD_IO_VIN1A_D7,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* CPI D10 */
            Bsp_platformSetPinmuxRegs(1, CTRL_CORE_PAD_IO_VIN1A_D8,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* CPI D11 */
            Bsp_platformSetPinmuxRegs(1, CTRL_CORE_PAD_IO_VIN1A_D9,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        }
        else if (BSP_BOARD_MODE_VIDEO_14BIT == boardMode)
        {
            /* CPI D8 */
            Bsp_platformSetPinmuxRegs(1, CTRL_CORE_PAD_IO_VIN1A_D6,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* CPI D9 */
            Bsp_platformSetPinmuxRegs(1, CTRL_CORE_PAD_IO_VIN1A_D7,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* CPI D10 */
            Bsp_platformSetPinmuxRegs(1, CTRL_CORE_PAD_IO_VIN1A_D8,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* CPI D11 */
            Bsp_platformSetPinmuxRegs(1, CTRL_CORE_PAD_IO_VIN1A_D9,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* CPI D12 */
            Bsp_platformSetPinmuxRegs(1, CTRL_CORE_PAD_IO_VIN1A_D10,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* CPI D13 */
            Bsp_platformSetPinmuxRegs(1, CTRL_CORE_PAD_IO_VIN1A_D11,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        }
        else if (BSP_BOARD_MODE_VIDEO_16BIT == boardMode)
        {
            /* CPI D8 */
            Bsp_platformSetPinmuxRegs(1, CTRL_CORE_PAD_IO_VIN1A_D6,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* CPI D9 */
            Bsp_platformSetPinmuxRegs(1, CTRL_CORE_PAD_IO_VIN1A_D7,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* CPI D10 */
            Bsp_platformSetPinmuxRegs(1, CTRL_CORE_PAD_IO_VIN1A_D8,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* CPI D11 */
            Bsp_platformSetPinmuxRegs(1, CTRL_CORE_PAD_IO_VIN1A_D9,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* CPI D12 */
            Bsp_platformSetPinmuxRegs(1, CTRL_CORE_PAD_IO_VIN1A_D10,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* CPI D13 */
            Bsp_platformSetPinmuxRegs(1, CTRL_CORE_PAD_IO_VIN1A_D11,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* CPI D14 */
            Bsp_platformSetPinmuxRegs(1, CTRL_CORE_PAD_IO_VIN1A_D12,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* CPI D15 */
            Bsp_platformSetPinmuxRegs(1, CTRL_CORE_PAD_IO_VIN1A_D15,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        }
        else /* Default 8bit*/
        {
            /* Nothing to be done */
        }
    }
#endif

#ifdef VPS_DSS_BUILD
    if ((FVID2_VPS_DCTRL_DRV == drvId) && (VPS_DSS_DISPC_OVLY_DPI1 == instId))
    {
        Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VOUT1_CLK,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        /* PAD=vout1_clk, PIN=vout1_clk */
        Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VOUT1_DE,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        /* PAD=vout1_de,  PIN=vout1_de */
        Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VOUT1_FLD,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        /* PAD=vout1_fld, PIN=vout1_fld */
        Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VOUT1_HSYNC,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        /* PAD=vout1_hsync, PIN=vout1_hsync */
        Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VOUT1_VSYNC,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        /* PAD=vout1_vsync, PIN=vout1_vsync */
        Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VOUT1_D0,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        /* PAD=vout1_d0,  PIN=vout1_d0 */
        Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VOUT1_D1,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        /* PAD=vout1_d1,  PIN=vout1_d1 */
        Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VOUT1_D2,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        /* PAD=vout1_d2,  PIN=vout1_d2 */
        Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VOUT1_D3,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        /* PAD=vout1_d3,  PIN=vout1_d3 */
        Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VOUT1_D4,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        /* PAD=vout1_d4,  PIN=vout1_d4 */
        Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VOUT1_D5,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        /* PAD=vout1_d5,  PIN=vout1_d5 */
        Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VOUT1_D6,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        /* PAD=vout1_d6,  PIN=vout1_d6 */
        Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VOUT1_D7,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        /* PAD=vout1_d7,  PIN=vout1_d7 */

        if ((BSP_BOARD_MODE_VIDEO_BT1120 == boardMode) ||
            (BSP_BOARD_MODE_VIDEO_24BIT == boardMode))
        {
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VOUT1_D8,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d8,  PIN=vout1_d8 */
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VOUT1_D9,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d9,  PIN=vout1_d9 */
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VOUT1_D10,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d10, PIN=vout1_d10 */
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VOUT1_D11,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d11, PIN=vout1_d11 */
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VOUT1_D12,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d12, PIN=vout1_d12 */
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VOUT1_D13,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d13, PIN=vout1_d13 */
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VOUT1_D14,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d14, PIN=vout1_d14 */
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VOUT1_D15,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d15, PIN=vout1_d15 */
        }

        if (BSP_BOARD_MODE_VIDEO_24BIT == boardMode)
        {
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VOUT1_D16,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d16, PIN=vout1_d16 */
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VOUT1_D17,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d17, PIN=vout1_d17 */
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VOUT1_D18,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d18, PIN=vout1_d18 */
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VOUT1_D19,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d19, PIN=vout1_d19 */
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VOUT1_D20,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d20, PIN=vout1_d20 */
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VOUT1_D21,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d21, PIN=vout1_d21 */
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VOUT1_D22,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d22, PIN=vout1_d22 */
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VOUT1_D23,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d23, PIN=vout1_d23 */
        }

        if (BSP_BOARD_MODE_VIDEO_BT656 == boardMode)
        {
            /* In BT656 Mode the data is sent on D2-D9 lines */
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VOUT1_D8,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d8,  PIN=vout1_d8 */
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VOUT1_D9,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d9,  PIN=vout1_d9 */
        }

        if (BSP_BOARD_MODE_VIDEO_BT1120 == boardMode)
        {
            /* In BT1120 Mode the data is sent on D2-D9 and D12-D19 lines */
            /* Note: Other pad configs are done in above code */
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VOUT1_D16,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d16, PIN=vout1_d16 */
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VOUT1_D17,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d17, PIN=vout1_d17 */
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VOUT1_D18,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d18, PIN=vout1_d18 */
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VOUT1_D19,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d19, PIN=vout1_d19 */
        }
    }
#endif

#ifdef VPS_VIP_BUILD
    /* VIN1A mux */
    if ((FVID2_VPS_CAPT_VID_DRV == drvId) &&
        (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA) ==
         instId))
    {
        Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VIN1A_CLK0,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VIN1A_DE0,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VIN1A_HSYNC0,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VIN1A_VSYNC0,
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
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VIN1A_D0,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VIN1A_D1,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VIN1A_D2,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VIN1A_D3,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VIN1A_D4,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VIN1A_D5,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VIN1A_D6,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VIN1A_D7,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        }
        if ((BSP_BOARD_MODE_VIDEO_BT1120 == boardMode) ||
            (BSP_BOARD_MODE_VIDEO_16BIT == boardMode) ||
            (BSP_BOARD_MODE_VIDEO_24BIT == boardMode))
        {
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VIN1A_D8,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VIN1A_D9,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VIN1A_D10,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VIN1A_D11,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VIN1A_D12,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VIN1A_D13,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VIN1A_D14,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VIN1A_D15,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        }
        if (BSP_BOARD_MODE_VIDEO_10BIT == boardMode)
        {
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VIN1A_D8,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VIN1A_D9,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        }
        if (BSP_BOARD_MODE_VIDEO_12BIT == boardMode)
        {
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VIN1A_D8,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VIN1A_D9,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VIN1A_D10,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VIN1A_D11,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        }
        if (BSP_BOARD_MODE_VIDEO_14BIT == boardMode)
        {
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VIN1A_D8,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VIN1A_D9,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VIN1A_D10,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VIN1A_D11,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VIN1A_D12,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VIN1A_D13,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        }
        if (BSP_BOARD_MODE_VIDEO_24BIT == boardMode)
        {
            Bsp_platformSetPinmuxRegs(2, CTRL_CORE_PAD_IO_VOUT1_VSYNC,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_vsync, PIN=vin1a_d16 */
            Bsp_platformSetPinmuxRegs(2, CTRL_CORE_PAD_IO_VOUT1_D0,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d0,  PIN=vin1a_d17 */
            Bsp_platformSetPinmuxRegs(2, CTRL_CORE_PAD_IO_VOUT1_D1,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d1,  PIN=vin1a_d18 */
            Bsp_platformSetPinmuxRegs(2, CTRL_CORE_PAD_IO_VOUT1_D2,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d2,  PIN=vin1a_d19 */
            Bsp_platformSetPinmuxRegs(2, CTRL_CORE_PAD_IO_VOUT1_D3,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d3,  PIN=vin1a_d20 */
            Bsp_platformSetPinmuxRegs(2, CTRL_CORE_PAD_IO_VOUT1_D4,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d4,  PIN=vin1a_d21 */
            Bsp_platformSetPinmuxRegs(2, CTRL_CORE_PAD_IO_VOUT1_D5,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d5,  PIN=vin1a_d22 */
            Bsp_platformSetPinmuxRegs(2, CTRL_CORE_PAD_IO_VOUT1_D6,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d6,  PIN=vin1a_d23 */
        }
    }

    /* VIN1B mux */
    if ((FVID2_VPS_CAPT_VID_DRV == drvId) &&
        (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTB) ==
         instId))
    {
        /* VIN1A_DE0 -> VIN1B_CLK1 */
        Bsp_platformSetPinmuxRegs(
            2, CTRL_CORE_PAD_IO_VIN1A_DE0, BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        /* DCAN2_TX -> VIN1B_HSYNC1 */
        Bsp_platformSetPinmuxRegs(
            7, CTRL_CORE_PAD_IO_DCAN2_TX, BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        /* DCAN2_RX -> VIN1B_VSYNC1 */
        Bsp_platformSetPinmuxRegs(
            7, CTRL_CORE_PAD_IO_DCAN2_RX, BSP_PLATFORM_IOPAD_CFG_DEFAULT);

        /* VIN1A[8:15] -> VIN1B[0:7]*/
        Bsp_platformSetPinmuxRegs(
            2, CTRL_CORE_PAD_IO_VIN1A_D8, BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs(
            2, CTRL_CORE_PAD_IO_VIN1A_D9, BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs(
            2, CTRL_CORE_PAD_IO_VIN1A_D10, BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs(
            2, CTRL_CORE_PAD_IO_VIN1A_D11, BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs(
            2, CTRL_CORE_PAD_IO_VIN1A_D12, BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs(
            2, CTRL_CORE_PAD_IO_VIN1A_D13, BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs(
            2, CTRL_CORE_PAD_IO_VIN1A_D14, BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs(
            2, CTRL_CORE_PAD_IO_VIN1A_D15, BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    }

    /* VIN2A mux */
    if ((FVID2_VPS_CAPT_VID_DRV == drvId) &&
        (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA) ==
         instId))
    {
        Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_VIN2A_CLK0,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs(9, CTRL_CORE_PAD_IO_UART2_CTSN,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs(9, CTRL_CORE_PAD_IO_UART2_RTSN,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);

        if ((BSP_BOARD_MODE_VIDEO_BT1120 == boardMode) ||
            (BSP_BOARD_MODE_VIDEO_BT656 == boardMode) ||
            (BSP_BOARD_MODE_VIDEO_8BIT == boardMode) ||
            (BSP_BOARD_MODE_VIDEO_10BIT == boardMode) ||
            (BSP_BOARD_MODE_VIDEO_12BIT == boardMode) ||
            (BSP_BOARD_MODE_VIDEO_14BIT == boardMode) ||
            (BSP_BOARD_MODE_VIDEO_16BIT == boardMode))
        {
            Bsp_platformSetPinmuxRegs(2, CTRL_CORE_PAD_IO_VOUT1_D8,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d8,  PIN=vin2a_d0 */
            Bsp_platformSetPinmuxRegs(2, CTRL_CORE_PAD_IO_VOUT1_D9,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d9,  PIN=vin2a_d1 */
            Bsp_platformSetPinmuxRegs(2, CTRL_CORE_PAD_IO_VOUT1_D10,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d10, PIN=vin2a_d2 */
            Bsp_platformSetPinmuxRegs(2, CTRL_CORE_PAD_IO_VOUT1_D11,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d11, PIN=vin2a_d3 */
            Bsp_platformSetPinmuxRegs(2, CTRL_CORE_PAD_IO_VOUT1_D12,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d12, PIN=vin2a_d4 */
            Bsp_platformSetPinmuxRegs(2, CTRL_CORE_PAD_IO_VOUT1_D13,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d13, PIN=vin2a_d5 */
            Bsp_platformSetPinmuxRegs(2, CTRL_CORE_PAD_IO_VOUT1_D14,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d14, PIN=vin2a_d6 */
            Bsp_platformSetPinmuxRegs(2, CTRL_CORE_PAD_IO_VOUT1_D15,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d15, PIN=vin2a_d7 */
        }
        if ((BSP_BOARD_MODE_VIDEO_BT1120 == boardMode) ||
            (BSP_BOARD_MODE_VIDEO_16BIT == boardMode))
        {
            Bsp_platformSetPinmuxRegs(2, CTRL_CORE_PAD_IO_VOUT1_D16,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d16, PIN=vin2a_d8 */
            Bsp_platformSetPinmuxRegs(2, CTRL_CORE_PAD_IO_VOUT1_D17,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d17, PIN=vin2a_d9 */
            Bsp_platformSetPinmuxRegs(2, CTRL_CORE_PAD_IO_VOUT1_D18,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d18, PIN=vin2a_d10 */
            Bsp_platformSetPinmuxRegs(2, CTRL_CORE_PAD_IO_VOUT1_D19,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d19, PIN=vin2a_d11 */
            Bsp_platformSetPinmuxRegs(2, CTRL_CORE_PAD_IO_VOUT1_D20,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d20, PIN=vin2a_d12 */
            Bsp_platformSetPinmuxRegs(2, CTRL_CORE_PAD_IO_VOUT1_D21,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d21, PIN=vin2a_d13 */
            Bsp_platformSetPinmuxRegs(2, CTRL_CORE_PAD_IO_VOUT1_D22,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d22, PIN=vin2a_d14 */
            Bsp_platformSetPinmuxRegs(2, CTRL_CORE_PAD_IO_VOUT1_D23,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d23, PIN=vin2a_d15 */
        }
        if (BSP_BOARD_MODE_VIDEO_10BIT == boardMode)
        {
            Bsp_platformSetPinmuxRegs(2, CTRL_CORE_PAD_IO_VOUT1_D16,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d16, PIN=vin2a_d8 */
            Bsp_platformSetPinmuxRegs(2, CTRL_CORE_PAD_IO_VOUT1_D17,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d17, PIN=vin2a_d9 */
        }
        if (BSP_BOARD_MODE_VIDEO_12BIT == boardMode)
        {
            Bsp_platformSetPinmuxRegs(2, CTRL_CORE_PAD_IO_VOUT1_D16,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d16, PIN=vin2a_d8 */
            Bsp_platformSetPinmuxRegs(2, CTRL_CORE_PAD_IO_VOUT1_D17,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d17, PIN=vin2a_d9 */
            Bsp_platformSetPinmuxRegs(2, CTRL_CORE_PAD_IO_VOUT1_D18,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d18, PIN=vin2a_d10 */
            Bsp_platformSetPinmuxRegs(2, CTRL_CORE_PAD_IO_VOUT1_D19,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d19, PIN=vin2a_d11 */
        }
        if (BSP_BOARD_MODE_VIDEO_14BIT == boardMode)
        {
            Bsp_platformSetPinmuxRegs(2, CTRL_CORE_PAD_IO_VOUT1_D16,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d16, PIN=vin2a_d8 */
            Bsp_platformSetPinmuxRegs(2, CTRL_CORE_PAD_IO_VOUT1_D17,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d17, PIN=vin2a_d9 */
            Bsp_platformSetPinmuxRegs(2, CTRL_CORE_PAD_IO_VOUT1_D18,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d18, PIN=vin2a_d10 */
            Bsp_platformSetPinmuxRegs(2, CTRL_CORE_PAD_IO_VOUT1_D19,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d19, PIN=vin2a_d11 */
            Bsp_platformSetPinmuxRegs(2, CTRL_CORE_PAD_IO_VOUT1_D20,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d20, PIN=vin2a_d12 */
            Bsp_platformSetPinmuxRegs(2, CTRL_CORE_PAD_IO_VOUT1_D21,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            /* PAD=vout1_d21, PIN=vin2a_d13 */
        }
    }

    /* VIN2B mux */
    if ((FVID2_VPS_CAPT_VID_DRV == drvId) &&
        (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTB) ==
         instId))
    {
        /* VIN1A_FLD0 -> VIN2B_CLK1 */
        Bsp_platformSetPinmuxRegs(
            2, CTRL_CORE_PAD_IO_VIN1A_FLD0, BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        /* VIN2A_DE0 -> VIN2B_HSYNC1 */
        Bsp_platformSetPinmuxRegs(
            2, CTRL_CORE_PAD_IO_VIN2A_DE0, BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        /* VIN2A_FLD0 -> VIN2B_VSYNC1 */
        Bsp_platformSetPinmuxRegs(
            2, CTRL_CORE_PAD_IO_VIN2A_FLD0, BSP_PLATFORM_IOPAD_CFG_DEFAULT);

        /* VOUT1[16:23] -> VIN2B[0:7]*/
        Bsp_platformSetPinmuxRegs(
            5, CTRL_CORE_PAD_IO_VOUT1_D16, BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs(
            5, CTRL_CORE_PAD_IO_VOUT1_D17, BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs(
            5, CTRL_CORE_PAD_IO_VOUT1_D18, BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs(
            5, CTRL_CORE_PAD_IO_VOUT1_D19, BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs(
            5, CTRL_CORE_PAD_IO_VOUT1_D20, BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs(
            5, CTRL_CORE_PAD_IO_VOUT1_D21, BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs(
            5, CTRL_CORE_PAD_IO_VOUT1_D22, BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs(
            5, CTRL_CORE_PAD_IO_VOUT1_D23, BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    }
#endif

    if (BSP_DRV_ID_UART == drvId)
    {
        if (BSP_DEVICE_UART_INST_ID_0 == instId)
        {
            /* boardMode is ignored as of now */
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_UART1_RXD,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_UART1_TXD,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_UART1_CTSN,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_UART1_RTSN,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        }
        else if (BSP_DEVICE_UART_INST_ID_1 == instId)
        {
            /* boardMode is ignored as of now */
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_UART2_RXD,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_UART2_TXD,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        }
        else if (BSP_DEVICE_UART_INST_ID_2 == instId)
        {
            /* boardMode is ignored as of now */
            Bsp_platformSetPinmuxRegs(1, (UInt32) CTRL_CORE_PAD_IO_SPI1_SCLK,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(1, (UInt32) CTRL_CORE_PAD_IO_SPI1_CS0,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(1, (UInt32) CTRL_CORE_PAD_IO_SPI1_D1,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(1, (UInt32) CTRL_CORE_PAD_IO_SPI1_D0,
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
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_I2C1_SDA,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_I2C1_SCL,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        }
        else if (BSP_DEVICE_I2C_INST_ID_1 == instId)
        {
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_I2C2_SDA,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_I2C2_SCL,
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
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_SPI1_SCLK,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_SPI1_D1,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_SPI1_D0,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_SPI1_CS0,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        }
        if (BSP_DEVICE_MCSPI_INST_ID_1 == instId)
        {
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_SPI2_SCLK,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_SPI2_D1,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_SPI2_D0,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(0, CTRL_CORE_PAD_IO_SPI2_CS0,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        }
        if (BSP_DEVICE_MCSPI_INST_ID_2 == instId)
        {
            Bsp_platformSetPinmuxRegs(4, CTRL_CORE_PAD_IO_GPMC_AD7,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(4, CTRL_CORE_PAD_IO_GPMC_AD5,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(4, CTRL_CORE_PAD_IO_GPMC_AD6,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(4, CTRL_CORE_PAD_IO_GPMC_AD8,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        }
        if (BSP_DEVICE_MCSPI_INST_ID_3 == instId)
        {
            Bsp_platformSetPinmuxRegs(4, CTRL_CORE_PAD_IO_UART1_CTSN,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(4, CTRL_CORE_PAD_IO_UART1_RXD,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(4, CTRL_CORE_PAD_IO_UART1_TXD,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(4, CTRL_CORE_PAD_IO_UART1_RTSN,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        }
    }
    if (BSP_DRV_ID_MMC == drvId)
    {
        if (BSP_DEVICE_MMC_INST_ID_4 == instId)
        {
            Bsp_platformSetPinmuxRegs(5, CTRL_CORE_PAD_IO_RGMII0_RXC,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(5, CTRL_CORE_PAD_IO_RGMII0_RXCTL,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(5, CTRL_CORE_PAD_IO_RGMII0_RXD3,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(5, CTRL_CORE_PAD_IO_RGMII0_RXD2,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(5, CTRL_CORE_PAD_IO_RGMII0_RXD1,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(5, CTRL_CORE_PAD_IO_RGMII0_RXD0,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        }
    }
#endif

    return (FVID2_SOK);
}

#if defined (BOARD_TYPE_TDA3XX_RVP)
Int32 Bsp_boardTda3xxRvpAr12xxRadarInit(UInt32 useFpdlink)
{
    if (0U == useFpdlink)
    {
        /*Pinmux setting for GPIO4_15 - Host Interrupt Input */
        Bsp_platformSetPinmuxRegs((UInt32) 14U,
                                  CTRL_CORE_PAD_IO_UART1_CTSN,
                                  BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
        GPIODirModeSet(SOC_GPIO4_BASE, 15, GPIO_DIR_INPUT);
        /*Pinmux setting for GPIO2_7 - NRESET */
        Bsp_platformSetPinmuxRegs((UInt32) 14U,
                                  CTRL_CORE_PAD_IO_VIN1A_D4,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        /*Pinmux setting for GPIO2_14 - MODE_SEL_TDO */
        Bsp_platformSetPinmuxRegs((UInt32) 14U,
                                  CTRL_CORE_PAD_IO_VIN1A_D11,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);

        /*Pinmux setting for GPIO2_13 - MODE_SEL_SYNC_OUT */
        Bsp_platformSetPinmuxRegs((UInt32) 14U,
                                  CTRL_CORE_PAD_IO_VIN1A_D10,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        /*Pinmux setting for GPIO2_12 - MODE_SEL_PMIC_CLKOUT */
        Bsp_platformSetPinmuxRegs((UInt32) 14U,
                                  CTRL_CORE_PAD_IO_VIN1A_D9,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        /*Pinmux setting for GPIO2_5 - ERRint */
        Bsp_platformSetPinmuxRegs((UInt32) 14U,
                                  CTRL_CORE_PAD_IO_VIN1A_D2,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        GPIODirModeSet(SOC_GPIO2_BASE, 5U, GPIO_DIR_OUTPUT);
        GPIOPinWrite(SOC_GPIO2_BASE, 5U, GPIO_PIN_HIGH);

        /* Set the McSPI pin Mux */
        Bsp_boardSetPinMux(BSP_DRV_ID_MCSPI,
                           BSP_DEVICE_MCSPI_INST_ID_1, BSP_BOARD_MODE_DEFAULT);

        /* UART 2 for printfs as MCSPI is being used */
        Bsp_boardSetPinMux(BSP_DRV_ID_UART, BSP_DEVICE_UART_INST_ID_1,
                           BSP_BOARD_MODE_DEFAULT);
    }
    else
    {
        /* Pinmux setting for GPIO2_6 - Host Interrupt for Satellite Radar */
        Bsp_platformSetPinmuxRegs(
            (UInt32) 0xE,
            (UInt32) CTRL_CORE_PAD_IO_VIN1A_D3,
            BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
        GPIODirModeSet(SOC_GPIO2_BASE, 6, GPIO_DIR_INPUT);
        /* Pinmux setting for GPIO2_7 - Host Interrupt for Satellite Radar */
        Bsp_platformSetPinmuxRegs(
            (UInt32) 0xE,
            (UInt32) CTRL_CORE_PAD_IO_VIN1A_D4,
            BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
        GPIODirModeSet(SOC_GPIO2_BASE, 7, GPIO_DIR_INPUT);
        /* Pinmux setting for GPIO2_8 - Host Interrupt for Satellite Radar */
        Bsp_platformSetPinmuxRegs(
            (UInt32) 0xE,
            (UInt32) CTRL_CORE_PAD_IO_VIN1A_D5,
            BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
        GPIODirModeSet(SOC_GPIO2_BASE, 8, GPIO_DIR_INPUT);
        /* Pinmux setting for GPIO2_9 - Host Interrupt for Satellite Radar */
        Bsp_platformSetPinmuxRegs(
            (UInt32) 0xE,
            (UInt32) CTRL_CORE_PAD_IO_VIN1A_D6,
            BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
        GPIODirModeSet(SOC_GPIO2_BASE, 9, GPIO_DIR_INPUT);
    }

    return (BSP_SOK);
}
#endif

/* Base EVM mux select */
static Int32 Bsp_boardSelectDeviceTda3xx(UInt32 devDrvId, UInt32 instId)
{
#ifdef BOARD_TYPE_TDA3XX_RVP
    return (BSP_SOK);
#else
    Int32  retVal = BSP_SOK;
    UInt8  regValue[TCA6424_NUM_PORTS];
    UInt32 i2cInst, ioExpAddr, numRegs;
    const Bsp_BoardI2cData *i2cData;
    UInt32 delay;
    UInt32 resetType = BOARD_RESET_TYPE_VOUT, doReset = FALSE;
    UInt32 regValueTemp;

    i2cData = Bsp_boardGetI2cData();
    GT_assert(BspBoardTrace, (i2cData != NULL));

    if ((Int32) FALSE == gBoardTda3xxIsIoexpInit)
    {
        Bsp_boardTda3xxInitIoexp();
    }

    i2cInst   = BOARD_IO_EXP_TCA6424_1_I2C_ID;
    ioExpAddr = BOARD_IO_EXP_TCA6424_1_I2C_ADDR;
    numRegs   = TCA6424_NUM_PORTS;
    retVal    = TCA6424_readOutputPort(
        i2cInst,
        ioExpAddr,
        regValue,
        numRegs);
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspBoardTrace, GT_ERR, "I2C read failed!!\r\n");
    }
    else
    {
        if ((FVID2_LCD_CTRL_DRV == devDrvId) ||
            (FVID2_VID_ENC_SII9022A_DRV == devDrvId) ||
            (FVID2_VID_ENC_DS90UH925_DRV == devDrvId))
        {
            if (0U == instId)
            {
                /* Assert VOUT CPLD reset when changing between display
                 * source */
                resetType = BOARD_RESET_TYPE_VOUT;
                doReset   = (UInt32) TRUE;
                Bsp_boardVideoReset(resetType, doReset);

                if (FVID2_LCD_CTRL_DRV == devDrvId)
                {
                    /* Set VOUT_MAP[2:0] to 110 for LCD panel */
                    regValueTemp = ((UInt32) regValue[TCA64XX_PORT1_OFFSET] &
                                    ((UInt32) ~(BOARD_TCA6424_VOUT_MAP0_MASK)));
                    regValue[TCA64XX_PORT1_OFFSET] = (UInt8) regValueTemp;
                    regValueTemp = ((UInt32) regValue[TCA64XX_PORT1_OFFSET] |
                                    (UInt32) BOARD_TCA6424_VOUT_MAP1_MASK);
                    regValue[TCA64XX_PORT1_OFFSET] = (UInt8) regValueTemp;
                    regValueTemp = ((UInt32) regValue[TCA64XX_PORT1_OFFSET] |
                                    (UInt32) BOARD_TCA6424_VOUT_MAP2_MASK);
                    regValue[TCA64XX_PORT1_OFFSET] = (UInt8) regValueTemp;
                }
                if (FVID2_VID_ENC_SII9022A_DRV == devDrvId)
                {
                    /* Set VOUT_MAP[2:0] to 010 for HDMI 24bit panel */
                    regValueTemp = ((UInt32) regValue[TCA64XX_PORT1_OFFSET] &
                                    ((UInt32) ~(BOARD_TCA6424_VOUT_MAP0_MASK)));
                    regValue[TCA64XX_PORT1_OFFSET] = (UInt8) regValueTemp;
                    regValueTemp = ((UInt32) regValue[TCA64XX_PORT1_OFFSET] |
                                    (UInt32) BOARD_TCA6424_VOUT_MAP1_MASK);
                    regValue[TCA64XX_PORT1_OFFSET] = (UInt8) regValueTemp;
                    regValueTemp = ((UInt32) regValue[TCA64XX_PORT1_OFFSET] &
                                    ((UInt32) ~(BOARD_TCA6424_VOUT_MAP2_MASK)));
                    regValue[TCA64XX_PORT1_OFFSET] = (UInt8) regValueTemp;
                }
                if (FVID2_VID_ENC_DS90UH925_DRV == devDrvId)
                {
                    /* Set VOUT_MAP[2:0] to 000 for FPD 24bit */
                    regValueTemp = ((UInt32) regValue[TCA64XX_PORT1_OFFSET] &
                                    ((UInt32) ~(BOARD_TCA6424_VOUT_MAP0_MASK)));
                    regValue[TCA64XX_PORT1_OFFSET] = (UInt8) regValueTemp;
                    regValueTemp = ((UInt32) regValue[TCA64XX_PORT1_OFFSET] &
                                    ((UInt32) ~(BOARD_TCA6424_VOUT_MAP1_MASK)));
                    regValue[TCA64XX_PORT1_OFFSET] = (UInt8) regValueTemp;
                    regValueTemp = (regValue[TCA64XX_PORT1_OFFSET] &
                                    ((UInt32) ~((UInt32)
                                                BOARD_TCA6424_VOUT_MAP2_MASK)));
                    regValue[TCA64XX_PORT1_OFFSET] = (UInt8) regValueTemp;
                }
            }
        }
        else if ((FVID2_VID_DEC_SII9127_DRV == devDrvId) ||
                 (FVID2_VID_DEC_ADV7611_DRV == devDrvId) ||
                 (FVID2_VID_DEC_DS90UH926_DRV == devDrvId) ||
                 (FVID2_VID_SENSOR_OV1063X_DRV == devDrvId) ||
                 (FVID2_VID_SENSOR_LI_OV1063X_DRV == devDrvId) ||
                 (FVID2_VID_SENSOR_APT_AR0132_DRV == devDrvId) ||
                 (FVID2_VID_SENSOR_APT_AR0140_DRV == devDrvId) ||
                 (FVID2_VID_SENSOR_MULDES_OV1063X_DRV == devDrvId))
        {
            /*
             * Assert VIN CPLD reset when changing between capture source
             * Note: This only resets APT, LI, OV ADV7611, SIL9022, CSI2.
             *       Multi-serializer and FPD devices are not put in reset
             *       hence when selecting multiple camera, second camera select
             *       won't reset the first camera which is already programmed!!
             */
            resetType = BOARD_RESET_TYPE_VIN;
            doReset   = (UInt32) TRUE;
            Bsp_boardVideoReset(resetType, doReset);

            if ((BSP_DEVICE_SII9127_INST_ID_0 == instId) ||
                (BSP_DEVICE_ADV7611_INST_ID_0 == instId) ||
                (BSP_DEVICE_DS90UH926_INST_ID_0 == instId) ||
                (BSP_DEVICE_OV1063X_INST_ID_0 == instId) ||
                (BSP_DEVICE_LI_OV1063X_INST_ID_0 == instId) ||
                (BSP_DEVICE_APT_AR0132_INST_ID_0 == instId) ||
                (BSP_DEVICE_MULDES_OV1063X_INST_ID_1 == instId) ||
                (BSP_DEVICE_MULDES_OV1063X_INST_ID_2 == instId))
            {
                if ((FVID2_VID_DEC_SII9127_DRV == devDrvId) ||
                    (FVID2_VID_DEC_ADV7611_DRV == devDrvId))
                {
                    /* Set VIN_MAP[3:5] to 010 for SII9127/ADV7611 to VIN1 */
                    regValueTemp = ((UInt32) regValue[TCA64XX_PORT2_OFFSET] &
                                    ((UInt32) ~(BOARD_TCA6424_VIN_MAP3_MASK)));
                    regValue[TCA64XX_PORT2_OFFSET] = (UInt8) regValueTemp;
                    regValueTemp = ((UInt32) regValue[TCA64XX_PORT2_OFFSET] |
                                    (UInt32) BOARD_TCA6424_VIN_MAP4_MASK);
                    regValue[TCA64XX_PORT2_OFFSET] = (UInt8) regValueTemp;
                    regValueTemp = ((UInt32) regValue[TCA64XX_PORT2_OFFSET] &
                                    ((UInt32) ~(BOARD_TCA6424_VIN_MAP5_MASK)));
                    regValue[TCA64XX_PORT2_OFFSET] = (UInt8) regValueTemp;
                }
                else if (FVID2_VID_DEC_DS90UH926_DRV == devDrvId)
                {
                    /* Set VIN_MAP[3:5] to 100 for DS90UH926 to VIN1 */
                    regValueTemp = ((UInt32) regValue[TCA64XX_PORT2_OFFSET] |
                                    BOARD_TCA6424_VIN_MAP3_MASK);
                    regValue[TCA64XX_PORT2_OFFSET] = (UInt8) regValueTemp;
                    regValueTemp = ((UInt32) regValue[TCA64XX_PORT2_OFFSET] &
                                    ((UInt32) ~(BOARD_TCA6424_VIN_MAP4_MASK)));
                    regValue[TCA64XX_PORT2_OFFSET] = (UInt8) regValueTemp;
                    regValueTemp = ((UInt32) regValue[TCA64XX_PORT2_OFFSET] &
                                    ((UInt32) ~(BOARD_TCA6424_VIN_MAP5_MASK)));
                    regValue[TCA64XX_PORT2_OFFSET] = (UInt8) regValueTemp;
                }
                else if (FVID2_VID_SENSOR_MULDES_OV1063X_DRV == devDrvId)
                {
                    /* Set VIN_MAP[3:5] to 101 for Expansion Camera2:1 to
                     * VIN1 */
                    regValueTemp = ((UInt32) regValue[TCA64XX_PORT2_OFFSET] |
                                    (UInt32) (BOARD_TCA6424_VIN_MAP3_MASK));
                    regValue[TCA64XX_PORT2_OFFSET] = (UInt8) regValueTemp;
                    regValueTemp = ((UInt32) regValue[TCA64XX_PORT2_OFFSET] &
                                    ((UInt32) ~(BOARD_TCA6424_VIN_MAP4_MASK)));
                    regValue[TCA64XX_PORT2_OFFSET] = (UInt8) regValueTemp;
                    regValueTemp = ((UInt32) regValue[TCA64XX_PORT2_OFFSET] |
                                    (UInt32) (BOARD_TCA6424_VIN_MAP5_MASK));
                    regValue[TCA64XX_PORT2_OFFSET] = (UInt8) regValueTemp;
                }
                else
                {
                    /* Set VIN_MAP[3:5] to 000 for Imager to VIN1 */
                    regValueTemp = ((UInt32) regValue[TCA64XX_PORT2_OFFSET] &
                                    ((UInt32) ~(BOARD_TCA6424_VIN_MAP3_MASK)));
                    regValue[TCA64XX_PORT2_OFFSET] = (UInt8) regValueTemp;
                    regValueTemp = ((UInt32) regValue[TCA64XX_PORT2_OFFSET] &
                                    ((UInt32) ~(BOARD_TCA6424_VIN_MAP4_MASK)));
                    regValue[TCA64XX_PORT2_OFFSET] = (UInt8) regValueTemp;
                    regValueTemp = ((UInt32) regValue[TCA64XX_PORT2_OFFSET] &
                                    ((UInt32) ~(BOARD_TCA6424_VIN_MAP5_MASK)));
                    regValue[TCA64XX_PORT2_OFFSET] = (UInt8) regValueTemp;
                }
            }

            if ((BSP_DEVICE_SII9127_INST_ID_1 == instId) ||
                (BSP_DEVICE_ADV7611_INST_ID_1 == instId) ||
                (BSP_DEVICE_OV1063X_INST_ID_1 == instId) ||
                (BSP_DEVICE_LI_OV1063X_INST_ID_1 == instId) ||
                (BSP_DEVICE_APT_AR0132_INST_ID_1 == instId) ||
                (BSP_DEVICE_MULDES_OV1063X_INST_ID_3 == instId) ||
                (BSP_DEVICE_MULDES_OV1063X_INST_ID_4 == instId))
            {
                if ((FVID2_VID_DEC_SII9127_DRV == devDrvId) ||
                    (FVID2_VID_DEC_ADV7611_DRV == devDrvId))
                {
                    /* Set VIN_MAP[6:7] to 10 for SII9127/ADV7611 to VIN2 */
                    regValueTemp = ((UInt32) regValue[TCA64XX_PORT2_OFFSET] |
                                    (UInt32) BOARD_TCA6424_VIN_MAP6_MASK);
                    regValue[TCA64XX_PORT2_OFFSET] = (UInt8) regValueTemp;
                    regValueTemp = ((UInt32) regValue[TCA64XX_PORT2_OFFSET] &
                                    ((UInt32) ~(BOARD_TCA6424_VIN_MAP7_MASK)));
                    regValue[TCA64XX_PORT2_OFFSET] = (UInt8) regValueTemp;
                }
                else if (FVID2_VID_SENSOR_MULDES_OV1063X_DRV == devDrvId)
                {
                    /*
                     * MUX C select for VIN2A[0:15] or VIN2A/B[0:7]
                     */
                    /* Set MUX_CNTL[4,3,0] to 111 for VIN2A/2B select */
                    regValueTemp = ((UInt32) regValue[TCA64XX_PORT0_OFFSET] |
                                    (UInt32) BOARD_TCA6424_MUX_CNTL4_MASK);
                    regValue[TCA64XX_PORT0_OFFSET] = (UInt8) regValueTemp;
                    regValueTemp = ((UInt32) regValue[TCA64XX_PORT0_OFFSET] |
                                    (UInt32) BOARD_TCA6424_MUX_CNTL3_MASK);
                    regValue[TCA64XX_PORT0_OFFSET] = (UInt8) regValueTemp;
                    regValueTemp = ((UInt32) regValue[TCA64XX_PORT0_OFFSET] |
                                    (UInt32) BOARD_TCA6424_MUX_CNTL0_MASK);
                    regValue[TCA64XX_PORT0_OFFSET] = (UInt8) regValueTemp;

                    /* Set VIN_MAP[6:7] to 11 for for Expansion Camera3:4 to
                     * VIN2 */
                    regValueTemp = ((UInt32) regValue[TCA64XX_PORT2_OFFSET] |
                                    (UInt32) (BOARD_TCA6424_VIN_MAP6_MASK));
                    regValue[TCA64XX_PORT2_OFFSET] = (UInt8) regValueTemp;
                    regValueTemp = ((UInt32) regValue[TCA64XX_PORT2_OFFSET] |
                                    (UInt32) (BOARD_TCA6424_VIN_MAP7_MASK));
                    regValue[TCA64XX_PORT2_OFFSET] = (UInt8) regValueTemp;
                }
                else
                {
                    /* Set VIN_MAP[6:7] to 00 for Imager to VIN2 */
                    regValueTemp = ((UInt32) regValue[TCA64XX_PORT2_OFFSET] &
                                    ((UInt32) ~(BOARD_TCA6424_VIN_MAP6_MASK)));
                    regValue[TCA64XX_PORT2_OFFSET] = (UInt8) regValueTemp;
                    regValueTemp = ((UInt32) regValue[TCA64XX_PORT2_OFFSET] &
                                    ((UInt32) ~(BOARD_TCA6424_VIN_MAP7_MASK)));
                    regValue[TCA64XX_PORT2_OFFSET] = (UInt8) regValueTemp;
                }
            }

            if (FVID2_VID_SENSOR_OV1063X_DRV == devDrvId)
            {
                /* Set VIN_MAP[0:2] to 101 for OV 8-bit - Level 2 */
                regValueTemp = ((UInt32) regValue[TCA64XX_PORT2_OFFSET] |
                                (UInt32) BOARD_TCA6424_VIN_MAP0_MASK);
                regValue[TCA64XX_PORT2_OFFSET] = (UInt8) regValueTemp;
                regValueTemp = ((UInt32) regValue[TCA64XX_PORT2_OFFSET] &
                                ((UInt32) ~(BOARD_TCA6424_VIN_MAP1_MASK)));
                regValue[TCA64XX_PORT2_OFFSET] = (UInt8) regValueTemp;
                regValueTemp = ((UInt32) regValue[TCA64XX_PORT2_OFFSET] |
                                (UInt32) BOARD_TCA6424_VIN_MAP2_MASK);
                regValue[TCA64XX_PORT2_OFFSET] = (UInt8) regValueTemp;
            }
            else if (FVID2_VID_SENSOR_LI_OV1063X_DRV == devDrvId)
            {
                /* Set VIN_MAP[0:2] to 000 for LI Straight - Level 2 */
                /* For LI sensor, always use a straight path as the bit shift is
                 * already taken care in the sensor board schematics */
                regValueTemp = ((UInt32) regValue[TCA64XX_PORT2_OFFSET] &
                                ((UInt32) ~(BOARD_TCA6424_VIN_MAP0_MASK)));
                regValue[TCA64XX_PORT2_OFFSET] = (UInt8) regValueTemp;
                regValueTemp = ((UInt32) regValue[TCA64XX_PORT2_OFFSET] &
                                ((UInt32) ~(BOARD_TCA6424_VIN_MAP1_MASK)));
                regValue[TCA64XX_PORT2_OFFSET] = (UInt8) regValueTemp;
                regValueTemp = ((UInt32) regValue[TCA64XX_PORT2_OFFSET] &
                                ((UInt32) ~(BOARD_TCA6424_VIN_MAP2_MASK)));
                regValue[TCA64XX_PORT2_OFFSET] = (UInt8) regValueTemp;
            }
            else if ((FVID2_VID_SENSOR_APT_AR0132_DRV == devDrvId) ||
                     (FVID2_VID_SENSOR_APT_AR0140_DRV == devDrvId))
            {
                /* Set VIN_MAP[0:2] to 010 for Aptina 12-bit - Level 2 */
                regValueTemp = ((UInt32) regValue[TCA64XX_PORT2_OFFSET] &
                                ((UInt32) ~(BOARD_TCA6424_VIN_MAP0_MASK)));
                regValue[TCA64XX_PORT2_OFFSET] = (UInt8) regValueTemp;
                regValueTemp = ((UInt32) regValue[TCA64XX_PORT2_OFFSET] |
                                (UInt32) BOARD_TCA6424_VIN_MAP1_MASK);
                regValue[TCA64XX_PORT2_OFFSET] = (UInt8) regValueTemp;
                regValueTemp = ((UInt32) regValue[TCA64XX_PORT2_OFFSET] &
                                ((UInt32) ~(BOARD_TCA6424_VIN_MAP2_MASK)));
                regValue[TCA64XX_PORT2_OFFSET] = (UInt8) regValueTemp;
            }
            else if ((FVID2_VID_DEC_SII9127_DRV == devDrvId) ||
                     (FVID2_VID_DEC_ADV7611_DRV == devDrvId) ||
                     (FVID2_VID_DEC_DS90UH926_DRV == devDrvId))
            {
                /* For SIL, ADV and 926, use straight path as default */
                regValueTemp = ((UInt32) regValue[TCA64XX_PORT2_OFFSET] &
                                ((UInt32) ~(BOARD_TCA6424_VIN_MAP0_MASK)));
                regValue[TCA64XX_PORT2_OFFSET] = (UInt8) regValueTemp;
            }
            else
            {
                /* Do Nothing */
            }

            /*
             * MUX D/E select
             */
            /* Set MUX_CNTL[5,0] to 01 for VIN1A/2A/2B select */
            regValueTemp = ((UInt32) regValue[TCA64XX_PORT0_OFFSET] &
                            ((UInt32) ~(BOARD_TCA6424_MUX_CNTL5_MASK)));
            regValue[TCA64XX_PORT0_OFFSET] = (UInt8) regValueTemp;
            regValueTemp = ((UInt32) regValue[TCA64XX_PORT0_OFFSET] |
                            (UInt32) BOARD_TCA6424_MUX_CNTL0_MASK);
            regValue[TCA64XX_PORT0_OFFSET] = (UInt8) regValueTemp;
        }
        else if (BSP_DRV_ID_UART == devDrvId)
        {
            if ((BSP_DEVICE_UART_INST_ID_0 == instId) ||
                (BSP_DEVICE_UART_INST_ID_1 == instId))
            {
                /* Set Mux J - MUX_CNTL[9,0] to 11 */
                regValueTemp = ((UInt32) regValue[TCA64XX_PORT0_OFFSET] |
                                (UInt32) BOARD_TCA6424_MUX_CNTL0_MASK);
                regValue[TCA64XX_PORT0_OFFSET] = (UInt8) regValueTemp;
                regValueTemp = ((UInt32) regValue[TCA64XX_PORT1_OFFSET] |
                                (UInt32) BOARD_TCA6424_MUX_CNTL9_MASK);
                regValue[TCA64XX_PORT1_OFFSET] = (UInt8) regValueTemp;
            }
            if (BSP_DEVICE_UART_INST_ID_0 == instId)
            {
                /* Mux K - MUX_CNTL[10] to 0 */
                regValueTemp = ((UInt32) regValue[TCA64XX_PORT1_OFFSET] &
                                ((UInt32) ~(BOARD_TCA6424_MUX_CNTL10_MASK)));
                regValue[TCA64XX_PORT1_OFFSET] = (UInt8) regValueTemp;
            }
            if (BSP_DEVICE_UART_INST_ID_2 == instId)
            {
                /* Mux H - MUX_CNTL[8] to 0 */
                regValueTemp = ((UInt32) regValue[TCA64XX_PORT1_OFFSET] &
                                ((UInt32) ~(BOARD_TCA6424_MUX_CNTL8_MASK)));
                regValue[TCA64XX_PORT1_OFFSET] = (UInt8) regValueTemp;
            }
        }
        else if (BSP_DRV_ID_MCSPI == devDrvId)
        {
            if (BSP_DEVICE_MCSPI_INST_ID_0 == instId)
            {
                /* Mux H - MUX_CNTL[8] to 1 */
                regValueTemp = ((UInt32) regValue[TCA64XX_PORT1_OFFSET] |
                                (UInt32) BOARD_TCA6424_MUX_CNTL8_MASK);
                regValue[TCA64XX_PORT1_OFFSET] = (UInt8) regValueTemp;
            }
        }
        else if (BSP_DRV_ID_MMC == devDrvId)
        {
            if (BSP_DEVICE_MMC_INST_ID_4 == instId)
            {
                /* Mux F - MUX_CNTL[7] & MUX_CNTL[6] to 10 */
                regValueTemp = ((UInt32) regValue[TCA64XX_PORT0_OFFSET] |
                                (UInt32) BOARD_TCA6424_MUX_CNTL7_MASK);
                regValue[TCA64XX_PORT0_OFFSET] = (UInt8) regValueTemp;
                regValueTemp = ((UInt32) regValue[TCA64XX_PORT0_OFFSET] &
                                ((UInt32) ~(BOARD_TCA6424_MUX_CNTL6_MASK)));
                regValue[TCA64XX_PORT0_OFFSET] = (UInt8) regValueTemp;
            }
        }
        else
        {
            /* Do Nothing */
        }
        retVal += TCA6424_writeOutputPort(
            i2cInst,
            ioExpAddr,
            regValue,
            numRegs);
        if (BSP_SOK != retVal)
        {
            GT_0trace(BspBoardTrace, GT_ERR, "I2C write failed!!\r\n");
        }
        if ((FVID2_VID_SENSOR_APT_AR0132_DRV == devDrvId) ||
            (FVID2_VID_SENSOR_APT_AR0140_DRV == devDrvId))
        {
            /* This brings the sensor out of reset, need below delay for
             * reset to complete. As per Aptina spec this is 35ms + 1 ms */
            delay = 50U;
            BspOsal_sleep(delay);
        }

        /* For HDMI IN, SEL_HDMI_INn needs to be set to 0 */
        if ((FVID2_VID_DEC_SII9127_DRV == devDrvId) ||
            (FVID2_VID_DEC_ADV7611_DRV == devDrvId))
        {
            if ((BSP_DEVICE_SII9127_INST_ID_0 == instId) ||
                (BSP_DEVICE_ADV7611_INST_ID_0 == instId))
            {
                i2cInst   = BOARD_IO_EXP_TCA6416_1_I2C_ID;
                ioExpAddr = BOARD_IO_EXP_TCA6416_1_I2C_ADDR;
                numRegs   = TCA6416_NUM_PORTS;
                retVal    = TCA6416_readOutputPort(
                    i2cInst,
                    ioExpAddr,
                    regValue,
                    numRegs);
                if (BSP_SOK != retVal)
                {
                    GT_0trace(BspBoardTrace, GT_ERR, "I2C read failed!!\r\n");
                }
                else
                {
                    /* Configure muxes to select HDMI IN - Active low */
                    regValueTemp = ((UInt32) regValue[TCA64XX_PORT0_OFFSET] &
                                    ((UInt32)
                                     ~(BOARD_TCA6416_SEL_HDMI_INN_MASK)));
                    regValue[TCA64XX_PORT0_OFFSET] = (UInt8) regValueTemp;
                    retVal += TCA6416_writeOutputPort(
                        i2cInst,
                        ioExpAddr,
                        regValue,
                        numRegs);
                    if (BSP_SOK != retVal)
                    {
                        GT_0trace(BspBoardTrace, GT_ERR,
                                  "I2C write failed!!\r\n");
                    }

                    /* After enabling power supply, as per ADV7611 25ms is
                     * required to power-up the chip. So need to wait to avoid
                     * I2C timeout when we access ADV7611. Given 5ms extra to
                     * be safe.
                     */
                    delay = 30U;
                    BspOsal_sleep(delay);
                }
            }
        }

        if ((UInt32) TRUE == doReset)
        {
            /* Release respective CPLD from reset */
            Bsp_boardVideoReset(resetType, (UInt32) FALSE);
        }
    }

    return (retVal);
#endif
}

/* Base EVM power on */
static Int32 Bsp_boardPowerOnDeviceTda3xx(UInt32 devDrvId,
                                          UInt32 instId,
                                          UInt32 powerOn)
{
#ifdef BOARD_TYPE_TDA3XX_RVP
    return (BSP_SOK);
#else
    Int32  retVal = BSP_SOK;
    UInt8  regValue[TCA6416_NUM_PORTS];
    UInt32 i2cInst, ioExpAddr, numRegs;
    const Bsp_BoardI2cData *i2cData;
    UInt32 regValueTemp;

    i2cData = Bsp_boardGetI2cData();
    GT_assert(BspBoardTrace, (i2cData != NULL));

    if ((Int32) FALSE == gBoardTda3xxIsIoexpInit)
    {
        Bsp_boardTda3xxInitIoexp();
    }

    if (FVID2_LCD_CTRL_DRV == devDrvId)
    {
        if (0U == instId)
        {
            i2cInst   = BOARD_IO_EXP_TCA6416_1_I2C_ID;
            ioExpAddr = BOARD_IO_EXP_TCA6416_1_I2C_ADDR;
            numRegs   = TCA6416_NUM_PORTS;
            retVal    = TCA6416_readOutputPort(
                i2cInst,
                ioExpAddr,
                regValue,
                numRegs);
            if (BSP_SOK != retVal)
            {
                GT_0trace(BspBoardTrace, GT_ERR, "I2C read failed!!\r\n");
            }

            /* Configure muxes to power on LCD */
            regValueTemp = ((UInt32) regValue[TCA64XX_PORT1_OFFSET] &
                            ((UInt32) ~(BOARD_TCA6416_CON_LCD_PWR_DN_MASK)));
            regValue[TCA64XX_PORT1_OFFSET] = (UInt8) regValueTemp;

            retVal += TCA6416_writeOutputPort(
                i2cInst,
                ioExpAddr,
                regValue,
                numRegs);
            if (BSP_SOK != retVal)
            {
                GT_0trace(BspBoardTrace, GT_ERR, "I2C write failed!!\r\n");
            }
        }
    }

    if ((BSP_DRV_ID_MMC == devDrvId) && (BSP_DEVICE_MCSPI_INST_ID_1 == instId))
    {
        Bsp_boardTda3xxEnableMmc4();
    }

    return (retVal);
#endif
}

#ifndef BOARD_TYPE_TDA3XX_RVP
static Int32 Bsp_boardVideoReset(UInt32 resetType, UInt32 doReset)
{
    Int32  retVal = BSP_SOK;
    UInt32 i2cInst, ioExpAddr, numRegs;
    UInt8  regValue[TCA6424_NUM_PORTS];
    UInt32 regValueTemp;

    i2cInst   = BOARD_IO_EXP_TCA6424_2_I2C_ID;
    ioExpAddr = BOARD_IO_EXP_TCA6424_2_I2C_ADDR;
    numRegs   = TCA6424_NUM_PORTS;
    retVal    = TCA6424_readOutputPort(
        i2cInst,
        ioExpAddr,
        regValue,
        numRegs);
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspBoardTrace, GT_ERR, "I2C read failed!!\r\n");
    }

    /*
     * Note: These resets are provided only from REVB base boards!!
     *       Doing this on REVA has no effect.
     */
    if (BOARD_RESET_TYPE_VIN == resetType)
    {
        if ((UInt32) TRUE == doReset)
        {
            /* VIN CPLD reset */
            regValueTemp = ((UInt32) regValue[TCA64XX_PORT0_OFFSET] &
                            ((UInt32) ~(BOARD_TCA6424_VIP_RSTN_MASK)));
            regValue[TCA64XX_PORT0_OFFSET] = (UInt8) regValueTemp;
        }
        else
        {
            /* Release VIN CPLD from reset */
            regValueTemp = ((UInt32) regValue[TCA64XX_PORT0_OFFSET] |
                            ((UInt32) BOARD_TCA6424_VIP_RSTN_MASK));
            regValue[TCA64XX_PORT0_OFFSET] = (UInt8) regValueTemp;
        }
    }
    else if (BOARD_RESET_TYPE_VOUT == resetType)
    {
        if ((UInt32) TRUE == doReset)
        {
            /* VOUT CPLD reset */
            regValueTemp = ((UInt32) regValue[TCA64XX_PORT0_OFFSET] &
                            ((UInt32) ~(BOARD_TCA6424_VOUT_RSTN_MASK)));
            regValue[TCA64XX_PORT0_OFFSET] = (UInt8) regValueTemp;
        }
        else
        {
            /* Release VOUT CPLD from reset */
            regValueTemp = ((UInt32) regValue[TCA64XX_PORT0_OFFSET] |
                            BOARD_TCA6424_VOUT_RSTN_MASK);
            regValue[TCA64XX_PORT0_OFFSET] = (UInt8) regValueTemp;
        }
    }
    else
    {
        /* This won't happen */
    }

    retVal += TCA6424_writeOutputPort(
        i2cInst,
        ioExpAddr,
        regValue,
        numRegs);
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspBoardTrace, GT_ERR, "I2C write failed!!\r\n");
    }

    return (retVal);
}

#endif

static Int32 Bsp_boardTda3xxInitIoexp(void)
{
#ifdef BOARD_TYPE_TDA3XX_RVP
    Bsp_BoardId bbtype = Bsp_boardGetId();
    if (bbtype == BSP_BOARD_TDA3XX_D3_SK)
    {
        Bsp_boardD3SK_ResetADV7611();
        gBoardTda3xxIsIoexpInit = (Int32) TRUE;
    }
    return (BSP_SOK);
#else
    Int32  retVal = BSP_SOK;
    UInt8  regValue[TCA6424_NUM_PORTS];
    UInt32 i2cInst, ioExpAddr, numRegs;
    const Bsp_BoardI2cData *i2cData;

    i2cData = Bsp_boardGetI2cData();
    GT_assert(BspBoardTrace, (i2cData != NULL));

    /* Configure TCA6416 1 IO expander */
    i2cInst   = BOARD_IO_EXP_TCA6416_1_I2C_ID;
    ioExpAddr = BOARD_IO_EXP_TCA6416_1_I2C_ADDR;
    numRegs   = TCA6416_NUM_PORTS;

    /* Configure IOEXP to set output pin level to required values.
     * By default the state of IO EXP output pins in not defined.
     */
    regValue[TCA64XX_PORT0_OFFSET] = 0xB8U;
    regValue[TCA64XX_PORT1_OFFSET] = 0xFFU;
    retVal += TCA6416_writeOutputPort(i2cInst, ioExpAddr, regValue, numRegs);
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspBoardTrace, GT_ERR, "I2C write failed!!\r\n");
    }

    /* Configure every pin as output except P03 for TCA6416 1 IO expander
     * 1 is input, 0 is output */
    regValue[TCA64XX_PORT0_OFFSET] = (UInt8) BOARD_TCA6416_HDMI_CEC_D_MASK;
    regValue[TCA64XX_PORT1_OFFSET] = 0x00U;
    retVal = TCA6416_writeConfig(i2cInst, ioExpAddr, regValue, numRegs);
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspBoardTrace, GT_ERR, "I2C write failed!!\r\n");
    }

    if (BSP_SOK == retVal)
    {
        /* Configure TCA6424 1 IO expander */
        i2cInst   = BOARD_IO_EXP_TCA6424_1_I2C_ID;
        ioExpAddr = BOARD_IO_EXP_TCA6424_1_I2C_ADDR;
        numRegs   = TCA6424_NUM_PORTS;

        /* Configure IOEXP to set output pin level to required values.
         * By default the state of IO EXP output pins in not defined.
         */
        regValue[TCA64XX_PORT0_OFFSET] = 0x5BU;
        regValue[TCA64XX_PORT1_OFFSET] = 0xD0U;
        regValue[TCA64XX_PORT2_OFFSET] = 0xFFU;
        retVal += TCA6424_writeOutputPort(
            i2cInst, ioExpAddr, regValue, numRegs);
        if (BSP_SOK != retVal)
        {
            GT_0trace(BspBoardTrace, GT_ERR, "I2C write failed!!\r\n");
        }

        /* Configure every pin as output for TCA6424 1 IO expander
         * 1 is input, 0 is output */
        regValue[TCA64XX_PORT0_OFFSET] = 0x00U;
        regValue[TCA64XX_PORT1_OFFSET] = 0x00U;
        regValue[TCA64XX_PORT2_OFFSET] = 0x00U;
        retVal = TCA6424_writeConfig(i2cInst, ioExpAddr, regValue, numRegs);
        if (BSP_SOK != retVal)
        {
            GT_0trace(BspBoardTrace, GT_ERR, "I2C write failed!!\r\n");
        }
    }

    if (BSP_SOK == retVal)
    {
        /* Configure TCA6424 2 IO expander */
        i2cInst   = BOARD_IO_EXP_TCA6424_2_I2C_ID;
        ioExpAddr = BOARD_IO_EXP_TCA6424_2_I2C_ADDR;
        numRegs   = TCA6424_NUM_PORTS;

        /* Configure every pin as output except SD detect and USR_SW for
         * TCA6424 2 IO expander
         * 1 is input, 0 is output */
        regValue[TCA64XX_PORT0_OFFSET] = 0x00U;
        regValue[TCA64XX_PORT1_OFFSET] =
            (UInt8) BOARD_TCA6424_SD_CARD_DETECTN_MASK;
        regValue[TCA64XX_PORT2_OFFSET] =
            (UInt8) (BOARD_TCA6424_USR_SW1_MASK | BOARD_TCA6424_USR_SW2_MASK |
                     BOARD_TCA6424_USR_SW3_MASK | BOARD_TCA6424_USR_SW4_MASK |
                     BOARD_TCA6424_USR_SW5_MASK);
        retVal = TCA6424_writeConfig(i2cInst, ioExpAddr, regValue, numRegs);
        if (BSP_SOK != retVal)
        {
            GT_0trace(BspBoardTrace, GT_ERR, "I2C write failed!!\r\n");
        }
    }

    if (BSP_SOK == retVal)
    {
        gBoardTda3xxIsIoexpInit = (Int32) TRUE;
    }

    return (retVal);
#endif
}

#ifdef BOARD_TYPE_TDA3XX_RVP
static uint16_t Bsp_boardTda3xxRvpGetId(UInt8 address)
{
    Int32       retval  = 0;
    const UInt8 regs[1] = {0x01};
    UInt8       vals[1] = {0};
    UInt8       id      = 0;

    retval = Bsp_deviceRead8(
        BSP_DEVICE_I2C_INST_ID_1,
        address,
        regs,
        vals,
        1U);

    if (BSP_SOK != retval)
    {
        return KID_FAIL;
    }

    id = vals[0] & 0x0F;

    /* will return 0xFF if timeout */
    return id;
}

static Bsp_BoardId Bsp_boardGetIdTda3xxRvp(void)
{
    Int32       somId;
    Bsp_BoardId rvpBoardId;
    Bsp_BoardRev bbId;
    somId = Bsp_boardTda3xxRvpGetId(KTCA9539_I2CADDR_SOM);
    switch (somId)
    {
        case KID_FAIL:
            rvpBoardId = BSP_BOARD_TDA3XX_RVP_ALPHA;
            break;

        case 0x00:
            rvpBoardId = BSP_BOARD_TDA3XX_RVP_BETA;
            break;

        case 0x04:
        case 0x06:
        case 0x07:
            /* Same board ID used for all producton RVPs. Rev ID used to differentiate */
            rvpBoardId = BSP_BOARD_TDA3XX_RVP_A;
            break;

        default:
            /*Default to RVP when the board ID is unknown for future board Revs*/
            rvpBoardId = BSP_BOARD_TDA3XX_RVP_A;
            break;
    }

    /*Check baseboard ID, if it is for starterkit override board type*/
    bbId = Bsp_boardGetRevTda3xxRvp();
    if ((bbId == BSP_BOARD_REV_STARTER_KIT_REV_1) ||
            (bbId == BSP_BOARD_REV_STARTER_KIT_REV_DASH))
    {
        rvpBoardId = BSP_BOARD_TDA3XX_D3_SK;
    }

    return rvpBoardId;
}

static Bsp_BoardRev Bsp_boardGetRevTda3xxRvp(void)
{
    Int32        baseBoardRev;
    Bsp_BoardRev rvpBoardRev;

    baseBoardRev = Bsp_boardTda3xxRvpGetId(KTCA9539_I2CADDR_BASEBOARD);

    switch (baseBoardRev)
    {
        case 0x01:
            rvpBoardRev = BSP_BOARD_REV_ALPHA;
            break;

        case 0x02:
            rvpBoardRev = BSP_BOARD_REV_BETA;
            break;

        case 0x03:
            rvpBoardRev = BSP_BOARD_REV_A;
            break;

        case 0x05:
            rvpBoardRev = BSP_BOARD_REV_A_4G;
            break;

        case 0x06:
            rvpBoardRev = BSP_BOARD_RADAR_DC_REV_1;
            break;

        case 0x07:
            rvpBoardRev = BSP_BOARD_REV_STARTER_KIT_REV_1;
            break;

        case 0x08:
            /* PCA-00C011204 Rev - */
            rvpBoardRev = BSP_BOARD_REV_STARTER_KIT_REV_DASH;
            break;

        case 0x09:
            /* PCA-00C011205 Rev - */
            rvpBoardRev = BSP_BOARD_REV_DASH_4G;
            break;

        case 0x0A:
            /* PCA-00C011206 Rev - */
            rvpBoardRev = BSP_BOARD_REV_DASH_2G_STP;
            break;

        case 0x0B:
            /* PCA-00C011207 Rev - */
            rvpBoardRev = BSP_BOARD_REV_DASH_4G_STP;
            break;

        case 0x0C:
            /* PCA-00C011204 Rev A */
            rvpBoardRev = BSP_BOARD_REV_A_2G;
            break;

        default:
        case KID_FAIL:
            rvpBoardRev = BSP_BOARD_REV_A;
            break;
    }

    return rvpBoardRev;
}

#define LED17_Off()     GPIOPinWrite(SOC_GPIO4_BASE, LED_D17_GPIO, GPIO_PIN_LOW)
#define LED17_On()      GPIOPinWrite(SOC_GPIO4_BASE, LED_D17_GPIO, GPIO_PIN_HIGH)
#define LED18_Off()     GPIOPinWrite(SOC_GPIO4_BASE, LED_D18_GPIO, GPIO_PIN_LOW)
#define LED18_On()      GPIOPinWrite(SOC_GPIO4_BASE, LED_D18_GPIO, GPIO_PIN_HIGH)

static void RvpInitLEDs(void)
{
    /* LEDs GPIO4_20, GPIO4_19 */
    Bsp_platformSetPinmuxRegs(
        CTRL_CORE_PAD_IO_MUXMODE_GPIOX_14 /* GPIO4_20 */,
        (UInt32) CTRL_CORE_PAD_IO_UART2_RTSN,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);

    Bsp_platformSetPinmuxRegs(
        CTRL_CORE_PAD_IO_MUXMODE_GPIOX_14 /* GPIO4_19 */,
        (UInt32) CTRL_CORE_PAD_IO_UART2_CTSN,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);

    /* set pins for output, write LOW to turn off LEDs */
    GPIODirModeSet(SOC_GPIO4_BASE, LED_D18_GPIO, GPIO_DIR_OUTPUT);
    GPIOPinWrite(SOC_GPIO4_BASE, LED_D18_GPIO, GPIO_PIN_LOW);

    GPIODirModeSet(SOC_GPIO4_BASE, LED_D17_GPIO, GPIO_DIR_OUTPUT);
    GPIOPinWrite(SOC_GPIO4_BASE, LED_D17_GPIO, GPIO_PIN_LOW);
}

static void RvpInitHDMIIn(void)
{
    /* Enable ADV7611 chip */
    /* clear the path for the HDMI input... */
    /* CPI_PCLK */
    Bsp_platformSetPinmuxRegs(1, CTRL_CORE_PAD_IO_VIN1A_CLK0, BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    /* CPI HSYNC */
    Bsp_platformSetPinmuxRegs(1, CTRL_CORE_PAD_IO_VIN1A_DE0, BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    /* CPI VSYNC */
    Bsp_platformSetPinmuxRegs(1, CTRL_CORE_PAD_IO_VIN1A_FLD0, BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    /* CPI WEN */
    Bsp_platformSetPinmuxRegs(1, CTRL_CORE_PAD_IO_VIN1A_D13, BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    /* CPI FID */
    Bsp_platformSetPinmuxRegs(1, CTRL_CORE_PAD_IO_VIN1A_D14, BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    /* CPI D0 */
    Bsp_platformSetPinmuxRegs(1, CTRL_CORE_PAD_IO_VIN1A_HSYNC0, BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    /* CPI D1 */
    Bsp_platformSetPinmuxRegs(1, CTRL_CORE_PAD_IO_VIN1A_VSYNC0, BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    /* CPI D2 */
    Bsp_platformSetPinmuxRegs(1, CTRL_CORE_PAD_IO_VIN1A_D0, BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    /* CPI D3 */
    Bsp_platformSetPinmuxRegs(1, CTRL_CORE_PAD_IO_VIN1A_D1, BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    /* CPI D4 */
    Bsp_platformSetPinmuxRegs(1, CTRL_CORE_PAD_IO_VIN1A_D2, BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    /* CPI D5 */
    Bsp_platformSetPinmuxRegs(1, CTRL_CORE_PAD_IO_VIN1A_D3, BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    /* CPI D6 */
    Bsp_platformSetPinmuxRegs(1, CTRL_CORE_PAD_IO_VIN1A_D4, BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    /* CPI D7 */
    Bsp_platformSetPinmuxRegs(1, CTRL_CORE_PAD_IO_VIN1A_D5, BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    /* CPI D8 */
    Bsp_platformSetPinmuxRegs(1, CTRL_CORE_PAD_IO_VIN1A_D6, BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    /* CPI D9 */
    Bsp_platformSetPinmuxRegs(1, CTRL_CORE_PAD_IO_VIN1A_D7, BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    /* CPI D10 */
    Bsp_platformSetPinmuxRegs(1, CTRL_CORE_PAD_IO_VIN1A_D8, BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    /* CPI D11 */
    Bsp_platformSetPinmuxRegs(1, CTRL_CORE_PAD_IO_VIN1A_D9, BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    /* CPI D12 */
    Bsp_platformSetPinmuxRegs(1, CTRL_CORE_PAD_IO_VIN1A_D10, BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    /* CPI D13 */
    Bsp_platformSetPinmuxRegs(1, CTRL_CORE_PAD_IO_VIN1A_D11, BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    /* CPI D14 */
    Bsp_platformSetPinmuxRegs(1, CTRL_CORE_PAD_IO_VIN1A_D12, BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    /* CPI D15 */
    Bsp_platformSetPinmuxRegs(1, CTRL_CORE_PAD_IO_VIN1A_D15, BSP_PLATFORM_IOPAD_CFG_DEFAULT);
}

static void StarterKitInitGPIO(void)
{
    /* Starter Kit GPIOs */
    Bsp_platformSetPinmuxRegs( /* BUF_INPUT0 - GPIO3_19 */
        CTRL_CORE_PAD_IO_MUXMODE_GPIOX_14 /* GPIO3_19 */,
        (UInt32) CTRL_CORE_PAD_IO_RGMII0_TXC,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs( /* BUF_INPUT1 - GPIO3_20 */
        CTRL_CORE_PAD_IO_MUXMODE_GPIOX_14 /* GPIO3_20 */,
        (UInt32) CTRL_CORE_PAD_IO_RGMII0_TXCTL,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs( /* BUF_OUTPUT0 - GPIO3_21 */
        CTRL_CORE_PAD_IO_MUXMODE_GPIOX_14 /* GPIO3_21 */,
        (UInt32) CTRL_CORE_PAD_IO_RGMII0_TXD3,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    Bsp_platformSetPinmuxRegs( /* BUF_OUTPUT1 - GPIO3_22 */
        CTRL_CORE_PAD_IO_MUXMODE_GPIOX_14 /* GPIO3_22 */,
        (UInt32) CTRL_CORE_PAD_IO_RGMII0_TXD2,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);

    GPIODirModeSet(SOC_GPIO3_BASE, BUF_INPUT0, GPIO_DIR_INPUT);
    GPIODirModeSet(SOC_GPIO3_BASE, BUF_INPUT1, GPIO_DIR_INPUT);
    GPIODirModeSet(SOC_GPIO3_BASE, BUF_OUTPUT0, GPIO_DIR_OUTPUT);
    GPIODirModeSet(SOC_GPIO3_BASE, BUF_OUTPUT1, GPIO_DIR_OUTPUT);
    GPIOPinWrite(SOC_GPIO3_BASE, BUF_OUTPUT0, GPIO_PIN_LOW);
    GPIOPinWrite(SOC_GPIO3_BASE, BUF_OUTPUT1, GPIO_PIN_LOW);
}

static void RvpInitIsolatedIO(void)
{
    /* Isolated IO GPIO2.(1,2,3,4) */
    /* GPIO2_1 is CPI_DATA0 Input IN0, J18.(5,6) */
    Bsp_platformSetPinmuxRegs(
        CTRL_CORE_PAD_IO_MUXMODE_GPIOX_14,
        (UInt32) CTRL_CORE_PAD_IO_VIN1A_HSYNC0,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);  /* BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI ? */
    /* GPIO2_2 is CPI_DATA1 Input IN1, J18.(7,8) */
    Bsp_platformSetPinmuxRegs(
        CTRL_CORE_PAD_IO_MUXMODE_GPIOX_14,
        (UInt32) CTRL_CORE_PAD_IO_VIN1A_VSYNC0,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT); /* BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI ? */
    /* GPIO2_3 is CPI_DATA2 Output OUT0, J18.(9,10) */
    Bsp_platformSetPinmuxRegs(
        CTRL_CORE_PAD_IO_MUXMODE_GPIOX_14,
        (UInt32) CTRL_CORE_PAD_IO_VIN1A_D0,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    /* GPIO2_4 is CPI_DATA3 Output OUT1, J18.(11,12) */
    Bsp_platformSetPinmuxRegs(
        CTRL_CORE_PAD_IO_MUXMODE_GPIOX_14,
        (UInt32) CTRL_CORE_PAD_IO_VIN1A_D1,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    /* and set up the GPIO mode and starting states so they're ready to be used
    **/
    GPIODirModeSet(SOC_GPIO2_BASE, ISODATA0_GPIO, GPIO_DIR_INPUT);
    GPIODirModeSet(SOC_GPIO2_BASE, ISODATA1_GPIO, GPIO_DIR_INPUT);
    GPIODirModeSet(SOC_GPIO2_BASE, ISODATA2_GPIO, GPIO_DIR_OUTPUT);
    GPIODirModeSet(SOC_GPIO2_BASE, ISODATA3_GPIO, GPIO_DIR_OUTPUT);
    GPIOPinWrite(SOC_GPIO2_BASE, ISODATA2_GPIO, GPIO_PIN_LOW);
    GPIOPinWrite(SOC_GPIO2_BASE, ISODATA3_GPIO, GPIO_PIN_LOW);
}

static void RvpInitDCAN1(void)
{
    /* DCAN1 */
    Bsp_platformSetPinmuxRegs(
        CTRL_CORE_PAD_IO_DCAN1_TX_MUXMODE_DCAN1_TX_0,
        (UInt32) CTRL_CORE_PAD_IO_DCAN1_TX,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    Bsp_platformSetPinmuxRegs(
        CTRL_CORE_PAD_IO_DCAN1_RX_MUXMODE_DCAN1_RX_0,
        (UInt32) CTRL_CORE_PAD_IO_DCAN1_RX,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);
}

static void RvpInitDCAN2(void)
{
    /* DCAN2 - RVP only*/
    Bsp_platformSetPinmuxRegs(
        CTRL_CORE_PAD_IO_UART1_RXD_MUXMODE_DCAN2_TX_12,
        (UInt32) CTRL_CORE_PAD_IO_DCAN2_TX,
        BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
    Bsp_platformSetPinmuxRegs(
        CTRL_CORE_PAD_IO_UART1_TXD_MUXMODE_DCAN2_RX_12,
        (UInt32) CTRL_CORE_PAD_IO_DCAN2_RX,
        BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE);
}

static void RvpInitEthernet(void)
{
    /* RGMII1 mux */
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_IO_GPMC_CLK_MUXMODE_RGMII1_TXC_1,
        (UInt32) CTRL_CORE_PAD_IO_GPMC_CLK,
        BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_ENABLE);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_IO_GPMC_BEN0_MUXMODE_RGMII1_TXCTL_1,
        (UInt32) CTRL_CORE_PAD_IO_GPMC_BEN0,
        BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_ENABLE);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_IO_GPMC_BEN1_MUXMODE_RGMII1_TXD3_1,
        (UInt32) CTRL_CORE_PAD_IO_GPMC_BEN1,
        BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_ENABLE);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_IO_GPMC_ADVN_ALE_MUXMODE_RGMII1_TXD2_1,
        (UInt32) CTRL_CORE_PAD_IO_GPMC_ADVN_ALE,
        BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_ENABLE);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_IO_GPMC_OEN_REN_MUXMODE_RGMII1_TXD1_1,
        (UInt32) CTRL_CORE_PAD_IO_GPMC_OEN_REN,
        BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_ENABLE);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_IO_GPMC_WEN_MUXMODE_RGMII1_TXD0_1,
        (UInt32) CTRL_CORE_PAD_IO_GPMC_WEN,
        BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_ENABLE);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_IO_GPMC_CS0_MUXMODE_RGMII1_RXCTL_1,
        (UInt32) CTRL_CORE_PAD_IO_GPMC_CS0,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_IO_GPMC_WAIT0_MUXMODE_RGMII1_RXD3_1,
        (UInt32) CTRL_CORE_PAD_IO_GPMC_WAIT0,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_IO_GPMC_AD0_MUXMODE_RGMII1_RXD2_1,
        (UInt32) CTRL_CORE_PAD_IO_GPMC_AD0,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_IO_GPMC_AD1_MUXMODE_RGMII1_RXD1_1,
        (UInt32) CTRL_CORE_PAD_IO_GPMC_AD1,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_IO_GPMC_AD2_MUXMODE_RGMII1_RXD0_1,
        (UInt32) CTRL_CORE_PAD_IO_GPMC_AD2,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) 1,
        (UInt32) CTRL_CORE_PAD_IO_GPMC_AD13,
        BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    Bsp_platformSetPinmuxRegs(
        (UInt32) 0,
        (UInt32) CTRL_CORE_PAD_IO_MDIO_MCLK,
        BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_UP);
    Bsp_platformSetPinmuxRegs(
        (UInt32) 0,
        (UInt32) CTRL_CORE_PAD_IO_MDIO_D,
        0x06);

    /* GPIO2_19 */
    /* Active low reset line on PHY */
    Bsp_platformSetPinmuxRegs(
        (UInt32) 14,
        (UInt32) CTRL_CORE_PAD_IO_VIN2A_CLK0,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);

    /* GPIO2_22 */
    /* Controls bus switch on the RGMII1 receive pins
     *  Low  - disconnected from PHY
     *  High - connected to PHY
     */
     Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_IO_VOUT1_FLD_MUXMODE_GPIO2_22_14,
        (UInt32) CTRL_CORE_PAD_IO_VOUT1_FLD,
         BSP_PLATFORM_IOPAD_CFG_DEFAULT);

    /* toggle phy reset_n */
    GPIODirModeSet(SOC_GPIO2_BASE, 19, GPIO_DIR_OUTPUT);
    GPIOPinWrite(SOC_GPIO2_BASE, 19, GPIO_PIN_LOW);
    BspOsal_sleep(1);
    GPIOPinWrite(SOC_GPIO2_BASE, 19, GPIO_PIN_HIGH);
}

static void RvpInitSDCard(void)
{
    /* Configure RGMII0 as MMC4 */
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_IO_RGMII0_RXC_MUXMODE_MMC4_CLK_5,
        (UInt32) CTRL_CORE_PAD_IO_RGMII0_RXC,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_IO_RGMII0_RXCTL_MUXMODE_MMC4_CMD_5,
        (UInt32) CTRL_CORE_PAD_IO_RGMII0_RXCTL,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_IO_RGMII0_RXD3_MUXMODE_MMC4_DAT0_5,
        (UInt32) CTRL_CORE_PAD_IO_RGMII0_RXD3,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_IO_RGMII0_RXD2_MUXMODE_MMC4_DAT1_5,
        (UInt32) CTRL_CORE_PAD_IO_RGMII0_RXD2,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_IO_RGMII0_RXD1_MUXMODE_MMC4_DAT2_5,
        (UInt32) CTRL_CORE_PAD_IO_RGMII0_RXD1,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_IO_RGMII0_RXD0_MUXMODE_MMC4_DAT3_5,
        (UInt32) CTRL_CORE_PAD_IO_RGMII0_RXD0,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);
}

static Int32 Bsp_boardTda3xxRvpInit(void)
{
    /* configure the LEDs first, so we can use them for indicators */
    RvpInitLEDs();
    LED17_On();
    LED18_On();
    RvpInitDCAN1();

    /* GPIO1_17 - FPD/Camera Power Enable */
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_IO_GPMC_AD3_MUXMODE_GPIO1_17_14,
        (UInt32) CTRL_CORE_PAD_IO_GPMC_AD3,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);

    GPIODirModeSet(SOC_GPIO1_BASE, CAMERA_POWER_ENABLE_GPIO, GPIO_DIR_OUTPUT);
    GPIOPinWrite(SOC_GPIO1_BASE, CAMERA_POWER_ENABLE_GPIO, GPIO_PIN_HIGH);

    /* GPIO1_18 - ADC Diagnostic Enable */
    Bsp_platformSetPinmuxRegs(
        (UInt32) CTRL_CORE_PAD_IO_GPMC_AD4_MUXMODE_GPIO1_18_14,
        (UInt32) CTRL_CORE_PAD_IO_GPMC_AD4,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);

    GPIODirModeSet(SOC_GPIO1_BASE, ADC_DIAGNOSTIC_ENABLE_GPIO, GPIO_DIR_OUTPUT);
    GPIOPinWrite(SOC_GPIO1_BASE, ADC_DIAGNOSTIC_ENABLE_GPIO, GPIO_PIN_LOW);

    /* GPIO1_29 */
    Bsp_platformSetPinmuxRegs(
        (UInt32) 15,
        (UInt32) CTRL_CORE_PAD_IO_GPMC_AD15,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);

    GPIODirModeSet(SOC_GPIO1_BASE, I2C_EXPANDER_GPIO, GPIO_DIR_OUTPUT);
    GPIOPinWrite(SOC_GPIO1_BASE, I2C_EXPANDER_GPIO, GPIO_PIN_HIGH);

    /* enable FET switch */
    GPIODirModeSet(SOC_GPIO2_BASE, 22, GPIO_DIR_OUTPUT);
    GPIOPinWrite(SOC_GPIO2_BASE, 22, GPIO_PIN_LOW);

    /* GPIO2_10 */
    Bsp_platformSetPinmuxRegs(
        (UInt32) 14,
        (UInt32) CTRL_CORE_PAD_IO_VIN1A_D7,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);

    GPIODirModeSet(SOC_GPIO2_BASE, 10, GPIO_DIR_OUTPUT);
    GPIOPinWrite(SOC_GPIO2_BASE, 10, GPIO_PIN_LOW);

    /* GPIO2_12 */
    Bsp_platformSetPinmuxRegs(
        (UInt32) 14,
        (UInt32) CTRL_CORE_PAD_IO_VIN1A_D9,
        BSP_PLATFORM_IOPAD_CFG_DEFAULT);

    GPIODirModeSet(SOC_GPIO2_BASE, 12, GPIO_DIR_OUTPUT);
    GPIOPinWrite(SOC_GPIO2_BASE, 12, GPIO_PIN_LOW);

    RvpInitEthernet();
    RvpInitSDCard();

    /* We will finish board-specific initialization in
       bsp_BoardLateInit()/Bsp_boardTda3xxRvpLateInit()
       after I2C is initialized. */
    LED17_Off();
    LED18_Off();

    return (0);
}

static Int32 Bsp_boardTda3xxRvpLateInit(void)
{
    Bsp_BoardId bbtype = BSP_BOARD_UNKNOWN;
    bbtype = Bsp_boardGetId();

    switch (bbtype)
    {
        case BSP_BOARD_TDA3XX_D3_SK:
            GT_0trace(BspBoardTrace, GT_INFO, "Starter Kit Late Init\r\n");
            LED17_Off();
            LED18_On();
            /* GPIO3_23 - Load switch IN */

            Bsp_platformSetPinmuxRegs(
                (UInt32) 14,
                (UInt32) CTRL_CORE_PAD_IO_RGMII0_TXD1,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);

            GPIODirModeSet(SOC_GPIO3_BASE, 23, GPIO_DIR_OUTPUT);
            GPIOPinWrite(SOC_GPIO3_BASE, 23, GPIO_PIN_LOW);

            StarterKitInitGPIO();

            RvpInitHDMIIn();
            break;

        case BSP_BOARD_TDA3XX_RVP_ALPHA:
            /* Fallthrough */
        case BSP_BOARD_TDA3XX_RVP_BETA:
            /* Fallthrough */
        case BSP_BOARD_TDA3XX_RVP_A:
            GT_0trace(BspBoardTrace, GT_INFO, "RVP Late Init\r\n");
            LED17_On();
            LED18_Off();
            /* GPIO2_13 - Load switch IN */
            Bsp_platformSetPinmuxRegs(
                (UInt32) 14,
                (UInt32) CTRL_CORE_PAD_IO_VIN1A_D10,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);

            GPIODirModeSet(SOC_GPIO2_BASE, 13, GPIO_DIR_OUTPUT);
            GPIOPinWrite(SOC_GPIO2_BASE, 13, GPIO_PIN_LOW);

            RvpInitIsolatedIO();
            RvpInitDCAN2();
            break;

        default:
            GT_0trace(BspBoardTrace, GT_INFO, "Unknown D3 Board Late Init\r\n");
            LED17_On();
            LED18_On();
            break;
    }

    return (0);
}

#define kAdvReset       (0x40)
Int32 Bsp_boardD3SK_ResetADV7611(void)
{
    UInt8 tempAddr, tempData;
    Int32 retVal = BSP_SOK;

    /* configure port 0 for 0x40 as output */
    tempAddr = 6;
    tempData = 0;
    retVal |= Bsp_deviceRead8(
                            BSP_DEVICE_I2C_INST_ID_1,
                            KTCA9539_I2CADDR_BASEBOARD,
                            &tempAddr,
                            &tempData,
                            1U);
    tempData &= ~kAdvReset;
    retVal |= Bsp_deviceWrite8(
                            BSP_DEVICE_I2C_INST_ID_1,
                            KTCA9539_I2CADDR_BASEBOARD,
                            &tempAddr,
                            &tempData,
                            1U);

    /* Toggle expander 0.kAdvReset for reset */
    tempAddr = 2;
    tempData = 0;
    /* read */
    retVal |= Bsp_deviceRead8(
                            BSP_DEVICE_I2C_INST_ID_1,
                            KTCA9539_I2CADDR_BASEBOARD,
                            &tempAddr,
                            &tempData,
                            1U);
    /* HIGH */
    tempData |= kAdvReset;
    retVal |= Bsp_deviceWrite8(
                            BSP_DEVICE_I2C_INST_ID_1,
                            KTCA9539_I2CADDR_BASEBOARD,
                            &tempAddr,
                            &tempData,1U);
    /* WAIT */
    BspOsal_sleep(10);

    /* LOW */
    tempData &= ~kAdvReset;
    retVal |= Bsp_deviceWrite8(
                            BSP_DEVICE_I2C_INST_ID_1,
                            KTCA9539_I2CADDR_BASEBOARD,
                            &tempAddr,
                            &tempData,
                            1U);

    /* WAIT */
    BspOsal_sleep(10);

    /* HIGH */
    tempData |= kAdvReset;
    retVal |= Bsp_deviceWrite8(
                            BSP_DEVICE_I2C_INST_ID_1,
                            KTCA9539_I2CADDR_BASEBOARD,
                            &tempAddr,
                            &tempData,
                            1U);
    BspOsal_sleep(10);

    return (retVal);
}

#else
static Int32 Bsp_boardTda3xxEnableMmc4(void)
{
#if defined (SOC_TDA3XX)
    uint32_t tmpRegVal;
    /*MMC4- CM_L4INIT_MMC4_CLKCTRL */
    tmpRegVal  = HW_RD_REG32(SOC_L4PER_CM_CORE_BASE + CM_L4PER_MMC4_CLKCTRL);
    tmpRegVal |= 0x02000000U;
    HW_WR_REG32(SOC_L4PER_CM_CORE_BASE + CM_L4PER_MMC4_CLKCTRL, tmpRegVal);

    /*MMC4 PRCM config*/
    HW_WR_REG32(SOC_L4PER_CM_CORE_BASE + CM_L4PER_MMC4_CLKCTRL, 0x2);
#endif
    return (BSP_SOK);
}

#endif

#if defined (BOARD_TYPE_TDA3XX_AR12_VIB_DAB_BOOSTER) || \
    defined (BOARD_TYPE_TDA3XX_AR12_ALPS)
static Int32 Bsp_boardTda3xxAr12xxRadarInit(void)
{
#if defined (BOARD_TYPE_TDA3XX_AR12_VIB_DAB_BOOSTER)
    /*Pinmux setting for GPIO3_29 - Host Interrupt Input */
    Bsp_platformSetPinmuxRegs((UInt32) 14U,
                              CTRL_CORE_PAD_IO_RGMII0_RXD1,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    /*Pinmux setting for GPIO3_19 - NRESET */
    Bsp_platformSetPinmuxRegs((UInt32) 14U,
                              CTRL_CORE_PAD_IO_RGMII0_TXC,
                              BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    /*Pinmux setting for GPIO3_24 - MODE_SEL_TDO */
    Bsp_platformSetPinmuxRegs((UInt32) 14U,
                              CTRL_CORE_PAD_IO_RGMII0_TXD0,
                              BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    /*Pinmux setting for GPIO3_25 - MODE_SEL_SYNC_OUT */
    Bsp_platformSetPinmuxRegs((UInt32) 14U,
                              CTRL_CORE_PAD_IO_RGMII0_RXC,
                              BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    /*Pinmux setting for GPIO3_26 - MODE_SEL_PMIC_CLKOUT */
    Bsp_platformSetPinmuxRegs((UInt32) 14U,
                              CTRL_CORE_PAD_IO_RGMII0_RXCTL,
                              BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    /* Set the McSPI pin Mux */
    Bsp_boardSetPinMux(BSP_DRV_ID_MCSPI,
                       BSP_DEVICE_MCSPI_INST_ID_0, BSP_BOARD_MODE_DEFAULT);

    /* UART 2 for printfs as MCSPI is being used */
    Bsp_boardSetPinMux(BSP_DRV_ID_UART, BSP_DEVICE_UART_INST_ID_1,
                       BSP_BOARD_MODE_DEFAULT);

#elif defined (BOARD_TYPE_TDA3XX_AR12_ALPS)
    /*Pinmux setting for GPIO4_15 - Host Interrupt Input */
    Bsp_platformSetPinmuxRegs((UInt32) 14U,
                              CTRL_CORE_PAD_IO_UART1_CTSN,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
    /*Pinmux setting for GPIO2_7 - NRESET */
    Bsp_platformSetPinmuxRegs((UInt32) 14U,
                              CTRL_CORE_PAD_IO_VIN1A_D4,
                              BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    /*Pinmux setting for GPIO2_6 - Warm Reset */
    Bsp_platformSetPinmuxRegs((UInt32) 14U,
                              CTRL_CORE_PAD_IO_VIN1A_D3,
                              BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    /*Pinmux setting for GPIO1_5 - MODE_SEL_TDO */
    Bsp_platformSetPinmuxRegs((UInt32) 14U,
                              CTRL_CORE_PAD_IO_GPMC_WEN,
                              BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    /*Pinmux setting for GPIO1_4 - MODE_SEL_SYNC_OUT */
    Bsp_platformSetPinmuxRegs((UInt32) 14U,
                              CTRL_CORE_PAD_IO_GPMC_OEN_REN,
                              BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    /*Pinmux setting for GPIO1_6 - MODE_SEL_PMIC_CLKOUT */
    Bsp_platformSetPinmuxRegs((UInt32) 14U,
                              CTRL_CORE_PAD_IO_GPMC_CS0,
                              BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    /* Set the McSPI pin Mux */
    Bsp_boardSetPinMux(BSP_DRV_ID_MCSPI,
                       BSP_DEVICE_MCSPI_INST_ID_1, BSP_BOARD_MODE_DEFAULT);

    /* UART 2 for printfs */
    Bsp_boardSetPinMux(BSP_DRV_ID_UART, BSP_DEVICE_UART_INST_ID_1,
                       BSP_BOARD_MODE_DEFAULT);
    /* UART 0 for flash */
    Bsp_boardSetPinMux(BSP_DRV_ID_UART, BSP_DEVICE_UART_INST_ID_0,
                       BSP_BOARD_MODE_DEFAULT);
#else
    ; /* Do nothing */
#endif
    return (BSP_SOK);
}

#endif
