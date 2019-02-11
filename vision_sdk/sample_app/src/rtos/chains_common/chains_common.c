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

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <system_cfg.h>
#include <src/rtos/chains_common/chains.h>
#include <src/rtos/utils_common/include/utils_stat_collector.h>
#include <include/link_stats_monitor.h>

Chains_CommonObj gChains_commonObj;

/**
 *******************************************************************************
 *
 * \brief   Set L3/DMM priority related registers
 *
 *******************************************************************************
*/
Void ChainsCommon_SetSystemL3DmmPri()
{
    /* Assert Mflag of DSS to give DSS highest priority */
    Utils_setDssMflagMode(UTILS_DSS_MFLAG_MODE_FORCE_ENABLE);

    /* enable usage of Mflag at DMM */
    Utils_setDmmMflagEmergencyEnable(TRUE);

    /* Set DMM as higest priority at DMM and EMIF */
    Utils_setDmmPri(UTILS_DMM_INITIATOR_ID_DSS, 0);
}

/**
 *******************************************************************************
 *
 * \brief   This function Print the statCollector output
 *          SYSTEM_COMMON_CMD_PRINT_STAT_COLL send to only IPU1_0 core.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 Chains_statCollectorPrint()
{
    UInt32 linkId;

    linkId = IPU1_0_LINK(SYSTEM_LINK_ID_PROCK_LINK_ID);

        System_linkControl(
            linkId,
            SYSTEM_COMMON_CMD_PRINT_STAT_COLL,
            NULL,
            0,
            TRUE
        );
        Task_sleep(100);


    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief   Print Statistics
 *
 *******************************************************************************
*/
Void ChainsCommon_PrintStatistics()
{
    System_linkControl(
        SYSTEM_LINK_ID_IPU1_0,
        SYSTEM_LINK_CMD_PRINT_CORE_PRF_LOAD,
        NULL,
        0,
        TRUE);

    Utils_prcmPrintAllVDTempValues();
    Utils_prcmPrintPowerConsumption();
    Chains_statCollectorPrint();
}

/**
 *******************************************************************************
 * \brief Max Size of the input string in characters.
 *******************************************************************************
 */
#define MAX_INPUT_STR_SIZE  (80)

/**
 *******************************************************************************
 *
 * \brief   Read a charater from UART or CCS console
 *
 * \return character that is read
 *
 *******************************************************************************
*/
char ChainsCommon_readChar()
{
    #if (defined(ENABLE_UART_LOG) || (defined(ENABLE_CCS_LOG)))
    Int8 ch[80];
    #endif

    #ifdef ENABLE_UART_LOG
    uartRead(ch);
    #endif
    #ifdef ENABLE_CCS_LOG
    fgets((char*)ch, MAX_INPUT_STR_SIZE, stdin);
    if(ch[1] != '\n' || ch[0] == '\n')
    ch[0] = '\n';
    #endif

    #if (defined(ENABLE_UART_LOG) || (defined(ENABLE_CCS_LOG)))
    return ch[0];
    #endif
}


