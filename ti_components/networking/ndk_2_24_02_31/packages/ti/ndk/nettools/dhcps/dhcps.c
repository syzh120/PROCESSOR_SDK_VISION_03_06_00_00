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
 * ======== dhcps.c ========
 *
 * Simple DHCP Server Utility
 *
 */

#include "dhcps.h"

#define BUFFER_LENGTH           1024
#define TAGBUF_LENGTH           32
#define EXPIRATION_TIME         (86400 * 7)   /* 7 Days */
#define TEMPREC_TIME            (3600 * 4)    /* 4 Hours */
#define MAX_OPTION_SIZE         312
#define DHCP_RECORD             CI_CLIENT

/* DHCP Instance */
typedef struct _dhcpsrv {
        HANDLE             hTask;         /* Handle to server task */
        HANDLE             hIF;           /* Handle to target IF */
        HANDLE             hCb;           /* Callback handle */
        void (*pCb)(HANDLE,uint);         /* Callback function */
        uint               IfIdx;         /* Interface Index */
        IPN                IPServer;      /* Server's IP address */
        IPN                IPMask;        /* Subnet mask */
        IPN                IPNameServer;  /* DNS to report to client (or NULL) */
        UINT32             PoolSize;      /* Number of addrs in pool */
        UINT32             PoolBase;      /* Addr base */
        DHCP_RECORD        ipr;           /* Current IP Record */
        HANDLE             hIPR;          /* Handle to the IPR we're holding */

        /* Socket state variables */

        SOCKET             s;
        struct sockaddr_in sin1;
        int                size;
        int                DomainLength;
        UINT8              DomainName[CFG_DOMAIN_MAX];
        char               buf[BUFFER_LENGTH];
        int                tagsize;
        char               tags[TAGBUF_LENGTH];
        } DHCPSRV;

/* DHCPS Main Thread */
static void dhcpsMain( DHCPSRV *pDS );

/* DHCP IP Address Entry Record Functions */
#define IPR_MODE_FIND          1        /* Find Only */
#define IPR_MODE_CREATE        2        /* Create entry if not found */
#define IPR_MODE_CREATEFIXED   3        /* Create entry only if IP available */

static int  iprMacCmp( UINT8 *pMAC1, UINT8 *pMAC2 );
static void iprSync( DHCPSRV *pDS );
static int  iprGetByIndex( DHCPSRV *pDS, uint Index );
static int  iprNew( DHCPSRV *pDS, uint mode, IPN IPReqAddr, UINT8 *pMAC );
static void iprRemove( DHCPSRV *pDS );
static void iprUpdate( DHCPSRV *pDS, uint Status );
static void iprTimeoutCheck( DHCPSRV *pDS );
static int  iprFindByIP( DHCPSRV *pDS, IPN IPReqAddr );
static int  iprFindByMAC( DHCPSRV *pDS, UINT8 *pMAC );


/* DHCP Server Packet Processing Functions */
static void ProcessMain( DHCPSRV *pDS );
static void SendDHCPReply(DHCPSRV *pDS, IPN IPAddr, UINT8 Message, uint flags);
#define SENDFLG_LEASETIME       1

/*---------------------------------------------------------------- */
/* DHCPSOpen() */

/* This function is called to initiate DHCPS control of the IP */
/* subnet on a given device. The base address does not have to be the */
/* base addr of the subnet (as defined by the mask). */

