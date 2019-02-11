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
 * ======== dnscomn.c ========
 *
 * DNS common routines
 *
 */

#include "dns.h"

static int DNSResolveByName( DNSREC *pQuery, DNSREPLY *pReply );
static int DNSResolveByNS( DNSREC *pQuery, DNSREPLY *pReply );
static int DNSResolveByAddr( DNSREC *pQuery, DNSREPLY *pReply );
static int DNSResolveExternal( DNSREC *pQuery, DNSREPLY *pReply );

/*-------------------------------------------------------------------- */
/* DNSResolveQuery() */

/* Answer a question posed in pQuery and return in ppReply */

/* Returns 1 if DNSREPLY created */
/*-------------------------------------------------------------------- */
int DNSResolveQuery( UINT16 ReqType, DNSREC *pQuery, DNSREPLY **ppReply )
{
    DNSREPLY *pReply;

    /* Allocate a reply record */
    pReply = mmAlloc( sizeof(DNSREPLY) );
    if( !pReply )
        return(0);
    bzero( pReply, sizeof(DNSREPLY) );

    /* Initial Flags Settings */
    pReply->Flags = ReqType | FLG_DNS_RA | FLG_DNS_QR;

    /* We only handle standard queries */
    if( ReqType != DNS_OP_STD )
    {
        pReply->Flags |= NOTIMP;
        return(1);
    }

    /* Locally we only support internet */
    if( pQuery->Class != C_IN )
        goto external_servers;

    /* First try and resolve the query locally. If this is not */
    /* possible, we'll go to outside DNS servers. */
    switch( pQuery->Type )
    {
    case T_CNAME:
        /* We don't support DNS aliasing, so CNAME is pointless. */
        /* We treat is like an address lookup and we'll include */
        /* a CNAME record in address lookup. */

        /* Fallthrough */

    case T_A:
        /* Address lookup is simple. If the domain matches one of */
        /* our local domains we give an authoritative answer. */

        /* We'll search for the hostname on the supplied domain. */

        /* If the hostname is our hostname, we match all local */
        /* domains. */

        /* Try and resolve by domain */
        if( DNSResolveByName( pQuery, pReply ) )
        {
            *ppReply = pReply;
            return(1);
        }

        /* Handle by outside servers */
        break;

    case T_NS:
        /* The Nameserver request looks up a name server for a */
        /* particular domain. If the domain matches one of our */
        /* local domains we just tack on our local host name. */
        /* Otherwise, we pass this question on. */

        /* Try and resolve by domain */
        if( DNSResolveByNS( pQuery, pReply ) )
        {
            *ppReply = pReply;
            return(1);
        }

        /* Handle by outside servers */
        break;

    case T_PTR:
        /* Here the request is to match an IP address with a host. */
        /* If the IP address is contained in one of our local */
        /* networks, we can give an authoritative answer. */
        /* Try and resolve by address */
        if( DNSResolveByAddr( pQuery, pReply ) )
        {
            *ppReply = pReply;
            return(1);
        }

        /* Handle by outside servers */
        break;
#ifdef _INCLUDE_IPv6_CODE
    case T_AAAA:
        /* We do not do local DNS lookups for IPv6 addresses
         * since we do not have Configuration Support for 
         * IPv6 yet. For now only external lookups possible
         * for IPv6.
         */
        /* Just fall through */
#endif
    default:
        /* We don't handle the oddball stuff */
        break;
    }

    /* If we get here we were unable to answer the question using */
    /* local informaiton. */
external_servers:
    if( DNSResolveExternal( pQuery, pReply ) )
    {
        *ppReply = pReply;
        return(1);
    }

    /* The following is executed when we have no reply */
    DNSReplyFree( pReply, 1 );
    return(0);
}

