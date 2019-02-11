/*
 *  Copyright (c) Texas Instruments Incorporated 2012-2015
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
 *  \ingroup BSP_DRV_DEVICE_API
 *  \defgroup BSP_DRV_DEVICE_VID_SENSOR_API External Camera Sensor API
 *
 *  This modules define API to capture sensor data using external sensors
 *  like OV10635, OV10630, MT9M024, OV10633, AR0132. Typically the external
 *  Camera sensor interface to the host via one of the VIP ports. I2C is used
 *  to send control commands to the camera Sensor.
 *
 *  User application controls and configures the camera sensor
 *
 *  The following video sensor's are currently supported
 *  - OV10630
 *  - OV10635
 *  - AR0132
 *  - OV2659
 *
 *  The API interface used in the FVID2 interface (See also \ref
 *  BSP_DRV_FVID2_API)
 *
 *  The following FVID2 APIs are supported by video decoder device drivers,
 *
 *
 * - <b> Creating the driver </b> - Fvid2_create()
 *   <table border="1">
 *    <tr>
 *      <th>Parameter</th>
 *      <th>Value</th>
 *    </tr>
 *    <tr>
 *      <td>drvId</td>
 *      <td>
 *      \ref FVID2_VID_SENSOR_OV1063X_DRV <br>
 *      \ref FVID2_VID_SENSOR_LI_OV1063X_DRV <br>
 *      \ref FVID2_VID_SENSOR_MULDES_OV1063X_DRV <br>
 *      \ref FVID2_VID_SENSOR_APT_AR0132_DRV <br>
 *      \ref FVID2_VID_SENSOR_OV2659_DRV <br>
 *      </td>
 *    </tr>
 *    <tr>
 *      <td>instanceId</td>
 *      <td> Set to 0
 *      </td>
 *    </tr>
 *    <tr>
 *      <td>createArgs</td>
 *      <td>
 *      Bsp_VidSensorCreateParams *
 *      </td>
 *    </tr>
 *    <tr>
 *      <td>createStatusArgs</td>
 *      <td>
 *      Bsp_VidSensorCreateStatus *
 *      </td>
 *    </tr>
 *    <tr>
 *      <td>cbParams</td>
 *      <td>
 *      NOT USED, Set to NULL.
 *      </td>
 *    </tr>
 *  </table>
 *  \ref Fvid2_Handle returned by Fvid2_create() is used in subsequent FVID2
 *  APIs
 *
 * - <b> Deleting the driver </b> - Fvid2_delete()
 *  <table border="1">
 *    <tr>
 *      <th>Parameter</th>
 *      <th>Value</th>
 *    </tr>
 *    <tr>
 *      <td>deleteArgs</td>
 *      <td>NOT USED, set to NULL</td>
 *    </tr>
 *  </table>
 *
 * - <b> Starting the driver </b> - Fvid2_start()
 *  <table border="1">
 *    <tr>
 *      <th>Parameter</th>
 *      <th>Value</th>
 *    </tr>
 *    <tr>
 *      <td>cmdArgs</td>
 *      <td>NOT USED, set to NULL</td>
 *    </tr>
 *  </table>
 *
 * - <b> Stopping the driver </b> - Fvid2_stop()
 *  <table border="1">
 *    <tr>
 *      <th>Parameter</th>
 *      <th>Value</th>
 *    </tr>
 *    <tr>
 *      <td>cmdArgs</td>
 *      <td>NOT USED, set to NULL</td>
 *    </tr>
 *  </table>
 *
 * - <b> Controlling the driver </b> - Fvid2_control() <br>
 * All supported camera sensor implement these IOCTLs. <br> <br>
 *
 * Typicall API calling sequence for video decoder in context of video capture
 * application would be like below
 * - Fvid2_create() - create the sensor driver instance and take the sensor to
 * standby
 * - \ref IOCTL_BSP_VID_SENSOR_GET_CHIP_ID - check if device is active
 * - \ref IOCTL_BSP_VID_SENSOR_GET_FEATURES - To get the sensor information and
 * support
 * - \ref IOCTL_BSP_VID_SENSOR_SET_CONFIG - setup the device for a particular
 * mode
 * - \ref Fvid2_start() - Start sensor
 * - \ref Fvid2_stop() - Take sensor to standby
 * - \ref Fvid2_delete() - delete sensor driver device
 * - Delete the capture driver
 * *
 *  @{
 */

/**
 *  \file bsp_videoSensor.h
 *
 *  \brief External Video sensor API.
 */

#ifndef BSP_VIDEO_SENSOR_H_
#define BSP_VIDEO_SENSOR_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/include/devices/bsp_device.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Max devices that can be associated with a single VIP port. */
#define BSP_VID_SENSOR_DEV_PER_PORT_MAX (2U)

/**
 *  \brief Value to use, when it is needed to apply device specific default
 *  setting value.
 */
#define BSP_VID_SENSOR_DEFAULT          ((UInt32) 0xFFFFFFFFU)

/**
 *  \brief Value to use, when it is needed to NOT change a device specific
 *  setting value.
 */
#define BSP_VID_SENSOR_NO_CHANGE        ((UInt32) 0xFFFFFFFEU)

/** \brief Value to use, when there no GPIO is used for device reset. */
#define BSP_VID_SENSOR_GPIO_NONE        ((UInt32) 0xFFFFFFFFU)

/** \brief Video sensor dummy register used for introducing delay in sensor  */
#define BSP_VID_SENSOR_DLY_REG          (0xABCD)

/** \brief Video sensor dummy register mask  */
#define BSP_VID_SENSOR_DLY_REG_MASK     (0xFF00)


/**
 *  \addtogroup BSP_DRV_IOCTL_DEVICE_VID_SENSOR
 *  @{
 */

/**
 *  \brief Get Chip ID.
 *
 *  This IOCTL can be used to get sensor chip information
 *  like chip number, revision, firmware/patch revision.
 *
 *  \param cmdArgs       [IN]  Bsp_VidSensorChipIdParams *
 *  \param cmdArgsStatus [OUT] Bsp_VidSensorChipIdStatus *
 *
 *  \return FVID2_SOK on success, else failure.
 */
#define IOCTL_BSP_VID_SENSOR_GET_CHIP_ID    (BSP_VID_SENSOR_IOCTL_BASE + 0x00U)

/**
 *  \brief Reset sensor chip.
 *
 *  This IOCTL can be used to reset sensor to power ON reset state.
 *
 *
 *  \param cmdArgs       [IN]   NULL
 *  \param cmdArgsStatus [OUT]  NULL
 *
 *  \return FVID2_SOK on success, else failure.
 *
 */
#define IOCTL_BSP_VID_SENSOR_RESET          (BSP_VID_SENSOR_IOCTL_BASE + 0x01U)

/**
 *  \brief To configure sensor
 *          Use this IOCTL to configure sensor
 *          Resolution, FPS, raw/yuv , color Pattern
 *
 *  \param cmdArgs          [IN]     Bsp_VidSensorConfigParams *
 *  \param cmdArgsStatus [OUT]  NULL
 *
 *  \return FVID2_SOK on success, else failure.
 *
 */
#define IOCTL_BSP_VID_SENSOR_SET_CONFIG      (BSP_VID_SENSOR_IOCTL_BASE + 0x02U)

/**
 *  \brief To get the configuration at which sensor is running
 *          Use this IOCTL to get current configuration at which
 *          sensor is currently running
 *
 *  \param cmdArgs          [IN]     Bsp_VidSensorConfigParams *
 *  \param cmdArgsStatus [OUT]  NULL
 *
 *  \return FVID2_SOK on success, else failure.
 *
 */
#define IOCTL_BSP_VID_SENSOR_GET_CONFIG      (BSP_VID_SENSOR_IOCTL_BASE + 0x03U)

/**
 *  \brief To get the sensor supported features
 *
 *  \param cmdArgs          [IN]     Bsp_VidSensorFeatures *
 *  \param cmdArgsStatus [OUT]  NULL
 *
 *  \return FVID2_SOK on success, else failure.
 *
 */
#define IOCTL_BSP_VID_SENSOR_GET_FEATURES (BSP_VID_SENSOR_IOCTL_BASE + 0x04U)

