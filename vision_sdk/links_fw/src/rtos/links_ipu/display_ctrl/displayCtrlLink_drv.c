/*
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
*/

/**
 *******************************************************************************
 * \file displayCtrlLink_drv.c
 *
 * \brief  This file has the implementataion of Display Control Driver Calls
 *
 *         This file implements the calls to display controller driver.
 *         Calls to driver create, control commands, deletion is done in this
 *         file. Conversion / population of FVID2 parameters based on
 *         parameters of link API structures happen here.|
 *
 * \version 0.0 (Jun 2013) : [PS] First version
 * \version 0.1 (Jul 2013) : [PS] Updates as per code review comments
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "displayCtrlLink_priv.h"
#include "ti/drv/pm/pmhal.h"
#include "ti/drv/pm/pmlib.h"

/*******************************************************************************
 *                  Internal Function Declarations
 *******************************************************************************
 */
void DisplayCtrlLink_configureVideoPllAndClkSrcForLCD(
                    UInt32 vencId, UInt32 pixelClock,UInt32 divisorPCD);

Int32 DisplayCtrlLink_drvOvlyParamsInit(DisplayCtrlLink_OvlyParams *pOvlyParams);

Int32 DisplayCtrlLink_drvOvlyPipeParamsInit(DisplayCtrlLink_OvlyPipeParams
                                           *pOvlyPipeParams);
Void DisplayCtrl_timerCallback(UInt32 arg);


Void DisplayCtrl_timerCallback(UInt32 arg)
{
    Int32 retVal;

    /* MISRA.CAST.PTR_TO_INT
     * MISRAC_2004 Rule_11.3
     * MISRAC_WAIVER:
     * This is a generic implementation which supports all dataTypes.
     * This typecasting is necessary.
     */
    DisplayCtrlLink_Obj * pObj = (DisplayCtrlLink_Obj * )arg;

    retVal = Fvid2_control(
        pObj->fvidHandleDisplayCtrl,
        IOCTL_VPS_DCTRL_GET_ERROR_STATS,
        &pObj->dctrlStat,
        NULL);
    if (FVID2_SOK != retVal)
    {
        Vps_printf("DISPLAYCTRL: Get display control status failed!!\r\n");
    }
    else
    {
        Utils_linkStatsSetSyncLostCount(pObj->dctrlStat.syncLost1,
            pObj->dctrlStat.syncLost2, pObj->dctrlStat.syncLost3,
            pObj->dctrlStat.syncLostTV, pObj->dctrlStat.ocpError);
    }
}

/**
 *******************************************************************************
 *
 * \brief Create displayCtrl link driver
 *
 *        This creates
 *         - displayCtrl driver
 *         - Does not perform any configuration, just keeps it ready for
 *           receiving next commands
 *
 * \param  pObj     [IN] Display Controller object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 DisplayCtrlLink_drvCreate(DisplayCtrlLink_Obj * pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    Vps_DssDispcMflagConfigParam dssDispcMflagParam;

#ifdef SYSTEM_DEBUG_DISPLAYCTRL
    Vps_printf(" DISPLAYCTRL: Create in progress !!!\n");
#endif

    /*
     * Create displayCtrl handle, used for setting venc and overlay
     * parameters
     */
    pObj->fvidHandleDisplayCtrl = FVID2_create(FVID2_VPS_DCTRL_DRV,
                                               VPS_DCTRL_INST_0,
                                               NULL,
                                               NULL,
                                               NULL);

    UTILS_assert(pObj->fvidHandleDisplayCtrl != NULL);

    pObj->timer = BspOsal_clockCreate(
                            &DisplayCtrl_timerCallback,
                            DCTRL_LINK_TIME_OUT_IN_MS, (Bool)FALSE, pObj);
    UTILS_assert(pObj->timer != NULL);

    /*
     * Set MFlag control
     * To set mflag param, get mflag param using IOCTL_VPS_DCTRL_GET_MFLAG_PARAM
     * to avoid overwriting of existing value.
     */

    status = Fvid2_control(pObj->fvidHandleDisplayCtrl,
                  IOCTL_VPS_DCTRL_GET_MFLAG_PARAM,
                  &dssDispcMflagParam,
                  NULL);

    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    /* Set DSS MFlag Param */
    dssDispcMflagParam.globalMflagStart = 1;
    dssDispcMflagParam.globalMflagCtrl  = 2;

    status = Fvid2_control(pObj->fvidHandleDisplayCtrl,
                  IOCTL_VPS_DCTRL_SET_MFLAG_PARAM,
                  &dssDispcMflagParam,
                  NULL);

    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

#ifdef SYSTEM_DEBUG_DISPLAYCTRL
    Vps_printf(" DISPLAYCTRL: Create Done !!!\n");
