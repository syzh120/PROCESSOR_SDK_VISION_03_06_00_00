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

 THIS SOFTWARE IS PROVIDED BY TI AND TI’S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI’S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/

/**
 *******************************************************************************
 * \file iss_sensor_ov2775.c
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
#include "iss_sensor_ov2775.h"
#include "ov2775_linear_1920x1080_setup.h"
#include "ov2775_dcc.h"

#include <ti/drv/vps/include/devices/bsp_device.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/* #define _USE_DIGITAL_GAIN_ */


#define ISS_SENSORS_OV2775_DEFAULT_EXP_RATIO    (16U)

#define ISS_SENSORS_OV2775_FEATURES     (ISS_SENSOR_FEATURE_MANUAL_EXPOSURE|   \
                                         ISS_SENSOR_FEATURE_MANUAL_GAIN|       \
                                         ISS_SENSOR_FEATURE_LINEAR_MODE|       \
                                         ISS_SENSOR_FEATURE_DCC_SUPPORTED)


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
} gOv2775DeviceObj;

/*******************************************************************************
 *  Local Functions Declarations
 *******************************************************************************
 */
static Int32 OV2775_Start(UInt32 chId, IssSensor_CreateParams *pCreatePrms);
static Int32 OV2775_Stop(UInt32 chId, IssSensor_CreateParams *pCreatePrms);
static Int32 OV2775_SetAeParams(IssSensor_CreateParams *pCreatePrms,
    IssSensor_AeParams *pAePrms);
static Int32 OV2775_GetDccParams(IssSensor_CreateParams *pCreatePrms,
    IssSensor_DccParams *pDccPrms);
static OV2775_GetExpParams(IssSensor_CreateParams *pCreatePrms,
    IssSensor_ExposureParams *pExpPrms);
static Void OV2775_InitAewbConfig(
    IssSensor_CreateParams *pCreatePrms,
    AlgorithmLink_IssAewbCreateParams *pAewbPrms);
static Void OV2775_GetIspConfig (
    IssSensor_CreateParams *pCreatePrms,
    IssIspConfigurationParameters *pIspCfg);
static Int32 OV2775_ReadWriteReg (
    IssSensor_CreateParams *pCreatePrms, UInt32 readWriteFlag,
    IssSensor_ReadWriteReg *pReg);

static Int32 OV2775_ReadReg(UInt8         i2cInstId,
                            UInt8         i2cAddr,
                            const UInt16 *regAddr,
                            UInt16       *regVal,
                            UInt32        numRegs);
static Int32 OV2775_WriteReg(UInt8         i2cInstId,
                             UInt8         i2cAddr,
                             const UInt16 *regAddr,
                             const UInt16 *regVal,
                             UInt32        numRegs);

/*******************************************************************************
 *  Globals
 *******************************************************************************
 */

/* \brief Sensor Params structure used for registering this sensor to chains_iss
 */
static IssSensorIf_Params SensorParams_Ov2775 = {0};

static const UInt8 gOv2775DccCfgLinearAndWdr[] = OV2775DCC_CFG;

static IssSensor_ConfigRegs gOV2775SensorsLinearConfig[] =
    OV2775_LINEAR_1920x1080_30FPS_CONFIG;

/**
 * \brief Structure for ISP H3A AEWB engine parameters.
 */
static vpsissH3aAewbConfig_t aewbConfig_ov2775 =
{
    FALSE, /* enableALowComp */
    FALSE, /* enableMedFilt */
    0xFFF, /* midFiltThreshold */
    {   /* vpsissH3aPaxelConfig_t      winCfg */
        {0u, 2u}, /* Fvid2_PosConfig pos */
        40u,     /* width */
        24u,     /* height */
        32u,     /* horzCount */
        33u,    /* vertCount */
        2,      /* horzIncr */
        8,      /* vertIncr */
    },
    1078,       /* Black Line Vertical Start */
    2u,         /* Black Line Width */
    VPS_ISS_H3A_OUTPUT_MODE_SUM_ONLY, /* vpsissH3aOutputMode_t outMode; */
    0,  /* sumShift */
    992u, /* satLimit */
    VPS_ISS_H3A_MODE_NORMAL /* vpsissH3aMode_t mode */
} ;

