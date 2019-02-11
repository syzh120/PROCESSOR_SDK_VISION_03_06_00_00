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
 *  \file bsputils_ub960.c
 *
 *  \brief Implements APIs to initialize, de-initialize UB960 EVM, address
 *          aliases & reset sensors.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>

#if defined (BARE_METAL)
#include <ti/csl/tistdtypes.h>
#else
#include <xdc/std.h>
#endif

#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/bsp_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/vps/include/common/bsp_common.h>
#include <ti/drv/vps/include/boards/bsp_board.h>
#include <ti/drv/vps/include/devices/bsp_device.h>
#include <ti/drv/vps/examples/utility/bsputils_app.h>
#include <ti/drv/vps/examples/utility/bsputils_ub960.h>
#include <ti/csl/csl_gpio.h>
#include <ti/csl/soc.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define UB960_REG_DELAY_TIME 1
/**< Time delay between programming each UB960 register */

#define UB960_FREQ_SEL_25MBS (0x58 | BSPUTILS_BACKCHFREQSELECT_25MHZ) /* 2G Mode */
#define UB960_FREQ_SEL_50MBS (0x58 | BSPUTILS_BACKCHFREQSELECT_50MHZ) /* 4G Mode */
#define UB960_FREQ_SEL  UB960_FREQ_SEL_25MBS  /* Use 2G Mode by default. */
/**< FPD-Link Speed Options */

/*#define UB960_TIDA1130_PATTERN_GEN    */
/*#define UB960_UB953_PATTERN_GEN       */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
static Int32 setCameraPower(BspUtils_FpdCamPowerLevel pwrlvl);
static Int32 initDeserializer(UInt32 instId);
#ifdef BOARD_TYPE_TDA3XX_RVP
static Int32 resetDeserializer(void);
static Int32 writeI2Cconfig(
                    Int32 regCount,
                    BspUtils_Ub960I2cParams *params,
                    UInt32 slaveAddr);
#endif
static void setUb960Gpio0To1(UInt32 instId, UInt32 port);

static Int32 BspUtils_appInitUB913PassThroughGPIO0(UInt32 instId, UInt32 portId);

static Int32 BspUtils_resetAR12xxToSOP4(UInt8 IOExpAddr);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
#ifdef BOARD_TYPE_TDA3XX_RVP
    /*
     *  The UB960 power ON on RVP should be done only once.
     *  These flags prevent UB960 power ON for subsequent init sequences.
     */
    static Bool gSetPowerDone = (UInt32)FALSE;
    static Bool gInitDeserDone = (UInt32)FALSE;
#endif

BspUtils_Ub960I2cParams gUb960Cfg_TIDA[] = {
    {0x01, 0x01, 0xFFF},    /* Digital Reset 0 */
    {0x1F, 0x05, 0x4FF},

    /* TIDA00262 1 */
    {0x4C, 0x01, 0x0},
    {0x58, 0x58, 0x0},
    {0x5D, 0xB0, 0x0},
    {0x65, ((UInt8) (TIDA00262_PORT_0_SER_ADDR << 1U)), 0x0},
    {0x5E, 0x20, 0x0},
    {0x66, ((UInt8) (TIDA00262_PORT_0_SENSOR_ADDR << 1U)), 0x0},
    {0x7C, 0x00, 0x0},
    {0x6e, 0x99, 0x0},
    {0x70, 0x2B, 0x0},
    {0x71, 0x2C, 0x0},
    {0x6D, 0x7E, 0x0},

    /* TIDA00262 2 */
    {0x4C, 0x12, 0x0},
    {0x58, 0x58, 0x0},
    {0x5D, 0xB0, 0x0},
    {0x65, ((UInt8) (TIDA00262_PORT_1_SER_ADDR << 1U)), 0x0},
    {0x5E, 0x20, 0x0},
    {0x66, ((UInt8) (TIDA00262_PORT_1_SENSOR_ADDR << 1U)), 0x0},
    {0x7C, 0x00, 0x0},
    {0x6e, 0x99, 0x0},
    {0x70, 0x6B, 0x0},
    {0x71, 0x6C, 0x0},
    {0x6D, 0x7E, 0x0},

    /* TIDA00262 3 */
    {0x4C, 0x24, 0x0},
    {0x58, 0x58, 0x0},
    {0x5D, 0xB0, 0x0},
    {0x65, ((UInt8) (TIDA00262_PORT_2_SER_ADDR << 1U)), 0x0},
    {0x5E, 0x20, 0x0},
    {0x66, ((UInt8) (TIDA00262_PORT_2_SENSOR_ADDR << 1U)), 0x0},
    {0x7C, 0x00, 0x0},
    {0x6e, 0x99, 0x0},
    {0x70, 0xAB, 0x0},
    {0x71, 0xAC, 0x0},
    {0x6D, 0x7E, 0x0},

    /* TIDA00262 4 */
    {0x4C, 0x38, 0x0},
    {0x58, 0x58, 0x0},
    {0x5D, 0xB0, 0x0},
    {0x65, ((UInt8) (TIDA00262_PORT_3_SER_ADDR << 1U)), 0x0},
    {0x5E, 0x20, 0x0},
    {0x66, ((UInt8) (TIDA00262_PORT_3_SENSOR_ADDR << 1U)), 0x0},
    {0x7C, 0x00, 0x0},
    {0x6e, 0x99, 0x0},
    {0x70, 0xEB, 0x0},
    {0x71, 0xEC, 0x0},
    {0x6D, 0x7E, 0x0},

    {0xB0, 0x1C, 0xFFF},
    {0xB1, 0x13, 0xFFF},
    {0xB2, 0x1F, 0xFFF},

    {0x32, 0x01, 0x0},
    {0x33, 0x03, 0x0},
    {0x20, 0x00, 0x0}
};

/*Duplicate definition - Also defined in bsp_boardPriv.h. Must change both together*/
#define BOARD_APT_AR0143_I2C_ADDR_0             (0x10U)

BspUtils_Ub960I2cParams gUb960Cfg_MARS_AR0143[] = {
    {0x01, 0x01, 0x10},    /* Digital Reset 0 */
    {0x1F, 0x05, 0x10},

    /* MARS AR0143 1 */
    {0x4C, 0x01, 0x10},
    {0x58, 0x58, 0x10},
    {0x5C, ((UInt8) ( MARS_PORT_0_SER_ADDR << 1U)), 0x10},
    {0x5D, ((UInt8) ( MARS_PORT_0_SENSOR_ADDR << 1U)), 0x10},
    {0x65, ((UInt8) (MARS_PORT_0_SER_ADDR << 1U)), 0x10},
    {0x5E, (BOARD_APT_AR0143_I2C_ADDR_0 << 1U), 0x10},
    {0x66, ((UInt8) (MARS_PORT_0_SENSOR_ADDR << 1U)), 0x10},
    {0x7C, 0x00, 0x10},
    {0x6e, 0x99, 0x10},
    {0x70, 0x2B, 0x10},
    {0x71, 0x2C, 0x10},
    {0x6D, 0x7E, 0x10},

    /* MARS AR0143 2 */
    {0x4C, 0x12, 0x10},
    {0x58, 0x58, 0x10},
    {0x5C, ((UInt8) ( MARS_PORT_1_SER_ADDR << 1U)), 0x10},
    {0x5D, ((UInt8) ( MARS_PORT_1_SENSOR_ADDR << 1U)), 0x10},
    {0x65, ((UInt8) (MARS_PORT_1_SER_ADDR << 1U)), 0x10},
    {0x5E, (BOARD_APT_AR0143_I2C_ADDR_0 << 1U), 0x10},
    {0x66, ((UInt8) (MARS_PORT_1_SENSOR_ADDR << 1U)), 0x10},
    {0x7C, 0x00, 0x10},
    {0x6e, 0x99, 0x10},
    {0x70, 0x2B, 0x10},
    {0x71, 0x6C, 0x10},
    {0x6D, 0x7E, 0x10},

    /* MARS AR0143 3 */
    {0x4C, 0x24, 0x10},
    {0x58, 0x58, 0x10},
    {0x5C, ((UInt8) ( MARS_PORT_2_SER_ADDR << 1U)), 0x10},
    {0x5D, ((UInt8) ( MARS_PORT_2_SENSOR_ADDR << 1U)), 0x10},
    {0x65, ((UInt8) (MARS_PORT_2_SER_ADDR << 1U)), 0x10},
    {0x5E, (BOARD_APT_AR0143_I2C_ADDR_0 << 1U), 0x10},
    {0x66, ((UInt8) (MARS_PORT_2_SENSOR_ADDR << 1U)), 0x10},
    {0x7C, 0x00, 0x10},
    {0x6e, 0x99, 0x10},
    {0x70, 0x2B, 0x10},
    {0x71, 0xAC, 0x10},
    {0x6D, 0x7E, 0x10},

    /* MARS AR0143 4 */
    {0x4C, 0x38, 0x10},
    {0x58, 0x58, 0x10},
    {0x5C, ((UInt8) ( MARS_PORT_3_SER_ADDR << 1U)), 0x10},
    {0x5D, ((UInt8) ( MARS_PORT_3_SENSOR_ADDR << 1U)), 0x10},
    {0x65, ((UInt8) (MARS_PORT_3_SER_ADDR << 1U)), 0x10},
    {0x5E, (BOARD_APT_AR0143_I2C_ADDR_0 << 1U), 0x10},
    {0x66, ((UInt8) (MARS_PORT_3_SENSOR_ADDR << 1U)), 0x10},
    {0x7C, 0x00, 0x10},
    {0x6e, 0x99, 0x10},
    {0x70, 0x2B, 0x10},
    {0x71, 0xEC, 0x10},
    {0x6D, 0x7E, 0x10},

    {0xB0, 0x1C, 0x10},
    {0xB1, 0x13, 0x10},
    {0xB2, 0x1F, 0x10},

    {0x32, 0x01, 0x10},
    {0x33, 0x03, 0x10},
    {0x20, 0x00, 0x10}
};

BspUtils_Ub960I2cParams gUB953SerCfg_TIDA1130[] = {
    /* Setup for OV2775 to UB953 on 2/4 lanes */
    {0x02, 0x52, 0x10},

    {0x06, 0x21, 0x10},
    {0x07, 0x28, 0x10},

    {0x0E, 0xF0, 0x10},
    {0x0D, 0x00, 0x10},
    {0x0D, 0x0C, 0x10},
};


BspUtils_Ub960I2cParams gUb960Cfg_TIDA1130[] = {
    /* Setup for OV2775 to UB953 on 2 lanes */
    {0x0C, 0x0F, 0x10},
    {0x1F, 0x00, 0x4FF}, /* 1.6Gbps CSI Freq */

    /*CAMERA 1*/
    {0x4C, 0x01, 0x10},        /*Page FPD3 port RX0 registers for R/W*/
    {0x58, 0x5D , 0x10},        /*Enable and set backchannel rate to 50Mbs / I2C passthrough enabled*/
    {0x5C, 0x30, 0x10},        /*set serializer alias to Ox18 (7-bit)*/
    {0x5D, ((uint8_t) (TIDA1130_OV2775_SER_ADDR << 1U)), 0x0},
    {0x65, ((uint8_t) (TIDA1130_OV2775_PORT_0_SER_ALIAS_ADDR << 1U)), 0x0},
    {0x5E, ((uint8_t) (TIDA1130_OV2775_SENSOR_ADDR << 1U)), 0x0},
    {0x66, ((uint8_t) (TIDA1130_OV2775_PORT_0_SENSOR_ALIAS_ADDR << 1U)), 0x0},
    {0x6D, 0x7C, 0x10},        /*CSI and coax mode*/
    {0xD5, 0xF0, 0x10},       /* Set AEQ MIN/MAX widest values*/
    {0x7C, 0x01, 0x10},        /*same as Omnivision*/
    {0x70, 0x2B, 0x10},        /*same as Omnivision*/
    {0x71, 0x2C, 0x10},        /*same as Omnivision*/
    {0x72, 0xE4, 0x10},        /*same as Omnivision*/

     /*CAMERA 2*/
    {0x4C, 0x12, 0x10},        /*Page FPD3 port RX0 registers for R/W*/
    {0x58, 0x5D , 0x10},        /*Enable and set backchannel rate to 50Mbs / I2C passthrough enabled*/
    {0x5C, 0x30, 0x10},        /*set serializer alias to Ox18 (7-bit)*/
    {0x5D, ((uint8_t) (TIDA1130_OV2775_SER_ADDR << 1U)), 0x0},
    {0x65, ((uint8_t) (TIDA1130_OV2775_PORT_1_SER_ALIAS_ADDR << 1U)), 0x0},
    {0x5E, ((uint8_t) (TIDA1130_OV2775_SENSOR_ADDR << 1U)), 0x0},
    {0x66, ((uint8_t) (TIDA1130_OV2775_PORT_1_SENSOR_ALIAS_ADDR << 1U)), 0x0},
    {0x6D, 0x7C, 0x10},        /*CSI and coax mode*/
    {0xD5, 0xF0, 0x10},       /* Set AEQ MIN/MAX widest values*/
    {0x7C, 0x01, 0x10},        /*same as Omnivision*/
    {0x70, 0x2B, 0x10},        /*same as Omnivision*/
    {0x71, 0x2C, 0x10},        /*same as Omnivision*/
    {0x72, 0x39, 0x10},        /*same as Omnivision*/

      /*CAMERA 3*/
    {0x4C, 0x24, 0x10},        /*Page FPD3 port RX0 registers for R/W*/
    {0x58, 0x5D , 0x10},        /*Enable and set backchannel rate to 50Mbs / I2C passthrough enabled*/
    {0x5C, 0x30, 0x10},        /*set serializer alias to Ox18 (7-bit)*/
    {0x5D, ((uint8_t) (TIDA1130_OV2775_SER_ADDR << 1U)), 0x0},
    {0x65, ((uint8_t) (TIDA1130_OV2775_PORT_2_SER_ALIAS_ADDR << 1U)), 0x0},
    {0x5E, ((uint8_t) (TIDA1130_OV2775_SENSOR_ADDR << 1U)), 0x0},
    {0x66, ((uint8_t) (TIDA1130_OV2775_PORT_2_SENSOR_ALIAS_ADDR << 1U)), 0x0},
    {0x6D, 0x7C, 0x10},        /*CSI and coax mode*/
    {0xD5, 0xF0, 0x10},       /* Set AEQ MIN/MAX widest values*/
    {0x7C, 0x01, 0x10},        /*same as Omnivision*/
    {0x70, 0x2B, 0x10},        /*same as Omnivision*/
    {0x71, 0x2C, 0x10},        /*same as Omnivision*/
    {0x72, 0x4e, 0x10},        /*same as Omnivision*/

     /*CAMERA 4*/
    {0x4C, 0x38, 0x10},        /*Page FPD3 port RX0 registers for R/W*/
    {0x58, 0x5D , 0x10},        /*Enable and set backchannel rate to 50Mbs / I2C passthrough enabled*/
    {0x5C, 0x30, 0x10},        /*set serializer alias to Ox18 (7-bit)*/
    {0x5D, ((uint8_t) (TIDA1130_OV2775_SER_ADDR << 1U)), 0x0},
    {0x65, ((uint8_t) (TIDA1130_OV2775_PORT_3_SER_ALIAS_ADDR << 1U)), 0x0},
    {0x5E, ((uint8_t) (TIDA1130_OV2775_SENSOR_ADDR << 1U)), 0x0},
    {0x66, ((uint8_t) (TIDA1130_OV2775_PORT_3_SENSOR_ALIAS_ADDR << 1U)), 0x0},
    {0x6D, 0x7C, 0x10},        /*CSI and coax mode*/
    {0xD5, 0xF0, 0x10},       /* Set AEQ MIN/MAX widest values*/
    {0x7C, 0x01, 0x10},        /*same as Omnivision*/
    {0x70, 0x2B, 0x10},        /*same as Omnivision*/
    {0x71, 0x2C, 0x10},        /*same as Omnivision*/
    {0x72, 0x93, 0x10},        /*same as Omnivision*/

    {0x32, 0x01, 0x10},        /*CSI0 select*/
    {0x33, 0x03, 0x10},        /*CSI_EN & CSI0 4L*/

    {0x21, 0x03, 0x10},
    {0x20, 0x00, 0x10},

    {0xB9, 0x18, 0x10},        /*ENABLE PARITY ERROR COUNT*/
    {0x42, 0x71, 0x10},        /*ENABLE S-Filter with AEQ*/
    {0x10, 0x59, 0x10},        /*Output Frame on GPIO0 */
};

BspUtils_Ub960I2cParams gUB953SerCfg_D3IMX390[] = {
    {0x01, 0x01, 2000}, /* reset */
    {0x02, 0x72, 0x10},

    {0x06, 0x21, 0x1F},
    {0x07, 0x28, 0x1F},

    {0x0D, 0x01, 0x10},
    {0x0E, 0xF0, 0x10},
    {0xB0, 0x04, 0x10},
    {0xB1, 0x08, 0x10},
    {0xB2, 0x07, 0x10},

#if defined(UB960_UB953_PATTERN_GEN)
    /* #Patgen Fixed Colorbar 1920x1080p30, 12Bp, 2pixel per block of 3 bytes */
    {0xB0, 0x00, 0x10},
    {0xB1, 0x01, 0x10},
    {0xB2, 0x01, 0x10},
    {0xB1, 0x02, 0x10},
    {0xB2, 0x80, 0x10},
    {0xB1, 0x03, 0x10},
    {0xB2, 0x2C, 0x10},

    {0xB1, 0x04, 0x10},
    {0xB2, 0x0b, 0x10},
    {0xB1, 0x05, 0x10},
    {0xB2, 0x40, 0x10},

    {0xB1, 0x06, 0x10},
    {0xB2, 0x01, 0x10},
    {0xB1, 0x07, 0x10},
    {0xB2, 0x68, 0x10},

    {0xB1, 0x08, 0x10},
    {0xB2, 0x04, 0x10},
    {0xB1, 0x09, 0x10},
    {0xB2, 0x38, 0x10},

    {0xB1, 0x0A, 0x10},
    {0xB2, 0x04, 0x10},
    {0xB1, 0x0B, 0x10},
    {0xB2, 0xB0, 0x10},

    {0xB1, 0x0C, 0x10},
    {0xB2, 0x0C, 0x10},
    {0xB1, 0x0D, 0x10},
    {0xB2, 0x67, 0x10},

    {0xB1, 0x0E, 0x10},
    {0xB2, 0x21, 0x10},
    {0xB1, 0x0F, 0x10},
    {0xB2, 0x0A, 0x10},
#endif

};

BspUtils_Ub960I2cParams gUB960SerCfg_D3IMX390[] = {
    {0x01, 0x02, 0xFFF},
    {0x1f, 0x00, 0xFFF},

    {0xB0, 0x1C,0xFFF},
    {0xB1, 0x16,0xFFF},
    {0xB2, 0x00,0xFFF},
    {0xB1, 0x17,0xFFF},
    {0xB2, 0x00,0xFFF},
    {0xB1, 0x18,0xFFF},
    {0xB2, 0x00,0xFFF},
    {0xB1, 0x19,0xFFF},
    {0xB2, 0x00,0xFFF},
    {0xB0, 0x1C,0xFFF},
    {0xB1, 0x15,0xFFF},
    {0xB2, 0x0A,0xFFF},
    {0xB2, 0x00,0xFFFF},

    {0x0D, 0x90, 0xFFF}, /*I/O to 3V3 - Options not valid with datashee*/
    {0x0C, 0x0F, 0xFFF}, /*Enable All ports*/

    /*Select Channel 0*/
    {0x4C, 0x01, 0xFFF},
    {0x58, 0x5D, 0xFFF}, /*Enable Back channel, set to 50Mbs*/
    {0x72, 0x00, 0xFFF}, /*VC map*/

    /*Select Channel 1*/
    {0x4C, 0x12, 0xFFF},
    {0x58, 0x5D, 0xFFF},/*Enable Back channel, set to 50Mbs*/

    /*Select Channel 2*/
    {0x4C, 0x24, 0xFFF},
    {0x58, 0x5D, 0xFFF},/*Enable Back channel, set to 50Mbs*/

    /*Select Channel 3*/
    {0x4C, 0x38, 0xFFF},
    {0x58, 0x5D, 0xFFF},/*Enable Back channel, set to 50Mbs*/

    /*Select Channel 0*/
    {0x4C, 0x01, 0xFFF},
    {0xB0, 0x04, 0xFFF},
    {0xB1, 0x03, 0xFFF},
    {0xB2, 0x20, 0xFFF},
    {0xB1, 0x13, 0xFFF},
    {0xB2, 0x20, 0xFFF},
    {0xB0, 0x04, 0xFFF},
    {0xB1, 0x04, 0xFFF},
    {0xB2, 0x3F, 0xFFF},
    {0xB1, 0x14, 0xFFF},
    {0xB2, 0x3F, 0xFFF},
    {0x42, 0x71, 0xFFF}, /*Unknown*/
    {0x41, 0xF0, 0xFFF}, /*Unknown*/
    {0xB9, 0x18, 0xFFF},

    /*Select Channel 1*/
    {0x4C, 0x12, 0xFFF},
    {0xB0, 0x08, 0xFFF},
    {0xB1, 0x03, 0xFFF},
    {0xB2, 0x20, 0xFFF},
    {0xB1, 0x13, 0xFFF},
    {0xB2, 0x20, 0xFFF},
    {0xB0, 0x08, 0xFFF},
    {0xB1, 0x04, 0xFFF},
    {0xB2, 0x3F, 0xFFF},
    {0xB1, 0x14, 0xFFF},
    {0xB2, 0x3F, 0xFFF},
    {0xB0, 0x08, 0xFFF},
    {0x42, 0x71, 0xFFF}, /*Unknown*/
    {0x41, 0xF0, 0xFFF}, /*Unknown*/
    {0xB9, 0x18, 0xFFF},

    /*Select Channel 2*/
    {0x4C, 0x24, 0xFFF},
    {0xB0, 0x0C, 0xFFF},
    {0xB1, 0x03, 0xFFF},
    {0xB2, 0x20, 0xFFF},
    {0xB1, 0x13, 0xFFF},
    {0xB2, 0x20, 0xFFF},
    {0xB0, 0x0C, 0xFFF},
    {0xB1, 0x04, 0xFFF},
    {0xB2, 0x3F, 0xFFF},
    {0xB1, 0x14, 0xFFF},
    {0xB2, 0x3F, 0xFFF},
    {0x42, 0x71, 0xFFF},/*Unknown*/
    {0x41, 0xF0, 0xFFF},/*Unknown*/
    {0xB9, 0x18, 0xFFF},

    /*Select Channel 3*/
    {0x4C, 0x38, 0xFFF},
    {0xB0, 0x10, 0xFFF},
    {0xB1, 0x03, 0xFFF},
    {0xB2, 0x20, 0xFFF},
    {0xB1, 0x13, 0xFFF},
    {0xB2, 0x20, 0xFFF},
    {0xB0, 0x10, 0xFFF},
    {0xB1, 0x04, 0xFFF},
    {0xB2, 0x3F, 0xFFF},
    {0xB1, 0x14, 0xFFF},
    {0xB2, 0x3F, 0xFFF},
    {0x42, 0x71, 0xFFF},/*Unknown*/
    {0x41, 0xF0, 0xFFF},/*Unknown*/
    {0xB9, 0x18, 0xFFF},

    {0x32, 0x01, 0xFFF}, /*Enable TX port 0*/
    {0x20, 0x00, 0xFFF}, /*Forwarding and using CSIport 0 */

    /*Sets GPIOS*/
    {0x10, 0x83, 0xFFF},
    {0x11, 0xA3, 0xFFF},
    {0x12, 0xC3, 0xFFF},
    {0x13, 0xE3, 0xFFF},

    {0x4C, 0x01, 0xFFF}, /* 0x01 */
    {0x32, 0x01, 0xFFF}, /*Enable TX port 0*/
    {0x33, 0x02, 0xFFF}, /*Enable Continuous clock mode and CSI output*/
    {0xBC, 0x00, 0xFFF}, /*Unknown*/
    {0x5D, 0x30, 0xFFF}, /*Serializer I2C Address*/
    {0x65, (D3IMX390_UB960_PORT_0_SER_ADDR << 1U), 0xFFF},
    {0x5E, 0x42, 0xFFF}, /*Sensor I2C Address*/
    {0x66, (D3IMX390_UB960_PORT_0_SENSOR_ADDR << 1U), 0xFFF},
    {0x6D, 0x6C,0xFFF}, /*CSI Mode*/
    {0x72, 0x00,0xFFF}, /*VC Map - All to 0 */
    {0x7C, 0x20, 0xFFFF}, /*Line Valid active high, Frame Valid active high*/
    {0xD5, 0xF3, 0xFFFF}, /*Auto Attenuation*/
    {0xB0,0x1C, 0xFFF},
    {0xB1,0x15, 0xFFF},
    {0xB2,0x0A, 0xFFF},
    {0xB2,0x00, 0xFFF},

    {0x4C, 0x12, 0xFFF}, /* 0x12 */
    {0x32, 0x01, 0xFFF}, /*Enable TX port 0*/
    {0x33, 0x02, 0xFFF}, /*Enable Continuous clock mode and CSI output*/
    {0xBC, 0x00, 0xFFF}, /*Unknown*/
    {0x5D, 0x30, 0xFFF}, /*Serializer I2C Address*/
    {0x65, (D3IMX390_UB960_PORT_1_SER_ADDR << 1U), 0xFFF},
    {0x5E, 0x42, 0xFFF}, /*Sensor I2C Address*/
    {0x66, (D3IMX390_UB960_PORT_1_SENSOR_ADDR << 1U), 0xFFF},
    {0x6D, 0x6C,0xFFF}, /*CSI Mode*/
    {0x72, 0x55,0xFFF}, /*VC Map - All to 1 */
    {0x7C, 0x20, 0xFFFF}, /*Line Valid active high, Frame Valid active high*/
    {0xD5, 0xF3, 0xFFFF}, /*Auto Attenuation*/
    {0xB0,0x1C, 0xFFF},
    {0xB1,0x15, 0xFFF},
    {0xB2,0x0A, 0xFFF},
    {0xB2,0x00, 0xFFF},

    {0x4C, 0x24, 0xFFF}, /* 0x24 */
    {0x32, 0x01, 0xFFF}, /*Enable TX port 0*/
    {0x33, 0x02, 0xFFF}, /*Enable Continuous clock mode and CSI output*/
    {0xBC, 0x00, 0xFFF}, /*Unknown*/
    {0x5D, 0x30, 0xFFF}, /*Serializer I2C Address*/
    {0x65, (D3IMX390_UB960_PORT_2_SER_ADDR << 1U), 0xFFF},
    {0x5E, 0x42, 0xFFF}, /*Sensor I2C Address*/
    {0x66, (D3IMX390_UB960_PORT_2_SENSOR_ADDR << 1U), 0xFFF},
    {0x6D, 0x6C,0xFFF}, /*CSI Mode*/
    {0x72, 0xaa,0xFFF}, /*VC Map - All to 2 */
    {0x7C, 0x20, 0xFFFF}, /*Line Valid active high, Frame Valid active high*/
    {0xD5, 0xF3, 0xFFFF}, /*Auto Attenuation*/
    {0xB0,0x1C, 0xFFF},
    {0xB1,0x15, 0xFFF},
    {0xB2,0x0A, 0xFFF},
    {0xB2,0x00, 0xFFF},

    {0x4C, 0x38, 0xFFF}, /* 0x38 */
    {0x32, 0x01, 0xFFF}, /*Enable TX port 0*/
    {0x33, 0x02, 0xFFF}, /*Enable Continuous clock mode and CSI output*/
    {0xBC, 0x00, 0xFFF}, /*Unknown*/
    {0x5D, 0x30, 0xFFF}, /*Serializer I2C Address*/
    {0x65, (D3IMX390_UB960_PORT_3_SER_ADDR << 1U), 0xFFF},
    {0x5E, 0x42, 0xFFF}, /*Sensor I2C Address*/
    {0x66, (D3IMX390_UB960_PORT_3_SENSOR_ADDR << 1U), 0xFFF},
    {0x6D, 0x6C,0xFFF}, /*CSI Mode*/
    {0x72, 0xFF,0xFFF}, /*VC Map - All to 3 */
    {0x7C, 0x20, 0xFFFF}, /*Line Valid active high, Frame Valid active high*/
    {0xD5, 0xF3, 0xFFFF}, /*Auto Attenuation*/
    {0xB0,0x1C, 0xFFF},
    {0xB1,0x15, 0xFFF},
    {0xB2,0x0A, 0xFFF},
    {0xB2,0x00, 0xFFF},

#if defined(UB960_TIDA1130_PATTERN_GEN)
    /* #Patgen Fixed Colorbar 1920x1080p30, 12Bp, 2pixel per block of 3 bytes */
    {0xB0, 0x00, 0x10},
    {0xB1, 0x01, 0x10},
    {0xB2, 0x01, 0x10},
    {0xB1, 0x02, 0x10},
    {0xB2, 0x33, 0x10},
    {0xB1, 0x03, 0x10},
    {0xB2, 0x2C, 0x10},

    {0xB1, 0x04, 0x10},
    {0xB2, 0x0b, 0x10},
    {0xB1, 0x05, 0x10},
    {0xB2, 0x40, 0x10},

    {0xB1, 0x06, 0x10},
    {0xB2, 0x01, 0x10},
    {0xB1, 0x07, 0x10},
    {0xB2, 0x68, 0x10},

    {0xB1, 0x08, 0x10},
    {0xB2, 0x04, 0x10},
    {0xB1, 0x09, 0x10},
    {0xB2, 0x38, 0x10},

    {0xB1, 0x0A, 0x10},
    {0xB2, 0x04, 0x10},
    {0xB1, 0x0B, 0x10},
    {0xB2, 0xB0, 0x10},

    {0xB1, 0x0C, 0x10},
    {0xB2, 0x0C, 0x10},
    {0xB1, 0x0D, 0x10},
    {0xB2, 0x67, 0x10},

    {0xB1, 0x0E, 0x10},
    {0xB2, 0x21, 0x10},
    {0xB1, 0x0F, 0x10},
    {0xB2, 0x0A, 0x10},
#endif
};

