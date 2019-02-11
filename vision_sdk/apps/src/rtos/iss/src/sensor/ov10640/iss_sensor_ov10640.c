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
 * \file iss_sensor_ar0140.c
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
#include "ov10640_wdr_1280x720_setup.h"
#include "ov10640_imi_wdr_1280x720_setup.h"
#include "ov10640_dcc.h"
#include "ov10640_dcc_1pass.h"

#include <ti/drv/vps/include/devices/bsp_device.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/* #define _USE_DIGITAL_GAIN_ */

#define ISS_SENSOR_OV10640_DEFAULT_EXP_RATIO    (32U)

#define ISS_SENSOR_OV10640_FEATURES     (ISS_SENSOR_FEATURE_HFLIP|             \
                                         ISS_SENSOR_FEATURE_VFLIP|             \
                                         ISS_SENSOR_FEATURE_MANUAL_EXPOSURE|   \
                                         ISS_SENSOR_FEATURE_MANUAL_GAIN|       \
                                         ISS_SENSOR_FEATURE_LINEAR_MODE|       \
                                         ISS_SENSOR_FEATURE_TWO_PASS_WDR_MODE| \
                                         ISS_SENSOR_FEATURE_ONE_PASS_WDR_MODE| \
                                         ISS_SENSOR_FEATURE_DCC_SUPPORTED)

#define ISS_SENSOR_OV10640_SUPPORTED_REV        (0xB4U)


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
} gOv10640DeviceObj;

/*******************************************************************************
 *  Local Functions Declarations
 *******************************************************************************
 */
static Int32 OV10640_Start(UInt32 chId, IssSensor_CreateParams *pCreatePrms);
static Int32 OV10640_imi_Start(UInt32 chId, IssSensor_CreateParams *pCreatePrms);
static Int32 OV10640_Stop(UInt32 chId, IssSensor_CreateParams *pCreatePrms);
static Int32 OV10640_SetAeParams(IssSensor_CreateParams *pCreatePrms,
    IssSensor_AeParams *pAePrms);
static Int32 OV10640_GetDccParams(IssSensor_CreateParams *pCreatePrms,
    IssSensor_DccParams *pDccPrms);
static OV10640_GetExpParams(IssSensor_CreateParams *pCreatePrms,
    IssSensor_ExposureParams *pExpPrms);
static Void OV10640_InitAewbConfig(
    IssSensor_CreateParams *pCreatePrms,
    AlgorithmLink_IssAewbCreateParams *pAewbPrms);
static Void OV10640_GetIspConfig (
    IssSensor_CreateParams *pCreatePrms,
    IssIspConfigurationParameters *pIspCfg);
static Int32 OV10640_ReadWriteReg (
    IssSensor_CreateParams *pCreatePrms, UInt32 readWriteFlag,
    IssSensor_ReadWriteReg *pReg);

static Int32 OV10640_ReadReg(UInt8         i2cInstId,
                             UInt8         i2cAddr,
                             const UInt16 *regAddr,
                             UInt8        *regVal,
                             UInt32        numRegs);
static Int32 OV10640_WriteReg(UInt8         i2cInstId,
                              UInt8         i2cAddr,
                              const UInt16 *regAddr,
                              const UInt8  *regVal,
                              UInt32        numRegs);

/*******************************************************************************
 *  Globals
 *******************************************************************************
 */

/* \brief Sensor Params structure used for registering this sensor to chains_iss
 */
static IssSensorIf_Params SensorParams_Ov10640 = {0};

static const UInt8 gOv10640DccCfgLinearAndWdr[] = OV10640DCC_CFG;
static const UInt8 gOv10640DccCfgSinglePassWdr[] = OV10640_1PASSDCC_CFG;

static IssSensor_ConfigRegs gOV10640SensorsConfig[] =
    OV10640_MIPI_720P_4LANES;

static IssSensor_ConfigRegs gOV10640ImiSensorsConfig[] =
    OV10640_MIPI_720P_4LANES_IMI;

/**
 * \brief Structure for ISP H3A AEWB engine parameters.
 */
static vpsissH3aAewbConfig_t aewbConfig_ov10640 =
{
    FALSE, /* enableALowComp */
    FALSE, /* enableMedFilt */
    0xFFF, /* midFiltThreshold */
    {   /* vpsissH3aPaxelConfig_t      winCfg */
        {160u, 120u}, /* Fvid2_PosConfig pos */
        48u,     /* width */
        24u,     /* height */
        20u,     /* horzCount */
        20u,     /* vertCount */
        4,      /* horzIncr */
        2,      /* vertIncr */
    },
    718u,       /* Black Line Vertical Start */
    2u,         /* Black Line Width */
    VPS_ISS_H3A_OUTPUT_MODE_SUM_ONLY, /* vpsissH3aOutputMode_t outMode; */
    2,  /* sumShift */
    1023u, /* satLimit */
    VPS_ISS_H3A_MODE_NORMAL /* vpsissH3aMode_t mode */
} ;

