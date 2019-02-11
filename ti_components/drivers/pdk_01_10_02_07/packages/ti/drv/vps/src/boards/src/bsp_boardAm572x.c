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
 *  \file bsp_boardAm572x.c
 *
 *  \brief File containing the Am572x BSP board functions.
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
#include <ti/csl/src/ip/ecap/V0/ecap.h>
#include <ti/drv/vps/include/platforms/bsp_platform.h>
#include <ti/board/board.h>
#include <string.h>

#ifdef VPS_VIP_BUILD
#include <ti/drv/vps/include/vps_capture.h>
#endif
#ifdef VPS_DSS_BUILD
#include <ti/drv/vps/include/vps_displayCtrl.h>
#endif
#include <ti/drv/vps/include/devices/bsp_device.h>
#include <ti/drv/vps/include/boards/bsp_board.h>
#include <bsp_boardPriv.h>
#include <bsp_boardAm572x.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Max of all the devices present in the board including any valid
 * combination of base board and daughter cards */
#define BOARD_MAX_DEVICE                    (20U)

/*  GP EVM LCD GPIO mappings */
#define BOARD_GPIO_BASE_LCD                 ((UInt32) SOC_GPIO2_BASE)
#define BOARD_GPIO_PIN_LCD_PWDN             ((UInt32) 5U)
#define BOARD_GPIO_PIN_LCD_RESET            ((UInt32) 2U)
#define BOARD_GPIO_BASE_CAMERA              ((UInt32) SOC_GPIO6_BASE)
#define BOARD_GPIO_PIN_CAMERA_EN            ((UInt32) 14U)
#define BOARD_GPIO_BASE_CAMERA_RESET_AM572X_EVM   ((UInt32) SOC_GPIO4_BASE)
#define BOARD_GPIO_BASE_CAMERA_PWRDN_AM572X_EVM   ((UInt32) SOC_GPIO5_BASE)
#define BOARD_GPIO_BASE_CAMERA_VIPMUX_AM572X_EVM  ((UInt32) SOC_GPIO6_BASE)
#define BOARD_GPIO_BASE_CAMERA_CLOCK_AM572X_EVM   ((UInt32) SOC_GPIO5_BASE)

#define BOARD_GPIO_PIN_CAMERA_CLOCK_AM572X_EVM ((UInt32) 10U)
#define BOARD_GPIO_PIN_CAMERA_RESET_AM572X_EVM ((UInt32) 17U)
#define BOARD_GPIO_PIN_CAMERA_PWRDN_AM572X_EVM ((UInt32) 11U)
#define BOARD_GPIO_PIN_CAMERA_BUF_EN_AM572X_EVM ((UInt32) 11U)

#define CTRL_CORE_VIP_MUX_SELECT                        (0xECU)
#define CTRL_CORE_VIP_MUX_SELECT_VIP_SEL_1B_SHIFT       (3U)
#define CTRL_CORE_VIP_MUX_SELECT_VIP_SEL_1B_MASK        (0x00000008U)
#define CTRL_CORE_VIP_MUX_SELECT_VIP_SEL_1B_GROUP4B     (0x00000000U)

#define CTRL_CORE_PAD_MDIO_MCLK                         (uint32_t)(0x23cU)
#define CTRL_CORE_PAD_GPMC_A8                           (uint32_t)(0x60U)
#define CTRL_CORE_PAD_RGMII0_TXD1                       (uint32_t)(0x260U)
#define CTRL_CORE_PAD_MDIO_D                            (uint32_t)(0x240U)
#define CTRL_CORE_PAD_UART3_RXD                         (uint32_t)(0x248U)
#define CTRL_CORE_PAD_UART3_TXD                         (uint32_t)(0x24cU)
#define CTRL_CORE_PAD_RGMII0_TXC                        (uint32_t)(0x250U)
#define CTRL_CORE_PAD_RGMII0_TXCTL                      (uint32_t)(0x254U)
#define CTRL_CORE_PAD_RGMII0_RXC                        (uint32_t)(0x268U)
#define CTRL_CORE_PAD_RGMII0_RXCTL                      (uint32_t)(0x26cU)
#define CTRL_CORE_PAD_RGMII0_RXD3                       (uint32_t)(0x270U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/** \brief EEPROM ID structure. */

/** Max number of characters per ID entry field */
#define BOARD_MAX_ID_STR_LEN  20

/**
 *  @brief This structure contains board specific information
 */
typedef struct {

    /* Header ID of the SOC */
    UInt32 header;

    /* Name of the board */
    char boardName[BOARD_MAX_ID_STR_LEN];

    /* Board version/revision info */
    char version[BOARD_MAX_ID_STR_LEN];

    /* Board serial number */
    char serialNum[BOARD_MAX_ID_STR_LEN];

} Bsp_BoardEepromId;


static  Bsp_BoardEepromId gEepromVal;

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

static Int32 Bsp_boardPowerOnDeviceAm572xIdk (UInt32 devDrvId,
                                             UInt32 instId,
                                             UInt32 powerOn);

