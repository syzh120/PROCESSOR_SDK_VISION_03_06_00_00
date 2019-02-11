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
 * ======== conroute.c ========
 *
 * Basic Console Functions
 *      ConCmdRoute     -   Route Command
 *
 */

#include <netmain.h>
#include <_stack.h>
#include "console.h"

static void DumpRouteTable();
static char *RouteErr = "\nError in command line. Type 'route' for help\n";

/*------------------------------------------------------------------------- */
/* ConCmdRoute() */
/* Function to print, add, and remove GATEWAY routes */
/*------------------------------------------------------------------------- */
void ConCmdRoute( int ntok, char *tok1, char *tok2, char *tok3, char *tok4 )
{
    /* Check for 'route print' */
    if( ntok == 1 && !stricmp( tok1, "print" ) )
        DumpRouteTable();
    /* Check for 'route add x.x.x.x x.x.x.x x.x.x.x' */
    else if( ntok == 4 && !stricmp( tok1, "add" ) )
    {
        struct in_addr in1;
        struct in_addr in2;
        struct in_addr in3;

        if( inet_aton(tok2,&in1)&&inet_aton(tok3,&in2)&&inet_aton(tok4,&in3) )
        {
            if( (in1.s_addr & in2.s_addr) != in1.s_addr )
                ConPrintf("\nIllegal destination/mask combination\n\n");
            else if( NtAddStaticGateway( in1.s_addr, in2.s_addr, in3.s_addr ) )
                ConPrintf("\nRoute created\n\n");
            else
                ConPrintf("\nRoute not created\n\n");
        }
        else
            ConPrintf(RouteErr);
    }
    /* Check for 'route delete x.x.x.x' */
    else if( ntok == 2 && !stricmp( tok1, "delete" ) )
    {
        struct in_addr in1;

        if( inet_aton(tok2,&in1) )
        {
            if( NtRemoveStaticGateway( in1.s_addr ) )
                ConPrintf("\nRoute removed\n\n");
            else
                ConPrintf("\nRoute not found\n\n");
        }
        else
            ConPrintf(RouteErr);
    }
    else if( ntok == 0 )
    {
        ConPrintf("\n[Route Command]\n");
        ConPrintf("\nCalled to print, add, or delete routes. Only IP addresses");
        ConPrintf("\nmay be used and they must in the traditional x.x.x.x format.\n\n");
        ConPrintf("route print                       - Print out the route table\n");
        ConPrintf("route add    IpDest IpMask IpGate - Create new gateway route\n");
        ConPrintf("route delete IpDest               - Delete gateway route\n\n");
    }
    else
        ConPrintf(RouteErr);
}

/*------------------------------------------------------------------------- */
/* DumpRouteTable() */
/* Function to dump the contents of the route table */
/*------------------------------------------------------------------------- */
static void DumpRouteTable()
{
    HANDLE hRt,hIF,hLLI;
    uint   wFlags,IFType,IFIdx;
    UINT32 IPAddr,IPMask;
    UINT8  MacAddr[6];
    char   str[40];

    /* We must use llEnter() and llExit() when calling stack functions */
    /* These will be used to bracket all calls to the stack */
    /* Note: This is a bit of an overkill when getting route properties, */
    /*       since the route can't go away while we hold a reference to */
    /*       it (which the walk functions do for us), but note that it is */
    /*       *very* important we call llExit() before calling any applicaions */
    /*       API functions (like sockets). In this case, ConPrintf() would */
    /*       hang if we called it in an llEnter()/llExit() pair. */

    /* Also Note: The flags printed here differ from the standard Unix */
    /*            definition in that L means "Local IP Address" and not */
    /*            "contains link-layer address". In this system, all */
    /*            host routes that aren't CLONING, GATEWAY, or LOCAL routes */
    /*            have a link-layer address (Unix"L" = H && !(G||C||L) ), */
    /*            so the UnixL is redundant. However it is useful to know */
    /*            what IP addresses are local to the system, and for this */
    /*            we use "L". */

    /* Walk the Route Tree */

    /* Start walking the tree */
    llEnter();
    hRt = RtWalkBegin();
    llExit();

    ConPrintf("\nAddress          Subnet Mask      Flags   Gateway\n");
    ConPrintf("---------------  ---------------  ------  -----------------\n");

    /* If the first call fails, there are no routes in the tree */
    if( !hRt )
        ConPrintf("The route table is empty\n");

    /* While there are routes, print the route information */
    while( hRt )
    {
        /* Get the IP addess and IP mask and flags of the route */
        llEnter();
        IPAddr = RtGetIPAddr( hRt );
        IPMask = RtGetIPMask( hRt );
        wFlags = RtGetFlags( hRt );
        hIF    = RtGetIF( hRt );
        if( hIF )
        {
            IFType = IFGetType(hIF);
            IFIdx  = IFGetIndex(hIF);
        }
        else
            IFType = IFIdx = 0;
        llExit();

        /* Print address and mask */
        NtIPN2Str( IPAddr, str );
        ConPrintf( "%-15s  ",str);
        NtIPN2Str( IPMask, str );
        ConPrintf( "%-15s  ",str);

        /* Decode flags */
        if( wFlags & FLG_RTE_UP )
            ConPrintf("U");
        else
            ConPrintf(" ");
        if( wFlags & FLG_RTE_GATEWAY )
            ConPrintf("G");
        else
            ConPrintf(" ");
        if( wFlags & FLG_RTE_HOST )
            ConPrintf("H");
        else
            ConPrintf(" ");
        if( wFlags & FLG_RTE_STATIC )
            ConPrintf("S");
        else
            ConPrintf(" ");
        if( wFlags & FLG_RTE_CLONING )
            ConPrintf("C");
        else
            ConPrintf(" ");
        if( wFlags & FLG_RTE_IFLOCAL )
            ConPrintf("L");
        else
            ConPrintf(" ");

        /* If the route is a gateway, print the gateway IP address as well */
        if( wFlags & FLG_RTE_GATEWAY )
        {
            llEnter();
            IPAddr = RtGetGateIP( hRt );
            llExit();
            NtIPN2Str( IPAddr, str );
            ConPrintf( "  %-15s  ",str);
        }
        /* Else if non-local host route on Ethernet, print ARP entry */
        else if( IFType == HTYPE_ETH &&
                 (wFlags&FLG_RTE_HOST) && !(wFlags&FLG_RTE_IFLOCAL) )
        {

            /* The stack has a MAC address if it has an LLI (link-layer info) */
            /* object, and LLIGetMacAddr returns 1. */
            llEnter();
            if( !(hLLI = RtGetLLI( hRt )) || !LLIGetMacAddr( hLLI, MacAddr, 6 ) )
                llExit();
            else
            {
                llExit();
                ConPrintf( "  %02X:%02X:%02X:%02X:%02X:%02X",
                           MacAddr[0], MacAddr[1], MacAddr[2],
                           MacAddr[3], MacAddr[4], MacAddr[5] );
            }

        }
        /* Else just print out the interface */
        else if( IFIdx )
        {
            if( wFlags & FLG_RTE_IFLOCAL )
                ConPrintf( "  local (if-%d)", IFIdx );
            else 
                ConPrintf( "  if-%d", IFIdx );
        }

        ConPrintf("\n");

        llEnter();
        hRt = RtWalkNext( hRt );
        llExit();
    }
    llEnter();
    RtWalkEnd( 0 );
    llExit();
    ConPrintf("\n");
}

