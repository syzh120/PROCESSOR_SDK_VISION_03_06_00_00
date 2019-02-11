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
/*
 * tests_rpc_stress.c
 *
 * Stress tests for rpmsg-rpc.
 *
 */

#include <sys/select.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <stdbool.h>
#include <semaphore.h>
#include <dlfcn.h>

#include "ti/ipc/rpmsg_rpc.h"
#include "ti/shmemallocator/SharedMemoryAllocatorUsr.h"


typedef struct {
    int a;
    int b;
    int c;
} fxn_add3_args;

typedef struct {
    int num;
    int *array;
} fxn_addx_args;

/* Note: Set bit 31 to indicate static function indicies:
 * This function order will be hardcoded on BIOS side, hence preconfigured:
 */
enum {
    FXN_IDX_FXNTRIPLE = 1,
    FXN_IDX_FXNADD,
    FXN_IDX_FXNADD3,
    FXN_IDX_FXNADDX,
    FXN_IDX_FXNCOMPUTE,
    FXN_IDX_FXNFAULT,
    FXN_IDX_MAX
};

#define NUM_ITERATIONS               20

static int test_status = 0;
static bool runTest = true;
static int testFunc = FXN_IDX_FXNTRIPLE;

int exec_cmd(int fd, char *msg, size_t len, char *reply_msg, int *reply_len)
{
    int ret = 0;

    ret = write(fd, msg, len);
    if (ret < 0) {
        perror("Can't write to rpc_example instance");
        return -1;
    }

    /* Now, await normal function result from rpc_example service:
     * Note: len should be max length of response expected.
     */
    ret = read(fd, reply_msg, len);
    if (ret < 0) {
        perror("Can't read from rpc_example instance");
        return -1;
    }
    else {
        *reply_len = ret;
    }
    return 0;
}

int send_cmd(int fd, char *msg, int len)
{
    int ret = 0;

    ret = write(fd, msg, len);
    if (ret < 0) {
         perror("Can't write to rpc_example instance\n");
         return -1;
    }

    return(0);
}

int recv_cmd(int fd, int len, char *reply_msg, int *reply_len)
{
    int ret = 0;

    /* Now, await normal function result from rpc_example service: */
    // Note: len should be max length of response expected.
    ret = read(fd, reply_msg, len);
    if (ret < 0) {
         perror("Can't read from rpc_example instance\n");
         return -1;
    }
    else {
          *reply_len = ret;
    }
    return(0);
}

typedef struct test_exec_args {
    int fd;
    int start_num;
    int test_num;
    sem_t * sem;
    int thread_num;
    int func_idx;
    int sub_test;
} test_exec_args;

static pthread_t * clientThreads = NULL;
static sem_t * clientSems = NULL;
static char **clientPackets = NULL;
static bool *readMsg = NULL;
static int *fds;

void *sharedmemalloc_lib = NULL;
int (*sharedmem_alloc)(int size, shm_buf *buf);
int (*sharedmem_free)(shm_buf *buf);

int deinit_sharedmem_funcs(void)
{
    int ret = 0;

    if (sharedmemalloc_lib)
        dlclose(sharedmemalloc_lib);
    sharedmemalloc_lib = NULL;

    return ret;
}

int init_sharedmem_funcs()
{
    int ret = 0;

    if (sharedmemalloc_lib == NULL) {
        sharedmemalloc_lib = dlopen("libsharedmemallocator.so",
                                    RTLD_NOW | RTLD_GLOBAL);
        if (sharedmemalloc_lib == NULL) {
            perror("init_sharedmem_funcs: Error opening shared lib");
            ret = -1;
        }
        else {
            sharedmem_alloc = dlsym(sharedmemalloc_lib, "SHM_alloc");
            if (sharedmem_alloc == NULL) {
                perror("init_sharedmem_funcs: Error getting shared lib sym");
                ret = -1;
            }
            else {
                sharedmem_free = dlsym(sharedmemalloc_lib, "SHM_release");
                if (sharedmem_free == NULL) {
                    perror("init_sharedmem_funcs: Error getting shared lib sym");
                    ret = -1;
                }
            }
        }
    }
    if (ret < 0) {
        deinit_sharedmem_funcs();
    }
    return ret;
}