/*-------------------------------------------------------------------- */
/* DNSReplyFree() */
/* Free a DNS reply and all records */
/*-------------------------------------------------------------------- */
void DNSReplyFree( DNSREPLY *pReply, uint fFreeReplyBuffer )
{
    DNSREC *pRec;

    while( pReply->NumAns-- )
    {
        pRec = pReply->pAns;
        pReply->pAns = pReply->pAns->pNext;
        mmFree( pRec );
    }

    while( pReply->NumAuth-- )
    {
        pRec = pReply->pAuth;
        pReply->pAuth = pReply->pAuth->pNext;
        mmFree( pRec );
    }

    while( pReply->NumAux-- )
    {
        pRec = pReply->pAux;
        pReply->pAux = pReply->pAux->pNext;
        mmFree( pRec );
    }

    if( fFreeReplyBuffer )
        mmFree( pReply );
}

/*********************************************************************
 * FUNCTION NAME : DNSResolveByName
 *********************************************************************
 * DESCRIPTION   :
 *  The function resolves the name.
 *
 * RETURNS       :
 *  1   -   If the answer in pReply is authoritative.
 *  0   -   If we dont handle the domain.
 *********************************************************************/
static int DNSResolveByName( DNSREC *pQuery, DNSREPLY *pReply )
{
    CI_IPNET  ci_net;
    CI_CLIENT ci_client;
    IPN       IPAddr;
    int       rc,i,j,k,tmp;
    DNSREC    *pRec;
    char      *pbComp;
    char      HostnameCmp[CFG_HOSTNAME_MAX];
    char      Hostname[CFG_HOSTNAME_MAX];
    uint      fAuth = 0;
    UINT16    ifcnt;
    UINT16*   device_index;
    int       ret_code;

    /* Get the number of interfaces in the System */
    ret_code = NIMUIoctl (NIMU_GET_NUM_NIMU_OBJ, NULL, &ifcnt, sizeof(ifcnt));
    if (ret_code < 0)
    {
        DbgPrintf(DBG_INFO,
                "DNSResolveByName: NIMUIOCTL (NIMU_GET_NUM_NIMU_OBJ) Failed with error code: %d\n",
                ret_code);
        return 0;
    }

    /* Allocate memory to get the device handles for all devices. */
    device_index = mmAlloc (sizeof(UINT16)*ifcnt);
    if(device_index == NULL)
    {
        DbgPrintf(DBG_INFO, "DNSResolveByName: FATAL Error: Out of memory\n");
        return 0;
    }

    /* Get information about all the device handles present. */
    ret_code = NIMUIoctl(NIMU_GET_ALL_INDEX, NULL, device_index,
            sizeof(UINT16) * ifcnt);

    if (ret_code < 0)
    {
        DbgPrintf(DBG_INFO,
                "DNSResolveByName: NIMUIOCTL (NIMU_GET_ALL_INDEX) Failed with error code: %d\n",
                ret_code);
        mmFree (device_index);
        return 0;
    }
    
    /* Scan all IF's in the CFG for network information */
    for( i=0; i<ifcnt; i++ )
    {
        j = 1;
        for(;;)
        {
            rc = CfgGetImmediate( 0, CFGTAG_IPNET, *(device_index + i), j,
                                  sizeof(ci_net), (UINT8 *)&ci_net );
            if( rc <= 0 )
                break;

            /* We only care about VIRTUAL addresses */
            if( !(ci_net.NetType & CFG_NETTYPE_VIRTUAL) )
                goto HostnameNotFound;

            /* Try this network */

            pbComp = (char *)pQuery->Name;

            /* Take off one level of naming */
            while( *pbComp && *pbComp != '.' )
                pbComp++;
            if( *pbComp )
                pbComp++;

            while( strlen( pbComp ) )
            {
                if( !stricmp( pbComp, ci_net.Domain ) )
                {
                    /* Host belongs to this domain */
                    bzero( Hostname, sizeof( Hostname ) );

                    /* Isolate the host name into HostnameCmp */
                    tmp = pbComp - (char *)pQuery->Name - 1;
                    if( tmp <= 0 || tmp > (CFG_HOSTNAME_MAX-1) )
                        goto HostnameNotFound;
                    bcopy( pQuery->Name, HostnameCmp, tmp );
                    HostnameCmp[tmp] = 0;

                    /* If the hostname is us, we match */
                    tmp = CfgGetImmediate( 0, CFGTAG_SYSINFO,
                                           CFGITEM_DHCP_HOSTNAME, 1,
                                           sizeof(Hostname)-1,
                                           (UINT8 *)Hostname);
                    Hostname[tmp]=0;

                    if( !stricmp( HostnameCmp, Hostname ) )
                    {
                        IPAddr = ci_net.IPAddr;
                        goto HostnameFound;
                    }

                    /* Search all clients */
                    k = 1;
                    for(;;)
                    {
                        rc = CfgGetImmediate( 0, CFGTAG_CLIENT, *(device_index + i), k,
                                              sizeof(ci_client),
                                              (UINT8 *)&ci_client );
                        if( rc <= 0 )
                            break;

                        /* If the hostname matches this client, we match */
                        /* Check only VALID and STATIC entries */
                        if( ((ci_client.Status == CFG_CLIENTSTATUS_VALID) ||
                            (ci_client.Status == CFG_CLIENTSTATUS_STATIC)) &&
                            !stricmp(HostnameCmp, ci_client.Hostname) )
                        {
                            strcpy( Hostname, ci_client.Hostname );
                            IPAddr = ci_client.IPAddr;
                            goto HostnameFound;
                        }
                        k++;
                    }

                    /* Host name was not found */
                    fAuth = 1;
                    goto HostnameNotFound;
                }

                /* Take off one level of naming */
                while( *pbComp && *pbComp != '.' )
                    pbComp++;
                if( *pbComp )
                    pbComp++;
            }
HostnameNotFound:
            j++;
        }
    }

    if( fAuth )
    {
        pReply->Flags |= NXDOMAIN | FLG_DNS_AA;
        mmFree (device_index);
        return(1);
    }

    /* We do not handle the supplied domain */
    mmFree (device_index);
    return(0);

HostnameFound:
    /* Here we have a valid IP address in IPAddr, */
    /* a valid hostname in Hostname, the domain name */
    /* in ci_net, and the original Query name in pQuery. */

    /* Allocate the answer record */
    pRec = mmAlloc( sizeof(DNSREC) );
    if( !pRec )
    {
        pReply->Flags |= SERVFAIL;
        mmFree (device_index);
        return(1);
    }
    bzero( pRec, sizeof(DNSREC) );

    /* Initialize the answer record */
    strcpy( (char *)(pRec->Name), (char *)(pQuery->Name) );
    pRec->Type       = T_A;
    pRec->Class      = C_IN;
    pRec->Ttl        = DNS_DEFAULT_TTL;
    pRec->DataLength = 4;
    IPAddr = ntohl( IPAddr );
    pRec->Data[0] = (UINT8)((IPAddr >> 24)&0xFF);
    pRec->Data[1] = (UINT8)((IPAddr >> 16)&0xFF);
    pRec->Data[2] = (UINT8)((IPAddr >> 8)&0xFF);
    pRec->Data[3] = (UINT8)(IPAddr & 0xFF);

    /* Set the answer */
    pReply->NumAns = 1;
    pReply->pAns = pRec;

    /* Allocate an answer record for a CNAME */
    pRec = mmAlloc( sizeof(DNSREC) );
    if( !pRec )
    {
        /* OOM: Just use what we got */
        pReply->Flags |= FLG_DNS_AA;
        mmFree (device_index);
        return(1);
    }
    bzero( pRec, sizeof(DNSREC) );

    /* Initialize the answer record */
    strcpy( (char *)(pRec->Name), (char *)(pQuery->Name) );
    pRec->Type       = T_CNAME;
    pRec->Class      = C_IN;
    pRec->Ttl        = DNS_DEFAULT_TTL;

    /* ensure <Hostname>.<domain name> will fit into Data[] */
    if (strlen(Hostname) + strlen(".") + strlen(ci_net.Domain) < DNS_NAME_MAX) {
        strcpy( (char *)(pRec->Data), Hostname );
        strcat( (char *)(pRec->Data), "." );
        strcat( (char *)(pRec->Data), ci_net.Domain );
    }
    else {
        /* error: Hostname is too large, return failure */
        return (0);
    }
    pRec->DataLength = (UINT16)strlen( (char *)(pRec->Data) );

    /* Set the answer */
    pReply->NumAns = 2;
    pReply->pAns->pNext = pRec;

    /* Answer is authoritative */
    pReply->Flags |= FLG_DNS_AA;
    mmFree (device_index);
    return(1);
}

