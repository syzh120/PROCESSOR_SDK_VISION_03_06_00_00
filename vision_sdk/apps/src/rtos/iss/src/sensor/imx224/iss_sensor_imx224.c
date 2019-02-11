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
 * \file iss_sensor_imx224.c
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
#include <ti/drv/vps/include/devices/bsp_device.h>
#include "imx224_linear_1280x960_config.h"
#include "imx224_dol_1312x2164_config.h"
#include "imx224_dcc.h"
#include "imx224_gain_table.h"

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

#define ISS_SENSOR_IMX224_DEFAULT_EXP_RATIO     (64U)

#define ISS_SENSOR_IMX224_FEATURES      (ISS_SENSOR_FEATURE_MANUAL_EXPOSURE|   \
                                         ISS_SENSOR_FEATURE_MANUAL_GAIN|       \
                                         ISS_SENSOR_FEATURE_LINEAR_MODE|       \
                                         ISS_SENSOR_FEATURE_TWO_PASS_WDR_MODE| \
                                         ISS_SENSOR_FEATURE_DCC_SUPPORTED)
#define ISS_IMX224_GAIN_TBL_SIZE                (150U)
#define ISS_IMX224_GAIN_TBL_STEP_SIZE           (100U)
#define ISS_IMX224_GAIN_TBL_STARTOFFSET         (10U)
#define ISS_IMX224_MAX_INTG_LINES               (2050U)
#define ISS_IMX224_VMAX                         (0x44c)
#define ISS_IMX224_RHS                          (0x85U)

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
} gImx224DeviceObj;

/*******************************************************************************
 *  Local Functions Declarations
 *******************************************************************************
 */
static Int32 IMX224_Start(UInt32 chId, IssSensor_CreateParams *pCreatePrms);
static Int32 IMX224_SetAeParams(IssSensor_CreateParams *pCreatePrms,
    IssSensor_AeParams *pAePrms);
static Int32 IMX224_GetDccParams(IssSensor_CreateParams *pCreatePrms,
    IssSensor_DccParams *pDccPrms);
static IMX224_GetExpParams(IssSensor_CreateParams *pCreatePrms,
    IssSensor_ExposureParams *pExpPrms);
static Void IMX224_InitAewbConfig(
    IssSensor_CreateParams *pCreatePrms,
    AlgorithmLink_IssAewbCreateParams *pAewbPrms);
static Void IMX224_GetIspConfig (
    IssSensor_CreateParams *pCreatePrms,
    IssIspConfigurationParameters *pIspCfg);
static Int32 IMX224_ReadWriteReg (
    IssSensor_CreateParams *pCreatePrms, UInt32 readWriteFlag,
    IssSensor_ReadWriteReg *pReg);

static Int32 IMX224_WriteReg(UInt8         i2cInstId,
                             UInt8         i2cAddr,
                             const UInt16 *regAddr,
                             const UInt8  *regVal,
                             UInt32        numRegs);
static Int32 IMX224_ReadReg(UInt8         i2cInstId,
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
static IssSensorIf_Params SensorParams_Imx224 = {0};

static const UInt8 gImx224DccCfg[] = IMX224DCC_CFG;

static IssSensor_ConfigRegs gIMX224LinearConfig[] =
    IMX224_LINEAR_1280X960_CONFIG;
static IssSensor_ConfigRegs gImx224DolConfig[] = IMX224_DOL_1312X2164_CONFIG;
static const UInt8 gIMX224GainsTable[] = IMX224_GAIN_TABLE;


/**
 * \brief Structure for ISP H3A AEWB engine parameters.
 */
static vpsissH3aAewbConfig_t aewbConfig_imx224 =
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

static vpsissGlbceConfig_t glbceCfg_imx224 =
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
        0,5377,10218,14600,18585,22224,25561,28631,31466,34092,36530,
        38801,40921,42904,44764,46511,48156,49706,51171,52557,53870,55116,
        56299,57425,58498,59520,60497,61429,62322,63176,63995,64781,
        65535
    }
};

static vpsissGlbcePerceptConfig_t glbceFwbPerCfg_imx224 =
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

static vpsissGlbcePerceptConfig_t glbceRevPerCfg_imx224 =
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

Void IssSensor_IMX224_Init()
{
    Int32 status;
    IssSensorIf_Params *prms = &SensorParams_Imx224;
    IssSensor_Info *info = &SensorParams_Imx224.info;

    IssSensorIf_Params_Init(prms);

    strncpy(prms->name, SENSOR_SONY_IMX224_CSI2, ISS_SENSORS_MAX_NAME);

    prms->dccId             = 224;

    info->width             = 1280;
    info->height            = 960;
    info->dataFormat        = SYSTEM_DF_BAYER_RGGB;
    info->bpp               = SYSTEM_BPP_BITS12;
    info->features          = ISS_SENSOR_IMX224_FEATURES;
    info->aewbMode          = ALGORITHMS_ISS_AEWB_MODE_AEWB;
    info->maxExp            = 1;
    info->ramOffset         = 26*1024*1024;

    info->lnIntrExpFrmInfo.totalWidth = 1312u;
    info->lnIntrExpFrmInfo.totalHeight = 2164u;
    info->lnIntrExpFrmInfo.info[ISS_SENSOR_EXPOSURE_LONG].startx = 0u;
    info->lnIntrExpFrmInfo.info[ISS_SENSOR_EXPOSURE_LONG].starty = 9u;
    info->lnIntrExpFrmInfo.info[ISS_SENSOR_EXPOSURE_LONG].width = 1280u;
    info->lnIntrExpFrmInfo.info[ISS_SENSOR_EXPOSURE_LONG].height = 960u;

    info->lnIntrExpFrmInfo.info[ISS_SENSOR_EXPOSURE_SHORT].startx = 0u;
    info->lnIntrExpFrmInfo.info[ISS_SENSOR_EXPOSURE_SHORT].starty = 142u;
    info->lnIntrExpFrmInfo.info[ISS_SENSOR_EXPOSURE_SHORT].width = 1280u;
    info->lnIntrExpFrmInfo.info[ISS_SENSOR_EXPOSURE_SHORT].height = 960u;

    prms->start             = IMX224_Start;
    prms->stop              = NULL;
    prms->setAeParams       = IMX224_SetAeParams;
    prms->getExpParams      = IMX224_GetExpParams;
    prms->getDccParams      = IMX224_GetDccParams;
    prms->initAewbConfig    = IMX224_InitAewbConfig;
    prms->getIspConfig      = IMX224_GetIspConfig;
    prms->readWriteReg      = IMX224_ReadWriteReg;

    status = IssSensorIf_RegisterSensor(prms);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);
}

/*******************************************************************************
 *  Local Functions Definition
 *******************************************************************************
 */

static Int32 IMX224_Start(UInt32 chId, IssSensor_CreateParams *pCreatePrms)
{
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;
    UInt32 cnt, i2cInstId, features, numRegs;
    UInt8 i2cAddr;
    UInt16 regAddr;
    UInt8 regValue;
    IssSensor_ConfigRegs *sensorCfg;

    UTILS_assert(NULL != pCreatePrms);

    i2cInstId = pCreatePrms->i2cInstId;
    i2cAddr = pCreatePrms->i2cAddr[chId];
    features = pCreatePrms->enableFeatures[chId];

    gImx224DeviceObj.lineIntgTimeInMs = 15.0f;
    gImx224DeviceObj.pixIntgTimeInMs = 0.0234f;
    gImx224DeviceObj.maxCoarseIntgTime = ISS_IMX224_MAX_INTG_LINES;

    if (ISS_SENSOR_FEATURE_TWO_PASS_WDR_MODE ==
        (features & ISS_SENSOR_FEATURE_TWO_PASS_WDR_MODE))
    {
        sensorCfg = gImx224DolConfig;
        numRegs = sizeof(gImx224DolConfig)/sizeof(IssSensor_ConfigRegs);
    }
    else
    {
        sensorCfg = gIMX224LinearConfig;
        numRegs = sizeof(gIMX224LinearConfig)/sizeof(IssSensor_ConfigRegs);
    }

    for (cnt = 0u; cnt < numRegs; cnt ++)
    {
        regAddr  = sensorCfg[cnt].regAddr;
        regValue = sensorCfg[cnt].regValue;

        if (ISS_SENSOR_FEATURE_TWO_PASS_WDR_MODE ==
            (features & ISS_SENSOR_FEATURE_TWO_PASS_WDR_MODE))
        {
            if (0x302c == regAddr)
            {
                regValue = (ISS_IMX224_RHS & 0xFF);
            }
            if (0x302d == regAddr)
            {
                regValue = (ISS_IMX224_RHS >> 8);
            }

            if (0x3018 == regAddr)
            {
                regValue = (ISS_IMX224_VMAX & 0xFF);
            }
            if (0x3019 == regAddr)
            {
                regValue = (ISS_IMX224_VMAX >> 8);
            }
        }

        /* Convert Registers address and value into 8bit array */
        status = IMX224_WriteReg(i2cInstId, i2cAddr, &regAddr,
            &regValue, 1u);

        if (SYSTEM_LINK_STATUS_SOK != status)
        {
            break;
        }

        BspOsal_sleep(sensorCfg[cnt].delay);
    }

    return (status);
}