void * test_exec_call(void * arg)
{
    int               i;
    int               packet_len;
    int               reply_len;
    char              packet_buf[512] = {0};
    char              return_buf[512] = {0};
    test_exec_args    *args = (test_exec_args *) arg;
    int               fd = args->fd;
    struct rppc_function *function;
    struct rppc_function_return *returned;
    shm_buf           buf, buf2;
    void              *ptr = NULL, *ptr2 = NULL;

    for (i = args->start_num; i < args->start_num + NUM_ITERATIONS; i++) {
        function = (struct rppc_function *)packet_buf;
        function->fxn_id = args->func_idx;
        switch (function->fxn_id) {
            case FXN_IDX_FXNTRIPLE:
                function->num_params = 1;
                function->params[0].type = RPPC_PARAM_TYPE_ATOMIC;
                function->params[0].size = sizeof(int);
                function->params[0].data = i;
                function->num_translations = 0;
                break;
            case FXN_IDX_FXNADD:
                function->num_params = 2;
                function->params[0].type = RPPC_PARAM_TYPE_ATOMIC;
                function->params[0].size = sizeof(int);
                function->params[0].data = i;
                function->params[1].type = RPPC_PARAM_TYPE_ATOMIC;
                function->params[1].size = sizeof(int);
                function->params[1].data = i+1;
                function->num_translations = 0;
                break;
            case FXN_IDX_FXNADD3:
                if ((*sharedmem_alloc)(sizeof(fxn_add3_args), &buf) < 0) {
                    test_status = -1;
                }
                else {
                    ptr = (fxn_add3_args *)(buf.vir_addr);
                    ((fxn_add3_args *)ptr)->a = i;
                    ((fxn_add3_args *)ptr)->b = i+1;
                    ((fxn_add3_args *)ptr)->c = i+2;
                    function->num_params = 1;
                    function->params[0].type = RPPC_PARAM_TYPE_PTR;
                    function->params[0].size = sizeof(fxn_add3_args);
                    function->params[0].data = (size_t)ptr;
                    function->params[0].base = (size_t)ptr;
                    function->num_translations = 0;
                }
                break;
            case FXN_IDX_FXNADDX:
                if ((*sharedmem_alloc)(sizeof(fxn_addx_args), &buf) < 0) {
                    test_status = -1;
                }
                else if ((*sharedmem_alloc)(sizeof(int) * 3, &buf2) < 0) {
                    test_status = -1;
                }
                else {
                    ptr = (fxn_addx_args *)(buf.vir_addr);
                    ptr2 = (int *)(buf2.vir_addr);
                    ((fxn_addx_args *)ptr)->num = 3;
                    ((fxn_addx_args *)ptr)->array = ptr2;
                    ((int *)ptr2)[0] = i;
                    ((int *)ptr2)[1] = i+1;
                    ((int *)ptr2)[2] = i+2;
                    function->num_params = 1;
                    function->params[0].type = RPPC_PARAM_TYPE_PTR;
                    function->params[0].size = sizeof(fxn_addx_args);
                    function->params[0].data = (size_t)ptr;
                    function->params[0].base = (size_t)ptr;
                    function->num_translations = 1;
                    function->translations[0].index = 0;
                    function->translations[0].offset = (int)&(((fxn_addx_args *)ptr)->array) - (int)ptr;
                    function->translations[0].base = (size_t)(((fxn_addx_args *)ptr)->array);
                }
                break;
            case FXN_IDX_FXNFAULT:
                function->num_params = 1;
                function->params[0].type = RPPC_PARAM_TYPE_ATOMIC;
                function->params[0].size = sizeof(int);
                function->params[0].data = args->sub_test;
                function->num_translations = 0;
                break;
        }

        if (test_status == -1)
            break;

        returned = (struct rppc_function_return *)return_buf;

        /* Exec command: */
        packet_len = sizeof(struct rppc_function) +\
                     (function->num_translations * \
                      sizeof(struct rppc_param_translation));
        if (args->test_num == 1)  {
            if (exec_cmd(fd, (char *)packet_buf, packet_len,
                         (char *)return_buf, &reply_len)) {
                test_status = -1;
                break;
            }
        }
        else if (args->test_num == 2 || args->test_num == 3) {
            if (send_cmd(fd, (char *)packet_buf, packet_len)) {
                test_status = -1;
                break;
            }
            sem_wait(&clientSems[args->thread_num]);
            memcpy(return_buf, clientPackets[args->thread_num], 512);
            readMsg[args->thread_num] = true;
        }
        switch (function->fxn_id) {
            case FXN_IDX_FXNTRIPLE:
                if (i * 3 != returned->status) {
                    printf ("rpc_stress: "
                            "called fxnTriple(%d), result = %d, expected %d\n",
                            function->params[0].data, returned->status, i * 3);
                    test_status = -1;
                }
                else {
                    printf ("rpc_stress: called fxnTriple(%d), result = %d\n",
                            function->params[0].data, returned->status);
                }
                break;
            case FXN_IDX_FXNADD:
                if (i + (i+1) != returned->status) {
                    printf ("rpc_stress: "
                            "called fxnAdd(%d,%d), result = %d, expected %d\n",
                            function->params[0].data, function->params[1].data,
                            returned->status, i + (i+1));
                    test_status = -1;
                }
                else {
                    printf ("rpc_stress: called fxnAdd(%d,%d), result = %d\n",
                            function->params[0].data, function->params[1].data,
                            returned->status);
                }
                break;
            case FXN_IDX_FXNADD3:
                if (i + (i+1) + (i+2) != returned->status) {
                    printf ("rpc_stress: "
                            "called fxnAdd3(%d,%d,%d), result = %d, expected %d\n",
                            ((fxn_add3_args *)ptr)->a,
                            ((fxn_add3_args *)ptr)->b,
                            ((fxn_add3_args *)ptr)->c, returned->status,
                            i + (i+1) + (i+2));
                    test_status = -1;
                }
                else {
                    printf ("rpc_stress: called fxnAdd3(%d,%d,%d), result = %d\n",
                            ((fxn_add3_args *)ptr)->a,
                            ((fxn_add3_args *)ptr)->b,
                            ((fxn_add3_args *)ptr)->c, returned->status);
                }
                (*sharedmem_free)(&buf);
                break;
            case FXN_IDX_FXNADDX:
                if (i + (i+1) + (i+2) != returned->status) {
                    printf ("rpc_stress: "
                            "called fxnAddX(%d,%d,%d), result = %d, expected %d\n",
                            ((int *)ptr2)[0], ((int *)ptr2)[1],
                            ((int *)ptr2)[2], returned->status,
                            i + (i+1) + (i+2));
                    test_status = -1;
                }
                else {
                    /* Check that reverse address translation is working */
                    if (((fxn_addx_args *)ptr)->array != ptr2) {
                        printf("rpc_stress: reverse addr translation failed, "
                               "addr = 0x%x expected 0x%x\n",
                               (int)(((fxn_addx_args *)ptr)->array), (int)ptr2);
                        test_status = -1;
                    }
                    printf ("rpc_stress: called fxnAddX(%d,%d,%d), result = %d\n",
                            ((int *)ptr2)[0], ((int *)ptr2)[1],
                            ((int *)ptr2)[2], returned->status);
                }
                (*sharedmem_free)(&buf);
                (*sharedmem_free)(&buf2);
                break;
        }
        if (test_status == -1) {
            break;
        }
    }

    return NULL;
}

void * test_select_thread (void * arg)
{
    int fd = 0;
    int reply_len;
    char return_buf[512] = {0};
    struct rppc_function_return *rtn_packet =
                               (struct rppc_function_return *)return_buf;
    int n, i;
    fd_set rfd;
    int max_fd = -1;

    while (runTest) {
        FD_ZERO(&rfd);
        for (i = 0; i < (int)arg; i++) {
            FD_SET(fds[i], &rfd);
            max_fd = max(max_fd, fds[i]);
        }
        n = select(1 + max_fd, &rfd, NULL, NULL, NULL);
        switch (n) {
            case -1:
                perror("select");
                return NULL;
            default:
                for (i = 0; i < (int)arg; i++) {
                    if (FD_ISSET(fds[i], &rfd)) {
                        fd = fds[i];
                        break;
                    }
                }
                break;
        }
        if (recv_cmd(fd, 512, (char *)rtn_packet, &reply_len)) {
            test_status = -1;
            printf("test_select_thread: recv_cmd failed!");
            break;
        }

        if (runTest == false)
            break;

        /* Decode reply: */
        while (readMsg[i] == false) {
            sleep(1);
        }
        memcpy(clientPackets[i], rtn_packet, 512);
        readMsg[i] = false;
        sem_post(&clientSems[i]);
    }
    return NULL;
}