BspUtils_Ub960I2cParams gUb960Cfg_IMI[] = {
    {0x01, 0x01, 0xFFF},    /* Digital Reset 0 */
    {0x1F, 0x05, 0x4FF},

    /* IMI OV10640 1 */
    {0x4C, 0x01, 0x0},
    {0x58, 0x58, 0x0},
    {0x6D, 0x7D, 0x0},
    {0x5D, 0xBA, 0x0},
    {0x65, ((UInt8) (IMI_PORT_0_SER_ADDR << 1U)), 0x0},
    {0x5E, 0x62,0},
    {0x66, ((UInt8) (IMI_PORT_0_SENSOR_ADDR << 1U)), 0x0},
    {0x7C, 0x00, 0x0},
    {0x6E, 0x99, 0x0},
    {0x70, 0x2B, 0x0},
    {0x71, 0x2C, 0x0},


    /* IMI OV10640 2 */
    {0x4C, 0x12, 0x0},
    {0x58, 0x58, 0x0},
    {0x6D, 0x7D, 0x0},
    {0x5D, 0xBA ,0x0},
    {0x65, ((UInt8) (IMI_PORT_1_SER_ADDR << 1U)), 0x0},
    {0x5E,0x62,0},
    {0x66, ((UInt8) (IMI_PORT_1_SENSOR_ADDR << 1U)), 0x0},
    {0x7C, 0x00, 0x0},
    {0x6E, 0x99, 0x0},
    {0x70, 0x6B, 0x0},
    {0x71, 0x6C, 0x0},


    /* IMI OV10640 3 */
    {0x4C, 0x24, 0x0},
    {0x58, 0x58, 0x0},
    {0x6D, 0x7D, 0x0},
    {0x5D, 0xBA, 0x0},
    {0x65, ((UInt8) (IMI_PORT_2_SER_ADDR << 1U)), 0x0},
    {0x5E, 0x62, 0x0},
    {0x66, ((UInt8) (IMI_PORT_2_SENSOR_ADDR << 1U)), 0x0},
    {0x7C, 0x00, 0x0},
    {0x6E, 0x99, 0x0},
    {0x70, 0xAB, 0x0},
    {0x71, 0xAC, 0x0},


    /* IMI OV10640 4 */
    {0x4C, 0x38, 0x0},
    {0x58, 0x58, 0x0},
    {0x6D, 0x7D, 0x0},
    {0x5D, 0xBA ,0x0},
    {0x65, ((UInt8) (IMI_PORT_3_SER_ADDR << 1U)), 0x0},
    {0x5E, 0x62, 0x0},
    {0x66, ((UInt8) (IMI_PORT_3_SENSOR_ADDR << 1U)), 0x0},
    {0x7C, 0x00, 0x0},
    {0x6E, 0x99, 0x0},
    {0x70, 0xEB, 0x0},
    {0x71, 0xEC, 0x0},

    {0xB0, 0x1C, 0xFFF},
    {0xB1, 0x13, 0xFFF},
    {0xB2, 0x1F, 0xFFF},

    {0x32, 0x01, 0x0},
#ifdef BOARD_TYPE_TDA3XX_RVP
    {0x33, 0x03, 0x0},  /* Enable CSI2 continous clock */
#else
    {0x33, 0x01, 0x0},
#endif
    {0x20, 0x00, 0x0},

    {0x10, 0x81, 0x0},
    {0x11, 0xa1, 0x0},
    {0x12, 0xc1, 0x0},
};

BspUtils_Ub960I2cParams gUb960Cfg_updateSlaveAddr[] = {

    /* camera 1 */
    {0x4C, 0x01, 0xFFF},
    {0x65, ((UInt8)(TIDA00262_PORT_0_SER_ADDR << 1U)), 0x0},
    {0x66, ((UInt8)(TIDA00262_PORT_0_SENSOR_ADDR << 1U)), 0x0},

    /* camera 2 */
    {0x4C, 0x12, 0xFFF},
    {0x65, ((UInt8)(TIDA00262_PORT_1_SER_ADDR << 1U)), 0x0},
    {0x66, ((UInt8)(TIDA00262_PORT_1_SENSOR_ADDR << 1U)), 0x0},

    /* camera 3 */
    {0x4C, 0x24, 0xFFF},
    {0x65, ((UInt8)(TIDA00262_PORT_2_SER_ADDR << 1U)), 0x0},
    {0x66, ((UInt8)(TIDA00262_PORT_2_SENSOR_ADDR << 1U)), 0x0},

    /* camera 4 */
    {0x4C, 0x38, 0xFFF},
    {0x65, ((UInt8)(TIDA00262_PORT_3_SER_ADDR << 1U)), 0x0},
    {0x66, ((UInt8)(TIDA00262_PORT_3_SENSOR_ADDR << 1U)), 0x0},
};

BspUtils_Ub960I2cParams gUb960ResetCfg[] = {
    {0x01, 0x2, 0x0}
};

BspUtils_Ub960I2cParams gUb960ResetCfg_SAT0088_OV10635[] = {
    /* Port 0 */
    {0x4C, 0x01, 0x0},
    {0x58, 0x58, 0x0},
    {0x6e, 0x99, 0xFF},  /*0x99: GPIO0=1 GPIO1 = 1. 0x98 = GPIO0=0 GPIO1 = 1 */

    /* Port 1 */
    {0x4C, 0x12, 0x0},
    {0x58, 0x58, 0x0},
    {0x6e, 0x99, 0xFF},  /*Power down sensor */

    /* Port 2 */
    {0x4C, 0x24, 0x0},
    {0x58, 0x58, 0x0},
    {0x6e, 0x99, 0xFF},  /*Power down sensor */

    /* Port 3 */
    {0x4C, 0x38, 0x0},
    {0x58, 0x58, 0x0},
    {0x6e, 0x99, 0xFF},  /*Power down sensor */

    {0x01, 0x2, 0x0}
};

BspUtils_Ub960I2cParams gUb960Cfg_SAT0088_OV10635[] = {
    {0x01, 0x01, 0xFFF},    /* Digital Reset 0 */
    {0x1F, 0x00, 0x4FF},    /* UB960 = 0x5 and UB964 = 0x00, 800 MHz DDR */
    {0x1D, 0xFF, 0x4FF},    /* Frame Count limit high byte limit to 0xFF */
    {0x1E, 0xFF, 0x4FF},    /* Frame Count limit low byte limit to 0xFF */

    /* Port 0 */
    {0x4C, 0x01, 0x0},
    {0x58, 0x58, 0x0},
    {0x5D, ((UInt8) (SAT0088_OV10635_SER_ADDR << 1U)), 0x0},
    {0x65, ((UInt8) (SAT0088_OV10635_PORT_0_SER_ALIAS_ADDR << 1U)), 0x0},
    {0x5E, ((UInt8) (SAT0088_OV10635_SENSOR_ADDR << 1U)), 0x0},
    {0x66, ((UInt8) (SAT0088_OV10635_PORT_0_SENSOR_ALIAS_ADDR << 1U)), 0x0},
    {0x7C, 0x81, 0x0},  /* SAT0088+OV10635,frame-valid polarity inversion &
                            process 8 MS bits only */
    {0x6e, 0x98, 0x0},  /*0x99: GPIO0=1 GPIO1 = 1. 0x98 = GPIO0=0 GPIO1 = 1 */
    {0x70, 0x1E, 0x0},  /* VPS_ISS_CAL_CSI2_YUV422_8B */
    {0x71, 0x2C, 0x0},
    {0x6D, 0x7F, 0x0}, /* 0x7E RAW 12, 0x7F RAW 10 */

    /* Port 1 */
    {0x4C, 0x12, 0x0},
    {0x58, 0x58, 0x0},
    {0x5D, ((UInt8) (SAT0088_OV10635_SER_ADDR << 1U)), 0x0},
    {0x65, ((UInt8) (SAT0088_OV10635_PORT_1_SER_ALIAS_ADDR << 1U)), 0x0},
    {0x5E, ((UInt8) (SAT0088_OV10635_SENSOR_ADDR << 1U)), 0x0},
    {0x66, ((UInt8) (SAT0088_OV10635_PORT_1_SENSOR_ALIAS_ADDR << 1U)), 0x0},
    {0x7C, 0x81, 0x0},
    {0x6e, 0x98, 0x0},
    {0x70, 0x5E, 0x0},  /* VPS_ISS_CAL_CSI2_YUV422_8B */
    {0x71, 0x6C, 0x0},
    {0x6D, 0x7F, 0x0}, /* 0x7E RAW 12, 0x7F RAW 10 */

    /* Port 2 */
    {0x4C, 0x24, 0x0},
    {0x58, 0x58, 0x0},
    {0x5D, ((UInt8) (SAT0088_OV10635_SER_ADDR << 1U)), 0x0},
    {0x65, ((UInt8) (SAT0088_OV10635_PORT_2_SER_ALIAS_ADDR << 1U)), 0x0},
    {0x5E, ((UInt8) (SAT0088_OV10635_SENSOR_ADDR << 1U)), 0x0},
    {0x66, ((UInt8) (SAT0088_OV10635_PORT_2_SENSOR_ALIAS_ADDR << 1U)), 0x0},
    {0x7C, 0x81, 0x0},
    {0x6e, 0x98, 0x0},
    {0x70, 0x9E, 0x0},  /* VPS_ISS_CAL_CSI2_YUV422_8B */
    {0x71, 0xAC, 0x0},
    {0x6D, 0x7F, 0x0}, /* 0x7E RAW 12, 0x7F RAW 10 */

    /* Port 3 */
    {0x4C, 0x38, 0x0},
    {0x58, 0x58, 0x0},
    {0x5D, ((UInt8) (SAT0088_OV10635_SER_ADDR << 1U)), 0x0},
    {0x65, ((UInt8) (SAT0088_OV10635_PORT_3_SER_ALIAS_ADDR << 1U)), 0x0},
    {0x5E, ((UInt8) (SAT0088_OV10635_SENSOR_ADDR << 1U)), 0x0},
    {0x66, ((UInt8) (SAT0088_OV10635_PORT_3_SENSOR_ALIAS_ADDR << 1U)), 0x0},
    {0x7C, 0x81, 0x0},
    {0x6e, 0x98, 0x0},
    {0x70, 0xDE, 0x0},  /* VPS_ISS_CAL_CSI2_YUV422_8B */
    {0x71, 0xEC, 0x0},
    {0x6D, 0x7F, 0x0}, /* 0x7E RAW 12, 0x7F RAW 10 */

    {0xB0, 0x1C, 0xFFF},
    {0xB1, 0x13, 0xFFF},
    {0xB2, 0x1F, 0xFFF},

    {0x32, 0x01, 0x0},
#ifdef STREAM_ON_2_LANES
    {0x33, 0x21, 0x0},
#else
    {0x33, 0x01, 0x0},
#endif /* STREAM_ON_2_LANES */

    {0x20, 0x00, 0xFFF}
};