static Int32 IMX224_SetAeParams(IssSensor_CreateParams *pCreatePrms,
    IssSensor_AeParams *pAePrms)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt16 regAddr[4];
    UInt8 regValue[4], i2cAddr;
    UInt32 i2cInstId, gainTblIdx;
    UInt32 features, lineIntgTimeU32;
    float lineIntgTime;
    UInt16 shsLong, shsShort;

    UTILS_assert(NULL != pAePrms);
    UTILS_assert(NULL != pCreatePrms);

    features = pCreatePrms->enableFeatures[pAePrms->chId];
    i2cInstId = pCreatePrms->i2cInstId;
    i2cAddr = pCreatePrms->i2cAddr[pAePrms->chId];

    /* Set Analog Gain first */
    gainTblIdx = (pAePrms->analogGain / ISS_IMX224_GAIN_TBL_STEP_SIZE) -
        ISS_IMX224_GAIN_TBL_STARTOFFSET;

    if (gainTblIdx >= ISS_IMX224_GAIN_TBL_SIZE)
    {
        gainTblIdx = ISS_IMX224_GAIN_TBL_SIZE - 1U;
    }

    regAddr[0] = 0x3014;
    regValue[0] = gIMX224GainsTable[gainTblIdx];

    status = IMX224_WriteReg(i2cInstId, i2cAddr, regAddr, regValue, 1u);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    /* Set Analog Gain first */
    lineIntgTime = pAePrms->exposureTime[0] / gImx224DeviceObj.lineIntgTimeInMs;
    if (lineIntgTime > gImx224DeviceObj.maxCoarseIntgTime)
    {
        lineIntgTime = gImx224DeviceObj.maxCoarseIntgTime;
    }

    lineIntgTimeU32 = (UInt32)lineIntgTime;
    if (ISS_SENSOR_FEATURE_TWO_PASS_WDR_MODE ==
        (features & ISS_SENSOR_FEATURE_TWO_PASS_WDR_MODE))
    {
        shsLong = (2U * ISS_IMX224_VMAX) - lineIntgTimeU32;
        regAddr[0] = 0x3023;
        regAddr[1] = 0x3024;
        regValue[0] = (UInt8)(shsLong & 0xFF);
        regValue[1] = (UInt8)(shsLong >> 8);

        shsShort = (UInt16)(ISS_IMX224_RHS - (lineIntgTimeU32 /
                        ISS_SENSOR_IMX224_DEFAULT_EXP_RATIO));

        regAddr[2] = 0x3020;
        regAddr[3] = 0x3021;
        regValue[2] = (UInt8)(shsShort & 0xFF);
        regValue[3] = (UInt8)(shsShort >> 8);

        status = IMX224_WriteReg(i2cInstId, i2cAddr, regAddr, regValue, 4u);
        UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    }
    else
    {
        shsLong = ISS_IMX224_VMAX - lineIntgTimeU32;
        regAddr[0] = 0x3020;
        regAddr[1] = 0x3021;
        regValue[0] = (UInt8)(shsLong & 0xFF);
        regValue[1] = (UInt8)(shsLong >> 8);
        status = IMX224_WriteReg(i2cInstId, i2cAddr, regAddr, regValue, 2u);
        UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    }

    return (status);
}