void * test_read_thread (void * arg)
{
    int    fd = (int)arg;
    int    reply_len;
    char   return_buf[512] = {0};
    struct rppc_function_return *rtn_packet =
                               (struct rppc_function_return *)return_buf;
    int    packet_id = 0;

    while (runTest) {
        if (recv_cmd(fd, 512, (char *)rtn_packet, &reply_len)) {
            test_status = -1;
            printf("test_read_tread: recv_cmd failed!");
            break;
        }

        if (runTest == false)
            break;

        /* Decode reply: */
        switch (testFunc) {
            case FXN_IDX_FXNTRIPLE:
                packet_id = ((rtn_packet->status / 3) - 1) / NUM_ITERATIONS;
                break;
            case FXN_IDX_FXNADD:
                packet_id = (((rtn_packet->status - 1) / 2) - 1) / NUM_ITERATIONS;
                break;
            case FXN_IDX_FXNADD3:
                packet_id = (((rtn_packet->status - 3) / 3) - 1) / NUM_ITERATIONS;
                break;
            case FXN_IDX_FXNADDX:
                packet_id = (((rtn_packet->status - 3) / 3) - 1) / NUM_ITERATIONS;
                break;
        }
        while (readMsg[packet_id] == false) {
            sleep(1);
        }
        memcpy(clientPackets[packet_id], rtn_packet, 512);
        readMsg[packet_id] = false;
        sem_post(&clientSems[packet_id]);
    }
    return NULL;
}

