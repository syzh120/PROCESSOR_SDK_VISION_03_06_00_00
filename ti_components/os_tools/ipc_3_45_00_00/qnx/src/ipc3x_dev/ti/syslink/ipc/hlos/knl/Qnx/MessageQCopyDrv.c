/*
 *  @file       MessageQCopyDrv.c
 *
 *  @brief      devctl handler for MessageQCopy component of IPC module.
 *
 *
 *  @ver        02.00.00.46_alpha1
 *
 *  ============================================================================
 *
 *  Copyright (c) 2010-2015, Texas Instruments Incorporated
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

/* OSAL & Utils headers */
#include <ti/syslink/utils/List.h>
#include <ti/syslink/utils/String.h>
//#include <OsalDriver.h>
#include <ti/syslink/utils/Trace.h>
#include <ti/syslink/utils/Memory.h>
#include <ti/syslink/utils/IGateProvider.h>
#include <ti/syslink/utils/GateSpinlock.h>

/*QNX specific header include */
#include <proto.h>
#include <errno.h>
#include <unistd.h>
#include <sys/iofunc.h>
#include <sys/dispatch.h>

/* Module headers */
#include <_MessageQCopy.h>
#include <ti/ipc/MessageQCopy.h>
#include <MessageQCopyDrvDefs.h>
#include <_MessageQCopyDefs.h>
#include "OsalSemaphore.h"
#include "std_qnx.h"
#include <pthread.h>

/** ============================================================================
 *  Function prototypes
 *  ============================================================================
 */
int MessageQCopyDrv_runtest (resmgr_context_t * ctp, io_devctl_t * msg,
                             ipc_ocb_t * ocb);


/** ============================================================================
 *  Structs
 *  ============================================================================
 */
typedef struct mqcopy_test_handle {
    MessageQCopy_Handle handle;
    UInt16 procId;
    UInt32 endpoint;
} mqcopy_test_handle;


/** ============================================================================
 *  Globals
 *  ============================================================================
 */
#define MQCOPY_TSET_MSG "hello world!"
#define MQCOPY_TEST_NUM_MSG 500

UInt16 local_procid = 0;
UInt32 local_endpoint = 0;
mqcopy_test_handle mqcopy_test_handles[10];
UInt32 mqcopy_test_num_msgs = 0;
OsalSemaphore_Handle mqcopy_test_sem = NULL;


/** ============================================================================
 *  Functions
 *  ============================================================================
 */
/**
 *  @brief        Handler for devctl() messages for MessageQCopyDrv module.
 *
 *  @param ctp    Thread's associated context information.
 *  @param msg    The actual devctl() message.
 *  @param ocb    OCB associated with client's session.
 *
 *  @return       Error: POSIX errno value.
 *                Success: _RESMGR_PTR() value.
 *
 *  @retval       _RESMGR_PTR() value    Success.
 *  @retval       EINVAL                 Invalid argument length.
 *  @retval       ENOSYS                 Unsupported command.
 */
Int
MessageQCopyDrv_devctl (resmgr_context_t * ctp, io_devctl_t * msg,
                        ipc_ocb_t * ocb)
{
    Int status = _RESMGR_ERRNO (EOK);
    Int32 dcmd = msg->i.dcmd;
    msg->o.ret_val = EOK;

    if (ctp->info.msglen - sizeof(msg->i) < sizeof (MessageQCopyDrv_CmdArgs)) {
        status = _RESMGR_ERRNO (EINVAL);
    }
    else {
        switch (dcmd)
        {
            case CMD_MESSAGEQCOPY_RUNTEST:
            {
                status = MessageQCopyDrv_runtest ( ctp, msg, ocb);
            }
            break;

            default:
            {
                GT_1trace (curTrace, GT_3CLASS,
                           "Invalid DEVCTL for MessageQCopy 0x%x",
                           msg->i.dcmd);
                status = _RESMGR_ERRNO (ENOSYS);
            }
            break;
        }
    }

    return status;
}


/**
 *  @brief        Handler for MessageQCopy create API.
 *
 *  @param ctp    Thread's associated context information.
 *  @param msg    The actual devctl() message.
 *  @param ocb    OCB associated with client's session.
 *
 *  @return       _RESMGR_PTR() value.
 *
 *  @retval       _RESMGR_PTR() value    Success.
 */
void mqcopy_server_test_cb(MessageQCopy_Handle handle, void * data, int len, void * priv, UInt32 src, UInt16 srcProc)
{
    char message[MessageQCopy_BUFSIZE];

    memcpy(message, data, len);
    message[len] = '\0';
    Osal_printf ("mqcopy_server_test_cb %d for handle %d from %d [%s]",
                 mqcopy_test_num_msgs++, handle, src, message);

    if (mqcopy_test_num_msgs < MQCOPY_TEST_NUM_MSG) {
        MessageQCopy_send (srcProc,
                           local_procid,
                           src,
                           local_endpoint,
                           MQCOPY_TSET_MSG,
                           String_len(MQCOPY_TSET_MSG),
                           TRUE);
    }
    else {
        OsalSemaphore_post(mqcopy_test_sem);
    }
}

void mqcopy_server_test_notify_cb (MessageQCopy_Handle handle, UInt16 procId, UInt32 endpoint)
{
    Int i = 0;
    Bool found = FALSE;

    for (i = 0; i < 10; i++) {
        if (mqcopy_test_handles[i].handle == NULL) {
            found = TRUE;
            break;
        }
    }

    if (found) {
        mqcopy_test_handles[i].handle = handle;
        mqcopy_test_handles[i].procId = procId;
        mqcopy_test_handles[i].endpoint = endpoint;

        MessageQCopy_send (procId,
                           local_procid,
                           50,
                           local_endpoint,
                           MQCOPY_TSET_MSG,
                           String_len(MQCOPY_TSET_MSG),
                           TRUE);
    }
}

static int run_mqcopy_server_test(void)
{
    int status = 0, i = 0;
    MessageQCopy_Handle handle = NULL;

    // TODO: protect from concurrent runs

    mqcopy_test_num_msgs = 0;

    for (i = 0; i < 10; i++) {
        mqcopy_test_handles[i].handle = NULL;
    }

    mqcopy_test_sem = OsalSemaphore_create(OsalSemaphore_Type_Binary);

    local_procid = MultiProc_self();
    handle = MessageQCopy_create(MessageQCopy_ADDRANY, "rpmsg-server-sample", mqcopy_server_test_cb, NULL, &local_endpoint);
    //status = MessageQCopy_registerNotify(handle, mqcopy_server_test_notify_cb);
    for (i = 0; i < MultiProc_getNumProcessors(); i++) {
        if (i != local_procid) {
            MessageQCopy_send (i,
                               local_procid,
                               50,
                               local_endpoint,
                               MQCOPY_TSET_MSG,
                               String_len(MQCOPY_TSET_MSG),
                               TRUE);
        }
    }

    /* wait for messaging to complete */
    OsalSemaphore_pend(mqcopy_test_sem, OSALSEMAPHORE_WAIT_FOREVER);

    //status = MessageQCopy_unregisterNotify(handle, mqcopy_server_test_notify_cb);
    status = MessageQCopy_delete(&handle);

    OsalSemaphore_delete(&mqcopy_test_sem);

    return status;
}

void mqcopy_client_test_cb(MessageQCopy_Handle handle, void * data, int len, void * priv, UInt32 src, UInt16 srcProc)
{
    int i = 0;
    char message[MessageQCopy_BUFSIZE];

    memcpy(message, data, len);
    message[len] = '\0';
    Osal_printf ("mqcopy_client_test_cb %d for handle %d from %d [%s]",
                 mqcopy_test_num_msgs++, handle, src, message);

    for (i = 0; i < 10; i++) {
        if (mqcopy_test_handles[i].endpoint == src &&
            mqcopy_test_handles[i].procId == srcProc)
            break;
    }
    if (i != 10) {
        if (mqcopy_test_num_msgs < MQCOPY_TEST_NUM_MSG) {
            MessageQCopy_send(mqcopy_test_handles[i].procId,
                              local_procid,
                              mqcopy_test_handles[i].endpoint,
                              local_endpoint,
                              MQCOPY_TSET_MSG,
                              String_len(MQCOPY_TSET_MSG),
                              TRUE);
        }
        else {
            OsalSemaphore_post(mqcopy_test_sem);
        }
    }
    else {
        Osal_printf("mqcopy_server_test_cb unknown handle received.");
    }
}

