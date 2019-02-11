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
 *  \file bsputils_lvds.c
 *
 *  \brief This file implements application level lvds related helper functions.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>

#if defined (BARE_METAL)
#include <ti/csl/tistdtypes.h>
#else
#include <xdc/std.h>
#endif

#include <stdint.h>
#include <ti/csl/hw_types.h>
#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/bsp_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/vps/include/common/bsp_common.h>
#include <ti/drv/vps/include/vps_control.h>
#include <ti/drv/vps/include/boards/bsp_board.h>
#include <ti/drv/vps/include/devices/bsp_device.h>
#include <ti/drv/vps/examples/utility/bsputils_app.h>
#include <ti/drv/vps/examples/utility/bsputils_lvds.h>
#include <ti/drv/vps/examples/utility/bsputils_mem.h>
#include <ti/drv/vps/examples/utility/bsputils_prf.h>
#include <ti/csl/soc.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Uncomment below to enable IMI v2 camera support. By default this is disabled
 * as the changes for supporting IMI2 is not backward compatible with ov1063x
 * camera module. IMI v1 camera works with this enabled or disabled. */
/* #define BSPUTILS_LVDS_IMI2_CAM_ENABLE */

#define BSPUTILS_MULDES_LOCK_CHECK_COUNT    (50U)
#define BSPUTILS_SER_RESET_CHECK_COUNT      (50U)

/* Sil9127 hdmi receiver Address */
#define BSPUTILS_SIL9127_ADDR           (0x31U)

#define BSPUTILS_MULTIDES_IO_EXP_ADDR_0 (0x27U)
#define BSPUTILS_MULTIDES_IO_EXP_ADDR_1 (0x21U)
#define BSPUTILS_MULTIDES_IO_EXP_ADDR_2 (0x25U)

/* Deserializers Addresses */
#if defined (TDA2XX_MC_BUILD)
#define BSPUTILS_DES1_ADDR              (0x65U) /* 0xC0/2 */
#define BSPUTILS_DES2_ADDR              (0x6AU) /* 0xC8/2 */
#define BSPUTILS_DES3_ADDR              (0x6FU) /* 0xD0/2 */
#define BSPUTILS_DES4_ADDR              (0x69U) /* 0xD2/2 */
#else
#define BSPUTILS_DES1_ADDR              (0x60U) /* 0xC0/2 */
#define BSPUTILS_DES2_ADDR              (0x64U) /* 0xC8/2 */
#define BSPUTILS_DES3_ADDR              (0x68U) /* 0xD0/2 */
#define BSPUTILS_DES4_ADDR              (0x6CU) /* 0xD8/2 */
#define BSPUTILS_DES5_ADDR              (0x61U) /* 0xC2/2 */
#define BSPUTILS_DES6_ADDR              (0x69U) /* 0xD2/2 */
#endif

/* Serializers addresses */
#define BSPUTILS_SER1_ALIAS_ADDR        (0x74U) /* 0xE8/2 */
#define BSPUTILS_SER2_ALIAS_ADDR        (0x75U) /* 0xEA/2 */
#define BSPUTILS_SER3_ALIAS_ADDR        (0x76U) /* 0xEC/2 */
#define BSPUTILS_SER4_ALIAS_ADDR        (0x77U) /* 0xEE/2 */
#define BSPUTILS_SER5_ALIAS_ADDR        (0x78U) /* 0xF0/2 */
#define BSPUTILS_SER6_ALIAS_ADDR        (0x79U) /* 0xF2/2 */

#define BSPUTILS_SER_ID_ADDR            (0x58U) /* 0xB0/2 */

/* Alias address of 6 OV sensors present in LVDS setup */
#define BSPUTILS_OV1063x_1_ALIAS_I2C_ADDR   (0x38U) /* 0x70/2 */
#define BSPUTILS_OV1063x_2_ALIAS_I2C_ADDR   (0x39U) /* 0x72/2 */
#define BSPUTILS_OV1063x_3_ALIAS_I2C_ADDR   (0x3AU) /* 0x74/2 */
#define BSPUTILS_OV1063x_4_ALIAS_I2C_ADDR   (0x3BU) /* 0x76/2 */
#define BSPUTILS_OV1063x_5_ALIAS_I2C_ADDR   (0x3CU) /* 0x78/2 */
#define BSPUTILS_OV1063x_6_ALIAS_I2C_ADDR   (0x3DU) /* 0x7A/2 */

#define BSPUTILS_OV1063x_I2C_ADDR       (0x30U)     /* 0x60/2 */

#if defined (TDA2XX_MC_BUILD)
#define BSPUTILS_MAX_DES_SER_COUNT      (4U)
#else
#define BSPUTILS_MAX_DES_SER_COUNT      (6U)
#endif

#define BSP_BOARD_MONSTERCAM_MAIN_IMAGER_OVINSTID    (3U)

/* Data Structures */
typedef struct
{
    UInt8 nRegAddr;
    UInt8 nRegValue;
} BspUtils_I2cParams;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static Int32 BspUtils_appConfSer(UInt32 devInstId, UInt32 i2cDevAddr);
static Int32 BspUtils_appConfMultiDeSer(UInt32 devInstId, UInt32 i2cDevAddr);

static Int32 BspUtils_appMultiDesIoExpConfig(UInt32 devDrvId,
                                             UInt32 devInstId,
                                             UInt32 i2cDevAddr);

static Int32 BspUtils_appDeConfSer(UInt32 devInstId, UInt32 i2cDevAddr);
static Int32 BspUtils_appDeConfMultiDeSer(UInt32 devInstId, UInt32 i2cDevAddr);

static UInt32 BspUtils_appConvToOvInstId(UInt32 devDrvId, UInt32 devInstId);

static Int32 BspUtils_appPrintReg(UInt32 devInstId,
                                  UInt32 i2cDevAddr,
                                  UInt8  nRegAddr);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
#if defined (TDA2XX_MC_BUILD)
static UInt32 gSerDesInitDone[BSPUTILS_MAX_DES_SER_COUNT] =
{
    FALSE, FALSE, FALSE, FALSE
};
#else
static UInt32 gSerDesInitDone[BSPUTILS_MAX_DES_SER_COUNT] =
{
    FALSE, FALSE, FALSE, FALSE, FALSE, FALSE
};
#endif

/* By default disable SerDes de configuration */
static UInt32 gAppUtilsSerDesDeCfgEnable = FALSE;

