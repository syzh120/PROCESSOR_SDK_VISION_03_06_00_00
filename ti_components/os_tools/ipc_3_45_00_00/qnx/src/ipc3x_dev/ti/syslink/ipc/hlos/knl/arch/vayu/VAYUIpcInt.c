/*
 *  @file   VAYUIpcInt.c
 *
 *  @brief      VAYU interrupt handling code.
 *              Defines necessary functions for Interrupt Handling.
 *
 *
 *  ============================================================================
 *
 *  Copyright (c) 2013-2015, Texas Instruments Incorporated
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
 *  Contact information for paper mail:
 *  Texas Instruments
 *  Post Office Box 655303
 *  Dallas, Texas 75265
 *  Contact information:
 *  http://www-k.ext.ti.com/sc/technical-support/product-information-centers.htm?
 *  DCMP=TIHomeTracking&HQS=Other+OT+home_d_contact
 *  ============================================================================
 *
 */



/* Standard headers */
#include <ti/syslink/Std.h>

/* OSAL headers */
#include <ti/syslink/utils/Trace.h>
#include <ti/syslink/utils/List.h>
#include <Bitops.h>

/* OSAL and utils headers */
#include <OsalIsr.h>
#include <_MultiProc.h>
#include <ti/ipc/MultiProc.h>
#include <ti/syslink/utils/Memory.h>
#include <ti/syslink/utils/Gate.h>
#include <ti/syslink/utils/GateMutex.h>

/* Hardware Abstraction Layer */
#include <_ArchIpcInt.h>
#include <_VAYUIpcInt.h>
#include <VAYUIpcInt.h>
#include <errno.h>