/**
 *  \brief Low level I2C register write. Advance IOCTL, not to be used generally
 *
 *  \param cmdArgs       [IN]   Bsp_VidSensorRegRdWrParams *
 *  \param cmdArgsStatus [OUT]  NULL
 *
 *  \return FVID2_SOK on success, else failure.
 *
 */
#define IOCTL_BSP_VID_SENSOR_REG_WRITE      (BSP_VID_SENSOR_IOCTL_BASE + 0x05U)

/**
 *  \brief Low level I2C register read. Advance IOCTL, not to be used generally
 *
 *  \param cmdArgs       [IN]   Bsp_VidSensorRegRdWrParams *
 *  \param cmdArgsStatus [OUT]  NULL
 *
 *  \return FVID2_SOK on success, else failure.
 *
 */
#define IOCTL_BSP_VID_SENSOR_REG_READ       (BSP_VID_SENSOR_IOCTL_BASE + 0x06U)

/**
 *  \brief IOCTL to flip sensor output in H and/or V direction
 *
 *  \param cmdArgs       [IN]   Bsp_VidSensorFlipParams *
 *  \param cmdArgsStatus [OUT]  NULL
 *
 *  \return FVID2_SOK on success, else failure.
 *
 */
#define IOCTL_BSP_VID_SENSOR_SET_FLIP_PARAMS (BSP_VID_SENSOR_IOCTL_BASE + 0x07U)

/**
 *  \brief IOCTL to set the sensor exposure parameters,
 *         currently only change in exposure time is supported
 *
 *  \param cmdArgs       [IN]   Bsp_VidSensorExposureParams *
 *  \param cmdArgsStatus [OUT]  NULL
 *
 *  \return FVID2_SOK on success, else failure.
 *
 */
#define IOCTL_BSP_VID_SENSOR_SET_EXP_PARAMS (BSP_VID_SENSOR_IOCTL_BASE + 0x08U)

/**
 *  \brief IOCTL to set the sensor gain parameters,
 *         currently only change in analog gain is supported
 *
 *  \param cmdArgs       [IN]   Bsp_VidSensorGainParams *
 *  \param cmdArgsStatus [OUT]  NULL
 *
 *  \return FVID2_SOK on success, else failure.
 *
 */
#define IOCTL_BSP_VID_SENSOR_SET_GAIN_PARAMS (BSP_VID_SENSOR_IOCTL_BASE + 0x09U)

/**
 *  \brief IOCTL to set the exposure ratio from the sensor,
 *         Supported only for the sensor which supports WDR merged output
 *         or multi exposure output
 *
 *  \param cmdArgs       [IN]   Bsp_VidSensorExpRatioParams *
 *  \param cmdArgsStatus [OUT]  NULL
 *
 *  \return FVID2_SOK on success, else failure.
 *
 */
#define IOCTL_BSP_VID_SENSOR_GET_EXP_RATIO_PARAMS (BSP_VID_SENSOR_IOCTL_BASE + \
                                                    0x0aU)

/**
 *  \brief IOCTL to set the WDR params,
 *         Supported only for the sensor which supports WDR merged output
 *         or multi exposure output
 *         Currently supports only WDR Enable/disable parameter
 *
 *  \param cmdArgs       [IN]   Bsp_VidSensorWdrParams *
 *  \param cmdArgsStatus [OUT]  NULL
 *
 *  \return FVID2_SOK on success, else failure.
 *
 */
#define IOCTL_BSP_VID_SENSOR_SET_WDR_PARAMS (BSP_VID_SENSOR_IOCTL_BASE + \
                                                    0x0bU)
/**
 *  \brief IOCTL to get the DCC params,
 *         Used to get the DCC parameters like camera id, pointer to
 *         the bin file, size of the bin file etc.
 *         Supported only for the sensor which supports DCC
 *
 *  \param cmdArgs       [IN]   Bsp_VidSensorDccParams *
 *  \param cmdArgsStatus [OUT]  NULL
 *
 *  \return FVID2_SOK on success, else failure.
 *
 */
#define IOCTL_BSP_VID_SENSOR_GET_DCC_PARAMS (BSP_VID_SENSOR_IOCTL_BASE + \
                                                    0x0cU)

/**
 *  \brief IOCTL to get WDR Offsets for the Line Interleaved mode
 *
 *  \param cmdArgs       [IN]   Bsp_VidSensorOffsetParams *
 *  \param cmdArgsStatus [OUT]  NULL
 *
 *  \return FVID2_SOK on success, else failure.
 *
 */
#define IOCTL_BSP_VID_SENSOR_GET_OFFSET_PARAMS (BSP_VID_SENSOR_IOCTL_BASE + \
                                                    0x0dU)
/**
 *  \brief Reset sensor chip.
 *
 *  This IOCTL can be used to set FPS.
 *
 *
 *  \param cmdArgs       [IN]   NULL
 *  \param cmdArgsStatus [OUT]  NULL
 *
 *  \return FVID2_SOK on success, else failure.
 *
 */
#define IOCTL_BSP_VID_SENSOR_SET_FPS          (BSP_VID_SENSOR_IOCTL_BASE + \
                                                    0x0eU)

/**
 *  \brief Enum for sensor ID for image sensors
 *          exposure time
 */
typedef enum
{
    BSP_VID_SENSOR_OV10635,
    /**< Omnivision OV10635 sensor */
    BSP_VID_SENSOR_OV10630,
    /**< Omnivision OV10630 sensor*/
    BSP_VID_SENSOR_MT9M024,
    /**< Aptina MT9M024 sensor */
    BSP_VID_SENSOR_OV10633,
    /**< Omnivision OV10633 sensor */
    BSP_VID_SENSOR_APT_AR0132,
    /**< Aptina AR0132 sensor */
    BSP_VID_SENSOR_APT_AR0132RCCC,
    /**< Aptina AR0132 RCCC sensor */
    BSP_VID_SENSOR_DM385_AR0132,
    /**< TI DM385 ISP + AR0132 sensor */
    BSP_VID_SENSOR_APT_AR0140,
    /**< Aptina AR0140 sensor */
    BSP_VID_SENSOR_OV10640,
    /**< Omnivision OV10640 sensor */
    BSP_VID_SENSOR_IMX224,
    /**< Sony IMX224 sensor */
    BSP_VID_SENSOR_OV2659,
   /**< Omnivision OV2659 sensor */
    BSP_VID_SENSOR_OV2775,
    /**< Omnivision OV2775 sensor */
    BSP_VID_SENSOR_OV490,
    /**< Omnivision OV490 sensor */
    BSP_VID_SENSOR_MAX
    /**< Max */
} Bsp_VidSensorId;

/**
 *  \brief Enum for specifying WDR mode.
 *         Used only for the sensors supporting WDR.
 *         Typically used for getting correct DCC file for given WDR mode
 *         Also sensor could be configured differently for
 *         different WDR mode.
 */
typedef enum
{
    BSP_VID_SENSOR_WDR_DISABLED = 0x0,
    /**< WDR Disabled */
    BSP_VID_SENSOR_WDR_MODE_1PASS = 0x1,
    /**< Single PASS WDR mode */
    BSP_VID_SENSOR_WDR_MODE_2PASS = 0x2,
    /**< Two PASS WDR mode */
    BSP_VID_SENSOR_WDR_MODE_2PASS_LINE_INTERLEAVED = 0x4,
    /**< Two PASS WDR mode */
    BSP_VID_SENSOR_WDR_MODE_MAX = 0x5
    /**< MAX Sensor Mode */
} Bsp_VidSensorWdrMode;

/**
 *  \brief Enum defining different exposures that sensor outputs.
 */
typedef enum
{
    BSP_VID_SENSOR_EXP_SHORT = 0,
    /**< Short exposure */
    BSP_VID_SENSOR_EXP_LONG,
    /**< Long exposure */
    BSP_VID_SENSOR_EXP_MAX
    /**< End of enum */
} Bsp_VidSensorExposureId;

/* @} */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Structure describing features/capabitlity of sensor
 */
