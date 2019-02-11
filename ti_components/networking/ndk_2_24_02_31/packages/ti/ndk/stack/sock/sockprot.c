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
 * ======== sockprot.c ========
 *
 * Object member functions for the Sock device object.
 *
 * These functions are protocol gateways called to perform
 * generic socket functions. They in turn call the actual
 * protocols.
 *
 *
 */

#include <stkmain.h>
#include "sock.h"

/*-------------------------------------------------------------------- */
/* SockPrAttach() */
/* Called to invoke protocol attach */
/*-------------------------------------------------------------------- */
int SockPrAttach( SOCK *ps )
{
    /* Should only be TCP, but make sure */
    if( ps->SockProt == SOCKPROT_TCP )
        return( TcpPrAttach( (HANDLE)ps, &ps->hTP ) );
    else
        return( SockPcbAttach( ps ) );
}

/*-------------------------------------------------------------------- */
/* SockPrDetach() */
/* Called to invoke protocol detach */
/*-------------------------------------------------------------------- */
int SockPrDetach( SOCK *ps )
{
    /* Should only be TCP, but make sure */
    if( ps->SockProt == SOCKPROT_TCP )
    {
        /* If we've already started the closing process, then this */
        /* is a hard drop - tell TCP to just free it and return. */
        /* Otherwise, TCP will try and tell the peer that we've */
        /* dropped the socket */
        if( ps->StateFlags & SS_CLOSING )
            return( TcpPrDetach( (HANDLE)ps, &ps->hTP, 1 ) );
        else
            return( TcpPrDetach( (HANDLE)ps, &ps->hTP, 0 ) );
    }
    else
        return( SockPcbDetach( ps ) );
}

const int Code2Err[] = { 0,            0,            0,            0,
                   0,            EMSGSIZE,     EHOSTDOWN,    EHOSTUNREACH,
                   EHOSTUNREACH, EHOSTUNREACH, ECONNREFUSED, ECONNREFUSED,
                   EMSGSIZE,     EHOSTUNREACH, 0,            0,
                   0,            0,            0,            0,
                   ENOPROTOOPT };

/*-------------------------------------------------------------------- */
/* SockPrCtlError() */
/* Called to notify socket of a problem */
/*-------------------------------------------------------------------- */
void SockPrCtlError( SOCK *ps, uint Code )
{
    if( ps->SockProt == SOCKPROT_TCP )
        TcpPrCtlError( ps, ps->hTP, Code, Code2Err[Code] );
    else if( ps->SockProt == SOCKPROT_UDP )
    {
        /* UDP is easy, just set the socket error */
        if( !ps->ErrorPending )
            ps->ErrorPending = Code2Err[Code];
    }
    return;
}

/* The TCP Only Functions can be #define'd */

#ifdef _STRONG_CHECKING
/*-------------------------------------------------------------------- */
/* SockPrRecv() */
/* Called to notify the protocol that data has been consumed */
/*-------------------------------------------------------------------- */
int SockPrRecv( SOCK *ps )
{
    if( ps->SockProt == SOCKPROT_TCP )
        return( TcpPrRecv( (HANDLE)ps, ps->hTP ) );
    else
        return( EINVAL );
}

/*-------------------------------------------------------------------- */
/* SockPrListen() */
/* Called to invoke protocol listen */
/*-------------------------------------------------------------------- */
int SockPrListen( SOCK *ps )
{
    /* Should only be TCP, but make sure */
    if( ps->SockProt == SOCKPROT_TCP )
        return( TcpPrListen( (HANDLE)ps, ps->hTP ) );
    else
        return( EINVAL );
}

/*-------------------------------------------------------------------- */
/* SockPrConnect() */
/* Called to invoke protocol connect request */
/*-------------------------------------------------------------------- */
int SockPrConnect( SOCK *ps )
{
    /* Should only be TCP, but make sure */
    if( ps->SockProt == SOCKPROT_TCP )
        return( TcpPrConnect( (HANDLE)ps, ps->hTP ) );
    else
        return( EINVAL );
}

/*-------------------------------------------------------------------- */
/* SockPrDisconnect() */
/* Called to invoke protocol disconnect request */
/*-------------------------------------------------------------------- */
int SockPrDisconnect( SOCK *ps )
{
    /* Should only be TCP, but make sure */
    if( ps->SockProt == SOCKPROT_TCP )
        return( TcpPrDisconnect( (HANDLE)ps, ps->hTP ) );
    else
        return( EINVAL );
}

/*-------------------------------------------------------------------- */
/* SockPrInherit() */
/* Called at spawn time so child can inherit parent options */
/*-------------------------------------------------------------------- */
void SockPrInherit( SOCK *psP, SOCK *psC )
{
    /* Should only be TCP, but make sure */
    if( psC->SockProt == SOCKPROT_TCP )
        TcpPrInherit( (HANDLE)psP, psP->hTP, (HANDLE)psC, psC->hTP );
}
#endif

