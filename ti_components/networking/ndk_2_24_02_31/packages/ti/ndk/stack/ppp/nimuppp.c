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
 * ======== nimuppp.c ========
 *
 *  This file has functions which implement the PPP Driver to be compliant
 *  with the  Network Interface Management Unit (NIMU). The driver is based
 *  on the original PPP driver but because of the number of changes to the
 *  driver to make it NIMU compliant it was decided to break it into two
 *  seperate files for clarity and readability.
 *
 *  The file is only compiled if NIMU support and PPP is enabled.
 *
 */

#include <stkmain.h>
#include <netmain.h>
#include "ppp.h"

#ifdef _INCLUDE_PPP_CODE

/*********************************************************************
 * FUNCTION NAME : PPPStart
 *********************************************************************
 * DESCRIPTION   :
 *  The function is used to initialize and start the PPP Protocol
 *
 * RETURNS       :
 *  0   -   Success
 *  <0  -   Error
 *********************************************************************/
static int PPPStart (NETIF_DEVICE* ptr_net_device)
{
    PPP_SESSION*    p;

    /* Get the PPP Session Information from the network device. */
    p = (PPP_SESSION *)ptr_net_device->pvt_data;

    /* Init PPP Protocols */
    lcpInit( (HANDLE)p );
    authInit( (HANDLE)p );
    ipcpInit( (HANDLE)p );

    /* Open LCP */
    lcpOpen( (HANDLE)p, 1 );
    return 0;
}

/*********************************************************************
 * FUNCTION NAME : PPPStop
 *********************************************************************
 * DESCRIPTION   :
 *  The function is used to de-initialize and stop the PPP protocol
 *
 * RETURNS       :
 *  0   -   Success
 *  <0  -   Error
 *********************************************************************/
static int PPPStop (NETIF_DEVICE* ptr_net_device)
{
    PPP_SESSION*    p;

    /* Get the PPP Session Information from the network device. */
    p = (PPP_SESSION *)ptr_net_device->pvt_data;
    if( !p || p->Type != HTYPE_PPP )
    {
        DbgPrintf(DBG_ERROR,"PPPStop: Bad Handle %08x",p);
        return -1;
    }

    /* close down LCP if ref count is INUSE_IDLE and not LOCKED */
    if( p->InUse != INUSE_LOCKED )
    {
        if( p->InUse > INUSE_IDLE )
        {
            p->InUse--;                 /* Deref one count */
        }
        else
        {
            /* Close protocols (closing LCP is sufficient) */
            lcpClose( p );

            /* Lock ref count */
            p->InUse = INUSE_LOCKED;
        }
    }
    return 0;
}

/*********************************************************************
 * FUNCTION NAME : PPPSend
 *********************************************************************
 * DESCRIPTION   :
 *  The function is the interface routine invoked by the NDK stack to
 *  pass packets to the driver. 
 *
 * RETURNS       :
 *  0   -   Success
 *  <0  -   Error
 *********************************************************************/
static int PPPSend (NETIF_DEVICE* ptr_net_device, PBM_Handle hPkt)
{
    PPP_SESSION*    p;

    /* Get the PPP Session Information from the network device. */
    p = (PPP_SESSION *)ptr_net_device->pvt_data;

    /* Use the call back function to interface this with the PPPoE 
     * Layer. NOTE: We will send packets only if the PPP connection
     * is UP and RUNNING; else packets are dropped. */
    if( p->hNet || p->hRoute )
    {
        /* Pass the packet through the call back API for transmission. */            
        p->SICtrl( p->hSI, SI_MSG_SENDPACKET, PPPPROT_IP, (PBM_Pkt *)hPkt);
        return 0;
    }

    /* The connection was not up and running; unable to transmit the
     * packet. */
    return -1;
}

/*********************************************************************
 * FUNCTION NAME : pppNew
 *********************************************************************
 * DESCRIPTION   :
 *  The API is used to create a new PPP device instance. The function
 *  has been modified from the original version to be compatible with
 *  the NIMU architecture. The function creates a network interface
 *  object and registers this with the Network Interface Management
 *  Unit.
 *
 * RETURNS       :
 *  Handle to the PPP connection   -   Success
 *  NULL                           -   Error
 *********************************************************************/
