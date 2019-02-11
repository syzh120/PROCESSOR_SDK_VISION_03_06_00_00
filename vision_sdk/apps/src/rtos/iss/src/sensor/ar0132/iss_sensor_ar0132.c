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
 * \file iss_sensor_ar0132.c
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
/**< ISS AEWB plugin is included here to get the default AEWB configuration
     from each sensor */
#include <algorithmLink_issAewb.h>
#include "ar0132_dcc.h"
#include "ar0132_wdr_720p60_setup.h"


#include <ti/drv/vps/include/devices/bsp_device.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */
/*
 * \brief Capabilites of AR0132
 */
#define ISS_SENSORS_AR0132_FEATURES     (ISS_SENSOR_FEATURE_HFLIP|             \
                                         ISS_SENSOR_FEATURE_VFLIP|             \
                                         ISS_SENSOR_FEATURE_LINEAR_MODE|       \
                                         ISS_SENSOR_FEATURE_TWO_PASS_WDR_MODE| \
					 ISS_SENSOR_FEATURE_ONE_PASS_WDR_MODE| \
                                         ISS_SENSOR_FEATURE_DCC_SUPPORTED)
/*
 * \brief Default exposure ratio
 */
#define ISS_SENSORS_AR0132_DEFAULT_EXP_RATIO    (256U)

/*******************************************************************************
 *  Data structure's
 *******************************************************************************
 */

struct {
    float                     lineIntgTimeInMs;
    /**< Line Integration time in ms. Standard / constant time for 1 line */
    float                     pixIntgTimeInMs;
    /**< Pixel Integration time in ms. Standard / constant time for x pixels */
} gAr0132DeviceObj;

/*******************************************************************************
 *  Local Functions Declarations
 *******************************************************************************
 */
static Int32 AR0132_Start(UInt32 chId, IssSensor_CreateParams *pCreatePrms);
static Int32 AR0132_Stop(UInt32 chId, IssSensor_CreateParams *pCreatePrms);
static Int32 AR0132_GetExpParams(IssSensor_CreateParams *pCreatePrms,
                                    IssSensor_ExposureParams *pExpPrms);
static AR0132_GetDccParams(IssSensor_CreateParams *pCreatePrms,
                            IssSensor_DccParams *pDccPrms);
static Void AR0132_InitAewbConfig(IssSensor_CreateParams *pCreatePrms,
                                AlgorithmLink_IssAewbCreateParams *pAewbPrms);
static Void AR0132_GetIspConfig (IssSensor_CreateParams *pCreatePrms,
                                    IssIspConfigurationParameters *pIspCfg);
static Int32 AR0132_ReadWriteReg (
    IssSensor_CreateParams *pCreatePrms, UInt32 readWriteFlag,
    IssSensor_ReadWriteReg *pReg);

static Int32 AR0132_ReadReg(UInt8         i2cInstId,
                            UInt8         i2cAddr,
                            const UInt16 *regAddr,
                            UInt16       *regVal,
                            UInt32        numRegs);
static Int32 AR0132_WriteReg(UInt8         i2cInstId,
                             UInt8         i2cAddr,
                             const UInt16 *regAddr,
                             const UInt16 *regValue,
                             UInt32        numRegs);


/*******************************************************************************
 *  Globals
 *******************************************************************************
 */

/*
 * \brief Sensor Params structure used for registering this sensor to
 *          chains_iss, with this sensor's capabilities
 */
static IssSensorIf_Params gSensorParamsAr0130 = {0};
/*
 * \brief DCC Parameters of AR0132
 */
static const UInt8 gAr0132DccCfgWdr[] = AR0132DCC_CFG;
/*
 * \brief Sensor register configurations
 */
static IssSensor_ConfigRegs gAR0132SensorsWdrConfig[] =
                                            AR01320_WDR_1280X720_P60_CONFIG;

/**
 * \brief Structure for ISP H3A AEWB engine parameters.
 */
static vpsissH3aAewbConfig_t aewbConfig_ar0132 =
{
    FALSE, /* enableALowComp */
    FALSE, /* enableMedFilt */
    0xFFF, /* midFiltThreshold */
    {   /* vpsissH3aPaxelConfig_t      winCfg */
        {32u, 16u}, /* Fvid2_PosConfig pos */
        64u,     /* width */
        24u,     /* height */
        16u,     /* horzCount */
        28u,     /* vertCount */
        4,      /* horzIncr */
        4,      /* vertIncr */
    },
    718U,       /* Black Line Vertical Start */
    2U,         /* Black Line Height */
    VPS_ISS_H3A_OUTPUT_MODE_SUM_ONLY, /* vpsissH3aOutputMode_t outMode; */
    2,  /* sumShift */
    1023u, /* satLimit */
    VPS_ISS_H3A_MODE_NORMAL /* vpsissH3aMode_t mode */

};

