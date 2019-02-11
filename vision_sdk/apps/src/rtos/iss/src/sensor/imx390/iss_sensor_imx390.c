/******************************************************************************
Copyright (c) [2012 - 2017] Texas Instruments Incorporated

All rights reserved not granted herein.

Limited License.

 Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 license under copyrights and patents it now or hereafter owns or controls to
 make,  have made, use, import, offer to sell and sell ("Utilize") this software
 subject to the terms herein.  With respect to the foregoing patent license,
 such license is granted  solely to the extent that any such patent is necessary
 to Utilize the software alone.  The patent license shall not apply to any
 combinations which include this software, other than combinations with devices
 manufactured by or for TI ("TI Devices").  No hardware patent is licensed
 hereunder.

 Redistributions must preserve existing copyright notices and reproduce this
 license (including the above copyright notice and the disclaimer and
 (if applicable) source code license limitations below) in the documentation
 and/or other materials provided with the distribution

 Redistribution and use in binary form, without modification, are permitted
 provided that the following conditions are met:

 * No reverse engineering, decompilation, or disassembly of this software
   is permitted with respect to any software provided in binary form.

 * Any redistribution and use are licensed by TI for use only with TI Devices.

 * Nothing shall obligate TI to provide you with source code for the software
   licensed and provided to you in object code.

 If software source code is provided to you, modification and redistribution of
 the source code are permitted provided that the following conditions are met:

 * Any redistribution and use of the source code, including any resulting
   derivative works, are licensed by TI for use only with TI Devices.

 * Any redistribution and use of any object code compiled from the source code
   and any resulting derivative works, are licensed by TI for use only with TI
   Devices.

 Neither the name of Texas Instruments Incorporated nor the names of its
 suppliers may be used to endorse or promote products derived from this software
 without specific prior written permission.

 DISCLAIMER.

 THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/

/**
 *******************************************************************************
 * \file iss_sensor_imx390.c
 *
 *
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include <iss_sensor_if.h>
#include <iss_sensor_serdes.h>
/**< ISS AEWB plugin is included here to get the default AEWB configuration
     from each sensor */
#include <algorithmLink_issAewb.h>
#include <ti/drv/vps/include/devices/bsp_device.h>
#include "imx390_linear_1920x1080_config.h"
#include "imx390_wdr_1920x1080_config.h"
#include "imx390_gain_table.h"
#include "imx390_dcc_linear.h"
#include "imx390_dcc_2PassWDR.h"

#include <ti/drv/vps/examples/utility/bsputils_ub960.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

#define ISS_SENSOR_IMX390_DEFAULT_EXP_RATIO     (128U)

#define ISS_SENSOR_IMX390_FEATURES      (ISS_SENSOR_FEATURE_MANUAL_EXPOSURE|   \
                                         ISS_SENSOR_FEATURE_MANUAL_GAIN|       \
                                         ISS_SENSOR_FEATURE_TWO_PASS_WDR_MODE| 	  \
                                         ISS_SENSOR_FEATURE_LINEAR_MODE|       \
                                         ISS_SENSOR_FEATURE_DCC_SUPPORTED)
#define ISS_IMX390_GAIN_TBL_SIZE                (150U)
#define ISS_IMX390_GAIN_TBL_STEP_SIZE           (100U)
#define ISS_IMX390_GAIN_TBL_STARTOFFSET         (10U)
#define ISS_IMX390_MAX_INTG_LINES               (2050U)
#define ISS_IMX390_VMAX                         (0x44c)
#define ISS_IMX390_RHS                          (0x85U)

#define IMX390_SP1H_ANALOG_GAIN_CONTROL_REG_ADDR         (0x0018U)
#define IMX390_SP1H_ANALOG_GAIN_CONTROL_REG_ADDR_HIGH    ( \
        IMX390_SP1H_ANALOG_GAIN_CONTROL_REG_ADDR + 1U)
#define IMX390_SP1L_ANALOG_GAIN_CONTROL_REG_ADDR         (0x001AU)
#define IMX390_SP1L_ANALOG_GAIN_CONTROL_REG_ADDR_HIGH    ( \
        IMX390_SP1L_ANALOG_GAIN_CONTROL_REG_ADDR + 1U)

#define IMX390_VMAX                         (0x465U)

#define IMX390_AE_CONTROL_LONG_REG_ADDR_LOW   (0x000C)
#define IMX390_AE_CONTROL_LONG_REG_ADDR_HIGH   ( \
        IMX390_AE_CONTROL_LONG_REG_ADDR_LOW + 1)
#define IMX390_AE_CONTROL_LONG_REG_ADDR_TOP   ( \
        IMX390_AE_CONTROL_LONG_REG_ADDR_HIGH + 1)

#define IMX390_AE_CONTROL_SHORT_REG_ADDR_LOW   (0x0010)
#define IMX390_AE_CONTROL_SHORT_REG_ADDR_HIGH  ( \
        IMX390_AE_CONTROL_SHORT_REG_ADDR_LOW + 1)
#define IMX390_AE_CONTROL_SHORT_REG_ADDR_MSB   ( \
        IMX390_AE_CONTROL_SHORT_REG_ADDR_HIGH + 1)


#define IMX390_SP1H_ANALOG_GAIN_CONTROL_REG_ADDR         (0x0018U)
#define IMX390_SP1H_ANALOG_GAIN_CONTROL_REG_ADDR_HIGH    ( \
        IMX390_SP1H_ANALOG_GAIN_CONTROL_REG_ADDR + 1U)

#define IMX390_SP1L_ANALOG_GAIN_CONTROL_REG_ADDR         (0x001AU)
#define IMX390_SP1L_ANALOG_GAIN_CONTROL_REG_ADDR_HIGH    ( \
        IMX390_SP1L_ANALOG_GAIN_CONTROL_REG_ADDR + 1U)