/**
 * \brief Structure for ISP H3A AF engine parameters.
 * Parameter values are chosen to divide the frame in a 3x3 grid of paxels
 * for scene obstruction detection purpose
 */

static vpsissH3aAfConfig_t afConfig_ov10640 =
{
    FALSE, /* enableALowCompr */
    TRUE, /*enableMedFilt */
    100,  /* midFiltThreshold*/
    VPS_ISS_H3A_AF_RGBPOS_GR_BG,  /* rgbPos */
    { /* vpsissH3aPaxelConfig_t*/
            {128u + 0, 16u + 1u}, /* Fvid2_PosConfig pos */
            (((1280u - 2u*128u)/3u) + 7u) & (~7u), /* width, rounded up to next multiple of 8*/
            (((720u - 2u*16u)/3u) + 7u) & (~7u), /* height, rounded up to next multiple of 8 */
            3u, /* horzCount */
            3u, /* vertCount*/
            8u, /* horzIncr */
            8u, /* vertIncr */
     },
     VPS_ISS_H3A_AF_FV_MODE_SUM, /* fvMode */
     VPS_ISS_H3A_AF_VF_VERT_HORZ, /* vfMode */
     { /* iirCfg1 */
     {8, -95, -49, 38, 76, 38, -111, -54, 17, -34, 17}, /* coeff */
        //{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        0 /* threshold */
     },
     { /* iirCfg2 */
    {11, -72, -50, 26, 51, 26, -92, -53, 19, -38, 19}, /* coeff */
        //{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        0
     },
     { /* firCfg1 */
     {3, -6, 0, 6, -3}, /* coeff */
       //{0, 0, 0, 0, 16},
        0 /* threshold */
     },
     { /* firCfg2 */
     {3, -6, 0, 6, -3}, /* coeff */
       //{0, 0, 0, 0, 16},
       0 /* threshold */
      },
      0, /* iirFiltStartPos */
      VPS_ISS_H3A_MODE_NORMAL /* AF mode */
};

static vpsissGlbceConfig_t glbceCfg_ov10640 =
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
        38801,40921,42904,44764,46511,48156,49706,51171,52557,53870,
        55116,56299,57425,58498,59520,60497,61429,62322,63176,63995,
        64781,65535
    }
};

static vpsissGlbcePerceptConfig_t glbceFwbPerCfg_ov10640 =
{
    TRUE,
    {
        0,4622,8653,11684,14195,16380,18335,20118,21766,23304,24751,26119,
        27422,28665,29857,31003,32108,33176,34209,35211,36185,37132,38055,
        38955,39834,40693,41533,42355,43161,43951,44727,45488,46236,46971,
        47694,48405,49106,49795,50475,51145,51805,52456,53099,53733,54360,
        54978,55589,56193,56789,57379,57963,58539,59110,59675,60234,60787,
        61335,61877,62414,62946,63473,63996,64513,65026,65535
    }
};

static vpsissGlbcePerceptConfig_t glbceRevPerCfg_ov10640 =
{
    TRUE,
    {
        0,228,455,683,910,1138,1369,1628,1912,2221,2556,2916,3304,3717,4158,
        4626,5122,5645,6197,6777,7386,8024,8691,9387,10113,10869,11654,
        12471,13317,14194,15103,16042,17012,18014,19048,20113,21210,22340,
        23501,24696,25922,27182,28475,29800,31159,32552,33977,35437,36930,
        38458,40019,41615,43245,44910,46609,48343,50112,51916,53755,55630,
        57539,59485,61466,63482,65535
    }
};

/**
 * \brief Structure for ISP GLBCE WDR Params.
 */
static vpsissGlbceWdrConfig_t glbceWdrCfg_ov10640 =
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

BspUtils_Ub960I2cParams gUB913_OV10640_IMI_SerCfg[OV10640_IMI_SER_CFG_SIZE] = {
    {0x03, 0xC5, 0x0},
    {0x0D, 0x99, 0x0},

    /* Changing the default I2C clock rate to 100 KHz */
    /* Default  0x82 = 74 kbits/sec
                0x64 = 100 kbps
                0x32 = 400 kbps */
    {0x11, 0x32, 0x0},  /* SCL High period */
    {0x12, 0x32, 0x0}   /* SCL Low period */
};