static BspOsal_SemHandle glockSem = NULL;

#if defined (TDA2XX_MC_BUILD)
static UInt32 gSerDesCfgDone[BSPUTILS_MAX_DES_SER_COUNT] =
{
    FALSE, FALSE, FALSE, FALSE
};
#else
static UInt32 gSerDesCfgDone[BSPUTILS_MAX_DES_SER_COUNT] =
{
    FALSE, FALSE, FALSE, FALSE, FALSE, FALSE
};
#endif

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined (SOC_TDA2EX)
/* i2c params for HDMI/I2C2 conflict removal */
static BspUtils_I2cParams gHdmiRecParams[] =
{
    {0x14, 0xF4},       /* SII9127 (?)   0x48->0x7A */
    {0x15, 0xF6},       /* SII9127 Color 0x32->0x7B */
    {0x16, 0xF8},       /* SII9127 (?)   0x68->0x7C */
    {0x17, 0xFA},       /* SII9127 (?)   0x73->0x7D */
    {0x18, 0xFC},       /* SII9127 CEC   0x60->0x7E */
    {0x19, 0xFE},       /* SII9127 EDID  0x70->0x7F */
};
#endif

#define SERDES_I2C_SCL_HIGH_TIME (0x08)
#define SERDES_I2C_SCL_HOLD_TIME (0x19)

static UInt32 gMulDesIoAddr[BSPUTILS_MAX_DES_SER_COUNT] =
{
#if defined (TDA2XX_MC_BUILD)
    0,
    0,
    0,
    0,
#else
    BSPUTILS_MULTIDES_IO_EXP_ADDR_0,
    BSPUTILS_MULTIDES_IO_EXP_ADDR_0,
    BSPUTILS_MULTIDES_IO_EXP_ADDR_1,
    BSPUTILS_MULTIDES_IO_EXP_ADDR_1,
    BSPUTILS_MULTIDES_IO_EXP_ADDR_2,
    BSPUTILS_MULTIDES_IO_EXP_ADDR_2,
#endif
};

/* De-serializer addresses */
static UInt32 gDesAddr[BSPUTILS_MAX_DES_SER_COUNT] =
{
#if defined (TDA2XX_MC_BUILD)
    BSPUTILS_DES1_ADDR,
    BSPUTILS_DES2_ADDR,
    BSPUTILS_DES3_ADDR,
    BSPUTILS_DES4_ADDR,
#else
    BSPUTILS_DES1_ADDR,
    BSPUTILS_DES2_ADDR,
    BSPUTILS_DES3_ADDR,
    BSPUTILS_DES4_ADDR,
    BSPUTILS_DES5_ADDR,
    BSPUTILS_DES6_ADDR,
#endif
};

/* i2c params for multi-deserializer */
#if defined (TDA2XX_MC_BUILD)
static BspUtils_I2cParams gMulDesParams[BSPUTILS_MAX_DES_SER_COUNT][7] =
{
    {
        {0x01, 0x04                                    },
        {0x03, 0xEC                                    },
        {0x1F, 0xF1                                    },
        {0x06, (BSPUTILS_SER_ID_ADDR * 2U)             },
        {0x08, (BSPUTILS_OV1063x_I2C_ADDR * 2U)        },
        {0x07, (BSPUTILS_SER1_ALIAS_ADDR * 2U)         },
        {0x10, (BSPUTILS_OV1063x_1_ALIAS_I2C_ADDR * 2U)},
    },
    {
        {0x01, 0x04                                    },
        {0x03, 0xEC                                    },
        {0x1F, 0xF1                                    },
        {0x06, (BSPUTILS_SER_ID_ADDR * 2U)             },
        {0x08, (BSPUTILS_OV1063x_I2C_ADDR * 2U)        },
        {0x07, (BSPUTILS_SER2_ALIAS_ADDR * 2U)         },
        {0x10, (BSPUTILS_OV1063x_2_ALIAS_I2C_ADDR * 2U)},
    },
    {
        {0x01, 0x04                                    },
        {0x03, 0xEC                                    },
        {0x1F, 0xF1                                    },
        {0x06, (BSPUTILS_SER_ID_ADDR * 2U)             },
        {0x08, (BSPUTILS_OV1063x_I2C_ADDR * 2U)        },
        {0x07, (BSPUTILS_SER3_ALIAS_ADDR * 2U)         },
        {0x10, (BSPUTILS_OV1063x_3_ALIAS_I2C_ADDR * 2U)},
    },
    {
        {0x01, 0x04                                    },
        {0x03, 0xEC                                    },
        {0x1F, 0xF1                                    },
        {0x06, (BSPUTILS_SER_ID_ADDR * 2U)             },
        {0x08, (BSPUTILS_OV1063x_I2C_ADDR * 2U)        },
        {0x07, (BSPUTILS_SER4_ALIAS_ADDR * 2U)         },
        {0x10, (BSPUTILS_OV1063x_4_ALIAS_I2C_ADDR * 2U)},
    }
};
#else
static BspUtils_I2cParams gMulDesParams[BSPUTILS_MAX_DES_SER_COUNT][8] =
{
    {
        {0x01, 0x04                                    },
        {0x03, 0xEC                                    },
        {0x06, (BSPUTILS_SER_ID_ADDR * 2U)             },
        {0x08, (BSPUTILS_OV1063x_I2C_ADDR * 2U)        },
        {0x07, (BSPUTILS_SER1_ALIAS_ADDR * 2U)         },
        {0x10, (BSPUTILS_OV1063x_1_ALIAS_I2C_ADDR * 2U)},
        {0x11, SERDES_I2C_SCL_HIGH_TIME},
        {0x12, SERDES_I2C_SCL_HIGH_TIME},
    },
    {
        {0x01, 0x04                                    },
        {0x03, 0xEC                                    },
        {0x06, (BSPUTILS_SER_ID_ADDR * 2U)             },
        {0x08, (BSPUTILS_OV1063x_I2C_ADDR * 2U)        },
        {0x07, (BSPUTILS_SER2_ALIAS_ADDR * 2U)         },
        {0x10, (BSPUTILS_OV1063x_2_ALIAS_I2C_ADDR * 2U)},
        {0x11, SERDES_I2C_SCL_HIGH_TIME},
        {0x12, SERDES_I2C_SCL_HIGH_TIME},
    },
    {
        {0x01, 0x04                                    },
        {0x03, 0xEC                                    },
        {0x06, (BSPUTILS_SER_ID_ADDR * 2U)             },
        {0x08, (BSPUTILS_OV1063x_I2C_ADDR * 2U)        },
        {0x07, (BSPUTILS_SER3_ALIAS_ADDR * 2U)         },
        {0x10, (BSPUTILS_OV1063x_3_ALIAS_I2C_ADDR * 2U)},
        {0x11, SERDES_I2C_SCL_HIGH_TIME},
        {0x12, SERDES_I2C_SCL_HIGH_TIME},
    },
    {
        {0x01, 0x04                                    },
        {0x03, 0xEC                                    },
        {0x06, (BSPUTILS_SER_ID_ADDR * 2U)             },
        {0x08, (BSPUTILS_OV1063x_I2C_ADDR * 2U)        },
        {0x07, (BSPUTILS_SER4_ALIAS_ADDR * 2U)         },
        {0x10, (BSPUTILS_OV1063x_4_ALIAS_I2C_ADDR * 2U)},
        {0x11, SERDES_I2C_SCL_HIGH_TIME},
        {0x12, SERDES_I2C_SCL_HIGH_TIME},
    },
    {
        {0x01, 0x04                                    },
        {0x03, 0xEC                                    },
        {0x06, (BSPUTILS_SER_ID_ADDR * 2U)             },
        {0x08, (BSPUTILS_OV1063x_I2C_ADDR * 2U)        },
        {0x07, (BSPUTILS_SER5_ALIAS_ADDR * 2U)         },
        {0x10, (BSPUTILS_OV1063x_5_ALIAS_I2C_ADDR * 2U)},
        {0x11, SERDES_I2C_SCL_HIGH_TIME},
        {0x12, SERDES_I2C_SCL_HIGH_TIME},
    },
    {
        {0x01, 0x04                                    },
        {0x03, 0xEC                                    },
        {0x06, (BSPUTILS_SER_ID_ADDR * 2U)             },
        {0x08, (BSPUTILS_OV1063x_I2C_ADDR * 2U)        },
        {0x07, (BSPUTILS_SER6_ALIAS_ADDR * 2U)         },
        {0x10, (BSPUTILS_OV1063x_6_ALIAS_I2C_ADDR * 2U)},
        {0x11, SERDES_I2C_SCL_HIGH_TIME},
        {0x12, SERDES_I2C_SCL_HIGH_TIME},
    }
};
#endif

