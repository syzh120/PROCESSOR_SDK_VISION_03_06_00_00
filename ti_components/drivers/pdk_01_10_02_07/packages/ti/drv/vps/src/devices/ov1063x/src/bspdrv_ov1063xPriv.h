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
 *  \file bspdrv_ov1063xPriv.h
 *
 *  \brief ov1063x decoder internal header file.
 */

#ifndef BSPDRV_OV1063X_PRIV_H_
#define BSPDRV_OV1063X_PRIV_H_

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
#include <ov1063x/bspdrv_ov1063x.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Driver object state - NOT IN USE. */
#define BSP_OV1063X_OBJ_STATE_UNUSED                    (0U)
/** \brief Driver object state - IN USE and IDLE. */
#define BSP_OV1063X_OBJ_STATE_IDLE                      (1U)

/** Default value @ 0x3003 is read. The value at 0x3003 should be 0x20. */
#define BSP_VID_SENSOR_OV1063X_DEFAULT_RD               (0x20U)

#define BSP_VID_SENSOR_OV10635_PID_MSB                  (0xA6U)
#define BSP_VID_SENSOR_OV10635_PID_LSB                  (0x35U)

#define BSP_VID_SENSOR_OV10630_PID_MSB                  (0xA6U)
#define BSP_VID_SENSOR_OV10630_PID_LSB                  (0x30U)

#define BSP_OV1063X_ACTIVE_PIXELS_H                     (1280U)
/** < NUmber of active pixel in sensor array width*/

#define BSP_OV1063X_ACTIVE_PIXELS_V                     (800U)
/** <Number of active pixel in sensor array height */

#define BSP_VID_SENSOR_OV1063X_DUMMY_LINES_TOP          (2U)
/** < NUmber of dummy lines from the top*/
#define BSP_VID_SENSOR_OV1063X_DUMMY_LINES_BOTTOM       (2U)
/** < NUmber of dummy lines from the Bottom*/

#define BSP_OV1063X_X_CLK                               (24000000U)
/**< XCLK 27MHz */

#define BSP_VID_SENSOR_OV1063X_MAX_LINES_OUTPUT         (814U)
/**< Max number of lines that can be output */

/*
 * OV1063x Register Offsets.
 */
/** \brief Reset register. */
#define BSP_OV1063X_OPERATING_MODE_REG                  (0x0100U)
/** < Register to set the operating mode of sensor : Streaming or Still
 *capture*/
#define BSP_OV1063X_SOFTWARE_RESET_REG                  (0x0103U)
/** < Register address for software reset*/
#define BSP_OV1063X_MIRROR_REG                          (0x381DU)
/** < Register address for mirroring the image : Bit[1:0] : Mirror ON/OFF select
 *
 *
 *                                                                            00
 * : Horizontoal mirror OFF
 *
 *
 *                                                                            01
 * : Not Allowed
 *
 *
 *                                                                            10
 * : Not Allowed
 *
 *
 *                                                                            11
 * : Horizontoal mirror ON*/

#define BSP_OV1063X_FLIP_REG                            (0x381CU)
/** < Register address for flipping the image : Bit[7:6]  : flip ON/OFF select
 *
 *
 *                                                                            00
 * : Vertical flip OFF
 *
 *
 *                                                                            01
 * : Not Allowed
 *
 *
 *                                                                            10
 * : Not Allowed
 *
 *
 *                                                                            11
 * : Vertical flip ON*/

#define BSP_OV1063X_CHIP_ID_UPPER_REG                   (0x300AU)
/** < Address of chip ID MSB register */
#define BSP_OV1063X_CHIP_ID_LOWER_REG                   (0x300BU)
/** <  Address of chip ID LSB register */

