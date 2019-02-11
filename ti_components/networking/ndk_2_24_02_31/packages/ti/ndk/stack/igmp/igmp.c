/*
 * Copyright (c) 2012-2014, Texas Instruments Incorporated
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
 * ======== igmp.c ========
 *
 * IGMP Stack Implementation.
 *
 */
#include <stkmain.h>

typedef struct _IGMP_REC
{
    IPN     IpAddr;
    UINT16  RefCount;
    UINT8   IfIdx;
    UINT8   ReportTime;
} IGMP_REC;

/* Max Groups */
#define IGMP_MAX_GROUP  32

/* Max supported intefaces */
#define IGMP_MAX_IFIDX  4

/* Default times */
#define IGMP_SECONDS_UPGRADE    400
#define IGMP_SECONDS_DEFAULT    10

static IGMP_REC igmp[IGMP_MAX_GROUP];
static uint     igmpCount[IGMP_MAX_IFIDX];
static uint     igmp_version = 2;
static uint     igmp_upgrade_timer = 0;

UINT32 _IGMPForceVersion1 = 0;
UINT32 _IGMPInDiscard;
UINT32 _IGMPInQuery;
UINT32 _IGMPInQueryGroup;
UINT32 _IGMPInResponse;
UINT32 _IGMPOutResponse;

static uint IGMPTimer();
static uint IGMPDoMCast( uint IfIdx, IPN IpAddr, uint fAdd );
static void IGMPSendReply( uint recidx, uint ingroup );


/*-------------------------------------------------------------------- */
/* IGMPMsg() */
/* Sevices intialization and resource messages */
/*-------------------------------------------------------------------- */
void IGMPMsg( uint Msg )
{
    static HANDLE hTimer = 0;

    switch( Msg )
    {
    /* System Initialization */
    case MSG_EXEC_SYSTEM_INIT:
        mmZeroInit( &igmp, sizeof(igmp) );
        mmZeroInit( &igmpCount, sizeof(igmpCount) );
        _IGMPInDiscard = 0;
        _IGMPInQuery = 0;
        _IGMPInQueryGroup = 0;
        _IGMPInResponse = 0;
        _IGMPOutResponse = 0;
        break;

    /* System Shutdown */
    case MSG_EXEC_SYSTEM_SHUTDOWN:
        if( hTimer )
        {
            TimerFree( hTimer );
            hTimer = 0;
        }
        break;

    /* A message saying we have new IGMP items to time */
    case MSG_IGMP_NEEDTIMER:
        if( !hTimer )
            hTimer = TimerNew( &IGMPMsg, 1, MSG_IGMP_TIMER );
        break;

    /* Half Second Timer Tick */
    case MSG_IGMP_TIMER:
        /* Check our timer items. This function returns NULL if */
        /* no more items to time */
        if( !IGMPTimer() )
        {
            TimerFree( hTimer );
            hTimer = 0;
        }
        break;
    }
}

/**
 *  @b Description
 *  @n
 *      The function is called to JOIN a multicast group on the specific
 *      interface. The function adds the multicast group to the interface
 *      list and kicks the IGMP membership state machine to send out the
 *      reports.
 *
 *      This is the OLD API which was used to JOIN multicast groups but
 *      has now been obsoleted. Users are advised to use the well defined
 *      setsockopt with the IP_ADD_MEMBERSHIP to acheive the needful.
 *
 *      This function is now called only from *kernel* context
 *
 *  @param[in]  IpAddr
 *      Multicast group IP address which is being joined.
 *  @param[in]  IfIdx
 *      Interface Index on which the group is being joined.
 *
 *  @retval
 *   1          -   Success
 *  @retval
 *   0   -   Error
 */
