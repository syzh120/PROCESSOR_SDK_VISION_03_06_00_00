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
 * ======== pppif.h ========
 *
 * Basic includes for PPP
 *
 */


#ifndef _C_PPPIF_INC
#define _C_PPPIF_INC

/*----------------------------------------------- */
/* Serial Interface Commands */
#define SI_MSG_CALLSTATUS       1               /* Aux = Call status */
#define SI_MSG_SENDPACKET       2               /* Send Packet */
#define SI_MSG_PEERCMAP         3               /* Aux = Peer's CMAP */

/* Call Status Aux Values */
#define SI_CSTATUS_WAITING              0       /* Idle */
#define SI_CSTATUS_NEGOTIATE            1       /* In LCP negotiation */
#define SI_CSTATUS_AUTHORIZE            2       /* In authorization */
#define SI_CSTATUS_CONFIGURE            3       /* In configuration */
#define SI_CSTATUS_CONNECTED            4       /* Connected */
#define SI_CSTATUS_DISCONNECT           128     /* Dropped */
#define SI_CSTATUS_DISCONNECT_LCP       129     /* Dropped in LCP */
#define SI_CSTATUS_DISCONNECT_AUTH      130     /* Dropped in authorization */
#define SI_CSTATUS_DISCONNECT_IPCP      131     /* Dropped in IP configuration */

/*----------------------------------------------- */
/* PPP Operational Option Flags */
#define PPPFLG_SERVER           0x0100    /* Operate in server mode */
#define PPPFLG_CLIENT           0x0200    /* Operate in client mode */
#define PPPFLG_OPT_AUTH_PAP     0x0001    /* Require/Allow PAP authentication */
#define PPPFLG_OPT_AUTH_CHAP    0x0002    /* Require/Allow CHAP authentication */
#define PPPFLG_OPT_USE_MSE      0x0004    /* Use MS extensions as server/client */
#define PPPFLG_OPT_LOCALDNS     0x0008    /* Claim Local IP as DNS server */
#define PPPFLG_SIOPT_SENDCMAP   0x0010    /* Send an async character map */
#define PPPFLG_SIOPT_RECVCMAP   0x0020    /* Accept an async character map */
#define PPPFLG_OPT_CLIENT_P2P   0x0040    /* Connect client as Point2Point only */
#define PPPFLG_OPT_ALLOW_IP     0x0080    /* Allow client to declare own IP addr */
#define PPPFLG_OPT_ALLOW_HC     0x0400    /* Allow peer to negotiate PFC/ACFP */
#define PPPFLG_CH1              0x1000    /* Server Channel 1 */
#define PPPFLG_CH2              0x2000    /* Server Channel 2 */
#define PPPFLG_CH3              0x4000    /* Server Channel 3 */
#define PPPFLG_CH4              0x8000    /* Server Channel 4 */
#define PPPFLG_CHMASK           0xF000

#define PPPNAMELEN              32        /* PPP UserId and Password Max len */

#ifdef _INCLUDE_PPP_CODE

/*----------------------------------------------- */
/* Public PPP Functions */
_extern HANDLE pppNew( HANDLE hSI, uint pppFlags, uint mru,
                       IPN IPServer, IPN IPMask, IPN IPClient,
                       char *Username, char *Password, UINT32 cmap,
                       void (*SICtrl)( HANDLE, uint, UINT32, PBM_Pkt * ) );
_extern void   pppFree( HANDLE hPPP );
_extern void   pppInput( HANDLE hPPP, PBM_Pkt *pPkt );
_extern void   pppTimer( HANDLE hPPP );
_extern void   pppTxIpPacket( PBM_Pkt *pPkt );

#endif

#endif
