/* ======================================================================
 *   Copyright (C) 2013 Texas Instruments Incorporated
 *
 *   All rights reserved. Property of Texas Instruments Incorporated.
 *   Restricted rights to use, duplicate or disclose this code are
 *   granted through contract.
 *
 *   The program may not be used without the written permission
 *   of Texas Instruments Incorporated or against the terms and conditions
 *   stipulated in the agreement under which this program has been
 *   supplied.
 * ==================================================================== */
/*
 * main.c
 */
#include <ti/csl/csl_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/cslr_mailbox.h>

#define MESSAGE_VALID           0
#define MESSAGE_INVALID         1

/*  Mailbox Queue's */
#define MAILBOX_QUEUE_0         0
#define MAILBOX_QUEUE_1         1
#define MAILBOX_QUEUE_2         2
#define MAILBOX_QUEUE_3         3
#define MAILBOX_QUEUE_4         4
#define MAILBOX_QUEUE_5         5
#define MAILBOX_QUEUE_6         6
#define MAILBOX_QUEUE_7         7
#define MAILBOX_QUEUE_8         8
#define MAILBOX_QUEUE_9         9
#define MAILBOX_QUEUE_10            10
#define MAILBOX_QUEUE_11            11
#define MAILBOX_QUEUE_12            12
#define MAILBOX_QUEUE_13            13
#define MAILBOX_QUEUE_14            14
#define MAILBOX_QUEUE_15            15

uint32_t MailboxGetMessage(uint32_t baseAdd, uint32_t queueId, uint32_t *msgPtr)
{
    uint32_t msgCount;

    msgCount = HWREG(baseAdd + MAILBOX_MSGSTATUS(queueId));

    if (msgCount > 0)
    {
        /*    Read message    */
        *msgPtr = HWREG(baseAdd + MAILBOX_MESSAGE(queueId));
        return MESSAGE_VALID;
    }
    else
    {
        /*    Queue empty*/
        return MESSAGE_INVALID;
    }
}

uint32_t MailboxSendMessage(uint32_t baseAdd, uint32_t queueId, uint32_t msg)
{
    uint32_t fifoFull;

    /* Read the FIFO Status */
    fifoFull = HWREG(baseAdd + MAILBOX_FIFOSTATUS(queueId));
    if (fifoFull == 0)
    {
        /* FIFO not full write msg */
        HWREG(baseAdd + MAILBOX_MESSAGE(queueId)) = msg;
        return MESSAGE_VALID;
    }
    else
    {
        return MESSAGE_INVALID;
    }
}

void main(void) {
    uint32_t msg = 'D';

    /* Wait for message from MPU */
    while (MESSAGE_INVALID ==
           MailboxGetMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_6, &msg)) ;

    /* Send ack message to MPU */
    MailboxSendMessage(SOC_MAILBOX9_BASE, MAILBOX_QUEUE_0, 0xAA55FF00);
    while (1) ;
}