static uint IGMPJoinHostGroup( IPN IpAddr, uint IfIdx )
{
    int     i,empty = -1;
    uint    retval = 0;

    /* Support default idx, make sure idx is legal */
    if( !IfIdx )
        IfIdx = 1;
    else if( IfIdx > IGMP_MAX_IFIDX )
        return(0);

    /* Make sure address makes sense */
    if( !IN_MULTICAST(IpAddr) || IpAddr == HNC32(0xe0000001) )
        return(0);

    /* See if we're already a member */
    for( i=0; i<IGMP_MAX_GROUP; i++ )
    {
        if( !igmp[i].RefCount )
            empty = i;
        else if( igmp[i].IpAddr == IpAddr && igmp[i].IfIdx == IfIdx )
        {
            igmp[i].RefCount++;
            retval = 1;
            goto join_exit;
        }
    }

    /* Here we're not a member */
    if( empty >= 0 )
    {
        /* Add this IP multicast to the Ethernet driver MCast list */
        if( !IGMPDoMCast( IfIdx, IpAddr, 1 ) )
            goto join_exit;

        /* If this is the first join on this IF, then install the */
        /* all-hosts group on this IF. */
        if( igmpCount[IfIdx-1] == 0 )
        {
            if( !IGMPDoMCast( IfIdx, HNC32(0xe0000001), 1 ) )
            {
                IGMPDoMCast( IfIdx, IpAddr, 0 );
                goto join_exit;
            }
        }

        /* Bump master count */
        igmpCount[IfIdx-1]++;

        /* Init record and setup to send a second reply */
        igmp[empty].RefCount   = 1;
        igmp[empty].IpAddr     = IpAddr;
        igmp[empty].IfIdx      = IfIdx;
        igmp[empty].ReportTime = 10;         /* 5 seconds */

        /* Send first reply now */
        IGMPSendReply(empty, 1);

        /* Tell IGMP message handler to start the timer */
        IGMPMsg(MSG_IGMP_NEEDTIMER);

        retval = 1;
    }

join_exit:
    return( retval );
}

/**
 *  @b Description
 *  @n
 *      The function is called to LEAVE a multicast group on the specific
 *      interface. The function leaves the multicast group on the interface
 *      list and kicks the IGMP membership state machine to send out the
 *      LEAVE reports.
 *
 *      This is the OLD API which was used to LEAVE multicast groups but
 *      has now been obsoleted. Users are advised to use the well defined
 *      setsockopt with the IP_DROP_MEMBERSHIP to acheive the needful.
 *
 *      This function is now called only from *kernel* context
 *
 *  @param[in]  IpAddr
 *      Multicast group IP address which is being joined.
 *  @param[in]  IfIdx
 *      Interface Index on which the group is being joined.
 *
 *  @retval
 *      Not Applicable.
 */
void IGMPLeaveHostGroup( IPN IpAddr, uint IfIdx )
{
    int     i;

    /* Support default idx */
    if( !IfIdx )
        IfIdx = 1;

    /* See if we're even a member */
    for( i=0; i<IGMP_MAX_GROUP; i++ )
    {
        if( igmp[i].RefCount &&
                igmp[i].IpAddr == IpAddr && igmp[i].IfIdx == IfIdx )
        {
            /* Dec the ref count remove if zero */
            igmp[i].RefCount--;
            if( !igmp[i].RefCount )
            {
                /* Send leave message now */
                IGMPSendReply(i, 0);

                /* Leave the group */
                IGMPDoMCast( IfIdx, IpAddr, 0 );

                /* Dec the total group count for this IF, remove */
                /* the all-hosts group if zero */
                igmpCount[IfIdx-1]--;
                if( !igmpCount[IfIdx-1] )
                {
                    /* Delete the "all-hosts" mulitcast address */
                    IGMPDoMCast( IfIdx, HNC32(0xe0000001), 0 );
                }
            }
            break;
        }
    }
}


