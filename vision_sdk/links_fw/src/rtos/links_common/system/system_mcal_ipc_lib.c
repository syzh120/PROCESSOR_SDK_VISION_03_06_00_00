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
 * \file system_ipc_safe_ipclib.c
 *
 * \brief  This file implements usage of safe ipc library
 *
 * \version 0.0 (Aug 2016) : [YM] first version implemented
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "system_priv_ipc.h"
#include <ti/ipc/MultiProc.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */
Void Mcal_IpcInit(Void);
Void Mcal_IpcDeInit(Void);


/**
 *******************************************************************************
 *
 * \brief Utility function to invoke the notify to remote processor.
 *
 *        This function generates the notify event. It takes linkId as input
 *        maps linkId with procId and generates notify event on that processor
 *
 * \param   linkId      [IN] Link Id to which notify needs to be generated.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success.
 *
 *******************************************************************************
 */
Int32 System_ipcNotifySendEvent(UInt32 linkId)
{
    /* Nothing to be done for MCAL IpcLib */
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Utility to initialize notify sub-system for links and chains
 *        work.
 *
 *        Initialize the notify event for local processor. It also registers
 *        callback with notify sub-system to get notify events from remote
 *        processor.
 *
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success.
 *
 *******************************************************************************
 */
Int32 System_ipcNotifyRegister(void)
{
    /* Nothing to be done for MCAL IpcLib */
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Utility to un-initialize notify sub-system for links and chains
 *        work.
 *
 *        Unregisters event
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success.
 *
 *******************************************************************************
 */
Int32 System_ipcNotifyUnregister(void)
{
    /* Nothing to be done for MCAL IpcLib */
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Function to enable mailboxes forcefully. This is used when
 *        booting sequence is unconventional.
 *
 *
 * \return  None.
 *
 *******************************************************************************
 */
Void System_ipcNotifyReset(UInt32 procId)
{
    /* Nothing to be done for MCAL IpcLib */
}

/**
 *******************************************************************************
 *
 * \brief Function to setup safe ipc
 *
 * \return  None.
 *
 *******************************************************************************
 */
Int32 System_ipcNotifyInit(void)
{
    Mcal_IpcInit();
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Utility to de-initialize notify sub-system for links and chains
 *        work.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success.
 *
 *******************************************************************************
 */
Int32 System_ipcNotifyDeInit(void)
{
    Mcal_IpcDeInit();
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Utility to get ipclib procId
 *
 * \return  procId on success.
 *
 *******************************************************************************
 */

UInt32 System_getIpcLibProcId(UInt32 procId)
{
    /* Nothing to be done for MCAL IpcLib */
    return 0;
}

/**
 *******************************************************************************
 *
 * \brief Configures IpcLib is IPC_LIB_INCLUDE if yes
 *
 * \return none
 *
 *******************************************************************************
 */
Void System_ipcInitConfig(void)
{
    /* Nothing to be done for MCAL IpcLib */
}

/**
 *******************************************************************************
 *
 * \brief De-initializes IpcLib is IPC_LIB_INCLUDE if yes
 *
 * \return none
 *
 *******************************************************************************
 */
Void System_ipcDeInitConfig(void)
{
    /* Nothing to be done for MCAL IpcLib */
}


/**
 *******************************************************************************
 *
 * \brief Wrapper around Ipc_start function of IPC component.
 *
 * \return  None
 *
 *******************************************************************************
 */
Void System_ipcStart(void)
{
    /* Nothing to be done for MCAL IpcLib */
}

/**
 *******************************************************************************
 *
 * \brief Wrapper around Ipc_stop function of IPC component.
 *
 *
 * \return  None
 *
 *******************************************************************************
 */
Void System_ipcStop(void)
{
    /* Nothing to be done for MCAL IpcLib */
}

/**
 *******************************************************************************
 *
 * \brief Attach local core to all cores for further IPC communication between
 *        cores
 *
 * \return  None
 *
 *******************************************************************************
 */
Void System_ipcAttach(void)
{
    /* Nothing to be done for MCAL IpcLib */
}
/**
 *******************************************************************************
 *
 * \brief Detach local core to all cores for further IPC communication between
 *        cores
 *
 * \return  None
 *
 *******************************************************************************
 */
Void System_ipcDetach(void)
{
    /* Nothing to be done for MCAL IpcLib */
}

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
    static UInt32 selfProcId = SYSTEM_PROC_INVALID;

    if(selfProcId!=SYSTEM_PROC_INVALID)
    {
        /*  find self proc ID only once, since it never changes run-time
        *  Doing this optimization since, this API is called for every
        *  System_linkXxxx API
        */
    }
    else
    {
        /* Doesn't use IpcLib to avoid proc name confilcts */

        #if defined (BUILD_A15)
             selfProcId = SYSTEM_PROC_A15_0;
        #endif
        #if defined (BUILD_DSP_1)
             selfProcId = SYSTEM_PROC_DSP1;
        #endif
        #if defined (BUILD_M4_0)
             selfProcId = SYSTEM_PROC_IPU1_0;
        #endif
        #if defined (BUILD_M4_2)
             selfProcId = SYSTEM_PROC_IPU2;
        #endif
        #if defined (BUILD_DSP_2)
             selfProcId = SYSTEM_PROC_DSP2;
        #endif
        #if defined (BUILD_M4_1)
             selfProcId = SYSTEM_PROC_IPU1_1;
        #endif
        #if defined (BUILD_ARP32_1)
             selfProcId = SYSTEM_PROC_EVE1;
        #endif
        #if defined (BUILD_ARP32_2)
             selfProcId = SYSTEM_PROC_EVE2;
        #endif
        #if defined (BUILD_ARP32_3)
             selfProcId = SYSTEM_PROC_EVE3;
        #endif
        #if defined (BUILD_ARP32_4)
             selfProcId = SYSTEM_PROC_EVE4;
        #endif
    }
    return selfProcId;
}

UInt32 System_getSyslinkProcId(UInt32 procId)
{
    char *procName = System_getProcName(procId);
    UInt32  retVal;

    if(strcmp(procName, SYSTEM_IPC_PROC_NAME_INVALID)!=0)
    {
        retVal = (UInt32)MultiProc_getId(procName);
    }
    else
    {
        retVal = (UInt32)MultiProc_INVALIDID;
    }
    return retVal;
}