/**
 *******************************************************************************
 *
 * \brief   Load Calculation enable/disable
 *
 *          This functions enables load profiling. A control command
 *          SYSTEM_COMMON_CMD_CPU_LOAD_CALC_START is passed to chianed links.
 *          If parameter Enable is set true Load profiling is enabled.
 *          If printStatus is set true a System CMD to Print CPU load,
 *          Task Laod and Heap status information is sent
 *          While creating enable = TRUE , printStatus & printTskLoad = FALSE
 *          While deleting enable = FALSE , printStatus & printTskLoad = TRUE
 *
 * \param   enable               [IN]   is set true Load profiling
 *
 * \param   printStatus          [IN] true a System CMD
 *
 * \param   printTskLoad         [IN]  true a Print CPU load
 *
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 Chains_prfLoadCalcEnable(Bool enable, Bool printStatus, Bool printTskLoad)
{
    UInt32 procId, linkId;


    for(procId=0; procId<SYSTEM_PROC_MAX; procId++)
    {
        if(System_isProcEnabled(procId)==FALSE)
            continue;

        linkId = SYSTEM_MAKE_LINK_ID(procId, SYSTEM_LINK_ID_PROCK_LINK_ID);

        if(enable)
        {
            System_linkControl(
                linkId,
                SYSTEM_COMMON_CMD_CPU_LOAD_CALC_START,
                NULL,
                0,
                TRUE
            );
        }
        else
        {
            System_linkControl(
                linkId,
                SYSTEM_COMMON_CMD_CPU_LOAD_CALC_STOP,
                NULL,
                0,
                TRUE
            );
            if(printStatus)
            {
                SystemCommon_PrintStatus printStatus;

                memset(&printStatus, 0, sizeof(printStatus));

                printStatus.printCpuLoad = TRUE;
                printStatus.printTskLoad = printTskLoad;
                System_linkControl(
                    linkId,
                    SYSTEM_COMMON_CMD_PRINT_STATUS,
                    &printStatus,
                    sizeof(printStatus),
                    TRUE
                );
                Task_sleep(100);
            }
            System_linkControl(
                linkId,
                SYSTEM_COMMON_CMD_CPU_LOAD_CALC_RESET,
                NULL,
                0,
                TRUE
            );
        }
    }
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief   Print Load Calculation.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 Chains_prfCpuLoadPrint()
{
    UInt32 procId, linkId;
    SystemCommon_PrintStatus printStatus;

    memset(&printStatus, 0, sizeof(printStatus));

    printStatus.printCpuLoad = TRUE;
    printStatus.printTskLoad = TRUE;

    for(procId=0; procId<SYSTEM_PROC_MAX; procId++)
    {
        if(System_isProcEnabled(procId)==FALSE)
            continue;

        linkId = SYSTEM_MAKE_LINK_ID(procId, SYSTEM_LINK_ID_PROCK_LINK_ID);

        System_linkControl(
            linkId,
            SYSTEM_COMMON_CMD_PRINT_STATUS,
            &printStatus,
            sizeof(printStatus),
            TRUE
        );
        Task_sleep(100);
    }
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief   Print Memory Heap Statistics
 *
 *          This function send a system control message
 *          SYSTEM_COMMON_CMD_CPU_LOAD_CALC_START to all cores.
 *
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 Chains_memPrintHeapStatus()
{
    UInt32 procId, linkId;
    SystemCommon_PrintStatus printStatus;

    memset(&printStatus, 0, sizeof(printStatus));

    printStatus.printHeapStatus = TRUE;

    for(procId=0; procId<SYSTEM_PROC_MAX; procId++)
    {
        if(System_isProcEnabled(procId)==FALSE)
            continue;

        linkId = SYSTEM_MAKE_LINK_ID(procId, SYSTEM_LINK_ID_PROCK_LINK_ID);

        System_linkControl(
                linkId,
                SYSTEM_COMMON_CMD_PRINT_STATUS,
                &printStatus,
                sizeof(printStatus),
                TRUE
            );
    }
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief   Read a charater from UART or CCS console
 *
 * \return character that is read
 *
 *******************************************************************************
*/
Void ChainsCommon_Init()
{
#if A15_TARGET_OS_BIOS
    Board_init();
#endif

#ifdef ENABLE_UART_LOG
    System_uartInit();

    /* let the pending prints from other processor's finish */
    if(!System_isFastBootEnabled() &&
       !System_isSrvFastBootEnabled())
    {
        Task_sleep(1000);
    }
#endif
    Utils_prcmClockRateInit();
    Utils_prcmPrintPowerConsumptionInit();

    if(!System_isFastBootEnabled() &&
       !System_isSrvFastBootEnabled())
    {
        System_qspiInit();
    }

    ChainsCommon_SetSystemL3DmmPri();
    Utils_statCollectorInit(); /* Initializing the statCollector */
    Chains_linkStatsMonitorInit();

}

