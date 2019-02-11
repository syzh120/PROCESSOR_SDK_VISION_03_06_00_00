/*
 * Copyright (c) 2012-2014 Texas Instruments Incorporated
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
 * ======== netsrv.c ========
 *
 * This module contains the service provider functions used to
 * implement the CONFIG system define in NETCFG, created by
 * NETCTRL and used by NETTOOLS.
 *
 */

#include <netmain.h>
#include <_stack.h>

/* Number of system IP Addresses */
static int fBooting = 0;

/* Copies of the Stack and OS config structures */
static IPCONFIG ipcfgcopy;
static OSENVCFG oscfgcopy;

/* Hook function to validate IPv4 address via protocols like RFC 5227 */
static NS_ValidateAddress validateAddressFxn = NULL;

/* NETCFG Configuration Tag Service Providers */
static int  SPService( HANDLE, uint, uint, uint, HANDLE );
static int  SPIpNet( HANDLE, uint, uint, uint, HANDLE );
static int  SPRoute( HANDLE, uint, uint, uint, HANDLE );
static int  SPConfig( HANDLE, uint, uint, uint, HANDLE );

/* Functions to spawn and kill NETTOOLS services */
static void ServiceCallback( HANDLE hCfgEntry, uint Status );
static void ServiceSpawn( HANDLE hCfg, HANDLE hCfgEntry );
static void ServiceKill( HANDLE hCfg, HANDLE hCfgEntry );
static void ServiceScan( HANDLE hCfg );

/* Configuration Initialization/Shutdown Order */
static uint OpenOrder[CFGTAG_MAX] =
    { CFGTAG_OS, CFGTAG_IP, CFGTAG_SERVICE,
      CFGTAG_IPNET, CFGTAG_ROUTE, CFGTAG_CLIENT,
      CFGTAG_SYSINFO, CFGTAG_ACCT, 0, 0, 0, 0, 0, 0, 0, 0 };

static uint CloseOrder[CFGTAG_MAX] =
    { CFGTAG_SERVICE, CFGTAG_ROUTE, CFGTAG_IPNET,
      CFGTAG_IP, CFGTAG_OS, CFGTAG_CLIENT,
      CFGTAG_SYSINFO, CFGTAG_ACCT, 0, 0, 0, 0, 0, 0, 0, 0 };

/*-------------------------------------------------------------------------- */
/* NS_PreBoot() */
/* This function must be called before any system initialization is */
/* performed. */
/*-------------------------------------------------------------------------- */
void NS_PreBoot()
{
    /* Our config service provider needs original copies of the */
    /* configuration arrays. */
    ipcfgcopy = _ipcfg;
    oscfgcopy = _oscfg;
}

/*-------------------------------------------------------------------------- */
/* NS_BootTask() */
/* This function is called as a task created by NETCTRL */
/* Note the call to TaskExit() at the end of the function. */
/*-------------------------------------------------------------------------- */
void NS_BootTask( HANDLE hCfg )
{
    /* Install the service provider callbacks */
    CfgSetService( hCfg, CFGTAG_OS,      &SPConfig );
    CfgSetService( hCfg, CFGTAG_IP,      &SPConfig );
    CfgSetService( hCfg, CFGTAG_SERVICE, &SPService );
    CfgSetService( hCfg, CFGTAG_IPNET,   &SPIpNet );
    CfgSetService( hCfg, CFGTAG_ROUTE,   &SPRoute );

    /* Set the configuration initialization order */
    CfgSetExecuteOrder( hCfg, CFGTAG_MAX, OpenOrder, CloseOrder );

    /* Enable the configuration */
    fBooting = 1;
    CfgExecute( hCfg, 1 );
    fBooting = 0;

    /* Now scan for loadable services */
    ServiceScan( hCfg );

    /* Inform NETCTRL of address count */
    /* This also boots the user tasks */
    NC_BootComplete();

    /* Exit this task thread */
    TaskExit();
}

void NS_setAddrHook(NS_ValidateAddress fxn)
{
    validateAddressFxn = fxn;
}