int test_rpc_stress_select(int core_id, int num_comps, int func_idx)
{
    int ret = 0;
    int i = 0, j = 0;
    struct rppc_create_instance connreq;
    struct rppc_function *function;
    pthread_t select_thread;
    int               packet_len;
    char              packet_buf[512] = {0};
    test_exec_args args[num_comps];
    char serviceMgrName[20];
    char serviceMgrPath[20];

    snprintf (serviceMgrName, _POSIX_PATH_MAX, "rpc_example_%d", core_id);
    snprintf (serviceMgrPath, _POSIX_PATH_MAX, "/dev/%s", serviceMgrName);

    fds = malloc (sizeof(int) * num_comps);
    if (!fds) {
        return -1;
    }
    for (i = 0; i < num_comps; i++) {
        fds[i] = open(serviceMgrPath, O_RDWR);
        if (fds[i] < 0) {
            perror("Can't open rpc_example device");
            break;
        }
        strcpy(connreq.name, serviceMgrName);

        /* Create an rpc_example server instance, and rebind its address to this
        * file descriptor.
        */
        ret = ioctl(fds[i], RPPC_IOC_CREATE, &connreq);
        if (ret < 0) {
            perror("Can't connect to rpc_example instance");
            close(fds[i]);
            break;
        }
        printf("rpc_sample: Connected to %s\n", connreq.name);
    }
    if (i != num_comps) {
        /* cleanup */
        for (j = 0; j < i; j++) {
            ret = close(fds[j]);
            if (ret < 0) {
                perror("Can't close rpc_example fd ??");
            }
        }
        free(fds);
        return -1;
    }

    clientSems = malloc(sizeof(sem_t) * num_comps);
    if (!clientSems) {
        free(clientThreads);
        for (i = 0; i < num_comps; i++) {
            ret = close(fds[i]);
            if (ret < 0) {
                perror("Can't close rpc_example fd ??");
            }
        }
        return -1;
    }

    readMsg = malloc(sizeof(bool) * num_comps);
    if (!readMsg) {
        free(clientSems);
        free(clientThreads);
        for (i = 0; i < num_comps; i++) {
            ret = close(fds[i]);
            if (ret < 0) {
                perror("Can't close rpc_example fd ??");
            }
        }
        return -1;
    }

    clientPackets = malloc(sizeof(char *) * num_comps);
    if (!clientPackets) {
        free(readMsg);
        free(clientSems);
        free(clientThreads);
        for (i = 0; i < num_comps; i++) {
            ret = close(fds[i]);
            if (ret < 0) {
                perror("Can't close rpc_example fd ??");
            }
        }
        return -1;
    }

    for (i = 0; i < num_comps; i++) {
        clientPackets[i] = malloc(512 * sizeof(char));
        if (!clientPackets[i]) {
            for (j = 0; j < i; j++) {
                free(clientPackets[j]);
            }
            free(clientPackets);
            free(readMsg);
            free(clientSems);
            free(clientThreads);
            for (i = 0; i < num_comps; i++) {
                ret = close(fds[i]);
                if (ret < 0) {
                    perror("Can't close rpc_example fd ??");
                }
            }
            return -1;
        }
    }

    ret = pthread_create(&select_thread, NULL, test_select_thread,
                         (void *)num_comps);
    if (ret < 0) {
        perror("Can't create thread");
        ret = -1;
    }

    clientThreads = malloc(sizeof(pthread_t) * num_comps);
    if (!clientThreads) {
        for (i = 0; i < num_comps; i++) {
            ret = close(fds[i]);
            if (ret < 0) {
                perror("Can't close rpc_example fd ??");
            }
        }
        free(fds);
        return -1;
    }

    for ( i = 0; i < num_comps; i++) {
        ret = sem_init(&clientSems[i], 0, 0);
        args[i].fd = fds[i];
        args[i].start_num = 1;
        args[i].test_num = 3;
        args[i].sem = &clientSems[i];
        args[i].thread_num = i;
        args[i].func_idx = func_idx;
        readMsg[i] = true;
        ret = pthread_create(&clientThreads[i], NULL, test_exec_call,
                             (void *)&args[i]);
        if (ret < 0) {
            perror("Can't create thread");
            ret = -1;
            break;
        }
        printf("Created thread %d\n", i);
    }

    for (j = 0; j < i; j++) {
        printf("Join thread %d\n", j);
        pthread_join(clientThreads[j], NULL);
    }

    free(clientThreads);

    function = (struct rppc_function *)packet_buf;
    function->fxn_id = FXN_IDX_FXNTRIPLE;
    function->num_params = 1;
    function->params[0].type = RPPC_PARAM_TYPE_ATOMIC;
    function->params[0].size = sizeof(int);
    function->params[0].data = i;
    function->num_translations = 0;

    /* Exec command: */
    packet_len = sizeof(struct rppc_function) +\
                 (function->num_translations *\
                  sizeof(struct rppc_param_translation));

    runTest = false;
    if (send_cmd(fds[0], (char *)packet_buf, packet_len)) {
        test_status = -1;
    }

    pthread_join(select_thread, NULL);

    for (i = 0; i < num_comps; i++) {
        free(clientPackets[i]);
    }
    free(clientPackets);
    free(readMsg);
    free(clientSems);

    for (i = 0; i < num_comps; i++) {
        /* Terminate connection and destroy rpc_example instance */
        ret = close(fds[i]);
        if (ret < 0) {
            perror("Can't close rpc_example fd ??");
            ret = -1;
        }
        printf("rpc_sample: Closed connection to %s!\n", connreq.name);
    }

    free(fds);
    return ret;
}

