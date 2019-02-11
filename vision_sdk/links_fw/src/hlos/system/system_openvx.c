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
 * \file system_ipc_notify.c
 *
 * \brief  This file implements the function for the IPC notify functionality
 *
 *         Registers callback with notify sub-system of IPC. Registers
 *         system wide callback to notify. Handles the notify event and pass
 *         it to the link for which notify is intended by calling link
 *         notify handler function.
 *
 * \version 0.0 (Feb 2017) : [BJ] First version taken from DVR RDK and
 *                                cleaned up for Vision_sdk
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include "system_priv_ipc.h"
#include "system_priv_openvx.h"

#include <osa_mem.h>

#define SYSTEM_OPENVX_MEM_ALIGN     (256u)

#define SYSTEM_OPENVX_HW_SPIN_LOCK_MAX        (256u)
#define SYSTEM_OPENVX_HW_SPIN_LOCK_MMR_BASE   (0x4A0F6000u)
#define SYSTEM_OPENVX_HW_SPIN_LOCK_MMR_SIZE   (4*1024u)
#define SYSTEM_OPENVX_HW_SPIN_LOCK_OFFSET(x)  (0x800u + 4u*(x))
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
    uint32_t  spinLockVirtAddr;
} System_openVxObj;


/**
 *******************************************************************************
 * \brief Global object for storing OpenVx IPC related parameters..
 *******************************************************************************
 */
System_openVxObj gSystem_openVxObj;

/*******************************************************************************
 *  Function Definations
 *******************************************************************************
 */
Void System_registerOpenVxNotifyCb(System_openVxNotifyHandler notifyCb)
{
    if(notifyCb!=NULL)
    {
        /* init */
        gSystem_openVxObj.spinLockVirtAddr =
            OSA_memMap(SYSTEM_OPENVX_HW_SPIN_LOCK_MMR_BASE, SYSTEM_OPENVX_HW_SPIN_LOCK_MMR_SIZE);
    }
    else
    {
        /* de-init */
        OSA_memUnMap(gSystem_openVxObj.spinLockVirtAddr, SYSTEM_OPENVX_HW_SPIN_LOCK_MMR_SIZE);
        gSystem_openVxObj.spinLockVirtAddr = 0;
    }
    gSystem_openVxObj.notifyHandler = notifyCb;
}

Int32 System_openVxSendNotify(unsigned int cpuId, unsigned int payload)
{
    unsigned int linkId = 0U;

    linkId = SYSTEM_LINK_ID_MAKE_NOTIFY_TYPE(
                    cpuId,
                    payload,
                    SYSTEM_LINK_ID_NOTIFY_TYPE_OPENVX
            );

    return System_ipcSendNotify(linkId);
}

Void System_openVxIpcHandler(unsigned int payload, void * arg)
{
    if (gSystem_openVxObj.notifyHandler)
    {
        payload = SYSTEM_GET_LINK_ID(payload);

        gSystem_openVxObj.notifyHandler(payload);
    }
}

unsigned int System_ovxGetObjDescShm()
{
    return (OSA_getOpenVxShmVirtAddr());
}

unsigned int System_ovxIsValidCMemVirtAddr(unsigned int virt_addr)
{
    unsigned int isCmemAddr = 0;

    unsigned int reg_type;
    reg_type = OSA_memVirt2RegionType(virt_addr);

    if (OSA_MEM_REGION_TYPE_MAX == reg_type)
    {
        isCmemAddr = 1u;
    }
    else
    {
        isCmemAddr = 0u;
    }

    return (isCmemAddr);
}

unsigned int System_ovxIsValidCMemPhysAddr(unsigned int phys_addr)
{
    unsigned int isCmemAddr = 0;

    unsigned int reg_type;
    reg_type = OSA_memPhys2RegionType(phys_addr);

    if (OSA_MEM_REGION_TYPE_MAX == reg_type)
    {
        isCmemAddr = 1u;
    }
    else
    {
        isCmemAddr = 0u;
    }

    return (isCmemAddr);
}

unsigned int System_ovxCacheInv(unsigned int virt_addr, unsigned int length)
{
    return (OSA_memCacheInv(virt_addr, length));
}

unsigned int System_ovxCacheWb(unsigned int virt_addr, unsigned int length)
{
    return (OSA_memCacheWb(virt_addr, virt_addr + length));
}

unsigned int System_ovxVirt2Phys(unsigned int virt_addr)
{
    return (OSA_memVirt2Phys(virt_addr, OSA_MEM_REGION_TYPE_AUTO));
}

unsigned int System_ovxPhys2Virt(unsigned int phys_addr)
{
    return (OSA_memPhys2Virt(phys_addr, OSA_MEM_REGION_TYPE_AUTO));
}

void *System_ovxAllocMem(unsigned int size)
{
    void *addr = NULL;

    if(size!=0)
    {
        addr = OSA_memAllocSR(OSA_MEM_REGION_TYPE_SR1, size, SYSTEM_OPENVX_MEM_ALIGN);
        if(addr!=NULL)
        {
            System_ovxCacheInv((unsigned int)addr, size);
        }
    }
    return addr;
}

void System_ovxFreeMem(void *addr, unsigned int size)
{
    if(addr!=NULL && size != 0)
    {
        System_ovxCacheInv((unsigned int)addr, size);
        OSA_memFreeSR(OSA_MEM_REGION_TYPE_SR1, addr, size);
    }
}

unsigned int System_openvxIsProcEnabled(unsigned int procId)
{
    return System_isProcEnabled(procId);
}

void System_openvxHwSpinLockAcquire(uint32_t hw_lock_id)
{
    volatile uint32_t *reg_addr;

    if(gSystem_openVxObj.spinLockVirtAddr!= 0
        && hw_lock_id < SYSTEM_OPENVX_HW_SPIN_LOCK_MAX)
    {
        reg_addr =
                (volatile uint32_t*)(
                    gSystem_openVxObj.spinLockVirtAddr +
                    SYSTEM_OPENVX_HW_SPIN_LOCK_OFFSET(hw_lock_id)
                        );

        /* spin until lock is free */
        while( *reg_addr == 1u )
        {
            /* keep spining */
        }
    }
}

void System_openvxHwSpinLockRelease(uint32_t hw_lock_id)
{
    volatile uint32_t *reg_addr;

    if(gSystem_openVxObj.spinLockVirtAddr!= 0
        && hw_lock_id < SYSTEM_OPENVX_HW_SPIN_LOCK_MAX)
    {
        reg_addr =
                (volatile uint32_t*)(
                    gSystem_openVxObj.spinLockVirtAddr +
                    SYSTEM_OPENVX_HW_SPIN_LOCK_OFFSET(hw_lock_id)
                        );

        *reg_addr = 0; /* free the lock */

    }
}
