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
 * \file chains_main_linux.c
 *
 * \brief  Entry point for IPU1-0 application when A15 OS is Linux
 *
 * \version 0.0 (Jun 2013) : [KC] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include <system_cfg.h>
#include <src/include/chains.h>
#include <src/include/chains_common.h>
#include <src/rtos/utils_common/include/utils_tsk.h>

#include <src/hlos/common/appCtrlLink.h>
#include <src/include/link_stats_monitor.h>
#include <src/rtos/utils_common/include/utils_stat_collector.h>

#include <ti/drv/vps/include/boards/bsp_board.h>

#include <include/common/app_ctrl_radar.h>

#define APP_CTRL_TSK_PRI                   (4)
#define APP_CTRL_TSK_STACK_SIZE            (16*1024)

/**
 *******************************************************************************
 * \brief Link Specific Object
 *******************************************************************************
 */
typedef struct {

    /**< App Ctrl Task Id */
    UInt32 tskId;

    /**< App Ctrl Task Handle */
    Utils_TskHndl tsk;
    VidSensor_CreateParams vidSensorPrm;

    ChainsCommon_Ar12xxConfigOut ar12xxCfg;

} AppCtrl_Obj;

/**
 *******************************************************************************
 * \brief Link Stack
 *******************************************************************************
 */
#pragma DATA_ALIGN(gAppCtrl_tskStack, 32)
#pragma DATA_SECTION(gAppCtrl_tskStack, ".bss:taskStackSection")
UInt8 gAppCtrl_tskStack[APP_CTRL_TSK_STACK_SIZE];

/**
 *******************************************************************************
 * \brief Link Object holds the task id and handle
 *******************************************************************************
 */
AppCtrl_Obj gAppCtrl_obj;

Chains_Ctrl gChains_usecaseCfg;
#ifdef EARLY_USECASE_ENABLE
extern void Chains_EarlyUsecase(Chains_Ctrl *ctlCfg);
#endif
/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief Set DMM priorities
 *
 *******************************************************************************
 */
Void AppCtrl_setSystemL3DmmPri()
{
    /* Assert Mflag of DSS to give DSS highest priority */
    Utils_setDssMflagMode(UTILS_DSS_MFLAG_MODE_FORCE_ENABLE);

    /* enable usage of Mflag at DMM */
    Utils_setDmmMflagEmergencyEnable(TRUE);

    /* Set DMM as higest priority at DMM and EMIF */
    Utils_setDmmPri(UTILS_DMM_INITIATOR_ID_DSS, 0);

    Utils_setBWLimiter(UTILS_DMM_INITIATOR_ID_GPU_P1, 1300);
    Utils_setBWLimiter(UTILS_DMM_INITIATOR_ID_GPU_P2, 1300);
}

static Int32 sensorStart(VideoSensorCreateAndStartAppPrm *pPrm)
{
    UInt32 portId[VIDEO_SENSOR_MAX_LVDS_CAMERAS];
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    VideoSensorCreateAndStartAppPrm *pAppPrm
     = (VideoSensorCreateAndStartAppPrm*)pPrm;

    if(pAppPrm->captureSrcId == CHAINS_CAPTURE_SRC_OV10635)
    {
        if(pAppPrm->isLVDSCaptMode)
        {
            ChainsCommon_MultiCam_StartCaptureDevice(pAppPrm->captureSrcId,portId,pAppPrm->numLvdsCh);
        }
        else
        {
            status = ChainsCommon_StartCaptureDevice(pAppPrm->captureSrcId,1280,720);
        }
    }
    else if (pAppPrm->captureSrcId == CHAINS_CAPTURE_SRC_UB964_OV1063X)
    {
        if(pAppPrm->isLVDSCaptMode)
        {
            ChainsCommon_MultiCam_StartCaptureDevice(pAppPrm->captureSrcId,NULL,pAppPrm->numLvdsCh);
        }
        else
        {
            status = ChainsCommon_StartCaptureDevice(pAppPrm->captureSrcId,1280,720);
        }
    }
    else if (pAppPrm->captureSrcId == CHAINS_CAPTURE_SRC_IMX290ISP)
    {
        if(pAppPrm->isLVDSCaptMode)
        {
            ChainsCommon_MultiCam_StartCaptureDevice(pAppPrm->captureSrcId,portId,pAppPrm->numLvdsCh);
        }
        else
        {
            ChainsCommon_MultiCam_StartCaptureDevice(pAppPrm->captureSrcId,portId,1);
        }
    }
    else if (pAppPrm->captureSrcId == CHAINS_CAPTURE_SRC_OV490)
    {
        if(pAppPrm->isLVDSCaptMode)
        {
            ChainsCommon_MultiCam_StartCaptureDevice(pAppPrm->captureSrcId,portId,pAppPrm->numLvdsCh);
        }
        else
        {
            ChainsCommon_MultiCam_StartCaptureDevice(pAppPrm->captureSrcId,portId,1);
        }
    }
    else
    {
        UTILS_assert(0);
    }

    return status;
}

static Int32 sensorStop(VideoSensorCreateAndStartAppPrm *pAppPrm)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    if((pAppPrm->captureSrcId == CHAINS_CAPTURE_SRC_OV10635) ||
       (pAppPrm->captureSrcId == CHAINS_CAPTURE_SRC_UB964_OV1063X) ||
       (pAppPrm->captureSrcId == CHAINS_CAPTURE_SRC_IMX290ISP)||
       (pAppPrm->captureSrcId == CHAINS_CAPTURE_SRC_OV490))
    {
        status = ChainsCommon_StopCaptureDevice(pAppPrm->captureSrcId);
    }

    return status;
}

static void AppCtrl_initIssParams(AppCtrl_IssParams *pPrms)
{
#ifdef ISS_INCLUDE
    if (NULL != pPrms)
    {
        if (SYSTEM_LINK_ID_INVALID != pPrms->issCaptLinkId)
        {
            appInitIssCaptParams(&pPrms->issSensorInfo, pPrms->issCaptLinkId,
                &pPrms->issCaptLinkPrms);
        }

        if (SYSTEM_LINK_ID_INVALID != pPrms->issIspLinkId)
        {
            appInitIssIspParams(&pPrms->issSensorInfo, pPrms->issIspLinkId,
                &pPrms->issIspLinkPrms);
        }

        if (SYSTEM_LINK_ID_INVALID != pPrms->issSimcopLinkId)
        {
            appInitIssSimcopParams(&pPrms->issSensorInfo,
                pPrms->issSimcopLinkId, &pPrms->issSimcopLinkPrms);
        }

        if (SYSTEM_LINK_ID_INVALID != pPrms->issAewbLinkId)
        {
            appInitIssAewbParams(&pPrms->issSensorInfo,
                pPrms->issAewbLinkId, &pPrms->issAewbLinkPrms);
        }
    }
#endif
}

static void AppCtrl_issSensorStart(AppUtils_Obj *pSensorPrms)
{
#ifdef ISS_INCLUDE
    if (NULL != pSensorPrms)
    {
        appStartIssSensorSerDes(pSensorPrms);
    }
#endif
}

static void AppCtrl_issSensorStop(AppUtils_Obj *pSensorPrms)
{
#ifdef ISS_INCLUDE
    if (NULL != pSensorPrms)
    {
        appStopISSSensor(pSensorPrms);
        appDeleteISSSensor(pSensorPrms);
    }
#endif
}

static void AppCtrl_issSetConfig(AppCtrl_IssParams *pPrm)
{
#ifdef ISS_INCLUDE
    if (NULL != pPrm)
    {
        if (SYSTEM_LINK_ID_INVALID != pPrm->issSimcopLinkId)
        {
            appSetDefaultSimcopParams();
        }

        if ((SYSTEM_LINK_ID_INVALID != pPrm->issIspLinkId) ||
            (SYSTEM_LINK_ID_INVALID != pPrm->issSimcopLinkId))
        {
            appSetDefaultIspParams(&pPrm->issSensorInfo);
        }
    }
#endif
}

static void AppCtrl_issSetBoardMux(AppUtils_Obj *pSensorPrms)
{
#if 0
    if (NULL != pSensorPrms)
    {
        /* Setup PinMux */
        ChainsPlatform_SetPinMux(pSensorPrms->sensorName);

        /* Init Board Mux */
        ChainsBoard_SetBoardMux(pSensorPrms->sensorName);
    }
#endif
}

static void AppCtrl_parseAndSetDccProfileFromSensor(AppUtils_Obj *pSensorPrms)
{
#ifdef ISS_INCLUDE
    if (NULL != pSensorPrms)
    {
        appDccParseAndSetIspParamsFromSensor(pSensorPrms);
    }
#endif
}

static void AppCtrl_parseAndSetDcc(AppCtrl_IssDccParams *pDccPrms)
{
#ifdef ISS_INCLUDE
    if (NULL != pDccPrms)
    {
        appParserAndSetDccProfile(pDccPrms->pDccBuf, pDccPrms->bufSize);
    }
#endif
}