int test_rpc_stress_multi_threads(int core_id, int num_threads, int func_idx)
{
    int ret = 0;
    int i = 0, j = 0;
    int fd;
    int packet_len;
    char packet_buf[512] = {0};
    pthread_t read_thread;
    struct rppc_create_instance connreq;
    struct rppc_function *function;
    test_exec_args args[num_threads];
    char serviceMgrName[20];
    char serviceMgrPath[20];

    snprintf (serviceMgrName, _POSIX_PATH_MAX, "rpc_example_%d", core_id);
    snprintf (serviceMgrPath, _POSIX_PATH_MAX, "/dev/%s", serviceMgrName);

    /* Connect to the rpc_example ServiceMgr on the specified core: */
    fd = open(serviceMgrPath, O_RDWR);
    if (fd < 0) {
        perror("Can't open rpc_example device");
        return -1;
    }
    strcpy(connreq.name, serviceMgrName);

    /* Create an rpc_example server instance, and rebind its address to this
    * file descriptor.
    */
    ret = ioctl(fd, RPPC_IOC_CREATE, &connreq);
    if (ret < 0) {
        perror("Can't connect to rpc_example instance");
        close(fd);
        return -1;
    }
    printf("rpc_sample: Connected to %s\n", connreq.name);

    clientThreads = malloc(sizeof(pthread_t) * num_threads);
    if (!clientThreads) {
        ret = close(fd);
        return -1;
    }
    clientSems = malloc(sizeof(sem_t) * num_threads);
    if (!clientSems) {
        free(clientThreads);
        ret = close(fd);
        return -1;
    }

    readMsg = malloc(sizeof(bool) * num_threads);
    if (!readMsg) {
        free(clientSems);
        free(clientThreads);
        ret = close(fd);
        return -1;
    }

    clientPackets = malloc(sizeof(char *) * num_threads);
    if (!clientPackets) {
        free(readMsg);
        free(clientSems);
        free(clientThreads);
        ret = close(fd);
        return -1;
    }

    for (i = 0; i < num_threads; i++) {
        clientPackets[i] = malloc(512 * sizeof(char));
        if (!clientPackets[i]) {
            for (j = 0; j < i; j++) {
                free(clientPackets[j]);
            }
            free(clientPackets);
            free(readMsg);
            free(clientSems);
            free(clientThreads);
            close(fd);
            return -1;
        }
    }

    ret = pthread_create(&read_thread, NULL, test_read_thread, (void *)fd);
    if (ret < 0) {
        perror("Can't create thread");
        for (i = 0; i < num_threads; i++) {
            free(clientPackets[i]);
        }
        free(clientPackets);
        free(readMsg);
        free(clientSems);
        free(clientThreads);
        close(fd);
        return -1;
    }

    for ( i = 0; i < num_threads; i++) {
        ret = sem_init(&clientSems[i], 0, 0);
        args[i].fd = fd;
        args[i].start_num = (i * NUM_ITERATIONS) + 1;
        args[i].test_num = 2;
        args[i].sem = &clientSems[i];
        args[i].thread_num = i;
        args[i].func_idx = func_idx;
        readMsg[i] = true;
        ret = pthread_create(&clientThreads[i], NULL, test_exec_call,
                             (void *)&args[i]);
        if (ret < 0) {
            perror("Can't create thread");
            ret = -1;
            break;
        }
        printf("Created thread %d\n", i);
    }

    for (j = 0; j < i; j++) {
        printf("Join thread %d\n", j);
        pthread_join(clientThreads[j], NULL);
        sem_destroy(&clientSems[j]);
    }

    function = (struct rppc_function *)packet_buf;
    function->fxn_id = FXN_IDX_FXNTRIPLE;
    function->num_params = 1;
    function->params[0].type = RPPC_PARAM_TYPE_ATOMIC;
    function->params[0].size = sizeof(int);
    function->params[0].data = i;
    function->num_translations = 0;

    /* Exec command: */
    packet_len = sizeof(struct rppc_function) +\
                 (function->num_translations *\
                  sizeof(struct rppc_param_translation));

    runTest = false;
    if (send_cmd(fd, (char *)packet_buf, packet_len)) {
        test_status = -1;
    }

    pthread_join(read_thread, NULL);

    for (i = 0; i < num_threads; i++) {
        free(clientPackets[i]);
    }
    free(clientPackets);
    free(readMsg);
    free(clientSems);
    free(clientThreads);

    /* Terminate connection and destroy rpc_example instance */
    ret = close(fd);
    if (ret < 0) {
        perror("Can't close rpc_example fd ??");
        ret = -1;
    }
    printf("rpc_sample: Closed connection to %s!\n", connreq.name);

    return ret;
}

