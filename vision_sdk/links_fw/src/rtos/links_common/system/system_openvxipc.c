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
 * \file system_openVxIpc.c
 *
 * \brief
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "system_priv_ipc.h"
#include <src/rtos/utils_common/include/utils_idle.h>
#include <src/rtos/utils_common/include/utils_spinlock.h>

/*******************************************************************************
 *  Data structure's
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *  \brief  OpenVx IPC object
 *
 *******************************************************************************
*/
typedef struct
{
    System_openVxNotifyHandler notifyHandler;
} System_openVxIpcObj;


/**
 *******************************************************************************
 * \brief Global object for storing OpenVx IPC related parameters..
 *******************************************************************************
 */

#define SYSTEM_OPENVX_SHM_SIZE  (1024U*1024U)

#pragma DATA_SECTION(gOpenVxShmMem, ".bss:extMemNonCache:tiovxObjDescShm");
#pragma DATA_ALIGN(gOpenVxShmMem, 1024);
static UInt8 gOpenVxShmMem[SYSTEM_OPENVX_SHM_SIZE];

System_openVxIpcObj gSystem_openVxIpcObj;

/*******************************************************************************
 *  Function Definations
 *******************************************************************************
 */

void *System_openvxGetObjDescShm(UInt32 *shmSize)
{
    *shmSize = SYSTEM_OPENVX_SHM_SIZE;

    return &gOpenVxShmMem[0];
}

Void System_registerOpenVxNotifyCb(System_openVxNotifyHandler notifyCb)
{
    gSystem_openVxIpcObj.notifyHandler = notifyCb;
}

Int32 System_openVxSendNotify(UInt32 cpuId, UInt32 payload)
{
    UInt32 linkId = 0U;

    linkId = SYSTEM_LINK_ID_MAKE_NOTIFY_TYPE(
                    cpuId,
                    payload,
                    SYSTEM_LINK_ID_NOTIFY_TYPE_OPENVX
            );

    return System_ipcSendNotify(linkId);
}

Void System_openVxIpcHandler(UInt32 payload, Ptr arg)
{
    if (gSystem_openVxIpcObj.notifyHandler)
    {
        payload = SYSTEM_GET_LINK_ID(payload);

        gSystem_openVxIpcObj.notifyHandler(payload);
    }
}


Void System_openvxActivate(void)
{
#if defined (BUILD_ARP32)
    Utils_idleEnableEveDMA();
#endif
}

Void System_openvxDeactivate(void)
{
#if defined (BUILD_ARP32)
    Utils_idleDisableEveDMA();
#endif
}

Bool System_openvxIsProcEnabled(UInt32 procId)
{
    return System_isProcEnabled(procId);
}

void System_openvxHwSpinLockAcquire(uint32_t hw_lock_id)
{
    UTILS_assert(hw_lock_id<MAX_NUM_SPINLOCKS);
    Utils_acquireSpinLock(UTILS_SPINLOCK_BASE_UTILS_L3FW,
        hw_lock_id,
        (UInt32)TRUE
            );
}

void System_openvxHwSpinLockRelease(uint32_t hw_lock_id)
{
    UTILS_assert(hw_lock_id<MAX_NUM_SPINLOCKS);
    Utils_freeSpinLock(UTILS_SPINLOCK_BASE_UTILS_L3FW, hw_lock_id);
}

