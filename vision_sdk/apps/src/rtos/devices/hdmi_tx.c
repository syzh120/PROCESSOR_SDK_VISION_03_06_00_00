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
 * \file hdmi_tx.c
 *
 * \brief  This file has the implementataion of hdmi transmitter Control API
 *
 *         APIs can be used to control hdmi transmitter.
 *         Drivers for hdmi transmitter can be part of BSP or any other package.
 *
 *
 * \version 0.0 (Nov 2013) : [CM] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <src/include/hdmi_tx.h>



/**
 *******************************************************************************
 *
 * \brief Set the default Create Params for Hdmi transmitter.
 *
 * \param  createParams   [IN] Create parameters for hdmi transmitter
 *
 *******************************************************************************
*/
Void HdmiTx_CreateParams_Init(HdmiTx_CreateParams *createParams)
{
    createParams->hdmiTxId        =  HDMI_TX_SII_9022A;
    createParams->standard        =  SYSTEM_STD_1080P_60;
    createParams->dssOvlyId       =  SYSTEM_DSS_DISPC_OVLY_DPI1;
    createParams->boardMode       =  BSP_BOARD_MODE_VIDEO_24BIT;
}

/**
 *******************************************************************************
 *
 * \brief Create function to create hdmi transmitter.
 *
 *        Creates the hdmi transmitter handle using bsp function calls.
 *
 * \param  createParams   [IN] Create parameters for hdmi transmitter
 *
 * \param  createStatus   [OUT] Status
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 HdmiTx_create(HdmiTx_CreateParams *createParams,
                      HdmiTx_CreateStatus *createStatus)
{
    Int32  retVal = SYSTEM_LINK_STATUS_EFAIL;
    UInt32 vidEncInstId, vidEncI2cInstId, vidEncI2cAddr;
    UInt32 vidEncDrvId;
    Bsp_VidEncCreateParams encCreateParams;
    Bsp_Sii9022aHpdParams hpdPrms;
    Bsp_Sii9022aHdmiChipId hdmiId;
    Bsp_VidEncConfigParams modePrms;
    Bsp_VidEncCreateStatus encCreateStatus;
    UInt8 regAddr;
    UInt8 regData;

    createParams->hdmiTxHandle = NULL;

    retVal = Bsp_boardSetPinMux(FVID2_VPS_DCTRL_DRV,
                                createParams->dssOvlyId,
                                createParams->boardMode);
    if (FVID2_SOK != retVal)
    {
        Vps_printf(" HDMI_TX: Pin Muxing Failed !!! \n");
    }

    if ((BSP_BOARD_TDA3XX_RVP_ALPHA == Bsp_boardGetId()) ||
        (BSP_BOARD_TDA3XX_RVP_BETA == Bsp_boardGetId()) ||
        (BSP_BOARD_TDA3XX_RVP_A == Bsp_boardGetId()) ||
        (BSP_BOARD_TDA3XX_D3_SK == Bsp_boardGetId()))
    {
        /* TFP410 enable */
        /* enable TFP410 output, bit 7 of Expander set to output */
        regAddr = 7;
        regData = 0x0;
        retVal = Bsp_deviceRead8(
                            BSP_DEVICE_I2C_INST_ID_1,
                            RVP_IOEXP_I2C_ADDR,
                            &regAddr,
                            &regData,
                            1);
        regData &= 0x7F;
        retVal = Bsp_deviceWrite8(
                            BSP_DEVICE_I2C_INST_ID_1,
                            RVP_IOEXP_I2C_ADDR,
                            &regAddr,
                            &regData,
                            1);
        if(0 != retVal)
        {
            Vps_printf(" HDMI_TX:error writing to gpio expander");
        }

        /* Set bit 7 of expander high */
        regAddr = 3;
        retVal = Bsp_deviceRead8(
                            BSP_DEVICE_I2C_INST_ID_1,
                            RVP_IOEXP_I2C_ADDR,
                            &regAddr,
                            &regData,
                            1);
        regData |= 0x80;
        retVal = Bsp_deviceWrite8(
                            BSP_DEVICE_I2C_INST_ID_1,
                            RVP_IOEXP_I2C_ADDR,
                            &regAddr,
                            &regData,
                            1);
        if(0 != retVal)
        {
            Vps_printf(" HDMI_TX:error writing to gpio expander");
        }
    }
    else
    {
        /* SII create */
        createStatus->retVal    = SYSTEM_LINK_STATUS_EFAIL;
        vidEncDrvId             = FVID2_VID_ENC_SII9022A_DRV;

        if(createParams->hdmiTxId == HDMI_TX_SII_9022A)
        {
            vidEncDrvId         = FVID2_VID_ENC_SII9022A_DRV;
        }

         vidEncInstId = Bsp_boardGetVideoDeviceInstId(
            vidEncDrvId,
            FVID2_VPS_DCTRL_DRV,
            SYSTEM_DSS_DISPC_OVLY_DPI1);

        vidEncI2cInstId = Bsp_boardGetVideoDeviceI2cInstId(
            vidEncDrvId,
            FVID2_VPS_DCTRL_DRV,
            createParams->dssOvlyId);

        vidEncI2cAddr = Bsp_boardGetVideoDeviceI2cAddr(
            vidEncDrvId,
            FVID2_VPS_DCTRL_DRV,
            createParams->dssOvlyId);

        /* Power on Video Encoder */
        retVal = Bsp_boardPowerOnDevice(vidEncDrvId, vidEncInstId, TRUE);
        if (FVID2_SOK != retVal)
        {
            Vps_printf(" HDMI_TX: Device Power On failed !!!\n");
        }

        /* select Video Encoder at board level mux */
        retVal = Bsp_boardSelectDevice(vidEncDrvId, vidEncInstId);
        if (FVID2_SOK != retVal)
        {
            Vps_printf(" HDMI_TX: Device select failed !!!\n");
        }

        /* Perform any reset needed at board level */
        retVal = Bsp_boardResetDevice(vidEncDrvId, vidEncInstId);
        if (FVID2_SOK != retVal)
        {
            Vps_printf(" HDMI_TX: Device reset failed !!!\n");
        }

        /* Select specific mode */
        retVal = Bsp_boardSelectMode(
                     vidEncDrvId,
                     vidEncInstId,
                     createParams->boardMode);
        if (FVID2_SOK != retVal)
        {
            Vps_printf(" HDMI_TX: Device select mode failed !!!\n");
        }

        if (FVID2_SOK == retVal)
        {
           /* Open HDMI Tx */
           encCreateParams.deviceI2cInstId = vidEncI2cInstId;
           encCreateParams.deviceI2cAddr = vidEncI2cAddr;
           encCreateParams.inpClk = 0u;
           encCreateParams.hotPlugGpioIntrLine = 0u;
           encCreateParams.clkEdge = FALSE;

           createParams->hdmiTxHandle = Fvid2_create(
                                    vidEncDrvId,
                                    0u,
                                    &encCreateParams,
                                    &encCreateStatus,
                                    NULL);
           if (NULL == createParams->hdmiTxHandle)
           {
               Vps_printf( " HDMI_TX: "
                         " ERROR: SII9022 create failed !!!\n");
               retVal = FVID2_EFAIL;
           }
        }

        if (FVID2_SOK == retVal)
        {
           retVal = Fvid2_control(
                        createParams->hdmiTxHandle,
                        IOCTL_BSP_SII9022A_GET_DETAILED_CHIP_ID,
                        &hdmiId,
                        NULL);
           if (FVID2_SOK != retVal)
           {
               Vps_printf( " HDMI_TX: "
                         "ERROR:  Could not get detailed chip ID!!\n");
           }
           else
           {
               Vps_printf( " HDMI_TX:"
                           " hdmiId.deviceId = %d,hdmiId.deviceProdRevId = %d,"
                           " hdmiId.hdcpRevTpi = %d, hdmiId.tpiRevId = %d\n",
                               hdmiId.deviceId,
                               hdmiId.deviceProdRevId,
                               hdmiId.hdcpRevTpi,
                               hdmiId.tpiRevId);
           }
        }

        if (FVID2_SOK == retVal)
        {
           retVal = Fvid2_control(
                        createParams->hdmiTxHandle,
                        IOCTL_BSP_SII9022A_QUERY_HPD,
                        &hpdPrms,
                        NULL);
           if (FVID2_SOK != retVal)
           {
               Vps_printf( " HDMI_TX: "
                         "ERROR:  Could not detect HPD!!\n");
           }
           else
           {
               Vps_printf( " HDMI_TX: "
                           " hpdPrms.busError = %d,"
                           " hpdPrms.hpdEvtPending = %d, hpdPrms.hpdStatus = %d\n",
                            hpdPrms.busError,
                            hpdPrms.hpdEvtPending,
                            hpdPrms.hpdStatus);
           }
        }

        if (FVID2_SOK == retVal)
        {
           BspVidEncConfigParams_init(&modePrms);
           modePrms.standard = createParams->standard;
           modePrms.videoIfMode = FVID2_VIFM_SCH_DS_AVID_VSYNC;
           modePrms.videoIfWidth = FVID2_VIFW_24BIT;
           modePrms.videoDataFormat = FVID2_DF_RGB24_888;

           retVal = Fvid2_control(
                        createParams->hdmiTxHandle,
                        IOCTL_BSP_VID_ENC_SET_MODE,
                        &modePrms,
                        NULL);
           if (FVID2_SOK != retVal)
           {
               Vps_printf( " HDMI_TX: "
                         "ERROR:  Could not set mode !!!\n");
           }
        }

        if (FVID2_SOK == retVal)
        {
            Bsp_Sii9022aParams prms;
            prms.outputFormat = BSP_SII9022A_HDMI_RGB;

            retVal = Fvid2_control(
                         createParams->hdmiTxHandle,
                         IOCTL_BSP_SII9022A_SET_PARAMS,
                         &prms,
                         NULL);
            if (FVID2_SOK != retVal)
            {
                Vps_printf( " HDMI_TX: "
                          "ERROR:  Could not set Params!!!\n");
            }
        }

        if ((FVID2_SOK != retVal) && (NULL != createParams->hdmiTxHandle))
        {
           /* Close HDMI transmitter */
           retVal += Fvid2_delete(createParams->hdmiTxHandle, NULL);
           createParams->hdmiTxHandle = NULL;
        }
    }

    createStatus->retVal = retVal;

    return (createStatus->retVal);
}


