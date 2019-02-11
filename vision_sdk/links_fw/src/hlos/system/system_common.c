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
 * \file system_common.c
 *
 * \brief   System level initialization for all components.
 *
 *          This file deals with system level initialization of links and
 *          chains framework. It creates a system tasks for handling all system
 *          wide functions. Initializes the system wide resources like
 *          and components performance counters, mail boxes, IPC, memory
 *          allocators. It also initializes all links in the system such that
 *          links are ready to take commands from application.
 *
 * \version 0.0 (Apr 2014) : [YM] First version taken from bios side vision sdk

 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <system_cfg.h>
#include "system_priv_common.h"
#include "system_priv_ipc.h"
#include <osa_remote_log_if.h>
#ifndef QNX_BUILD
#include "dmabuf-ioctl.h"
#include <sys/ioctl.h>
#endif

/**
 *******************************************************************************
 * \brief Global object for system link.
 *
 *        All the links registers itself to system link. This global object
 *        has information about all links like link's call back functions
 *        and linkInfo
 *******************************************************************************
 */
System_CommonObj gSystem_objCommon;

#if defined(OPENVX_INCLUDE)
void tivxInit(void);
void tivxDeInit(void);
#endif

/**
 *******************************************************************************
 * \brief Global object for defining which Processors needs to be enabled.
 *
 * This is required to loop around the IPC attach and other ipc functions
 * based on processors enabled in links and chains.
 *
 * \warning The araay is size is MAX + 2 to ensure we have space to hold MAX
 *          marker and invalid entry marker.
 *******************************************************************************
 */
UInt32 gSystem_ipcEnableProcId[SYSTEM_PROC_MAX + 2U] = {

#ifdef PROC_IPU1_0_INCLUDE
    SYSTEM_PROC_IPU1_0,
#endif
#ifdef PROC_IPU1_1_INCLUDE
    SYSTEM_PROC_IPU1_1,
#endif
#ifdef PROC_IPU2_INCLUDE
    SYSTEM_PROC_IPU2,
#endif
#ifdef PROC_DSP1_INCLUDE
    SYSTEM_PROC_DSP1,
#endif
#ifdef PROC_DSP2_INCLUDE
    SYSTEM_PROC_DSP2,
#endif
#ifdef PROC_EVE1_INCLUDE
    SYSTEM_PROC_EVE1,
#endif
#ifdef PROC_EVE2_INCLUDE
    SYSTEM_PROC_EVE2,
#endif
#ifdef PROC_EVE3_INCLUDE
    SYSTEM_PROC_EVE3,
#endif
#ifdef PROC_EVE4_INCLUDE
    SYSTEM_PROC_EVE4,
#endif
#ifdef PROC_A15_0_INCLUDE
    SYSTEM_PROC_A15_0,
#endif

    SYSTEM_PROC_MAX,

    /* MISRA C Fix 9.2
        When some of the cores are disabled, this code ensures that all
        the elements are initialized */
#ifndef PROC_IPU1_0_INCLUDE
    SYSTEM_PROC_INVALID,
#endif
#ifndef PROC_IPU1_1_INCLUDE
    SYSTEM_PROC_INVALID,
#endif
#ifndef PROC_IPU2_INCLUDE
    SYSTEM_PROC_INVALID,
#endif
#ifndef PROC_DSP1_INCLUDE
    SYSTEM_PROC_INVALID,
#endif
#ifndef PROC_DSP2_INCLUDE
    SYSTEM_PROC_INVALID,
#endif
#ifndef PROC_EVE1_INCLUDE
    SYSTEM_PROC_INVALID,
#endif
#ifndef PROC_EVE2_INCLUDE
    SYSTEM_PROC_INVALID,
#endif
#ifndef PROC_EVE3_INCLUDE
    SYSTEM_PROC_INVALID,
#endif
#ifndef PROC_EVE4_INCLUDE
    SYSTEM_PROC_INVALID,
#endif
#ifndef PROC_A15_0_INCLUDE
    SYSTEM_PROC_INVALID,
#endif

    SYSTEM_PROC_INVALID
};

/**
 *******************************************************************************
 *
 * \brief Returns processor ID on which function is called.
 *
 *        Returns the processor id on which this function is getting called.
 *        Suppose code on DSP calls this function it returns processor id as
 *        DSP
 *
 * \return  ProcessorId for valid processor else SYSTEM_PROC_INVALID
 *
 *******************************************************************************
 */