BspUtils_Ub960I2cParams gAppIssUtilsUb960Cfg_OV10640_IMI[OV10640_IMI_DES_CFG_SIZE] = {
    {0x01, 0x01, 0x64},    /* Digital Reset 0 */
    {0x1F, 0x05, 0x10},

    /* IMI OV10640 1 */
    {0x4C, 0x01, 0x0},
    {0x58, 0x58, 0x0},
    {0x6D, 0x7D, 0x0},
    {0x5D, 0xBA, 0x0},
    {0x65, ((UInt8) (PORT_0_SER_ADDR << 1U)), 0x0},
    {0x5E, 0x62,0},
    {0x66, ((UInt8) (PORT_0_SENSOR_ADDR << 1U)), 0x0},
    {0x7C, 0x00, 0x0},
    {0x6E, 0x99, 0x0},
    {0x70, 0x2B, 0x0},
    {0x71, 0x2C, 0x0},


    /* IMI OV10640 2 */
    {0x4C, 0x12, 0x0},
    {0x58, 0x58, 0x0},
    {0x6D, 0x7D, 0x0},
    {0x5D, 0xBA ,0x0},
    {0x65, ((UInt8) (PORT_1_SER_ADDR << 1U)), 0x0},
    {0x5E,0x62,0},
    {0x66, ((UInt8) (PORT_1_SENSOR_ADDR << 1U)), 0x0},
    {0x7C, 0x00, 0x0},
    {0x6E, 0x99, 0x0},
    {0x70, 0x6B, 0x0},
    {0x71, 0x6C, 0x0},


    /* IMI OV10640 3 */
    {0x4C, 0x24, 0x0},
    {0x58, 0x58, 0x0},
    {0x6D, 0x7D, 0x0},
    {0x5D, 0xBA, 0x0},
    {0x65, ((UInt8) (PORT_2_SER_ADDR << 1U)), 0x0},
    {0x5E, 0x62, 0x0},
    {0x66, ((UInt8) (PORT_2_SENSOR_ADDR << 1U)), 0x0},
    {0x7C, 0x00, 0x0},
    {0x6E, 0x99, 0x0},
    {0x70, 0xAB, 0x0},
    {0x71, 0xAC, 0x0},


    /* IMI OV10640 4 */
    {0x4C, 0x38, 0x0},
    {0x58, 0x58, 0x0},
    {0x6D, 0x7D, 0x0},
    {0x5D, 0xBA ,0x0},
    {0x65, ((UInt8) (PORT_3_SER_ADDR << 1U)), 0x0},
    {0x5E, 0x62, 0x0},
    {0x66, ((UInt8) (PORT_3_SENSOR_ADDR << 1U)), 0x0},
    {0x7C, 0x00, 0x0},
    {0x6E, 0x99, 0x0},
    {0x70, 0xEB, 0x0},
    {0x71, 0xEC, 0x0},

    {0xB0, 0x1C, 0x64},
    {0xB1, 0x13, 0x10},
    {0xB2, 0x1F, 0x10},

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

/*******************************************************************************
 *  Function Definition
 *******************************************************************************
 */

Void IssSensor_OV10640_Init()
{
    Int32 status;
    IssSensorIf_Params *prms = &SensorParams_Ov10640;
    IssSensor_Info *info = &SensorParams_Ov10640.info;

    IssSensorIf_Params_Init(prms);

    strncpy(prms->name, SENSOR_OMNIVISION_OV10640_CSI2, ISS_SENSORS_MAX_NAME);

    prms->dccId             = 10640;

    info->width             = 1280;
    info->height            = 720;
    info->dataFormat        = SYSTEM_DF_BAYER_BGGR;
    info->bpp               = SYSTEM_BPP_BITS12;
    info->features          = ISS_SENSOR_OV10640_FEATURES;
    info->aewbMode          = ALGORITHMS_ISS_AEWB_MODE_AEWB;
    info->maxExp            = 1;
    info->ramOffset         = 25*1024*1024;

    prms->start             = OV10640_Start;
    prms->stop              = OV10640_Stop;
    prms->setAeParams       = OV10640_SetAeParams;
    prms->getExpParams      = OV10640_GetExpParams;
    prms->getDccParams      = OV10640_GetDccParams;
    prms->initAewbConfig    = OV10640_InitAewbConfig;
    prms->getIspConfig      = OV10640_GetIspConfig;
    prms->readWriteReg      = OV10640_ReadWriteReg;

    status = IssSensorIf_RegisterSensor(prms);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);
}

Void IssSensor_OV10640_imi_Init()
{
    Int32 status;
    IssSensorIf_Params *prms = &SensorParams_Ov10640;
    IssSensor_Info *info = &SensorParams_Ov10640.info;

    IssSensorIf_Params_Init(prms);

    strncpy(prms->name, SENSOR_OMNIVISION_OV10640_IMI, ISS_SENSORS_MAX_NAME);

    prms->dccId             = 10640;

    info->width             = 1280;
    info->height            = 720;
    info->dataFormat        = SYSTEM_DF_BAYER_BGGR;
    info->bpp               = SYSTEM_BPP_BITS12;
    info->features          = ISS_SENSOR_OV10640_FEATURES;
    info->aewbMode          = ALGORITHMS_ISS_AEWB_MODE_AEWB;
    info->maxExp            = 1;
    info->ramOffset         = 25*1024*1024;

    prms->start             = OV10640_imi_Start;
    prms->stop              = OV10640_Stop;
    prms->setAeParams       = OV10640_SetAeParams;
    prms->getExpParams      = OV10640_GetExpParams;
    prms->getDccParams      = OV10640_GetDccParams;
    prms->initAewbConfig    = OV10640_InitAewbConfig;
    prms->getIspConfig      = OV10640_GetIspConfig;
    prms->readWriteReg      = OV10640_ReadWriteReg;

    status = IssSensorIf_RegisterSensor(prms);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);
}

