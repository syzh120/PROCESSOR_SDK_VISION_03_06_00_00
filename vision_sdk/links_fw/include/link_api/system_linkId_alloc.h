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

/**
 *******************************************************************************
 *
 *  \file system_linkId_alloc.h
 *  \brief  System Link ID Alloc API
 *
 *******************************************************************************
*/

#ifndef SYSTEM_LINK_ID_ALLOC_H_
#define SYSTEM_LINK_ID_ALLOC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <include/link_api/system.h>

/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */

/**
 *******************************************************************************
 * \brief Specifies the link type.
 *******************************************************************************
 */
typedef enum {

    SYSTEM_LINK_TYPE_IPC_OUT,
    SYSTEM_LINK_TYPE_IPC_IN,
    SYSTEM_LINK_TYPE_NULL,
    SYSTEM_LINK_TYPE_GRPX_SRC,
    SYSTEM_LINK_TYPE_DUP,
    SYSTEM_LINK_TYPE_GATE,
    SYSTEM_LINK_TYPE_SYNC,
    SYSTEM_LINK_TYPE_MERGE,
    SYSTEM_LINK_TYPE_SELECT,
    SYSTEM_LINK_TYPE_ALG,
    SYSTEM_LINK_TYPE_NULL_SRC,
    SYSTEM_LINK_TYPE_AVB_RX,
    SYSTEM_LINK_TYPE_RTI,
    SYSTEM_LINK_TYPE_CAPTURE,
    SYSTEM_LINK_TYPE_DISPLAY_CTRL,
    SYSTEM_LINK_TYPE_DISPLAY,
    SYSTEM_LINK_TYPE_VPE,
    SYSTEM_LINK_TYPE_VENC,
    SYSTEM_LINK_TYPE_VDEC,
    SYSTEM_LINK_TYPE_ISSCAPTURE,
    SYSTEM_LINK_TYPE_ISSM2MISP,
    SYSTEM_LINK_TYPE_ISSM2MSIMCOP,
    SYSTEM_LINK_TYPE_APP_CTRL,
    SYSTEM_LINK_TYPE_ULTRASONIC_CAPTURE,
    SYSTEM_LINK_TYPE_HCF,
    SYSTEM_LINK_TYPE_SPLIT,
    SYSTEM_LINK_TYPE_RADAR_CAPTURE,
    SYSTEM_LINK_TYPE_SGXFRMCPY,
    SYSTEM_LINK_TYPE_SGX3DSRV,
    SYSTEM_LINK_TYPE_SGX3DSFM,
    SYSTEM_LINK_TYPE_EP,
    SYSTEM_LINK_TYPE_MAX,
    SYSTEM_LINK_TYPE_FORCE_32BITS = 0x7FFFFFFFU

} System_LinkType;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *  \brief Reset link ID alloc data structure to mark all link ID
 *         as free
 *
 *         Called once during system init
 *
 *******************************************************************************
 */
Void System_linkIdAllocReset();


/**
 *******************************************************************************
 *
 *  \brief Alloc link ID for a given procId and link type
 *
 *  \param procId [IN] See SYSTEM_PROC_xxx
 *  \param linkType [IN] See \ref System_LinkType
 *
 *  \return allocate link ID, returns SYSTEM_LINK_ID_INVALID if link ID could
 *          not be allocated
 *
 *******************************************************************************
 */
UInt32 System_linkIdAlloc(UInt32 procId, System_LinkType linkType);

/**
 *******************************************************************************
 *
 *  \brief Free link ID of a given link type
 *
 *  \param linkId [IN] allocated using System_linkIdAlloc()
 *  \param linkType [IN] See \ref System_LinkType
 *
 *******************************************************************************
 */
Void System_linkIdFree(System_LinkType linkType, UInt32 linkId);



#ifdef  __cplusplus
}
#endif

#endif

/*@}*/

