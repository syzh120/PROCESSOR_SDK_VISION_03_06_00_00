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
 *  @file   ipclib_interruptTda2xxMailboxCfg.c
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
#if defined (__TI_ARM_V7M4__)
    SOC_EVE1_L3_MBX0_BASE + IPCLIB_BITBAND_OFFSET, /* EVE1 Internal Mailbox 0 */
    SOC_EVE1_L3_MBX1_BASE + IPCLIB_BITBAND_OFFSET, /* EVE1 Internal Mailbox 1 */
#else
    SOC_EVE1_MBX0_BASE,                            /* EVE1 Internal Mailbox 0 */
    SOC_EVE1_MBX1_BASE,                            /* EVE1 Internal Mailbox 1 */
#endif
    SOC_MAILBOX2_BASE,                             /* System Mailbox 2 */
    IPCLIB_INVALID_INFO,                           /* Free mailbox enry */
    IPCLIB_INVALID_INFO,                           /* Free mailbox enry */
    IPCLIB_INVALID_INFO,                           /* Free mailbox enry */
    IPCLIB_INVALID_INFO,                           /* Free mailbox enry */
    IPCLIB_INVALID_INFO,                           /* Free mailbox enry */
    IPCLIB_INVALID_INFO,                           /* Free mailbox enry */
    IPCLIB_INVALID_INFO,                           /* Free mailbox enry */
    IPCLIB_INVALID_INFO,                           /* Free mailbox enry */
    IPCLIB_INVALID_INFO,                           /* Free mailbox enry */
    IPCLIB_INVALID_INFO,                           /* Free mailbox enry */
    IPCLIB_INVALID_INFO,                           /* Free mailbox enry */
    IPCLIB_INVALID_INFO,                           /* Free mailbox enry */
    IPCLIB_INVALID_INFO                            /* Free mailbox enry */
};

/**
 * DES_ID : DOX_DES_TAG(DES_IPC_LITE_004)
 */
/**
 * REQ_ID : DOX_REQ_TAG(PDK-1409) DOX_REQ_TAG(PDK-1429) DOX_REQ_TAG(PDK-1432)
 */
/* Mailbox mapping for cores in TDA3xx */
IpcLib_InterruptMailboxCfg
IpcLib_gMailboxConfig[IPCLIB_MAX_PROC][IPCLIB_MAX_PROC] = {
    /* DSP1 as SRC */
    /* Mbx Usr Fifo */
    {
        {IE, IE, IE },      /* DSP1 -> DSP1   */
        {2U, 1U, 3U },      /* DSP1 -> DSP2   */
        {2U, 2U, 6U },      /* DSP1 -> IPU1_0 */
        {2U, 3U, 9U },      /* DSP1 -> IPU1_1 */
        {0U, 0U, 1U }       /* DSP1 -> EVE1   */
    },

    /* DSP2 as SRC */
    /* Mbx Usr Fifo */
    {
        {2U, 0U, 0U },      /* DSP2 -> DSP1   */
        {IE, IE, IE },      /* DSP2 -> DSP2   */
        {2U, 2U, 7U },      /* DSP2 -> IPU1_0 */
        {2U, 3U, 10U},      /* DSP2 -> IPU1_1 */
        {0U, 0U, 3U }       /* DSP2 -> EVE1   */
    },

    /* IPU1_0 as SRC */
    /* Mbx Usr Fifo */
    {
        {2U, 0U, 1U },      /* IPU1_0 -> DSP1   */
        {2U, 1U, 4U },      /* IPU1_0 -> DSP2   */
        {IE, IE, IE },      /* IPU1_0 -> IPU1_0 */
        {2U, 3U, 11U},      /* IPU1_0 -> IPU1_1 */
        {0U, 0U, 5U }       /* IPU1_0 -> EVE1   */
    },

    /* IPU1_1 as SRC */
    /* Mbx Usr Fifo */
    {
        {2U, 0U, 2U },      /* IPU1_1 -> DSP1   */
        {2U, 1U, 5U },      /* IPU1_1 -> DSP2   */
        {2U, 2U, 8U },      /* IPU1_1 -> IPU1_0 */
        {IE, IE, IE },      /* IPU1_1 -> IPU1_1 */
        {1U, 0U, 1U }       /* IPU1_1 -> EVE1   */
    },

    /* EVE1 as SRC */
    /* Mbx Usr Fifo */
    {
        {0U, 1U, 0U },      /* EVE1 -> DSP1   */
        {0U, 2U, 2U },      /* EVE1 -> DSP2   */
        {0U, 3U, 4U },      /* EVE1 -> IPU1_0 */
        {1U, 1U, 0U },      /* EVE1 -> IPU1_1 */
        {IE, IE, IE }       /* EVE1 -> EVE1   */
    }
};
