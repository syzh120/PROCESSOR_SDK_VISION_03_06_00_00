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
#include "chains_fastBoot_issIspSimcop_pd_Display_priv.h"
#include "chains_fastBoot_dspEvePowerDown.h"
#include <src/include/chains_common.h>

/**
 *******************************************************************************
 *
 * \brief   Send commands to stop the CPU load calculation for IPU cores.
 *          This is done to have individual control on which CPU core's load
 *          can be enabled or disabled when DSP and EVEs are put to power down
 *          mode.
 *
 * \param   None
 *
 * \return  None
 *
 *******************************************************************************
*/
Void chains_fastBoot_stopIpuLoadCalculation(Void)
{
    UInt32 procId, linkId, i;
    UInt32 procIdArr[2U] = {SYSTEM_PROC_IPU1_0, SYSTEM_PROC_IPU1_1};
    /* Ensure that the CPU Load calculation for IPU is stopped */
    for (i = 0U; i < 2U; i++)
    {
        procId = procIdArr[i];
        if(System_isProcEnabled(procId))
        {
            linkId = linkId = SYSTEM_MAKE_LINK_ID(procId, SYSTEM_LINK_ID_PROCK_LINK_ID);
            System_linkControl(
                linkId,
                SYSTEM_COMMON_CMD_CPU_LOAD_CALC_STOP,
                NULL,
                0,
                TRUE
            );
            System_linkControl(
                linkId,
                SYSTEM_COMMON_CMD_CPU_LOAD_CALC_RESET,
                NULL,
                0,
                TRUE
            );
        }
    }
    return;
}

/**
 *******************************************************************************
 *
 * \brief   Send commands to stop the CPU load calculation for DSP & EVE cores.
 *          This is done to have individual control on which CPU core's load
 *          can be enabled or disabled when DSP and EVEs are put to power down
 *          mode.
 *
 * \param   None
 *
 * \return  None
 *
 *******************************************************************************
*/
Void chains_fastBoot_stopDspEveLoadCalculation(Void)
{
    UInt32 procId, linkId, i;
    UInt32 procIdArr[3U] = {SYSTEM_PROC_DSP1, SYSTEM_PROC_DSP2, SYSTEM_PROC_EVE1};
    for (i = 0U; i < 3U; i++)
    {
        procId = procIdArr[i];
        if(System_isProcEnabled(procId))
        {
            linkId = linkId = SYSTEM_MAKE_LINK_ID(procId, SYSTEM_LINK_ID_PROCK_LINK_ID);
            System_linkControl(
                linkId,
                SYSTEM_COMMON_CMD_CPU_LOAD_CALC_STOP,
                NULL,
                0,
                TRUE
            );
            System_linkControl(
                linkId,
                SYSTEM_COMMON_CMD_CPU_LOAD_CALC_RESET,
                NULL,
                0,
                TRUE
            );
        }
    }
    return;
}

