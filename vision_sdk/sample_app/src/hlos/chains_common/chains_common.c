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
 * \file chains_common.c
 *
 * \brief  Board specific initializations through APP_CTRL link.
 *
 *         All peripherals thats are controlled from IPU like video sensors, d
 *         displays etc are controlled from A15 through APP_CTRL link commands
 *
 * \version 0.0 (Jun 2014) : [YM] First version implemented.
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include <src/hlos/chains_common/chains_common.h>
#include <include/link_stats_monitor.h>

#define MAX_INPUT_STR_SIZE        (80)


/**
 *******************************************************************************
 *
 *  \brief  Common information related to all use-case
 *
 *******************************************************************************
*/
typedef struct {

    UInt32  displayCtrlLinkId;

    DisplayCtrlLink_ConfigParams    dctrlCfgPrms;
    DisplayCtrlLink_OvlyPipeParams  pipeParams[4];
    DisplayCtrlLink_OvlyParams      ovlyParams;
} Chains_CommonObj;

Chains_CommonObj gChains_commonObj;

static Int32 int_power(Int32 base, Int32 exp)
{
    Int32 result = 1;
    while (exp)
    {
        if (exp & 1)
        {
            result *= base;
        }
        exp /= 2;
        base *= base;
    }
    return result;
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
char Chains_readChar()
{
    Int8 ch[80];

    fflush(stdin);
    fgets((char*)ch, MAX_INPUT_STR_SIZE, stdin);
    if(ch[1] != '\n' || ch[0] == '\n')
    ch[0] = '\n';

    return ch[0];
}

/**
 *******************************************************************************
 *
 * \brief   Read an integer from UART or CCS console
 *
 * \return character that is read
 *
 *******************************************************************************
*/
Int32 Chains_readInt()
{
    Int8 ch[80];
    Int32 retVal = 0;
    UInt16 digits = 0, i;

    fflush(stdin);
    fgets((char*)ch, MAX_INPUT_STR_SIZE, stdin);

    /* Checking escape value ? */
    if ((69 == ch[0]) || (101 == ch[0]))
    {
        retVal = -1;
    }

    for (i = 0; i < 80; i++)
    {
        if (10 == ch[i])
        {
            digits = i;
            break;
        }
    }

    if (45 == ch[0])
    {
        for (i = 1; i < digits; i++)
        {
            /* Check to see if value is a number */
            if ((ch[i] > 57) || (ch[i] < 48))
            {
                retVal = 0;
                break;
            }
            else
            {
                retVal = retVal + (ch[i]-48)*int_power(10, digits-i-1);
            }
        }
        retVal = -1*retVal;
    }
    else
    {
        for (i = 0; i < digits; i++)
        {
            if ((ch[i] > 57) || (ch[i] < 48))
            {
                retVal = 0;
                break;
            }
            else
            {
                retVal = retVal + (ch[i]-48)*int_power(10, digits-i-1);
            }
        }
    }

    return retVal;
}

/**
 *******************************************************************************
 *
 * \brief   Initializes / starts peripherals remotely with APP_CTRL commands
 *
 *
 *******************************************************************************
 */
Int32 ChainsCommon_appCtrlCommonInit()
{

    Int32 status = SYSTEM_LINK_STATUS_SOK;

    status = System_linkControl(SYSTEM_LINK_ID_APP_CTRL,
                                APP_CTRL_LINK_CMD_SET_DMM_PRIORITIES,
                                NULL,
                                0,
                                TRUE);
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = System_linkControl(SYSTEM_LINK_ID_APP_CTRL,
                                APP_CTRL_LINK_CMD_STAT_COLLECTOR_INIT,
                                NULL,
                                0,
                                TRUE);
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    return status;
}

/**
 *******************************************************************************
 *
 * \brief   DeInitializes and stops peripheral remotely with APP_CTRL commands
 *
 *
 *******************************************************************************
 */
Int32 ChainsCommon_appCtrlCommonDeInit()
{

    Int32 status = SYSTEM_LINK_STATUS_SOK;

    status = System_linkControl(SYSTEM_LINK_ID_APP_CTRL,
                                APP_CTRL_LINK_CMD_STAT_COLLECTOR_DEINIT,
                                NULL,
                                0,
                                TRUE);
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    return status;
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

    ChainsCommon_statCollectorPrint();
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
Int32 ChainsCommon_prfLoadCalcEnable(Bool enable, Bool printStatus, Bool printTskLoad)
{
    UInt32 procId, linkId;


    for(procId=0; procId<SYSTEM_PROC_MAX; procId++)
    {
        if(    System_isProcEnabled(procId)==FALSE
            || procId == System_getSelfProcId()
           )
        {
            continue;
        }

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
                OSA_waitMsecs(100);
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
Int32 ChainsCommon_prfCpuLoadPrint()
{
    UInt32 procId, linkId;
    SystemCommon_PrintStatus printStatus;

    memset(&printStatus, 0, sizeof(printStatus));

    printStatus.printCpuLoad = TRUE;
    printStatus.printTskLoad = TRUE;

    for(procId=0; procId<SYSTEM_PROC_MAX; procId++)
    {
        if(    System_isProcEnabled(procId)==FALSE
            || procId == System_getSelfProcId()
           )
        {
            continue;
        }

        linkId = SYSTEM_MAKE_LINK_ID(procId, SYSTEM_LINK_ID_PROCK_LINK_ID);

        System_linkControl(
            linkId,
            SYSTEM_COMMON_CMD_PRINT_STATUS,
            &printStatus,
            sizeof(printStatus),
            TRUE
        );
        OSA_waitMsecs(100);
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
Int32 ChainsCommon_memPrintHeapStatus()
{
    UInt32 procId, linkId;
    SystemCommon_PrintStatus printStatus;

    memset(&printStatus, 0, sizeof(printStatus));

    printStatus.printHeapStatus = TRUE;

    for(procId=0; procId<SYSTEM_PROC_MAX; procId++)
    {
        if(    System_isProcEnabled(procId)==FALSE
            || procId == System_getSelfProcId()
           )
        {
            continue;
        }

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
 * \brief   This function Print the statCollector output
 *          SYSTEM_COMMON_CMD_PRINT_STAT_COLL send to only IPU1_0 core.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 ChainsCommon_statCollectorPrint()
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
        OSA_waitMsecs(100);
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief   This function Reset the statCollector registers
 *          SYSTEM_COMMON_CMD_RESET_STAT_COLL send to only IPU1_0 core.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 ChainsCommon_statCollectorReset()
{
    UInt32 linkId;

    linkId = IPU1_0_LINK(SYSTEM_LINK_ID_PROCK_LINK_ID);

        System_linkControl(
            linkId,
            SYSTEM_COMMON_CMD_RESET_STAT_COLL,
            NULL,
            0,
            TRUE
        );
        OSA_waitMsecs(100);
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief   Show CPU status from remote CPUs
 *
 *******************************************************************************
 */
void ChainsCommon_printCpuStatus()
{
    if(System_isProcEnabled(SYSTEM_IPU_PROC_PRIMARY))
    {
        System_linkControl(
            SYSTEM_LINK_ID_IPU1_0,
            SYSTEM_COMMON_CMD_CORE_STATUS,
            NULL,
            0,
            TRUE
        );
    }
    if(System_isProcEnabled(SYSTEM_PROC_DSP1))
    {
        System_linkControl(
            SYSTEM_LINK_ID_DSP1,
            SYSTEM_COMMON_CMD_CORE_STATUS,
            NULL,
            0,
            TRUE
        );
    }
    if(System_isProcEnabled(SYSTEM_PROC_DSP2))
    {
        System_linkControl(
            SYSTEM_LINK_ID_DSP2,
            SYSTEM_COMMON_CMD_CORE_STATUS,
            NULL,
            0,
            TRUE
        );
    }
    if(System_isProcEnabled(SYSTEM_PROC_EVE1))
    {
        System_linkControl(
            SYSTEM_LINK_ID_EVE1,
            SYSTEM_COMMON_CMD_CORE_STATUS,
            NULL,
            0,
            TRUE
        );
    }
    if(System_isProcEnabled(SYSTEM_PROC_EVE2))
    {
        System_linkControl(
            SYSTEM_LINK_ID_EVE2,
            SYSTEM_COMMON_CMD_CORE_STATUS,
            NULL,
            0,
            TRUE
        );
    }
    if(System_isProcEnabled(SYSTEM_PROC_EVE3))
    {
        System_linkControl(
            SYSTEM_LINK_ID_EVE3,
            SYSTEM_COMMON_CMD_CORE_STATUS,
            NULL,
            0,
            TRUE
        );
    }
    if(System_isProcEnabled(SYSTEM_PROC_EVE4))
    {
        System_linkControl(
            SYSTEM_LINK_ID_EVE4,
            SYSTEM_COMMON_CMD_CORE_STATUS,
            NULL,
            0,
            TRUE
        );
    }
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
        default:
            OSA_assert(0);
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
       displayType == CHAINS_DISPLAY_TYPE_HDMI_1080P)
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
        ovlyPrms->vencId = pVInfo->vencId;
    }
    else
    {
        OSA_assert(0);
    }

    if(displayType == CHAINS_DISPLAY_TYPE_HDMI_720P)
    {
        pVInfo->mInfo.standard = SYSTEM_STD_720P_60;

    }
    else if (displayType == CHAINS_DISPLAY_TYPE_HDMI_1080P)
    {
        pVInfo->mInfo.standard = SYSTEM_STD_1080P_60;
    }

    /* TODO Dont know what to set here */
    pVInfo->mode = 0;
    pVInfo->isInputPipeConnected[0] = TRUE;
    pVInfo->isInputPipeConnected[1] = TRUE;
    pVInfo->isInputPipeConnected[2] = TRUE;
    pVInfo->isInputPipeConnected[3] = TRUE;
    pVInfo->writeBackEnabledFlag = FALSE;


    /* Setting other overlay parameters common to both Venc */
    ovlyPrms->deltaLinesPerPanel   = 0;
    ovlyPrms->alphaBlenderEnable   = 0;
    ovlyPrms->backGroundColor      = 0x0;
    ovlyPrms->colorKeyEnable       = 1;
    ovlyPrms->colorKeySel          = SYSTEM_DSS_DISPC_TRANS_COLOR_KEY_SRC;
    ovlyPrms->ovlyOptimization     = SYSTEM_DSS_DISPC_OVLY_FETCH_ALLDATA;
    ovlyPrms->transColorKey        = 0x0000;    /* DRAW2D_TRANSPARENT_COLOR; */

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

    pipeOvlyPrms[2].pipeLine = SYSTEM_DSS_DISPC_PIPE_VID3;
    pipeOvlyPrms[2].globalAlpha = 0xFF;
    pipeOvlyPrms[2].preMultiplyAlpha = 0;
    pipeOvlyPrms[2].zorderEnable = TRUE;
    pipeOvlyPrms[2].zorder = SYSTEM_DSS_DISPC_ZORDER2;

    pipeOvlyPrms[3].pipeLine = SYSTEM_DSS_DISPC_PIPE_GFX1;
    pipeOvlyPrms[3].globalAlpha = 0xFF;
    pipeOvlyPrms[3].preMultiplyAlpha = 0;
    pipeOvlyPrms[3].zorderEnable = TRUE;
    pipeOvlyPrms[3].zorder = SYSTEM_DSS_DISPC_ZORDER3;
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
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = System_linkControl(gChains_commonObj.displayCtrlLinkId,
                                DISPLAYCTRL_LINK_CMD_SET_OVLY_PARAMS,
                                &gChains_commonObj.ovlyParams,
                                sizeof(DisplayCtrlLink_OvlyParams),
                                TRUE);
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = System_linkControl(gChains_commonObj.displayCtrlLinkId,
                                DISPLAYCTRL_LINK_CMD_SET_OVLY_PIPELINE_PARAMS,
                                &gChains_commonObj.pipeParams[0],
                                sizeof(DisplayCtrlLink_OvlyPipeParams),
                                TRUE);
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = System_linkControl(gChains_commonObj.displayCtrlLinkId,
                                DISPLAYCTRL_LINK_CMD_SET_OVLY_PIPELINE_PARAMS,
                                &gChains_commonObj.pipeParams[1],
                                sizeof(DisplayCtrlLink_OvlyPipeParams),
                                TRUE);
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = System_linkControl(gChains_commonObj.displayCtrlLinkId,
                            DISPLAYCTRL_LINK_CMD_SET_OVLY_PIPELINE_PARAMS,
                            &gChains_commonObj.pipeParams[2],
                            sizeof(DisplayCtrlLink_OvlyPipeParams),
                            TRUE);
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = System_linkControl(gChains_commonObj.displayCtrlLinkId,
                                DISPLAYCTRL_LINK_CMD_SET_OVLY_PIPELINE_PARAMS,
                                &gChains_commonObj.pipeParams[3],
                                sizeof(DisplayCtrlLink_OvlyPipeParams),
                                TRUE);
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

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
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = System_linkDelete(gChains_commonObj.displayCtrlLinkId);
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    return status;
}

