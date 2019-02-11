/*
 * Copyright (c) 2013-2015, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/* =============================================================================
 *  @file   NameServerApp.c
 *
 *  @brief  Sample application for NameServer module between MPU and Remote Proc
 *
 *  ============================================================================
 */

/* this define must precede inclusion of any xdc header file */
#define Registry_CURDESC Test__Desc
#define MODULE_NAME "Server"

/* Standard headers */
#include <stdio.h>

/* Ipc Standard header */
#include <xdc/std.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Registry.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>

#include <ti/ipc/Ipc.h>
//#include <_NameServer.h>

/* Module level headers */
#include <ti/ipc/NameServer.h>


/** ============================================================================
 *  Macros and types
 *  ============================================================================
 */
#define NSNAME "MyNS"
#define NSNAME2 "MyNS2"
#define NSLONGNAME "LongNameabcdefghijklmnopqrstuvwxyz1234567890abcdefghi" \
    "jklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890"

/* private data */
Registry_Desc               Registry_CURDESC;

Void smain (UArg arg0, UArg arg1);

/** ============================================================================
 *  Globals
 *  ============================================================================
 */
Int nameLenTest()
{
    NameServer_Params params;
    NameServer_Handle nsHandle;
    Int32 status = 0;
    UInt32 val;

    Log_print0(Diags_INFO, "Testing long names...\n");
#if 0 /* Commented out due to assertion thrown when name length > maxNameLen */
    NameServer_Params_init(&params);

    params.maxValueLen = sizeof(UInt32);
    params.maxNameLen = 32;

    nsHandle = NameServer_create(NSLONGNAME, &params);
    if (nsHandle == NULL) {
        Log_print1(Diags_INFO, "Failed to create NameServer '%s'\n",
            (IArg)NSLONGNAME);
        return -1;
    }
    else {
        printf("Created NameServer '%s'\n", NSLONGNAME);
    }

    /* This name should be too long for creation params and results in error */
    printf("Trying to add a name that exceeds maxNameLen...\n");
    ptr = NameServer_addUInt32(nsHandle, NSLONGNAME, 0xdeadbeef);
    if (ptr == NULL) {
        Log_print0(Diags_INFO,
            "    ...got expected Failure from NameServer_addUInt32()\n");
    }
    else {
        Log_print1(Diags_INFO,
            "    Error: NameServer_addUInt32() returned non-NULL %p (but "
            "was expected to fail)\n", (IArg)ptr);
        NameServer_delete(&nsHandle);
        return -1;
    }

    Log_print0(Diags_INFO, "Deleting nsHandle...\n");
    NameServer_delete(&nsHandle);
#endif
    NameServer_Params_init(&params);

    params.maxValueLen = sizeof(UInt32);
    params.maxNameLen = 180;

    nsHandle = NameServer_create(NSNAME, &params);
    if (nsHandle == NULL) {
        Log_print1(Diags_INFO, "Failed to create NameServer '%s'\n",
            (IArg)NSNAME);
        return -1;
    }
    else {
        Log_print1(Diags_INFO, "Created NameServer '%s'\n", (IArg)NSNAME);
    }

    /* This name is too long for remote to handle and results in error */
    Log_print0(Diags_INFO,
        "Trying to get a name that the remote cannot handle...\n");
    val = 0x00c0ffee;
    status = NameServer_getUInt32(nsHandle, NSLONGNAME, &val, NULL);
    if (status == NameServer_E_NAMETOOLONG) {
        Log_print0(Diags_INFO,
            "    ...got expected Failure from NameServer_getUInt32()\n");
    }
    else {
        Log_print1(Diags_INFO,
            "    Error: NameServer_getUint32() returned unexpected "
            "result: %d\n", (IArg)status);
        return -1;
    }

    Log_print0(Diags_INFO, "Deleting nsHandle...\n");
    NameServer_delete(&nsHandle);

    NameServer_Params_init(&params);

    params.maxValueLen = sizeof(UInt32);
    params.maxNameLen = 32;

    nsHandle = NameServer_create(NSLONGNAME, &params);
    if (nsHandle == NULL) {
        Log_print1(Diags_INFO, "Failed to create NameServer '%s'\n",
            (IArg)NSLONGNAME);
        return -1;
    }
    else {
        Log_print1(Diags_INFO, "Created NameServer '%s'\n", (IArg)NSLONGNAME);
    }

    /* The instance name is too long for remote and results in error */
    Log_print0(Diags_INFO,
        "Trying to use an instance name that the remote cannot handle...\n");
    val = 0x00c0ffee;
    status = NameServer_getUInt32(nsHandle, "Key", &val, NULL);
    if (status == NameServer_E_NAMETOOLONG) {
        Log_print0(Diags_INFO,
            "    ...got expected Failure from NameServer_getUInt32()\n");
    }
    else {
        Log_print1(Diags_INFO,
            "    Error: NameServer_getUint32() returned unexpected "
            "result: %d\n", (IArg)status);
        return -1;
    }

    Log_print0(Diags_INFO, "Deleting nsHandle...\n");
    NameServer_delete(&nsHandle);

    return 0;
}

Int testNS(NameServer_Handle nsHandle, String name)
{
    Int32 status = 0;
    Ptr ptr;
    UInt32 val;
    char key[16];
    Int i;

    ptr = NameServer_addUInt32(nsHandle, name, 0xdeadbeef);
    if (ptr == NULL) {
        Log_print0(Diags_INFO, "Failed to NameServer_addUInt32()\n");
        return -1;
    }
    else {
        Log_print1(Diags_INFO, "NameServer_addUInt32() returned %p\n", (IArg)ptr);
    }

    Log_print0(Diags_INFO, "Trying to add same key (should fail)...\n");
    ptr = NameServer_addUInt32(nsHandle, name, 0xdeadc0de);
    if (ptr == NULL) {
        Log_print0(Diags_INFO, " ...got expected Failure from NameServer_addUInt32()\n");
    }
    else {
        Log_print1(Diags_INFO, "    Error: NameServer_addUInt32() returned non-NULL %p (but was expected to fail)\n", (IArg)ptr);
        return -1;
    }

    val = 0x00c0ffee;
    status = NameServer_getUInt32(nsHandle, name, &val, NULL);
    Log_print2(Diags_INFO, "NameServer_getUInt32() returned %d, val=0x%x (was 0x00c0ffee)\n", status, val);

    Log_print0(Diags_INFO, "Removing 0xdeadbeef w/ NameServer_remove()...\n");
    status = NameServer_remove(nsHandle, name);
    if (status < 0) {
        Log_print1(Diags_INFO, "NameServer_remove() failed: %d\n", status);
        return -1;
    }

    ptr = NameServer_addUInt32(nsHandle, name, 0xdeadc0de);
    if (ptr == NULL) {
        Log_print0(Diags_INFO, "Error: NameServer_addUInt32() failed\n");
        return -1;
    }
    else {
        Log_print0(Diags_INFO, "NameServer_addUInt32(0xdeadc0de) succeeded\n");
    }

    val = 0x00c0ffee;
    status = NameServer_getUInt32(nsHandle, name, &val, NULL);
    Log_print2(Diags_INFO, "NameServer_getUInt32() returned %d, val=0x%x (was 0x00c0ffee)\n", status, val);

    Log_print0(Diags_INFO, "Removing 0xdeadc0de w/ NameServer_removeEntry()...\n");
    status = NameServer_removeEntry(nsHandle, ptr);
    if (status < 0) {
        Log_print1(Diags_INFO, "NameServer_remove() failed: %d\n", status);
        return -1;
    }

    ptr = NameServer_addUInt32(nsHandle, name, 0x0badc0de);
    if (ptr == NULL) {
        Log_print0(Diags_INFO, "Error: NameServer_addUInt32() failed\n");
        return -1;
    }
    else {
        Log_print0(Diags_INFO, "NameServer_addUInt32(0x0badc0de) succeeded\n");
    }

    val = 0x00c0ffee;
    status = NameServer_getUInt32(nsHandle, name, &val, NULL);
    Log_print2(Diags_INFO, "NameServer_getUInt32() returned %d, val=0x%x (was 0x00c0ffee)\n", status, val);

    status = NameServer_remove(nsHandle, name);
    if (status < 0) {
        Log_print0(Diags_INFO, "Error: NameServer_remove() failed\n");
        return -1;
    }
    else {
        Log_print1(Diags_INFO, "NameServer_remove(%s) succeeded\n", (IArg)name);
    }

    for (i = 0; i < 10; i++) {
        sprintf(key, "foobar%d", i);

        ptr = NameServer_addUInt32(nsHandle, key, 0x0badc0de + i);
        if (ptr == NULL) {
            Log_print0(Diags_INFO, "Error: NameServer_addUInt32() failed\n");
            return -1;
        }
        else {
            Log_print2(Diags_INFO, "NameServer_addUInt32(%s, 0x%x) succeeded\n", (IArg)key, 0x0badc0de + i);
        }

        val = 0x00c0ffee;
        status = NameServer_getUInt32(nsHandle, key, &val, NULL);
        Log_print3(Diags_INFO, "NameServer_getUInt32(%s) returned %d, val=0x%x (was 0x00c0ffee)\n", (IArg)key, status, val);

        if (val != (0x0badc0de + i)) {
            Log_print2(Diags_INFO, "get val (0x%x) != add val (0x%x)!\n", val, 0x0badc0de + i);
        }
    }

    for (i = 0; i < 10; i++) {
        sprintf(key, "foobar%d", i);

        status = NameServer_remove(nsHandle, key);
        if (status < 0) {
            Log_print0(Diags_INFO, "Error: NameServer_remove() failed\n");
            return -1;
        }
        else {
            Log_print1(Diags_INFO, "NameServer_remove(%s) succeeded\n", (IArg)key);
        }
    }

    return 0;
}

