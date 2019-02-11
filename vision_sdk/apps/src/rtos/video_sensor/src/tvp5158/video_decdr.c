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
 * \file video_decdr.c
 *
 * \brief  This file has the implementataion of video decoder Control API
 *
 *         APIs can be used to control video decoder.
 *         Drivers for video decoder can be part of BSP or any other package.
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <video_decdr.h>

#include <ti/drv/vps/include/fvid2/fvid2.h>
#include <ti/drv/vps/include/vps.h>
#include <ti/drv/vps/include/devices/bsp_videoDecoder.h>
#include <ti/drv/vps/include/boards/bsp_board.h>

/**
 *******************************************************************************
 *
 * \brief Set the default Create Params for Video decoder.
 *
 * \param  createParams   [IN] Create parameters for video decoder
 *
 *******************************************************************************
*/
Void VideoDecdr_CreateParams_Init(VideoDecdr_CreateParams *createParams)
{
    if(Bsp_platformIsTda2xxFamilyBuild())
    {
        createParams->videoDecdrId        =    VIDEO_DECDR_TVP_5158;
    }

#ifdef TDA2EX_BUILD
    createParams->vipInstId         =    SYSTEM_CAPTURE_INST_VIP1_SLICE2_PORTA;
#else
    createParams->vipInstId         =    SYSTEM_CAPTURE_INST_VIP1_SLICE1_PORTA;
#endif
    createParams->standard          =    SYSTEM_STD_D1;
    createParams->dataformat        =    SYSTEM_DF_YUV422I_YUYV;
    createParams->videoIfWidth      =    SYSTEM_VIFW_8BIT;
    createParams->videoIfMode       =    SYSTEM_VIFM_SCH_ES;
    createParams->numChan           =    1;
}

/**
 *******************************************************************************
 *
 * \brief Create function to create video decoder.
 *
 *        Creates the video decoder handle using bsp function calls.
 *
 * \param  createParams   [IN] Create parameters for video decoder
 *
 * \param  createStatus   [OUT] Status
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 VideoDecdr_create(VideoDecdr_CreateParams *createParams,
                      VideoDecdr_CreateStatus *createStatus)
{
    Int32  retVal = SYSTEM_LINK_STATUS_EFAIL;
    UInt32 videoDecdrInstId, videoDecdrI2cInstId, videoDecdrI2cAddr, videoDecdrDrvId;

    Bsp_VidDecCreateParams         videoDecdrCreateParams;
    Bsp_VidDecChipIdParams         videoDecdrChipIdParams;
    Bsp_VidDecChipIdStatus         videoDecdrChipIdStatus;
    Bsp_VidDecCreateStatus         videoDecdrCreateStatus;
    Bsp_VidDecVideoModeParams      videoDecdrVidModeParams;
    Bsp_VidDecVideoStatusParams    videoDecdrVideoStatusPrms;
    Bsp_VidDecVideoStatus          videoDecdrVideoStatus;

    createStatus->retVal     = SYSTEM_LINK_STATUS_EFAIL;
    videoDecdrDrvId          = VIDEO_DECDR_MAX;

    Vps_printf(" VIDEO_DECODER: ********** CREATE **********\n");

    if(createParams->videoDecdrId == VIDEO_DECDR_TVP_5158)
    {
        videoDecdrDrvId         = FVID2_VID_DEC_TVP5158_DRV;
    }

    videoDecdrInstId = Bsp_boardGetVideoDeviceInstId(
       videoDecdrDrvId,
       FVID2_VPS_CAPT_VID_DRV,
       createParams->vipInstId);

    videoDecdrI2cInstId = Bsp_boardGetVideoDeviceI2cInstId(
       videoDecdrDrvId,
       FVID2_VPS_CAPT_VID_DRV,
       createParams->vipInstId);

    videoDecdrI2cAddr = Bsp_boardGetVideoDeviceI2cAddr(
       videoDecdrDrvId,
       FVID2_VPS_CAPT_VID_DRV,
       createParams->vipInstId);

    retVal = Bsp_boardSetPinMux(FVID2_VPS_CAPT_VID_DRV,
                            createParams->vipInstId,
                            BSP_BOARD_MODE_VIDEO_BT656);
    UTILS_assert (retVal == 0);

    /* Power on video decoder */
    retVal = Bsp_boardPowerOnDevice(videoDecdrDrvId, videoDecdrInstId, TRUE);
    UTILS_assert (retVal == 0);

    /* select video decoder at board level mux */
    retVal = Bsp_boardSelectDevice(videoDecdrDrvId, videoDecdrInstId);
    UTILS_assert (retVal == 0);

    /* Perform any reset needed at board level */
    retVal = Bsp_boardResetDevice(videoDecdrDrvId, videoDecdrInstId);
    UTILS_assert (retVal == 0);

    retVal = Bsp_boardSelectMode(
                     videoDecdrDrvId,
                     videoDecdrInstId,
                     BSP_BOARD_MODE_VIDEO_BT656);
    UTILS_assert (retVal == 0);

    videoDecdrCreateParams.deviceI2cInstId     = videoDecdrI2cInstId;
    videoDecdrCreateParams.numDevicesAtPort    = 1u;
    videoDecdrCreateParams.deviceI2cAddr[0u]   = videoDecdrI2cAddr;
    videoDecdrCreateParams.deviceResetGpio[0u] = BSP_VID_DEC_GPIO_NONE;

    /* Creates video decoder handle */
    createParams->videoDecdrHandle = Fvid2_create(
                                                videoDecdrDrvId,
                                                videoDecdrInstId,
                                                &videoDecdrCreateParams,
                                                &videoDecdrCreateStatus,
                                                NULL);
    UTILS_assert (createParams->videoDecdrHandle != NULL);

    videoDecdrChipIdParams.deviceNum = 0;
    retVal = Fvid2_control(
                            createParams->videoDecdrHandle,
                            IOCTL_BSP_VID_DEC_GET_CHIP_ID,
                            &videoDecdrChipIdParams,
                            &videoDecdrChipIdStatus);

    UTILS_assert (retVal == 0);

    /* Setting video decoder video mode parameters */
    videoDecdrVidModeParams.videoIfWidth               =    createParams->videoIfWidth;
    videoDecdrVidModeParams.videoDataFormat            =    createParams->dataformat;
    videoDecdrVidModeParams.standard                   =    createParams->standard;
    videoDecdrVidModeParams.videoIfMode                =    createParams->videoIfMode;
    videoDecdrVidModeParams.videoSystem                =   BSP_VID_DEC_VIDEO_SYSTEM_AUTO_DETECT;
    videoDecdrVidModeParams.videoAutoDetectTimeout     =     VIDEO_DECDR_WAIT_FOREVER;
    videoDecdrVidModeParams.videoCropEnable            =     FALSE;

    retVal = Fvid2_control(
                            createParams->videoDecdrHandle,
                            IOCTL_BSP_VID_DEC_SET_VIDEO_MODE,
                            &videoDecdrVidModeParams,
                            NULL);
    UTILS_assert (retVal == 0);

    /* Checking video status. For debugging purpose only */
    videoDecdrVideoStatusPrms.channelNum    =    0;
    retVal = Fvid2_control(
                createParams->videoDecdrHandle,
                IOCTL_BSP_VID_DEC_GET_VIDEO_STATUS,
                &videoDecdrVideoStatusPrms,
                &videoDecdrVideoStatus);
    UTILS_assert (retVal == 0);

    createStatus->retVal = retVal;

    return (createStatus->retVal);
}


/*******************************************************************************
 *
 * \brief Delete function to delete video decoder.
 *
 *        Deletes the video decoder handle using Fvid2_delete function calls.
 *
 * \param  createParams    [IN] Create parameters for video decoder
 *
 * \param  deleteArgs      Not used.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 VideoDecdr_delete(VideoDecdr_CreateParams *createParams, Ptr deleteArgs)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    if(createParams->videoDecdrHandle != NULL)
    {
        status = Fvid2_delete((Fvid2_Handle)createParams->videoDecdrHandle, NULL);
    }

    return status;
}


/*******************************************************************************
 *
 * \brief Control function to start stop and reset video decoder.
 *
 *        Control the receiver operation like start and stop of the receiver using
 *        Fvid2 calls.
 *        receiver reset is performed using IOCTL call IOCTL_BSP_VID_DEC_RESET
 *
 * \param  handle        [IN] Handle to control video decoder.
 *
 * \param  cmd           [IN] Control command for video decoder.
 *
 * \param  cmdArgs       [IN] Arguments for command if any.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 VideoDecdr_control(VideoDecdr_CreateParams *createParams,
                        UInt32 cmd,
                        Ptr    cmdArgs,
                        UInt32 cmdStatusArgs)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    switch(cmd)
    {
        case VIDEO_DECDR_CMD_START:

                                status = Fvid2_start(
                                (Fvid2_Handle)createParams->videoDecdrHandle,
                                NULL);
                                break;

        case VIDEO_DECDR_CMD_STOP:

                                status = Fvid2_stop(
                                (Fvid2_Handle)createParams->videoDecdrHandle,
                                NULL);
                                break;

        case VIDEO_DECDR_CMD_RESET:

                                status = Fvid2_control(
                                (Fvid2_Handle)createParams->videoDecdrHandle,
                                IOCTL_BSP_VID_DEC_RESET,
                                NULL, NULL);
                                break;
    }
    return status;
}