BspUtils_Ub960I2cParams gUb960Cfg_D3AR1243[] = {
    /* Reset */
    {0x01, 0x01, 1000},
    /* ENABLE SERIAL LINK DATA INTEGRITY ERROR COUNT */
    {0xB9, 0x18, UB960_REG_DELAY_TIME},
    /* ENABLE SFILTER with AEQ ADAPTION */
    {0x42, 0x71, UB960_REG_DELAY_TIME},

    /* RX0 */
    {0x4c, 0x01, 1000},    /* Port 0 */
    {0x58, UB960_FREQ_SEL, UB960_REG_DELAY_TIME},  /* Enable Back channel, set to 50Mbs */
    {0xD5, 0xC0, UB960_REG_DELAY_TIME},  /* Set AEQ MIN/MAX widest values */

    {0x5D, 0x30, UB960_REG_DELAY_TIME}, /*Serializer I2C Address*/
    {0x65, (D3_AR1243_PORT_0_SER_ADDR << 1U), UB960_REG_DELAY_TIME}, /*Serializer alias address*/
    {0x5E, 0x50, UB960_REG_DELAY_TIME}, /*I2C-SPI bridge I2C Address*/
    {0x66, (D3_AR1243_PORT_0_SENSOR_ADDR << 1U), UB960_REG_DELAY_TIME}, /*Bridge alias address (Used to be 0x7c)*/
    {0x5F, 0xE8, UB960_REG_DELAY_TIME}, /*GPIO expander I2C Address*/
    {0x67, (D3RIB_PORT_0_IOEXP_ADDR << 1U), UB960_REG_DELAY_TIME}, /*GPIO expander alias address*/

    {0x32, 0x01, UB960_REG_DELAY_TIME}, /*Enable TX port 0*/
    {0x33, 0x03, UB960_REG_DELAY_TIME}, /*Enable Continuous clock mode and CSI output*/

    {0xBC, 0x00, UB960_REG_DELAY_TIME}, /*Unknown*/
    {0x6D, 0x6C, UB960_REG_DELAY_TIME}, /*CSI Mode*/
    {0x05, 0x00, UB960_REG_DELAY_TIME}, /*CSI Mode*/
    {0x06, 0x01, UB960_REG_DELAY_TIME}, /*CSI Mode*/
    {0x72, 0x00, UB960_REG_DELAY_TIME}, /*VC Map - All to 0*/
    {0x7C, 0x00, UB960_REG_DELAY_TIME}, /*Line Valid active high, Frame Valid active high*/
    {0xD5, 0xF3, UB960_REG_DELAY_TIME}, /*Auto Attenuation*/

    /* RX1 */
    {0x4c, 0x12, 100},    /* Port 1 */
    {0x58, UB960_FREQ_SEL, UB960_REG_DELAY_TIME},  /* Enable Back channel, set to 50Mbs */
    {0xD5, 0xC0, UB960_REG_DELAY_TIME},  /* Set AEQ MIN/MAX widest values */

    {0x5D, 0x30, UB960_REG_DELAY_TIME}, /*Serializer I2C Address*/
    {0x65, (D3_AR1243_PORT_1_SER_ADDR << 1U), UB960_REG_DELAY_TIME}, /*Serializer alias address*/
    {0x5E, 0x50, UB960_REG_DELAY_TIME}, /*I2C-SPI bridge I2C Address*/
    {0x66, (D3_AR1243_PORT_1_SENSOR_ADDR << 1U), UB960_REG_DELAY_TIME}, /*Bridge alias address*/
    {0x5F, 0xE8, UB960_REG_DELAY_TIME}, /*GPIO expander I2C Address*/
    {0x67, (D3RIB_PORT_1_IOEXP_ADDR << 1U), UB960_REG_DELAY_TIME}, /*GPIO expander alias address*/

    {0x32, 0x01, UB960_REG_DELAY_TIME}, /*Enable TX port 0*/
    {0x33, 0x03, UB960_REG_DELAY_TIME}, /*Enable Continuous clock mode and CSI output*/

    {0xBC, 0x00, UB960_REG_DELAY_TIME}, /*Unknown*/
    {0x6D, 0x6C, UB960_REG_DELAY_TIME}, /*CSI Mode*/
    {0x05, 0x00, UB960_REG_DELAY_TIME}, /*CSI Mode*/
    {0x06, 0x01, UB960_REG_DELAY_TIME}, /*CSI Mode*/
    {0x72, 0x55, UB960_REG_DELAY_TIME}, /*VC Map - All to 0*/
    {0x7C, 0x00, UB960_REG_DELAY_TIME}, /*Line Valid active high, Frame Valid active high*/
    {0xD5, 0xF3, UB960_REG_DELAY_TIME}, /*Auto Attenuation*/

    /* RX2 */
    {0x4c, 0x24, 100},    /* Port 2 */
    {0x58, UB960_FREQ_SEL, UB960_REG_DELAY_TIME},  /* Enable Back channel, set to 50Mbs */
    {0xD5, 0xC0, UB960_REG_DELAY_TIME},  /* Set AEQ MIN/MAX widest values */

    {0x5D, 0x30, UB960_REG_DELAY_TIME}, /*Serializer I2C Address*/
    {0x65, (D3_AR1243_PORT_2_SER_ADDR << 1U), UB960_REG_DELAY_TIME}, /*Serializer alias address*/
    {0x5E, 0x50, UB960_REG_DELAY_TIME}, /*I2C-SPI bridge I2C Address*/
    {0x66, (D3_AR1243_PORT_2_SENSOR_ADDR << 1U), UB960_REG_DELAY_TIME}, /*Bridge alias address*/
    {0x5F, 0xE8, UB960_REG_DELAY_TIME}, /*GPIO expander I2C Address*/
    {0x67, (D3RIB_PORT_2_IOEXP_ADDR << 1U), UB960_REG_DELAY_TIME}, /*GPIO expander alias address*/

    {0x32, 0x01, UB960_REG_DELAY_TIME}, /*Enable TX port 0*/
    {0x33, 0x03, UB960_REG_DELAY_TIME}, /*Enable Continuous clock mode and CSI output*/

    {0xBC, 0x00, UB960_REG_DELAY_TIME}, /*Unknown*/
    {0x6D, 0x6C, UB960_REG_DELAY_TIME}, /*CSI Mode*/
    {0x05, 0x00, UB960_REG_DELAY_TIME}, /*CSI Mode*/
    {0x06, 0x01, UB960_REG_DELAY_TIME}, /*CSI Mode*/
    {0x72, 0xAA, UB960_REG_DELAY_TIME}, /*VC Map - All to 0*/
    {0x7C, 0x00, UB960_REG_DELAY_TIME}, /*Line Valid active high, Frame Valid active high*/
    {0xD5, 0xF3, UB960_REG_DELAY_TIME}, /*Auto Attenuation*/

    /* RX3 */
    {0x4c, 0x38, 100},    /* Port 3 */
    {0x58, UB960_FREQ_SEL, UB960_REG_DELAY_TIME},  /* Enable Back channel, set to 50Mbs */
    {0xD5, 0xC0, UB960_REG_DELAY_TIME},  /* Set AEQ MIN/MAX widest values */

    {0x5D, 0x30, UB960_REG_DELAY_TIME}, /*Serializer I2C Address*/
    {0x65, (D3_AR1243_PORT_3_SER_ADDR << 1U), UB960_REG_DELAY_TIME}, /*Serializer alias address*/
    {0x5E, 0x50, UB960_REG_DELAY_TIME}, /*I2C-SPI bridge I2C Address*/
    {0x66, (D3_AR1243_PORT_3_SENSOR_ADDR << 1U), UB960_REG_DELAY_TIME}, /*Bridge alias address*/
    {0x5F, 0xE8, UB960_REG_DELAY_TIME}, /*GPIO expander I2C Address*/
    {0x67, (D3RIB_PORT_3_IOEXP_ADDR << 1U), UB960_REG_DELAY_TIME}, /*GPIO expander alias address*/

    {0x32, 0x01, UB960_REG_DELAY_TIME}, /*Enable TX port 0*/
    {0x33, 0x03, UB960_REG_DELAY_TIME}, /*Enable Continuous clock mode and CSI output*/

    {0xBC, 0x00, UB960_REG_DELAY_TIME}, /*Unknown*/
    {0x6D, 0x6C, UB960_REG_DELAY_TIME}, /*CSI Mode*/
    {0x05, 0x00, UB960_REG_DELAY_TIME}, /*CSI Mode*/
    {0x06, 0x01, UB960_REG_DELAY_TIME}, /*CSI Mode*/
    {0x72, 0xFF, UB960_REG_DELAY_TIME}, /*VC Map - All to 0*/
    {0x7C, 0x00, UB960_REG_DELAY_TIME}, /*Line Valid active high, Frame Valid active high*/
    {0xD5, 0xF3, UB960_REG_DELAY_TIME}, /*Auto Attenuation*/

    {0x0D, 0x90, UB960_REG_DELAY_TIME}, /*I/O to 3V3 - Options not valid with datasheet*/
    {0x0C, 0x0F, UB960_REG_DELAY_TIME}, /*Enable All ports*/
    {0x20, 0x00, UB960_REG_DELAY_TIME}, /*Forwarding and using CSIport 0*/

    /*Sets GPIOS*/
    {0x0F, 0xF0, UB960_REG_DELAY_TIME}, /*Disable GPIO 0 ~ 3 input*/
#ifdef BOARD_TYPE_TDA3XX_RVP
    {0x10, 0x41, UB960_REG_DELAY_TIME}, /*GPIO 0 - Output received GPIO 2 (HST_INT) from Port 0*/
    {0x11, 0x45, UB960_REG_DELAY_TIME}, /*GPIO 1 - Output received GPIO 2 (HST_INT) from Port 1*/
    {0x12, 0x49, UB960_REG_DELAY_TIME}, /*GPIO 2 - Output received GPIO 2 (HST_INT) from Port 2*/
    {0x13, 0x4D, UB960_REG_DELAY_TIME}, /*GPIO 3 - Output received GPIO 2 (HST_INT) from Port 3*/
#else
    {0x14, 0x41, UB960_REG_DELAY_TIME}, /*GPIO 4 - Output received GPIO 2 (HST_INT) from Port 0*/
#endif
    {0x59, 0x83, UB960_REG_DELAY_TIME}, /* Enable 4 GPIOs */
    {0x21, 0x01, UB960_REG_DELAY_TIME}, /* for Round Robin/Best Effort Forwarding */
    {0x20, 0x00, UB960_REG_DELAY_TIME}, /* forwarding RX Port0~3 to CSI2 Port0 */
};

BspUtils_Ub960I2cParams gUB953SerCfg[] = {
    {0x01, 0x01, 1000},
    {0x0E, 0x04, 10},
    {0x0D, 0x00, 10},
    {0x33, 0x07, 10},
};
BspUtils_Ub960I2cParams gUB913SerCfg[] = {
    {0x03, 0xC5, 0x0},
    {0x0D, 0x99, 0x0},

    /* Changing the default I2C clock rate to 100 KHz */
    /* Default  0x82 = 74 kbits/sec
                0x64 = 100 kbps
                0x32 = 400 kbps */
    {0x11, 0x32, 0x0},  /* SCL High period */
    {0x12, 0x32, 0x0}   /* SCL Low period */
};

BspUtils_Ub960I2cParams gUB913SerResetCfg[] = {
    {0x0D, 0x11, 0x0}
};

BspUtils_Ub960I2cParams gUb913SerCfg_SAT0088_OV10635[] = {
    {0x03, 0xC5, 0x0},
    {0x0D, 0x55, 0x0},

    /* Changing the default I2C clock rate to 100 KHz */
    /* Default  0x82 = 74 kbits/sec
                0x64 = 100 kbps
                0x32 = 400 kbps */
    {0x11, 0x32, 0x0},      /* SCL High period */
    {0x12, 0x32, 0xFFFF}    /* SCL Low period */
};

BspUtils_Ub960I2cParams gUB913SerResetCfg_SAT0088_OV10635[] = {
    {0x0D, 0x11, 0xFFFF},   /* Power down sensor */
    /*{0x01, 0x02, 0x0},       Reset 913 */
};

BspUtils_Ub960I2cParams g964AlphaInitCfg[] = {
    {0xB0, 0x1C, 0xFFF},
    {0xB1, 0x16, 0xFFF},
    {0xB2, 0x00, 0xFFF},
    {0xB1, 0x17, 0xFFF},
    {0xB2, 0x00, 0xFFF},
    {0xB1, 0x18, 0xFFF},
    {0xB2, 0x00, 0xFFF},
    {0xB1, 0x19, 0xFFF},
    {0xB2, 0x00, 0xFFF},
    {0xB0, 0x1C, 0xFFF},     /* digital share debug registers */
    {0xB1, 0x15, 0xFFF},
    {0xB2, 0x0A, 0xFFF},
    {0xB2, 0x00, 0xFFF},
    {0x1F, 0x02, 0x4FF},
    {0xB0, 0x1C, 0xFFF},
    {0xB1, 0x13, 0xFFF},
    {0xB2, 0x1F, 0xFFF},
    {0xB0, 0x14, 0xFFF},
    {0xB1, 0x04, 0xFFF},
    {0xB2, 0x04, 0xFFF},
    {0xB0, 0x18, 0xFFF},
    {0xB1, 0x14, 0xFFF},
    {0xB2, 0x1f, 0xFFF},
    {0xB0, 0x18, 0xFFF},
    {0xB1, 0x13, 0xFFF},
    {0xB2, 0x25, 0xFFF},
    {0xB0, 0x1C, 0xFFF},
    {0xB1, 0x1D, 0xFFF},
    {0xB2, 0x40, 0xFFF},
    {0xB0, 0x1C, 0xFFF},
    {0xB1, 0x1A, 0xFFF},
    {0xB2, 0x99, 0xFFF},
};

BspUtils_Ub960I2cParams g960AlphaInitCfg[] = {
    {0x1F, 0x05, 0x4FF},
    {0xB0, 0x1C, 0xFFF},
    {0xB1, 0x13, 0xFFF},
    {0xB2, 0x1F, 0xFFF},
};

BspUtils_Ub960SourceI2cAddr gSlaveAliases[] =  { {0x3D, 0U, {0U, 0U, 0U, 0U}, \
                                                       {0U, 0U, 0U, 0U}},
                                                  {0x36, 0U, {0U, 0U, 0U, 0U}, \
                                                       {0U, 0U, 0U, 0U}},
                                               };

