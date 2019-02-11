/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2018
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
 *  \file bsputils_lvdsRvp.c
 *
 *  \brief This file implements application level lvds related helper functions
 *  for RVP board.
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

#define BSPUTILS_OVINST_ID_1            (0U)
#define BSPUTILS_OVINST_ID_2            (1U)
#define BSPUTILS_OVINST_ID_3            (2U)
#define BSPUTILS_OVINST_ID_4            (3U)
#define BSPUTILS_OVINST_ID_5            (4U)
#define BSPUTILS_OVINST_ID_6            (5U)
#define BSPUTILS_OVINST_ID_7            (6U)
#define BSPUTILS_OVINST_ID_8            (7U)

/* Deserializers Addresses */
#define BSPUTILS_DES1_ADDR              (0x30U) /* 0x60/2 */
#define BSPUTILS_DES2_ADDR              (0x32U) /* 0x64/2 */
#define BSPUTILS_DES3_ADDR              (0x34U) /* 0x68/2 */
#define BSPUTILS_DES4_ADDR              (0x3DU) /* 0x7A/2 */
#define BSPUTILS_DES5_ADDR              (0x30U) /* 0x60/2 */
#define BSPUTILS_DES6_ADDR              (0x32U) /* 0x64/2 */
#define BSPUTILS_DES7_ADDR              (0x34U) /* 0x68/2 */
#define BSPUTILS_DES8_ADDR              (0x3DU) /* 0x7A/2 */

/* Serializers addresses */
#define BSPUTILS_SER1_ALIAS_ADDR        (0x60U) /* 0xC0/2 */
#define BSPUTILS_SER2_ALIAS_ADDR        (0x61U) /* 0xC4/2 */
#define BSPUTILS_SER3_ALIAS_ADDR        (0x62U) /* 0xC8/2 */
#define BSPUTILS_SER4_ALIAS_ADDR        (0x63U) /* 0xCC/2 */
#define BSPUTILS_SER5_ALIAS_ADDR        (0x60U) /* 0xD0/2 */
#define BSPUTILS_SER6_ALIAS_ADDR        (0x61U) /* 0xD4/2 */
#define BSPUTILS_SER7_ALIAS_ADDR        (0x62U) /* 0xD8/2 */
#define BSPUTILS_SER8_ALIAS_ADDR        (0x63U) /* 0xDC/2 */

#define BSPUTILS_SER_ID_ADDR            (0x58U) /* 0xB0/2 */

#define BSPUTILS_OV1063x_1_ALIAS_I2C_ADDR  (0x64U)
#define BSPUTILS_OV1063x_2_ALIAS_I2C_ADDR  (0x65U)
#define BSPUTILS_OV1063x_3_ALIAS_I2C_ADDR  (0x66U)
#define BSPUTILS_OV1063x_4_ALIAS_I2C_ADDR  (0x67U)
#define BSPUTILS_OV1063x_5_ALIAS_I2C_ADDR  (0x64U)
#define BSPUTILS_OV1063x_6_ALIAS_I2C_ADDR  (0x65U)
#define BSPUTILS_OV1063x_7_ALIAS_I2C_ADDR  (0x66U)
#define BSPUTILS_OV1063x_8_ALIAS_I2C_ADDR  (0x67U)

#define BSPUTILS_OV490_1_ALIAS_I2C_ADDR    (0x68U)
#define BSPUTILS_OV490_2_ALIAS_I2C_ADDR    (0x69U)
#define BSPUTILS_OV490_3_ALIAS_I2C_ADDR    (0x6AU)
#define BSPUTILS_OV490_4_ALIAS_I2C_ADDR    (0x6BU)
#define BSPUTILS_OV490_5_ALIAS_I2C_ADDR    (0x68U)
#define BSPUTILS_OV490_6_ALIAS_I2C_ADDR    (0x69U)
#define BSPUTILS_OV490_7_ALIAS_I2C_ADDR    (0x6AU)
#define BSPUTILS_OV490_8_ALIAS_I2C_ADDR    (0x6BU)