/**
 *******************************************************************************
 *
 * \brief Handles the Commands received.
 *
 * \param   pObj           [IN] AppCtrl_Obj
 *
 * \param   cmd            [IN] input command
 *
 * \param   pPrm           [IN] input message
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 AppCtrl_cmdHandler(AppCtrl_Obj * pObj, UInt32 cmd, Void * pPrm)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
#if defined (BOARD_TYPE_TDA2XX_RVP)
    AppCtrl_BoardIds *boardIds;
#endif

    switch (cmd)
    {
        case APP_CTRL_LINK_CMD_VIDEO_SENSOR_CREATE_AND_START:
        {
            status = sensorStart(pPrm);
            break;
        }

        case APP_CTRL_LINK_CMD_VIDEO_SENSOR_STOP_AND_DELETE:
        {
            VideoSensorCreateAndStartAppPrm *pAppPrm
                 = (VideoSensorCreateAndStartAppPrm*)pPrm;
            status = sensorStop(pAppPrm);
            break;
        }

        case APP_CTRL_LINK_CMD_BOARD_ENABLE_USB_CHARGING:
            Board_enableUsbCharging();
            break;

        case APP_CTRL_LINK_CMD_BOARD_IS_MULTI_DES_CONNECTED:
        {
            AppCtrlCmd_BoardIsMultiDesConnectedPrm *pAppPrm
                = (AppCtrlCmd_BoardIsMultiDesConnectedPrm*)pPrm;

            pAppPrm->isConnected = Board_isMultiDesConnected();
            break;
        }

        case APP_CTRL_LINK_CMD_SET_DMM_PRIORITIES:
             AppCtrl_setSystemL3DmmPri();
            break;

        case APP_CTRL_LINK_CMD_STAT_COLLECTOR_INIT:
            Utils_statCollectorInit(); /* Initializing the statCollector */
            break;

        case APP_CTRL_LINK_CMD_STAT_COLLECTOR_DEINIT:
            Utils_statCollectorDeInit();
            break;
        case APP_CTRL_LINK_CMD_INIT_ISS_PARAMS:
            AppCtrl_initIssParams(pPrm);
            break;

        case APP_CTRL_LINK_CMD_ISS_SENSOR_CREATE:
            {
                #ifdef ISS_INCLUDE
                AppUtils_Obj *pSensorPrms = (AppUtils_Obj *)pPrm;
                if (NULL != pSensorPrms)
                {
                    appCreateISSSensor(pSensorPrms);
                }
                #endif
            }
            break;
        case APP_CTRL_LINK_CMD_ISS_SENSOR_START:
            AppCtrl_issSensorStart(pPrm);
            break;
        case APP_CTRL_LINK_CMD_ISS_SENSOR_STOP_AND_DELETE:
            AppCtrl_issSensorStop(pPrm);
            break;
        case APP_CTRL_LINK_CMD_ISS_DEFAULT_CONFIG:
            AppCtrl_issSetConfig(pPrm);
            break;
        case APP_CTRL_LINK_CMD_SET_BOARD_MUXES:
            AppCtrl_issSetBoardMux(pPrm);
            break;
        case APP_CTRL_LINK_CMD_ENABLE_CSI_OUTPUT:
            Vps_printf("Setting BspUtils_enableUb960CsiOutput!!!!\n");
            BspUtils_enableUb960CsiOutput();
            break;
        case APP_CTRL_LINK_CMD_PARSE_AND_SET_SENSOR_DCC:
            AppCtrl_parseAndSetDccProfileFromSensor(pPrm);
            break;
        case APP_CTRL_LINK_CMD_PARSE_AND_SET_DCC:
            AppCtrl_parseAndSetDcc(pPrm);
            break;
        case APP_CTRL_LINK_CMD_SET_BOARD_IDS:
#if defined (BOARD_TYPE_TDA2XX_RVP)
            boardIds = (AppCtrl_BoardIds *) pPrm;
            bsp_boardTda2xxRvpSomId = boardIds->boardIdSOM;
            bsp_boardTda2xxRvpBaseboardId = boardIds->boardIdBaseboard;
            Bsp_boardClearId();
            Bsp_boardClearBaseBoardRev();