/**
 * \brief Structure for ISP GLBCE WDR Params.
 */
static vpsissGlbceWdrConfig_t glbceWdrCfg_ov2775 =
{
    TRUE,
    {
        0U,24U,64U,114U,172U,237U,307U,383U,464U,549U,638U,731U,828U,928U,
        1031U,1138U,1248U,1361U,1477U,1596U,1717U,1841U,1967U,2096U,2228U,
        2361U,2498U,2636U,2777U,2919U,3064U,3211U,3360U,3511U,3664U,3819U,
        3976U,4134U,4295U,4457U,4622U,4787U,4955U,5125U,5296U,5468U,5643U,
        5819U,5997U,6176U,6357U,6539U,6723U,6908U,7095U,7284U,7474U,7665U,
        7858U,8052U,8248U,8445U,8644U,8843U,9045U,9247U,9451U,9656U,9863U,
        10071U,10280U,10490U,10702U,10915U,11129U,11345U,11561U,11779U,11998U,
        12219U,12440U,12663U,12887U,13112U,13338U,13566U,13794U,14024U,14255U,
        14487U,14720U,14954U,15189U,15426U,15663U,15902U,16142U,16382U,16624U,
        16867U,17111U,17356U,17602U,17849U,18097U,18346U,18596U,18847U,19099U,
        19353U,19607U,19862U,20118U,20375U,20633U,20892U,21152U,21413U,21675U,
        21938U,22202U,22467U,22732U,22999U,23267U,23535U,23805U,24075U,24346U,
        24618U,24891U,25165U,25440U,25716U,25993U,26270U,26549U,26828U,27108U,
        27389U,27671U,27954U,28238U,28522U,28807U,29094U,29381U,29669U,29957U,
        30247U,30537U,30829U,31121U,31414U,31707U,32002U,32297U,32593U,32890U,
        33188U,33487U,33786U,34086U,34387U,34689U,34992U,35295U,35599U,35904U,
        36210U,36516U,36823U,37132U,37440U,37750U,38060U,38371U,38683U,38996U,
        39309U,39623U,39938U,40254U,40570U,40887U,41205U,41523U,41843U,42163U,
        42483U,42805U,43127U,43450U,43774U,44098U,44423U,44749U,45075U,45403U,
        45731U,46059U,46389U,46719U,47049U,47381U,47713U,48046U,48379U,48714U,
        49048U,49384U,49720U,50057U,50395U,50733U,51072U,51412U,51752U,52093U,
        52435U,52777U,53121U,53464U,53809U,54154U,54499U,54846U,55193U,55540U,
        55889U,56238U,56587U,56938U,57289U,57640U,57992U,58345U,58699U,59053U,
        59408U,59763U,60119U,60476U,60833U,61191U,61550U,61909U,62269U,62629U,
        62990U,63352U,63714U,64077U,64441U,64805U,65170U,65535U
    }
};

#define TIDA1130_OV2775_SER_ADDR                    (0x18U)
/**< Serializer address */
#define TIDA1130_OV2775_SENSOR_ADDR                 (0x36U)
/**< Sensor address */

BspUtils_Ub960I2cParams gUB953_OV2775_TIDA1130_SerCfg[OV2775_TIDA1130_SER_CFG_SIZE] = {
    /* Setup for OV2775 to UB953 on 2/4 lanes */
    {0x02, 0x52, 0x10},

    {0x06, 0x21, 0x1},
    {0x07, 0x28, 0x1},

    {0x0E, 0xF0, 0x1},
    {0x0D, 0x00, 0x1},
    {0x0D, 0x0C, 0x1},
};

