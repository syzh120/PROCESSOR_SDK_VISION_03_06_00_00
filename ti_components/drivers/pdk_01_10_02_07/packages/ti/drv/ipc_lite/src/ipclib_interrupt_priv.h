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
 *  @file   ipclib_interrupt_priv.h
 *
 *  @brief  This file contains internal data structures maintained by interrupt
 *          module.
 *
 */

#ifndef IPCLIB_INTERRUPT_PRIV_H_
#define IPCLIB_INTERRUPT_PRIV_H_

/******************************************************************************
 *                             INCLUDE FILES
 *******************************************************************************/

#include <stdint.h>
#include <ipclib_interrupt.h>
#include <ti/drv/vps/include/osal/bsp_osal.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 *                        MACRO DEFINITIONS
 ******************************************************************************/

/* M4s can not access 0x42XX_XXXX hence defining base addresses here
 * These addresses can be differennt based on AMMU mapping
 * If AMMU mapping of 0x6000_0000 to 0x4000_0000 is changed,
 * this offset should change accordingly.
 */
#define IPCLIB_BITBAND_OFFSET                       (0x20000000U)

/**
 *  \brief Maximum value that can fit in upper 27 bits of mailbox msg
 */
#define IPCLIB_SMALL_PAYLOAD_MAX                    (0x7FFFFFFU)

/**
 *  \brief First msg mask to be used with eventIds.
 */
#define IPCLIB_SMALL_PAYLOAD_MASK                   (0xFFFFFFE0U)

/**
 *  \brief First msg mask to be used with eventIds.
 */
#define IPCLIB_MAILBOX_READ_COUNT                   (64U)

/**
 *  \brief Defines maximum proc name length
 */
#define IPCLIB_MAX_PROCNAME_LEN                     (10U)

/**
 *  \brief Crossbar configurations per core only for mailbox interrupts
 *
 */
#define IPCLIB_MAX_XBARCONFIG                       (256U)

/**
 *  \brief Maximum mailbox base addresses needed.
 */
#define IPCLIB_MAX_MAILBOXES                        (16U)

/**
 *  \brief Mailbox fifo lenght.
 */
#define IPCLIB_MAILBOX_FIFOLENGTH                   (4U)

/**
 *  \brief Invalid entry for mailbox table.
 */
#define IE                                           (IPCLIB_INVALID_INFO)

/**
 *  \brief Last entry in cross bar table.
 */
#define LE                                           (IPCLIB_INVALID_INFO)

/******************************************************************************
 *                        Structures
 ******************************************************************************/

/**
 *  \brief This structure is for proc info
 */
typedef struct {
    uint32_t id;
    /**< unique processor id */

    char     name[IPCLIB_MAX_PROCNAME_LEN];
    /**< processor name */
}IpcLib_InterruptProcInfo;

/**
 *  \brief This structure for proc table.
 */

typedef struct {
    uint32_t                 selfProcId;
    /**< Processor id of configuring processor */

    IpcLib_InterruptProcInfo procInfo[IPCLIB_MAX_PROC];
    /**< unique processor id */
} IpcLib_InterruptProcCfg;

/**
 *  \brief This structure for mailbox table.
 */
typedef struct {
    uint32_t mbxId;
    /**< Mailbox id */

    uint32_t userId;
    /**< Mailbox user id */

    uint32_t fifo;
    /**< fifo queue number or sub mailbox id */
}IpcLib_InterruptMailboxCfg;

/**
 *  \brief This structure is for interruppt mapping.
 */
typedef struct {
    uint32_t xbarInst;
    /**< intC id */

    uint32_t xbarInput;
    /**< Cross bar input */
}IpcLib_InterruptXbar;

/**
 *  \brief This structure for callback table config.
 */
typedef struct
{
    IpcLib_InterruptCallback fxns[IPCLIB_MAX_PROC][IPCLIB_MAX_EVENTS];
    /**< Callback function addresses */

    void                    *args[IPCLIB_MAX_PROC][IPCLIB_MAX_EVENTS];
    /**< Callback function arguments */
} IpcLib_InterruptCallbackCfg;

/**
 *  \brief This structure is module level config.
 */
typedef struct
{
    IpcLib_InterruptCallbackCfg callbackTable;
    /**< Registered callback table */

    IpcLib_InterruptProcCfg     procTable;
    /**< Proc table for procs participating in ipc */

    IpcLib_InterruptMailboxCfg  mailboxTable[IPCLIB_MAX_PROC][IPCLIB_MAX_PROC];
    /**< Mailbox table for mailboxes participating in ipc */

    IpcLib_InterruptInitPrms    initPrms;
    /**< Module initialization parameters */

    uint32_t                    interruptTable[IPCLIB_MAX_PROC];
    /**< Interrupt table for procs participating in ipc
     *   indexed by remoteproc id */

    BspOsal_IntrHandle          intrHandle[IPCLIB_MAX_PROC];
    /**< Interrupt handlers */

    BspOsal_SemHandle           lockSem;
    /**< Module level lock */

    uint32_t                    registeredInterrupts[IPCLIB_MAX_PROC];
    /**< Records interrupt numbers being registered */

}IpcLib_InterruptModuleObject;

/******************************************************************************
 *                        Externs
 ******************************************************************************/

/**
 *  \brief Proc table instance to be configured.
 */
extern IpcLib_InterruptProcCfg      IpcLib_gProcConfig;

/**
 *  \brief Mailbox table instance to be configured.
 */
extern IpcLib_InterruptMailboxCfg   IpcLib_gMailboxConfig[IPCLIB_MAX_PROC][
    IPCLIB_MAX_PROC];

/**
 *  \brief Mailbox base addresses.
 */
extern uint32_t IpcLib_gMailboxBaseAddr[IPCLIB_MAX_MAILBOXES];

/**
 *  \brief Cross bar table instance to be configured.
 */
extern IpcLib_InterruptXbar         IpcLib_gXbarConfig[IPCLIB_MAX_XBARCONFIG];

/**
 *  \brief interrupt numbers per core.
 */
extern uint32_t IpcLib_gIntNumConfig[IPCLIB_MAX_PROC];

/******************************************************************************
 *                        Internal Functions
 ******************************************************************************/
void ipcLibISR(uint32_t arg);
void ipcLibDeliverMessage(uint32_t mbxBase, uint32_t mbxUser, uint32_t mbxFifo,
                          uint32_t remoteProcId);
void ipcLibInitInterrupts(void);
void ipcLibDeInitInterrupts(void);
void ipcLibUpdateMbxAddr(uint32_t selfProcId,
                         uint32_t remoteProcId,
                         uint32_t *mbxBase);


#ifdef __cplusplus
}
#endif

#endif