BspUtils_Ub960DebugRegData gUB96xdebugStatus;
/* ========================================================================== */
/*                          Function Implementation                           */
/* ========================================================================== */
Int32 BspUtils_appInitUb960(UInt32 instId,
                            UInt32 sensorDrvId,
                            const BspUtils_Ub960SourceI2cAddr *pSlaveAddr,
                            BspUtils_Ub960Status *pStatus)
{
    Int32   retVal = BSP_EBADARGS;
    UInt32  nIdx, numRegs, numSerRegs, initSerializer = TRUE;
    UInt32  i2cInst, serAddr, sensorAddr, waitAfterPowerOn = 0U, waitAfter960Init = 0U;
    volatile UInt32 count;
    BspUtils_Ub960I2cParams *pUb960I2cPrm;
    BspUtils_Ub960I2cParams *pSerI2cPrm;
    Uint8 ub96xVer;
    BspUtils_BackChFreqSelect freq = BSPUTILS_BACKCHFREQSELECT_50MHZ;


    if ((NULL != pStatus) && (NULL != pSlaveAddr) && instId < BSPUTILS_UB960_MAX_INSTANCE)
    {
        retVal = BSP_SOK;
        gSlaveAliases[instId].slaveAddr = pSlaveAddr->slaveAddr;
        gSlaveAliases[instId].numSource = pSlaveAddr->numSource;
    }

    switch (sensorDrvId)
    {
        case FVID2_VID_SENSOR_IMI_OV10640_DRV:
            pUb960I2cPrm = gUb960Cfg_IMI;
            numRegs = sizeof (gUb960Cfg_IMI)/sizeof (gUb960Cfg_IMI[0U]);
            pSerI2cPrm = gUB913SerCfg;
            numSerRegs = sizeof (gUB913SerCfg)/sizeof (gUB913SerCfg[0U]);
            initSerializer = TRUE;
            waitAfterPowerOn = 0U;
            break;
        case FVID2_VID_SENSOR_TIDA00262_APT_AR0140_DRV:
            pUb960I2cPrm = gUb960Cfg_TIDA;
            numRegs = sizeof (gUb960Cfg_TIDA)/sizeof (gUb960Cfg_TIDA[0U]);
            pSerI2cPrm = gUB913SerCfg;
            numSerRegs = sizeof (gUB913SerCfg)/sizeof (gUB913SerCfg[0U]);
            initSerializer = TRUE;
            waitAfterPowerOn = 0U;
            break;
        case FVID2_VID_SENSOR_OV2775_TIDA1130_DRV:
            pUb960I2cPrm = gUb960Cfg_TIDA1130;
            numRegs = sizeof (gUb960Cfg_TIDA1130)/sizeof (gUb960Cfg_TIDA1130[0U]);
            pSerI2cPrm = gUB953SerCfg_TIDA1130;
            numSerRegs = sizeof (gUB953SerCfg_TIDA1130)/
                sizeof (gUB953SerCfg_TIDA1130[0U]);
            initSerializer = TRUE;
            waitAfterPowerOn = 0U;
            break;
        case FVID2_VID_SENSOR_MULDES_OV1063X_DRV:
            pUb960I2cPrm = gUb960Cfg_SAT0088_OV10635;
            numRegs = sizeof (gUb960Cfg_SAT0088_OV10635)/
                                        sizeof (gUb960Cfg_SAT0088_OV10635[0U]);
            pSerI2cPrm = &gUb913SerCfg_SAT0088_OV10635[0U];
            numSerRegs = sizeof (gUb913SerCfg_SAT0088_OV10635) /
                             sizeof (gUb913SerCfg_SAT0088_OV10635[0U]);
/* C & C++ INVARIANT_CONDITION.GEN
 * Expression 'if (BSPUTILS_UB964_VERSION_ID != ub96xVer)' used in the condition
 * always yields the same result.
 * Name if (BSPUTILS_UB964_VERSION_ID != ub96xVer)
 * KW State: Ignore -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * In cases where value in the if condition  is dependent on the return of a
 * function and currently the function is hardcoded to return a value. Code is
 * currently unreachable but as the implementation of the function changes, it
 * will not be unreachable.
 */
            ub96xVer = BspUtils_appGetUb96xVersion(0U);
            if (BSPUTILS_UB964_VERSION_ID != ub96xVer)
            {
                GT_assert(BspAppTrace,
                            (0x1F == gUb960Cfg_SAT0088_OV10635[1U].nRegAddr));

                if (0x1F == gUb960Cfg_SAT0088_OV10635[1U].nRegAddr)
                {
                    gUb960Cfg_SAT0088_OV10635[1U].nRegValue = 0x05U;
                }
            }
            {
                if (BSP_PLATFORM_SOC_ID_TDA2EX == Bsp_platformGetSocId())
                {
                    if (BSP_PLATFORM_PACKAGE_TYPE_17x17 ==
                        Bsp_platformGetPackageType())
                    {
                        for (nIdx = 0U; nIdx < numRegs; nIdx++)
                        {
                            if (0x33 == gUb960Cfg_SAT0088_OV10635[nIdx].nRegAddr)
                            {
                                gUb960Cfg_SAT0088_OV10635[nIdx].nRegValue = 0x21;
                                GT_0trace(BspAppTrace, GT_INFO,
                                            "Updated UB964 to 2 Lanes !!!\r\n");
                                break;
                            }
                        }
                    }
                }
            }


            break;
       case FVID2_VID_SENSOR_AR1243_2G_DRV:
       case FVID2_VID_SENSOR_AR1243_4G_DRV:
       case FVID2_VID_SENSOR_FUSION_DRV:
            GT_0trace(BspAppTrace, GT_INFO,"Using AR12xx\n");
            pUb960I2cPrm = gUb960Cfg_D3AR1243;
            numRegs = sizeof (gUb960Cfg_D3AR1243)/sizeof (gUb960Cfg_D3AR1243[0U]);
            pSerI2cPrm = gUB953SerCfg;
            numSerRegs = sizeof (gUB953SerCfg)/sizeof (gUB953SerCfg[0U]);
            initSerializer = TRUE;
            waitAfterPowerOn = 500U;
            waitAfter960Init = 1000U;
            if (FVID2_VID_SENSOR_AR1243_2G_DRV == sensorDrvId)
            {
                freq = BSPUTILS_BACKCHFREQSELECT_25MHZ;
            }
            else if (FVID2_VID_SENSOR_AR1243_4G_DRV == sensorDrvId)
            {
                freq = BSPUTILS_BACKCHFREQSELECT_50MHZ;
            }
            else
            {
                freq = BSPUTILS_BACKCHFREQSELECT_25MHZ;
            }
            break;
        case FVID2_VID_SENSOR_MARS_APT_AR0143_DRV:
            GT_0trace(BspAppTrace, GT_ERR,"MARS module\n");
            pUb960I2cPrm = gUb960Cfg_MARS_AR0143;
            numRegs = sizeof (gUb960Cfg_MARS_AR0143)/sizeof (gUb960Cfg_MARS_AR0143[0U]);
            pSerI2cPrm = gUB913SerCfg;
            numSerRegs = sizeof (gUB913SerCfg)/sizeof (gUB913SerCfg[0U]);
            initSerializer = TRUE;
            waitAfterPowerOn = 500U;
            waitAfter960Init = 500;
            break;
        case FVID2_VID_SENSOR_D3_SONY_IMX390_DRV:
            GT_0trace(BspAppTrace, GT_ERR,"D3 IMX390 module\n");
            pUb960I2cPrm = gUB960SerCfg_D3IMX390;
            numRegs = sizeof (gUB960SerCfg_D3IMX390)/
                sizeof (gUB960SerCfg_D3IMX390[0U]);
            pSerI2cPrm = gUB953SerCfg_D3IMX390;
            numSerRegs = sizeof (gUB953SerCfg_D3IMX390)/
                sizeof (gUB953SerCfg_D3IMX390[0U]);
            initSerializer = TRUE;
            waitAfterPowerOn = 2000U;
            waitAfter960Init = 2000U;
            break;
        default:
            pUb960I2cPrm = gUb960Cfg_IMI;
            numRegs = sizeof (gUb960Cfg_IMI)/sizeof (gUb960Cfg_IMI[0U]);
            pSerI2cPrm = gUB913SerCfg;
            numSerRegs = sizeof (gUB913SerCfg)/sizeof (gUB913SerCfg[0U]);
            initSerializer = TRUE;
            waitAfterPowerOn = 0U;
            break;
    }

#ifndef BOARD_TYPE_TDA3XX_RVP
    /* UB96X on RVP is not yet powered ON hence avoiding below I2C read */
    ub96xVer = BspUtils_appGetUb96xVersion(0U);
    if ((BSPUTILS_UB964_VERSION_ID == ub96xVer) &&
        (FVID2_VID_SENSOR_OV2775_TIDA1130_DRV != sensorDrvId)&&
        (FVID2_VID_SENSOR_OV2775_CSI2_DRV != sensorDrvId) &&
        (FVID2_VID_SENSOR_D3_SONY_IMX390_DRV != sensorDrvId))
    {
        for (nIdx = 0U; nIdx < numRegs; nIdx++)
        {
            if (0x1F == (pUb960I2cPrm + nIdx)->nRegAddr)
            {
                (pUb960I2cPrm + nIdx)->nRegValue = 0x00;
                GT_0trace(BspAppTrace, GT_INFO,
                            "Switching to 800MHz Mode !!!\r\n");
                break;
            }
        }
    }
#endif

    if (BSP_SOK == retVal)
    {
        for (nIdx = 0U; nIdx < BSPUTILS_UB960EVM_MAX_PORTS; nIdx++)
        {
            gSlaveAliases[instId].rSlave1Addr[nIdx] = pSlaveAddr->rSlave1Addr[nIdx];
            gSlaveAliases[instId].rSlave2Addr[nIdx] = pSlaveAddr->rSlave2Addr[nIdx];
        }

        if (sensorDrvId != FVID2_VID_SENSOR_FUSION_DRV)
        {
            /*
             *  select FPD output power
             */
            retVal = setCameraPower(BSPUTILS_FPDCAMPOWERLEVEL_12V0);
            /* Some sensors need time to boot once they are powered on */
            if (0U != waitAfterPowerOn)
            {
                BspOsal_sleep(waitAfterPowerOn);
            }
            if(BSP_SOK == retVal)
            {
                /*
                 *  Init deserializer
                 */
                retVal = initDeserializer(instId);
                if(BSP_SOK == retVal)
                {
                    count = 0U;
                    for (nIdx = 0U;nIdx < numRegs;nIdx++)
                    {

                        if (0x65 == (pUb960I2cPrm + nIdx)->nRegAddr)
                        {
                            (pUb960I2cPrm + nIdx)->nRegValue =
                                    (gSlaveAliases[instId].rSlave1Addr[count] << 1U);
                        }
                        if (0x66 == (pUb960I2cPrm + nIdx)->nRegAddr)
                        {
                            (pUb960I2cPrm + nIdx)->nRegValue =
                                    (gSlaveAliases[instId].rSlave2Addr[count] << 1U);
                            count++;
                        }

                        GT_assert(BspAppTrace, \
                                            (BSPUTILS_UB960EVM_MAX_PORTS >= count));

                        /* Update Back Channel Frequency selection based on Sensor ID */
                        if ((FVID2_VID_SENSOR_AR1243_2G_DRV == sensorDrvId) ||
                                (FVID2_VID_SENSOR_AR1243_4G_DRV == sensorDrvId))
                        {
                            if (0x58 == (pUb960I2cPrm + nIdx)->nRegAddr)
                            {
                                (pUb960I2cPrm + nIdx)->nRegValue = 0x58 | freq;
                            }
                        }
                    }

                    for (nIdx = 0U;nIdx < numRegs;nIdx++)
                    {
                        retVal = Bsp_deviceWrite8(
                            UB960_ACCESSIBLE_FROM_I2C_INST,
                            gSlaveAliases[instId].slaveAddr,
                            &((pUb960I2cPrm + nIdx)->nRegAddr),
                            &((pUb960I2cPrm + nIdx)->nRegValue),
                            (UInt32) 1U);
                        if (retVal != BSP_SOK)
                        {
                            GT_0trace(BspAppTrace, GT_ERR,
                                      "Could not configure UB960 !!!\r\n");
                            break;
                        }

                        if (0 != (pUb960I2cPrm + nIdx)->nDelay)
                        {
                            count = (pUb960I2cPrm + nIdx)->nDelay;
                            if ((FVID2_VID_SENSOR_AR1243_2G_DRV != sensorDrvId) ||
                                    (FVID2_VID_SENSOR_AR1243_4G_DRV != sensorDrvId) ||
                                    (FVID2_VID_SENSOR_D3_SONY_IMX390_DRV == sensorDrvId) ||
                                    (FVID2_VID_SENSOR_MARS_APT_AR0143_DRV != sensorDrvId))
                            {
                                while (count)
                                {
                                    count--;
                                }
                            }
                            else
                            {
                                BspOsal_sleep(count);
                            }
                        }
                    }
                }
            }
        }
    }

    if ((FVID2_VID_SENSOR_AR1243_2G_DRV == sensorDrvId) ||
            (FVID2_VID_SENSOR_AR1243_4G_DRV == sensorDrvId) ||
            (FVID2_VID_SENSOR_FUSION_DRV == sensorDrvId))
    {
        /*
         * If Radar data is transmitted from UB960 before TDA3x CAL_A is initialized,
         * CAL_A sometimes does not initialize properly and fails to capture data.
         * Disable CSI output of the 960 here and then call BspUtils_enableUb960CsiOutput
         * after the CSI port on TDA3x has been initialized.
         */
        BspUtils_disableUb960CsiOutput();
    }

    if (0U != waitAfter960Init)
    {
        BspOsal_sleep(waitAfter960Init);
    }

    /* Figure out which modules are connected */
    if ((BSP_SOK == retVal) &&
        (FVID2_VID_SENSOR_MULDES_OV1063X_DRV != sensorDrvId))
    {
        pStatus->numDetected = 0U;
        i2cInst = UB960_ACCESSIBLE_FROM_I2C_INST;
        Int32   serProbeStatus = BSP_EBADARGS;
        Int32   sensorProbeStatus = BSP_EBADARGS;

        for (nIdx = 0U; nIdx < gSlaveAliases[instId].numSource; nIdx++)
        {
            if ((sensorDrvId != FVID2_VID_SENSOR_FUSION_DRV) ||
                    ((sensorDrvId == FVID2_VID_SENSOR_FUSION_DRV) && (nIdx == D3_AR1243_FUSION_PORT_ID)))
            {
                /*  Init serializer
                */
                if(TRUE == initSerializer)
                {
                      BspUtils_appInitUB913Ser(instId, nIdx, pSerI2cPrm, numSerRegs);
                }

                serAddr = gSlaveAliases[instId].rSlave1Addr[nIdx];
                sensorAddr = gSlaveAliases[instId].rSlave2Addr[nIdx];
                serProbeStatus = Bsp_deviceI2cProbeDevice(i2cInst, (UInt8)serAddr);

                if(BSP_SOK != serProbeStatus)
                {
                    GT_2trace(BspAppTrace, GT_ERR,
                        "Failed to probe serializer at alias: %x | status: %d\n",
                        serAddr, serProbeStatus);
                }

                sensorProbeStatus = Bsp_deviceI2cProbeDevice(i2cInst, (UInt8)sensorAddr);

                if(BSP_SOK != sensorProbeStatus)
                {
                    GT_2trace(BspAppTrace, GT_ERR,
                        "Failed to probe sensor at alias: %x | status: %d\n",
                        sensorAddr, sensorProbeStatus);
                }

                retVal = serProbeStatus | sensorProbeStatus;
                if (BSP_SOK == retVal)
                {
                    pStatus->portNum[nIdx] = nIdx;
                    pStatus->numDetected++;
                }
                else
                {
                    pStatus->portNum[nIdx] =
                                    BSPUTILS_UB960EVM_NO_SOURCE_DETECTED;
                }
            }
        }

        retVal = BSP_SOK;
    }

    if ((BSP_SOK == retVal) &&
        (FVID2_VID_SENSOR_MULDES_OV1063X_DRV == sensorDrvId))
    {
        pStatus->numDetected = 0U;
        i2cInst = UB960_ACCESSIBLE_FROM_I2C_INST;
        for (nIdx = 0U; nIdx < BSPUTILS_UB960EVM_MAX_PORTS; nIdx++)
        {
            pStatus->portNum[nIdx] =
                                BSPUTILS_UB960EVM_NO_SOURCE_DETECTED;

            serAddr = gSlaveAliases[instId].rSlave1Addr[nIdx];
            sensorAddr = gSlaveAliases[instId].rSlave2Addr[nIdx];
            retVal = Bsp_deviceI2cProbeDevice(i2cInst, (UInt8)serAddr);
            if (BSP_SOK == retVal)
            {
                retVal = Bsp_deviceI2cProbeDevice(i2cInst, (UInt8)sensorAddr);
                if (BSP_SOK == retVal)
                {
                    pStatus->portNum[nIdx] = nIdx;
                    pStatus->numDetected++;
                }
                else
                {
                    /* Check for the IMI version */
                    setUb960Gpio0To1(instId, nIdx);
                    retVal = Bsp_deviceI2cProbeDevice(i2cInst,
                                                        (UInt8)sensorAddr);
                    if (BSP_SOK == retVal)
                    {
                        pStatus->portNum[nIdx] = nIdx;
                        pStatus->numDetected++;
                    }
                }
            }
            else
            {
                GT_2trace(BspAppTrace, GT_ERR, "Failed to find 913; nIdx: %d | retVal: %d\n", nIdx, retVal);

                pStatus->portNum[nIdx] =
                                    BSPUTILS_UB960EVM_NO_SOURCE_DETECTED;

            }
        }
        retVal = BSP_SOK;
    }
    if(BSP_SOK == retVal)
    {
        gUB96xdebugStatus.ub96xdebugData[0].regAddr =  BSPUTILS_UB960_DEVICE_STS;
        gUB96xdebugStatus.ub96xdebugData[1].regAddr =  BSPUTILS_UB960_GPIO_STS;
        gUB96xdebugStatus.ub96xdebugData[2].regAddr =  BSPUTILS_UB960_INTERRUPT_STS_ADDR;
        gUB96xdebugStatus.ub96xdebugData[3].regAddr =  BSPUTILS_UB960_TS_STATUS;
        gUB96xdebugStatus.ub96xdebugData[4].regAddr =  BSPUTILS_UB960_CSI_CTL;
        gUB96xdebugStatus.ub96xdebugData[5].regAddr =  BSPUTILS_UB960_CSI_CTL2;
        gUB96xdebugStatus.ub96xdebugData[6].regAddr =  BSPUTILS_UB960_CSI_STS_ADDR;
        gUB96xdebugStatus.ub96xdebugData[7].regAddr =  BSPUTILS_UB960_CSI_TX_ISR;
        gUB96xdebugStatus.ub96xdebugData[8].regAddr =  BSPUTILS_UB960_RX_PORT_STS1;
        gUB96xdebugStatus.ub96xdebugData[9].regAddr =  BSPUTILS_UB960_RX_PORT_STS2;
        gUB96xdebugStatus.ub96xdebugData[10].regAddr = BSPUTILS_UB960_RX_FREQ_HIGH;
        gUB96xdebugStatus.ub96xdebugData[11].regAddr = BSPUTILS_UB960_RX_FREQ_LOW;
        gUB96xdebugStatus.ub96xdebugData[12].regAddr = BSPUTILS_UB960_RX_PAR_ERR_HI;
        gUB96xdebugStatus.ub96xdebugData[13].regAddr = BSPUTILS_UB960_RX_PAR_ERR_LO;
        gUB96xdebugStatus.ub96xdebugData[14].regAddr = BSPUTILS_UB960_BIST_ERR_COUNT;
        gUB96xdebugStatus.ub96xdebugData[15].regAddr = BSPUTILS_UB960_LINE_COUNT_1;
        gUB96xdebugStatus.ub96xdebugData[16].regAddr = BSPUTILS_UB960_LINE_COUNT_0;
        gUB96xdebugStatus.ub96xdebugData[17].regAddr = BSPUTILS_UB960_LINE_LEN_1;
        gUB96xdebugStatus.ub96xdebugData[18].regAddr = BSPUTILS_UB960_LINE_LEN_0;
        gUB96xdebugStatus.ub96xdebugData[19].regAddr = BSPUTILS_UB960_CSI_RX_STS;
        gUB96xdebugStatus.ub96xdebugData[20].regAddr = BSPUTILS_UB960_CSI_ERR_COUNTER;
        gUB96xdebugStatus.ub96xdebugData[21].regAddr = BSPUTILS_UB960_PORT_CONFIG2;
        gUB96xdebugStatus.ub96xdebugData[22].regAddr = BSPUTILS_UB960_MODE_IDX_STS;
        gUB96xdebugStatus.ub96xdebugData[23].regAddr = BSPUTILS_UB960_PORT_ISR_HI;
        gUB96xdebugStatus.ub96xdebugData[24].regAddr = BSPUTILS_UB960_AEQ_STATUS;
        gUB96xdebugStatus.ub96xdebugData[25].regAddr = BSPUTILS_UB960_PORT_ISR_LO;
        gUB96xdebugStatus.ub96xdebugData[26].regAddr = BSPUTILS_UB960_FPD3_RX_ID5;

        gUB96xdebugStatus.numofReg = BSPUTILS_UB960_MAX_NUM_DEBUG_REG;
    }
    return (retVal);
}