/* i2c params for Multi De-serializer i2c expander */
static BspUtils_I2cParams gI2cExpParams[BSPUTILS_MAX_DES_SER_COUNT][4] =
{
#if defined (TDA2XX_MC_BUILD)
    {
        {0x00, 0x00},   /* IODIRA[7:0] - Output */
        {0x0C, 0x00},   /* GPPUA[7:0]  - Pull-up enabled */
        {0x12, 0x63},   /* GPIOA - 0:2-Mode,3-GPIO,4-BISTEN,5-OEN,6-SEL,7-PDB */
        {0x12, 0xE3},   /* GPIOA - 7-PDB=1, Power-up */
    },
    {
        {0x01, 0x00},   /* IODIRB[7:0] - Output */
        {0x0D, 0x00},   /* GPPUB[7:0]  - Pull-up enabled */
        {0x13, 0x63},   /* GPIOB - 0:2-Mode,3-GPIO,4-BISTEN,5-OEN,6-SEL,7-PDB */
        {0x13, 0xE3}    /* GPIOB - 7-PDB=1, Power-up */
    },
    {
        {0x00, 0x00},   /* IODIRA[7:0] - Output */
        {0x0C, 0x00},   /* GPPUA[7:0]  - Pull-up enabled */
        {0x12, 0x63},   /* GPIOA - 0:2-Mode,3-GPIO,4-BISTEN,5-OEN,6-SEL,7-PDB */
        {0x12, 0xE3},   /* GPIOA - 7-PDB=1, Power-up */
    },
#else
    {
        {0x00, 0x00},   /* IODIRA[7:0] - Output */
        {0x0C, 0x00},   /* GPPUA[7:0]  - Pull-up enabled */
        {0x12, 0x63},   /* GPIOA - 0:2-Mode,3-GPIO,4-BISTEN,5-OEN,6-SEL,7-PDB */
#ifdef BSPUTILS_LVDS_IMI2_CAM_ENABLE
        {0x12, 0xEB},   /* GPIOA - 3-RESET, 7-FSIN=1 */
#else
        {0x12, 0xE3},   /* GPIOA - 7-PDB=1, Power-up */
#endif
    },
    {
        {0x01, 0x00},   /* IODIRB[7:0] - Output */
        {0x0D, 0x00},   /* GPPUB[7:0]  - Pull-up enabled */
        {0x13, 0x63},   /* GPIOB - 0:2-Mode,3-GPIO,4-BISTEN,5-OEN,6-SEL,7-PDB */
#ifdef BSPUTILS_LVDS_IMI2_CAM_ENABLE
        {0x13, 0xEB}    /* GPIOB - 3-RESET, 7-FSIN=1 */
#else
        {0x13, 0xE3}    /* GPIOB - 7-PDB=1, Power-up */
#endif
    },
    {
        {0x00, 0x00},   /* IODIRA[7:0] - Output */
        {0x0C, 0x00},   /* GPPUA[7:0]  - Pull-up enabled */
        {0x12, 0x63},   /* GPIOA - 0:2-Mode,3-GPIO,4-BISTEN,5-OEN,6-SEL,7-PDB */
#ifdef BSPUTILS_LVDS_IMI2_CAM_ENABLE
        {0x12, 0xEB},   /* GPIOA - 3-RESET, 7-FSIN=1 */
#else
        {0x12, 0xE3},   /* GPIOA - 7-PDB=1, Power-up */
#endif
    },
    {
        {0x01, 0x00},   /* IODIRB[7:0] - Output */
        {0x0D, 0x00},   /* GPPUB[7:0]  - Pull-up enabled */
        {0x13, 0x63},   /* GPIOB - 0:2-Mode,3-GPIO,4-BISTEN,5-OEN,6-SEL,7-PDB */
#ifdef BSPUTILS_LVDS_IMI2_CAM_ENABLE
        {0x13, 0xEB}    /* GPIOB - 3-RESET, 7-FSIN=1 */
#else
        {0x13, 0xE3}    /* GPIOB - 7-PDB=1, Power-up */
#endif
    },
    {
        {0x00, 0x00},   /* IODIRA[7:0] - Output */
        {0x0C, 0x00},   /* GPPUA[7:0]  - Pull-up enabled */
        {0x12, 0x63},   /* GPIOA - 0:2-Mode,3-GPIO,4-BISTEN,5-OEN,6-SEL,7-PDB */
#ifdef BSPUTILS_LVDS_IMI2_CAM_ENABLE
        {0x12, 0xEB},   /* GPIOA - 3-RESET, 7-FSIN=1 */
#else
        {0x12, 0xE3},   /* GPIOA - 7-PDB=1, Power-up */
#endif
    },
    {
        {0x01, 0x00},   /* IODIRB[7:0] - Output */
        {0x0D, 0x00},   /* GPPUB[7:0]  - Pull-up enabled */
        {0x13, 0x63},   /* GPIOB - 0:2-Mode,3-GPIO,4-BISTEN,5-OEN,6-SEL,7-PDB */
#ifdef BSPUTILS_LVDS_IMI2_CAM_ENABLE
        {0x13, 0xEB}    /* GPIOB - 3-RESET, 7-FSIN=1 */
#else
        {0x13, 0xE3}    /* GPIOB - 7-PDB=1, Power-up */
#endif
    },
#endif
};

