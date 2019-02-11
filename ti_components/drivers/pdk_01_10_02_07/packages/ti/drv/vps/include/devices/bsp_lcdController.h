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
 *  \defgroup BSP_DRV_DEVICE_LCD_CTRL_API LCD controller API
 *
 *  This modules define API specific to LCD controller.
 *
 *  @{
 */

/* TODO - Explain the sequence - refer bsp_videodecoder.h */

/**
 *  \file bsp_lcdController.h
 *
 *  \brief LCD Controller  API.
 */

#ifndef BSP_LCD_CONTROLLER_H_
#define BSP_LCD_CONTROLLER_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/include/fvid2/fvid2_dataTypes.h>
#include <ti/drv/vps/include/devices/bsp_device.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \brief Enum for sensor ID for image sensors
 *          exposure time
 */
typedef enum
{
    BSP_LCD_CTRL_MODE_DE,
    /**< Data Enable mode of operation. */
    BSP_LCD_CTRL_MODE_HSYNC_VSYNC,
    /**< Hsync Vsync mode of operation. */
    BSP_LCD_CTRL_MODE_MAX
                            /**< Max mode. */
} Bsp_LcdCtrlSyncMode;

/**
 *  \brief Max Tlc59108 pwm controllers that can be associated with a single
 *  LCD. */
#define BSP_TLC59108_PWM_DEV_PER_LCD_MAX    (2U)

/**
 *  \brief Power On LCD.
 *
 *  This IOCTL can be used to power on the LCD.
 *
 *  \param cmdArgs       [IN] NULL
 *  \param cmdArgsStatus [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure.
 */
#define IOCTL_BSP_LCDCTRL_POWER_ON                (BSP_LCD_CTRL_IOCTL_BASE + \
                                                   0x00U)

/**
 *  \brief Power Off LCD.
 *
 *  This IOCTL can be used to power off the LCD.
 *
 *  \param cmdArgs       [IN] NULL
 *  \param cmdArgsStatus [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure.
 */
#define IOCTL_BSP_LCDCTRL_POWER_OFF                (BSP_LCD_CTRL_IOCTL_BASE + \
                                                    0x01U)

/**
 *  \brief enable the backlight.
 *
 *  This IOCTL can be used to enable the backlight.
 *
 *  \param cmdArgs       [IN] NULL
 *  \param cmdArgsStatus [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure.
 */
#define IOCTL_BSP_LCDCTRL_ENABLE_BACKLIGHT        (BSP_LCD_CTRL_IOCTL_BASE + \
                                                   0x02U)

/**
 *  \brief Disable the backlight.
 *
 *  This IOCTL can be used to disable the backlight.
 *
 *  \param cmdArgs       [IN] TODO - Fill this
 *  \param cmdArgsStatus [OUT] TODO - Fill this
 *
 *  \return FVID2_SOK on success, else failure.
 */
#define IOCTL_BSP_LCDCTRL_DISABLE_BACKLIGHT        (BSP_LCD_CTRL_IOCTL_BASE + \
                                                    0x03U)

/**
 *  \brief Rotate the image.
 *
 *  This IOCTL can be used to rotate the image updown.
 *
 *  \param cmdArgs       [IN] TODO - Fill this
 *  \param cmdArgsStatus [OUT] TODO - Fill this
 *
 *  \return FVID2_SOK on success, else failure.
 */
#define IOCTL_BSP_LCDCTRL_ROTATE_UPDOWN           (BSP_LCD_CTRL_IOCTL_BASE + \
                                                   0x04U)

/**
 *  \brief control brightness.
 *
 *  This IOCTL can be used to control the brightness of the LCD. Input to this
 *  API is pointer to the brightness value. Value is in percentage(only 0 to
 *  100 is valid)
 *
 *  \param cmdArgs       [IN] UInt32 *
 *  \param cmdArgsStatus [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure.
 */
#define IOCTL_BSP_LCDCTRL_CONTROL_BRIGHTNESS      (BSP_LCD_CTRL_IOCTL_BASE + \
                                                   0x05U)

/**
 *  \brief select the mode.
 *
 *  This IOCTL can be used to select the mode. For supported values
 *  #Bsp_LcdCtrlSyncMode.
 *  cmdArgs is pointer to an integer(valid values #Bsp_LcdCtrlSyncMode).
 *
 *  \param cmdArgs       [IN] UInt32 *
 *  \param cmdArgsStatus [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure.
 */
#define IOCTL_BSP_LCDCTRL_SELECT_MODE_DE_OR_SYNC  (BSP_LCD_CTRL_IOCTL_BASE + \
                                                   0x06U)

/**
 *  \brief Get LCD panel information like timing, polarity etc.
 *
 *  This IOCTL can be used to get the LCD data.
 *
 *  \param cmdArgs       [OUT] Bsp_LcdCtrlPanelInfo *
 *  \param cmdArgsStatus [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure.
 */
#define IOCTL_BSP_LCDCTRL_GET_PANEL_INFO    (BSP_LCD_CTRL_IOCTL_BASE + 0x07U)

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
    UInt32 numDevices;
    /**< Number of TLC59108 devices present in LCD . */
    UInt32 deviceI2cAddr[BSP_TLC59108_PWM_DEV_PER_LCD_MAX];
    /**< I2C device address for each TLC59108 device. */
    UInt32 deviceResetGpio[BSP_TLC59108_PWM_DEV_PER_LCD_MAX];
    /**< GPIO number that is used to reset the device
     *   In case HW does not have any such GPIO then set this to
     *   BSP_VID_DEC_GPIO_NONE. */
} Bsp_LcdCtrlCreateParams;

/**
 *  \brief Status of Fvid2_create().
 */
typedef struct
{
    Int32 retVal;
    /**< FVID2_SOK on success, else failure. */
} Bsp_LcdCtrlCreateStatus;

/**
 *  \brief LCD panel timing and other information.
 */
typedef struct
{
    Fvid2_ModeInfo modeInfo;
    /**< [OUT] LCD typical timing information. */

    UInt32 videoIfWidth;
    /**< [OUT] 8 or 16 or 24-bit video interface mode.
     *   For valid values see #Fvid2_VideoIfWidth. */
    UInt32 videoDataFormat;
    /**< [OUT] LCD input data format. For valid values see #Fvid2_DataFormat. */
    UInt32 videoIfMode;
    /**< [OUT] Interface mode - embedded, discrete sync (HS/VS, AVID/VS etc...).
     *   For valid values see #Fvid2_VideoIfMode. */

    UInt32 vsPolarity;
    /**< Polarity for the vertical sync signal.
     *   For valid values see #Fvid2_VideoIfMode. */
    UInt32 hsPolarity;
    /**< Polarity for the horizontal sync signal.
     *   For valid values see #Fvid2_VideoIfMode. */
    UInt32 actVidPolarity;
    /**< Polarity for the active video signal.
     *   For valid values see #Fvid2_VideoIfMode. */
    UInt32 fidPolarity;
    /**< Polarity for the field id signal. Valid only in case of interlaced
     *   format. For valid values see #Fvid2_Polarity. */
    UInt32 pixelClkPolarity;
    /**< LCD clock polarity - LCD data driven on rising or falling edge of the
     *   pixel clock. For valid values see #Fvid2_Polarity. */
} Bsp_LcdCtrlPanelInfo;

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef BSP_LCD_CONTROLLER_H_ */

/*@} */