/** ============================================================================
 *  Functions
 *  ============================================================================
 */
Int
NameServerApp_startup()
{
    Int32 status = 0;
    NameServer_Params params;
    NameServer_Handle nsHandle;
    NameServer_Handle nsHandleAlias;
    NameServer_Handle nsHandle2;
    Int iteration = 0;

    Log_print0(Diags_INFO, "Entered NameServerApp_startup\n");

/*    status = Ipc_start();

    if (status < 0) {
        Log_print1(Diags_INFO, "Ipc_start failed: status = %d\n", status);
        return -1;
    }
*/
//    Log_print0(Diags_INFO, "Calling NameServer_setup()...\n");
//    NameServer_setup();

again:
    NameServer_Params_init(&params);

    params.maxValueLen = sizeof(UInt32);
    params.maxNameLen = 32;

    Log_print1(Diags_INFO, "params.maxValueLen=%d\n", params.maxValueLen);
    Log_print1(Diags_INFO, "params.maxNameLen=%d\n", params.maxNameLen);
    Log_print1(Diags_INFO, "params.checkExisting=%d\n", params.checkExisting);

    nsHandle = NameServer_create(NSNAME, &params);
    if (nsHandle == NULL) {
        Log_print1(Diags_INFO, "Failed to create NameServer '%s'\n", (IArg)NSNAME);
        return -1;
    }
    else {
        Log_print1(Diags_INFO, "Created NameServer '%s'\n", (IArg)NSNAME);
    }

    nsHandleAlias = NameServer_create(NSNAME, &params);
    if (nsHandleAlias == NULL) {
        Log_print1(Diags_INFO, "Failed to get handle to NameServer '%s'\n", (IArg)NSNAME);
        return -1;
    }
    else {
        Log_print1(Diags_INFO, "Got another handle to NameServer '%s'\n", (IArg)NSNAME);
    }

    NameServer_Params_init(&params);

    params.maxValueLen = sizeof(UInt32);
    params.maxNameLen = 32;
    nsHandle2 = NameServer_create(NSNAME2, &params);
    if (nsHandle2 == NULL) {
        Log_print1(Diags_INFO, "Failed to create NameServer '%s'\n", (IArg)NSNAME2);
        return -1;
    }
    else {
        Log_print1(Diags_INFO, "Created NameServer '%s'\n", (IArg)NSNAME2);
    }

    Log_print0(Diags_INFO, "Testing nsHandle\n");
    status = testNS(nsHandle, "Key");
    if (status != 0) {
        Log_print0(Diags_INFO, "test failed on nsHandle\n");
        return status;
    }
    Log_print0(Diags_INFO, "Testing nsHandle2\n");
    status = testNS(nsHandle2, "Key");
    if (status != 0) {
        Log_print0(Diags_INFO, "test failed on nsHandle2\n");
        return status;
    }

    Log_print0(Diags_INFO, "Deleting nsHandle and nsHandle2...\n");
    NameServer_delete(&nsHandle);
    NameServer_delete(&nsHandle2);

    /*
     * Verify that we can still use the alias handle after deleting the
     * initial handle
     */
    Log_print0(Diags_INFO, "Testing nsHandleAlias\n");
    status = testNS(nsHandleAlias, "Key");
    if (status != 0) {
        Log_print0(Diags_INFO, "test failed on nsHandleAlias\n");
        return status;
    }
    Log_print0(Diags_INFO, "Deleting nsHandleAlias...\n");
    NameServer_delete(&nsHandleAlias);

    iteration++;
    if (iteration < 2) {
        goto again;
    }

    status = nameLenTest();
    if (status != 0) {
        Log_print0(Diags_INFO, "Name Length test failed\n");
        return status;
    }

//    Log_print0(Diags_INFO, "Calling NameServer_destroy()...\n");
//    NameServer_destroy();

    Log_print1(Diags_INFO, "Leaving NameServerApp_startup: status = 0x%x\n", status);

    return status;
}


