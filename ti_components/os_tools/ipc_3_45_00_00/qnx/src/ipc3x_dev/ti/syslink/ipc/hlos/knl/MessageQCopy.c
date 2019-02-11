/*
 *  Copyright (c) 2011-2015, Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  *  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *  *  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 *  *  Neither the name of Texas Instruments Incorporated nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 *  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 *  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 *  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


/* Standard headers */
#include <ti/syslink/Std.h>

/* Osal & utils headers */
#include <ti/syslink/utils/Trace.h>
#include <ti/syslink/utils/String.h>
#include <ti/syslink/utils/Gate.h>
#include <ti/syslink/utils/IGateProvider.h>
#include <ti/syslink/utils/GateSpinlock.h>
#include <ti/syslink/utils/Memory.h>
#include <ti/syslink/utils/List.h>
#include <ti/syslink/inc/Bitops.h>
#include <ti/ipc/MultiProc.h>
#include <OsalSemaphore.h>
#include <atomic_qnx.h>

/* Module headers */
#include <ti/syslink/ProcMgr.h>
#include <ti/ipc/MessageQCopy.h>
#include <_MessageQCopyDefs.h>
#include <_MessageQCopy.h>
#include <VirtQueue.h>
//#include "virtio_ring.h"
#include <rpmsg.h>

#if defined (__cplusplus)
extern "C" {
#endif /* defined (__cplusplus) */


/* =============================================================================
 *  Macros, types, and constants
 *  For additional, see _MessageQCopyDefs.h
 * =============================================================================
 */
/*!
 *  @brief Macro to make a correct module magic number with refCount
 */
#define MessageQCopy_MAKE_MAGICSTAMP(x) ((MessageQCopy_MODULEID << 12u) | (x))

/*!
 *  @brief   Defines the Notify instance object.
 */
typedef struct MessageQCopyTransport_Object_tag {
    UInt16                  procId;
    /*!< Remote MultiProc id        */
    ProcMgr_Handle          procHandle;
    /*!< Remote Proc handle         */
    UInt32                  vqAddr;
    /*!< Virtial address of VQ, needed for un-mapping */
    UInt32                  vqPAddr;
    /*!< Physical address of VQ, needed for un-mapping */
    MessageQCopy_Handle     mq [MessageQCopy_MAXMQS];
    /*!< List of MessgeQCopy_Handles associated with this transport */
    VirtQueue_Handle        vq [MessageQCopy_NUMVIRTQS];
    /*!< VirtQueues associated with this transport */
} MessageQCopyTransport_Object;

/*!
 *  @brief  Defines the type for the handle to the Notify driver.
 */
typedef MessageQCopyTransport_Object * MessageQCopyTransport_Handle;

/*!
 *  @brief   Defines the Notify state object, which contains all the module
 *           specific information.
 */
typedef struct MessageQCopy_ModuleObject_tag {
    Atomic                          refCount;
    /*!< Reference count */
    MessageQCopy_Config             cfg;
    /*!< Notify configuration structure */
    MessageQCopy_Config             defCfg;
    /*!< Default module configuration */
    IGateProvider_Handle            gateHandle;
    /*!< Handle of gate to be used for local thread safety */
    Bool                            isSetup;
    /*!< Indicates whether the MessageQCopy module is setup. */
    MessageQCopyTransport_Handle    transport [MultiProc_MAXPROCESSORS];
    /*!< Array of configured transports. */
    MessageQCopy_Handle             mq [MessageQCopy_MAXMQS];
    /*!< Array of endpoints that exist on this processor */
}MessageQCopy_ModuleObject;

/*!
 *  @brief   Defines the MessageQCopy instance object.
 */
typedef struct MessageQCopy_Object_tag {
    UInt16              procId;
    /*!< Remote MultiProc id */
    UInt32              addr;
    /*!< Address (endpoint) of this MessageQCopy instance */
    Char                name [RPMSG_NAME_SIZE];
    /*!< Name of this MessageQCopy instance (may not be set) */
    Char                desc [RPMSG_NAME_SIZE];
    /*!< Desc of this MessageQCopy instance (may not be set) */
    Bool                announce;
    /*!< Flag to indicate if creation/deletion of this instance should be
         announced to the remote cores. */
    Void (*cb)(MessageQCopy_Handle, Void *, Int, Void *, UInt32, UInt16);
    /*!< Callback to invoke when a message is received for this addr.  */
    Void              * priv;
    /*!< Private data that is passed to the callback */
    Void (*notifyCb)(MessageQCopy_Handle, UInt16, UInt32, Char *, Bool);
    /*!< Optional callback that can be registered to request notification when
         MQCopy objects of the same name are created */
} MessageQCopy_Object;


/* =============================================================================
 *  Forward declarations of internal functions.
 * =============================================================================
 */
static
 Void
 _MessageQCopy_callback_NS (MessageQCopy_Handle handle, Void *data, Int len,
                            Void *priv, UInt32 src, UInt16 srcProc);

static
Void
_MessageQCopy_callback_bufReady (VirtQueue_Handle vq, void *arg);

static
MessageQCopy_Handle
_MessageQCopy_create (MessageQCopyTransport_Handle handle, UInt32 reserved,
                      String name, String desc,
                      Void (*cb)(MessageQCopy_Handle,
                                 Void *, Int, Void *, UInt32, UInt16),
                      Void *priv, UInt32 * endpoint);


/* =============================================================================
 *  Globals
 * =============================================================================
 */
/*!
 *  @var    MessageQCopy_state
 *
 *  @brief  MessageQCopy state object variable
 */
static
MessageQCopy_ModuleObject MessageQCopy_state =
{
    .gateHandle = NULL,
    .isSetup = FALSE,
};

/*!
 *  @var    MessageQCopy_module
 *
 *  @brief  Pointer to the MessageQCopy module state.
 */
static
MessageQCopy_ModuleObject * MessageQCopy_module = &MessageQCopy_state;


/* =============================================================================
 *  APIs called by applications.
 * =============================================================================
 */
/*!
 *  @brief      Setup the MessageQCopy module.
 *
 *              This function sets up the MessageQCopy module. This function
 *              must be called before any other instance-level APIs can be
 *              invoked.
 *              Module-level configuration needs to be provided to this
 *              function.
 *              This function call the VirtQueue startup function for each
 *              processor in the configuration and creates the transports
 *              (VirtQueues) per each processor mentioned in the configuration.
 *
 *  @param      cfg   MessageQCopy module configuration.
 *
 *  @sa         MessageQCopy_destroy
 *              GateSpinlock_create
 *              VirtQueue_startup
 *              VirtQueue_create
 *              VirtQueue_addAvailBuf
 *              VirtQueue_addUsedBufAddr
 *              VirtQueue_kick
 *              MessageQCopy_create
 */
Int
MessageQCopy_setup (const MessageQCopy_Config * cfg)
{
    Int                                 status      = MessageQCopy_S_SUCCESS;
    UInt32                              endpoint    = 0;
    Error_Block                         eb;

    GT_0trace (curTrace, GT_ENTER, "MessageQCopy_setup");

    GT_assert (curTrace, (cfg != NULL));

    Error_init(&eb);

    /* This sets the refCount variable if not initialized, upper 16 bits is
     * written with module Id to ensure correctness of refCount variable.
     */
    Atomic_cmpmask_and_set (&MessageQCopy_module->refCount,
                            MessageQCopy_MAKE_MAGICSTAMP(0),
                            MessageQCopy_MAKE_MAGICSTAMP(0));

    if (Atomic_inc_return (&MessageQCopy_module->refCount)
                           != MessageQCopy_MAKE_MAGICSTAMP(1u)) {
        status = MessageQCopy_S_ALREADYSETUP;
        GT_0trace (curTrace,
                   GT_2CLASS,
                   "MessageQCopy module already initialized!");
    }
    else if (cfg == NULL) {
        /*! @retval  MessageQCopy_E_INVALIDARG Invalid cfg argument
                                         provided. */
        status = MessageQCopy_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "MessageQCopy_setup",
                             status,
                             "Invalid cfg argument provided.");
    }
    else {
        /* Create a default gate handle for local module protection. */
        MessageQCopy_module->gateHandle = (IGateProvider_Handle)
                        GateSpinlock_create ((GateSpinlock_Params *) NULL, &eb);
#if !defined(IPC_BUILD_OPTIMIZE)
        if (MessageQCopy_module->gateHandle == NULL) {
            /*! @retval MessageQCopy_E_FAIL Failed to create GateSpinlock! */
            status = MessageQCopy_E_FAIL;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "MessageQCopy_setup",
                                 status,
                                 "Failed to create GateSpinlock!");
        }
        else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
            /* Initialize the driver mapping array. */
            Memory_set (MessageQCopy_module->transport,
                        0,
                        (sizeof (MessageQCopyTransport_Handle)
                         * MultiProc_MAXPROCESSORS));

            /* Initialize all the local endpoints. */
            Memory_set (&MessageQCopy_module->mq,
                        0,
                        (sizeof (MessageQCopy_Handle) * MessageQCopy_MAXMQS));
#if !defined(IPC_BUILD_OPTIMIZE)
        }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

        MessageQCopy_module->mq[MessageQCopy_NS_PORT] =
                                     MessageQCopy_create (MessageQCopy_NS_PORT,
                                                      NULL,
                                                      _MessageQCopy_callback_NS,
                                                      NULL,
                                                      &endpoint);
        if (MessageQCopy_module->mq[MessageQCopy_NS_PORT] == NULL) {
            /*! @retval MessageQCopy_E_MEMORY Failed to create virtqueue! */
            status = MessageQCopy_E_MEMORY;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "MessageQCopy_setup",
                                 status,
                                 "Failed to create name service MessageQ!");
        }
        else {
            Memory_copy (&MessageQCopy_module->cfg, (Ptr)cfg,
                         sizeof (MessageQCopy_Config));
        }

        if (status < 0) {
            MessageQCopy_destroy();
        }
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "MessageQCopy_setup", status);

    /*! @retval MessageQCopy_S_SUCCESS Operation successful */
    return (status);
}


