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

#ifdef USE_PERFUTILS
#include "PerfUtils.h"
#endif
#include <sys/neutrino.h>
#include <sys/syspage.h>

typedef struct {
    int a;
} fxn_double_args;

/* Note: Set bit 31 to indicate static function indicies:
 * This function order will be hardcoded on BIOS side, hence preconfigured:
 * See src/examples/srvmgr/test_omx.c.
 */
#define FXN_IDX_FXNDOUBLE            (3 | 0x80000000)

#ifdef USE_PERFUTILS
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
#else
uint64_t diff(uint64_t start, uint64_t end)
{
    unsigned long    nsecs;

    uint64_t temp;
    if ((end-start)<0) {
       temp = (~(uint64_t)0) - start + end;
    } else {
       temp = end - start;
    }
    printf("%llu cycles\n", temp);
    nsecs = temp * 1000000000 / SYSPAGE_ENTRY(qtime)->cycles_per_sec;
    return nsecs;
}
#endif

int exec_cmd(int fd, char *msg, int len, char *reply_msg, int *reply_len)
{
    int ret = 0;
#ifndef USE_PERFUTILS
    //uint64_t start, end, delta;

    //start = ClockCycles();
#endif
    ret = write(fd, msg, len);
#ifndef USE_PERFUTILS
    //end = ClockCycles();
    //diff(start, end);
#endif
    if (ret < 0) {
         perror("Can't write to OMX instance");
         return -1;
    }

    /* Now, await normal function result from OMX service: */
    // Note: len should be max length of response expected.
#ifndef USE_PERFUTILS
    //start = ClockCycles();
#endif
    ret = read(fd, reply_msg, len);
#ifndef USE_PERFUTILS
    //end = ClockCycles();
    //diff(start, end);
#endif
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

void test_exec_call(int fd, int num_iterations)
{
    int               i;
    uint16_t          server_status;
    int               packet_len;
    int               reply_len;
    char              packet_buf[512] = {0};
    char              return_buf[512] = {0};
    omx_packet        *packet = (omx_packet *)packet_buf;
    omx_packet        *rtn_packet = (omx_packet *)return_buf;
    fxn_double_args   *fxn_args   = (fxn_double_args *)&packet->data[1];
#ifdef USE_PERFUTILS
    struct timespec   start,end;
    unsigned long     elapsed=0,delta;
#else
    uint64_t          start = 0,end = 0;
    uint64_t          elapsed=0,delta;
#endif

#ifdef USE_PERFUTILS
    PerfUtils_init();
    PerfUtils_startGpTimer(10);
    PerfUtils_addFxn(0, "omx_benchmark_fxndouble", 0, 0, 0);
#else
    printf("SYSPAGE_ENTRY(qtime)->cycles_per_sec is %llu\n", SYSPAGE_ENTRY(qtime)->cycles_per_sec);
    printf("overflow (~(uint64_t)0) / SYSPAGE_ENTRY(qtime)->cycles_per_sec is %llu\n", (~(uint64_t)0) / SYSPAGE_ENTRY(qtime)->cycles_per_sec);
#endif
    for (i = 1; i <= num_iterations; i++) {

        /* Set Packet Header for the RCMServer, synchronous execution: */
        init_omx_packet(packet, OMX_DESC_MSG);

        /* Set OMX Function Index to call, with data: */
        packet->fxn_idx = FXN_IDX_FXNDOUBLE;

        /* Set data for the OMX function: */
        packet->data_size = sizeof(fxn_double_args) + sizeof(int);
        packet->data[0] = 0; // RPC_OMX_MAP_INFO_NONE
        fxn_args->a = i;

        /* Exec command: */
        packet_len = sizeof(omx_packet) + packet->data_size;
#ifdef USE_PERFUTILS
        PerfUtils_enter(0);
#else
        start = ClockCycles();
#endif
        exec_cmd(fd, (char *)packet, packet_len, (char *)rtn_packet, &reply_len);
#ifdef USE_PERFUTILS
        PerfUtils_exit(0);
#else
        end = ClockCycles();
#endif
        delta = diff(start,end);
        elapsed += delta;

        /* Decode reply: */
        server_status = (OMX_DESC_TYPE_MASK & rtn_packet->desc) >>
                OMX_DESC_TYPE_SHIFT;
        if (server_status == OMXSERVER_STATUS_SUCCESS)  {

           printf ("omx_benchmark: called fxnDouble(%d)), result = %d\n",
                        fxn_args->a, rtn_packet->result);
#ifndef USE_PERFUTILS
           printf ("exec_cmd time (%d): %llu\n", i, delta);
#endif
        }
        else {
           printf("omx_benchmark: Failed to execute fxnDouble: server status: %d\n",
                server_status);
        }

    }
#ifdef USE_PERFUTILS
    PerfUtils_printReport(1);
    PerfUtils_stopGpTimer(10);
    PerfUtils_destroy();
#else
    printf("exec_cmd avg time: %llu nsecs\n", elapsed/num_iterations);
#endif
}

int main(int argc, char *argv[])
{
       int fd;
       int ret;
       int core_id;
       int num_iterations = 1;
       struct omx_conn_req connreq = { .name = "OMX" };
       char device_name[_POSIX_PATH_MAX];

       if (argc > 3)  {
            printf("Usage: omx_sample <core_id> [<num_iterations>]\n");
            return 1;
       }
       else if (argc == 3) {
            core_id = atoi(argv[1]);
            num_iterations = atoi(argv[2]);
       }
       else if (argc == 2) {
            core_id = atoi(argv[1]);
            num_iterations = 1;
       }
       else {
            core_id = 0;
            num_iterations = 1;
       }

       /* Connect to the OMX ServiceMgr on Ducati core 1: */
       snprintf (device_name, _POSIX_PATH_MAX,
                 "/dev/rpmsg-omx%d", core_id);
       fd = open(device_name, O_RDWR);
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
       test_exec_call(fd, num_iterations);

       /* Terminate connection and destroy OMX instance */
       ret = close(fd);
       if (ret < 0) {
            perror("Can't close OMX fd ??");
            return 1;
       }

       printf("omx_sample: Closed connection to %s!\n", connreq.name);
       return 0;
}
