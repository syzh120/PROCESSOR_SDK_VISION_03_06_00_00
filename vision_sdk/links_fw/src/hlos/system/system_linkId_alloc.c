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
 *  \ingroup SYSTEM_LINK_API
 *  \defgroup SYSTEM_LINK_ID_ALLOC  System Link ID Alloc API
 *
 *  These APIs are used to allocate link ID's dynamically.
 *  Typicaly called by the code generated using the vision sdk use-case gen tool
 *  when "-dynamic_link_id"
 *
 *  @{
*/

#include <osa_types.h>
#include <osa_debug.h>
#include <osa_mutex.h>
#include <include/link_api/system_linkId.h>
#include <include/link_api/system_linkId_alloc.h>

static UInt32 linkVal[SYSTEM_PROC_MAX][SYSTEM_LINK_TYPE_MAX];
static OSA_MutexHndl linkIdAllocMutex;

static inline Uint8 linkValMax() 
{
    Uint32 numBitsInByte = 8;
    return (numBitsInByte * sizeof(UInt32));
} 

Void System_linkIdAllocReset()
{
    Int32 i,j;
    static UInt8 isInit = 0;

    for (i=0; i<SYSTEM_PROC_MAX; i++) {
        for (j=0; j<SYSTEM_PROC_MAX; j++) {
            linkVal[i][j] = 0;
        }
    }

    if (isInit == 0) {
        OSA_assert((OSA_mutexCreate(&linkIdAllocMutex) == OSA_SOK));
        isInit = 1;
    }
}

UInt32 System_linkIdAlloc(UInt32 procId, System_LinkType linkType)
{
    Uint32 pos, linkId, tempLinkId;

    OSA_mutexLock(&linkIdAllocMutex);

    for (pos=0; pos<linkValMax(); pos++) {
        if(!(linkVal[procId][linkType] & (1 << pos)))
            break;
    }
    OSA_assert(pos < linkValMax());
    
    switch (linkType)
    {
        case SYSTEM_LINK_TYPE_IPC_OUT:
            tempLinkId = pos + SYSTEM_LINK_ID_IPC_OUT_0;
            linkId = SYSTEM_MAKE_LINK_ID(procId, tempLinkId);
        break;
        case SYSTEM_LINK_TYPE_IPC_IN:
            tempLinkId = pos + SYSTEM_LINK_ID_IPC_IN_0;
            linkId = SYSTEM_MAKE_LINK_ID(procId, tempLinkId);
        break;
        case SYSTEM_LINK_TYPE_NULL:
            tempLinkId = pos + SYSTEM_LINK_ID_NULL_0;
            linkId = SYSTEM_MAKE_LINK_ID(procId, tempLinkId);
        break;
        case SYSTEM_LINK_TYPE_GRPX_SRC:
            tempLinkId = pos + SYSTEM_LINK_ID_GRPX_SRC_0;
            linkId = SYSTEM_MAKE_LINK_ID(procId, tempLinkId);
        break;
        case SYSTEM_LINK_TYPE_DUP:
            tempLinkId = pos + SYSTEM_LINK_ID_DUP_0;
            linkId = SYSTEM_MAKE_LINK_ID(procId, tempLinkId);
        break;
        case SYSTEM_LINK_TYPE_GATE:
            tempLinkId = pos + SYSTEM_LINK_ID_GATE_0;
            linkId = SYSTEM_MAKE_LINK_ID(procId, tempLinkId);
        break;
        case SYSTEM_LINK_TYPE_SYNC:
            tempLinkId = pos + SYSTEM_LINK_ID_SYNC_0;
            linkId = SYSTEM_MAKE_LINK_ID(procId, tempLinkId);
        break;
        case SYSTEM_LINK_TYPE_MERGE:
            tempLinkId = pos + SYSTEM_LINK_ID_MERGE_0;
            linkId = SYSTEM_MAKE_LINK_ID(procId, tempLinkId);
        break;
        case SYSTEM_LINK_TYPE_SELECT:
            tempLinkId = pos + SYSTEM_LINK_ID_SELECT_0;
            linkId = SYSTEM_MAKE_LINK_ID(procId, tempLinkId);
        break;
        case SYSTEM_LINK_TYPE_ALG:
            tempLinkId = pos + SYSTEM_LINK_ID_ALG_0;
            linkId = SYSTEM_MAKE_LINK_ID(procId, tempLinkId);
        break;
        case SYSTEM_LINK_TYPE_NULL_SRC:
            tempLinkId = pos + SYSTEM_LINK_ID_NULL_SRC_0;
            linkId = SYSTEM_MAKE_LINK_ID(procId, tempLinkId);
        break;
        case SYSTEM_LINK_TYPE_AVB_RX:
            tempLinkId = pos + SYSTEM_LINK_ID_AVB_RX;
            linkId = SYSTEM_MAKE_LINK_ID(procId, tempLinkId);
        break;
        case SYSTEM_LINK_TYPE_RTI:
            tempLinkId = pos + SYSTEM_LINK_ID_RTI_0;
            linkId = SYSTEM_MAKE_LINK_ID(procId, tempLinkId);
        break;
        case SYSTEM_LINK_TYPE_CAPTURE:
            linkId = pos + SYSTEM_LINK_ID_CAPTURE_0;
        break;
        case SYSTEM_LINK_TYPE_DISPLAY_CTRL:
            linkId = pos + SYSTEM_LINK_ID_DISPLAYCTRL;
        break;
        case SYSTEM_LINK_TYPE_DISPLAY:
            linkId = pos + SYSTEM_LINK_ID_DISPLAY_0;
        break;
        case SYSTEM_LINK_TYPE_VPE:
            linkId = pos + SYSTEM_LINK_ID_VPE_0;
        break;
        case SYSTEM_LINK_TYPE_VENC:
            linkId = pos + SYSTEM_LINK_ID_VENC_0;
        break;
        case SYSTEM_LINK_TYPE_VDEC:
            linkId = pos + SYSTEM_LINK_ID_VDEC_0;
        break;
        case SYSTEM_LINK_TYPE_ISSCAPTURE:
            linkId = pos + SYSTEM_LINK_ID_ISSCAPTURE_0;
        break;
        case SYSTEM_LINK_TYPE_ISSM2MISP:
            linkId = pos + SYSTEM_LINK_ID_ISSM2MISP_0;
        break;
        case SYSTEM_LINK_TYPE_APP_CTRL:
            linkId = pos + SYSTEM_LINK_ID_APP_CTRL;
        break;
        case SYSTEM_LINK_TYPE_ULTRASONIC_CAPTURE:
            linkId = pos + SYSTEM_LINK_ID_ULTRASONIC_CAPTURE;
        break;
        case SYSTEM_LINK_TYPE_HCF:
            linkId = pos + SYSTEM_LINK_ID_HCF_0;
        break;
        case SYSTEM_LINK_TYPE_SPLIT:
            linkId = pos + SYSTEM_LINK_ID_SPLIT_0;
        break;
        case SYSTEM_LINK_TYPE_RADAR_CAPTURE:
            linkId = pos + SYSTEM_LINK_ID_RADAR_CAPTURE;
        break;
        case SYSTEM_LINK_TYPE_SGXFRMCPY:
            linkId = pos + SYSTEM_LINK_ID_SGXFRMCPY_0;
        break;
        case SYSTEM_LINK_TYPE_SGX3DSRV:
            linkId = pos + SYSTEM_LINK_ID_SGX3DSRV_0;
        break;
        case SYSTEM_LINK_TYPE_SGX3DSFM:
            linkId = pos + SYSTEM_LINK_ID_SGX3DSFM_0;
        break;
        case SYSTEM_LINK_TYPE_EP:
            linkId = pos + SYSTEM_LINK_ID_EP_0;
        break;
        default:
            linkId = 0xFFFFFFFF;
        break;

    }

    linkVal[procId][linkType] |= (1 << pos);

    OSA_mutexUnlock(&linkIdAllocMutex);
    
    return (linkId);
}

Void System_linkIdFree(System_LinkType linkType, UInt32 linkId) 
{
    Uint32 procId, pos, tempLinkId;

    OSA_mutexLock(&linkIdAllocMutex);

    tempLinkId = SYSTEM_GET_LINK_ID(linkId);

    switch (linkType)
    {
        case SYSTEM_LINK_TYPE_IPC_OUT:
            pos = tempLinkId - SYSTEM_LINK_ID_IPC_OUT_0;
        break;
        case SYSTEM_LINK_TYPE_IPC_IN:
            pos = tempLinkId - SYSTEM_LINK_ID_IPC_IN_0;
        break;
        case SYSTEM_LINK_TYPE_NULL:
            pos = tempLinkId - SYSTEM_LINK_ID_NULL_0;
        break;
        case SYSTEM_LINK_TYPE_GRPX_SRC:
            pos = tempLinkId - SYSTEM_LINK_ID_GRPX_SRC_0;
        break;
        case SYSTEM_LINK_TYPE_DUP:
            pos = tempLinkId - SYSTEM_LINK_ID_DUP_0;
        break;
        case SYSTEM_LINK_TYPE_GATE:
            pos = tempLinkId - SYSTEM_LINK_ID_GATE_0;
        break;
        case SYSTEM_LINK_TYPE_SYNC:
            pos = tempLinkId - SYSTEM_LINK_ID_SYNC_0;
        break;
        case SYSTEM_LINK_TYPE_MERGE:
            pos = tempLinkId - SYSTEM_LINK_ID_MERGE_0;
        break;
        case SYSTEM_LINK_TYPE_SELECT:
            pos = tempLinkId - SYSTEM_LINK_ID_SELECT_0;
        break;
        case SYSTEM_LINK_TYPE_ALG:
            pos = tempLinkId - SYSTEM_LINK_ID_ALG_0;
        break;
        case SYSTEM_LINK_TYPE_NULL_SRC:
            pos = tempLinkId - SYSTEM_LINK_ID_NULL_SRC_0;
        break;
        case SYSTEM_LINK_TYPE_AVB_RX:
            pos = tempLinkId - SYSTEM_LINK_ID_AVB_RX;
        break;
        case SYSTEM_LINK_TYPE_RTI:
            pos = tempLinkId - SYSTEM_LINK_ID_RTI_0;
        break;
        case SYSTEM_LINK_TYPE_CAPTURE:
            pos = tempLinkId - SYSTEM_GET_LINK_ID(SYSTEM_LINK_ID_CAPTURE_0);
        break;
        case SYSTEM_LINK_TYPE_DISPLAY_CTRL:
            pos = tempLinkId - SYSTEM_GET_LINK_ID(SYSTEM_LINK_ID_DISPLAYCTRL);
        break;
        case SYSTEM_LINK_TYPE_DISPLAY:
            pos = tempLinkId - SYSTEM_GET_LINK_ID(SYSTEM_LINK_ID_DISPLAY_0);
        break;
        case SYSTEM_LINK_TYPE_VPE:
            pos = tempLinkId - SYSTEM_GET_LINK_ID(SYSTEM_LINK_ID_VPE_0);
        break;
        case SYSTEM_LINK_TYPE_VENC:
            pos = tempLinkId - SYSTEM_GET_LINK_ID(SYSTEM_LINK_ID_VENC_0);
        break;
        case SYSTEM_LINK_TYPE_VDEC:
            pos = tempLinkId - SYSTEM_GET_LINK_ID(SYSTEM_LINK_ID_VDEC_0);
        break;
        case SYSTEM_LINK_TYPE_ISSCAPTURE:
            pos = tempLinkId - SYSTEM_GET_LINK_ID(SYSTEM_LINK_ID_ISSCAPTURE_0);
        break;
        case SYSTEM_LINK_TYPE_ISSM2MISP:
            pos = tempLinkId - SYSTEM_GET_LINK_ID(SYSTEM_LINK_ID_ISSM2MISP_0);
        break;
        case SYSTEM_LINK_TYPE_APP_CTRL:
            pos = tempLinkId - SYSTEM_GET_LINK_ID(SYSTEM_LINK_ID_APP_CTRL);
        break;
        case SYSTEM_LINK_TYPE_ULTRASONIC_CAPTURE:
            pos = tempLinkId - SYSTEM_GET_LINK_ID(SYSTEM_LINK_ID_ULTRASONIC_CAPTURE);
        break;
        case SYSTEM_LINK_TYPE_HCF:
            pos = tempLinkId - SYSTEM_GET_LINK_ID(SYSTEM_LINK_ID_HCF_0);
        break;
        case SYSTEM_LINK_TYPE_SPLIT:
            pos = tempLinkId - SYSTEM_GET_LINK_ID(SYSTEM_LINK_ID_SPLIT_0);
        break;
        case SYSTEM_LINK_TYPE_RADAR_CAPTURE:
            pos = tempLinkId - SYSTEM_GET_LINK_ID(SYSTEM_LINK_ID_RADAR_CAPTURE);
        break;
        case SYSTEM_LINK_TYPE_SGXFRMCPY:
            pos = tempLinkId - SYSTEM_GET_LINK_ID(SYSTEM_LINK_ID_SGXFRMCPY_0);
        break;
        case SYSTEM_LINK_TYPE_SGX3DSRV:
            pos = tempLinkId - SYSTEM_GET_LINK_ID(SYSTEM_LINK_ID_SGX3DSRV_0);
        break;
        case SYSTEM_LINK_TYPE_SGX3DSFM:
            pos = tempLinkId - SYSTEM_GET_LINK_ID(SYSTEM_LINK_ID_SGX3DSFM_0);
        break;
        case SYSTEM_LINK_TYPE_EP:
            pos = tempLinkId - SYSTEM_GET_LINK_ID(SYSTEM_LINK_ID_EP_0);
        break;
        default:
            pos = 0xFFFFFFFF;
        break;
    }

    OSA_assert(pos < linkValMax());

    procId = SYSTEM_GET_PROC_ID(linkId);
    OSA_assert(procId < SYSTEM_PROC_MAX);
    /* ipu2 to ipu1 hack */
    if(procId == SYSTEM_PROC_IPU2)
        procId = SYSTEM_PROC_IPU1_0;

    linkVal[procId][linkType] &= ~(1 << pos);

    OSA_mutexUnlock(&linkIdAllocMutex);
}
