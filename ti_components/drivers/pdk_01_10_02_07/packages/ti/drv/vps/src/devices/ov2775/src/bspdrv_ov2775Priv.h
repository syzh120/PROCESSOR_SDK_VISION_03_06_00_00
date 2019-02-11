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
 *  \file bspdrv_ov2775Priv.h
 *
 *  \brief ov2775 decoder internal header file.
 */

#ifndef BSPDRV_OV2775_PRIV_H_
#define BSPDRV_OV2775_PRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/csl/tistdtypes.h>
#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/bsp_config.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/osal/bsp_osal.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/vps/include/fvid2/fvid2_drvMgr.h>
#include <ti/drv/vps/include/platforms/bsp_platform.h>
#include <ti/drv/vps/include/devices/bsp_videoSensor.h>
#include <ov2775/bspdrv_ov2775.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Driver object state - NOT IN USE. */
#define BSP_OV2775_OBJ_STATE_UNUSED                    (0U)
/** \brief Driver object state - IN USE and IDLE. */
#define BSP_OV2775_OBJ_STATE_IDLE                      (1U)

#define BSP_VID_SENSOR_OV2775_WIDTH                    (1920U)
#define BSP_VID_SENSOR_OV2775_HEIGHT                   (1080U)

#define BSP_VID_SENSOR_OV2775_MAX_EXP_ROWS     (BSP_VID_SENSOR_OV2775_HEIGHT)

/*
 * OV2775 Register Offsets.
 */

/** < Register to set the operating mode of sensor : Streaming or Still
 *    capture*/
#define BSP_OV2775_SOFTWARE_RESET_REG                  (0x3013U)

#define BSP_OV2775_CHIP_ID_UPPER_REG                   (0x300AU)
/** < Address of chip ID MSB register */
#define BSP_OV2775_CHIP_ID_LOWER_REG                   (0x300BU)
/** <  Address of chip ID LSB register */
#define BSP_OV2775_CHIP_ID_REV_ID                      (0x300DU)
/** <  Address of chip ID LSB register */

#define BSP_OV2775_DGC_COARSE_EXP_REG                  (0x30B6U)
#define BSP_OV2775_VS_COARSE_EXP_REG                   (0x30B8U)
#define BSP_OV2775_VS_FRACT_EXP_REG                    (0x30BAU)
#define BSP_OV2775_ANALOG_GAIN_REG                     (0x30BBU)
#define BSP_OV2775_DGAIN_L_REG                         (0x315AU)
#define BSP_OV2775_DGAIN_L_FRACT_REG                   (0x315BU)
#define BSP_OV2775_DGAIN_S_REG                         (0x315CU)
#define BSP_OV2775_DGAIN_S_FRACT_REG                   (0x315DU)
#define BSP_OV2775_DGAIN_VS_REG                        (0x315EU)
#define BSP_OV2775_DGAIN_VS_FRACT_REG                  (0x315FU)

#define BSP_OV2775_WB_GAIN_R_L_REG                     (0x3360U)
#define BSP_OV2775_WB_GAIN_GR_L_REG                    (0x3362U)
#define BSP_OV2775_WB_GAIN_GB_L_REG                    (0x3364U)
#define BSP_OV2775_WB_GAIN_B_L_REG                     (0x3366U)

#define BSP_OV2775_WB_GAIN_R_S_REG                     (0x3368U)
#define BSP_OV2775_WB_GAIN_GR_S_REG                    (0x336AU)
#define BSP_OV2775_WB_GAIN_GB_S_REG                    (0x336CU)
#define BSP_OV2775_WB_GAIN_B_S_REG                     (0x336EU)

#define BSP_OV2775_WB_GAIN_R_VS_REG                    (0x3370U)
#define BSP_OV2775_WB_GAIN_GR_VS_REG                   (0x3372U)
#define BSP_OV2775_WB_GAIN_GB_VS_REG                   (0x3374U)
#define BSP_OV2775_WB_GAIN_B_VS_REG                    (0x3376U)