BspUtils_Ub960I2cParams gAppIssUtilsUb960Cfg_OV2775_TIDA1130_DesCfg[OV2775_TIDA1130_DES_CFG_SIZE] = {
    /* Setup for OV2775 to UB953 on 2 lanes */
    {0x0C, 0x0F, 0x10},
    {0x1F, 0x00, 0x10}, /* 1.6Gbps CSI Freq */

    /*CAMERA 1*/
    {0x4C, 0x01, 0x1},        /*Page FPD3 port RX0 registers for R/W*/
    {0x58, 0x5D , 0x1},        /*Enable and set backchannel rate to 50Mbs / I2C passthrough enabled*/
    {0x5C, 0x30, 0x1},        /*set serializer alias to Ox18 (7-bit)*/
    {0x5D, ((uint8_t) (TIDA1130_OV2775_SER_ADDR << 1U)), 0x0},
    {0x65, ((uint8_t) (PORT_0_SER_ADDR << 1U)), 0x0},
    {0x5E, ((uint8_t) (TIDA1130_OV2775_SENSOR_ADDR << 1U)), 0x0},
    {0x66, ((uint8_t) (PORT_0_SENSOR_ADDR << 1U)), 0x0},
    {0x6D, 0x7C, 0x1},        /*CSI and coax mode*/
    {0xD5, 0xF0, 0x1},       /* Set AEQ MIN/MAX widest values*/
    {0x7C, 0x01, 0x1},        /*same as Omnivision*/
    {0x70, 0x2B, 0x1},        /*same as Omnivision*/
    {0x71, 0x2C, 0x1},        /*same as Omnivision*/
    {0x72, 0xE4, 0x1},        /*same as Omnivision*/

     /*CAMERA 2*/
    {0x4C, 0x12, 0x1},        /*Page FPD3 port RX0 registers for R/W*/
    {0x58, 0x5D , 0x1},        /*Enable and set backchannel rate to 50Mbs / I2C passthrough enabled*/
    {0x5C, 0x30, 0x1},        /*set serializer alias to Ox18 (7-bit)*/
    {0x5D, ((uint8_t) (TIDA1130_OV2775_SER_ADDR << 1U)), 0x0},
    {0x65, ((uint8_t) (PORT_1_SER_ADDR << 1U)), 0x0},
    {0x5E, ((uint8_t) (TIDA1130_OV2775_SENSOR_ADDR << 1U)), 0x0},
    {0x66, ((uint8_t) (PORT_1_SENSOR_ADDR << 1U)), 0x0},
    {0x6D, 0x7C, 0x1},        /*CSI and coax mode*/
    {0xD5, 0xF0, 0x1},       /* Set AEQ MIN/MAX widest values*/
    {0x7C, 0x01, 0x1},        /*same as Omnivision*/
    {0x70, 0x2B, 0x1},        /*same as Omnivision*/
    {0x71, 0x2C, 0x1},        /*same as Omnivision*/
    {0x72, 0x39, 0x1},        /*same as Omnivision*/

      /*CAMERA 3*/
    {0x4C, 0x24, 0x1},        /*Page FPD3 port RX0 registers for R/W*/
    {0x58, 0x5D , 0x1},        /*Enable and set backchannel rate to 50Mbs / I2C passthrough enabled*/
    {0x5C, 0x30, 0x1},        /*set serializer alias to Ox18 (7-bit)*/
    {0x5D, ((uint8_t) (TIDA1130_OV2775_SER_ADDR << 1U)), 0x0},
    {0x65, ((uint8_t) (PORT_2_SER_ADDR << 1U)), 0x0},
    {0x5E, ((uint8_t) (TIDA1130_OV2775_SENSOR_ADDR << 1U)), 0x0},
    {0x66, ((uint8_t) (PORT_2_SENSOR_ADDR << 1U)), 0x0},
    {0x6D, 0x7C, 0x1},        /*CSI and coax mode*/
    {0xD5, 0xF0, 0x1},       /* Set AEQ MIN/MAX widest values*/
    {0x7C, 0x01, 0x1},        /*same as Omnivision*/
    {0x70, 0x2B, 0x1},        /*same as Omnivision*/
    {0x71, 0x2C, 0x1},        /*same as Omnivision*/
    {0x72, 0x4e, 0x1},        /*same as Omnivision*/

     /*CAMERA 4*/
    {0x4C, 0x38, 0x1},        /*Page FPD3 port RX0 registers for R/W*/
    {0x58, 0x5D , 0x1},        /*Enable and set backchannel rate to 50Mbs / I2C passthrough enabled*/
    {0x5C, 0x30, 0x1},        /*set serializer alias to Ox18 (7-bit)*/
    {0x5D, ((uint8_t) (TIDA1130_OV2775_SER_ADDR << 1U)), 0x0},
    {0x65, ((uint8_t) (PORT_3_SER_ADDR << 1U)), 0x0},
    {0x5E, ((uint8_t) (TIDA1130_OV2775_SENSOR_ADDR << 1U)), 0x0},
    {0x66, ((uint8_t) (PORT_3_SENSOR_ADDR << 1U)), 0x0},
    {0x6D, 0x7C, 0x1},        /*CSI and coax mode*/
    {0xD5, 0xF0, 0x1},       /* Set AEQ MIN/MAX widest values*/
    {0x7C, 0x01, 0x1},        /*same as Omnivision*/
    {0x70, 0x2B, 0x1},        /*same as Omnivision*/
    {0x71, 0x2C, 0x1},        /*same as Omnivision*/
    {0x72, 0x93, 0x1},        /*same as Omnivision*/

    {0x32, 0x01, 0x1},        /*CSI0 select*/
    {0x33, 0x03, 0x1},        /*CSI_EN & CSI0 4L*/

    {0x21, 0x03, 0x1},
    {0x20, 0x00, 0x1},

    {0xB9, 0x18, 0x1},        /*ENABLE PARITY ERROR COUNT*/
    {0x42, 0x71, 0x1},        /*ENABLE S-Filter with AEQ*/
    {0x10, 0x59, 0x1},        /*Output Frame on GPIO0 */
};