int test_rpc_stress_multi_srvmgr(int core_id, int num_comps, int func_idx)
{
    int ret = 0;
    int i = 0, j = 0;
    int fd[num_comps];
    struct rppc_create_instance connreq;
    test_exec_args args[num_comps];
    char serviceMgrName[20];
    char serviceMgrPath[20];

    snprintf (serviceMgrName, _POSIX_PATH_MAX, "rpc_example_%d", core_id);
    snprintf (serviceMgrPath, _POSIX_PATH_MAX, "/dev/%s", serviceMgrName);

    for (i = 0; i < num_comps; i++) {
        /* Connect to the rpc_example ServiceMgr on the specified core: */
        fd[i] = open(serviceMgrPath, O_RDWR);
        if (fd[i] < 0) {
            perror("Can't open rpc_example device");
            ret = -1;
            break;
        }
        strcpy(connreq.name, serviceMgrName);

        /* Create an rpc_example server instance, and rebind its address to this
        * file descriptor.
        */
        ret = ioctl(fd[i], RPPC_IOC_CREATE, &connreq);
        if (ret < 0) {
            perror("Can't connect to rpc_example instance");
            close(fd[i]);
            break;
        }
        printf("rpc_sample: Connected to %s\n", connreq.name);
    }
    if (i != num_comps) {
        /* cleanup */
        for (j = 0; j < i; j++) {
            ret = close(fd[j]);
            if (ret < 0) {
                perror("Can't close rpc_example fd ??");
            }
        }
        return -1;
    }

    clientThreads = malloc(sizeof(pthread_t) * num_comps);
    if (!clientThreads) {
        for (i = 0; i < num_comps; i++) {
            ret = close(fd[i]);
            if (ret < 0) {
                perror("Can't close rpc_example fd ??");
            }
        }
        return -1;
    }

    for ( i = 0; i < num_comps; i++) {
        args[i].fd = fd[i];
        args[i].start_num = 1;
        args[i].test_num = 1;
        args[i].sem = NULL;
        args[i].thread_num = i;
        args[i].func_idx = func_idx;
        ret = pthread_create(&clientThreads[i], NULL, test_exec_call,
                             (void *)&args[i]);
        if (ret < 0) {
            perror("Can't create thread");
            ret = -1;
            break;
        }
        printf("Created thread %d\n", i);
    }

    for (j = 0; j < i; j++) {
        printf("Join thread %d\n", j);
        pthread_join(clientThreads[j], NULL);
    }

    free(clientThreads);

    for (i = 0; i < num_comps; i++) {
        /* Terminate connection and destroy rpc_example instance */
        ret = close(fd[i]);
        if (ret < 0) {
            perror("Can't close rpc_example fd ??");
            ret = -1;
        }
        printf("rpc_sample: Closed connection to %s!\n", connreq.name);
    }

    return ret;
}

int test_errors(int core_id, int num_comps, int sub_test)
{
    int ret = 0;
    int i = 0, j = 0;
    int fd;
    struct rppc_create_instance connreq;
    test_exec_args args;
    char serviceMgrName[20];
    char serviceMgrPath[20];

    snprintf (serviceMgrName, _POSIX_PATH_MAX, "rpc_example_%d", core_id);
    snprintf (serviceMgrPath, _POSIX_PATH_MAX, "/dev/%s", serviceMgrName);

    /* Connect to the rpc_example ServiceMgr on the specified core: */
    fd = open(serviceMgrPath, O_RDWR);
    if (fd < 0) {
        perror("Can't open rpc_example device");
        ret = -1;
        return -1;
    }
    strcpy(connreq.name, serviceMgrName);

    /* Create an rpc_example server instance, and rebind its address to this
    * file descriptor.
    */
    ret = ioctl(fd, RPPC_IOC_CREATE, &connreq);
    if (ret < 0) {
        perror("Can't connect to rpc_example instance");
        close(fd);
        return -1;
    }
    printf("rpc_sample: Connected to %s\n", connreq.name);

    clientThreads = malloc(sizeof(pthread_t));
    if (!clientThreads) {
        ret = close(fd);
        if (ret < 0) {
            perror("Can't close rpc_example fd ??");
        }
        return -1;
    }

    args.fd = fd;
    args.start_num = 1;
    args.test_num = 1;
    args.sem = NULL;
    args.thread_num = i;
    args.func_idx = FXN_IDX_FXNFAULT;
    args.sub_test = sub_test;
    ret = pthread_create(&clientThreads[0], NULL, test_exec_call,
                         (void *)&args);
    if (ret < 0) {
        perror("Can't create thread");
        ret = close(fd);
        if (ret < 0) {
            perror("Can't close rpc_example fd ??");
        }
        return -1;
    }
    printf("Created thread %d\n", i);

    printf("Join thread %d\n", j);
    pthread_join(clientThreads[0], NULL);

    free(clientThreads);

    /* Terminate connection and destroy rpc_example instance */
    ret = close(fd);
    if (ret < 0) {
        perror("Can't close rpc_example fd ??");
        ret = -1;
    }
    printf("rpc_sample: Closed connection to %s!\n", connreq.name);

    return ret;
}

