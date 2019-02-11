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
 * \file hdmi_recvr.c
 *
 * \brief  This file has the implementataion of hdmi receiver Control API
 *
 *         APIs can be used to control hdmi receiver.
 *         Drivers for hdmi receiver can be part of BSP or any other package.
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
#include <src/include/hdmi_recvr.h>

#include <ti/drv/vps/include/fvid2/fvid2.h>
#include <ti/drv/vps/include/vps.h>
#include <ti/drv/vps/include/devices/bsp_videoDecoder.h>
#include <ti/drv/vps/include/boards/bsp_board.h>




/**
 *******************************************************************************
 *
 * \brief Set the default Create Params for Hdmi receiver.
 *
 * \param  createParams   [IN] Create parameters for hdmi receiver
 *
 *******************************************************************************
*/
Void HdmiRecvr_CreateParams_Init(HdmiRecvr_CreateParams *createParams)
{
    Bsp_BoardRev     dcBoardRev;

    if(Bsp_platformIsTda3xxFamilyBuild())
    {
        createParams->hdmiRecvrId        =    HDMI_RECVR_ADV_7611;
    }
    if(Bsp_platformIsTda2xxFamilyBuild())
    {
        /* SIL9127 not present in REV D VISION cards */
        createParams->hdmiRecvrId        =    HDMI_RECVR_ADV_7611;
        dcBoardRev = Bsp_boardGetDcRev();
        if (dcBoardRev < BSP_BOARD_REV_D)
        {
            createParams->hdmiRecvrId    =    HDMI_RECVR_SII_9127;
        }
    }
    createParams->vipInstId         =    SYSTEM_CAPTURE_INST_VIP1_SLICE1_PORTA;
    createParams->standard          =    SYSTEM_STD_AUTO_DETECT;
    createParams->dataformat        =    SYSTEM_DF_YUV422I_YUYV;
    createParams->videoIfWidth      =    SYSTEM_VIFW_16BIT;
    createParams->videoIfMode        =    SYSTEM_VIFM_SCH_DS_AVID_VSYNC;
    createParams->numChan           =    1;
}

