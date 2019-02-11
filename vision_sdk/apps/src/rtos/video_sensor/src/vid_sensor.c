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

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include <include/link_api/system.h>
#include <video_sensor.h>
#include <video_decdr.h>
#include <hdmi_recvr.h>
#include <eth_cam.h>
#include <chains_common_sensor.h>
#include <src/sensor_priv.h>

vidSensor_Obj gvidSensorObj;

static Void ChainsCommon_SetVidSensorMultiOV490Prms(
                                    VidSensor_CreateParams *pPrm,
                                    UInt32 portId[],
                                    UInt32 numCh
                                    )
{
    pPrm->sensorId      = VID_SENSOR_MULDES_OV490;
    pPrm->standard      = SYSTEM_STD_720P_60;
    pPrm->dataformat    = SYSTEM_DF_YUV422I_UYVY;
    pPrm->videoIfWidth  = SYSTEM_VIFW_8BIT;
    pPrm->fps           = SYSTEM_FPS_30;
    pPrm->isLVDSCaptMode = TRUE;
    pPrm->numChan       = numCh;

    pPrm->vipInstId[0] = SYSTEM_CAPTURE_INST_VIP1_SLICE1_PORTA;
    pPrm->vipInstId[1] = SYSTEM_CAPTURE_INST_VIP1_SLICE2_PORTA;
    pPrm->vipInstId[2] = SYSTEM_CAPTURE_INST_VIP2_SLICE1_PORTA;
    pPrm->vipInstId[3] = SYSTEM_CAPTURE_INST_VIP3_SLICE1_PORTA;
    pPrm->vipInstId[4] = SYSTEM_CAPTURE_INST_VIP3_SLICE2_PORTA;
    pPrm->vipInstId[5] = SYSTEM_CAPTURE_INST_VIP2_SLICE2_PORTB;

#ifdef BOARD_TYPE_TDA2XX_RVP
    pPrm->vipInstId[0] = SYSTEM_CAPTURE_INST_VIP2_SLICE1_PORTA;
    pPrm->vipInstId[1] = SYSTEM_CAPTURE_INST_VIP2_SLICE2_PORTA;
    pPrm->vipInstId[2] = SYSTEM_CAPTURE_INST_VIP3_SLICE2_PORTA;
    pPrm->vipInstId[3] = SYSTEM_CAPTURE_INST_VIP3_SLICE1_PORTA;
    pPrm->vipInstId[4] = SYSTEM_CAPTURE_INST_VIP1_SLICE2_PORTA;
    pPrm->vipInstId[5] = SYSTEM_CAPTURE_INST_VIP1_SLICE1_PORTA;
    pPrm->vipInstId[6] = SYSTEM_CAPTURE_INST_VIP1_SLICE1_PORTB;
    pPrm->vipInstId[7] = SYSTEM_CAPTURE_INST_VIP2_SLICE2_PORTB;
#endif

    if(Bsp_platformIsTda3xxFamilyBuild())
    {
        pPrm->vipInstId[0] = SYSTEM_CAPTURE_INST_VIP1_SLICE1_PORTA;
        pPrm->vipInstId[1] = SYSTEM_CAPTURE_INST_VIP1_SLICE1_PORTB;
        pPrm->vipInstId[2] = SYSTEM_CAPTURE_INST_VIP1_SLICE2_PORTA;
        pPrm->vipInstId[3] = SYSTEM_CAPTURE_INST_VIP1_SLICE2_PORTB;
    }
    /* copy VIP inst ID to portId[] so that this can be during setting up
     * of VIP capture parameters
     */
    UTILS_assert(portId != NULL);
    memcpy(portId,
            pPrm->vipInstId,
            sizeof(pPrm->vipInstId));
}