/*-------------------------------------------------------------------- */
/* IGMPInput() */
/* Rx IGMP Packet */
/*-------------------------------------------------------------------- */
void IGMPInput( PBM_Pkt *pPkt )
{
    uint       w,IPHdrLen,IGMPLen;
    UINT8      *pb;
    IPHDR      *pIpHdr;
    IGMPHDR    *pIgHdr;
    uint       Type,IfIdx,time;
    int        i;
    IPN        IpDst,IpGrp;

    /* Get the IP header len */
    IPHdrLen = pPkt->IpHdrLen;

    /* Get the buffer pointer */
    pb = pPkt->pDataBuffer + pPkt->DataOffset;

    /* Assign an IP header pointer */
    pIpHdr = (IPHDR *)pb;

    /* Assign a ICMP header pointer */
    pIgHdr = (IGMPHDR *)(pb + IPHdrLen);

    /* Get the total length of the IGMP message */
    IGMPLen = (uint)(HNC16( pIpHdr->TotalLen )) - IPHdrLen;

    /* Check for packet too small */
    if( IGMPLen != IGMPHDR_SIZE )
    {
IGMPError:
        _IGMPInDiscard++;
        PBM_free( pPkt );
        return;
    }

    /* Check checksum */
    w = (uint)pIgHdr->Checksum;
    if( w == 0xFFFF )
        w = 0;
    ICMPChecksum( (ICMPHDR *)pIgHdr, IGMPLen );
    if( w != (uint)pIgHdr->Checksum )
        goto IGMPError;

    /* Get type and IfIdx */
    Type = (uint)pIgHdr->VerType;
    IfIdx = IFGetIndex( pPkt->hIFRx );

    /* Get destination address and group address */
    IpDst = RdNet32(&pIpHdr->IPDst);
    IpGrp = RdNet32(&pIgHdr->IpAddr);

    /* Handle Query */
    if( Type == 0x11 )
    {
        /* Get response max time and convert to half seconds */
        time = (uint)pIgHdr->MaxTime;
        if( !time )
        {
            time = IGMP_SECONDS_DEFAULT * 2;
            if( !_IGMPForceVersion1 )
            {
                /* Fallback to version 1 */
                igmp_version = 1;
                igmp_upgrade_timer = IGMP_SECONDS_UPGRADE;

                /* Tell IGMP message handler to start the timer */
                IGMPMsg(MSG_IGMP_NEEDTIMER);
            }
        }
        else
            time /= 5; /* Convert to half seconds */

        if( !IpGrp )
        {
            /* General Query */

            /* Dest IP must be all-hosts */
            if( HNC32(IpDst) != 0xe0000001 )
                goto IGMPError;

            _IGMPInQuery++;

            /* Setup replies. Reset each counter to be withing the new */
            /* time limit if needed. */
            w = 1;
            for( i=0; i<IGMP_MAX_GROUP; i++ )
            {
                if( igmp[i].RefCount && igmp[i].IfIdx == IfIdx &&
                    (!igmp[i].ReportTime || igmp[i].ReportTime>w) )
                {
                    igmp[i].ReportTime = w;
                    if( ++w > time )
                        w = 1;
                }
            }
        }
        else
        {
            /* Group Specific Query */

#if 0 /* Customer reported issue on this */
            /* Dest IP must be Group */
            if( IpDst != IpGrp )
                goto IGMPError;
#endif

            _IGMPInQueryGroup++;

            /* Setup replies. Reset each counter to be withing the new */
            /* time limit if needed. */
            w = 1;
            for( i=0; i<IGMP_MAX_GROUP; i++ )
            {
                if( igmp[i].RefCount && igmp[i].IpAddr == IpGrp &&
                    igmp[i].IfIdx == IfIdx &&
                    (!igmp[i].ReportTime || igmp[i].ReportTime>w) )
                {
                    igmp[i].ReportTime = w;
                    if( ++w > time )
                        w = 1;
                }
            }
        }

        /* Tell IGMP message handler to start the timer */
        IGMPMsg(MSG_IGMP_NEEDTIMER);
    }
    else if( Type == 0x12 || Type == 0x16 )
    {
        if( IpDst != IpGrp )
            goto IGMPError;

        _IGMPInResponse++;

        /* This is a reply. We can clear our timer if it matches us */
        for( i=0; i<IGMP_MAX_GROUP; i++ )
            if( igmp[i].RefCount &&
                    igmp[i].IpAddr == IpDst && igmp[i].IfIdx == IfIdx )
                igmp[i].ReportTime = 0;
    }
    else
        goto IGMPError;

    PBM_free( pPkt );
}


/*-------------------------------------------------------------------- */
/* IGMPTimer() */
/* Parse the group list looking for reports due. Return */
/* "1" if more timer ticks are required, else "0". */
/*-------------------------------------------------------------------- */
static uint IGMPTimer()
{
    int i,more = 0;

    if( igmp_upgrade_timer && igmp_version==1 )
    {
        if( !--igmp_upgrade_timer )
            igmp_version = 2;
        else
            more = 1;
    }

    for( i=0; i<IGMP_MAX_GROUP; i++ )
    {
        if( igmp[i].RefCount && igmp[i].ReportTime )
        {
            igmp[i].ReportTime--;
            if( igmp[i].ReportTime )
                more = 1;
            else
                IGMPSendReply(i, 1);
        }
    }

    return( more );
}