#define BSP_OV2775_WB_OFFSET_R_L_REG                  (0x3378U)
#define BSP_OV2775_WB_OFFSET_GR_L_REG                 (0x337BU)
#define BSP_OV2775_WB_OFFSET_GB_L_REG                 (0x337EU)
#define BSP_OV2775_WB_OFFSET_B_L_REG                  (0x3381U)

#define BSP_OV2775_WB_OFFSET_R_S_REG                  (0x3384U)
#define BSP_OV2775_WB_OFFSET_GR_S_REG                 (0x3387U)
#define BSP_OV2775_WB_OFFSET_GB_S_REG                 (0x338AU)
#define BSP_OV2775_WB_OFFSET_B_S_REG                  (0x338DU)

#define BSP_OV2775_WB_OFFSET_R_VS_REG                 (0x3390U)
#define BSP_OV2775_WB_OFFSET_GR_VS_REG                (0x3393U)
#define BSP_OV2775_WB_OFFSET_GB_VS_REG                (0x3396U)
#define BSP_OV2775_WB_OFFSET_B_VS_REG                 (0x3399U)


#define BSP_OV2775_VERT_TOTAL_SIZE_REG                 (0x30B2U)

#define BSP_OV2775_DLY_IN_MS                           (10U)

#define BSP_OV2775_STATUS_LINE_MARKER                  (0xDA)

#define BSP_OV2775_STATUS_LINE_FIRST_REG               (0x3000U)

#define BSP_OV2775_STATUS_LINE_DGC_COARSE_EXP          (0x30C9U)
#define BSP_OV2775_STATUS_LINE_VS_COARSE_EXP           (0x30CBU)
#define BSP_OV2775_STATUS_LINE_VS_FRACT_EXP            (0x30CDU)

#define BSP_OV2775_STATUS_LINE_CG_AGAIN_USE            (0x30D0U)

#define BSP_OV2775_STATUS_LINE_DGAIN_L                 (0x3166U)
#define BSP_OV2775_STATUS_LINE_DGAIN_S                 (0x3168U)
#define BSP_OV2775_STATUS_LINE_DGAIN_VS                (0x316AU)

#define BSP_OV2775_OUTPUT_DATA_FMT_MASK                (0x0FU)
#define BSP_OV2775_OUTPUT_DATA_FMT_LINEAR              (0x08U)
#define BSP_OV2775_OUTPUT_DATA_FMT_2x12BIT             (0x01U)
#define BSP_OV2775_OUTPUT_DATA_FMT_2x12_COMB           (0x02U)
#define BSP_OV2775_OUTPUT_DATA_FMT_3x12BIT             (0x05U)
#define BSP_OV2775_OUTPUT_DATA_FMT_2x12_COMB_12BITS_LINEAR  (0x06U)
#define BSP_OV2775_OUTPUT_DATA_FMT_16BIT_COMB_12BITS_LINEAR (0x07U)

#define BSP_OV2775_DCC_CAMERA_ID                       (2775U)

#define BSP_OV2775_READ_MODE_MIRROR_ENABLE_MASK        (0x4U)
#define BSP_OV2775_READ_MODE_FLIP_ENABLE_MASK          (0x8U)

#define BSP_OV2775_ISP_CTRL2_MIRROR_ENABLE_MASK        (0x1U)
#define BSP_OV2775_ISP_CTRL2_FLIP_ENABLE_MASK          (0x2U)

#define BSP_OV2775_GROUP_LENGTH                        (0x3460U)
#define BSP_OV2775_GROUP_CONTROL                       (0x3464U)
#define BSP_OV2775_GROUP_OPER_CONTROL                  (0x3467U)