Int32 BspUtils_appDeInitUb960(UInt32 instId, UInt32 sensorDrvId)
{
    Int32   retVal = BSP_SOK;
    UInt32  nIdx, nRegs;
    volatile UInt32 count;
    BspUtils_Ub960I2cParams *pUb960I2cPrm;

    if(instId >= BSPUTILS_UB960_MAX_INSTANCE)
    {
        retVal = BSP_EBADARGS;
    }

    pUb960I2cPrm = &gUb960ResetCfg[0U];
    nRegs = sizeof (gUb960ResetCfg) / sizeof (gUb960ResetCfg[0U]);

    if (FVID2_VID_SENSOR_MULDES_OV1063X_DRV == sensorDrvId)
    {
        pUb960I2cPrm = &gUb960ResetCfg_SAT0088_OV10635[0U];
        nRegs = sizeof (gUb960ResetCfg_SAT0088_OV10635) /
                    sizeof (gUb960ResetCfg_SAT0088_OV10635[0U]);
    }

    if(retVal == BSP_SOK)
    {
        for (nIdx = 0U; nIdx < nRegs; nIdx++)
        {
            retVal = Bsp_deviceWrite8(
                UB960_ACCESSIBLE_FROM_I2C_INST,
                gSlaveAliases[instId].slaveAddr,
                &(pUb960I2cPrm[nIdx].nRegAddr),
                &(pUb960I2cPrm[nIdx].nRegValue),
                (UInt32) 1U);
            if (retVal != BSP_SOK)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          "Could not configure UB960 !!!\r\n");
                break;
            }

            if (0 != pUb960I2cPrm[nIdx].nDelay)
            {
                count = pUb960I2cPrm[nIdx].nDelay;
                while (count)
                {
                    count--;
                }
            }
        }
    }

    return (retVal);
}


Int32 BspUtils_appInitUB913Ser(UInt32 instId, UInt32 portId, BspUtils_Ub960I2cParams* i2cPrms,UInt32 numRegs)
{
    Int32   retVal = BSP_SOK;
    UInt32  nIdx;
    UInt32  i2cDevAddr;
    UInt32  count;

    if (BSPUTILS_UB960EVM_MAX_PORTS > portId)
    {
        i2cDevAddr = gSlaveAliases[instId].rSlave1Addr[portId];
    }
    else
    {
        GT_0trace(BspAppTrace, GT_ERR,
                      "Wrong instance of UB913 Ser !!!\r\n");
        retVal = BSP_EFAIL;
    }

    for (nIdx = 0U; ((nIdx < numRegs) && (BSP_SOK == retVal)); nIdx++)
    {
        retVal = Bsp_deviceWrite8(
            UB960_ACCESSIBLE_FROM_I2C_INST,
            i2cDevAddr,
            &(i2cPrms[nIdx].nRegAddr),
            &(i2cPrms[nIdx].nRegValue),
            (UInt32) 1U);
        if (retVal != BSP_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      "Could not configure UB913 Ser !!!\r\n");
            break;
        }

        if (0 != i2cPrms[nIdx].nDelay)
        {
            count = i2cPrms[nIdx].nDelay;
            if ((gUB953SerCfg != i2cPrms) &&
                (gUB953SerCfg_TIDA1130 != i2cPrms) &&
                (gUB953SerCfg_D3IMX390 != i2cPrms))
            {
                while(count)
                {
                    count--;
                }
            }
            else
            {
                BspOsal_sleep(count);
            }
        }
    }

    return (retVal);
}


Int32 BspUtils_appDeInitUB913Ser(UInt32 instId, UInt32 portId, UInt32 sensorDrvId)
{
    Int32   retVal = BSP_SOK;
    UInt32  nIdx;
    UInt32 i2cDevAddr, numRegs;
    volatile UInt32 count;
    BspUtils_Ub960I2cParams *pSerCfg;

    if (BSPUTILS_UB960EVM_MAX_PORTS > portId)
    {
        i2cDevAddr = gSlaveAliases[instId].rSlave1Addr[portId];
    }
    else
    {
        GT_0trace(BspAppTrace, GT_ERR,
                      "Wrong instance of TIDA00262 !!!\r\n");
        retVal = BSP_EFAIL;
    }
    if (BSP_SOK == retVal)
    {
        numRegs = (sizeof (gUB913SerResetCfg) / sizeof (gUB913SerResetCfg[0U]));
        pSerCfg = &gUB913SerResetCfg[0U];
        if (FVID2_VID_SENSOR_MULDES_OV1063X_DRV == sensorDrvId)
        {
            numRegs = (sizeof (gUB913SerResetCfg_SAT0088_OV10635) /
                            sizeof (gUB913SerResetCfg_SAT0088_OV10635[0U]));
            pSerCfg = &gUB913SerResetCfg_SAT0088_OV10635[0U];
        }

        for (nIdx = 0U;nIdx < numRegs;nIdx++)
        {
            retVal = Bsp_deviceWrite8(
                UB960_ACCESSIBLE_FROM_I2C_INST,
                i2cDevAddr,
                &(pSerCfg[nIdx].nRegAddr),
                &(pSerCfg[nIdx].nRegValue),
                (UInt32) 1U);
            if (retVal != BSP_SOK)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          "Could not configure TIDA00262 !!!\r\n");
                break;
            }

            if (0 != (pSerCfg + nIdx)->nDelay)
            {
                count = (pSerCfg + nIdx)->nDelay;
                while (count)
                {
                    count--;
                }
            }
        }
    }

    return (retVal);
}

UInt32 BspUtils_getSerAddrTida00262(UInt32 instId)
{
    UInt32 addr;
    if (0x0U == instId)
    {
        addr = TIDA00262_PORT_0_SER_ADDR;
    }
    else if (0x1U == instId)
    {
        addr = TIDA00262_PORT_1_SER_ADDR;
    }
    else if (0x2U == instId)
    {
        addr = TIDA00262_PORT_2_SER_ADDR;
    }
    else
    {
        addr = TIDA00262_PORT_3_SER_ADDR;
    }
    return (addr);
}

UInt32 BspUtils_getSerAddrIMI(UInt32 instId)
{
    UInt32 addr;
    if (0x0U == instId)
    {
        addr = IMI_PORT_0_SER_ADDR;
    }
    else if (0x1U == instId)
    {
        addr = IMI_PORT_1_SER_ADDR;
    }
    else if (0x2U == instId)
    {
        addr = IMI_PORT_2_SER_ADDR;
    }
    else
    {
        addr = IMI_PORT_3_SER_ADDR;
    }
    return (addr);
}

UInt32 BspUtils_getSerAddrAR1xxx(UInt32 instId)
{
    UInt32 addr;
    if (0x0U == instId)
    {
        addr = D3_AR1243_PORT_0_SER_ADDR;
    }
    else if (0x1U == instId)
    {
        addr = D3_AR1243_PORT_1_SER_ADDR;
    }
    else if (0x2U == instId)
    {
        addr = D3_AR1243_PORT_2_SER_ADDR;
    }
    else
    {
        addr = D3_AR1243_PORT_3_SER_ADDR;
    }
    return (addr);
}

Int32 BspUtils_updateSlaveAddrUb960(UInt32 instId,
                            const BspUtils_Ub960SourceI2cAddr *pSlaveAddr)
{
    Int32   retVal = BSP_EBADARGS;
    UInt32  nIdx, numRegs;
    volatile UInt32 count;

    if (NULL != pSlaveAddr)
    {
        retVal = BSP_SOK;
        gSlaveAliases[instId].slaveAddr = pSlaveAddr->slaveAddr;
        gSlaveAliases[instId].numSource = pSlaveAddr->numSource;
    }

    if (BSP_SOK == retVal)
    {
        for (nIdx = 0U; nIdx < BSPUTILS_UB960EVM_MAX_PORTS; nIdx++)
        {
            gSlaveAliases[instId].rSlave1Addr[nIdx] = pSlaveAddr->rSlave1Addr[nIdx];
            gSlaveAliases[instId].rSlave2Addr[nIdx] = pSlaveAddr->rSlave2Addr[nIdx];
        }

        count = 0U;
        numRegs = (sizeof (gUb960Cfg_updateSlaveAddr) / \
                                    sizeof (gUb960Cfg_updateSlaveAddr[0U]));

        for (nIdx = 0U;nIdx < numRegs;nIdx++)
        {
            if (0x65 == gUb960Cfg_updateSlaveAddr[nIdx].nRegAddr)
            {
                gUb960Cfg_updateSlaveAddr[nIdx].nRegValue =
                        (gSlaveAliases[instId].rSlave1Addr[count] << 1U);
            }
            if (0x66 == gUb960Cfg_updateSlaveAddr[nIdx].nRegAddr)
            {
                gUb960Cfg_updateSlaveAddr[nIdx].nRegValue =
                        (gSlaveAliases[instId].rSlave2Addr[count] << 1U);
                count++;
            }
            GT_assert(BspAppTrace, (BSPUTILS_UB960EVM_MAX_PORTS >= count));
        }

        for (nIdx = 0U;nIdx < numRegs;nIdx++)
        {
            retVal = Bsp_deviceWrite8(
                UB960_ACCESSIBLE_FROM_I2C_INST,
                gSlaveAliases[instId].slaveAddr,
                &(gUb960Cfg_updateSlaveAddr[nIdx].nRegAddr),
                &(gUb960Cfg_updateSlaveAddr[nIdx].nRegValue),
                (UInt32) 1U);
            if (retVal != BSP_SOK)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          "Could not configure UB960 !!!\n");
                break;
            }

            if (0 != gUb960Cfg_updateSlaveAddr[nIdx].nDelay)
            {
                count = gUb960Cfg_updateSlaveAddr[nIdx].nDelay;
                while (count)
                {
                    count--;
                }
            }
        }
    }

    return (retVal);
}

UInt32 BspUtils_getSerAddrSat0088(UInt32 instId)
{
    UInt32 addr;
    if (0x0U == instId)
    {
        addr = SAT0088_OV10635_PORT_0_SER_ALIAS_ADDR;
    }
    else if (0x1U == instId)
    {
        addr = SAT0088_OV10635_PORT_1_SER_ALIAS_ADDR;
    }
    else if (0x2U == instId)
    {
        addr = SAT0088_OV10635_PORT_2_SER_ALIAS_ADDR;
    }
    else
    {
        addr = SAT0088_OV10635_PORT_3_SER_ALIAS_ADDR;
    }
    return (addr);
}

Int32 BspUtils_getDebugRegVal(UInt32 instId,
                                  UInt32 sensorDrvId,
                                  const BspUtils_Ub960SourceI2cAddr *pSlaveAddr,
                                  BspUtils_Ub960DebugRegData *pDebugStatus)
{
    Int32 retVal = 0;
    UInt32 cnt = 0;

    for (cnt = 0;cnt < gUB96xdebugStatus.numofReg; cnt++)
    {
        /* read deserializer version number */
        retVal += Bsp_deviceRead8(
                    UB960_ACCESSIBLE_FROM_I2C_INST,
                    pSlaveAddr->slaveAddr,
                    &gUB96xdebugStatus.ub96xdebugData[cnt].regAddr,
                    &pDebugStatus->ub96xdebugData[cnt].regValue,
                    (UInt32) 1U);
        pDebugStatus->ub96xdebugData[cnt].regAddr =
                gUB96xdebugStatus.ub96xdebugData[cnt].regAddr;
    }
    pDebugStatus->numofReg = gUB96xdebugStatus.numofReg;
    return retVal;
}