HANDLE pppNew( HANDLE hSI, uint pppFlags, uint mru,
               IPN IPServer, IPN IPMask, IPN IPClient,
               char *Username, char *Password, UINT32 cmap,
               void (*SICtrl)( HANDLE, uint, UINT32, PBM_Pkt * ) )
{
    PPP_SESSION*    p;
    NETIF_DEVICE*   ptr_ppp_device;

    /* Allocate space for PPP Session */
    if( !(p = mmAlloc( sizeof(PPP_SESSION) )) )
    {
        DbgPrintf(DBG_WARN,"pppNew: OOM");
        NotifyLowResource();
        return(0);
    }

    /* Initialize the allocated block of memory. */
    mmZeroInit( p, sizeof(PPP_SESSION) );

    /* Initialize the session structure. */
    p->Type     = HTYPE_PPP;
    p->InUse    = INUSE_IDLE;
    p->hSI      = hSI;
    p->ProtMTU  = mru;
    p->SICtrl   = SICtrl;
    p->Flags    = pppFlags;
    p->MTU_Phys = mru;
    p->CMap     = cmap;
    p->MTU_Tx   = p->MTU_Phys;
    p->MTU_Rx   = p->MTU_Phys;

    /* Allocate memory for the NIMU Network Interface Object. */
    ptr_ppp_device = mmAlloc(sizeof(NETIF_DEVICE));
    if (ptr_ppp_device == NULL)
    {
        DbgPrintf(DBG_WARN,"pppNew: OOM");
        NotifyLowResource();
        return(0);
    }

    /* Initialize the allocated memory block. */
    mmZeroInit (ptr_ppp_device, sizeof(NETIF_DEVICE));

    /* Link the PPP Session and NIMU Objects together */
    ptr_ppp_device->pvt_data    = (void *)p;
    p->ptr_ppp_device           = ptr_ppp_device;

    /* Populate the Network Interface Object. */
    strcpy (ptr_ppp_device->name, "ppp0");
    ptr_ppp_device->mtu         = mru;

    /* PPP does not need to have an ARP protocol. */
    ptr_ppp_device->flags       = ptr_ppp_device->flags | NIMU_DEVICE_NO_ARP;

    /* Populate the Driver Interface Functions. */
    ptr_ppp_device->start       = PPPStart;
    ptr_ppp_device->stop        = PPPStop;
    ptr_ppp_device->poll        = NULL;
    ptr_ppp_device->send        = PPPSend;
    ptr_ppp_device->pkt_service = NULL;
    ptr_ppp_device->ioctl       = NULL;
    ptr_ppp_device->add_header  = NULL;

    /* Register the device with NIMU */
    if (NIMURegister (ptr_ppp_device) < 0)
    {
        DbgPrintf(DBG_INFO, "pppNew: Error: Unable to register the PPP Device\n");
        return 0;
    }

    /* Reread the device index received after the NIMURegister as it will have
     * a unique value assigned to the interface. */
    p->llIndex  = ptr_ppp_device->index;

    /* Remaining options are server/client dependent */
    if( p->Flags & PPPFLG_SERVER )
    {
        /* Set the local and peer IP addr */
        p->IPClient = IPClient;
        p->IPServer = IPServer;
        p->IPMask   = IPMask;

        /* If using MS extensions, get the current DNS and NBNS IP addrs */
        if( p->Flags & PPPFLG_OPT_USE_MSE )
        {
            if( p->Flags & PPPFLG_OPT_LOCALDNS )
            {
                /* Read the default DNS and NBNS */
                p->IPDNS1   = IPServer;
                p->IPDNS2   = 0x0;
            }
            else
            {
                /* Here we go external to get the DNS servers */
                llExit();
                CfgGetImmediate( 0, CFGTAG_SYSINFO,
                                 CFGITEM_DHCP_DOMAINNAMESERVER, 1,
                                 sizeof(p->IPNBNS1), (UINT8 *)&p->IPDNS1);
                CfgGetImmediate( 0, CFGTAG_SYSINFO,
                                 CFGITEM_DHCP_DOMAINNAMESERVER, 2,
                                 sizeof(p->IPNBNS2), (UINT8 *)&p->IPDNS2);
                llEnter();
            }

            /* We always go external to get the NBNS servers */
            llExit();
            CfgGetImmediate( 0, CFGTAG_SYSINFO, CFGITEM_DHCP_NBNS, 1,
                             sizeof(p->IPNBNS1), (UINT8 *)&p->IPNBNS1);
            CfgGetImmediate( 0, CFGTAG_SYSINFO, CFGITEM_DHCP_NBNS, 2,
                             sizeof(p->IPNBNS2), (UINT8 *)&p->IPNBNS2);
            llEnter();
        }
    }
    else
    {
        if( Username && strlen(Username) < sizeof(p->UserId) )
            strcpy( p->UserId, Username );
        if( Password && strlen(Password) < sizeof(p->Password) )
            strcpy( p->Password, Password );
    }

    return( (HANDLE)p );
}