/** < hold function is bit 15 of address */
#define BSP_OV2775_DGC_COARSE_EXP_REG_HOLD             (BSP_OV2775_DGC_COARSE_EXP_REG|0x8000U)
#define BSP_OV2775_VS_COARSE_EXP_REG_HOLD              (BSP_OV2775_VS_COARSE_EXP_REG|0x8000U)
#define BSP_OV2775_VS_FRACT_EXP_REG_HOLD               (BSP_OV2775_VS_FRACT_EXP_REG|0x8000U)
#define BSP_OV2775_ANALOG_GAIN_REG_HOLD                (BSP_OV2775_ANALOG_GAIN_REG|0x8000U)
#define BSP_OV2775_DGAIN_L_REG_HOLD                    (BSP_OV2775_DGAIN_L_REG|0x8000U)
#define BSP_OV2775_DGAIN_L_FRACT_REG_HOLD              (BSP_OV2775_DGAIN_L_FRACT_REG|0x8000U)
#define BSP_OV2775_DGAIN_S_REG_HOLD                    (BSP_OV2775_DGAIN_S_REG|0x8000U)
#define BSP_OV2775_DGAIN_S_FRACT_REG_HOLD              (BSP_OV2775_DGAIN_S_FRACT_REG|0x8000U)
#define BSP_OV2775_DGAIN_VS_REG_HOLD                   (BSP_OV2775_DGAIN_VS_REG|0x8000U)
#define BSP_OV2775_DGAIN_VS_FRACT_REG_HOLD             (BSP_OV2775_DGAIN_VS_FRACT_REG|0x8000U)

#define BSP_OV2775_WB_GAIN_R_L_REG_HOLD                (BSP_OV2775_WB_GAIN_R_L_REG|0x8000U)
#define BSP_OV2775_WB_GAIN_GR_L_REG_HOLD               (BSP_OV2775_WB_GAIN_GR_L_REG|0x8000U)
#define BSP_OV2775_WB_GAIN_GB_L_REG_HOLD               (BSP_OV2775_WB_GAIN_GB_L_REG|0x8000U)
#define BSP_OV2775_WB_GAIN_B_L_REG_HOLD                (BSP_OV2775_WB_GAIN_B_L_REG|0x8000U)

#define BSP_OV2775_WB_GAIN_R_S_REG_HOLD                (BSP_OV2775_WB_GAIN_R_S_REG|0x8000U)
#define BSP_OV2775_WB_GAIN_GR_S_REG_HOLD               (BSP_OV2775_WB_GAIN_GR_S_REG|0x8000U)
#define BSP_OV2775_WB_GAIN_GB_S_REG_HOLD               (BSP_OV2775_WB_GAIN_GB_S_REG|0x8000U)
#define BSP_OV2775_WB_GAIN_B_S_REG_HOLD                (BSP_OV2775_WB_GAIN_B_S_REG|0x8000U)

#define BSP_OV2775_WB_GAIN_R_VS_REG_HOLD               (BSP_OV2775_WB_GAIN_R_VS_REG|0x8000U)
#define BSP_OV2775_WB_GAIN_GR_VS_REG_HOLD              (BSP_OV2775_WB_GAIN_GR_VS_REG|0x8000U)
#define BSP_OV2775_WB_GAIN_GB_VS_REG_HOLD              (BSP_OV2775_WB_GAIN_GB_VS_REG|0x8000U)
#define BSP_OV2775_WB_GAIN_B_VS_REG_HOLD               (BSP_OV2775_WB_GAIN_B_VS_REG|0x8000U)

#define BSP_OV2775_WB_OFFSET_R_L_REG_HOLD             (BSP_OV2775_WB_OFFSET_R_L_REG|0x8000U)
#define BSP_OV2775_WB_OFFSET_GR_L_REG_HOLD            (BSP_OV2775_WB_OFFSET_GR_L_REG|0x8000U)
#define BSP_OV2775_WB_OFFSET_GB_L_REG_HOLD            (BSP_OV2775_WB_OFFSET_GB_L_REG|0x8000U)
#define BSP_OV2775_WB_OFFSET_B_L_REG_HOLD             (BSP_OV2775_WB_OFFSET_B_L_REG|0x8000U)

#define BSP_OV2775_WB_OFFSET_R_S_REG_HOLD             (BSP_OV2775_WB_OFFSET_R_S_REG|0x8000U)
#define BSP_OV2775_WB_OFFSET_GR_S_REG_HOLD            (BSP_OV2775_WB_OFFSET_GR_S_REG|0x8000U)
#define BSP_OV2775_WB_OFFSET_GB_S_REG_HOLD            (BSP_OV2775_WB_OFFSET_GB_S_REG|0x8000U)
#define BSP_OV2775_WB_OFFSET_B_S_REG_HOLD             (BSP_OV2775_WB_OFFSET_B_S_REG|0x8000U)