/*-------------------------------------------------------------------------- */
/* SPConfig() - CFGTAG_IP and CFGTAG_OS Service Provider */
/*-------------------------------------------------------------------------- */
static int SPConfig(HANDLE hCfg, uint Tag, uint Item, uint Op, HANDLE hCfgEntry)
{
    uint *pi,*pdst,*pdef;

    (void)hCfg;

    /* Get the information */
    if( CfgEntryInfo( hCfgEntry, 0, (UINT8 **)(&pi) ) < 0 )
        return( -1 );

    /* Setup to handle IP or OS */
    if( Tag == CFGTAG_IP )
    {
        /* Bound the value of Item */
        if( Item >= CFGITEM_IP_MAX )
            return( -1 );
        pdst = (uint *)&_ipcfg;
        pdef = (uint *)&ipcfgcopy;
    }
    else if( Tag == CFGTAG_OS )
    {
        /* Bound the value of Item */
        if( Item > CFGITEM_OS_MAX )
            return( -1 );
        pdst = (uint *)&_oscfg;
        pdef = (uint *)&oscfgcopy;
    }
    else
        return( -1 );

    /* Verify Item */
    if( !Item )
        return( -1 );
    Item--;

    /* If this is an "add", add the entry */
    if( Op == CFGOP_ADD )
        *(pdst+Item) = *pi;
    /* Else if "remove", restore the default */
    else if( Op == CFGOP_REMOVE )
        *(pdst+Item) = *(pdef+Item);

    /* Return success */
    return(1);
}

/*-------------------------------------------------------------------------- */
/* SPService() - CFGTAG_SERVICE Service Provider */
/*-------------------------------------------------------------------------- */
static int SPService(HANDLE hCfg, uint Tag, uint Item, uint Op, HANDLE hCfgEntry)
{
    CISARGS *pa;

    (void)Tag;

    /* If this is an "add", add the entry */
    if( Op == CFGOP_ADD )
    {
        /* If we can't get the info, just return */
        if( CfgEntryInfo( hCfgEntry, 0, (UINT8 **)(&pa) ) < 0 )
            return(-1);

        /* Set status to "waiting" */
        pa->Status     = CIS_SRV_STATUS_WAIT;
        pa->hService   = 0;
        pa->ReportCode = 0;

        /* Keep a local copy of the Item value */
        pa->Item       = Item;

        /* 
         * Most services are have qualification requirements before
         * they can be invoked. Since these qualifications must be
         * reviewed on every address add and removal, we don't
         * attempt to spawn the service here.
         *
         * An exception to this is the DHCP client service, which
         * in an attempt to speed up the boot process, we'll launch
         * ASAP.
         *
         * We don't invoke other services here. We will rescan the
         * service table if we're not booting. This will invoke
         * the new service if its requirements are met.
         */

        if( Item == CFGITEM_SERVICE_DHCPCLIENT )
            ServiceSpawn( hCfg, hCfgEntry );
        else if( !fBooting )
            ServiceScan( hCfg );
    }
    /* Else if this is a "remove", remove the entry */
    else if( Op == CFGOP_REMOVE )
    {
        /* Not only can tasks be removed here, but they can also */
        /* be removed if they loose their IP address. This is */
        /* done is ServiceScan(). In order to make this a little */
        /* cleaner, we use a single "kill" routine. */

        /* Remove the service */
        ServiceKill( hCfg, hCfgEntry );
    }

    /* Return success */
    return(1);
}