/**
 *******************************************************************************
 *
 * \brief   Do common system init
 *
 *******************************************************************************
*/
Void ChainsCommon_DeInit()
{
#if A15_TARGET_OS_BIOS
    Board_deInit();
#endif
    Chains_linkStatsMonitorDeInit();
}

/**
 *******************************************************************************
 *
 * \brief   Return W x H of a given display type
 *
 *******************************************************************************
*/
Void ChainsCommon_GetDisplayWidthHeight(
                    Chains_DisplayType displayType,
                    UInt32 *displayWidth,
                    UInt32 *displayHeight)
{
    switch(displayType)
    {
        case CHAINS_DISPLAY_TYPE_HDMI_720P:
            *displayWidth = 1280;
            *displayHeight = 720;
            break;
        case CHAINS_DISPLAY_TYPE_HDMI_1080P:
            *displayWidth = 1920;
            *displayHeight = 1080;
            break;
        case CHAINS_DISPLAY_TYPE_HDMI_XGA_TDM:
            *displayWidth = 1024;
            *displayHeight = 768;
            break;
        case CHAINS_DISPLAY_TYPE_HDMI_WXGA:
            *displayWidth = 1280;
            *displayHeight = 800;
            break;
        default:
            UTILS_assert(0);
            break;
    }
}