static vpsissGlbceConfig_t glbceCfg_ar0132 =
{
    TRUE,           /* ENABLE */
    255,            /* IR Strength */
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
        0,5377,10218,14600,18585,22224,25561,28631,31466,34092,36530,
        38801,40921,42904,44764,46511,48156,49706,51171,52557,53870,
        55116,56299,57425,58498,59520,60497,61429,62322,63176,63995,
        64781,65535
    }
};

static vpsissGlbcePerceptConfig_t glbceFwbPerCfg_ar0132 =
{
    FALSE,
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

static vpsissGlbcePerceptConfig_t glbceRevPerCfg_ar0132 =
{
    FALSE,
    {
        0,228,455,683,910,1138,1369,1628,1912,2221,2556,2916,3304,3717,
        4158,4626,5122,5645,6197,6777,7386,8024,8691,9387,10113,10869,
        11654,12471,13317,14194,15103,16042,17012,18014,19048,20113,21210,
        22340,23501,24696,25922,27182,28475,29800,31159,32552,33977,
        35437,36930,38458,40019,41615,43245,44910,46609,48343,50112,
        51916,53755,55630,57539,59485,61466,63482,65535
    }
};

static vpsissIpipeInConfig_t ipipeInputCfg_ar132 =
    {VPS_ISS_IPIPE_DATA_PATH_RAW_YUV422, 0, 2, 1280, 718};

/*******************************************************************************
 *  Function Definition
 *******************************************************************************
 */

Void IssSensor_AR0132_Init()
{
    IssSensorIf_Params *prms = &gSensorParamsAr0130;
    IssSensor_Info *info = &gSensorParamsAr0130.info;

    IssSensorIf_Params_Init(prms);

    strncpy(prms->name, SENSOR_APTINA_AR0132, ISS_SENSORS_MAX_NAME);

    prms->dccId             = 132;

    info->width             = 1280;
    info->height            = 720;
    info->dataFormat        = SYSTEM_DF_BAYER_GRBG;
    info->bpp               = SYSTEM_BPP_BITS12;
    info->features          = ISS_SENSORS_AR0132_FEATURES;
    info->aewbMode          = ALGORITHMS_ISS_AEWB_MODE_AWB;
    info->maxExp            = 1;
    info->ramOffset         = 24*1024*1024;

    prms->start             = AR0132_Start;
    prms->stop              = AR0132_Stop;
    prms->setAeParams       = NULL;
    prms->getExpParams      = AR0132_GetExpParams;
    prms->getDccParams      = AR0132_GetDccParams;
    prms->initAewbConfig    = AR0132_InitAewbConfig;
    prms->getIspConfig      = AR0132_GetIspConfig;
    prms->readWriteReg      = AR0132_ReadWriteReg;

    IssSensorIf_RegisterSensor(prms);
}

/*******************************************************************************
 *  Local Functions Definition
 *******************************************************************************
 */

static Int32 AR0132_Start(UInt32 chId, IssSensor_CreateParams *pCreatePrms)
{
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;
    UInt32 cnt, i2cInstId, numRegs, numSensRegs;
    UInt8 i2cAddr;
    UInt16 regAddr, regValue;
    IssSensor_ConfigRegs *sensorRegs;

    UTILS_assert(NULL != pCreatePrms);

    i2cInstId = pCreatePrms->i2cInstId;
    i2cAddr = pCreatePrms->i2cAddr[chId];

    sensorRegs = gAR0132SensorsWdrConfig;
    numRegs = sizeof(gAR0132SensorsWdrConfig) / sizeof(IssSensor_ConfigRegs);

    for (cnt = 0u; cnt < numRegs; cnt ++)
    {
        regAddr  = sensorRegs[cnt].regAddr;
        regValue = sensorRegs[cnt].regValue;

        /* Data formats */
        if (0x30b0U == regAddr)
        {
            /* Default GRBG */
            regValue = regValue & (0xFF7FU);
            /* for RAW12 regValue = regValue & (0x0080U); */
        }
        /* WDR Mode */
        if (0x3082U == regAddr)
        {
            /* WDR Enabled */
            regValue = (UInt16)0x28;
            /* for RAW12 / WDR disable regValue = (UInt16)0x29; */
        }
        /* No support for flipping as of now */

        if ((SENSOR_DLY_REG == sensorRegs[cnt].regAddr) &&
            (SENSOR_DLY_REG_MASK == sensorRegs[cnt].regValue))
        {
            BspOsal_sleep((UInt32) sensorRegs[cnt].delay);
        }
        else
        {
            numSensRegs = 1U;

            status = AR0132_WriteReg(i2cInstId,
                                     i2cAddr,
                                     &regAddr,
                                     &regValue,
                                     numSensRegs);
        }

        if (SYSTEM_LINK_STATUS_SOK != status)
        {
            break;
        }
    }

    return (status);
}

static Int32 AR0132_Stop(UInt32 chId, IssSensor_CreateParams *pCreatePrms)
{
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;
    UInt16 regAddr, regValue;
    UInt32 numSensRegs;

    UTILS_assert(NULL != pCreatePrms);

    regAddr = 0x301A;

    /* Read of this register fails */
    numSensRegs = 1U;
    regValue = 0U;
    status = AR0132_ReadReg(pCreatePrms->i2cInstId,
                            pCreatePrms->i2cAddr[chId],
                            &regAddr,
                            &regValue,
                            numSensRegs);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    regValue = regValue & (UInt16) 0xFFFBU;

    numSensRegs = 1U;

    status = AR0132_WriteReg(pCreatePrms->i2cInstId,
                             pCreatePrms->i2cAddr[chId],
                             &regAddr,
                             &regValue,
                             numSensRegs);
    return (status);
}

static AR0132_GetDccParams(IssSensor_CreateParams *pCreatePrms,
                            IssSensor_DccParams *pDccPrms)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    UTILS_assert(NULL != pCreatePrms);
    UTILS_assert(NULL != pDccPrms);

    {
        pDccPrms->pDccCfg = (UInt8 *)gAr0132DccCfgWdr;
        pDccPrms->dccCfgSize = sizeof(gAr0132DccCfgWdr);
    }

    return (status);
}

