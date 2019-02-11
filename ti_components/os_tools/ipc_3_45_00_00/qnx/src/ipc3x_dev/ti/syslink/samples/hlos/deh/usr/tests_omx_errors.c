/*
 * Copyright (c) 2011-2015, Texas Instruments Incorporated
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
 * omx_benchmark.c
 *
 * Benchmark average round trip time for equivalent of RcmClient_exec.
 *
 * This calls the fxnDouble RcmServer function, similar to the ducati
 * rcm/singletest.
 *
 * Requires:
 * --------
 * test_omx.c sample, with fxnDouble registered in RcmServer table.
 *
 * To Configure Ducati code for Benchmarking:
 * ------------------------------------------
 * In package.bld:
 *   - Set profile=release in package.bld
 * In bencmark test code:
 *   - Disable printf's, trace.
 * In benchmark .cfg file:
 *   - Defaults.common$.diags_ASSERT = Diags.ALWAYS_OFF
 *   - Defaults.common$.logger = null;
 *
 * Expected Result:  (Linux, Panda Board ES 2.1, rpmsg13 branch)
 * ---------------
 * avg time: 110 usecs
 *
 * Expected Result:  (Qnx, Playbook ES 2.1, no branch yet - local development)
 * ---------------
 * avg time: 140 usecs
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
//#include <sys/eventfd.h>

#include "ti/ipc/rpmsg_omx.h"

#include "omx_packet.h"

#include <stdbool.h>


typedef struct {
    int a;
    int b;
} fxn_error_args;

/* Note: Set bit 31 to indicate static function indicies:
 * This function order will be hardcoded on BIOS side, hence preconfigured:
 * See src/examples/srvmgr/test_omx.c.
 */
#define FXN_IDX_FXNERROR             (4 | 0x80000000)

unsigned long diff(struct timespec start, struct timespec end)
{
    unsigned long    nsecs;

    struct timespec temp;
    if ((end.tv_nsec-start.tv_nsec)<0) {
        temp.tv_sec = end.tv_sec-start.tv_sec-1;
        temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
    } else {
        temp.tv_sec = end.tv_sec-start.tv_sec;
        temp.tv_nsec = end.tv_nsec-start.tv_nsec;
    }
    nsecs = temp.tv_sec * 1000000 + temp.tv_nsec;
    return nsecs;
}

int exec_cmd(int fd, char *msg, int len, char *reply_msg, int *reply_len)
{
    int ret = 0;

    ret = write(fd, msg, len);
    if (ret < 0) {
         perror("Can't write to OMX instance");
         return -1;
    }

    /* Now, await normal function result from OMX service: */
    // Note: len should be max length of response expected.
    ret = read(fd, reply_msg, len);
    if (ret < 0) {
         perror("Can't read from OMX instance");
         return -1;
    }
    else {
          *reply_len = ret;
    }
    return(0);
}


void init_omx_packet(omx_packet *packet, uint16_t desc)
{
    /* initialize the packet structure */
    packet->desc  |= desc << OMX_DESC_TYPE_SHIFT;
    packet->msg_id  = 0;
    packet->flags  = OMX_POOLID_JOBID_NONE;
    packet->fxn_idx = OMX_INVALIDFXNIDX;
    packet->result = 0;
}