Uint8 BspUtils_appGetUb96xVersion(UInt32 instId)
{
    Int32 retVal;
    Uint8 tempAddr, tempData;

    /* FPD3_RX_ID5 register of UB96x */
    tempAddr = (Uint8)0xF5;
    tempData = 0x00;

    /* read deserializer version number */
    retVal = Bsp_deviceRead8(
                    UB960_ACCESSIBLE_FROM_I2C_INST,
                    gSlaveAliases[instId].slaveAddr,
                    &tempAddr,
                    &tempData,
                    (UInt32) 1U);

/* C & C++ INVARIANT_CONDITION.GEN
 * Expression 'if (BSPUTILS_UB964_VERSION_ID == tempData)' used in the condition
 * always yields the same result.
 * Name if (BSPUTILS_UB964_VERSION_ID != ub96xVer)
 * KW State: Ignore -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * In cases where value in the if condition  is dependent on the return of a
 * function and currently the function is hardcoded to return a value. Code is
 * currently unreachable but as the implementation of the function changes, it
 * will not be unreachable.
 */
    if(BSP_SOK == retVal)
    {
        if (BSPUTILS_UB964_VERSION_ID == tempData)
        {
            GT_0trace(BspAppTrace, GT_INFO,
                                "Detected UB964 !!!\r\n");
        }
        else
        {
            GT_0trace(BspAppTrace, GT_INFO,
                                "Detected UB960 !!!\r\n");
        }
    }
    else
    {
        tempData = 0x00;
    }

    return (tempData);
}

static Int32 setCameraPower(BspUtils_FpdCamPowerLevel pwrlvl)
{
#ifdef BOARD_TYPE_TDA3XX_RVP
    Int32 retVal = BSP_SOK;
    Bsp_BoardRev rvpBoardRev;

    if((UInt32)FALSE == gSetPowerDone)
    {
        rvpBoardRev = Bsp_boardGetBaseBoardRev();

        if((rvpBoardRev == BSP_BOARD_REV_BETA) ||
           (rvpBoardRev == BSP_BOARD_REV_A) ||
           (rvpBoardRev == BSP_BOARD_REV_A_4G))
        {
            uint32_t Enable_FPD_Power_Out_Base = SOC_GPIO2_BASE;
            uint32_t Enable_FPD_Power_Out_Pin  = 10; /* 0 = disable, 1 = enable */
            uint32_t Voltage_Select_5V12V_Base = SOC_GPIO2_BASE;
            uint32_t Voltage_Select_5V12V_Pin  = 12; /* 0 = 5v5, 1 = 12v */
            uint32_t LoadSwitch_IN_Base = SOC_GPIO2_BASE;
            uint32_t LoadSwitch_IN_Pin  = 13; /* 0 = disable, 1 = enable */

            GT_0trace(BspAppTrace, GT_INFO, " D3 RVP UB96x Power Up" );

            switch (pwrlvl)
            {
                case BSPUTILS_FPDCAMPOWERLEVEL_OFF:
                    GPIOPinWrite(Enable_FPD_Power_Out_Base, Enable_FPD_Power_Out_Pin, 0);
                    GPIOPinWrite(LoadSwitch_IN_Base, LoadSwitch_IN_Pin, 0);
                    break;

                case BSPUTILS_FPDCAMPOWERLEVEL_5V5:
                    /* disable power */
                    GPIOPinWrite(Enable_FPD_Power_Out_Base, Enable_FPD_Power_Out_Pin, 0);
                    GPIOPinWrite(LoadSwitch_IN_Base, LoadSwitch_IN_Pin, 0);
                    BspOsal_sleep(10);

                    /* set 5v5 */
                    GPIOPinWrite(Voltage_Select_5V12V_Base, Voltage_Select_5V12V_Pin, 0);
                    BspOsal_sleep(10);

                    /* enable VDD_FPD */
                    GPIOPinWrite(Enable_FPD_Power_Out_Base, Enable_FPD_Power_Out_Pin, 1);
                    BspOsal_sleep(10);

                    /* enable output power */
                    GPIOPinWrite(LoadSwitch_IN_Base, LoadSwitch_IN_Pin, 1);
                    break;

                case BSPUTILS_FPDCAMPOWERLEVEL_12V0:
                    /* disable power */
                    GPIOPinWrite(Enable_FPD_Power_Out_Base, Enable_FPD_Power_Out_Pin, 0);
                    GPIOPinWrite(LoadSwitch_IN_Base, LoadSwitch_IN_Pin, 0);
                    BspOsal_sleep(10);

                    /* set 12v0 */
                    GPIOPinWrite(Voltage_Select_5V12V_Base, Voltage_Select_5V12V_Pin, 1);
                    BspOsal_sleep(10);

                    /* enable VDD_FPD */
                    GPIOPinWrite(Enable_FPD_Power_Out_Base, Enable_FPD_Power_Out_Pin, 1);
                    BspOsal_sleep(10);

                    /* enable output power */
                    GPIOPinWrite(LoadSwitch_IN_Base, LoadSwitch_IN_Pin, 1);
                    break;

                default:
                    GT_0trace(BspAppTrace, GT_ERR,
                            " Unknown power option\n");
                    retVal = BSP_EFAIL;
                    break;
            }
        }
        else if((rvpBoardRev == BSP_BOARD_REV_STARTER_KIT_REV_1) ||
                (rvpBoardRev == BSP_BOARD_REV_STARTER_KIT_REV_DASH))
        {
            uint32_t LoadSwitch_IN_Base = SOC_GPIO3_BASE;
            uint32_t LoadSwitch_IN_Pin  = 23; /* 0 = disable, 1 = enable */
            GT_0trace(BspAppTrace, GT_INFO, " D3 Starter Kit UB96x Power Up" );

            switch (pwrlvl)
            {
                case BSPUTILS_FPDCAMPOWERLEVEL_OFF:
                    GPIOPinWrite(LoadSwitch_IN_Base, LoadSwitch_IN_Pin, 0);
                    break;

                case BSPUTILS_FPDCAMPOWERLEVEL_5V5: /* Unsupported in SK hardware */
                        GT_0trace(BspAppTrace, GT_ERR, "ERROR: 5V5 FPD Link power option not available!  Using 12V.\n");
                        /* fall through... */

                case BSPUTILS_FPDCAMPOWERLEVEL_12V0:
                    /* enable output power */
                    GPIOPinWrite(LoadSwitch_IN_Base, LoadSwitch_IN_Pin, 1);
                    break;

                default:
                    GT_0trace(BspAppTrace, GT_ERR,
                            " Unknown power option\n");
                    retVal = BSP_EFAIL;
                    break;
            }
        }
        else if(rvpBoardRev == BSP_BOARD_MAX)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                    " Failed to detect board ID\n");
        }
        else
        {
            GT_0trace(BspAppTrace, GT_ERR,
                    " Failed to detect board ID\n");
        }

        gSetPowerDone = (UInt32)TRUE;
    }
    else
    {
        retVal = BSP_SOK;
    }

    return retVal;
#else
    /*
     *  UB960 EVM: Selected using jumper.
     */
    return (BSP_SOK);
#endif
}

static Int32 initDeserializer(UInt32 instId)
{
#ifdef BOARD_TYPE_TDA3XX_RVP
    Int32 retVal;
    Uint8 tempAddr, tempData;

    if((UInt32)FALSE == gInitDeserDone)
    {
        retVal = resetDeserializer();
        if(retVal != BSP_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                        " Failed to reset deserializer\n");
        }

        tempAddr = 0x03;
        tempData = 0x00;

        /* read deserializer version number */
        retVal = Bsp_deviceRead8(
                        UB960_ACCESSIBLE_FROM_I2C_INST,
                        gSlaveAliases[instId].slaveAddr,
                        &tempAddr,
                        &tempData,
                        (UInt32) 1U);

        /* perform unique init based on deserializer version */
        if(retVal == BSP_SOK)
        {
            /* 960 Alpha */
            if(tempData == 0x10)
            {
                GT_0trace(BspAppTrace, GT_INFO,
                            " Detected 960 DeSerializer\n");
                writeI2Cconfig(
                            sizeof(g960AlphaInitCfg)/sizeof(g960AlphaInitCfg[0]),
                            g960AlphaInitCfg,
                            gSlaveAliases[instId].slaveAddr);
            }
            else if(tempData == 0x20)
            {
                GT_0trace(BspAppTrace, GT_INFO,
                            " Detected 964 v2 DeSerializer\n");
                writeI2Cconfig(
                            sizeof(g964AlphaInitCfg)/sizeof(g964AlphaInitCfg[0]),
                            g964AlphaInitCfg,
                            gSlaveAliases[instId].slaveAddr);
            }
            else if(tempData == 0x30)
            {
                GT_0trace(BspAppTrace, GT_INFO,
                            " Detected 964 v3 DeSerializer\n");
            }
            else if(tempData == 0x40)
            {
                GT_0trace(BspAppTrace, GT_INFO,
                            " Detected 964 v4 DeSerializer\n");
            }
            else
            {
                GT_0trace(BspAppTrace, GT_INFO,
                            " Unknown DeSerializer Version\n");
            }
        }
        else
        {
            GT_0trace(BspAppTrace, GT_ERR,
                        " Failed to read from DeSerializer\n");
        }

        gInitDeserDone = (UInt32)TRUE;
    }
    else
    {
        retVal = BSP_SOK;
    }

    return retVal;
#else
    return (BSP_SOK);
#endif
}

#ifdef BOARD_TYPE_TDA3XX_RVP
static Int32 resetDeserializer(void)
{
    Int32 retVal = BSP_SOK;
    Uint8 tempAddr, tempData;

    tempAddr = 7;
    tempData = 0;
    retVal |= Bsp_deviceRead8(
                            BSP_DEVICE_I2C_INST_ID_1,
                            KTCA9539_I2CADDR_BASEBOARD,
                            &tempAddr,
                            &tempData,
                            1U);
    tempData &= 0xEF;
    retVal |= Bsp_deviceWrite8(
                            BSP_DEVICE_I2C_INST_ID_1,
                            KTCA9539_I2CADDR_BASEBOARD,
                            &tempAddr,
                            &tempData,
                            1U);

    /* Toggle expander bit 4 for reset */
    tempAddr  = 3;
    tempData = 0;
    retVal |= Bsp_deviceRead8(
                            BSP_DEVICE_I2C_INST_ID_1,
                            KTCA9539_I2CADDR_BASEBOARD,
                            &tempAddr,
                            &tempData,
                            1U);
    tempData |= 0x10;
    retVal |= Bsp_deviceWrite8(
                            BSP_DEVICE_I2C_INST_ID_1,
                            KTCA9539_I2CADDR_BASEBOARD,
                            &tempAddr,
                            &tempData,1U);
    BspOsal_sleep(100);
    tempData &= 0xEF;
    retVal |= Bsp_deviceWrite8(
                            BSP_DEVICE_I2C_INST_ID_1,
                            KTCA9539_I2CADDR_BASEBOARD,
                            &tempAddr,
                            &tempData,
                            1U);

    BspOsal_sleep(100);
    tempData |= 0x10;
    retVal |= Bsp_deviceWrite8(
                            BSP_DEVICE_I2C_INST_ID_1,
                            KTCA9539_I2CADDR_BASEBOARD,
                            &tempAddr,
                            &tempData,
                            1U);
    BspOsal_sleep(100);

    return (retVal);
}

static Int32 writeI2Cconfig(
                    Int32 regCount,
                    BspUtils_Ub960I2cParams *params,
                    UInt32 slaveAddr)
{
    Int32   retVal = BSP_SOK;
    UInt32 nIdx;
    Int32 count;

    for (nIdx = 0U;nIdx < regCount; nIdx++)
    {
        retVal = Bsp_deviceWrite8(
                        UB960_ACCESSIBLE_FROM_I2C_INST,
                        slaveAddr,
                        &(params[nIdx].nRegAddr),
                        &(params[nIdx].nRegValue),
                        (UInt32) 1U);

        if (retVal != BSP_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      " Could not configure UB960 !!!\n");
            break;
        }

        if (0 != params[nIdx].nDelay)
        {
            count = params[nIdx].nDelay;
            while (count)
            {
                count --;
            }
        }
    }

    return retVal;
}
#endif /* BOARD_TYPE_TDA3XX_RVP */

static void setUb960Gpio0To1(UInt32 instId, UInt32 port)
{
    Int32 retVal;
    UInt8 regAddr, regValue;

    /*  Select port
        Read GPIO Register
        Modify GPIO 0 to low
        Write back
    */

    /* Select Port */
    regAddr = (UInt8)0x4C;
    if (0U == port)
    {
        regValue = (UInt8)0x01;
    }
    else if (1U == port)
    {
        regValue = (UInt8)0x12;
    }
    else if (2U == port)
    {
        regValue = (UInt8)0x24;
    }
    else
    {
        regValue = (UInt8)0x38;
    }
    retVal = Bsp_deviceWrite8(  UB960_ACCESSIBLE_FROM_I2C_INST,
                                gSlaveAliases[instId].slaveAddr,
                                &regAddr,
                                &regValue,
                                (UInt32) 1U);
    if (retVal != BSP_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                            "GPI0 Change Could not write UB960 (1) !!!\r\n");
    }

    /* Read GPIO Register */
    regAddr = (UInt8)0x6E;
    regValue = 0U;
    retVal = Bsp_deviceRead8(   UB960_ACCESSIBLE_FROM_I2C_INST,
                                gSlaveAliases[instId].slaveAddr,
                                &regAddr,
                                &regValue,
                                (UInt32) 1U);
    if (retVal != BSP_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                            "GPI0 Change Could not read UB960 (2) !!!\r\n");
    }
    /* Bit 0 & 3 set */
    regValue = regValue | (UInt8)0x09;

    retVal = Bsp_deviceWrite8(  UB960_ACCESSIBLE_FROM_I2C_INST,
                                gSlaveAliases[instId].slaveAddr,
                                &regAddr,
                                &regValue,
                                (UInt32) 1U);
    if (retVal != BSP_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                            "GPI0 Change Could not write UB960 (3) !!!\r\n");
    }
}