static Int32 AR0132_GetExpParams(IssSensor_CreateParams *pCreatePrms,
                                    IssSensor_ExposureParams *pExpPrms)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 chId;

    UTILS_assert(NULL != pCreatePrms);
    UTILS_assert(NULL != pExpPrms);

    chId = pExpPrms->chId;

    if (SYSTEM_LINK_STATUS_SOK == status)
    {
        pExpPrms->expRatio = ISS_SENSORS_AR0132_DEFAULT_EXP_RATIO;
        pExpPrms->exposureTime[chId] = 0U;
    }

    return (status);
}

static Void AR0132_InitAewbConfig(IssSensor_CreateParams *pCreatePrms,
                                AlgorithmLink_IssAewbCreateParams *pAewbPrms)
{
    AlgorithmLink_IssAewbAeDynamicParams *dynPrms = NULL;
    IssSensor_Info *info = &gSensorParamsAr0130.info;

    UTILS_assert(NULL != pCreatePrms);
    UTILS_assert(NULL != pAewbPrms);

    /* Set H3A Params */
    /* Set H3A Params */
    pAewbPrms->h3aParams.winCountH = aewbConfig_ar0132.winCfg.horzCount;
    pAewbPrms->h3aParams.winCountV = aewbConfig_ar0132.winCfg.vertCount;
    pAewbPrms->h3aParams.winSizeH  = aewbConfig_ar0132.winCfg.width;
    pAewbPrms->h3aParams.winSizeV  = aewbConfig_ar0132.winCfg.height;
    pAewbPrms->h3aParams.winSkipH  = aewbConfig_ar0132.winCfg.horzIncr;
    pAewbPrms->h3aParams.winSkipV  = aewbConfig_ar0132.winCfg.vertIncr;

    pAewbPrms->dataFormat = info->dataFormat;
    pAewbPrms->mode = (AlgorithmLink_IssAewbMode)info->aewbMode;
    pAewbPrms->isWdrEnable = TRUE;

    pAewbPrms->dccCameraId = gSensorParamsAr0130.dccId;

    pAewbPrms->calbData = NULL;

    dynPrms = &pAewbPrms->aeDynParams;

    dynPrms->targetBrightnessRange.min = 0;
    dynPrms->targetBrightnessRange.max = 0;
    dynPrms->targetBrightness = 0;
    dynPrms->threshold = 0;

    dynPrms->exposureTimeRange[0].min = 0;
    dynPrms->exposureTimeRange[0].max = 0;
    dynPrms->apertureLevelRange[0].min = 1;
    dynPrms->apertureLevelRange[0].max = 1;
    dynPrms->sensorGainRange[0].min = 1000;
    dynPrms->sensorGainRange[0].max = 1000;
    dynPrms->ipipeGainRange[0].min = 512;
    dynPrms->ipipeGainRange[0].max = 512;

    dynPrms->numAeDynParams = 1;
    dynPrms->exposureTimeStepSize = 1;
    dynPrms->enableBlc = FALSE;
}