/*********************************************************************
 * FUNCTION NAME : pppFree
 *********************************************************************
 * DESCRIPTION   :
 *  The API is used to close and cleanup an existing PPP connection.
 *********************************************************************/
void pppFree( HANDLE hPPP )
{
    PPP_SESSION*    p;

    /* Get the PPP Session Information and validate it. */    
    p = (PPP_SESSION *)hPPP;
    if( !p )
    {
        DbgPrintf(DBG_ERROR,"pppFree: Bad Handle %08x",p);
        return;
    }
    else if( p->Type != HTYPE_PPP )
    {
        DbgPrintf(DBG_ERROR,"pppFree: Error: Type (%d) != HTYPE_PPP", p->Type);
        return;
    }

    /* Remove the route if we have one */
    if( p->hRoute )
    {
        RtRemove( p->hRoute, FLG_RTF_REPORT, RTC_NETUNREACH );
        RtDeRef( p->hRoute );
    }

    /* Remove all configuration entries */

    /* Remove client record if any */
    if( p->hClient )
    {
        CfgRemoveEntry( 0, p->hClient );
    }

    /* Remove the IP address */
    if ( p->hNet )
	{
        llExit();
        CfgRemoveEntry(0, p->hNet);
        llEnter();
    }

    /* Unregister and stop the device. */
    if (NIMUUnregister(p->ptr_ppp_device) < 0)
    {
        DbgPrintf(DBG_INFO,
                "pppFree: Error: Unregistering PPP device %d failed\n",
                p->llIndex);
    }

    /* Cleanup the memory allocated in pppNew (ptr_ppp_device freed by NIMU) */
    mmFree (p);

    return;
}

/*-------------------------------------------------------------------- */
/* pppTimer() */
/* Timer function called once per second */
/*-------------------------------------------------------------------- */
void pppTimer( HANDLE hPPP )
{
    PPP_SESSION *p = (PPP_SESSION *)hPPP;

    if( !p || p->Type != HTYPE_PPP )
    {
        DbgPrintf(DBG_ERROR,"pppTimer: Bad Handle %08x",p);
        return;
    }

    /* Add reference and execute */
    if( p->InUse < (INUSE_LOCKED-1) )
    {
        p->InUse++;

        lcpTimer( p );
        authTimer( p );
        ipcpTimer( p );

        /* Remove reference */
        if( p->InUse == INUSE_IDLE )
            pppFree( p );
        else
            p->InUse--;
    }
}

/*-------------------------------------------------------------------- */
/* pppInput() */
/* Called when a packet is received by the serial interface */
/*-------------------------------------------------------------------- */
void pppInput( HANDLE hPPP, PBM_Pkt *pPkt )
{
    PPP_SESSION *p = (PPP_SESSION *)hPPP;
    UINT16      type;
    UINT8       *pb;

    if( !p || p->Type != HTYPE_PPP )
    {
        DbgPrintf(DBG_ERROR,"pppInput: Bad Handle %08x",p);
        PBM_free( pPkt );
        return;
    }

    if( !pPkt || pPkt->ValidLen < 2 )
    {
        DbgPrintf(DBG_ERROR,"pppInput: Bad packet!");
        return;
    }

    /* Add reference and execute */
    if( p->InUse < (INUSE_LOCKED-1) )
    {
        p->InUse++;

        /* Set pb to point to PPP header */
        pb = pPkt->pDataBuffer + pPkt->DataOffset;

        /* Adjust packet to point to next header */
        pPkt->DataOffset += 2;
        pPkt->ValidLen   -= 2;

        type = RdNet16s(pb);

        switch( type )
        {
        case PPPPROT_IP:
            /* Only pass IP if hNet or hRoute is set */
            if( p->hNet || p->hRoute )
            {
                /* Setup packet to look like it came from Ethernet */
                pPkt->hIFRx       = p->ptr_ppp_device;
                pPkt->EtherType   = 0x800;

                /* Give it to IP */
                IPRxPacket( pPkt );     /* Consume packet */
                break;
            }
            PBM_free( pPkt );           /* Free packet */
            break;

        case PPPPROT_LCP:
            lcpInput( p, pPkt );        /* Consume packet */
            break;

        case PPPPROT_PAP:
            papInput( p, pPkt );        /* Consume packet */
            break;

        case PPPPROT_CHAP:
            chapInput( p, pPkt );       /* Consume packet */
            break;

        case PPPPROT_IPCP:
            ipcpInput( p, pPkt );       /* Consume packet */
            break;

        default:
            /* Put the protocol back on the packet */
            pPkt->DataOffset -= 2;
            pPkt->ValidLen   += 2;
            lcpReject( p, pPkt );       /* Reject packet */
            break;
        }

        /* Remove reference */
        if( p->InUse == INUSE_IDLE )
            pppFree( p );
        else
            p->InUse--;
    }
}