/*******************************************************************************
 *  Local Functions Definition
 *******************************************************************************
 */

static Int32 OV10640_Start(UInt32 chId, IssSensor_CreateParams *pCreatePrms)
{
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;
    UInt32 cnt, i2cInstId, features, numRegs, nValueTemp;
    UInt8 i2cAddr;
    UInt16 regAddr;
    UInt8 regValue;

    UTILS_assert(NULL != pCreatePrms);

    i2cInstId = pCreatePrms->i2cInstId;
    i2cAddr = pCreatePrms->i2cAddr[chId];
    features = pCreatePrms->enableFeatures[chId];

    gOv10640DeviceObj.lineIntgTimeInMs = 16.66667f;
    gOv10640DeviceObj.pixIntgTimeInMs  = 0.0089f;

    /* First check the Rev ID */
    regAddr = 0x300D;
    status = OV10640_ReadReg(i2cInstId, i2cAddr, &regAddr, &regValue, 1u);
    if ((SYSTEM_LINK_STATUS_SOK == status) &&
        (ISS_SENSOR_OV10640_SUPPORTED_REV == regValue))
    {
        numRegs = sizeof(gOV10640SensorsConfig)/sizeof(IssSensor_ConfigRegs);

        for (cnt = 0u; cnt < numRegs; cnt ++)
        {
            regAddr  = gOV10640SensorsConfig[cnt].regAddr;
            regValue = gOV10640SensorsConfig[cnt].regValue;

            /* Number of lanes in CSI2 format */
            if (0x3444U == regAddr)
            {
                nValueTemp = ((UInt32) regValue & ((UInt32) ~((UInt32) 0x70)));
                regValue   = (UInt8) nValueTemp;

                if (FVID2_VIFW_4LANES == pCreatePrms->videoIfWidth[chId])
                {
                    nValueTemp = (UInt32) regValue | (UInt32) 0x40;
                    regValue   = (UInt8) nValueTemp;
                }
                else if (FVID2_VIFW_3LANES == pCreatePrms->videoIfWidth[chId])
                {
                    nValueTemp = (UInt32) regValue | (UInt32) 0x30;
                    regValue   = (UInt8) nValueTemp;
                }
                else if (FVID2_VIFW_2LANES == pCreatePrms->videoIfWidth[chId])
                {
                    nValueTemp = (UInt32) regValue | (UInt32) 0x20;
                    regValue   = (UInt8) nValueTemp;
                }
                else
                {
                    nValueTemp = (UInt32) regValue | (UInt32) 0x10;
                    regValue   = (UInt8) nValueTemp;
                }
            }

            /* Enable Mirror Shift HDR */
            if (0x3090U == regAddr)
            {
                regValue &= (UInt8) (~(0x0c));
                if (ISS_SENSOR_FEATURE_HFLIP ==
                    (features & ISS_SENSOR_FEATURE_HFLIP))
                {
                    regValue |= 0x4;
                }
                if (ISS_SENSOR_FEATURE_VFLIP ==
                    (features & ISS_SENSOR_FEATURE_VFLIP))
                {
                    regValue |= 0x8;
                }
            }

            /* Enable Mirror Shift in ISP */
            if (0x3291U == regAddr)
            {
                regValue &= (UInt8) (~(0x6));
                if (ISS_SENSOR_FEATURE_HFLIP ==
                    (features & ISS_SENSOR_FEATURE_HFLIP))
                {
                    regValue |= 0x2;
                }
                if (ISS_SENSOR_FEATURE_VFLIP ==
                    (features & ISS_SENSOR_FEATURE_VFLIP))
                {
                    regValue |= 0x4;
                }
            }

            if (0x3119U == regAddr)
            {
                regValue &= (UInt8) (~0x7);

                if(ISS_SENSOR_FEATURE_LINEAR_MODE ==
                    (ISS_SENSOR_FEATURE_LINEAR_MODE & features))
                {
                    regValue |= 0x5;
                }
                else
                {
                    regValue |= 0x4;
                }
            }

            if ((0x3080 == regAddr) || (0x3081 == regAddr))
            {
                if (60 == pCreatePrms->fps[chId])
                {
                    if (0x3080 == regAddr)
                    {
                        regValue = 0x05;
                    }
                    if (0x3081 == regAddr)
                    {
                        regValue = 0xAA;
                    }
                }
                if (30 == pCreatePrms->fps[chId])
                {
                    if (0x3080 == regAddr)
                    {
                        regValue = 0x05;
                    }
                    if (0x3081 == regAddr)
                    {
                        regValue = 0xB4;
                    }
                }
                if (15 == pCreatePrms->fps[chId])
                {
                    if (0x3080 == regAddr)
                    {
                        regValue = 0x0B;
                    }
                    if (0x3081 == regAddr)
                    {
                        regValue = 0x68;
                    }
                }
            }

            /* Convert Registers address and value into 8bit array */
            status = OV10640_WriteReg(i2cInstId, i2cAddr, &regAddr,
                &regValue, 1u);

            if (SYSTEM_LINK_STATUS_SOK != status)
            {
                break;
            }

            BspOsal_sleep(gOV10640SensorsConfig[cnt].delay);
        }

        if (SYSTEM_LINK_STATUS_SOK == status)
        {
            /* By Default WDR Merge output is enabled */
            pCreatePrms->enableFeatures[chId] &=
                ~ISS_SENSOR_FEATURE_LINEAR_MODE;
            pCreatePrms->enableFeatures[chId] |=
                ISS_SENSOR_FEATURE_TWO_PASS_WDR_MODE;
        }
    }

    return (status);
}