/*-------------------------------------------------------------------------- */
/* SPIpNet() - CFGTAG_IPNET Service Provider */
/*-------------------------------------------------------------------------- */
static int SPIpNet(HANDLE hCfg, uint Tag, uint Item, uint Op, HANDLE hCfgEntry)
{
    CI_IPNET *pi;
    HANDLE   hIF;

    (void)Tag;

    /* Get the information */
    if( CfgEntryInfo( hCfgEntry, 0, (UINT8 **)(&pi) ) < 0 )
        return( -1 );

    /* If this is an "add", add the entry */
    if( Op == CFGOP_ADD )
    {
        {
            NIMU_IF_REQ ifreq;

            /* Initialize the NIMU Interface Object. */
            mmZeroInit (&ifreq, sizeof(NIMU_IF_REQ));

            /*
             *  We are interested in receiving the handle associated with
             *  'index' Item
             */
            ifreq.index = Item;
            if (NIMUIoctl(NIMU_GET_DEVICE_HANDLE, &ifreq, &hIF, sizeof(HANDLE))
                    < 0)
                return -1;
        }

        /* Optionally, validate the IP address */
        if (validateAddressFxn) {
            if (!validateAddressFxn(pi->IPAddr)) {
                return (-1);
            }
        }

        /* Add the newtwork */
        pi->hBind = NtAddNetwork( hIF, pi->IPAddr, pi->IPMask );

        /* If network not added, return error */
        if( !pi->hBind )
            return(-1);

        /* Notify NetCtrl */
        NC_IPUpdate( pi->IPAddr, Item, 1 );
    }
    /* Else if this is a "remove", remove the entry */
    else if( Op == CFGOP_REMOVE )
    {
        /* If no network, return "pass" */
        if( !pi->hBind )
            return(0);

        /* Remove the network */
        NtRemoveNetwork( pi->hBind );
        pi->hBind = 0;

        /* BUG FIX SDSCM00014560 
         *  When an IP address is modified we need to close the sockets of all existing
         *  applications. */
        {
            SockCleanPcb (SOCKPROT_TCP, pi->IPAddr);
            SockCleanPcb (SOCKPROT_UDP, pi->IPAddr);
            SockCleanPcb (SOCKPROT_RAW, pi->IPAddr);
        }

        /* Notify NetCtrl */
        NC_IPUpdate( pi->IPAddr, Item, 0 );
    }

    /* Perform service maintenance when not in boot process */
    if( !fBooting )
        ServiceScan( hCfg );

    /* Return success */
    return(1);
}

/*-------------------------------------------------------------------------- */
/* SPRoute() - CFGTAG_ROUTE Service Provider */
/*-------------------------------------------------------------------------- */
static int SPRoute(HANDLE hCfg, uint Tag, uint Item, uint Op, HANDLE hCfgEntry)
{
    CI_ROUTE *pr;

    (void)hCfg;
    (void)Tag;
    (void)Item;

    /* Get the information */
    if( CfgEntryInfo( hCfgEntry, 0, (UINT8 **)(&pr) ) < 0 )
        return( -1 );

    /* If this is an "add", add the entry */
    if( Op == CFGOP_ADD )
    {
        /* Start calling STACK functions */
        llEnter();

        /* Create the route and make it STATIC */
        pr->hRoute = RtCreate( FLG_RTF_REPORT, FLG_RTE_GATEWAY,
                               pr->IPDestAddr & pr->IPDestMask,
                               pr->IPDestMask, 0, pr->IPGateAddr, 0 );

        /* Stop calling STACK functions */
        llExit();

        /* If route not added, return error */
        if( !pr->hRoute )
            return(-1);
    }
    /* Else if this is a "remove", remove the entry */
    else if( Op == CFGOP_REMOVE )
    {
        /* If no network, return "pass" */
        if( !pr->hRoute )
            return(0);

        /* Start calling STACK functions */
        llEnter();

        /* Remove the route */
        RtRemove( pr->hRoute, FLG_RTF_REPORT, RTC_NETUNREACH );

        /* DeRef it */
        RtDeRef( pr->hRoute );
        pr->hRoute = 0;

        /* Stop calling STACK functions */
        llExit();
    }

    /* Return success */
    return(1);
}


/*-------------------------------------------------------------------------- */
/* ServiceCallback() */
/* Function to receive callback information from NetTools Services */
/*-------------------------------------------------------------------------- */
static void ServiceCallback( HANDLE hCfgEntry, uint Status )
{
    CISARGS *pa;

    /* If we can't get the info, just return */
    if( CfgEntryInfo( hCfgEntry, 0, (UINT8 **)(&pa) ) < 0 )
        return;

    /* Save the report code */
    pa->ReportCode = Status;

    /* Callback status change if pCbSrv is set */
    if( pa->pCbSrv )
        (pa->pCbSrv)( pa->Item, pa->Status, pa->ReportCode, hCfgEntry );
}

/*-------------------------------------------------------------------------- */
/* ServiceSpawn() */
/* Spawn a service that is known ready */
/*-------------------------------------------------------------------------- */
static void ServiceSpawn( HANDLE hCfg, HANDLE hCfgEntry )
{
    CISARGS *pa;
    NTARGS  NTA;

    (void)hCfg;

    /* If we can't get the info, just return */
    if( CfgEntryInfo( hCfgEntry, 0, (UINT8 **)(&pa) ) < 0 )
        return;

    /* If the service is already running, return */
    if( pa->hService )
        return;

    /* Set default state */
    pa->Status     = CIS_SRV_STATUS_ENABLED;
    pa->ReportCode = 0;

    /* Setup NetTools Arguments */
    if( !(pa->Mode & CIS_FLG_IFIDXVALID) || (pa->Mode & CIS_FLG_CALLBYIP) )
    {
        NTA.CallMode = NT_MODE_IPADDR;
        NTA.IPAddr   = pa->IPAddr;
    }
    else
    {
        NTA.CallMode = NT_MODE_IFIDX;
        NTA.IfIdx    = pa->IfIdx;
    }

    /* Install our callback */
    NTA.hCallback = hCfgEntry;
    NTA.pCb       = &ServiceCallback;

    /* Launch Service */
    switch( pa->Item )
    {
#if NETSRV_ENABLE_TELNET
    case CFGITEM_SERVICE_TELNET:
        {
            CI_SERVICE_TELNET *pt = (CI_SERVICE_TELNET *)pa;
            pa->hService = TelnetOpen( &NTA, &(pt->param) );
        }
        break;
#endif

#if NETSRV_ENABLE_HTTP
    case CFGITEM_SERVICE_HTTP:
        {
            CI_SERVICE_HTTP *pt = (CI_SERVICE_HTTP *)pa;
            pa->hService = httpOpen( &NTA, &(pt->param) );
        }
        break;
#endif

#if NETSRV_ENABLE_NAT
    case CFGITEM_SERVICE_NAT:
        {
            CI_SERVICE_NAT *pt = (CI_SERVICE_NAT *)pa;
            pa->hService = NATOpen( &NTA, &(pt->param) );
        }
        break;
#endif

#if NETSRV_ENABLE_DHCPSERVER
    case CFGITEM_SERVICE_DHCPSERVER:
        {
            CI_SERVICE_DHCPS *pt = (CI_SERVICE_DHCPS *)pa;
            pa->hService = DHCPSOpen( &NTA, &(pt->param) );
        }
        break;
#endif

#if NETSRV_ENABLE_DHCPCLIENT
    case CFGITEM_SERVICE_DHCPCLIENT:
        {
            CI_SERVICE_DHCPC *pt = (CI_SERVICE_DHCPC *)pa;
            pa->hService = DHCPOpen( &NTA, &(pt->param) );
        }
        break;
#endif

#if NETSRV_ENABLE_DNSSERVER
    case CFGITEM_SERVICE_DNSSERVER:
        pa->hService = DNSServerOpen( &NTA );
        break;
#endif
    }

    /* Adjust status on failure */
    if( !pa->hService )
    {
        pa->Status = CIS_SRV_STATUS_FAILED;
        pa->ReportCode = 0;
    }

    /* Callback status change if pCbSrv is set */
    if( pa->pCbSrv )
        (pa->pCbSrv)( pa->Item, pa->Status, pa->ReportCode, hCfgEntry );
}

