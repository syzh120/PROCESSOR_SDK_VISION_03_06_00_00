/*
 * Copyright (c) 2011, Texas Instruments Incorporated
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
 * omx_sample.c
 *
 * User space example showing how to create/connect/communicate
 * to an OMX component server.
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

#include "ti/ipc/rpmsg_omx.h"

#include "omx_packet.h"

#define CALLBACK_DATA       "OMX_Callback"
#define SUCCESS             0
#define ERROR               -1

/* Some Example OMX Application stuff: */
#define H264_DECODER_NAME   "H264_decoder"

/* Note: Set bit 31 to indicate static function indicies:
 * This function order will be hardcoded on BIOS side, hence preconfigured:
 */
#define FXN_IDX_OMX_GETHANDLE        (0 | 0x80000000)
#define FXN_IDX_OMX_SETPARAMETER     (1 | 0x80000000)
#define FXN_IDX_OMX_GETPARAMETER     (2 | 0x80000000)

/* OMX_HANDLETYPE defined elsewhere, but for this example ... */
typedef uint32_t OMX_HANDLETYPE;

/* The map_info_type enum is defined in the rpmsg_omx driver, and is defined
 * elsewhere in userspace, but define it here for this sample. The data portion
 * of the packet being written is expected to start with this.
 */
typedef enum {
    RPC_OMX_MAP_INFO_NONE       = 0,
    RPC_OMX_MAP_INFO_ONE_BUF    = 1,
    RPC_OMX_MAP_INFO_TWO_BUF    = 2,
    RPC_OMX_MAP_INFO_THREE_BUF  = 3,
    RPC_OMX_MAP_INFO_MAX        = 0x7FFFFFFF
} map_info_type;

int num_iterations = 1;