#define BSP_OV1063X_MAN_ID_UPPER_REG                    (0x3038U)
/** < Address of Manufacturer ID MSB register */
#define BSP_OV1063X_MAN_ID_LOWER_REG                    (0x3039U)
/** < Address of Manufacturer ID LSB register */
#define BSP_OV1063X_FORMAT_CONTROL_REG                  (0x4300U)
/** < Bit[7:4] : Output Format select
 *          0x3 : YUV mode
 *          0xF : Raw Mode
 *          Others : Not allowed
 *       Bit[3:0] : Pixel order
 *       1000 : YUYV
 *       1001 : YVYU
 *       1010 : UYVY
 *       1011 : VYUY
 */

#define BSP_OV1063X_PLL_MULTIPLIER_REG                  (0x3003U)
/** 0x3003[5:0] */
#define BSP_OV1063X_PLL_DIVIDER_REG                     (0x3004U)
/** 0x3004[6:4]  and 0x3004[2:0] */

#define BSP_OV1063X_PCLK_PLL_DISABLE_REG                (0x3024U)

#define BSP_OV1063X_FIFO_RESET_REG                      (0x301bU)
/** This register (0x301b) should be set to 0xF1 before changing register
 * configurations
 * and should again be set to 0xF0 after configuration */

#define BSP_OV1063X_FIFO_RESET_REG_1                    (0x301aU)

#define BSP_OV1063X_FIFO_RESET_REG_2                    (0x301cU)

#define BSP_OV1063X_INTERFACE_WIDTH_REG                 (0x4605U)
/**< Use this register configure sensor output interface width to
 * 8 bit or 10 bit . Note that this option is valid only for YUV422 output
 * Bit[3]: 0 : 10 bit YUV422 mode
 *          1  : 8 bit YUV422 mode
 */

#define BSP_OV1063X_ANALOG1_TIMING_CTRL_REG             (0x3702U)
#define BSP_OV1063X_ANALOG2_TIMING_CTRL_REG             (0x3703U)
#define BSP_OV1063X_ANALOG3_TIMING_CTRL_REG             (0x3704U)

/* Timing control [0x3800 ~ 0x3821] */
#define BSP_OV1063X_TIMING_HS_X_ADDR_START_UPPER_REG    (0x3800U)
#define BSP_OV1063X_TIMING_HS_X_ADDR_START_LOWER_REG    (0x3801U)
#define BSP_OV1063X_TIMING_VS_Y_ADDR_START_UPPER_REG    (0x3802U)
#define BSP_OV1063X_TIMING_VS_Y_ADDR_START_LOWER_REG    (0x3803U)
#define BSP_OV1063X_TIMING_HW_X_ADDR_END_UPPER_REG      (0x3804U)
#define BSP_OV1063X_TIMING_HW_X_ADDR_END_LOWER_REG      (0x3805U)
#define BSP_OV1063X_TIMING_VH_Y_ADDR_END_UPPER_REG      (0x3806U)
#define BSP_OV1063X_TIMING_VH_Y_ADDR_END_LOWER_REG      (0x3807U)
#define BSP_OV1063X_TIMING_DVPHO_HORZ_WIDTH_UPPER_REG   (0x3808U)
#define BSP_OV1063X_TIMING_DVPHO_HORZ_WIDTH_LOWER_REG   (0x3809U)
#define BSP_OV1063X_TIMING_DVPO_UPPER_REG               (0x380AU)
#define BSP_OV1063X_TIMING_DVPO_LOWER_REG               (0x380BU)
#define BSP_OV1063X_TIMING_HTS_UPPER_REG                (0x380CU)
#define BSP_OV1063X_TIMING_HTS_LOWER_REG                (0x380DU)
#define BSP_OV1063X_TIMING_VTS_UPPER_REG                (0x380EU)
#define BSP_OV1063X_TIMING_VTS_LOWER_REG                (0x380FU)
#define BSP_OV1063X_TIMING_HOFFSET_UPPER_REG            (0x3810U)
#define BSP_OV1063X_TIMING_HOFFSET_LOWER_REG            (0x3811U)
#define BSP_OV1063X_TIMING_VOFFSET_UPPER_REG            (0x3812U)
#define BSP_OV1063X_TIMING_VOFFSET_LOWER_REG            (0x3813U)

#define BSP_OV1063X_VER_SUBSAMPLING_ENABLE_REG          (0x381cU)

#define BSP_OV1063X_HOR_SUBSAMPLING_ENABLE_REG          (0x5005U)

#define BSP_OV1063X_VTS_UPPER_REG                       (0xc518U)
#define BSP_OV1063X_VTS_LOWER_REG                       (0xc519U)

#define BSP_OV1063X_HTS_UPPER_REG                       (0xc51aU)
#define BSP_OV1063X_HTS_LOWER_REG                       (0xc51bU)

#define BSP_OV1063X_Horizontal_CROP_REG                 (0x3621U)

#define BSP_OV1063X_HOR_CROP_0                          (1312U)
#define BSP_OV1063X_HOR_CROP_1                          (768U)
#define BSP_OV1063X_HOR_CROP_2                          (656U)

#define BSP_OV1063X_NUM_REGS                            (585U)
#define BSP_OV1063X_VTS_CONST                           (17820U)

/**
 *  \brief OV1063x driver handle object.
 */
typedef struct
{
    UInt32                    state;
    /**< Handle state - used or free. */
    UInt32                    handleId;
    /**< Handle ID, 0..BSP_DEVICE_MAX_HANDLES-1. */
    UInt32                    nDrvId;
    /**< Driver Id - LI_OV,MULDES_OV, OV */
    BspOsal_SemHandle         lock;
    /**< Driver lock. */
    Bsp_VidSensorCreateParams createPrms;
    /**< Create time arguments. */
    Bsp_VidSensorFeatures     sensorFeature;
    /**< Sensor capabilities */
    Bsp_VidSensorConfigParams sensorConfig;
} Bsp_Ov1063xHandleObj;

/**
 *  \brief OV1063x Global driver object.
 */
typedef struct
{
    BspOsal_SemHandle    lock;
    /* Global driver lock. */
    Bsp_Ov1063xHandleObj handlePool[BSP_DEVICE_MAX_HANDLES];
    /**< Handle objects. */
} Bsp_Ov1063xObj;

Int32 Bsp_ov1063xGetChipId(Bsp_Ov1063xHandleObj            *pObj,
                           const Bsp_VidSensorChipIdParams *pPrm,
                           Bsp_VidSensorChipIdStatus       *pStatus);

Int32 Bsp_ov1063xGetSensorFeatures(const Bsp_Ov1063xHandleObj *pObj,
                                   Bsp_VidSensorFeatures      *pSenFeature);

Int32 Bsp_ov1063xSoftwareReset(const Bsp_Ov1063xHandleObj *pObj);

Int32 Bsp_ov1063xSensorStartStop(const Bsp_Ov1063xHandleObj *pObj,
                                 UInt32                      bStartSensor);

Int32 Bsp_ov1063xSetConfig(Bsp_Ov1063xHandleObj            *pObj,
                           const Bsp_VidSensorConfigParams *configParams);

Int32 Bsp_ov1063xSensorConfig(
    const Bsp_Ov1063xHandleObj *pObj,
    Bsp_VidSensorConfigRegs    *sensorConfig,
    UInt32
    numSensorConfigEntries);

Int32 Bsp_ov1063xRegWrite(Bsp_Ov1063xHandleObj             *pObj,
                          const Bsp_VidSensorRegRdWrParams *pPrm);

Int32 Bsp_ov1063xRegRead(Bsp_Ov1063xHandleObj       *pObj,
                         Bsp_VidSensorRegRdWrParams *pPrm);

Int32 Bsp_ov1063xSetFlipParams(const Bsp_Ov1063xHandleObj    *pObj,
                               const Bsp_VidSensorFlipParams *pPrm);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef BSPDRV_OV1063X_PRIV_H_  */