/*!
 *  @brief      Destroy the MessageQCopy module.
 *
 *              Once this function is called, other MessageQCopy module APIs
 *              cannot be called anymore.
 *
 *  @sa         MessageQCopy_setup
 *              GateSpinlock_delete
 *              MessageQCopy_delete
 */
Int
MessageQCopy_destroy (Void)
{
    Int                                 status      = MessageQCopy_S_SUCCESS;
    Int16                               i           = 0;

    GT_0trace (curTrace, GT_ENTER, "MessageQCopy_destroy");

#if !defined(IPC_BUILD_OPTIMIZE)
    if (Atomic_cmpmask_and_lt (&(MessageQCopy_module->refCount),
                               MessageQCopy_MAKE_MAGICSTAMP(0),
                               MessageQCopy_MAKE_MAGICSTAMP(1))
        == TRUE) {
        /*! @retval Notify_E_INVALIDSTATE Module was not initialized */
        status = MessageQCopy_E_INVALIDSTATE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "MessageQCopy_destroy",
                             status,
                             "Module was not initialized!");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        if (Atomic_dec_return (&MessageQCopy_module->refCount)
            == MessageQCopy_MAKE_MAGICSTAMP(0)) {
            /* Temporarily increment refCount here. */
            Atomic_set (&MessageQCopy_module->refCount,
                        MessageQCopy_MAKE_MAGICSTAMP(1));

            if (MessageQCopy_module->mq[MessageQCopy_NS_PORT] != NULL) {
                MessageQCopy_delete (
                               &MessageQCopy_module->mq[MessageQCopy_NS_PORT]);
                MessageQCopy_module->mq[MessageQCopy_NS_PORT] = NULL;
            }

            /* Check if any MessageQ instances have not been deleted so far. */
            for (i = 0 ; i < MessageQCopy_MAXMQS; i++) {
                /*
                 * This is possible if recovery is performed and the app does
                 * not yet know about it, hence has not yet had a chance to
                 * clean up.
                 */
                if (MessageQCopy_module->mq [i] != NULL) {
                    MessageQCopy_delete(&MessageQCopy_module->mq [i]);
                    MessageQCopy_module->mq [i] = NULL;
                }
            }

            /* Decrease the refCount */
            Atomic_set (&MessageQCopy_module->refCount,
                        MessageQCopy_MAKE_MAGICSTAMP(0));

            if (MessageQCopy_module->gateHandle != NULL) {
                GateSpinlock_delete ((GateSpinlock_Handle *)
                                     &(MessageQCopy_module->gateHandle));
            }
        }
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "MessageQCopy_destroy", status);

    /*! @retval MessageQCopy_S_SUCCESS Operation successful */
    return (status);
}

