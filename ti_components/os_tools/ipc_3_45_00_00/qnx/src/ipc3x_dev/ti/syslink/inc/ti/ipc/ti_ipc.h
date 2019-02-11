/*
 * TI IPC remote processor driver
 *
 * Copyright (c) 2013 Texas Instruments. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the documentation and/or other materials provided with the
 *   distribution.
 * * Neither the name Texas Instruments nor the names of its
 *   contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef TI_IPC_H
#define TI_IPC_H

#include <stdint.h>
#include <ioctl.h>

/* To request any local addr */
#define TIIPC_ADDRANY           0xFFFFFFFF

/* Params for TIIPC_IOCSETLOCAL and TIIPC_IOCGETLOCAL */
typedef struct tiipc_local_params_t {
    uint32_t local_addr;
} tiipc_local_params;

/* Params for TIIPC_IOCSETREMOTE and TIIPC_IOCGETREMOTE */
typedef struct tiipc_remote_params_t {
    uint32_t remote_addr;
    uint32_t remote_proc;
} tiipc_remote_params;


#define TIIPC_IOC_MAGIC       'M'

#define TIIPC_IOCSETLOCAL     _IOWR(TIIPC_IOC_MAGIC, 1, tiipc_local_params)

#define TIIPC_IOCGETLOCAL     _IOR (TIIPC_IOC_MAGIC, 2, tiipc_local_params)

#define TIIPC_IOCSETREMOTE    _IOWR(TIIPC_IOC_MAGIC, 3, tiipc_remote_params)

#define TIIPC_IOCGETREMOTE    _IOR (TIIPC_IOC_MAGIC, 4, tiipc_remote_params)

#endif /* TI_IPC_H */