/* i2c params for Multi De-serializer i2c expander for IMX290 */
static BspUtils_I2cParams gI2cImx290ExpParams[BSPUTILS_MAX_DES_SER_COUNT][4] =
{
#if defined (TDA2XX_MC_BUILD)
    0,
    0,
    0,
    0,
#else
    {
        {0x00,0x00         }, /* IODIRA[7:0] - Output */
        {0x0C,0x00         }, /* GPPUA[7:0]  - Pull-up enabled */
        {0x12,0x63         }, /* GPIOA -
                               *0:2-Mode,3-GPIO,4-BISTEN,5-OEN,6-SEL,7-PDB */
        {0x12,0xEB         }, /* GPIOA - 3-RESET, 7-FSIN=1 */
    },
    {
        {0x01,0x00         }, /* IODIRB[7:0] - Output */
        {0x0D,0x00         }, /* GPPUB[7:0]  - Pull-up enabled */
        {0x13,0x63         }, /* GPIOB -
                               *0:2-Mode,3-GPIO,4-BISTEN,5-OEN,6-SEL,7-PDB */
        {0x13,0xEB         } /* GPIOB - 3-RESET, 7-FSIN=1 */
    },
    {
        {0x00,0x00         }, /* IODIRA[7:0] - Output */
        {0x0C,0x00         }, /* GPPUA[7:0]  - Pull-up enabled */
        {0x12,0x63         }, /* GPIOA -
                               *0:2-Mode,3-GPIO,4-BISTEN,5-OEN,6-SEL,7-PDB */
        {0x12,0xEB         }, /* GPIOA - 3-RESET, 7-FSIN=1 */
    },
    {
        {0x01,0x00         }, /* IODIRB[7:0] - Output */
        {0x0D,0x00         }, /* GPPUB[7:0]  - Pull-up enabled */
        {0x13,0x63         }, /* GPIOB -
                               *0:2-Mode,3-GPIO,4-BISTEN,5-OEN,6-SEL,7-PDB */
        {0x13,0xEB         } /* GPIOB - 3-RESET, 7-FSIN=1 */
    },
    {
        {0x00,0x00         }, /* IODIRA[7:0] - Output */
        {0x0C,0x00         }, /* GPPUA[7:0]  - Pull-up enabled */
        {0x12,0x63         }, /* GPIOA -
                               *0:2-Mode,3-GPIO,4-BISTEN,5-OEN,6-SEL,7-PDB */
        {0x12,0xEB         }, /* GPIOA - 3-RESET, 7-FSIN=1 */
    },
    {
        {0x01,0x00         }, /* IODIRB[7:0] - Output */
        {0x0D,0x00         }, /* GPPUB[7:0]  - Pull-up enabled */
        {0x13,0x63         }, /* GPIOB -
                               *0:2-Mode,3-GPIO,4-BISTEN,5-OEN,6-SEL,7-PDB */
        {0x13,0xEB         } /* GPIOB - 3-RESET, 7-FSIN=1 */
    },
#endif
};

/* i2c params for serializer */
static BspUtils_I2cParams gSerParams[] =
{
    {0x03, 0xC5},
    {0x0D, 0x55},
    {0x11, SERDES_I2C_SCL_HOLD_TIME},
    {0x12, SERDES_I2C_SCL_HOLD_TIME},
};

/* i2c de Configure params for serializer */
static BspUtils_I2cParams gSerDeCfgParams[] =
{
    {0x01, 0x33},
};

/* i2c de Configure params for multi-deserializer */
static BspUtils_I2cParams gMulDesDeCfgParams[] =
{
    {0x01, 0x24},
};

/**
 *  BspUtils_appInitSerDeSer
 *
 *  \brief BSP application utils function to setup board for LVDS Support.
 *         Removes I2C Addr Conflict
 */
Int32 BspUtils_appInitSerDeSer(void)
{
    Int32        retVal = BSP_SOK;
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined (SOC_TDA2EX)
    UInt32       i2cDevAddr;
    UInt32       nIdx;
    Bsp_BoardRev dcBoardRev;
#endif

    /* Assert if init is called twice with out deinit */
    GT_assert(BspAppTrace, (NULL == glockSem));
    glockSem = BspOsal_semCreate((Int32) 1, FALSE);
    if (NULL == glockSem)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  "Error: Semaphore create failed!!\r\n");
        retVal = BSP_EALLOC;
    }

    if (BSP_SOK == retVal)
    {
        BspOsal_semWait(glockSem, BSP_OSAL_WAIT_FOREVER);

        GT_0trace(BspAppTrace, GT_INFO,
                  "Initializing Multi-Deserializer Setup ...!!\r\n");

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined (SOC_TDA2EX)
        dcBoardRev = Bsp_boardGetDcRev();
        /* SIL9127 not present in REV D VISION cards */
        if ((BSP_BOARD_MONSTERCAM != Bsp_boardGetId()) &&
            (dcBoardRev < BSP_BOARD_REV_D))
        {
            i2cDevAddr = BSPUTILS_SIL9127_ADDR;
            for (nIdx = 0U;
                 nIdx < (sizeof (gHdmiRecParams) /
                         sizeof (gHdmiRecParams[0U]));
                 nIdx++)
            {
                UInt32 i2cInstId;

#if defined (SOC_TDA2EX) || defined (SOC_TDA2PX)
                i2cInstId = BSP_DEVICE_I2C_INST_ID_4;
#else
                i2cInstId = BSP_DEVICE_I2C_INST_ID_1;
#endif

                /* I2C write to remove I2C addr conflict with HDMI receiver
                 * - SIL9127 , present on Vision APP board */
                retVal += Bsp_deviceWrite8(
                    i2cInstId,
                    i2cDevAddr,
                    &(gHdmiRecParams[nIdx].nRegAddr),
                    &(gHdmiRecParams[nIdx].nRegValue),
                    (UInt32) 1U);
                if (retVal != BSP_SOK)
                {
                    GT_0trace(BspAppTrace, GT_ERR,
                              "I2C Addr Conflict Removal Failed!!\r\n");
                    break;
                }
            }
        }
#endif
    }

    if (NULL != glockSem)
    {
        BspOsal_semPost(glockSem);
    }

    return (retVal);
}