/*********************************************************************
 * FUNCTION NAME : DNSResolveByNS
 *********************************************************************
 * DESCRIPTION   :
 *  The function resolves the name.
 *
 * RETURNS       :
 *  1   -   If the answer in pReply is authoritative.
 *  0   -   If we dont handle the domain.
 *********************************************************************/
static int DNSResolveByNS( DNSREC *pQuery, DNSREPLY *pReply )
{
    CI_IPNET  ci_net;
    IPN       IPAddr;
    int       rc,i,j;
    char      *pbComp;
    DNSREC    *pRec;
    char      Hostname[CFG_HOSTNAME_MAX];
    UINT16    ifcnt;
    UINT16*   device_index;
    int       ret_code;

    /* Get the number of interfaces in the System */
    ret_code = NIMUIoctl (NIMU_GET_NUM_NIMU_OBJ, NULL, &ifcnt, sizeof(ifcnt));
    if (ret_code < 0)
    {
        DbgPrintf(DBG_INFO, "DNSResolveByNS: NIMUIOCTL (NIMU_GET_NUM_NIMU_OBJ) Failed with error code: %d\n", ret_code);
        return 0;
    }

    /* Allocate memory to get the device handles for all devices. */
    device_index = mmAlloc (sizeof(UINT16)*ifcnt);
    if(device_index == NULL)
    {
        DbgPrintf(DBG_INFO, "DNSResolveByNS: FATAL Error: Out of memory\n");
        return 0;
    }

    /* Get information about all the device handles present. */
    ret_code = NIMUIoctl (NIMU_GET_ALL_INDEX, NULL, device_index,
            sizeof(UINT16) * ifcnt);

    if (ret_code < 0)
    {
        DbgPrintf(DBG_INFO, "DNSResolveByNS: NIMUIOCTL (NIMU_GET_ALL_INDEX) Failed with error code: %d\n", ret_code);
        mmFree (device_index);
        return 0;
    }
    
    /* Scan all IF's in the CFG for network information */
    for( i=0; i<ifcnt; i++ )
    {
        j = 1;
        for(;;)
        {
            rc = CfgGetImmediate( 0, CFGTAG_IPNET, *(device_index + i), j,
                                  sizeof(ci_net), (UINT8 *)&ci_net );
            if( rc <= 0 )
                break;

            /* We only care about VIRTUAL addresses */
            if( ci_net.NetType & CFG_NETTYPE_VIRTUAL )
            {
                /* Try this network */
                pbComp = (char *)(pQuery->Name);

                while( strlen( pbComp ) )
                {
                    if( !stricmp( pbComp, ci_net.Domain ) )
                    {
                        /* This is our domain. We reply with */
                        /* our hostname contatinated with our */
                        /* domain name */
                        goto DomainFound;
                    }

                    /* Take off one level of naming */
                    while( *pbComp && *pbComp != '.' )
                        pbComp++;
                    if( *pbComp )
                        pbComp++;
                }
            }

            j++;
        }
    }

    /* We do not handle the supplied domain */
    mmFree (device_index);
    return(0);

DomainFound:
    /* Here we the query is for a local virtual domain. */
    /* We are the DNS server for this domain. */

    j = CfgGetImmediate( 0, CFGTAG_SYSINFO, CFGITEM_DHCP_HOSTNAME, 1,
                         sizeof(Hostname)-1, (UINT8 *)Hostname);
    Hostname[j] = 0;

    /* Allocate the answer record */
    pRec = mmAlloc( sizeof(DNSREC) );
    if( !pRec )
    {
        pReply->Flags |= SERVFAIL;
        mmFree (device_index);
        return(1);
    }
    bzero( pRec, sizeof(DNSREC) );

    /* Initialize the answer record */
    strcpy( (char *)(pRec->Name), (char *)(pQuery->Name) );
    pRec->Type       = T_NS;
    pRec->Class      = C_IN;
    pRec->Ttl        = DNS_DEFAULT_TTL;

    /* ensure <Hostname>.<domain name> will fit into Data[] */
    if (strlen(Hostname) + strlen(".") + strlen(ci_net.Domain) < DNS_NAME_MAX) {
        strcpy( (char *)(pRec->Data), Hostname );
        strcat( (char *)(pRec->Data), "." );
        strcat( (char *)(pRec->Data), ci_net.Domain );
    }
    else {
        /* error: Hostname is too large, return failure */
        return (0);
    }
    pRec->DataLength = (UINT16)strlen( (char *)(pRec->Data) );

    /* Set the answer */
    pReply->NumAns = 1;
    pReply->pAns = pRec;

    /* Allocate an answer record for an address */
    pRec = mmAlloc( sizeof(DNSREC) );
    if( !pRec )
    {
        /* OOM: Just use what we got */
        pReply->Flags |= FLG_DNS_AA;
        mmFree (device_index);
        return(1);
    }
    bzero( pRec, sizeof(DNSREC) );

    /* Initialize an address */
    strcpy( (char *)(pRec->Name), Hostname );
    strcat( (char *)(pRec->Name), "." );
    strcat( (char *)(pRec->Name), ci_net.Domain );
    pRec->Type       = T_A;
    pRec->Class      = C_IN;
    pRec->Ttl        = DNS_DEFAULT_TTL;
    pRec->DataLength = 4;
    IPAddr = ntohl( ci_net.IPAddr );
    pRec->Data[0] = (UINT8)((IPAddr >> 24)&0xFF);
    pRec->Data[1] = (UINT8)((IPAddr >> 16)&0xFF);
    pRec->Data[2] = (UINT8)((IPAddr >> 8)&0xFF);
    pRec->Data[3] = (UINT8)(IPAddr & 0xFF);

    /* Set the answer */
    pReply->NumAns = 2;
    pReply->pAns->pNext = pRec;

    /* Answer is authoritative */
    pReply->Flags |= FLG_DNS_AA;
    mmFree (device_index);
    return(1);
}

