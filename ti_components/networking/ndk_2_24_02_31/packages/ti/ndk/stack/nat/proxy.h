/*
 * Copyright (c) 2012, Texas Instruments Incorporated
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
 * ======== proxy.h ========
 *
 * NAT - Proxy service
 *
 */


#ifndef _PROXY_INC
#define _PROXY_INC

/*------------------------------------------------------------------------- */
/* Proxy Structure */
typedef struct _proxy {
    uint                Type;           /* Set to HTYPE_PROXY */
    uint                NatMode;        /* NatMode (0 to 3) */
#define PROXY_OFFSET_UDP        2
    UINT16              Port;           /* TCP/UDP Port */
    IPN                 IPTarget;       /* Target IP for Rx Proxies */
    int (*pfnEnableCb)( NATINFO *, uint ); /* Enable Proxy Callback */
    int (*pfnTxCb)( NATINFO *, IPHDR *);   /* Tx Proxy Callback */
    int (*pfnRxCb)( NATINFO *, IPHDR *);   /* Rx Proxy Callback */
    struct _proxy       *pNext;         /* Next entry in list */
    struct _proxy       **ppPrev;       /* Ptr to Prev entry's pNext */
    } PROXY;

/*------------------------------------------------------------------------- */
/* Proxy Entry Structure */
typedef struct _proxyentry {
    uint                Type;           /* Set to HTYPE_PROXYENTRY */
    UINT32              TxSeqThresh;    /* Tx TCP Sequence Threshold */
    int                 TxOffset1;      /* Tx Offset <= Threshold */
    int                 TxOffset2;      /* Tx Offset > Threshold */
    UINT32              RxSeqThresh;    /* Rx TCP Sequence Threshold */
    int                 RxOffset1;      /* Rx Offset <= Threshold */
    int                 RxOffset2;      /* Rx Offset > Threshold */
    int (*pfnEnableCb)( NATINFO *, uint ); /* Enable Proxy Callback */
    int (*pfnTxCb)( NATINFO *, IPHDR *);   /* Tx Proxy Callback */
    int (*pfnRxCb)( NATINFO *, IPHDR *);   /* Rx Proxy Callback */
    } PROXYENTRY;

#endif