/**
 *******************************************************************************
 *
 * \brief   Switch the DSP and EVE CPUs ON
 *
 *          Function first boots the DSP and EVE cores and then sends the IPC
 *          sync to the cores. The usecase is then created and started, gate
 *          links are switched on. Display link is switched to show analytics
 *          output.
 *
 * \param   pObj       [IN]   chains_fastBoot_issIspSimcop_pd_DisplayAppObj
 * \param   bootParams [IN]   Utils_BootSlaves_Params - To boot cores
 *
 *******************************************************************************
*/
Void chains_fastBoot_switchDspEveOn(chains_fastBoot_issIspSimcop_pd_DisplayAppObj *pObj,
                                              Utils_BootSlaves_Params *bootParams)
{
    DisplayLink_SwitchChannelParams displayPrm;
    UInt32 startTime, endTime, timeTaken;

    pObj->analyticsState = ANALYTICS_ON;
    startTime = Utils_getCurGlobalTimeInMsec();
    /* boot & sync other cores here */
    Utils_bootSlaves(bootParams);
    Utils_syncSlaves();

    /* create & start late usecase */
    chains_fastBoot_issIspSimcop_pd_Display_Create_UcLate(&pObj->ucObj, pObj);
    chains_fastBoot_issIspSimcop_pd_Display_StartApp_UcLate(pObj);
    /* Send command to toggle operation status */
    System_linkControl(
            pObj->ucObj.Gate_algFeatureComputeLinkID,
            GATE_LINK_CMD_SET_OPERATION_MODE_ON,
            NULL,
            0,
            TRUE);

    System_linkControl(
            pObj->ucObj.Gate_algCaptureLinkID,
            GATE_LINK_CMD_SET_OPERATION_MODE_ON,
            NULL,
            0,
            TRUE);

    System_linkControl(
            pObj->ucObj.Gate_algDrawLinkID,
            GATE_LINK_CMD_SET_OPERATION_MODE_ON,
            NULL,
            0,
            TRUE);

    displayPrm.activeChId = 1;

    System_linkControl(pObj->ucObj.Display_VideoLinkID,
                    DISPLAY_LINK_CMD_SWITCH_CH,
                    &displayPrm,
                    sizeof(displayPrm),
                    TRUE);
    endTime = Utils_getCurGlobalTimeInMsec();
    timeTaken = endTime - startTime;
    Vps_printf(" CHAINS: DSP and EVE power ON Time = %d ms\n", timeTaken);
}
/**
 *******************************************************************************
 *
 * \brief   Switch the DSP and EVE CPUs OFF
 *
 *          Function first switches off the gates, waits for the buffers to be
 *          release and then powers down the cores after detaching IPC. DSP and
 *          EVE applications are completely exitted before switching off the
 *          cores.
 *
 * \param   pObj       [IN]   chains_fastBoot_issIspSimcop_pd_DisplayAppObj
 *
 *******************************************************************************
*/
Void chains_fastBoot_switchDspEveOff(chains_fastBoot_issIspSimcop_pd_DisplayAppObj *pObj)
{
    DisplayLink_SwitchChannelParams displayPrm;
    UInt32 startTime, endTime, timeTaken;
    UInt32 numBuffersPending;

    startTime = Utils_getCurGlobalTimeInMsec();
    pObj->analyticsState = ANALYTICS_OFF;
    displayPrm.activeChId = 0;

    System_linkControl(pObj->ucObj.Display_VideoLinkID,
                    DISPLAY_LINK_CMD_SWITCH_CH,
                    &displayPrm,
                    sizeof(displayPrm),
                    TRUE);
    /* Send command to toggle operation status */
    System_linkControl(
            pObj->ucObj.Gate_algFeatureComputeLinkID,
            GATE_LINK_CMD_SET_OPERATION_MODE_OFF,
            NULL,
            0,
            TRUE);
    System_linkControl(
            pObj->ucObj.Gate_algCaptureLinkID,
            GATE_LINK_CMD_SET_OPERATION_MODE_OFF,
            NULL,
            0,
            TRUE);

    System_linkControl(
            pObj->ucObj.Gate_algDrawLinkID,
            GATE_LINK_CMD_SET_OPERATION_MODE_OFF,
            NULL,
            0,
            TRUE);
    /* Wait for the buffers in Gate links to be freed before
     * powering down DSP and EVE.
     */
    do
    {
        BspOsal_sleep(1U);
        System_linkControl(
            pObj->ucObj.Gate_algFeatureComputeLinkID,
            GATE_LINK_CMD_GET_BUFFER_FORWARD_COUNT,
            &numBuffersPending,
            sizeof(numBuffersPending),
            TRUE);
    } while (numBuffersPending != 0U);
    /* Wait for the buffers in Gate links to be freed before
     * powering down DSP and EVE.
     */
    do
    {
        BspOsal_sleep(1U);
        System_linkControl(
            pObj->ucObj.Gate_algCaptureLinkID,
            GATE_LINK_CMD_GET_BUFFER_FORWARD_COUNT,
            &numBuffersPending,
            sizeof(numBuffersPending),
            TRUE);
    } while (numBuffersPending != 0U);
    /* Wait for the buffers in Gate links to be freed before
     * powering down DSP and EVE.
     */
    do
    {
        BspOsal_sleep(1U);
        System_linkControl(
            pObj->ucObj.Gate_algDrawLinkID,
            GATE_LINK_CMD_GET_BUFFER_FORWARD_COUNT,
            &numBuffersPending,
            sizeof(numBuffersPending),
            TRUE);
    } while (numBuffersPending != 0U);
    /* Stop and delete the UC late chains */
    chains_fastBoot_issIspSimcop_pd_Display_StopAndDeleteApp_UcLate(pObj);
    /* Perform the IPC detach and shut down the cores */
    Utils_bootPowerDownSlaves();
    endTime = Utils_getCurGlobalTimeInMsec();
    timeTaken = endTime - startTime;
    Vps_printf(" CHAINS: DSP and EVE power OFF Time = %d ms\n", timeTaken);
}