Int
NameServerApp_execute()
{
    Int32 status = 0;

    Log_print0(Diags_INFO, "Entered NameServerApp_execute\n");

    Log_print0(Diags_INFO, "Leaving NameServerApp_execute\n\n");

    return status;
}

Int
NameServerApp_shutdown()
{
    Int32 status = 0;

    Log_print0(Diags_INFO, "Entered NameServerApp_shutdown()\n");

/*    status = Ipc_stop();
    if (status < 0) {
        Log_print1(Diags_INFO, "Ipc_stop failed: status = %d\n", status);
    }
*/
    Log_print0(Diags_INFO, "Leave NameServerApp_shutdown()\n");

    return status;
}

Int main(Int argc, Char* argv[])
{
    Error_Block     eb;
    Task_Params     taskParams;
    Registry_Result result;

    Log_print0(Diags_ENTRY, "--> main:");

    /* must initialize the error block before using it */
    Error_init(&eb);

    /* create main thread (interrupts not enabled in main on BIOS) */
    Task_Params_init(&taskParams);
    taskParams.instance->name = "smain";
    taskParams.stackSize = 0x1000;
    Task_create(smain, &taskParams, &eb);

    if (Error_check(&eb)) {
        System_abort("main: failed to create application startup thread");
    }

    /* register with xdc.runtime to get a diags mask */
    result = Registry_addModule(&Registry_CURDESC, MODULE_NAME);
    Assert_isTrue(result == Registry_SUCCESS, (Assert_Id)NULL);

    /* start scheduler, this never returns */
    BIOS_start();

    /* should never get here */
    Log_print0(Diags_EXIT, "<-- main:");
    return (0);
}

Void smain (UArg arg0, UArg arg1)
{
    int status = 0;

    Log_print0(Diags_ENTRY | Diags_INFO, "--> smain:");

    /* turn on Diags_INFO trace */
    Diags_setMask("Server+F");

    status = NameServerApp_startup();
    if (status < 0) {
        goto leave;
    }

    status = NameServerApp_execute();
    if (status < 0) {
        goto leave;
    }

    status = NameServerApp_shutdown();
    if (status < 0) {
        goto leave;
    }

leave:
    Log_print1(Diags_EXIT, "<-- smain: %d", (IArg)status);
    return;
}