/* Calls the SetupProxy to setup the MessageQ transports. */
Int
MessageQCopy_attach (UInt16 remoteProcId, Ptr sharedAddr, UInt16 startId)
{
    Int                                 status      = MessageQCopy_S_SUCCESS;
    MessageQCopyTransport_Object *      obj         = NULL;
    UInt                                i           = 0;
    Void *                              buf         = NULL;
    Int32                               vqVAddr     = 0;
    Int32                               vqPAddr     = 0;
    UInt32                              recvBufsAddr;
    UInt32                              sendBufsAddr;
    ProcMgr_AddrInfo                    addrInfo;

    GT_2trace (curTrace, GT_ENTER, "MessageQCopy_attach", remoteProcId,
               sharedAddr);

    if (EXPECT_TRUE (MultiProc_getNumProcessors () > 1)) {
#if !defined(IPC_BUILD_OPTIMIZE)
        if (remoteProcId >= MultiProc_getNumProcessors()) {
            /*! @retval MessageQCopy_E_INVALIDPROCID ProcId is invalid! */
            status = MessageQCopy_E_INVALIDPROCID;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "MessageQCopy_attach",
                                 status,
                                 "ProcId is invalid!");
        }
        else if (MessageQCopy_module->transport[remoteProcId]) {
            /*! @retval MessageQCopy_E_ALREADYEXISTS Transport already
                                        exists! */
            status = MessageQCopy_E_ALREADYEXISTS;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "MessageQCopy_attach",
                                 status,
                                 "Transport is already attached!");
        }
        else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

            /* Allocate memory for the MessageQCopyTransport object. */
            obj = Memory_calloc (NULL,
                                 sizeof (MessageQCopyTransport_Object), 0u,
                                 NULL);
#if !defined(IPC_BUILD_OPTIMIZE)
            if (obj == NULL) {
                /*! @retval MessageQCopy_E_MEMORY Failed to allocate memory
                                        for MessageQCopyTransport_Object! */
                status = MessageQCopy_E_MEMORY;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "MessageQCopy_attach",
                                     status,
                                     "Failed to allocate memory for "
                                     "MessageQCopyTransport_Object!");
            }
            else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
                obj->procId = remoteProcId;

                status = ProcMgr_open(&obj->procHandle, obj->procId);
#if !defined(IPC_BUILD_OPTIMIZE)
                if (status < 0) {
                        Memory_free(NULL, obj,
                                    sizeof (MessageQCopyTransport_Object));
                        /*! @retval MessageQCopy_E_MEMORY Unable to open Proc
                                                          handle for specified
                                                          remoteProcId! */
                        status = MessageQCopy_E_RESOURCE;
                        GT_setFailureReason (curTrace,
                                             GT_4CLASS,
                                             "MessageQCopy_attach",
                                             status,
                                             "Unable to open Proc handle for "
                                             "specified remoteProcId!");
                }
                else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
                    status = ProcMgr_translateAddr(obj->procHandle,
                                                   (Ptr *)&vqPAddr,
                                                   ProcMgr_AddrType_MasterPhys,
                                                   sharedAddr,
                                                   ProcMgr_AddrType_SlaveVirt);
                    if (status < 0) {
                        ProcMgr_close(&obj->procHandle);
                        Memory_free(NULL, obj,
                                    sizeof (MessageQCopyTransport_Object));
                        /*! @retval MessageQCopy_E_MEMORY Unable translate
                                                          addr! */
                        status = MessageQCopy_E_MEMORY;
                        GT_setFailureReason (curTrace,
                                             GT_4CLASS,
                                             "MessageQCopy_attach",
                                             status,
                                             "Unable to translate addr!");
                    }
                    else {
                        obj->vqPAddr = vqPAddr;
                        addrInfo.addr[ProcMgr_AddrType_MasterPhys] = vqPAddr;
                        addrInfo.size = (MessageQCopy_NUMVIRTQS *\
                                         ROUND_UP(MessageQCopy_RINGSIZE,
                                                  0x4000)) +
                                         (MessageQCopy_NUMBUFS * \
                                              MessageQCopy_BUFSIZE * 2);
                        addrInfo.isCached = FALSE;
                        addrInfo.isMapped = TRUE;
                        status = ProcMgr_map(obj->procHandle,
                                             ProcMgr_MASTERKNLVIRT, &addrInfo,
                                             ProcMgr_AddrType_MasterPhys);
                        if (status < 0) {
                            ProcMgr_close(&obj->procHandle);
                            Memory_free(NULL, obj,
                                        sizeof (MessageQCopyTransport_Object));
                            /*! @retval MessageQCopy_E_MEMORY Unable translate
                                                              addr! */
                            status = MessageQCopy_E_MEMORY;
                            GT_setFailureReason (curTrace,
                                                 GT_4CLASS,
                                                 "MessageQCopy_attach",
                                                 status,
                                                 "Unable to translate addr!");
                        }
                        obj->vqAddr = vqVAddr =
                                  addrInfo.addr[ProcMgr_AddrType_MasterKnlVirt];
                    }

                    if (status >= 0) {
                        /* Startup the VirtQueue module for this procId. */
                        VirtQueue_startup(obj->procId,
                                    MessageQCopy_module->cfg.intId[obj->procId],
                                    vqPAddr);

                        /*
                         * The buffer area is divided into two parts, one
                         * for receiving messages from the remote processor
                         * and one for sending messages.  Here, we calculate
                         * the address of the start of each buffer section.
                         */
                        recvBufsAddr = vqVAddr + (MessageQCopy_NUMVIRTQS *\
                                       ROUND_UP(MessageQCopy_RINGSIZE, 0x4000));
                        sendBufsAddr = recvBufsAddr +
                                             (MessageQCopy_NUMBUFS * \
                                              MessageQCopy_BUFSIZE);

                        /* Create the virtqueues */
                        for (i = 0; i < MessageQCopy_NUMVIRTQS; i++) {
                            obj->vq[i] = VirtQueue_create (
                                                _MessageQCopy_callback_bufReady,
                                                obj->procId,
                                                startId + i,
                                                vqVAddr,
                                                vqPAddr,
                                                MessageQCopy_NUMBUFS,
                                                MessageQCopy_VRINGALIGN,
                                                (void *)obj);

#if !defined(IPC_BUILD_OPTIMIZE)
                            if (obj->vq[i] == NULL) {
                                for (; i >= 0; --i) {
                                    VirtQueue_delete (&obj->vq[i]);
                                }
                                VirtQueue_destroy(obj->procId);
                                addrInfo.addr[ProcMgr_AddrType_MasterKnlVirt] = obj->vqAddr;
                                ProcMgr_unmap(obj->procHandle,
                                              ProcMgr_MASTERKNLVIRT, &addrInfo,
                                              ProcMgr_AddrType_MasterPhys);
                                ProcMgr_close(&obj->procHandle);
                                Memory_free(NULL, obj,
                                            sizeof (MessageQCopyTransport_Object));
                                /*! @retval MessageQCopy_E_MEMORY Failed to
                                                                  create
                                                                  virtqueue! */
                                status = MessageQCopy_E_MEMORY;
                                GT_setFailureReason (curTrace,
                                                     GT_4CLASS,
                                                     "MessageQCopy_attach",
                                                     status,
                                                     "Failed to create "
                                                     "virtqueue!");
                                break;
                            }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
                            vqVAddr += ROUND_UP(MessageQCopy_RINGSIZE, 0x4000);
                            vqPAddr += ROUND_UP(MessageQCopy_RINGSIZE, 0x4000);
                        }
                    }

                    if (status >= 0) {
                        /* Register for interrupts */
                        for (i = 0; i < MessageQCopy_NUMBUFS; i++) {
                            buf = (Void *)((UInt32)recvBufsAddr +\
                                           (i * MessageQCopy_BUFSIZE));
                            VirtQueue_addAvailBuf (obj->vq[0], buf, 0, i);
                        }
                        /* Add all the bufs for A9->remote proc communication */
                        for (i = 0; i < MessageQCopy_NUMBUFS; i++) {
                            buf = (Void *)((UInt32)sendBufsAddr +\
                                           (i * MessageQCopy_BUFSIZE));
                            VirtQueue_addUsedBufAddr (obj->vq[1], buf,
                                                      MessageQCopy_BUFSIZE);
                        }
                        /* Notify the remote proc about the buffers */
                        VirtQueue_kick(obj->vq[0]);

                        /* Save the transport object */
                        MessageQCopy_module->transport [obj->procId] = obj;
                    }
                }