static Int32 Bsp_boardSetPinMuxAm572xIdk(UInt32        drvId,
                                         UInt32        instId,
                                         Bsp_BoardMode boardMode);

static Int32 Bsp_boardAm572xEnableEcap(void);

#if !defined(SOC_AM571x) && !defined(SOC_AM574x)
static Int32 Bsp_boardSetPinMuxAm572xGp(UInt32        drvId,
                                        UInt32        instId,
                                        Bsp_BoardMode boardMode);

static Int32 Bsp_boardPowerOnDeviceAm572xGp (UInt32 devDrvId,
                                             UInt32 instId,
                                             UInt32 powerOn);

static Int32 Bsp_boardAm572xEnableEHRPWM(void);
#endif

#ifdef __cplusplus
}
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static Bsp_BoardI2cInstData gBoardAm572xGPI2cInstData[] =
{
#ifndef BSP_DISABLE_I2C0
    {
        BSP_DEVICE_I2C_INST_ID_0,           /* instId */
        SOC_I2C1_BASE,                      /* baseAddr */
        CSL_INTC_EVENTID_I2CINT1,           /* intNum */
        400U                                /* busClkKHz */
    },
#endif  /* #ifndef BSP_DISABLE_I2C0 */

#ifndef BSP_DISABLE_I2C2
    {
        BSP_DEVICE_I2C_INST_ID_2,           /* instId */
        SOC_I2C3_BASE,                      /* baseAddr */
        CSL_INTC_EVENTID_I2CINT3,           /* intNum */
        400U                                /* busClkKHz */
    },
#endif  /* #ifndef BSP_DISABLE_I2C2 */
    {
        BSP_DEVICE_I2C_INST_ID_4,           /* instId */
        SOC_I2C5_BASE,                      /* baseAddr */
        CSL_INTC_EVENTID_I2CINT5,           /* intNum */
        400U                                /* busClkKHz */
    }
};

static Bsp_BoardI2cData     gBoardAm572xGPI2cData =
{
    /* numI2c */
    (sizeof (gBoardAm572xGPI2cInstData) / sizeof (Bsp_BoardI2cInstData)),
    /* i2cData */
    gBoardAm572xGPI2cInstData,
    /* probeInstId */
    BSP_DEVICE_I2C_INST_ID_0
};

static Bsp_BoardI2cInstData gBoardAm572xIdkI2cInstData[] =
{
    {
        BSP_DEVICE_I2C_INST_ID_0,           /* instId */
        SOC_I2C1_BASE,                      /* baseAddr */
        CSL_INTC_EVENTID_I2CINT1,           /* intNum */
        400U                                /* busClkKHz */
    },
    {
        BSP_DEVICE_I2C_INST_ID_2,           /* instId */
        SOC_I2C2_BASE,                      /* baseAddr */
        CSL_INTC_EVENTID_I2CINT2,           /* intNum */
        400U                                /* busClkKHz */
    }
};

static Bsp_BoardI2cData     gBoardAm572xIdkI2cData =
{
    /* numI2c */
    (sizeof (gBoardAm572xIdkI2cInstData) / sizeof (Bsp_BoardI2cInstData)),
    /* i2cData */
    gBoardAm572xIdkI2cInstData,
    /* probeInstId */
    BSP_DEVICE_I2C_INST_ID_0
};


static Bsp_BoardDeviceData  gBoardAm572xDevData[BOARD_MAX_DEVICE];

static Bsp_BoardData        gBoardAm572xData =
{
    /* numDev */
    0U,
    /* devData */
    &gBoardAm572xDevData[0U]
};

#if !defined(SOC_AM571x) && !defined(SOC_AM574x)
/* AM571x has only IDK, hence this SOC define indicates it is for IDK compilation */
static Bsp_BoardDeviceData  gBoardAm572xGpDefaultDevData[] =
    BSP_BOARD_GP_AM572X_DEFAULT_DEVDATA;

static Bsp_BoardData        gBoardAm572xGpDefaultData =
{
    /* numDev */
    (sizeof (gBoardAm572xGpDefaultDevData) / sizeof (Bsp_BoardDeviceData)),
    /* devData */
    gBoardAm572xGpDefaultDevData
};

/* Am572x interposer */
extern Bsp_BoardData        gBoardAm572xGpDefaultData;

#endif

#if defined (SOC_AM572x) || defined (SOC_AM574x)
static Bsp_BoardDeviceData  gBoardAm572xIdkDefaultDevData[] =
    BSP_BOARD_IDK_AM57XX_DEFAULT_DEVDATA;

static Bsp_BoardData        gBoardAm572xIdkDefaultData =
{
    /* numDev */
    (sizeof (gBoardAm572xIdkDefaultDevData) / sizeof (Bsp_BoardDeviceData)),
    /* devData */
    gBoardAm572xIdkDefaultDevData
};
#else
static Bsp_BoardDeviceData  gBoardAm571xIdkDefaultDevData[] =
    BSP_BOARD_IDK_AM57XX_DEFAULT_DEVDATA;