int exec_cmd(int fd, char *msg, size_t len, char *reply_msg, int *reply_len, int cb)
{
    int ret = 0;
    int cb_len;
    char              callback_buf[512] = {0};
    omx_packet        *cb_packet = (omx_packet *)callback_buf;

    ret = write(fd, msg, len);
    if (ret < 0) {
        perror("Can't write to OMX instance");
        return ERROR;
    }

    if (cb)  {
        /* Get intervening callback message, sent from RPC_SKEL_GetHandle() */
        cb_len = sizeof(omx_packet) + sizeof(CALLBACK_DATA);
        ret = read(fd, callback_buf, cb_len);
        if (ret < 0) {
            perror("Did not get callback OMX message");
            return ERROR;
        }
        else {
            printf("\tmsg_id: %d, fxn_idx: %d, data_size: %d, data: %s\n",
                     cb_packet->msg_id, cb_packet->fxn_idx, cb_packet->data_size,
                     (char *)cb_packet->data);
        }
    }

    /* Now, await normal function result from OMX service:
     * Note: len should be max length of response expected.
     */
    ret = read(fd, reply_msg, len);
    if (ret < 0) {
        perror("Can't read from OMX instance");
        return ERROR;
    }
    else {
        *reply_len = ret;
    }
    return SUCCESS;
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

int test_h264_decoder(int fd, int i)
{
    uint16_t          server_status;
    size_t            packet_len;
    int               reply_len;
    int               ret;
    char              packet_buf[512] = {0};
    char              return_buf[512] = {0};
    omx_packet        *packet = (omx_packet *)packet_buf;
    omx_packet        *rtn_packet = (omx_packet *)return_buf;
    OMX_HANDLETYPE    omx_handle;
    map_info_type     map_info = RPC_OMX_MAP_INFO_NONE;
    /* Call OMX_GetHandle to create an H264_decoder: */

    /* Set Packet Header for the RCMServer, synchronous execution: */
    init_omx_packet(packet, OMX_DESC_MSG);

    /* Set OMX Function Index to call, with data: */
    packet->fxn_idx = FXN_IDX_OMX_GETHANDLE;
    /* Set data for the OMX function: */
    packet->data_size = strlen(H264_DECODER_NAME) + sizeof(map_info) + 1;
    memcpy(packet->data, &map_info, sizeof(map_info));
    strcpy((char *)&packet->data + sizeof(map_info), H264_DECODER_NAME);
    *(char *)&packet->data[packet->data_size] = '\0';

    /* Exec command: */
    packet_len = sizeof(omx_packet) + packet->data_size;
    printf("omx_sample (%d): OMX_GetHandle (%s).\n", i, H264_DECODER_NAME);
    ret = exec_cmd(fd, (char *)packet, packet_len, (char *)rtn_packet, &reply_len, 1);
    if (SUCCESS != ret) {
        printf("omx_sample exec cmd failed\n");
        return ERROR;
    }

    /* Decode reply: */
    server_status = (OMX_DESC_TYPE_MASK & rtn_packet->desc) >>
            OMX_DESC_TYPE_SHIFT;
    if (server_status == OMXSERVER_STATUS_SUCCESS)  {
        omx_handle = *(OMX_HANDLETYPE *)rtn_packet->data;
        printf("omx_sample (%d): Got omx_handle: 0x%x\n", i, omx_handle);
    }
    else {
        printf("omx_sample: Failed to execute OMX_GetHandle: server status: %d\n",
            server_status);
    }

    /* now call SetParameter, passing back omx_handle...*/
    init_omx_packet(packet, OMX_DESC_MSG);
    packet->fxn_idx = FXN_IDX_OMX_SETPARAMETER;
    packet->data_size = sizeof(OMX_HANDLETYPE) + sizeof(map_info);
    memcpy(packet->data, &map_info, sizeof(map_info));
    memcpy(packet->data + sizeof(map_info), &omx_handle, sizeof(OMX_HANDLETYPE));

    /* Exec command: */
    packet_len = sizeof(omx_packet) + packet->data_size;
    printf("omx_sample(%d): OMX_SetParameter (0x%x)\n", i, omx_handle);
    ret = exec_cmd(fd, (char *)packet, packet_len, (char *)rtn_packet, &reply_len, 0);
    if (SUCCESS != ret) {
        printf("omx_sample exec cmd failed\n");
        return ERROR;
    }

    /* Decode reply: */
    server_status = (OMX_DESC_TYPE_MASK & rtn_packet->desc) >>
            OMX_DESC_TYPE_SHIFT;
    if (server_status == OMXSERVER_STATUS_SUCCESS)  {
        printf("omx_sample (%d): Got result %d\n", i, rtn_packet->result);
    }
    else {
        printf("omx_sample: Failed to execute OMX_SetParameter: server status: %d\n",
            server_status);
    }

    return SUCCESS;
}


int main(int argc, char *argv[])
{
    int fd;
    int ret;
    struct omx_conn_req connreq = { .name = "OMX" };
    int i;
    int core_id;
    char device_name[_POSIX_PATH_MAX];

    if (argc > 3)  {
        printf("Usage: omx_sample <core_id> [<num_iterations>]\n");
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

    /* Connect to the OMX ServiceMgr on Ducati core 1: */
    snprintf (device_name, _POSIX_PATH_MAX,
              "/dev/rpmsg-omx%d", core_id);
    fd = open(device_name, O_RDWR);
    if (fd < 0) {
        perror("Can't open OMX device");
        return ERROR;
    }

    /* Create an OMX server instance, and rebind its address to this
     * file descriptor.
     */
    ret = ioctl(fd, OMX_IOCCONNECT, &connreq);
    if (ret < 0) {
        perror("Can't connect to OMX instance");
        return ERROR;
    }
    printf("omx_sample: Connected to %s\n", connreq.name);

    for (i = 1; i <= num_iterations; i++) {
        ret = test_h264_decoder(fd, i);
        if (SUCCESS != ret) {
            printf("dummy decoder test failed\n");
            return ERROR;
        }
    }

    /* Terminate connection and destroy OMX instance */
    ret = close(fd);
    if (ret < 0) {
        perror("Can't close OMX fd ??");
        return ERROR;
    }

    printf("omx_sample: Closed connection to %s!\n", connreq.name);

    return SUCCESS;
}