static Int32 OV10640_imi_Start(UInt32 chId, IssSensor_CreateParams *pCreatePrms)
{
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;
    UInt32 cnt, i2cInstId, features, numRegs, nValueTemp;
    UInt8 i2cAddr;
    UInt16 regAddr;
    UInt8 regValue;

    UTILS_assert(NULL != pCreatePrms);

    i2cInstId = pCreatePrms->i2cInstId;
    i2cAddr = pCreatePrms->i2cAddr[chId];
    features = pCreatePrms->enableFeatures[chId];

    gOv10640DeviceObj.lineIntgTimeInMs = 16.66667f;
    gOv10640DeviceObj.pixIntgTimeInMs  = 0.0089f;

    /* First check the Rev ID */
    regAddr = 0x300D;
    status = OV10640_ReadReg(i2cInstId, i2cAddr, &regAddr, &regValue, 1u);
    if ((SYSTEM_LINK_STATUS_SOK == status) &&
        (ISS_SENSOR_OV10640_SUPPORTED_REV == regValue))
    {
        numRegs = sizeof(gOV10640ImiSensorsConfig)/sizeof(IssSensor_ConfigRegs);

        for (cnt = 0u; cnt < numRegs; cnt ++)
        {
            regAddr  = gOV10640ImiSensorsConfig[cnt].regAddr;
            regValue = gOV10640ImiSensorsConfig[cnt].regValue;

            /* Number of lanes in CSI2 format */
            if (0x3444U == regAddr)
            {
                nValueTemp = ((UInt32) regValue & ((UInt32) ~((UInt32) 0x70)));
                regValue   = (UInt8) nValueTemp;

                if (FVID2_VIFW_4LANES == pCreatePrms->videoIfWidth[chId])
                {
                    nValueTemp = (UInt32) regValue | (UInt32) 0x40;
                    regValue   = (UInt8) nValueTemp;
                }
                else if (FVID2_VIFW_3LANES == pCreatePrms->videoIfWidth[chId])
                {
                    nValueTemp = (UInt32) regValue | (UInt32) 0x30;
                    regValue   = (UInt8) nValueTemp;
                }
                else if (FVID2_VIFW_2LANES == pCreatePrms->videoIfWidth[chId])
                {
                    nValueTemp = (UInt32) regValue | (UInt32) 0x20;
                    regValue   = (UInt8) nValueTemp;
                }
                else
                {
                    nValueTemp = (UInt32) regValue | (UInt32) 0x10;
                    regValue   = (UInt8) nValueTemp;
                }
            }

            /* Enable Mirror Shift HDR */
            if (0x3090U == regAddr)
            {
                regValue &= (UInt8) (~(0x0c));
                if (ISS_SENSOR_FEATURE_HFLIP ==
                    (features & ISS_SENSOR_FEATURE_HFLIP))
                {
                    regValue |= 0x4;
                }
                if (ISS_SENSOR_FEATURE_VFLIP ==
                    (features & ISS_SENSOR_FEATURE_VFLIP))
                {
                    regValue |= 0x8;
                }
            }

            /* Enable Mirror Shift in ISP */
            if (0x3291U == regAddr)
            {
                regValue &= (UInt8) (~(0x6));
                if (ISS_SENSOR_FEATURE_HFLIP ==
                    (features & ISS_SENSOR_FEATURE_HFLIP))
                {
                    regValue |= 0x2;
                }
                if (ISS_SENSOR_FEATURE_VFLIP ==
                    (features & ISS_SENSOR_FEATURE_VFLIP))
                {
                    regValue |= 0x4;
                }
            }

            if (0x3119U == regAddr)
            {
                regValue &= (UInt8) (~0x7);

                if(ISS_SENSOR_FEATURE_LINEAR_MODE ==
                    (ISS_SENSOR_FEATURE_LINEAR_MODE & features))
                {
                    regValue |= 0x5;
                }
                else
                {
                    regValue |= 0x4;
                }
            }

            /* Convert Registers address and value into 8bit array */
            status = OV10640_WriteReg(i2cInstId, i2cAddr, &regAddr,
                &regValue, 1u);

            if (SYSTEM_LINK_STATUS_SOK != status)
            {
                break;
            }

            BspOsal_sleep(gOV10640ImiSensorsConfig[cnt].delay);
        }
    }

    return (status);
}