void mqcopy_client_test_notify_cb (MessageQCopy_Handle handle, UInt16 procId,
                                   UInt32 endpoint, Char * desc, Bool create)
{
    Int i = 0;
    Bool found = FALSE;

    for (i = 0; i < 10; i++) {
        if (mqcopy_test_handles[i].handle == NULL) {
            found = TRUE;
            break;
        }
    }

    if (found) {
        mqcopy_test_handles[i].handle = handle;
        mqcopy_test_handles[i].procId = procId;
        mqcopy_test_handles[i].endpoint = endpoint;

        MessageQCopy_send (procId,
                           local_procid,
                           endpoint,
                           local_endpoint,
                           MQCOPY_TSET_MSG,
                           String_len(MQCOPY_TSET_MSG),
                           TRUE);
    }
}

int run_mqcopy_client_test(void)
{
    int status = 0, i = 0;
    MessageQCopy_Handle handle = NULL;

    // TODO: protect from concurrent runs

    mqcopy_test_num_msgs = 0;

    for (i = 0; i < 10; i++) {
        mqcopy_test_handles[i].handle = NULL;
    }

    mqcopy_test_sem = OsalSemaphore_create(OsalSemaphore_Type_Binary);

    local_procid = MultiProc_self();
    handle = MessageQCopy_create(MessageQCopy_ADDRANY, "rpmsg-client-sample", mqcopy_client_test_cb, NULL, &local_endpoint);
    status = MessageQCopy_registerNotify(handle, mqcopy_client_test_notify_cb);

    /* wait for messaging to complete */
    OsalSemaphore_pend(mqcopy_test_sem, OSALSEMAPHORE_WAIT_FOREVER);

    //status = MessageQCopy_unregisterNotify(handle, mqcopy_server_test_notify_cb);
    status = MessageQCopy_delete(&handle);

    OsalSemaphore_delete(&mqcopy_test_sem);

    return status;
}

void mqcopy_error_test_cb(MessageQCopy_Handle handle, void * data, int len, void * priv, UInt32 src, UInt16 srcProc)
{
    Osal_printf ("mqcopy_error_test_cb for handle %d from procId %d src %d",
                 handle, srcProc, src);
}

void mqcopy_error_test_notify_cb (MessageQCopy_Handle handle, UInt16 procId,
                                  UInt32 endpoint, Char * desc, Bool create)
{
    Osal_printf ("mqcopy_error_test_notify_cb for handle %d from procId %d endpoint %d",
                 handle, procId, endpoint);
}