#if defined (__cplusplus)
extern "C" {
#endif

/* From TableInit.xs in packages/ti/sdo/ipc/family/vayu: */
/*
 * src     dst     mbox userid  subidx
 * IPU1_0  DSP1    5    0       3
 * HOST    DSP1    5    0       5
 * IPU1_1  DSP1    5    0       8
 * DSP1    IPU1_0  5    1       0
 * HOST    IPU1_0  5    1       6
 * DSP1    HOST    5    2       1
 * IPU1_0  HOST    5    2       4
 * IPU1_1  HOST    5    2       9
 * DSP1    IPU1_1  5    3       2
 * HOST    IPU1_1  5    3       7
 * IPU2_0  DSP2    6    0       3
 * HOST    DSP2    6    0       5
 * IPU2_1  DSP2    6    0       8
 * DSP2    IPU2_0  6    1       0
 * HOST    IPU2_0  6    1       6
 * DSP2    HOST    6    2       1
 * IPU2_0  HOST    6    2       4
 * IPU2_1  HOST    6    2       9
 * DSP2    IPU2_1  6    3       2
 * HOST    IPU2_1  6    3       7
 */

/* =============================================================================
 *  Macros and types
 * =============================================================================
 */

/*!
 *  @def    VAYU_VAYU_NUMPROCS
 *  @brief  Number of processors supported on this platform
 */
#define VAYU_NUMPROCS 5
/*!
 *  @def    VAYU_INDEX_DSP1
 *  @brief  Dsp1 index.
 */
#define VAYU_INDEX_DSP1 4
/*!
 *  @def    VAYU_INDEX_DSP2
 *  @brief  Dsp2 index.
 */
#define VAYU_INDEX_DSP2 3
/*!
 *  @def    VAYU_INDEX_IPU1
 *  @brief  IPU1 index.
 */
#define VAYU_INDEX_IPU1 2
/*!
 *  @def    VAYU_INDEX_IPU2
 *  @brief  IPU2 index.
 */
#define VAYU_INDEX_IPU2 1
/*!
 *  @def    VAYU_INDEX_HOST
 *  @brief  HOST index.
 */
#define VAYU_INDEX_HOST 0

/*!
 *  @def    VAYU_HOST_IPU1_MBOX
 *  @brief  Mailbox used for HOST<->IPU1 communication.
 */
#define VAYU_HOST_IPU1_MBOX 5

/*!
 *  @def    VAYU_HOST_IPU2_MBOX
 *  @brief  Mailbox used for HOST<->IPU2 communication.
 */
#define VAYU_HOST_IPU2_MBOX 6

/*!
 *  @def    IPU1_HOST_SUB_MBOX
 *  @brief  Sub-Mailbox used for IPU1->HOST communication.
 */
#define IPU1_HOST_SUB_MBOX  4

/*!
 *  @def    HOST_IPU1_SUB_MBOX
 *  @brief  Sub-Mailbox used for HOST->IPU1 communication.
 */
#define HOST_IPU1_SUB_MBOX  6

/*!
 *  @def    IPU2_HOST_SUB_MBOX
 *  @brief  Sub-Mailbox used for IPU2->HOST communication.
 */
#define IPU2_HOST_SUB_MBOX  4

/*!
 *  @def    HOST_IPU2_SUB_MBOX
 *  @brief  Sub-Mailbox used for HOST->IPU2 communication.
 */
#define HOST_IPU2_SUB_MBOX  6

/*!
 *  @def    VAYU_HOST_DSP1_MBOX
 *  @brief  Mailbox used for HOST<->DSP1 communication.
 */
#define VAYU_HOST_DSP1_MBOX 5

/*!
 *  @def    DSP1_HOST_SUB_MBOX
 *  @brief  Mailbox used for DSP1->HOST communication.
 */
#define DSP1_HOST_SUB_MBOX  1

/*!
 *  @def    HOST_DSP1_SUB_MBOX
 *  @brief  Mailbox used for HOST->DSP1 communication.
 */
#define HOST_DSP1_SUB_MBOX  5

/*!
 *  @def    VAYU_HOST_DSP2_MBOX
 *  @brief  Mailbox used for HOST<->DSP2 communication.
 */
#define VAYU_HOST_DSP2_MBOX 6

/*!
 *  @def    DSP2_HOST_SUB_MBOX
 *  @brief  Mailbox used for DSP2->HOST communication.
 */
#define DSP2_HOST_SUB_MBOX  1

/*!
 *  @def    HOST_DSP2_SUB_MBOX
 *  @brief  Mailbox used for HOST->DSP2 communication.
 */
#define HOST_DSP2_SUB_MBOX  5

/*!
 *  @def    VAYU_HOST_USER_ID
 *  @brief  User ID of HOST.
 */
#define VAYU_HOST_USER_ID 2

/*!
 *  @def    VAYU_IPU1_USER_ID
 *  @brief  User ID of IPU2.
 */
#define VAYU_IPU1_USER_ID 1

/*!
 *  @def    VAYU_IPU2_USER_ID
 *  @brief  User ID of IPU2.
 */
#define VAYU_IPU2_USER_ID 1

/*!
 *  @def    VAYU_DSP1_USER_ID
 *  @brief  User ID of DSP1.
 */
#define VAYU_DSP1_USER_ID 0

/*!
 *  @def    VAYU_DSP2_USER_ID
 *  @brief  User ID of DSP2.
 */
#define VAYU_DSP2_USER_ID 0

/* Macro to make a correct module magic number with refCount */
#define VAYUIPCINT_MAKE_MAGICSTAMP(x) \
                                    ((VAYUIPCINT_MODULEID << 12u) | (x))

/*!
 *  @def    REG
 *  @brief  Regsiter access method.
 */
#define REG(x)          *((volatile UInt32 *) (x))
#define REG32(x)        (*(volatile UInt32 *) (x))

/* Register access method. */
#define REG16(A)        (*(volatile UInt16 *) (A))

/*!
 *  @def    AINTC_BASE_ADDR
 *  @brief  configuraion address.
 */
#define AINTC_BASE_ADDR                 0x48200000

/*!
 *  @def    AINTC_BASE_SIZE
 *  @brief  size to be ioremapped.
 */
#define AINTC_BASE_SIZE                 0x1000

/*!
 *  @def    CTRL_MODULE_BASE
 *  @brief  configuration address.
 */
#define CTRL_MODULE_BASE                 0x4A002000

/*!
 *  @def    CTRL_MODULE_SIZE
 *  @brief  size to be ioremapped.
 */
#define CTRL_MODULE_SIZE                 0x1000

/*!
 *  @def    CTRL_MODULE_MMR_OFFSET
 *  @brief  offset in ctrl module to MMR LOCK reg.
 */
#define CTRL_MODULE_MMR_OFFSET           0x544

/*!
 *  @def    CTRL_MODULE_MPU_OFFSET
 *  @brief  offset in ctrl module to MPU INTs.
 */
#define CTRL_MODULE_MPU_OFFSET           0xA4C

/*!
 *  @def    CTRL_MODULE_INT_BASE
 *  @brief  interrupt num at offset.
 */
#define CTRL_MODULE_INT_BASE             0x8

/*!
 *  @def    CTRL_MODULE_INT_m_OFFSET
 *  @brief  interrupt num at offset.
 */
#define CTRL_MODULE_INT_m_OFFSET(m)      CTRL_MODULE_MPU_OFFSET + \
                                         ((((m) - CTRL_MODULE_INT_BASE) / 2) * 4) - \
                                         (((m) > 131) ? 4 : 0)

/*!
 *  @def    IRQ_XBAR_MBOX_6_USR_2
 *  @brief  irq xbar num for mailbox 6 user 2.
 */
#define IRQ_XBAR_MBOX_6_USR_2            255

/*!
 *  @def    IRQ_XBAR_MBOX_5_USR_2
 *  @brief  irq xbar num for mailbox 5 user 2.
 */
#define IRQ_XBAR_MBOX_5_USR_2            251

/*!
 *  @def    IRQ_XBAR_DSP1
 *  @brief  irq xbar num for dsp1.
 */
#define IRQ_XBAR_DSP1                    IRQ_XBAR_MBOX_5_USR_2

/*!
 *  @def    IRQ_XBAR_DSP2
 *  @brief  irq xbar num for dsp2.
 */
#define IRQ_XBAR_DSP2                    IRQ_XBAR_MBOX_6_USR_2

/*!
 *  @def    IRQ_XBAR_IPU1
 *  @brief  irq xbar num for ipu1.
 */
#define IRQ_XBAR_IPU1                    IRQ_XBAR_MBOX_5_USR_2

/*!
 *  @def    IRQ_XBAR_IPU2
 *  @brief  irq xbar num for ipu2.
 */
#define IRQ_XBAR_IPU2                    IRQ_XBAR_MBOX_6_USR_2

/* Mailbox management values */
/*!
 *  @def    VAYU_MAILBOX_5_BASE
 *  @brief  configuraion address.
 */
#define MAILBOX_5_BASE                   0x48840000

/*!
 *  @def    VAYU_MAILBOX_6_BASE
 *  @brief  configuraion address.
 */
#define MAILBOX_6_BASE                   0x48842000

/*!
 *  @def    MAILBOX_SIZE
 *  @brief  size to be ioremapped.
 */
#define MAILBOX_SIZE                     0x1000

/*!
 *  @def    MAILBOX_SYSCONFIG_OFFSET
 *  @brief  Offset from the Mailbox base address.
 */
#define MAILBOX_SYSCONFIG_OFFSET      0x10

/*!
 *  @def    MAILBOX_MAXNUM
 *  @brief  maximum number of mailbox.
 */
#define MAILBOX_MAXNUM                   0xC

/*!
 *  @def    MAILBOX_MESSAGE_m_OFFSET
 *  @brief  mailbox message address Offset from the Mailbox base
 *          address. m = 0 to 7 => offset = 0x40 + 0x4*m
 */
#define MAILBOX_MESSAGE_m_OFFSET(m)        (0x40 + (m<<2))

/*!
 *  @def    MAILBOX_MSGSTATUS_m_OFFSET
 *  @brief  mailbox message status address Offset from the Mailbox base
 *          address. m = 0 to 7 => offset = 0x40 + 0x4*m
 */
#define MAILBOX_MSGSTATUS_m_OFFSET(m)        (0xC0 + (m<<2))

/*!
 *  @def    MAILBOX_IRQSTATUS_CLEAR_OFFSET
 *  @brief  mailbox IRQSTATUS clear address Offset from the Mailbox base
 *          address.
 */
#define MAILBOX_IRQSTATUS_CLEAR_OFFSET  0x104

/*!
 *  @def    MAILBOX_IRQENABLE_SET_OFFSET
 *  @brief  mailbox IRQ enable set address Offset from the Mailbox base
 *          address.
 */
#define MAILBOX_IRQENABLE_SET_OFFSET    0x108
/*!
 *  @def    MAILBOX_IRQENABLE_CLR_OFFSET
 *  @brief  mailbox IRQ enable clear address Offset from the Mailbox base
 *          address.
 */
#define MAILBOX_IRQENABLE_CLR_OFFSET    0x10C


/* Macro used when saving the mailbox context */
#define VAYU_MAILBOX_IRQENABLE(u)    (0x108 + 0x10 * (u))

/* Msg elem used to store messages from the remote proc */
typedef struct VAYUIpcInt_MsgListElem_tag {
    List_Elem elem;
    UInt32 msg;
    struct VAYUIpcInt_MsgListElem * next;
    struct VAYUIpcInt_MsgListElem * prev;
} VAYUIpcInt_MsgListElem;

/* Msg elem used to store isrHandles */
typedef struct VAYUIpcInt_isrHandleElem_tag {
    List_Elem      elem;
    OsalIsr_Handle isrHandle;
    UInt32         intId;
    Atomic         refCount;
} VAYUIpcInt_isrHandleElem;

/*!
 *  @brief  Device specific object
 *          It can be populated as per device need and it is used internally in
 *          the device specific implementation only.
 */
typedef struct VAYUIpcInt_Object_tag {
    Atomic                 isrRefCount;
    /*!< ISR Reference count */
    Atomic                 asserted;
    /*!< Indicates receipt of interrupt from particular processor */
    UInt32                 recvIntId;
    /*!<recevive interrupt id */
    ArchIpcInt_CallbackFxn fxn;
    /*!< Callbck function to be registered for particular instance of driver*/
    Ptr                    fxnArgs;
    /*!< Argument to the call back function */
    List_Elem             * isrHandle;
    /*!< isrHandle */
} VAYUIpcInt_Object;


/*!
 *  @brief  Device specific object
 *          It can be populated as per device need and it is used internally in
 *          the device specific implementation only.
 */
typedef struct VAYUIpcInt_ModuleObject_tag {
    Atomic             isrRefCount;
    /*!< ISR Reference count */
    //OsalIsr_Handle     isrHandle;
    List_Handle        isrHandles;
    /*!< Handle to the OsalIsr object */
    UInt16             procIds [VAYU_NUMPROCS];
    /*!< Processors supported */
    UInt16             maxProcessors;
    /*!< Maximum number of processors supported by this platform*/
    VAYUIpcInt_Object isrObjects [MultiProc_MAXPROCESSORS];
    /*!< Array of Isr objects */
    List_Handle isrLists [MultiProc_MAXPROCESSORS];
    /*!< Array of Isr lists */
    UInt32         archCoreCmBase;
    /*!< configuration mgmt base */
    UInt32         mailbox5Base;
    /*!< mail box configuration mgmt base */
    UInt32         mailbox6Base;
    /*!< mail box configuration mgmt base */
    UInt32         controlModuleBase;
    /*!< control module base */
    UInt32         intId;
    /*!< interrupt id for this proc */
} VAYUIpcInt_ModuleObject;



/* =============================================================================
 * Forward declarations of internal functions.
 * =============================================================================
 */
/* This function implements the interrupt service routine for the interrupt
 * received from the remote processor.
 */
static Bool _VAYUIpcInt_isr (Ptr ref);

/*!
 *  @brief  Forward declaration of check and clear function
 */
static Bool _VAYUIpcInt_checkAndClearFunc (Ptr arg);


/* =============================================================================
 *  Globals
 * =============================================================================
 */
/*!
 *  @brief  State object for VAYUIpcInt
 */
VAYUIpcInt_ModuleObject VAYUIpcInt_state;

/*!
 *  @brief  Function table for OMAP3530
 */
ArchIpcInt_FxnTable VAYUIpcInt_fxnTable = {
    VAYUIpcInt_interruptRegister,
    VAYUIpcInt_interruptUnregister,
    VAYUIpcInt_interruptEnable,
    VAYUIpcInt_interruptDisable,
    VAYUIpcInt_waitClearInterrupt,
    VAYUIpcInt_sendInterrupt,
    VAYUIpcInt_clearInterrupt,
};

int mailbox_5_context_ipu1[MAILBOX_SIZE];
int mailbox_5_context_ipu2[MAILBOX_SIZE];
int mailbox_6_context[MAILBOX_SIZE];

/* =============================================================================
 *  APIs
 * =============================================================================
 */

/*!
 *  @brief      Function to initialize the VAYUIpcInt module.
 *
 *  @param      cfg  Configuration for setup
 *
 *  @sa         VAYUIpcInt_destroy
 */
Void
VAYUIpcInt_setup (VAYUIpcInt_Config * cfg)
{
#if !defined(IPC_BUILD_OPTIMIZE)
    Int            status = VAYUIPCINT_SUCCESS;
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
    Int i = 0;
    Memory_MapInfo mapInfo;
    List_Params listParams;

    GT_1trace (curTrace, GT_ENTER, "VAYUIpcInt_setup", cfg);

    GT_assert (curTrace, (cfg != NULL));

    /* The setup will be called only once, either from SysMgr or from
     * archipcvayu module. Hence it does not need to be atomic.
     */
#if !defined(IPC_BUILD_OPTIMIZE)
    if (cfg == NULL) {
        GT_setFailureReason (curTrace,
                        GT_4CLASS,
                        "VAYUIpcInt_setup",
                        VAYUIPCINT_E_FAIL,
                        "config for driver specific setup can not be NULL");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

        /* Map general control base */
        mapInfo.src      = AINTC_BASE_ADDR;
        mapInfo.size     = AINTC_BASE_SIZE;
        mapInfo.isCached = FALSE;
#if !defined(IPC_BUILD_OPTIMIZE)
        status =
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        Memory_map (&mapInfo);
#if !defined(IPC_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "VAYUIpcInt_setup",
                                 status,
                                 "Failure in Memory_map for general ctrl base");
            VAYUIpcInt_state.archCoreCmBase = 0;
        }
        else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
            VAYUIpcInt_state.archCoreCmBase = mapInfo.dst;
            /* Map mailbox5Base */
            mapInfo.src      = MAILBOX_5_BASE;
            mapInfo.size     = MAILBOX_SIZE;
            mapInfo.isCached = FALSE;
 #if !defined(IPC_BUILD_OPTIMIZE)
            status =
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
                Memory_map (&mapInfo);
#if !defined(IPC_BUILD_OPTIMIZE)
            if (status < 0) {
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "VAYUIpcInt_setup",
                                     status,
                                     "Failure in Memory_map for mailbox5Base");
                VAYUIpcInt_state.mailbox5Base = 0;
            }
            else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
                VAYUIpcInt_state.mailbox5Base = mapInfo.dst;
                /* Map mailbox5Base */
                mapInfo.src      = MAILBOX_6_BASE;
                mapInfo.size     = MAILBOX_SIZE;
                mapInfo.isCached = FALSE;