static Int32 OV10640_Stop(UInt32 chId,
    IssSensor_CreateParams *pCreatePrms)
{
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;
    UInt16 regAddr;
    UInt8 regValue;

    UTILS_assert(NULL != pCreatePrms);

    regAddr = 0x3012U;

    /* Convert Registers address and value into 8bit array */
    status = OV10640_WriteReg(pCreatePrms->i2cInstId,
        pCreatePrms->i2cAddr[chId], &regAddr, &regValue, 1u);

    if (SYSTEM_LINK_STATUS_SOK == status)
    {
        regValue &= ~(0x1);

        /* Convert Registers address and value into 8bit array */
        status = OV10640_WriteReg(pCreatePrms->i2cInstId,
            pCreatePrms->i2cAddr[chId], &regAddr, &regValue, 1u);
    }

    return (status);
}

static Int32 OV10640_SetAeParams(IssSensor_CreateParams *pCreatePrms,
    IssSensor_AeParams *pAePrms)
{
    Int32 status;
    UInt16 regAddr[2];
    UInt8 regVal[2], analogGain, conversionGain, i2cAddr;
    UInt16 numLinesLong, numLinesVeryShort;
    UInt16 l_vs_exp_ratio = 256U;
    UInt32 nValueTemp, i2cInstId;
    UInt32 features;

    UTILS_assert(NULL != pAePrms);
    UTILS_assert(NULL != pCreatePrms);

    numLinesLong = (UInt16) (pAePrms->exposureTime[0] /
        gOv10640DeviceObj.lineIntgTimeInMs);
    features = pCreatePrms->enableFeatures[pAePrms->chId];
    i2cInstId = pCreatePrms->i2cInstId;
    i2cAddr = pCreatePrms->i2cAddr[pAePrms->chId];

    if (numLinesLong > (UInt16) 1000)
    {
        numLinesLong = (UInt16) 1000;
    }

    /* Write Long Exposure Time*/
    regAddr[0] = 0x30E6U;
    regAddr[1] = 0x30E7U;
    regVal[0] = (UInt8)(numLinesLong >> 8);
    regVal[1] = (UInt8)(numLinesLong & 0xFF);

    status = OV10640_WriteReg(i2cInstId,
                              i2cAddr,
                              regAddr,
                              regVal,
                              (UInt32) 2U);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    if(ISS_SENSOR_FEATURE_LINEAR_MODE !=
        (ISS_SENSOR_FEATURE_LINEAR_MODE & features))
    {

        /* For basic AE, short and very short have same integration time.
           WDR is achieved by QE difference between two pixels*/
        regAddr[0] = 0x30E8U;
        regAddr[1] = 0x30E9U;

        status = OV10640_WriteReg(i2cInstId,
                                  i2cAddr,
                                  regAddr,
                                  regVal,
                                  (UInt32) 2U);
        UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

        /* Setting VS = L/l_vs_exp_ratio. 5 fractional bits */
        numLinesVeryShort = (UInt8)((numLinesLong*32U)/l_vs_exp_ratio);
        if(numLinesVeryShort>128U)
        {
            numLinesVeryShort = 128U;
        }

        /* Write VS register*/
        regAddr[0] = 0x30EAU;
        regVal[0] = numLinesVeryShort;
        status = OV10640_WriteReg(i2cInstId,
                                  i2cAddr,
                                  regAddr,
                                  regVal,
                                  (UInt32) 1U);
        UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);
    }

    if(pAePrms->analogGain > 10000U)
    {
        analogGain       = (UInt8) 3U;
        conversionGain   = (UInt8) 1U;
    }
    else if(pAePrms->analogGain > 5000U)
    {
        analogGain      = (UInt8) 2U;
        conversionGain  = (UInt8) 1U;
    }
    else if(pAePrms->analogGain > 2500U)
    {
        analogGain      = (UInt8) 1U;
        conversionGain  = (UInt8) 1U;
    }
    else if(pAePrms->analogGain > 1000U)
    {
        analogGain      = (UInt8) 0;
        conversionGain  = (UInt8) 1U;
    }
    else
    {
        analogGain      = (UInt8) 0;
        conversionGain  = (UInt8) 0;
    }

    /* Write CG_AGAIN register*/
    regAddr[0] = 0x30EBU;
    nValueTemp = ((UInt32) conversionGain << 7U) |
                 ((UInt32) conversionGain << 6U) |
                 ((UInt32) analogGain << 4U)     |
                 ((UInt32) analogGain << 2U)     |
                  (UInt32) analogGain;

    regVal[0] = (UInt8) nValueTemp;
    status = OV10640_WriteReg(i2cInstId,
                              i2cAddr,
                              regAddr,
                              regVal,
                              (UInt32) 1U);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    return (SYSTEM_LINK_STATUS_SOK);
}