/*-------------------------------------------------------------------- */
/* pppAddIP() */
/* Local function to add IP address via the configuration system */
/*-------------------------------------------------------------------- */
static HANDLE pppAddIP( uint Index, uint NetType, IPN IPAddr, IPN IPMask )
{
    CI_IPNET NA;
    int      rc;
    HANDLE   hNet;

    /* Initialize Network Address */
    mmZeroInit( &NA, sizeof(NA) );
    NA.NetType = NetType;
    NA.IPAddr  = IPAddr;
    NA.IPMask  = IPMask;
    NDK_sprintf( NA.Domain, "localppp%d.net", Index );

    /* Add the Entry */
    /* Note we need to keep a copy of the address we add in the event */
    /* that we need to remove it later. An alternate way of doing this */
    /* would be to search the configuration for the entry we want to */
    /* remove once its time, but this way is cleaner. */
    llExit();
    rc = CfgAddEntry( 0, CFGTAG_IPNET, Index,
            CFG_ADDMODE_NOSAVE | CFG_ADDMODE_UNIQUE, sizeof(CI_IPNET),
            (UINT8 *)&NA, &hNet );
    if( rc < 0 )
    {
        /* If this is a service error, the entry was still added */
        if( rc <= CFGERROR_SERVICE )
            CfgRemoveEntry( 0, hNet );
        hNet = 0;
    }
    llEnter();

    return(hNet);
}

/*-------------------------------------------------------------------- */
/* pppAddClient() */
/* Local function to add a client record to the configuration system */
/*-------------------------------------------------------------------- */
static HANDLE pppAddClient( uint Index, IPN IPAddr, INT8 *Name )
{
    CI_CLIENT CC;
    int       rc;
    HANDLE    hClient;

    /* Initialize Network Address */
    mmZeroInit( &CC, sizeof(CC) );

    CC.ClientType = CFG_CLIENTTYPE_DYNAMIC;
    CC.IPAddr     = IPAddr;
    CC.Status     = CFG_CLIENTSTATUS_STATIC;

    if (strlen(Name) < CFG_HOSTNAME_MAX) {
        strcpy( CC.Hostname, Name );
    }
    else {
        return (0);
    }

    /* Add it to the configuration */
    llExit();
    rc = CfgAddEntry( 0, CFGTAG_CLIENT, Index, CFG_ADDMODE_NOSAVE,
                      sizeof(CI_CLIENT), (UINT8 *)&CC, &hClient );
    if( rc < 0 )
    {
        /* If this is a service error, the entry was still added */
        if( rc <= CFGERROR_SERVICE )
            CfgRemoveEntry( 0, hClient );
        hClient = 0;
    }
    llEnter();

    return(hClient);
}