/*********************************************************************
 * FUNCTION NAME : DNSResolveByNS
 *********************************************************************
 * DESCRIPTION   :
 *  The function resolves the DNS query by IP Address.
 *
 * RETURNS       :
 *  1   -   If the answer in pReply is authoritative.
 *  0   -   If we dont handle the domain.
 *********************************************************************/
static int DNSResolveByAddr( DNSREC *pQuery, DNSREPLY *pReply )
{
    CI_IPNET  ci_net;
    CI_CLIENT ci_client;
    IPN       IPAddr;
    int       rc,i,j,k,tmp;
    DNSREC    *pRec;
    char      Hostname[CFG_HOSTNAME_MAX];
    uint      fAuth = 0;
    UINT16    ifcnt;
    UINT16*   device_index;
    int       ret_code;

    IPAddr = inet_addr( (char *)(pQuery->Name) );
    IPAddr = ((IPAddr>>24)&0xFF) | ((IPAddr>>8)&0xFF00) |
             ((IPAddr<<8)&0xFF0000) | ((IPAddr<<24)&0xFF000000);

    /* Get the number of interfaces in the System */
    ret_code = NIMUIoctl (NIMU_GET_NUM_NIMU_OBJ, NULL, &ifcnt, sizeof(ifcnt));
    if (ret_code < 0)
    {
        DbgPrintf(DBG_INFO,
                "DNSResolveByAddr: NIMUIOCTL (NIMU_GET_NUM_NIMU_OBJ) Failed with error code: %d\n",
                ret_code);
        return 0;
    }

    /* Allocate memory to get the device handles for all devices. */
    device_index = mmAlloc (sizeof(UINT16)*ifcnt);
    if(device_index == NULL)
    {
        DbgPrintf(DBG_INFO, "DNSResolveByAddr: FATAL Error: Out of memory\n");
        return 0;
    }

    /* Get information about all the device handles present. */
    ret_code = NIMUIoctl(NIMU_GET_ALL_INDEX, NULL, device_index,
            sizeof(UINT16) * ifcnt);

    if (ret_code < 0)
    {
        DbgPrintf(DBG_INFO,
                 "DNSResolveByAddr: NIMUIOCTL (NIMU_GET_ALL_INDEX) Failed with error code: %d\n",
                 ret_code);
        mmFree (device_index);
        return 0;
    }
    
    /* Scan all IF's in the CFG for network information */
    for( i=0; i<ifcnt; i++ )
    {
        j = 1;
        for(;;)
        {
            rc = CfgGetImmediate( 0, CFGTAG_IPNET, *(device_index + i), j,
                                  sizeof(ci_net), (UINT8 *)&ci_net );
            if( rc <= 0 )
                break;

            /* We only care about VIRTUAL addresses */
            /* See the target address on on this interface */
            if( (ci_net.NetType & CFG_NETTYPE_VIRTUAL) &&
                    (IPAddr&ci_net.IPMask) == (ci_net.IPAddr&ci_net.IPMask) )
            {
                /* Start searching for this particular address */
                bzero( Hostname, sizeof( Hostname ) );

                /* If the address is an exact match, its us!! */
                if( IPAddr == ci_net.IPAddr )
                {
                    tmp = CfgGetImmediate( 0, CFGTAG_SYSINFO,
                                           CFGITEM_DHCP_HOSTNAME, 1,
                                           sizeof(Hostname)-1,
                                           (UINT8 *)Hostname);
                    Hostname[tmp] = 0;
                    goto ipaddr_found;
                }

                /* Search all clients */
                k = 1;
                for(;;)
                {
                    rc = CfgGetImmediate( 0, CFGTAG_CLIENT, i, k,
                                     sizeof(ci_client), (UINT8 *)&ci_client );
                    if( rc <= 0 )
                        break;

                    /* Check only VALID and STATIC entries */
                    if( ((ci_client.Status == CFG_CLIENTSTATUS_VALID) ||
                        (ci_client.Status == CFG_CLIENTSTATUS_STATIC)) &&
                        ci_client.IPAddr == IPAddr )
                    {
                        strcpy( Hostname, ci_client.Hostname );
                        goto ipaddr_found;
                    }
                    k++;
                }
                fAuth = 1;
            }
            j++;
        }
    }

    if( fAuth )
    {
        pReply->Flags |= NXDOMAIN | FLG_DNS_AA;
        mmFree (device_index);
        return(1);
    }

    /* We do not handle the subnet which contains this address */
    mmFree (device_index);
    return(0);

ipaddr_found:
    /* Here we have a valid IP address in IPAddr, */
    /* a valid hostname in Hostname, the domain name */
    /* in ci_net, and the original Query name in pQuery. */

    /* Allocate the answer record */
    pRec = mmAlloc( sizeof(DNSREC) );
    if( !pRec )
    {
        pReply->Flags |= SERVFAIL;
        mmFree (device_index);
        return(1);
    }
    bzero( pRec, sizeof(DNSREC) );

    /* Initialize the answer record */
    strcpy( (char *)(pRec->Name), (char *)(pQuery->Name) );
    pRec->Type  = T_PTR;
    pRec->Class = C_IN;
    pRec->Ttl   = DNS_DEFAULT_TTL;

    /* ensure <Hostname>.<domain name> will fit into Data[] */
    if (strlen(Hostname) + strlen(".") + strlen(ci_net.Domain) < DNS_NAME_MAX) {
        strcpy( (char *)(pRec->Data), Hostname );
        strcat( (char *)(pRec->Data), "." );
        strcat( (char *)(pRec->Data), ci_net.Domain );
    }
    else {
        /* error: Hostname is too large, return failure */
        return (0);
    }
    pRec->DataLength = (UINT16)strlen( (char *)(pRec->Data) );

    /* Set the answer */
    pReply->NumAns = 1;
    pReply->pAns = pRec;

    /* Answer is authoritative */
    pReply->Flags |= FLG_DNS_AA;
    mmFree (device_index);
    return(1);
}

