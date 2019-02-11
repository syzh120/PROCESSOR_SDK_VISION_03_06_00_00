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
 *
 * \ingroup GATE_LINK_API
 * \defgroup GATE_LINK_IMPL Gate Link Implementation
 *
 * @{
 */

/**
 *******************************************************************************
 *
 * \file gateLink_priv.h Gate Link private API/Data structures
 *
 * \brief  This file is a private header file for gate link implementation
 *         This file lists the data structures, function prototypes which are
 *         implemented and used as a part of gate link.
 *
 * \version 0.0 (Apr 2015) : [YM] First version
 *
 *******************************************************************************
 */

#ifndef GATE_LINK_PRIV_H_
#define GATE_LINK_PRIV_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <src/rtos/links_ipu/system/system_priv_ipu1_0.h>
#include <include/link_api/gateLink.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

 /**
 *******************************************************************************
 *
 * \brief Maximum number of gate link objects
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define GATE_LINK_OBJ_MAX    (4U)

/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */

/**
 *******************************************************************************
 *  \brief Enumerations for AVB Src notification types
 *
 *  SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
typedef enum
{
    GATE_LINK_OPERATION_STATUS_ON = 0U,
    /**< Switches the operation on at runtime
     *   It it indicates gate link can forward the data to next link */

    GATE_LINK_OPERATION_STATUS_OFF = 1U,
    /**< Switches the operation off at runtime
     *   It it indicates gate link can not forward the data to next link
     */

    GATE_LINK_OPERATION_STATUE_FORCE32BITS = 0x7FFFFFFFU
     /**< This should be the last value after the max enumeration value.
      *   This is to make sure enum size defaults to 32 bits always regardless
      *   of compiler.
      */
} GateLink_OperationStatus;



/*******************************************************************************
 *  Data structure's
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief Structure to hold all Gate link related information
 *
 *******************************************************************************
 */
typedef struct {
    UInt32 tskId;
    /**< Placeholder to store gate link task id */

    char name[32];
    /**< Link name */

    UInt32 state;
    /**< Link state, one of SYSTEM_LINK_STATE_xxx */

    Utils_TskHndl tsk;
    /**< Handle to capture link task */

    GateLink_OperationStatus opStatus;
    /**< Decision on received buffer is taken based on this,
     *   Buffers are forwarded as it is or returned back
     */

    Int32 bufCount;
    /**< This signifies number of buffers to be released by
      *  gate link, this is useful while turning opStatus on->off
      *  or off->on */

    BspOsal_SemHandle lock;
    /**< Link level lock, used while updating the link params */

    GateLink_CreateParams createArgs;
    /**< Create params for gate link */

} GateLink_Obj;

extern GateLink_Obj gGateLink_obj[GATE_LINK_OBJ_MAX];

/**
 *******************************************************************************
 *
 *   \brief Gate link's task
 *
 *   \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Void GateLink_tskMain(struct Utils_TskHndl_t * pTsk, Utils_MsgHndl * pMsg);

/**
 *******************************************************************************
 *
 *   \brief Gate link's task creation fuciton
 *
 *   \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 GateLink_tskCreate(UInt32 instId);

/**
 *******************************************************************************
 *
 *   \brief Gate link's driver creation fuction
 *
 *   \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/

Int32 GateLink_drvCreate(GateLink_Obj * pObj, const GateLink_CreateParams * pPrm);

/**
 *******************************************************************************
 *
 *   \brief Gate link's Process Data functions actually process buffers at
 *          runtime
 *
 *   \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 GateLink_drvProcessData(GateLink_Obj * pObj);

/**
 *******************************************************************************
 *
 *   \brief Gets buffers to be processed from input queue
 *
 *   \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 GateLink_getFullBuffers(Void * ptr, UInt16 queId,
                            System_BufferList * pBufList);

/**
 *******************************************************************************
 *
 *   \brief Provides Link info to the caller
 *
 *   \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 GateLink_getLinkInfo(Void * ptr, System_LinkInfo * info);

/**
 *******************************************************************************
 *
 *   \brief Releases processed buffers
 *
 *   \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 GateLink_putEmptyBuffers(Void * ptr, UInt16 queId,
                              System_BufferList * pBufList);
/**
 *******************************************************************************
 *
 *   \brief Gate link's driver delete fuciton
 *
 *   \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 GateLink_drvDelete(GateLink_Obj * pObj);



#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */


