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
 * ======== pipe.c ========
 *
 * Object member functions for the Pipe device object.
 *
 */

#include <stkmain.h>

/*-------------------------------------------------------------------- */
/* PipeNew() */
/* Creates a pipe, consisting of two handles */
/*-------------------------------------------------------------------- */
int PipeNew( HANDLE *phPipe1, HANDLE *phPipe2 )
{
    PIPE   *pp1 = 0, *pp2 = 0;
    int    error = 0;

    /* Attempt to allocate space for both pipe ends */
    pp1 = mmAlloc(sizeof(PIPE));
    pp2 = mmAlloc(sizeof(PIPE));

    if( !pp1 || !pp2 )
    {
        NotifyLowResource();
        error = ENOMEM;
        goto pipenew_freehandle;
    }

    /* Initialize both pipe ends */
    mmZeroInit( pp1, sizeof(PIPE) );     /* Most Q's and counts init to Zero */
    mmZeroInit( pp2, sizeof(PIPE) );     /* Most Q's and counts init to Zero */
    pp1->fd.Type     = HTYPE_PIPE;
    pp2->fd.Type     = HTYPE_PIPE;
    pp1->fd.OpenCount = 1;
    pp2->fd.OpenCount = 1;
    pp1->pConnect = pp2;                /* 1 is connected to 2 */
    pp2->pConnect = pp1;                /* 2 is connected to 1 */
    pp1->TxSpace  = PIPE_BUFMINTX;      /* Space req to write to other end */
    pp2->TxSpace  = PIPE_BUFMINTX;      /* Space req to write to other end */

    pp1->hSBRx = SBNew( PIPE_BUFSIZE, PIPE_BUFMINRX, SB_MODE_LINEAR );
    pp2->hSBRx = SBNew( PIPE_BUFSIZE, PIPE_BUFMINRX, SB_MODE_LINEAR );

    if( !pp1->hSBRx || !pp2->hSBRx )
    {
        error = ENOMEM;
        goto pipenew_free;
    }

    *phPipe1 = (HANDLE)pp1;
    *phPipe2 = (HANDLE)pp2;

    return( error );

pipenew_free:
    /* Free whatever we allocated */
    if( pp1->hSBRx )
        SBFree( pp1->hSBRx );
    if( pp2->hSBRx )
        SBFree( pp2->hSBRx );

pipenew_freehandle:
    if( pp1 )
    {
        pp1->fd.Type = 0;
        mmFree( pp1 );
    }
    if( pp2 )
    {
        pp2->fd.Type = 0;
        mmFree( pp2 );
    }

    return( error );
}

/*-------------------------------------------------------------------- */
/* PipeClose() */
/* Close a pipe end */
/*-------------------------------------------------------------------- */
int PipeClose( HANDLE h )
{
    PIPE *pp = (PIPE *)h;

#ifdef _STRONG_CHECKING
    if( pp->fd.Type != HTYPE_PIPE )
    {
        DbgPrintf(DBG_ERROR,"PipeClose: HTYPE %04x",pp->fd.Type);
        return( EINVAL );
    }
#endif

    /* If still connected, disconnect */
    if( pp->pConnect )
    {
        pp->pConnect->pConnect = 0;
        /* We can event them now since their link to our side is broken */
        FdSignalEvent( pp->pConnect, FD_EVENT_READ );
        pp->pConnect = 0;
    }

    /* Free the Rx Buffer */
    if( pp->hSBRx )
        SBFree( pp->hSBRx );

    /* Free the pipe memory */
    pp->fd.Type = 0;
    mmFree( pp );

    return(0);
}

/*-------------------------------------------------------------------- */
/* PipeCheck() */
/* Check for pipe read/write/except status */
/*-------------------------------------------------------------------- */
int PipeCheck( HANDLE h, int IoType )
{
    PIPE *pp = (PIPE *)h;

#ifdef _STRONG_CHECKING
    if( pp->fd.Type != HTYPE_PIPE )
    {
        DbgPrintf(DBG_ERROR,"PipeCheck: HTYPE %04x",pp->fd.Type);
        return( 0 );
    }
#endif

    switch( IoType )
    {
    case PIPE_READ:
        /* Return TRUE if readable */
        if( SBGetTotal(pp->hSBRx) >= SBGetMin(pp->hSBRx) || !pp->pConnect )
            return(1);
        break;

    case PIPE_WRITE:
        /* Return TRUE if writeable */
        if( !pp->pConnect || SBGetSpace(pp->pConnect->hSBRx) >= pp->TxSpace )
            return(1);
        break;
    }
    return(0);
}

/*-------------------------------------------------------------------- */
/* PipeStatus() */
/* Return pipe read/write status */
/*-------------------------------------------------------------------- */
int PipeStatus( HANDLE h, int request, int *results )
{
    PIPE *pp = (PIPE *)h;

#ifdef _STRONG_CHECKING
    if( pp->fd.Type != HTYPE_PIPE )
    {
        DbgPrintf(DBG_ERROR,"PipeStatus: HTYPE %04x",pp->fd.Type);
        return( EINVAL );
    }
#endif

    if( request==FDSTATUS_RECV && results )
    {
        if( !pp->pConnect )
            *results = -1;
        else
            *results = SBGetTotal(pp->hSBRx);
    }
    else if( request==FDSTATUS_SEND && results )
    {
        if( !pp->pConnect )
            *results = -1;
        else
            *results = SBGetSpace(pp->pConnect->hSBRx);
    }
    else
        return( EINVAL );

    return(0);
}


/*-------------------------------------------------------------------- */
/* PipeRecv */
/* Receive data from a pipe. */
/*-------------------------------------------------------------------- */
int PipeRecv( HANDLE h, char *pBuf, INT32 size, int flags, INT32 *pRetSize )
{
    PIPE     *pp = (PIPE *)h;
    INT32    Total      = 0;
    INT32    SizeCopy   = 0;
    INT32    PeekOffset = 0;
    int      read_again = 1;
    int      error      = 0;

#ifdef _STRONG_CHECKING
    if( pp->fd.Type != HTYPE_PIPE )
    {
        DbgPrintf(DBG_ERROR,"PipeRecv: HTYPE %04x",pp->fd.Type);
        return( EINVAL );
    }
#endif

    /* Check for a null read */
    if( !size )
        goto rx_complete;

rx_restart:
    /* Get the total bytes available */
    Total = SBGetTotal(pp->hSBRx) - PeekOffset;

    /* Check for blocking condition */
    if( !Total )
    {
        /* Check all non-blocking conditions first */

        /* Set read_again to zero. If we break out of this */
        /* section without blocking, we don't read again */
        read_again = 0;

        /* Don't block if the pipe is no longer connected */
        if( !pp->pConnect )
        {
            error = ENOTCONN;
            goto rx_dontblock;
        }

        /* Don't block if there was an overriding request not to block */
        if( flags & MSG_DONTWAIT )
            goto rx_dontblock;

        /* Don't block if we have Rx'd the minimum */
        if( SizeCopy >= SBGetMin(pp->hSBRx) )
            goto rx_dontblock;

        /* Finally, the blocking code */

        /* If we get a file event, then try the loop again */
        if( FdWaitEvent( pp, FD_EVENT_READ, DEF_PIPE_TIMEIO*1000 ) )
        {
            read_again = 1;
            goto rx_restart;
        }
    }

rx_dontblock:
    /* Check for FATAL blocking condition */
    if( !Total && !SizeCopy )
    {
        if( !error )
            error = EWOULDBLOCK;
        return( error );
    }

    /* Get how much data to copy */

    /* Adjust to buffer size */
    if( size < (Total+SizeCopy) )
        Total = size-SizeCopy;

    if( Total )
    {
        if( flags & MSG_PEEK )
        {
            Total = SBRead( pp->hSBRx, Total, PeekOffset,
                            (UINT8 *)(pBuf+SizeCopy), 0, 0, 1 );
            PeekOffset += Total;
        }
        else
            Total = SBRead( pp->hSBRx, Total, 0,
                            (UINT8 *)(pBuf+SizeCopy), 0, 0, 0 );

        /* Record that we received this data */
        SizeCopy += Total;

        /* Notify the other side that we've read from our buffer */
        if( pp->pConnect )
            FdSignalEvent( pp->pConnect, FD_EVENT_WRITE );
    }

    /* Try and get all the data if possible */
    if( read_again && size > SizeCopy )
        goto rx_restart;

rx_complete:
    *pRetSize = SizeCopy;
    if( SizeCopy )
        return(0);
    return(error);
}

/*-------------------------------------------------------------------- */
/* PipeSend() */
/* Send data to a pipe. */
/*-------------------------------------------------------------------- */
int PipeSend( HANDLE h, char *pBuf, INT32 size, int flags, INT32 *pRetSize )
{
    PIPE     *pp = (PIPE *)h;
    int      error = 0;
    INT32    SizeCopy = 0;
    INT32    Space;
    INT32    ToCopy;

#ifdef _STRONG_CHECKING
    if( pp->fd.Type != HTYPE_PIPE )
    {
        DbgPrintf(DBG_ERROR,"PipeRecv: HTYPE %04x",pp->fd.Type);
        return( EINVAL );
    }
#endif

    while( SizeCopy < size )
    {
        /* Must be connected */
        if( !pp->pConnect )
        {
            error = ENOTCONN;
            break;
        }

        /* Append as much data as possible to connected end's buffer */
        ToCopy = size - SizeCopy;
        Space  = SBGetSpace( pp->pConnect->hSBRx );
        if( Space < ToCopy )
            ToCopy = Space;

        if( ToCopy )
        {
            /* Copy out the data and mark what we did copy */
            SizeCopy += SBWrite(pp->pConnect->hSBRx, ToCopy, pBuf+SizeCopy, 0);

            /* Notify connected end we wrote to its buffer */
            FdSignalEvent( pp->pConnect, FD_EVENT_READ );
        }

        /* Check blocking condition */
        if( SizeCopy < size && !ToCopy )
        {
            /* Don't block if DONTWAIT specified. */
            /* If we timeout, we have an error and break the loop */
            if( flags & MSG_DONTWAIT ||
                !FdWaitEvent( pp, FD_EVENT_WRITE, DEF_PIPE_TIMEIO*1000 ) )
            {
                error = EWOULDBLOCK;
                break;
            }
        }
    }

    *pRetSize = SizeCopy;
    return( error );
}