/* Returns a HANDLE to a DHCPS instance structure which is used in */
/* calls to other DHCPS functions like DHCPSClose(). */
/*---------------------------------------------------------------- */
HANDLE DHCPSOpen( NTARGS *pNTA, NTPARAM_DHCPS *pNTP )
{
    DHCPSRV  *pDS;
    CI_IPNET ci_net;
    int      i,rc;

    /* We only support IFIDX calling mode */
    if( pNTA->CallMode != NT_MODE_IFIDX )
        return(0);

    /* Allocate Instance */
    pDS = mmBulkAlloc( sizeof(DHCPSRV) );
    if( !pDS )
        return(0);

    /* Initialize Instance */
    bzero( pDS, sizeof( DHCPSRV ) );

    /* Get the HANDLE to the interface */
    pDS->IfIdx = pNTA->IfIdx;

    {
        NIMU_IF_REQ ifreq;

        /* Initialize the NIMU Interface Object. */
        mmZeroInit (&ifreq, sizeof(NIMU_IF_REQ));

        /*
         *  We are interested in receiving the handle associated with 'index'
         *  Item
         */
        ifreq.index = pDS->IfIdx;
        if (NIMUIoctl(NIMU_GET_DEVICE_HANDLE, &ifreq, (void *)&pDS->hIF,
                sizeof(HANDLE)) < 0)
            goto error_abort;
    }

    /* Search CFG for network with DHCPS flag set */
    i = 1;
    while(i)
    {
        rc = CfgGetImmediate( 0, CFGTAG_IPNET, pNTA->IfIdx, i,
                              sizeof(ci_net), (UINT8 *)&ci_net );
        if( rc <= 0 )
            goto error_abort;

        if( ci_net.NetType & CFG_NETTYPE_DHCPS )
            break;

        i++;
    }

    /* Get the server IP and the mask */
    pDS->IPServer = ci_net.IPAddr;
    pDS->IPMask   = ci_net.IPMask;

    /* Record the IP of the local name server if we're to use it */
    if( pNTP->Flags & DHCPS_FLG_LOCALDNS )
        pDS->IPNameServer = pDS->IPServer;

    /* Copy the domain name if in VIRTUAL mode else get the public */
    /* domain name. */
    if( pNTP->Flags & DHCPS_FLG_LOCALDOMAIN )
        strcpy( (char *)(pDS->DomainName), ci_net.Domain );
    else
        NtGetPublicHost( 0, CFG_DOMAIN_MAX, pDS->DomainName );
    pDS->DomainLength = strlen( (char *)(pDS->DomainName) );

    /* Save the Callback Information */
    pDS->hCb = pNTA->hCallback;
    pDS->pCb = pNTA->pCb;

    /* Convert optional pool to host format */
    pDS->PoolBase   = htonl( pNTP->PoolBase );
    pDS->PoolSize   = pNTP->PoolCount;

    /* Verify server address can serve the supplied pool */
    if( pDS->IPServer && pNTP->PoolBase )
        if( (pDS->IPServer & pDS->IPMask) != (pNTP->PoolBase & pDS->IPMask) )
            goto error_abort;

    /* Init the socket value */
    pDS->s = INVALID_SOCKET;

    /* Create the DHCPS task */
    pDS->hTask = TaskCreate( (void(*)())dhcpsMain, "DHCPserver",
                             OS_TASKPRINORM, OS_TASKSTKLOW,
                             (UINT32)pDS, 0, 0 );

    if( !pDS->hTask )
        goto error_abort;

    /* Return the handle to our instance */
    return( pDS );

error_abort:
    mmBulkFree( pDS );
    return(0);
}

/*---------------------------------------------------------------- */
/* DHCPSClose() */

/* This function terminates DHCPS control and free the supplied */
/* instance handle. */
/*---------------------------------------------------------------- */
void DHCPSClose( HANDLE hDHCPS )
{
    DHCPSRV     *pDS = (DHCPSRV *)hDHCPS;

    /* Kill the server task */
    if( pDS->hTask )
    {
        fdCloseSession( pDS->hTask );
        TaskDestroy( pDS->hTask );
    }

    /* Close the socket */
    if( pDS->s != INVALID_SOCKET )
        fdClose( pDS->s );

    /* Free any held record */
    iprSync( pDS );

    /* Free the instance */
    mmBulkFree( pDS );
}

/*---------------------------------------------------------------- */
/* dhcpsMain() */