/**
 *  BspUtils_appDeInitSerDeSer
 *
 *  \brief BSP application utils function to undo stuff done in init.
 *  1. Deletion of semaphore created.
 */
Int32 BspUtils_appDeInitSerDeSer(void)
{
    Int32 retVal = BSP_SOK;

    if (NULL != glockSem)
    {
        BspOsal_semDelete(&glockSem);
        glockSem = NULL;
    }

    return retVal;
}

Int32 BspUtils_appDumpDeSerReg(UInt32 devDrvId, UInt32 devInstId)
{
    Int32  retVal = BSP_SOK;
    UInt32 serI2cDevAddr;
    UInt32 ovInstId;
    UInt8  cnt;

    if ((FVID2_VID_SENSOR_MULDES_OV1063X_DRV == devDrvId) ||
        (FVID2_VID_SENSOR_GW4200_IMX290_DRV == devDrvId))
    {
        BspOsal_semWait(glockSem, BSP_OSAL_WAIT_FOREVER);

        ovInstId = BspUtils_appConvToOvInstId(devDrvId, devInstId);
        if (ovInstId < BSPUTILS_MAX_DES_SER_COUNT)
        {
            serI2cDevAddr = BSPUTILS_SER1_ALIAS_ADDR + ovInstId;
            for (cnt = 0U; cnt < 0x25U; cnt++)
            {
                BspUtils_appPrintReg(ovInstId, serI2cDevAddr, cnt);
                BspOsal_sleep((UInt32) 10U);
            }
        }
        else
        {
            retVal = BSP_EBADARGS;
        }

        BspOsal_semPost(glockSem);
    }
    else
    {
        retVal = BSP_EBADARGS;
    }

    return (retVal);
}

/**
 *  BspUtils_appConfSerDeSer
 *
 *  \brief BSP application utils function to Configure a particular instance of
 *  De-Serializer and serializer for LVDS Support.
 *  Sequence
 *  2. Configures a particular instance of Des with alias address of serializer
 *     and Ov sensor, enable I2C Pass through, enable I2C Auto Ack etc
 *  3. Configure a particular instace of Serializer in I2C pass through etc.
 */
Int32 BspUtils_appConfSerDeSer(UInt32 devDrvId, UInt32 devInstId)
{
    Int32  retVal = BSP_SOK;
    UInt32 serI2cDevAddr;
    UInt32 ovInstId;

    if ((FVID2_VID_SENSOR_MULDES_OV1063X_DRV == devDrvId) ||
        (FVID2_VID_SENSOR_GW4200_IMX290_DRV == devDrvId))
    {
        BspOsal_semWait(glockSem, BSP_OSAL_WAIT_FOREVER);

        ovInstId = BspUtils_appConvToOvInstId(devDrvId, devInstId);
        if (ovInstId < BSPUTILS_MAX_DES_SER_COUNT)
        {
            if ((UInt32) FALSE == gSerDesInitDone[ovInstId])
            {
                if ((BSP_BOARD_MONSTERCAM != Bsp_boardGetId()))
                {
                    /* Configure IO Expander per sensor in MULDES board */
                    retVal = BspUtils_appMultiDesIoExpConfig(
                        devDrvId,
                        ovInstId,
                        gMulDesIoAddr[ovInstId]);
                    if (retVal != BSP_SOK)
                    {
                        GT_0trace(
                            BspAppTrace, GT_ERR,
                            "Error: Configuring MutiDeserializer IO exp Failed!!\r\n");
                    }

                    /* Sleep so that reset could happen */
                    BspOsal_sleep((UInt32) 80U);

                    gSerDesInitDone[ovInstId] = (UInt32) TRUE;
                }
            }

            if ((UInt32) FALSE == gSerDesCfgDone[ovInstId])
            {
                retVal = BspUtils_appConfMultiDeSer(
                    ovInstId,
                    gDesAddr[ovInstId]);
                if (BSP_SOK == retVal)
                {
                    serI2cDevAddr = BSPUTILS_SER1_ALIAS_ADDR + ovInstId;
                    retVal        = BspUtils_appConfSer(ovInstId, serI2cDevAddr);
                }

                /* Sleep is required after Configuring
                 * each instance of multi deserializer and before accessing
                 * sensor */
                BspOsal_sleep((UInt32) 1U);

                gSerDesCfgDone[ovInstId] = (UInt32) TRUE;
            }
        }
        else
        {
            retVal = BSP_EBADARGS;
        }

        BspOsal_semPost(glockSem);
    }
    else
    {
        retVal = BSP_EBADARGS;
    }

    return (retVal);
}

/**
 *  BspUtils_appDeConfSerDeSer
 *
 *  \brief BSP application utils function to De-Configure a particular instance
 *         of De-Serializer and serializer for LVDS Support.
 */
