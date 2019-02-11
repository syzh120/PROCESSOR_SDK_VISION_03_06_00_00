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
 * ======== ipaddr.c ========
 *
 * Routines to aid in IP address management
 *
 */

#include <netmain.h>
#include <_stack.h>

/* The Trial Address is static only to this module */
static IPN IPTrialAddress;

/*-------------------------------------------------------------- */
/* RouteHook() */

/* This functions hooks the stack's route control messages. */
/* it looks for Duplicate IP addresses for AddNetwork() */
/*-------------------------------------------------------------- */
static void RouteHook( uint msg, UINT32 param1, UINT32 param2 )
{
    (void)param2;

    /* If the message is DUPIP and the IP in trouble is the trial IP, */
    /* then clear the address so that AddNetwork() will know there */
    /* was a problem. */
    if( msg == MSG_RTC_DUPIP && param1 == IPTrialAddress )
        IPTrialAddress = 0;
}

/*-------------------------------------------------------------- */
/* NtAddNetwork() */

/* Adds a new network binding to the indicated interface. */
/* Uses the RTCSetHookFunction() call to trap any duplicate */
/* IP errors. */

/* Returns a handle to the new binding, or NULL on error */
/*-------------------------------------------------------------- */
HANDLE NtAddNetwork( HANDLE hIF, IPN dwIP, IPN dwIPMask )
{
    HANDLE  hBind;

    /* Start calling STACK functions */
    llEnter();

    /* Hook route control messages to trap duplicate IP (DUPIP) message */
    /* If the hook fails, continue anyway */
    RTCAddHook( &RouteHook );

    /* Set IPTrialAddress to the IP host we're adding */
    IPTrialAddress = dwIP;

    /* Create the Binding */
    hBind = BindNew( hIF, dwIP, dwIPMask );

    /* If the binding was created successfully, test it */
    if( hBind )
    {
        /* Wait a half second for potential error to be detected by RouteHook(), */
        /* but don't sleep inside the llEnter() / llExit() pair */
        /* llExit();
        TaskSleep( 500 );
        llEnter();*/

        /* If the global IPTrialAddress is now NULL, there was an error */
        if( !IPTrialAddress )
        {
            /* Destroy the binding with the bad IP address */
            BindFree( hBind );
            hBind = 0;
        }
    }

    /* Un-Hook the route control message */
    RTCRemoveHook( &RouteHook );

    /* Stop calling STACK functions */
    llExit();

    /* Return the handle to the binding (if any) */
    return( hBind );
}

/*-------------------------------------------------------------- */
/* NtRemoveNetwork() */

/* Removes a network binding from the system */
/*-------------------------------------------------------------- */
void NtRemoveNetwork( HANDLE hBind )
{
    /* Start calling STACK functions */
    llEnter();

    /* Free the Network Binding */
    BindFree( hBind );

    /* Stop calling STACK functions */
    llExit();
}

/*-------------------------------------------------------------- */
/* NtAddStaticGateway() */

/* Adds a static gateway route to the system. The IP host or */
/* subnet accessible via the gateway is specified in IPTargetAddr */
/* and IPTargetMask. For a default route, both of these are NULL. */

/* Returns HANDLE to Gateway */
/*-------------------------------------------------------------- */
HANDLE NtAddStaticGateway( IPN IPTargetAddr, IPN IPTargetMask, IPN IPGateway )
{
    HANDLE hRt;

    /* Start calling STACK functions */
    llEnter();

    /* Create the route and make it STATIC */
    hRt = RtCreate( FLG_RTF_REPORT, FLG_RTE_GATEWAY | FLG_RTE_STATIC,
                    IPTargetAddr, IPTargetMask, 0, IPGateway, 0 );

    /* Since the route is STATIC, we can DeRef it here, and we */
    /* don't have to worry about keeping track of it. */
    if( hRt )
        RtDeRef( hRt );

    /* Stop calling STACK functions */
    llExit();

    /* Return an indication of success */
    return( hRt );
}

/*-------------------------------------------------------------- */
/* NtRemoveStaticGateway() */

/* Removes a STATIC route generated from AddStaticGateway() by */
/* walking the route tree. */
/*-------------------------------------------------------------- */
int NtRemoveStaticGateway( IPN IPTarget )
{
    HANDLE hRt;
    int    removed = 0;

    /* Start calling STACK functions */
    llEnter();

    /* Start walking the tree */
    hRt = RtWalkBegin();

    /* Search while there's more to search */
    while( hRt )
    {
        /* The IP target must match and it must be STATIC GATEWAY */
        if( (IPTarget==RtGetIPAddr(hRt)) && ((RtGetFlags( hRt )
            & (FLG_RTE_STATIC|FLG_RTE_GATEWAY)) ==
            (FLG_RTE_STATIC|FLG_RTE_GATEWAY)) )
        {
            /* Remove this route and quit walking */
            RtRemove( hRt, FLG_RTF_REPORT, RTC_NETUNREACH );
            removed = 1;
            break;
        }
        hRt = RtWalkNext( hRt );
    }

    RtWalkEnd( hRt );

    llExit();

    /* Return with removed status (yes or no) */
    return( removed );
}