static Int32 OV10640_ReadReg(UInt8         i2cInstId,
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

static Int32 OV10640_WriteReg(UInt8         i2cInstId,
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

static OV10640_GetDccParams(IssSensor_CreateParams *pCreatePrms,
    IssSensor_DccParams *pDccPrms)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 features;

    UTILS_assert(NULL != pCreatePrms);
    UTILS_assert(NULL != pDccPrms);

    features = pCreatePrms->enableFeatures[pDccPrms->chId];

    if (ISS_SENSOR_FEATURE_ONE_PASS_WDR_MODE ==
        (features & ISS_SENSOR_FEATURE_ONE_PASS_WDR_MODE))
    {
        pDccPrms->pDccCfg = (UInt8 *)gOv10640DccCfgSinglePassWdr;
        pDccPrms->dccCfgSize = sizeof(gOv10640DccCfgSinglePassWdr);
    }
    else
    {
        pDccPrms->pDccCfg = (UInt8 *)gOv10640DccCfgLinearAndWdr;
        pDccPrms->dccCfgSize = sizeof(gOv10640DccCfgLinearAndWdr);
    }

    return (status);
}

static OV10640_GetExpParams(IssSensor_CreateParams *pCreatePrms,
    IssSensor_ExposureParams *pExpPrms)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    UTILS_assert(NULL != pCreatePrms);
    UTILS_assert(NULL != pExpPrms);

    {
        pExpPrms->expRatio = ISS_SENSOR_OV10640_DEFAULT_EXP_RATIO;
    }

    return (status);
}

static Void OV10640_InitAewbConfig(
    IssSensor_CreateParams *pCreatePrms,
    AlgorithmLink_IssAewbCreateParams *pAewbPrms)
{
    AlgorithmLink_IssAewbAeDynamicParams *dynPrms = NULL;

    UTILS_assert(NULL != pCreatePrms);
    UTILS_assert(NULL != pAewbPrms);

    /* Set H3A Params */
    pAewbPrms->h3aParams.winCountH = aewbConfig_ov10640.winCfg.horzCount;
    pAewbPrms->h3aParams.winCountV = aewbConfig_ov10640.winCfg.vertCount;
    pAewbPrms->h3aParams.winSizeH  = aewbConfig_ov10640.winCfg.width;
    pAewbPrms->h3aParams.winSizeV  = aewbConfig_ov10640.winCfg.height;
    pAewbPrms->h3aParams.winSkipH  = aewbConfig_ov10640.winCfg.horzIncr;
    pAewbPrms->h3aParams.winSkipV  = aewbConfig_ov10640.winCfg.vertIncr;
    pAewbPrms->numH3aPlanes = 1u;

    pAewbPrms->dataFormat = SensorParams_Ov10640.info.dataFormat;;
    pAewbPrms->mode = (AlgorithmLink_IssAewbMode)SensorParams_Ov10640.info.aewbMode;

    pAewbPrms->dccCameraId = SensorParams_Ov10640.dccId;

    dynPrms = &pAewbPrms->aeDynParams;

    if (ISS_SENSOR_FEATURE_LINEAR_MODE ==
            (ISS_SENSOR_FEATURE_LINEAR_MODE&pCreatePrms->enableFeatures[0]))
    {
        pAewbPrms->isWdrEnable = FALSE;
    }
    else
    {
        pAewbPrms->isWdrEnable = TRUE;
    }
    dynPrms->targetBrightnessRange.min = 35;
    dynPrms->targetBrightnessRange.max = 45;
    dynPrms->targetBrightness = 40;
    dynPrms->threshold = 5;
    dynPrms->enableBlc = TRUE;

    dynPrms->exposureTimeRange[0].min = 100;
    dynPrms->exposureTimeRange[0].max = 16666;
    dynPrms->apertureLevelRange[0].min = 1;
    dynPrms->apertureLevelRange[0].max = 1;
    dynPrms->sensorGainRange[0].min = 1000;
    dynPrms->sensorGainRange[0].max = 1000;
    dynPrms->ipipeGainRange[0].min = 512;
    dynPrms->ipipeGainRange[0].max = 512;

    dynPrms->exposureTimeRange[1].min = 6666;
    dynPrms->exposureTimeRange[1].max = 16666;
    dynPrms->apertureLevelRange[1].min = 1;
    dynPrms->apertureLevelRange[1].max = 1;
    dynPrms->sensorGainRange[1].min = 2500;
    dynPrms->sensorGainRange[1].max = 2500;
    dynPrms->ipipeGainRange[1].min = 512;
    dynPrms->ipipeGainRange[1].max = 512;

    dynPrms->exposureTimeRange[2].min = 8333;
    dynPrms->exposureTimeRange[2].max = 16666;
    dynPrms->apertureLevelRange[2].min = 1;
    dynPrms->apertureLevelRange[2].max = 1;
    dynPrms->sensorGainRange[2].min = 5000;
    dynPrms->sensorGainRange[2].max = 5000;
    dynPrms->ipipeGainRange[2].min = 512;
    dynPrms->ipipeGainRange[2].max = 512;


    dynPrms->exposureTimeRange[3].min = 8333;
    dynPrms->exposureTimeRange[3].max = 16666;
    dynPrms->apertureLevelRange[3].min = 1;
    dynPrms->apertureLevelRange[3].max = 1;
    dynPrms->sensorGainRange[3].min = 10000;
    dynPrms->sensorGainRange[3].max = 10000;
    dynPrms->ipipeGainRange[3].min = 512;
    dynPrms->ipipeGainRange[3].max = 512;


    dynPrms->exposureTimeRange[4].min = 8333;
    dynPrms->exposureTimeRange[4].max = 16666;
    dynPrms->apertureLevelRange[4].min = 1;
    dynPrms->apertureLevelRange[4].max = 1;
    dynPrms->sensorGainRange[4].min = 20000;
    dynPrms->sensorGainRange[4].max = 20000;
    dynPrms->ipipeGainRange[4].min = 512;
    dynPrms->ipipeGainRange[4].max = 512;

    dynPrms->numAeDynParams = 5;

    dynPrms->exposureTimeStepSize = 1;

    pAewbPrms->calbData = NULL;
}
static vpsissIsifGainOfstConfig_t isifWbCfg_ov10640 = 
{
    {0x200, 0x200, 0x200, 0x200},
    0,
    {0,0,0},
    {0,0,0},
};