#if !defined(IPC_BUILD_OPTIMIZE)
                status =
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
                    Memory_map (&mapInfo);
#if !defined(IPC_BUILD_OPTIMIZE)
                if (status < 0) {
                    GT_setFailureReason (curTrace,
                                         GT_4CLASS,
                                         "VAYUIpcInt_setup",
                                         status,
                                         "Failure in Memory_map for mailbox6Base");
                    VAYUIpcInt_state.mailbox6Base = 0;
                }
                else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
                    VAYUIpcInt_state.mailbox6Base = mapInfo.dst;
                    /* Map mailbox5Base */
                    mapInfo.src      = CTRL_MODULE_BASE;
                    mapInfo.size     = CTRL_MODULE_SIZE;
                    mapInfo.isCached = FALSE;
#if !defined(IPC_BUILD_OPTIMIZE)
                    status =
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
                        Memory_map (&mapInfo);
#if !defined(IPC_BUILD_OPTIMIZE)
                    if (status < 0) {
                        GT_setFailureReason (curTrace,
                                             GT_4CLASS,
                                             "VAYUIpcInt_setup",
                                             status,
                                             "Failure in Memory_map for mailbox6Base");
                        VAYUIpcInt_state.controlModuleBase = 0;
                    }
                    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
                        VAYUIpcInt_state.controlModuleBase = mapInfo.dst;

                        /* Program the MMR lock registers to access the SCM
                         * IRQ crossbar register address range */
                        REG32(VAYUIpcInt_state.controlModuleBase + CTRL_MODULE_MMR_OFFSET) = 0xF757FDC0;

                        /* Reset Mailbox 5 */
                        REG(VAYUIpcInt_state.mailbox5Base + MAILBOX_SYSCONFIG_OFFSET) =
                            REG(VAYUIpcInt_state.mailbox5Base + MAILBOX_SYSCONFIG_OFFSET) | 0x1;
                        while (REG(VAYUIpcInt_state.mailbox5Base + MAILBOX_SYSCONFIG_OFFSET) == 0x1);
                        /*Set Mailbox to Smart Idle */
                        REG(VAYUIpcInt_state.mailbox5Base + MAILBOX_SYSCONFIG_OFFSET) = 0x8;
                        /* Reset Mailbox 6 */
                        REG(VAYUIpcInt_state.mailbox6Base + MAILBOX_SYSCONFIG_OFFSET) =
                            REG(VAYUIpcInt_state.mailbox6Base + MAILBOX_SYSCONFIG_OFFSET) | 0x1;
                        while (REG(VAYUIpcInt_state.mailbox6Base + MAILBOX_SYSCONFIG_OFFSET) == 0x1);
                        /*Set Mailbox to Smart Idle */
                        REG(VAYUIpcInt_state.mailbox6Base + MAILBOX_SYSCONFIG_OFFSET) = 0x8;