BspUtils_Ub960I2cParams gAppIssUtilsUB953SerCfg_D3IMX390[IMX390_D3_SER_CFG_SIZE] = {
    {0x01, 0x01, 2000}, /* reset */
    {0x02, 0x72, 0x10},

    {0x06, 0x21, 0x1F},
    {0x07, 0x28, 0x1F},

    {0x0D, 0x01, 0x10},
    {0x0E, 0xF0, 0x10},
    {0xB0, 0x04, 0x10},
    {0xB1, 0x08, 0x10},
    {0xB2, 0x07, 0x10},
};

BspUtils_Ub960I2cParams gUB960DesCfg_D3IMX390[IMX390_D3_DES_CFG_SIZE] = {
    {0x01, 0x02, 0x10},
    {0x1f, 0x00, 0x10},

    {0xB0, 0x1C,0x10},
    {0xB1, 0x16,0x10},
    {0xB2, 0x00,0x10},
    {0xB1, 0x17,0x10},
    {0xB2, 0x00,0x10},
    {0xB1, 0x18,0x10},
    {0xB2, 0x00,0x10},
    {0xB1, 0x19,0x10},
    {0xB2, 0x00,0x10},
    {0xB0, 0x1C,0x10},
    {0xB1, 0x15,0x10},
    {0xB2, 0x0A,0x100},
    {0xB2, 0x00,0x100},

    {0x0D, 0x90, 0x10}, /*I/O to 3V3 - Options not valid with datashee*/
    {0x0C, 0x0F, 0x10}, /*Enable All ports*/

    /*Select Channel 0*/
    {0x4C, 0x01, 0x10},
    {0x58, 0x5D, 0x10}, /*Enable Back channel, set to 50Mbs*/
    {0x72, 0x00, 0x10}, /*VC map*/

    /*Select Channel 1*/
    {0x4C, 0x12, 0x10},
    {0x58, 0x5D, 0x10},/*Enable Back channel, set to 50Mbs*/

    /*Select Channel 2*/
    {0x4C, 0x24, 0x10},
    {0x58, 0x5D, 0x10},/*Enable Back channel, set to 50Mbs*/

    /*Select Channel 3*/
    {0x4C, 0x38, 0x10},
    {0x58, 0x5D, 0x10},/*Enable Back channel, set to 50Mbs*/

    /*Select Channel 0*/
    {0x4C, 0x01, 0x10},
    {0xB0, 0x04, 0x10},
    {0xB1, 0x03, 0x10},
    {0xB2, 0x20, 0x10},
    {0xB1, 0x13, 0x10},
    {0xB2, 0x20, 0x10},
    {0xB0, 0x04, 0x10},
    {0xB1, 0x04, 0x10},
    {0xB2, 0x3F, 0x10},
    {0xB1, 0x14, 0x10},
    {0xB2, 0x3F, 0x10},
    {0x42, 0x71, 0x10}, /*Unknown*/
    {0x41, 0xF0, 0x10}, /*Unknown*/
    {0xB9, 0x18, 0x10},

    /*Select Channel 1*/
    {0x4C, 0x12, 0x10},
    {0xB0, 0x08, 0x10},
    {0xB1, 0x03, 0x10},
    {0xB2, 0x20, 0x10},
    {0xB1, 0x13, 0x10},
    {0xB2, 0x20, 0x10},
    {0xB0, 0x08, 0x10},
    {0xB1, 0x04, 0x10},
    {0xB2, 0x3F, 0x10},
    {0xB1, 0x14, 0x10},
    {0xB2, 0x3F, 0x10},
    {0xB0, 0x08, 0x10},
    {0x42, 0x71, 0x10}, /*Unknown*/
    {0x41, 0xF0, 0x10}, /*Unknown*/
    {0xB9, 0x18, 0x10},

    /*Select Channel 2*/
    {0x4C, 0x24, 0x10},
    {0xB0, 0x0C, 0x10},
    {0xB1, 0x03, 0x10},
    {0xB2, 0x20, 0x10},
    {0xB1, 0x13, 0x10},
    {0xB2, 0x20, 0x10},
    {0xB0, 0x0C, 0x10},
    {0xB1, 0x04, 0x10},
    {0xB2, 0x3F, 0x10},
    {0xB1, 0x14, 0x10},
    {0xB2, 0x3F, 0x10},
    {0x42, 0x71, 0x10},/*Unknown*/
    {0x41, 0xF0, 0x10},/*Unknown*/
    {0xB9, 0x18, 0x10},

    /*Select Channel 3*/
    {0x4C, 0x38, 0x10},
    {0xB0, 0x10, 0x10},
    {0xB1, 0x03, 0x10},
    {0xB2, 0x20, 0x10},
    {0xB1, 0x13, 0x10},
    {0xB2, 0x20, 0x10},
    {0xB0, 0x10, 0x10},
    {0xB1, 0x04, 0x10},
    {0xB2, 0x3F, 0x10},
    {0xB1, 0x14, 0x10},
    {0xB2, 0x3F, 0x10},
    {0x42, 0x71, 0x10},/*Unknown*/
    {0x41, 0xF0, 0x10},/*Unknown*/
    {0xB9, 0x18, 0x10},

    {0x32, 0x01, 0x10}, /*Enable TX port 0*/
    {0x20, 0x00, 0x10}, /*Forwarding and using CSIport 0 */

    /*Sets GPIOS*/
    {0x10, 0x83, 0x10},
    {0x11, 0xA3, 0x10},
    {0x12, 0xC3, 0x10},
    {0x13, 0xE3, 0x10},

    {0x4C, 0x01, 0x10}, /* 0x01 */
    {0x32, 0x01, 0x10}, /*Enable TX port 0*/
    {0x33, 0x02, 0x10}, /*Enable Continuous clock mode and CSI output*/
    {0xBC, 0x00, 0x10}, /*Unknown*/
    {0x5D, 0x30, 0x10}, /*Serializer I2C Address*/
    {0x65, (PORT_0_SER_ADDR << 1U), 0x10},
    {0x5E, 0x42, 0x10}, /*Sensor I2C Address*/
    {0x66, (PORT_0_SENSOR_ADDR << 1U), 0x10},
    {0x6D, 0x6C,0x10}, /*CSI Mode*/
    {0x72, 0x00,0x10}, /*VC Map - All to 0 */
    {0x7C, 0x20, 0x100}, /*Line Valid active high, Frame Valid active high*/
    {0xD5, 0xF3, 0x100}, /*Auto Attenuation*/
    {0xB0,0x1C, 0x10},
    {0xB1,0x15, 0x10},
    {0xB2,0x0A, 0x10},
    {0xB2,0x00, 0x10},

    {0x4C, 0x12, 0x10}, /* 0x12 */
    {0x32, 0x01, 0x10}, /*Enable TX port 0*/
    {0x33, 0x02, 0x10}, /*Enable Continuous clock mode and CSI output*/
    {0xBC, 0x00, 0x10}, /*Unknown*/
    {0x5D, 0x30, 0x10}, /*Serializer I2C Address*/
    {0x65, (PORT_1_SER_ADDR << 1U), 0x10},
    {0x5E, 0x42, 0x10}, /*Sensor I2C Address*/
    {0x66, (PORT_1_SENSOR_ADDR << 1U), 0x10},
    {0x6D, 0x6C,0x10}, /*CSI Mode*/
    {0x72, 0x55,0x10}, /*VC Map - All to 1 */
    {0x7C, 0x20, 0x100}, /*Line Valid active high, Frame Valid active high*/
    {0xD5, 0xF3, 0x100}, /*Auto Attenuation*/
    {0xB0,0x1C, 0x10},
    {0xB1,0x15, 0x10},
    {0xB2,0x0A, 0x10},
    {0xB2,0x00, 0x10},

    {0x4C, 0x24, 0x10}, /* 0x24 */
    {0x32, 0x01, 0x10}, /*Enable TX port 0*/
    {0x33, 0x02, 0x10}, /*Enable Continuous clock mode and CSI output*/
    {0xBC, 0x00, 0x10}, /*Unknown*/
    {0x5D, 0x30, 0x10}, /*Serializer I2C Address*/
    {0x65, (PORT_2_SER_ADDR << 1U), 0x10},
    {0x5E, 0x42, 0x10}, /*Sensor I2C Address*/
    {0x66, (PORT_2_SENSOR_ADDR << 1U), 0x10},
    {0x6D, 0x6C,0x10}, /*CSI Mode*/
    {0x72, 0xaa,0x10}, /*VC Map - All to 2 */
    {0x7C, 0x20, 0x100}, /*Line Valid active high, Frame Valid active high*/
    {0xD5, 0xF3, 0x100}, /*Auto Attenuation*/
    {0xB0,0x1C, 0x10},
    {0xB1,0x15, 0x10},
    {0xB2,0x0A, 0x10},
    {0xB2,0x00, 0x10},

    {0x4C, 0x38, 0x10}, /* 0x38 */
    {0x32, 0x01, 0x10}, /*Enable TX port 0*/
    {0x33, 0x02, 0x10}, /*Enable Continuous clock mode and CSI output*/
    {0xBC, 0x00, 0x10}, /*Unknown*/
    {0x5D, 0x30, 0x10}, /*Serializer I2C Address*/
    {0x65, (PORT_3_SER_ADDR << 1U), 0x10},
    {0x5E, 0x42, 0x10}, /*Sensor I2C Address*/
    {0x66, (PORT_3_SENSOR_ADDR << 1U), 0x10},
    {0x6D, 0x6C,0x10}, /*CSI Mode*/
    {0x72, 0xFF,0x10}, /*VC Map - All to 3 */
    {0x7C, 0x20, 0x100}, /*Line Valid active high, Frame Valid active high*/
    {0xD5, 0xF3, 0x100}, /*Auto Attenuation*/
    {0xB0,0x1C, 0x10},
    {0xB1,0x15, 0x10},
    {0xB2,0x0A, 0x10},
    {0xB2,0x00, 0x10},
};