static Bsp_BoardData        gBoardAm571xIdkDefaultData =
{
    /* numDev */
    (sizeof (gBoardAm571xIdkDefaultDevData) / sizeof (Bsp_BoardDeviceData)),
    /* devData */
    gBoardAm571xIdkDefaultDevData
};
#endif

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
Int32 Bsp_boardAm572xInit(void)
{
   /* Moving the board init to application for AM devices to be at par
      with other driver examples */
   return (BSP_SOK);
}

Bsp_BoardId Bsp_boardGetIdAm572x(void)
{
    Bsp_BoardId             boardId = BSP_BOARD_UNKNOWN;
    Board_IDInfo            id;
    Board_STATUS            ret;
    Int32                   retVal;
#ifndef BSP_DISABLE_I2C0

    ret = Board_getIDInfo(&id);
    if (ret == BOARD_SOK)
    {
        retVal = BSP_SOK;
    }
    else
    {
        retVal = BSP_EFAIL;
    }

    if (FVID2_SOK == retVal)
    {
        if ( (id.boardName[5] == 'I') &&
             (id.boardName[6] == 'D') )
        {
            boardId = BSP_BOARD_IDK_AM57XX;
        }

        if ( (id.boardName[5] == 'P') &&
             (id.boardName[6] == 'M') )
        {
            boardId = BSP_BOARD_GP_AM572X;
        }
    }
#endif

    /* store the eeprom read values for future use */
    memcpy (&gEepromVal.header, &id.header, sizeof(UInt32));
    memcpy (&gEepromVal.boardName, &id.boardName, BOARD_MAX_ID_STR_LEN);
    memcpy (&gEepromVal.version, &id.version, BOARD_MAX_ID_STR_LEN);

    return (boardId);
}

Bsp_BoardRev Bsp_boardGetBaseBoardRevAm572x(void)
{
    Bsp_BoardRev      boardRev = BSP_BOARD_REV_UNKNOWN;

#ifndef BSP_DISABLE_I2C0

    {
        if (gEepromVal.header == 0xEE3355AAU)
        {
            GT_1trace(BspBoardTrace, GT_INFO,
                      " EEPROM Base Board Name: [%s]\n", gEepromVal.boardName);
            switch (gEepromVal.version[0])
            {
                case 'A':
                    boardRev = BSP_BOARD_REV_A;
                    break;

                case '1':
                    if ( (gEepromVal.version[1] == '.') &&
                         (gEepromVal.version[2] == '3') &&
                         (gEepromVal.version[3] == 'A') )
                        boardRev = BSP_BOARD_REV_1P3A;
                    break;

                default:
                    boardRev = BSP_BOARD_REV_UNKNOWN;
                    break;
            }
        }
        else
        {
            GT_0trace(BspBoardTrace, GT_INFO,
                      " EEPROM Board Info Header Mismatch!!\n");
        }
     }
#endif

    return (boardRev);
}

Bsp_BoardRev Bsp_boardGetDcRevAm572x(void)
{
    return (BSP_BOARD_REV_A);
}

const Bsp_BoardI2cData *Bsp_boardGetI2cDataAm572x(void)
{
    Bsp_BoardId boardId = Bsp_boardGetId();
    Bsp_BoardI2cData     *i2cData;

    if (BSP_BOARD_IDK_AM57XX == boardId)
    {
      i2cData = &gBoardAm572xIdkI2cData;
    }
    else
    {
      i2cData = &gBoardAm572xGPI2cData;
    }

    return (i2cData);
}