static Void ChainsCommon_SetVidSensorMultiOV10635Prms(
                                    VidSensor_CreateParams *pPrm,
                                    UInt32 portId[],
                                    UInt32 numCh
                                    )
{
    pPrm->sensorId      = VID_SENSOR_MULDES_OV1063X;
    pPrm->standard      = SYSTEM_STD_720P_60;
    pPrm->dataformat    = SYSTEM_DF_YUV422I_UYVY;
    pPrm->videoIfWidth  = SYSTEM_VIFW_8BIT;
    pPrm->fps           = SYSTEM_FPS_30;
    pPrm->isLVDSCaptMode = TRUE;
    pPrm->numChan       = numCh;

    pPrm->vipInstId[0] = SYSTEM_CAPTURE_INST_VIP1_SLICE1_PORTA;
    pPrm->vipInstId[1] = SYSTEM_CAPTURE_INST_VIP1_SLICE2_PORTA;
    pPrm->vipInstId[2] = SYSTEM_CAPTURE_INST_VIP2_SLICE1_PORTA;
    pPrm->vipInstId[3] = SYSTEM_CAPTURE_INST_VIP3_SLICE1_PORTA;
    pPrm->vipInstId[4] = SYSTEM_CAPTURE_INST_VIP3_SLICE2_PORTA;
    pPrm->vipInstId[5] = SYSTEM_CAPTURE_INST_VIP2_SLICE2_PORTB;

#ifdef TDA2PX_BUILD
    pPrm->vipInstId[3] = SYSTEM_CAPTURE_INST_VIP1_SLICE2_PORTB;
#endif


#ifdef TDA2EX_BUILD
    pPrm->vipInstId[0] = SYSTEM_CAPTURE_INST_VIP1_SLICE2_PORTA;
    pPrm->vipInstId[1] = SYSTEM_CAPTURE_INST_VIP1_SLICE1_PORTA;
    pPrm->vipInstId[2] = SYSTEM_CAPTURE_INST_VIP1_SLICE2_PORTB;
    pPrm->vipInstId[3] = SYSTEM_CAPTURE_INST_VIP1_SLICE1_PORTB;
#endif

#ifdef BOARD_TYPE_TDA2XX_RVP
    pPrm->vipInstId[0] = SYSTEM_CAPTURE_INST_VIP2_SLICE1_PORTA;
    pPrm->vipInstId[1] = SYSTEM_CAPTURE_INST_VIP2_SLICE2_PORTA;
    pPrm->vipInstId[2] = SYSTEM_CAPTURE_INST_VIP3_SLICE2_PORTA;
    pPrm->vipInstId[3] = SYSTEM_CAPTURE_INST_VIP3_SLICE1_PORTA;
    pPrm->vipInstId[4] = SYSTEM_CAPTURE_INST_VIP1_SLICE2_PORTA;
    pPrm->vipInstId[5] = SYSTEM_CAPTURE_INST_VIP1_SLICE1_PORTA;
    pPrm->vipInstId[6] = SYSTEM_CAPTURE_INST_VIP1_SLICE1_PORTB;
    pPrm->vipInstId[7] = SYSTEM_CAPTURE_INST_VIP2_SLICE2_PORTB;
#endif

    if(Bsp_platformIsTda3xxFamilyBuild())
    {
        pPrm->vipInstId[0] = SYSTEM_CAPTURE_INST_VIP1_SLICE1_PORTA;
        pPrm->vipInstId[1] = SYSTEM_CAPTURE_INST_VIP1_SLICE1_PORTB;
        pPrm->vipInstId[2] = SYSTEM_CAPTURE_INST_VIP1_SLICE2_PORTA;
        pPrm->vipInstId[3] = SYSTEM_CAPTURE_INST_VIP1_SLICE2_PORTB;
    }
    /* copy VIP inst ID to portId[] so that this can be during setting up
     * of VIP capture parameters
     */
    UTILS_assert(portId != NULL);
    memcpy(portId,
            pPrm->vipInstId,
            sizeof(pPrm->vipInstId));
}