#if !defined(IPC_BUILD_OPTIMIZE)
            }
        }
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "MessageQCopy_attach",
                                 status,
                                 "Failed in transport setup!");
        }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
    }
    else {
        status = MessageQCopy_E_FAIL;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "MessageQCopy_attach",
                             status,
                             "Function called incorrectly!");
    }

    GT_1trace (curTrace, GT_LEAVE, "MessageQCopy_attach", status);

    /*! @retval MessageQCopy_S_SUCCESS Operation successfully completed! */
    return status;
}

/* Calls the SetupProxy to detach the MessageQ transports. */
Int
MessageQCopy_detach (UInt16 remoteProcId)
{
    Int status = MessageQCopy_S_SUCCESS;
    MessageQCopyTransport_Object *      obj         = NULL;
    Int16                               i           = 0;
    ProcMgr_AddrInfo                    addrInfo;

    GT_1trace (curTrace, GT_ENTER, "MessageQCopy_detach", remoteProcId);

    if (EXPECT_TRUE (MultiProc_getNumProcessors () > 1)) {
#if !defined(IPC_BUILD_OPTIMIZE)
        if (remoteProcId >= MultiProc_getNumProcessors()) {
            /*! @retval MessageQCopy_E_INVALIDPROCID ProcId is invalid! */
            status = MessageQCopy_E_INVALIDPROCID;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "MessageQCopy_detach",
                                 status,
                                 "ProcId is invalid!");
        }
        else if (MessageQCopy_module->transport[remoteProcId] == NULL) {
            /*! @retval MessageQCopy_E_NOTFOUND Transport is not
                                        setup! */
            status = MessageQCopy_E_NOTFOUND;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "MessageQCopy_detach",
                                 status,
                                 "Transport is not setup!");
        }
        else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
            obj = MessageQCopy_module->transport[remoteProcId];

            /* Check if any MessageQ instances have not been deleted so far.
             * Delete them, but don't assert since these are remote-proc
             * allocated MessageQ's.
             */
            for (i = 0 ; i < MessageQCopy_MAXMQS; i++) {
                if (obj->mq [i] != NULL) {
                    MessageQCopy_delete(&obj->mq [i]);
                    obj->mq [i] = NULL;
                }
            }

            MessageQCopy_module->transport[remoteProcId] = NULL;

            /* Delete the virtqueues */
            for (i = 0; i < MessageQCopy_NUMVIRTQS; i++) {
                VirtQueue_delete (&obj->vq[i]);
                obj->vq[i] = NULL;
            }

            VirtQueue_destroy(remoteProcId);
            addrInfo.addr[ProcMgr_AddrType_MasterPhys] = obj->vqPAddr;
            addrInfo.addr[ProcMgr_AddrType_MasterKnlVirt] = obj->vqAddr;
            addrInfo.size = (MessageQCopy_NUMVIRTQS *\
                             ROUND_UP(MessageQCopy_RINGSIZE, 0x4000)) +
                             (MessageQCopy_NUMBUFS * MessageQCopy_BUFSIZE * 2);
            addrInfo.isCached = FALSE;
            addrInfo.isMapped = TRUE;
            ProcMgr_unmap(obj->procHandle,
                          ProcMgr_MASTERKNLVIRT, &addrInfo,
                          ProcMgr_AddrType_MasterPhys);
            ProcMgr_close(&obj->procHandle);
            /* Allocate memory for the MessageQCopyTransport object. */
            Memory_free (NULL, obj, sizeof (MessageQCopyTransport_Object));
#if !defined(IPC_BUILD_OPTIMIZE)
        }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
    }
    else {
        status = MessageQCopy_E_FAIL;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "MessageQCopy_detach",
                             status,
                             "Function called incorrectly!");
    }

    GT_1trace (curTrace, GT_LEAVE, "MessageQCopy_detach", status);

    /*! @retval MessageQCopy_S_SUCCESS Operation successfully completed! */
    return status;
}


