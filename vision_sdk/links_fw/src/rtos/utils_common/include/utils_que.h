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
 * \defgroup UTILS_QUE_API Software Queue API
 *
 * \brief This module defines the APIs for a software queue
 *
 *        This software queue is used to build multiple software constructs
 *        like message box, buffer queue.
 *
 *        The software queue implmenetation is a fixed size arrary based queue
 *        for simplicity and performance. The APIs take care fo mutual
 *        exclusion protection via interuupt locks. The API optionally support
 *        blocking 'get' and 'put' APIs
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file utils_que.h
 *
 * \brief Software Queue API
 *
 * \version 0.0 (July 2013) : [KC] First version
 *
 *******************************************************************************
 */

#ifndef UTILS_QUE_H_
#define UTILS_QUE_H_

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <src/rtos/utils_common/include/utils.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/* @{ */

/**
 *******************************************************************************
 * \brief Queue Flag: Do not block on que get and que put,
 *******************************************************************************
 */
#define UTILS_QUE_FLAG_NO_BLOCK_QUE    (0x00000000U)

/**
 *******************************************************************************
 * \brief Queue Flag: Block on que put if que is full
 *******************************************************************************
 */
#define UTILS_QUE_FLAG_BLOCK_QUE_PUT   (0x00000001U)

/**
 *******************************************************************************
 * \brief Queue Flag: Block on que get if que is empty
 *******************************************************************************
 */
#define UTILS_QUE_FLAG_BLOCK_QUE_GET   (0x00000002U)

/**
 *******************************************************************************
 * \brief Queue Flag: Block on que put if que is full, Block on que get if que
 *                    is empty
 *******************************************************************************
 */
#define UTILS_QUE_FLAG_BLOCK_QUE       (0x00000003U)

/* @} */

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

  UInt32 curRd;
  /**< Current read index */

  UInt32 curWr;
  /**< Current write index  */

  UInt32 count;
  /**< Count of element in queue  */

  UInt32 maxElements;
  /**< Max elements that be present in the queue  */

  Ptr *queue;
  /**< Address of data area of the queue elements */

  BspOsal_SemHandle semRd;
  /**< Read semaphore */

  BspOsal_SemHandle semWr;
  /**< Write semaphore  */

  UInt32 flags;
  /**< Controls how APIs behave internally, i.e blocking wait or non-blocking */

  volatile Bool blockedOnGet;
  /**< Flag indicating queue is blocked on get operation */

  volatile Bool blockedOnPut;
  /**< Flag indicating queue is blocked on put operation */

  volatile Bool forceUnblockGet;
  /**< Flag indicating forced unblock of queueGet */

  volatile Bool forceUnblockPut;
  /**< Flag indicating forced unblock of queuePut */

} Utils_QueHandle;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

Int32  Utils_queCreate(Utils_QueHandle * handle,
                      UInt32 maxElements, Ptr queueMem, UInt32 flags);

Int32  Utils_queDelete(Utils_QueHandle * handle);

Int32  Utils_quePut(Utils_QueHandle * handle, Ptr data, UInt32 timeout);

Int32  Utils_queGet(Utils_QueHandle * handle,
                   Ptr * data, UInt32 minCount, UInt32 timeout);

Int32  Utils_quePeek(const Utils_QueHandle * handle, Ptr * data);

UInt32 Utils_queIsEmpty(const Utils_QueHandle * handle);

UInt32 Utils_queIsFull(const Utils_QueHandle * handle);

UInt32 Utils_queGetQueuedCount(const Utils_QueHandle * handle);

Int32  Utils_queUnBlock(Utils_QueHandle * handle);

Int32  Utils_queReset(Utils_QueHandle * handle);

#endif

/* @} */