int run_mqcopy_error_test()
{
    int status = EOK;
    UInt32 ept;
    MessageQCopy_Handle handle = NULL;
    int i;
    char test_name[RPMSG_NAME_SIZE];
    int tests_passed = 0;
    int tests_failed = 0;
    int tests_run = 0;

    Osal_printf ("Running MessageQCopy Error Tests");
    Osal_printf ("================================");

    status = MessageQCopy_setup(NULL);

    /* MessageQCopy_create test, INVALID reserved value (out of range) */
    Osal_printf ("Q_IPC_API_0000_0001");
    tests_run++;
    handle = MessageQCopy_create(MessageQCopy_MAXMQS, "Test", mqcopy_error_test_cb, NULL, &ept);
    if (handle != NULL) {
        tests_failed++;
        Osal_printf("TEST %d: FAILED", tests_run);
    }
    else {
        tests_passed++;
        Osal_printf("TEST %d: PASSED", tests_run);
    }

    /* MessageQCopy_create test, INVALID reserved value (already in use) */
    Osal_printf ("Q_IPC_API_0000_0002");
    tests_run++;
    handle = MessageQCopy_create(53, "Test", mqcopy_error_test_cb, NULL, &ept);
    if (handle != NULL) {
        tests_failed++;
        Osal_printf("TEST %d: FAILED", tests_run);
    }
    else {
        tests_passed++;
        Osal_printf("TEST %d: PASSED", tests_run);
    }

    /* MessageQCopy_create test, INVALID name value (no null terminator) */
    Osal_printf ("Q_IPC_API_0000_0003");
    tests_run++;
    for (i = 0; i < RPMSG_NAME_SIZE; i++) {
        test_name[i] = 'a';
    }
    handle = MessageQCopy_create(MessageQCopy_ADDRANY, test_name, mqcopy_error_test_cb, NULL, &ept);
    if (handle != NULL) {
        tests_failed++;
        Osal_printf("TEST %d: FAILED", tests_run);
    }
    else {
        tests_passed++;
        Osal_printf("TEST %d: PASSED", tests_run);
    }

    /* MessageQCopy_create test, INVALID cb value */
    Osal_printf ("Q_IPC_API_0000_0004");
    tests_run++;
    handle = MessageQCopy_create(MessageQCopy_ADDRANY, "test", NULL, NULL, &ept);
    if (handle != NULL) {
        tests_failed++;
        Osal_printf("TEST %d: FAILED", tests_run);
    }
    else {
        tests_passed++;
        Osal_printf("TEST %d: PASSED", tests_run);
    }

    /* MessageQCopy_create test, INVALID endpoint value */
    Osal_printf ("Q_IPC_API_0000_0005");
    tests_run++;
    handle = MessageQCopy_create(MessageQCopy_ADDRANY, "test", mqcopy_error_test_cb, NULL, NULL);
    if (handle != NULL) {
        tests_failed++;
        Osal_printf("TEST %d: FAILED", tests_run);
    }
    else {
        tests_passed++;
        Osal_printf("TEST %d: PASSED", tests_run);
    }

    /* MessageQCopy_delete test, INVALID NULL handlePtr */
    Osal_printf ("Q_IPC_API_0001_0001");
    tests_run++;
    status = MessageQCopy_delete(NULL);
    if (status >= 0) {
        tests_failed++;
        Osal_printf("TEST %d: FAILED", tests_run);
    }
    else {
        tests_passed++;
        Osal_printf("TEST %d: PASSED", tests_run);
    }

    /* MessageQCopy_delete test, INVALID NULL handle */
    Osal_printf ("Q_IPC_API_0001_0002");
    tests_run++;
    status = MessageQCopy_delete(&handle);
    if (status >= 0) {
        tests_failed++;
        Osal_printf("TEST %d: FAILED", tests_run);
    }
    else {
        tests_passed++;
        Osal_printf("TEST %d: PASSED", tests_run);
    }

    /* MessageQCopy_delete test, INVALID handle */
    Osal_printf ("Q_IPC_API_0001_0003");
    tests_run++;
    handle = (MessageQCopy_Handle)1;
    status = MessageQCopy_delete(&handle);
    if (status >= 0) {
        tests_failed++;
        Osal_printf("TEST %d: FAILED", tests_run);
    }
    else {
        tests_passed++;
        Osal_printf("TEST %d: PASSED", tests_run);
    }
    handle = NULL;

    /* MessageQCopy_registerNotify test, INVALID NULL handle */
    Osal_printf ("Q_IPC_API_0002_0001");
    tests_run++;
    status = MessageQCopy_registerNotify(NULL, mqcopy_error_test_notify_cb);
    if (status >= 0) {
        tests_failed++;
        Osal_printf("TEST %d: FAILED", tests_run);
    }
    else {
        tests_passed++;
        Osal_printf("TEST %d: PASSED", tests_run);
    }

    /* MessageQCopy_registerNotify test, INVALID handle */
    Osal_printf ("Q_IPC_API_0002_0002");
    tests_run++;
    handle = (MessageQCopy_Handle)1;
    status = MessageQCopy_registerNotify(handle, mqcopy_error_test_notify_cb);
    if (status >= 0) {
        tests_failed++;
        Osal_printf("TEST %d: FAILED", tests_run);
    }
    else {
        tests_passed++;
        Osal_printf("TEST %d: PASSED", tests_run);
    }
    handle = NULL;

    /* MessageQCopy_registerNotify test, INVALID handle->name */
    Osal_printf ("Q_IPC_API_0002_0003");
    tests_run++;
    handle = MessageQCopy_create(MessageQCopy_ADDRANY, NULL, mqcopy_error_test_cb, NULL, &ept);
    if (handle != NULL) {
        status = MessageQCopy_registerNotify(handle, mqcopy_error_test_notify_cb);
        if (status >= 0) {
            tests_failed++;
            Osal_printf("TEST %d: FAILED", tests_run);
        }
        else {
            MessageQCopy_delete(&handle);
            tests_passed++;
            Osal_printf("TEST %d: PASSED", tests_run);
        }
    }
    else {
        tests_failed++;
        Osal_printf("TEST %d: FAILED", tests_run);
    }
    handle = NULL;

    /* MessageQCopy_registerNotify test, INVALID NULL cb */
    Osal_printf ("Q_IPC_API_0002_0004");
    tests_run++;
    handle = MessageQCopy_create(MessageQCopy_ADDRANY, "test", mqcopy_error_test_cb, NULL, &ept);
    if (handle != NULL) {
        status = MessageQCopy_registerNotify(handle, NULL);
        if (status >= 0) {
            tests_failed++;
            Osal_printf("TEST %d: FAILED", tests_run);
        }
        else {
            tests_passed++;
            Osal_printf("TEST %d: PASSED", tests_run);
        }
    }
    else {
        tests_failed++;
        Osal_printf("TEST %d: FAILED", tests_run);
    }

    /* MessageQCopy_send test, INVALID dstProc (out of range) */
    Osal_printf ("Q_IPC_API_0003_0001");
    tests_run++;
    status = MessageQCopy_send (MultiProc_MAXPROCESSORS, /* dstProc */
                                MultiProc_self(), /* srcProc */
                                50, /* dstEndpt */
                                ept, /* srcEndpt */
                                MQCOPY_TSET_MSG, /* data */
                                String_len(MQCOPY_TSET_MSG), /* len */
                                TRUE); /* wait */
    if (status >= 0) {
        tests_failed++;
        Osal_printf("TEST %d: FAILED", tests_run);
    }
    else {
        tests_passed++;
        Osal_printf("TEST %d: PASSED", tests_run);
    }

    /* MessageQCopy_send test, INVALID dstProc (not initialized) */
    Osal_printf ("Q_IPC_API_0003_0002");
    tests_run++;
    status = MessageQCopy_send (MultiProc_getNumProcessors(), /* dstProc */
                                MultiProc_self(), /* srcProc */
                                50, /* dstEndpt */
                                ept, /* srcEndpt */
                                MQCOPY_TSET_MSG, /* data */
                                String_len(MQCOPY_TSET_MSG), /* len */
                                TRUE); /* wait */
    if (status >= 0) {
        tests_failed++;
        Osal_printf("TEST %d: FAILED", tests_run);
    }
    else {
        tests_passed++;
        Osal_printf("TEST %d: PASSED", tests_run);
    }

    /* MessageQCopy_send test, INVALID srcProc */
    Osal_printf ("Q_IPC_API_0003_0003");
    tests_run++;
    status = MessageQCopy_send (MultiProc_self() + 1, /* dstProc */
                                MultiProc_getNumProcessors(), /* srcProc */
                                50, /* dstEndpt */
                                ept, /* srcEndpt */
                                MQCOPY_TSET_MSG, /* data */
                                String_len(MQCOPY_TSET_MSG), /* len */
                                TRUE); /* wait */
    if (status >= 0) {
        tests_failed++;
        Osal_printf("TEST %d: FAILED", tests_run);
    }
    else {
        tests_passed++;
        Osal_printf("TEST %d: PASSED", tests_run);
    }

    /* MessageQCopy_send test, INVALID dstEndpt */
    Osal_printf ("Q_IPC_API_0003_0004");
    tests_run++;
    status = MessageQCopy_send (MultiProc_self() + 1, /* dstProc */
                                MultiProc_self(), /* srcProc */
                                MessageQCopy_ADDRANY, /* dstEndpt */
                                ept, /* srcEndpt */
                                MQCOPY_TSET_MSG, /* data */
                                String_len(MQCOPY_TSET_MSG), /* len */
                                TRUE); /* wait */
    if (status >= 0) {
        tests_failed++;
        Osal_printf("TEST %d: FAILED", tests_run);
    }
    else {
        tests_passed++;
        Osal_printf("TEST %d: PASSED", tests_run);
    }

    /* MessageQCopy_send test, INVALID srcEndpt */
    Osal_printf ("Q_IPC_API_0003_0005");
    tests_run++;
    status = MessageQCopy_send (MultiProc_self() + 1, /* dstProc */
                                MultiProc_self(), /* srcProc */
                                50, /* dstEndpt */
                                MessageQCopy_ADDRANY, /* srcEndpt */
                                MQCOPY_TSET_MSG, /* data */
                                String_len(MQCOPY_TSET_MSG), /* len */
                                TRUE); /* wait */
    if (status >= 0) {
        tests_failed++;
        Osal_printf("TEST %d: FAILED", tests_run);
    }
    else {
        tests_passed++;
        Osal_printf("TEST %d: PASSED", tests_run);
    }

    /* MessageQCopy_send test, INVALID data pointer */
    Osal_printf ("Q_IPC_API_0003_0006");
    tests_run++;
    status = MessageQCopy_send (MultiProc_self() + 1, /* dstProc */
                                MultiProc_self(), /* srcProc */
                                50, /* dstEndpt */
                                MessageQCopy_ADDRANY, /* srcEndpt */
                                NULL, /* data */
                                String_len(MQCOPY_TSET_MSG), /* len */
                                TRUE); /* wait */
    if (status >= 0) {
        tests_failed++;
        Osal_printf("TEST %d: FAILED", tests_run);
    }
    else {
        tests_passed++;
        Osal_printf("TEST %d: PASSED", tests_run);
    }

    /* MessageQCopy_send test, INVALID len */
    Osal_printf ("Q_IPC_API_0003_0007");
    tests_run++;
    status = MessageQCopy_send (MultiProc_self() + 1, /* dstProc */
                                MultiProc_self(), /* srcProc */
                                50, /* dstEndpt */
                                MessageQCopy_ADDRANY, /* srcEndpt */
                                MQCOPY_TSET_MSG, /* data */
                                MessageQCopy_BUFSIZE, /* len */
                                TRUE); /* wait */
    if (status >= 0) {
        tests_failed++;
        Osal_printf("TEST %d: FAILED", tests_run);
    }
    else {
        tests_passed++;
        Osal_printf("TEST %d: PASSED", tests_run);
    }

    status = MessageQCopy_delete(&handle);

    status = MessageQCopy_destroy();

    Osal_printf ("================================");
    Osal_printf ("TESTS RUN: %d PASSED: %d FAILED: %d", tests_run, tests_passed, tests_failed);


    if (tests_failed > 0) {
        status = -1;
    }
    else {
        status = 0;
    }

    return status;
}

int MessageQCopyDrv_runtest (resmgr_context_t * ctp, io_devctl_t * msg,
                             ipc_ocb_t * ocb)
{
    MessageQCopyDrv_CmdArgs *       cargs       =
                             (MessageQCopyDrv_CmdArgs *)(_DEVCTL_DATA (msg->i));
    MessageQCopyDrv_CmdArgs *       out         =
                             (MessageQCopyDrv_CmdArgs *)(_DEVCTL_DATA (msg->o));
    Int                             status      = 0;

    switch (cargs->args.runtest.testNo) {
        case 1:
            status = run_mqcopy_server_test();
            break;
        case 2:
            status = run_mqcopy_client_test();
            break;
        case 3:
            status = run_mqcopy_error_test();
            break;
        default:
            status = -1;
            break;
    }
    out->apiStatus = status;

    return (_RESMGR_PTR (ctp, &msg->o,
                         sizeof (msg->o) + sizeof(MessageQCopyDrv_CmdArgs)));
}