/* This routine listens for packets and processes requests */
/*---------------------------------------------------------------- */
static void dhcpsMain( DHCPSRV *pDS )
{
    int tmp;

    fdOpenSession( TaskSelf() );

    /* Create the main socket */
    pDS->s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if( pDS->s == INVALID_SOCKET )
        goto leave;

    /* Bind to the DHCP Server port */
    bzero( &pDS->sin1, sizeof(struct sockaddr_in) );
    pDS->sin1.sin_family      = AF_INET;
    pDS->sin1.sin_addr.s_addr = 0;
    pDS->sin1.sin_port        = htons(NDHCPS);

    if( bind( pDS->s, (PSA)&pDS->sin1, sizeof( pDS->sin1 ) ) < 0 )
        goto leave;

    /* Set socket option to allow us to broadcast */
    tmp = 1;
    if( setsockopt( pDS->s, SOL_SOCKET, SO_BROADCAST, &tmp, sizeof(int) ) )
        goto leave;

    /* Set socket option to specifiy packet broadcast device */
    /* The SO_IFDEVICE option is specific to this stack. */
    if( setsockopt( pDS->s, SOL_SOCKET, SO_IFDEVICE, &pDS->IfIdx, sizeof(uint) ) )
        goto leave;

    /* Inform that all is well with the world */
    if( pDS->pCb )
        (*pDS->pCb)( pDS->hCb, NETTOOLS_STAT_RUNNING );

    /* Listen for incoming requests */
    /* Run until task is destroyed by the system */
    for(;;)
    {
        fd_set ibits;

        /* Initialize the select flags */
        FD_ZERO(&ibits);
        FD_SET(pDS->s, &ibits);

        /* Wait for socket activity */
        if( fdSelect( (int)pDS->s, &ibits, 0, 0, 0 ) < 0 )
            goto leave;

        /* Check for new data on UDP socket */
        if( FD_ISSET(pDS->s, &ibits) )
        {
            tmp  = sizeof( pDS->sin1 );
            pDS->size = recvfrom( pDS->s, pDS->buf,
                                  sizeof(pDS->buf), 0,(struct sockaddr *)&pDS->sin1, &tmp);

            /* Process the request */
            if( pDS->size > 0 )
                ProcessMain( pDS );
        }
    }

leave:
    if( pDS->s != INVALID_SOCKET )
    {
        fdClose( pDS->s );
        pDS->s = INVALID_SOCKET;
    }

    /* Update status */
    if( pDS->pCb )
        (*pDS->pCb)( pDS->hCb, NETTOOLS_STAT_FAULT );

    /* We don't return - we're killed by the system */
    TaskBlock( TaskSelf() );
}

/*---------------------------------------------------------------- */
/*---------------------------------------------------------------- */
/* DHCPS - IP Database Functions */
/* The IP database is used to track MAC/IP address relationships. */
/* These functions are used to create / lookup address entries, */
/* and to age out invalid or long-pending entries. */
/*---------------------------------------------------------------- */
/*---------------------------------------------------------------- */

/*---------------------------------------------------------------- */
/* iprMacCmp - Hawrdware Address Compare */
/* Returns NULL if addresses are identical */
/*---------------------------------------------------------------- */
static int iprMacCmp( UINT8 *pMAC1, UINT8 *pMAC2 )
{
    int i;
    for( i=1; i<=6; i++ )
        if( *pMAC1++ != *pMAC2++ )
            return( i );
    return(0);
}

/*---------------------------------------------------------------- */
/* iprSync - Free any held IPR */
/*---------------------------------------------------------------- */
static void iprSync( DHCPSRV *pDS )
{
    if( pDS->hIPR )
    {
        CfgEntryDeRef( pDS->hIPR );
        pDS->hIPR = 0;
    }
}

/*---------------------------------------------------------------- */
/* iprGetByIndex - Get an IPR by Index */
/*---------------------------------------------------------------- */
static int iprGetByIndex( DHCPSRV *pDS, uint Index )
{
    HANDLE hCfgEntry;
    int    rc,size;

    /* Just to make sure... */
    iprSync( pDS );

    /* Get entry */
    rc = CfgGetEntry( 0, CFGTAG_CLIENT, pDS->IfIdx, Index, &hCfgEntry );
    if( rc < 1 )
        return(0);

    /* Get data */
    size = sizeof( DHCP_RECORD );
    CfgEntryGetData( hCfgEntry, &size, (UINT8 *)&pDS->ipr );

    /* Remember that we're holding this entry */
    pDS->hIPR = hCfgEntry;

    return(1);
}