/**
 *******************************************************************************
 *
 * \brief   Set Display Controller Create Parameters
 *
 * \param   pPrm         [IN]    DisplayCtrlLink_ConfigParams
 *
 *******************************************************************************
*/
static Void ChainsCommon_SetDctrlConfig(
                                DisplayCtrlLink_ConfigParams *pPrm,
                                DisplayCtrlLink_OvlyParams *ovlyPrms,
                                DisplayCtrlLink_OvlyPipeParams *pipeOvlyPrms,
                                UInt32 displayType,
                                UInt32 displayWidth,
                                UInt32 displayHeight)
{
    DisplayCtrlLink_VencInfo *pVInfo;

    pPrm->numVencs = 1;
    pPrm->tiedVencs = 0;

    pVInfo = &pPrm->vencInfo[0];

    pVInfo->tdmMode = DISPLAYCTRL_LINK_TDM_DISABLE;

    if(displayType == CHAINS_DISPLAY_TYPE_HDMI_720P ||
       displayType == CHAINS_DISPLAY_TYPE_HDMI_1080P ||
       displayType == CHAINS_DISPLAY_TYPE_HDMI_WXGA)
    {
        pPrm->deviceId = DISPLAYCTRL_LINK_USE_HDMI;
        pVInfo->vencId = SYSTEM_DCTRL_DSS_VENC_HDMI;
        pVInfo->outputPort = SYSTEM_DCTRL_DSS_HDMI_OUTPUT;
        pVInfo->vencOutputInfo.vsPolarity = SYSTEM_DCTRL_POLARITY_ACT_HIGH;
        pVInfo->vencOutputInfo.hsPolarity = SYSTEM_DCTRL_POLARITY_ACT_HIGH;

        /* Below are of dont care for EVM LCD */
        pVInfo->vencOutputInfo.fidPolarity = SYSTEM_DCTRL_POLARITY_ACT_LOW;
        pVInfo->vencOutputInfo.actVidPolarity = SYSTEM_DCTRL_POLARITY_ACT_HIGH;

        pVInfo->vencOutputInfo.dataFormat = SYSTEM_DF_RGB24_888;
        pVInfo->vencOutputInfo.dvoFormat = SYSTEM_DCTRL_DVOFMT_GENERIC_DISCSYNC;
        pVInfo->vencOutputInfo.videoIfWidth = SYSTEM_VIFW_24BIT;

        pVInfo->vencOutputInfo.pixelClkPolarity = SYSTEM_DCTRL_POLARITY_ACT_HIGH;
        pVInfo->vencOutputInfo.aFmt = SYSTEM_DCTRL_A_OUTPUT_MAX;

        /* Configure overlay params */
        ovlyPrms->vencId = SYSTEM_DCTRL_DSS_VENC_HDMI;
    }

    if(displayType == CHAINS_DISPLAY_TYPE_HDMI_720P)
    {
        pVInfo->mInfo.standard = SYSTEM_STD_720P_60;
    }
    else if (displayType == CHAINS_DISPLAY_TYPE_HDMI_1080P)
    {
        pVInfo->mInfo.standard = SYSTEM_STD_1080P_60;
    }
    else if(displayType == CHAINS_DISPLAY_TYPE_HDMI_WXGA)
    {
        pVInfo->mInfo.standard = SYSTEM_STD_WXGA_60;
    }

    /* TODO Dont know what to set here */
    pVInfo->mode = 0;
    pVInfo->isInputPipeConnected[0] = TRUE;
    pVInfo->isInputPipeConnected[1] = TRUE;
    if(Bsp_platformIsTda2xxFamilyBuild())
    {
        pVInfo->isInputPipeConnected[2] = TRUE;
    }
    else
    {
        pVInfo->isInputPipeConnected[2] = FALSE;
    }

    pVInfo->isInputPipeConnected[3] = TRUE;
    pVInfo->writeBackEnabledFlag = FALSE;

    /* Setting other overlay parameters common to both Venc */
    ovlyPrms->deltaLinesPerPanel   = 0;
    ovlyPrms->alphaBlenderEnable   = 0;
    ovlyPrms->backGroundColor      = 0x0;
    ovlyPrms->colorKeyEnable       = 1;
    ovlyPrms->colorKeySel          = SYSTEM_DSS_DISPC_TRANS_COLOR_KEY_SRC;
#ifdef ROBUST_RVC_INCLUDE
    ovlyPrms->ovlyOptimization     = SYSTEM_DSS_DISPC_OVLY_FETCH_OPTIMIZED;
#else
    ovlyPrms->ovlyOptimization     = SYSTEM_DSS_DISPC_OVLY_FETCH_ALLDATA;
#endif
    ovlyPrms->transColorKey        = 0x0000;    /* DRAW2D_TRANSPARENT_COLOR */

    /* Setting overlay pipe parameters */
    pipeOvlyPrms[0].pipeLine = SYSTEM_DSS_DISPC_PIPE_VID1;
    pipeOvlyPrms[0].globalAlpha = 0xFF;
    pipeOvlyPrms[0].preMultiplyAlpha = 0;
    pipeOvlyPrms[0].zorderEnable = TRUE;
    pipeOvlyPrms[0].zorder = SYSTEM_DSS_DISPC_ZORDER0;

    pipeOvlyPrms[1].pipeLine = SYSTEM_DSS_DISPC_PIPE_VID2;
    pipeOvlyPrms[1].globalAlpha = 0xFF;
    pipeOvlyPrms[1].preMultiplyAlpha = 0;
    pipeOvlyPrms[1].zorderEnable = TRUE;
    pipeOvlyPrms[1].zorder = SYSTEM_DSS_DISPC_ZORDER1;

    if(Bsp_platformIsTda2xxFamilyBuild())
    {
        pipeOvlyPrms[2].pipeLine = SYSTEM_DSS_DISPC_PIPE_VID3;
        pipeOvlyPrms[2].globalAlpha = 0xFF;
        pipeOvlyPrms[2].preMultiplyAlpha = 0;
        pipeOvlyPrms[2].zorderEnable = TRUE;
        pipeOvlyPrms[2].zorder = SYSTEM_DSS_DISPC_ZORDER2;
    }

    pipeOvlyPrms[3].pipeLine = SYSTEM_DSS_DISPC_PIPE_GFX1;
    pipeOvlyPrms[3].globalAlpha = 0xFF;
    pipeOvlyPrms[3].preMultiplyAlpha = 0;
    pipeOvlyPrms[3].zorderEnable = TRUE;
    pipeOvlyPrms[3].zorder = SYSTEM_DSS_DISPC_ZORDER3;

    if(Bsp_platformIsTda3xxFamilyBuild())
    {
        pipeOvlyPrms[3].zorder = SYSTEM_DSS_DISPC_ZORDER2;
    }
}