/*-------------------------------------------------------------------- */
/* pppEvent() */
/* Event function called by upper level protocols */
/*-------------------------------------------------------------------- */
void pppEvent( HANDLE hPPP, uint Event )
{
    PPP_SESSION *p = (PPP_SESSION *)hPPP;
    NETIF_DEVICE*   ptr_ppp_device;

    switch( Event )
    {
    case PPP_EVENT_LCP_CONNECT:
        if( p->auth.Protocol )
        {
            authStart( p );
            p->SICtrl( p->hSI, SI_MSG_CALLSTATUS, SI_CSTATUS_AUTHORIZE, 0);
            break;
        }

        /* Fallthrough ... */

    case PPP_EVENT_AUTH_CONNECT:
        ipcpStart( p );
        p->SICtrl( p->hSI, SI_MSG_CALLSTATUS, SI_CSTATUS_CONFIGURE, 0);
        break;

    case PPP_EVENT_IPCP_CONNECT:
        /* Use the smallest of all the MTU's */
        if( p->ProtMTU > p->MTU_Tx )
            p->ProtMTU = p->MTU_Tx;
        if( p->ProtMTU > p->MTU_Rx )
            p->ProtMTU = p->MTU_Rx;

        /* Get the pointer to the PPP Network Interface Object */
        ptr_ppp_device = NIMUFindByIndex (p->llIndex);
        if (ptr_ppp_device == NULL)
        {
            DbgPrintf(DBG_ERROR,"pppEvent: NIMU Object for PPP %d does not exist", p->llIndex);
            return;
        }

        if( p->Flags & PPPFLG_SERVER )
        {
            /* SERVER MODE */

            /* Create the Local Address */
            if( p->Flags & PPPFLG_OPT_LOCALDNS )
            {
                p->hNet = pppAddIP( p->llIndex,
                                    CFG_NETTYPE_DYNAMIC | CFG_NETTYPE_VIRTUAL,
                                    p->IPServer, p->IPMask );
                p->hClient = pppAddClient(p->llIndex, p->IPClient, p->UserId);
            }
            else
                p->hNet = pppAddIP( p->llIndex, CFG_NETTYPE_DYNAMIC,
                                    p->IPServer, p->IPMask );

            /* Create a route to the client. Also proxy it just in case its */
            /* on the same subnet as our Ethernet devices. */
            p->hRoute = RtCreate( FLG_RTF_REPORT, FLG_RTE_PROXY | FLG_RTE_HOST,
                                  p->IPClient, 0xffffffff, (HANDLE)ptr_ppp_device, 0, 0 );
        }
        else
        {
            /* CLIENT MODE */

            /* Create the Local Address */
            p->hNet = pppAddIP( p->llIndex, CFG_NETTYPE_DYNAMIC,
                                p->IPClient, 0xffffffff );

            /* If point to point mode, create a direct route */
            if( p->Flags & PPPFLG_OPT_CLIENT_P2P )
                p->hRoute = RtCreate( FLG_RTF_REPORT, FLG_RTE_PROXY | FLG_RTE_HOST,
                                      p->IPServer, 0xffffffff, (HANDLE)ptr_ppp_device, 0, 0 );
            /* Else create a default route that sends everything up this uplink */
            else
                p->hRoute = RtCreate( FLG_RTF_REPORT, 0, 0, 0, (HANDLE)ptr_ppp_device, 0, 0 );

            /* If using MS extensions, record the new values */
            if( p->Flags & PPPFLG_OPT_USE_MSE )
            {
                HANDLE hEntry;

                llExit();

                /* Remove all current DNS Entries from configuration */
                while( CfgGetEntry( 0, CFGTAG_SYSINFO,
                       CFGITEM_DHCP_DOMAINNAMESERVER, 1, &hEntry ) )
                    CfgRemoveEntry( 0, hEntry );

                /* Remove all current NBNS Entries from configuration */
                while( CfgGetEntry( 0, CFGTAG_SYSINFO,
                       CFGITEM_DHCP_NBNS, 1, &hEntry ) )
                    CfgRemoveEntry( 0, hEntry );

                /* Add the entries we got from the server */
                if( p->IPDNS1 )
                    CfgAddEntry( 0, CFGTAG_SYSINFO,
                                 CFGITEM_DHCP_DOMAINNAMESERVER,
                                 CFG_ADDMODE_NOSAVE,
                                 4, (UINT8 *)&p->IPDNS1, 0 );

                if( p->IPDNS2 )
                    CfgAddEntry( 0, CFGTAG_SYSINFO,
                                 CFGITEM_DHCP_DOMAINNAMESERVER,
                                 CFG_ADDMODE_NOSAVE,
                                 4, (UINT8 *)&p->IPDNS2, 0 );

                if( p->IPNBNS1 )
                    CfgAddEntry( 0, CFGTAG_SYSINFO,
                                 CFGITEM_DHCP_NBNS,
                                 CFG_ADDMODE_NOSAVE,
                                 4, (UINT8 *)&p->IPNBNS1, 0 );

                if( p->IPNBNS2 )
                    CfgAddEntry( 0, CFGTAG_SYSINFO,
                                 CFGITEM_DHCP_NBNS,
                                 CFG_ADDMODE_NOSAVE,
                                 4, (UINT8 *)&p->IPNBNS2, 0 );

                llEnter();
            }
        }
        p->SICtrl( p->hSI, SI_MSG_CALLSTATUS, SI_CSTATUS_CONNECTED, 0);
        break;

    case PPP_EVENT_LCP_STOPPED:
        p->SICtrl( p->hSI, SI_MSG_CALLSTATUS, SI_CSTATUS_DISCONNECT_LCP, 0);
        break;

    case PPP_EVENT_AUTH_STOPPED:
        p->SICtrl( p->hSI, SI_MSG_CALLSTATUS, SI_CSTATUS_DISCONNECT_AUTH, 0);
        break;

    case PPP_EVENT_IPCP_STOPPED:
        p->SICtrl( p->hSI, SI_MSG_CALLSTATUS, SI_CSTATUS_DISCONNECT_IPCP, 0);
        break;
    }
}

#endif /* _INCLUDE_PPP_CODE */