/*---------------------------------------------------------------- */
/* iprNew - Find or create a new address entry */
/*---------------------------------------------------------------- */
static int iprNew( DHCPSRV *pDS, uint mode, IPN IPReqAddr, UINT8 *pMAC )
{
    UINT32      i,j=0;
    int         rc;

    /* Sanity check the mode */
    if( mode < IPR_MODE_FIND || mode > IPR_MODE_CREATEFIXED )
        return(0);

    /* First, try and find an entry */
    if( iprFindByMAC( pDS, pMAC ) )
    {
        if( mode == IPR_MODE_CREATEFIXED && IPReqAddr != pDS->ipr.IPAddr )
            return( 0 );
        return( 1 );
    }

    /* Here we must create an entry. If not set to create, return NULL */
    if( mode == IPR_MODE_FIND )
        return( 0 );

    /* See if we can use the preferred IP */
    i = htonl( IPReqAddr );

    /* If the address is out of range, we can't use it */
    /* else, see if the address has already been allocated */
    if( i<pDS->PoolBase || i>=(pDS->PoolBase+pDS->PoolSize) ||
                                          (j=iprFindByIP(pDS, IPReqAddr)) )
    {
        /* Requested IP is invalid or in use. If in use and marked */
        /* INVALID, we'll may allow use of the IP. This is because another */
        /* client could have claimed it invalid, although its "OK" for */
        /* this client - after all, it is specifically requesting it. */
        if( i && j )
        {
            if( pDS->ipr.Status == CFG_CLIENTSTATUS_INVALID )
            {
                /* The MAC address of this client can not match that */
                /* of the client that marked it invalid */
                for(j=0; j<6; j++)
                    if( *(pMAC+j) != *(pDS->ipr.MacAddr+j) )
                        break;
                if( j != 6 )
                {
                    /* We will attempt to reuse this IP addr. First, */
                    /* remove the INVALID record. */
                    iprRemove( pDS );
                    goto IPADDROK;
                }
            }
        }

        /* Requested IP is invalid or in use - get a new one */

        /* If the user only wanted the requested IP, then we're done */
        if( mode == IPR_MODE_CREATEFIXED )
            return(0);

        /* First try and time out any old entries */
        iprTimeoutCheck( pDS );

        /* Find a valid IP */
        for( i=0; i<pDS->PoolSize; i++ )
        {
            j = pDS->PoolBase + i;
            j = htonl( j );
            if( !iprFindByIP(pDS, j) )
                break;
        }

        /* If we're full, its an error */
        if( i == pDS->PoolSize )
            return( 0 );

        /* Change the requested IP to the free value we've decided to use */
        IPReqAddr = j;
    }

IPADDROK:
    /* If we're holding an IPR, ditch it */
    iprSync( pDS );

    /* Here, IPReqAddr contains a legal IP address. We just need to */
    /* intialize the entry. */
    pDS->ipr.ClientType = CFG_CLIENTTYPE_DYNAMIC;
    pDS->ipr.IPAddr     = IPReqAddr;
    pDS->ipr.Status     = CFG_CLIENTSTATUS_PENDING;
    pDS->ipr.TimeExpire = EXPIRATION_TIME;
    pDS->ipr.TimeStatus = llTimerGetTime(0);
    bcopy( pMAC, pDS->ipr.MacAddr, 6 );

    /* Add it to the configuration */
    rc = CfgAddEntry( 0, CFGTAG_CLIENT, pDS->IfIdx, CFG_ADDMODE_NOSAVE,
                      sizeof( DHCP_RECORD ), (UINT8 *)&(pDS->ipr), &pDS->hIPR );
    if( rc < 0 )
        return(0);

    return( 1 );
}

/*---------------------------------------------------------------- */
/* iprRemove - Remove the current ipr */
/*---------------------------------------------------------------- */
static void iprRemove( DHCPSRV *pDS )
{
    if( pDS->hIPR )
    {
        /* If entry is one of ours, remove it. */
        if( pDS->ipr.ClientType == CFG_CLIENTTYPE_DYNAMIC )
        {
            CfgRemoveEntry( 0, pDS->hIPR );
            pDS->hIPR = 0;
        }
        /* Else just clear its state and deref */
        else
        {
            iprUpdate( pDS, 0 );
            iprSync( pDS );
        }
    }
}

/*---------------------------------------------------------------- */
/* iprUpdate - Set status and update IP record */
/*---------------------------------------------------------------- */
static void iprUpdate( DHCPSRV *pDS, uint Status )
{
    if( pDS->hIPR )
    {
        pDS->ipr.Status = Status;
        pDS->ipr.TimeStatus = llTimerGetTime(0);
        CfgEntrySetData( pDS->hIPR, sizeof( DHCP_RECORD ), (UINT8 *)&pDS->ipr );
    }
}

