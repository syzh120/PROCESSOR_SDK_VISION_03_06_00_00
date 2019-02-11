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
#include <src/rtos/utils_common/include/utils_tsk.h>
#include <src/rtos/alg_plugins/surroundview/include/svCommonDefs.h>
#include <src/include/chains_common.h>
#include <src/rtos/iss/include/iss_sensors.h>
#include <src/rtos/iss/include/iss_utils.h>
#include <src/include/chains_common_surround_view.h>
#include <src/rtos/links_common/system/system_priv_common.h>
#include <src/include/chains_common_osal.h>
#include <src/include/chains_common_srv_calib.h>
#include "chains_issMultCaptIspDeWarp3dSv_priv.h"
#include "chains_issMultCaptIspDeWarp3dSv.h"

/*******************************************************************************
 *  Defines / Globals
 *******************************************************************************
*/

/* Media Thread */
#define SRV_UC_3D_MEDIA_TASK_PRI            (4U)
#define SRV_UC_3D_MEDIA_TASK_STACK_SIZE     (32U * 1024U)
#pragma DATA_ALIGN(srvUc3dMediaTaskStack, 32)
#pragma DATA_SECTION(srvUc3dMediaTaskStack, ".bss:taskStackSection")
static UInt8 srvUc3dMediaTaskStack[SRV_UC_3D_MEDIA_TASK_STACK_SIZE];

/* DSP create Thread */
/*
 *  The DSP create thread priority should be lower than SYSTEM_TSK_PRI (2U).
 *  Otherwise the use case creation on DSP will not happen in parallel.
 */
#define SRV_UC_3D_DSPCREATE_TASK_PRI            (1U)
#define SRV_UC_3D_DSPCREATE_TASK_STACK_SIZE     (32U * 1024U)
#pragma DATA_ALIGN(srvUc3dDspCreateTaskStack, 32)
#pragma DATA_SECTION(srvUc3dDspCreateTaskStack, ".bss:taskStackSection")
static UInt8 srvUc3dDspCreateTaskStack[SRV_UC_3D_DSPCREATE_TASK_STACK_SIZE];

/* View transitions Variables */
static UInt32 gNumViewPoints = 0U;
static UInt32 gSvAutoSwitchViews = TRUE;
static UInt32 gLastCount = 0U;
static UInt32 gViewId = 0U;
static UInt32 gDirViewPoint = 0U;

static chains_issMultCaptIspDewarpSv_DisplayAppObj chainsObj;
/**< Instance object of this chain */

#if defined(SOC_TDA2PX)
#define SRV_SRC_DIR SRV_DIR_2PX
#else
#define SRV_SRC_DIR SRV_DIR_3X
#endif


/*
 *******************************************************************************
 *  LDC Optimization parameters
 *******************************************************************************
 */
/*
 *  LDC read Max Tag count:
        0..15
 */
UInt32 gLdcRdMaxTagCnt = 15U;

/*
 *  Route LDC read traffic on NRT1 port
 */
ALG_PLUGIN_DEWARP_LDC_ROUTE gLdcTraffic = ALG_PLUGIN_DEWARP_LDC_ROUTE_NRT1;

/*
 *  Route ISP traffic on NRT2 port
 */
IssM2mIspLink_Route gIspTraffic = ISSM2MISP_LINK_ROUTE_NRT2;

/*
 *  Place the LDC LUTs in OCMC RAM
 */
Bool gUseOcmcLdcLut = TRUE;

/*
 *  Below setting is valid only if 'LOCAL_LDC_SLICE_PRM' is defied in
 *  chains_issMultCaptIspDeWarp3dSv_Media.c file:
 *      SRV_UC_3D_LDC_SLICE_PRM_1_16x16
 *      SRV_UC_3D_LDC_SLICE_PRM_1_16x8
 *      SRV_UC_3D_LDC_SLICE_PRM_2_16x16_16x8
 *      SRV_UC_3D_LDC_SLICE_PRM_2_16x16_16x4
 *      SRV_UC_3D_LDC_SLICE_PRM_1_16x4
 *      SRV_UC_3D_LDC_SLICE_PRM_2_16x8_16x4
 *      SRV_UC_3D_LDC_SLICE_PRM_3_16x16_16x8_16x4
 */
SRV_UC_3D_LDC_SLICE_PRM gLdcSlicePrmNo = SRV_UC_3D_LDC_SLICE_PRM_3_16x16_16x8_16x4;
UInt32 gLdcPixelPad = SRV_LDC_PIXEL_PAD;

/*
 *  Luma Interpolation Type:
 *      VPS_ISS_LDC_LUMA_INTRP_BICUBIC
 *      VPS_ISS_LDC_LUMA_INTRP_BILINEAR
 */
vpsissldcLumaIntrType_t gLdcLumaIntrType = VPS_ISS_LDC_LUMA_INTRP_BILINEAR;

/*
 *******************************************************************************
 *******************************************************************************
 */

char gSrvUc3dRunTimeMenu[] = {
"\r\n "
"\r\n ===================="
"\r\n Chains Run-time Menu"
"\r\n ===================="
"\r\n "
"\r\n 0: Stop Chain"
#ifndef TDA3XX_128MB_DDR
"\r\n 1: Save a Captured RAW frame from channel 0 (Will be saved in DDR)"
"\r\n 2: Save a DeWarp Output Frame (Will be saved in DDR)"
"\r\n 3: Save ISP output frames (Will be saved in MMC/SD : All channels)"
#endif
"\r\n s: Stop / Start Transitions"
"\r\n n: Change to Next View Point, after transitions are stopped"
"\r\n r: Change to Previous View Point, after transitions are stopped"
"\r\n "
"\r\n d: Save Display Frame to MMC/SD card"
"\r\n "
"\r\n t: Print UB96x debug registers "
"\r\n "
"\r\n p: Print Performance Statistics "
"\r\n "
"\r\n Enter Choice: "
"\r\n "
};

/*******************************************************************************
 *  Local Function Implementation
 *******************************************************************************
 */
static Void setSyncParams(SyncLink_CreateParams *pSyncPrm,
                            UInt32 numCh,
                            UInt32 syncPeriod)
{
    pSyncPrm->syncDelta = syncPeriod;
    pSyncPrm->syncThreshold = pSyncPrm->syncDelta * 2U;
}

static Void saveIspOutputIntoMmcsd(
                            chains_issMultCaptIspDewarpSv_DisplayAppObj *pObj)
{
    UInt32 cnt, chanId;
    char fileName[128];
    Int32 fp;
    IssM2mIspLink_GetSaveFrameStatus saveFrameStatus;

    for (cnt = 0;cnt < pObj->numCh;cnt ++)
    {
        chanId = cnt;
        System_linkControl(pObj->ucObj.IssM2mIspLinkID,
                            ISSM2MISP_LINK_CMD_SAVE_FRAME,
                            &chanId,
                            sizeof(chanId),
                            TRUE);

        /* Wait for frame dump completion */
        saveFrameStatus.chId = chanId;
        do {
            System_linkControl(pObj->ucObj.IssM2mIspLinkID,
                                ISSM2MISP_LINK_CMD_GET_SAVE_FRAME_STATUS,
                                &saveFrameStatus,
                                sizeof(IssM2mIspLink_GetSaveFrameStatus),
                                TRUE);
            /* 30 FPS is the assumption */
            Task_sleep(35U);
        }while (saveFrameStatus.isSaveFrameComplete == FALSE);

        switch(cnt)
        {
            default:
            case 0:
                strcpy(fileName,"FRONT.YUV");
                break;
            case 1:
                strcpy(fileName,"RIGHT.YUV");
                break;
            case 2:
                strcpy(fileName,"BACK.YUV");
                break;
            case 3:
                strcpy(fileName,"LEFT.YUV");
                break;
        }

        fp = ChainsCommon_Osal_fileOpen(fileName, \
                                        CHAINSCOMMON_OSAL_FILEMODE_WRITE_BIN);
        UTILS_assert(0 <= fp);

        Vps_printf("Writing YUV image %d to the file %s ...\n",cnt, fileName);

        /* Dump Y plane */
        ChainsCommon_Osal_fileWrite(
                            fp,
                            (UInt8*)saveFrameStatus.saveBufAddr[0],
                            saveFrameStatus.saveBufSize[0]);

        /* Dump UV plane */
        ChainsCommon_Osal_fileWrite(
                            fp,
                            (UInt8*)saveFrameStatus.saveBufAddr[1],
                            saveFrameStatus.saveBufSize[1]);

        ChainsCommon_Osal_fileClose(fp);

        Vps_printf("Writing YUV image %d to the file %s DONE\n",cnt, fileName);
    }

    Vps_printf("Writing YUV image is completed\n");
}

static Void saveRawIntoMmcsd(
                chains_issMultCaptIspDewarpSv_DisplayAppObj *pObj, UInt32 chId)
{
    char fileName[128];
    Int32 fp;
    IssCaptureLink_GetSaveFrameStatus saveFrameStatus;
    System_linkControl(chainsObj.ucObj.IssCaptureLinkID,
                        ISSCAPTURE_LINK_CMD_SAVE_FRAME,
                        &chId,
                        sizeof(UInt32),
                        TRUE);
    /* Wait for frame dump completion */
    do {
        System_linkControl(pObj->ucObj.IssCaptureLinkID,
                            ISSCAPTURE_LINK_CMD_GET_SAVE_FRAME_STATUS,
                            &saveFrameStatus,
                            sizeof(IssCaptureLink_GetSaveFrameStatus),
                            TRUE);
        /* 30 FPS is the assumption */
        Task_sleep(35U);
    }while (saveFrameStatus.isSaveFrameComplete == FALSE);

    switch(chId)
    {
        default:
        case 0:
            strcpy(fileName,"FRONT.raw");
            break;
        case 1:
            strcpy(fileName,"RIGHT.raw");
            break;
        case 2:
            strcpy(fileName,"BACK.raw");
            break;
        case 3:
            strcpy(fileName,"LEFT.raw");
            break;
    }

    fp = ChainsCommon_Osal_fileOpen(fileName, CHAINSCOMMON_OSAL_FILEMODE_WRITE_BIN);
    UTILS_assert(0 <= fp);

    Vps_printf("Writing RAW image to the file %s ...\n", fileName);

    ChainsCommon_Osal_fileWrite(
                        fp,
                        (UInt8*)saveFrameStatus.bufAddr,
                        saveFrameStatus.bufSize);

    ChainsCommon_Osal_fileClose(fp);

    Vps_printf("Writing RAW image to the file %s DONE\n", fileName);
}

/**
 *******************************************************************************
 *
 * \brief   LDC Advanced Configuration
 *
 *          Function sends a control command to capture and display link to
 *          to Start all the required links . Links are started in reverce
 *          order as information of next link is required to connect.
 *          System_linkStart is called with LinkId to start the links.
 *
 * \param   pObj  [IN] chains_issMultCaptIspDewarpSv_DisplayAppObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
static Void ldcOptimizationConfig(
                chains_issMultCaptIspDewarpSv_DisplayAppObj *pObj,
                ALG_PLUGIN_DEWARP_LDC_ROUTE ldcTraffic,
                IssM2mIspLink_Route ispTraffic)
{
    Int32 status;
    AlgLink_DeWarpSetLdcRouteCfg ldcRouteCfg;
    IssM2mIspLink_RouteCfg ispRouteCfg;
    AlgLink_DeWarpTaskPriority dewarpTaskPri;

    ldcRouteCfg.route = ldcTraffic;
    ldcRouteCfg.baseClassControl.controlCmd = \
                                        ALG_LINK_DEWARP_CMD_LDC_ROUTECFG;
    ldcRouteCfg.baseClassControl.size = \
                                    sizeof (AlgLink_DeWarpSetLdcRouteCfg);

    status = System_linkControl(
                            pObj->ucObj.Alg_DeWarpLinkID,
                            ALGORITHM_LINK_CMD_CONFIG,
                            &ldcRouteCfg,
                            sizeof(AlgLink_DeWarpSetLdcRouteCfg),
                            TRUE);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    ispRouteCfg.route = ispTraffic;
    status = System_linkControl(
                            pObj->ucObj.IssM2mIspLinkID,
                            ISSM2MISP_LINK_CMD_SET_ISP_ROUTE_CFG,
                            &ispRouteCfg,
                            sizeof(IssM2mIspLink_RouteCfg),
                            TRUE);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    /*
     *  Set higher priority for the Dewarp alg plug-in
     */
    dewarpTaskPri.baseClassControl.controlCmd = ALG_LINK_DEWARP_CMD_GET_TASKPRI;
    dewarpTaskPri.baseClassControl.size = sizeof(AlgLink_DeWarpTaskPriority);

    status = System_linkControl(
                            pObj->ucObj.Alg_DeWarpLinkID,
                            ALGORITHM_LINK_CMD_CONFIG,
                            &dewarpTaskPri,
                            sizeof(AlgLink_DeWarpTaskPriority),
                            TRUE);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    Vps_printf(" Dewarp Task Priority = %d\n",dewarpTaskPri.taskPriority);

    if (ALGORITHM_LINK_TSK_PRI == dewarpTaskPri.taskPriority)
    {
        dewarpTaskPri.taskPriority += 2U;
    }
    dewarpTaskPri.baseClassControl.controlCmd = ALG_LINK_DEWARP_CMD_SET_TASKPRI;
    dewarpTaskPri.baseClassControl.size = sizeof(AlgLink_DeWarpTaskPriority);

    status = System_linkControl(
                            pObj->ucObj.Alg_DeWarpLinkID,
                            ALGORITHM_LINK_CMD_CONFIG,
                            &dewarpTaskPri,
                            sizeof(AlgLink_DeWarpTaskPriority),
                            TRUE);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);
}

Void dspCreateTask(UArg arg1, UArg arg2)
{
    Int32 status;
    chains_issMultCaptIspDewarpSv_DisplayAppObj *pChainsObj = \
            (chains_issMultCaptIspDewarpSv_DisplayAppObj *)arg1;
    AlgorithmLink_SynthesisControlParams synthLateCreatePrm;

    BspOsal_semWait(pChainsObj->dspCreate, BSP_OSAL_WAIT_FOREVER);

    synthLateCreatePrm.baseClassControl.controlCmd = \
                                    ALGORITHM_LINK_SRV_SYNTHESIS_LATE_CREATE;
    synthLateCreatePrm.baseClassControl.size = \
                                sizeof (AlgorithmLink_SynthesisControlParams);
    status = System_linkControl(pChainsObj->ucObj.Alg_SynthesisLinkID,
                                ALGORITHM_LINK_CMD_CONFIG,
                                &synthLateCreatePrm,
                                sizeof(AlgorithmLink_SynthesisControlParams),
                                TRUE);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    Vps_printf (" DSP Create done\n");
}

