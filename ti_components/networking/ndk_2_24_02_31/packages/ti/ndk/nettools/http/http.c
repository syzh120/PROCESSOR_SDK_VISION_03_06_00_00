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
 * ======== http.c ========
 *
 * HTTP Server
 *
 */

#include "http.h"

HANDLE httpOpen( NTARGS *pNTA, NTPARAM_HTTP *pNTP )
{
    HANDLE hEntry;
    IPN    IpAddr;

    if( !pNTA || !pNTP )
        return(0);

    /* Check for called by address */
    if( pNTA->CallMode == NT_MODE_IPADDR )
        IpAddr = pNTA->IPAddr;
    /* Check for called by IfIfx */
    else if( pNTA->CallMode == NT_MODE_IFIDX )
    {
        if( !NtIfIdx2Ip( pNTA->IfIdx, &IpAddr ) )
            return(0);
    }
    else
        return(0);

    if( !pNTP->MaxCon )
        pNTP->MaxCon = 4;

    if( !pNTP->Port )
        pNTP->Port = HTTPPORT;

    hEntry = DaemonNew( SOCK_STREAM, IpAddr, pNTP->Port, httpClientProcess,
                        OS_TASKPRINORM, OS_TASKSTKHIGH, 0, pNTP->MaxCon );

    return( hEntry );
}

void httpClose( HANDLE h )
{
    DaemonFree( h );
}