/* Internal create function. */
static
MessageQCopy_Handle
_MessageQCopy_create (MessageQCopyTransport_Handle handle, UInt32 reserved,
           String name, String desc,
           void (*cb)(MessageQCopy_Handle, void *, int, void *, UInt32, UInt16),
           Void *priv, UInt32 * endpoint)
{
    Int32                       status          = MessageQCopy_S_SUCCESS;
    MessageQCopy_Object *       obj             = NULL;
    IArg                        key             = NULL;
    Bool                        found           = FALSE;
    Int                         i               = 0;
    UInt16                      queueIndex      = 0;
    MessageQCopy_Handle *       mq              = NULL;
    Bool                        announce        = FALSE;

    GT_5trace (curTrace, GT_ENTER, "_MessageQCopy_create",
               handle, reserved, name, desc, endpoint);

    GT_assert (curTrace, (endpoint != NULL));
    /* name is optional and may be NULL. */
    /* desc is optional and may be NULL. */
    /* handle is optional and may be NULL. */

#if !defined(IPC_BUILD_OPTIMIZE)
    if (Atomic_cmpmask_and_lt (&(MessageQCopy_module->refCount),
                               MessageQCopy_MAKE_MAGICSTAMP(0),
                               MessageQCopy_MAKE_MAGICSTAMP(1))
        == TRUE) {
       /*! @retval  MessageQCopy_E_INVALIDSTATE Notify module not setup */
        status = MessageQCopy_E_INVALIDSTATE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "_MessageQCopy_create",
                             status,
                             "MessageQCopy module not setup");
    }
    else if (endpoint == NULL) {
        /*! @retval  MessageQCopy_E_INVALIDARG Invalid endpoint argument
                                         provided. */
        status = MessageQCopy_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "_MessageQCopy_create",
                             status,
                             "Invalid endpoint argument provided");
    }
    else if (name && String_nlen(name, RPMSG_NAME_SIZE - 1) == -1) {
        /*! @retval  MessageQCopy_E_INVALIDARG Invalid name argument
                                         provided. */
        status = MessageQCopy_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "_MessageQCopy_create",
                             status,
                             "Invalid name argument provided");
    }
    else if (desc && String_nlen(desc, RPMSG_NAME_SIZE - 1) == -1) {
        /*! @retval  MessageQCopy_E_INVALIDARG Invalid name argument
                                         provided. */
        status = MessageQCopy_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "_MessageQCopy_create",
                             status,
                             "Invalid desc argument provided");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        if (handle == NULL) {
            mq = MessageQCopy_module->mq;
            if (reserved != MessageQCopy_ADDRANY && name != NULL)
                announce = TRUE;
        }
        else {
            mq = handle->mq;
        }

        /* Enter critical section protection. */
        key = IGateProvider_enter (MessageQCopy_module->gateHandle);

        if (reserved == MessageQCopy_ADDRANY)  {
            /* Search the array for a free slot above reserved: */
            for (i = MessageQCopy_MAXRESERVEDEPT + 1;
                 (i < MessageQCopy_MAXMQS) && (found == FALSE) ; i++) {
                if (mq[i] == NULL) {
                    queueIndex = i;
                    found = TRUE;
                    break;
                }
            }
        }
        else if ((queueIndex = reserved) < MessageQCopy_MAXMQS) {
            if (mq[queueIndex] == NULL)
                found = TRUE;
        }

        if (found) {
            obj = Memory_calloc(NULL, sizeof(MessageQCopy_Object), 0, NULL);
            if (obj != NULL) {
                /* Store our endpoint, and object: */
                obj->addr = queueIndex;
                obj->cb = cb;
                obj->priv = priv;
                if (handle)
                    obj->procId = handle->procId;
                else
                    obj->procId = MultiProc_self();
                if (name) {
                    String_cpy (obj->name, name);
                }
                else
                    obj->name[0] = '\0';
                if (desc) {
                    String_cpy (obj->desc, desc);
                }
                else
                    obj->desc[0] = '\0';

                mq[queueIndex] = obj;

                *endpoint = queueIndex;

                obj->announce = announce;
                if (obj->announce) {
                    struct rpmsg_ns_msg msg;

                    msg.addr = obj->addr;
                    msg.flags = RPMSG_NS_CREATE;
                    String_ncpy (msg.name, obj->name, RPMSG_NAME_SIZE);
                    if (obj->desc)
                        String_ncpy (msg.desc, obj->desc, RPMSG_NAME_SIZE);
                    else
                        msg.desc[0] = '\0';

                    /* Send to all procs */
                    for (i = 0; i < MultiProc_MAXPROCESSORS; i++) {
                        if (MessageQCopy_module->transport[i]) {
                            UInt16 remoteProcId =
                                      MessageQCopy_module->transport[i]->procId;
                            UInt16 localProcId = MultiProc_self();

                            IGateProvider_leave (
                                                MessageQCopy_module->gateHandle,
                                                key);

                            status = MessageQCopy_send (
                                  remoteProcId,
                                  localProcId,
                                  MessageQCopy_NS_PORT, obj->addr, &msg,
                                  sizeof (struct rpmsg_ns_msg), TRUE);

                            key = IGateProvider_enter (
                                               MessageQCopy_module->gateHandle);
                        }
                    }
                }

                /* notify anyone registered of this channel */
                if (name) {
                    for (i = 0; i < MessageQCopy_MAXMQS; i++) {
                        if (MessageQCopy_module->mq[i] &&
                            MessageQCopy_module->mq[i]->name) {
                            if (!String_ncmp(name,
                                             MessageQCopy_module->mq[i]->name,
                                             RPMSG_NAME_SIZE)) {
                                if (MessageQCopy_module->mq[i]->notifyCb)
                                    MessageQCopy_module->mq[i]->notifyCb(
                                                     MessageQCopy_module->mq[i],
                                                     obj->procId,
                                                     obj->addr,
                                                     obj->desc,
                                                     TRUE);
                            }
                        }
                    }
                }
            }
        }

        /* Leave critical section protection. */
        IGateProvider_leave (MessageQCopy_module->gateHandle, key);
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "_MessageQCopy_create", status);

    /*! @retval MessageQCopy_S_SUCCESS Operation successful */
    return (MessageQCopy_Handle)(obj);
}


/* Create an endpoint and handle.  Return a handle. */
MessageQCopy_Handle
MessageQCopy_create (UInt32 reserved, String name,
           void (*cb)(MessageQCopy_Handle, void *, int, void *, UInt32, UInt16),
           Void *priv, UInt32 * endpoint)
{
    Int32                       status      = MessageQCopy_S_SUCCESS;
    MessageQCopy_Object *       obj         = NULL;

    GT_3trace (curTrace, GT_ENTER, "MessageQCopy_create",
               reserved, name, endpoint);

    GT_assert (curTrace, (endpoint != NULL));
    /* name is optional and may be NULL. */

#if !defined(IPC_BUILD_OPTIMIZE)
    if (Atomic_cmpmask_and_lt (&(MessageQCopy_module->refCount),
                               MessageQCopy_MAKE_MAGICSTAMP(0),
                               MessageQCopy_MAKE_MAGICSTAMP(1))
        == TRUE) {
       /*! @retval  MessageQCopy_E_INVALIDSTATE Notify module not setup */
        status = MessageQCopy_E_INVALIDSTATE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "MessageQCopy_create",
                             status,
                             "MessageQCopy module not setup");
    }
    else if (cb == NULL) {
        /*! @retval  MessageQCopy_E_INVALIDARG Invalid cb argument
                                         provided. */
        status = MessageQCopy_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "MessageQCopy_create",
                             status,
                             "Invalid cb argument provided");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

        obj = _MessageQCopy_create (NULL, reserved, name, NULL, cb, priv,
                                    endpoint);