int main(int argc, char *argv[])
{
    int ret = 0;
    int test_id = -1;
    int core_id = 0;
    int num_comps = 1;
    int num_threads = 1;
    int func_idx = 1;
    int sub_test = 0;
    int c;

    while (1)
    {
        c = getopt (argc, argv, "t:c:x:l:f:s:");
        if (c == -1)
            break;

        switch (c)
        {
        case 't':
            test_id = atoi(optarg);
            break;
        case 'c':
            core_id = atoi(optarg);
            break;
        case 'x':
            num_comps = atoi(optarg);
            break;
        case 'l':
            num_threads = atoi(optarg);
            break;
        case 'f':
            func_idx = atoi(optarg);
            break;
        case 's':
            sub_test = atoi(optarg);
            break;
        default:
            printf ("Unrecognized argument\n");
        }
    }

    if (test_id < 0 || test_id > 4) {
        printf("Invalid test id\n");
        return 1;
    }

    if (func_idx < FXN_IDX_FXNTRIPLE || func_idx >= FXN_IDX_MAX) {
        printf("Invalid function index\n");
        return 1;
    }
    testFunc = func_idx;

    if (func_idx == FXN_IDX_FXNADD3 || func_idx == FXN_IDX_FXNADDX) {
        if (init_sharedmem_funcs() < 0) {
            printf("failure: shmemallocator library must be present for this test function\n");
            return 1;
        }
    }

    switch (test_id) {
        case 1:
            /* multiple threads each with an RPMSG-RPC ServiceMgr instance */
            if (core_id < 0 || core_id > 4) {
                printf("Invalid core id\n");
                return 1;
            }
            if (num_comps < 0) {
                printf("Invalid num comps id\n");
                return 1;
            }
            ret = test_rpc_stress_multi_srvmgr(core_id, num_comps, func_idx);
            break;
        case 2:
            /* Multiple threads, 1 RPMSG-RPC ServiceMgr instances */
            if (core_id < 0 || core_id > 4) {
                printf("Invalid core id\n");
                return 1;
            }
            if (num_threads < 0) {
                printf("Invalid num threads\n");
                return 1;
            }
            ret = test_rpc_stress_multi_threads(core_id, num_threads, func_idx);
            break;
        case 3:
            /* 1 thread using multiple RPMSG-RPC ServiceMgr instances */
            if (core_id < 0 || core_id > 4) {
                printf("Invalid core id\n");
                return 1;
            }
            if (num_comps < 0) {
                printf("Invalid num comps id\n");
                return 1;
            }
            ret = test_rpc_stress_select(core_id, num_comps, func_idx);
            break;
        case 4:
            /* MMU fault test */
            if (core_id < 0 || core_id > 4) {
                printf("Invalid core id\n");
                return 1;
            }
            if (num_comps < 0) {
                printf("Invalid num comps id\n");
                return 1;
            }
            ret = test_errors(core_id, num_comps, sub_test);
            break;
        default:
            break;
    }

    if (ret < 0 || test_status < 0) {
        printf ("TEST STATUS: FAILED.\n");
    }
    else {
        printf ("TEST STATUS: PASSED.\n");
    }
    return 0;
}