const Bsp_BoardData *Bsp_boardGetDataAm572x(void)
{
    UInt32               numDev;
    Bsp_BoardId          boardId;
    Bsp_BoardData       *boardData;
    Bsp_BoardDeviceData *tempDevData;

    boardId   = Bsp_boardGetId();
    boardData = &gBoardAm572xData;

    /* Copy only for the first time */
    if (0U == boardData->numDev)
    {
        /* Copy the individual board data to global board data as per
         * hierarchy */
        numDev      = 0U;
        tempDevData = &gBoardAm572xDevData[0U];
        switch (boardId)
        {
#if !defined(SOC_AM571x) && !defined(SOC_AM574x)
            case BSP_BOARD_GP_AM572X:
                numDev += gBoardAm572xGpDefaultData.numDev;
                /* Array bound check */
                GT_assert(BspBoardTrace, numDev < BOARD_MAX_DEVICE);
                BspUtils_memcpy(
                    tempDevData,
                    gBoardAm572xGpDefaultData.devData,
                    (sizeof (Bsp_BoardDeviceData) *
                     gBoardAm572xGpDefaultData.numDev));
                tempDevData += gBoardAm572xGpDefaultData.numDev;
                break;
#endif
            case BSP_BOARD_IDK_AM57XX:
#if defined(SOC_AM571x)
                numDev += gBoardAm571xIdkDefaultData.numDev;
                /* Array bound check */
                GT_assert(BspBoardTrace, numDev < BOARD_MAX_DEVICE);
                BspUtils_memcpy(
                    tempDevData,
                    gBoardAm571xIdkDefaultData.devData,
                    (sizeof (Bsp_BoardDeviceData) *
                     gBoardAm571xIdkDefaultData.numDev));
                tempDevData += gBoardAm571xIdkDefaultData.numDev;
#else
                numDev += gBoardAm572xIdkDefaultData.numDev;
                /* Array bound check */
                GT_assert(BspBoardTrace, numDev < BOARD_MAX_DEVICE);
                BspUtils_memcpy(
                    tempDevData,
                    gBoardAm572xIdkDefaultData.devData,
                    (sizeof (Bsp_BoardDeviceData) *
                     gBoardAm572xIdkDefaultData.numDev));
                tempDevData += gBoardAm572xIdkDefaultData.numDev;
#endif
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


Int32 Bsp_boardSetPinMuxAm572x(
    UInt32        drvId,
    UInt32        instId,
    Bsp_BoardMode boardMode)
{
      Int32 retVal;

      Bsp_BoardId   boardId = Bsp_boardGetId();

      if (boardId == BSP_BOARD_GP_AM572X)
      {
#if  defined(SOC_AM571x) || defined (SOC_AM574x)
          retVal = FVID2_SOK;
#else
          retVal = Bsp_boardSetPinMuxAm572xGp(drvId, instId, boardMode);
#endif
      }
      else if ( (boardId == BSP_BOARD_IDK_AM57XX))
      {
          retVal = Bsp_boardSetPinMuxAm572xIdk(drvId, instId, boardMode);
      }
      else
      {
          retVal = FVID2_EFAIL;
      }

      return (retVal);
}

#if !defined(SOC_AM571x) && !defined(SOC_AM574x)
Int32 Bsp_boardSetPinMuxAm572xGp(
    UInt32        drvId,
    UInt32        instId,
    Bsp_BoardMode boardMode)
{

#ifdef VPS_VIP_BUILD
       Bsp_BoardId          boardId;
       boardId   = Bsp_boardGetId();
#endif

#ifdef VPS_DSS_BUILD
        if ((FVID2_VPS_DCTRL_DRV == drvId) && (VPS_DSS_DISPC_OVLY_DPI1 == instId))
        {
            Bsp_boardAm572xEnableEHRPWM();

            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_CLK,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_DE,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_FLD,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U,
                                      (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_HSYNC,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U,
                                      (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_VSYNC,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_D0,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_D1,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_D2,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_D3,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_D4,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_D5,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_D6,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_D7,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_D8,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_D9,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_D10,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_D11,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_D12,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_D13,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_D14,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_D15,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_D16,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_D17,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_D18,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_D19,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_D20,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_D21,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_D22,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_D23,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);

            /* 0xA: ehrpwm2A : MUX MODE */
            Bsp_platformSetPinmuxRegs((UInt32) 10U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_GPIO6_10,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        }

        if ((FVID2_VPS_DCTRL_DRV == drvId) && (VPS_DSS_DISPC_OVLY_HDMI == instId))
        {
            /* I2C mux */
            Bsp_platformSetPinmuxRegs((UInt32) 0x01U,
                                      (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_I2C2_SDA,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);

            Bsp_platformSetPinmuxRegs((UInt32) 0x01U,
                                      (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_I2C2_SCL,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);

            /* HDMI1 mux */
            Bsp_platformSetPinmuxRegs((UInt32) 0x06U,
                                      (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_SPI1_CS2,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);

            Bsp_platformSetPinmuxRegs((UInt32) 0x06U,
                                      (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_SPI1_CS3,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        }
#endif

#ifdef VPS_VIP_BUILD

        if (FVID2_VPS_CAPT_VID_DRV == drvId)
        {
            if (BSP_BOARD_GP_AM572X == boardId)
            {
                /* VIN3A mux for group 3a*/
                Bsp_platformSetPinmuxRegs((UInt32) 0x02U,
                                          (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A10,
                                          BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);

                Bsp_platformSetPinmuxRegs((UInt32) 0x02U,
                                          (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A9,
                                          BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);

                Bsp_platformSetPinmuxRegs((UInt32) 0x02U,
                                          (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A8,
                                          BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);

                Bsp_platformSetPinmuxRegs((UInt32) 0x02U,
                                          (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A11,
                                          BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);

                Bsp_platformSetPinmuxRegs((UInt32) 0x02U,
                                          (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A12,
                                          BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);


                Bsp_platformSetPinmuxRegs((UInt32) 0x06U,
                                          (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VIN1A_D16,
                                          BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);

                Bsp_platformSetPinmuxRegs((UInt32) 0x06U,
                                          (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VIN1A_D17,
                                          BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);

                Bsp_platformSetPinmuxRegs((UInt32) 0x06U,
                                          (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VIN1A_D18,
                                          BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);

                Bsp_platformSetPinmuxRegs((UInt32) 0x06U,
                                          (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VIN1A_D19,
                                          BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);

                Bsp_platformSetPinmuxRegs((UInt32) 0x06U,
                                          (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VIN1A_D20,
                                          BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);

                Bsp_platformSetPinmuxRegs((UInt32) 0x06U,
                                          (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VIN1A_D21,
                                          BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);

                Bsp_platformSetPinmuxRegs((UInt32) 0x06U,
                                          (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VIN1A_D22,
                                          BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);

                Bsp_platformSetPinmuxRegs((UInt32) 0x06U,
                                          (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VIN1A_D23,
                                          BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);

                Bsp_platformSetPinmuxRegs((UInt32) 0x02U,
                                          (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A0,
                                          BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);

                Bsp_platformSetPinmuxRegs((UInt32) 0x02U,
                                          (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A1,
                                           BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);

                Bsp_platformSetPinmuxRegs((UInt32) 0x02U,
                                          (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A2,
                                          BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);

                Bsp_platformSetPinmuxRegs((UInt32) 0x02U,
                                          (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A3,
                                          BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);

                Bsp_platformSetPinmuxRegs((UInt32) 0x02U,
                                          (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A4,
                                          BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);

                Bsp_platformSetPinmuxRegs((UInt32) 0x02U,
                                          (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A5,
                                          BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);

                Bsp_platformSetPinmuxRegs((UInt32) 0x02U,
                                          (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A6,
                                          BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);

                Bsp_platformSetPinmuxRegs((UInt32) 0x02U,
                                          (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A7,
                                          BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            }
        }
#endif


    return (FVID2_SOK);
}

#endif

Int32 Bsp_boardSetPinMuxAm572xIdk(
    UInt32        drvId,
    UInt32        instId,
    Bsp_BoardMode boardMode)
{

#ifdef VPS_VIP_BUILD
       Bsp_BoardId          boardId;
       boardId   = Bsp_boardGetId();
#endif
#ifdef VPS_DSS_BUILD
        if ((FVID2_VPS_DCTRL_DRV == drvId) && (VPS_DSS_DISPC_OVLY_DPI1 == instId))
        {
            Bsp_boardAm572xEnableEcap();

                /* I2C mux */
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_I2C1_SDA,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_I2C1_SCL,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);

            /* vout1 MUX */
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_CLK,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_DE,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_FLD,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U,
                                      (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_HSYNC,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U,
                                      (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_VSYNC,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_D0,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_D1,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_D2,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_D3,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_D4,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_D5,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_D6,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_D7,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_D8,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_D9,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_D10,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_D11,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_D12,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_D13,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_D14,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_D15,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_D16,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_D17,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_D18,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_D19,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_D20,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_D21,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_D22,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs((UInt32) 0U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VOUT1_D23,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);

            /* 0xA: eCAP1_in_PWM1_out */
            Bsp_platformSetPinmuxRegs((UInt32) 10U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_VIN2A_D2,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);

            /* 0x9: clkout3 */
            Bsp_platformSetPinmuxRegs((UInt32) 9U, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_XREF_CLK3,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        }

        if ((FVID2_VPS_DCTRL_DRV == drvId) && (VPS_DSS_DISPC_OVLY_HDMI == instId))
        {
            /* I2C mux */
            Bsp_platformSetPinmuxRegs((UInt32) 0x01U,
                                      (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_I2C2_SDA,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);

            Bsp_platformSetPinmuxRegs((UInt32) 0x01U,
                                      (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_I2C2_SCL,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);

            /* HDMI1 mux */
            Bsp_platformSetPinmuxRegs((UInt32) 0x06U,
                                      (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_SPI1_CS2,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);

            Bsp_platformSetPinmuxRegs((UInt32) 0x06U,
                                      (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_SPI1_CS3,
                                      BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        }
#endif

#ifdef VPS_VIP_BUILD

    if (FVID2_VPS_CAPT_VID_DRV == drvId)
    {
        if (BSP_BOARD_IDK_AM57XX == boardId)
        {
#if defined (SOC_AM571x)
            /* Set the VIN mux at control module level */
            HW_WR_FIELD32(
                (SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                 CTRL_CORE_VIP_MUX_SELECT),
                CTRL_CORE_VIP_MUX_SELECT_VIP_SEL_1B,
                CTRL_CORE_VIP_MUX_SELECT_VIP_SEL_1B_GROUP4B);
#endif
            /* VIN1B mux for group 4b*/
            Bsp_platformSetPinmuxRegs((UInt32) 0x06U,
                                      (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A10,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);

            Bsp_platformSetPinmuxRegs((UInt32) 0x06U,
                                      (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A9,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);

            Bsp_platformSetPinmuxRegs((UInt32) 0x06U,
                                      (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A8,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);

            Bsp_platformSetPinmuxRegs((UInt32) 0x06U,
                                      (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A11,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);

            Bsp_platformSetPinmuxRegs((UInt32) 0x06U,
                                      (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A12,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);

            Bsp_platformSetPinmuxRegs((UInt32) 0x06U,
                                      (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A0,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);

            Bsp_platformSetPinmuxRegs((UInt32) 0x06U,
                                      (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A1,
                                       BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);

            Bsp_platformSetPinmuxRegs((UInt32) 0x06U,
                                      (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A2,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);

            Bsp_platformSetPinmuxRegs((UInt32) 0x06U,
                                      (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A3,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);

            Bsp_platformSetPinmuxRegs((UInt32) 0x06U,
                                      (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A4,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);

            Bsp_platformSetPinmuxRegs((UInt32) 0x06U,
                                      (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A5,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);

            Bsp_platformSetPinmuxRegs((UInt32) 0x06U,
                                      (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A6,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);

            Bsp_platformSetPinmuxRegs((UInt32) 0x06U,
                                      (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A7,
                                      BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
        }
    }

#endif

    return (FVID2_SOK);
}

#if !defined(SOC_AM571x) && !defined(SOC_AM574x)
static Int32 Bsp_boardPowerOnDeviceAm572xGp(UInt32 devDrvId,
                                          UInt32 instId,
                                          UInt32 powerOn)
{

    if (FVID2_LCD_CTRL_DRV == devDrvId)
    {
         /* 0x15: GPMC A15 Mux Mode to gpio2_5 */
         Bsp_platformSetPinmuxRegs((UInt32) 0x0004000EU, \
                                   (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A15, \
                                   BSP_PLATFORM_IOPAD_CFG_DEFAULT);

        /* Enable GPIO required for LCD power on for GP EVM */
          GPIOModuleEnable(BOARD_GPIO_BASE_LCD);

          GPIODirModeSet(
              BOARD_GPIO_BASE_LCD,
              BOARD_GPIO_PIN_LCD_PWDN,
              GPIO_DIR_OUTPUT);

          if (powerOn == (UInt32) TRUE)
          {
              GPIOPinWrite(
                  BOARD_GPIO_BASE_LCD,
                  BOARD_GPIO_PIN_LCD_PWDN,
                  GPIO_PIN_HIGH);
          }
          else
          {
              GPIOPinWrite(
                  BOARD_GPIO_BASE_LCD,
                  BOARD_GPIO_PIN_LCD_PWDN,
                  GPIO_PIN_LOW);
          }

           BspOsal_sleep(0x10);

          /* 0x15: GPMC A12 Mux Mode to gpio2_2 */
          Bsp_platformSetPinmuxRegs((UInt32) 0x0006000EU, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A12,
                                    BSP_PLATFORM_IOPAD_CFG_DEFAULT);

          /* Global reset for LCD - normally to stay high, enter low for reset */
          GPIODirModeSet(
              BOARD_GPIO_BASE_LCD,
              BOARD_GPIO_PIN_LCD_RESET,
              GPIO_DIR_OUTPUT);

          GPIOPinWrite(
              BOARD_GPIO_BASE_LCD,
              BOARD_GPIO_PIN_LCD_RESET,
              GPIO_PIN_LOW);

             BspOsal_sleep(0x10);

          GPIOPinWrite(
              BOARD_GPIO_BASE_LCD,
              BOARD_GPIO_PIN_LCD_RESET,
              GPIO_PIN_HIGH);

           BspOsal_sleep(0x10);
    }

#ifdef VPS_VIP_BUILD
        if (FVID2_VID_SENSOR_OV1063X_DRV == devDrvId)
        {
            Bsp_platformSetPinmuxRegs((UInt32) 0x0EU, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_GPIO6_11,
                                     BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_UP);

            Bsp_platformSetPinmuxRegs((UInt32) 0x0EU, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_MCASP1_AXR11,
                                     BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_UP);

            Bsp_platformSetPinmuxRegs((UInt32) 0x0EU, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_MCASP1_AXR8,
                                     BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_UP);

            Bsp_platformSetPinmuxRegs((UInt32) 0x0EU, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_MCASP1_AXR9,
                                     BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_UP);

            /* Enable GPIO required for Camera operations for GP EVM */
              GPIOModuleEnable(BOARD_GPIO_BASE_CAMERA_RESET_AM572X_EVM);
              GPIOModuleEnable(BOARD_GPIO_BASE_CAMERA_PWRDN_AM572X_EVM);
              GPIOModuleEnable(BOARD_GPIO_BASE_CAMERA_VIPMUX_AM572X_EVM);

              GPIODirModeSet(
                  BOARD_GPIO_BASE_CAMERA_RESET_AM572X_EVM,
                  BOARD_GPIO_PIN_CAMERA_RESET_AM572X_EVM,
                  GPIO_DIR_OUTPUT);

              GPIODirModeSet(
                  BOARD_GPIO_BASE_CAMERA_PWRDN_AM572X_EVM,
                  BOARD_GPIO_PIN_CAMERA_PWRDN_AM572X_EVM,
                  GPIO_DIR_OUTPUT);

              GPIODirModeSet(
                  BOARD_GPIO_BASE_CAMERA_CLOCK_AM572X_EVM,
                  BOARD_GPIO_PIN_CAMERA_CLOCK_AM572X_EVM,
                  GPIO_DIR_OUTPUT);

              GPIODirModeSet(
                  BOARD_GPIO_BASE_CAMERA_VIPMUX_AM572X_EVM,
                  BOARD_GPIO_PIN_CAMERA_BUF_EN_AM572X_EVM,
                  GPIO_DIR_OUTPUT);

              BspOsal_sleep(0x10);

              if (powerOn == (UInt32) TRUE)
              {
                  /* start the camera clock */
                  GPIOPinWrite(
                      BOARD_GPIO_BASE_CAMERA_CLOCK_AM572X_EVM,
                      BOARD_GPIO_PIN_CAMERA_CLOCK_AM572X_EVM,
                      GPIO_PIN_HIGH);

                  /* Power down */
                  GPIOPinWrite(
                       BOARD_GPIO_BASE_CAMERA_PWRDN_AM572X_EVM,
                       BOARD_GPIO_PIN_CAMERA_PWRDN_AM572X_EVM,
                       GPIO_PIN_HIGH);

                  /* Need to atleast wait for 200 micro seconds to release reset */
                  BspOsal_sleep(0x1000);

                  GPIOPinWrite(
                       BOARD_GPIO_BASE_CAMERA_RESET_AM572X_EVM,
                       BOARD_GPIO_PIN_CAMERA_RESET_AM572X_EVM,
                       GPIO_PIN_HIGH);

               /* camera buffer enable, set mux to enable VIP data lines */
                  GPIOPinWrite(
                        BOARD_GPIO_BASE_CAMERA_VIPMUX_AM572X_EVM,
                        BOARD_GPIO_PIN_CAMERA_BUF_EN_AM572X_EVM,
                        GPIO_PIN_LOW);
              }
              else
              {
                  /* camera buffer disable, reset mux to enable VIP data lines */
                  GPIOPinWrite(
                         BOARD_GPIO_BASE_CAMERA_VIPMUX_AM572X_EVM,
                         BOARD_GPIO_PIN_CAMERA_BUF_EN_AM572X_EVM,
                         GPIO_PIN_HIGH);

                  /* reset high */
                  GPIOPinWrite(
                       BOARD_GPIO_BASE_CAMERA_RESET_AM572X_EVM,
                       BOARD_GPIO_PIN_CAMERA_RESET_AM572X_EVM,
                       GPIO_PIN_LOW);

                  BspOsal_sleep(0x100);

                  /* Power down */
                  GPIOPinWrite(
                       BOARD_GPIO_BASE_CAMERA_PWRDN_AM572X_EVM,
                       BOARD_GPIO_PIN_CAMERA_PWRDN_AM572X_EVM,
                       GPIO_PIN_LOW);

                  /* stop the camera clock */
                  GPIOPinWrite(
                      BOARD_GPIO_BASE_CAMERA_CLOCK_AM572X_EVM,
                      BOARD_GPIO_PIN_CAMERA_CLOCK_AM572X_EVM,
                      GPIO_PIN_LOW);
              }

              BspOsal_sleep(0x10);
        }
#endif


    return (BSP_SOK);
}
#endif

static Int32 Bsp_boardPowerOnDeviceAm572xIdk(UInt32 devDrvId,
                                          UInt32 instId,
                                          UInt32 powerOn)
{

#ifdef VPS_VIP_BUILD
    if (FVID2_VID_SENSOR_OV2659_DRV == devDrvId)
    {
        Bsp_platformSetPinmuxRegs((UInt32) 0x0EU, (UInt32) CSL_CONTROL_CORE_PAD_IO_PAD_GPIO6_14,
                                 BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_UP);

        /* Enable GPIO required for Camera power on for IDK EVM */
          GPIOModuleEnable(BOARD_GPIO_BASE_CAMERA);
          GPIODirModeSet(
              BOARD_GPIO_BASE_CAMERA,
              BOARD_GPIO_PIN_CAMERA_EN,
              GPIO_DIR_OUTPUT);

          BspOsal_sleep(0x10);

          if (powerOn == (UInt32) TRUE)
          {
              GPIOPinWrite(
                  BOARD_GPIO_BASE_CAMERA,
                  BOARD_GPIO_PIN_CAMERA_EN,
                  GPIO_PIN_LOW);
          }
          else
          {
              GPIOPinWrite(
                  BOARD_GPIO_BASE_CAMERA,
                  BOARD_GPIO_PIN_CAMERA_EN,
                  GPIO_PIN_HIGH);
          }

          BspOsal_sleep(0x10);
    }
#endif

   return (FVID2_SOK);
}

static Int32 Bsp_boardAm572xEnableEcap(void)
{
  Int32 retVal = BSP_SOK;

  /* Step 1. Initialize ECAP */

  /* Enable Interface and Module Clocks for PWMSS */

    HW_WR_REG32(SOC_L4PER_CM_CORE_BASE + CM_L4PER2_PWMSS1_CLKCTRL, CM_L4PER2_PWMSS1_CLKCTRL_MODULEMODE_ENABLE);

    while(CM_L4PER2_PWMSS1_CLKCTRL_MODULEMODE_ENABLE !=
            (HWREG(SOC_L4PER_CM_CORE_BASE + CM_L4PER2_PWMSS1_CLKCTRL) &
            CM_L4PER2_PWMSS1_CLKCTRL_MODULEMODE_MASK));

    while((CM_L4PER2_PWMSS1_CLKCTRL_IDLEST_FUNC <<
            CM_L4PER2_PWMSS1_CLKCTRL_IDLEST_SHIFT) !=
            (HWREG(SOC_L4PER_CM_CORE_BASE + CM_L4PER2_PWMSS1_CLKCTRL) &
            CM_L4PER2_PWMSS1_CLKCTRL_IDLEST_MASK));

  /* Enable Clock */
  ECAPClockEnable(SOC_PWMSS1_IPWMSS_BASE);

  /* Configure ECAP to Generate PWM wave form */
  ECAPOperatingModeSelect(SOC_PWMSS1_IECAP_BASE, ECAP_APWM_MODE);

  /* Set Counter */
  ECAPCounterConfig(SOC_PWMSS1_IECAP_BASE, 0);

  /* Configure ECAP_PWM_OUT pin as LOW */
  ECAPAPWMPolarityConfig(SOC_PWMSS1_IECAP_BASE, ECAP_APWM_ACTIVE_LOW);

  return (retVal);

}

#if !defined(SOC_AM571x) && !defined(SOC_AM574x)
static Int32 Bsp_boardAm572xEnableEHRPWM(void)
{
   UInt32 reg;
   UInt16 reg16, pwmss_aqctl_chana_polnormal = 0U;
  /* Enable Interface and Module Clocks for PWMSS2 */

    HW_WR_REG32(SOC_L4PER_CM_CORE_BASE + CM_L4PER2_PWMSS2_CLKCTRL, CM_L4PER2_PWMSS2_CLKCTRL_MODULEMODE_ENABLE);

    while(CM_L4PER2_PWMSS2_CLKCTRL_MODULEMODE_ENABLE !=
            (HWREG(SOC_L4PER_CM_CORE_BASE + CM_L4PER2_PWMSS2_CLKCTRL) &
            CM_L4PER2_PWMSS2_CLKCTRL_MODULEMODE_MASK));

    while((CM_L4PER2_PWMSS2_CLKCTRL_IDLEST_FUNC <<
            CM_L4PER2_PWMSS2_CLKCTRL_IDLEST_SHIFT) !=
            (HWREG(SOC_L4PER_CM_CORE_BASE + CM_L4PER2_PWMSS2_CLKCTRL) &
            CM_L4PER2_PWMSS2_CLKCTRL_IDLEST_MASK));

    /*Set PWMSSn_TBCLKEN = 0. This will stop the time-base clock within any enabled ePWMx module */
    reg =  HW_RD_REG32(0x4A002558U);
    reg &= ~0x00200000U;
    HW_WR_REG32(0x4A002558U, reg);


    /* Changes to shadow mode (Load on event counter equals zero) */
    HW_WR_REG16(SOC_PWMSS2_IEPWM_BASE + PWMSS_EPWM_AQSFRC, 0);

    /* Forcing disabled, that is, has no effect */
    HW_WR_REG16(SOC_PWMSS2_IEPWM_BASE + PWMSS_EPWM_AQCSFRC,0);

    /*
     * Configure PWM output to HIGH/LOW level on counter
     * reaches compare register value and LOW/HIGH level
     * on counter value reaches period register value and
     * zero value on counter
     */
     reg16 = HW_RD_REG16(SOC_PWMSS2_IEPWM_BASE + PWMSS_EPWM_AQCTLA);
     pwmss_aqctl_chana_polnormal = (PWMSS_EPWM_AQCTLA_CAU_CLEAR   << PWMSS_EPWM_AQCTLA_CAU_SHIFT) |
                                   (PWMSS_EPWM_AQCTLA_PRD_SET     << PWMSS_EPWM_AQCTLB_PRD_SHIFT) |
                                   (PWMSS_EPWM_AQCTLA_ZRO_SET     << PWMSS_EPWM_AQCTLA_ZRO_SHIFT);
     reg16 &= ~pwmss_aqctl_chana_polnormal;
     reg16 |= pwmss_aqctl_chana_polnormal;
     HW_WR_REG16(SOC_PWMSS2_IEPWM_BASE + PWMSS_EPWM_AQCTLA, reg16) ;

    /* Update clock prescaler values */
     reg16 = HW_RD_REG16(SOC_PWMSS2_IEPWM_BASE + PWMSS_EPWM_TBCTL);
     reg16 &= ~0x1F;
     HW_WR_REG16(SOC_PWMSS2_IEPWM_BASE + PWMSS_EPWM_TBCTL, reg16);

    /* Configure shadow loading on Period register */
    reg16 &= ~0x0008;
    HW_WR_REG16(SOC_PWMSS2_IEPWM_BASE + PWMSS_EPWM_TBCTL, reg16);


     /* Set Counter */
    HW_WR_REG16(SOC_PWMSS2_IEPWM_BASE + PWMSS_EPWM_TBCNT, 0);

    /* Configure ehrpwm counter for up-count mode */
    reg16 &= ~0x03;
    HW_WR_REG16(SOC_PWMSS2_IEPWM_BASE + PWMSS_EPWM_TBCTL, reg16);

    /* Simultaneously set bits PWMSSn_TBCLKEN to 0b1 (where n = 1 to 3) 1.*/
    reg =  HW_RD_REG32(0x4A002558U);
    reg |= 0x00200000U;
    HW_WR_REG32(0x4A002558U, reg);

  return (BSP_SOK);
}
#endif

/* nothing past this point */