#if !defined(IPC_BUILD_OPTIMIZE)
        if (obj == NULL) {
            /*! @retval  MessageQCopy_E_FAIL Failed to create handle. */
            status = MessageQCopy_E_FAIL;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "MessageQCopy_create",
                                 status,
                                 "Failed to create handle");
        }
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "MessageQCopy_create", status);

    /*! @retval MessageQCopy_S_SUCCESS Operation successful */
    return (MessageQCopy_Handle)obj;
}


/* Internal delete function. */
Int
MessageQCopy_delete (      MessageQCopy_Handle * handlePtr)
{
    Int32                           status          = MessageQCopy_S_SUCCESS;
    MessageQCopy_Object *           obj             = NULL;
    IArg                            key             = NULL;
    UInt32                          i               = 0;
    UInt32                          j               = 0;
    MessageQCopy_Handle *           mq              = NULL;
    Bool                            found           = FALSE;

    GT_1trace (curTrace, GT_ENTER, "MessageQCopy_delete", handlePtr);

    GT_assert (curTrace, (handlePtr != NULL));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (Atomic_cmpmask_and_lt (&(MessageQCopy_module->refCount),
                               MessageQCopy_MAKE_MAGICSTAMP(0),
                               MessageQCopy_MAKE_MAGICSTAMP(1))
        == TRUE) {
       /*! @retval  MessageQCopy_E_INVALIDSTATE Notify module not setup */
        status = MessageQCopy_E_INVALIDSTATE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "MessageQCopy_delete",
                             status,
                             "MessageQCopy module not setup");
    }
    else if (handlePtr == NULL) {
        /*! @retval  MessageQCopy_E_INVALIDARG Invalid handlePtr argument
                                         provided. */
        status = MessageQCopy_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "MessageQCopy_delete",
                             status,
                             "Invalid handlePtr argument provided");
    }
    else if (*handlePtr == NULL) {
        /*! @retval  MessageQCopy_E_INVALIDARG Invalid *handlePtr argument
                                         provided. */
        status = MessageQCopy_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "MessageQCopy_delete",
                             status,
                             "Invalid *handlePtr argument provided");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        obj = (MessageQCopy_Object *)(*handlePtr);
        /* Search through all transports for this handle to validate that it is real */
        mq = MessageQCopy_module->mq;
        for (i = 0; i < MessageQCopy_MAXMQS; i++) {
            if (mq[i] == obj) {
                found = TRUE;
                break;
            }
        }
        if (!found) {
            for (j = 0; j < MultiProc_MAXPROCESSORS; j++) {
                if (MessageQCopy_module->transport[j]) {
                    mq = MessageQCopy_module->transport[j]->mq;
                    for (i = 0; i < MessageQCopy_MAXMQS; i++) {
                        if (mq[i] == obj) {
                            found = TRUE;
                            break;
                        }
                    }
                    if (found == TRUE)
                        break;
                }
            }
        }
        if (found) {
            /* Enter critical section protection. */
            key = IGateProvider_enter (MessageQCopy_module->gateHandle);

            if (obj->announce) {
                struct rpmsg_ns_msg msg;

                msg.addr = obj->addr;
                msg.flags = RPMSG_NS_DESTROY;
                String_ncpy(msg.name, obj->name, RPMSG_NAME_SIZE);
                if (obj->desc)
                    String_ncpy(msg.desc, obj->desc, RPMSG_NAME_SIZE);
                else
                    msg.desc[0] = '\0';

                /* Send to all procs */
                for (i = 0; i < MultiProc_MAXPROCESSORS; i++) {
                    if (MessageQCopy_module->transport[i]) {
                        UInt16 remoteProcId =
                                      MessageQCopy_module->transport[i]->procId;
                        UInt16 localProcId = MultiProc_self();

                        IGateProvider_leave (MessageQCopy_module->gateHandle,
                                             key);
                        status = MessageQCopy_send (remoteProcId, localProcId,
                                                   MessageQCopy_NS_PORT,
                                                   obj->addr, &msg,
                                                   sizeof (struct rpmsg_ns_msg),
                                                   TRUE);
                        key = IGateProvider_enter (
                                               MessageQCopy_module->gateHandle);
                    }
                }
            }
            /* notify anyone registered of this channel */
            if (obj->name) {
                for (i = 0; i < MessageQCopy_MAXMQS; i++) {
                    if (MessageQCopy_module->mq[i] &&
                        MessageQCopy_module->mq[i]->name &&
                        obj->procId != MessageQCopy_module->mq[i]->procId) {
                        if (!String_ncmp(obj->name,
                                         MessageQCopy_module->mq[i]->name,
                                         RPMSG_NAME_SIZE)) {
                            if (MessageQCopy_module->mq[i]->notifyCb)
                                MessageQCopy_module->mq[i]->notifyCb(
                                                     MessageQCopy_module->mq[i],
                                                     obj->procId,
                                                     obj->addr,
                                                     obj->desc,
                                                     FALSE);
                        }
                    }
                }
            }

            mq[obj->addr] = NULL;

            /* Leave critical section protection. */
            IGateProvider_leave (MessageQCopy_module->gateHandle, key);

            Memory_free (NULL, obj, sizeof (MessageQCopy_Object));

            *handlePtr = NULL;
        }
        else {
            /*! @retval  MessageQCopy_E_INVALIDARG Invalid *handlePtr argument
                                             provided. */
            status = MessageQCopy_E_INVALIDARG;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "MessageQCopy_delete",
                                 status,
                                 "Invalid *handlePtr argument provided");
        }
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "MessageQCopy_delete", status);

    /*! @retval MessageQCopy_S_SUCCESS Operation successful */
    return (status);
}


