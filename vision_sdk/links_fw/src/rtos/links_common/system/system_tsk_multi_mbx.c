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
#include "system_priv_common.h"

#ifdef BUILD_DSP_1
/* This size of 512KB is for PD algo requirement */
#define SYSTEM_TSK_MULTI_MBX_STACK_SIZE ((UInt32)1024*KB)
#endif

#ifdef BUILD_DSP_2
#define SYSTEM_TSK_MULTI_MBX_STACK_SIZE ((UInt32)1024*(UInt32)1024)
#endif

#ifdef BUILD_ARP32_1
#define SYSTEM_TSK_MULTI_MBX_STACK_SIZE ((UInt32)8*KB)
#endif

#ifdef BUILD_ARP32_2
#define SYSTEM_TSK_MULTI_MBX_STACK_SIZE ((UInt32)8*KB)
#endif

#ifdef BUILD_ARP32_3
#define SYSTEM_TSK_MULTI_MBX_STACK_SIZE ((UInt32)8*KB)
#endif

#ifdef BUILD_ARP32_4
#define SYSTEM_TSK_MULTI_MBX_STACK_SIZE ((UInt32)8*KB)
#endif

#ifdef BUILD_M4
#define SYSTEM_TSK_MULTI_MBX_STACK_SIZE (SYSTEM_DEFAULT_TSK_STACK_SIZE)
#endif

#ifdef BUILD_A15
#define SYSTEM_TSK_MULTI_MBX_STACK_SIZE (SYSTEM_DEFAULT_TSK_STACK_SIZE)
#endif

/**
 *******************************************************************************
 * \brief Link Stack
 *******************************************************************************
 */
#pragma DATA_ALIGN(gSystem_tskMultiMbxStack, 32)
#pragma DATA_SECTION(gSystem_tskMultiMbxStack, ".bss:taskStackSection:systemTskMultiMbx")
UInt8 gSystem_tskMultiMbxStack[SYSTEM_TSK_MULTI_MBX_STACK_SIZE];


Utils_TskMultiMbxHndl gSystem_tskMultiMbx;


Utils_TskMultiMbxHndl *System_getTskMultiMbxHndl(void)
{
    char tskName[32];
    static Bool isInit = FALSE;

    if(!isInit)
    {
        snprintf(tskName, sizeof(tskName)-1U, "SYSTEM_TSK_MULTI_MBX");

        Utils_tskMultiMbxSetupTskHndl(
            &gSystem_tskMultiMbx,
            gSystem_tskMultiMbxStack,
            sizeof(gSystem_tskMultiMbxStack),
            SYSTEM_TSK_MULTI_MBX_TSK_PRI,
            UTILS_TASK_MULTI_MBX_RECV_QUE_MAX,
            tskName
            );

        isInit = (Bool)TRUE;
    }
    return &gSystem_tskMultiMbx;
}