/*-------------------------------------------------------------------- */
/* DNSResolveExternal() */
/* Routine to build Query, and Get Reply */
/*-------------------------------------------------------------------- */
static int DNSResolveExternal( DNSREC *pQuery, DNSREPLY *pReply )
{
    static UINT16   Id = 1;             /* Packet Id */
    struct sockaddr_in sin;
    struct timeval  timeout;            /* Timeout struct for select */
    SOCKET          s;
    char            *PktBuf = 0;        /* Packet Buffer */
    IPN             IPServer;
    int             rc = 0;
    int             i,cc,serverIdx;
    DNSREPLY        *pTempReply;
    int             fHaveReply = 0;

    /* Allocate a temp reply record */
    pTempReply = mmAlloc( sizeof(DNSREPLY) );
    if( !pTempReply )
        return(0);
    bzero( pTempReply, sizeof(DNSREPLY) );

    /* Allocate the Packet Buffer */
    if( !(PktBuf = mmAlloc( MAX_PACKET )) )
        goto dnsleave2;

    /* Start with the primary server */
    serverIdx = 1;

    /* Create the Socket */
    s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if( s == INVALID_SOCKET )
        goto dnsleave;

    /* Create to binding address */
    bzero( &sin, sizeof(struct sockaddr_in));
    sin.sin_family      = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;

    if( bind( s, (struct sockaddr *)&sin, sizeof(sin) ) < 0 )
        goto dnsleave;

    /* Configure our timeout to be 2 seconds */
    timeout.tv_sec  = 2;
    timeout.tv_usec = 0;
    rc = setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)); 
    if (rc < 0) {
        goto dnsleave;
    }

    while( serverIdx < 4 )
    {
        rc = CfgGetImmediate( 0, CFGTAG_SYSINFO,
                              CFGITEM_DHCP_DOMAINNAMESERVER,
                              serverIdx, 4, (UINT8 *)&IPServer );
        if( rc != 4 )
            goto skipServer;

        /* Create to "to" address */
        sin.sin_addr.s_addr  = IPServer;
        sin.sin_port         = htons( DNS_PORT );

        /* Make at most 3 attempts */
        for( i=0; i<3; i++ )
        {
            /* Bump the Id value */
            Id++;

            /* Build the DNS RR packet */
            cc = DNSBuildRequest( (DNSHDR *)PktBuf, Id, pQuery );

            /* Send the request */
            if( sendto( s, PktBuf, cc, 0,(struct sockaddr *)&sin, sizeof(sin) ) < 0 )
                goto skipServer;

            /* Wait for the reply */
            while( (cc = (int)recv( s, PktBuf, MAX_PACKET, 0 )) > 0 )
            {
                /* Check the reply. Bump the recv count if good reply */
                rc = DNSGetReply( (DNSHDR *)PktBuf, Id, cc, pTempReply );

                /* If we got a reply, then process */
                if( rc )
                {
                    /* Free any previous reply, but not the caller's buffer */
                    if( fHaveReply )
                        DNSReplyFree( pReply, 0 );

                    /* Copy the new reply in the caller's buffer */
                    *pReply = *pTempReply;
                    fHaveReply = 1;

                    /* If the reply is not an error, or if the server is */
                    /* an authority, then leave now */
                    if( !(pReply->Flags & MASK_DNS_RCODE) ||
                            (pReply->Flags & FLG_DNS_AA) )
                        goto dnsleave;

                    /* Else we skip this server and go to next */
                    goto skipServer;
                }
            }
        }

skipServer:
        /* Here, 3 attempts have failed */
        /* Setup to use the alternate server */
        serverIdx++;
    }

    /* Set return code as to if we got any reply */
    rc = fHaveReply;

dnsleave:
    /* Close the socket */
    if( s != INVALID_SOCKET )
        fdClose( s );

    /* Free the packet buffer */
    mmFree( PktBuf );

dnsleave2:
    /* Free our temp reply buffer with mmFree (we don't free the reply data) */
    mmFree( pTempReply );

    /* Return the error code */
    return( rc );
}
