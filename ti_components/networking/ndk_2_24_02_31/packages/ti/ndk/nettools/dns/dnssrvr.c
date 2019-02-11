/*
 * Copyright (c) 2014, Texas Instruments Incorporated
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
 * ======== dnssrvr.c ========
 *
 * DNS Server
 *
 */

#include "dns.h"

#define DNSMAXCONN      4


/* Data specific to a DNS Server Master Task */

typedef struct _dnsmaster {
        HANDLE          hTaskMaster;            /* DNSS task */
        HANDLE          hSemChild;              /* Connection/Child Semaphore */
        HANDLE          hSemPipe;               /* Connection/Child Semaphore */
        SOCKET          SockPrivate;            /* Private socket for master */
        HANDLE          fdPipePrivate;          /* Private pipe for master */
        HANDLE          fdPipe;                 /* Public end of pipe */
        IPN             IPAddr;                 /* Master IP Addr */
        char            *PktBuf;                /* Packet Buffer */
        HANDLE          hCb;                    /* Callback handle */
        void            (*pCb)(HANDLE,uint);    /* Status Function */
} DNSMASTER;


/* Data specific to a DNS Server Child Task */

typedef struct _dnschild {
        DNSMASTER          *pdm;                /* DNS Master */
        struct sockaddr_in from;                /* Who packet was from */
        char               *PktBuf;             /* Packet Data */
        int                PktSize;             /* Size of packet data */
} DNSCHILD;


/* Static Functions */

static void dnss( DNSMASTER *pdm );
static void dnss_task( DNSCHILD *pdc );
static void DNSSendReplyPacket( DNSCHILD *pdc, int size, UINT8 *pBuf );


/* DNSServerOpen */

/* Create an instance of the DNS Server */

HANDLE DNSServerOpen( NTARGS *pNTA )
{
    DNSMASTER *pdm;

    /* Alloc our instance structure */
    pdm = mmBulkAlloc( sizeof(DNSMASTER) );

    /* If the alloc failed, abort */
    if ( !pdm )
        return(0);

    /* Initialize the instance structure */
    bzero( pdm, sizeof(DNSMASTER) );

    /* Check for called by address */
    if( pNTA->CallMode == NT_MODE_IPADDR )
        pdm->IPAddr = pNTA->IPAddr;
    /* Check for called by IfIfx */
    else if( pNTA->CallMode == NT_MODE_IFIDX )
    {
        if( !NtIfIdx2Ip( pNTA->IfIdx, &pdm->IPAddr ) )
            goto Error;
    }
    else
        goto Error;

    /* Load callback parameters */
    pdm->hCb  = pNTA->hCallback;
    pdm->pCb  = pNTA->pCb;

    /* Create the "max connection" semaphore */
    pdm->hSemChild = SemCreate( DNSMAXCONN );
    if( !pdm->hSemChild )
        goto Error;

    /* Create the pipe semaphore */
    pdm->hSemPipe = SemCreate( 1 );
    if( !pdm->hSemPipe )
        goto Error2;

    /* Init the private pipe and socket variables */
    pdm->fdPipePrivate = INVALID_SOCKET;
    pdm->SockPrivate = INVALID_SOCKET;

    /* Create the DNS Server task */
    pdm->hTaskMaster = TaskCreate( &dnss, "DNSserver", OS_TASKPRINORM,
                                   OS_TASKSTKLOW, (UINT32)pdm, 0, 0 );

    if( !pdm->hTaskMaster )
    {
        SemDelete( pdm->hSemPipe );
Error2:
        SemDelete( pdm->hSemChild );
Error:
        mmBulkFree(pdm);
        return(0);
    }

    return( pdm );
}

/*
 * DNSServerClose
 *
 * Destroy an instance of the DNS Server
 */
void DNSServerClose( HANDLE h )
{
    DNSMASTER *pdm = (DNSMASTER *)h;
    int        i;

    /* Zap the master first */
    fdCloseSession( pdm->hTaskMaster );
    TaskDestroy( pdm->hTaskMaster );

    /* Close private end of the pipe if present */
    if( pdm->fdPipePrivate != INVALID_SOCKET )
        fdClose( pdm->fdPipePrivate );

    /* Close the private socket if we have one */
    if( pdm->SockPrivate != INVALID_SOCKET )
        fdClose( pdm->SockPrivate );

    /* We should be able to get the child semaphore */
    /* a total of DNSMAXCONN times. In other words, wait */
    /* for the children to complete or timeout */
    for( i=0; i<DNSMAXCONN; i++ )
        SemPend( pdm->hSemChild, SEM_FOREVER );

    /* Kill the rest */
    if( pdm->PktBuf )
        mmFree( pdm->PktBuf );
    if( pdm->fdPipe )
        fdClose( pdm->fdPipe );
    SemDelete( pdm->hSemPipe );
    SemDelete( pdm->hSemChild );
    mmBulkFree(pdm);
}

/*
 * dnss - DNS Server Master Task
 */
static void dnss( DNSMASTER *pdm )
{
    int                cc,tmp;
    struct sockaddr_in us;                      /* Who we are */
    struct sockaddr_in sin;
    DNSCHILD           *pdc;
    fd_set             ibits;

    fdOpenSession( TaskSelf() );

    /* Create master socket */
    pdm->SockPrivate = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if ( pdm->SockPrivate == INVALID_SOCKET )
        goto leave;

    bzero( &us, sizeof(struct sockaddr_in) );
    us.sin_family      = AF_INET;
    us.sin_addr.s_addr = pdm->IPAddr;
    us.sin_port        = htons(DNS_PORT);

    /* Bind  socket to DNS port */
    if( bind( pdm->SockPrivate, (struct sockaddr *) &us, sizeof(us) ) < 0 )
        goto leave;

    /* Allocate the Packet Buffer */
    if( !(pdm->PktBuf = mmAlloc( MAX_PACKET )) )
        goto leave;

    /* Create the outgoing packet pipe */
    if( pipe( &pdm->fdPipePrivate, &pdm->fdPipe ) != 0 )
        goto leave;

    /* Update status */
    if( pdm->pCb )
        (pdm->pCb)(pdm->hCb,NETTOOLS_STAT_RUNNING);

    /* Main Loop */
    for(;;)
    {
        /* Clear the select flags */
        FD_ZERO(&ibits);

        /* Look for input on the pipe or socket */
        FD_SET(pdm->SockPrivate, &ibits);
        FD_SET(pdm->fdPipePrivate, &ibits);

        /* Wait without timeout */
        if( fdSelect( 3, &ibits, 0, 0, 0 ) < 0 )
            goto leave;

        /* Check for new DNS packet */
        if( FD_ISSET(pdm->SockPrivate, &ibits) )
        {
            /* Get packet */
            tmp = sizeof(sin);
            cc = (int)recvfrom( pdm->SockPrivate, pdm->PktBuf,
                                MAX_PACKET, 0,(struct sockaddr *)&sin, &tmp );
            if( cc <= 0 )
                goto leave;

            /* Here we have a possible query in PktBuf */
            /* Check for available child. If not available, skip the question */
            if( SemPend( pdm->hSemChild, 0 ) )
            {
                /* If we can't allocate the child instance, skip it */
                if( (pdc = mmAlloc( sizeof(DNSCHILD) )) == 0 )
                    goto skip;

                /* Assign the child parameters */
                pdc->pdm     = pdm;
                pdc->from    = sin;
                pdc->PktBuf  = pdm->PktBuf;
                pdc->PktSize = cc;

                /* Now we must allocate a new PktBuf for the Master. If we */
                /* can't, take the old one back and skip this request */
                if( !(pdm->PktBuf = mmAlloc( MAX_PACKET )) )
                {
                    pdm->PktBuf = pdc->PktBuf;
                    mmFree( pdc );
                    goto skip;
                }

                /* Create a child task to service the question */
                /* If the create fails, post back our connection count */
                /* and free the child's stuff */
                if( !TaskCreate( &dnss_task, "DNSchild", OS_TASKPRINORM,
                                 1200, (UINT32)pdc, 0, 0 ) )
                {
                    mmFree( pdc->PktBuf );
                    mmFree( pdc );
skip:
                    SemPost( pdm->hSemChild );
                }
            }
        }

        /* Check for packet from child to send */
        if( FD_ISSET(pdm->fdPipePrivate, &ibits) )
        {
            /* Get the destination */
            if( recv( pdm->fdPipePrivate, &sin, sizeof(sin), 0 ) <= 0 )
                goto leave;

            /* Get the size */
            if( recv( pdm->fdPipePrivate, &cc, sizeof(int), 0 ) <= 0 )
                goto leave;

            /* Get the packet */
            if( recv( pdm->fdPipePrivate, pdm->PktBuf, cc, 0 ) <= 0 )
                goto leave;

            /* Send the packet */
            sendto( pdm->SockPrivate, pdm->PktBuf, cc, 0,(struct sockaddr *)&sin, sizeof(sin) );
        }
    }

leave:
    /* Close our end of the pipe if present */
    if( pdm->fdPipePrivate != INVALID_SOCKET )
    {
        fdClose( pdm->fdPipePrivate );
        pdm->fdPipePrivate = INVALID_SOCKET;
    }

    /* Close the socket if we have one */
    if( pdm->SockPrivate != INVALID_SOCKET )
    {
        fdClose( pdm->SockPrivate );
        pdm->SockPrivate = INVALID_SOCKET;
    }

    /* Update status */
    if( pdm->pCb )
        (pdm->pCb)(pdm->hCb,NETTOOLS_STAT_FAULT);

    /* We are destroyed by the system task, so here we block forever */
    TaskBlock( TaskSelf() );
}

/*
 *  dnss_task - DNS Server Child Task
 */
static void dnss_task( DNSCHILD *pdc )
{
    DNSREC      *pQuery,*pTemp;
    DNSREPLY    *pReply;
    int         NumQuery,cc;
    UINT16      Flags,Id;
    UINT16      ReqType;
    DNSHDR      *pDNS;
    UINT8       *pPacket;

    fdOpenSession( TaskSelf() );

    pDNS = (DNSHDR *)pdc->PktBuf;

    /* Get Flags and Id */
    Flags = htons( pDNS->Flags );
    Id    = htons( pDNS->Id );

    /* Make sure this is a DNS query */
    if( htons(pDNS->Flags) & FLG_DNS_QR )
        goto skipit;

    /* Get the request type */
    ReqType = Flags & MASK_DNS_OP;

    /* PktBuf holds a DNS question or questions. First, we'll */
    /* decode the questions into a linked list */

    /* Allocate the first Query Rec here */
    if( !(pQuery = mmAlloc(sizeof(DNSREC))) )
        goto skipit;

    /* Get a chain of query records */
    NumQuery = DNSGetQuery( pDNS, pQuery );

    /* If NumQuery is <= 0, we need to free the query record */
    if( NumQuery <= 0 )
        mmFree( pQuery );

    /* Now for each question, we get a reply */
    while( NumQuery > 0 )
    {
        /* Try and get an authoritative reply */
        if( DNSResolveQuery( ReqType, pQuery, &pReply ) )
        {
            pPacket = mmAlloc( MAX_PACKET );

            if( pPacket )
            {
                cc = DNSBuildReply( (DNSHDR *)pPacket, Id, pQuery, pReply );
                if( cc > 0 )
                    DNSSendReplyPacket( pdc, cc, pPacket);
                mmFree( pPacket );
            }

            /* Free the reply */
            DNSReplyFree( pReply, 1 );
        }

        /* Free the question */
        pTemp = pQuery;
        pQuery = pQuery->pNext;
        mmFree( pTemp );
        NumQuery--;
    }

skipit:
    /* Thread Shutdown */

    /* Post back a child instance */
    SemPost( pdc->pdm->hSemChild );

    /* Free packet buffer and instance */
    mmFree( pdc->PktBuf );
    mmFree( pdc );

    fdCloseSession( TaskSelf() );

    TaskExit();
}

/*-------------------------------------------------------------------- */
/* DNSSendReplyPacket() */
/* Send a UDP reply packet to the indicated destination */
/*-------------------------------------------------------------------- */
static void DNSSendReplyPacket( DNSCHILD *pdc, int size, UINT8 *pBuf )
{
    /* Note: We can't bind to the DNS port without risking pre-empting */
    /*       reception of our parent's DNS frames. Thus, we use a pipe */
    /*       to pipe the packet back to our parent. */

    /* Only one child can use pipe at a time */
    SemPend( pdc->pdm->hSemPipe, SEM_FOREVER );

    /* Send destination */
    send( pdc->pdm->fdPipe, &pdc->from, sizeof(SA), 0 );

    /* Send Size */
    send( pdc->pdm->fdPipe, &size, sizeof(int), 0 );

    /* Send packet */
    send( pdc->pdm->fdPipe, pBuf, size, 0 );

    /* Signal we're done */
    SemPost( pdc->pdm->hSemPipe );
}
