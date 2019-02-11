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
 * ======== contftp.c ========
 *
 * Basic Console Functions:
 *      ConCmdTFTP  -   Name server lookup
 *
 */

#include <netmain.h>
#include <_stack.h>
#include "console.h"

static void TestTFTP( IPN IPAddr, char *File );

/*------------------------------------------------------------------------- */
/* ConCmdTFTP() */
/* Function to perform TFTP */
/*------------------------------------------------------------------------- */
void ConCmdTFTP( int ntok, char *tok1, char *tok2 )
{
    IPN    IPAddr;

    /* Check for 'stat ip' */
    if( ntok == 0 )
    {
        ConPrintf("\n[TFTP Command]\n");
        ConPrintf("\nCalled to retrieve a file from a TFTP server.\n\n");
        ConPrintf("tftp x.x.x.x myfile  - Retrieve 'myfile' from IP address\n");
        ConPrintf("tftp hostname myfile - Resolve 'hostname' and retrieve 'myfile'\n\n");
    }
    else if( ntok == 2 )
    {
       if( !ConStrToIPN( tok1, &IPAddr ) )
           ConPrintf("Invalid address\n\n");
       else
           TestTFTP( IPAddr, tok2 );
    }
    else
        ConPrintf("\nIllegal argument. Type 'tftp' for help\n");
}

/*------------------------------------------------------------------------- */
/* TestTFTP() */
/*------------------------------------------------------------------------- */
static void TestTFTP( IPN IPAddr, char *File )
{
    int    rc;
    char   *buffer;
    UINT16 ErrorCode;
    UINT32 Size;

    buffer = mmAlloc(3000);
    if( !buffer )
    {
        ConPrintf("\nFailed allocating temp buffer\n");
        return;
    }

    Size = 3000;
    rc = NtTftpRecv( IPAddr, File, buffer, &Size, &ErrorCode );

    if( rc >= 0 )
    {
        UINT32 i;
        int    c;

        ConPrintf("\nFile Retrieved: Size is %d\n",Size);

        if( !rc )
            Size = 3000;

        ConPrintf("\nDisplay (%d bytes) (y/n)\n",Size);
        do { c=ConGetCh(); }
            while( c != 'y' && c !='Y' && c != 'N' && c != 'n' );
        if( c=='Y' || c=='y' )
            for( i=0; i<Size; i++ )
                ConPrintf( "%c", *(buffer+i) );

        ConPrintf("\n");
    }
    else if( rc < 0 )
    {
        ConPrintf("\nTFTP Reported Error: %d\n",rc);
        if( rc == TFTPERROR_ERRORREPLY )
            ConPrintf("TFTP Server Error: %d (%s)\n",ErrorCode,buffer);
    }

    mmFree( buffer );
}