BspUtils_Ub960I2cParams gUB960DesCfg_D3IMX390_AWR1243[IMX390_AWR1243_D3_DES_CFG_SIZE] = {
    {0x01, 0x02, 1000}, /* Reset */
    {0x1f, 0x00, 0x10}, /* 1.6 Gbps */
    {0xB9, 0x18, 0x10}, /* ENABLE SERIAL LINK DATA INTEGRITY ERROR COUNT */
    {0x42, 0x71, 0x10}, /* ENABLE SFILTER with AEQ ADAPTION */

    /* Select Port 0 */
    {0x4C, 0x01, 0x10}, /* Port 0 */
    {0x58, 0x5D, 0x10}, /* Enable Back channel, set to 50Mbs */
    {0x32, 0x01, 0x10}, /*Enable TX port 0*/
    {0x33, 0x02, 0x10}, /*Enable Continuous clock mode and CSI output*/
    {0xBC, 0x00, 0x10}, /*Unknown*/
    {0x5D, 0x30, 0x10}, /*Serializer I2C Address*/
    {0x65, (PORT_0_SER_ADDR << 1U), 0x10},
    {0x5E, 0x42, 0x10}, /*Sensor I2C Address*/
    {0x66, (PORT_0_SENSOR_ADDR << 1U), 0x10},
    {0x6D, 0x6C,0x10}, /*CSI Mode*/
    {0x72, 0x00,0x10}, /*VC Map - All to 0 */
    {0x7C, 0x20, 0x100}, /*Line Valid active high, Frame Valid active high*/
    {0xD5, 0xF3, 0x100}, /*Auto Attenuation*/
    {0xB0, 0x1C, 0x10},
    {0xB1, 0x15, 0x10},
    {0xB2, 0x0A, 0x10},
    {0xB2, 0x00, 0x10},

    /* Select Port 1 */
    {0x4c, 0x12, 100},   /* Port 1 */
    {0x58, 0x5D, 0x10},  /* Enable Back channel, set to 50Mbs */
    {0xD5, 0xC0, 0x10},  /* Set AEQ MIN/MAX widest values */

    {0x5D, 0x30, 0x10}, /*Serializer I2C Address*/
    {0x65, (D3_AR1243_PORT_1_SER_ADDR << 1U), 0x10}, /*Serializer alias address*/
    {0x5E, 0x50, 0x10}, /*I2C-SPI bridge I2C Address*/
    {0x66, (D3_AR1243_PORT_1_SENSOR_ADDR << 1U), 0x10}, /*Bridge alias address*/
    {0x5F, 0xE8, 0x10}, /*GPIO expander I2C Address*/
    {0x67, (D3RIB_PORT_1_IOEXP_ADDR << 1U), 0x10}, /*GPIO expander alias address*/

    {0x32, 0x01, 0x10}, /*Enable TX port 0*/
    {0x33, 0x03, 0x10}, /*Enable Continuous clock mode and CSI output*/

    {0xBC, 0x00, 0x10}, /*Unknown*/
    {0x6D, 0x6C, 0x10}, /*CSI Mode*/
    {0x05, 0x00, 0x10}, /*CSI Mode*/
    {0x06, 0x01, 0x10}, /*CSI Mode*/
    {0x72, 0x55, 0x10}, /*VC Map - All to 0*/
    {0x7C, 0x00, 0x10}, /*Line Valid active high, Frame Valid active high*/
    {0xD5, 0xF3, 0x10}, /*Auto Attenuation*/

    {0x0D, 0x90, 0x10}, /*I/O to 3V3 - Options not valid with datasheet*/
    {0x0C, 0x0F, 0x10}, /*Enable All ports*/
    {0x20, 0x00, 0x10}, /*Forwarding and using CSIport 0*/

    /*Sets GPIOs*/
    {0x0F, 0xE0, 0x10}, /*Disable GPIO 0 ~ 4 input*/
    {0x10, 0x41, 0x10}, /*GPIO 0 - Output received GPIO 2 (HST_INT) from Port 0*/
    //{0x11, 0x45, 0x10}, /*GPIO 1 - Output received GPIO 2 (HST_INT) from Port 1*/
    {0x12, 0x49, 0x10}, /*GPIO 2 - Output received GPIO 2 (HST_INT) from Port 2*/
    {0x13, 0x4D, 0x10}, /*GPIO 3 - Output received GPIO 2 (HST_INT) from Port 3*/
    {0x14, 0x45, 0x10}, /*GPIO 4 - Output received GPIO 2 (HST_INT) from Port 0*/
    {0x59, 0x83, 0x10}, /* Enable 4 GPIOs */
    {0x21, 0x01, 0x10}, /* for Round Robin/Best Effort Forwarding */
    {0x20, 0x00, 0x10}, /* forwarding RX Port0~3 to CSI2 Port0 */

};

