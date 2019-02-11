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
  ******************************************************************************
 * \file grpxSrcLink_tsk.c
 *
 * \brief  This file has the implementation of Grpx Src Link API
 **
 *           This file implements the state machine logic for this link.
 *           A message command will cause the state machine
 *           to take some action and then move to a different state.
 *
 * \version 0.0 (Oct 2013) : [NN] First version
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <system_cfg.h>
#include "grpxSrcLink_priv.h"
#include <src/rtos/modules/data_vis/data_vis.h>

/**
 *******************************************************************************
 * \brief Link Stack
 *******************************************************************************
 */
#pragma DATA_ALIGN(gGrpxSrcLink_tskStack, 32)
#pragma DATA_SECTION(gGrpxSrcLink_tskStack, ".bss:taskStackSection")
UInt8 gGrpxSrcLink_tskStack[GRPX_SRC_LINK_OBJ_MAX][GRPX_SRC_LINK_TSK_STACK_SIZE];

/**
 *******************************************************************************
 * \brief Link object, stores all link related information
 *******************************************************************************
 */
GrpxSrcLink_Obj gGrpxSrcLink_obj[GRPX_SRC_LINK_OBJ_MAX];

Int32 GrpxSrcLink_initAndDrawStaticBmp(GrpxSrcLink_Obj * pObj,
                                        System_LinkChInfo *pChInfo)
{
    Int32 status, frameId;
    Draw2D_BufInfo bufInfo;
    GrpxSrcLink_CreateParams *createPrms = &pObj->createArgs;
    GrpxSrcLink_LogoParameters   *logoPrms;
    Draw2D_BmpPrm bmpPrm;


    System_VideoFrameBuffer *pSysVidBuf;

    pObj->draw2DHndl = NULL;

    status = Draw2D_create(&pObj->draw2DHndl);

    if (status != SYSTEM_LINK_STATUS_SOK)
    {
        return status;
    }

    bufInfo.bufWidth          = pObj->info.queInfo[0].chInfo[0].width;
    bufInfo.bufHeight         = pObj->info.queInfo[0].chInfo[0].height;
    bufInfo.bufPitch[0]       = pObj->info.queInfo[0].chInfo[0].pitch[0];
    bufInfo.dataFormat        = pObj->createArgs.grpxBufInfo.dataFormat;
    bufInfo.transperentColor  = DRAW2D_TRANSPARENT_COLOR;
    bufInfo.transperentColorFormat = DRAW2D_TRANSPARENT_COLOR_FORMAT;

    #ifdef DATA_VIS_INCLUDE
    if(pObj->createArgs.dataVisDataBwDisplayEnable)
    {
        DataVis_DataBwPrm dataVisPrm;

        DataVis_DataBwPrm_Init(&dataVisPrm);
        dataVisPrm.pDraw2DHandle = pObj->draw2DHndl;
        dataVisPrm.winPosX = bufInfo.bufWidth - dataVisPrm.winWidth - 20;
        dataVisPrm.winPosY = bufInfo.bufHeight - dataVisPrm.winHeight - 20;

        DataVis_setDataBwPrm(&dataVisPrm, TRUE, TRUE);
    }
    #endif

    for (frameId = 0; frameId < pObj->outObj.numFrames; frameId++)
    {
        pSysVidBuf = pObj->outObj.buffers[frameId].payload;

        bufInfo.bufAddr[0] = (UInt32) pSysVidBuf->bufAddr[0];
        status = Draw2D_setBufInfo(pObj->draw2DHndl, &bufInfo);

        if (status != SYSTEM_LINK_STATUS_SOK)
        {
            return status;
        }

        #ifndef ROBUST_RVC_INCLUDE
        Draw2D_clearBuf(pObj->draw2DHndl);
        #endif

        #ifdef DATA_VIS_INCLUDE
        if(pObj->createArgs.dataVisDataBwDisplayEnable)
        {
            DataVis_drawDataBw();
        }
        #endif

        if (createPrms->logoDisplayEnable)
        {
            logoPrms = &createPrms->logoParams;
            bmpPrm.bmpIdx = DRAW2D_BMP_IDX_TI_LOGO;
            Draw2D_drawBmp(pObj->draw2DHndl,
                           logoPrms->startX,
                           logoPrms->startY,
                           &bmpPrm
                           );
        }

        #ifndef RADAR_ONLY
        if (createPrms->surroundViewEdgeDetectLayoutEnable ||
            createPrms->surroundViewDOFLayoutEnable ||
            (createPrms->surroundViewPdTsrLayoutEnable &&
             createPrms->surroundViewLdLayoutEnable)
           )
        {
            GrpxSrcLink_drawSurroundViewEdgeDetectLayout(pObj);
        }

        if (createPrms->opticalFlowLayoutEnable)
        {
            GrpxSrcLink_drawOpticalFlowLayout(pObj);
        }

        if (createPrms->pdTsrLdLayoutEnable)
        {
            GrpxSrcLink_drawPdTsrLdLayout(pObj);
        }

        if (createPrms->pdTsrLdSofLayoutEnable)
        {
            GrpxSrcLink_drawPdTsrLdSofLayout(pObj);
        }

        if (createPrms->pdTsrLdSofStereoLayoutEnable)
        {
            GrpxSrcLink_drawPdTsrLdSofStereoLayout(pObj);
        }

        if (createPrms->stereoDisparityLayoutEnable)
        {
            GrpxSrcLink_drawStereoDisparityLayout(pObj);
        }

        #ifdef UC_lvds_vip_sv_tda3xx
        if (createPrms->tda3xxSvFsRotLayoutEnable)
        {
            GrpxSrcLink_drawSurroundViewSOFLayout(pObj, pChInfo);
        }
        #endif

        if (createPrms->tda3xx3DSvLayoutEnable)
        {
            GrpxSrcLink_drawTDA3x3DSVLayout(pObj);
        }

        if (createPrms->tda3xxRearView3DSvLayoutEnable)
        {
            GrpxSrcLink_drawTDA3xRearView3DSVLayout(pObj);
        }

        #ifdef UC_iss_mult_capture_isp_2d_3d_sv_tda3x
        if (createPrms->tda3xx2D3DSvLayoutEnable)
        {
            GrpxSrcLink_drawTDA3x2D3DSVLayout(pObj);
        }
        #endif

        if (createPrms->surroundViewStandaloneLayoutEnable)
        {
            GrpxSrcLink_drawSurroundViewStandaloneLayout(pObj,
                                                createPrms->disablePreview);
        }

        if (createPrms->surroundViewStandaloneLayout2Enable)
        {
            GrpxSrcLink_drawSurroundViewStandaloneLayout2(pObj,
                                                createPrms->disablePreview);
        }

        if (createPrms->fcAnalytics2LayoutEnable)
        {
            GrpxSrcLink_drawFcAnalytics2Layout(pObj);
        }
        if (createPrms->sfmLayoutEnable)
        {
            GrpxSrcLink_drawSfMLayout(pObj);
        }

        if (createPrms->srvCalibLayout)
        {
            GrpxSrcLink_drawSrvCalibLayout(
                                            pObj,
                                            pChInfo,
                                            createPrms->captureWidth,
                                            createPrms->captureHeight);
        }

        if (createPrms->enableRearViewPanoramaLayout)
        {
            GrpxSrcLink_drawRearViewPanoramaLayout(pObj);
        }

        if (createPrms->stereoCalibDisplayPrms.stereoCalibLayout)
        {
            GrpxSrcLink_drawStereoCalibLayout(
                                            pObj,
                                            createPrms->stereoCalibDisplayPrms);
        }
        #ifdef UC_semSeg
        if(createPrms->semSegOverlay)
        {
            GrpxSrcLink_drawSemSegLayout(
                                pObj,
                                createPrms->captureWidth,
                                createPrms->captureHeight);
        }
        #endif
        #ifdef UC_tidl_OD
        if(createPrms->tidlOdOverlay)
        {
            GrpxSrcLink_drawtidlOdLayout(
                                pObj,
                                createPrms->captureWidth,
                                createPrms->captureHeight);
        }
        #endif
        #endif
    }

    return SYSTEM_LINK_STATUS_SOK;
}