#define BSP_OV2775_WB_OFFSET_R_VS_REG_HOLD            (BSP_OV2775_WB_OFFSET_R_VS_REG|0x8000U)
#define BSP_OV2775_WB_OFFSET_GR_VS_REG_HOLD           (BSP_OV2775_WB_OFFSET_GR_VS_REG|0x8000U)
#define BSP_OV2775_WB_OFFSET_GB_VS_REG_HOLD           (BSP_OV2775_WB_OFFSET_GB_VS_REG|0x8000U)
#define BSP_OV2775_WB_OFFSET_B_VS_REG_HOLD            (BSP_OV2775_WB_OFFSET_B_VS_REG|0x8000U)

#define PREC_MULT (1000)
#define MULT256 (256)
#define ROWS_MULT32 (32)
#define CG_GAIN_OFF (0)
#define CG_GAIN_ON (1)
#define AG_ONE (1)
#define AG_TWO (2)
#define AG_FOUR (4)
#define AG_EIGHT (8)

#define VS_MIN_ROWS32  (UInt32)(1.0 * ROWS_MULT32) /* min 1 rows * 32 */
#define VS_MAX_ROWS32  (UInt32)(4.0 * ROWS_MULT32) /* max 4 rows * 32 */

#define CG_GAIN        (UInt32)(11.0)
#define MIN_SVS_DGAIN  (UInt32)(1.094 * PREC_MULT)
#define MIN_L_DGAIN    (UInt32)(2 * PREC_MULT)
#define LVS_CONV_GAIN  (11 * MULT256) /* (~11x, 256=1x) */
#define MIN_L_AGAIN    (UInt32)(1 * PREC_MULT)
#define MIN_SVS_AGAIN  (UInt32)(2 * PREC_MULT)
#define L2S_CONV_RATIO (UInt32)(16.0 / CG_GAIN * PREC_MULT)
#define MIN_TOT_L_GAIN (UInt32)(PREC_MULT * 2.0 * 1.094 * 16.0) /* min total L gain */
#define MIN_AD_L_GAIN  (UInt32)(PREC_MULT * 2.0 * 1.094 * 16.0 / CG_GAIN) /* min A*D gain */
#define MIN_D_L_GAIN   (UInt32)(PREC_MULT * 1.094 * 16.0 / CG_GAIN) /* min D gain */
#define S2L_COR_RATIO  (UInt32)(PREC_MULT * 2.0 * 16.0 / 11.0)
#define MAX_DGAIN      (UInt32)(0x3FFF * PREC_MULT / MULT256)  /* 6.8 format of DGain */
#define MIN_VS_GAIN    (UInt32)(1.094 * 2.0 * PREC_MULT)

#define FRACT_STEP0    (0)
#define FRACT_STEP1    (3)
#define FRACT_STEP2    (18)
#define FRACT_STEP3    (27)

typedef struct {
    UInt32 shutter;  /* shutter speed, [us] */
    UInt32 again;    /* analog gain [mult * 1000] */
    UInt32 exposureTime, analogGain, sensorDGain, convSensorGainFlag, digitalGain;
    UInt32 exposureTimeS, analogGainS, sensorDGainS, convSensorGainFlagS;
    UInt32 exposureTimeVS, analogGainVS, sensorDGainVS, convSensorGainFlagVS;
} OV2775_HDR_Prms;

typedef struct {
    UInt32 nExposureTime;
    UInt32 nAnalogGain;
    UInt32 nDigitalGain;
    Bool   bConvGain;

} Bsp_ov2775ExpoGainParams;

/**
 *  \brief OV2775 driver Bsp_ov2775ExpoGain object.
 */