/*******************************************************************************
 *  Function Definition
 *******************************************************************************
 */

Void IssSensor_OV2775_Init()
{
    Int32 status;
    IssSensorIf_Params *prms = &SensorParams_Ov2775;
    IssSensor_Info *info = &SensorParams_Ov2775.info;

    IssSensorIf_Params_Init(prms);

    strncpy(prms->name, SENSOR_OMNIVISION_OV2775_CSI2, ISS_SENSORS_MAX_NAME);

    prms->dccId             = 2775;

    info->width             = SENSOR_OV2775_NATIVE_WIDTH;
    info->height            = SENSOR_OV2775_NATIVE_HEIGHT;
    info->dataFormat        = SYSTEM_DF_BAYER_BGGR;
    info->bpp               = SYSTEM_BPP_BITS12;
    info->features          = ISS_SENSORS_OV2775_FEATURES;
    info->aewbMode          = ALGORITHMS_ISS_AEWB_MODE_AEWB;
    info->maxExp            = 1;
    info->ramOffset         = 24*1024*1024;

    prms->start             = OV2775_Start;
    prms->stop              = OV2775_Stop;
    prms->setAeParams       = OV2775_SetAeParams;
    prms->getExpParams      = OV2775_GetExpParams;
    prms->getDccParams      = OV2775_GetDccParams;
    prms->initAewbConfig    = OV2775_InitAewbConfig;
    prms->getIspConfig      = OV2775_GetIspConfig;
    prms->readWriteReg      = OV2775_ReadWriteReg;

    status = IssSensorIf_RegisterSensor(prms);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);
}

Void IssSensor_OV2775_Tida1130_Init()
{
    Int32 status;
    IssSensorIf_Params *prms = &SensorParams_Ov2775;
    IssSensor_Info *info = &SensorParams_Ov2775.info;

    IssSensorIf_Params_Init(prms);

    strncpy(prms->name, SENSOR_OMNIVISION_OV2775_TIDA1130, ISS_SENSORS_MAX_NAME);

    prms->dccId             = 2775;

    info->width             = SENSOR_OV2775_NATIVE_WIDTH;
    info->height            = SENSOR_OV2775_NATIVE_HEIGHT;
    info->dataFormat        = SYSTEM_DF_BAYER_BGGR;
    info->bpp               = SYSTEM_BPP_BITS12;
    info->features          = ISS_SENSORS_OV2775_FEATURES;
    info->aewbMode          = ALGORITHMS_ISS_AEWB_MODE_AEWB;
    info->maxExp            = 1;
    info->ramOffset         = 24*1024*1024;

    prms->start             = OV2775_Start;
    prms->stop              = OV2775_Stop;
    prms->setAeParams       = OV2775_SetAeParams;
    prms->getExpParams      = OV2775_GetExpParams;
    prms->getDccParams      = OV2775_GetDccParams;
    prms->initAewbConfig    = OV2775_InitAewbConfig;
    prms->getIspConfig      = OV2775_GetIspConfig;
    prms->readWriteReg      = OV2775_ReadWriteReg;

    status = IssSensorIf_RegisterSensor(prms);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);
}


