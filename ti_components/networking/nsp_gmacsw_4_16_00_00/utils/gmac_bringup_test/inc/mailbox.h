/*
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
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

/**
 *  \file  mailbox.h
 *
 *  \brief This file contains the function prototypes for Mail box access.
 */

#ifndef      MAILBOX_H_
#define      MAILBOX_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "hw_types.h"
#include "soc.h"
#include "hw_mailbox.h"

/* ======================================================================= */
/**
 * @def    User Id's Corresponds to the Core using the mailbox
 *         Mailbox Queue's Corresponds to the Mailbox Queue Number
 */
/* ======================================================================= */
/********************** MACROS ***************************/

/*  Mailbox Queue's */
#define MAILBOX_QUEUE_0         0U
#define MAILBOX_QUEUE_1         1U
#define MAILBOX_QUEUE_2         2U
#define MAILBOX_QUEUE_3         3U
#define MAILBOX_QUEUE_4         4U
#define MAILBOX_QUEUE_5         5U
#define MAILBOX_QUEUE_6         6U
#define MAILBOX_QUEUE_7         7U
#define MAILBOX_QUEUE_8         8U
#define MAILBOX_QUEUE_9         9U
#define MAILBOX_QUEUE_10        10U
#define MAILBOX_QUEUE_11        11U
#define MAILBOX_QUEUE_12        12U
#define MAILBOX_QUEUE_13        13U
#define MAILBOX_QUEUE_14        14U
#define MAILBOX_QUEUE_15        15U

#define MESSAGE_VALID           0U
#define MESSAGE_INVALID         1U

/*****************************************************************************
**                   FUNCTION DECLARATIONS
*****************************************************************************/

/*  Queue Access API's  */
/**
 *  This function resets the mailbox
 *
 * @param   baseAdd    It is the Memory address of the Mailbox instance.
 *                       MAILBOXn (n = 1 to 10) Ex MAILBOX1, MAILBOX2, etc
 *                       EVEn_MLBm (n = 1 to 3, m = 1 to 4)
 * @return    None
 */
void MailboxReset(uint32_t baseAdd);

/* ========================================================================= */
/**
 *  This function configures the idle mode of the mailbox
 *
 * @param   baseAdd    It is the Memory address of the Mailbox instance.
 * @param     idleMode  Idle mode to be configured. Possible values are
 *                      0x0: Force-idle. An idle request is acknowledged
 *                           unconditionally
 *                      0x1: No-idle. An idle request is never acknowledged
 *                      0x2: Smart-idle. Acknowledgement to an idle request is
 *                           given based on the internal activity of the module
 * @return    None
 */
void MailboxConfigIdleMode(uint32_t baseAdd, uint32_t idleMode);

/**
 *  This function gets the first message in the queue
 *
 * @param   baseAdd    It is the Memory address of the Mailbox instance.
 * @param     queueId   Queue to be read
 * @param     *msgPtr   Message pointer in which the message will be returned
 *
 * @return    Validity  The return value indicates whether the message is valid
 */
uint32_t MailboxGetMessage(uint32_t baseAdd, uint32_t queueId, uint32_t *msgPtr);

/**
 *  This function writes message in the queue
 *
 * @param   baseAdd    It is the Memory address of the Mailbox instance.
 * @param     queueId   Queue to be written
 * @param     msg       Message which has to be sent
 *
 * @return    status    The return value indicates whether the message is
 *                      written to the queue. Possible values are,
 *                          0   -   Written successfully
 *                          0   -   Queue full
 */
uint32_t MailboxSendMessage(uint32_t baseAdd, uint32_t queueId, uint32_t msg);

/*  Mailbox user(hw using mailbox) access API's */
/**
 *  This function enables the new message interrupt for a user for given queue
 *
 * @param   baseAdd    It is the Memory address of the Mailbox instance.
 * @param     userId    User for whom the new meaasge should be intimated
 * @param     queueId   Queue to be monitored for new message
 *
 * @return    None
 */
void MailboxEnableNewMsgInt(uint32_t baseAdd, uint32_t userId, uint32_t queueId);

/**
 *  This function enables the queue not full interrupt for a user for given
 *  queue
 *
 * @param   baseAdd    It is the Memory address of the Mailbox instance.
 * @param     userId    User for whom the event should be intimated
 * @param     queueId   Queue to be monitored for non-full condition
 *
 * @return    None
 */
void MailboxEnableQueueNotFullInt(uint32_t baseAdd, uint32_t userId,
                                  uint32_t queueId);

/**
 *  This function disables the new message interrupt for a user for given queue
 *
 * @param   baseAdd    It is the Memory address of the Mailbox instance.
 * @param     userId    User for whom the new meaasge event should be disabled
 * @param     queueId   Queue to be monitored for new message
 *
 * @return    None
 */
void MailboxDisableNewMsgInt(uint32_t baseAdd, uint32_t userId,
                             uint32_t queueId);

/**
 *  This function disables the queue not full interrupt for a user for given
 *  queue
 *
 * @param   baseAdd    It is the Memory address of the Mailbox instance.
 * @param     userId    User for whom the event should be disabled
 * @param     queueId   Queue for  which the non-full event to be disabled
 *
 * @return    None
 */
void MailboxDisableQueueNotFullInt(uint32_t baseAdd, uint32_t userId,
                                   uint32_t queueId);

/**
 *  This function clears the queue not-full status
 *
 * @param   baseAdd    It is the Memory address of the Mailbox instance.
 * @param     userId    User for whom the event should be cleared
 * @param     queueId   Queue for  which the event should be cleared
 *
 * @return    None
 */
void MailboxClrNewMsgStatus(uint32_t baseAdd, uint32_t userId, uint32_t queueId);

/**
 *  This function clears the queue not-full status
 *
 * @param   baseAdd    It is the Memory address of the Mailbox instance.
 * @param     userId    User for whom the event should be cleared
 * @param     queueId   Queue for  which the event should be cleared
 *
 * @return    None
 */
void MailboxClrQueueNotFullStatus(uint32_t baseAdd, uint32_t userId,
                                  uint32_t queueId);

/**
 *  This function gets the raw new message status
 *
 * @param   baseAdd    It is the Memory address of the Mailbox instance.
 * @param     userId    User for whom the event should be checked
 * @param     queueId   Queue for  which the event should be checked
 *
 * @return    status    status of new message
 */
uint32_t MailboxGetRawNewMsgStatus(uint32_t baseAdd, uint32_t userId,
                                   uint32_t queueId);

/**
 *  This function gets the raw queue not-full status
 *
 * @param   baseAdd    It is the Memory address of the Mailbox instance.
 * @param     userId    User for whom the event should be checked
 * @param     queueId   Queue for  which the event should be checked
 *
 * @return    status    Queue not full status
 */
uint32_t MailboxGetRawQueueNotFullStatus(uint32_t baseAdd, uint32_t userId,
                                         uint32_t queueId);

#ifdef __cplusplus
}
#endif

#endif