static Void postDspCreateSem(chains_issMultCaptIspDewarpSv_DisplayAppObj *chainsObj)
{
    BspOsal_semPost(chainsObj->dspCreate);
}

static Int32 createMediaThread(
                        chains_issMultCaptIspDewarpSv_DisplayAppObj *chainsObj)
{
    Int32 status;

    chainsObj->startSrvDemo = BspOsal_semCreate(0, (Bool) TRUE);
    UTILS_assert(NULL != chainsObj->startSrvDemo);

    chainsObj->mediaTaskHndl = BspOsal_taskCreate((BspOsal_TaskFuncPtr)
                                    chains_issMultCaptIspDeWarp3dSv_MediaTask,
                                    "ChainsCommon_Iss3DSRVDeWarp_MediaTsk",
                                    SRV_UC_3D_MEDIA_TASK_PRI,
                                    srvUc3dMediaTaskStack,
                                    sizeof(srvUc3dMediaTaskStack),
                                    chainsObj,
                                    UTILS_TSK_AFFINITY_CORE0);
    UTILS_assert(NULL != chainsObj->mediaTaskHndl);

    status = Utils_prfLoadRegister(chainsObj->mediaTaskHndl,
                                   "3D_SRV_MEDIA_TSK");
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    /*
     *  Thread for doing chain creation on DSP in parallel
     */
    chainsObj->dspCreate = BspOsal_semCreate(0, (Bool) TRUE);
    UTILS_assert(NULL != chainsObj->dspCreate);

    chainsObj->dspCreateTaskHndl = BspOsal_taskCreate((BspOsal_TaskFuncPtr)
                                    dspCreateTask,
                                    "ChainsCommon_Iss3DSRVDeWarp_DSPCreateTsk",
                                    SRV_UC_3D_DSPCREATE_TASK_PRI,
                                    srvUc3dDspCreateTaskStack,
                                    sizeof(srvUc3dDspCreateTaskStack),
                                    chainsObj,
                                    UTILS_TSK_AFFINITY_CORE0);
    UTILS_assert(NULL != chainsObj->dspCreateTaskHndl);

    return (status);
}

static Void deleteMediaThread(
                        chains_issMultCaptIspDewarpSv_DisplayAppObj *chainsObj)
{
    Utils_prfLoadUnRegister(chainsObj->mediaTaskHndl);
    BspOsal_taskDelete(&chainsObj->mediaTaskHndl);
    BspOsal_semDelete(&chainsObj->startSrvDemo);

    /* DSP create thread */
    BspOsal_taskDelete(&chainsObj->dspCreateTaskHndl);
    BspOsal_semDelete(&chainsObj->dspCreate);
}

static AlgLink_DeWarpViewPointParams *provideViewParams (UInt32 processedCount)
{
    /* There are 30 iteration between view points */
    #define NUM_ITERATION_VIEW_POINT        (30U)
    #define DELAY_IN_FRAMES                 (50U)

    static UInt32 lastViewId = 0U;
    static Bool intiateViewPointCfg = TRUE;
    UInt32 switchFlag;

    /* In case of warparounds */
    if (gLastCount > processedCount)
    {
        gLastCount = processedCount;
    }

    if ((TRUE == intiateViewPointCfg) && (DELAY_IN_FRAMES == processedCount))
    {
        intiateViewPointCfg = FALSE;
    }
    if (TRUE == chainsObj.freeToSwitch)
    {
        if (FALSE == gSvAutoSwitchViews)
        {
            /*
             *  If the Auto switch is OFF then keep using
             *  the last view point params.
             */
            lastViewId = gViewId;
        }
        else
        {
            if (0U == gDirViewPoint)
            {
                /* Forward direction */
                if (1U == gViewId)
                {
                    /* Corner point */
                    switchFlag = \
                            ((gLastCount + DELAY_IN_FRAMES) < processedCount);
                }
                else if ((gViewId > 1U) && \
                                (0U == ((gViewId - 1U) % NUM_ITERATION_VIEW_POINT)))
                {
                    switchFlag = \
                            ((gLastCount + DELAY_IN_FRAMES) < processedCount);
                }
                else
                {
                    switchFlag = (gLastCount < processedCount);
                }
            }

            if (1U == gDirViewPoint)
            {
                /* Backward direction */
                if ((gNumViewPoints - 2U) == gViewId)
                {
                    /* Corner point */
                    switchFlag = \
                            ((gLastCount + DELAY_IN_FRAMES) < processedCount);
                }
                else if ((gViewId < (gNumViewPoints - 1U)) && \
                            (0U == ((gViewId + 1) % NUM_ITERATION_VIEW_POINT)))
                {
                    switchFlag = \
                            ((gLastCount + DELAY_IN_FRAMES) < processedCount);
                }
                else
                {
                    switchFlag = (gLastCount < processedCount);
                }
            }

            if (switchFlag)
            {
                lastViewId = gViewId;

                if(gDirViewPoint == 0)
                {
                    gViewId++;
                }
                else
                {
                    gViewId--;
                }

                if(gViewId == (gNumViewPoints - 1U))
                {
                    /*
                     *  Switch direction to DOWN
                     */
                    gDirViewPoint = 1U;
                }

                if(gViewId == 0U)
                {
                    /*
                     *  Switch direction to UP
                     */
                    gDirViewPoint = 0U;
                }

                gLastCount = processedCount;
            }
        } /* if (TRUE == gSvAutoSwitchViews) */

        return (&chainsObj.algViewParams[lastViewId]);
    }
    else
    {
        /*
         *  Start Surround view with first view point.
         */
        return (&chainsObj.algViewParams[0U]);
    }
}


/**
 *******************************************************************************
 *
 * \brief   ISP and Dewarp update with the default parameters
 *
 *******************************************************************************
*/
static Void updateIspDeWarpWithDefaultParams(
            chains_issMultCaptIspDewarpSv_DisplayAppObj *pObj)
{
    Int32 status;
    UInt32 numCh;
    AlgorithmLink_SrvCommonViewPointParams *pDefViewCfg;
    UInt32 cnt, downScaleFactor, srvSubSample;

    pDefViewCfg = &chainsObj.algViewParams[SRV_UC_3D_DEFAULT_VIEW_TO_USE];

    /* ISP Config */
    appSetDefaultIspParams(&pObj->appObjPrms);
    appSetIspParamsFromDCC(&pObj->appObjPrms);

    /* Initialize Simcop Configuration */
    IssM2mSimcopLink_ConfigParams_Init(&pObj->simcopConfig);

    pObj->simcopConfig.ldcConfig = &pObj->ldcCfg;
    pObj->simcopConfig.vtnfConfig = &pObj->vtnfCfg;

    /* Simcop/Dewarp Config */
    IssUtils_InitSimcopConfig(
            &pObj->simcopConfig,
            pObj->bypassLdc,
            pObj->bypassVtnf);

    /* Changing Simcop Configuration as required for this usecase */
    if (pObj->bypassLdc == TRUE)
    {
        pObj->ldcCfg.pixelPad = 0;
    }
    else
    {
        pObj->ldcCfg.pixelPad = gLdcPixelPad;
    }

    pObj->ldcCfg.advCfg.outputBlockWidth = 16;
    pObj->ldcCfg.advCfg.outputBlockHeight = 16;
    pObj->ldcCfg.lumeIntrType = gLdcLumaIntrType;

    Vps_printf (" ********** LDC Optimization **************\n");
    Vps_printf (" gLdcRdMaxTagCnt   = %d\n",gLdcRdMaxTagCnt);
    Vps_printf (" gLdcTrafficOnNrt1 = %d\n",gLdcTraffic);
    Vps_printf (" gIspTrafficOnNrt2 = %d\n",gIspTraffic);
    Vps_printf (" gUseOcmcLdcLut    = %d\n",gUseOcmcLdcLut);
    Vps_printf (" gLdcSlicePrmNo    = %d\n",gLdcSlicePrmNo);
    Vps_printf (" gLdcPixelPad      = %d\n",gLdcPixelPad);
    Vps_printf (" lumeIntrType(0:bicubic,1:bilinear) = %d\n",\
            pObj->ldcCfg.lumeIntrType);
    Vps_printf (" ******************************************\n");

    /*
     *  Calculate the down scale factor as power of 2
     */
    downScaleFactor = 0;
    srvSubSample = pDefViewCfg->srvSubSample;
    for(cnt = 0U;cnt < 32;cnt++)
    {
        srvSubSample = (srvSubSample >> 1);
        if(srvSubSample == 0)
            break;
        downScaleFactor ++;
    }

    /* MUST be called after link create and before link start */
    /* Apply the same config to all channel,
        right now the sensor are the same so its fine. */
    for (numCh = 0U; numCh < pObj->numCh; numCh++)
    {
        pObj->simcopConfig.chNum = numCh;

        /* Configure the LDC Luts */
        pObj->ldcCfg.lutCfg.downScaleFactor = \
                            (vpsissldcLutDownScFactor_t)downScaleFactor;

        if (pDefViewCfg->ldcOutFrameWidth[numCh] > SRV_UC_3D_ISP_OUTPUT_WIDTH_W_PAD)
        {
            pObj->ldcCfg.lutCfg.lineOffset = \
                            SRV_LDC_MESH_TABLE_PITCH(pDefViewCfg->ldcOutFrameWidth[numCh], \
                                                    pDefViewCfg->srvSubSample);
        }
        else
        {
            pObj->ldcCfg.lutCfg.lineOffset = \
                            SRV_LDC_MESH_TABLE_PITCH(SRV_UC_3D_ISP_OUTPUT_WIDTH_W_PAD, \
                                                    pDefViewCfg->srvSubSample);
        }

        pObj->ldcCfg.inputFrameWidth = SRV_UC_3D_ISP_OUTPUT_WIDTH_W_PAD;
        pObj->ldcCfg.inputFrameHeight = SRV_UC_3D_ISP_OUTPUT_HEIGHT_W_PAD;

        pObj->ldcCfg.advCfg.outputFrameWidth =
                                        pDefViewCfg->ldcOutFrameWidth[numCh];
        pObj->ldcCfg.advCfg.outputFrameHeight =
                                        pDefViewCfg->ldcOutFrameHeight[numCh];
        pObj->ldcCfg.advCfg.outputBlockWidth = SRV_UC_3D_LDC_BLOCK_WIDTH;
        pObj->ldcCfg.advCfg.outputBlockHeight = SRV_UC_3D_LDC_BLOCK_HEIGHT;

        pObj->deWarpSimcopCfg.chNum = pObj->simcopConfig.chNum;
        pObj->deWarpSimcopCfg.ldcConfig = pObj->simcopConfig.ldcConfig;
        pObj->deWarpSimcopCfg.vtnfConfig = pObj->simcopConfig.vtnfConfig;

        /* Frame a plugin command and sent it out */
        pObj->deWarpSimcopCfg.baseClassControl.controlCmd
                                            = ALG_LINK_DEWARP_CMD_SET_LDCCONFIG;
        pObj->deWarpSimcopCfg.baseClassControl.size
                                            = sizeof(pObj->deWarpSimcopCfg);
        status = System_linkControl(pObj->ucObj.Alg_DeWarpLinkID,
                                    ALGORITHM_LINK_CMD_CONFIG,
                                    &pObj->deWarpSimcopCfg,
                                    sizeof(pObj->deWarpSimcopCfg),
                                    TRUE);
        UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);
    }
}
/**
 *******************************************************************************
 *
 * \brief   Update ISS Capture and ISP parameters for multi channel support
 *
 *******************************************************************************
*/
static Void updateCaptureIspPrm(
            chains_issMultCaptIspDewarpSv_DisplayAppObj *pObj,
            UInt32 rszAOutWidth,
            UInt32 rszAOutHeight)
{
    UInt32 ch;
    IssCaptureLink_CreateParams *pCapturePrm = &pObj->ucObj.IssCapturePrm;
    IssCaptureLink_OutParams *pOutPrm0, *pOutPrm;
    IssM2mIspLink_CreateParams *pIspPrm = &pObj->ucObj.IssM2mIspPrm;

    pCapturePrm->numCh = pObj->numCh;
    pOutPrm0 = &pCapturePrm->outParams[0U];

    pIspPrm->channelParams[0U].outParams.widthRszA = rszAOutWidth;
    pIspPrm->channelParams[0U].outParams.heightRszA = rszAOutHeight;

    /* Disable Resizer B */
    pIspPrm->channelParams[0U].\
                        enableOut[ISSM2MISP_LINK_OUTPUTQUE_IMAGE_RSZ_B] = 0;

    for(ch = 1;ch < pCapturePrm->numCh;ch++)
    {
        pOutPrm = &pCapturePrm->outParams[ch];

        pOutPrm->dataFormat = pOutPrm0->dataFormat;
        pOutPrm->width = pOutPrm0->width;
        pOutPrm->height = pOutPrm0->height;
        pOutPrm->maxWidth = pOutPrm0->maxWidth;
        pOutPrm->maxHeight = pOutPrm0->maxHeight;
        pOutPrm->numOutBuf = pOutPrm0->numOutBuf;
        pOutPrm->inCsi2DataFormat = pOutPrm0->inCsi2DataFormat;
        pOutPrm->inCsi2VirtualChanNum = ch;

        pIspPrm->channelParams[ch].outParams.widthRszA = rszAOutWidth;
        pIspPrm->channelParams[ch].outParams.heightRszA = rszAOutHeight;

        /* Disable Resizer B */
        pIspPrm->channelParams[ch].\
                            enableOut[ISSM2MISP_LINK_OUTPUTQUE_IMAGE_RSZ_B] = 0;
    }
}

/**
 *******************************************************************************
 *
 * \brief   Set the pin mux for the TDA3X EVM
 *
 *******************************************************************************
*/
static setMuxes(chains_issMultCaptIspDewarpSv_DisplayAppObj *pObj)
{
#ifndef BOARD_TYPE_TDA3XX_RVP
    /* Mux is configured only on TDA3X EVM */
    /* Setup PinMux */
    ChainsPlatform_SetPinMux(pObj->chainsCfg->sensorName);

    /* Init Board Mux */
    ChainsBoard_SetBoardMux(pObj->chainsCfg->sensorName);
#endif
}

/*******************************************************************************
 *  Functions that would be called to create, apply config, start and stop the
 *      chain.
 *******************************************************************************
 */

Void chains_issMultCaptIspDeWarp3dSv_SetAppPrms(
                    chains_issMultCaptIspDeWarp3dSvObj *pUcObj, Void *appObj)
{
    UInt32 numCh, chId;
    chains_issMultCaptIspDewarpSv_DisplayAppObj *pObj
                        = (chains_issMultCaptIspDewarpSv_DisplayAppObj*)appObj;
    IssM2mIspLink_OperatingMode ispOpMode;
    Int16 carBoxWidth;
    Int16 carBoxHeight;
    AlgorithmLink_SrvCommonViewPointParams *pDefViewCfg;
    UInt32 lineOffset;
    System_LinkChInfo *pChInfo;

    pDefViewCfg = &chainsObj.algViewParams[SRV_UC_3D_DEFAULT_VIEW_TO_USE];

    pObj->captureOutWidth  = SRV_UC_3D_CAPT_SENSOR_OV10640_WIDTH;
    pObj->captureOutHeight = SRV_UC_3D_CAPT_SENSOR_OV10640_HEIGHT;

    if(0 == strcmp(pObj->chainsCfg->sensorName, SENSOR_APTINA_AR0140_TIDA262))
    {
        pObj->captureOutWidth  = SRV_UC_3D_CAPT_SENSOR_AR140_WIDTH;
        pObj->captureOutHeight = SRV_UC_3D_CAPT_SENSOR_AR140_HEIGHT;
    }

    ChainsCommon_GetDisplayWidthHeight(pObj->chainsCfg->displayType,
                                       &pObj->displayWidth,
                                       &pObj->displayHeight);

    ispOpMode = pObj->chainsCfg->ispOpMode;

    pObj->bypassVtnf = TRUE;
    pObj->bypassLdc  = FALSE;

    pObj->simcopConfig.ldcConfig = &pObj->ldcCfg;
    pObj->simcopConfig.vtnfConfig = &pObj->vtnfCfg;

    /* Create the sensor now */
    strncpy(pObj->appObjPrms.sensorName, pObj->chainsCfg->sensorName,
        ISS_SENSORS_MAX_NAME);
    pObj->appObjPrms.numCh = pObj->numCh;
    pObj->appObjPrms.ispOpMode = ispOpMode;
    pObj->appObjPrms.simcopOpMode = ISSM2MSIMCOP_LINK_OPMODE_MAXNUM;
    pObj->appObjPrms.numCSI2Inst = 1;
    appCreateISSSensor(&pObj->appObjPrms);

    appInitIssCaptParams(&pObj->appObjPrms, pUcObj->IssCaptureLinkID,
        &pUcObj->IssCapturePrm);
    appInitIssIspParams(&pObj->appObjPrms, pUcObj->IssM2mIspLinkID,
        &pUcObj->IssM2mIspPrm);
    appInitIssAewbParams(&pObj->appObjPrms, pUcObj->Alg_IssAewbLinkID,
        &pUcObj->Alg_IssAewbPrm);

    /*  Override the capture and ISP parameters for multi channel and
        disable resizer B */
    updateCaptureIspPrm(
                pObj,
                pObj->captureOutWidth,
                pObj->captureOutHeight);


    /* AEWB parameters */
    pUcObj->Alg_IssAewbPrm.runAewbOnlyForOneCh = TRUE;
    pUcObj->Alg_IssAewbPrm.chId = 0U;

    /* deWarp create params */
    for(chId = 0U; chId < ALG_LINK_DEWARP_MAX_CH; chId++)
    {
        pUcObj->Alg_DeWarpPrm.channelParams[chId].operatingMode
                                                    = ALGLINK_DEWARP_OPMODE_LDC;

        pUcObj->Alg_DeWarpPrm.channelParams[chId].numBuffersPerCh = 3U;
    }

    ChainsCommon_SurroundView_SetSyncPrm(
        &pUcObj->Sync_dewarpPrm, pObj->numCh, 1); /* 1: Tight Sync */

    /* Display */
    pUcObj->Display_VideoPrm.rtParams.tarHeight = pDefViewCfg->srvOutputHeight;
    pUcObj->Display_VideoPrm.rtParams.posY = (pObj->displayHeight - pDefViewCfg->srvOutputHeight)/2;
    pUcObj->Display_VideoPrm.rtParams.tarWidth = pDefViewCfg->srvOutputWidth;
    pUcObj->Display_VideoPrm.rtParams.posX = (pObj->displayWidth - pDefViewCfg->srvOutputWidth)/2;;
    pUcObj->Display_VideoPrm.displayId = DISPLAY_LINK_INST_DSS_VID1;

    ChainsCommon_StartDisplayCtrl(
                                    pObj->chainsCfg->displayType,
                                    pObj->displayWidth,
                                    pObj->displayHeight);

    carBoxWidth = SRV_UC_3D_CARBOX_WIDTH;
    carBoxHeight = SRV_UC_3D_CARBOX_HEIGHT;

    setSyncParams(&pUcObj->Sync_dewarpPrm, pObj->numCh, 35U);

    ChainsCommon_SurroundView_SetSynthParams(&pUcObj->Alg_SynthesisPrm,
                                            SRV_UC_3D_LDC_OUTPUT_WIDTH_MAX,
                                            SRV_UC_3D_LDC_OUTPUT_HEIGHT_MAX,
                                            pDefViewCfg->srvOutputWidth,
                                            pDefViewCfg->srvOutputHeight,
                                            SRV_UC_3D_NUM_CAMERAS,
                                            carBoxWidth,
                                            carBoxHeight,
                                            ALGORITHM_LINK_SRV_OUTPUT_3D_LDC,
                                            FALSE); /* Enable CAR overlay */
    /* Set the LDC Input Frame size parameters in Synthesys */
    for (numCh = 0U; numCh < pObj->numCh; numCh ++)
    {
            pUcObj->Alg_SynthesisPrm.ldcFrmWidth[numCh] =
                                        pDefViewCfg->ldcOutFrameWidth[numCh];
            pUcObj->Alg_SynthesisPrm.ldcFrmHeight[numCh] =
                                        pDefViewCfg->ldcOutFrameHeight[numCh];
    }
    pUcObj->Alg_SynthesisPrm.carPosX = pDefViewCfg->carPosX;
    pUcObj->Alg_SynthesisPrm.carPosY = pDefViewCfg->carPosY;
    pUcObj->Alg_SynthesisPrm.earlyCreate = TRUE;
    pUcObj->Alg_SynthesisPrm.useUserBlendTable3DLDC = \
                                        pObj->useUserBlendTable3DLDC;
    pUcObj->Alg_SynthesisPrm.subsampleratio = pDefViewCfg->srvSubSample;
    pUcObj->Alg_SynthesisPrm.numOutputFrames = 3;

    gNumViewPoints = chainsObj.numViewPoints;

    ChainsCommon_SurroundView_SetPAlignParams(&pUcObj->Alg_PhotoAlignPrm,
                                            SRV_UC_3D_LDC_OUTPUT_WIDTH_MAX,
                                            SRV_UC_3D_LDC_OUTPUT_HEIGHT_MAX,
                                            pDefViewCfg->srvOutputWidth,
                                            pDefViewCfg->srvOutputHeight,
                                            SRV_UC_3D_NUM_CAMERAS,
                                            carBoxWidth,
                                            carBoxHeight,
                                            ALGORITHM_LINK_SRV_OUTPUT_3D_LDC);

    pUcObj->Alg_DeWarpPrm.provideViewPointParams = &provideViewParams;
    for (numCh = 0U; numCh < pObj->numCh; numCh ++)
    {
        /*ISP */
        pUcObj->IssM2mIspPrm.channelParams[numCh].useBufSizePrmsFlag = TRUE;
        pUcObj->IssM2mIspPrm.channelParams[numCh].maxBufWidth =
                                            SRV_UC_3D_ISP_OUTPUT_WIDTH_W_PAD;
        pUcObj->IssM2mIspPrm.channelParams[numCh].maxBufHeight =
                                            SRV_UC_3D_ISP_OUTPUT_HEIGHT_W_PAD;

        pUcObj->IssM2mIspPrm.channelParams[numCh].numBuffersPerCh =
            SRV_UC_3D_ISP_NUM_OUTPUT_BUFS;

        /* De Warp */
        pUcObj->Alg_DeWarpPrm.channelParams[numCh].numBuffersPerCh =
            SRV_UC_3D_DEWARP_NUM_OUTPUT_BUFS;
        pUcObj->Alg_DeWarpPrm.channelParams[numCh].overrideInFrmSize =
            TRUE;
        pUcObj->Alg_DeWarpPrm.channelParams[numCh].inputFrameWidth =
                                            SRV_UC_3D_ISP_OUTPUT_WIDTH_W_PAD;
        pUcObj->Alg_DeWarpPrm.channelParams[numCh].inputFrameHeight =
                                            SRV_UC_3D_ISP_OUTPUT_HEIGHT_W_PAD;

        pUcObj->Alg_DeWarpPrm.channelParams[numCh].useMaxOutputFrameSize = TRUE;
        pUcObj->Alg_DeWarpPrm.channelParams[numCh].maxOutputFrameWidth =
                                        pDefViewCfg->ldcOutFrameWidth[numCh];
        pUcObj->Alg_DeWarpPrm.channelParams[numCh].maxOutputFrameHeight =
                                        pDefViewCfg->ldcOutFrameHeight[numCh];

        pUcObj->Alg_DeWarpPrm.channelParams[numCh].useOutputFrameSize = TRUE;

        pUcObj->Alg_DeWarpPrm.channelParams[numCh].outputFrameWidth =
                                        pDefViewCfg->ldcOutFrameWidth[numCh];
        pUcObj->Alg_DeWarpPrm.channelParams[numCh].outputFrameHeight =
                                        pDefViewCfg->ldcOutFrameHeight[numCh];
    }

    /* Enable filling of output buffers for the dewarp algorithm */
    /* The filling can be enabled based on the camera */
    pUcObj->Alg_DeWarpPrm.fillOutBuf[0U] = ALGLINK_DEWARP_FILLTYPE_HORZ_DOWN;
    pUcObj->Alg_DeWarpPrm.fillOutBuf[1U] = ALGLINK_DEWARP_FILLTYPE_VERT_LEFT;
    pUcObj->Alg_DeWarpPrm.fillOutBuf[2U] = ALGLINK_DEWARP_FILLTYPE_HORZ_TOP;
    pUcObj->Alg_DeWarpPrm.fillOutBuf[3U] = ALGLINK_DEWARP_FILLTYPE_VERT_RIGHT;
    pUcObj->Alg_DeWarpPrm.fillValueY = 0x00;
    pUcObj->Alg_DeWarpPrm.fillValueUV = 0x80;

    /*
     *  A strip which is portion of the output buffer is filled.
     *  The strip is horizontal for Front and Back camera.
     *  The strip is vertical for Left and Right camera.
     *  1: Whole buffer,2: half of the buffer,4:quarter of the buffer
     */
    pUcObj->Alg_DeWarpPrm.fillRatio = 8;

    /* Enable OCMC RAM for LDC LUT */
    pUcObj->Alg_DeWarpPrm.useOcmcLdcLut = gUseOcmcLdcLut;

    if (TRUE == pUcObj->Alg_DeWarpPrm.useOcmcLdcLut)
    {
        lineOffset = \
                (SRV_UC_3D_LDC_OUTPUT_WIDTH_MAX/pDefViewCfg->srvSubSample) + 1U;
        lineOffset += 15;
        lineOffset &= ~0xF;
        lineOffset *= 4;

        pUcObj->Alg_DeWarpPrm.maxLdcLutSize = lineOffset * \
                            ((SRV_UC_3D_LDC_OUTPUT_HEIGHT_MAX / \
                                    pDefViewCfg->srvSubSample) + 1U);
    }
    else
    {
        pUcObj->Alg_DeWarpPrm.maxLdcLutSize = 0U;
    }

    /* LDC Read Max Tag Count */
    pUcObj->Alg_DeWarpPrm.ldcRdMaxTagCnt = gLdcRdMaxTagCnt;

    /* Null Source Link used as dummy source for input Q1 of Synthesis */
    NullSrcLink_CreateParams_Init(&pUcObj->NullSourcePrm);
    pUcObj->NullSourcePrm.timerPeriodMilliSecs = 10000U;
    pUcObj->NullSourcePrm.outQueInfo.numCh = 1U;
    pUcObj->NullSourcePrm.channelParams[0].numBuffers = 2U;

    pChInfo = &pUcObj->NullSourcePrm.outQueInfo.chInfo[0];
    pChInfo->width = 32U;
    pChInfo->height = 32U;
    pChInfo->startX = 0;
    pChInfo->startY = 0;
    pChInfo->pitch[0U] = SystemUtils_align(pChInfo->width, 32U);
    pChInfo->pitch[1U] = SystemUtils_align(pChInfo->width, 32U);
    pChInfo->flags = System_Link_Ch_Info_Set_Flag_Data_Format(
                                            pChInfo->flags,
                                            SYSTEM_DF_YUV420SP_UV);
    pChInfo->flags = System_Link_Ch_Info_Set_Flag_Scan_Format(
                                            pChInfo->flags,
                                            SYSTEM_SF_PROGRESSIVE);
    pChInfo->flags = System_Link_Ch_Info_Set_Flag_Buf_Type(
                                            pChInfo->flags,
                                            SYSTEM_BUFFER_TYPE_VIDEO_FRAME);

#ifndef TDA3XX_128MB_DDR
    pUcObj->IssCapturePrm.allocBufferForRawDump = TRUE;
    pUcObj->IssM2mIspPrm.allocBufferForDump = TRUE;
    pUcObj->Alg_DeWarpPrm.allocBufferForDump = TRUE;
#else
    pUcObj->IssCapturePrm.allocBufferForRawDump = FALSE;
    pUcObj->IssM2mIspPrm.allocBufferForDump = FALSE;
    pUcObj->Alg_DeWarpPrm.allocBufferForDump = FALSE;
#endif
}

