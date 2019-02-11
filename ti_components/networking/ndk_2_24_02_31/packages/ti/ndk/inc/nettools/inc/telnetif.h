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
 * ======== telnetif.h ========
 *
 */

#ifndef _TELNETIF_H_
#define _TELNETIF_H_

/* TELNET SERVICE */

/* Telnet Parameter Structure */
typedef struct _ntparam_telnet {
        int     MaxCon;             /* Max number of telnet connections */
        int     Port;               /* Port (set to NULL for telnet default) */
        SOCKET  (*Callback)(PSA);   /* Connect function that returns local pipe */
        } NTPARAM_TELNET;

/* TelnetOpen */
/* Create an instance of the Telnet Server */
/* Compatible with NT_MODE_IFIDX and NT_MODE_IPADDR. */
/* Returns a HANDLE to the Telnet instance */
_extern HANDLE TelnetOpen( NTARGS *pNTA, NTPARAM_TELNET *pNTP );

/* TelnetClose */
/* Destroy an instance of the Telnet Server */
_extern void TelnetClose( HANDLE h );

/* telnetClientProcess */
/* This entry point is used to invoke telnet directly from */
/* the server daemon. */
_extern int   telnetClientProcess( SOCKET s, SOCKET (*cbfn)(PSA) );


#endif