/*---------------------------------------------------------------- */
/* iprTimeoutCheck - Scan list and timeout entries */
/*---------------------------------------------------------------- */
static void iprTimeoutCheck( DHCPSRV *pDS )
{
    UINT32 TimeNow;
    int    i=1;

    /* Get the current time */
    TimeNow = llTimerGetTime(0);

    for(;;)
    {
        /* Get the next entry */
        if( !iprGetByIndex( pDS, i ) )
            return;

        /* Remove any expired entry */

        /* STATIC entires are not subject to timeout */
        /* INVALID and PENDING timeout on a fixed TEMPREC timeout */
        /* VALID entries use the supplied timout */
        if( pDS->ipr.Status != CFG_CLIENTSTATUS_STATIC )
        {
            if( pDS->ipr.Status != CFG_CLIENTSTATUS_VALID )
            {
                if( (pDS->ipr.TimeStatus + TEMPREC_TIME) <= TimeNow )
                    iprRemove( pDS );
            }
            else
            {
                if( (pDS->ipr.TimeStatus + pDS->ipr.TimeExpire) <= TimeNow )
                    iprRemove( pDS );
            }
        }
        i++;
    }
}

/*---------------------------------------------------------------- */
/* iprFindByIP - Find Record by IP Address */
/*---------------------------------------------------------------- */
static int iprFindByIP( DHCPSRV *pDS, IPN IPReqAddr )
{
    int i=1;

    for(;;)
    {
        /* Get the next entry */
        if( !iprGetByIndex( pDS, i ) )
            return(0);

        if( pDS->ipr.IPAddr == IPReqAddr )
            return(1);

        i++;
    }
}

/*---------------------------------------------------------------- */
/* iprFindByMAC - Find Record by MAC Address */
/*---------------------------------------------------------------- */
static int iprFindByMAC( DHCPSRV *pDS, UINT8 *pMAC )
{
    int i=1;

    for(;;)
    {
        /* Get the next entry */
        if( !iprGetByIndex( pDS, i ) )
            return(0);

        /* Only care about VALID entries */
        if( pDS->ipr.Status != CFG_CLIENTSTATUS_INVALID )
        {
            if( !iprMacCmp( (UINT8 *)(pDS->ipr.MacAddr), pMAC ) )
                return(1);
        }

        i++;
    }
}

/*---------------------------------------------------------------- */
/*---------------------------------------------------------------- */
/* DHCPS - Network Packet Processing */
/*---------------------------------------------------------------- */
/*---------------------------------------------------------------- */

