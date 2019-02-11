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
 * \file lcd.c
 *
 * \brief  This file has implementataion of APIs for controlling external LCD
 *
 * \version 0.0 (Jun 2013) : [CM] First version
 * \version 0.1 (Jul 2013) : [CM] Updates as per code review comments
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "lcd_pvt.h"
#include <ti/drv/vps/include/boards/bsp_board.h>
#include <ti/drv/vps/include/platforms/bsp_platform.h>

/**
 *******************************************************************************
 * \brief LCD object, stores all LCD related information
 *******************************************************************************
 */
Lcd_Obj gLcdObj[LCD_DEVICE_INST_ID_MAX];

#ifdef __cplusplus
extern "C" {
#endif

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
Int32 Lcd_init()
{
    UInt32  instId;
    Int32  retVal = SYSTEM_LINK_STATUS_SOK;
    for( instId = 0; instId < LCD_DEVICE_INST_ID_MAX; instId++)
    {
        gLcdObj[instId].lcdCtrlhdl = NULL;
        gLcdObj[instId].boardMode  = BSP_BOARD_MODE_VIDEO_24BIT;
    }
    return retVal;
}

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
Int32 Lcd_deInit()
{
    UInt32  instId;
    Int32  retVal = SYSTEM_LINK_STATUS_SOK;
    for( instId = 0; instId < LCD_DEVICE_INST_ID_MAX; instId++)
    {
        if(gLcdObj[instId].lcdCtrlhdl != NULL)
        {
            gLcdObj[instId].lcdCtrlhdl = NULL;
        }
    }
    return retVal;
}

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
Int32 Lcd_turnOn(UInt32 lcdInstId, Lcd_CreateParams *createPrm)
{
    Int32  retVal = SYSTEM_LINK_STATUS_EFAIL;
    UInt32 lcdCtrlInstId, lcdCtrlI2cInstId, lcdCtrlI2cAddr;
    UInt32 lcdCtrlDrvId;
    UInt32 syncMode;
    System_DssDispcOvly dpiPort;

    if(lcdInstId >= LCD_DEVICE_INST_ID_MAX)
    {
        Vps_printf(" LCD: Inst Id is greater than max devices supported !!!\n");
    }
    else
    {
        if(gLcdObj[lcdInstId].lcdCtrlhdl != NULL)
        {
            Vps_printf(" LCD: Inst Id %d is already created \n",lcdInstId);
        }
        else
        {
            do{
                dpiPort = SYSTEM_DSS_DISPC_OVLY_DPI1;
                if ((BSP_PLATFORM_SOC_ID_TDA2EX == Bsp_platformGetSocId()) &&
                    (BSP_PLATFORM_PACKAGE_TYPE_17x17 ==
                                                Bsp_platformGetPackageType()))
                {
                    /* In case of TDA2EX and Package is 17 X 17,
                       LCD is on DPI 3 */
                    dpiPort = SYSTEM_DSS_DISPC_OVLY_DPI3;
                }
                  if( LCD_CNTR_DRV == createPrm->drvId )
                  {
                      lcdCtrlDrvId = FVID2_LCD_CTRL_DRV;
                      syncMode = BSP_LCD_CTRL_MODE_DE;
                  }
                  else
                  {
                      Vps_printf(" LCD: Invalid LCD device ID !!!\n");
                      break;
                  }

                  lcdCtrlInstId = Bsp_boardGetVideoDeviceInstId(
                                          lcdCtrlDrvId,
                                          FVID2_VPS_DCTRL_DRV,
                                          dpiPort);

                  lcdCtrlI2cInstId = Bsp_boardGetVideoDeviceI2cInstId(
                                          lcdCtrlDrvId,
                                          FVID2_VPS_DCTRL_DRV,
                                          dpiPort);

                  lcdCtrlI2cAddr = Bsp_boardGetVideoDeviceI2cAddr(
                                          lcdCtrlDrvId,
                                          FVID2_VPS_DCTRL_DRV,
                                          dpiPort);

                  retVal = Bsp_boardSetPinMux(FVID2_VPS_DCTRL_DRV,
                                dpiPort,
                                gLcdObj[lcdInstId].boardMode);
                  if (SYSTEM_LINK_STATUS_SOK != retVal)
                  {
                      Vps_printf(" LCD: Pinmux setting failed !!!\n");
                      break;
                  }

                  /* Power on LCD controller */
                  retVal = Bsp_boardPowerOnDevice( lcdCtrlDrvId,
                                                   lcdCtrlInstId,
                                                   TRUE);
                  if (SYSTEM_LINK_STATUS_SOK != retVal)
                  {
                      Vps_printf(" LCD: Device Power On failed !!!\n");
                      break;
                  }

                  /* select lcd Controller at board level mux */
                  retVal = Bsp_boardSelectDevice( lcdCtrlDrvId,
                                                  lcdCtrlInstId);
                  if (SYSTEM_LINK_STATUS_SOK != retVal)
                  {
                      Vps_printf(" LCD: Device select failed !!!\n");
                      break;
                  }

                  /* Perform any reset needed at board level */
                  retVal = Bsp_boardResetDevice( lcdCtrlDrvId, lcdCtrlInstId);
                  if (SYSTEM_LINK_STATUS_SOK != retVal)
                  {
                      Vps_printf(" LCD: Device reset failed !!!\n");
                      break;
                  }

                  /* Select specific mode */
                  retVal = Bsp_boardSelectMode(
                             lcdCtrlDrvId,
                             lcdCtrlInstId,
                             gLcdObj[lcdInstId].boardMode);
                  if (SYSTEM_LINK_STATUS_SOK != retVal)
                  {
                      Vps_printf(" LCD: Board select failed !!!\n");
                      break;
                  }

                  /* Verify LCD connectivity */
                  retVal = Bsp_deviceI2cProbeDevice(lcdCtrlI2cInstId,
                                                    lcdCtrlI2cAddr);

                  if(SYSTEM_LINK_STATUS_SOK != retVal)
                  {
                      Vps_printf(" **************************************\n");
                      Vps_printf(" NO LCD CONNECTED OR LCD NOT RESPONDING\n");
                      Vps_printf(" **************************************\n");
                  }

                  gLcdObj[lcdInstId].lcdCtrlCreatePrms.deviceI2cAddr[0]   =
                                                       lcdCtrlI2cAddr;
                  gLcdObj[lcdInstId].lcdCtrlCreatePrms.deviceResetGpio[0] = 0;
                  gLcdObj[lcdInstId].lcdCtrlCreatePrms.deviceI2cInstId    =
                                                       lcdCtrlI2cInstId;
                  gLcdObj[lcdInstId].lcdCtrlCreatePrms.numDevices         = 1;

                  gLcdObj[lcdInstId].lcdCtrlhdl = Fvid2_create(
                            FVID2_LCD_CTRL_DRV,
                            0,
                            &(gLcdObj[lcdInstId].lcdCtrlCreatePrms),
                            NULL,
                            NULL);

                  retVal = Fvid2_control( gLcdObj[lcdInstId].lcdCtrlhdl,
                                          IOCTL_BSP_LCDCTRL_POWER_ON,
                                          NULL,
                                          NULL);

                  if (retVal != SYSTEM_LINK_STATUS_SOK)
                  {
                      Vps_printf(" LCD: Lcd powering on Failed !!!\n");
                      break;
                  }

                  retVal = Fvid2_control( gLcdObj[lcdInstId].lcdCtrlhdl,
                                          IOCTL_BSP_LCDCTRL_ENABLE_BACKLIGHT,
                                          NULL,
                                          NULL);

                  if (retVal != SYSTEM_LINK_STATUS_SOK)
                  {
                      Vps_printf(" LCD: Enabling backlight failed !!!\n");
                      break;
                  }

                  retVal =  Fvid2_control(
                            gLcdObj[lcdInstId].lcdCtrlhdl,
                            IOCTL_BSP_LCDCTRL_SELECT_MODE_DE_OR_SYNC,
                            &syncMode,
                            NULL);

                  if (retVal != SYSTEM_LINK_STATUS_SOK)
                  {
                      Vps_printf(" LCD: Selecting sync mode failed !!!\n");
                      break;
                  }

                  retVal = Fvid2_control( gLcdObj[lcdInstId].lcdCtrlhdl,
                                          IOCTL_BSP_LCDCTRL_CONTROL_BRIGHTNESS,
                                          &(createPrm->brightnessValue),
                                          NULL);

                  if (retVal != SYSTEM_LINK_STATUS_SOK)
                  {
                      Vps_printf(" LCD: Controlling LCD brightness Failed !!!\n");
                      break;
                  }
               }while(0);
           }
       }
       return retVal;
}

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
Int32 Lcd_turnOff(UInt32 lcdInstId)
{
    Int32 retVal = FVID2_EFAIL;

    do{
        /*Disable backlight*/
        retVal = Fvid2_control( gLcdObj[lcdInstId].lcdCtrlhdl,
                                IOCTL_BSP_LCDCTRL_DISABLE_BACKLIGHT,
                                NULL,
                                NULL);

        if (retVal != SYSTEM_LINK_STATUS_SOK)
        {
            Vps_printf(" LCD: Disable backlight failed !!!\n");
            break;
        }
        /*Power off LCD */
        retVal = Fvid2_control( gLcdObj[lcdInstId].lcdCtrlhdl,
                                IOCTL_BSP_LCDCTRL_POWER_OFF,
                                NULL,
                                NULL);

        if (retVal != SYSTEM_LINK_STATUS_SOK)
        {
            Vps_printf(" LCD: Lcd powering Off Failed !!!\n");
            break;
        }

        if (NULL != gLcdObj[lcdInstId].lcdCtrlhdl)
        {
            /* Delete LCD controller handle */
            retVal = Fvid2_delete(gLcdObj[lcdInstId].lcdCtrlhdl, NULL);
            if (retVal != SYSTEM_LINK_STATUS_SOK)
            {
                Vps_printf(" LCD: LCD controller handle delete failed !!!\n");
                break;
            }
            gLcdObj[lcdInstId].lcdCtrlhdl = NULL;
        }
    }while(0);

    return retVal;
}

#ifdef __cplusplus
}
#endif