typedef struct
{
    UInt32 sensorId;
    /**< Unique ID of the sensor for differnt types use #Bsp_VidSensorId enum*/
    UInt32 chipId;
    /**< Chip ID*/
    UInt32 chipRevision;
    /**< Chip Reivision*/
    UInt32 firmwareVersion;
    /**< Firmware revision number*/
    UInt32 bayerPattern;
    /**< Output color pattern for the sensor */
    UInt32 activePixelH;
    /**< Active pixels in Horizontal direction*/
    UInt32 activePixelV;
    /**< Active pixels in Vertical direction*/
    UInt32 isEmbededDataSupported;
    /**< Whether sensor supports Embedded data or not */
    UInt32 isManualExposureSupported;
    /**< Whether sensor supports manual exposure configuration data or not
         ioctl IOCTL_BSP_VID_SENSOR_SET_EXP_PARAMS can be used only if
         this flag is set to TRUE */
    UInt32 isEepromDataSupported;
    /**< Whether sensor supports Eeprom data or not */
    UInt32 isSoftStandbySupported;
    /**< This parameter shows whether sensor can be stopped durring operation
     *(enter in software standby) */
    UInt32 isFlipSupported;
    /**< Whether sensor supports horizontal or vertical or both flip
        ioctl IOCTL_BSP_VID_SENSOR_SET_FLIP_PARAMS can be used only if
        this flag is set to TRUE*/
    UInt32 isManualAnalogGainSupported;
    /**< Whether sensor supports manual analog gain contiguration or not */
    UInt32 isWdrModeSupported;
    /**< Whether sensor WDR merged output or not,
         ioctls IOCTL_BSP_VID_SENSOR_SET_WDR_PARAMS and
         IOCTL_BSP_VID_SENSOR_GET_EXP_RATIO_PARAMS can be used only if this
         flag is set to TRUE */
    UInt32 isSetCfgSupported;
    /**< Wether or not SET_CONFIG ioctl supported */
    UInt32 isDccCfgSupported;
    /**< Flag to indicate whether sensor driver DCC configuration,
         Based on this GET_DCC_PARAMS ioclt can be called. */
    UInt32 isOnePassWdrSupported;
    /**< Flag to indicated if sensor driver supports one pass wdr or not,
         This flag can be TRUE only after #isWdrModeSupported is set to TRUE */
} Bsp_VidSensorFeatures;

/**
 *  \brief Structure to configure sensor
 *          This structure is used as an input for IOCTL_BSP_VID_SENSOR_CONFIG
 */
typedef struct
{
    UInt32 standard;
    /**< camer sensor standard.
     * _xx field indicated by Fvid2_Standard which indicates FPS should be
     * ignored while using this structure.
     * OV1063x supports following:
     * FVID2_STD_CIF -  352,  288,
     * FVID2_STD_720P_xx, 1280, 720},
     * FVID2_STD_VGA_xx,  640,  480},
     * FVID2_STD_WXGA_xx, 1280, 800},
     * For valid values see #Fvid2_Standard. */
    UInt32 dataformat;
    /**< RGB or YUV data format. valid values are given below \n
     * OV1063x supports following:
     *   FVID2_DF_YUV422I_UYVY, \n
     *   FVID2_DF_YUV422I_YUYV,  \n
     *   FVID2_DF_YUV422I_YVYU,  \n
     *   FVID2_DF_YUV422I_VYUY,  \n
     *
     *   For valid values see #Fvid2_DataFormat. */
    UInt32 videoIfWidth;
    /**< 8 or 12 or 14 camera interface mode.
     * OV1063x supports following:
     * FVID2_VIFW_8BIT
     * FVID2_VIFW_10BIT
     *
     *   For valid values see #Fvid2_VideoIfWidth. */
    UInt32 fps;
    /**<     frame rate supported values are
     * 15,30,60 , actual configuration will depend on whether sensor supports
     * this or not
     * OV1063x supports following FPS
     * FVID2_FPS_60
     * FVID2_FPS_30
     * FVID2_FPS_25
     * FVID2_FPS_24
     * FVID2_FPS_15
     * For valid values see #Fvid2_VideoFrameRate. */
    UInt32 bpp;
    /**< Bits per pixel supported,
     *   Used only when videoIfWidth is used for specifying CSI2
     *   number of lanes.
     *   8bpp, 10bpp, 12bpp actual configuration will depend on whether
     *   sensor this or not
     * For valid values see #Fvid2_BitsPerPixel. */
     UInt32 width;
     /**< Sensor Output Frame width */
     UInt32 height;
     /**< Sensor Output Frame width */
} Bsp_VidSensorConfigParams;

