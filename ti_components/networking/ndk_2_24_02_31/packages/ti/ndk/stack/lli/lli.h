/*
 * Copyright (c) 2012-2014, Texas Instruments Incorporated
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
 * */
/*
 * ======== lli.h ========
 *
 * Link layer object definitions and includes
 *
 */


#ifndef _C_LLI_INC
#define _C_LLI_INC  /* #defined if this .h file has been included */

/*----------------------------------------------------------------------- */
/* Private Structures */
/*----------------------------------------------------------------------- */

/* LLI Structure */
typedef struct _lli {
        uint        Type;            /* Set to HTYPE_LLI */
        struct _lli *pNextExp;       /* Next LLI in timeout list */
        uint        Status;          /* Status code */
        HANDLE      hRt;             /* Associated Route */
        UINT32      Timeout;         /* ARP Request Timeout */
        UINT32      LastUsed;        /* Time for last usage. */
        UINT32      PacketCount;     /* Packets sent via this route */
        PBMQ        ArpPktQ;         /* Queue of packets waiting on this LLI */
        UINT8       MacAddr[6];      /* MacAddr */
        } LLI;

/* LLI Status */
#define LLI_STATUS_IDLE        0   /* Arp Inactive */
#define LLI_STATUS_ARP0        1   /* Arp Request Initiating */
#define LLI_STATUS_ARP1        2   /* Arp Request 1 Pending */
#define LLI_STATUS_ARP2        3   /* Arp Request 2 Pending */
#define LLI_STATUS_ARP3        4   /* Arp Request 3 Pending */
#define LLI_STATUS_ARP4        5   /* Arp Request 4 Pending */
#define LLI_STATUS_ARP5        6   /* Arp Request 5 Pending */
#define LLI_STATUS_DOWN        7   /* Host in "down time" (typically 20 sec) */
#define LLI_STATUS_VALID       8   /* MacAddr is valid */
#define LLI_STATUS_REVALID1    9   /* Revalidation 1 Pending. */
#define LLI_STATUS_REVALID2    10  /* Revalidation 2 Pending. */
#define LLI_STATUS_REVALID3    11  /* Revalidation 3 Pending. */

/*----------------------------------------------------------------------- */
/* Private Functions */

extern void   _LLIExpListInsert( LLI *plli, UINT32 dwExp );
extern void   _LLIExpListRemove( LLI *plli );
extern void   _LLITimeoutCheck();
extern void   _LLITimeoutFlush();
extern void   _LLILowResource();

#endif