static Void ChainsCommon_SetVidSensorOV10635Prms(
                                    VidSensor_CreateParams *pPrm,
                                    UInt32 portId[],
                                    UInt32 numCh
                                    )
{
    pPrm->sensorId      = VID_SENSOR_OV10635;
    pPrm->vipInstId[0]     = SYSTEM_CAPTURE_INST_VIP1_SLICE1_PORTA;
#ifdef TDA2EX_BUILD
   //This change is done to support tda2ex VIP1_SLICE2_PORTA
    pPrm->vipInstId[0]     = SYSTEM_CAPTURE_INST_VIP1_SLICE2_PORTA;
#endif
#ifdef BOARD_TYPE_TDA2XX_RVP
    pPrm->vipInstId[0]     = SYSTEM_CAPTURE_INST_VIP2_SLICE1_PORTA;
#endif
    pPrm->standard      = SYSTEM_STD_720P_60;
    pPrm->dataformat    = SYSTEM_DF_YUV422I_UYVY;
    pPrm->videoIfWidth  = SYSTEM_VIFW_8BIT;
    pPrm->fps           = SYSTEM_FPS_30;
    pPrm->numChan       = numCh;
    if(numCh > 1)
    {
        pPrm->isLVDSCaptMode = TRUE;
    }
    else
    {
        pPrm->isLVDSCaptMode = FALSE;
    }
}

static Void ChainsCommon_SetVidSensorMulti_IMX290Prms(
                                    VidSensor_CreateParams *pPrm,
                                    UInt32 portId[],
                                    UInt32 numCh
                                    )
{
    pPrm->sensorId      = VID_SENSOR_MULDES_IMX290;
    pPrm->standard      = SYSTEM_STD_720P_60;
    pPrm->dataformat    = SYSTEM_DF_YUV422I_UYVY;
    pPrm->videoIfWidth  = SYSTEM_VIFW_8BIT;
    pPrm->fps           = SYSTEM_FPS_30;
    pPrm->isLVDSCaptMode = TRUE;
    pPrm->numChan       = numCh;

    pPrm->vipInstId[0] = SYSTEM_CAPTURE_INST_VIP1_SLICE1_PORTA;
    pPrm->vipInstId[1] = SYSTEM_CAPTURE_INST_VIP1_SLICE2_PORTA;
    pPrm->vipInstId[2] = SYSTEM_CAPTURE_INST_VIP2_SLICE1_PORTA;
    pPrm->vipInstId[3] = SYSTEM_CAPTURE_INST_VIP3_SLICE1_PORTA;
    pPrm->vipInstId[4] = SYSTEM_CAPTURE_INST_VIP3_SLICE2_PORTA;
    pPrm->vipInstId[5] = SYSTEM_CAPTURE_INST_VIP2_SLICE2_PORTB;

#ifdef TDA2EX_BUILD
    pPrm->vipInstId[0] = SYSTEM_CAPTURE_INST_VIP1_SLICE2_PORTA;
    pPrm->vipInstId[1] = SYSTEM_CAPTURE_INST_VIP1_SLICE1_PORTA;
    pPrm->vipInstId[2] = SYSTEM_CAPTURE_INST_VIP1_SLICE2_PORTB;
    pPrm->vipInstId[3] = SYSTEM_CAPTURE_INST_VIP1_SLICE1_PORTB;
#endif

    if(Bsp_platformIsTda3xxFamilyBuild())
    {
        pPrm->vipInstId[0] = SYSTEM_CAPTURE_INST_VIP1_SLICE1_PORTA;
        pPrm->vipInstId[1] = SYSTEM_CAPTURE_INST_VIP1_SLICE1_PORTB;
        pPrm->vipInstId[2] = SYSTEM_CAPTURE_INST_VIP1_SLICE2_PORTA;
        pPrm->vipInstId[3] = SYSTEM_CAPTURE_INST_VIP1_SLICE2_PORTB;
    }
    /* copy VIP inst ID to portId[] so that this can be during setting up
     * of VIP capture parameters
     */
    UTILS_assert(portId != NULL);
    memcpy(portId,
            pPrm->vipInstId,
            sizeof(pPrm->vipInstId));
}