#if !defined(IPC_BUILD_OPTIMIZE)
                    }
                }
            }
        }
        if (status >= 0) {
            /*Registering vayu platform with ArchIpcInt*/
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
            ArchIpcInt_object.fxnTable = &VAYUIpcInt_fxnTable;
            ArchIpcInt_object.obj      = &VAYUIpcInt_state;

            for (i = 0; i < MultiProc_getNumProcessors(); i++ ) {
                Atomic_set (&(VAYUIpcInt_state.isrObjects [i].asserted), 1);
                List_Params_init(&listParams);
                VAYUIpcInt_state.isrLists [i] = List_create(&listParams);
                if (VAYUIpcInt_state.isrLists [i] == NULL) {
                    status = VAYUIPCINT_E_MEMORY;
                    GT_setFailureReason (curTrace,
                                         GT_4CLASS,
                                         "VAYUIpcInt_setup",
                                         status,
                                         "Failure in List_create");
                    for (i = i - 1; i >= 0; i--) {
                        List_delete(&VAYUIpcInt_state.isrLists [i]);
                    }
                    break;
                }
            }

            List_Params_init(&listParams);
            VAYUIpcInt_state.isrHandles = List_create(&listParams);

            /* Calling MultiProc APIs here in setup save time in ISR and makes
             * it small and fast with less overhead.  This can be done
             * regardless of status.
             */
            VAYUIpcInt_state.procIds [VAYU_INDEX_DSP1] =
                                                       MultiProc_getId ("DSP1");
            VAYUIpcInt_state.procIds [VAYU_INDEX_DSP2] =
                                                       MultiProc_getId ("DSP2");
            VAYUIpcInt_state.procIds [VAYU_INDEX_IPU1] =
                                                       MultiProc_getId ("IPU1");
            VAYUIpcInt_state.procIds [VAYU_INDEX_IPU2] =
                                                    MultiProc_getId ("IPU2");
            VAYUIpcInt_state.maxProcessors = MultiProc_getNumProcessors();

            if (status >= 0) {
                ArchIpcInt_object.isSetup  = TRUE;
            }
#if !defined(IPC_BUILD_OPTIMIZE)
        }
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_0trace (curTrace, GT_LEAVE, "VAYUIpcInt_setup");
}


/*!
 *  @brief      Function to finalize the VAYUIpcInt module
 *
 *  @sa         VAYUIpcInt_setup
 */
Void
VAYUIpcInt_destroy (Void)
{
    Memory_UnmapInfo unmapInfo;
    UInt32 i = 0;
    List_Elem * elem = NULL, * temp = NULL;

    GT_0trace (curTrace, GT_ENTER, "VAYUIpcInt_destroy");

    GT_assert (curTrace,(ArchIpcInt_object.isSetup == TRUE));

    ArchIpcInt_object.isSetup  = FALSE;
    ArchIpcInt_object.obj      = NULL;
    ArchIpcInt_object.fxnTable = NULL;

    for (i = 0; i < MultiProc_getNumProcessors(); i++ ) {
        if (VAYUIpcInt_state.isrLists [i]) {
            List_delete(&VAYUIpcInt_state.isrLists [i]);
        }
    }

    List_traverse_safe(elem, temp, VAYUIpcInt_state.isrHandles) {
        Memory_free(NULL, elem, sizeof(VAYUIpcInt_isrHandleElem));
    }
    List_delete(&VAYUIpcInt_state.isrHandles);

    if (VAYUIpcInt_state.archCoreCmBase != (UInt32) NULL) {
        unmapInfo.addr = VAYUIpcInt_state.archCoreCmBase;
        unmapInfo.size = AINTC_BASE_SIZE;
        unmapInfo.isCached = FALSE;
        Memory_unmap (&unmapInfo);
        VAYUIpcInt_state.archCoreCmBase = (UInt32) NULL;
    }

    if (VAYUIpcInt_state.mailbox5Base != (UInt32) NULL) {
        unmapInfo.addr = VAYUIpcInt_state.mailbox5Base;
        unmapInfo.size = MAILBOX_SIZE;
        unmapInfo.isCached = FALSE;
        Memory_unmap (&unmapInfo);
        VAYUIpcInt_state.mailbox5Base = (UInt32) NULL;
    }

    if (VAYUIpcInt_state.mailbox6Base != (UInt32) NULL) {
        unmapInfo.addr = VAYUIpcInt_state.mailbox6Base;
        unmapInfo.size = MAILBOX_SIZE;
        unmapInfo.isCached = FALSE;
        Memory_unmap (&unmapInfo);
        VAYUIpcInt_state.mailbox6Base = (UInt32) NULL;
    }

    if (VAYUIpcInt_state.controlModuleBase != (UInt32) NULL) {
        unmapInfo.addr = VAYUIpcInt_state.controlModuleBase;
        unmapInfo.size = CTRL_MODULE_SIZE;
        unmapInfo.isCached = FALSE;
        Memory_unmap (&unmapInfo);
        VAYUIpcInt_state.controlModuleBase = (UInt32) NULL;
    }

    GT_0trace (curTrace, GT_ENTER, "VAYUIpcInt_destroy");
}


/*!
 *  @brief      Function to register the interrupt.
 *
 *  @param      procId  destination procId.
 *  @param      intId   interrupt id.
 *  @param      fxn     callback function to be called on receiving interrupt.
 *  @param      fxnArgs arguments to the callback function.
 *
 *  @sa         VAYUIpcInt_interruptEnable
 */

