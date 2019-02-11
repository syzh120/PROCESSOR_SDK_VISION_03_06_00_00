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
 *  \defgroup BSP_DRV_DEVICE_VID_DEC_API External Video Decoder API
 *
 *  This modules define API to capture video data using external video
 *  decoders like TVP5158, TVP7002. Typically the external video decoders
 *  interface to the host via one of the VIP ports. I2C is used to send
 *  control commands to the video decoder.
 *
 *  User application controls and configures the video decoder
 *  and based on this in turn configures the VIP port.
 *
 *  The following video decoder's are currently supported
 *  - TVP5158 - Multi-CH NTSC/PAL video decoder
 *  - TVP7002 - Component HD video decoder
 *  - SII9127 - HDMI HD video decoder
 *  - ADV7611 - HDMI HD video decoder
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
 *      \ref FVID2_VID_DEC_TVP5158_DRV <br>
 *      \ref FVID2_VID_DEC_TVP7002_DRV <br>
 *      \ref FVID2_VID_DEC_SII9127_DRV <br>
 *      \ref FVID2_VID_DEC_ADV7611_DRV <br>
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
 *      Bsp_VidDecCreateParams *
 *      </td>
 *    </tr>
 *    <tr>
 *      <td>createStatusArgs</td>
 *      <td>
 *      Bsp_VidDecCreateStatus *
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
 * See \ref BSP_DRV_IOCTL_DEVICE_VID_DEC for the list of IOCTLs supported by the
 * driver. <br>
 * All supported video decoders implement these IOCTLs. <br> <br>
 * - TVP5158 supports further additional specific IOCTLs (See \ref
 * BSP_DRV_DEVICE_VID_DEC_TVP5158_API)
 * - SII9153 and TVP7002 do not support any additional specific IOCTLs.
 *
 * Typicall API calling sequence for video decoder in context of video capture
 * application would be like below
 * - Fvid2_create() - create the video decoder device handle
 * - \ref IOCTL_BSP_VID_DEC_GET_CHIP_ID - check if device is active
 * - \ref IOCTL_BSP_VID_DEC_RESET  - reset it
 * - \ref IOCTL_BSP_VID_DEC_SET_VIDEO_MODE - setup the device for a particular
 * mode
 * - \ref IOCTL_BSP_VID_DEC_GET_VIDEO_STATUS - check if video source is detected
 * - Create capture driver based on video decoder setup and video decoder
 * status.
 * - Start capture driver
 * - \ref Fvid2_start() - enable video decoder to start data output to VIP
 * capture port
 * - Do video capture using capture driver.
 * - Stop capture driver
 * - \ref Fvid2_stop() - disable video decoder device
 * - \ref Fvid2_delete() - delete video decoder device
 * - Delete the capture driver
 *
 *  @{
 */

/**
 *  \file bsp_videoDecoder.h
 *
 *  \brief External Video Decoder API.
 */

#ifndef BSP_VIDEO_DECODER_H_
#define BSP_VIDEO_DECODER_H_

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
#define BSP_VID_DEC_DEV_PER_PORT_MAX    (2U)

/**
 *  \brief Value to use, when it is needed to apply device specific default
 *  setting value.
 */
#define BSP_VID_DEC_DEFAULT             ((UInt32) 0xFFFFFFFFU)

/**
 *  \brief Value to use, when it is needed to NOT change a device specific
 *  setting value.
 */
#define BSP_VID_DEC_NO_CHANGE           ((UInt32) 0xFFFFFFFEU)

/** \brief Value to use, when there no GPIO is used for device reset. */
#define BSP_VID_DEC_GPIO_NONE           ((UInt32) 0xFFFFFFFFU)

/**
 *  \addtogroup BSP_DRV_IOCTL_DEVICE_VID_DEC
 *  @{
 */

/**
 *  \brief Get Chip ID.
 *
 *  This IOCTL can be used to get video decoder chip information
 *  like chip number, revision, firmware/patch revision.
 *
 *  \param cmdArgs       [IN]  Bsp_VidDecChipIdParams *
 *  \param cmdArgsStatus [OUT] Bsp_VidDecChipIdStatus *
 *
 *  \return FVID2_SOK on success, else failure.
 */
#define IOCTL_BSP_VID_DEC_GET_CHIP_ID       (BSP_VID_DEC_IOCTL_BASE + 0x00U)

/**
 *  \brief Reset video decoder chip.
 *
 *  This IOCTL can be used to reset video decoder chip to power ON reset state.
 *
 *
 *  \param cmdArgs       [IN]   NULL
 *  \param cmdArgsStatus [OUT]  NULL
 *
 *  \return FVID2_SOK on success, else failure.
 *
 */
#define IOCTL_BSP_VID_DEC_RESET             (BSP_VID_DEC_IOCTL_BASE + 0x01U)

/**
 *  \brief Configure video decoder video mode.
 *
 *  This IOCTL can be used to configure video decoder in a specific mode
 *  like YUV output, 16-bit output, input standard selection, auto detection
 *  of input standard and so on.
 *
 *  When standard is set as AUTO-DETECT, this API will wait internally until
 *  video is detected (upto a timeout limit set by user).
 *
 *  Once the API returns IOCTL_BSP_VID_DEC_GET_VIDEO_STATUS can be used
 *  to get the detected video standard information.
 *
 *  \param cmdArgs       [IN]  Bsp_VidDecVideoModeParams *
 *  \param cmdArgsStatus [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure.
 *
 */
#define IOCTL_BSP_VID_DEC_SET_VIDEO_MODE    (BSP_VID_DEC_IOCTL_BASE + 0x02U)

/**
 *  \brief Get video status.
 *
 *  This IOCTL can be used to detect current video status like video standard
 *  widthxheight, interlaced or progressive video etc.
 *
 *  Note, this API will not wait until video is detected. User can call this
 *  API repeatedly if they want to wait until video is detected.
 *
 *  This API can be called independently for every channel in case of
 *  multi-channel video decoders.
 *
 *  This API can be called only after calling
 *  IOCTL_BSP_VID_DEC_SET_VIDEO_MODE with appropriate parameters.
 *
 *  \param cmdArgs       [IN]   Bsp_VidDecVideoStatusParams *
 *  \param cmdArgsStatus [OUT]  Bsp_VidDecVideoStatus *
 *
 *  \return FVID2_SOK on success, else failure.
 *
 */
#define IOCTL_BSP_VID_DEC_GET_VIDEO_STATUS  (BSP_VID_DEC_IOCTL_BASE + 0x03U)

/**
 *  \brief Set video color processing related parameters.
 *
 *  This IOCTL can be called separetly for each channel.
 *
 *  \param cmdArgs       [IN]   Bsp_VidDecColorParams *
 *  \param cmdArgsStatus [OUT]  NULL
 *
 *  \return FVID2_SOK on success, else failure.
 *
 */
#define IOCTL_BSP_VID_DEC_SET_VIDEO_COLOR   (BSP_VID_DEC_IOCTL_BASE + 0x04U)

/**
 *  \brief Low level I2C register write.
 *
 *  \param cmdArgs       [IN]   Bsp_VidDecRegRdWrParams *
 *  \param cmdArgsStatus [OUT]  NULL
 *
 *  \return FVID2_SOK on success, else failure.
 *
 */
#define IOCTL_BSP_VID_DEC_REG_WRITE         (BSP_VID_DEC_IOCTL_BASE + 0x08U)

/**
 *  \brief Low level I2C register read.
 *
 *  \param cmdArgs       [IN]   Bsp_VidDecRegRdWrParams *
 *  \param cmdArgsStatus [OUT]  NULL
 *
 *  \return FVID2_SOK on success, else failure.
 *
 */
#define IOCTL_BSP_VID_DEC_REG_READ          (BSP_VID_DEC_IOCTL_BASE + 0x09U)

/* @} */

/**
 *  \brief Video system
 */
typedef enum
{
    BSP_VID_DEC_VIDEO_SYSTEM_NTSC = 0,
    /**< Interlaced, NTSC system, 720x240 per field. */
    BSP_VID_DEC_VIDEO_SYSTEM_PAL,
    /**< Interlaced, PAL system, 720x288 per field. */
    BSP_VID_DEC_VIDEO_SYSTEM_AUTO_DETECT,
    /**< Auto-detect NTSC or PAL system. */
    BSP_VID_DEC_VIDEO_SYSTEM_NONE,
    /**< Neither NTSC nor PAL system. */
    BSP_VID_DEC_VIDEO_SYSTEM_MAX
    /**< Max video system */
} Bsp_VidDecVideoSystem;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Arguments for Fvid2_create().
 */
typedef struct
{
    UInt32 deviceI2cInstId;
    /**< I2C device instance ID to use. */
    UInt32 numDevicesAtPort;
    /**< Number of devices connected to a video port. */
    UInt32 deviceI2cAddr[BSP_VID_DEC_DEV_PER_PORT_MAX];
    /**< I2C device address for each device. */
    UInt32 deviceResetGpio[BSP_VID_DEC_DEV_PER_PORT_MAX];
    /**< GPIO number that is used to reset the device
     *   In case HW does not have any such GPIO then set this to
     *   BSP_VID_DEC_GPIO_NONE. */
} Bsp_VidDecCreateParams;

/**
 *  \brief Status of Fvid2_create().
 */
typedef struct
{
    Int32 retVal;
    /**< FVID2_SOK on success, else failure. */
} Bsp_VidDecCreateStatus;

/**
 * \brief Arguments for \ref IOCTL_BSP_VID_DEC_GET_CHIP_ID
 */
typedef struct
{
    UInt32 deviceNum;
    /**< Device number for which chip ID is required.
     *
     *   Device number will be 0 in most cases, unless multiple devices
     *   are cascaded together like in TVP5158 in which case device num
     *   can be from 0 .. Bsp_VidDecCreateParams.numDevicesAtPort - 1 */
} Bsp_VidDecChipIdParams;

/**
 *  \brief Status for \ref IOCTL_BSP_VID_DEC_GET_CHIP_ID
 */
typedef struct
{
    UInt32 chipId;
    /**< Chip ID, value is device specific. */
    UInt32 chipRevision;
    /**< Chip revision, value is device specific. */
    UInt32 firmwareVersion;
    /**< Chip internal patch/firmware revision, value is device specific. */
} Bsp_VidDecChipIdStatus;

/**
 *  \brief Arguments for \ref IOCTL_BSP_VID_DEC_SET_VIDEO_MODE
 */
typedef struct
{
    UInt32 videoIfWidth;
    /**< 8 or 16 or 24-bit video interface mode.
     *   For valid values see #Fvid2_VideoIfWidth. */

    UInt32 videoDataFormat;
    /**< RGB or YUV data format. valid values are given below \n
     *   FVID2_DF_YUV422P, ( 'P' is not relavent for input data format) \n
     *   FVID2_DF_YUV444P, ( 'P' is not relavent for input data format) \n
     *   FVID2_DF_RGB24_888.
     *
     *   For valid values see #Fvid2_DataFormat. */

    UInt32 standard;
    /**< Video decoder video standard.
     *
     *   When set to FVID2_STD_AUTO_DETECT the video resolution
     *   will be auto-detected but user will still need to provide other
     *   parameters like videoIfWidth, videoDataFormat, videoIfMode
     *   For valid values see #Fvid2_Standard. */

    UInt32 videoIfMode;
    /**< Multiplexing mode, line mux or pixel mux or split line mode.
     *   For valid values see #Fvid2_VideoIfMode. */

    UInt32 videoSystem;
    /**< Video system, NTSC or PAL or NONE or Auto-detect.
     *
     *   When set to BSP_VID_DEC_VIDEO_SYSTEM_AUTO_DETECT the video
     *   system NTSC or PAL will be auto-detected but user will
     *   still need to provide other parameters like videoIfWidth,
     *   videoDataFormat, videoIfMode, standard
     *   For valid values see #Bsp_VidDecVideoSystem. */

    Int32  videoAutoDetectTimeout;
    /**< Auto-detect timeout, when auto-detecting standard in OS ticks.
     *   To wait forever, need to provide FVID2_TIMEOUT_FOREVER.
     *
     *   Valid only when
     *
     *   Bsp_VidDecVideoModeParams.standard
     *     = FVID2_STD_AUTO_DETECT
     *
     *   OR
     *
     *   Bsp_VidDecVideoModeParams.videoSystem
     *     = BSP_VID_DEC_VIDEO_SYSTEM_AUTO_DETECT */

    UInt32 videoCropEnable;
    /**< Applicable only for D1/CIF capture input.
     *   Crops 720 to 704 and 360 to 352 at video decoder.
     *   Only applied if video decoder supports this mode. */
} Bsp_VidDecVideoModeParams;

/**
 *  \brief Arguments for \ref IOCTL_BSP_VID_DEC_GET_VIDEO_STATUS
 */
typedef struct
{
    UInt32 channelNum;
    /**< Channel number for which status is needed
     *
     *   Channel number will be 0 in most cases, unless the device is capable of
     *   multi-channel capture like in TVP5158 in which case channel number
     *   can be from 0 .. Device specific max channels-1 */
} Bsp_VidDecVideoStatusParams;

/**
 *  \brief Status for \ref IOCTL_BSP_VID_DEC_GET_VIDEO_STATUS
 */
typedef struct
{
    UInt32 isVideoDetect;
    /**<  TRUE: Video signal is present, FALSE: no video signal */

    UInt32 frameWidth;
    /**< Frame or field width in pixels
     *
     * This is detected video signal frame or field width.
     * Further change in width or height due to additional
     * cropping, scaling like CIF, HALF-D1 is not accoutned for in this field */

    UInt32 frameHeight;
    /**< Frame or field height in lines
     *
     * This is detected video signal frame or field height.
     * Further change in width or height due to additional
     * cropping, scaling like CIF, HALF-D1 is not accoutned for in this field */

    UInt32 frameInterval;
    /**< Interval between two fields or frames in micro-seconds */

    UInt32 isInterlaced;
    /**< TRUE: Source is Interlaced, FALSE: Source is Progressive */
} Bsp_VidDecVideoStatus;

/**
 *  \brief Arguments for \ref IOCTL_BSP_VID_DEC_SET_VIDEO_COLOR
 */
typedef struct
{
    UInt32 channelNum;
    /**< Channel number for which these parameters are to be applied.
     *
     *   Channel number will be 0 in most cases, unless the device is capable
     *   of multi-channel capture like in TVP5158 in which case channel number
     *   can be from 0 .. Device specific max channels-1. */

    UInt32 videoBrightness;
    /**< Video brightness, value is device specific.
     *
     *   This field can be set to \ref BSP_VID_DEC_DEFAULT when device
     *   specific default needs to be applied in current IOCTL call.
     *
     *   This field can be set to \ref BSP_VID_DEC_NO_CHANGE when last
     *   applied value needs to be retained in current IOCTL call. */

    UInt32 videoContrast;
    /**< Video contrast, value is device specific.
     *
     *   This field can be set to \ref BSP_VID_DEC_DEFAULT when device
     *   specific default needs to be applied in current IOCTL call.
     *
     *   This field can be set to \ref BSP_VID_DEC_NO_CHANGE when last
     *   applied value needs to be retained in current IOCTL call. */

    UInt32 videoSaturation;
    /**< Video saturation, value is device specific.
     *
     *   This field can be set to \ref BSP_VID_DEC_DEFAULT when device
     *   specific default needs to be applied in current IOCTL call.
     *
     *   This field can be set to \ref BSP_VID_DEC_NO_CHANGE when last
     *   applied value needs to be retained in current IOCTL call. */

    UInt32 videoSharpness;
    /**< Video sharpness, value is device specific.
     *
     *   This field can be set to \ref BSP_VID_DEC_DEFAULT when device
     *   specific default needs to be applied in current IOCTL call.
     *
     *   This field can be set to \ref BSP_VID_DEC_NO_CHANGE when last
     *   applied value needs to be retained in current IOCTL call. */

    UInt32 videoHue;
    /**< Video hue, value is device specific.
     *
     *   This field can be set to \ref BSP_VID_DEC_DEFAULT when device
     *   specific default needs to be applied in current IOCTL call.
     *
     *   This field can be set to \ref BSP_VID_DEC_NO_CHANGE when last
     *   applied value needs to be retained in current IOCTL call. */
} Bsp_VidDecColorParams;

/**
 *  \brief Arguments for \ref IOCTL_BSP_VID_DEC_REG_WRITE
 *   and \ref IOCTL_BSP_VID_DEC_REG_READ
 */
typedef struct
{
    UInt32 deviceNum;
    /**< Device from which to do I2C read/write
     *
     *   Device number will be 0 in most cases, unless multiple devices
     *   are cascaded together like in TVP5158 in which case device num
     *   can be from 0 .. Bsp_VidDecCreateParams.numDevicesAtPort-1 */
    UInt32 numRegs;
    /**< Number of registers to read/write. */
    UInt8 *regAddr;
    /**< Array of register addresses. */
    UInt8 *regValue8;
    /**< Array of register value to write or read back. */
} Bsp_VidDecRegRdWrParams;

/* ========================================================================== */
/*                         Functions                                          */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef BSP_VIDEO_DECODER_H_ */

/* @} */
