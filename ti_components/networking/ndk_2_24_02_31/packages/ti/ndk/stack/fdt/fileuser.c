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
 * ======== fileuser.c ========
 *
 * User Callable File Management Functions
 *
 * Note: User functions are callable without the llEnter()/llExit()
 *       retrictions placed on stack functions.
 *
 */

#include <stkmain.h>
#include "fdt.h"

/*-------------------------------------------------------------------- */
/* fdsetRemoveEntry()      (fd_set Utility Function) */
/* Abort out of a select call */
/*-------------------------------------------------------------------- */
void fdsetRemoveEntry( fd_set *pSet, HANDLE hEntry )
{
    int i;

    for( i=0; i<pSet->count; i++ )
    {
        if( pSet->fd[i] == hEntry )
        {
            pSet->count--;
            if( i < pSet->count )
                mmCopy( &(pSet->fd[i]), &(pSet->fd[i+1]),
                        ((pSet->count)-i)*sizeof(HANDLE) );
            i = -1;
            continue;
        }
    }
}

/*-------------------------------------------------------------------- */
/* fdsetTestEntry()      (fd_set Utility Function) */
/* Abort out of a select call */
/*-------------------------------------------------------------------- */
uint fdsetTestEntry( fd_set *pSet, HANDLE hEntry )
{
    int i;

    for( i=0; i<pSet->count; i++ )
        if( pSet->fd[i] == hEntry )
            return(1);

    return(0);
}

/*-------------------------------------------------------------------- */
/* fdOpenSession()      (USER FUNCTION) */
/* Create a new file descriptor table for the supplied task */
/* Returns 1 on success, or 0 on failure */
/*-------------------------------------------------------------------- */
int fdOpenSession( HANDLE hOwner )
{
    FDTABLE *pfdt;

    if( TaskGetEnv( hOwner, 0 ) )
        return(0);

    llEnter();

    /* Allocate the FDT */
    if( !(pfdt = mmAlloc(sizeof(FDTABLE))) )
    {
        DbgPrintf(DBG_WARN,"fdOpenSession: OOM");
        NotifyLowResource();
        llExit();
        return(0);
    }

    /* Clear table */
    mmZeroInit( pfdt, sizeof(FDTABLE) );

    /* Initialize type */
    pfdt->Type = HTYPE_FDTABLE;
    pfdt->RefCount = 1;

    /* Allocate the semaphore to be used for file events */
    if( !(pfdt->hSem = SemCreate( 0 )) )
    {
        mmFree( pfdt );
        llExit();
        return(0);
    }

    /* The setenv() function is used to track the association */
    /* between task threads and fd tables. */
    TaskSetEnv( hOwner, 0, pfdt );

    llExit();

    return(1);
}

/*-------------------------------------------------------------------- */
/* fdCloseSession()     (USER FUNCTION) */
/* Free a file descriptor table */
/*-------------------------------------------------------------------- */
void fdCloseSession( HANDLE hTask )
{
    FDTABLE *pfdt;

    llEnter();

    pfdt = fdint_getfdt( hTask );

    /* If the pointer is NULL, the session may already be closed */
    if(!pfdt)
    {
        llExit();
        return;
    }

    /* fClosing will prevent the table from being accessed again */
    pfdt->fClosing = 1;

    if( hTask != TaskSelf() )
    {
        /* Not closing our own session. Signal the session */
        /* to allow the owner to exit gracefully */
        fdint_signaltimeout( pfdt );
    }

    /* Now clear the fdt out of the environment pointer */
    TaskSetEnv(hTask, 0, 0);

    /* If not in use, free the fd table */
    if( !--pfdt->RefCount )
        fdint_freefdt( pfdt );

    llExit();
}

/*-------------------------------------------------------------------- */
/* fdError()     (USER FUNCTION) */
/* Returns the File Operation Error associated with a task */
/*-------------------------------------------------------------------- */
int fdError()
{
    FDTABLE *pfdt;
    int     error;

    llEnter();
    pfdt = fdint_getfdt( 0 );
    if(!pfdt)
        error = SOCKET_ERROR;
    else
        error = pfdt->error;
    llExit();

    return( error );
}

/*-------------------------------------------------------------------- */
/* fdClose()      (USER FUNCTION) */
/* Remove a reference / Close a file descriptor */
/*-------------------------------------------------------------------- */
int fdClose( HANDLE hFd )
{
    FILEDESC *pfd = (FILEDESC *)hFd;
    FDTABLE  *pfdt;
    int      index,error = 0;

    llEnter();

    if( !pfd || (pfd->Type != HTYPE_SOCK && pfd->Type != HTYPE_PIPE &&
#ifdef _INCLUDE_IPv6_CODE
        pfd->Type != HTYPE_SOCK6 &&
#endif
        pfd->Type != HTYPE_RAWETHSOCK || !pfd->OpenCount ))
    {
        error = EBADF;
        goto close_error;
    }

    /* Remove one open reference */
    pfd->OpenCount--;

    /* If open references are null, start the close process */
    if( !pfd->OpenCount )
    {
        /* If the descriptor is locked, signal timeouts to all */
        if( pfd->LockCount )
        {
            for( index=0; index<FDMAXSHARE; index++ )
            {
                if( pfd->hFDTWait[index] )
                    fdint_signaltimeout((FDTABLE *)(pfd->hFDTWait[index]));
            }
        }
        /* Else close the descriptor now */
        else
        {
            /* Close socket according to its type */
            if( pfd->Type == HTYPE_SOCK )
                error = SockClose( pfd );
#ifdef _INCLUDE_IPv6_CODE
            else if( pfd->Type == HTYPE_SOCK6 )
                error = Sock6Close( pfd );
#endif
            else if( pfd->Type == HTYPE_RAWETHSOCK )
                error = RawEthSockClose( pfd );
            else
                error = PipeClose( pfd );
        }
    }

    if( !error )
    {
        llExit();
        return( 0 );
    }

close_error:
    /* There's been an error. Save it if there's a socket session */
    if( (pfdt=fdint_getfdt(0)) != 0 )
        pfdt->error = error;

    llExit();
    return( SOCKET_ERROR );
}

/*-------------------------------------------------------------------- */
/* fdStatus()      (USER FUNCTION) */
/* Called to get the status of a file descriptor */
/*-------------------------------------------------------------------- */
int fdStatus( HANDLE fd, int request, int *presults )
{
    FILEDESC *pfd = (FILEDESC *)fd;
    FDTABLE  *pfdt;
    int      error = 0;
    int      results = 0;

    llEnter();

    if( !pfd || (pfd->Type != HTYPE_SOCK && pfd->Type != HTYPE_PIPE &&
#ifdef _INCLUDE_IPv6_CODE
        pfd->Type != HTYPE_SOCK6 &&
#endif
        pfd->Type != HTYPE_RAWETHSOCK || !pfd->OpenCount ))
    {
        error = EBADF;
        goto status_error;
    }



    if( pfd->Type == HTYPE_SOCK )
    {
        if( request == FDSTATUS_TYPE )
            results = FDSTATUS_TYPE_SOCKET;
        else if( request == FDSTATUS_RECV || request == FDSTATUS_SEND )
            error = SockStatus( pfd, request, &results );
        else
            error = EINVAL;
    }
#ifdef _INCLUDE_IPv6_CODE
    else if( pfd->Type == HTYPE_SOCK6 )
    {
        if( request == FDSTATUS_TYPE )
            results = FDSTATUS_TYPE_SOCKET;
        else if( request == FDSTATUS_RECV || request == FDSTATUS_SEND )
            error = Sock6Status( pfd, request, &results );
        else
            error = EINVAL;
    }
#endif
    else if( pfd->Type == HTYPE_RAWETHSOCK )
    {
        if( request == FDSTATUS_TYPE )
            results = FDSTATUS_TYPE_SOCKET;
        else if( request == FDSTATUS_RECV || request == FDSTATUS_SEND )
            error = RawEthSockStatus( pfd, request, &results );
        else
            error = EINVAL;
    }
    else
    {
        if( request == FDSTATUS_TYPE )
            results = FDSTATUS_TYPE_PIPE;
        else if( request == FDSTATUS_RECV || request == FDSTATUS_SEND )
            error = PipeStatus( pfd, request, &results );
        else
            error = EINVAL;
    }

    if( !error )
    {
        llExit();
        if( presults )
            *presults = results;
        return(0);
    }

status_error:
    /* There's been an error. Save it if there's a socket session */
    if( (pfdt=fdint_getfdt(0)) != 0 )
        pfdt->error = error;

    llExit();
    return( SOCKET_ERROR );
}


/*-------------------------------------------------------------------- */
/* fdShare()      (USER FUNCTION) */
/* Add a reference to a file descriptor */
/*-------------------------------------------------------------------- */
int fdShare( HANDLE fd )
{
    FILEDESC *pfd = (FILEDESC *)fd;
    FDTABLE  *pfdt;

    llEnter();

    if( !pfd || (pfd->Type != HTYPE_SOCK && pfd->Type != HTYPE_PIPE &&
#ifdef _INCLUDE_IPv6_CODE
        pfd->Type != HTYPE_SOCK6 &&
#endif
        pfd->Type != HTYPE_RAWETHSOCK || !pfd->OpenCount ))
    {
        if( (pfdt=fdint_getfdt(0)) != 0 )
            pfdt->error = EBADF;
        llExit();
        return( SOCKET_ERROR );
    }

    pfd->OpenCount++;

    llExit();

    return( 0 );
}

/*-------------------------------------------------------------------- */
/* fdSelectAbort()      (USER FUNCTION) */
/* Abort out of a select call */
/*-------------------------------------------------------------------- */
void fdSelectAbort( HANDLE hTask )
{
    FDTABLE  *pfdt;

    llEnter();

    pfdt = fdint_getfdt( hTask );
    if( pfdt )
    {
        pfdt->fAbortPoll = 1;
        fdint_signaltimeout( pfdt );
    }

    llExit();
}


/* Verify #define assumptions */
#if POLLIN != FD_EVENT_READ
#error Bad define on POLLIN
#endif
#if POLLOUT != FD_EVENT_WRITE
#error Bad define on POLLOUT
#endif
#if POLLPRI != FD_EVENT_EXCEPT
#error Bad define on POLLPRI
#endif
#if POLLNVAL != FD_EVENT_INVALID
#error Bad define on POLLNVAL
#endif

/*-------------------------------------------------------------------- */
/* fdPoll()     (USER FUNCTION) */
/* Selects on a file descriptor list. */
/* items[] - File Descriptor items to test */
/* itemcnt - Number of items in the list */
/* timeout - Timeout in MS, or POLLINFTIM for no timeout */
/*-------------------------------------------------------------------- */
int fdPoll( FDPOLLITEM items[], uint itemcnt, INT32 timeout )
{
    FDTABLE  *pfdt;
    FILEDESC *pfd;
    uint     num_fd,cantblock,i,evented;
    UINT32   tval;
    UINT8    tmp8;

    llEnter();

    /* Verify Task */
    if( !(pfdt = fdint_getfdt( 0 )) )
    {
        llExit();
        return( SOCKET_ERROR );
    }

    /* Make sure the args are good */
    if( itemcnt && !items )
    {
        pfdt->error = EINVAL;
        llExit();
        return( SOCKET_ERROR );
    }

    /* Convert timeout to our format in tval */
    if( timeout == POLLINFTIM )
        tval = 0;
    else
        tval = timeout;

    /* Start Select Loop */
retry:
    /* Set the initial count */
    num_fd = 0;

    /* Test all the descriptors in the list for activity */
    for(i=0; i<itemcnt; i++)
    {
        pfd = (FILEDESC *)items[i].fd;

        items[i].eventsDetected = 0;

        if( pfd!=INVALID_SOCKET && items[i].eventsRequested )
        {
            /* Make sure the fd is valid */
            if( !pfd || !pfd->OpenCount ||
                (pfd->Type != HTYPE_SOCK &&  pfd->Type != HTYPE_PIPE &&
#ifdef _INCLUDE_IPv6_CODE
                 pfd->Type != HTYPE_SOCK6 &&
#endif
                 pfd->Type != HTYPE_RAWETHSOCK) )
            {
                 items[i].eventsDetected |= POLLNVAL;
            }
            /* Else check for socket type */
            else if( pfd->Type == HTYPE_SOCK )
            {
                if( (items[i].eventsRequested & POLLIN) &&
                                                SockCheck(pfd, SOCK_READ) )
                    items[i].eventsDetected |= POLLIN;
                if( (items[i].eventsRequested & POLLOUT) &&
                                                SockCheck(pfd, SOCK_WRITE) )
                    items[i].eventsDetected |= POLLOUT;
                if( items[i].eventsRequested & POLLPRI &&
                                                SockCheck(pfd, SOCK_EXCEPT) )
                    items[i].eventsDetected |= POLLPRI;
            }
#ifdef _INCLUDE_IPv6_CODE
            /* Else check for IPV6 socket type */
            else if( pfd->Type == HTYPE_SOCK6 )
            {
                if( (items[i].eventsRequested & POLLIN) &&
                                                Sock6Check(pfd, SOCK_READ) )
                    items[i].eventsDetected |= POLLIN;
                if( (items[i].eventsRequested & POLLOUT) &&
                                                Sock6Check(pfd, SOCK_WRITE) )
                    items[i].eventsDetected |= POLLOUT;
                if( items[i].eventsRequested & POLLPRI &&
                                                Sock6Check(pfd, SOCK_EXCEPT) )
                    items[i].eventsDetected |= POLLPRI;
            }
#endif
            /* Else check for Raw ethernet socket type */
            else if( pfd->Type == HTYPE_RAWETHSOCK )
            {
                if( (items[i].eventsRequested & POLLIN) &&
                                                RawEthSockCheck(pfd, SOCK_READ) )
                    items[i].eventsDetected |= POLLIN;
                if( (items[i].eventsRequested & POLLOUT) &&
                                                RawEthSockCheck(pfd, SOCK_WRITE) )
                    items[i].eventsDetected |= POLLOUT;
                if( items[i].eventsRequested & POLLPRI &&
                                                RawEthSockCheck(pfd, SOCK_EXCEPT) )
                    items[i].eventsDetected |= POLLPRI;
            }
            /* else must be pipe type */
            else
            {
                if( (items[i].eventsRequested & POLLIN) &&
                                                PipeCheck(pfd, PIPE_READ) )
                    items[i].eventsDetected |= POLLIN;
                if( (items[i].eventsRequested & POLLOUT) &&
                                                PipeCheck(pfd, PIPE_WRITE) )
                    items[i].eventsDetected |= POLLOUT;
                if( items[i].eventsRequested & POLLPRI )
                    items[i].eventsDetected |= POLLNVAL;
            }

            if( items[i].eventsDetected )
                num_fd++;
        }
    }

    /* If we detected some events or have no timeout, return now */
    if( num_fd || !timeout )
    {
        /* Clear any pending fdSelectAbort() */
        pfdt->fAbortPoll = 0;

        /* Return results */
        llExit();
        return(num_fd);
    }

    /* Don't allow the fd table to disappear during this process */
    pfdt->RefCount++;

    /* If a select abort is pending, don't bother installing events */
    if( pfdt->fAbortPoll )
    {
        cantblock = 1;
        itemcnt = 0;
    }
    else
    {
        /* Install blocking events and locks for each fd */
        /* Note: We know that all fd's are valid because we didn't */
        /* detect any invalid fd's in the first loop. */
        cantblock = 0;
        for(i=0; i<itemcnt; i++)
        {
            pfd = (FILEDESC *)items[i].fd;

            if( pfd!=INVALID_SOCKET &&
                (tmp8=(items[i].eventsRequested & (POLLIN|POLLOUT|POLLPRI))) )
            {
                /* Bump the lock count */
                pfd->LockCount++;

                /* Install the event - flag if we can't block */
                if( !fdint_setevent(pfdt, pfd, tmp8) )
                    cantblock = 1;
            }
        }
    }

    /* Sleep the task with our "wait time" */
    if( !cantblock )
        evented = fdint_waitevent( pfdt, tval );
    else
        evented = 0;

    /* In case we were aborted, reset abort flag now */
    pfdt->fAbortPoll = 0;

    /* Cleanup blocking events and locks */
    for(i=0; i<itemcnt; i++)
    {
        pfd = (FILEDESC *)items[i].fd;

        if( pfd!=INVALID_SOCKET &&
            (items[i].eventsRequested & (POLLIN|POLLOUT|POLLPRI)) )
        {
            /* Clear the event */
            fdint_clearevent( pfdt, pfd );

            /* Decrement the lock count */
            pfd->LockCount--;

            /* See if the fd is closed */
            if( !pfd->OpenCount )
            {
                /* Mark the entry as invalid */
                items[i].eventsDetected = POLLNVAL;
                num_fd++;

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
                    else if( pfd->Type == HTYPE_RAWETHSOCK )
                        RawEthSockClose( pfd );
                    else
                        PipeClose( pfd );
                }
            }
        }
    }

    /* See if we must delete the fd table */
    if( !--pfdt->RefCount )
    {
        fdint_freefdt( pfdt );
        llExit();
        return(SOCKET_ERROR);
    }

    /* Return a fatal error if our socket session is closed */
    if( pfdt->fClosing )
    {
        llExit();
        return(SOCKET_ERROR);
    }

    /* If we couldn't block or there was a timeout, return now */
    /* Also, if a socket was closed while we slept, we bumped num_fd */
    if( !evented || num_fd )
    {
        llExit();
        return(num_fd);
    }

    goto retry;
}


/*-------------------------------------------------------------------- */
/* fdSelect()     (USER FUNCTION) */
/* Selects on a file descriptor. Returns the number of descriptor */
/* bits set. */
/*-------------------------------------------------------------------- */
int fdSelect( int maxfd, fd_set *readfds, fd_set *writefds,
                         fd_set *exceptfds, struct timeval *timeout )
{
    FDTABLE     *pfdt;
    INT32       tval;
    FDPOLLITEM  *ppi;
    int         num_fd,i,ppiCnt;

    (void)maxfd;

    /* Convert timeout value in "timeout" to time in milliseconds used by poll */
    if( !timeout )
        tval = POLLINFTIM;
    else
    {
        tval = (UINT32)timeout->tv_sec * 1000;
        tval += (UINT32)((timeout->tv_usec+999)/1000);
        if( tval < 0 )
            tval = 0x7FFFFFFF;
    }

    /* Convert the FD_SETs to a fdPoll() list and call fdPoll() */

    /* Count how big a list we'll need */
    num_fd = 0;
    if( readfds )
        num_fd += readfds->count;
    if( writefds )
        num_fd += writefds->count;
    if( exceptfds )
        num_fd += exceptfds->count;

    /* If no descriptors, pass the NULL set to fdPoll */
    if( !num_fd )
        return( fdPoll(0,0,tval) );

    /* Allocate the list */
    i = sizeof(FDPOLLITEM) * num_fd;
    ppi = mmAlloc( i );
    if( !ppi )
    {
        if( (pfdt=fdint_getfdt(0)) != 0 )
             pfdt->error = ENOMEM;
        return( -1 );
    }
    mmZeroInit( ppi, i );

    /* Populate the list based on what was supplied in the FD sets */
    ppiCnt = 0;
    if( readfds )
    {
        for( i=0; i<readfds->count; i++ )
        {
            (ppi+ppiCnt)->fd = readfds->fd[i];
            (ppi+ppiCnt)->eventsRequested = POLLIN;
            ppiCnt++;
        }
        FD_ZERO( readfds );
    }
    if( writefds )
    {
        for( i=0; i<writefds->count; i++ )
        {
            (ppi+ppiCnt)->fd = writefds->fd[i];
            (ppi+ppiCnt)->eventsRequested = POLLOUT;
            ppiCnt++;
        }
        FD_ZERO( writefds );
    }
    if( exceptfds )
    {
        for( i=0; i<exceptfds->count; i++ )
        {
            (ppi+ppiCnt)->fd = exceptfds->fd[i];
            (ppi+ppiCnt)->eventsRequested = POLLPRI;
            ppiCnt++;
        }
        FD_ZERO( exceptfds );
    }

    /* Call poll */
    num_fd = fdPoll( ppi, ppiCnt, tval );

    /* Read the results back into the caller's FD sets */
    if( num_fd > 0 )
    {
        for( i=0; i<ppiCnt; i++ )
        {
            if( (ppi+i)->eventsDetected )
            {
                if( (ppi+i)->eventsDetected & POLLNVAL )
                {
                    if( (pfdt=fdint_getfdt(0)) != 0 )
                         pfdt->error = EBADF;
                    num_fd = SOCKET_ERROR;
                    break;
                }
                if( readfds && ((ppi+i)->eventsDetected & POLLIN) )
                    FD_SET( (ppi+i)->fd, readfds );
                if( writefds && ((ppi+i)->eventsDetected & POLLOUT) )
                    FD_SET( (ppi+i)->fd, writefds );
                if( exceptfds && ((ppi+i)->eventsDetected & POLLPRI) )
                    FD_SET( (ppi+i)->fd, exceptfds );
            }
        }
    }

    /* Free the fdPoll() list we allocated earlier */
    mmFree( ppi );

    /* return */
    return( num_fd );
}