/*-------------------------------------------------------------- */
/* NtIfIdx2Ip() */

/* Converts an IfIdx to an active IP Host address */
/* Returns 0 if conversion failed. */
/*-------------------------------------------------------------- */
int NtIfIdx2Ip( uint IfIdx, IPN *pIPAddr )
{
    HANDLE hEth;
    IPN    IPAddr;

    {
        NIMU_IF_REQ ifreq;

        /* Initialize the NIMU Interface Object. */
        mmZeroInit (&ifreq, sizeof(NIMU_IF_REQ));

        /*
         *  We are interested in receiving the handle associated with 'index'
         *  Item
         */
        ifreq.index = IfIdx;
        if (NIMUIoctl(NIMU_GET_DEVICE_HANDLE, &ifreq, (void *)&hEth,
                sizeof(HANDLE)) < 0)
            return -1;

        IPAddr = BindIF2IPHost(hEth);
    }

    if( !hEth || !IPAddr )
        return(0);

    if( pIPAddr )
        *pIPAddr = IPAddr;

    return(1);
}

/*********************************************************************
 * FUNCTION NAME : NtGetPublicHost
 *********************************************************************
 * DESCRIPTION   :
 *  The function gets the public host information
 *
 * RETURNS       :
 *  1   -   Information has been found.
 *  0   -   Unable to find the information.
 *********************************************************************/
int NtGetPublicHost( IPN *pIPAddr, uint MaxSize, UINT8 *pDomain )
{
    int         i,j,rc;
    int         gotone = 0;
    CI_IPNET    ci_net;
    UINT16      num_nimu_device;
    int         ret_code;
    UINT16*     device_index;

    /* Get the number of NIMU devices which exist in the System */
    ret_code = NIMUIoctl (NIMU_GET_NUM_NIMU_OBJ, NULL, &num_nimu_device, sizeof(num_nimu_device));
    if (ret_code < 0)
    {
        DbgPrintf(DBG_INFO, "NtGetPublicHost: NIMUIOCTL (NIMU_GET_NUM_NIMU_OBJ) Failed with error code: %d\n", ret_code);
        return 0;
    }

    /* Allocate memory to get the device handles for all devices. */
    device_index = mmAlloc (sizeof(UINT16)*num_nimu_device);
    if(device_index == NULL)
        return 0;

    /* Get information about all the device handles present. */
    ret_code = NIMUIoctl (NIMU_GET_ALL_INDEX, NULL, device_index,sizeof(UINT16)*num_nimu_device);
    if (ret_code < 0)
    {
        DbgPrintf(DBG_INFO, "NtGetPublicHost: NIMUIOCTL (NIMU_GET_ALL_INDEX) Failed with error code: %d\n", ret_code);
        mmFree (device_index);
        return 0;
    }

    /* Scan all IF's in the CFG for network information */
    for( i=0; i<num_nimu_device; i++ )
    {
        j = 1;
        for(;;)
        {
            /* Try and get a IP network address */
            rc = CfgGetImmediate( 0, CFGTAG_IPNET, *(device_index+i), j,
                                  sizeof(ci_net), (UINT8 *)&ci_net );
            if( rc <= 0 )
                break;

            /* We got something */
            gotone = 1;

            /* If this net is not virtual, break */
            if( !(ci_net.NetType & CFG_NETTYPE_VIRTUAL) )
                goto GOTPUBLIC;

            j++;
        }
    }

GOTPUBLIC:
    /* If we have an address, return some info */
    if( gotone )
    {
        /* If the user wants the IP address, return it */
        if( pIPAddr )
           *pIPAddr = ci_net.IPAddr;

        /* If the user wants the domain, return it */
        if( MaxSize && pDomain )
        {
            if( strlen(ci_net.Domain) < MaxSize )
                strcpy( (char *)pDomain, ci_net.Domain );
            else
                strncpy( (char *)pDomain, ci_net.Domain, MaxSize-1 );
        }
    }

    /* Cleanup the allocated memory before returning. */
    mmFree (device_index);
    return( gotone );
}

/*-------------------------------------------------------------- */
/* NtIPN2Str */

/* Quick routine to print out an IPN addr */
/*-------------------------------------------------------------- */
void NtIPN2Str( IPN IPAddr, char *str )
{
    IPAddr = htonl( IPAddr );
    NDK_sprintf( str, "%d.%d.%d.%d",
             (UINT8)((IPAddr>>24)&0xFF), (UINT8)((IPAddr>>16)&0xFF),
             (UINT8)((IPAddr>>8)&0xFF), (UINT8)(IPAddr&0xFF) );
}