Int32 BspUtils_appUb960EnableFsin(UInt32 instId,
                                  UInt32 sensorDrvId,
                                  const BspUtils_Ub960SourceI2cAddr *pSlaveAddr,
                                  const BspUtils_Ub960Status *pStatus)
{
    Int32   retVal = BSP_EBADARGS;
    UInt32  nIdx, numRegs;
    BspUtils_Ub960I2cParams *pUb960I2cPrm;
    BspUtils_Ub960I2cParams ub960I2cPrm[] = {
        {0x19, 0x01, 0x0},
        {0x1A, 0x15, 0x0},
        {0x1B, 0x09, 0x0},
        {0x1C, 0xC3, 0x0},
        {0x18, 0x01, 0xFFF}, /* Start FSIN. Delay to allow it to stabilize */
        {0x4C, 0x01, 0x0},
        {0x6e, 0x9A, 0x0},   /* Send FSIN on BC_GPIO0 RX0 */
        {0x4C, 0x12, 0x0},
        {0x6e, 0x9A, 0x0},   /* Send FSIN on BC_GPIO0 RX1 */
        {0x4C, 0x24, 0x0},
        {0x6e, 0x9A, 0x0},   /* Send FSIN on BC_GPIO0 RX2 */
        {0x4C, 0x38, 0x0},
        {0x6e, 0x9A, 0x0}    /* Send FSIN on BC_GPIO0 RX3 */
    };
    Int32 count;

    pUb960I2cPrm = &ub960I2cPrm[0];
    numRegs = sizeof (ub960I2cPrm)/sizeof (ub960I2cPrm[0U]);

    if ((NULL != pStatus) && (NULL != pSlaveAddr))
    {
        retVal = BSP_SOK;
        gSlaveAliases[instId].slaveAddr = pSlaveAddr->slaveAddr;
        gSlaveAliases[instId].numSource = pSlaveAddr->numSource;
    }

    for (nIdx = 0U;nIdx < numRegs;nIdx++)
    {
        retVal = Bsp_deviceWrite8(
            UB960_ACCESSIBLE_FROM_I2C_INST,
            gSlaveAliases[instId].slaveAddr,
            &((pUb960I2cPrm + nIdx)->nRegAddr),
            &((pUb960I2cPrm + nIdx)->nRegValue),
            (UInt32) 1U);

        if (retVal != BSP_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      "Could not configure UB960 !!!\r\n");
            break;
        }

        if (0 != (pUb960I2cPrm + nIdx)->nDelay)
        {
            count = (pUb960I2cPrm + nIdx)->nDelay;
            while (count)
            {
                count--;
            }
        }
    }

    for (nIdx = 0U; nIdx < gSlaveAliases[instId].numSource; nIdx++)
    {
        BspUtils_appInitUB913PassThroughGPIO0(instId, nIdx);
    }

    return (retVal);
}

static Int32 BspUtils_appInitUB913PassThroughGPIO0(UInt32 instId, UInt32 portId)
{
    Int32   retVal = BSP_SOK;
    UInt32  nIdx;
    UInt32 i2cDevAddr = 0U, numRegs;
    volatile UInt32 count;
    BspUtils_Ub960I2cParams *pSerCfg = NULL;
    BspUtils_Ub960I2cParams gUB913PassThruGPIO0[] = {
        {0x0D, 0x9D, 0x0},
    };

    pSerCfg = &gUB913PassThruGPIO0[0U];
    numRegs = sizeof (gUB913PassThruGPIO0) /
                            sizeof (gUB913PassThruGPIO0[0U]);

    if (BSPUTILS_UB960EVM_MAX_PORTS > portId)
    {
        i2cDevAddr = gSlaveAliases[instId].rSlave1Addr[portId];
    }
    else
    {
        GT_0trace(BspAppTrace, GT_ERR,
                      "Wrong instance of UB913 Ser !!!\r\n");
        retVal = BSP_EFAIL;
    }

    for (nIdx = 0U; ((nIdx < numRegs) && (BSP_SOK == retVal)); nIdx++)
    {
        retVal = Bsp_deviceWrite8(
            UB960_ACCESSIBLE_FROM_I2C_INST,
            i2cDevAddr,
            &(pSerCfg[nIdx].nRegAddr),
            &(pSerCfg[nIdx].nRegValue),
            (UInt32) 1U);
        if (retVal != BSP_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      "Could not configure UB913 Ser !!!\r\n");
            break;
        }

        if (0 != (pSerCfg + nIdx)->nDelay)
        {
            count = (pSerCfg + nIdx)->nDelay;
            while (count)
            {
                count--;
            }
        }
    }

    return (retVal);
}

Int32 BspUtils_resetAR12xxToSOP4(UInt8 IOExpAddr)
{
    UInt32 status = BSP_SOK, funcStatus=BSP_SOK;
    UInt8 tempAddr = 0x4C, tempData;
    Int32 retries = 0, maxRetries = 10;
    /*Switching RX Port on Ub960, locking write access to other sensors */
    switch (IOExpAddr)
    {
        case (D3RIB_PORT_0_IOEXP_ADDR):
            tempData = 0x01;
            break;
        case (D3RIB_PORT_1_IOEXP_ADDR):
            tempData = 0x12;
            break;
        case (D3RIB_PORT_2_IOEXP_ADDR):
            tempData = 0x24;
            break;
        case (D3RIB_PORT_3_IOEXP_ADDR):
            tempData = 0x38;
            break;
        default:
            return BSP_EBADARGS;
    }
    status = Bsp_deviceWrite8(
                            UB960_ACCESSIBLE_FROM_I2C_INST,
                            UB960_SLAVE_ADDR,
                            &tempAddr,
                            &tempData,
                            (UInt32) 1U);
    BspOsal_sleep(500);

    /*Set SOP Modes and Reset using GPIO expander*/
    /*-------------------------------------------*/
    do{
        /*Assert Reset and Warm Reset*/
        tempAddr = 2;
        tempData = 0x00; /*[7:0] 0000 0000*/
        status = Bsp_deviceWrite8(
                            UB960_ACCESSIBLE_FROM_I2C_INST,
                            IOExpAddr,
                            &tempAddr,
                            &tempData,
                            (UInt32) 1U);
        BspOsal_sleep(100);
        retries++;
    }while((status != BSP_SOK) && (retries < maxRetries));
    retries = 0;
    funcStatus |= status;
    BspOsal_sleep(500);

    do{
        /*Set Pin directions for bank 0 of IO expander*/
        tempAddr = 6; /*Pin direction of bank 0 pins*/
        tempData = 0x38; /*[7:0] OOII IOOO*/
        status = Bsp_deviceWrite8(
                            UB960_ACCESSIBLE_FROM_I2C_INST,
                            IOExpAddr,
                            &tempAddr,
                            &tempData,
                            (UInt32) 1U);
        BspOsal_sleep(10);
        retries++;
    }while((status != BSP_SOK) && (retries < maxRetries));
    BspOsal_sleep(500);

    retries = 0;
    funcStatus |= status;

    do{
        /*Assert AR_ERROR_INn*/
        tempAddr = 3;
        tempData = 0x00; /*[7:0] 0000 0000*/
        status = Bsp_deviceWrite8(
                            UB960_ACCESSIBLE_FROM_I2C_INST,
                            IOExpAddr,
                            &tempAddr,
                            &tempData,
                            (UInt32) 1U);
        BspOsal_sleep(100);
        retries++;
    }while((status != BSP_SOK) && (retries < maxRetries));
    retries = 0;
    funcStatus |= status;
    BspOsal_sleep(500);

    do{
        /*Set Pin directions for bank 1 of IO expander*/
        tempAddr = 7; /*Pin direction of bank 1 pins*/
        tempData = 0xDF; /*[7:0] IIOI IIII*/
        status = Bsp_deviceWrite8(
                            UB960_ACCESSIBLE_FROM_I2C_INST,
                            IOExpAddr,
                            &tempAddr,
                            &tempData,
                            (UInt32) 1U);
        BspOsal_sleep(100);
        retries++;
    }while((status != BSP_SOK) && (retries < maxRetries));
    retries = 0;
    funcStatus |= status;
    BspOsal_sleep(500);

    do{
        /*Set SOP Mode 4*/
        tempAddr = 2;
        tempData = 0x04; /*[7:0] 11O0 0100*/
        status = Bsp_deviceWrite8(
                            UB960_ACCESSIBLE_FROM_I2C_INST,
                            IOExpAddr,
                            &tempAddr,
                            &tempData,
                            (UInt32) 1U);
        BspOsal_sleep(100);
        retries++;
    }while((status != BSP_SOK) && (retries < maxRetries));
    retries = 0;
    funcStatus |= status;
    BspOsal_sleep(500);

    do{
        /*De-Assert AR_ERROR_INn*/
        tempAddr = 3;
        tempData = 0x20; /*[7:0] 0010 0000*/
        status = Bsp_deviceWrite8(
                            UB960_ACCESSIBLE_FROM_I2C_INST,
                            IOExpAddr,
                            &tempAddr,
                            &tempData,
                            (UInt32) 1U);
        BspOsal_sleep(100);
        retries++;
    }while((status != BSP_SOK) && (retries < maxRetries));
    retries = 0;
    funcStatus |= status;
    BspOsal_sleep(500);

    do{
        /*Bring radar module out of reset*/
        tempAddr = 2;
        tempData = 0xC4; /*[7:0] 1100 0100*/
        status = Bsp_deviceWrite8(
                            UB960_ACCESSIBLE_FROM_I2C_INST,
                            IOExpAddr,
                            &tempAddr,
                            &tempData,
                            (UInt32) 1U);
        BspOsal_sleep(500);
        retries++;
    }while((status != BSP_SOK) && (retries < maxRetries));
    funcStatus |= status;
    BspOsal_sleep(500);

    return funcStatus;
}

Int32 BspUtils_appUb960InitAR12xx(UInt32 sensorDrvId, UInt32 numSensors)
{
    UInt32 instId = 0;
    BspUtils_Ub960SourceI2cAddr i2Cinfo;
    BspUtils_Ub960Status ub960Status;
    Int32 status = BSP_SOK;

    i2Cinfo.slaveAddr = UB960_SLAVE_ADDR;
    i2Cinfo.rSlave1Addr[0] = D3_AR1243_PORT_0_SER_ADDR;
    i2Cinfo.rSlave1Addr[1] = D3_AR1243_PORT_1_SER_ADDR;
    i2Cinfo.rSlave1Addr[2] = D3_AR1243_PORT_2_SER_ADDR;
    i2Cinfo.rSlave1Addr[3] = D3_AR1243_PORT_3_SER_ADDR;
    i2Cinfo.rSlave2Addr[0] = D3_AR1243_PORT_0_SENSOR_ADDR;
    i2Cinfo.rSlave2Addr[1] = D3_AR1243_PORT_1_SENSOR_ADDR;
    i2Cinfo.rSlave2Addr[2] = D3_AR1243_PORT_2_SENSOR_ADDR;
    i2Cinfo.rSlave2Addr[3] = D3_AR1243_PORT_3_SENSOR_ADDR;
    i2Cinfo.numSource = numSensors;
    status = BspUtils_appInitUb960(instId, sensorDrvId, &i2Cinfo, &ub960Status);

    return status;
}

Int32 BspUtils_appUb960DeInitAR12xx(void)
{
    UInt8 IOexpI2Caddr = D3_AR1243_PORT_0_SENSOR_ADDR;
    UInt8 tempAddr = 0U, tempData = 0U;
    Int32 retVal = BSP_SOK;
    Int32 status = BSP_SOK;
    Int32 maxRetries = 10, retries = 0;

    do{
        /* Set radar module into reset*/
        tempAddr = 2;
        tempData = 0x00; /*[7:0]  0x00 to put everything into reset, FPD Link only */
        status = Bsp_deviceWrite8(
                    UB960_ACCESSIBLE_FROM_I2C_INST,
                    IOexpI2Caddr,
                    &tempAddr,
                    &tempData,
                    (UInt32) 1U);
        BspOsal_sleep(500);
        retries++;
    }while((status != BSP_SOK) && (retries < maxRetries));

    /* power it off. */
    retVal = setCameraPower( BSPUTILS_FPDCAMPOWERLEVEL_OFF );
    BspOsal_sleep( 500 );

#ifdef BOARD_TYPE_TDA3XX_RVP
    /* reset the deserializer */
    resetDeserializer();
#endif

    return retVal;
}

Int32 BspUtils_appUb960BootAR12xx(UInt8 port)
{
    Int32 status = BSP_SOK;

    switch(port)
    {
        case 3:
            status = BspUtils_resetAR12xxToSOP4(D3RIB_PORT_3_IOEXP_ADDR);
           break;
        case 2:
            status = BspUtils_resetAR12xxToSOP4(D3RIB_PORT_2_IOEXP_ADDR);
            break;
        case 1:
            status = BspUtils_resetAR12xxToSOP4(D3RIB_PORT_1_IOEXP_ADDR);
            break;
        case 0:
            status = BspUtils_resetAR12xxToSOP4(D3RIB_PORT_0_IOEXP_ADDR);
            break;
        default:
            GT_1trace(BspDeviceTrace, GT_ERR, "Invalid deserializer port number: %d! \r\n", port);
            status = BSP_EBADARGS;
    }

    if (status != BSP_SOK)
    {
        GT_1trace(BspDeviceTrace, GT_ERR, "Port %d ERR\r\n", port);
    }
    else
    {
        GT_1trace(BspDeviceTrace, GT_INFO, "Port %d done \r\n", port);
    }

    return status;
}

Int32 BspUtils_enableUb960CsiOutput(void)
{
    Int32 status = 0;
    UInt8 j;
    UInt8 tempData, tempAddr;

    for(j = 0; j < 4; j++)
    {
        tempAddr = 0x4C;
        tempData = (j<<4) | (1<<j);
        /* Select Channel */
        status |= Bsp_deviceWrite8(
                    UB960_ACCESSIBLE_FROM_I2C_INST,
                    UB960_SLAVE_ADDR,
                    &tempAddr,
                    &tempData,
                    1U);
        BspOsal_sleep(100);

        tempAddr = 0x33;
        status |= Bsp_deviceRead8(
                    UB960_ACCESSIBLE_FROM_I2C_INST,
                    UB960_SLAVE_ADDR,
                    &tempAddr,
                    &tempData,
                    1U);

        tempData |= 0x01; /*Enable CSI Output*/
        status |= Bsp_deviceWrite8(
                    UB960_ACCESSIBLE_FROM_I2C_INST,
                    UB960_SLAVE_ADDR,
                    &tempAddr,
                    &tempData,
                    1U);

    }

    return status;
}

Int32 BspUtils_disableUb960CsiOutput(void)
{
    UInt8 j;
    UInt8 tempData, tempAddr;
    Int32 status = 0;

    for(j = 0; j < 4; j++)
    {
        /* Select Channel */
        tempAddr = 0x4C;
        tempData = (j<<4) | (1<<j);
        status |= Bsp_deviceWrite8(
                    UB960_ACCESSIBLE_FROM_I2C_INST,
                    UB960_SLAVE_ADDR,
                    &tempAddr,
                    &tempData,
                    1U);
        BspOsal_sleep(100);

        tempAddr = 0x33;
        status |= Bsp_deviceRead8(
                    UB960_ACCESSIBLE_FROM_I2C_INST,
                    UB960_SLAVE_ADDR,
                    &tempAddr,
                    &tempData,
                    1U);

        tempData &= ~(0x01); /*Disable CSI Output*/
        status |= Bsp_deviceWrite8(
                    UB960_ACCESSIBLE_FROM_I2C_INST,
                    UB960_SLAVE_ADDR,
                    &tempAddr,
                    &tempData,
                    1U);
    }

    return status;
}