/*-------------------------------------------------------------------------- */
/* ServiceKill() */
/* Kill a service that may or may not be currently executing */
/*-------------------------------------------------------------------------- */
static void ServiceKill( HANDLE hCfg, HANDLE hCfgEntry )
{
    CISARGS *pa;

    (void)hCfg;

    /* If we can't get the info, just return */
    if( CfgEntryInfo( hCfgEntry, 0, (UINT8 **)(&pa) ) < 0 )
        return;

    /* If the service is not running, return */
    if( pa->Status != CIS_SRV_STATUS_ENABLED )
        return;

    /* Set status to DISABLED */
    pa->Status     = CIS_SRV_STATUS_DISABLED;
    pa->ReportCode = 0;

    if( pa->hService )
    {
        switch( pa->Item )
        {
#if NETSRV_ENABLE_TELNET
        case CFGITEM_SERVICE_TELNET:
            TelnetClose( pa->hService );
            break;
#endif

#if NETSRV_ENABLE_HTTP
        case CFGITEM_SERVICE_HTTP:
            httpClose( pa->hService );
            break;
#endif

#if NETSRV_ENABLE_NAT
        case CFGITEM_SERVICE_NAT:
            NATClose( pa->hService );
            break;
#endif

#if NETSRV_ENABLE_DHCPSERVER
        case CFGITEM_SERVICE_DHCPSERVER:
            DHCPSClose( pa->hService );
            break;
#endif

#if NETSRV_ENABLE_DHCPCLIENT
        case CFGITEM_SERVICE_DHCPCLIENT:
            DHCPClose( pa->hService );
            break;
#endif

#if NETSRV_ENABLE_DNSSERVER
        case CFGITEM_SERVICE_DNSSERVER:
            DNSServerClose( pa->hService );
            break;
#endif
        }
    }

    /* Clear service just to be safe */
    pa->hService = 0;

    /* Callback status change if pCbSrv is set */
    if( pa->pCbSrv )
        (pa->pCbSrv)( pa->Item, pa->Status, pa->ReportCode, hCfgEntry );
}

/*-------------------------------------------------------------------------- */
/* ServiceScan() */
/* Scan services and Spawn and Kill as necessary */
/*-------------------------------------------------------------------------- */
static void ServiceScan( HANDLE hCfg )
{
    CISARGS *pa;
    HANDLE  hCfgEntry;
    int     cfgret,Item;

    /* This is a standard walk of the configuration */
    for( Item=1; Item<=CFGITEM_SERVICE_MAX; Item++ )
    {
        cfgret = CfgGetEntry( hCfg, CFGTAG_SERVICE, Item, 1, &hCfgEntry );
        while( cfgret == 1 )
        {
            /* If we can't get the info, skip it */
            if( CfgEntryInfo( hCfgEntry, 0, (UINT8 **)(&pa) ) < 0 )
                goto item_done;

            /* If we're waiting, see if there's an IP address ready */
            if( pa->Status == CIS_SRV_STATUS_WAIT )
            {
                /* If the task is not using "ResolveIP", it can always */
                /* start. Otherwise; see if there's an IP address */
                /* available. */
                if( pa->Mode & CIS_FLG_RESOLVEIP )
                {
                    /* Here we must check and see if we have an address */
                    if( !NtIfIdx2Ip(pa->IfIdx, &pa->IPAddr) )
                        goto item_done;
                }

                /* If we get here, the service can start */
                ServiceSpawn( hCfg, hCfgEntry );
            }
            /* Else we examine services that are running to see if they */
            /* should be killed. */
            else if( pa->Status == CIS_SRV_STATUS_ENABLED )
            {
                HANDLE hTmp;

                /* If the task is not using "ResolveIP", it is never */
                /* terminated here. */
                if( !(pa->Mode & CIS_FLG_RESOLVEIP) )
                    goto item_done;

                /* Verify the IP address still exists */
                llEnter();
                hTmp = BindIPHost2IF( pa->IPAddr );
                llExit();

                /* Kill the task if the IPAddr is no longer in the system */
                if( !hTmp )
                {
                    /* Kill the service */
                    ServiceKill( hCfg, hCfgEntry );

                    /* Set new service state based on behaviour flag */
                    if( pa->Mode & CIS_FLG_RESTARTIPTERM )
                        pa->Status = CIS_SRV_STATUS_WAIT;
                    else
                        pa->Status = CIS_SRV_STATUS_IPTERM;
                }
            }

item_done:
            /* Get the next entry - also releases current entry */
            cfgret = CfgGetNextEntry( hCfg, hCfgEntry, &hCfgEntry );
        }
    }
}