#endif

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Deletes displayCtrl link driver
 *
 * \param  pObj     [IN] Display Controller object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 DisplayCtrlLink_drvDelete(DisplayCtrlLink_Obj * pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

#ifdef SYSTEM_DEBUG_DISPLAYCTRL
    Vps_printf(" DISPLAYCTRL: Deletion in progress !!!\n");
#endif

    status = FVID2_delete(pObj->fvidHandleDisplayCtrl, NULL);

    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    if (NULL != pObj->timer)
    {
        BspOsal_clockDelete(&pObj->timer);
    }

#ifdef SYSTEM_DEBUG_DISPLAYCTRL
    Vps_printf(" DISPLAYCTRL: Delete Done !!!\n");
#endif

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Populates Vps_DctrlConfig parameter for a given vencId
 *
 *        Vps_DctrlConfig is the structure used for FVID2_Control
 *        IOCTL_VPS_DCTRL_SET_CONFIG and IOCTL_VPS_DCTRL_CLR_CONFIG command.
 *        It primarily captures connectivity paths between video / graphics
 *        pipes, Vencs and Display output ports. Vps_DctrlConfig is defined
 *        considering paths involving all the Vencs.
 *        DisplayCtrlLink_VencInfo, which is defined as part of display
 *        ctrl interface, comprehends all attribtues of one Venc.
 *
 *        This function essentially performs translations from definitions
 *        of DisplayCtrlLink_VencInfo to Vps_DctrlConfig. This function gets
 *        called during both SET_CONFIG and CLR_CONFIG FVID2_Control calls.
 *        Also this function gets called once per Venc. Hence some information
 *        like total edge counter is maintained across calls of this function.
 *
 *        Note following limitations of current definition of link interface
 *        1. Write back to memory is only after blender stage. Direct pipe
 *           output cannot be written back.
 *        2. Output of one Venc can be connected to only one of the output
 *           display ports
 *
 * \param  pVencInfo     [IN] Pointer to struct capturing Info of one Venc
 * \param  pDctrlCfg     [IN] Pointer to driver structure of Display Controller
 * \param  vencCntr      [IN] Venc ID
 * \param  pEdgeCntr     [IN/OUT] Counter of number of edges, maintained across
 *                                calls. Hence a pointer is sent.
 * \param  pipeUsedFlag  [IN/OUT] Captures information of which pipe gets used
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 DisplayCtrlLink_drvConfigInit(const DisplayCtrlLink_VencInfo *pVencInfo,
                                    Vps_DctrlConfig *pDctrlCfg,
                                    UInt32 vencCntr,
                                    UInt32 *pEdgeCntr,
                                    UInt32 *pipeUsedFlag)
{
    Fvid2_ModeInfo *pMInfo;
    UInt32          blenderNode, i;
    UInt32          edgeCntr = *pEdgeCntr;
    Int32           status   = SYSTEM_LINK_STATUS_SOK;

    if(Bsp_platformIsTda3xxFamilyBuild())
    {
        if((SYSTEM_DCTRL_DSS_VENC_LCD2 == pVencInfo->vencId)
            ||
           (SYSTEM_DCTRL_DSS_VENC_LCD3 == pVencInfo->vencId)
            ||
           (SYSTEM_DCTRL_DSS_VENC_HDMI == pVencInfo->vencId)
            ||
           ((UInt32)TRUE == pVencInfo->isInputPipeConnected[2]))
        {
            Vps_printf(" DISPLAYCTRL: DSS_VENC_LCD2/LCD3/HDMI NOT supported on TDA3xx"
                       " !!!\n"
                       );
            Vps_printf(" DISPLAYCTRL: DSS_VID3_PIPE NOT supported on TDA3xx"
                       " !!!\n"
                       );

            UTILS_assert((Bool)0U);
        }
    }

    if(SYSTEM_DCTRL_DSS_VENC_SDTV == pVencInfo->vencId)
    {
        if(Bsp_platformIsTda3xxFamilyBuild())
        {
        }
        else
        {
            Vps_printf(" DISPLAYCTRL: SDVENC Not available"
                       " !!!\n"
                       );
            UTILS_assert((Bool)0U);
        }
    }

    Fvid2ModeInfo_init(&pDctrlCfg->vencInfo.modeInfo[vencCntr].mInfo);

    /*
     * Pick blender node based on the Venc id
     */
    if((pVencInfo->vencId == SYSTEM_DCTRL_DSS_VENC_LCD1) ||
       (pVencInfo->vencId == SYSTEM_DCTRL_DSS_VENC_SDTV))
    {
       blenderNode = VPS_DCTRL_DSS_LCD1_BLENDER;
    }
    else if (pVencInfo->vencId == SYSTEM_DCTRL_DSS_VENC_LCD2)
    {
       blenderNode = VPS_DCTRL_DSS_LCD2_BLENDER;
    }
    else if (pVencInfo->vencId == SYSTEM_DCTRL_DSS_VENC_LCD3)
    {
       blenderNode = VPS_DCTRL_DSS_LCD3_BLENDER;
    }
    else if (pVencInfo->vencId == SYSTEM_DCTRL_DSS_VENC_HDMI)
    {
       blenderNode = VPS_DCTRL_DSS_HDMI_BLENDER;
    }
    else
    {
       blenderNode = VPS_DCTRL_DSS_LCD1_BLENDER; /* To avoid KW error */
       UTILS_assert((Bool)0U);
    }

    /*
     * Connecting video / graphix pipelines to Venc. Also captures info
     * of which pipe gets used
     */
    if(pVencInfo->isInputPipeConnected[0] == (UInt32)TRUE)
    {
        pDctrlCfg->edgeInfo[edgeCntr].startNode  =
            VPS_DCTRL_DSS_VID1_INPUT_PATH;
        pDctrlCfg->edgeInfo[edgeCntr].endNode  = blenderNode;
        edgeCntr++;
        pipeUsedFlag[SYSTEM_DSS_DISPC_PIPE_VID1] = (UInt32)TRUE;
        /* MISRA.PTR.ARITH
         * MISRAC_2004_Rule_17.1 MISRAC_2004_Rule_17.4: Pointer is used in
         *                       arithmetic or array index expression
         * KW State: Defer -> Waiver -> Case by case
         *
         * Pointer arithmetic is required for indexing the array.
         * The harmful side effect of violating this rule (accessing outside
         * valid memory) shall be checked by another code checker like Klocwork.
         */
    }
    if(pVencInfo->isInputPipeConnected[1] == (UInt32)TRUE)
    {
        pDctrlCfg->edgeInfo[edgeCntr].startNode  =
            VPS_DCTRL_DSS_VID2_INPUT_PATH;
        pDctrlCfg->edgeInfo[edgeCntr].endNode  = blenderNode;
        edgeCntr++;
        pipeUsedFlag[SYSTEM_DSS_DISPC_PIPE_VID2] = (UInt32)TRUE;
        /* MISRA.PTR.ARITH
         * MISRAC_2004_Rule_17.1 MISRAC_2004_Rule_17.4: Pointer is used in
         *                       arithmetic or array index expression
         * KW State: Defer -> Waiver -> Case by case
         *
         * Pointer arithmetic is required for indexing the array.
         * The harmful side effect of violating this rule (accessing outside
         * valid memory) shall be checked by another code checker like Klocwork.
         */
    }
    if(pVencInfo->isInputPipeConnected[2] == (UInt32)TRUE)
    {
        pDctrlCfg->edgeInfo[edgeCntr].startNode  =
            VPS_DCTRL_DSS_VID3_INPUT_PATH;
        pDctrlCfg->edgeInfo[edgeCntr].endNode  = blenderNode;
        edgeCntr++;
        pipeUsedFlag[SYSTEM_DSS_DISPC_PIPE_VID3] = (UInt32)TRUE;
        /* MISRA.PTR.ARITH
         * MISRAC_2004_Rule_17.1 MISRAC_2004_Rule_17.4: Pointer is used in
         *                       arithmetic or array index expression
         * KW State: Defer -> Waiver -> Case by case
         *
         * Pointer arithmetic is required for indexing the array.
         * The harmful side effect of violating this rule (accessing outside
         * valid memory) shall be checked by another code checker like Klocwork.
         */
    }
    if(pVencInfo->isInputPipeConnected[3] == (UInt32)TRUE)
    {
        pDctrlCfg->edgeInfo[edgeCntr].startNode  =
            VPS_DCTRL_DSS_GFX1_INPUT_PATH;
        pDctrlCfg->edgeInfo[edgeCntr].endNode  = blenderNode;
        edgeCntr++;
        pipeUsedFlag[SYSTEM_DSS_DISPC_PIPE_GFX1] = (UInt32)TRUE;
        /* MISRA.PTR.ARITH
         * MISRAC_2004_Rule_17.1 MISRAC_2004_Rule_17.4: Pointer is used in
         *                       arithmetic or array index expression
         * KW State: Defer -> Waiver -> Case by case
         *
         * Pointer arithmetic is required for indexing the array.
         * The harmful side effect of violating this rule (accessing outside
         * valid memory) shall be checked by another code checker like Klocwork.
         */
    }

    /*
     * Connecting write back if enabled.
     */
    if(pVencInfo->writeBackEnabledFlag==TRUE)
    {
        pDctrlCfg->edgeInfo[edgeCntr].startNode = blenderNode;
        pDctrlCfg->edgeInfo[edgeCntr].endNode = VPS_DCTRL_DSS_WB_OUTPUT;
        edgeCntr++;
    }

    /*
     * Connecting Venc to output port
     */
    pDctrlCfg->edgeInfo[edgeCntr].startNode = blenderNode;
    pDctrlCfg->edgeInfo[edgeCntr].endNode = pVencInfo->outputPort;
    edgeCntr++;

    pDctrlCfg->vencInfo.modeInfo[vencCntr].vencId = pVencInfo->vencId;
    pDctrlCfg->vencInfo.modeInfo[vencCntr].mode   = pVencInfo->mode;

    pMInfo              = &pDctrlCfg->vencInfo.modeInfo[vencCntr].mInfo;
    pMInfo->standard    = pVencInfo->mInfo.standard;
    pMInfo->width       = pVencInfo->mInfo.width;
    pMInfo->height      = pVencInfo->mInfo.height;
    pMInfo->scanFormat  = pVencInfo->mInfo.scanFormat;
    pMInfo->pixelClock  = pVencInfo->mInfo.pixelClock;
    pMInfo->fps         = pVencInfo->mInfo.fps;
    pMInfo->hFrontPorch = pVencInfo->mInfo.hFrontPorch;
    pMInfo->hBackPorch  = pVencInfo->mInfo.hBackPorch;
    pMInfo->hSyncLen    = pVencInfo->mInfo.hSyncLen;
    pMInfo->vFrontPorch = pVencInfo->mInfo.vFrontPorch;
    pMInfo->vBackPorch  = pVencInfo->mInfo.vBackPorch;
    pMInfo->vSyncLen    = pVencInfo->mInfo.vSyncLen;

    for (i = 0U; i < 4U; i++)
    {
        pMInfo->reserved[i] = 0;
    }
    pDctrlCfg->vencInfo.modeInfo[vencCntr].mode  = pVencInfo->mode;

    /*
     * Store back edge counter since this is a running counter across
     * different Vencs
     */
    *pEdgeCntr = edgeCntr;

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Populates init (default) values for Overlay Params
 *
 * \param  pOvlyParams     [IN] Pointer to struct DisplayCtrlLink_OvlyParams
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 DisplayCtrlLink_drvOvlyParamsInit(DisplayCtrlLink_OvlyParams *pOvlyParams)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    pOvlyParams->vencId             = SYSTEM_DCTRL_DSS_VENC_LCD1;
    pOvlyParams->colorKeyEnable     = 0;
    pOvlyParams->colorKeySel        = SYSTEM_DSS_DISPC_TRANS_COLOR_KEY_SRC;
    pOvlyParams->deltaLinesPerPanel = 0;
    pOvlyParams->transColorKey      = 0x00;
    pOvlyParams->backGroundColor    = 0x00FF00;
    pOvlyParams->alphaBlenderEnable = 0;
    pOvlyParams->ovlyOptimization   = SYSTEM_DSS_DISPC_OVLY_FETCH_ALLDATA;

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Populates init (default) values for Overlay Pipe Params
 *
 * \param  pOvlyPipeParams [IN] Pointer to struct DisplayCtrlLink_OvlyPipeParams
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 DisplayCtrlLink_drvOvlyPipeParamsInit(DisplayCtrlLink_OvlyPipeParams
                                           *pOvlyPipeParams)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    pOvlyPipeParams->zorderEnable = FALSE;

    if(pOvlyPipeParams->pipeLine == SYSTEM_DSS_DISPC_PIPE_VID1)
    {
        pOvlyPipeParams->zorder = SYSTEM_DSS_DISPC_ZORDER0;
    }
    else if (pOvlyPipeParams->pipeLine == SYSTEM_DSS_DISPC_PIPE_VID2)
    {
        pOvlyPipeParams->zorder = SYSTEM_DSS_DISPC_ZORDER1;
    }
    else if (pOvlyPipeParams->pipeLine == SYSTEM_DSS_DISPC_PIPE_VID3)
    {
        pOvlyPipeParams->zorder = SYSTEM_DSS_DISPC_ZORDER2;
    }
    else if (pOvlyPipeParams->pipeLine == SYSTEM_DSS_DISPC_PIPE_GFX1)
    {
        pOvlyPipeParams->zorder = SYSTEM_DSS_DISPC_ZORDER2;
    }
    else
    {
        UTILS_assert((Bool)0U);
    }

    if(pOvlyPipeParams->pipeLine == SYSTEM_DSS_DISPC_PIPE_GFX1)
    {
        pOvlyPipeParams->globalAlpha = 0x7F;
    }
    else
    {
        pOvlyPipeParams->globalAlpha = 0xFF;
    }

    pOvlyPipeParams->preMultiplyAlpha = 0;

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Configures the clock source and Video PLL
 *
 * \param  vencId                  [IN] Venc ID.
 * \param  pixelClock              [IN] Pixel CLock Value.
 * \param  divisorPCD              [IN] Pixel clock divisor value.
 *
 *******************************************************************************
 */
void DisplayCtrlLink_configureVideoPllAndClkSrcForLCD(
                    UInt32 vencId, UInt32 pixelClock,UInt32 divisorPCD)
{
    Bsp_PlatformSetPllFreq vPllCfg;
    Bsp_PlatformVencSrc    vencClkCfg;
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    /*
    * For LCD resolution 800x480@60fps pixelClock = 29.232Mhz
    * PixelCLock is computed as follows -
    * No. of pixels per frame = (800 + H blanking) * (480 + Vertical blanking
    *                         = 928*525 = 487200
    *For 60fps i.e 60 * 487200 = 29232000. i.e 29232 KHz.
    */
    vPllCfg.videoPll = BSP_PLATFORM_PLL_VIDEO1;

    if(Bsp_platformIsTda3xxFamilyBuild())
    {
        vPllCfg.videoPll = BSP_PLATFORM_PLL_EVE_VID_DSP;
    }

    /*
    * HPixel clock to be configured. based on the PCD divisor.
    * This is the value for which the VideoPLL can lock.
    * TODO: Currently from usecase divisor is being set as 4. This is due to a
    * defect in BSP - PLL not locking for 29232 * 1. Once this issue is
    * resolved divisorPCD can be set to 1
    */
    vPllCfg.pixelClk = pixelClock * divisorPCD;
    vPllCfg.chooseMaxorMinMN = (UInt32) BSP_PLATFORM_VIDEO_PLL_CALC_MAX_MN;

    status = Bsp_platformSetPllFreq(&vPllCfg);
    UTILS_assert (status == SYSTEM_LINK_STATUS_SOK);


    switch(vencId)
    {
    case SYSTEM_DCTRL_DSS_VENC_LCD1:
    case SYSTEM_DCTRL_DSS_VENC_SDTV:
        vencClkCfg.outputVenc = BSP_PLATFORM_VENC_LCD1;
        vencClkCfg.vencClkSrc = BSP_PLATFORM_CLKSRC_DPLL_VIDEO1_CLKOUT1;
        if(Bsp_platformIsTda3xxFamilyBuild())
        {
            vencClkCfg.vencClkSrc = BSP_PLATFORM_CLKSRC_DPLL_EVE_VID_DSP;
        }
        break;

    case SYSTEM_DCTRL_DSS_VENC_LCD2:
        vencClkCfg.outputVenc = BSP_PLATFORM_VENC_LCD2;
        vencClkCfg.vencClkSrc = BSP_PLATFORM_CLKSRC_DPLL_VIDEO1_CLKOUT3;
        break;

    case SYSTEM_DCTRL_DSS_VENC_LCD3:
        vencClkCfg.outputVenc = BSP_PLATFORM_VENC_LCD3;
        vencClkCfg.vencClkSrc = BSP_PLATFORM_CLKSRC_DPLL_VIDEO1_CLKOUT3;
        break;

    default:
        UTILS_assert((Bool)0U);
        break;
    }

    status = Bsp_platformSetVencClkSrc(&vencClkCfg);
    UTILS_assert (status == SYSTEM_LINK_STATUS_SOK);

}

/**
 *******************************************************************************
 *
 * \brief Set configuration for displayCtrl
 *
 *        Function that implements driver calls for command
 *        DISPLAYCTRL_LINK_CMD_SET_CONFIG.
 *
 *        This function performs following for one or more Vencs
 *        - Configures input and output connections
 *          (IOCTL_VPS_DCTRL_SET_CONFIG). Since this driver call comprehends
 *          paths of all the Vencs, a loop is run to collect info of all Vencs
 *          in a loop and this FVID2_Control call is done once outside the Venc
 *          loop
 *        - Sets parameters of output info (IOCTL_VPS_DCTRL_SET_VENC_OUTPUT)
 *          This FVID2_Control call is done per Venc. Hence part of Venc loop
 *        - Configures divisor info (IOCTL_VPS_DCTRL_SET_VENC_PCLK_DIVISORS)
 *          This FVID2_Control call is done per Venc. Hence part of Venc loop
 *        pConfigParams captures information for above configurations.
 *
 *        Default intializations are done for following, since the application
 *        might not call commands for them
 *        - Overlay parameters
 *          Done for each Venc Id used. Hence inside the Venc loop.
 *        - Overlay Pipe parameters
 *          Done for each pipe used. But pipe usage info needs to be gathered
 *          based on looking at attributes for all the Vencs. Hence this
 *          info is gathered in DisplayCtrlLink_drvConfigInit function.
 *          And finally call for drv function is made outside the Venc loop.
 *        Above default configurations are done by calls to the corresponding
 *        DisplayCtrlLink_drv functions.
 *
 * \param  pObj          [IN] Display ctrl Object Handle
 * \param  pConfigParams [IN] Handle to link interface of Config params
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 DisplayCtrlLink_drvSetConfig(DisplayCtrlLink_Obj *pObj,
                                   DisplayCtrlLink_ConfigParams *pConfigParams)
{
    Int32                           retVal;
    DisplayCtrlLink_OvlyParams      defaultOvlyParams, *pDefaultOvlyParams;
    DisplayCtrlLink_OvlyPipeParams  defaultOvlyPipeParams;
    DisplayCtrlLink_OvlyPipeParams *pDefaultOvlyPipeParams;
    Vps_DctrlConfig                 dctrlCfg, *pDctrlCfg;
    DisplayCtrlLink_VencInfo       *pVencInfo;
    Vps_DctrlVencDivisorInfo        vencDivisors;
    Vps_DctrlOutputInfo             vencOutputInfo;

    UInt32 vencCntr = 0;
    UInt32 edgeCntr = 0;
    Int32   status = SYSTEM_LINK_STATUS_SOK;
    Bool isSdVencUsed;

    UInt32 pipeUsedFlag[SYSTEM_DSS_DISPC_PIPE_MAX] = { (UInt32)FALSE };

    pDctrlCfg              = &dctrlCfg;
    pDefaultOvlyParams     = &defaultOvlyParams;
    pDefaultOvlyPipeParams = &defaultOvlyPipeParams;

    VpsDctrlConfig_init(pDctrlCfg);
    /*
     * Same default overlay values are used for all Vencs. Hence called outside
     * Venc Loop.
     */
    retVal = DisplayCtrlLink_drvOvlyParamsInit(pDefaultOvlyParams);
    UTILS_assert(retVal == SYSTEM_LINK_STATUS_SOK);

#ifdef SYSTEM_DEBUG_DISPLAYCTRL
    Vps_printf(" DISPLAYCTRL: Set config in progress !!!\n");
#endif

    /*
     * Venc Loop: Loop runs over all the number of Vencs used.
     * Configurations which are specific to given vencId are done here.
     */
    for(vencCntr = 0U; vencCntr < pConfigParams->numVencs; vencCntr++)
    {
        pVencInfo = &pConfigParams->vencInfo[vencCntr];

        /*
         * Currently, enum SYSTEM_DCTRL_DSS_VENC_SDTV is not supported in
         * FVID interface. Hence value is overwritten as SYSTEM_DCTRL_DSS_VENC_LCD1.
         * In future once support is available, below overwriting is not needed.
         */
        if(pVencInfo->vencId == SYSTEM_DCTRL_DSS_VENC_SDTV)
        {
          if(Bsp_platformIsTda3xxFamilyBuild())
          {
            isSdVencUsed = (Bool)TRUE;
            pVencInfo->vencId = SYSTEM_DCTRL_DSS_VENC_LCD1;
          }
          else
          {
            isSdVencUsed = (Bool)FALSE; /* To avoid KW error */
            UTILS_assert((Bool)0U);
          }
        }
        else
        {
            isSdVencUsed = (Bool)FALSE;
        }

        DisplayCtrlLink_drvConfigInit(pVencInfo,
                                      pDctrlCfg,
                                      vencCntr,
                                      &edgeCntr,
                                      pipeUsedFlag);

        if (pVencInfo->vencId == SYSTEM_DCTRL_DSS_VENC_HDMI)
        {
            #ifdef SYSTEM_DEBUG_DISPLAYCTRL
            Vps_printf(" DISPLAYCTRL: Enabled HDMI PLL for HDMI !!!\n");
            #endif

            status = Bsp_platformEnableHdmiPll((UInt32)TRUE);
            UTILS_assert (status == SYSTEM_LINK_STATUS_SOK);
        }

        if (   (pVencInfo->vencId == SYSTEM_DCTRL_DSS_VENC_LCD1)
            || (pVencInfo->vencId == SYSTEM_DCTRL_DSS_VENC_LCD2)
            || (pVencInfo->vencId == SYSTEM_DCTRL_DSS_VENC_LCD3)
            || (pVencInfo->vencId == SYSTEM_DCTRL_DSS_VENC_SDTV)
           )
        {
            UInt32 pixelClock;

            #ifdef SYSTEM_DEBUG_DISPLAYCTRL
            Vps_printf(" DISPLAYCTRL: Enabled Video PLL for LCD !!!\n");
            #endif

            vencDivisors.vencId     = pVencInfo->vencId;
            vencDivisors.divisorLCD = pVencInfo->vencDivisorInfo.divisorLCD;
            vencDivisors.divisorPCD = pVencInfo->vencDivisorInfo.divisorPCD;

            retVal = Fvid2_control(pObj->fvidHandleDisplayCtrl,
                               IOCTL_VPS_DCTRL_SET_VENC_PCLK_DIVISORS,
                               &vencDivisors,
                               NULL);
            UTILS_assert(retVal == SYSTEM_LINK_STATUS_SOK);

            if(pVencInfo->mInfo.standard == SYSTEM_STD_CUSTOM)
            {
                pixelClock = pVencInfo->mInfo.pixelClock;
            }
            else
            {
                Fvid2_ModeInfo mInfo;

                mInfo.standard = pVencInfo->mInfo.standard;

                /* We are extracting the Pixel Clock frequency which will be used to
                    configure the PLL */
                retVal = Fvid2_getModeInfo(&mInfo);
                if(retVal!=SYSTEM_LINK_STATUS_SOK)
                {
                    Vps_printf(" DISPLAYCTRL: Invalid standard (%d) specified !!!\n",
                        mInfo.standard
                        );
                    UTILS_assert((Bool)0U);
                }

                pixelClock = mInfo.pixelClock;

                if(isSdVencUsed == (Bool)TRUE)
                {
                    pixelClock = pixelClock * 2U;
                }

                if(Bsp_platformIsTda3xxFamilyBuild())
                {
                    UInt32 clk = 0U;
                    if(DISPLAYCTRL_LINK_TDM_24BIT_TO_8BIT == pVencInfo->tdmMode)
                    {
                        pixelClock = pixelClock * 3U;
                    }
                    retVal = (Int32)PMLIBClkRateGet(PMHAL_PRCM_MOD_DSP1, PMHAL_PRCM_CLK_GENERIC, &clk);
                    if ((retVal == SYSTEM_LINK_STATUS_SOK) && (clk == 745000000U))
                    {
                        if (pixelClock == 148500U)
                        {
                            /* In TDA3xx with OPP High the pixel clock can only be 149 MHz or 74.5 MHz */
                            pixelClock = 149000U;
                        }
                    }
                }
            }

            DisplayCtrlLink_configureVideoPllAndClkSrcForLCD(vencDivisors.vencId,
                pixelClock, vencDivisors.divisorPCD);
        }

    }

    for(vencCntr = 0U; vencCntr < pConfigParams->numVencs; vencCntr++)
    {
        pVencInfo = &pConfigParams->vencInfo[vencCntr];

        vencOutputInfo.actVidPolarity   =
            pVencInfo->vencOutputInfo.actVidPolarity;
        vencOutputInfo.hsPolarity       =
            pVencInfo->vencOutputInfo.hsPolarity;
        vencOutputInfo.vsPolarity       =
            pVencInfo->vencOutputInfo.vsPolarity;
        vencOutputInfo.pixelClkPolarity =
            pVencInfo->vencOutputInfo.pixelClkPolarity;
        vencOutputInfo.dvoFormat        =
            pVencInfo->vencOutputInfo.dvoFormat;
        vencOutputInfo.vencId           =
            pVencInfo->vencId;
        vencOutputInfo.dataFormat       =
            pVencInfo->vencOutputInfo.dataFormat;
        vencOutputInfo.videoIfWidth     =
            pVencInfo->vencOutputInfo.videoIfWidth;
        vencOutputInfo.fidPolarity      =
            pVencInfo->vencOutputInfo.fidPolarity;

        retVal = Fvid2_control(pObj->fvidHandleDisplayCtrl,
                               IOCTL_VPS_DCTRL_SET_VENC_OUTPUT,
                               &vencOutputInfo,
                               NULL);
        UTILS_assert(retVal == SYSTEM_LINK_STATUS_SOK);

        if(Bsp_platformIsTda3xxFamilyBuild())
        {
            Vps_DssDispcAdvLcdTdmConfig advTdmPrms;
            VpsDssDispcAdvLcdTdmConfig_init(&advTdmPrms);
            advTdmPrms.tdmEnable = 0;
            if(DISPLAYCTRL_LINK_TDM_24BIT_TO_8BIT == pVencInfo->tdmMode)
            {
                advTdmPrms.tdmEnable = 1;
                /* Default init of advTdmPrms is for
                 * DISPLAYCTRL_LINK_TDM_24BIT_TO_8BIT mode
                 */
            }
            advTdmPrms.vencId    = pVencInfo->vencId;

            retVal = Fvid2_control(pObj->fvidHandleDisplayCtrl,
                                   IOCTL_VPS_DCTRL_DSS_SET_ADV_VENC_TDM_PARAMS,
                                   &advTdmPrms,
                                   NULL);
            UTILS_assert(retVal == SYSTEM_LINK_STATUS_SOK);
        }

    }

    /*
     * Configurations which are NOT vencID specific
     */
    pDctrlCfg->vencInfo.numVencs  = pConfigParams->numVencs;
    pDctrlCfg->vencInfo.tiedVencs = pConfigParams->tiedVencs;

    pDctrlCfg->numEdges = edgeCntr;
    pDctrlCfg->useCase  = VPS_DCTRL_USERSETTINGS;

    retVal = Fvid2_control(pObj->fvidHandleDisplayCtrl,
                           IOCTL_VPS_DCTRL_SET_CONFIG,
                           pDctrlCfg,
                           NULL);
    UTILS_assert(retVal == SYSTEM_LINK_STATUS_SOK);

    for(vencCntr = 0U; vencCntr < pConfigParams->numVencs; vencCntr++)
    {
        pVencInfo = &pConfigParams->vencInfo[vencCntr];
        pDefaultOvlyParams->vencId = pVencInfo->vencId;
        retVal = DisplayCtrlLink_drvSetOvlyParams(pObj, pDefaultOvlyParams);
        UTILS_assert(retVal == SYSTEM_LINK_STATUS_SOK);
    }

    /*
     * Configuring default values for used pipes
     */
    if(pipeUsedFlag[SYSTEM_DSS_DISPC_PIPE_VID1] == (UInt32)TRUE)
    {
        pDefaultOvlyPipeParams->pipeLine = SYSTEM_DSS_DISPC_PIPE_VID1;
        retVal = DisplayCtrlLink_drvOvlyPipeParamsInit(pDefaultOvlyPipeParams);
        UTILS_assert(retVal == SYSTEM_LINK_STATUS_SOK);
        retVal = DisplayCtrlLink_drvSetOvlyPipelineParams(
                     pObj,
                     pDefaultOvlyPipeParams);
        UTILS_assert(retVal == SYSTEM_LINK_STATUS_SOK);
    }

    if(pipeUsedFlag[SYSTEM_DSS_DISPC_PIPE_VID2] == (UInt32)TRUE)
    {
        pDefaultOvlyPipeParams->pipeLine = SYSTEM_DSS_DISPC_PIPE_VID2;
        retVal = DisplayCtrlLink_drvOvlyPipeParamsInit(pDefaultOvlyPipeParams);
        UTILS_assert(retVal == SYSTEM_LINK_STATUS_SOK);
        retVal = DisplayCtrlLink_drvSetOvlyPipelineParams(
                     pObj,
                     pDefaultOvlyPipeParams);
        UTILS_assert(retVal == SYSTEM_LINK_STATUS_SOK);
    }

    if(pipeUsedFlag[SYSTEM_DSS_DISPC_PIPE_VID3] == (UInt32)TRUE)
    {
        pDefaultOvlyPipeParams->pipeLine = SYSTEM_DSS_DISPC_PIPE_VID3;
        retVal = DisplayCtrlLink_drvOvlyPipeParamsInit(pDefaultOvlyPipeParams);
        UTILS_assert(retVal == SYSTEM_LINK_STATUS_SOK);
        retVal = DisplayCtrlLink_drvSetOvlyPipelineParams(
                     pObj,
                     pDefaultOvlyPipeParams);
        UTILS_assert(retVal == SYSTEM_LINK_STATUS_SOK);
    }

    if(pipeUsedFlag[SYSTEM_DSS_DISPC_PIPE_GFX1] == (UInt32)TRUE)
    {
        pDefaultOvlyPipeParams->pipeLine = SYSTEM_DSS_DISPC_PIPE_GFX1;
        retVal = DisplayCtrlLink_drvOvlyPipeParamsInit(pDefaultOvlyPipeParams);
        UTILS_assert(retVal == SYSTEM_LINK_STATUS_SOK);
        retVal = DisplayCtrlLink_drvSetOvlyPipelineParams(
                     pObj,
                     pDefaultOvlyPipeParams);
        UTILS_assert(retVal == SYSTEM_LINK_STATUS_SOK);
    }

    if(Bsp_platformIsTda3xxFamilyBuild())
    {
        /* For devices which have SD DAC and support SYSTEM_STD_NTSC / SYSTEM_STD_PAL */
        for(vencCntr = 0U; vencCntr < pConfigParams->numVencs; vencCntr++)
        {
            pVencInfo = &pConfigParams->vencInfo[vencCntr];
            if((pVencInfo->vencId == SYSTEM_DCTRL_DSS_VENC_LCD1) ||
               (pVencInfo->vencId == SYSTEM_DCTRL_DSS_VENC_SDTV)
              )
            {
                if((pVencInfo->mInfo.standard == SYSTEM_STD_NTSC)||
                   (pVencInfo->mInfo.standard == SYSTEM_STD_PAL)
                  )
                {
                    Vps_DctrlSDVencVideoStandard vidStd;
                    UInt32 enable;

                    vidStd.videoStandard = pVencInfo->mInfo.standard;

                    enable = (UInt32)TRUE;

                    /* SD-VENC Power on and Configure IOCTL's */
                    retVal = Fvid2_control(
                                pObj->fvidHandleDisplayCtrl,
                                IOCTL_VPS_DCTRL_ENABLE_SDVENC,
                                &enable,
                                NULL);
                    UTILS_assert(retVal == SYSTEM_LINK_STATUS_SOK);

                    /* SD-VENC Power on and Configure IOCTL's */
                    retVal = Fvid2_control(
                                pObj->fvidHandleDisplayCtrl,
                                IOCTL_VPS_DCTRL_SET_SDVENC_MODE,
                                &vidStd,
                                NULL);
                    UTILS_assert(retVal == SYSTEM_LINK_STATUS_SOK);
                }
            }
        }
    }

#ifdef SYSTEM_DEBUG_DISPLAYCTRL
    Vps_printf(" DISPLAYCTRL: Set config Done !!!\n");
#endif

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Clear configuration for displayCtrl
 *
 *        Function that implements driver calls for command
 *        DISPLAYCTRL_LINK_CMD_CLR_CONFIG.
 *
 *        This function performs following for one or more Vencs
 *        - Clears input and output connections
 *          (IOCTL_VPS_DCTRL_CLR_CONFIG). Since this driver call comprehends
 *          paths of all the Vencs, a loop is run to collect info of all Vencs
 *          in a loop and this FVID2_Control call is done once outside the Venc
 *          loop
 *
 * \param  pObj          [IN] Display ctrl Object Handle
 * \param  pConfigParams [IN] Handle to link interface of Config params
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 DisplayCtrlLink_drvClrConfig(DisplayCtrlLink_Obj *pObj,
                                   DisplayCtrlLink_ConfigParams *pConfigParams)
{
    Int32                    retVal;
    Vps_DctrlConfig          dctrlCfg, *pDctrlCfg;
    DisplayCtrlLink_VencInfo *pVencInfo;

    UInt32 vencCntr = 0;
    UInt32 edgeCntr = 0;
    Int32 status   = SYSTEM_LINK_STATUS_SOK;

    UInt32 pipeUsedFlag[SYSTEM_DSS_DISPC_PIPE_MAX] = { (UInt32)FALSE };

    pDctrlCfg = &dctrlCfg;

#ifdef SYSTEM_DEBUG_DISPLAYCTRL
    Vps_printf(" DISPLAYCTRL: Clear config in progress !!!\n");
#endif

    /*
     * Venc Loop: Loop runs over all the number of Vencs used
     */
    for(vencCntr = 0U; vencCntr < pConfigParams->numVencs; vencCntr++)
    {
        pVencInfo = &pConfigParams->vencInfo[vencCntr];

        DisplayCtrlLink_drvConfigInit(pVencInfo,
                                      pDctrlCfg,
                                      vencCntr,
                                      &edgeCntr,
                                      pipeUsedFlag);

        if(Bsp_platformIsTda3xxFamilyBuild())
        {
            if((pVencInfo->vencId == SYSTEM_DCTRL_DSS_VENC_LCD1) ||
               (pVencInfo->vencId == SYSTEM_DCTRL_DSS_VENC_SDTV)
              )
            {
                if((pVencInfo->mInfo.standard == SYSTEM_STD_NTSC)||
                   (pVencInfo->mInfo.standard == SYSTEM_STD_PAL)
                  )
                {
                    UInt32 enable;

                    enable = (UInt32)FALSE;

                    /* SD-VENC Power on and Configure IOCTL's */
                    retVal = Fvid2_control(
                                pObj->fvidHandleDisplayCtrl,
                                IOCTL_VPS_DCTRL_ENABLE_SDVENC,
                                &enable,
                                NULL);
                    UTILS_assert(retVal == SYSTEM_LINK_STATUS_SOK);
                }
            }
        }

        /* Display controller expects this flag to be set for each VENC,
           Based on this flag, it disabled venc/overlay. */
        pDctrlCfg->vencInfo.modeInfo[vencCntr].isVencRunning = TRUE;
    }

    /*
     * Configurations which are NOT vencID specific
     */
    pDctrlCfg->vencInfo.numVencs  = pConfigParams->numVencs;
    pDctrlCfg->vencInfo.tiedVencs = pConfigParams->tiedVencs;

    /*
     * Num of edges get accumulated over all Venc paths
     */
    pDctrlCfg->numEdges = edgeCntr;
    pDctrlCfg->useCase  = VPS_DCTRL_USERSETTINGS;

    retVal = Fvid2_control(pObj->fvidHandleDisplayCtrl,
                           IOCTL_VPS_DCTRL_CLEAR_CONFIG,
                           pDctrlCfg,
                           NULL);
    UTILS_assert(retVal == SYSTEM_LINK_STATUS_SOK);

#ifdef SYSTEM_DEBUG_DISPLAYCTRL
    Vps_printf(" DISPLAYCTRL: Clear config Done !!!\n");
#endif

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Set overlay parameters
 *
 *        Function that implements driver calls for link command
 *        DISPLAYCTRL_LINK_CMD_SET_OVLY_PARAMS
 *
 *        This function performs following for one Venc
 *        - Setting of Overlay parameters via IOCTL_VPS_DCTRL_SET_OVLY_PARAMS
 *          driver command.
 *
 * \param  pObj          [IN] Display ctrl Object Handle
 * \param  pOvlyParams   [IN] Handle to link interface of Overlay params
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 DisplayCtrlLink_drvSetOvlyParams(DisplayCtrlLink_Obj        * pObj,
                                       const DisplayCtrlLink_OvlyParams *pOvlyParams)
{
    Int32 retVal, status = SYSTEM_LINK_STATUS_SOK;
    Vps_DssDispcOvlyPanelConfig panelCfg, *pPanelCfg;

    pPanelCfg = &panelCfg;

#ifdef SYSTEM_DEBUG_DISPLAYCTRL
    Vps_printf(" DISPLAYCTRL: Set overlay params in progress !!!\n");
#endif

    if(Bsp_platformIsTda3xxFamilyBuild())
    {
        if((pOvlyParams->vencId==SYSTEM_DCTRL_DSS_VENC_LCD2)
            ||
           (pOvlyParams->vencId==SYSTEM_DCTRL_DSS_VENC_LCD3)
            ||
           (pOvlyParams->vencId==SYSTEM_DCTRL_DSS_VENC_HDMI)
            ||
           (pOvlyParams->vencId==SYSTEM_DCTRL_DSS_VENC_SDTV))
        {
            Vps_printf(" DISPLAYCTRL: DSS_VENC_LCD2/LCD3/HDMI NOT supported on TDA3xx"
                       " !!!\n"
                       );

            status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
        }
    }

    if(status==SYSTEM_LINK_STATUS_SOK)
    {
        pPanelCfg->vencId              = pOvlyParams->vencId;
        pPanelCfg->colorKeyEnable      = pOvlyParams->colorKeyEnable;
        pPanelCfg->colorKeySel         = pOvlyParams->colorKeySel;
        pPanelCfg->deltaLinesPerPanel  = pOvlyParams->deltaLinesPerPanel;
        pPanelCfg->transColorKey       = pOvlyParams->transColorKey;
        pPanelCfg->backGroundColor     = pOvlyParams->backGroundColor;
        pPanelCfg->alphaBlenderEnable  = pOvlyParams->alphaBlenderEnable;
        pPanelCfg->ovlyOptimization    = pOvlyParams->ovlyOptimization;

        retVal = Fvid2_control(pObj->fvidHandleDisplayCtrl,
                               IOCTL_VPS_DCTRL_SET_OVLY_PARAMS,
                               pPanelCfg,
                               NULL);
        UTILS_assert(retVal == SYSTEM_LINK_STATUS_SOK);
    }
#ifdef SYSTEM_DEBUG_DISPLAYCTRL
    Vps_printf(" DISPLAYCTRL: Set overlay params Done !!!\n");
#endif

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Set overlay pipeline parameters
 *
 *        Function that implements driver calls for link command
 *        DISPLAYCTRL_LINK_CMD_SET_OVLY_PIPELINE_PARAMS
 *
 *        This function performs following for one pipeline
 *        - Setting of Overlay parameters via
 *          IOCTL_VPS_DCTRL_SET_PIPELINE_PARAMS driver command.
 *
 * \param  pObj              [IN] Display ctrl Object Handle
 * \param  pOvlyPipeParams   [IN] Handle to link interface of Overlaypipe params
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 DisplayCtrlLink_drvSetOvlyPipelineParams(
          DisplayCtrlLink_Obj            *pObj,
          const DisplayCtrlLink_OvlyPipeParams *pOvlyPipeParams)
{
    Int32                      retVal;
    Vps_DssDispcOvlyPipeConfig ovlpipecfg, *pOvlpipecfg;

    Int32 status = SYSTEM_LINK_STATUS_SOK;
    pOvlpipecfg  = &ovlpipecfg;

#ifdef SYSTEM_DEBUG_DISPLAYCTRL
    Vps_printf(" DISPLAYCTRL: Set overlay pipeline params in progress !!!\n");
#endif

    if(Bsp_platformIsTda3xxFamilyBuild())
    {
        if(pOvlpipecfg->pipeLine==SYSTEM_DSS_DISPC_PIPE_VID3
            )
        {
            Vps_printf(" DISPLAYCTRL: DSS_VID3_PIPE NOT supported on TDA3xx"
                       " !!!\n"
                       );

            status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
        }
    }

    if(status==SYSTEM_LINK_STATUS_SOK)
    {
        pOvlpipecfg->pipeLine         = pOvlyPipeParams->pipeLine;
        pOvlpipecfg->zorder           = pOvlyPipeParams->zorder;
        pOvlpipecfg->zorderEnable     = pOvlyPipeParams->zorderEnable;
        pOvlpipecfg->globalAlpha      = pOvlyPipeParams->globalAlpha;
        pOvlpipecfg->preMultiplyAlpha = pOvlyPipeParams->preMultiplyAlpha;

        retVal = Fvid2_control(pObj->fvidHandleDisplayCtrl,
                               IOCTL_VPS_DCTRL_SET_PIPELINE_PARAMS,
                               pOvlpipecfg,
                               NULL);
        UTILS_assert(retVal == SYSTEM_LINK_STATUS_SOK);
    }
#ifdef SYSTEM_DEBUG_DISPLAYCTRL
    Vps_printf(" DISPLAYCTRL: Set overlay pipeline params Done !!!\n");
#endif

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Print status of Display Controller link
 *
 * \param  pObj              [IN] Display ctrl Object Handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 DisplayCtrlLink_drvPrintStatus(DisplayCtrlLink_Obj * pObj)
{
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Flip HDMI P/N Order
 *
 *        Function that implements driver calls for command
 *        DISPLAYCTRL_LINK_CMD_HDMI_FLIP_DATA_P_N_ORDER.
 *
 * \param  pObj          [IN] Display ctrl Object Handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 DisplayCtrlLink_drvHdmiFlipDataPNOrder(DisplayCtrlLink_Obj *pObj)
{
    Int32 status   = SYSTEM_LINK_STATUS_SOK;

#ifdef SYSTEM_DEBUG_DISPLAYCTRL
    Vps_printf(" DISPLAYCTRL: HDMI Flip Data P/N Order in progress !!!\n");
#endif

    status = Fvid2_control(pObj->fvidHandleDisplayCtrl,
                           IOCTL_VPS_DCTRL_HDMI_FLIP_DATA_P_N_ORDER,
                           NULL,
                           NULL);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

#ifdef SYSTEM_DEBUG_DISPLAYCTRL
    Vps_printf(" DISPLAYCTRL: HDMI Flip Data P/N Order Done !!!\n");
#endif

    return status;
}
