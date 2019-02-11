/*
 *  @file   MessageQCopy.c
 *
 *  @brief      User side MessageQCopy Manager
 *
 *
 *  @ver        02.00.00.53_alpha2
 *
 *  ============================================================================
 *
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


/* Standard headers*/
#include <ti/syslink/Std.h>

/* TBD: this should be removed as getpid should made as osal */
#include <unistd.h>

/* Osal headers*/
#include <ti/syslink/utils/Trace.h>

/* MessageQCopy Headers */
//#include <ti/ipc/MessageQCopy.h>
//#include <_MessageQCopy.h>
#include <MessageQCopyDrvDefs.h>
#include <MessageQCopyDrv.h>


#if defined (__cplusplus)
extern "C" {
#endif /* defined (__cplusplus) */


/* =============================================================================
 *  Macros and types
 * =============================================================================
 */
/*!
 *  @brief  MessageQCopy Module state object
 */
typedef struct MessageQCopy_ModuleObject_tag {
    UInt32          setupRefCount;
    /*!< Reference count for number of times setup/destroy were called in this
         process. */
} MessageQCopy_ModuleObject;


/* =============================================================================
 *  Globals
 * =============================================================================
 */
/*!
 *  @var    MessageQCopy_state
 *
 *  @brief  MessageQCopy state object variable
 */
#if !defined(IPC_BUILD_DEBUG)
static
#endif /* if !defined(IPC_BUILD_DEBUG) */
MessageQCopy_ModuleObject MessageQCopy_state =
{
    .setupRefCount = 0
};

/*!
 *  @var    MessageQCopy_module
 *
 *  @brief  Pointer to the MessageQCopy module state.
 */
#if !defined(IPC_BUILD_DEBUG)
static
#endif /* if !defined(IPC_BUILD_DEBUG) */
MessageQCopy_ModuleObject * MessageQCopy_module = &MessageQCopy_state;


/* =============================================================================
 *  APIs
 * =============================================================================
 */
/* Function to setup the MessageQCopy module. */
Int
MessageQCopy_setup (const MessageQCopy_Config * config)
{
    Int                     status = MessageQCopy_S_SUCCESS;

    GT_1trace (curTrace, GT_ENTER, "MessageQCopy_setup", config);

    /* TBD: Protect from multiple threads. */
    MessageQCopy_module->setupRefCount++;
    /* This is needed at runtime so should not be in IPC_BUILD_OPTIMIZE. */
    if (MessageQCopy_module->setupRefCount > 1) {
        status = MessageQCopy_S_ALREADYSETUP;
        GT_1trace (curTrace,
                   GT_1CLASS,
                   "MessageQCopy module has been already setup in this process.\n"
                   "    RefCount: [%d]\n",
                   MessageQCopy_module->setupRefCount);
    }
    else {
        /* Open the driver handle. */
        status = MessageQCopyDrv_open ();
#if !defined(IPC_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "MessageQCopy_setup",
                                 status,
                                 "Failed to open driver handle!");
        }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
    }

    GT_1trace (curTrace, GT_LEAVE, "MessageQCopy_setup", status);

    return status;
}


/* Function to destroy the MessageQCopy module. */
Int
MessageQCopy_destroy (void)
{
    Int                 status = MessageQCopy_S_SUCCESS;

    GT_0trace (curTrace, GT_ENTER, "MessageQCopy_destroy");

    /* TBD: Protect from multiple threads. */
    MessageQCopy_module->setupRefCount--;
    /* This is needed at runtime so should not be in IPC_BUILD_OPTIMIZE. */
    if (MessageQCopy_module->setupRefCount >= 1) {
        status = MessageQCopy_S_ALREADYSETUP;
        GT_1trace (curTrace,
                   GT_1CLASS,
                   "MessageQCopy module has been already setup in this process.\n"
                   "    RefCount: [%d]\n",
                   MessageQCopy_module->setupRefCount);
    }
    else {
        /* Close the driver handle. */
        MessageQCopyDrv_close ();
    }

    GT_1trace (curTrace, GT_LEAVE, "MessageQCopy_destroy", status);

    return status;
}


/*!
 *  @brief      This function runs a MessgeQ test in the kernel.
 *
 *  @param      testNo          Test number to run.
 *
 *  @return     MessageQCopy_S_SUCCESS       Success.
 *              MessageQCopy_E_OSFAILURE     Failure in ioctl call.
 *
 *  @sa         MessageQCopyDrv_ioctl
 */
Int
MessageQCopy_runtest (UInt32 testNo)

{
    Int32                       status      = MessageQCopy_S_SUCCESS;
    MessageQCopyDrv_CmdArgs     cmdArgs;

    GT_1trace (curTrace, GT_ENTER, "MessageQCopy_runtest",
               testNo);

    cmdArgs.args.runtest.testNo = testNo;

    status = MessageQCopyDrv_ioctl (CMD_MESSAGEQCOPY_RUNTEST, &cmdArgs);
#if !defined(IPC_BUILD_OPTIMIZE)
    if (status < 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "MessageQCopy_runtest",
                             status,
                             "API (through IOCTL) failed!");
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "MessageQCopy_runtest", status);

    /*! @retval MessageQCopy_S_SUCCESS Operation successful */
    return (status);
}

#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */
