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
 * ======== condns.c ========
 *
 * Basic console functions
 *     ConCmdLookup  - Name server lookup
 *     ConStrToIPN   - Name/IP String to IPN
 *
 */

#include <netmain.h>
#include <_stack.h>
#include "console.h"

#ifndef _INCLUDE_IPv6_CODE

/*------------------------------------------------------------------------- */
/* ConCmdLookup() */
/* Function to lookup host */
/*------------------------------------------------------------------------- */
void ConCmdLookup( int ntok, char *tok1 )
{
    char   *buffer;
    struct in_addr in1;
    int    retcode;

    /* Check for 'stat ip' */
    if( ntok == 0 )
    {
        ConPrintf("\n[NsLookup Command]\n");
        ConPrintf("\nCalled to lookup an official hostname and IP address\n");
        ConPrintf("from a supplied hostname or IP address\n\n");
        ConPrintf("nslookup hostname            - Resolve 'hostname' on default domain\n");
        ConPrintf("nslookup hostname.home1.net  - Resolve 'hostname.home1.net'\n");
        ConPrintf("nslookup x.x.x.x             - Resolve IP address\n\n");
    }
    else if( ntok == 1 )
    {
        /* All the DNS functions need a scrap buffer */
        buffer = mmAlloc( 512 );

        if( buffer )
        {
            /* We can treat buffer as a HOSTENT structure after */
            /* DNSGetHostByXxx calls */
            HOSTENT *phe = (HOSTENT *)buffer;

            /* See if tok1 is an IP address */
            if( inet_aton( tok1, &in1 ) )
                retcode = DNSGetHostByAddr( in1.s_addr, buffer, 512 );
            else
                retcode = DNSGetHostByName( tok1, buffer, 512 );

            if( retcode )
            {
                ConPrintf("DNSGetHostByName returned (%d) %s\n",
                           retcode, DNSErrorStr(retcode) );
                if( retcode == SOCKETERROR )
                    ConPrintf("Socket Error %d\n",fdError());
            }
            else
            {
                if( phe->h_name )
                    ConPrintf("Hostname = %s\n",phe->h_name);
                ConPrintf("AddrCnt  = %d\n",phe->h_addrcnt);
                for( retcode = 0; retcode < phe->h_addrcnt; retcode++ )
                {
                    ConPrintf("IPAddr = ");
                    ConPrintIPN(phe->h_addr[retcode]);
                    ConPrintf("\n");
                }
            }
            ConPrintf("\n");
            mmFree( buffer );
        }
    }
    else
        ConPrintf("\nIllegal argument. Type 'nslookup' for help\n");
}

#else

/** 
 *  @b Description
 *  @n  
 *      This function handles IPv4 DNS resolution commands
 *      from the console.
 *
 *  @param[in]   ntok
 *      Number of arguments available for parsing. This is 
 *      typically equal to 1. It holds the hostname/IPv4
 *      address to be resolved.
 *
 *  @param[in]  tok1
 *      The HostName/IPv4 Address that needs to be resolved
 *      in String format.
 *
 *  @retval
 *      None
 */
void ConCmdLookup( int ntok, char *tok1 )
{
    char   *buffer;
    struct in_addr in1;
    int    retcode;
    IPN    IPTmp;

    /* Check for 'stat ip' */
    if( ntok == 0 )
    {
        ConPrintf("\n[NsLookup Command]\n");
        ConPrintf("\nCalled to lookup an official hostname and IP address\n");
        ConPrintf("from a supplied hostname or IP address\n\n");
        ConPrintf("nslookup hostname            - Resolve 'hostname' on default domain\n");
        ConPrintf("nslookup hostname.home1.net  - Resolve 'hostname.home1.net'\n");
        ConPrintf("nslookup x.x.x.x             - Resolve IP address\n\n");
    }
    else if( ntok == 1 )
    {
        /* All the DNS functions need a scrap buffer */
        buffer = mmAlloc( 512 );

        if( buffer )
        {
            /* We can treat buffer as a HOSTENT structure after */
            /* DNSGetHostByXxx calls */
            HOSTENT *phe = (HOSTENT *)buffer;

            /* See if tok1 is an IP address */
            if( inet_aton( tok1, &in1 ) )
                retcode = DNSGetHostByAddr( in1.s_addr, buffer, 512 );
            else
                retcode = DNSGetHostByName( tok1, buffer, 512 );

            if( retcode )
            {
                ConPrintf("DNSGetHostByName returned (%d) %s\n",
                           retcode, DNSErrorStr(retcode) );
                if( retcode == SOCKETERROR )
                    ConPrintf("Socket Error %d\n",fdError());
            }
            else
            {
                if( phe->h_name )
                    ConPrintf("Hostname = %s\n",phe->h_name);
                ConPrintf("AddrCnt  = %d\n",phe->h_addrcnt);
                for( retcode = 0; retcode < phe->h_addrcnt; retcode++ )
                {
                    IPTmp = (IPN)RdNet32(phe->h_addr_list[retcode]);
                    ConPrintf("IPAddr = ");
                    ConPrintIPN(IPTmp);
                    ConPrintf("\n");
                }
            }
            ConPrintf("\n");
            mmFree( buffer );
        }
    }
    else
        ConPrintf("\nIllegal argument. Type 'nslookup' for help\n");
}

/** 
 *  @b Description
 *  @n  
 *      This function handles IPv6 DNS resolution commands
 *      from the console.
 *
 *  @param[in]   ntok
 *      Number of arguments available for parsing. This is 
 *      typically equal to 1. It holds the hostname/IPv6
 *      address to be resolved.
 *
 *  @param[in]  tok1
 *      The HostName/IPv6 Address that needs to be resolved
 *      in String format.
 *
 *  @retval
 *      None
 */
void ConCmdLookupIPv6( int ntok, char *tok1 )
{
    char   *buffer;
    int    retcode;
    IPN    IPTmp;
    IP6N   IPv6Tmp;

    /* We expect either an IPv6 address/Hostname to be passed.
     * Validate the input.
     */
    if( ntok == 0 )
    {
        ConPrintf("\n[v6nsLookup Command]\n");
        ConPrintf("\nCalled to resolve a hostname to IPv6 address / \n");
        ConPrintf("a given IPv6 address to its corresponding hostname \n\n");
        ConPrintf("v6nslookup hostname            - Resolve 'hostname' to an IPv6 address on default domain (ip6.arpa)\n");
        ConPrintf("v6nslookup hostname.home1.net  - Resolve 'hostname.home1.net' to an IPv6 address\n");
        ConPrintf("v6nslookup <ipv6_address>      - Resolve an IPv6 address to its corresponding hostname\n\n");
    }
    else if( ntok == 1 )
    {
        /* All the DNS functions need a scrap buffer */
        buffer = mmAlloc( 512 );

        if( buffer )
        {
            /* We can treat buffer as a HOSTENT structure after
             * DNSGetHostByXxx calls
             */
            HOSTENT *phe = (HOSTENT *)buffer;

            /* See if tok1 is an IPv6 address. If so,
             * call DNSGetHostByAddr2 for reverse lookup.
             * If tok1 is a hostname call DNSGetHostByName 
             * for forward lookup.
             */
            if( !IPv6StringToIPAddress(tok1, &IPv6Tmp) )
                retcode = DNSGetHostByAddr2( IPv6Tmp, buffer, 512 );
            else 
                retcode = DNSGetHostByName2( tok1, AF_INET6, buffer, 512 );

            if( retcode )
            {
                /* DNS resolution failed. Print the error details. */
                ConPrintf("DNSGetHostByName2 returned (%d) %s\n",
                           retcode, DNSErrorStr(retcode) );
                if( retcode == SOCKETERROR )
                    ConPrintf("Socket Error %d\n",fdError());
            }
            else
            {
                /* DNS resolution succeeded. Print out the results. */
                if( phe->h_name )
                    ConPrintf("Hostname = %s\n",phe->h_name);
                ConPrintf("AddrCnt  = %d\n", phe->h_addrcnt);
                if(phe->h_addrtype == AF_INET)
                {
                    for( retcode = 0; retcode < phe->h_addrcnt; retcode++ )
                    {
                        IPTmp = *(IPN *)phe->h_addr_list[retcode]; 
                        ConPrintf("IPv4 Addr = ");
                        ConPrintIPN(IPTmp);
                        ConPrintf("\n");
                    }
                }
                else if(phe->h_addrtype == AF_INET6)
                {
                    for( retcode = 0; retcode < phe->h_addrcnt; retcode++ )
                    {
                        IPv6Tmp = *(IP6N *)phe->h_addr_list[retcode]; 
                        ConPrintf("IPv6 Addr = ");
                        ConIPv6DisplayIPAddress(IPv6Tmp);
                        ConPrintf("\n");
                    }
                }
            }
            ConPrintf("\n");
            mmFree( buffer );
        }
    }
    else
        ConPrintf("\nIllegal argument. Type 'v6nslookup' for help\n");
}
#endif

/*------------------------------------------------------------------------- */
/* ConStrToIPN() */
/* Function to return an IP address from a supplied string. It is very */
/* similar to the NSLOOKUP command. */
/*------------------------------------------------------------------------- */
int ConStrToIPN( char *str, IPN *pIPN )
{
    char   *buffer;
    struct in_addr in1;
    int    retcode = 0;

    /* If the string is an IP, we're done */
    if( inet_aton( str, &in1 ) )
    {
        *pIPN = in1.s_addr;
        return(1);
    }

    /* All the DNS functions need a scrap buffer */
    buffer = mmAlloc( 512 );
    if( buffer )
    {
        /* We can treat buffer as a HOSTENT structure after */
        /* DNSGetHostByXxx calls */
        HOSTENT *phe = (HOSTENT *)buffer;

        retcode = DNSGetHostByName( str, buffer, 512 );
        if( !retcode && phe->h_addrcnt )
        {
#ifndef _INCLUDE_IPv6_CODE
            *pIPN = phe->h_addr[0];
#else
            /*
             *  phe is written using WrNet32 macro and may not be aligned.  Use
             *  RdNet32 macro to read it back (handles unaligned IP addresses).
             */
            *pIPN = RdNet32(phe->h_addr_list[0]);
#endif
            retcode = 1;
        }
        else
            retcode = 0;

        mmFree( buffer );
    }
    return( retcode );
}