/*******************************************************************************
 *
 * \brief Delete function to delete hdmi transmitter.
 *
 *        Deletes the hdmi transmitter handle using Fvid2_delete function calls.
 *
 * \param  createParams    [IN] Create parameters for hdmi transmitter
 *
 * \param  deleteArgs      Not used.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 HdmiTx_delete(HdmiTx_CreateParams *createParams, Ptr deleteArgs)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    if(createParams->hdmiTxHandle != NULL)
    {
        status = Fvid2_delete((Fvid2_Handle)createParams->hdmiTxHandle, NULL);
    }

    return status;
}


/*******************************************************************************
 *
 * \brief Control function to start stop and reset hdmi transmitter.
 *
 *        Control the transmitter operation like start and stop of the transmitter using
 *        Fvid2 calls.
 *        transmitter reset is performed using IOCTL call IOCTL_BSP_VID_DEC_RESET
 *
 * \param  handle        [IN] Handle to control hdmi transmitter.
 *
 * \param  cmd           [IN] Control command for hdmi transmitter.
 *
 * \param  cmdArgs       [IN] Arguments for command if any.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 HdmiTx_control(HdmiTx_CreateParams *createParams,
                        UInt32 cmd,
                        Ptr    cmdArgs,
                        UInt32 cmdStatusArgs)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    switch(cmd)
    {
        case HDMI_TX_CMD_START:

            if (NULL != createParams->hdmiTxHandle)
            {
                status = Fvid2_start(
                (Fvid2_Handle)createParams->hdmiTxHandle,
                NULL);
            }
            break;

        case HDMI_TX_CMD_STOP:

            if (NULL != createParams->hdmiTxHandle)
            {
                status = Fvid2_stop(
                (Fvid2_Handle)createParams->hdmiTxHandle,
                NULL);
            }
            break;

    }
    return status;
}