/*---------------------------------------------------------------- */
/* ProcessMain() */
/*---------------------------------------------------------------- */
static void ProcessMain( DHCPSRV *pDS )
{
    DHCPS       *pHdr = (DHCPS *)pDS->buf;
    UINT8       Hostname[CFG_HOSTNAME_MAX];
    UINT8       *pv;
    UINT16      MessageType;
    int         TagLength,TmpSize;
    IPN         IPRequested = 0;
    IPN         IPClaimed = 0;
    UINT32      tmp;
    int         ipr=0;

    MessageType = 0;

    /*  If packet not for us, then just return */
    if( (pHdr->op != BOOTREQUEST) ||
                     (pHdr->htype != ETHERNET) || (pHdr->hlen != ELEN ) )
        return;

    /* PV is our options pointer */
    pv = (UINT8 *)pHdr->options + 4;
    TmpSize = pDS->size - (sizeof(DHCPS) - (SZOPTIONS-4));

    if( TmpSize < 0 )
        return;

    /* Reset any requested tag count */
    pDS->tagsize = 0;


    /* Scan through the option tags and perform the following: */

    /* - Get the Message Type */
    /* - Record any requested IP */
    /* - If there's a server ID supplied, be sure it matches */
    /* - Record the list of requested options */

    while( TmpSize )
    {
        switch( *pv++ )
        {
        case DHCPOPT_END:
            TmpSize = 0;
            break;

        case DHCPOPT_HOSTNAME:
            TagLength = *pv;
            if( TagLength > (CFG_HOSTNAME_MAX-1) )
                TagLength = CFG_HOSTNAME_MAX-1;
            strncpy( (char *)Hostname, (char *)(pv+1), TagLength );
            Hostname[TagLength] = 0;
            TagLength = *pv++;
            goto continue_scan;

        case DHCPOPT_DHCP_MESSAGE_TYPE:
            TagLength = *pv++;
            MessageType = *pv;
            goto continue_scan;

        case DHCPOPT_REQUESTED_IP_ADDRESS:
            TagLength = *pv++;
            if( TagLength == 4 )
                bcopy( pv, &IPRequested, 4 );
            goto continue_scan;

        case DHCPOPT_PARAMETER_REQUEST_LIST:
            TagLength = *pv++;
            if( TagLength <= TAGBUF_LENGTH )
            {
                bcopy( pv, pDS->tags, TagLength );
                pDS->tagsize = TagLength;
            }
            goto continue_scan;

        case DHCPOPT_SERVER_IDENTIFIER:
            TagLength = *pv++;
            if( TagLength == 4 )
            {
                bcopy( pv, &tmp, 4 );
                if( tmp == pDS->IPServer )
                    goto continue_scan;
            }
            /* If here, then the tag is illegal or doesn't match */
            return;

        default:
            /* skip over by using the length field */
            TagLength = *pv++;
        continue_scan:
            pv += TagLength;
            TmpSize -= TagLength+2;
            break;
        }
    }

    /* If the client is claiming an IP address, record it. */
    bcopy( &pHdr->ciaddr, &IPClaimed, 4 );

    /* Process the message */
    switch( MessageType )
    {
    case DHCPDISCOVER:
        ipr = iprNew(pDS, IPR_MODE_CREATE, IPRequested, (UINT8 *)pHdr->chaddr);
        if( ipr )
            SendDHCPReply( pDS, pDS->ipr.IPAddr, DHCPOFFER, 0 );
        break;

    case DHCPREQUEST:
        /* Get the requested IP from the header or the options, but we */
        /* prefer the header */
        if( !IPClaimed )
            IPClaimed = IPRequested;

        /* If the client claimed an IP address, we must use it */
        /* Else, use any IP address we can get */
        if( IPClaimed )
            ipr = iprNew(pDS, IPR_MODE_CREATEFIXED, IPClaimed,
                                                    (UINT8 *)pHdr->chaddr);
        else
            ipr = iprNew(pDS, IPR_MODE_CREATE, 0, (UINT8 *)pHdr->chaddr);

        /* If we got an address, use it, else send a NAK */
        if( !ipr )
        {
            /* Note: We don't get here if there was a ServerID in the packet */
            /* and it wasn't us. */
            SendDHCPReply( pDS, IPClaimed, DHCPNAK, 0 );
        }
        else
        {
            strcpy( pDS->ipr.Hostname, (char *)Hostname );
            iprUpdate( pDS, CFG_CLIENTSTATUS_VALID );
            SendDHCPReply( pDS, pDS->ipr.IPAddr, DHCPACK, SENDFLG_LEASETIME );
        }
        break;

    case DHCPDECLINE:
        /* Here, just mark the client's entry as invalid */
        ipr = iprFindByMAC( pDS, (UINT8 *)pHdr->chaddr );
        if( ipr )
            iprUpdate( pDS, CFG_CLIENTSTATUS_INVALID );
        break;

    case DHCPRELEASE:
        /* Here, free the client's entry */
        ipr = iprFindByMAC( pDS, (UINT8 *)pHdr->chaddr );
        if( ipr )
            iprRemove( pDS );
        break;

    case DHCPINFORM:
        /* Here we create the entry if we can. If we can, we ACK the packet */
        if( IPClaimed )
        {
            ipr = iprNew(pDS, IPR_MODE_CREATEFIXED, IPClaimed,
                                                    (UINT8 *)pHdr->chaddr);

            /* If we agree on address, send a reply, else ignore it */
            if( ipr )
            {
                iprUpdate( pDS, CFG_CLIENTSTATUS_STATIC );
                SendDHCPReply( pDS, pDS->ipr.IPAddr, DHCPACK, 0 );
            }
        }
        break;

    default:
        break;
    }

    return;
}


