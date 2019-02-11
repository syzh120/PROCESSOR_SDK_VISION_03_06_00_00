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
 *  \defgroup IPC_LIB_INTERRUPT IPC LIB Interrupt Module
 *
 *  @{
 */
/**
 * @file ipclib_interrupt.h
 *
 * This file contains the IpcLib APIs for inter processor communication using
 * ipc interrupt module.
 *
 * IpcLib interrupt module implementation is as mentioned below
 *
 * file - ipclib/ipclib_interrupt.c
 * API Implementation common to all platforms
 *
 * file - ipclib/[$SOC]/ipclib_interrupt[$SOC].c
 * Platform specific implementation of interrupt setup / connection
 *
 * Ipclib module configuration is as mentioned below
 *
 * file - ipclib/[$SOC]/ipclib_interrupt[$SOC]ProcCfg.c
 * Platform specific implementation of available processors in the system.
 * IpcLib API and utility functions operate on IpcLib_gProcConfig to get
 * information about processor ids and names
 *
 * file - ipclib/[$SOC]/ipclib_interrupt[$SOC]MailboxCfg.c
 * Platform specific implementation of mailbox base addresses and mailbox table
 * that is used for N x N bidirectional communication. Each entry in this table
 * indicates mailbox entry that is used for unidirectional comminication
 * from source to destination. Here Source and destinations are indexes to
 * 2D IpcLib_gMailboxConfig
 *
 * file - ipclib/[$SOC]/ipclib_interrupt[$SOC]XbarCfg.c
 * Platform specific implementation of local interrupt numbers and
 * their connections. This can change based on platform
 *
 * Using IpcLib in application
 * Receiver's sequence
 *
 * 1. IpcLib_interruptSetDefaultInitPrm() (optional but advised)
 * 2. Change params as required
 * 3. IpcLib_interruptInit() - with valid params
 * 4. IpcLib_interruptRegisterEvent() - with valid callback function
 *
 * Sender's sequence
 *
 * 1. IpcLib_interruptSetDefaultInitPrm() (optional but advised)
 * 2. Change params as required
 * 3. IpcLib_interruptInit() - with valid params
 * 4. IpcLib_interruptSendEvent() - with valid payload and event id
 *
 * Essentially IpcLib allows receivers to register multiple callback functions.
 * Number of callbacks is capped by IPCLIB_MAX_EVENTS. The module maintains
 * this callback table and delivers message to right callback upon receiving
 * interrupt. It multiplexes over single interrupt line from sender M to
 * receiver N. This gives applications more flexibilty with minimal system
 * resource suage.
 *
 * Message delivery from sender to receiver
 *
 * IpcLib allows 32 bit value to be sent across. Depending upon value of message
 * it uses one or two mailbox entries. It uses last 5 bits of first message as
 * eventId, if payload value fits into rest 27 bits it sends the single message
 * or else it utilizes another message. ISR in the ipclib ensures messages are
 * delivered correctly. These are implementation details and application
 * writer need not worry about this.
 *
 * IMPORTANT NOTE - IpcLib does not take care of synchronization between
 *                  sender and receiver application.
 */

#ifndef IPCLIB_INTERRUPT_H_
#define IPCLIB_INTERRUPT_H_

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 *                             INCLUDE FILES
 ******************************************************************************/
#include <stdint.h>

/* This header file defines peocessor ids user can change these as per
 * requirement but all processor ids should be unique and macro definitions
 * shouldn't be changed.
 */
#if defined (SOC_TDA2XX) || defined (SOC_AM572x)
    #include <ti/drv/ipc_lite/ipclib_interruptTda2xx.h>
#elif defined (SOC_TDA2PX)
    #include <ti/drv/ipc_lite/ipclib_interruptTda2px.h>
#elif defined (SOC_TDA3XX)
    #include <ti/drv/ipc_lite/ipclib_interruptTda3xx.h>
#elif defined (SOC_TDA2EX) || defined (SOC_AM571x)
    #include <ti/drv/ipc_lite/ipclib_interruptTda2ex.h>
#else
    #error "platform specific header file not included in ipclib_interrupt.h"
#endif

/**
 * Below are the IPC_LIB module environment requirements which can't be mapped
 * to a particular source ID.
 */
/** DES_ID : DOX_DES_TAG(DES_IPC_LITE_001) */
/**
 * REQ_ID : DOX_REQ_TAG(PDK-1414) DOX_REQ_TAG(PDK-1430) DOX_REQ_TAG(PDK-1480)
 *          DOX_REQ_TAG(PDK-1422) DOX_REQ_TAG(PDK-1424) DOX_REQ_TAG(PDK-1420)
 *          DOX_REQ_TAG(PDK-1412) DOX_REQ_TAG(PDK-1479)
 */

/**
 * Below are the IPC_LIB module environment requirements which can't be mapped
 * to this driver.
 */
/** DES_ID : DOX_DES_TAG(DES_IPC_LITE_002) */
 /**
 * REQ_ID : DOX_REQ_TAG(PDK-1481) DOX_REQ_TAG(PDK-1586)
 */
/******************************************************************************
 *                        MACRO DEFINITIONS
 ******************************************************************************/

/**
 *  \brief Defines number of events supported per interrupt
 */
#define IPCLIB_MAX_EVENTS       (32U)

/**
 *  \brief Defines invalid entry
 */
#define IPCLIB_INVALID_INFO     (0xFFFFFFFFU)

/******************************************************************************
 *                        ENUMS
 ******************************************************************************/
/**
 *  \brief    Enumerates the error codes that ipclib returns to the caller
 */
typedef enum
{
    IPCLIB_SOK = 0,
    /**< Return success */

    IPCLIB_EFAIL = -((int32_t) 1),
    /**< send interrupt failed */

    IPCLIB_EBADARGS = -((int32_t) 2),
    /**< Wrong parameters passed */

    IPCLIB_EALREADYREGISTERED = -((int32_t) 3),
    /**< Call back is already registered for the event */

    IPCLIB_ESENDFAILED = -((int32_t) 4),
    /**< Send interrupt failed */

    IPCLIB_EINVALIDPROCID = -((int32_t) 5),
    /**< Send interrupt failed */

    IPCLIB_ENOTSUPPORTED = -((int32_t) 6),
    /**< Mailbox communication not supported */

    IPCLIB_ETIMEOUT = -((int32_t) 8),
    /**< Incomplete message being delivered */

    IPCLIB_FORCE32BITS = 0x7FFFFFFF
    /**< To make sure enum is 32 bits */
} IpcLib_InterruptReturnCodes;

/******************************************************************************
 *                        Structures
 ******************************************************************************/

/**
 *  \brief This structure holds parameters required to initialize ipclib
 *         interrupt module.
 */
typedef struct
{
    uint32_t numValidProcs;
    /**< Number of valid CPU ids that will participate in ipc */

    uint32_t validProcIds[IPCLIB_MAX_PROC];
    /**< Array of valid CPU ids, order of valid CPU ids is not important */

    uint32_t msgTimeOut;
    /**< Value is milisecs used by driver to avoid busy loop in ISR
     *   TO DO: Timer to be implemented, currently this is a counter.
     */
}IpcLib_InterruptInitPrms;

/**
 *  \brief This is interrupt callback fxn ptr to be stored in callback table.
 *
 *         Application should define and register a callback function of type
 *         IpcLib_InterruptCallback
 *
 * \param  remoteProcId Processor id which interrupted current processor
 * \param  eventId      Event id out of IPCLIB_MAX_EVENTS
 * \param  payload      Message that remote processor wanted to convey
 * \param  arg          Argument to the callback function
 * \param  status       ISR status IPCLIB_SOK indicates payload is complete
 *                      and callback ISR execeuted successfully. Any other
 *                      return code indicates ISR failed to retrieve message.
 *
 */
typedef int32_t (*IpcLib_InterruptCallback)(uint32_t remoteProcId,
                                            uint32_t eventId,
                                            uint32_t payload,
                                            void    *arg,
                                            int32_t  status);

/******************************************************************************
 *                        IpcLib API
 ******************************************************************************/
/**
 * \brief     This API is used to initialize ipc interrupt module
 *
 * \param     pPrm Initialization parameters for ipclib
 *                                    interrupt module
 *
 * \return    Status of initilization
 *
 */
int32_t IpcLib_interruptInit(const IpcLib_InterruptInitPrms *pPrm);

/**
 * \brief     This API is used to de-initialize ipc interrupt module
 *
 */
void IpcLib_interruptDeInit(void);

/**
 * \brief     This API is used to set default params
 *
 * \param     pPrm initialization parameters for ipclib
 *            interrupt module
 *
 * \return    None
 *
 */
void IpcLib_interruptSetDefaultInitPrm(IpcLib_InterruptInitPrms *pPrm);

/**
 * \brief     This API is used to registers interrupt callback function
 *
 * \param     remoteProcId Remote processor id for which event is being
 *            registered
 *                         (remote processor from which interrupt is expected)
 * \param     eventId      Event number less than maximum supported events
 * \param     fxn          Callback function to be registered
 * \param     arg          Argument to the callback function
 *
 * \return    Status codes
 *
 */
int32_t IpcLib_interruptRegisterEvent(uint32_t                 remoteProcId,
                                      uint32_t                 eventId,
                                      IpcLib_InterruptCallback fxn,
                                      void                    *arg);

/**
 * \brief     This API is used to unregisters interrupt callback function
 *
 * \param     remoteProcId Remote processor id for which event is being
 *                         unregistered
 * \param     eventId      Event number less than maximum supported events
 *
 * \return    Status codes
 *
 */
int32_t IpcLib_interruptUnregisterEvent(uint32_t remoteProcId,
                                        uint32_t eventId);

/**
 * \brief     This API is used to send 32 bit value to remote core and
 *            interrupt remote processor
 *
 * \param     remoteProcId Remote processor id which needs to be interrupted
 * \param     eventId      Event number for which interrupt is to be sent
 * \param     payload      Message value that needs to be sent accross
 * \param    waitClear    Flag which ensures interrupt is delivered / processed
 *                         by intented remote core. Setting this TRUE guarantees
 *                         tx message to be written in mailbox.
 *
 * \return    Status codes
 *
 */
int32_t IpcLib_interruptSendEvent(uint32_t remoteProcId,
                                  uint32_t eventId,
                                  uint32_t payload,
                                  uint32_t waitClear);

/**
 * \brief     This API is used to enable mailboxes
 *
 * \param     remoteProcId Remote processor id for which mailboxes need to be
 *                         enabled
 *
 * \return    Status codes
 *
 * \note      This API is valid only for Tdaxx
 */
int32_t IpcLib_interruptEnable(uint32_t remoteProcId);

/**
 * \brief     This API is used to Disable mailboxes
 *
 * \param     remoteProcId remote processor id for which mailboxes need to be
 *                         disabled
 *
 * \return    Status codes
 *
 * \note      This API is valid only for Tdaxx
 */
int32_t IpcLib_interruptDisable(uint32_t remoteProcId);

/******************************************************************************
 *                IpcLib utility functions for applications
 ******************************************************************************/
/**
 * \brief     This function returns procId of executing processor.
 *
 * \return    procId
 *
 * \note      This internal fucntion is valid only for Tdaxx
 */
uint32_t IpcLib_interruptGetSelfProcId(void);

/**
 * \brief     This function returns procId based on processor name.
 *
 * \param     name output - proc name
 *
 * \return    procId
 *
 * \note      This internal fucntion is valid only for Tdaxx
 */
uint32_t IpcLib_interruptGetProcId(const char *name);

/**
 * \brief     This function returns proc name based on procId.
 *
 * \param     name        - OUT param - name of processor
 * \param     length      - max character length for name
 * \param     id          - proc id for which name needs to be retrieved
 *
 * \return    Status codes
 *
 * \note      This internal fucntion is valid only for Tdaxx
 */
int32_t IpcLib_interruptGetProcName(char    *name,
                                    uint32_t length,
                                    uint32_t id);

#ifdef __cplusplus
}
#endif
#endif

/* @} */
/**
 * \mainpage  Inter Processor Communication Library
 *
 * \par IMPORTANT NOTE
 *   <b>
 *   The interfaces defined in this package are bound to change.
 *   Release notes/user guide list the additional limitation/restriction
 *   of this module/interfaces.
 *   </b> See also \ref TI_DISCLAIMER.
 *
 *
 * Inter Processor Communication Library(IPCLib) is built on top for
 * mailbox driver to abstract functionality of mailboxes and makes it usable
 * in software stack with or without operating system. IpcLib supports event
 * multiplexing, which means application writers can register multiple
 * callbacks for one remote core using single mailbox queue.
 * It supports 32bit value to be transferred across from sender core to
 * receiver core. IpcLib does not use any dynamic memory allocation or
 * shared memory to transferring messages.
 *
 * <b>
 * Also refer to top level user guide for detailed features,
 * limitations and usage description.
 * </b>
 *
 * - <b> IPC Library interrupt module
 * </b> (See \ref IPC_LIB_INTERRUPT) <br>
 *
 */

/**
 *  \page  TI_DISCLAIMER  TI Disclaimer
 *
 *  \htmlinclude ti_disclaim.htm
 */