#endif
            break;
        case APP_CTRL_LINK_CMD_LINUX_INIT_COMPLETE:
            gChains_usecaseCfg.linux_InitComplete = TRUE;
            break;
        case APP_CTRL_LINK_CMD_INIT_RADAR:
        {
            AppCtrl_RadarConfigFiles *pConfigFiles =
                            (AppCtrl_RadarConfigFiles *) pPrm;
            appCtrlRadarInit(&pObj->ar12xxCfg,
                             pConfigFiles);
            break;
        }
        case APP_CTRL_LINK_CMD_SET_RADAR_CAPTURE_PARAM:
            appCtrlSetRadarCaptureParamsRadar(pPrm,
                                            &pObj->ar12xxCfg);
            break;
        case APP_CTRL_LINK_CMD_START_RADAR:
            appCtrlRadarStart();
            break;
        case APP_CTRL_LINK_CMD_STOP_RADAR:
            appCtrlRadarStop(&pObj->ar12xxCfg);
            break;
        default:
            break;
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Creates Command handler task
 *        handles the commands for Profiling and core stats
 *
 * \param   pTsk    [IN]  Utils_TskHndl
 *
 * \param   pMsg    [IN]  Utils_MsgHndl
 *
 *******************************************************************************
*/
Void AppCtrl_tskMain(struct Utils_TskHndl_t * pTsk, Utils_MsgHndl * pMsg)
{
    Int32 status;
    AppCtrl_Obj *pObj = (AppCtrl_Obj *) pTsk->appData;

    status = AppCtrl_cmdHandler(pObj,
                                   Utils_msgGetCmd(pMsg),
                                   Utils_msgGetPrm(pMsg));
    Utils_tskAckOrFreeMsg(pMsg, status);

    return;
}

/**
 *******************************************************************************
 *
 * \brief Initialize the ipu systemLink
 *        Initializes the linkObj and creates the task for AppCtrl_tskMain
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 AppCtrl_init()
{
    Int32 status;
    System_LinkObj linkObj;
    AppCtrl_Obj *pObj;
    char tskName[32];
    unsigned int coreId;

    pObj = &gAppCtrl_obj;

    memset(pObj, 0, sizeof(*pObj));
    coreId = System_getSelfProcId();
    pObj->tskId = SYSTEM_MAKE_LINK_ID(coreId, SYSTEM_LINK_ID_APP_CTRL);

    linkObj.pTsk = &pObj->tsk;
    linkObj.linkGetFullBuffers = NULL;
    linkObj.linkPutEmptyBuffers = NULL;
    linkObj.getLinkInfo = NULL;

    System_registerLink(pObj->tskId, &linkObj);

    sprintf(tskName, "APP_CTRL");

    status = Utils_tskCreate(&pObj->tsk,
                             AppCtrl_tskMain,
                             APP_CTRL_TSK_PRI,
                             gAppCtrl_tskStack,
                             sizeof(gAppCtrl_tskStack), pObj, tskName,
                             UTILS_TSK_AFFINITY_CORE0);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Delete the AppCtrl_tskMain created
 *
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 AppCtrl_deInit()
{
    Utils_tskDelete(&gAppCtrl_obj.tsk);

    return SYSTEM_LINK_STATUS_SOK;
}


/**
 *******************************************************************************
 *
 * \brief   Entry point for application on IPU1-0
 *
 * \param   arg0    [IN]  default args
 *
 * \param   arg1    [IN]  default args
 *
 *******************************************************************************
*/
Void Chains_main(UArg arg0, UArg arg1)
{
#ifdef IPU_PRIMARY_CORE_IPU1
    Void IPU1_0_main(UArg arg0, UArg arg1);
#else
    Void IPU2_main(UArg arg0, UArg arg1);
#endif

    Vps_printf(" CHAINS: Application Started !!!");

    AppCtrl_init();

#ifndef A15_TARGET_OS_QNX
    GrpxSrcLink_init();
    SplitLink_init();
    Chains_linkStatsMonitorInit();
#endif

    Board_init();

#ifdef ISS_INCLUDE
    IssSensor_Init();
#endif

#ifdef ULTRASONIC_INCLUDE
#ifdef PGA460
        UltrasonicCaptureLink_init(USM_ID_PGA460);
#elif PGA450
        UltrasonicCaptureLink_init(USM_ID_PGA450);
#endif
#endif

#ifdef EARLY_USECASE_ENABLE
    Chains_EarlyUsecase(&gChains_usecaseCfg);
#endif

#ifdef IPU_PRIMARY_CORE_IPU1
    IPU1_0_main(NULL, NULL);
#else
    IPU2_main(NULL, NULL);
#endif

    AppCtrl_deInit();

#ifndef A15_TARGET_OS_QNX
    GrpxSrcLink_deInit();
    SplitLink_deInit();
    Chains_linkStatsMonitorDeInit();
#endif

    Board_deInit();
    Vps_printf(" CHAINS: Application Exited !!!");
}

