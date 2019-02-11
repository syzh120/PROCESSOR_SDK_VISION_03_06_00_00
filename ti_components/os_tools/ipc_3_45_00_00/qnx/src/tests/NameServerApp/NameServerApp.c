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

/* Standard headers */
#include <stdio.h>

/* Ipc Standard header */
#include <ti/ipc/Std.h>

#include <ti/ipc/Ipc.h>
#include <_NameServer.h>

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

/** ============================================================================
 *  Globals
 *  ============================================================================
 */
Int nameLenTest()
{
    NameServer_Params params;
    NameServer_Handle nsHandle;
    Int32 status = 0;
    Ptr ptr;
    UInt32 val;

    printf("Testing long names...\n");

    NameServer_Params_init(&params);

    params.maxValueLen = sizeof(UInt32);
    params.maxNameLen = 32;

    nsHandle = NameServer_create(NSLONGNAME, &params);
    if (nsHandle == NULL) {
        printf("Failed to create NameServer '%s'\n", NSLONGNAME);
        return -1;
    }
    else {
        printf("Created NameServer '%s'\n", NSLONGNAME);
    }

    /* This name should be too long for creation params and results in error */
    printf("Trying to add a name that exceeds maxNameLen...\n");
    ptr = NameServer_addUInt32(nsHandle, NSLONGNAME, 0xdeadbeef);
    if (ptr == NULL) {
        printf("    ...got expected Failure from NameServer_addUInt32()\n");
    }
    else {
        printf("    Error: NameServer_addUInt32() returned non-NULL %p (but "
            "was expected to fail)\n", ptr);
        NameServer_delete(&nsHandle);
        return -1;
    }

    printf("Deleting nsHandle...\n");
    NameServer_delete(&nsHandle);

    NameServer_Params_init(&params);

    params.maxValueLen = sizeof(UInt32);
    params.maxNameLen = 180;

    nsHandle = NameServer_create(NSLONGNAME, &params);
    if (nsHandle == NULL) {
        printf("Failed to create NameServer '%s'\n", NSLONGNAME);
        return -1;
    }
    else {
        printf("Created NameServer '%s'\n", NSLONGNAME);
    }

    /* This name is too long for remote to handle and results in error */
    printf("Trying to get a name that the remote cannot handle...\n");
    val = 0x00c0ffee;
    status = NameServer_getUInt32(nsHandle, NSLONGNAME, &val, NULL);
    if (status == NameServer_E_NAMETOOLONG) {
        printf("    ...got expected Failure from NameServer_getUInt32()\n");
    }
    else {
        printf("    Error: NameServer_getUint32() returned unexpected "
            "result: %d\n", status);
        return -1;
    }

    printf("Deleting nsHandle...\n");
    NameServer_delete(&nsHandle);

    NameServer_Params_init(&params);

    params.maxValueLen = sizeof(UInt32);
    params.maxNameLen = 32;

    nsHandle = NameServer_create(NSLONGNAME, &params);
    if (nsHandle == NULL) {
        printf("Failed to create NameServer '%s'\n", NSLONGNAME);
        return -1;
    }
    else {
        printf("Created NameServer '%s'\n", NSLONGNAME);
    }

    /* The instance name is too long for remote and results in error */
    printf("Trying to use an instance name that the remote cannot "
        "handle...\n");
    val = 0x00c0ffee;
    status = NameServer_getUInt32(nsHandle, "Key", &val, NULL);
    if (status == NameServer_E_NAMETOOLONG) {
        printf("    ...got expected Failure from NameServer_getUInt32()\n");
    }
    else {
        printf("    Error: NameServer_getUint32() returned unexpected "
            "result: %d\n", status);
        return -1;
    }

    printf("Deleting nsHandle...\n");
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
        printf("Failed to NameServer_addUInt32()\n");
        return -1;
    }
    else {
        printf("NameServer_addUInt32() returned %p\n", ptr);
    }

    printf("Trying to add same key (should fail)...\n");
    ptr = NameServer_addUInt32(nsHandle, name, 0xdeadc0de);
    if (ptr == NULL) {
        printf("    ...got expected Failure from NameServer_addUInt32()\n");
    }
    else {
        printf("    Error: NameServer_addUInt32() returned non-NULL %p (but was expected to fail)\n", ptr);
        return -1;
    }

    val = 0x00c0ffee;
    status = NameServer_getUInt32(nsHandle, name, &val, NULL);
    printf("NameServer_getUInt32() returned %d, val=0x%x (was 0x00c0ffee)\n", status, val);

    printf("Removing 0xdeadbeef w/ NameServer_remove()...\n");
    status = NameServer_remove(nsHandle, name);
    if (status < 0) {
        printf("NameServer_remove() failed: %d\n", status);
        return -1;
    }

    ptr = NameServer_addUInt32(nsHandle, name, 0xdeadc0de);
    if (ptr == NULL) {
        printf("Error: NameServer_addUInt32() failed\n");
        return -1;
    }
    else {
        printf("NameServer_addUInt32(0xdeadc0de) succeeded\n");
    }

    val = 0x00c0ffee;
    status = NameServer_getUInt32(nsHandle, name, &val, NULL);
    printf("NameServer_getUInt32() returned %d, val=0x%x (was 0x00c0ffee)\n", status, val);

    printf("Removing 0xdeadc0de w/ NameServer_removeEntry()...\n");
    status = NameServer_removeEntry(nsHandle, ptr);
    if (status < 0) {
        printf("NameServer_remove() failed: %d\n", status);
        return -1;
    }

    ptr = NameServer_addUInt32(nsHandle, name, 0x0badc0de);
    if (ptr == NULL) {
        printf("Error: NameServer_addUInt32() failed\n");
        return -1;
    }
    else {
        printf("NameServer_addUInt32(0x0badc0de) succeeded\n");
    }

    val = 0x00c0ffee;
    status = NameServer_getUInt32(nsHandle, name, &val, NULL);
    printf("NameServer_getUInt32() returned %d, val=0x%x (was 0x00c0ffee)\n", status, val);

    status = NameServer_remove(nsHandle, name);
    if (status < 0) {
        printf("Error: NameServer_remove() failed\n");
        return -1;
    }
    else {
        printf("NameServer_remove(%s) succeeded\n", name);
    }

    for (i = 0; i < 10; i++) {
        sprintf(key, "foobar%d", i);

        ptr = NameServer_addUInt32(nsHandle, key, 0x0badc0de + i);
        if (ptr == NULL) {
            printf("Error: NameServer_addUInt32() failed\n");
            return -1;
        }
        else {
            printf("NameServer_addUInt32(%s, 0x%x) succeeded\n", key, 0x0badc0de + i);
        }

        val = 0x00c0ffee;
        status = NameServer_getUInt32(nsHandle, key, &val, NULL);
        printf("NameServer_getUInt32(%s) returned %d, val=0x%x (was 0x00c0ffee)\n", key, status, val);

        if (val != (0x0badc0de + i)) {
            printf("get val (0x%x) != add val (0x%x)!\n", val, 0x0badc0de + i);
        }
    }

    for (i = 0; i < 10; i++) {
        sprintf(key, "foobar%d", i);

        status = NameServer_remove(nsHandle, key);
        if (status < 0) {
            printf("Error: NameServer_remove() failed\n");
            return -1;
        }
        else {
            printf("NameServer_remove(%s) succeeded\n", key);
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

    printf ("Entered NameServerApp_startup\n");

    status = Ipc_start();

    if (status < 0) {
        printf("Ipc_start failed: status = %d\n", status);
        return -1;
    }

    printf("Calling NameServer_setup()...\n");
    NameServer_setup();

again:
    NameServer_Params_init(&params);

    params.maxValueLen = sizeof(UInt32);
    params.maxNameLen = 32;

    printf("params.maxValueLen=%d\n", params.maxValueLen);
    printf("params.maxNameLen=%d\n", params.maxNameLen);
    printf("params.checkExisting=%d\n", params.checkExisting);

    nsHandle = NameServer_create(NSNAME, &params);
    if (nsHandle == NULL) {
        printf("Failed to create NameServer '%s'\n", NSNAME);
        return -1;
    }
    else {
        printf("Created NameServer '%s'\n", NSNAME);
    }

    nsHandleAlias = NameServer_create(NSNAME, &params);
    if (nsHandleAlias == NULL) {
        printf("Failed to get handle to NameServer '%s'\n", NSNAME);
        return -1;
    }
    else {
        printf("Got another handle to NameServer '%s'\n", NSNAME);
    }

    NameServer_Params_init(&params);

    params.maxValueLen = sizeof(UInt32);
    params.maxNameLen = 32;
    nsHandle2 = NameServer_create(NSNAME2, &params);
    if (nsHandle2 == NULL) {
        printf("Failed to create NameServer '%s'\n", NSNAME2);
        return -1;
    }
    else {
        printf("Created NameServer '%s'\n", NSNAME2);
    }

    printf("Testing nsHandle\n");
    status = testNS(nsHandle, "Key");
    if (status != 0) {
        printf("test failed on nsHandle\n");
        return status;
    }
    printf("Testing nsHandle2\n");
    status = testNS(nsHandle2, "Key");
    if (status != 0) {
        printf("test failed on nsHandle2\n");
        return status;
    }

    printf("Deleting nsHandle and nsHandle2...\n");
    NameServer_delete(&nsHandle);
    NameServer_delete(&nsHandle2);

    /*
     * Verify that we can still use the alias handle after deleting the
     * initial handle
     */
    printf("Testing nsHandleAlias\n");
    status = testNS(nsHandleAlias, "Key");
    if (status != 0) {
        printf("test failed on nsHandleAlias\n");
        return status;
    }
    printf("Deleting nsHandleAlias...\n");
    NameServer_delete(&nsHandleAlias);

    iteration++;
    if (iteration < 2) {
        goto again;
    }

    status = nameLenTest();
    if (status != 0) {
        printf("Name Length test failed\n");
        return status;
    }

    printf("Calling NameServer_destroy()...\n");
    NameServer_destroy();

    printf ("Leaving NameServerApp_startup: status = 0x%x\n", status);

    return status;
}


Int
NameServerApp_execute()
{
    Int32 status = 0;

    printf ("Entered NameServerApp_execute\n");

    printf ("Leaving NameServerApp_execute\n\n");

    return status;
}

Int
NameServerApp_shutdown()
{
    Int32 status = 0;

    printf ("Entered NameServerApp_shutdown()\n");

    status = Ipc_stop();
    if (status < 0) {
        printf("Ipc_stop failed: status = %d\n", status);
    }

    printf ("Leave NameServerApp_shutdown()\n");

    return status;
}

int
main (int argc, char ** argv)
{
    int status = 0;

    status = NameServerApp_startup();
    if (status < 0) {
        return -1;
    }

    status = NameServerApp_execute();
    if (status < 0) {
        return -1;
    }

    status = NameServerApp_shutdown();
    if (status < 0) {
        return -1;
    }

    return(0);
}