/*******************************************************************************
 *  Functions that would be called to create, apply config, start and stop the
 *      chain.
 *******************************************************************************
 */
Void chains_issMultCaptIspDeWarp3dSv_grpx_SetAppPrms(
                chains_issMultCaptIspDeWarp3dSv_grpxObj *pUcObj, Void *appObj)
{
    chains_issMultCaptIspDewarpSv_DisplayAppObj *pObj
                        = (chains_issMultCaptIspDewarpSv_DisplayAppObj*)appObj;
    AlgorithmLink_SrvCommonViewPointParams *pDefViewCfg = \
                        &chainsObj.algViewParams[SRV_UC_3D_DEFAULT_VIEW_TO_USE];

    ChainsCommon_GetDisplayWidthHeight(pObj->chainsCfg->displayType,
                                       &pObj->displayWidth,
                                       &pObj->displayHeight);

    /*
     *  The video display and the graphics display will end up getting the
     *  same link Id (SYSTEM_LINK_ID_DISPLAY_0) since they are created
     *  in 2 different use cases.
     *  Therefore the Graphics display link Id is changed to an id different
     *  than video display link Id:
     */
    pUcObj->Display_GrpxLinkID = SYSTEM_LINK_ID_DISPLAY_1;

    pUcObj->GrpxSrcPrm.grpxBufInfo.dataFormat = SYSTEM_DF_BGR16_565;
    pUcObj->GrpxSrcPrm.grpxBufInfo.height = pObj->displayHeight;
    pUcObj->GrpxSrcPrm.grpxBufInfo.width = pObj->displayWidth;

    pUcObj->GrpxSrcPrm.tda3x3DSvSrcResolution = SYSTEM_STD_720P_60;

    if(0 == strcmp(pObj->chainsCfg->sensorName, SENSOR_APTINA_AR0140_TIDA262))
    {
        pUcObj->GrpxSrcPrm.tda3x3DSvSrcResolution = SYSTEM_STD_WXGA_30;
    }

    pUcObj->GrpxSrcPrm.tda3xxSvFsRotLayoutEnable = FALSE;
    pUcObj->GrpxSrcPrm.tda3xx3DSvLayoutEnable = FALSE;
    pUcObj->GrpxSrcPrm.statsDisplayEnable = TRUE;
    pUcObj->GrpxSrcPrm.tda3xx3DSvLayoutEnable = TRUE;
    pUcObj->GrpxSrcPrm.enableJeepOverlay = FALSE;
    pUcObj->GrpxSrcPrm.displaySrv3D.srvOutWidth = pDefViewCfg->srvOutputWidth;
    pUcObj->GrpxSrcPrm.displaySrv3D.srvOutHeight = pDefViewCfg->srvOutputHeight;

    pUcObj->Display_GrpxPrm.rtParams.tarWidth = pObj->displayWidth;
    pUcObj->Display_GrpxPrm.rtParams.tarHeight = pObj->displayHeight;
    pUcObj->Display_GrpxPrm.rtParams.posX = 0;
    pUcObj->Display_GrpxPrm.rtParams.posY = 0;
    pUcObj->Display_GrpxPrm.displayId = DISPLAY_LINK_INST_DSS_GFX1;
}

