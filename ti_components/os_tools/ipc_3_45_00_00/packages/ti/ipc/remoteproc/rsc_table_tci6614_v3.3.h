/*
 * Copyright (c) 2012-2013, Texas Instruments Incorporated
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
 *  ======== rsc_table_tci6614_v3.3.h ========
 *
 *  Linux v3.3 remoteproc version of the resource table.
 *
 *  Include this table in each base image, which is read from remoteproc on
 *  host side.
 *
 */

#ifndef _RSC_TABLE_TCI6614_H_
#define _RSC_TABLE_TCI6614_H_

#include <xdc/cfg/global.h>

struct resource {
    uint32_t type;
    uint32_t id;
    uint32_t da_low;
    uint32_t da_high;
    uint32_t pa_low;
    uint32_t pa_high;
    uint32_t len;
    uint32_t flags;
    uint32_t pad1;
    uint32_t pad2;
    uint32_t pad3;
    uint32_t pad4;
    char name[48];
};

/* virtio ids: keep in sync with the linux "include/linux/virtio_ids.h" */
#define VIRTIO_ID_RPMSG         7 /* virtio remote processor messaging */

/* Indices of rpmsg virtio features we support */
#define VIRTIO_RPMSG_F_NS       0 /* RP supports name service notifications */

#define IPU_C0_FEATURES         1

#define TYPE_CARVEOUT    0
#define TYPE_DEVMEM      1
#define TYPE_TRACE       2
#define TYPE_VRING       3
#define TYPE_VIRTIO_DEV  4

/* Size constants must match those used on host: include/asm-generic/sizes.h */
#define SZ_1M                           0x00100000
#define SZ_2M                           0x00200000
#define SZ_4M                           0x00400000
#define SZ_8M                           0x00800000
#define SZ_16M                          0x01000000
#define SZ_32M                          0x02000000
#define SZ_64M                          0x04000000
#define SZ_128M                         0x08000000
#define SZ_256M                         0x10000000
#define SZ_512M                         0x20000000

#define VRING0_DA               0xA0000000
#define VRING1_DA               0xA0004000

/*
 * sizes of the virtqueues (expressed in number of buffers supported,
 * and must be power of 2)
 */
#define VQ0_SIZE                256
#define VQ1_SIZE                256


/* Add trace buffer information to the resource table */
#define TRACEBUFADDR (UInt32)&xdc_runtime_SysMin_Module_State_0_outbuf__A
#define TRACEBUFSIZE sysMinBufSize

#pragma DATA_SECTION(resources, ".resource_table")
#pragma DATA_ALIGN(resources, 4096)
struct resource resources[] = {
    /*
     * Virtio entries must come first.
     */
#ifndef TRACE_RESOURCE_ONLY
    {TYPE_VIRTIO_DEV,0,IPU_C0_FEATURES,0,0,0,0,VIRTIO_ID_RPMSG,0,0,0,0,"vdev:rpmsg"},
    {TYPE_VRING, 0, VRING0_DA, 0, 0, 0,VQ0_SIZE,0,0,0,0,0,"vring:dsp->arm"},
    {TYPE_VRING, 1, VRING1_DA, 0, 0, 0,VQ1_SIZE,0,0,0,0,0,"vring:mpu->dsp"},
#endif
    {TYPE_TRACE, 0, TRACEBUFADDR,0,0,0, TRACEBUFSIZE, 0,0,0,0,0,"trace:dsp"},
};

#endif /* _RSC_TABLE_TCI6614_H_ */