/*******************************************************************************
 *  Data structure's
 *******************************************************************************
 */

struct {

    UInt32                    maxCoarseIntgTime;
    /**< Max Coarse integration time supported by sensor */
    float                     lineIntgTimeInMs;
    /**< Line Integration time in ms */
    float                     pixIntgTimeInMs;
    /**< Pixel Integration time in ms */
} gImx390DeviceObj;

/*******************************************************************************
 *  Local Functions Declarations
 *******************************************************************************
 */
static Int32 IMX390_Start(UInt32 chId, IssSensor_CreateParams *pCreatePrms);
static Int32 IMX390_SetAeParams(IssSensor_CreateParams *pCreatePrms,
    IssSensor_AeParams *pAePrms);
static Int32 IMX390_GetDccParams(IssSensor_CreateParams *pCreatePrms,
    IssSensor_DccParams *pDccPrms);
static IMX390_GetExpParams(IssSensor_CreateParams *pCreatePrms,
    IssSensor_ExposureParams *pExpPrms);
static Void IMX390_InitAewbConfig(
    IssSensor_CreateParams *pCreatePrms,
    AlgorithmLink_IssAewbCreateParams *pAewbPrms);
static Void IMX390_GetIspConfig (
    IssSensor_CreateParams *pCreatePrms,
    IssIspConfigurationParameters *pIspCfg);
static Int32 IMX390_ReadWriteReg (
    IssSensor_CreateParams *pCreatePrms, UInt32 readWriteFlag,
    IssSensor_ReadWriteReg *pReg);

static Int32 IMX390_WriteReg(UInt8         i2cInstId,
                             UInt8         i2cAddr,
                             const UInt16 *regAddr,
                             const UInt8  *regVal,
                             UInt32        numRegs);
static Int32 IMX390_ReadReg(UInt8         i2cInstId,
                            UInt8         i2cAddr,
                            const UInt16 *regAddr,
                            UInt8        *regVal,
                            UInt32        numRegs);

/*******************************************************************************
 *  Globals
 *******************************************************************************
 */