/**
 *******************************************************************************
 *
 * \brief Create function to create hdmi receiver.
 *
 *        Creates the hdmi receiver handle using bsp function calls.
 *
 * \param  createParams   [IN] Create parameters for hdmi receiver
 *
 * \param  createStatus   [OUT] Status
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 HdmiRecvr_create(HdmiRecvr_CreateParams *createParams,
                      HdmiRecvr_CreateStatus *createStatus)
{
    Int32  retVal = SYSTEM_LINK_STATUS_EFAIL;
    UInt32 hdmiRecvrInstId, hdmiRecvrI2cInstId, hdmiRecvrI2cAddr, hdmiRecvrDrvId;

    Bsp_VidDecCreateParams         hdmiRecvrCreateParams;
    Bsp_VidDecChipIdParams         hdmiRecvrChipIdParams;
    Bsp_VidDecChipIdStatus         hdmiRecvrChipIdStatus;
    Bsp_VidDecCreateStatus         hdmiRecvrCreateStatus;
    Bsp_VidDecVideoModeParams    hdmiRecvrVidModeParams;
    Bsp_VidDecVideoStatusParams hdmiRecvrVideoStatusPrms;
    Bsp_VidDecVideoStatus       hdmiRecvrVideoStatus;

    createStatus->retVal     = SYSTEM_LINK_STATUS_EFAIL;
    hdmiRecvrDrvId             = HDMI_RECVR_MAX;

    if(createParams->hdmiRecvrId == HDMI_RECVR_SII_9127)
    {
        hdmiRecvrDrvId         = FVID2_VID_DEC_SII9127_DRV;
    }
    if(createParams->hdmiRecvrId == HDMI_RECVR_ADV_7611)
    {
        hdmiRecvrDrvId         = FVID2_VID_DEC_ADV7611_DRV;
    }


    hdmiRecvrInstId = Bsp_boardGetVideoDeviceInstId(
       hdmiRecvrDrvId,
       FVID2_VPS_CAPT_VID_DRV,
       createParams->vipInstId);

    hdmiRecvrI2cInstId = Bsp_boardGetVideoDeviceI2cInstId(
       hdmiRecvrDrvId,
       FVID2_VPS_CAPT_VID_DRV,
       createParams->vipInstId);

    hdmiRecvrI2cAddr = Bsp_boardGetVideoDeviceI2cAddr(
       hdmiRecvrDrvId,
       FVID2_VPS_CAPT_VID_DRV,
       createParams->vipInstId);

    retVal = Bsp_boardSetPinMux(FVID2_VPS_CAPT_VID_DRV,
                            createParams->vipInstId,
                            BSP_BOARD_MODE_VIDEO_16BIT);
    UTILS_assert (retVal == 0);

    /* Power on video decoder */
    retVal = Bsp_boardPowerOnDevice(hdmiRecvrDrvId, hdmiRecvrInstId, TRUE);
    UTILS_assert (retVal == 0);

    /* select video decoder at board level mux */
    retVal = Bsp_boardSelectDevice(hdmiRecvrDrvId, hdmiRecvrInstId);
    UTILS_assert (retVal == 0);

    /* Perform any reset needed at board level */
    retVal = Bsp_boardResetDevice(hdmiRecvrDrvId, hdmiRecvrInstId);
    UTILS_assert (retVal == 0);

    retVal = Bsp_boardSelectMode(
                     hdmiRecvrDrvId,
                     hdmiRecvrInstId,
                     BSP_BOARD_MODE_VIDEO_16BIT);
    UTILS_assert (retVal == 0);

    hdmiRecvrCreateParams.deviceI2cInstId     = hdmiRecvrI2cInstId;
    hdmiRecvrCreateParams.numDevicesAtPort    = 1u;
    hdmiRecvrCreateParams.deviceI2cAddr[0u]   = hdmiRecvrI2cAddr;
    hdmiRecvrCreateParams.deviceResetGpio[0u] = BSP_VID_DEC_GPIO_NONE;

    /* Creates hdmi receiver handle */
    createParams->hdmiRecvrHandle = Fvid2_create(
                                                hdmiRecvrDrvId,
                                                hdmiRecvrInstId,
                                                &hdmiRecvrCreateParams,
                                                &hdmiRecvrCreateStatus,
                                                NULL);
    UTILS_assert (createParams->hdmiRecvrHandle != NULL);

    hdmiRecvrChipIdParams.deviceNum = 0;
    retVal = Fvid2_control(
                            createParams->hdmiRecvrHandle,
                            IOCTL_BSP_VID_DEC_GET_CHIP_ID,
                            &hdmiRecvrChipIdParams,
                            &hdmiRecvrChipIdStatus);

    UTILS_assert (retVal == 0);

    /* Setting hdmi receiver video mode parameters */
    hdmiRecvrVidModeParams.videoIfWidth               =    createParams->videoIfWidth;
    hdmiRecvrVidModeParams.videoDataFormat            =    createParams->dataformat;
    hdmiRecvrVidModeParams.standard                   =    createParams->standard;
    hdmiRecvrVidModeParams.videoIfMode                =    createParams->videoIfMode;
    hdmiRecvrVidModeParams.videoSystem                 =   BSP_VID_DEC_VIDEO_SYSTEM_AUTO_DETECT;
    hdmiRecvrVidModeParams.videoAutoDetectTimeout     =     HDMI_RECVR_WAIT_FOREVER;
    hdmiRecvrVidModeParams.videoCropEnable            =     FALSE;

    retVal = Fvid2_control(
                            createParams->hdmiRecvrHandle,
                            IOCTL_BSP_VID_DEC_SET_VIDEO_MODE,
                            &hdmiRecvrVidModeParams,
                            NULL);
    UTILS_assert (retVal == 0);

    /* Checking video status. For debugging purpose only */
    hdmiRecvrVideoStatusPrms.channelNum    =    0;
    retVal = Fvid2_control(
                createParams->hdmiRecvrHandle,
                IOCTL_BSP_VID_DEC_GET_VIDEO_STATUS,
                &hdmiRecvrVideoStatusPrms,
                &hdmiRecvrVideoStatus);
    UTILS_assert (retVal == 0);




    createStatus->retVal = retVal;

    return (createStatus->retVal);


}


/*******************************************************************************
 *
 * \brief Delete function to delete hdmi receiver.
 *
 *        Deletes the hdmi receiver handle using Fvid2_delete function calls.
 *
 * \param  createParams    [IN] Create parameters for hdmi receiver
 *
 * \param  deleteArgs      Not used.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 HdmiRecvr_delete(HdmiRecvr_CreateParams *createParams, Ptr deleteArgs)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    if(createParams->hdmiRecvrHandle != NULL)
    {
        status = Fvid2_delete((Fvid2_Handle)createParams->hdmiRecvrHandle, NULL);
    }

    return status;
}


/*******************************************************************************
 *
 * \brief Control function to start stop and reset hdmi receiver.
 *
 *        Control the receiver operation like start and stop of the receiver using
 *        Fvid2 calls.
 *        receiver reset is performed using IOCTL call IOCTL_BSP_VID_DEC_RESET
 *
 * \param  handle        [IN] Handle to control hdmi receiver.
 *
 * \param  cmd           [IN] Control command for hdmi receiver.
 *
 * \param  cmdArgs       [IN] Arguments for command if any.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 HdmiRecvr_control(HdmiRecvr_CreateParams *createParams,
                        UInt32 cmd,
                        Ptr    cmdArgs,
                        UInt32 cmdStatusArgs)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    switch(cmd)
    {
        case HDMI_RECVR_CMD_START:

                                status = Fvid2_start(
                                (Fvid2_Handle)createParams->hdmiRecvrHandle,
                                NULL);
                                break;

        case HDMI_RECVR_CMD_STOP:

                                status = Fvid2_stop(
                                (Fvid2_Handle)createParams->hdmiRecvrHandle,
                                NULL);
                                break;

        case HDMI_RECVR_CMD_RESET:

                                status = Fvid2_control(
                                (Fvid2_Handle)createParams->hdmiRecvrHandle,
                                IOCTL_BSP_VID_DEC_RESET,
                                NULL, NULL);
                                break;
    }
    return status;
}
