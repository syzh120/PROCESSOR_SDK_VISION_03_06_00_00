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
 *
 * \ingroup EXAMPLES_API
 * \defgroup EXAMPLES_LCD_API APIs for controlling external LCD
 *
 * \brief  LCD API to control external LCD
 *
 * @{
 */

/**
 *******************************************************************************
 *
 * \file lcd.h
 *
 * \brief APIs for controlling external LCD
 *
 * \version 0.0 (Jun 2013) : [CM] First version
 * \version 0.1 (Jul 2013) : [CM] Updates as per code review comments
 *
 *******************************************************************************
 */

#ifndef _LCD_H_
#define _LCD_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <include/link_api/system.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *
 * \brief LCD DEVICE INST ID: LCD Instance Id 0
 *
 *  Lcd instance id refers to the default LCD
 *
 *  \param None
 *
 *  \return None
 *
 *******************************************************************************
 */
#define LCD_DEVICE_INST_ID_0         0

/**
 *******************************************************************************
 *
 *
 * \brief LCD DEVICE INST ID: LCD Instance Id 1
 *
 *  Lcd instance id to select the other LCD display
 *
 *  \param None
 *
 *  \return None
 *
 *******************************************************************************
 */
#define LCD_DEVICE_INST_ID_1         1

/**
 *******************************************************************************
 *
 *
 * \brief LCD DEVICE INST ID: LCD Instance Id Max
 *
 *  Maximum number of LCD supported
 *
 *  \param None
 *
 *  \return None
 *
 *******************************************************************************
 */
#define LCD_DEVICE_INST_ID_MAX       2

/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */
typedef enum
{
    LCD_CNTR_DRV,
    /**< LCD Controller driver ID */
    LCD_DRV_ID_MAX = 0xFFFFu,
    /**< Max */
    LCD_DRV_FORCE32BITS = 0x7FFFFFFF
    /**< This should be the last value after the max enumeration value.
    *   This is to make sure enum size defaults to 32 bits always regardless
    *   of compiler.
    */
}Driver_Id;

/*******************************************************************************
 *  Data structure's
 *******************************************************************************
 */

 /**
 *******************************************************************************
 *
 *  \brief  Structure containing LCD create parameters.
 *
 *  This structure is used to set LCD parameters .
 *  This structure is set by the usecase file.
 *  Create params are inParams for Lcd_turnOn fnx.
 *
 *******************************************************************************
*/
typedef struct
{
    Driver_Id                   drvId;
    /**< Set the driver id */
    UInt32                      brightnessValue;
    /**< Brightness Value to be set for the LCD 0 - 100 */
}Lcd_CreateParams;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief This function initialize the LCD and turns on the LCD
 *
 * This will configure Venc with LCD timings
 * In this function LCDObject handle is created with a Fvid2Create and
          Controlled with Fvid2Control
          Lcd power on with             IOCTL IOCTL_BSP_LCDCTRL_POWER_ON .
          Lcd enable backlight          IOCTL_BSP_LCDCTRL_ENABLE_BACKLIGHT
          Lcd select sync mode          IOCTL_BSP_LCDCTRL_SELECT_MODE_DE_OR_SYNC
          and control brightness        IOCTL_BSP_LCDCTRL_CONTROL_BRIGHTNESS
 *
 * \param  lcdInstId  [IN] Lcd id to be turned on
 *
 * \param  createPrm  [IN]Lcd_CreateParams
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Lcd_turnOn(UInt32 lcdInstId, Lcd_CreateParams *createPrm);

/**
 *******************************************************************************
 *
 * \brief This function deInitialize the LCD and turns off the LCD.
 *
 * In this function LCDObject handle is deleted with a Fvid2_delete and
          Controlled with Fvid2_control
          Lcd disable backlight             IOCTL_BSP_LCDCTRL_DISABLE_BACKLIGHT
          Lcd poweroff                      IOCTL_BSP_LCDCTRL_POWER_OFF
 *
 * \param  lcdInstId     [IN] LCD_Device_Instance_ID
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Lcd_turnOff(UInt32 lcdInstId);

/**
 *******************************************************************************
 *
 * \brief This function initializes Max number of LCD Objects.
 *
 * In this function LCDObject handle is set to NULL
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Lcd_init();

/**
 *******************************************************************************
 *
 * \brief This function deinitializes Maximum number of LCD Objects created.
 *
 * In this function LCDObject handle is set to NULL
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Lcd_deInit();


#ifdef __cplusplus
}
#endif

#endif /* #ifndef _LCD_H_ */

/* @} */
