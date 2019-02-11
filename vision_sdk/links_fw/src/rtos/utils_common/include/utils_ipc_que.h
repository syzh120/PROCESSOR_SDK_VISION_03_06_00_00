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
 * \ingroup UTILS_API
 * \defgroup UTILS_IPC_QUE_API IPC Software Queue API
 *
 * \brief This module defines the APIs for a software queue which is used for
 *        inter processor communication
 *
 *        The software queue implmentation is a fixed size, NON-LOCKING
 *        array based queue for simplicity and performance.
 *
 *        The APIs take care fo mutual exclusion protection via interuupt locks
 *        for threads running on the same processor.
 *
 *        The API DOES NOT support blocking 'get' and 'put' APIs. This needs to
 *        be taken care by the user of the API
 *
 *        Since the implementation does not take inter processors locks, it
 *        is important that there be exactly one CPU which is the "writer"
 *        and exactly one CPU which is the "reader"
 *
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file utils_ipc_que.h
 *
 * \brief IPC Software Queue API
 *
 * \version 0.0 (July 2013) : [KC] First version
 *
 *******************************************************************************
 */

#ifndef UTILS_IPC_QUE_H_
#define UTILS_IPC_QUE_H_

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <src/rtos/utils_common/include/utils.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */


/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */

/*******************************************************************************
 *  Data structure's
 *******************************************************************************
 */




/**
 *******************************************************************************
 * \brief Queue Handle
 *
 *        Typically user does not need to know internals of queue handle
 *        data structure
 *******************************************************************************
*/
typedef struct {

  UInt32 elementSize;
  /**< Size of individual element in units of bytes */

  UInt32 maxElements;
  /**< Max elements that be present in the queue  */

  Ptr    sharedMemBaseAddr;
  /**< Address of shared memory area of the queue */

} Utils_IpcQueHandle;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

Int32  Utils_ipcQueCreate(Utils_IpcQueHandle * handle,
                            UInt32 maxElements,
                            Ptr sharedMemBaseAddr,
                            UInt32 elementSize);

Int32  Utils_ipcQueReset(Utils_IpcQueHandle * handle,
                            Ptr sharedMemBaseAddr,
                            Bool resetRdIdx,
                            Bool resetWrIdx
                        );

Int32  Utils_ipcQueDelete(const Utils_IpcQueHandle * handle);

Int32  Utils_ipcQueWrite(const Utils_IpcQueHandle * handle,
                         const volatile UInt8 *data,
                         volatile UInt32 dataSize);

Int32  Utils_ipcQueRead(const Utils_IpcQueHandle * handle,
                        volatile UInt8 *data,
                        volatile UInt32 dataSize);

UInt32 Utils_ipcQueIsEmpty(const Utils_IpcQueHandle * handle);

UInt32 Utils_ipcQueIsFull(const Utils_IpcQueHandle * handle);

Int32 Utils_ipcQueWriteString(const Utils_IpcQueHandle * handle, const char pString[]);
Int32 Utils_ipcQueReadString(const Utils_IpcQueHandle * handle, char pString[], UInt32 *strSize);

#endif

/* @} */