/**
 *  \brief Sensor register configuration structure.
 */
typedef struct
{
    UInt16 regAddr;
    /**< Register Address to read/write from/to. */
    UInt16 regValue;
    /**< Register Value to be written at the regAddr. */
    UInt16 regMask;
    /**< Register Mask to be used while writing at the regAddr. */
} Bsp_VidSensorConfigRegs;

/**
 *  \brief Arguments for Fvid2_create().
 */
typedef struct
{
    UInt32                   deviceI2cInstId;
    /**< I2C device instance ID to use. */
    UInt32                   numDevicesAtPort;
    /**< Number of devices connected to a video port. */
    UInt32                   deviceI2cAddr[BSP_VID_SENSOR_DEV_PER_PORT_MAX];
    /**< I2C device address for each device. */
    UInt32                   deviceResetGpio[BSP_VID_SENSOR_DEV_PER_PORT_MAX];
    /**< GPIO number that is used to reset the device
     *   In case HW does not have any such GPIO then set this to
     *   BSP_VID_SENSOR_GPIO_NONE. */

    Bsp_VidSensorConfigRegs *sensorCfg;
    /**< Should not be used Address of the Sensor Configuration array. */
    UInt32                   numSensorCfg;
    /**< Size of the sensor configuration array. */
} Bsp_VidSensorCreateParams;

/**
 *  \brief Status of Fvid2_create().
 */
typedef struct
{
    Int32 retVal;
    /**< FVID2_SOK on success, else failure. */
} Bsp_VidSensorCreateStatus;

/**
 * \brief Arguments for \ref IOCTL_BSP_VID_SENSOR_GET_CHIP_ID.
 */
typedef struct
{
    UInt32 deviceNum;
    /**< Device number for which chip ID is required.
     *
     *   Device number will be 0 in most cases, unless multiple devices
     *   are cascaded together like in TVP5158 in which case device num
     *   can be from 0 .. Bsp_VidSensorCreateParams.numDevicesAtPort - 1 */
} Bsp_VidSensorChipIdParams;

/**
 *  \brief Status for \ref IOCTL_BSP_VID_SENSOR_GET_CHIP_ID.
 */
typedef struct
{
    UInt32 chipId;
    /**< Chip ID, value is device specific. */
    UInt32 chipRevision;
    /**< Chip revision, value is device specific. */
    UInt32 firmwareVersion;
    /**< Chip internal patch/firmware revision, value is device specific. */
} Bsp_VidSensorChipIdStatus;

/**
 *  \brief Arguments for \ref IOCTL_BSP_VID_SENSOR_REG_WRITE
 *   and \ref IOCTL_BSP_VID_SENSOR_REG_READ
 */
typedef struct
{
    UInt32  deviceNum;
    /**< Device from which to do I2C read/write
     *
     *   Device number will be 0 in most cases, unless multiple devices
     *   are cascaded together like in TVP5158 in which case device num
     *   can be from 0 .. Bsp_VidSensorCreateParams.numDevicesAtPort-1 */
    UInt32  numRegs;
    /**< Number of registers to read/write. */
    UInt16 *regAddr;
    /**< Array of register addresses. */
    UInt8  *regValue8;
    /**< Array of register value to write or read back. */
    UInt16 *regValue16;
    /**< Array of register value to write or read back */
} Bsp_VidSensorRegRdWrParams;

/**
 *  \brief Arguments for \ref IOCTL_BSP_VID_SENSOR_SET_FLIP_PARAMS
 *
 */
typedef struct
{
    UInt32 hFlip;
    /**< 0: Dont flip horizontally, 1: flip horizontally */

    UInt32 vFlip;
    /**< 0: Dont flip vertically, 1: flip vertically */
} Bsp_VidSensorFlipParams;

/**
 *  \brief Arguments for \ref IOCTL_BSP_VID_SENSOR_SET_EXP_PARAMS
 *
 */
