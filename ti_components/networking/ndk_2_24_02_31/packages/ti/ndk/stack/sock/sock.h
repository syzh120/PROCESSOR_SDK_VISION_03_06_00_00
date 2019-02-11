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
 * ======== sock.h ========
 *
 * Sock object private definitions
 *
 */

#ifndef _SOCK_INC_
#define _SOCK_INC_

/* Socket State Bits */
#define SS_CONNREQUIRED         0x0001  /* socket connected required */
#define SS_ADDR                 0x0002  /* supply address on send */
#define SS_ATOMIC               0x0004  /* read/write one packet per call */
#define SS_ATOMICREAD           0x0008  /* read one packet per call */
#define SS_ATOMICWRITE          0x0010  /* write one packet per call */
#define SS_ISCONNECTED          0x0020  /* socket is connected */
#define SS_ISCONNECTING         0x0040  /* socket connect in progress */
#define SS_CLOSING              0x0080  /* socket close in progress (abandoned) */
#define SS_CANTSENDMORE         0x0100  /* can't send more data to peer */
#define SS_CANTRCVMORE          0x0200  /* can't receive more data from peer */
#define SS_OOBACTIVE            0x0400  /* OOB variables are valid */
#define SS_OOBDATAVALID         0x0800  /* OOB data byte is valid */
#define SS_NBIO                 0x1000  /* non-blocking operations only */
#define SS_READYQ               0x2000  /* on parent's ready queue */
#define SS_PENDINGQ             0x4000  /* on parent's pending queue */
#define SS_LINGERING            0x8000  /* we are waiting on a disconnect */

/* Internal Socket Access Functions */
extern void SockIntAbort( SOCK *ps );

/* Internal Socket Protocol Functions */
extern int SockPrAttach( SOCK *ps );
extern int SockPrDetach( SOCK *ps );
extern void SockPrCtlError( SOCK *ps, uint Code );

/* Some protocol functions are called for TCP only... */
#ifdef _STRONG_CHECKING
extern int  SockPrRecv( SOCK *ps );
extern int  SockPrListen( SOCK *ps );
extern int  SockPrConnect( SOCK *ps );
extern int  SockPrDisconnect( SOCK *ps );
extern void SockPrInherit( SOCK *psParent, SOCK *psChild );
#define SockPrGetState( p, c )  TcpPrGetState( (HANDLE)p, p->hTP )
#else
#define SockPrRecv(h)           if((h)->SockProt==SOCKPROT_TCP) TcpPrRecv( (HANDLE)(h), (h)->hTP );
#define SockPrListen(h)         TcpPrListen( (HANDLE)(h), (h)->hTP )
#define SockPrConnect(h)        TcpPrConnect( (HANDLE)(h), (h)->hTP )
#define SockPrDisconnect(h)     TcpPrDisconnect( (HANDLE)(h), (h)->hTP )
#define SockPrInherit( p, c )   TcpPrInherit( (HANDLE)(p), (p)->hTP, (HANDLE)(c), (c)->hTP )
#define SockPrGetState( p, c )  TcpPrGetState( (HANDLE)(p), (p)->hTP )
#endif

#endif
