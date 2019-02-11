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
 * \ingroup FRAMEWORK_MODULE_API
 * \defgroup SYSTEM_WORK_QUEUE_API System Work Queue API
 *
 *
 * @{
 *******************************************************************************
*/

/**
 *******************************************************************************
 *
 * \file   system_work_queue_if.h
 *
 * \brief  System Work Queue API
 *
 *   The APIs defined in this module are used to submit work from a host CPU to
 *   a remote CPU
 *
 *******************************************************************************
 */

#ifndef SYSTEM_WORK_QUEUE_IF_H_
#define SYSTEM_WORK_QUEUE_IF_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * Includes
 *******************************************************************************
 */

#include <include/link_api/system.h>


/*******************************************************************************
 *  Defines
 *******************************************************************************
 */


/**
 *******************************************************************************
 * \brief Flag to tell alloc API to use semaphore for ACK
 *******************************************************************************
 */
#define SYSTEM_WORK_OBJ_ALLOC_FLAG_USE_ACK_SEM       (0x00000001U)

/**
 *******************************************************************************
 * \brief Identifier for a invalid work object
 *******************************************************************************
 */
#define SYSTEM_WORK_OBJ_INVALID             (0xFFFFU)

/**
 *******************************************************************************
 * \brief Wait for ever timeout
 *******************************************************************************
 */
#define SYSTEM_WORK_TIMEOUT_FOREVER        (0xFFFFFFFFU)


/**
 *******************************************************************************
 * \brief In and out argument pointer and size passed to work object
 *        MUST be aligned to this value
 *******************************************************************************
 */
#define SYSTEM_WORK_ARGS_ALIGN              (256U)



/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

/**
 *******************************************************************************
 * \brief Handle to identify a work obj
 *******************************************************************************
 */
typedef UInt16 System_WorkObjId;

/**
 *******************************************************************************
 * \brief User callback to call after completion of work object execution
 *
 * \param workObjId [IN] Work Object that finished execution
 * \param pUserObj  [IN] User register object passed back to the user
 *
 *******************************************************************************
 */
typedef Void (*System_WorkUserCallback)(System_WorkObjId workObjId, Void *pUserObj);

/**
 *******************************************************************************
 * \brief Handler for a work function
 *
 * \param workFxnId [IN] Work function to execute
 * \param workCmdId [IN] Command to execute within the work function
 * \param pInArgs   [IN] Pointer to user supplied input arguments
 * \param inArgsSize[IN] Size fo input argument structure
 * \param pOutArgs  [OUT] Pointer to user supplied output arguments
 * \param outArgsSize[IN] Size for output argument structure
 *******************************************************************************
 */
typedef UInt32 (*System_WorkHandler)(
                UInt16 workFxnId,
                UInt16 workCmdId,
                Void *pInArgs,
                UInt32 inArgsSize,
                Void *pOutArgs,
                UInt32 outArgsSize);


/*******************************************************************************
 *  Functions Prototypes
 *******************************************************************************
 */


/**
 *******************************************************************************
 * \brief Allocate a work object ID from a pre-defined pool
 *
 * \param workObjId [OUT] Allocated work obj ID
 * \param allocFlags [IN]  Flags which control the allocation
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 System_workAllocObj(System_WorkObjId *workObjId, UInt32 allocFlags);

/**
 *******************************************************************************
 * \brief Free a previously allocated work object
 *
 *        After API is successful, workObjId is set to SYSTEM_WORK_OBJ_INVALID
 *
 * \param workObjId [IN/OUT] work obj ID
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 System_workFreeObj(System_WorkObjId *workObjId);

/**
 *******************************************************************************
 * \brief Reset work obj ID state to initial state just after alloc
 *
 * \param workObjId [IN] work obj ID
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 System_workResetObj(System_WorkObjId workObjId);

/**
 *******************************************************************************
 * \brief Set input arguments for work obj ID
 *
 * \param workObjId  [IN] work obj ID
 * \param pInArgs    [IN] pointer to input args
 *                        (MUST be aligned to SYSTEM_WORK_ARGS_ALIGN)
 * \param inArgsSize [IN] input args size
 *                        (MUST be aligned to SYSTEM_WORK_ARGS_ALIGN)
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 System_workSetInArgs(System_WorkObjId workObjId, Void *pInArgs, UInt32 inArgsSize);

/**
 *******************************************************************************
 * \brief Set output arguments for work obj ID
 *
 * \param workObjId  [IN] work obj ID
 * \param pOutArgs   [IN] pointer to output args
 *                        (MUST be aligned to SYSTEM_WORK_ARGS_ALIGN)
 * \param outArgsSize [IN] output args size
 *                        (MUST be aligned to SYSTEM_WORK_ARGS_ALIGN)
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 System_workSetOutArgs(System_WorkObjId workObjId, Void *pOutArgs, UInt32 outArgsSize);

/**
 *******************************************************************************
 * \brief Set command to execute
 *
 * \param workObjId  [IN] work obj ID
 * \param workFxnId  [IN] Work function ID
 * \param cmdId      [IN] Command ID
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 System_workSetCommand(System_WorkObjId workObjId, UInt16 workFxnId, UInt16 cmdId);

/**
 *******************************************************************************
 * \brief Register user callback to call for a given work object completion
 *
 * \param workObjId  [IN] work obj ID
 * \param callback   [IN] user callback
 * \param pUserObj   [IN] user context to getback with this callback
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 System_workSetCallback(System_WorkObjId workObjId,
                        System_WorkUserCallback callback, Void *pUserObj);

/**
 *******************************************************************************
 * \brief Submit work for execution on a remote CPU
 *
 * \param workObjId  [IN] work obj ID
 * \param dstCpuId   [IN] CPU on which to execute this work
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 System_workSubmit(System_WorkObjId workObjId, UInt32 dstCpuId);

/**
 *******************************************************************************
 * \brief Wait for work execution to complete
 *
 * \param workObjId     [IN] work obj ID
 * \param timeout       [IN] timeout in OS ticks
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 System_workWaitComplete(System_WorkObjId workObjId, UInt32 timeout);

/**
 *******************************************************************************
 * \brief Return status value after work function execution
 *
 * \param workObjId     [IN] work obj ID
 * \param workStatus    [OUT] work status
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 System_workGetStatus(System_WorkObjId workObjId, UInt32 *workStatus);

/**
 *******************************************************************************
 * \brief Associate a hander with a workFxn
 *
 * \param workFxnId     [IN] work function ID. MUST unique for given CPU
 * \param pHandler      [IN] Handler to call when work object with workFxnId is
 *                           received
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 System_workHandlerRegister(UInt16 workFxnId, System_WorkHandler pHandler);




#ifdef  __cplusplus
}
#endif

#endif

/*@}*/