void test_exec_call(int fd, int test_id, uint32_t test_arg)
{
    uint16_t          server_status;
    int               packet_len;
    int               reply_len;
    char              packet_buf[512] = {0};
    char              return_buf[512] = {0};
    omx_packet        *packet = (omx_packet *)packet_buf;
    omx_packet        *rtn_packet = (omx_packet *)return_buf;
    fxn_error_args   *fxn_args   = (fxn_error_args *)&packet->data[1];

    /* Set Packet Header for the RCMServer, synchronous execution: */
    init_omx_packet(packet, OMX_DESC_MSG);

    /* Set OMX Function Index to call, with data: */
    packet->fxn_idx = FXN_IDX_FXNERROR;

    /* Set data for the OMX function: */
    packet->data_size = sizeof(fxn_error_args) + sizeof(int);
    packet->data[0] = 0; // RPC_OMX_MAP_INFO_NONE
    fxn_args->a = test_id;
    fxn_args->b = test_arg;

    /* Exec command: */
    packet_len = sizeof(omx_packet) + packet->data_size;
    exec_cmd(fd, (char *)packet, packet_len, (char *)rtn_packet, &reply_len);

    /* Decode reply: */
    server_status = (OMX_DESC_TYPE_MASK & rtn_packet->desc) >>
            OMX_DESC_TYPE_SHIFT;
    if (server_status == OMXSERVER_STATUS_SUCCESS)  {

       printf ("omx_errors: called fxnError(%d)), result = %d\n",
                    fxn_args->a, rtn_packet->result);
    }
    else {
       printf("omx_errors: Failed to execute fxnError: server status: %d\n",
            server_status);
    }
}

int main(int argc, char *argv[])
{
       int fd;
       int ret;
       int test_id = -1;
       int core_id = 0;
       uint32_t test_arg = (uint32_t)-1;
       bool test_arg_set = false;
       int c;
       struct omx_conn_req connreq = { .name = "OMX" };

       while (1)
       {
           c = getopt (argc, argv, "t:c:a:");
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
           case 'a':
               sscanf(optarg, "%x", &test_arg);
               test_arg_set = true;
               break;
           default:
               printf ("Unrecognized argument\n");
           }
       }

        switch (test_id) {
            case 1:
                printf("DivByZero Test\n");
                break;
            case 2:
                printf("WatchDog Test\n");
                break;
            case 3:
                printf("MMU Fault Test\n");
                if (test_arg == 1) {
                    test_id = 3;
                }
                else if (test_arg == 2) {
                    test_id = 4;
                }
                else {
                    printf("Invalid arg\n");
                    return 1;
                }
                break;
            case 4:
                printf("AMMU Fault Test\n");
                if (test_arg == 1) {
                    test_id = 5;
                }
                else if (test_arg == 2) {
                    test_id = 6;
                }
                else {
                    printf("Invalid arg\n");
                    return 1;
                }
                break;
            case 5:
                printf("Read Inv. Addr Test\n");
                test_id = 7;
                if (!test_arg_set) {
                    printf("Invalid arg\n");
                    return 1;
                }
                break;
            case 6:
                printf("Write Inv. Addr Test\n");
                test_id = 8;
                if (!test_arg_set) {
                    printf("Invalid arg\n");
                    return 1;
                }
                break;
            default:
                printf("Invalid test id\n");
                return 1;
        }

        if (core_id < 0 || core_id > 1) {
            printf("Invalid core id\n");
            return 1;
        }

        printf("omx_sample: Connecting to core %d\n", core_id);

       if (core_id == 0) {
           /* Connect to the OMX ServiceMgr on Ducati core 0: */
           fd = open("/dev/rpmsg-omx0", O_RDWR);
       }
       else {
           /* Connect to the OMX ServiceMgr on Ducati core 1: */
           fd = open("/dev/rpmsg-omx1", O_RDWR);
       }
       if (fd < 0) {
            perror("Can't open OMX device");
            return 1;
       }

       /* Create an OMX server instance, and rebind its address to this
        * file descriptor.
        */
       ret = ioctl(fd, OMX_IOCCONNECT, &connreq);
       if (ret < 0) {
            perror("Can't connect to OMX instance");
            return 1;
       }

       printf("omx_sample: Connected to %s\n", connreq.name);
       test_exec_call(fd, test_id, test_arg);

       /* Terminate connection and destroy OMX instance */
       ret = close(fd);
       if (ret < 0) {
            perror("Can't close OMX fd ??");
            return 1;
       }

       printf("omx_sample: Closed connection to %s!\n", connreq.name);
       return 0;
}