/* Register to be notified of a MQ created on the remote core. */
Int
MessageQCopy_registerNotify (MessageQCopy_Handle handle,
                  Void (*cb)(MessageQCopy_Handle, UInt16, UInt32, Char *, Bool))
{
    Int32                               status      = MessageQCopy_S_SUCCESS;
    MessageQCopyTransport_Object *      obj         = NULL;
    IArg                                key         = NULL;
    Int                                 i           = 0;
    Int                                 j           = 0;
    Bool                                found       = FALSE;

    GT_2trace (curTrace, GT_ENTER, "MessageQCopy_registerNotify", handle, cb);

    GT_assert (curTrace, (handle != NULL));
    GT_assert (curTrace, (cb != NULL));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (Atomic_cmpmask_and_lt (&(MessageQCopy_module->refCount),
                               MessageQCopy_MAKE_MAGICSTAMP(0),
                               MessageQCopy_MAKE_MAGICSTAMP(1))
        == TRUE) {
       /*! @retval  MessageQCopy_E_INVALIDSTATE MessageQCopy module not setup */
        status = MessageQCopy_E_INVALIDSTATE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "MessageQCopy_registerNotify",
                             status,
                             "MessageQCopy module not setup");
    }
    else if (handle == NULL) {
        /*! @retval  MessageQCopy_E_INVALIDARG Invalid handle argument
                                         provided. */
        status = MessageQCopy_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "MessageQCopy_registerNotify",
                             status,
                             "Invalid handle argument provided");
    }
    else if (cb == NULL) {
        /*! @retval  MessageQCopy_E_INVALIDARG Invalid callback argument
                                         provided. */
        status = MessageQCopy_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "MessageQCopy_registerNotify",
                             status,
                             "Invalid callback argument provided.");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        /* Enter critical section protection. */
        key = IGateProvider_enter (MessageQCopy_module->gateHandle);

        /*
         * Search through the local transport for this handle to validate that
         * it is real. The handle must be a local handle.
         */
        for (i = 0; i < MessageQCopy_MAXMQS; i++) {
            if (MessageQCopy_module->mq[i] == handle) {
                found = TRUE;
                break;
            }
        }

        if (found) {
            if (String_nlen(handle->name, RPMSG_NAME_SIZE - 1) == 0) {
                /*! @retval  MessageQCopy_E_INVALIDARG Invalid handle argument
                                                 provided. */
                status = MessageQCopy_E_INVALIDARG;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "MessageQCopy_registerNotify",
                                     status,
                                     "Invalid handle argument provided");
            }
            else {
                /* save the callback for future use */
                handle->notifyCb = cb;

                /* using the id_table, try to find a registered channel */
                for (j = 0; j < MultiProc_MAXPROCESSORS; j++) {
                    obj = MessageQCopy_module->transport[j];

                    if (obj) {
                        for (i = 0; i < MessageQCopy_MAXMQS; i++) {
                            if (obj->mq[i] && obj->mq[i]->name) {
                                if (!String_ncmp (handle->name,
                                                  obj->mq[i]->name,
                                                  RPMSG_NAME_SIZE) ) {
                                    /* call the callback */
                                    cb(handle, j, obj->mq[i]->addr,
                                       obj->mq[i]->desc, TRUE);
                                }
                            }
                        }
                    }
                }
            }
        }
        else {
            /*! @retval  MessageQCopy_E_INVALIDARG Invalid handle argument
                                             provided. */
            status = MessageQCopy_E_INVALIDARG;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "MessageQCopy_registerNotify",
                                 status,
                                 "Invalid handle argument provided");
        }

        /* Leave critical section protection. */
        IGateProvider_leave (MessageQCopy_module->gateHandle, key);
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "MessageQCopy_registerNotify", status);

    /*! @retval MessageQCopy_S_SUCCESS Operation successful */
    return status;
}


/*
 * Send the specified message to the specified proc using the specified src and
 * dst endpoints.
 */
Int
MessageQCopy_send (UInt16 dstProc, UInt16 srcProc, UInt32 dstEndpt,
                   UInt32 srcEndpt, Ptr data, UInt16 len, Bool wait)
{

    Int32                               status      = MessageQCopy_S_SUCCESS;
    MessageQCopyTransport_Object *      obj         = NULL;
    IArg                                key         = NULL;
    struct rpmsg_hdr *                  msg         = NULL;
    Int16                               token       = 0;

    GT_5trace (curTrace, GT_ENTER, "MessageQCopy_send",
               dstProc, dstEndpt, srcEndpt, data, len);

    GT_assert (curTrace, (dstProc < MultiProc_getNumProcessors()));
    GT_assert (curTrace, (data != NULL));
    GT_assert (curTrace, (len > 0));
    GT_assert (curTrace, (len <= (MessageQCopy_BUFSIZE -\
                                  sizeof(struct rpmsg_hdr))));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (Atomic_cmpmask_and_lt (&(MessageQCopy_module->refCount),
                               MessageQCopy_MAKE_MAGICSTAMP(0),
                               MessageQCopy_MAKE_MAGICSTAMP(1))
        == TRUE) {
       /*! @retval  MessageQCopy_E_INVALIDSTATE Notify module not setup */
        status = MessageQCopy_E_INVALIDSTATE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "MessageQCopy_send",
                             status,
                             "MessageQCopy module not setup");
    }
    else if (dstProc >= MultiProc_getNumProcessors()) {
        /*! @retval  MessageQCopy_E_INVALIDARG Invalid procId argument
                                         provided. */
        status = MessageQCopy_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "MessageQCopy_send",
                             status,
                             "Invalid dstProc argument provided");
    }
    else if (srcProc != MultiProc_self()) {
        /*! @retval  MessageQCopy_E_INVALIDARG Invalid procId argument
                                         provided. */
        status = MessageQCopy_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "MessageQCopy_send",
                             status,
                             "Invalid srcProc argument provided");
    }
    else if (data == NULL) {
        /*! @retval  MessageQCopy_E_INVALIDARG Invalid data argument
                                         provided. */
        status = MessageQCopy_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "MessageQCopy_send",
                             status,
                             "Invalid data argument provided");
    }
    else if (len <= 0) {
        /*! @retval  MessageQCopy_E_INVALIDARG Invalid len specified. */
        status = MessageQCopy_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "MessageQCopy_send",
                             status,
                             "Invalid len specified.");
    }
    else if (len > (MessageQCopy_BUFSIZE - sizeof(struct rpmsg_hdr))) {
        /*! @retval  MessageQCopy_E_INVALIDARG Invalid len specified. */
        status = MessageQCopy_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "MessageQCopy_send",
                             status,
                             "Invalid len specified");
    }
    else if (dstEndpt == MessageQCopy_ADDRANY) {
        /*! @retval  MessageQCopy_E_INVALIDARG Invalid dstEndpt. */
        status = MessageQCopy_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "MessageQCopy_send",
                             status,
                             "Invalid dstEndpt.");
    }
    else if (srcEndpt == MessageQCopy_ADDRANY) {
        /*! @retval  MessageQCopy_E_INVALIDARG Invalid srcEndpt. */
        status = MessageQCopy_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "MessageQCopy_send",
                             status,
                             "Invalid srcEndpt.");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

        if (dstProc != MultiProc_self()) {
            /* Enter critical section protection. */
            key = IGateProvider_enter (MessageQCopy_module->gateHandle);

            obj = (MessageQCopyTransport_Object *)
                      MessageQCopy_module->transport[dstProc];

            if (obj == NULL) {
                status = MessageQCopy_E_INVALIDARG;
                GT_1trace(curTrace, GT_2CLASS,
                    "MessageQCopy_send: obj is NULL. Core %d is not attached",
                    dstProc);
            }
            else if (obj->vq[1] == NULL) {
                status = MessageQCopy_E_INVALIDSTATE;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "MessageQCopy is not attached",
                                     status,
                                     "obj->vq[1] is NULL.");
            }
            else {
                /* Get a buf from the UsedBuf list */
                token = VirtQueue_getUsedBuf (obj->vq[1], (Void **)&msg);

                if (token != -1 && msg != NULL) {
                    /* Copy the payload and set message header: */
                    Memory_copy(msg->data, data, len);
                    msg->len = len;
                    msg->dst = dstEndpt;
                    msg->src = srcEndpt;
                    msg->flags = 0;
                    msg->unused = 0;

                    VirtQueue_addAvailBuf(obj->vq[1], msg, sizeof(*msg) + len, token);
                    VirtQueue_kick(obj->vq[1]);
                }
                else {
                    status = MessageQCopy_E_FAIL;
                    GT_setFailureReason (curTrace,
                                         GT_4CLASS,
                                         "MessageQCopy_send",
                                         status,
                                         "getAvailBuf failed.");
                }
            }
            IGateProvider_leave(MessageQCopy_module->gateHandle, key);
        }
        else {
            status = MessageQCopy_E_INVALIDARG;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "MessageQCopy_send",
                                 status,
                                 "sending to local proc not supported.");
        }
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "MessageQCopy_send", status);

    /*! @retval MessageQCopy_S_SUCCESS Operation successful */
    return (status);
}