Int32
VAYUIpcInt_interruptRegister  (UInt16                     procId,
                               UInt32                     intId,
                               ArchIpcInt_CallbackFxn     fxn,
                               Ptr                        fxnArgs)
{
    Int32 status = VAYUIPCINT_SUCCESS;
    OsalIsr_Params isrParams;
    OsalIsr_Handle isrHandle;
    List_Elem * elem = NULL;
    UInt32 reg = 0;
    UInt32 mboxId = 0;

    GT_4trace (curTrace,
               GT_ENTER,
               "VAYUIpcInt_interruptRegister",
               procId,
               intId,
               fxn,
               fxnArgs);

    GT_assert (curTrace,(ArchIpcInt_object.isSetup == TRUE));
    GT_assert(curTrace, (procId < MultiProc_MAXPROCESSORS));
    GT_assert(curTrace, (fxn != NULL));


    /* This sets the refCount variable if not initialized, upper 16 bits is
     * written with module Id to ensure correctness of refCount variable.
     */
    Atomic_cmpmask_and_set (
                            &VAYUIpcInt_state.isrObjects [procId].isrRefCount,
                            VAYUIPCINT_MAKE_MAGICSTAMP(0),
                            VAYUIPCINT_MAKE_MAGICSTAMP(0));

    /* This is a normal use-case, so should not be inside
     * IPC_BUILD_OPTIMIZE.
     */
    if (Atomic_inc_return (&VAYUIpcInt_state.isrObjects [procId].isrRefCount)
            != VAYUIPCINT_MAKE_MAGICSTAMP(1u)) {
        /*! @retval VAYUIPCINT_S_ALREADYREGISTERED ISR already registered!
         */
            status = VAYUIPCINT_S_ALREADYREGISTERED;
        GT_0trace (curTrace,
                   GT_2CLASS,
                   "ISR already registered!");
    }
    else {
        VAYUIpcInt_state.isrObjects [procId].fxn       = fxn;
        VAYUIpcInt_state.isrObjects [procId].fxnArgs   = fxnArgs;
        VAYUIpcInt_state.isrObjects [procId].recvIntId = intId;
        /* Enable hardware interrupt. */
        VAYUIpcInt_interruptEnable (procId, intId);
    }

    isrParams.sharedInt        = FALSE;
    isrParams.checkAndClearFxn = &_VAYUIpcInt_checkAndClearFunc;
    isrParams.fxnArgs          = NULL;
    isrParams.intId            = intId;

    /* Check if handle is already created/installed */
    List_traverse(elem, VAYUIpcInt_state.isrHandles) {
        if (((VAYUIpcInt_isrHandleElem *)elem)->intId == intId) {
            Atomic_inc_return (&((VAYUIpcInt_isrHandleElem *)elem)->refCount);
            status = VAYUIPCINT_S_ALREADYREGISTERED;
            GT_0trace (curTrace,
                       GT_2CLASS,
                       "ISR already set !");
            break;
        }
    }
    if (elem == &((List_Object *)VAYUIpcInt_state.isrHandles)->elem) {
        if (procId == VAYUIpcInt_state.procIds [VAYU_INDEX_DSP1]) {
            mboxId = IRQ_XBAR_DSP1;
        }
        else if (procId == VAYUIpcInt_state.procIds [VAYU_INDEX_DSP2]) {
            mboxId = IRQ_XBAR_DSP2;
        }
        else if (procId == VAYUIpcInt_state.procIds [VAYU_INDEX_IPU1]){
            mboxId = IRQ_XBAR_IPU1;
        }
        else if (procId == VAYUIpcInt_state.procIds [VAYU_INDEX_IPU2]){
            mboxId = IRQ_XBAR_IPU2;
        }

        /* Program the IntXbar */
        reg = REG32(VAYUIpcInt_state.controlModuleBase + CTRL_MODULE_INT_m_OFFSET((intId - 32)));
        if (((intId - 32) - CTRL_MODULE_INT_BASE) % 2) {
            REG32(VAYUIpcInt_state.controlModuleBase + CTRL_MODULE_INT_m_OFFSET((intId - 32))) =
                (reg & 0x0000FFFF) | (mboxId << 16);
        }
        else {
            REG32(VAYUIpcInt_state.controlModuleBase + CTRL_MODULE_INT_m_OFFSET((intId - 32))) =
                (reg & 0xFFFF0000) | (mboxId);
        }
        isrHandle = OsalIsr_create (&_VAYUIpcInt_isr, NULL, &isrParams);
#if !defined(IPC_BUILD_OPTIMIZE)
        if (isrHandle == NULL) {
            /*! @retval VAYUIPCINT_E_FAIL OsalIsr_create failed */
            status = VAYUIPCINT_E_FAIL;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "VAYUIpcInt_interruptRegister",
                                 status,
                                 "OsalIsr_create failed");
        }
        else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
            status = OsalIsr_install (isrHandle);
#if !defined(IPC_BUILD_OPTIMIZE)
            if (status < 0) {
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "VAYUIpcInt_interruptRegister",
                                     status,
                                     "OsalIsr_install failed");
            }
            else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
                elem = Memory_alloc(NULL, sizeof(VAYUIpcInt_isrHandleElem),
                                    0, NULL);
#if !defined(IPC_BUILD_OPTIMIZE)
                if (elem == NULL) {
                    status = VAYUIPCINT_E_MEMORY;
                    GT_setFailureReason (curTrace,
                                         GT_4CLASS,
                                         "VAYUIpcInt_interruptRegister",
                                         status,
                                         "Memory_alloc failed");
                }
                else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
                    ((VAYUIpcInt_isrHandleElem *)elem)->isrHandle = isrHandle;
                    Atomic_cmpmask_and_set (
                              &((VAYUIpcInt_isrHandleElem *)elem)->refCount,
                              VAYUIPCINT_MAKE_MAGICSTAMP(0),
                              VAYUIPCINT_MAKE_MAGICSTAMP(1));
                    ((VAYUIpcInt_isrHandleElem *)elem)->intId = intId;
                    List_put(VAYUIpcInt_state.isrHandles, elem);
#if !defined(IPC_BUILD_OPTIMIZE)
                }
            }
        }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
    }

#if !defined(IPC_BUILD_OPTIMIZE)
    if (status >= 0) {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        VAYUIpcInt_state.isrObjects [procId].isrHandle = elem;
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "VAYUIpcInt_interruptRegister", status);

    /*! @retval VAYUIPCINT_SUCCESS Interrupt successfully registered */
    return status;
}



/*!
 *  @brief      Function to unregister interrupt.
 *
 *  @param      procId  destination procId
 *
 *  @sa         VAYUIpcInt_interruptRegister
 */
Int32
VAYUIpcInt_interruptUnregister  (UInt16 procId)
{
    Int32 status = VAYUIPCINT_SUCCESS;
#if !defined(IPC_BUILD_OPTIMIZE)
    Int32 tmpStatus = VAYUIPCINT_SUCCESS;
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
    VAYUIpcInt_isrHandleElem * isrHandleElem;

    GT_1trace (curTrace,GT_ENTER,"VAYUIpcInt_interruptUnregister", procId);

    GT_assert (curTrace,(ArchIpcInt_object.isSetup == TRUE));
    GT_assert(curTrace, (procId < MultiProc_MAXPROCESSORS));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (   Atomic_cmpmask_and_lt (
                            &VAYUIpcInt_state.isrObjects [procId].isrRefCount,
                            VAYUIPCINT_MAKE_MAGICSTAMP(0),
                            VAYUIPCINT_MAKE_MAGICSTAMP(1))
        == TRUE) {
        /*! @retval VAYUIPCINT_E_INVALIDSTATE ISR was not registered */
        status = VAYUIPCINT_E_INVALIDSTATE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUIpcInt_interruptUnregister",
                             status,
                             "ISR was not registered!");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        /* This is a normal use-case, so should not be inside
         * IPC_BUILD_OPTIMIZE.
         */
        if (Atomic_dec_return(&VAYUIpcInt_state.isrObjects[procId].isrRefCount)
            == VAYUIPCINT_MAKE_MAGICSTAMP(0)) {
            /* Disable hardware interrupt. */
            VAYUIpcInt_interruptDisable (procId,
                              VAYUIpcInt_state.isrObjects [procId].recvIntId);

            VAYUIpcInt_state.isrObjects [procId].fxn       = NULL;
            VAYUIpcInt_state.isrObjects [procId].fxnArgs   = NULL;
            VAYUIpcInt_state.isrObjects [procId].recvIntId = -1u;
        }

        isrHandleElem = (VAYUIpcInt_isrHandleElem *)VAYUIpcInt_state.isrObjects [procId].isrHandle;

        if (   Atomic_dec_return (&isrHandleElem->refCount)
            == VAYUIPCINT_MAKE_MAGICSTAMP(0)) {
            List_remove(VAYUIpcInt_state.isrHandles, (List_Elem *)isrHandleElem);
            status = OsalIsr_uninstall (isrHandleElem->isrHandle);
#if !defined(IPC_BUILD_OPTIMIZE)
            if (status < 0) {
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "VAYUIpcInt_interruptUnregister",
                                     status,
                                     "OsalIsr_uninstall failed");
            }
            tmpStatus =
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
                OsalIsr_delete (&(isrHandleElem->isrHandle));
#if !defined(IPC_BUILD_OPTIMIZE)
            if ((status >= 0) && (tmpStatus < 0)) {
                status = tmpStatus;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "VAYUIpcInt_interruptUnregister",
                                     status,
                                     "OsalIsr_delete failed");
            }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
            Memory_free(NULL, isrHandleElem, sizeof(VAYUIpcInt_isrHandleElem));
        }
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "VAYUIpcInt_interruptUnregister",
               status);

    /*! @retval VAYUIPCINT_SUCCESS Interrupt successfully unregistered */
    return status;
}


/*!
 *  @brief      Function to enable the specified interrupt
 *
 *  @param      procId  Remote processor ID
 *  @param      intId   interrupt id
 *
 *  @sa         VAYUIpcInt_interruptDisable
 */
Void
VAYUIpcInt_interruptEnable (UInt16 procId, UInt32 intId)
{
    GT_2trace (curTrace, GT_ENTER, "VAYUIpcInt_interruptEnable",
               procId, intId);

    GT_assert (curTrace,(ArchIpcInt_object.isSetup == TRUE));
    GT_assert (curTrace, (procId < MultiProc_MAXPROCESSORS));

    if (procId == VAYUIpcInt_state.procIds [VAYU_INDEX_DSP1]) {
        /*
         * Mailbox 5 is used for HOST<->DSP1 communication
         */
        SET_BIT(REG(VAYUIpcInt_state.mailbox5Base + \
                    VAYU_MAILBOX_IRQENABLE(VAYU_HOST_USER_ID)),
                ( (DSP1_HOST_SUB_MBOX) << 1));
    }
    else if (procId == VAYUIpcInt_state.procIds [VAYU_INDEX_DSP2]) {
        /*
         * Mailbox 6 is used for HOST<->DSP2 communication
         */
        SET_BIT(REG(VAYUIpcInt_state.mailbox6Base + \
                    VAYU_MAILBOX_IRQENABLE(VAYU_HOST_USER_ID)),
                ( (DSP2_HOST_SUB_MBOX) << 1));
    }
    else if (procId == VAYUIpcInt_state.procIds [VAYU_INDEX_IPU1]) {
        /*
         * Mailbox 5 is used for HOST<->IPU1 communication
         */
        SET_BIT(REG(VAYUIpcInt_state.mailbox5Base + \
                    VAYU_MAILBOX_IRQENABLE(VAYU_HOST_USER_ID)),
                ( (IPU1_HOST_SUB_MBOX) << 1));
    }
    else if (procId == VAYUIpcInt_state.procIds [VAYU_INDEX_IPU2]) {
        /*
         * Mailbox 6 is used for HOST<->IPU2 communication
         */
        SET_BIT(REG(VAYUIpcInt_state.mailbox6Base + \
                    VAYU_MAILBOX_IRQENABLE(VAYU_HOST_USER_ID)),
                ( (IPU2_HOST_SUB_MBOX) << 1));
    }
#if !defined(IPC_BUILD_OPTIMIZE)
    else {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUIpcInt_interruptEnable",
                             VAYUIPCINT_E_FAIL,
                             "Invalid procId specified");
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_0trace (curTrace, GT_LEAVE, "VAYUIpcInt_interruptEnable");
}


/*!
 *  @brief      Function to disable the specified interrupt
 *
 *  @param      procId  Remote processor ID
 *  @param      intId   interrupt id
 *
 *  @sa         VAYUIpcInt_interruptEnable
 */
Void
VAYUIpcInt_interruptDisable (UInt16 procId, UInt32 intId)
{
    GT_2trace (curTrace, GT_ENTER, "VAYUIpcInt_interruptDisable",
               procId, intId);

    GT_assert (curTrace,(ArchIpcInt_object.isSetup == TRUE));
    GT_assert (curTrace, (procId < MultiProc_MAXPROCESSORS));

    if (procId == VAYUIpcInt_state.procIds [VAYU_INDEX_DSP1]) {
        /*
         * Mailbox 5 is used for HOST<->DSP1 communication
         */
        REG(VAYUIpcInt_state.mailbox5Base + \
            MAILBOX_IRQENABLE_CLR_OFFSET + (0x10 * VAYU_HOST_USER_ID)) =
            1 << ((DSP1_HOST_SUB_MBOX) << 1);
    }
    else if (procId == VAYUIpcInt_state.procIds [VAYU_INDEX_DSP2]) {
        /*
         * Mailbox 6 is used for HOST<->DSP2 communication
         */
        REG(VAYUIpcInt_state.mailbox6Base + \
            MAILBOX_IRQENABLE_CLR_OFFSET + (0x10 * VAYU_HOST_USER_ID)) =
            1 << ((DSP2_HOST_SUB_MBOX) << 1);
    }
    else if (procId == VAYUIpcInt_state.procIds [VAYU_INDEX_IPU1]) {
        /*
         * Mailbox 5 is used for HOST<->IPU1 communication
         */
        REG(VAYUIpcInt_state.mailbox5Base + \
            MAILBOX_IRQENABLE_CLR_OFFSET + (0x10 * VAYU_HOST_USER_ID)) =
            1 << ((IPU1_HOST_SUB_MBOX) << 1);
    }
    else if (procId == VAYUIpcInt_state.procIds [VAYU_INDEX_IPU2]) {
        /*
         * Mailbox 6 is used for HOST<->IPU2 communication
         */
        REG(VAYUIpcInt_state.mailbox6Base + \
            MAILBOX_IRQENABLE_CLR_OFFSET + (0x10 * VAYU_HOST_USER_ID)) =
            1 << ((IPU2_HOST_SUB_MBOX) << 1);
    }
#if !defined(IPC_BUILD_OPTIMIZE)
    else {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUIpcInt_interruptDisable",
                             VAYUIPCINT_E_FAIL,
                             "Invalid procId specified");
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_0trace (curTrace, GT_LEAVE, "VAYUIpcInt_interruptDisable");
}