/*-------------------------------------------------------------------- */
/* IGMPDoMCast() */
/* Adds or removes an Ethernet multicast address based on the */
/* calling arguments. */
/* Returns "1" on success, or "0" on error. */
/*-------------------------------------------------------------------- */
static uint IGMPDoMCast( uint IfIdx, IPN IpAddr, uint fAdd )
{
    UINT8  bMacAddr[6];
    UINT32 tmp;
    HANDLE hEther;

    /* Map the relevant IP bits */
    tmp = HNC32(IpAddr);
    tmp = (tmp & 0x7fffff) | 0x5e000000;

    /* Form multicast MAC address */
    bMacAddr[0] = 0x01;
    bMacAddr[1] = 0x00;
    bMacAddr[2] = (UINT8)(tmp >> 24);
    bMacAddr[3] = (UINT8)(tmp >> 16);
    bMacAddr[4] = (UINT8)(tmp >> 8);
    bMacAddr[5] = (UINT8)(tmp);

    /* This is being called from within the NDK critical section */
    hEther = (HANDLE)NIMUFindByIndex(IfIdx);
    if( !hEther )
        return(0);

    /* If this is a PPP device, we pretend we added the address */
    if( IFGetType(hEther) != HTYPE_ETH )
    {
        if( IFGetType(hEther) == HTYPE_PPP )
            return(1);
         else
            return(0);
    }

    {
        NETIF_DEVICE*   ptr_device;

        /*
         *  Get the NIMU network interface object on which we need to add the
         *  multicast address.
         */
        ptr_device = (NETIF_DEVICE *)hEther;

        /*
         *  Ensure that there is an IOCTL Function registered to configure
         *  device addresses.
         *
         *  If there is no IOCTL Function specified the device multicast list
         *  cannot be configured.
         */
        if (ptr_device->ioctl == NULL)
            return 0;

        if (fAdd)
        {
            /*
             *  Add a multicast address; we are already in kernel mode hence we
             *  can directly call the Device specific IOCTL function.
             */
            if (ptr_device->ioctl(ptr_device, NIMU_ADD_MULTICAST_ADDRESS,
                    (void *)&bMacAddr[0], 6) < 0)
            {
                /* The Device specific IOCTL Failed. Pass back the error... */
                return 0;
            }

            /*
             *  Multicast address was successfully added to the Device
             *  Multicast List
             */
            return 1;
        }

        /*
         *  Delete a multicast address; we are already in kernel mode hence we
         *  can directly call the Device specific IOCTL function.
         */
        if (ptr_device->ioctl(ptr_device, NIMU_DEL_MULTICAST_ADDRESS,
                (void *)&bMacAddr[0], 6) < 0)
        {
            /* The Device specific IOCTL Failed. Pass back the error... */
            return 0;
        }

        /*
         *  Multicast address was successfully added to the Device Multicast
         *  List
         */
        return 1;
    }
}

