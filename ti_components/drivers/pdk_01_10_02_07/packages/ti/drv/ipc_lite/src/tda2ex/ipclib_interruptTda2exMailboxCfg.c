/*
 *   Copyright (c) Texas Instruments Incorporated 2016
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
 *  @file   ipclib_interruptTda2exMailboxCfg.c
 *
 *  @brief  This file contains platform specific configuration
 *          for ipclib interrupt module.
 *
 *
 */

/*_______________________________ Include Files _____________________________*/
#include <stdint.h>
#include <stdlib.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/soc.h>
#include <ipclib_interrupt_priv.h>

/* Maibox base adderesses*/

/* Initialize mailbox base address table */
uint32_t IpcLib_gMailboxBaseAddr[IPCLIB_MAX_MAILBOXES] = {
    SOC_MAILBOX5_BASE,                          /* System Mailbox 5 */
    SOC_MAILBOX6_BASE,                          /* System Mailbox 6 */
    SOC_MAILBOX7_BASE,                          /* System Mailbox 7 */
    SOC_MAILBOX8_BASE,                          /* System Mailbox 8 */
    IPCLIB_INVALID_INFO,                        /* Free mailbox enry */
    IPCLIB_INVALID_INFO,                        /* Free mailbox enry */
    IPCLIB_INVALID_INFO,                        /* Free mailbox enry */
    IPCLIB_INVALID_INFO,                        /* Free mailbox enry */
    IPCLIB_INVALID_INFO,                        /* Free mailbox enry */
    IPCLIB_INVALID_INFO,                        /* Free mailbox enry */
    IPCLIB_INVALID_INFO,                        /* Free mailbox enry */
    IPCLIB_INVALID_INFO,                        /* Free mailbox enry */
    IPCLIB_INVALID_INFO,                        /* Free mailbox enry */
    IPCLIB_INVALID_INFO,                        /* Free mailbox enry */
    IPCLIB_INVALID_INFO,                        /* Free mailbox enry */
    IPCLIB_INVALID_INFO                         /* Free mailbox enry */
};

/**
 * DES_ID : DOX_DES_TAG(DES_IPC_LITE_004)
 */
/**
 * REQ_ID : DOX_REQ_TAG(PDK-1409) DOX_REQ_TAG(PDK-1429) DOX_REQ_TAG(PDK-1432)
 */
/* Mailbox mapping for cores in TDA2xx */
IpcLib_InterruptMailboxCfg IpcLib_gMailboxConfig[IPCLIB_MAX_PROC][
    IPCLIB_MAX_PROC] = {
    /* DSP1 as SRC */
    /* Mbx Usr Fifo */
    {
        {IE, IE, IE},      /* DSP1 -> DSP1   */
        {0U, 1U, 0U},      /* DSP1 -> IPU1_0 */
        {2U, 3U, 1U},      /* DSP1 -> IPU2_0 */
        {0U, 2U, 1U},      /* DSP1 -> HOST   */
        {0U, 3U, 2U},      /* DSP1 -> IPU1_1 */
        {3U, 3U, 0U}       /* DSP1 -> IPU2_1 */
    },


    /* IPU1_0 as SRC */
    /* Mbx Usr Fifo */
    {
        {0U, 0U, 3U},      /* IPU1_0 -> DSP1   */
        {IE, IE, IE},      /* IPU1_0 -> IPU1_0 */
        {2U, 3U, 5U},      /* IPU1_0 -> IPU2_0 */
        {0U, 2U, 4U},      /* IPU1_0 -> HOST   */
        {3U, 2U, 4U},      /* IPU1_0 -> IPU1_1 */
        {3U, 3U, 1U}       /* IPU1_0 -> IPU2_1 */
    },
    /* IPU2_0 as SRC */
    /* Mbx Usr Fifo */
    {
        {2U, 0U, 6U},      /* IPU2_0 -> DSP1   */
        {2U, 2U, 7U},      /* IPU2_0 -> IPU1_0 */
        {IE, IE, IE},      /* IPU2_0 -> IPU2_0 */
        {1U, 2U, 4U},      /* IPU2_0 -> HOST   */
        {3U, 2U, 3U},      /* IPU2_0 -> IPU1_1 */
        {IE,  IE, IE}      /* IPU2_0 -> IPU2_1 */ /* new */
    },

    /* A15 as SRC */
    /* Mbx Usr Fifo */
    {
        {0U, 0U, 5U},      /* A15 -> DSP1   */
        {0U, 1U, 6U},      /* A15 -> IPU1_0 */
        {1U, 1U, 6U},      /* A15 -> IPU2_0 */
        {IE, IE, IE},      /* A15 -> HOST   */
        {0U, 3U, 7U},      /* A15 -> IPU1_1 */
        {1U, 3U, 7U}       /* A15 -> IPU2_1 */
    },

    /* IPU1_1 as SRC */
    /* Mbx Usr Fifo */
    {

        {0U, 0U, 8U},      /* IPU1_1 -> DSP1   */
        {2U, 2U, 8U},      /* IPU1_1 -> IPU1_0 */
        {3U, 3U, 2U},      /* IPU1_1 -> IPU2_0 */
        {0U, 2U, 9U},      /* IPU1_1 -> HOST   */
        {IE, IE, IE},      /* IPU1_1 -> IPU1_1 */
        {IE, IE, IE}       /* IPU1_1 -> IPU2_1 */ /* new */
    },
    /* IPU2_1 as SRC */
    /* Mbx Usr Fifo */
    {
        {3U, 0U, 2U},      /* IPU2_1 -> DSP1   */
        {3U, 2U, 3U},      /* IPU2_1 -> IPU1_0 */
        {IE, IE, IE},      /* IPU2_1 -> IPU2_0 */ /* new */
        {1U, 2U, 9U},      /* IPU2_1 -> HOST   */
        {IE, IE, IE},      /* IPU2_1 -> IPU1_1 */ /* new */
        {IE, IE, IE}       /* IPU2_1 -> IPU2_1 */
    }
};