/**
 *******************************************************************************
 *
 * \brief   Configure and start display controller
 *
 *******************************************************************************
*/
Int32 ChainsCommon_StartDisplayCtrl(
                                UInt32 displayType,
                                UInt32 displayWidth,
                                UInt32 displayHeight)
{
    Int32 status=0;

    gChains_commonObj.displayCtrlLinkId = SYSTEM_LINK_ID_DISPLAYCTRL;

    ChainsCommon_SetDctrlConfig(
            &gChains_commonObj.dctrlCfgPrms,
            &gChains_commonObj.ovlyParams,
            &gChains_commonObj.pipeParams[0],
            displayType,
            displayWidth,
            displayHeight);

    /* There are no createtime Params for display controller */
    status = System_linkCreate(gChains_commonObj.displayCtrlLinkId,
                                NULL,
                                0);

    status = System_linkControl(gChains_commonObj.displayCtrlLinkId,
                                DISPLAYCTRL_LINK_CMD_SET_CONFIG,
                                &gChains_commonObj.dctrlCfgPrms,
                                sizeof(DisplayCtrlLink_ConfigParams),
                                TRUE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = System_linkControl(gChains_commonObj.displayCtrlLinkId,
                                DISPLAYCTRL_LINK_CMD_SET_OVLY_PARAMS,
                                &gChains_commonObj.ovlyParams,
                                sizeof(DisplayCtrlLink_OvlyParams),
                                TRUE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = System_linkControl(gChains_commonObj.displayCtrlLinkId,
                                DISPLAYCTRL_LINK_CMD_SET_OVLY_PIPELINE_PARAMS,
                                &gChains_commonObj.pipeParams[0],
                                sizeof(DisplayCtrlLink_OvlyPipeParams),
                                TRUE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = System_linkControl(gChains_commonObj.displayCtrlLinkId,
                                DISPLAYCTRL_LINK_CMD_SET_OVLY_PIPELINE_PARAMS,
                                &gChains_commonObj.pipeParams[1],
                                sizeof(DisplayCtrlLink_OvlyPipeParams),
                                TRUE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    if(Bsp_platformIsTda2xxFamilyBuild())
    {
        status = System_linkControl(gChains_commonObj.displayCtrlLinkId,
                                DISPLAYCTRL_LINK_CMD_SET_OVLY_PIPELINE_PARAMS,
                                &gChains_commonObj.pipeParams[2],
                                sizeof(DisplayCtrlLink_OvlyPipeParams),
                                TRUE);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    status = System_linkControl(gChains_commonObj.displayCtrlLinkId,
                                DISPLAYCTRL_LINK_CMD_SET_OVLY_PIPELINE_PARAMS,
                                &gChains_commonObj.pipeParams[3],
                                sizeof(DisplayCtrlLink_OvlyPipeParams),
                                TRUE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);


    return status;
}

/**
 *******************************************************************************
 *
 * \brief   Stop and Delete display controller
 *
 *******************************************************************************
*/
Int32 ChainsCommon_StopDisplayCtrl()
{
    Int32 status=0;

    status = System_linkControl(gChains_commonObj.displayCtrlLinkId,
                                DISPLAYCTRL_LINK_CMD_CLR_CONFIG,
                                &gChains_commonObj.dctrlCfgPrms,
                                sizeof(DisplayCtrlLink_ConfigParams),
                                TRUE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = System_linkDelete(gChains_commonObj.displayCtrlLinkId);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    return status;
}

