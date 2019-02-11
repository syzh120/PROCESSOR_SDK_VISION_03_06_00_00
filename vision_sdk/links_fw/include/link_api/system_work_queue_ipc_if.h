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

#ifndef SYSTEM_WORK_QUEUE_IPC_H_
#define SYSTEM_WORK_QUEUE_IPC_H_

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <include/link_api/system_work_queue_if.h>

#define SYSTEM_WORK_MAX_OBJ_PER_CPU     (32U)

#define SYSTEM_WORK_OBJ_SRC_CPU_MASK    ((UInt32)0x0F00U)
#define SYSTEM_WORK_OBJ_SRC_CPU_SHIFT   ((UInt32) 8U)
#define SYSTEM_WORK_OBJ_INST_MASK       ((UInt32)0x00FFU)
#define SYSTEM_WORK_OBJ_INST_SHIFT      ((UInt32) 0U)

#define SYSTEM_WORK_OBJ_FLAG_IS_FREE          ((UInt32)0x00000001U)
#define SYSTEM_WORK_OBJ_FLAG_IS_ACK_REQUIRED  ((UInt32)0x00000002U)
#define SYSTEM_WORK_OBJ_FLAG_IS_ACK           ((UInt32)0x00000004U)

#define SYSTEM_WORK_OBJ_FXN_ID_MASK           ((UInt32)0xFFFF0000U)
#define SYSTEM_WORK_OBJ_FXN_ID_SHIFT          ((UInt32)16U)
#define SYSTEM_WORK_OBJ_CMD_ID_MASK           ((UInt32)0x0000FFFFU)
#define SYSTEM_WORK_OBJ_CMD_ID_SHIFT          ((UInt32)0U)

typedef struct {

    UInt32 fxnIdCmdId;
    UInt32 flags;
    UInt32 *pInArgs;
    UInt32 inArgsSize;
    UInt32 *pOutArgs;
    UInt32 outArgsSize;
    UInt32 status;
    Void   *pSemaphore;
    System_WorkUserCallback userCallback;
    Void   *pUserObj;
} System_Work;

typedef struct {

    System_Work obj[SYSTEM_PROC_MAX][SYSTEM_WORK_MAX_OBJ_PER_CPU];

} System_WorkIpcObj;

static Void System_workSetIsFree(System_Work *pWork, Bool isFree);
static Void System_workSetIsAck(System_Work *pWork, Bool isAck);
static Void System_workSetIsAckRequired(System_Work *pWork, Bool isAckRequired);
static Bool System_workGetIsAck(const System_Work *pWork);
static Bool System_workGetIsAckRequired(const System_Work *pWork);
static Bool System_workGetIsFree(const System_Work *pWork);
static System_WorkObjId System_workMakeWorkObjId(UInt16 instId, UInt16 srcCpuId);
static UInt16 System_workGetWorkObjInst(System_WorkObjId workObjId);
static UInt16 System_workGetWorkObjSrcCpu(System_WorkObjId workObjId);
static Void System_workMakeFxnIdCmdId(System_Work *pWork, UInt16 fxnId, UInt16 cmdId);
static UInt16 System_workGetFxnId(const System_Work *pWork);
static UInt16 System_workGetCmdId(const System_Work *pWork);

/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: Waiver for static inline functions defined in header file
 *                doing init of interface structure and small functions for
 *                performance reasons.
 */
static inline Void System_workSetIsFree(System_Work *pWork, Bool isFree)
{
    if(isFree)
    {
        pWork->flags |= SYSTEM_WORK_OBJ_FLAG_IS_FREE;
    }
    else
    {
        pWork->flags &= ~SYSTEM_WORK_OBJ_FLAG_IS_FREE;
    }
}

/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: Waiver for static inline functions defined in header file
 *                doing init of interface structure and small functions for
 *                performance reasons.
 */
static inline Void System_workSetIsAck(System_Work *pWork, Bool isAck)
{
    if(isAck)
    {
        pWork->flags |= SYSTEM_WORK_OBJ_FLAG_IS_ACK;
    }
    else
    {
        pWork->flags &= ~SYSTEM_WORK_OBJ_FLAG_IS_ACK;
    }
}

/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: Waiver for static inline functions defined in header file
 *                doing init of interface structure and small functions for
 *                performance reasons.
 */