#define BSPUTILS_OV1063x_I2C_ADDR       (0x30U)     /* 0x60/2 */
#define BSPUTILS_OV490_I2C_ADDR         (0x24U)     /* 0x48/2 */

#define BSPUTILS_MAX_DES_SER_COUNT      (8U)

#define FPD3_93X_DES_RESET              (0x01U)
#define FPD3_93X_DIGITAL_RESET0         (1U << 0U)
#define FPD3_93X_DIGITAL_RESET1         (1U << 1U)

#define FPD3_93X_DES_GN_CONFIG          (0x02U)
#define FPD3_93X_DES_BCC_CONFIG         (0x58U)
#define FPD3_93X_DES_PORT_CONFIG        (0x6DU)

#define FPD3_93X_DES_DEVICE_STS         (0x04U)
#define FPD3_93X_DES_LOCK_DETECT        (1U << 2U)

#define FPD3_93X_DES_SER_ID             (0x5B)
#define FPD3_93X_DES_SER_AL             (0x5C)
#define FPD3_93X_DES_SLAVE_ID0          (0x5D)
#define FPD3_93X_DES_SLAVE_AL0          (0x65)
#define FPD3_93X_DES_SLAVE_ID1          (0x5E)
#define FPD3_93X_DES_SLAVE_AL1          (0x66)

#define FPD3_93X_DES_BC_GPIO_CTL0       (0x6EU)

/* Data Structures */
typedef struct
{
    UInt8 nRegAddr;
    UInt8 nRegValue;
} BspUtils_I2cParams;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static Int32 BspUtils_appConfSer(UInt32 ovInstId, UInt32 i2cDevAddr);
static Int32 BspUtils_appConfMultiDeSer(UInt32 devDrvId,
                                        UInt32 ovInstId,
                                        UInt32 i2cDevAddr);

static Int32 BspUtils_appDeConfSer(UInt32 ovInstId, UInt32 i2cDevAddr);
static Int32 BspUtils_appDeConfMultiDeSer(UInt32 ovInstId, UInt32 i2cDevAddr);

static UInt32 BspUtils_appConvToOvInstId(UInt32 devDrvId, UInt32 ovInstId);
static UInt32 BspUtils_ovInstIdToSerI2cAddr(UInt32 ovInstId);

static Int32 BspUtils_appPrintReg(UInt32 ovInstId,
                                  UInt32 i2cDevAddr,
                                  UInt8  nRegAddr);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* By default disable SerDes de configuration */
static UInt32 gAppUtilsSerDesDeCfgEnable = FALSE;

static BspOsal_SemHandle glockSem = NULL;

static UInt32 gSerDesCfgDone[BSPUTILS_MAX_DES_SER_COUNT] =
{
    FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE
};

#define SERDES_I2C_SCL_HIGH_TIME (0x08)
#define SERDES_I2C_SCL_HOLD_TIME (0x19)

/* De-serializer addresses */
static UInt32 gDesAddr[BSPUTILS_MAX_DES_SER_COUNT] =
{
    BSPUTILS_DES1_ADDR,
    BSPUTILS_DES2_ADDR,
    BSPUTILS_DES3_ADDR,
    BSPUTILS_DES4_ADDR,
    BSPUTILS_DES5_ADDR,
    BSPUTILS_DES6_ADDR,
    BSPUTILS_DES7_ADDR,
    BSPUTILS_DES8_ADDR,
};

static BspUtils_I2cParams fpd3_934_des_init_seq[] = {
    {FPD3_93X_DES_RESET, FPD3_93X_DIGITAL_RESET1},
    /* Magic */
    {0xb0, 0x04},
    {0xb1, 0x04},
    {0xb2, 0x1f},
    {0xb0, 0x04},
    {0xb1, 0x14},
    {0xb2, 0x1f},
    {0xb0, 0x08},
    {0xb1, 0x04},
    {0xb2, 0x1f},
    {0xb0, 0x08},
    {0xb1, 0x14},
    {0xb2, 0x1f},
    {0x41, 0xb6},
    {0x42, 0x75},
    {0x4c, 0x03},
    {0xd2, 0x9c},
    {0xb0, 0x05},
    {0xb1, 0x03},
    {0xb2, 0x06},
    {0xb1, 0x04},
    {0xb2, 0x06},
    /* input_port_override, input port 0, rx parity check en */
    {FPD3_93X_DES_GN_CONFIG, 0x9e},
    /* coax-mode, RAW10/100MHz */
    {FPD3_93X_DES_PORT_CONFIG, 0x07},
    /* i2c passthrough decode match,
       bc enable, bc crc gen enabled */
    {FPD3_93X_DES_BCC_CONFIG, 0x58},
};

/* i2c params for multi-deserializer */
static BspUtils_I2cParams gMulDesParams[BSPUTILS_MAX_DES_SER_COUNT][6] =
{
    {
        {FPD3_93X_DES_SER_ID,    (BSPUTILS_SER_ID_ADDR << 1)             },
        {FPD3_93X_DES_SER_AL,    (BSPUTILS_SER1_ALIAS_ADDR << 1)         },
        {FPD3_93X_DES_SLAVE_ID0, (BSPUTILS_OV1063x_I2C_ADDR << 1)        },
        {FPD3_93X_DES_SLAVE_AL0, (BSPUTILS_OV1063x_1_ALIAS_I2C_ADDR << 1)},
        {FPD3_93X_DES_SLAVE_ID1, (BSPUTILS_OV490_I2C_ADDR << 1)          },
        {FPD3_93X_DES_SLAVE_AL1, (BSPUTILS_OV490_1_ALIAS_I2C_ADDR << 1)  },
    },
    {
        {FPD3_93X_DES_SER_ID,    (BSPUTILS_SER_ID_ADDR << 1)             },
        {FPD3_93X_DES_SER_AL,    (BSPUTILS_SER2_ALIAS_ADDR << 1)         },
        {FPD3_93X_DES_SLAVE_ID0, (BSPUTILS_OV1063x_I2C_ADDR << 1)        },
        {FPD3_93X_DES_SLAVE_AL0, (BSPUTILS_OV1063x_2_ALIAS_I2C_ADDR << 1)},
        {FPD3_93X_DES_SLAVE_ID1, (BSPUTILS_OV490_I2C_ADDR << 1)          },
        {FPD3_93X_DES_SLAVE_AL1, (BSPUTILS_OV490_2_ALIAS_I2C_ADDR << 1)  },
    },
    {
        {FPD3_93X_DES_SER_ID,    (BSPUTILS_SER_ID_ADDR << 1)             },
        {FPD3_93X_DES_SER_AL,    (BSPUTILS_SER3_ALIAS_ADDR << 1)         },
        {FPD3_93X_DES_SLAVE_ID0, (BSPUTILS_OV1063x_I2C_ADDR << 1)        },
        {FPD3_93X_DES_SLAVE_AL0, (BSPUTILS_OV1063x_3_ALIAS_I2C_ADDR << 1)},
        {FPD3_93X_DES_SLAVE_ID1, (BSPUTILS_OV490_I2C_ADDR << 1)          },
        {FPD3_93X_DES_SLAVE_AL1, (BSPUTILS_OV490_3_ALIAS_I2C_ADDR << 1)  },
    },
    {
        {FPD3_93X_DES_SER_ID,    (BSPUTILS_SER_ID_ADDR << 1)             },
        {FPD3_93X_DES_SER_AL,    (BSPUTILS_SER4_ALIAS_ADDR << 1)         },
        {FPD3_93X_DES_SLAVE_ID0, (BSPUTILS_OV1063x_I2C_ADDR << 1)        },
        {FPD3_93X_DES_SLAVE_AL0, (BSPUTILS_OV1063x_4_ALIAS_I2C_ADDR << 1)},
        {FPD3_93X_DES_SLAVE_ID1, (BSPUTILS_OV490_I2C_ADDR << 1)          },
        {FPD3_93X_DES_SLAVE_AL1, (BSPUTILS_OV490_4_ALIAS_I2C_ADDR << 1)  },
    },
    {
        {FPD3_93X_DES_SER_ID,    (BSPUTILS_SER_ID_ADDR << 1)             },
        {FPD3_93X_DES_SER_AL,    (BSPUTILS_SER5_ALIAS_ADDR << 1)         },
        {FPD3_93X_DES_SLAVE_ID0, (BSPUTILS_OV1063x_I2C_ADDR << 1)        },
        {FPD3_93X_DES_SLAVE_AL0, (BSPUTILS_OV1063x_5_ALIAS_I2C_ADDR << 1)},
        {FPD3_93X_DES_SLAVE_ID1, (BSPUTILS_OV490_I2C_ADDR << 1)          },
        {FPD3_93X_DES_SLAVE_AL1, (BSPUTILS_OV490_5_ALIAS_I2C_ADDR << 1)  },
    },
    {
        {FPD3_93X_DES_SER_ID,    (BSPUTILS_SER_ID_ADDR << 1)             },
        {FPD3_93X_DES_SER_AL,    (BSPUTILS_SER6_ALIAS_ADDR << 1)         },
        {FPD3_93X_DES_SLAVE_ID0, (BSPUTILS_OV1063x_I2C_ADDR << 1)        },
        {FPD3_93X_DES_SLAVE_AL0, (BSPUTILS_OV1063x_6_ALIAS_I2C_ADDR << 1)},
        {FPD3_93X_DES_SLAVE_ID1, (BSPUTILS_OV490_I2C_ADDR << 1)          },
        {FPD3_93X_DES_SLAVE_AL1, (BSPUTILS_OV490_6_ALIAS_I2C_ADDR << 1)  },
    },
    {
        {FPD3_93X_DES_SER_ID,    (BSPUTILS_SER_ID_ADDR << 1)             },
        {FPD3_93X_DES_SER_AL,    (BSPUTILS_SER7_ALIAS_ADDR << 1)         },
        {FPD3_93X_DES_SLAVE_ID0, (BSPUTILS_OV1063x_I2C_ADDR << 1)        },
        {FPD3_93X_DES_SLAVE_AL0, (BSPUTILS_OV1063x_7_ALIAS_I2C_ADDR << 1)},
        {FPD3_93X_DES_SLAVE_ID1, (BSPUTILS_OV490_I2C_ADDR << 1)          },
        {FPD3_93X_DES_SLAVE_AL1, (BSPUTILS_OV490_7_ALIAS_I2C_ADDR << 1)  },
    },
    {
        {FPD3_93X_DES_SER_ID,    (BSPUTILS_SER_ID_ADDR << 1)             },
        {FPD3_93X_DES_SER_AL,    (BSPUTILS_SER8_ALIAS_ADDR << 1)         },
        {FPD3_93X_DES_SLAVE_ID0, (BSPUTILS_OV1063x_I2C_ADDR << 1)        },
        {FPD3_93X_DES_SLAVE_AL0, (BSPUTILS_OV1063x_8_ALIAS_I2C_ADDR << 1)},
        {FPD3_93X_DES_SLAVE_ID1, (BSPUTILS_OV490_I2C_ADDR << 1)          },
        {FPD3_93X_DES_SLAVE_AL1, (BSPUTILS_OV490_8_ALIAS_I2C_ADDR << 1)  },
    }
};

