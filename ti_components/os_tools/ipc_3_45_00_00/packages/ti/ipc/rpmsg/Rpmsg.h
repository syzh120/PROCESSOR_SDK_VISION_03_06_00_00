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
/** ============================================================================
 *  @file       Rpmsg.h
 *
 *  @brief      Rpmsg and related structures.
 *
 */


#ifndef ti_ipc_Rpmsg__include
#define ti_ipc_Rpmsg__include

#if defined (__cplusplus)
extern "C" {
#endif


enum Rpmsg_nsFlags {
    RPMSG_NS_CREATE = 0,
    RPMSG_NS_DESTROY = 1
};

#define RPMSG_NAME_SIZE 32


typedef struct Rpmsg_NsMsg {
    char name[RPMSG_NAME_SIZE]; /* name of service including 0 */
    UInt32 addr;                /* address of the service */
    UInt32 flags;               /* see below */
} Rpmsg_NsMsg;


#define RPMSG_NAMESERVICE_PORT   53

/* Message Header: Must match rp_msg_hdr in virtio_rp_msg.h on Linux side. */
typedef struct Rpmsg_Header {
    Bits32 srcAddr;                 /* source endpoint addr               */
    Bits32 dstAddr;                 /* destination endpoint addr          */
    Bits32 reserved;                /* reserved                           */
    Bits16 dataLen;                 /* data length                        */
    Bits16 flags;                   /* bitmask of different flags         */
    UInt8  payload[];               /* Data payload                       */
} Rpmsg_Header;

typedef Rpmsg_Header *Rpmsg_Msg;


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */
#endif /* ti_ipc_Rpmsg__include */