static inline Void System_workSetIsAckRequired(System_Work *pWork, Bool isAckRequired)
{
    if(isAckRequired)
    {
        pWork->flags |= SYSTEM_WORK_OBJ_FLAG_IS_ACK_REQUIRED;
    }
    else
    {
        pWork->flags &= ~SYSTEM_WORK_OBJ_FLAG_IS_ACK_REQUIRED;
    }
}

/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: Waiver for static inline functions defined in header file
 *                doing init of interface structure and small functions for
 *                performance reasons.
 */
static inline Bool System_workGetIsAck(const System_Work *pWork)
{
    return (pWork->flags & SYSTEM_WORK_OBJ_FLAG_IS_ACK) ? TRUE : FALSE;
}

/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: Waiver for static inline functions defined in header file
 *                doing init of interface structure and small functions for
 *                performance reasons.
 */
static inline Bool System_workGetIsAckRequired(const System_Work *pWork)
{
    return (pWork->flags & SYSTEM_WORK_OBJ_FLAG_IS_ACK_REQUIRED) ? TRUE : FALSE;
}

/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: Waiver for static inline functions defined in header file
 *                doing init of interface structure and small functions for
 *                performance reasons.
 */
static inline Bool System_workGetIsFree(const System_Work *pWork)
{
    return (pWork->flags & SYSTEM_WORK_OBJ_FLAG_IS_FREE) ? TRUE : FALSE;
}

/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: Waiver for static inline functions defined in header file
 *                doing init of interface structure and small functions for
 *                performance reasons.
 */
static inline System_WorkObjId System_workMakeWorkObjId(UInt16 instId, UInt16 srcCpuId)
{
    return
        (System_WorkObjId)((((UInt32)instId << SYSTEM_WORK_OBJ_INST_SHIFT) & SYSTEM_WORK_OBJ_INST_MASK)
        |
        (((UInt32)srcCpuId << SYSTEM_WORK_OBJ_SRC_CPU_SHIFT) & SYSTEM_WORK_OBJ_SRC_CPU_MASK))
        ;
}

/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: Waiver for static inline functions defined in header file
 *                doing init of interface structure and small functions for
 *                performance reasons.
 */
static inline UInt16 System_workGetWorkObjInst(System_WorkObjId workObjId)
{
    return
        (UInt16)((workObjId & SYSTEM_WORK_OBJ_INST_MASK) >> SYSTEM_WORK_OBJ_INST_SHIFT)
        ;
}

/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: Waiver for static inline functions defined in header file
 *                doing init of interface structure and small functions for
 *                performance reasons.
 */
static inline UInt16 System_workGetWorkObjSrcCpu(System_WorkObjId workObjId)
{
    return
        (UInt16)((workObjId & SYSTEM_WORK_OBJ_SRC_CPU_MASK) >> SYSTEM_WORK_OBJ_SRC_CPU_SHIFT)
        ;
}

/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: Waiver for static inline functions defined in header file
 *                doing init of interface structure and small functions for
 *                performance reasons.
 */
static inline Void System_workMakeFxnIdCmdId(System_Work *pWork, UInt16 fxnId, UInt16 cmdId)
{
    pWork->fxnIdCmdId =
        (UInt32)
        ((UInt32)(((UInt32)fxnId << SYSTEM_WORK_OBJ_FXN_ID_SHIFT) & SYSTEM_WORK_OBJ_FXN_ID_MASK)
        |
        (UInt32)(((UInt32)cmdId << SYSTEM_WORK_OBJ_CMD_ID_SHIFT) & SYSTEM_WORK_OBJ_CMD_ID_MASK))
        ;
}

/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: Waiver for static inline functions defined in header file
 *                doing init of interface structure and small functions for
 *                performance reasons.
 */
static inline UInt16 System_workGetFxnId(const System_Work *pWork)
{
    return
        (UInt16)((pWork->fxnIdCmdId & SYSTEM_WORK_OBJ_FXN_ID_MASK) >> SYSTEM_WORK_OBJ_FXN_ID_SHIFT)
        ;
}

/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: Waiver for static inline functions defined in header file
 *                doing init of interface structure and small functions for
 *                performance reasons.
 */
static inline UInt16 System_workGetCmdId(const System_Work *pWork)
{
    return
        (UInt16)((pWork->fxnIdCmdId & SYSTEM_WORK_OBJ_CMD_ID_MASK) >> SYSTEM_WORK_OBJ_CMD_ID_SHIFT)
        ;
}

#endif