static Void ChainsCommon_SetVidSensorSAT0088_OV1063XPrms(
                                    VidSensor_CreateParams *pPrm,
                                    UInt32 portId[],
                                    UInt32 numCh
                                    )
{
    UInt32 idx;

    for (idx = 0U; idx < numCh; idx++)
    {
        pPrm->vipInstId[idx] = VPS_CAPT_INST_ISS_CAL_A + idx;
    }
    pPrm->sensorId         = VID_SENSOR_SAT0088_OV1063X;
    pPrm->standard         = SYSTEM_STD_720P_60;
    pPrm->dataformat       = SYSTEM_DF_YUV422I_YUYV;
    pPrm->videoIfWidth     = SYSTEM_VIFW_8BIT;
    pPrm->videoIfMode      = SYSTEM_VIFM_SCH_CSI2;
    pPrm->fps              = SYSTEM_FPS_30;
    pPrm->isLVDSCaptMode   = FALSE;
    pPrm->numChan          = numCh;

#ifdef TDA3XX_BUILD
    pPrm->dataformat       = SYSTEM_DF_YUV422I_UYVY;
#endif

}
/**
 *******************************************************************************
 *
 * \brief   Set Sensor Create Parameters
 *
 *          This function is used to set the Video Sensor params.
 *          It is called in Create function. It is advisable to have
 *          Chains_VipSingleCameraView_ResetLinkPrms prior to set params
 *          so all the default params get set.
 *          Video sensor Id , Instance Id data format are set.
 *
 * \param   pPrm      [IN]    VidSensor_CreateParams
 * \param   sensorId  [IN]    Sensor ID
 * \param   portId    [OUT]   Ports used by this sensor,
 *                            only valid when sensorId is
 *                            VID_SENSOR_MULDES_OV1063X
 * \param   numCh     [IN]    Num of channels used
 *                            only valid when sensorId is
 *                            VID_SENSOR_MULDES_OV1063X or captureSrc is
 *                            CHAINS_CAPTURE_SRC_UB960_TIDA00262
 *
 *******************************************************************************
*/
static Void ChainsCommon_SetVidSensorPrms(
                                    VidSensor_CreateParams *pPrm,
                                    VidSensor_Id sensorId,
                                    UInt32 portId[],
                                    UInt32 numCh,
                                    Chains_CaptureSrc captureSrc
                                    )
{
    if(sensorId==VID_SENSOR_OV10635)
    {
        ChainsCommon_SetVidSensorOV10635Prms(pPrm,portId,numCh);
    }
    else if(sensorId==VID_SENSOR_MULDES_OV1063X)
    {
        ChainsCommon_SetVidSensorMultiOV10635Prms(pPrm,portId,numCh);
    }
    else if(sensorId==VID_SENSOR_SAT0088_OV1063X)
    {
        ChainsCommon_SetVidSensorSAT0088_OV1063XPrms(pPrm,portId,numCh);
    }
    else if(sensorId==VID_SENSOR_MULDES_IMX290)
    {
        ChainsCommon_SetVidSensorMulti_IMX290Prms(pPrm,portId,numCh);
    }
    else if(sensorId==VID_SENSOR_MULDES_OV490)
    {
        ChainsCommon_SetVidSensorMultiOV490Prms(pPrm,portId,numCh);
    }
    else
    {
        UTILS_assert(0);
    }
}