Int32 BspUtils_appDeConfSerDeSer(UInt32 devDrvId, UInt32 devInstId)
{
    Int32  retVal = BSP_SOK;
    UInt32 serI2cDevAddr;
    UInt32 ovInstId;

    if ((FVID2_VID_SENSOR_MULDES_OV1063X_DRV == devDrvId) ||
        (FVID2_VID_SENSOR_GW4200_IMX290_DRV == devDrvId))
    {
        BspOsal_semWait(glockSem, BSP_OSAL_WAIT_FOREVER);

        ovInstId = BspUtils_appConvToOvInstId(devDrvId, devInstId);
        if (ovInstId < BSPUTILS_MAX_DES_SER_COUNT)
        {
            if (((Bool) TRUE) == ((Bool) gAppUtilsSerDesDeCfgEnable))
            {
                serI2cDevAddr = BSPUTILS_SER1_ALIAS_ADDR + ovInstId;
                retVal        = BspUtils_appDeConfSer(ovInstId, serI2cDevAddr);
                if (BSP_SOK == retVal)
                {
                    retVal = BspUtils_appDeConfMultiDeSer(
                        ovInstId,
                        gDesAddr[ovInstId]);
                }

                /* Sleep is required after DeConfiguring
                 * each instance of multi deserializer */
                BspOsal_sleep((UInt32) 1U);

                gSerDesCfgDone[ovInstId] = FALSE;
            }
        }
        else
        {
            retVal = BSP_EBADARGS;
        }

        BspOsal_semPost(glockSem);
    }

    return (retVal);
}

/*  In Multi des board the connections are as shown below
 *
 *   CAM1 ---> VIN1A
 *   CAM2 ---> VIN2A
 *   CAM3 ---> VIN3A
 *   CAM4 ---> VIN5A
 *   CAM5 ---> VIN4B
 *   CAM6 ---> VIN6A
 *
 */
static UInt32 BspUtils_appConvToOvInstId(UInt32 devDrvId, UInt32 devInstId)
{
    UInt32 ovInstId;

    if (FVID2_VID_SENSOR_GW4200_IMX290_DRV == devDrvId)
    {
        switch (devInstId)
        {
            case BSP_DEVICE_MULDES_IMX290_INST_ID_1:
                ovInstId = 0U;
                break;

            case BSP_DEVICE_MULDES_IMX290_INST_ID_2:
                ovInstId = 1U;
                break;

            case BSP_DEVICE_MULDES_IMX290_INST_ID_3:
                ovInstId = 2U;
                break;

            case BSP_DEVICE_MULDES_IMX290_INST_ID_4:
                ovInstId = 3U;
                break;

            case BSP_DEVICE_MULDES_IMX290_INST_ID_5:
                ovInstId = 4U;
                break;

            case BSP_DEVICE_MULDES_IMX290_INST_ID_6:
                ovInstId = 5U;
                break;

            default:
                ovInstId = BSPUTILS_MAX_DES_SER_COUNT;
                break;
        }
    }
    else
    {
        switch (devInstId)
        {
            case BSP_DEVICE_MULDES_OV1063X_INST_ID_1:
                ovInstId = 0U;
                break;

            case BSP_DEVICE_MULDES_OV1063X_INST_ID_2:
                ovInstId = 1U;
                break;

            case BSP_DEVICE_MULDES_OV1063X_INST_ID_3:
                ovInstId = 2U;
                break;

            case BSP_DEVICE_MULDES_OV1063X_INST_ID_4:
                ovInstId = 3U;
                break;

            case BSP_DEVICE_MULDES_OV1063X_INST_ID_5:
                ovInstId = 4U;
                break;

            case BSP_DEVICE_MULDES_OV1063X_INST_ID_6:
                ovInstId = 5U;
                break;

            default:
                ovInstId = BSPUTILS_MAX_DES_SER_COUNT;
                break;
        }
    }

    return (ovInstId);
}

static Int32 BspUtils_appConfSer(UInt32 devInstId, UInt32 i2cDevAddr)
{
    Int32  retVal = BSP_SOK;
    UInt32 nIdx   = 0;
    UInt8  nRegAddr, nRegValue;
    UInt32 cnt = 0;
    UInt32 i2cInstId;

#if defined (SOC_TDA2EX) || defined (SOC_TDA2PX)
    i2cInstId = BSP_DEVICE_I2C_INST_ID_4;
#else
    i2cInstId = BSP_DEVICE_I2C_INST_ID_1;
#endif

    if (BSP_BOARD_MONSTERCAM == Bsp_boardGetId())
    {
        i2cInstId = BSP_DEVICE_I2C_INST_ID_2;
        if (BSP_BOARD_MONSTERCAM_MAIN_IMAGER_OVINSTID == devInstId)
        {
            i2cInstId = BSP_DEVICE_I2C_INST_ID_0;
        }
    }

    /*
     * Reset serializer
     */
    nRegAddr  = 0x01U;
    nRegValue = 0x33U;
    retVal    = Bsp_deviceWrite8(
        i2cInstId,
        i2cDevAddr,
        &nRegAddr,
        &nRegValue,
        (UInt32) 1U);
    if (retVal != BSP_SOK)
    {
        GT_1trace(BspAppTrace, GT_ERR,
                  "Error: Failed to Configure ser for device 0x%x \r\n",
                  i2cDevAddr);
    }

    /* sleep needed to reset serializer */
    BspOsal_sleep((UInt32) 1U);

    if (BSP_SOK == retVal)
    {
        nRegAddr  = 0x01U;
        nRegValue = 0x00U;
        /* Checking the reset bit to get cleared */
        while (cnt < BSPUTILS_SER_RESET_CHECK_COUNT)
        {
            retVal = Bsp_deviceRead8(i2cInstId,
                                     i2cDevAddr,
                                     &nRegAddr,
                                     &nRegValue,
                                     (UInt32) 1U);
            if (retVal != FVID2_SOK)
            {
                GT_2trace(BspAppTrace, GT_ERR,
                          " device address - %x i2c error - %d\r\n",
                          i2cDevAddr,
                          retVal);
                /* If I2C read fails re-try, don't exit!! */
            }

            if ((nRegValue & 0x03U) == 0U)
            {
                /* Reset done */
                retVal = FVID2_SOK;
                break;
            }

            /* sleep */
            BspOsal_sleep((UInt32) 1U);
            cnt++;
        }
        if (cnt == BSPUTILS_SER_RESET_CHECK_COUNT)
        {
            GT_1trace(BspAppTrace, GT_ERR,
                      " Ser reset failed - %x \r\n", i2cDevAddr);
            retVal = BSP_EFAIL;
        }
    }

    if (BSP_SOK == retVal)
    {
        for (nIdx = 0U;
             nIdx < (sizeof (gSerParams) / sizeof (gSerParams[0U]));
             nIdx++)
        {
            retVal += Bsp_deviceWrite8(i2cInstId,
                                       i2cDevAddr,
                                       &gSerParams[nIdx].nRegAddr,
                                       &gSerParams[nIdx].nRegValue,
                                       (UInt32) 1U);
            if (retVal != BSP_SOK)
            {
                GT_1trace(BspAppTrace, GT_ERR,
                          "Error: Failed to Configure ser for device 0x%x \r\n",
                          i2cDevAddr);
                break;
            }

            /* sleep needed to reset serializer */
            BspOsal_sleep((UInt32) 1U);
        }
    }

    return (retVal);
}