/* =============================================================================
 *  Internal functions
 * =============================================================================
 */
 static
 Void
 _MessageQCopy_callback_NS(MessageQCopy_Handle handle, void *data,
                            int len, void *priv, UInt32 src, UInt16 srcProc)
{
    struct rpmsg_ns_msg *           msg         = data;
    UInt32                          endpoint    = MessageQCopy_ADDRANY;
    MessageQCopyTransport_Object *  transport   = NULL;

    GT_6trace (curTrace, GT_ENTER, "_MessageQCopy_callback_NS",
               handle, data, len, priv, src, srcProc);

    /* handle will be NULL */
    GT_assert (curTrace, (data != NULL));
    GT_assert (curTrace, (len >= sizeof(struct rpmsg_ns_msg)));
    GT_assert (curTrace, (srcProc < MultiProc_MAXPROCESSORS));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (Atomic_cmpmask_and_lt (&(MessageQCopy_module->refCount),
                               MessageQCopy_MAKE_MAGICSTAMP(0),
                               MessageQCopy_MAKE_MAGICSTAMP(1))
        == TRUE) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "_MessageQCopy_callback_NS",
                             MessageQCopy_E_INVALIDSTATE,
                             "rpmsg module not setup");
    }
    else if (data == NULL) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "_MessageQCopy_callback_NS",
                             MessageQCopy_E_INVALIDARG,
                             "Invalid data argument provided");
    }
    else if (len < sizeof(struct rpmsg_ns_msg)) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "_MessageQCopy_callback_NS",
                             MessageQCopy_E_INVALIDARG,
                             "Invalid len argument provided");
    }
    else if (srcProc >= MultiProc_MAXPROCESSORS) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "_MessageQCopy_callback_NS",
                             MessageQCopy_E_INVALIDARG,
                             "Invalid srcProc argument provided");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        transport = MessageQCopy_module->transport[srcProc];

        if (transport) {
            /* Check flag to see if this is a create or destroy call */
            if (msg->flags & RPMSG_NS_DESTROY) {
                MessageQCopy_delete (&transport->mq[msg->addr]);
            }
            else {
                if (!_MessageQCopy_create (transport, msg->addr, msg->name,
                                           msg->desc, NULL, NULL, &endpoint)) {
                    GT_0trace (curTrace, GT_4CLASS,
                               "creating of MQ in NS Callback failed!");
                }
            }
        }
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
}


static
Void
_MessageQCopy_callback_bufReady (VirtQueue_Handle vq, void *arg)
{
    struct rpmsg_hdr *                  msg                 = NULL;
    Bool                                availBufAdded       = FALSE;
    MessageQCopyTransport_Object *      obj                 = NULL;
    MessageQCopy_Object *               mq                  = NULL;
    Int16                               token               = 0;

    if (vq) {
        obj = (MessageQCopyTransport_Object *)arg;
    }

    if (obj && obj->vq[0] == vq) {
        /* this is a notification of a ready message on the remote proc */
        /* Process all available buffers: */
        while ((token = VirtQueue_getUsedBuf(vq, (Void **)&msg)) != -1) {

            /* Put on a Message queue on this processor: */
            mq = MessageQCopy_module->mq[msg->dst];
            if (mq == NULL) {
                Osal_printf ("_MessageQCopy_callback_bufReady: "
                             "no object for endpoint: %d", msg->dst);
            }
            else {
                if (mq->cb) {
                    mq->cb(mq, msg->data, msg->len, mq->priv, msg->src,
                           obj->procId);
                }
                else {
                    Osal_printf ("_MessageQCopy_callback_bufReady: "
                                 "no callback for endpoint: %d", msg->dst);
                }
                VirtQueue_addAvailBuf(vq, msg, sizeof(*msg) + msg->len, token);
                availBufAdded = TRUE;
            }
        }
        if (availBufAdded)  {
           /* Tell host we've processed the buffers: */
           VirtQueue_kick(vq);
        }
    }
    else if (obj && obj->vq[1] == vq) {
        /* this is a notification that the remote proc has processed a buffer */
    }
    else {
        /* something has gone wrong! */
    }
}


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */
