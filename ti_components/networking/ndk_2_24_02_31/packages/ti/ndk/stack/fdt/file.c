/*
 * Copyright (c) 2012-2015, Texas Instruments Incorporated
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
 * ======== file.c ========
 *
 * File Management Functions
 *
 */

#include <stkmain.h>
#include "fdt.h"

/*-------------------------------------------------------------------- */
/* FdWaitEvent() */
/* Wait for a file event on the supplied FD handle with a timeout */
/* If timeout is NULL, function waits forever */
/* Returns 1 if the event was detected, or 0 on timeout */
/*-------------------------------------------------------------------- */
int FdWaitEvent( HANDLE hFd, UINT8 EventFlags, UINT32 timeout )
{
    FILEDESC *pfd  = (FILEDESC *)hFd;
    FDTABLE  *pfdt;
    int      index,event;

#ifdef _STRONG_CHECKING
     if( (pfd->Type != HTYPE_RAWETHSOCK) &&
#ifdef _INCLUDE_IPv6_CODE
        (pfd->Type != HTYPE_SOCK6) &&
#endif
        (pfd->Type != HTYPE_SOCK && pfd->Type != HTYPE_PIPE)
      )
    {
        DbgPrintf(DBG_ERROR,"FdWaitEvent: HTYPE %04x",pfd->Type);
        return(0);
    }
#endif

    /* The socket gave us the root FD in the share list, but it may not */
    /* be the FD actually owned by this task. Look for the FD owned by */
    /* the current task. */

    /* Get a pointer to the FD Table */
    pfdt = fdint_getfdt( 0 );

    /* If pointer is bad, we can't do a thing */
    if( !pfdt )
        return(0);

    /* Find an index to use */
    for( index=0; index<FDMAXSHARE && pfd->hFDTWait[index]; index++ );

    /* If the table is full, we can do anything */
    if( index == FDMAXSHARE )
        return(0);

    /* Don't allow the fd table to disappear while we sleep */
    pfdt->RefCount++;

    /* Use this slot */
    pfd->hFDTWait[index] = pfdt;
    pfd->EventFlags[index] = EventFlags;

    /* If there's no timeout, this will wait forever */
    /* Else wait for the time limit */
    event = fdint_waitevent( pfdt, timeout );

    /* Clear the slot */
    pfd->hFDTWait[index] = 0;

    /* If the fd table was deleted while we slept, we may need */
    /* to free it. */
    if( !--pfdt->RefCount )
        fdint_freefdt( pfdt );

    /* Return our event status */
    return(event);
}

/*-------------------------------------------------------------------- */
/* FdSignalEvent() */
/* Signal a file event on the supplied FD handle */
/*-------------------------------------------------------------------- */
void FdSignalEvent( HANDLE hFd, UINT8 EventFlags )
{
    FILEDESC *pfd  = (FILEDESC *)hFd;
    FDTABLE  *pfdt;
    int      index;

#ifdef _STRONG_CHECKING
     if( (pfd->Type != HTYPE_RAWETHSOCK) &&
#ifdef _INCLUDE_IPv6_CODE
        (pfd->Type != HTYPE_SOCK6) &&
#endif
        (pfd->Type != HTYPE_SOCK && pfd->Type != HTYPE_PIPE)
      )
    {
        DbgPrintf(DBG_ERROR,"FdSignalEvent: HTYPE %04x",pfd->Type);
        return;
    }
#endif

    /* Wake if conditions are right for all FD's in the chain */
    for( index=0; index<FDMAXSHARE; index++ )
    {
        if( pfd->hFDTWait[index] && (pfd->EventFlags[index] & EventFlags) )
        {
            pfdt = (FDTABLE *)pfd->hFDTWait[index];

            if( pfdt->Type == HTYPE_FDTABLE )
            {
                /* Wake the owning task */
                fdint_signalevent( pfdt );
            }
#ifdef _STRONG_CHECKING
            else
                DbgPrintf(DBG_ERROR,"FdSignalEvent: Bad pending FDT");
#endif
        }
    }
}

/*-------------------------------------------------------------------- */
/* fdint_signalevent() */
/* Signals a file event for the indicated table */
/*-------------------------------------------------------------------- */
void fdint_signalevent( FDTABLE *pfdt )
{
    pfdt->fEvented = 1;
    SemPost( pfdt->hSem );
}

/*-------------------------------------------------------------------- */
/* fdint_signaltimeout() */
/* Signals a file timeout for the indicated table */
/*-------------------------------------------------------------------- */
void fdint_signaltimeout( FDTABLE *pfdt )
{
    pfdt->fEvented = 0;
    SemPost( pfdt->hSem );
}

/*-------------------------------------------------------------------- */
/* fdint_waitevent() */
/* Wait for a file event with a timeout. If no timeout is specified, */
/* the function waits forever. */
/* Returns the evented status */
/*-------------------------------------------------------------------- */
int fdint_waitevent( FDTABLE *pfdt, UINT32 timeout )
{
    pfdt->fEvented = 0;
    SemReset( pfdt->hSem, 0 );

    /* Convert a timeout of 0 to forever */
    if( !timeout )
        timeout = SEM_FOREVER;

    /* Since this SemPend may block, we must exit and then */
    /* reenter the kernel mode */
    llExit();
    SemPend( pfdt->hSem, timeout );
    llEnter();

    if( pfdt->fEvented && !pfdt->fClosing )
        return( 1 );
    else
        return( 0 );
}

/*-------------------------------------------------------------------- */
/* fdint_getfdt() */
/* Returns a handle to File Descriptor Table. */
/* When called with NULL handle, the FDT for the current task is */
/* returned. */
/*-------------------------------------------------------------------- */
FDTABLE *fdint_getfdt( HANDLE hTask )
{
    FDTABLE *pfdt;
    if( !hTask )
        pfdt = TaskGetEnv( TaskSelf(), 0 );
    else
        pfdt = TaskGetEnv( hTask, 0 );

    if( !pfdt || pfdt->Type != HTYPE_FDTABLE )
    {
#ifdef _STRONG_CHECKING
        DbgPrintf(DBG_ERROR,"fdint_getfdt: Descriptor Error: Did you call fdOpenSession()?");
#endif
        return(0);
    }

    return( pfdt );
}

/*-------------------------------------------------------------------- */
/* fdint_lockfd() */
/* Validate fd table */
/* Validate fd */
/* Validate Type (0 = Either SOCK or PIPE) */
/* Validate fd is open */
/* Place any errors in the fd table */
/* Bump the fd lock count if no error */
/* Returns 0 or SOCKET_ERROR */
/*-------------------------------------------------------------------- */
int fdint_lockfd( FILEDESC *pfd, uint Type )
{
    FDTABLE *pfdt;

    /* Check the file descriptor table */
    pfdt = TaskGetEnv( TaskSelf(), 0 );
    if( !pfdt || pfdt->Type != HTYPE_FDTABLE )
        return( SOCKET_ERROR );

    /* Verify Socket and verify that it is open */
    if( !pfd ||
        (Type && pfd->Type != Type) ||
        ((pfd->Type != HTYPE_RAWETHSOCK) &&
#ifdef _INCLUDE_IPv6_CODE
        (pfd->Type != HTYPE_SOCK6) &&
#endif
        (pfd->Type != HTYPE_SOCK && pfd->Type != HTYPE_PIPE)
        ) || !pfd->OpenCount )
    {
        pfdt->error = EBADF;
        return( SOCKET_ERROR );
    }

    pfd->LockCount++;

    return(0);
}

/*-------------------------------------------------------------------- */
/* fdint_unlockfd() */
/* Place the supplied error into the fd table (if any) */
/* Decrement the fd lock count */
/* Close the fd if both lock count and open count are null */
/*-------------------------------------------------------------------- */
void fdint_unlockfd( FILEDESC *pfd, uint error )
{
    FDTABLE *pfdt;

    /* Decrement the lock count */
    pfd->LockCount--;

    /* See if the fd is closed */
    if( !pfd->OpenCount )
    {
        /* Alter the error code (if any) */
        if( error )
            error = EBADF;

        /* If the lock count is NULL, close the fd */
        if( !pfd->LockCount )
        {
            /* Close socket according to its type */
            /* Here we don't care about the return code from close */
            if( pfd->Type == HTYPE_SOCK )
                SockClose( pfd );
#ifdef _INCLUDE_IPv6_CODE            
            else if( pfd->Type == HTYPE_SOCK6 )
                Sock6Close( pfd );
#endif
            else if(pfd->Type == HTYPE_RAWETHSOCK)
                RawEthSockClose( pfd );
            else 
                PipeClose( pfd );
        }
    }

    /* Place any error in the file descriptor table */
    if( error && ((pfdt=fdint_getfdt(0)) != 0) )
        pfdt->error = error;
}

/*-------------------------------------------------------------------- */
/* fdint_freefdt() */
/* Frees a handle to File Descriptor Table. */
/* When called with NULL handle, the FDT for the current task is */
/* returned. */
/*-------------------------------------------------------------------- */
void fdint_freefdt( FDTABLE *pfdt )
{
    /* Kill type for debug */
    pfdt->Type = 0;

    /* Free the semaphore */
    SemDelete( pfdt->hSem );

    /* Free the table */
    mmFree( pfdt );
}

/*-------------------------------------------------------------------- */
/* fdint_setevent() */
/* Function to set socket wait event */
/*-------------------------------------------------------------------- */
int fdint_setevent( FDTABLE *pfdt, FILEDESC *pfd, UINT8 EventFlags )
{
    int index;

    /* Find an index to use */
    for( index=0; index<FDMAXSHARE && pfd->hFDTWait[index]; index++ );

    /* If no free entries, we're done */
    if( index == FDMAXSHARE )
    {
#ifdef _STRONG_CHECKING
        DbgPrintf(DBG_WARN,"fdint_setevent: Descriptor Sharing: Max use exceeded");
#endif
        return(0);
    }

    /* Use this slot */
    pfd->hFDTWait[index] = pfdt;
    pfd->EventFlags[index] = EventFlags;

    return(1);
}

/*-------------------------------------------------------------------- */
/* fdint_clearevent() */
/* Function to clear socket wait event */
/*-------------------------------------------------------------------- */
void fdint_clearevent( FDTABLE *pfdt, FILEDESC *pfd )
{
    int index;

    /* Find the index that this FDT used */
    for( index=0; index<FDMAXSHARE; index++ )
    {
        if( pfd->hFDTWait[index] == pfdt )
        {
            pfd->hFDTWait[index] = 0;
            return;
        }
    }
}