/**
 *******************************************************************************
 *
 * \brief   Start the capture display Links
 *
 *          Function sends a control command to capture and display link to
 *          to Start all the required links . Links are started in reverce
 *          order as information of next link is required to connect.
 *          System_linkStart is called with LinkId to start the links.
 *
 * \param   pObj  [IN] chains_issMultCaptIspDewarpSv_DisplayAppObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
static Void chains_issMultCaptIspDeWarp3dSv_StartApp(
                            chains_issMultCaptIspDewarpSv_DisplayAppObj *pObj)
{
    Int32 status;

    Chains_memPrintHeapStatus();

    updateIspDeWarpWithDefaultParams(pObj);

    /*
     *  LDC Optimization configuration for the best performance
     */
    ldcOptimizationConfig(
                pObj,
                gLdcTraffic,
                gIspTraffic);

    setMuxes(pObj);
    appStartIssSensorSerDes(&pObj->appObjPrms);
    ChainsCommon_StartDisplayDevice(pObj->chainsCfg->displayType);

    chains_issMultCaptIspDeWarp3dSv_Start(&pObj->ucObj);

    Chains_prfLoadCalcEnable(TRUE, FALSE, FALSE);

    /* Stop the Null Source Link */
    status = System_linkStop(pObj->ucObj.NullSourceLinkID);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
}

/**
 *******************************************************************************
 *
 * \brief   Delete the capture display Links
 *
 *          Function sends a control command to capture and display link to
 *          to delete all the prior created links
 *          System_linkDelete is called with LinkId to delete the links.
 *
 * \param   pObj   [IN]   chains_issMultCaptIspDewarpSv_DisplayAppObj
 *
 *******************************************************************************
*/
static Void chains_issMultCaptIspDeWarp3dSv_StopAndDeleteApp(
                            chains_issMultCaptIspDewarpSv_DisplayAppObj *pObj)
{
    chains_issMultCaptIspDeWarp3dSv_Stop(&pObj->ucObj);
    chains_issMultCaptIspDeWarp3dSv_grpx_Stop(&pObj->ucGrpxObj);

    chains_issMultCaptIspDeWarp3dSv_Delete(&pObj->ucObj);
    chains_issMultCaptIspDeWarp3dSv_grpx_Delete(&pObj->ucGrpxObj);

    ChainsCommon_StopDisplayCtrl();

    appStopISSSensor(&pObj->appObjPrms);
    appDeleteISSSensor(&pObj->appObjPrms);

    ChainsCommon_StopDisplayDevice(pObj->chainsCfg->displayType);

    /* Print the HWI, SWI and all tasks load */
    /* Reset the accumulated timer ticks */
    Chains_prfLoadCalcEnable(FALSE, TRUE, TRUE);
}