static BspUtils_I2cParams gMulDesIoParamsOv490[1] = {
    {FPD3_93X_DES_BC_GPIO_CTL0, 0x98}, // GPIO1, HIGH, GPIO0 low
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
            serI2cDevAddr = BspUtils_ovInstIdToSerI2cAddr(ovInstId);
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
        (FVID2_VID_SENSOR_GW4200_IMX290_DRV == devDrvId) ||
        (FVID2_VID_SENSOR_MULDES_OV490_DRV == devDrvId))
    {
        BspOsal_semWait(glockSem, BSP_OSAL_WAIT_FOREVER);

        ovInstId = BspUtils_appConvToOvInstId(devDrvId, devInstId);
        if (ovInstId < BSPUTILS_MAX_DES_SER_COUNT)
        {
            if ((UInt32) FALSE == gSerDesCfgDone[ovInstId])
            {
                retVal = BspUtils_appConfMultiDeSer(devDrvId,
                                                    ovInstId,
                                                    gDesAddr[ovInstId]);
                if (BSP_SOK == retVal)
                {
                    serI2cDevAddr = BspUtils_ovInstIdToSerI2cAddr(ovInstId);
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
                serI2cDevAddr = BspUtils_ovInstIdToSerI2cAddr(ovInstId);
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
                ovInstId = BSPUTILS_OVINST_ID_1;
                break;

            case BSP_DEVICE_MULDES_IMX290_INST_ID_2:
                ovInstId = BSPUTILS_OVINST_ID_2;
                break;

            case BSP_DEVICE_MULDES_IMX290_INST_ID_3:
                ovInstId = BSPUTILS_OVINST_ID_3;
                break;

            case BSP_DEVICE_MULDES_IMX290_INST_ID_4:
                ovInstId = BSPUTILS_OVINST_ID_4;
                break;

            case BSP_DEVICE_MULDES_IMX290_INST_ID_5:
                ovInstId = BSPUTILS_OVINST_ID_5;
                break;

            case BSP_DEVICE_MULDES_IMX290_INST_ID_6:
                ovInstId = BSPUTILS_OVINST_ID_6;
                break;

            default:
                ovInstId = BSPUTILS_MAX_DES_SER_COUNT;
                break;
        }
    }
    else if(FVID2_VID_SENSOR_MULDES_OV1063X_DRV == devDrvId)
    {
        switch (devInstId)
        {
            case BSP_DEVICE_MULDES_OV1063X_INST_ID_1:
                ovInstId = BSPUTILS_OVINST_ID_1;
                break;

            case BSP_DEVICE_MULDES_OV1063X_INST_ID_2:
                ovInstId = BSPUTILS_OVINST_ID_2;
                break;

            case BSP_DEVICE_MULDES_OV1063X_INST_ID_3:
                ovInstId = BSPUTILS_OVINST_ID_3;
                break;

            case BSP_DEVICE_MULDES_OV1063X_INST_ID_4:
                ovInstId = BSPUTILS_OVINST_ID_4;
                break;

            case BSP_DEVICE_MULDES_OV1063X_INST_ID_5:
                ovInstId = BSPUTILS_OVINST_ID_5;
                break;

            case BSP_DEVICE_MULDES_OV1063X_INST_ID_6:
                ovInstId = BSPUTILS_OVINST_ID_6;
                break;

            case BSP_DEVICE_MULDES_OV1063X_INST_ID_7:
                ovInstId = BSPUTILS_OVINST_ID_7;
                break;

            case BSP_DEVICE_MULDES_OV1063X_INST_ID_8:
                ovInstId = BSPUTILS_OVINST_ID_8;
                break;

            default:
                ovInstId = BSPUTILS_MAX_DES_SER_COUNT;
                break;
        }
    }
    else if(FVID2_VID_SENSOR_MULDES_OV490_DRV == devDrvId)
    {
        switch (devInstId)
        {
            case BSP_DEVICE_MULDES_OV490_INST_ID_1:
                ovInstId = BSPUTILS_OVINST_ID_1;
                break;

            case BSP_DEVICE_MULDES_OV490_INST_ID_2:
                ovInstId = BSPUTILS_OVINST_ID_2;
                break;

            case BSP_DEVICE_MULDES_OV490_INST_ID_3:
                ovInstId = BSPUTILS_OVINST_ID_3;
                break;

            case BSP_DEVICE_MULDES_OV490_INST_ID_4:
                ovInstId = BSPUTILS_OVINST_ID_4;
                break;

            case BSP_DEVICE_MULDES_OV490_INST_ID_5:
                ovInstId = BSPUTILS_OVINST_ID_5;
                break;

            case BSP_DEVICE_MULDES_OV490_INST_ID_6:
                ovInstId = BSPUTILS_OVINST_ID_6;
                break;

            case BSP_DEVICE_MULDES_OV490_INST_ID_7:
                ovInstId = BSPUTILS_OVINST_ID_7;
                break;

            case BSP_DEVICE_MULDES_OV490_INST_ID_8:
                ovInstId = BSPUTILS_OVINST_ID_8;
                break;

            default:
                ovInstId = BSPUTILS_MAX_DES_SER_COUNT;
                break;
        }
    }

    return (ovInstId);
}

static UInt32 BspUtils_appConvToI2cInstId(UInt32 ovInstId)
{
    UInt32 i2cInstId;

    switch (ovInstId)
    {
        case BSPUTILS_OVINST_ID_1:
        /* Intended fallthrough */
        case BSPUTILS_OVINST_ID_2:
        /* Intended fallthrough */
        case BSPUTILS_OVINST_ID_3:
        /* Intended fallthrough */
        case BSPUTILS_OVINST_ID_4:
            i2cInstId = BSP_DEVICE_I2C_INST_ID_3;
            break;

        case BSPUTILS_OVINST_ID_5:
        /* Intended fallthrough */
        case BSPUTILS_OVINST_ID_6:
        /* Intended fallthrough */
        case BSPUTILS_OVINST_ID_7:
        /* Intended fallthrough */
        case BSPUTILS_OVINST_ID_8:
            i2cInstId = BSP_DEVICE_I2C_INST_ID_4;
            break;

        default:
            i2cInstId = BSP_DEVICE_I2C_INST_ID_3;
            break;
    }

    return i2cInstId;
}

static UInt32 BspUtils_ovInstIdToSerI2cAddr(UInt32 ovInstId)
{
    UInt32 serI2cDevAddr;

    switch (ovInstId)
    {
        case BSPUTILS_OVINST_ID_1:
            serI2cDevAddr = BSPUTILS_SER1_ALIAS_ADDR;
            break;
        case BSPUTILS_OVINST_ID_2:
            serI2cDevAddr = BSPUTILS_SER2_ALIAS_ADDR;
            break;
        case BSPUTILS_OVINST_ID_3:
            serI2cDevAddr = BSPUTILS_SER3_ALIAS_ADDR;
            break;
        case BSPUTILS_OVINST_ID_4:
            serI2cDevAddr = BSPUTILS_SER4_ALIAS_ADDR;
            break;
        case BSPUTILS_OVINST_ID_5:
            serI2cDevAddr = BSPUTILS_SER5_ALIAS_ADDR;
            break;
        case BSPUTILS_OVINST_ID_6:
            serI2cDevAddr = BSPUTILS_SER6_ALIAS_ADDR;
            break;
        case BSPUTILS_OVINST_ID_7:
            serI2cDevAddr = BSPUTILS_SER7_ALIAS_ADDR;
            break;
        case BSPUTILS_OVINST_ID_8:
            serI2cDevAddr = BSPUTILS_SER8_ALIAS_ADDR;
            break;
        default:
            serI2cDevAddr = BSPUTILS_SER1_ALIAS_ADDR;
    }

    return serI2cDevAddr;
}

static Int32 BspUtils_appConfSer(UInt32 ovInstId, UInt32 i2cDevAddr)
{
    Int32  retVal = BSP_SOK;
    UInt32 nIdx   = 0;
    UInt8  nRegAddr, nRegValue;
    UInt32 cnt;
    UInt32 i2cInstId;

    i2cInstId = BspUtils_appConvToI2cInstId(ovInstId);

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
        for (cnt = 0; cnt < BSPUTILS_SER_RESET_CHECK_COUNT; cnt++)
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
            for (cnt = 0; cnt < BSPUTILS_SER_RESET_CHECK_COUNT; cnt++)
            {
                retVal = Bsp_deviceWrite8(i2cInstId,
                                          i2cDevAddr,
                                          &gSerParams[nIdx].nRegAddr,
                                          &gSerParams[nIdx].nRegValue,
                                          (UInt32) 1U);
                BspOsal_sleep((UInt32) 10U);
                if (retVal == BSP_SOK)
                {
                    break;
                }
            }

            if (cnt == BSPUTILS_SER_RESET_CHECK_COUNT)
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

static Int32 BspUtils_appDeConfSer(UInt32 ovInstId, UInt32 i2cDevAddr)
{
    Int32  retVal = BSP_SOK;
    UInt32 nIdx   = 0;
    UInt32 i2cInstId;

    i2cInstId = BspUtils_appConvToI2cInstId(ovInstId);

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

static Int32 BspUtils_appDeConfMultiDeSer(UInt32 ovInstId, UInt32 i2cDevAddr)
{
    Int32  retVal  = BSP_SOK;
    UInt32 nIdx    = 0;
    UInt32 numRegs = 1U;
    UInt32 i2cInstId;

    i2cInstId = BspUtils_appConvToI2cInstId(ovInstId);

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

static Int32 BspUtils_appConfMultiDeSer(UInt32 devDrvId, UInt32 ovInstId, UInt32 i2cDevAddr)
{
    Int32  retVal = BSP_SOK;
    UInt32 nIdx   = 0;
    UInt8  nRegAddr, nRegValue;
    UInt32 cnt = 0;
    UInt32 i2cInstId;

    i2cInstId = BspUtils_appConvToI2cInstId(ovInstId);

    for (nIdx = 0U;
         nIdx <
         (sizeof (fpd3_934_des_init_seq) /
          sizeof (fpd3_934_des_init_seq[0U]));
         nIdx++)
    {
        retVal = Bsp_deviceWrite8(i2cInstId,
                                  i2cDevAddr,
                                  &(fpd3_934_des_init_seq[nIdx].nRegAddr),
                                  &(fpd3_934_des_init_seq[nIdx].nRegValue),
                                  (UInt32) 1U);
        if (retVal != BSP_SOK)
        {
            GT_1trace(
                BspAppTrace, GT_ERR,
                "Error: Failed to Configure 934 for device 0x%x \n",
                i2cDevAddr);
            break;
        }

        /* sleep */
        BspOsal_sleep((UInt32) 1U);
    }

    if (FVID2_VID_SENSOR_MULDES_OV490_DRV == devDrvId) {
        for (nIdx = 0U;
             nIdx <
             (sizeof (gMulDesIoParamsOv490) /
              sizeof (gMulDesIoParamsOv490[0U]));
             nIdx++)
        {
            retVal = Bsp_deviceWrite8(i2cInstId,
                                      i2cDevAddr,
                                      &(gMulDesIoParamsOv490[nIdx].nRegAddr),
                                      &(gMulDesIoParamsOv490[nIdx].nRegValue),
                                      (UInt32) 1U);
            if (retVal != BSP_SOK)
            {
                GT_1trace(
                    BspAppTrace, GT_ERR,
                    "Error: Failed to Configure 934 for device 0x%x \n",
                    i2cDevAddr);
                break;
            }

            /* sleep */
            BspOsal_sleep((UInt32) 1U);
        }
    }

    for (nIdx = 0U;
         nIdx <
         (sizeof (gMulDesParams[ovInstId]) /
          sizeof (gMulDesParams[ovInstId][0U]));
         nIdx++)
    {
        retVal += Bsp_deviceWrite8(i2cInstId,
                                   i2cDevAddr,
                                   &(gMulDesParams[ovInstId][nIdx].nRegAddr),
                                   &(gMulDesParams[ovInstId][nIdx].nRegValue),
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

    nRegAddr  = FPD3_93X_DES_SER_ID;
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

    nRegAddr  = FPD3_93X_DES_SER_AL;
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

    nRegAddr  = FPD3_93X_DES_DEVICE_STS;
    nRegValue = 0x0U;
    /* Checking the Lock status */
    while(((nRegValue & FPD3_93X_DES_LOCK_DETECT) == 0x0) &&
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
        BspOsal_sleep((UInt32) 10U);
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

static Int32 BspUtils_appPrintReg(UInt32 ovInstId,
                                  UInt32 i2cDevAddr,
                                  UInt8  nRegAddr)
{
    Int32  retVal = BSP_SOK;
    UInt8  nRegValue;
    UInt32 i2cInstId;

    i2cInstId = BspUtils_appConvToI2cInstId(ovInstId);

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