typedef struct
{
    UInt32 exposureTime;
    /**< Sensor Exposure Time */
} Bsp_VidSensorExposureParams;

/**
 *  \brief Arguments for \ref IOCTL_BSP_VID_SENSOR_SET_GAIN_PARAMS
 *
 */
typedef struct
{
    UInt32 analogGain;
    /**< Sensor Analog Gain */
} Bsp_VidSensorGainParams;

/**
 *  \brief Arguments for \ref IOCTL_BSP_VID_SENSOR_GET_EXP_RATIO_PARAMS
 *
 */
typedef struct
{
    UInt32 exposureRatio;
    /**< Sensor Exposure Ratio, used for WDR Merge mode */
} Bsp_VidSensorExpRatioParams;

/**
 *  \brief Arguments for \ref IOCTL_BSP_VID_SENSOR_SET_WDR_PARAMS
 *
 */
typedef struct
{
    Bsp_VidSensorWdrMode wdrMode;
    /**< WDR Mode, used for specifying mode when wdr is enabled. */
} Bsp_VidSensorWdrParams;

/**
 *  \brief Arguments for \ref IOCTL_BSP_VID_SENSOR_GET_DCC_PARAMS
 *
 */
typedef struct
{
    UInt32 dccCameraId;
    /**< DCC camera Id, stored in the dcc bin file,
         Used by the DCC parser for matching */
    const UInt8 *pDccCfg;
    /**< Pointer to the DCC Config file */
    UInt32 dccCfgSize;
    /**< Size of the DCC Config file pointed by pDccCfg */
} Bsp_VidSensorDccParams;

/**
 *  \brief Structure for getting offset of the frame from the large
 *         frame captured from the sensor
 *         Used for Line Interleaved exposure output format.
 */
typedef struct
{
    UInt32 lineOffset[BSP_VID_SENSOR_EXP_MAX];
    /**< Line offset in bytes for different exposures */
    UInt32 pixelOffset[BSP_VID_SENSOR_EXP_MAX];
    /**< Pixel offset in bytes for different exposures */
    UInt32 width;
    /**< Width of the actual images */
    UInt32 height;
    /**< height of the actual images */
} Bsp_VidSensorOffsetParams;


/* ========================================================================== */
/*                         Function Declarations                              */
/* ========================================================================== */

/**
 *  \brief Bsp_VidSensorOffsetParams structure init function.
 *
 *  \param prms   [IN] Pointer to #Bsp_VidSensorOffsetParams structure.
 *
 */
static inline void BspVidSensorConfigParams_Init(
    Bsp_VidSensorConfigParams *prms);

/**
 *  \brief Bsp_VidSensorOffsetParams structure init function.
 *
 *  \param prms   [IN] Pointer to #Bsp_VidSensorOffsetParams structure.
 *
 */
static inline void BspVidSensorOffsetParams_Init(
    Bsp_VidSensorOffsetParams *prms);


/* ========================================================================== */
/*                         Function Definitions                               */
/* ========================================================================== */

static inline void BspVidSensorConfigParams_Init(
    Bsp_VidSensorConfigParams *prms)
{
    if (NULL != prms)
    {
        prms->standard     = FVID2_STD_720P_60;
        prms->dataformat   = FVID2_DF_YUV422I_UYVY;
        prms->videoIfWidth = FVID2_VIFW_12BIT;
        prms->fps          = FVID2_FPS_60;
        prms->bpp          = FVID2_BPP_BITS12;
        prms->width        = 1280U;
        prms->height       = 720U;
    }

    return;
}

static inline void BspVidSensorOffsetParams_Init(
    Bsp_VidSensorOffsetParams *prms)
{
    UInt32  i;

    if (NULL != prms)
    {
        for (i = 0U; i < BSP_VID_SENSOR_EXP_MAX; i++)
        {
            prms->lineOffset[i]  = 0U;
            prms->pixelOffset[i] = 0U;
        }
        prms->width  = 0U;
        prms->height = 0U;
    }

    return;
}

#ifdef __cplusplus
}
#endif

#endif  /*  BSP_VIDEO_SENSOR_H_  */

/* @} */