/*!
 *  @brief      Function to wait for interrupt to be cleared.
 *
 *  @param      procId  Remote processor ID
 *  @param      intId   interrupt id
 *
 *  @sa         VAYUIpcInt_sendInterrupt
 */
Int32
VAYUIpcInt_waitClearInterrupt (UInt16 procId, UInt32 intId)
{
    Int32 status = VAYUIPCINT_SUCCESS;

    GT_2trace (curTrace,GT_ENTER,"VAYUIpcInt_waitClearInterrupt",
               procId, intId);

    GT_assert (curTrace,(ArchIpcInt_object.isSetup == TRUE));
    GT_assert (curTrace, (procId < MultiProc_MAXPROCESSORS));

    if (procId == VAYUIpcInt_state.procIds [VAYU_INDEX_DSP1]) {
        /* Wait for DSP to clear the previous interrupt */
        while( (  REG32((  VAYUIpcInt_state.mailbox5Base
                        + MAILBOX_MSGSTATUS_m_OFFSET(HOST_DSP1_SUB_MBOX)))
                & 0x3F ));
    }
    else if (procId == VAYUIpcInt_state.procIds [VAYU_INDEX_DSP2]) {
        /* Wait for DSP to clear the previous interrupt */
        while( (  REG32((  VAYUIpcInt_state.mailbox6Base
                        + MAILBOX_MSGSTATUS_m_OFFSET(HOST_DSP2_SUB_MBOX)))
                & 0x3F ));
    }
    else if (procId == VAYUIpcInt_state.procIds [VAYU_INDEX_IPU1]) {
        /* Wait for M4 to clear the previous interrupt */
        while( (  REG32((VAYUIpcInt_state.mailbox5Base
                      + MAILBOX_MSGSTATUS_m_OFFSET(HOST_IPU1_SUB_MBOX)))
                & 0x3F ));
    }
    else if (procId == VAYUIpcInt_state.procIds [VAYU_INDEX_IPU2]) {
        /* Wait for M4 to clear the previous interrupt */
        while( (  REG32((VAYUIpcInt_state.mailbox6Base
                      + MAILBOX_MSGSTATUS_m_OFFSET(HOST_IPU2_SUB_MBOX)))
                & 0x3F ));
    }
#if !defined(IPC_BUILD_OPTIMIZE)
    else {
        /*! @retval VAYUIPCINT_E_FAIL Invalid procId specified */
        status = VAYUIPCINT_E_FAIL;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUIpcInt_waitClearInterrupt",
                             status,
                             "Invalid procId specified");
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace,GT_LEAVE,"VAYUIpcInt_waitClearInterrupt", status);

    /*! @retval VAYUIPCINT_SUCCESS Wait for interrupt clearing successfully
                completed. */
    return status ;
}


/*!
 *  @brief      Function to send a specified interrupt to the DSP.
 *
 *  @param      procId  Remote processor ID
 *  @param      intId   interrupt id
 *  @param      value   Value to be sent with the interrupt
 *
 *  @sa         VAYUIpcInt_waitClearInterrupt
 */
Int32
VAYUIpcInt_sendInterrupt (UInt16 procId, UInt32 intId,  UInt32 value)
{
    Int32 status = VAYUIPCINT_SUCCESS;

    GT_3trace (curTrace, GT_ENTER, "VAYUIpcInt_sendInterrupt",
               procId, intId, value);

    GT_assert (curTrace,(ArchIpcInt_object.isSetup == TRUE));
    GT_assert (curTrace, (procId < MultiProc_MAXPROCESSORS));

    if (procId == VAYUIpcInt_state.procIds [VAYU_INDEX_DSP1]) {
        /*
         * Mailbox 5 is used for HOST<->DSP1 communication
         */
        REG32(VAYUIpcInt_state.mailbox5Base + \
                  MAILBOX_MESSAGE_m_OFFSET(HOST_DSP1_SUB_MBOX)) = value;
    }
    else if (procId == VAYUIpcInt_state.procIds [VAYU_INDEX_DSP2]) {
        /*
         * Mailbox 6 is used for HOST<->DSP2 communication
         */
        REG32(VAYUIpcInt_state.mailbox6Base + \
                  MAILBOX_MESSAGE_m_OFFSET(HOST_DSP2_SUB_MBOX)) = value;
    }
    else if (procId == VAYUIpcInt_state.procIds [VAYU_INDEX_IPU1]) {
        /*
         * Mailbox 5 is used for HOST<->IPU1 communication
         */
        REG32(VAYUIpcInt_state.mailbox5Base + \
              MAILBOX_MESSAGE_m_OFFSET(HOST_IPU1_SUB_MBOX)) = value;
    }
    else if (procId == VAYUIpcInt_state.procIds [VAYU_INDEX_IPU2]) {
        /*
         * Mailbox 6 is used for HOST<->IPU2 communication
         */
        REG32(VAYUIpcInt_state.mailbox6Base + \
              MAILBOX_MESSAGE_m_OFFSET(HOST_IPU2_SUB_MBOX)) = value;
    }
#if !defined(IPC_BUILD_OPTIMIZE)
    else {
        /*! @retval VAYUIPCINT_E_FAIL Invalid procId specified */
        status = VAYUIPCINT_E_FAIL;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUIpcInt_sendInterrupt",
                             status,
                             "Invalid procId specified");
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "VAYUIpcInt_sendInterrupt",status);

    /*! @retval VAYUIPCINT_SUCCESS Interrupt successfully sent */
    return status;
}


/*!
 *  @brief      Function to clear the specified interrupt received from the
 *              remote core.
 *
 *  @param      procId  Remote processor ID
 *  @param      intId   interrupt id
 *
 *  @sa         VAYUIpcInt_sendInterrupt
 */
UInt32
VAYUIpcInt_clearInterrupt (UInt16 procId, UInt16 mboxNum)
{
    UInt32 retVal = 0;
    UInt32 mailboxBase = 0;

    GT_1trace (curTrace,GT_ENTER,"VAYUIpcInt_clearInterrupt", mboxNum);

    GT_assert (curTrace,(ArchIpcInt_object.isSetup == TRUE));
    if (procId == VAYUIpcInt_state.procIds [VAYU_INDEX_IPU2] ||
        procId == VAYUIpcInt_state.procIds [VAYU_INDEX_DSP2])
        mailboxBase = VAYUIpcInt_state.mailbox6Base;
    else
        mailboxBase = VAYUIpcInt_state.mailbox5Base;

    if (mboxNum < MAILBOX_MAXNUM) {
        /* Read the register to get the entry from the mailbox FIFO */
        retVal = REG32(mailboxBase + MAILBOX_MESSAGE_m_OFFSET(mboxNum));

        /* Clear the IRQ status.
         * If there are more in the mailbox FIFO, it will re-assert.
         */
        REG32(mailboxBase + MAILBOX_IRQSTATUS_CLEAR_OFFSET + \
                (0x10 * VAYU_HOST_USER_ID)) = 0x1 << (mboxNum << 1);
    }
#if !defined(IPC_BUILD_OPTIMIZE)
    else {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUIpcInt_clearInterrupt",
                             VAYUIPCINT_E_FAIL,
                             "Invalid mailbox number specified");
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_0trace (curTrace, GT_LEAVE, "VAYUIpcInt_clearInterrupt");

    /*! @retval Value Value received with the interrupt. */
    return retVal;
}