/* \brief Sensor Params structure used for registering this sensor to chains_iss
 */
static IssSensorIf_Params SensorParams_Imx390 = {0};

static IssSensor_ConfigRegs gIMX390LinearConfig[] =
    IMX390_LINEAR_1920X1080_CONFIG;
static IssSensor_ConfigRegs gIMX390WDRConfig[] =
    IMX390_WDR_1920X1080_CONFIG;
/*
 * \brief Gain Table for IMX390
 */
static const UInt8 gIMX390GainsTable[] = IMX390_GAIN_TABLE;
/*
 * \brief DCC Parameters of IMX390
 */
static const UInt8 gImx390DccCfgLinear[] = IMX390DCC_CFG;

static const UInt8 gImx390DccCfgTwoPassWDR[] = IMX390_2PASSDCC_CFG;

/**
 * \brief Structure for ISP H3A AEWB engine parameters.
 */
static vpsissH3aAewbConfig_t aewbConfig_imx390 =
{
    FALSE, /* enableALowComp */
    FALSE, /* enableMedFilt */
    0xFFF, /* midFiltThreshold */
    {   /* vpsissH3aPaxelConfig_t      winCfg */
        {16u, 48u}, /* Fvid2_PosConfig pos */
        36u,     /* width */
        54u,     /* height */
        32u,     /* horzCount */
        16u,     /* vertCount */
        6,      /* horzIncr */
        6,      /* vertIncr */
    },
    958u,       /* Black Line Vertical Start */
    2u,         /* Black Line Width */
    VPS_ISS_H3A_OUTPUT_MODE_SUM_ONLY, /* vpsissH3aOutputMode_t outMode; */
    2,  /* sumShift */
    1023u, /* satLimit */
    VPS_ISS_H3A_MODE_NORMAL /* vpsissH3aMode_t mode */

} ;

static vpsissGlbceConfig_t glbceCfg_imx390 =
{
    TRUE,           /* ENABLE */
    240u,           /* IR Strength */
    0,              /* blackLevel */
    65535,          /* White Level */
    12,             /* Intensity variance */
    7,              /* Spacial variance */
    6,              /* Bright Amplification Limit */
    6,              /* Dark Amplification Limit */
    VPS_ISS_GLBCE_DITHER_FOUR_BIT,
    64,             /* MAX Slope Limit */
    72,             /* MIN Slope Limit */
    {
        0,5377,10218,14600,18585,22390,25561,28631,31466,34092,36530,
        38801,40921,42904,44764,46511,48156,49706,51171,52557,53870,55116,
        56299,57425,58498,59520,60497,61429,62322,63176,63995,64781,
        65535
    }
};

static vpsissGlbcePerceptConfig_t glbceFwbPerCfg_imx390 =
{
    TRUE,
    {
        0,4622,8653,11684,14195,16380,18335,20118,21766,23304,24751,
        26119,27422,28665,29857,31003,32108,33176,34209,35211,36185,
        37132,38055,38955,39834,40693,41533,42355,43161,43951,44727,
        45488,46236,46971,47694,48405,49106,49795,50475,51145,51805,
        52456,53099,53733,54360,54978,55589,56193,56789,57379,57963,
        58539,59110,59675,60234,60787,61335,61877,62414,62946,63473,
        63996,64513,65026,65535
    }
};

static vpsissGlbcePerceptConfig_t glbceRevPerCfg_imx390 =
{
    TRUE,
    {
        0,228,455,683,910,1138,1369,1628,1912,2221,2556,2916,3304,3717,
        4158,4626,5122,5645,6197,6777,7386,8024,8691,9387,10113,10869,
        11654,12471,13317,14194,15103,16042,17012,18014,19048,20113,21210,
        22340,23501,24696,25922,27182,28475,29800,31159,32552,33977,35437,
        36930,38458,40019,41615,43245,44910,46609,48343,50112,51916,53755,
        55630,57539,59485,61466,63482,65535
    }
};


/*******************************************************************************
 *  Function Definition
 *******************************************************************************
 */

Void IssSensor_IMX390_Init()
{
    Int32 status;
    IssSensorIf_Params *prms = &SensorParams_Imx390;
    IssSensor_Info *info = &SensorParams_Imx390.info;

    IssSensorIf_Params_Init(prms);

    strncpy(prms->name, SENSOR_SONY_IMX390_UB953_D3, ISS_SENSORS_MAX_NAME);

    prms->dccId             = 390;

    info->width             = 1920;
    info->height            = 1080;
    info->dataFormat        = SYSTEM_DF_BAYER_RGGB;
    info->bpp               = SYSTEM_BPP_BITS12;
    info->features          = ISS_SENSOR_IMX390_FEATURES;
    info->aewbMode          = ALGORITHMS_ISS_AEWB_MODE_AEWB;
    info->maxExp            = 1;
    info->ramOffset         = 26*1024*1024;

    prms->start             = IMX390_Start;
    prms->stop              = NULL;
    prms->setAeParams       = IMX390_SetAeParams;
    prms->getExpParams      = IMX390_GetExpParams;
    prms->getDccParams      = IMX390_GetDccParams;
    prms->initAewbConfig    = IMX390_InitAewbConfig;
    prms->getIspConfig      = IMX390_GetIspConfig;
    prms->readWriteReg      = IMX390_ReadWriteReg;

    status = IssSensorIf_RegisterSensor(prms);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    strncpy(prms->name, SENSOR_SONY_IMX390_AWR1243_UB953_D3, ISS_SENSORS_MAX_NAME);
    status = IssSensorIf_RegisterSensor(prms);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

}

/*******************************************************************************
 *  Local Functions Definition
 *******************************************************************************
 */
static Int32 IMX390_Start(UInt32 chId, IssSensor_CreateParams *pCreatePrms)
{
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;
    UInt32 cnt, i2cInstId, numRegs, features;
    UInt8 i2cAddr;
    UInt16 regAddr;
    UInt8 regValue;
    IssSensor_ConfigRegs *sensorCfg;

    UTILS_assert(NULL != pCreatePrms);

    i2cInstId = pCreatePrms->i2cInstId;
    i2cAddr = pCreatePrms->i2cAddr[chId];
    features = pCreatePrms->enableFeatures[chId];

    gImx390DeviceObj.lineIntgTimeInMs = 14.38f;
    gImx390DeviceObj.pixIntgTimeInMs = 0.0078f;
    gImx390DeviceObj.maxCoarseIntgTime = ISS_IMX390_MAX_INTG_LINES;
    if (ISS_SENSOR_FEATURE_LINEAR_MODE ==
             (features & ISS_SENSOR_FEATURE_LINEAR_MODE))
    {
        sensorCfg = gIMX390LinearConfig;
        numRegs = sizeof(gIMX390LinearConfig)/sizeof(IssSensor_ConfigRegs);
    }else
    {
        sensorCfg = gIMX390WDRConfig;
        numRegs = sizeof(gIMX390WDRConfig)/sizeof(IssSensor_ConfigRegs);
    }

    for (cnt = 0u; cnt < numRegs; cnt ++)
    {
        regAddr  = sensorCfg[cnt].regAddr;
        regValue = sensorCfg[cnt].regValue;
        /* Convert Registers address and value into 8bit array */
        status = IMX390_WriteReg(i2cInstId, i2cAddr, &regAddr,
            &regValue, 1u);

        if (SYSTEM_LINK_STATUS_SOK != status)
        {
            Vps_printf(" IMX390: Sensor RegWrite Failed for regAddr %x\n",
                regAddr);
            break;
        }
    }

    return (status);
}

static Int32 IMX390_SetAeParams(IssSensor_CreateParams *pCreatePrms,
    IssSensor_AeParams *pAePrms)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt16 regAddr[4];
    UInt8 regValue[4], i2cAddr;
    UInt32 i2cInstId, gainTblIdx;

    UTILS_assert(NULL != pAePrms);
    UTILS_assert(NULL != pCreatePrms);

    i2cInstId = pCreatePrms->i2cInstId;
    i2cAddr = pCreatePrms->i2cAddr[pAePrms->chId];

    /* Set Analog Gain first */
    gainTblIdx = (pAePrms->analogGain / ISS_IMX390_GAIN_TBL_STEP_SIZE) -
        ISS_IMX390_GAIN_TBL_STARTOFFSET;

    if (gainTblIdx >= ISS_IMX390_GAIN_TBL_SIZE)
    {
        gainTblIdx = ISS_IMX390_GAIN_TBL_SIZE - 1U;
    }

    /* Note: due to issues with hardware, the assertions are disabled resulting in occasional AE errors */
    regAddr[0] = 0x0008;
    regValue[0] = 1;
    //status = IMX390_WriteReg(i2cInstId, i2cAddr, regAddr, regValue, 1u);
    //UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    regAddr[0] = IMX390_SP1H_ANALOG_GAIN_CONTROL_REG_ADDR;
    regValue[0] = gIMX390GainsTable[gainTblIdx] & 0xFF;
    IMX390_WriteReg(i2cInstId, i2cAddr, regAddr, regValue, 1u);
    /* Note: removed status check */
    //status = IMX390_WriteReg(i2cInstId, i2cAddr, regAddr, regValue, 1u);
    //UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    regAddr[0] = IMX390_SP1H_ANALOG_GAIN_CONTROL_REG_ADDR_HIGH;
    regValue[0] = gIMX390GainsTable[gainTblIdx] >> 8;
    /* Note: removed status check */
    IMX390_WriteReg(i2cInstId, i2cAddr, regAddr, regValue, 1u);
    //status = IMX390_WriteReg(i2cInstId, i2cAddr, regAddr, regValue, 1u);
    //UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    regAddr[0] = 0x0008;
    regValue[0] = 0;
    //status = IMX390_WriteReg(i2cInstId, i2cAddr, regAddr, regValue, 1u);
    //UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    #if 0
    {
        float lineIntgTime;
        UInt32 lineIntgTimeU32;
        UInt16 shs_shortTmp;
        UInt32 shs_short;
        UInt32 frameSetCount;

        lineIntgTime = pAePrms->exposureTime[0] / gImx390DeviceObj.lineIntgTimeInMs;

        if (lineIntgTime > gImx390DeviceObj.maxCoarseIntgTime)
        {
            lineIntgTime = gImx390DeviceObj.maxCoarseIntgTime;
        }
        lineIntgTimeU32 = (UInt32)lineIntgTime;


        //hold register
        regAddr[0] = 0x0008;
        regValue[0] = 1;
        status = IMX390_WriteReg(i2cInstId, i2cAddr, regAddr, regValue, 1u);
        UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

        frameSetCount = IMX390_VMAX;
        shs_short = (frameSetCount - lineIntgTimeU32);
        shs_shortTmp = (UInt16)(shs_short & 0xFFU);
        regValue[0] = (UInt8)shs_shortTmp;
        regAddr[0] = (UInt16)IMX390_AE_CONTROL_LONG_REG_ADDR_LOW;
        status = IMX390_WriteReg(i2cInstId, i2cAddr, regAddr, regValue, 1u);
        UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

        regAddr[0] = (UInt16)IMX390_AE_CONTROL_LONG_REG_ADDR_HIGH;
        regValue[0] = (UInt8)((shs_short >> 8U) & 0xFFU);
        status = IMX390_WriteReg(i2cInstId, i2cAddr, regAddr, regValue, 1u);
        UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

        regAddr[0] = (UInt16)IMX390_AE_CONTROL_SHORT_REG_ADDR_MSB;
        regValue[0] = 0;//Forces short reg to match long reg(UInt8)((shs_short >> 16U) & 0x1U);
        status = IMX390_WriteReg(i2cInstId, i2cAddr, regAddr, regValue, 1u);
        UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

        regAddr[0] = (UInt16)IMX390_AE_CONTROL_SHORT_REG_ADDR_HIGH;
        regValue[0] = 0;//Forces short reg to match long reg(UInt8)((shs_short >> 16U) & 0x1U);
        status = IMX390_WriteReg(i2cInstId, i2cAddr, regAddr, regValue, 1u);
        UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

        regAddr[0] = (UInt16)IMX390_AE_CONTROL_SHORT_REG_ADDR_LOW;
        regValue[0] = 0;//Forces short reg to match long reg(UInt8)((shs_short >> 16U) & 0x1U);
        status = IMX390_WriteReg(i2cInstId, i2cAddr, regAddr, regValue, 1u);
        UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

        //hold register
        regAddr[0] = 0x0008;
        regValue[0] = 0;
        status = IMX390_WriteReg(i2cInstId, i2cAddr, regAddr, regValue, 1u);
        UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);
    }
    #endif

    return (status);
}

static Int32 IMX390_ReadReg(UInt8         i2cInstId,
                            UInt8         i2cAddr,
                            const UInt16 *regAddr,
                            UInt8        *regVal,
                            UInt32        numRegs)
{
    Int32  status = SYSTEM_LINK_STATUS_SOK;
    UInt32 cnt;
    UInt8  rawRegVal[3];

    for (cnt = 0; cnt < numRegs; cnt++)
    {
        /* Convert Registers address and value into 8bit array */
        rawRegVal[0U] = (UInt8) ((regAddr[cnt] >> 8U) & (UInt8) 0xFF);
        rawRegVal[1U] = (UInt8) ((regAddr[cnt] >> 0U) & (UInt8) 0xFF);

        status = Bsp_deviceRawWrite8(i2cInstId, i2cAddr, rawRegVal, 2u);

        if (FVID2_SOK == status)
        {
            status = Bsp_deviceRawRead8(i2cInstId, i2cAddr, &rawRegVal[2U],
                1u);

            regVal[cnt] = rawRegVal[2u];
        }
    }

    return (status);
}

static Int32 IMX390_WriteReg(UInt8         i2cInstId,
                             UInt8         i2cAddr,
                             const UInt16 *regAddr,
                             const UInt8  *regValue,
                             UInt32        numRegs)
{
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;
    UInt32 cnt;
    UInt8 rawRegVal[3];

    for (cnt = 0u; cnt < numRegs; cnt ++)
    {
        /* Convert Registers address and value into 8bit array */
        rawRegVal[0U] = (UInt8) ((regAddr[cnt] >> 8U) & (UInt8) 0xFF);
        rawRegVal[1U] = (UInt8) ((regAddr[cnt] >> 0U) & (UInt8) 0xFF);
        rawRegVal[2U] = (UInt8) ((regValue[cnt] >> 0U) & (UInt8) 0xFF);

        status = Bsp_deviceRawWrite8(i2cInstId, i2cAddr, rawRegVal, 3U);

        if (SYSTEM_LINK_STATUS_SOK != status)
        {
            break;
        }
    }

    return (status);
}

static IMX390_GetDccParams(IssSensor_CreateParams *pCreatePrms,
    IssSensor_DccParams *pDccPrms)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 features;
    
    UTILS_assert(NULL != pCreatePrms);
    UTILS_assert(NULL != pDccPrms);
    
    features = pCreatePrms->enableFeatures[pDccPrms->chId];
    if (ISS_SENSOR_FEATURE_LINEAR_MODE ==
             (features & ISS_SENSOR_FEATURE_LINEAR_MODE))
    {
        pDccPrms->dccCfgSize  = sizeof (gImx390DccCfgLinear);
        pDccPrms->pDccCfg     = (UInt8 *)gImx390DccCfgLinear;
    }else if (ISS_SENSOR_FEATURE_TWO_PASS_WDR_MODE ==
             (features & ISS_SENSOR_FEATURE_TWO_PASS_WDR_MODE))
    {
        pDccPrms->dccCfgSize  = sizeof (gImx390DccCfgTwoPassWDR);
        pDccPrms->pDccCfg     = (UInt8 *)gImx390DccCfgTwoPassWDR;
    }else
    {
        status = SYSTEM_LINK_STATUS_EFAIL;
    }

    return (status);
}

static IMX390_GetExpParams(IssSensor_CreateParams *pCreatePrms,
    IssSensor_ExposureParams *pExpPrms)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    UTILS_assert(NULL != pCreatePrms);
    UTILS_assert(NULL != pExpPrms);

    {
        pExpPrms->expRatio = ISS_SENSOR_IMX390_DEFAULT_EXP_RATIO;
    }

    return (status);
}

static Void IMX390_InitAewbConfig(
    IssSensor_CreateParams *pCreatePrms,
    AlgorithmLink_IssAewbCreateParams *pAewbPrms)
{
    AlgorithmLink_IssAewbAeDynamicParams *dynPrms = NULL;

    UTILS_assert(NULL != pAewbPrms);

    /* Set H3A Params */
    pAewbPrms->h3aParams.winCountH = aewbConfig_imx390.winCfg.horzCount;
    pAewbPrms->h3aParams.winCountV = aewbConfig_imx390.winCfg.vertCount;
    pAewbPrms->h3aParams.winSizeH  = aewbConfig_imx390.winCfg.width;
    pAewbPrms->h3aParams.winSizeV  = aewbConfig_imx390.winCfg.height;
    pAewbPrms->h3aParams.winSkipH  = aewbConfig_imx390.winCfg.horzIncr;
    pAewbPrms->h3aParams.winSkipV  = aewbConfig_imx390.winCfg.vertIncr;
    pAewbPrms->numH3aPlanes = 1u;

    pAewbPrms->dataFormat = SensorParams_Imx390.info.dataFormat;
    pAewbPrms->mode =
        (AlgorithmLink_IssAewbMode)SensorParams_Imx390.info.aewbMode;

    if (ISS_SENSOR_FEATURE_LINEAR_MODE ==
            (ISS_SENSOR_FEATURE_LINEAR_MODE&pCreatePrms->enableFeatures[0]))
    {
        pAewbPrms->isWdrEnable = FALSE;
    }
    else
    {
        pAewbPrms->isWdrEnable = TRUE;
    }

    pAewbPrms->dccCameraId = SensorParams_Imx390.dccId;

    dynPrms = &pAewbPrms->aeDynParams;

    dynPrms->targetBrightnessRange.min = 30;
    dynPrms->targetBrightnessRange.max = 45;
    dynPrms->targetBrightness = 35;
    dynPrms->threshold = 1;

#if 0
    dynPrms->exposureTimeRange[0].min = 100;
    dynPrms->exposureTimeRange[0].max = 8333;
    dynPrms->apertureLevelRange[0].min = 1;
    dynPrms->apertureLevelRange[0].max = 1;
    dynPrms->sensorGainRange[0].min = 1000;
    dynPrms->sensorGainRange[0].max = 1000;
    dynPrms->ipipeGainRange[0].min = 512;
    dynPrms->ipipeGainRange[0].max = 512;

    dynPrms->exposureTimeRange[1].min = 8333;
    dynPrms->exposureTimeRange[1].max = 8333;
    dynPrms->apertureLevelRange[1].min = 1;
    dynPrms->apertureLevelRange[1].max = 1;
    dynPrms->sensorGainRange[1].min = 1000;
    dynPrms->sensorGainRange[1].max = 2000;
    dynPrms->ipipeGainRange[1].min = 512;
    dynPrms->ipipeGainRange[1].max = 512;

    dynPrms->exposureTimeRange[2].min = 16666;
    dynPrms->exposureTimeRange[2].max = 30750;
    dynPrms->apertureLevelRange[2].min = 1;
    dynPrms->apertureLevelRange[2].max = 1;
    dynPrms->sensorGainRange[2].min = 1000;
    dynPrms->sensorGainRange[2].max = 1000;
    dynPrms->ipipeGainRange[2].min = 512;
    dynPrms->ipipeGainRange[2].max = 512;

    dynPrms->exposureTimeRange[3].min = 30750;
    dynPrms->exposureTimeRange[3].max = 30750;
    dynPrms->apertureLevelRange[3].min = 1;
    dynPrms->apertureLevelRange[3].max = 1;
    dynPrms->sensorGainRange[3].min = 1000;
    dynPrms->sensorGainRange[3].max = 160000;
    dynPrms->ipipeGainRange[3].min = 512;
    dynPrms->ipipeGainRange[3].max = 512;

    dynPrms->numAeDynParams = 4;
#else
    dynPrms->exposureTimeRange[0].min = 11000;
    dynPrms->exposureTimeRange[0].max = 11000;
    dynPrms->apertureLevelRange[0].min = 1;
    dynPrms->apertureLevelRange[0].max = 1;
    dynPrms->sensorGainRange[0].min = 1000;
    dynPrms->sensorGainRange[0].max = 160000;
    dynPrms->ipipeGainRange[0].min = 512;
    dynPrms->ipipeGainRange[0].max = 512;

    dynPrms->numAeDynParams = 1;
#endif

    dynPrms->exposureTimeStepSize = 1;

    dynPrms->enableBlc = FALSE;

    pAewbPrms->calbData = NULL;
}

static Void IMX390_GetIspConfig (
    IssSensor_CreateParams *pCreatePrms,
    IssIspConfigurationParameters *pIspCfg)
{
    UTILS_assert(NULL != pIspCfg);

    pIspCfg->aewbCfg = &aewbConfig_imx390;

    /* glbceCfg */
    pIspCfg->glbceCfg = &glbceCfg_imx390;

    /* fwdPerCfg */
    pIspCfg->glbceFwdPerCfg = &glbceFwbPerCfg_imx390;

    /* revPerCfg */
    pIspCfg->glbceRevPerCfg = &glbceRevPerCfg_imx390;
}

static Int32 IMX390_ReadWriteReg (
    IssSensor_CreateParams *pCreatePrms, UInt32 readWriteFlag,
    IssSensor_ReadWriteReg *pReg)
{
    Int32 status;
    UInt32 chId;
    UInt8 regValue;

    UTILS_assert(NULL != pReg);
    UTILS_assert(NULL != pReg);

    /* Assuming Channel Id as 0 */
    chId = pReg->chId;

    if (readWriteFlag)
    {
        regValue = pReg->regValue;
        status = IMX390_WriteReg(pCreatePrms->i2cInstId,
            pCreatePrms->i2cAddr[chId], &pReg->regAddr, &regValue, 1u);
    }
    else
    {
        status = IMX390_ReadReg(pCreatePrms->i2cInstId,
            pCreatePrms->i2cAddr[chId], &pReg->regAddr, &regValue, 1u);

        if (SYSTEM_LINK_STATUS_SOK == status)
        {
            pReg->regValue = regValue;
        }
    }

    return (status);
}