/**
 *******************************************************************************
 * \brief Grpx Src Link is used in two scenarios
 *
 *     1. To Query other links, get statistics, use font/drawing API and display
 *        on using the graphics pipe
 *
 * \param  pObj     [IN]  Grpx Src  link instance handle
 *
 * \return status   SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 GrpxSrcLink_drvCreate(GrpxSrcLink_Obj * pObj, GrpxSrcLink_CreateParams * pPrm)
{
    Int32 status;
    System_Buffer *pSysBuf;
    System_VideoFrameBuffer *pSysVidBuf;
    System_LinkChInfo chInfo;
    GrpxSrcLink_OutObj *pOutObj;
    UInt32 flags, id, planes;
    Utils_QueHandle *pQueHandle;

#ifdef SYSTEM_DEBUG
    Vps_printf(" GRPXSRC: Create in progress !!!\n");
#endif

    UTILS_MEMLOG_USED_START();

    memcpy(&pObj->createArgs, pPrm, sizeof(GrpxSrcLink_CreateParams));

    /*
     * Populate channel info, These values have to come from use case
     */

    chInfo.height = pPrm->grpxBufInfo.height;
    chInfo.width  = pPrm->grpxBufInfo.width;
    chInfo.startX = 0;
    chInfo.startY = 0;
    chInfo.flags  = 0;

    chInfo.flags = System_Link_Ch_Info_Set_Flag_Scan_Format(chInfo.flags,
                                              SYSTEM_SF_PROGRESSIVE);
    chInfo.flags = System_Link_Ch_Info_Set_Flag_Mem_Type(chInfo.flags,
                                           SYSTEM_MT_NONTILEDMEM);

    UTILS_assert(pPrm->grpxBufInfo.dataFormat == SYSTEM_DF_BGR16_565
                             ||
                pPrm->grpxBufInfo.dataFormat == SYSTEM_DF_BGRA16_4444
            );

    chInfo.flags = System_Link_Ch_Info_Set_Flag_Data_Format(chInfo.flags,
                                              pPrm->grpxBufInfo.dataFormat);
    chInfo.flags = System_Link_Ch_Info_Set_Flag_Buf_Type(chInfo.flags,
                                           SYSTEM_BUFFER_TYPE_VIDEO_FRAME);

    pOutObj = &pObj->outObj;

    pOutObj->format.width  = chInfo.width;
    pOutObj->format.height = chInfo.height;
    pOutObj->format.chNum = 0;
    pOutObj->format.pitch[2] = 0;
    pOutObj->format.fieldMerged[0] = FALSE;
    pOutObj->format.fieldMerged[1] = FALSE;
    pOutObj->format.fieldMerged[2] = FALSE;
    pOutObj->format.scanFormat = SYSTEM_SF_PROGRESSIVE;
    pOutObj->format.bpp = FVID2_BPP_BITS16;
    pOutObj->format.reserved = NULL;
    pOutObj->format.dataFormat = pPrm->grpxBufInfo.dataFormat;
    pOutObj->format.pitch[0] = VpsUtils_align(pOutObj->format.width,
                                               VPS_BUFFER_ALIGNMENT);
    pOutObj->format.pitch[0] *= 2;
    pOutObj->format.pitch[1] = pOutObj->format.pitch[0];
    pOutObj->format.pitch[2] = pOutObj->format.pitch[0];

    chInfo.pitch[0] = pOutObj->format.pitch[0];
    chInfo.pitch[1] = pOutObj->format.pitch[1];
    chInfo.pitch[2] = pOutObj->format.pitch[2];

    pOutObj = &pObj->outObj;

    status = Utils_bufCreate(&pOutObj->bufOutQue, TRUE, FALSE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    pOutObj->numFrames = GRPX_SRC_LINK_OUT_FRAMES;
    status = Utils_memFrameAlloc(&pOutObj->format,
                                  pOutObj->frames,
                                  pOutObj->numFrames,
                                  0);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    pQueHandle = &pOutObj->bufOutQue.emptyQue;

    for (id = 0; id < pOutObj->numFrames; id++)
    {
         pSysBuf    = &pOutObj->buffers[id];
         pSysVidBuf = &pOutObj->videoFrames[id];

         pSysBuf->payload      = pSysVidBuf;
         pSysBuf->payloadSize  = sizeof(System_VideoFrameBuffer);
         pSysBuf->chNum        = 0;
         pSysBuf->bufType      = SYSTEM_BUFFER_TYPE_VIDEO_FRAME;
         pSysBuf->srcTimestamp = Utils_getCurGlobalTimeInUsec();
         pSysBuf->frameId      = 0;
         pSysBuf->linkLocalTimestamp = pSysBuf->srcTimestamp;
         flags = pSysVidBuf->chInfo.flags;
         flags = System_Link_Ch_Info_Set_Flag_Is_Rt_Prm_Update(flags,0);
         pOutObj->frames[id].perFrameCfg    = NULL;
         pOutObj->frames[id].subFrameInfo   = NULL;
         pOutObj->frames[id].reserved       = NULL;
         pOutObj->frames[id].appData        = pSysBuf;
         pOutObj->frames[id].chNum          = pSysBuf->chNum;
         for (planes = 0; planes < SYSTEM_MAX_PLANES; planes++)
         {
            pSysVidBuf->bufAddr[planes] = pOutObj->frames[id].addr[0][planes];
         }

         status = Utils_quePut(pQueHandle, pSysBuf, BSP_OSAL_NO_WAIT);
         UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    pObj->info.numQue = 1;
    pObj->info.queInfo[0].numCh = 1;
    pObj->info.queInfo[0].chInfo[0] = chInfo;

    GrpxSrcLink_initAndDrawStaticBmp(pObj, &chInfo);

    pObj->isFirstProcessCall = TRUE;
    pObj->isLinkStarted = FALSE;
    pObj->isNewDataCmdSendOut = FALSE;
    pObj->statsDisplayObj.refreshInterval =
                                      GRPX_SRC_LINK_LOAD_REFRESH_INTERVAL_MSEC;
    pObj->statsDisplayObj.profilerState =
                GRAPHICS_SRC_LINK_PROFILER_NOT_RUNNING;

    #ifdef ULTRASONIC_INCLUDE
    if(pObj->createArgs.ultrasonicParams.enable)
    {
        status = GrpxSrcLink_drawMetaDataResultsCreate(pObj);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }
    #endif
    #ifndef RADAR_ONLY
    if (pObj->createArgs.tda3xxRearView3DSvLayoutEnable)
    {
        status = GrpxSrcLink_drawOverlaysCreate(pObj);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }
    #endif

    UTILS_MEMLOG_USED_END(pObj->memUsed);
    UTILS_MEMLOG_PRINT("GRPXSRC:",
                       pObj->memUsed,
                       UTILS_ARRAYSIZE(pObj->memUsed));
#ifdef SYSTEM_DEBUG
    Vps_printf(" GRPXSRC: Create Done !!!\n");
#endif

    return status;
}

Int32 GrpxSrcLink_startResetProfiling(UInt32 cmd)
{
    UInt32 procId, linkId;
    UInt32 status;

    for (procId = 0; procId < SYSTEM_PROC_MAX; procId++)
    {
        if(System_isProcEnabled(procId)==FALSE)
            continue;

        if(System_getCoreState(procId)!=SYSTEM_CORE_STATE_ACTIVE)
            continue;

        linkId = SYSTEM_MAKE_LINK_ID(procId, SYSTEM_LINK_ID_PROCK_LINK_ID);

        if (cmd == GRAPHICS_SRC_LINK_START_PROFILER)
        {
            status = System_linkControl(
                                        linkId,
                                        SYSTEM_COMMON_CMD_CPU_LOAD_CALC_START,
                                        NULL,
                                        0,
                                        TRUE
                                       );
            if (status != SYSTEM_LINK_STATUS_SOK)
                return SYSTEM_LINK_STATUS_EFAIL;
        }
        else if(cmd == GRAPHICS_SRC_LINK_RESET_PROFILER)
        {
            status = System_linkControl(
                                        linkId,
                                        SYSTEM_COMMON_CMD_CPU_LOAD_CALC_RESET,
                                        NULL,
                                        0,
                                        TRUE
                                       );
            if (status != SYSTEM_LINK_STATUS_SOK)
                return SYSTEM_LINK_STATUS_EFAIL;
        }

    }
    return SYSTEM_LINK_STATUS_SOK;
}

Int32 GrpxSrcLink_getSystemLoad(GrpxSrcLink_Obj *pObj)
{
    UInt32 procId;
    Utils_SystemLoadStats loadStats[SYSTEM_PROC_MAX];

    System_linkControl(
        SYSTEM_LINK_ID_IPU1_0,
        SYSTEM_LINK_CMD_GET_CORE_PRF_LOAD,
        loadStats,
        sizeof(Utils_SystemLoadStats)*SYSTEM_PROC_MAX,
        TRUE);

    for (procId = 0; procId < SYSTEM_PROC_MAX; procId++)
    {
        if(System_isProcEnabled(procId)==FALSE)
            continue;

#if defined(IPU1_SMP_BIOS_INCLUDE)
        /* In SMP IPU1-0 will set CPU load for other core */
        if (procId == SYSTEM_PROC_IPU1_0)
        {
            memcpy(&pObj->statsDisplayObj.systemLoadStats[SYSTEM_PROC_IPU1_1],
                   &loadStats[SYSTEM_PROC_IPU1_1],
                   sizeof(Utils_SystemLoadStats));
        }

#endif
        memcpy(&pObj->statsDisplayObj.systemLoadStats[procId],
               &loadStats[procId],
               sizeof(Utils_SystemLoadStats));
    }
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 * \brief Grpx Src Link process frames
 *
 * \param  pObj     [IN]  Grpx Src link instance handle
 *
 * \return status   SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Void GrpxSrcLink_displayStats(GrpxSrcLink_Obj * pObj)
{
    GrpxSrcLink_StatsPrintParams *statsPrintParams;

    statsPrintParams = &pObj->createArgs.statsPrintParams;

    GrpxSrcLink_drawCpuLoad(pObj,
            statsPrintParams->startX,
            statsPrintParams->startY,
            30,
            60,
            4,
            4,
            1
            );
}

/**
 *******************************************************************************
 *
 * \brief This function handles logic for running/stopping the profiler
 * \param  pObj [IN] GrpxSrcLink_Obj
 *
 *******************************************************************************
 */
Int32 GrpxSrcLink_runDisplayStats(GrpxSrcLink_Obj *pObj)
{
    UInt32 cmd;
    Int32  status = SYSTEM_LINK_STATUS_SOK;
    UInt32 elapsedTime;

    #ifdef DATA_VIS_INCLUDE
    if(pObj->createArgs.dataVisDataBwDisplayEnable)
    {
        DataVis_drawDataBw();
    }
    #endif

    if (pObj->statsDisplayObj.profilerState ==
                                         GRAPHICS_SRC_LINK_PROFILER_NOT_RUNNING)
    {
        /* reset load calc stats */
        cmd = GRAPHICS_SRC_LINK_RESET_PROFILER;
        status = GrpxSrcLink_startResetProfiling(cmd);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

        /* start load calc stats */
        cmd = GRAPHICS_SRC_LINK_START_PROFILER;
        status = GrpxSrcLink_startResetProfiling(cmd);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        pObj->statsDisplayObj.startTime = Utils_getCurTimeInMsec();
        pObj->statsDisplayObj.profilerState =
                                     GRAPHICS_SRC_LINK_PROFILER_RUNNING;
    }
    else if(pObj->statsDisplayObj.profilerState ==
                                         GRAPHICS_SRC_LINK_PROFILER_RUNNING)
    {
        elapsedTime = Utils_getCurTimeInMsec() -
                                         pObj->statsDisplayObj.startTime;

        if (elapsedTime >= pObj->statsDisplayObj.refreshInterval)
        {
            status = GrpxSrcLink_getSystemLoad(pObj);
            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

        /*reset stats collector every GRPX_SRC_LINK_LOAD_REFRESH_INTERVAL_MSEC frames*/
            pObj->statsDisplayObj.profilerState =
                                     GRAPHICS_SRC_LINK_PROFILER_NOT_RUNNING;

            #ifndef RADAR_ONLY
            if (pObj->createArgs.surroundViewEdgeDetectLayoutEnable ||
                pObj->createArgs.surroundViewDOFLayoutEnable ||
                (pObj->createArgs.surroundViewPdTsrLayoutEnable &&
                 pObj->createArgs.surroundViewLdLayoutEnable)
                )
            {
                GrpxSrcLink_displaySurroundViewEdgeDetectStats(pObj);
            }
            else if (pObj->createArgs.opticalFlowLayoutEnable)
            {
                GrpxSrcLink_displayOpticalFlowDetectStats(pObj);
            }
            else if (pObj->createArgs.pdTsrLdLayoutEnable)
            {
                GrpxSrcLink_displayPdTsrLdStats(pObj);
            }
            else if (pObj->createArgs.pdTsrLdSofLayoutEnable)
            {
                GrpxSrcLink_displayPdTsrLdSofStats(pObj);
            }
            else if (pObj->createArgs.pdTsrLdSofStereoLayoutEnable)
            {
                GrpxSrcLink_displayPdTsrLdSofStereoStats(pObj);
            }
            else if (pObj->createArgs.stereoDisparityLayoutEnable)
            {
                GrpxSrcLink_displayStereoDisparityStats(pObj);
            }
            else if (pObj->createArgs.tda3xxSvFsRotLayoutEnable)
            {
                #ifdef UC_lvds_vip_sv_tda3xx
                GrpxSrcLink_displaySurroundViewSOFStats(pObj);
                #endif
            }
            else if (pObj->createArgs.tda3xx3DSvLayoutEnable)
            {
                GrpxSrcLink_displayTDA3x3DSVStats(pObj);
            }
            else if (pObj->createArgs.tda3xxRearView3DSvLayoutEnable)
            {
                GrpxSrcLink_displayTDA3xRearView3DSVStats(pObj);
            }
            else if (pObj->createArgs.tda3xx2D3DSvLayoutEnable)
            {
                #ifdef UC_iss_mult_capture_isp_2d_3d_sv_tda3x
                GrpxSrcLink_displayTDA3x2D3DSVStats(pObj);
                #endif
            }
            else if (pObj->createArgs.surroundViewStandaloneLayoutEnable)
            {
                GrpxSrcLink_displaySurroundViewStandaloneStats(pObj);
            }
            else if(pObj->createArgs.surroundViewStandaloneLayout2Enable)
            {
                GrpxSrcLink_displaySurroundViewStandaloneStats(pObj);
            }
            else if (pObj->createArgs.sfmLayoutEnable)
            {
                GrpxSrcLink_displaySfMStats(pObj);
            }
            else if (pObj->createArgs.srvCalibLayout)
            {
                /*
                 *  Nothing to do here
                 */
            }
            else if (pObj->createArgs.enableRearViewPanoramaLayout)
            {
                //GrpxSrcLink_displayRearViewPanoramaStats(pObj);
            }
            else
            #endif
            {
                GrpxSrcLink_displayStats(pObj);
            }

            pObj->statsDisplayObj.startTime = Utils_getCurTimeInMsec();

            if(pObj->isLinkStarted && !pObj->isNewDataCmdSendOut)
            {
                System_sendLinkCmd(pObj->createArgs.outQueParams.nextLink, SYSTEM_CMD_NEW_DATA, NULL);
                pObj->isNewDataCmdSendOut = TRUE;
            }
        }
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief This function handles logic for printing a stirng on display
 * \param  pObj [IN] GrpxSrcLink_Obj
 *
 *******************************************************************************
 */
static Int32 GrpxSrcLink_runStringPrint(GrpxSrcLink_Obj *pObj)
{
    Draw2D_FontPrm fontPrm;

    switch (pObj->stringPrintInfo.stringPrintState)
    {
        case GRAPHICS_SRC_LINK_STRPRINT_PRINTSTR:
            fontPrm.fontIdx = pObj->stringPrintInfo.stringInfo.fontType;
            Draw2D_drawString (pObj->draw2DHndl,
                  pObj->stringPrintInfo.stringInfo.startX,
                  pObj->stringPrintInfo.stringInfo.startY,
                  pObj->stringPrintInfo.stringInfo.string,
                  &fontPrm);
            pObj->stringPrintInfo.stringPrintState =
                                             GRAPHICS_SRC_LINK_STRPRINT_ACTIVE;
            break;
        case GRAPHICS_SRC_LINK_STRPRINT_CLEARSTR:
            fontPrm.fontIdx = pObj->stringPrintInfo.stringInfo.fontType;
            Draw2D_clearString (pObj->draw2DHndl,
                  pObj->stringPrintInfo.stringInfo.startX,
                  pObj->stringPrintInfo.stringInfo.startY,
                  strlen(pObj->stringPrintInfo.stringInfo.string),
                  &fontPrm);
            pObj->stringPrintInfo.stringPrintState =
                                           GRAPHICS_SRC_LINK_STRPRINT_INACTIVE;
            break;
        case GRAPHICS_SRC_LINK_STRPRINT_ACTIVE:
            pObj->stringPrintInfo.remainingDuration -=
                                           GRPX_SRC_LINK_PROCESS_INTERVAL_MSEC;
            if (pObj->stringPrintInfo.remainingDuration <= 0)
            {
                pObj->stringPrintInfo.stringPrintState =
                                           GRAPHICS_SRC_LINK_STRPRINT_CLEARSTR;
            }
            break;
        default:
            //Do nothing
            break;
    }
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 * \brief Grpx Src Link process frames
 *
 * \param  pObj     [IN]  Grpx Src link instance handle
 *
 * \return status   SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 GrpxSrcLink_drvProcessData(GrpxSrcLink_Obj * pObj)
{
    System_BufferList bufList;
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    if (pObj->isFirstProcessCall)
    {
        UInt32 i;
        System_Buffer *pSysBuf;

        Utils_bufGetEmpty(&pObj->outObj.bufOutQue, &bufList, BSP_OSAL_NO_WAIT);

        for(i=0; i<bufList.numBuf; i++)
        {
            pSysBuf = bufList.buffers[i];
            pSysBuf->srcTimestamp = Utils_getCurGlobalTimeInUsec();
            pSysBuf->frameId = 0;
            pSysBuf->linkLocalTimestamp = pSysBuf->srcTimestamp;
        }

        Utils_bufPutFull(&pObj->outObj.bufOutQue, &bufList);
        pObj->isFirstProcessCall = FALSE;
    }
    if(pObj->isLinkStarted && !pObj->isNewDataCmdSendOut)
    {
        System_sendLinkCmd(pObj->createArgs.outQueParams.nextLink, SYSTEM_CMD_NEW_DATA, NULL);
        pObj->isNewDataCmdSendOut = TRUE;
    }

    if (pObj->createArgs.statsDisplayEnable)
    {
        status = GrpxSrcLink_runDisplayStats(pObj);
    }
    #ifdef ULTRASONIC_INCLUDE
    if(pObj->createArgs.ultrasonicParams.enable)
    {
        status = GrpxSrcLink_drawMetaDataResultsRun(pObj);
    }
    #endif
    if (pObj->stringPrintInfo.stringPrintState !=
        GRAPHICS_SRC_LINK_STRPRINT_INACTIVE)
    {
        status = GrpxSrcLink_runStringPrint(pObj);
    }
    return status;
}

static Int32 GrpxSrcLink_drvPrintHandler(GrpxSrcLink_Obj * pObj,
                                         GrpxSrcLink_StringRunTimePrintParams *  pMsg)
{
    if (pMsg->duration_ms > GRPX_SRC_LINK_PROCESS_INTERVAL_MSEC)
    {
        if (pObj->stringPrintInfo.stringPrintState ==
            GRAPHICS_SRC_LINK_STRPRINT_ACTIVE)
        {
           Draw2D_FontPrm fontPrm;

           /* If any string is being actively displayed clear it now */
           fontPrm.fontIdx = pObj->stringPrintInfo.stringInfo.fontType;
           Draw2D_clearString (pObj->draw2DHndl,
                  pObj->stringPrintInfo.stringInfo.startX,
                  pObj->stringPrintInfo.stringInfo.startY,
                  strlen(pObj->stringPrintInfo.stringInfo.string),
                  &fontPrm);
        }
        pObj->stringPrintInfo.remainingDuration = pMsg->duration_ms;
        pObj->stringPrintInfo.stringInfo = pMsg->stringInfo;
        pObj->stringPrintInfo.stringPrintState = GRAPHICS_SRC_LINK_STRPRINT_PRINTSTR;
    }
    return SYSTEM_LINK_STATUS_SOK;
}

Int32 GrpxSrcLink_drvDelete(GrpxSrcLink_Obj *pObj)
{
    Int32 status;
    GrpxSrcLink_OutObj *pOutObj = &pObj->outObj;

#ifdef SYSTEM_DEBUG
    Vps_printf(" GRPXSRC: Delete in progress !!!\n");
#endif

    status = Draw2D_delete(pObj->draw2DHndl);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = Utils_bufDelete(&pObj->outObj.bufOutQue);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    #ifdef ULTRASONIC_INCLUDE
    if(pObj->createArgs.ultrasonicParams.enable)
    {
        status = GrpxSrcLink_drawMetaDataResultsDelete(pObj);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }
    #endif
    #ifndef RADAR_ONLY
    if (pObj->createArgs.tda3xxRearView3DSvLayoutEnable)
    {
        status = GrpxSrcLink_drawOverlaysDelete(pObj);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }
    #endif

    Utils_memFrameFree(&pOutObj->format,
                       pOutObj->frames,
                       pOutObj->numFrames,
                       0
                       );

#ifdef SYSTEM_DEBUG
    Vps_printf(" GRPXSRC: Delete Done !!!\n");
#endif

    return status;
}

/**
 *******************************************************************************
 *
 * \brief This function implements the following.
 *    Accepts commands for
 *     - Creating Grpx Src link
 *     - Generating data/handling incoming data request
 *     - Deleting Grpx Src link
 * \param  pTsk [IN] Task Handle
 * \param  pMsg [IN] Message Handle
 *
 *******************************************************************************
 */
Void GrpxSrcLink_tskMain(struct Utils_TskHndl_t * pTsk, Utils_MsgHndl * pMsg)
{
    UInt32 cmd = Utils_msgGetCmd(pMsg);
    Bool done, ackMsg;
    Int32 status;

    GrpxSrcLink_Obj *pObj = (GrpxSrcLink_Obj *) pTsk->appData;

    /*
     * At this stage only create command is the expected command.
     * If other message gets received Ack with error status
     */

     if (cmd != SYSTEM_CMD_CREATE)
     {
        Utils_tskAckOrFreeMsg(pMsg, SYSTEM_LINK_STATUS_EUNSUPPORTED_CMD);
        return;
     }

    status = GrpxSrcLink_drvCreate(pObj, Utils_msgGetPrm(pMsg));

    Utils_tskAckOrFreeMsg(pMsg, status);

    if (status != SYSTEM_LINK_STATUS_SOK)
        return;

    done = FALSE;

    while (!done)
    {
        status = Utils_tskRecvMsg(pTsk, &pMsg, BSP_OSAL_NO_WAIT);

        if (status != SYSTEM_LINK_STATUS_EFAIL)
        {
            cmd = Utils_msgGetCmd(pMsg);

            switch (cmd)
            {
                 case SYSTEM_CMD_START:
                     status = SYSTEM_LINK_STATUS_SOK;
                     pObj->isLinkStarted = TRUE;
                     Utils_tskAckOrFreeMsg(pMsg, status);
                     break;

                 case SYSTEM_CMD_DELETE:
                     done = TRUE;
                     ackMsg = TRUE;
                     break;

                 case GRPX_SRC_LINK_CMD_PRINT_STRING_WO_CLEAR:
                     pObj->stringPrintInfo.stringPrintState = GRAPHICS_SRC_LINK_STRPRINT_INACTIVE;
                     status = GrpxSrcLink_drvPrintHandler(pObj,Utils_msgGetPrm(pMsg));
                     Utils_tskAckOrFreeMsg(pMsg, status);
                     break;
                 case GRPX_SRC_LINK_CMD_PRINT_STRING:
                     status = GrpxSrcLink_drvPrintHandler(pObj,Utils_msgGetPrm(pMsg));
                     Utils_tskAckOrFreeMsg(pMsg, status);
                     break;
#ifndef RADAR_ONLY
                 case GRPX_SRC_LINK_CMD_SRV_CALIB_PARAM:
                     {
                        GrpxSrcLink_SrvCalibPrm *pSrvCalibPrm;
                        pSrvCalibPrm = \
                                (GrpxSrcLink_SrvCalibPrm*)Utils_msgGetPrm(pMsg);
                        GrpxSrcLink_displaySrvCalibStats(pObj, pSrvCalibPrm);
                        Utils_tskAckOrFreeMsg(pMsg, status);
                     }
                     break;
                 case GRPX_SRC_LINK_CMD_NEW_OVERLAY:
                     status = GrpxSrcLink_drawOverlaysRun(pObj);
                     Utils_tskAckOrFreeMsg(pMsg, status);
                     break;
                 case GRPX_SRC_LINK_CMD_STEREO_CALIB_PARAM:
                    {
                     GrpxSrcLink_StereoCalibPrm *pStereoCalibPrm;
                     pStereoCalibPrm = (GrpxSrcLink_StereoCalibPrm*)Utils_msgGetPrm(pMsg);
                     status = GrpxSrcLink_displayStereoCalibStats(pObj, pStereoCalibPrm);
                     Utils_tskAckOrFreeMsg(pMsg, status);
                    }
                    break;
#endif
                 default:
                     Utils_tskAckOrFreeMsg(pMsg, status);
                 break;
            }

        }
        else
        {
            GrpxSrcLink_drvProcessData(pObj);
            Task_sleep(GRPX_SRC_LINK_PROCESS_INTERVAL_MSEC);
        }
    }

    GrpxSrcLink_drvDelete(pObj);

    if (ackMsg && pMsg !=NULL)
        Utils_tskAckOrFreeMsg(pMsg, status);

    return;
}

/**
 *******************************************************************************
 * \brief Function called by links connected to Grpx Src link to get data from
 *    the output queue of Grpx Src link
 *
 * \param  ptr      [IN]  Handle to task
 * \param  queId    [IN]  output queue Id
 * \param  pBufList [OUT] A List of buffers needed for the next link
 *
 * \return SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 GrpxSrcLink_getFullBuffers(Void * ptr, UInt16 queId,
                            System_BufferList * pBufList)
{
    Int32 status;
    GrpxSrcLink_Obj *pObj;
    Utils_TskHndl *pTsk = (Utils_TskHndl *) ptr;

    pObj = (GrpxSrcLink_Obj *) pTsk->appData;
    UTILS_assert(queId < GRPX_SRC_LINK_MAX_OUT_QUE);

    status = Utils_bufGetFull(&pObj->outObj.bufOutQue, pBufList,
                              BSP_OSAL_NO_WAIT);
    return status;
}

/**
 *******************************************************************************
 * \brief Function called by links connected to Grpx Src link to return back
 *    buffers
 *
 * \param  ptr      [IN]  Handle to task
 * \param  queId    [IN]  output queue Id
 * \param  pBufList [IN]  A List of buffers returned back to DUP link
 *
 * \return SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 GrpxSrcLink_putEmptyBuffers(Void * ptr, UInt16 queId,
                              System_BufferList * pBufList)
{
    Int32 status;
    Utils_TskHndl *pTsk = (Utils_TskHndl *) ptr;
    GrpxSrcLink_Obj *pObj = (GrpxSrcLink_Obj *) pTsk->appData;

    UTILS_assert(queId < GRPX_SRC_LINK_MAX_OUT_QUE);

    status = Utils_bufPutEmpty(&pObj->outObj.bufOutQue, pBufList);

    return status;
}

/**
 *******************************************************************************
 * \brief Function called by links connected to Grpx Src link to get output queue
 *    Information of this link
 *
 * \param  ptr      [IN]  Handle to task
 * \param  info     [OUT] output queues information of Grpx Src link
 *
 * \return SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 GrpxSrcLink_getLinkInfo(Void * ptr, System_LinkInfo * info)
{
    Utils_TskHndl *pTsk = (Utils_TskHndl *) ptr;

    GrpxSrcLink_Obj *pObj = (GrpxSrcLink_Obj *) pTsk->appData;

    memcpy(info, &pObj->info, sizeof(*info));

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Init function for Grpx Src link. This function does the following
 *   for each Grpx link,
 *  - Creates a task for the link
 *  - Registers this link with the system
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 GrpxSrcLink_init()
{
    Int32 status;
    System_LinkObj linkObj;
    UInt32 grpxSrcId;
    GrpxSrcLink_Obj *pObj;
    UInt32 procId = System_getSelfProcId();


    #ifdef DATA_VIS_INCLUDE
    {
        DataVis_CreatePrm dataVisCreatePrm;

        DataVis_CreatePrm_Init(&dataVisCreatePrm);
        DataVis_create(&dataVisCreatePrm);
    }
    #endif

    for (grpxSrcId = 0; grpxSrcId < GRPX_SRC_LINK_OBJ_MAX; grpxSrcId++)
    {
        pObj = &gGrpxSrcLink_obj[grpxSrcId];

        memset(pObj, 0, sizeof(*pObj));

        pObj->tskId = SYSTEM_MAKE_LINK_ID(procId,
                                          SYSTEM_LINK_ID_GRPX_SRC_0 + grpxSrcId);
        memset(&linkObj, 0, sizeof(linkObj));
        linkObj.pTsk = &pObj->tsk;

        linkObj.linkGetFullBuffers  = GrpxSrcLink_getFullBuffers;
        linkObj.linkPutEmptyBuffers = GrpxSrcLink_putEmptyBuffers;
        linkObj.getLinkInfo = GrpxSrcLink_getLinkInfo;

        System_registerLink(pObj->tskId, &linkObj);

        snprintf(pObj->name, GRPX_SRC_LINK_STR_SZ, "GrpxSrc%u", (unsigned int)grpxSrcId);

        status = Utils_tskCreate(&pObj->tsk,
                                 GrpxSrcLink_tskMain,
                                 GRPX_SRC_LINK_TSK_PRI,
                                 gGrpxSrcLink_tskStack[grpxSrcId],
                                 GRPX_SRC_LINK_TSK_STACK_SIZE, pObj, pObj->name,
                                 UTILS_TSK_AFFINITY_CORE1);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief De-init function for Grpx Src link. This function de-registers this
 *  link from the system
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 GrpxSrcLink_deInit()
{
    UInt32 grpxSrcId;

    #ifdef DATA_VIS_INCLUDE
    DataVis_delete();
    #endif

    for (grpxSrcId = 0; grpxSrcId < GRPX_SRC_LINK_OBJ_MAX; grpxSrcId++)
    {
        Utils_tskDelete(&gGrpxSrcLink_obj[grpxSrcId].tsk);
    }
    return SYSTEM_LINK_STATUS_SOK;
}
