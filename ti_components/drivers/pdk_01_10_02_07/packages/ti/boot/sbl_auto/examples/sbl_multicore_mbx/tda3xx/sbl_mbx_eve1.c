/**
 *  \file     sbl_mbx_eve1.c
 *
 *  \brief    This file contains SBL multicore mailbox binary for EVE1.
 *
 *  \details   IPU1 CPU0 sends message to IPU1 CPU1, DSP1, DSP2 and EVE1. Each
 *             core sends an acknowledgement after receiving message.
 *
 *  \copyright Copyright (C) 2014 Texas Instruments Incorporated -
 *             http://www.ti.com/
 */

/* ======================================================================
 *   Copyright (C) 2014 Texas Instruments Incorporated
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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/csl/csl_types.h>
#include <ti/csl/csl_mailbox.h>
#include <ti/csl/soc.h>

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
int32_t main()
{
    uint32_t msg = 0U;

    /* Wait for message from IPU1 CPU0 */
    while (MESSAGE_INVALID ==
           MailboxGetMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_3, &msg)) ;

    /* Send acknowledgement message to IPU1 CPU0 */
    MailboxSendMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_7, 0xAA55FF00);

    while (1) ;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

/* None */