/**
 *******************************************************************************
 *
 * \brief   Set Hdmi receiver Create Parameters
 *
 *          This function is used to set the Video Sensor params.
 *          It is called in Create function. It is advisable to have
 *          Chains_VipSingleCameraView_ResetLinkPrms prior to set params
 *          so all the default params get set.
 *          Video sensor Id , Instance Id data format are set.
 *
 * \param   pPrm      [IN]    HdmiRecvr_CreateParams
 *
 *******************************************************************************
*/
static Void ChainsCommon_SetHdmiRecvrPrms(
                                    HdmiRecvr_CreateParams *pPrm)
{
    Bsp_BoardRev     dcBoardRev;

    if(Bsp_platformIsTda3xxFamilyBuild())
    {
        pPrm->hdmiRecvrId        =    HDMI_RECVR_ADV_7611;
    }
    if(Bsp_platformIsTda2xxFamilyBuild())
    {
        /* SIL9127 not present in REV D VISION cards */
        pPrm->hdmiRecvrId       =    HDMI_RECVR_ADV_7611;
        dcBoardRev = Bsp_boardGetDcRev();
        if (dcBoardRev < BSP_BOARD_REV_D)
        {
            pPrm->hdmiRecvrId   =    HDMI_RECVR_SII_9127;
        }
    }
    pPrm->vipInstId         =    SYSTEM_CAPTURE_INST_VIP1_SLICE1_PORTA;
#ifdef TDA2EX_BUILD
        //This change is done for supporting tda2ex
        pPrm->vipInstId     =   SYSTEM_CAPTURE_INST_VIP1_SLICE2_PORTA;
#endif
    pPrm->standard          =    SYSTEM_STD_CUSTOM;
    pPrm->dataformat        =    SYSTEM_DF_YUV422P;
    pPrm->videoIfWidth      =    SYSTEM_VIFW_16BIT;
    pPrm->videoIfMode        =    SYSTEM_VIFM_SCH_DS_AVID_VSYNC;
    pPrm->numChan           =    1;
}

/**
 *******************************************************************************
 *
 * \brief   Set Video decoder Create Parameters
 *
 *          This function is used to set the Video Decoder params.
 *          It is called in Create function. It is advisable to have
 *          Chains_VipSingleCameraView_ResetLinkPrms prior to set params
 *          so all the default params get set.
 *          Video sensor Id , Instance Id, Data format are set.
 *
 * \param   pPrm      [IN]    VideoDecdr_CreateParams
 *
 *******************************************************************************
*/
static Void ChainsCommon_SetVideoDecdrPrms(
                                    VideoDecdr_CreateParams *pPrm)
{
    if(Bsp_platformIsTda2xxFamilyBuild())
    {
        pPrm->videoDecdrId  =    VIDEO_DECDR_TVP_5158;
    }
#ifdef TDA2EX_BUILD
    pPrm->vipInstId         =    SYSTEM_CAPTURE_INST_VIP1_SLICE2_PORTA;
#else
    pPrm->vipInstId         =    SYSTEM_CAPTURE_INST_VIP1_SLICE1_PORTA;
#endif
    pPrm->standard          =    SYSTEM_STD_D1;
    pPrm->dataformat        =    SYSTEM_DF_YUV422I_YUYV;
    pPrm->videoIfWidth      =    SYSTEM_VIFW_8BIT;
    pPrm->videoIfMode       =    SYSTEM_VIFM_SCH_ES;
    pPrm->numChan           =    1;
    pPrm->fps               =    SYSTEM_FPS_60;
}

