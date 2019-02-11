/*
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
 *  \file bspdrv_ar0140Priv.h
 *
 *  \brief ar0140 decoder internal header file.
 */

#ifndef BSPDRV_AR0140_PRIV_H_
#define BSPDRV_AR0140_PRIV_H_

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
#include <ar0140/bspdrv_ar0140.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Driver object state - NOT IN USE. */
#define BSP_AR0140_OBJ_STATE_UNUSED                    (0U)
/** \brief Driver object state - IN USE and IDLE. */
#define BSP_AR0140_OBJ_STATE_IDLE                      (1U)

#define BSP_VID_SENSOR_AR0140_PID_MSB                  (0x24U)
#define BSP_VID_SENSOR_AR0140_PID_LSB                  (0x00U)

#define BSP_AR0140_MIRROR_MODE_ENABLE_MASK             ((uint32_t) 0x1U << 14)
#define BSP_AR0140_FLIP_MODE_ENABLE_MASK               ((uint32_t) 0x1U << 15)

/*
 * AR0140 Register Offsets.
 */

/** < Register to set the operating mode of sensor : Streaming or Still
 *    capture*/
#define BSP_AR0140_SOFTWARE_RESET_REG                   (0x301AU)

#define BSP_AR0140_SOFTWARE_RESET_REG_VAL               (0x10D8U)

#define BSP_AR0140_OPERATING_MODE_REG_VAL               (0x10D8U)

/** < Address of chip ID MSB register */
#define BSP_AR0140_CHIP_ID_REG                          (0x3000U)

/** < Address of Analog Gain Register */
#define BSP_AR0140_ANALOG_GAIN_REG                      (0x3060U)

#define BSP_AR0140_NUM_REGS                             (320U)

#define BSP_AR0140_DEFAULT_EXP_RATIO                    (16U)

#define BSP_AR0140_EXP_RATIO_MULTIPLIER                 (51U)

#define BSP_AR0140_COARD_INTG_TIME_FRAME_SUBTRACT       (52U)

#define BSP_AR0140_DCC_CAMERA_ID                        (140U)

#define BSP_AR0140_SENSORS_DEFAULT_NUM_ELEM             (389U)
#define BSP_AR0140_SENSORS_WDR_NUM_ELEM                 (404U)

#define BSP_AR0140_SENSOR_DLY_IN_MS_AFTER_RESET         (0xA)

/**
 *  \brief AR0140 driver handle object.
 */
typedef struct
{
    UInt32                    state;
    /**< Handle state - used or free. */
    UInt32                    handleId;
    /**< Handle ID, 0..BSP_DEVICE_MAX_HANDLES-1. */
    UInt32                    nDrvId;
    /**< Driver Id - AR0140 */
    BspOsal_SemHandle         lock;
    /**< Driver lock. */
    Bsp_VidSensorCreateParams createPrms;
    /**< Create time arguments. */
    Bsp_VidSensorConfigParams sensorConfig;
    /**< Sensor Configuration  */

    Bsp_VidSensorFlipParams   flipPrms;
    /**< Flipping parameters */
    UInt32                    maxCoarseIntgTime;
    /**< Max Coarse integration time supported by sensor */
    UInt32                    outputHeight;
    /**< Sensor Output Frame Height */

    Float32                   lineIntgTimeInMs;
    Float32                   pixIntgTimeInMs;

    UInt32                    wdrEnable;
} Bsp_ar0140HandleObj;

/**
 *  \brief AR0140 Global driver object.
 */
typedef struct
{
    BspOsal_SemHandle   lock;
    /* Global driver lock. */
    Bsp_ar0140HandleObj handlePool[BSP_DEVICE_MAX_HANDLES];
    /**< Handle objects. */
} Bsp_ar0140Obj;

Int32 Bsp_ar0140GetChipId(Bsp_ar0140HandleObj             *pObj,
                          const Bsp_VidSensorChipIdParams *pPrm,
                          Bsp_VidSensorChipIdStatus       *pStatus);

Int32 Bsp_ar0140SoftwareReset(const Bsp_ar0140HandleObj *pObj);

Int32 Bsp_ar0140SensorStartStop(const Bsp_ar0140HandleObj *pObj,
                                UInt32                     bStartSensor);

Int32 Bsp_ar0140SensorSetConfig(
    Bsp_ar0140HandleObj             *pObj,
    const Bsp_VidSensorConfigParams *cfgPrms);

Int32 Bsp_ar0140SensorConfig(Bsp_ar0140HandleObj     *pObj,
                             Bsp_VidSensorConfigRegs *sensorConfig,
                             UInt32                   numSensorConfigEntries);

Int32 Bsp_ar0140RegWrite(Bsp_ar0140HandleObj              *pObj,
                         const Bsp_VidSensorRegRdWrParams *pPrm);

Int32 Bsp_ar0140RegRead(const Bsp_ar0140HandleObj        *pObj,
                        const Bsp_VidSensorRegRdWrParams *pPrm);

Int32 Bsp_ar0140SetGainParams(const Bsp_ar0140HandleObj     *pObj,
                              const Bsp_VidSensorGainParams *gainPrms);

Int32 Bsp_ar0140SetExpParams(const Bsp_ar0140HandleObj         *pObj,
                             const Bsp_VidSensorExposureParams *expPrms);

Int32 Bsp_ar0140SensorGetExposureRatio(
    const Bsp_ar0140HandleObj   *pObj,
    Bsp_VidSensorExpRatioParams *expRatioPrms);

Int32 Bsp_ar0140SensorSetWdrParams(
    Bsp_ar0140HandleObj          *pObj,
    const Bsp_VidSensorWdrParams *wdrPrms);

Int32 Bsp_ar0140SensorGetDccParams(
    const Bsp_ar0140HandleObj *pObj,
    Bsp_VidSensorDccParams    *dccPrms);

Int32 Bsp_ar0140SensorSetFps(
    const Bsp_ar0140HandleObj *pObj,
    const UInt32     *pFps);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef BSPDRV_AR0140_PRIV_H_  */