static Int32 BspUtils_appDeConfSer(UInt32 devInstId, UInt32 i2cDevAddr)
{
    Int32  retVal = BSP_SOK;
    UInt32 nIdx   = 0;
    UInt32 i2cInstId;

#if defined (SOC_TDA2EX) || defined (SOC_TDA2PX)
    i2cInstId = BSP_DEVICE_I2C_INST_ID_4;
#else
    i2cInstId = BSP_DEVICE_I2C_INST_ID_1;
#endif

    if (BSP_BOARD_MONSTERCAM == Bsp_boardGetId())
    {
        i2cInstId = BSP_DEVICE_I2C_INST_ID_2;
        if (BSP_BOARD_MONSTERCAM_MAIN_IMAGER_OVINSTID == devInstId)
        {
            i2cInstId = BSP_DEVICE_I2C_INST_ID_0;
        }
    }

    for (nIdx = 0U;
         nIdx < (sizeof (gSerDeCfgParams) / sizeof (gSerDeCfgParams[0U]));
         nIdx++)
    {
        retVal = Bsp_deviceWrite8(i2cInstId,
                                  i2cDevAddr,
                                  &gSerDeCfgParams[nIdx].nRegAddr,
                                  &gSerDeCfgParams[nIdx].nRegValue,
                                  (UInt32) 1U);
        if (retVal != FVID2_SOK)
        {
            GT_1trace(
                BspAppTrace, GT_ERR,
                "Error: Failed to DeConfigure Ser for device 0x%x \r\n",
                i2cDevAddr);
            break;
        }

        /* sleep needed to reset serializer */
        BspOsal_sleep((UInt32) 10U);
    }

    return (retVal);
}

static Int32 BspUtils_appMultiDesIoExpConfig(UInt32 devDrvId,
                                             UInt32 devInstId,
                                             UInt32 i2cDevAddr)
{
    Int32  retVal = BSP_SOK;
    UInt32 nIdx   = 0;
    UInt32 i2cInstId;

#if defined (SOC_TDA2EX) || defined (SOC_TDA2PX)
    i2cInstId = BSP_DEVICE_I2C_INST_ID_4;
#else
    i2cInstId = BSP_DEVICE_I2C_INST_ID_1;
#endif

    if (BSP_BOARD_MONSTERCAM == Bsp_boardGetId())
    {
        i2cInstId = BSP_DEVICE_I2C_INST_ID_2;
        if (BSP_BOARD_MONSTERCAM_MAIN_IMAGER_OVINSTID == devInstId)
        {
            i2cInstId = BSP_DEVICE_I2C_INST_ID_0;
        }
    }

    if (FVID2_VID_SENSOR_GW4200_IMX290_DRV == devDrvId)
    {
        for (nIdx = 0U;
             nIdx < (sizeof (gI2cImx290ExpParams[devInstId]) /
                     sizeof (gI2cImx290ExpParams[devInstId][0U]));
             nIdx++)
        {
            retVal += Bsp_deviceWrite8(i2cInstId,
                                       i2cDevAddr,
                                       &(gI2cImx290ExpParams[devInstId][nIdx].
                                         nRegAddr),
                                       &(gI2cImx290ExpParams[devInstId][nIdx].
                                         nRegValue),
                                       (UInt32) 1U);
            if (retVal != BSP_SOK)
            {
                GT_1trace(
                    BspAppTrace, GT_ERR,
                    "Error: Failed to Configure De-ser for device 0x%x \r\n",
                    i2cDevAddr);
                break;
            }

            /* sleep so that reset could be performed */
            BspOsal_sleep((UInt32) 1U);
        }
    }
    else
    {
        for (nIdx = 0U;
             nIdx < (sizeof (gI2cExpParams[devInstId]) /
                     sizeof (gI2cExpParams[devInstId][0U]));
             nIdx++)
        {
            retVal += Bsp_deviceWrite8(i2cInstId,
                                       i2cDevAddr,
                                       &(gI2cExpParams[devInstId][nIdx].
                                         nRegAddr),
                                       &(gI2cExpParams[devInstId][nIdx].
                                         nRegValue),
                                       (UInt32) 1U);
            if (retVal != BSP_SOK)
            {
                GT_1trace(
                    BspAppTrace, GT_ERR,
                    "Error: Failed to Configure De-ser for device 0x%x \r\n",
                    i2cDevAddr);
                break;
            }

            /* sleep so that reset could be performed */
            BspOsal_sleep((UInt32) 1U);
        }
    }

    return (retVal);
}

static Int32 BspUtils_appDeConfMultiDeSer(UInt32 devInstId, UInt32 i2cDevAddr)
{
    Int32  retVal  = BSP_SOK;
    UInt32 nIdx    = 0;
    UInt32 numRegs = 1U;
    UInt32 i2cInstId;

#if defined (SOC_TDA2EX) || defined (SOC_TDA2PX)
    i2cInstId = BSP_DEVICE_I2C_INST_ID_4;
#else
    i2cInstId = BSP_DEVICE_I2C_INST_ID_1;
#endif

    if (BSP_BOARD_MONSTERCAM == Bsp_boardGetId())
    {
        i2cInstId = BSP_DEVICE_I2C_INST_ID_2;
        if (BSP_BOARD_MONSTERCAM_MAIN_IMAGER_OVINSTID == devInstId)
        {
            i2cInstId = BSP_DEVICE_I2C_INST_ID_0;
        }
    }

    for (nIdx = 0U;
         nIdx < (sizeof (gMulDesDeCfgParams) / sizeof (gMulDesDeCfgParams[0U]));
         nIdx++)
    {
        retVal = Bsp_deviceWrite8(i2cInstId,
                                  i2cDevAddr,
                                  &(gMulDesDeCfgParams[nIdx].nRegAddr),
                                  &(gMulDesDeCfgParams[nIdx].nRegValue),
                                  numRegs);
        if (retVal != FVID2_SOK)
        {
            GT_1trace(
                BspAppTrace, GT_ERR,
                "Error: Failed to De-Configure De-ser for device 0x%x \r\n",
                i2cDevAddr);
            break;
        }

        /* sleep */
        BspOsal_sleep((UInt32) 10U);
    }

    return (retVal);
}