static Int32 IMX224_ReadReg(UInt8         i2cInstId,
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

static Int32 IMX224_WriteReg(UInt8         i2cInstId,
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

static IMX224_GetDccParams(IssSensor_CreateParams *pCreatePrms,
    IssSensor_DccParams *pDccPrms)
{
    pDccPrms->dccCfgSize  = sizeof (gImx224DccCfg);
    pDccPrms->pDccCfg     = (UInt8 *)gImx224DccCfg;

    return (SYSTEM_LINK_STATUS_SOK);
}

static IMX224_GetExpParams(IssSensor_CreateParams *pCreatePrms,
    IssSensor_ExposureParams *pExpPrms)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    UTILS_assert(NULL != pCreatePrms);
    UTILS_assert(NULL != pExpPrms);

    {
        pExpPrms->expRatio = ISS_SENSOR_IMX224_DEFAULT_EXP_RATIO;
    }

    return (status);
}

static Void IMX224_InitAewbConfig(
    IssSensor_CreateParams *pCreatePrms,
    AlgorithmLink_IssAewbCreateParams *pAewbPrms)
{
    AlgorithmLink_IssAewbAeDynamicParams *dynPrms = NULL;

    UTILS_assert(NULL != pAewbPrms);

    /* Set H3A Params */
    pAewbPrms->h3aParams.winCountH = aewbConfig_imx224.winCfg.horzCount;
    pAewbPrms->h3aParams.winCountV = aewbConfig_imx224.winCfg.vertCount;
    pAewbPrms->h3aParams.winSizeH  = aewbConfig_imx224.winCfg.width;
    pAewbPrms->h3aParams.winSizeV  = aewbConfig_imx224.winCfg.height;
    pAewbPrms->h3aParams.winSkipH  = aewbConfig_imx224.winCfg.horzIncr;
    pAewbPrms->h3aParams.winSkipV  = aewbConfig_imx224.winCfg.vertIncr;
    pAewbPrms->numH3aPlanes = 1u;

    pAewbPrms->dataFormat = SensorParams_Imx224.info.dataFormat;
    pAewbPrms->mode =
        (AlgorithmLink_IssAewbMode)SensorParams_Imx224.info.aewbMode;

    if (ISS_SENSOR_FEATURE_LINEAR_MODE ==
            (ISS_SENSOR_FEATURE_LINEAR_MODE&pCreatePrms->enableFeatures[0]))
    {
        pAewbPrms->isWdrEnable = FALSE;
    }
    else
    {
        pAewbPrms->isWdrEnable = TRUE;
    }

    pAewbPrms->dccCameraId = SensorParams_Imx224.dccId;

    dynPrms = &pAewbPrms->aeDynParams;

    dynPrms->targetBrightnessRange.min = 30;
    dynPrms->targetBrightnessRange.max = 45;
    dynPrms->targetBrightness = 35;
    dynPrms->threshold = 1;

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

    dynPrms->exposureTimeStepSize = 1;

    dynPrms->enableBlc = TRUE;

    pAewbPrms->calbData = NULL;
}

static Void IMX224_GetIspConfig (
    IssSensor_CreateParams *pCreatePrms,
    IssIspConfigurationParameters *pIspCfg)
{
    UTILS_assert(NULL != pIspCfg);

    pIspCfg->aewbCfg = &aewbConfig_imx224;

    /* glbceCfg */
    pIspCfg->glbceCfg = &glbceCfg_imx224;

    /* fwdPerCfg */
    pIspCfg->glbceFwdPerCfg = &glbceFwbPerCfg_imx224;

    /* revPerCfg */
    pIspCfg->glbceRevPerCfg = &glbceRevPerCfg_imx224;
}

static Int32 IMX224_ReadWriteReg (
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
        status = IMX224_WriteReg(pCreatePrms->i2cInstId,
            pCreatePrms->i2cAddr[chId], &pReg->regAddr, &regValue, 1u);
    }
    else
    {
        status = IMX224_ReadReg(pCreatePrms->i2cInstId,
            pCreatePrms->i2cAddr[chId], &pReg->regAddr, &regValue, 1u);

        if (SYSTEM_LINK_STATUS_SOK == status)
        {
            pReg->regValue = regValue;
        }
    }

    return (status);
}