/**
 *******************************************************************************
 *
 * \brief   Configure and start single channel capture device
 *
 *******************************************************************************
*/
Int32 ChainsCommon_StartCaptureDevice(Chains_CaptureSrc captureSrc,
                        UInt32 captureOutWidth,
                        UInt32 captureOutHeight
                        )
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    VidSensor_CreateStatus vidSensorStatus;
    HdmiRecvr_CreateStatus hdmiRecvrStatus;
    VideoDecdr_CreateStatus videoDecdrStatus;

    Vps_printf(" CHAINS: Sensor create in progress\n");

    VidSensor_CreateParams_Init(&gvidSensorObj.vidSensorPrm);

    if((captureSrc == CHAINS_CAPTURE_SRC_HDMI_720P) ||
        (captureSrc == CHAINS_CAPTURE_SRC_HDMI_1080P))
    {
        HdmiRecvr_CreateParams_Init(&gvidSensorObj.hdmiRecvrPrm);
    }
    else if(captureSrc == CHAINS_CAPTURE_SRC_VIDDEC_TVP5158)
    {
        VideoDecdr_CreateParams_Init(&gvidSensorObj.videoDecdrPrm);
    }

    if(captureSrc == CHAINS_CAPTURE_SRC_OV10635)
    {
        ChainsCommon_SetVidSensorPrms(
                &gvidSensorObj.vidSensorPrm,
                VID_SENSOR_OV10635,
                NULL,
                1,
                captureSrc
                );
    }
    else if(captureSrc == CHAINS_CAPTURE_SRC_OV10635_LVDS)
    {
        ChainsCommon_SetVidSensorPrms(
                &gvidSensorObj.vidSensorPrm,
                VID_SENSOR_MULDES_OV1063X,
                NULL,
                1U,
                captureSrc
                );
    }
    else if(captureSrc == CHAINS_CAPTURE_SRC_UB964_OV1063X)
    {
        ChainsCommon_SetVidSensorPrms(
                &gvidSensorObj.vidSensorPrm,
                VID_SENSOR_SAT0088_OV1063X,
                NULL,
                1U,
                captureSrc
                );
    }
    else if((captureSrc == CHAINS_CAPTURE_SRC_HDMI_720P) ||
        (captureSrc == CHAINS_CAPTURE_SRC_HDMI_1080P))
    {
        ChainsCommon_SetHdmiRecvrPrms(&gvidSensorObj.hdmiRecvrPrm);
    }
    else if(captureSrc == CHAINS_CAPTURE_SRC_VIDDEC_TVP5158)
    {
        ChainsCommon_SetVideoDecdrPrms(&gvidSensorObj.videoDecdrPrm);
    }
    else if((captureSrc == CHAINS_CAPTURE_SRC_TRULY_AVB_CAM))
    {
        /* Do nothing */
    }
    else
    {
        /* Un Recognized Capture source */
        UTILS_assert(FALSE);
    }

    if(captureSrc == CHAINS_CAPTURE_SRC_OV10635
        ||
       captureSrc == CHAINS_CAPTURE_SRC_OV10635_LVDS
        )
    {
        status = VidSensor_create(&gvidSensorObj.vidSensorPrm,
                                    &vidSensorStatus);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

        status = VidSensor_control(&gvidSensorObj.vidSensorPrm,
                                    VID_SENSOR_CMD_START,
                                    NULL,
                                    NULL);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }
    else if((captureSrc == CHAINS_CAPTURE_SRC_HDMI_720P) ||
        (captureSrc == CHAINS_CAPTURE_SRC_HDMI_1080P))
    {
        status = HdmiRecvr_create(&gvidSensorObj.hdmiRecvrPrm, &hdmiRecvrStatus);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

        status = HdmiRecvr_control(&gvidSensorObj.hdmiRecvrPrm,
                                   HDMI_RECVR_CMD_START,
                                   NULL,
                                   NULL);
    }
    else if(captureSrc == CHAINS_CAPTURE_SRC_VIDDEC_TVP5158)
    {
        status = VideoDecdr_create(&gvidSensorObj.videoDecdrPrm, &videoDecdrStatus);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

        status = VideoDecdr_control(&gvidSensorObj.videoDecdrPrm,
                                    VIDEO_DECDR_CMD_START,
                                    NULL,
                                    NULL);
    }
    else if((captureSrc == CHAINS_CAPTURE_SRC_TRULY_AVB_CAM))
    {
        status = EthCam_create();
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }


    Vps_printf(" CHAINS: Sensor create ... DONE !!!\n");

    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    return status;
}