/*-------------------------------------------------------------------- */
/* IGMPSendReply() */
/* Send out an IGMP report packet for the indicated record index. */
/*-------------------------------------------------------------------- */
static void IGMPSendReply( uint recidx, uint ingroup )
{
    PBM_Pkt    *pPkt;
    UINT8      *pb;
    IGMPHDR    *pIgHdr;
    IPHDR      *pIpHdr;
    IPN        IpHost;

    /* See if this message makes sense */
    if( !ingroup && ( igmp_version==1 || _IGMPForceVersion1 ) )
        return;

    /* Create the packet */
    /* Payload = IGMPHDR */
    /* Also add in the size for a STANDARD IP header for the new pkt */
    if( !(pPkt = NIMUCreatePacket( IGMPHDR_SIZE+IPHDR_SIZE+4 )) )
        return;

    /* Get a pointer to the new IGMP header */
    /* pb --> Layer3 */
    /* pIgHdr --> Layer4 */
    pb     = pPkt->pDataBuffer + pPkt->DataOffset;
    pIpHdr = (IPHDR *)pb;
    pIgHdr = (IGMPHDR *)(pb + IPHDR_SIZE + 4);

    /* Get a source address for this packet */
    IpHost = BindIF2IPHost( pPkt->hIFTx );
    if( !IpHost )
        IpHost = BindIF2IPHost( 0 );
    if( !IpHost )
    {
        PBM_free( pPkt );
        return;
    }

    /* Set some IP header stuff */
    pIpHdr->VerLen   = 0x46;        /* Required when creating own header */
    pIpHdr->Ttl      = 1;           /* TTL = 1 on reports */
    pIpHdr->Tos      = 0;
    pIpHdr->Protocol = 2;           /* IGMP */
    WrNet32( &pIpHdr->IPSrc, IpHost );

    /*
     *  Set the destination IP Multicast address (RFC 2236)
     *  Joining the group : IP# is Group Multicast Address
     *  Leaving the group : 224.0.0.2 (All-ROUTERS)
     *
     */
    if (ingroup) {
        WrNet32( &pIpHdr->IPDst, igmp[recidx].IpAddr );
    }
    else {
        WrNet32( &pIpHdr->IPDst, HNC32(0xe0000002) );
    }

    /* Add "router alert" option */
    pIpHdr->Options[0] = 0x94;      /* Router alert + "copied" flag */
    pIpHdr->Options[1] = 0x4;       /* Total byte length of option */
    pIpHdr->Options[2] = 0x0;
    pIpHdr->Options[3] = 0x0;

    /* Set the message type */
    if( !ingroup )
        pIgHdr->VerType = 0x17;
    else if( igmp_version==1 || _IGMPForceVersion1 )
        pIgHdr->VerType = 0x12;
    else
        pIgHdr->VerType = 0x16;

    /* Write the rest of the header */
    pIgHdr->MaxTime = 0;
    WrNet32( &pIgHdr->IpAddr, igmp[recidx].IpAddr );

    /* Checksum the IGMP header (we'll use the ICMP checksum function) */
    ICMPChecksum( (ICMPHDR *)pIgHdr, IGMPHDR_SIZE );

    /* Set the packet valid data size */
    pPkt->ValidLen = IGMPHDR_SIZE+IPHDR_SIZE+4;

    /* Since we know the egress IF, may as well tell IP */
    pPkt->hIFTx = (HANDLE)NIMUFindByIndex(igmp[recidx].IfIdx);

    /* Send the packet */
    IPTxPacket( pPkt, 0 );

    _IGMPOutResponse++;
}

/*-------------------------------------------------------------------- */
/* IGMPTestGroup( IPN IpAddr, uint IfIdx ) */
/* Checks to see if IpAddr and IfIdx match an installed IGMP group */
/* Returns 1 on success, 0 on failure */
/*-------------------------------------------------------------------- */
uint IGMPTestGroup( IPN IpAddr, uint IfIdx )
{
    int i;

    /* See if we're already a member */
    for( i=0; i<IGMP_MAX_GROUP; i++ )
    {
        if( igmp[i].RefCount && igmp[i].IpAddr==IpAddr
            && igmp[i].IfIdx==IfIdx )
            return(1);
    }
    return(0);
}

/**
 *  @b Description
 *  @n
 *      The function is called from the setsockopt to join a multicast
 *      group. This function was added to make the IGMP Join behavior
 *      similar to the standard 'socket' interface via the IP_ADD_MEMBERSHIP
 *      socket option.
 *
 *  @param[in]  hSock
 *      Handle to the socket on which the multicast group is being joined.
 *  @param[in]  ptr_ipmreq
 *      Multicast Request structure populated by the application which
 *      contains the Multicast group address and the address of the interface
 *      on which the group is being joined.
 *
 *  @retval
 *   0          -   Success
 *  @retval
 *   Non Zero   -   Error
 */
