/*
 * Copyright (c) 2013, Texas Instruments Incorporated
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
/*
 * tests_ipc_sample.c
 *
 */

#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
//#include <sys/eventfd.h>

#include "ti/ipc/ti_ipc.h"

#define SUCCESS             0
#define ERROR               -1

int num_iterations = 1;

#define PING_TEST_MSG "hello world!"
#define PING_TEST_NUM_MSG 500

int run_ping_test(int fd, int i)
{
    char              buf[512] = {0};
    int               ret;

    /* send ping message */
    ret = write(fd, PING_TEST_MSG, sizeof(PING_TEST_MSG));
    if (ret < 0) {
        perror("Can't write to remote endpoint");
        return ERROR;
    }
    printf("ping [%d] %s\n", i, PING_TEST_MSG);

    ret = read(fd, buf, sizeof(buf));
    if (ret < 0) {
        perror("Can't read from remote endpoint");
        return ERROR;
    }

    printf("pong [%d] %s\n", i, buf);

    return SUCCESS;
}


int main(int argc, char *argv[])
{
    int fd;
    int ret;
    int i;
    int core_id;
    tiipc_remote_params remote;
    tiipc_local_params local;

    if (argc > 3)  {
        printf("Usage: ti-ipc-test <core_id> [<num_iterations>]\n");
        return ERROR;
    }
    else if (argc == 3) {
        core_id = atoi(argv[1]);
        num_iterations = atoi(argv[2]);
    }
    else if (argc == 2) {
        core_id = atoi(argv[1]);
        num_iterations = 1;
    }

    /* Connect to the ti-ipc */
    fd = open("/dev/tiipc", O_RDWR);
    if (fd < 0) {
        perror("Can't open tiipc device");
        return ERROR;
    }

    /* Connect to a remote endpoint on a particular core */
    remote.remote_proc = core_id;
    remote.remote_addr = 50;
    ret = ioctl(fd, TIIPC_IOCSETREMOTE, &remote);
    if (ret < 0) {
        perror("Can't connect to remote endpoint 50");
        return ERROR;
    }
    printf("ti-ipc-test: Connected to endpoint %d on core %d\n",
           remote.remote_addr, remote.remote_proc);

    /* Test retrieving the remote information */
    remote.remote_proc = 0;
    remote.remote_addr = 0;
    ret = ioctl(fd, TIIPC_IOCGETREMOTE, &remote);
    if (ret < 0) {
        perror("Can't get the remote endpoint info");
        return ERROR;
    }
    printf("ti-ipc-test: Got remote endpoint %d on core %d\n",
           remote.remote_addr, remote.remote_proc);

    /* Create any local endpoint for receiving messages */
    local.local_addr = TIIPC_ADDRANY;
    ret = ioctl(fd, TIIPC_IOCSETLOCAL, &local);
    if (ret < 0) {
        perror("Can't set local endpoint");
        return ERROR;
    }
    printf("ti-ipc-test: Created local endpoint %d\n",
           local.local_addr);

    /* Test retrieving local endpoint for receiving messages */
    local.local_addr = TIIPC_ADDRANY;
    ret = ioctl(fd, TIIPC_IOCGETLOCAL, &local);
    if (ret < 0) {
        perror("Can't get local endpoint info");
        return ERROR;
    }
    printf("ti-ipc-test: Got local endpoint %d\n",
           local.local_addr);

    for (i = 1; i <= num_iterations; i++) {
        ret = run_ping_test(fd, i);
        if (SUCCESS != ret) {
            printf("ping test failed\n");
            return ERROR;
        }
    }

    /* Terminate connection and destroy instance */
    ret = close(fd);
    if (ret < 0) {
        perror("Can't close fd ??");
        return ERROR;
    }

    printf("ti-ipc-test: Closed connection to remote endpoint %d!\n",
           remote.remote_addr);

    return SUCCESS;
}