static Void AR0132_GetIspConfig (
    IssSensor_CreateParams *pCreatePrms,
    IssIspConfigurationParameters *pIspCfg)
{
    UTILS_assert(NULL != pIspCfg);
    UTILS_assert(NULL != pCreatePrms);

    UTILS_assert(NULL != pIspCfg);

    /* Override common settings for specific sensor */
    pIspCfg->aewbCfg = &aewbConfig_ar0132;

    pIspCfg->glbceCfg = &glbceCfg_ar0132;

    /* fwdPerCfg */
    pIspCfg->glbceFwdPerCfg = &glbceFwbPerCfg_ar0132;

    /* revPerCfg */
    pIspCfg->glbceRevPerCfg = &glbceRevPerCfg_ar0132;

    /* ipipe config */
    pIspCfg->ipipeInputCfg = &ipipeInputCfg_ar132;

}

static Int32 AR0132_ReadWriteReg (
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
        status = AR0132_WriteReg(pCreatePrms->i2cInstId,
            pCreatePrms->i2cAddr[chId], &pReg->regAddr, &pReg->regValue, 1u);
    }
    else
    {
        status = AR0132_ReadReg(pCreatePrms->i2cInstId,
            pCreatePrms->i2cAddr[chId], &pReg->regAddr, &pReg->regValue, 1u);
    }

    return (status);
}

static Int32 AR0132_ReadReg(UInt8         i2cInstId,
                            UInt8         i2cAddr,
                            const UInt16 *regAddr,
                            UInt16       *regVal,
                            UInt32        numRegs)
{
    Int32  status = SYSTEM_LINK_STATUS_SOK;
    UInt32 cnt;
    UInt8  rawRegVal[4];

    for (cnt = 0; cnt < numRegs; cnt++)
    {
        /* Convert Registers address and value into 8bit array */
        rawRegVal[0U] = (UInt8) ((regAddr[cnt] >> 8U) & (UInt8) 0xFF);
        rawRegVal[1U] = (UInt8) ((regAddr[cnt] >> 0U) & (UInt8) 0xFF);

        status = Bsp_deviceRawWrite8(i2cInstId, i2cAddr, rawRegVal, 2u);

        if (FVID2_SOK == status)
        {
            status = Bsp_deviceRawRead8(i2cInstId, i2cAddr, &rawRegVal[2U],
                2u);

            regVal[cnt] =
                (UInt16)((UInt16)((rawRegVal[2U] & (UInt16) 0xFF) << 8U) |
                         ((UInt16)(rawRegVal[3U] & (UInt16) 0xFF)));
        }
    }

    return (status);
}

static Int32 AR0132_WriteReg(UInt8         i2cInstId,
                             UInt8         i2cAddr,
                             const UInt16 *regAddr,
                             const UInt16 *regValue,
                             UInt32        numRegs)
{
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;
    UInt32 cnt;
    UInt8 rawRegVal[4];

    for (cnt = 0u; cnt < numRegs; cnt ++)
    {
        /* Convert Registers address and value into 8bit array */
        rawRegVal[0U] = (UInt8) ((regAddr[cnt] >> 8U) & (UInt8) 0xFF);
        rawRegVal[1U] = (UInt8) ((regAddr[cnt] >> 0U) & (UInt8) 0xFF);
        rawRegVal[2U] = (UInt8) ((regValue[cnt] >> 8U) & (UInt8) 0xFF);
        rawRegVal[3U] = (UInt8) ((regValue[cnt] >> 0U) & (UInt8) 0xFF);

        status = Bsp_deviceRawWrite8(i2cInstId, i2cAddr, rawRegVal, 4U);

        if (SYSTEM_LINK_STATUS_SOK != status)
        {
            break;
        }
    }

    return (status);
}