static Void OV10640_GetIspConfig (
    IssSensor_CreateParams *pCreatePrms,
    IssIspConfigurationParameters *pIspCfg)
{
    UInt32 chId;

    UTILS_assert(NULL != pIspCfg);
    UTILS_assert(NULL != pCreatePrms);

    /* Assuming Channel Id as 0 */
    chId = 0;

    /* Override common settings for specific sensor */
    pIspCfg->aewbCfg = &aewbConfig_ov10640;

    /* Initialize AF config */
    pIspCfg->afCfg = &afConfig_ov10640;

    /* glbceCfg */
    pIspCfg->glbceCfg = &glbceCfg_ov10640;

    /* fwdPerCfg */
    pIspCfg->glbceFwdPerCfg = &glbceFwbPerCfg_ov10640;

    /* revPerCfg */
    pIspCfg->glbceRevPerCfg = &glbceRevPerCfg_ov10640;

    pIspCfg->isifWbCfg = &isifWbCfg_ov10640;
    isifWbCfg_ov10640.gain[0] = 0x200;
    isifWbCfg_ov10640.gain[1] = 0x200;
    isifWbCfg_ov10640.gain[2] = 0x200;
    isifWbCfg_ov10640.gain[3] = 0x200;
    isifWbCfg_ov10640.gainEnable[VPS_ISS_ISIF_OUTPUT_H3A] = (UInt32)FALSE;
    isifWbCfg_ov10640.gainEnable[VPS_ISS_ISIF_OUTPUT_IPIPE] = (UInt32)FALSE;
    isifWbCfg_ov10640.gainEnable[VPS_ISS_ISIF_OUTPUT_MEMORY] = (UInt32)FALSE;
    aewbConfig_ov10640.sumShift = 2;
    if (ISS_SENSOR_FEATURE_ONE_PASS_WDR_MODE ==
            (ISS_SENSOR_FEATURE_ONE_PASS_WDR_MODE &
                pCreatePrms->enableFeatures[chId]))
    {
        /* WDR Config */
        pIspCfg->glbceWdrCfg = &glbceWdrCfg_ov10640;
        isifWbCfg_ov10640.gain[0] = 0x600;
        isifWbCfg_ov10640.gain[1] = 0x600;
        isifWbCfg_ov10640.gain[2] = 0x600;
        isifWbCfg_ov10640.gain[3] = 0x600;
        isifWbCfg_ov10640.gainEnable[VPS_ISS_ISIF_OUTPUT_H3A] = (UInt32)TRUE;
        isifWbCfg_ov10640.gainEnable[VPS_ISS_ISIF_OUTPUT_IPIPE] = (UInt32)FALSE;
        isifWbCfg_ov10640.gainEnable[VPS_ISS_ISIF_OUTPUT_MEMORY] = (UInt32)FALSE;
        aewbConfig_ov10640.sumShift = 0;
    }
}

static Int32 OV10640_ReadWriteReg (
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
        status = OV10640_WriteReg(pCreatePrms->i2cInstId,
            pCreatePrms->i2cAddr[chId], &pReg->regAddr, &regValue, 1u);
    }
    else
    {
        status = OV10640_ReadReg(pCreatePrms->i2cInstId,
            pCreatePrms->i2cAddr[chId], &pReg->regAddr, &regValue, 1u);

        if (SYSTEM_LINK_STATUS_SOK == status)
        {
            pReg->regValue = regValue;
        }
    }

    return (status);
}