/*
 * Instead of constantly allocating and freeing the msg structures
 * we just cache a few of them, and recycle them instead.
 */
#define CACHE_NUM 20
static VAYUIpcInt_MsgListElem *msg_cache;
static int num_msg = 0;

static VAYUIpcInt_MsgListElem *get_msg()
{
    VAYUIpcInt_MsgListElem *msg;
    IArg key = NULL;

    key = Gate_enterSystem();
    msg = msg_cache;
    if (msg != NULL) {
        msg_cache = (VAYUIpcInt_MsgListElem *)msg_cache->next;
        num_msg--;
        Gate_leaveSystem(key);
    } else {
        Gate_leaveSystem(key);
        msg = Memory_alloc(NULL, sizeof(VAYUIpcInt_MsgListElem), 0, NULL);
    }
    return(msg);
}

static void put_msg(VAYUIpcInt_MsgListElem * msg)
{
    IArg key = NULL;
    key = Gate_enterSystem();
    if (num_msg >= CACHE_NUM) {
        Gate_leaveSystem(key);
        Memory_free(NULL, msg, sizeof(*msg));
    } else {
        msg->next = (struct VAYUIpcInt_MsgListElem *)msg_cache;
        msg_cache = msg;
        num_msg++;
        Gate_leaveSystem(key);
    }
    return;
}


/*!
 *  @brief      Function to check and clear the remote proc interrupt
 *
 *  @param      arg     Optional argument to the function.
 *
 *  @sa         _VAYUIpcInt_isr
 */
static
Bool
_VAYUIpcInt_checkAndClearFunc (Ptr arg)
{
    UInt16 procId;
    UInt32 msg;
    VAYUIpcInt_MsgListElem * elem = NULL;

    GT_1trace (curTrace, GT_ENTER, "_VAYUIpcInt_checkAndClearFunc", arg);

    if (REG32(VAYUIpcInt_state.mailbox6Base
              + MAILBOX_MSGSTATUS_m_OFFSET(IPU2_HOST_SUB_MBOX)) != 0 ){
        procId = VAYUIpcInt_state.procIds [VAYU_INDEX_IPU2];
        msg = VAYUIpcInt_clearInterrupt (procId, IPU2_HOST_SUB_MBOX);

        GT_1trace (curTrace, GT_1CLASS, "Got msg [0x%08x] from IPU2", msg);

        /* This is a message from IPU2, put the message in IPU2's list */
        elem = get_msg();
        if (elem) {
            elem->msg = msg;
            List_put(VAYUIpcInt_state.isrLists[procId], (List_Elem *)elem);
        }
    }
    if (REG32(VAYUIpcInt_state.mailbox5Base
              + MAILBOX_MSGSTATUS_m_OFFSET(IPU1_HOST_SUB_MBOX)) != 0 ){
        procId = VAYUIpcInt_state.procIds [VAYU_INDEX_IPU1];
        msg = VAYUIpcInt_clearInterrupt (procId, IPU1_HOST_SUB_MBOX);

        GT_1trace (curTrace, GT_1CLASS, "Got msg [0x%08x] from IPU1", msg);

        /* This is a message from IPU1, put the message in IPU1's list */
        elem = get_msg();
        if (elem) {
            elem->msg = msg;
            List_put(VAYUIpcInt_state.isrLists[procId], (List_Elem *)elem);
        }
    }
    if (REG32(VAYUIpcInt_state.mailbox6Base
              + MAILBOX_MSGSTATUS_m_OFFSET(DSP2_HOST_SUB_MBOX)) != 0 ){
        procId = VAYUIpcInt_state.procIds [VAYU_INDEX_DSP2];
        msg = VAYUIpcInt_clearInterrupt (procId, DSP2_HOST_SUB_MBOX);

        GT_1trace (curTrace, GT_1CLASS, "Got msg [0x%08x] from DSP2", msg);

        /* This is a message from DSP2, put the message in DSP2's list */
        elem = get_msg();
        if (elem) {
            elem->msg = msg;
            List_put(VAYUIpcInt_state.isrLists[procId], (List_Elem *)elem);
        }
    }
    if (REG32(VAYUIpcInt_state.mailbox5Base
              + MAILBOX_MSGSTATUS_m_OFFSET(DSP1_HOST_SUB_MBOX)) != 0 ){
        procId = VAYUIpcInt_state.procIds [VAYU_INDEX_DSP1];
        msg = VAYUIpcInt_clearInterrupt (procId, DSP1_HOST_SUB_MBOX);

        GT_1trace (curTrace, GT_1CLASS, "Got msg [0x%08x] from DSP1", msg);

        /* This is a message from DSP1, put the message in DSP1's list */
        elem = get_msg();
        if (elem) {
            elem->msg = msg;
            List_put(VAYUIpcInt_state.isrLists[procId], (List_Elem *)elem);
        }
    }

    GT_1trace (curTrace, GT_LEAVE, "_VAYUIpcInt_checkAndClearFunc", TRUE);

    /* This is not a shared interrupt, so interrupt has always occurred */
    /*! @retval TRUE Interrupt has occurred. */
    return (TRUE);
}


/*!
 *  @brief      Interrupt Service Routine for VAYUIpcInt module
 *
 *  @param      arg     Optional argument to the function.
 *
 *  @sa         _VAYUIpcInt_checkAndClearFunc
 */
static
Bool
_VAYUIpcInt_isr (Ptr ref)
{
    UInt16 i = 0;
    VAYUIpcInt_MsgListElem * elem = NULL;
    GT_1trace (curTrace, GT_ENTER, "_VAYUIpcInt_isr", ref);

    for (i = 0 ; i < VAYUIpcInt_state.maxProcessors ; i++) {
        if ((elem = List_get(VAYUIpcInt_state.isrLists [i])) != NULL) {
            /*Calling the particular ISR */
            GT_assert(curTrace,(VAYUIpcInt_state.isrObjects [i].fxn != NULL));
            if (VAYUIpcInt_state.isrObjects [i].fxn != NULL) {
                VAYUIpcInt_state.isrObjects [i].fxn (elem->msg,
                                    VAYUIpcInt_state.isrObjects [i].fxnArgs);
            }
            put_msg(elem);
        }
    }

    GT_1trace (curTrace, GT_LEAVE, "_VAYUIpcInt_isr", TRUE);

    /*! @retval TRUE Interrupt has been handled. */
    return (TRUE);
}

#if defined (__cplusplus)
}
#endif