/*******************************************************************************
 *  Local Functions Definition
 *******************************************************************************
 */

static Int32 OV2775_Start(UInt32 chId, IssSensor_CreateParams *pCreatePrms)
{
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;
    UInt32 cnt, i2cInstId, features, numRegs;
    UInt8 i2cAddr;
    UInt16 regAddr, regValue, delay;
    IssSensor_ConfigRegs *sensorRegs;

    UTILS_assert(NULL != pCreatePrms);

    i2cInstId = pCreatePrms->i2cInstId;
    i2cAddr = pCreatePrms->i2cAddr[chId];
    features = pCreatePrms->enableFeatures[chId];

    if (ISS_SENSOR_FEATURE_LINEAR_MODE ==
        (features & ISS_SENSOR_FEATURE_LINEAR_MODE))
    {
        sensorRegs = gOV2775SensorsLinearConfig;
        numRegs = sizeof(gOV2775SensorsLinearConfig)/
            sizeof(IssSensor_ConfigRegs);

        gOv2775DeviceObj.maxCoarseIntgTime =
            SENSOR_OV2775_MAX_EXP_ROWS;
    }
    else
    {
/*TBD : Assert*/
    }
    gOv2775DeviceObj.lineIntgTimeInMs = 32.4f;
    gOv2775DeviceObj.pixIntgTimeInMs  = 0.0169f;


    for (cnt = 0u; cnt < numRegs; cnt ++)
    {
        regAddr  = sensorRegs[cnt].regAddr;
        regValue = sensorRegs[cnt].regValue;
        delay = sensorRegs[cnt].delay;

        /* Convert Registers address and value into 8bit array */
        status = OV2775_WriteReg(i2cInstId, i2cAddr, &regAddr,
            &regValue, 1u);

        Task_sleep(delay);

        if (SYSTEM_LINK_STATUS_SOK != status)
        {
            break;
        }
    }

    return (status);
}


static Int32 OV2775_Stop(UInt32 chId,
    IssSensor_CreateParams *pCreatePrms)
{
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;


    status = SYSTEM_LINK_STATUS_SOK;
    return (status);
}

static Int32 OV2775_SetAeParams(IssSensor_CreateParams *pCreatePrms,
    IssSensor_AeParams *pAePrms)
{
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;
    UInt32 chId;
    UInt16 regAddr, regValue;
    UInt32 nValueTemp;
    UInt8 nValue;
    UInt8 longAnalogGain;
    UInt8 shortAnalogGain;

    UTILS_assert(NULL != pCreatePrms);
    UTILS_assert(NULL != pAePrms);

    chId = pAePrms->chId;
    regAddr = SENSOR_OV2775_DCG_CEXP_REG_H;
    regValue = (UInt16) (pAePrms->exposureTime[0] /
        gOv2775DeviceObj.lineIntgTimeInMs);

    if (regValue > gOv2775DeviceObj.maxCoarseIntgTime)
    {
        regValue = gOv2775DeviceObj.maxCoarseIntgTime;
    }

    /* Convert Registers address and value into 8bit array */
    status = OV2775_WriteReg(pCreatePrms->i2cInstId,
        pCreatePrms->i2cAddr[chId], &regAddr, &regValue, 1u);

    if (SYSTEM_LINK_STATUS_SOK == status)
    {
        nValueTemp =  (pAePrms->analogGain)/1000U;
        nValue = (UInt8) nValueTemp;

        if(nValue >= (UInt8) 8U)
        {
                longAnalogGain       = (UInt8) 3U;
        }
        else if(nValue >= (UInt8) 4U)
        {
                longAnalogGain      = (UInt8) 2U;
        }
        else if(nValue >= (UInt8) 2U)
        {
                longAnalogGain      = (UInt8) 1U;
        }
        else
        {
                longAnalogGain      = (UInt8) 0;
        }

        shortAnalogGain = longAnalogGain;

        /* Write CG_AGAIN register*/
        regAddr = SENSOR_OV2775_ANALOG_GAIN_REG;
        regValue = (UInt8) (longAnalogGain | (shortAnalogGain<<2) );

        status = OV2775_WriteReg(pCreatePrms->i2cInstId,
        pCreatePrms->i2cAddr[chId], &regAddr, &regValue, 1u);

    }

    return (status);
}

static Int32 OV2775_ReadReg(UInt8         i2cInstId,
                                    UInt8         i2cAddr,
                                    const UInt16 *regAddr,
                                    UInt16       *regVal,
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

static Int32 OV2775_WriteReg(UInt8         i2cInstId,
                             UInt8         i2cAddr,
                             const UInt16 *regAddr,
                             const UInt16 *regValue,
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

static OV2775_GetDccParams(IssSensor_CreateParams *pCreatePrms,
    IssSensor_DccParams *pDccPrms)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
/*    UInt32 features;*/

    UTILS_assert(NULL != pCreatePrms);
    UTILS_assert(NULL != pDccPrms);

/*    features = pCreatePrms->enableFeatures[pDccPrms->chId];*/
    pDccPrms->pDccCfg = (UInt8 *)gOv2775DccCfgLinearAndWdr;
    pDccPrms->dccCfgSize = sizeof(gOv2775DccCfgLinearAndWdr);

    return (status);
}

static OV2775_GetExpParams(IssSensor_CreateParams *pCreatePrms,
    IssSensor_ExposureParams *pExpPrms)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 chId;
    UInt16 regAddr, regValue;

    UTILS_assert(NULL != pCreatePrms);
    UTILS_assert(NULL != pExpPrms);

    regAddr = 0x30B6U;

    chId = pExpPrms->chId;

    /* Convert Registers address and value into 8bit array */
    status = OV2775_ReadReg(pCreatePrms->i2cInstId,
        pCreatePrms->i2cAddr[chId], &regAddr, &regValue, 1u);

    if (SYSTEM_LINK_STATUS_SOK == status)
    {
        pExpPrms->expRatio = ISS_SENSORS_OV2775_DEFAULT_EXP_RATIO;
        pExpPrms->exposureTime[chId] = regValue *
            gOv2775DeviceObj.lineIntgTimeInMs;
    }
    return (status);
}

static Void OV2775_InitAewbConfig(
    IssSensor_CreateParams *pCreatePrms,
    AlgorithmLink_IssAewbCreateParams *pAewbPrms)
{
    AlgorithmLink_IssAewbAeDynamicParams *dynPrms = NULL;

    UTILS_assert(NULL != pCreatePrms);
    UTILS_assert(NULL != pAewbPrms);

    /* Set H3A Params */
    pAewbPrms->h3aParams.winCountH = aewbConfig_ov2775.winCfg.horzCount;
    pAewbPrms->h3aParams.winCountV = aewbConfig_ov2775.winCfg.vertCount;
    pAewbPrms->h3aParams.winSizeH  = aewbConfig_ov2775.winCfg.width;
    pAewbPrms->h3aParams.winSizeV  = aewbConfig_ov2775.winCfg.height;
    pAewbPrms->h3aParams.winSkipH  = aewbConfig_ov2775.winCfg.horzIncr;
    pAewbPrms->h3aParams.winSkipV  = aewbConfig_ov2775.winCfg.vertIncr;
    pAewbPrms->numH3aPlanes = 1u;

    pAewbPrms->dataFormat = SensorParams_Ov2775.info.dataFormat;
    pAewbPrms->mode = (AlgorithmLink_IssAewbMode)SensorParams_Ov2775.info.aewbMode;

    /* Using Channel Id 9 */
    if (ISS_SENSOR_FEATURE_LINEAR_MODE ==
            (ISS_SENSOR_FEATURE_LINEAR_MODE&pCreatePrms->enableFeatures[0]))
    {
        pAewbPrms->isWdrEnable = FALSE;
    }

    pAewbPrms->dccCameraId = SensorParams_Ov2775.dccId;

    dynPrms = &pAewbPrms->aeDynParams;

    dynPrms->targetBrightnessRange.min = 35;
    dynPrms->targetBrightnessRange.max = 45;
    dynPrms->targetBrightness = 40;
    dynPrms->threshold = 5;

    dynPrms->exposureTimeRange[0].min = 100;
    dynPrms->exposureTimeRange[0].max = 33333;
    dynPrms->apertureLevelRange[0].min = 1;
    dynPrms->apertureLevelRange[0].max = 1;
    dynPrms->sensorGainRange[0].min = 1000;
    dynPrms->sensorGainRange[0].max = 1000;
    dynPrms->ipipeGainRange[0].min = 512;
    dynPrms->ipipeGainRange[0].max = 512;

    dynPrms->exposureTimeRange[1].min = 16666;
    dynPrms->exposureTimeRange[1].max = 33333;
    dynPrms->apertureLevelRange[1].min = 1;
    dynPrms->apertureLevelRange[1].max = 1;
    dynPrms->sensorGainRange[1].min = 2000;
    dynPrms->sensorGainRange[1].max = 2000;
    dynPrms->ipipeGainRange[1].min = 512;
    dynPrms->ipipeGainRange[1].max = 512;

    dynPrms->exposureTimeRange[2].min = 16666;
    dynPrms->exposureTimeRange[2].max = 33333;
    dynPrms->apertureLevelRange[2].min = 1;
    dynPrms->apertureLevelRange[2].max = 1;
    dynPrms->sensorGainRange[2].min = 4000;
    dynPrms->sensorGainRange[2].max = 4000;
    dynPrms->ipipeGainRange[2].min = 512;
    dynPrms->ipipeGainRange[2].max = 512;


    dynPrms->exposureTimeRange[3].min = 16666;
    dynPrms->exposureTimeRange[3].max = 33333;
    dynPrms->apertureLevelRange[3].min = 1;
    dynPrms->apertureLevelRange[3].max = 1;
    dynPrms->sensorGainRange[3].min = 8000;
    dynPrms->sensorGainRange[3].max = 8000;
    dynPrms->ipipeGainRange[3].min = 512;
    dynPrms->ipipeGainRange[3].max = 512;

    dynPrms->numAeDynParams = 4;
    dynPrms->exposureTimeStepSize = 1;
    dynPrms->enableBlc = TRUE;
    pAewbPrms->calbData = NULL;

}
static Void OV2775_GetIspConfig (
    IssSensor_CreateParams *pCreatePrms,
    IssIspConfigurationParameters *pIspCfg)
{
    UInt32 chId;

    UTILS_assert(NULL != pIspCfg);
    UTILS_assert(NULL != pCreatePrms);

    /* Assuming Channel Id as 0 */
    chId = 0;

    /* Override common settings for specific sensor */
    pIspCfg->aewbCfg = &aewbConfig_ov2775;

    if (ISS_SENSOR_FEATURE_ONE_PASS_WDR_MODE ==
            (ISS_SENSOR_FEATURE_ONE_PASS_WDR_MODE &
                pCreatePrms->enableFeatures[chId]))
    {
        /* WDR Config */
        pIspCfg->glbceWdrCfg = &glbceWdrCfg_ov2775;
    }
}

static Int32 OV2775_ReadWriteReg (
    IssSensor_CreateParams *pCreatePrms, UInt32 readWriteFlag,
    IssSensor_ReadWriteReg *pReg)
{
    Int32 status;
    UInt32 chId;

    UTILS_assert(NULL != pReg);
    UTILS_assert(NULL != pReg);

    /* Assuming Channel Id as 0 */
    chId = pReg->chId;

    if (readWriteFlag)
    {
        status = OV2775_WriteReg(pCreatePrms->i2cInstId,
            pCreatePrms->i2cAddr[chId], &pReg->regAddr, &pReg->regValue, 1u);
    }
    else
    {
        status = OV2775_ReadReg(pCreatePrms->i2cInstId,
            pCreatePrms->i2cAddr[chId], &pReg->regAddr, &pReg->regValue, 1u);
    }

    return (status);
}