static Int32 BspUtils_appConfMultiDeSer(UInt32 devInstId, UInt32 i2cDevAddr)
{
    Int32  retVal = BSP_SOK;
    UInt32 nIdx   = 0;
    UInt8  nRegAddr, nRegValue;
    UInt32 cnt = 0;
    UInt32 i2cInstId;

#if defined (SOC_TDA2EX) || defined (SOC_TDA2PX)
    i2cInstId = BSP_DEVICE_I2C_INST_ID_4;
#else
    i2cInstId = BSP_DEVICE_I2C_INST_ID_1;
#endif

    if (BSP_BOARD_MONSTERCAM == Bsp_boardGetId())
    {
        i2cInstId = BSP_DEVICE_I2C_INST_ID_2;
        if (BSP_BOARD_MONSTERCAM_MAIN_IMAGER_OVINSTID == devInstId)
        {
            i2cInstId = BSP_DEVICE_I2C_INST_ID_0;
        }
    }

    for (nIdx = 0U;
         nIdx <
         (sizeof (gMulDesParams[devInstId]) /
          sizeof (gMulDesParams[devInstId][0U]));
         nIdx++)
    {
        retVal += Bsp_deviceWrite8(i2cInstId,
                                   i2cDevAddr,
                                   &(gMulDesParams[devInstId][nIdx].nRegAddr),
                                   &(gMulDesParams[devInstId][nIdx].nRegValue),
                                   (UInt32) 1U);
        if (retVal != BSP_SOK)
        {
            GT_1trace(
                BspAppTrace, GT_ERR,
                "Error: Failed to Configure De-ser for device 0x%x \r\n",
                i2cDevAddr);
            break;
        }

        /* sleep */
        BspOsal_sleep((UInt32) 1U);
    }

    nRegAddr  = 0x06U;
    nRegValue = 0x0U;  /* Serializer ID */
    retVal    = Bsp_deviceRead8(i2cInstId,
                                i2cDevAddr,
                                &nRegAddr,
                                &nRegValue,
                                (UInt32) 1U);
    if (retVal != FVID2_SOK)
    {
        GT_2trace(BspAppTrace, GT_ERR,
                  " device address - %x i2c error - %d\r\n",
                  i2cDevAddr,
                  retVal);
    }

    GT_3trace(BspAppTrace, GT_DEBUG,
              " Deser - %x - Address: 0x%x, Value: 0x%x\r\n",
              i2cDevAddr,
              nRegAddr, nRegValue);

    /* sleep */
    BspOsal_sleep((UInt32) 1U);

    nRegAddr  = 0x07U;
    nRegValue = 0x0U;  /* Serializer Alias */
    retVal    = Bsp_deviceRead8(i2cInstId,
                                i2cDevAddr,
                                &nRegAddr,
                                &nRegValue,
                                (UInt32) 1U);
    if (retVal != FVID2_SOK)
    {
        GT_2trace(BspAppTrace, GT_ERR,
                  " Device address - %x i2c error - %d\r\n",
                  i2cDevAddr,
                  retVal);
    }

    GT_3trace(BspAppTrace, GT_DEBUG,
              " Deser - %x - Address: 0x%x, Value: 0x%x\r\n",
              i2cDevAddr,
              nRegAddr, nRegValue);

    /* sleep */
    BspOsal_sleep((UInt32) 1U);

    nRegAddr  = 0x1CU;
    nRegValue = 0x0U;
    /* Checking the Lock status */
    while (((nRegValue & 0x02U) == 0x0) &&
           (cnt < BSPUTILS_MULDES_LOCK_CHECK_COUNT))
    {
        retVal = Bsp_deviceRead8(i2cInstId,
                                 i2cDevAddr,
                                 &nRegAddr,
                                 &nRegValue,
                                 (UInt32) 1U);
        if (retVal != FVID2_SOK)
        {
            GT_2trace(BspAppTrace, GT_ERR,
                      " device address - %x i2c error - %d\r\n",
                      i2cDevAddr,
                      retVal);
        }
        cnt++;

        /* sleep */
        BspOsal_sleep((UInt32) 1U);
    }
    if (cnt >= BSPUTILS_MULDES_LOCK_CHECK_COUNT)
    {
        GT_1trace(BspAppTrace, GT_ERR,
                  " DE-Ser and Ser Link is not up for addr - %x \r\n",
                  i2cDevAddr);
        retVal = BSP_EFAIL;
    }

    GT_3trace(BspAppTrace, GT_DEBUG,
              " Deser - %x - Address: 0x%x, Value: 0x%x\r\n",
              i2cDevAddr,
              nRegAddr, nRegValue);

    return (retVal);
}

static Int32 BspUtils_appPrintReg(UInt32 devInstId,
                                  UInt32 i2cDevAddr,
                                  UInt8  nRegAddr)
{
    Int32  retVal = BSP_SOK;
    UInt8  nRegValue;
    UInt32 i2cInstId;

#if defined (SOC_TDA2EX) || defined (SOC_TDA2PX)
    i2cInstId = BSP_DEVICE_I2C_INST_ID_4;
#else
    i2cInstId = BSP_DEVICE_I2C_INST_ID_1;
#endif

    if (BSP_BOARD_MONSTERCAM == Bsp_boardGetId())
    {
        i2cInstId = BSP_DEVICE_I2C_INST_ID_2;
        if (BSP_BOARD_MONSTERCAM_MAIN_IMAGER_OVINSTID == devInstId)
        {
            i2cInstId = BSP_DEVICE_I2C_INST_ID_0;
        }
    }

    nRegValue = 0x0U;
    retVal    = Bsp_deviceRead8(i2cInstId,
                                i2cDevAddr,
                                &nRegAddr,
                                &nRegValue,
                                (UInt32) 1U);
    if (retVal != FVID2_SOK)
    {
        GT_2trace(BspAppTrace, GT_ERR,
                  " device address - %x i2c error - %d\r\n",
                  i2cDevAddr, retVal);
    }
    GT_3trace(BspAppTrace, GT_INFO,
              " Device (0x%0.2x) Offset: 0x%0.2x, Value: 0x%0.2x\r\n",
              i2cDevAddr, nRegAddr, nRegValue);

    return (retVal);
}