/**
 *******************************************************************************
 *
 * \brief   Configure and start multi-channel capture device
 *
 *******************************************************************************
*/
Int32 ChainsCommon_MultiCam_StartCaptureDevice( Chains_CaptureSrc captureSrc,
                                    UInt32 portId[],
                                    UInt32 numLvdsCh
                                    )
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    VidSensor_CreateStatus vidSensorStatus;

    Vps_printf(" CHAINS: ChainsCommon_MultiCam_StartCaptureDevice\n");

    if(captureSrc==CHAINS_CAPTURE_SRC_OV10635)
    {
        ChainsCommon_SetVidSensorPrms(
                &gvidSensorObj.vidSensorPrm,
                VID_SENSOR_MULDES_OV1063X,
                portId,
                numLvdsCh,
                captureSrc);
    }
    else if(captureSrc == CHAINS_CAPTURE_SRC_OV490)
    {
        ChainsCommon_SetVidSensorPrms(
                &gvidSensorObj.vidSensorPrm,
                VID_SENSOR_MULDES_OV490,
                portId,
                numLvdsCh,
                captureSrc
                );
    }
    else if(captureSrc == CHAINS_CAPTURE_SRC_UB964_OV1063X)
    {
        ChainsCommon_SetVidSensorPrms(
                &gvidSensorObj.vidSensorPrm,
                VID_SENSOR_SAT0088_OV1063X,
                portId,
                numLvdsCh,
                captureSrc
                );
    }
    else if(captureSrc == CHAINS_CAPTURE_SRC_IMX290ISP)
    {
        ChainsCommon_SetVidSensorPrms(
                &gvidSensorObj.vidSensorPrm,
                VID_SENSOR_MULDES_IMX290,
                portId,
                numLvdsCh,
                captureSrc
                );
    }
    else
    {
        UTILS_assert(0);
        /* assert here invalid src  */
    }
    status = VidSensor_create(&gvidSensorObj.vidSensorPrm,
                                &vidSensorStatus);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    VidSensor_control(&gvidSensorObj.vidSensorPrm,
                                VID_SENSOR_CMD_START,
                                NULL,
                                NULL);

    return status;
}


/**
 *******************************************************************************
 *
 * \brief   Stop capture device
 *
 *******************************************************************************
*/
Int32 ChainsCommon_StopCaptureDevice(Chains_CaptureSrc captureSrc)
{
    Int32 status=0;

Vps_printf(" Stop sensor ChainsCommon_StopCaptureDevice \n");
    if(captureSrc == CHAINS_CAPTURE_SRC_OV10635 ||
       captureSrc == CHAINS_CAPTURE_SRC_OV10635_LVDS ||
       captureSrc == CHAINS_CAPTURE_SRC_UB964_OV1063X ||
       captureSrc == CHAINS_CAPTURE_SRC_IMX290ISP ||
       captureSrc == CHAINS_CAPTURE_SRC_OV490)
    {
        VidSensor_control(&gvidSensorObj.vidSensorPrm,
                                    VID_SENSOR_CMD_STOP,
                                    NULL,
                                    NULL);

        VidSensor_control(&gvidSensorObj.vidSensorPrm,
                                    VID_SENSOR_CMD_RESET,
                                    NULL,
                                    NULL);

        VidSensor_delete(&gvidSensorObj.vidSensorPrm, NULL);
    }
    else if((captureSrc == CHAINS_CAPTURE_SRC_HDMI_720P) ||
        (captureSrc == CHAINS_CAPTURE_SRC_HDMI_1080P))
    {
        status = HdmiRecvr_control(&gvidSensorObj.hdmiRecvrPrm,
                                    HDMI_RECVR_CMD_STOP,
                                    NULL,
                                    NULL);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

        HdmiRecvr_delete(&gvidSensorObj.hdmiRecvrPrm, NULL);
    }
    else if((captureSrc == CHAINS_CAPTURE_SRC_VIDDEC_TVP5158))
    {
        status = VideoDecdr_control(&gvidSensorObj.videoDecdrPrm,
                                    VIDEO_DECDR_CMD_STOP,
                                    NULL,
                                    NULL);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

        VideoDecdr_delete(&gvidSensorObj.videoDecdrPrm, NULL);
    }
    else if((captureSrc == CHAINS_CAPTURE_SRC_TRULY_AVB_CAM))
    {
        status = EthCam_delete();
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    return status;
}

VidSensor_CreateParams *ChainsCommon_GetSensorCreateParams()
{
    return (&gvidSensorObj.vidSensorPrm);
}