/**
 *******************************************************************************
 *
 * \brief   4 Channel surround view usecase entry function
 *
 *          This function configure, creates, link various links to establish
 *          usecase.
 *
 *          Further in a while loop displays run time menu and waits
 *          for user inputs to print the statistics or to end the demo.
 *
 *          Once the user inputs end of demo stop and delete
 *          functions are executed.
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_issMultCaptIspDewarp3dSv_Display(
                        Chains_Ctrl *chainsCfg,
                        AlgorithmLink_SrvOutputModes ucSrvOutMode)
{
    Int32 status;
    char ch;
    UInt32 done = FALSE, chId, validChId = 0;
    AlgLink_DeWarpSaveFrame *pDeWarpFrameCmd;
    static UInt32 disFrCnt = 0;

    chainsObj.bypassVtnf = 0; /* KW error fix */
    chainsObj.bypassLdc  = 0; /* KW error fix */
    gLastCount = 0U;
    gViewId = 0U;
    gDirViewPoint = 0U;
    gSvAutoSwitchViews = TRUE;
    chainsObj.useUserBlendTable3DLDC = TRUE;
    chainsObj.numCh = 4U;

    /*  This is use case level SRV output mode.
        This is NOT passed to the algorithm.
        The algorithm will always creates 'ALGORITHM_LINK_SRV_OUTPUT_3D_LDC'.
    */
    chainsObj.ucSrvOutMode = ucSrvOutMode;

    if ((ISSM2MISP_LINK_OPMODE_1PASS_WDR != chainsCfg->ispOpMode) &&
        (ISSM2MISP_LINK_OPMODE_12BIT_LINEAR != chainsCfg->ispOpMode))
    {
        Vps_printf(" CHAINS: WDR should either be disabled or "
                    "in One Pass mode!!!\n");
        return;
    }

    chainsCfg->displayType = CHAINS_DISPLAY_TYPE_HDMI_1080P;
    chainsObj.chainsCfg = chainsCfg;
    chainsObj.numViewPoints = 1U;
    chainsObj.freeToSwitch = FALSE;

    memset((void*) &chainsObj.algViewParams, 0,
                    (sizeof(AlgLink_DeWarpViewPointParams) *
                            SRV_UC_3D_MAX_NUM_VIEW_POINTS));
    Vps_printf(" CHAINS: Initiating read of LDC Look Up Tables from MMC/SD \n");

    /*
     *  The SV files are present in the TDA3X folder
     */
    status = File_chDir(SRV_SRC_DIR);
    if (SYSTEM_LINK_STATUS_SOK != status)
    {
        Vps_printf(" CHAINS: -------------------------------------------------- \n");
        Vps_printf(" CHAINS: %s Folder not present in MMC/SD \n", SRV_SRC_DIR);
        Vps_printf(" CHAINS: Create %s folder and copy the following files from\n", SRV_SRC_DIR);
        Vps_printf(" CHAINS: '/vision_sdk/tools/surround_vision_tools/Srv_LUTs':\n");
        Vps_printf(" CHAINS:     1. LUT_IDX.BIN  \n");
        Vps_printf(" CHAINS:     2. CARIMAGE_IDX.BIN  \n");
        Vps_printf(" CHAINS:     3. CARIMAGE_SET0.LZ4  \n");
        Vps_printf(" CHAINS:                ...        \n");
        Vps_printf(" CHAINS:        CARIMAGE_SETn.LZ4  \n");
        Vps_printf(" CHAINS:     4. LUT_SET0.LZ4  \n");
        Vps_printf(" CHAINS:                ...        \n");
        Vps_printf(" CHAINS:        LUT_SETn.LZ4  \n");
        Vps_printf(" CHAINS: -------------------------------------------------- \n");
        Task_sleep (100U);

        return;
    }

    /* . Create a sem for media handshake
       . Wait for LDC LUTs read completion
       . Create the chain and proceed normally
       . DeWarp callback occurs at every frame, provide required LUTs
       */
    if (SYSTEM_LINK_STATUS_SOK == status)
    {
        createMediaThread(&chainsObj);

        /* Wait for LDC LUTs */
        BspOsal_semWait(chainsObj.startSrvDemo, BSP_OSAL_WAIT_FOREVER);
    }

    done = FALSE;
    chains_issMultCaptIspDeWarp3dSv_Create(&chainsObj.ucObj, &chainsObj);

    if (TRUE == chainsObj.ucObj.Alg_SynthesisPrm.earlyCreate)
    {
        /*
         *  If late create is enabled then signal the DSP create thread
         *  to do the late creation.
         */
        postDspCreateSem(&chainsObj);
    }

    chains_issMultCaptIspDeWarp3dSv_StartApp(&chainsObj);

    BspOsal_semPost(chainsObj.startSrvDemo);

    /*
     *  Graphics Use case is started after capture is started
     */
    chains_issMultCaptIspDeWarp3dSv_grpx_Create(
                                        &chainsObj.ucGrpxObj,
                                        &chainsObj);

    chains_issMultCaptIspDeWarp3dSv_grpx_Start(&chainsObj.ucGrpxObj);

    ch = 'a';
    do
    {
        Vps_printf(gSrvUc3dRunTimeMenu);

        ch = Chains_readChar();

        switch(ch)
        {
            case '0':
                done = TRUE;
                break;

            case '1':
                do
                {
                    Vps_printf("Enter Channel Id [0:3]:");
                    ch = Chains_readChar();
                    chId = ch - '0';
                } while (chId > 3);
                saveRawIntoMmcsd(&chainsObj, chId);
                break;

            case '2':
                validChId = 0U;
                do
                {
                    Vps_printf("Enter Channel Id [0:%d]:",
                        chainsObj.numCh - 1);
                    ch = Chains_readChar();

                    chId = ch - '0';

                    if (chId < chainsObj.numCh)
                    {
                        validChId = 1U;
                    }
                } while (!validChId);

                pDeWarpFrameCmd = &chainsObj.deWarpSaveFrame;

                pDeWarpFrameCmd->chId = chId;
                pDeWarpFrameCmd->baseClassControl.controlCmd
                                        = ALG_LINK_DEWARP_CMD_SAVE_FRAME;
                pDeWarpFrameCmd->baseClassControl.size
                                        = sizeof(AlgLink_DeWarpSaveFrame);

                status = System_linkControl(
                                        chainsObj.ucObj.Alg_DeWarpLinkID,
                                        ALGORITHM_LINK_CMD_CONFIG,
                                        pDeWarpFrameCmd,
                                        sizeof(AlgLink_DeWarpSaveFrame),
                                        TRUE);
                UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

                do
                {
                    /* Assuming 30 FPS */
                    Task_sleep(35U);
                    pDeWarpFrameCmd = &chainsObj.deWarpSaveFrame;

                    pDeWarpFrameCmd->chId = chId;
                    pDeWarpFrameCmd->baseClassControl.controlCmd
                                = ALG_LINK_DEWARP_CMD_GET_SAVE_FRAME_STATUS;
                    pDeWarpFrameCmd->baseClassControl.size
                                        = sizeof(AlgLink_DeWarpSaveFrame);

                    status = System_linkControl(
                                        chainsObj.ucObj.Alg_DeWarpLinkID,
                                        ALGORITHM_LINK_CMD_CONFIG,
                                        pDeWarpFrameCmd,
                                        sizeof(AlgLink_DeWarpSaveFrame),
                                        TRUE);
                    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);
                } while (FALSE == pDeWarpFrameCmd->isSaveFrameComplete);
                break;

            case '3':
                saveIspOutputIntoMmcsd(&chainsObj);
                break;

            case 's':
            {
                gSvAutoSwitchViews = (TRUE == gSvAutoSwitchViews)?FALSE:TRUE;
                Vps_printf ("SV Auto Switch is %d \n",gSvAutoSwitchViews);
                break;
            }

            case 'n':
            {
                if (FALSE == gSvAutoSwitchViews)
                {
                    gViewId ++;

                    if(gViewId == gNumViewPoints)
                    {
                        gViewId = 0U;
                    }

                    Vps_printf ("Switched to view point %d\n",gViewId);
                }
                break;
            }

            case 'r':
            {
                if (FALSE == gSvAutoSwitchViews)
                {
                    if(gViewId == 0U)
                    {
                        gViewId = gNumViewPoints;
                    }

                    gViewId --;

                    Vps_printf ("Switched to view point %d\n",gViewId);
                }
                break;
            }

            case 'd':
            case 'D':
            {
                #define NUM_DISPLAY_FRAMES       (1U)
                char fileName[128];

                Void chains_saveDisFrame(
                                    char *fileName,
                                    UInt32 numSaveFrames,
                                    UInt32 displayWidth,
                                    UInt32 displayHeight);

                sprintf(fileName,"DF_%d.YUV",disFrCnt++);
                chains_saveDisFrame(
                        fileName,
                        NUM_DISPLAY_FRAMES,
                        chainsObj.displayWidth,
                        chainsObj.displayHeight);

                break;
            }

            case 't':
            case 'T':
                appGetUB96xRegVal(&chainsObj.appObjPrms);
                break;

            case 'p':
            case 'P':
                ChainsCommon_PrintStatistics();
                chains_issMultCaptIspDeWarp3dSv_printStatistics(
                                                        &chainsObj.ucObj);
                chains_issMultCaptIspDeWarp3dSv_grpx_printStatistics(
                                                        &chainsObj.ucGrpxObj);
                break;

            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n",
                            ch);
                break;
        }
    } while (FALSE == done);

    chains_issMultCaptIspDeWarp3dSv_StopAndDeleteApp(&chainsObj);

    /*
     *  Free the memory allocated for the LDC LUTs and Car image
     */
    chains_issMultCaptIspDeWarp3dSv_FreeBufs();

    deleteMediaThread(&chainsObj);

    /*
     *  Change to the root dir
     */
    status = File_chDir("/\0");
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);
}
