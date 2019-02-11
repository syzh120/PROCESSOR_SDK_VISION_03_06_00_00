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
 * ======== nat.h ========
 *
 * Network Address Translation
 *
 */


#ifndef _NAT_INC
#define _NAT_INC

typedef struct _natentry {
    uint                Type;           /* Set to HTYPE_NAT */
    uint                Flags;          /* Entry Flags */
#define NI_FLG_STATIC       0x0001          /* Entry does not have a timeout */
#define NI_FLG_RESERVED     0x0002          /* Entry used reserved port */
#define NI_FLG_WILD         0x0004          /* Foreign addr/port is unresolved */
    struct _natinfo     NI;
    struct _natentry    *pNextTIME;     /* Next entry in timeout list */
    struct _natentry    **ppPrevTIME;   /* Ptr to Prev entry's pNextTIME */
    struct _natentry    *pNextMAPPED;   /* Next entry in MAPPED list */
    struct _natentry    **ppPrevMAPPED; /* Ptr to Prev entry's pNextMAPPED */
    struct _natentry    *pNextLOCAL;    /* Next entry in LOCAL list */
    struct _natentry    **ppPrevLOCAL;  /* Ptr to Prev entry's pNextLOCAL */
    } NATENTRY;

/* NatFindPNI - Find PNI */
extern NATINFO *NatFindPNI( IPN IPLocal, UINT16 PortLocal,
                            IPN IPForeign, UINT16 PortForeign,
                            UINT8 Protocol, UINT16 PortMapped );
#endif
