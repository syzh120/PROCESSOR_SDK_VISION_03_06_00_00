/*
 * Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/

#ifndef TFDTP_QUEUE_H_
#define TFDTP_QUEUE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "tfdtp_types.h"

typedef struct queue_t_
{
    /*! The current number of entries in the queue */
    uint32_t count;
    /*! The top of the queue */
    node_t *pHead;
    /*! The end of the queue */
    node_t *pTail;
} queue_t;

/*! \brief Initializes the packet queue - does not free or dequeue
 * \ingroup group_tfdtp
 */
extern void         TFDTP_queueInit(queue_t *pQueue);
/*! \brief Does a shallow copy of the source queue
 * \ingroup group_tfdtp
 */
extern void         TFDTP_queueCopy(queue_t *pDstQueue, const queue_t *pSrcQueue);
/*! \brief Thread safe queuing to the tail of the queue
 * \ingroup group_tfdtp
 */
extern void         TFDTP_enqueue(queue_t *pQueue, node_t *pNode);
/*! \brief Thread safe queuing at the head of the queue
 * \ingroup group_tfdtp
 */
extern void         TFDTP_enqueueHead(queue_t *pQueue, node_t *pNode);
/*! \brief Thread safe dequeue from the head of the queue
 * \ingroup group_tfdtp
 */
extern node_t      *TFDTP_dequeue(queue_t *pQueue);
/*! \brief Appending one queue to another at the tail
 * \ingroup group_tfdtp
 */
extern void         TFDTP_appendQueue(queue_t *pDstQueue, const queue_t *pSrcQueue);

#ifdef __cplusplus
}
#endif
#endif /* TFDTP_QUEUE_H_ */
