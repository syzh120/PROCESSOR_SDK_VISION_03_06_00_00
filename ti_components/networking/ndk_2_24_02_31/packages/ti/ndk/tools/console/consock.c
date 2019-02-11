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
 * ======== consock.c ========
 *
 * Basic Console Functions
 *      ConCmdSocket    -   Socket Command
 *
 */

#include <netmain.h>
#include <_stack.h>
#include "console.h"

static void DumpSockets( uint SockProt );

/*------------------------------------------------------------------------- */
/* ConCmdSocket() */
/* Function to dump socket status */
/*------------------------------------------------------------------------- */
void ConCmdSocket( int ntok, char *tok1 )
{
    if( ntok == 1 && !stricmp( tok1, "udp" ) )
        DumpSockets( SOCKPROT_UDP );
    else if( ntok == 1 && !stricmp( tok1, "tcp" ) )
        DumpSockets( SOCKPROT_TCP );
    else if( ntok == 1 && !stricmp( tok1, "raw" ) )
        DumpSockets( SOCKPROT_RAW );
    else if( ntok == 0 )
    {
        ConPrintf("\n[Socket Command]\n");
        ConPrintf("\nCalled to print the status of all sockets in the system\n\n");
        ConPrintf("socket tcp   - Print out TCP socket status\n");
        ConPrintf("socket udp   - Print out UDP socket status\n");
        ConPrintf("socket raw   - Print out RAW socket status\n\n");
    }
    else
        ConPrintf("\nError in command line. Type 'socket' for help\n");
}

static char *States[] = { "CLOSED","LISTEN","SYNSENT","SYNRCVD",
                          "ESTABLISHED","CLOSEWAIT","FINWAIT1","CLOSING",
                          "LASTACK","FINWAIT2","TIMEWAIT" };

/*------------------------------------------------------------------------- */
/* DumpSockets() */
/* Function to dump the socket list */
/*------------------------------------------------------------------------- */
static void DumpSockets( uint SockProt )
{
    UINT8   *pBuf;
    int     Entries,i;
    SOCKPCB *ppcb;
    char    str[40];

    pBuf = mmBulkAlloc(2048);
    if( !pBuf )
        return;

    /* Use llEnter / llExit since we're calling into the stack */
    llEnter();
    Entries = SockGetPcb( SockProt, 2048, pBuf );
    llExit();

    ConPrintf("\nLocal IP         LPort  Foreign IP       FPort  State\n");
    ConPrintf("---------------  -----  ---------------  -----  -----------\n");

    for(i=0; i<Entries; i++)
    {
        ppcb = (SOCKPCB *)(pBuf+(i*sizeof(SOCKPCB)));

        NtIPN2Str( ppcb->IPAddrLocal, str );
        ConPrintf( "%-15s  %-5u  ", str, htons(ppcb->PortLocal) );

        NtIPN2Str( ppcb->IPAddrForeign, str );
        ConPrintf( "%-15s  %-5u", str, htons(ppcb->PortForeign) );

        if( SockProt == SOCKPROT_TCP )
            ConPrintf("  %s\n",States[ppcb->State]);
        else
            ConPrintf("\n");
    }
    ConPrintf("\n");

    mmBulkFree( pBuf );
}
