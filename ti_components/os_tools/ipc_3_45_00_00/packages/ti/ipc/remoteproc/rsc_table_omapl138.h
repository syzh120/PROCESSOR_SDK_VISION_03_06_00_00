/*
 * Copyright (c) 2011-2013, Texas Instruments Incorporated
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
 *  ======== rsc_table_omapl138.h ========
 *
 *  Include this table in each base image, which is read from remoteproc on
 *  host side.
 *
 */

#ifndef _RSC_TABLE_OMAPL138_H_
#define _RSC_TABLE_OMAPL138_H_

#include "rsc_types.h"

#define DATA_DA                 0xc3100000

#ifndef DATA_SIZE
#  define DATA_SIZE  (SZ_1M * 15)
#endif

#define RPMSG_VRING0_DA         0xc3000000
#define RPMSG_VRING1_DA         0xc3004000

#define CONSOLE_VRING0_DA       0xc3008000
#define CONSOLE_VRING1_DA       0xc300C000

#define BUFS0_DA                0xc3040000
#define BUFS1_DA                0xc3080000

/*
 * sizes of the virtqueues (expressed in number of buffers supported,
 * and must be power of 2)
 */
#define RPMSG_VQ0_SIZE          256
#define RPMSG_VQ1_SIZE          256

#define CONSOLE_VQ0_SIZE        256
#define CONSOLE_VQ1_SIZE        256

/* flip up bits whose indices represent features we support */
#define RPMSG_IPU_C0_FEATURES         1

struct my_resource_table {
    struct resource_table base;

    UInt32 offset[13];

    /* rpmsg vdev entry */
    struct fw_rsc_vdev rpmsg_vdev;
    struct fw_rsc_vdev_vring rpmsg_vring0;
    struct fw_rsc_vdev_vring rpmsg_vring1;

    /* data carveout entry */
    struct fw_rsc_carveout data_cout;

    /* trace entry */
    struct fw_rsc_trace trace;
};

#define TRACEBUFADDR (UInt32)&xdc_runtime_SysMin_Module_State_0_outbuf__A
#define TRACEBUFSIZE 0x8000

#pragma DATA_SECTION(ti_ipc_remoteproc_ResourceTable, ".resource_table")
#pragma DATA_ALIGN(ti_ipc_remoteproc_ResourceTable, 4096)

struct my_resource_table ti_ipc_remoteproc_ResourceTable = {
    1, /* we're the first version that implements this */
    3, /* number of entries in the table */
    0, 0, /* reserved, must be zero */
    /* offsets to entries */
    {
        offsetof(struct my_resource_table, rpmsg_vdev),
        offsetof(struct my_resource_table, data_cout),
        offsetof(struct my_resource_table, trace),
    },

    /* rpmsg vdev entry */
    {
        TYPE_VDEV, VIRTIO_ID_RPMSG, 0,
        RPMSG_IPU_C0_FEATURES, 0, 0, 0, 2, { 0, 0 },
        /* no config data */
    },
    /* the two vrings */
    { RPMSG_VRING0_DA, 4096, RPMSG_VQ0_SIZE, 1, 0 },
    { RPMSG_VRING1_DA, 4096, RPMSG_VQ1_SIZE, 2, 0 },

    {
        TYPE_CARVEOUT, DATA_DA, DATA_DA, DATA_SIZE, 0, 0, "IPU_MEM_DATA",
    },

    {
        TYPE_TRACE, TRACEBUFADDR, TRACEBUFSIZE, 0, "trace:dsp",
    },
};

#endif /* _RSC_TABLE_OMAPL138_H_ */