int IGMPJoin (HANDLE hSock, struct ip_mreq* ptr_ipmreq)
{
    HANDLE          hIf;
    MCAST_SOCK_REC* ptr_mcast_rec;
    SOCK*           ps;

    /* Get access to the socket information. */
    ps = (SOCK *)hSock;

    /* Map the Interface IP Address to a handle. */
    if ((IPN)ptr_ipmreq->imr_interface.s_addr == INADDR_ANY) {
        hIf = BindGetIF(BindGetFirst());
    }
    else {
        hIf = BindIPHost2IF ((IPN)ptr_ipmreq->imr_interface.s_addr);
    }
    if (!hIf)
        return (EINVAL);

    /* Check for duplicates; if the multicast group has already joined then we
     * dont need to do anything. */
    ptr_mcast_rec = (MCAST_SOCK_REC *)list_get_head ((LIST_NODE**)&ps->pMcastList);
    while (ptr_mcast_rec != NULL)
    {
        /* Check for a hit! */
        if (ptr_mcast_rec->mreq.imr_multiaddr.s_addr == ptr_ipmreq->imr_multiaddr.s_addr)
            return 0;

        /* Get the next entry. */
        ptr_mcast_rec = (MCAST_SOCK_REC *)list_get_next ((LIST_NODE*)ptr_mcast_rec);
    }

    /* Allocate memory for the multicast record. */
    ptr_mcast_rec = mmAlloc(sizeof(MCAST_SOCK_REC));
    if(ptr_mcast_rec == NULL)
    {
        /* FATAL Error: Out of memory error... */
        NotifyLowResource();
        return (ENOMEM);
    }

    /* Initialize the Multicast record information */
    mmCopy ((void *)&ptr_mcast_rec->mreq, (void *)ptr_ipmreq, sizeof(struct ip_mreq));
    ptr_mcast_rec->hIf      = hIf;

    /* Actually Join the Multicast Group. */
    if (IGMPJoinHostGroup(ptr_mcast_rec->mreq.imr_multiaddr.s_addr, IFGetIndex(hIf)) == 0)
    {
        /* Error: Unable to join the group. Clean memory. */
        mmFree(ptr_mcast_rec);
        return (ENOBUFS);
    }

    /* Once the group has been successfully joined add it to the socket list  */
    list_add ((LIST_NODE**)&ps->pMcastList, (LIST_NODE*)ptr_mcast_rec);

    /* Group has been joined successfully. */
    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function is called from the setsockopt to leave a multicast
 *      group. This function was added to make the IGMP Leave behavior
 *      similar to the standard 'socket' interface via the IP_DROP_MEMBERSHIP
 *      socket option.
 *
 *  @param[in]  hSock
 *      Handle to the socket on which the multicast group is leaving.
 *  @param[in]  ptr_ipmreq
 *      Multicast Request structure populated by the application which
 *      contains the Multicast group address and the address of the interface
 *      on which the group will be left.
 *
 *  @retval
 *   0          -   Success
 *  @retval
 *   Non Zero   -   Error
 */
int IGMPLeave (HANDLE hSock, struct ip_mreq* ptr_ipmreq)
{
    HANDLE          hIf;
    MCAST_SOCK_REC* ptr_mcast_rec;
    SOCK*           ps;

    /* Get access to the socket information. */
    ps = (SOCK *)hSock;

    /* Map the Interface IP Address to a handle. */
    hIf = BindIPHost2IF ((IPN)ptr_ipmreq->imr_interface.s_addr);
    if (!hIf)
        return (EINVAL);

    /* Search the socket list for a match */
    ptr_mcast_rec = (MCAST_SOCK_REC *)list_get_head ((LIST_NODE**)&ps->pMcastList);
    while (ptr_mcast_rec != NULL)
    {
        /* Check for a hit! */
        if (ptr_mcast_rec->mreq.imr_multiaddr.s_addr == ptr_ipmreq->imr_multiaddr.s_addr)
        {
            /* Found it! */
            IGMPLeaveHostGroup (ptr_mcast_rec->mreq.imr_multiaddr.s_addr, IFGetIndex(ptr_mcast_rec->hIf));

            /* Remove the node from the socket list. */
            list_remove_node ((LIST_NODE**)&ps->pMcastList, (LIST_NODE*) ptr_mcast_rec);

            /* Cleanup the allocated block of memory. */
            mmFree(ptr_mcast_rec);

            /* We are done. */
            return 0;
        }

        /* Get the next entry. */
        ptr_mcast_rec = (MCAST_SOCK_REC *)list_get_next ((LIST_NODE*)ptr_mcast_rec);
    }

    /* Control comes here implies that the multicast group being deleted was never
     * a member of the socket. */
    return EADDRNOTAVAIL;
}
