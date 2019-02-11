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
 * ======== natsrv.c ========
 *
 * NAT Control Utility
 *
 */

#include <netmain.h>
#include <_stack.h>

static int Enabled = 0;

/*---------------------------------------------------------------- */
/* NATOpen() */

/* This function is called to enable the NAT service. */
/* This service utilizes the virtual and external network information */
/* using the configuration system. If the configuration system was not */
/* used to create the network records, this function will fail. */

/* Returns a HANDLE to a NAT instance structure which is used in */
/* calls to other NAT functions like NATClose(). */
/*---------------------------------------------------------------- */
HANDLE NATOpen( NTARGS *pNTA, NTPARAM_NAT *pNTP )
{
    CI_IPNET ci_net;
    IPN      IPAddr,IPMask,IPServ;
    uint     MTU;
    int      rc,i;

    /* Only 1 instance */
    if( Enabled )
        return(0);

    /* We only support IFIDX calling mode */
    if( pNTA->CallMode != NT_MODE_IFIDX )
        return(0);

    IPServ = 0;
    IPAddr = pNTP->IPVirt;
    IPMask = pNTP->IPMask;
    MTU    = pNTP->MTU;

    /* Scan the IF for a physical IP address */
    i = 1;
    for(;;)
    {
        rc = CfgGetImmediate( 0, CFGTAG_IPNET, pNTA->IfIdx, i,
                              sizeof(ci_net), (UINT8 *)&ci_net );
        if( rc <= 0 )
            break;

        /* We need an EXTERNAL address */
        if( !(ci_net.NetType & CFG_NETTYPE_VIRTUAL) )
        {
            IPServ = ci_net.IPAddr;
            break;
        }

        i++;
    }

    /* If we don't have a server, addr or mask, quit */
    if( !IPServ || !IPMask || !IPAddr )
        return(0);

    /* If our server is in the NAT group, quit */
    if( (IPServ & IPMask) == (IPAddr & IPMask) )
        return(0);

    /* If the MTU is out of the 64 to 1500 range, quit */
    if( MTU < 64 || MTU > 1500 )
        return(0);

    llEnter();
    /* Set the IP Firewall filter */
    IPFilterSet( IPAddr, IPMask );
    /* Configure NAT at the stack level */
    NatSetConfig( IPAddr, IPMask, IPServ, MTU );
    llExit();

    /* Enable Filtering in the stack */
    _ipcfg.IpFilterEnable  = 1;

    /* Enable NAT in the stack */
    _ipcfg.IpNatEnable  = 1;

    Enabled = 1;

    return((HANDLE)1);
}

/*---------------------------------------------------------------- */
/* NATClose() */

/* This function terminates NAT control */
/*---------------------------------------------------------------- */
void NATClose( HANDLE hNAT )
{
    (void)hNAT;

    if( Enabled )
    {
        _ipcfg.IpNatEnable    = 0;
        _ipcfg.IpFilterEnable = 0;
    }
    Enabled = 0;
}