/*---------------------------------------------------------------- */
/* SendDHCPReply() */
/* Called to send a reply to the specifed IP address */
/*---------------------------------------------------------------- */
static void SendDHCPReply( DHCPSRV *pDS, IPN IPAddr, UINT8 message, uint flags )
{
    DHCPS   *pHdr = (DHCPS *)pDS->buf;
    HANDLE  hRt;
    UINT8   *pv;
    UINT32  Magic = htonl(RFC1084);
    int     OptSize,MsgSize;
    IPN     IPReturn;                   /* IP Address for DHCP message */
    int     tagSize,i;
    int     idx,rc,multi;
    UINT8   TagData[64];

    /* Adjust the header */
    pHdr->op   = BOOTREPLY;
    pHdr->secs = 0;
    pHdr->hops = 0;

    /* Fill in yiaddr unless this is a NAK */
    if( message != DHCPNAK )
        bcopy( &IPAddr, &pHdr->yiaddr, 4);
    else
        bzero( &pHdr->yiaddr, 4);

    /* Clear siaddr */
    bzero( &pHdr->siaddr, 4);

    /* Clear SNAME, FILE, and OPTIONS */
    bzero(pHdr->sname, SZSNAME);
    bzero(pHdr->file, SZFNAME);
    bzero(pHdr->options, SZOPTIONS);

    /* Construct new options section */
    bcopy( &Magic, pHdr->options, 4);

    pv = (UINT8 *)pHdr->options + 4;
    OptSize = 4;

    /* We always supply a message */
    *pv++ = DHCPOPT_DHCP_MESSAGE_TYPE;
    *pv++ = 1;
    *pv++ = message;
    OptSize += 3;

    /* We always supply a server ID */
    *pv++ = DHCPOPT_SERVER_IDENTIFIER;
    *pv++ = 4;
    bcopy( &pDS->IPServer, pv, 4);
    pv+=4;
    OptSize += 6;

    /* Force lease time under some circumstances */
    if( flags & SENDFLG_LEASETIME )
    {
        *pv++ = DHCPOPT_IP_ADDRESS_LEASE_TIME;
        *pv++ = 4;
        Magic = htonl( pDS->ipr.TimeExpire );
        bcopy( &Magic, pv, 4);
        pv+=4;
        OptSize += 6;
    }

    /* Now add the optional tags if not sending a NAK */
    if( message != DHCPNAK )
    {
        for( i=0; i<pDS->tagsize; i++ )
        {
            switch( pDS->tags[i] )
            {
            case DHCPOPT_SUBNET_MASK:
                *pv++ = DHCPOPT_SUBNET_MASK;
                *pv++ = 4;
                bcopy( &pDS->IPMask, pv, 4);
                pv+=4;
                tagSize = 6;
                break;

            case DHCPOPT_ROUTER:
                *pv++ = DHCPOPT_ROUTER;
                *pv++ = 4;
                bcopy( &pDS->IPServer, pv, 4);
                pv+=4;
                tagSize = 6;
                break;

            case DHCPOPT_DOMAIN_NAME:
                *pv++ = DHCPOPT_DOMAIN_NAME;
                tagSize = pDS->DomainLength;
                *pv++ = (UINT8)tagSize;
                bcopy( &pDS->DomainName, pv, tagSize);
                pv += tagSize;
                tagSize += 2;
                break;

            case DHCPOPT_DOMAIN_NAME_SERVERS:
                /* If we aren't running our own name server, */
                /* then pass-through the external servers we use. */
                if( !pDS->IPNameServer )
                {
                    multi = 1;
                    goto config_tag;
                }
                *pv++ = DHCPOPT_DOMAIN_NAME_SERVERS;
                *pv++ = 4;
                bcopy( &pDS->IPServer, pv, 4);
                pv+=4;
                tagSize = 6;
                break;

            /* Generic Tag Handling */

            /* Single Instance Tags */
            case DHCPOPT_NETBIOS_NODE_TYPE:
            case DHCPOPT_NETBIOS_SCOPE:
                multi = 0;
                goto config_tag;

            /* Multi Instance Tags */
            case DHCPOPT_NETBIOS_NAME_SERVER:
                multi = 1;
config_tag:
                idx     = 1;
                tagSize = 0;
                do
                {
                    rc = CfgGetImmediate( 0, CFGTAG_SYSINFO,
                                          pDS->tags[i], idx,
                                          sizeof(TagData), TagData);
                    if( rc <= 0 )
                        break;

                    /* Copy Tag Data */
                    bcopy( TagData, pv+tagSize+2, rc );
                    tagSize += rc;

                    /* Do next index (if any) */
                    idx++;

                } while( multi );

                if( tagSize )
                {
                    *pv++ = pDS->tags[i];
                    *pv++ = (UINT8)tagSize;
                    pv += tagSize;
                    tagSize += 2;
                }
                break;

            case DHCPOPT_IP_ADDRESS_LEASE_TIME:
                /* Don't send it twice */
                if( flags & SENDFLG_LEASETIME )
                    tagSize = 0;
                else
                {
                    *pv++ = DHCPOPT_IP_ADDRESS_LEASE_TIME;
                    *pv++ = 4;
                    Magic = htonl( pDS->ipr.TimeExpire );
                    bcopy( &Magic, pv, 4);
                    tagSize = 6;
                }
                break;

            default:
                tagSize = 0;
                break;
            }

            /* Track the option size - bound by max value */
            if( tagSize )
            {
                OptSize += tagSize;
                if( OptSize > (MAX_OPTION_SIZE-1) )
                {
                    OptSize -= tagSize;
                    pv -= tagSize;
                    break;
                }
            }
        }
    }

    /* Add the final tag */
    *pv++ = DHCPOPT_END;
    OptSize++;

    /* Bound OptSize by its min value */
    if( OptSize < SZOPTIONS )
        OptSize = SZOPTIONS;

    /* Calculate message size */
    MsgSize = sizeof(DHCPS) - SZOPTIONS + OptSize;

    /* Now send the packet via broadcast or unicast */

    /* Get the return address (if any) */
    bcopy( &pHdr->giaddr, &IPReturn, 4);

    /* If no return address in giaddr, try the ciaddr */
    if( !IPReturn )
    {
        /* NAK messages are always broadcast when giaddr is NULL */
        if( message == DHCPNAK )
            goto broadcast_reply;

        /* Get the contents of ciaddr */
        bcopy( &pHdr->ciaddr, &IPReturn, 4);
    }

    /* If still no return address, then use yiaddr unless the broadcast */
    /* flag is set */
    if( !IPReturn )
    {
        /* If the broadcast flag is set, then broadcast the reply */
        if( pHdr->flags & 1 )
            goto broadcast_reply;

        /* If we got here, we know IPAddr == yiaddr */
        IPReturn = IPAddr;
    }

    /* Use UNICAST addressing */

    /* Configure sin1 to point back to client */
    pDS->sin1.sin_family      = AF_INET;
    pDS->sin1.sin_addr.s_addr = IPReturn;
    pDS->sin1.sin_port        = htons(NDHCPC);

    /* If the client is expecting a UNICAST reply, its possible that it */
    /* can not yet respond to an ARP request. For this reason, if we're not */
    /* sending a NAK, but are sending direct to the client, then we'll manually */
    /* validate the route in our ARP table. */
    if( (message != DHCPNAK) && (IPReturn == IPAddr) )
    {
        llEnter();
        hRt = LLIValidateRoute( pDS->hIF, IPReturn, (UINT8 *)pHdr->chaddr );
        /* Note: The function returns a reference handle which we don't want */
        if( hRt )
            RtDeRef( hRt );
        llExit();
    }

    /* Send the packet */
    sendto( pDS->s, pDS->buf, MsgSize, 0,(struct sockaddr *)&pDS->sin1, sizeof(pDS->sin1) );
    return;

broadcast_reply:
    /* Use BROADCAST addressing */

    /* Configure sin1 to point back to client */
    pDS->sin1.sin_family      = AF_INET;
    pDS->sin1.sin_addr.s_addr = INADDR_BROADCAST;
    pDS->sin1.sin_port        = htons(NDHCPC);

    /* Send the packet */
    sendto( pDS->s, pDS->buf, MsgSize, 0,(struct sockaddr *)&pDS->sin1, sizeof(pDS->sin1) );
}




