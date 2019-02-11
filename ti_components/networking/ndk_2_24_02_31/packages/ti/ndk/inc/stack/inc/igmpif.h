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
 * ======== igmpif.h ========
 *
 */


#ifndef _C_IGMPIF_INC
#define _C_IGMPIF_INC  /* #defined if this .h file has been included */

/*----------------------------------------------------------------------- */
/* Global Task Information */

/* Defined Messages */
#define MSG_IGMP_TIMER                    (ID_IGMP*MSG_BLOCK + 0)
#define MSG_IGMP_NEEDTIMER                (ID_IGMP*MSG_BLOCK + 1)

/* Global Statistics */
extern UINT32 _IGMPInDiscard;
extern UINT32 _IGMPInQuery;
extern UINT32 _IGMPInResponse;
extern UINT32 _IGMPOutResponse;

/* Access Functions (Kernel) */
_extern void IGMPMsg( uint Msg );
_extern void IGMPInput( PBM_Pkt *pPkt );
_extern uint IGMPTestGroup( IPN IpAddr, uint IfIdx );
_extern int IGMPJoin (HANDLE hSock, struct ip_mreq* ptr_ipmreq);
_extern int IGMPLeave (HANDLE hSock, struct ip_mreq* ptr_ipmreq);

#endif

