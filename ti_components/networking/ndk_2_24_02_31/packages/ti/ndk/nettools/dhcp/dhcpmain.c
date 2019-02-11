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
 * ======== dhcpmain.c ========
 *
 * Simple DHCP Client Utility
 *
 */

#include "dhcp.h"

/*---------------------------------------------------------------- */
/* DHCPOpen() */

/* This function is called to initiate DHCP control of the IP */
/* address binding on the specified interface. */

/* Returns a HANDLE to a DHCP instance structure which is used in */
/* calls to other DHCP functions like DHCPClose(). */
/*---------------------------------------------------------------- */
HANDLE DHCPOpen( NTARGS *pNTA, NTPARAM_DHCP *pNTP )
{
    DHCPLEASE *pLease;
    int i;

    /* We only support IFIDX calling mode */
    if( pNTA->CallMode != NT_MODE_IFIDX )
        return(0);

    /* Allocate Instance */
    pLease = mmBulkAlloc( sizeof(DHCPLEASE) );
    if( !pLease )
        return(0);

    /* Initialize Instance */
    bzero( pLease, sizeof( DHCPLEASE ) );

    {
        NIMU_IF_REQ if_req;
        int         ret_code;

        /* Initialize the interface request. */
        bzero(&if_req, sizeof(NIMU_IF_REQ));

        /* Get the interface index. */
        pLease->IfIdx = pNTA->IfIdx;

        /* Get the device MAC Address */
        if_req.index = pLease->IfIdx;
        ret_code = NIMUIoctl(NIMU_GET_DEVICE_MAC, &if_req, &pLease->MacAddress,
                sizeof(pLease->MacAddress));
        if (ret_code < 0)
        {
            DbgPrintf(DBG_INFO,
                    "DHCPOpen: NIMUIOCTL (NIMU_GET_DEVICE_MAC) Failed with error code: %d\n",
                    ret_code);
            return 0;
        }
    }

    /* Save the Callback Information */
    pLease->hCb = pNTA->hCallback;
    pLease->pCb = pNTA->pCb;

    /* Copy Over the HostName - function returns bytes copied */
    i = CfgGetImmediate( 0, CFGTAG_SYSINFO, CFGITEM_DHCP_HOSTNAME,
                         1, HOSTNAME_LENGTH-1, (UINT8 *)pLease->HostName );
#if DEBUGON
    DbgPrintf(DBG_INFO,
            "DHCPOpen: Warning: HOSTNAME for DHCP client may be invalid!\r\n");
#endif

    pLease->HostName[i] = 0;

    /* Get the DHCP Client Information if present. */
    i = CfgGetImmediate( 0, CFGTAG_SYSINFO, CFGITEM_DHCP_CLIENT_OPTION,
                         1, HOSTNAME_LENGTH-1, pLease->ClientID);
    pLease->ClientID[i] = 0;

    /* Set initial stat to "INIT" */
    pLease->StateNext = INIT;

    /* Copy the options from the parameters */
    pLease->options_len = 0; /* indicate that no options were passed in */
    if ( pNTP->len != 0 )
    {
        if( pNTP->len > DHCP_MAX_OPTIONS )
            pNTP->len = DHCP_MAX_OPTIONS;

        if( (pLease->pOptions = mmAlloc(sizeof(UINT8) * pNTP->len)) )
        {
            bcopy(pNTP->pOptions, pLease->pOptions, pNTP->len);
            pLease->options_len = pNTP->len;
        }
    }

    /* Initialize the socket to "None" */
    pLease->Sock = INVALID_SOCKET;

    /* Create our DHCP task */
    pLease->dhcpTASK = TaskCreate( (void(*)())dhcpState, "DHCPclient",
                                   OS_TASKPRINORM, OS_TASKSTKLOW,
                                   (UINT32)pLease, 0, 0 );

    /* Return the handle to our instance */
    return( pLease );
}

/*---------------------------------------------------------------- */
/* DHCPClose() */

/* This function terminates DHCP control and free the supplied */
/* instance handle. */
/*---------------------------------------------------------------- */
void DHCPClose( HANDLE hDHCP )
{
    DHCPLEASE *pLease = (DHCPLEASE *)hDHCP;

    /* free the options */
    if( pLease->pOptions )
        mmFree( pLease->pOptions );

    /* Kill our DHCP task if needed */
    if( pLease->dhcpTASK )
    {
        fdCloseSession( pLease->dhcpTASK );
        TaskDestroy( pLease->dhcpTASK );
    }

    /* Close the socket if we have one open */
    dhcpSocketClose( pLease );

    /* Unload the gateway address if we've installed one */
    if( pLease->hCE_IPGate )
        CfgRemoveEntry( 0, pLease->hCE_IPGate );

    /* Unload the address if we've installed one */
    if( pLease->hCE_IPAddr )
        CfgRemoveEntry( 0, pLease->hCE_IPAddr );

    /* Free the instance */
    mmBulkFree( pLease );
}

