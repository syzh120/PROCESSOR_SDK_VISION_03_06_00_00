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
 * \defgroup UTILS_BUF_API System Buffer Exchange API
 *
 * \brief This module define APIs to exchange system buffers between two tasks
 *        or links
 *
 *        Internally a buffer queue this consists of two queues
 *        - empty or input queue
 *        - full or output queue
 *
 *        The queue implementation uses fixed a size array based queue
 *        data structure, with mutual exclusion protection built inside the
 *        queue implementation.
 *
 *        Optional blocking of Get and/or Put operation is possible
 *
 *        The element that can be inserted/extracted from the queue is of
 *        type System_Buffer *
 *
 *        The basic operation is as below
 *
 *        - When a producer task needs to output some data, it firsts 'gets'
 *          an empty system buffer to output the data from the buffer handle.
 *        - The task outputs the data to the empty system buffer
 *        - The task then 'puts' this data as full data into the buffer handle
 *        - The consumer task, then 'gets' this full buffer from the buffer
 *          handle
 *        - After using or consuming this buffer, it 'puts' this buffer
 *          as empty buffer into this buffer handle.
 *        - This way buffers are exchanged between a producer and consumer.
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file utils_buf.h
 *
 * \brief System Buffer exchange API
 *
 * \version 0.0 (July 2013) : [KC] First version
 *
 *******************************************************************************
 */

#ifndef UTILS_BUF_H_
#define UTILS_BUF_H_

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <src/rtos/utils_common/include/utils_que.h>
#include <include/link_api/system_inter_link_api.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/**
 *******************************************************************************
 * \brief Maximum elements that can reside in a buffer queue
 *******************************************************************************
 */
#define UTILS_BUF_MAX_QUE_SIZE       (384U)

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
 *
 * \brief System Buffer Handle
 *
 *******************************************************************************
*/
typedef struct {

    Utils_QueHandle emptyQue;
    /**< Empty or input queue */

    Utils_QueHandle fullQue;
    /**< Full or output queue */

    System_Buffer *emptyQueMem[UTILS_BUF_MAX_QUE_SIZE];
    /**< Memory for empty queue elements */

    System_Buffer *fullQueMem[UTILS_BUF_MAX_QUE_SIZE];
    /**< Memory for full queue elements */

} Utils_BufHndl;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

Int32  Utils_bufCreate(Utils_BufHndl * pHndl, Bool blockOnGet, Bool blockOnPut);

Int32  Utils_bufDelete(Utils_BufHndl * pHndl);

Int32  Utils_bufGetEmpty(Utils_BufHndl * pHndl,
                        System_BufferList * pBufList, UInt32 timeout);

Int32  Utils_bufGetEmptyBuffer(Utils_BufHndl * pHndl,
                              System_Buffer ** pBuf, UInt32 timeout);

Int32  Utils_bufPutEmpty(Utils_BufHndl * pHndl, System_BufferList * pBufList);

Int32  Utils_bufPutEmptyBuffer(Utils_BufHndl * pHndl, System_Buffer * pBuf);

UInt32 Utils_bufGetEmptyBufferCount(const Utils_BufHndl * pHndl);
static inline System_Buffer *Utils_bufPeekEmpty(const Utils_BufHndl * pHndl);
static inline System_Buffer *Utils_bufPeekFull(const Utils_BufHndl * pHndl);

/**
 *******************************************************************************
 *
 * \brief Peek into empty queue
 *
 *        This only peeks at the top of the queue but does not remove the
 *        buffer from the queue
 *
 * \param pHndl        [IN] Buffer handle
 *
 * \return buffer pointer if buffer is present in the empty queue, else NULL
 *
 *******************************************************************************
 */
static inline System_Buffer *Utils_bufPeekEmpty(const Utils_BufHndl * pHndl)
{
    System_Buffer *pBuf;

    /* MISRA.CAST.PTR
     * MISRAC_2004_Rule_11.4
     * MISRAC_WAIVER:
     * Generic implementation of quePeek requires argument in Ptr *
     * format, so typecasting.
     */
    Utils_quePeek(&pHndl->emptyQue, (Ptr *) & pBuf);

    return pBuf;
}

Int32  Utils_bufGetFull(Utils_BufHndl * pHndl,
                       System_BufferList * pBufList, UInt32 timeout);

Int32  Utils_bufGetFullBuffer(Utils_BufHndl * pHndl,
                             System_Buffer ** pBuf, UInt32 timeout);

Int32  Utils_bufPutFull(Utils_BufHndl * pHndl, System_BufferList * pBufList);

Int32  Utils_bufPutFullBuffer(Utils_BufHndl * pHndl, System_Buffer * pBuf);

UInt32 Utils_bufGetFullBufferCount(const Utils_BufHndl * pHndl);

/**
 *******************************************************************************
 *
 * \brief Peek into full queue
 *
 *        This only peeks at the top of the queue but does not remove the
 *        buffer from the queue
 *
 * \param pHndl        [IN] Buffer handle
 *
 * \return buffer pointer if buffer is present in the full queue, else NULL
 *
 *******************************************************************************
*/
static inline System_Buffer *Utils_bufPeekFull(const Utils_BufHndl * pHndl)
{
    System_Buffer *pBuf;

    /* MISRA.CAST.PTR
     * MISRAC_2004_Rule_11.4
     * MISRAC_WAIVER:
     * Generic implementation of quePeek requires argument in Ptr *
     * format, so typecasting.
     */
    Utils_quePeek(&pHndl->fullQue, (Ptr *) & pBuf);

    return pBuf;
}

Void   Utils_bufPrintStatus(UInt8 *str, Utils_BufHndl * pHndl);

Int32  Utils_bufInitFrame(FVID2_Frame *pFrame, System_Buffer *pBuffer);

#endif

/* @} */

