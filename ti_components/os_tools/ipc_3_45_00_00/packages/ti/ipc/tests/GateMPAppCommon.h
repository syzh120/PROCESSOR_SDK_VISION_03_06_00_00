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
 *  ======== GateMPAppCommon.h ========
 *
 */

#ifndef GateMPAppCommon__include
#define GateMPAppCommon__include
#if defined (__cplusplus)
extern "C" {
#endif


/*
 *  ======== Application Configuration ========
 */

/* notify commands 00 - FF */
#define GATEMPAPP_CMD_MASK            0xFF000000

/* used by host and remote device to synchronize states with each other*/
#define GATEMPAPP_CMD_SPTR_ADDR       0x10000000
#define GATEMPAPP_CMD_SPTR_ADDR_ACK   0x12000000
#define GATEMPAPP_CMD_SHUTDOWN_ACK    0x20000000
#define GATEMPAPP_CMD_SHUTDOWN        0x21000000
#define GATEMPAPP_CMD_SYNC            0x30000000

/* GateMP instance created on host */
#define GATEMP_HOST_NAME             "GATE_MP1"
/* GateMP instance created on slave */
#define GATEMP_SLAVE_NAME            "GATE_MP2"

/* queue error message*/
#define GATEMPAPP_E_FAILURE           0xF0000000
#define GATEMPAPP_E_UNEXPECTEDMSG     0xF2000000

/* Number of times to lock/unlock */
#define LOOP_ITR    300

typedef struct {
    MessageQ_MsgHeader  reserved;
    UInt32              cmd;
    UInt32              payload;
} GateMPApp_Msg;

#define GateMPApp_MsgHeapId           0
#define GateMPApp_HostMsgQueName      "HOST:MsgQ:01"
#define GateMPApp_SlaveMsgQueName     "SLAVE:MsgQ:01"

#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */
#endif /* GateMPAppCommon__include */