typedef struct {
    Bsp_ov2775ExpoGainParams longExposure;
    Bsp_ov2775ExpoGainParams shortExposure;
    Bsp_ov2775ExpoGainParams veryShortExposure;
    UInt32  ExposureTime;
    /**< Sensor Exposure Time */
    UInt32 shortExposureTime;
    /**< Sensor Short Exposure Time used in WDR case */
    UInt32 VeryShortExposureTime;
    /**< Sensor Very Short Exposure Time used in WDR case */
    UInt32 realGain;
    /**< Sensor Gain */
    UInt32 realShortGain;
    /**< Sensor Short Gain */
    UInt32 realVeryShortGain;
    /**< Sensor Very Short Gain */
    UInt32 ispGain;
    /**< ISP Digital Gain */
    UInt32 lsExpRatio;
    /**< Long to Short exposure ratio*/
    UInt32 lvsExpRatio;
    /**< Long to Very Short exposure ratio*/
} Bsp_ov2775ExpoGain;
/**
 *  \brief OV2775 driver handle object.
 */
typedef struct
{
    UInt32                    state;
    /**< Handle state - used or free. */
    UInt32                    handleId;
    /**< Handle ID, 0..BSP_DEVICE_MAX_HANDLES-1. */
    UInt32                    nDrvId;
    /**< Driver Id - OV10640 */
    UInt32                    instId;
    /*< Driver instance id */
    BspOsal_SemHandle         lock;
    /**< Driver lock. */
    Bsp_VidSensorCreateParams createPrms;
    /**< Create time arguments. */
    Bsp_VidSensorConfigParams sensorConfig;
    /**< Sensor Configuration */
    UInt32                    wdrMode;
    /**< Flag to indicate whether WDR output is enabled or not. */
    Bsp_VidSensorFlipParams   flipPrms;
    /**< Flipping parameters */
    Float32                   lineIntgTimeInMs;
    Float32                   pixIntgTimeInMs;


} Bsp_ov2775HandleObj;

/**
 *  \brief OV2775 Global driver object.
 */
typedef struct
{
    BspOsal_SemHandle    lock;
    /* Global driver lock. */
    Bsp_ov2775HandleObj handlePool[BSP_DEVICE_MAX_HANDLES];
    /**< Handle objects. */
} Bsp_ov2775Obj;

Int32 Bsp_ov2775GetChipId(Bsp_ov2775HandleObj            *pObj,
                           const Bsp_VidSensorChipIdParams *pPrm,
                           Bsp_VidSensorChipIdStatus       *pStatus);

Int32 Bsp_ov2775SoftwareReset(const Bsp_ov2775HandleObj *pObj);

Int32 Bsp_ov2775SensorStartStop(const Bsp_ov2775HandleObj *pObj,
                                 UInt32                      bStartSensor);

Int32 Bsp_ov2775SensorConfig(
    Bsp_ov2775HandleObj          *pObj,
    const Bsp_VidSensorConfigRegs *sensorConfig);

Int32 Bsp_ov2775SetExpParams(const Bsp_ov2775HandleObj     *pObj,
                             const Bsp_VidSensorExposureParams *expPrms);

Int32 Bsp_ov2775SetGainParams(const Bsp_ov2775HandleObj     *pObj,
                              const Bsp_VidSensorGainParams *gainPrms);

Int32 Bsp_ov2775RegWrite(Bsp_ov2775HandleObj             *pObj,
                          const Bsp_VidSensorRegRdWrParams *pPrm);

Int32 Bsp_ov2775RegRead(const Bsp_ov2775HandleObj       *pObj,
                         const Bsp_VidSensorRegRdWrParams *pPrm);

Int32 Bsp_ov2775SensorGetExposureRatio(
    const Bsp_ov2775HandleObj  *pObj,
    Bsp_VidSensorExpRatioParams *expRatioPrms);

Int32 Bsp_ov2775SensorSetWdrParams(
    Bsp_ov2775HandleObj         *pObj,
    const Bsp_VidSensorWdrParams *wdrPrms);

Int32 Bsp_ov2775SensorGetDccParams(
    const Bsp_ov2775HandleObj *pObj,
    Bsp_VidSensorDccParams     *dccPrms);

Int32 Bsp_ov2775SensorSetFps(
    const Bsp_ov2775HandleObj *pObj,
    const UInt32     *pFps);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef BSPDRV_OV2775_PRIV_H_  */

