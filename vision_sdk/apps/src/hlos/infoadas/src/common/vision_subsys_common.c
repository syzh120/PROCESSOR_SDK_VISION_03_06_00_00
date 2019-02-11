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

#include <src/hlos/common/chains_common.h>
#include <include/link_api/epLink.h>
#include <include/link_api/system_linkId_alloc.h>
#include <vivi_plugin.h>

extern Int32 (*link_control)(UInt32 link_id, UInt32 cmd, Void *param, 
                                        UInt32 param_size, Bool ack);
/** Vision subsytem init/deinit
 */
Int32 Vision_subsys_init()
{
    System_init();

#ifndef EARLY_SRV_ENABLE
    if(OSA_isRemoteLogClientEnabled()==TRUE)
    {
        /* allow remote prints to complete, before showing main menu */
        OSA_waitMsecs(500);
    }
#endif

    System_linkIdAllocReset();

    /** Initialize function pointers for link control
     * We have these function pointers for two reasons....
     * (1) we don't want to expose too many header files from Vision subsys
     * (2) we don't want to create wrapper functions for such generic functions.
     * The plugin or the Core of the vivi framework will invoke these functions
     * via the following function pointers.
     */
    link_control = &System_linkControl;

    ChainsCommon_prfLoadCalcEnable(FALSE, FALSE, FALSE);
    ChainsCommon_prfLoadCalcEnable(TRUE, FALSE, FALSE);

    return 0;
}

Int32 Vision_subsys_deinit()
{
    ChainsCommon_prfLoadCalcEnable(FALSE, FALSE, FALSE);

    System_deInit(FALSE);

    return 0;
}

/** The epLink control APIs invoked by the vivi framework Core or the plugins.
 */

/** This function is used to return the empty buffers to the sink eplink.
 */
Int32 eplink_control_put_empty_buf(UInt32 eplink_id, System_Buffer *obj)
{
    UInt16 queId;
    System_BufferList pBufList;
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;

    pBufList.numBuf = 1;
    pBufList.buffers[0] = obj;

    /**
     * this being an endpoint link, queId is not used to send the buffers
     * back to the eplink
     */
    queId = 0;

    status = System_putLinksEmptyBuffers(eplink_id, queId, &pBufList);
    if (status < 0) {
        Vps_printf("VIVI: Endpoint: %x: Failed to put empty buf\n", eplink_id);
    }

    return status;
}

/** This function is used to input the filled buffers to a source eplink.
 */
Int32 eplink_control_put_filled_buf(UInt32 eplink_id, System_Buffer *obj)
{
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;

    status = System_linkControl(eplink_id, EP_CMD_PUT_BUF, (Void*) obj, sizeof(Void*), TRUE);

    return status;
}

/** This function is used to create buffer que handle - required by the eplink.
 */
Int32 eplink_control_create_qh(UInt32 eplink_id, struct ep_buf_que *que)
{
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;

    status = System_linkControl(eplink_id, EP_CMD_CREATE_QUE_HANDLE, (Void*) que,
                                        sizeof(struct ep_buf_que), TRUE);

    return status;
}

/** This function is used to get the channel info from a eplink, acting as sink.
 */
Int32 eplink_control_get_ch_info(UInt32 eplink_id, System_LinkQueInfo *epInfo)
{
    System_LinkInfo linkInfo;
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;

    status = System_linkGetInfo(eplink_id, &linkInfo);
    OSA_assert(linkInfo.numQue == 1);

    memcpy(epInfo, &linkInfo.queInfo[0], sizeof(System_LinkQueInfo));

    return status;
}

#ifdef QNX_BUILD
/** Getting CPU load from remote cores
  */
typedef struct {

    struct TotalLoad{

        UInt32 integerValue;
        UInt32 fractionalValue;

    } totalLoadParams;

} Utils_SystemLoadStats;

Int32 Vision_subsys_get_cpu_load(UInt32 proc_id, UInt32 *integer, UInt32 *fractional)
{
    Int32 status;

    Utils_SystemLoadStats cpuLoad;
    UInt32 linkId;

    if (proc_id == VIVI_PROC_IPU1_0)
        proc_id = SYSTEM_PROC_IPU1_0;
    else if (proc_id == VIVI_PROC_IPU1_1)
        proc_id = SYSTEM_PROC_IPU1_1;
    else if (proc_id == VIVI_PROC_DSP1)
        proc_id = SYSTEM_PROC_DSP1;
    else if (proc_id == VIVI_PROC_DSP2)
        proc_id = SYSTEM_PROC_DSP2;
    else if (proc_id == VIVI_PROC_EVE1)
        proc_id = SYSTEM_PROC_EVE1;
    else if (proc_id == VIVI_PROC_EVE2)
        proc_id = SYSTEM_PROC_EVE2;
    else
        return SYSTEM_LINK_STATUS_EFAIL;

    if(System_isProcEnabled(proc_id)== TRUE)
    {
        memset(&cpuLoad, 0, sizeof(cpuLoad));
        linkId = SYSTEM_MAKE_LINK_ID(proc_id, SYSTEM_LINK_ID_PROCK_LINK_ID);
        status = System_linkControl(
                                linkId,
                                SYSTEM_COMMON_CMD_GET_LOAD,
                                &cpuLoad,
                                sizeof(cpuLoad),
                                TRUE
                                );
        if (status != SYSTEM_LINK_STATUS_SOK)
            return SYSTEM_LINK_STATUS_EFAIL;

        *integer = cpuLoad.totalLoadParams.integerValue;
        *fractional = cpuLoad.totalLoadParams.fractionalValue;
    } else {
            return SYSTEM_LINK_STATUS_EFAIL;
    }
    return SYSTEM_LINK_STATUS_SOK;
}

Void Vision_subsys_reset_cpu_load(Void)
{
    Int32 proc_id;
    UInt32 linkId;

    for (proc_id=0; proc_id<SYSTEM_PROC_MAX; proc_id++) {
        if((System_isProcEnabled(proc_id)== TRUE) &&
                        (proc_id != System_getSelfProcId())){
            linkId = SYSTEM_MAKE_LINK_ID(proc_id, SYSTEM_LINK_ID_PROCK_LINK_ID);
            System_linkControl(
                linkId,
                SYSTEM_COMMON_CMD_CPU_LOAD_CALC_RESET,
                NULL,
                0,
                TRUE
            );
        }
    }
}
#endif