UInt32 System_getSelfProcId(void)
{
    return SYSTEM_PROC_A15_0;
}

/**
 *******************************************************************************
 *
 * \brief This function waits for all cores to complete the application level
 *        initialization.
 *
 *        This function is effective only for the "host" processor
 *
 *******************************************************************************
 */
Void System_waitAppInitComplete(void)
{
    UInt32 procId;
    UInt32 initDone[SYSTEM_PROC_MAX] = {0,};
    UInt32 allInitDone;
    unsigned int state;

    initDone[SYSTEM_PROC_A15_0] = TRUE;

    while (1)
    {
        for(procId=0; procId<SYSTEM_PROC_MAX; procId++)
        {
            if(System_isProcEnabled(procId))
            {
                if (FALSE == initDone[procId])
                {
                    RemoteLog_getAppInitState(procId, &state);

                    if (state == CORE_APP_INITSTATUS_CONFIRM_INIT_DONE)
                    {
                        initDone[procId] = TRUE;
                    }
                }
            }
        }

        allInitDone = TRUE;

        for(procId=0; procId<SYSTEM_PROC_MAX; procId++)
        {
            if(System_isProcEnabled(procId))
            {
                if (FALSE == initDone[procId])
                {
                    allInitDone = FALSE;
                    break;
                }
            }
        }

        if(TRUE == allInitDone)
        {
            break;
        }
        OSA_waitMsecs(1);
    }
}

/**
 *******************************************************************************
 *
 * \brief This function set the trigger to exit the application
 *        for all remote processor's in the system
 *
 *        This function is effective only for the "host" processor
 *
 *******************************************************************************
 */
Void System_triggerAppExit(void)
{
    unsigned int state = CORE_APP_INITSTATUS_DO_EXIT;

    /* only trigger app exit for IPU1-0, it will in turn
     * trigger exit and wait for other's CPU to exit
     */
    RemoteLog_setAppInitState(SYSTEM_IPU_PROC_PRIMARY, state);
}

/**
 *******************************************************************************
 *
 * \brief This function waits for all cores to complete the application level
 *        initialization.
 *
 *        This function is effective only for the "host" processor
 *
 *******************************************************************************
 */
Void System_waitAppExitComplete(void)
{
    UInt32 procId;
    UInt32 exitDone[SYSTEM_PROC_MAX] = {0,};
    UInt32 allInitDone;
    unsigned int state;

    exitDone[SYSTEM_PROC_A15_0] = TRUE;

    while (1)
    {
        for(procId=0; procId<SYSTEM_PROC_MAX; procId++)
        {
            if(System_isProcEnabled(procId))
            {
                if (FALSE == exitDone[procId])
                {
                    RemoteLog_getAppInitState(procId, &state);

                    if (state == CORE_APP_INITSTATUS_EXIT_DONE)
                    {
                        exitDone[procId] = TRUE;
                    }
                }
            }
        }

        allInitDone = TRUE;

        for(procId=0; procId<SYSTEM_PROC_MAX; procId++)
        {
            if(System_isProcEnabled(procId))
            {
                if (FALSE == exitDone[procId])
                {
                    allInitDone = FALSE;
                    break;
                }
            }
        }

        if(TRUE == allInitDone)
        {
            break;
        }
        OSA_waitMsecs(1);
    }
}

/**
 *******************************************************************************
 * \brief API to Initialize the system
 *
 *   - Initialize various links present in the core
 *   - Initialize the resources
 *
 * \return SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 System_init(void)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    OSA_init();

#ifdef SYSTEM_DEBUG
    Vps_printf(" SYSTEM: System A15 Init in progress !!!\n");
#endif

    memset(&gSystem_objCommon, 0, sizeof(gSystem_objCommon));
    status = OSA_mutexCreate(&gSystem_objCommon.linkControlMutex);
    OSA_assertSuccess(status);
    status = OSA_mbxCreate(&gSystem_objCommon.mbx);
    OSA_assertSuccess(status);
    System_waitAppInitComplete();
#ifndef QNX_BUILD
    gSystem_objCommon.devBufFD = open("/dev/vmemexp", O_RDWR | O_CLOEXEC);
#endif
    System_ipcInit();
    System_initLinks();
    System_waitAppInitComplete();
    OSA_syncGlobalTime();
#if defined(OPENVX_INCLUDE)
    tivxInit();
#endif

#ifdef SYSTEM_DEBUG
    Vps_printf(" SYSTEM: System A15 Init Done !!!\n");
#endif
    return status;
}

/**
 *******************************************************************************
 *
 * \brief API to De-Initialize the system
 *
 *  - De-Initialize various links present in the core
 *  - De-Initialize the resources
 *
 * \param shutdownRemoteProcs   [IN] Set FALSE always for Bios only build.
 *                                   For Linux builds choose TRUE or FALSE
 *
 * \return SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 System_deInit(UInt32 shutdownRemoteProcs)
{
#ifdef SYSTEM_DEBUG
    Vps_printf(" SYSTEM: System A15 De-Init in progress !!!\n");
#endif

#if defined(OPENVX_INCLUDE)
    tivxDeInit();
#endif

    if(shutdownRemoteProcs)
    {
        System_triggerAppExit();
        System_waitAppExitComplete();
    }
    System_deInitLinks();

    System_ipcDeInit();
#ifdef SYSTEM_DEBUG
    Vps_printf(" SYSTEM: System A15 De-Init Done !!!\n");
#endif

    /* wait for remote log prints to get flushed */
    OSA_waitMsecs(20);
#ifndef QNX_BUILD
    close(gSystem_objCommon.devBufFD);
#endif
    OSA_deInit();

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Initialize the A15 system links
 *
 *******************************************************************************
*/
Void System_initLinks(void)
{
    Vps_printf(" SYSTEM: Initializing A15 Links !!! \r\n");

    IpcOutLink_init();
    IpcInLink_init();
    NullLink_init();
    NullSrcLink_init();
    DispDistSrcLink_init();
#ifdef ALG_surroundview
    Sgx3DsrvLink_init();
#endif
#ifdef BUILD_INFOADAS
    EpLink_init();
#else
    AlgorithmLink_init();
    DupLink_init();
    SyncLink_init();
    MergeLink_init();
    SelectLink_init();
    GateLink_init();
    SgxFrmcpyLink_init();
#ifdef ALG_structurefrommotion
    Sgx3DsfmLink_init();
#endif
#endif
    Vps_printf(" SYSTEM: Initializing A15 Links ... DONE !!! \r\n");
}

/**
 *******************************************************************************
 *
 * \brief De-initialize the previously initialized A15 link
 *
 *******************************************************************************
*/
Void System_deInitLinks(void)
{
    Vps_printf(" SYSTEM: De-Initializing A15 Links !!! \r\n");

    IpcOutLink_deInit();
    IpcInLink_deInit();
    NullLink_deInit();
    NullSrcLink_deInit();
    DispDistSrcLink_deInit();
#ifdef ALG_surroundview
    Sgx3DsrvLink_deInit();
#endif
#ifdef BUILD_INFOADAS
    EpLink_deInit();
#else
    AlgorithmLink_deInit();
    DupLink_deInit();
    SyncLink_deInit();
    MergeLink_deInit();
    SelectLink_deInit();
    GateLink_deInit();
    SgxFrmcpyLink_deInit();
#ifdef ALG_structurefrommotion
    Sgx3DsfmLink_deInit();
#endif
#endif
    Vps_printf(" SYSTEM: De-Initializing A15 Links ... DONE !!! \r\n");
}

Int32 System_exportDmaBuf(void * vAddr, UInt32 size, UInt32 *fdBuf)
{
    Int32 retVal = -1;
#ifndef QNX_BUILD
    struct dmabuf_vmem_export exp;
    exp.vaddr = (unsigned long)vAddr;
    exp.size = size;

    if(gSystem_objCommon.devBufFD > 0)
    {
        /* Export as DMAbuf handle */
        retVal = ioctl(gSystem_objCommon.devBufFD, DBUFIOC_EXPORT_VIRTMEM, &exp);
        if(retVal == SYSTEM_LINK_STATUS_SOK)
        {
            *fdBuf = exp.fd;
        }
        else
        {
            Vps_printf(" exportDmaBuf failed \n ");
        }
    }
#else
    retVal = SYSTEM_LINK_STATUS_SOK;
#endif
return retVal;
}

